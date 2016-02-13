/*
 * This file is part of MobilECG, an open source clinical grade Holter
 * ECG. For more information visit http://mobilecg.hu
 *
 * Copyright (C) 2016  Robert Csordas, Peter Isza
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include "EcgArea.h"
#include "log.h"
#include "EcgProcessor.h"

EcgArea::EcgArea():
        pixelDensity(100,100){

    grid.setZOrder(10);
    drawableList.push_back(&grid);

    //Use separater for loops to avoid mixing the order of
    //curves, circles and texts to eliminate unnecessary shader switches.
    for (int a=0; a<ECG_CURVE_COUNT; a++) {
        drawableList.push_back(&ecgCurves[a]);
        ecgCurves[a].setZOrder(1);
    }

    for (int a=0; a<ECG_CURVE_COUNT; a++) {
        drawableList.push_back(&endpointCircles[a]);
        endpointCircles[a].setZOrder(0);
    }

    for (int a=0; a<ECG_CURVE_COUNT; a++) {
        drawableList.push_back(&labels[a]);
        labels[a]
                .setColor(Image::BLACK)
                .setTextSizeMM(2.5);
    }

    drawableList.push_back(&devLabel);
    devLabel
        .setColor(Image::GREY)
        .setTextSizeMM(3.5);

    padInCm=0.5;
    ecgCmPerMv = 2.0;
    ecgCmPerSec = 2.5;
    lastSampleFrequency=0;

    drawableList.push_back(&disconnectedLabel);
    disconnectedLabel.setColor(Image::GREY);
    disconnectedLabel.setTextSizeMM(3.5);

    deviceDisconnected();
}

EcgArea &EcgArea::instance(){
    static EcgArea area;
    return area;
}

void EcgArea::init(AAssetManager *assetManager){
    redraw();
    DrawableGroup::init(assetManager);
}

void EcgArea::rescale(){
    lastSampleFrequency=EcgProcessor::instance().getSamplingFrequency();

    float xScale = ecgCmPerSec * pixelDensity.x / lastSampleFrequency;
    float yScale = ecgCmPerMv * pixelDensity.y;

    for (int a=0; a<ECG_CURVE_COUNT; a++) {
        ecgCurves[a].setScale(xScale, yScale);
        labels[a].drawText(labelText[a]);
    }

    disconnectedLabel.drawText("DISCONNECTED");
    devLabel.drawText("DEVELOPMENT VERSION " GIT_HASH " - " __DATE__ );

}

void EcgArea::constructLayout(){
    int r,c;
    if (activeArea.width()<activeArea.height()){
        c=2;
    } else {
        c=3;
    }

    r=(ECG_CURVE_COUNT+c-1)/c;

    disconnectedLabel.setPosition((screenSize.w - disconnectedLabel.getWidth())/2, screenSize.h/2 - disconnectedLabel.getHeight());

    int padInPixels=padInCm*pixelDensity.x;
    int curveWidth=(activeArea.width()-(c-1)*padInPixels)/c;

    const int yStep = activeArea.height()/r;
    const int xStep = curveWidth+padInPixels;


    const int bottomCurves = r % 3;
    const int topCurves = r - bottomCurves;

    const int topCurveCount = topCurves * c;

    for (int a=0; a<ECG_CURVE_COUNT; a++){
        ecgCurves[a].setLength(curveWidth);

        const bool bottom = a >= topCurveCount;

        const int x=bottom ? (c -1  - ((a - topCurveCount) / bottomCurves)) : (a / topCurves);
        const int y=bottom ? ((a - topCurveCount) % bottomCurves + topCurves) : (a % topCurves);

        const int xCoord=activeArea.left() + x*xStep;
        const int yCoord=activeArea.top() + y*yStep + yStep/2;

        ecgCurves[a].setPosition(xCoord, yCoord);
        labels[a].setPosition(xCoord, yCoord - 0.8*pixelDensity.y);
    }

    devLabel.setPosition(
            pixelDensity.x*0.0,
            screenSize.h - devLabel.getHeight()
    );
}

void EcgArea::contextResized(int w, int h){
    int deleteX=calculateUnalignedArea(w, pixelDensity.x);
    int deleteY=calculateUnalignedArea(h, pixelDensity.y);

    screenSize.w=w;
    screenSize.h=h;

    activeArea=Rect(deleteX/2, deleteY/2, w-deleteX+1, h+1-deleteY);

    redraw();
    DrawableGroup::contextResized(w,h);
    constructLayout();
}


int EcgArea::calculateUnalignedArea(int size, float dpcm){
    int unalignedPixels=(((float)size) / dpcm);
    return size-(int)(unalignedPixels*dpcm);
}

const Rect &EcgArea::getActiveArea(){
    return activeArea;
}

const Vec2<float> &EcgArea::getPixelDensity(){
    return pixelDensity;
}

void EcgArea::setPixelDensity(const Vec2<float> &pPixelDensity){
    pixelDensity=pPixelDensity;
    rescale();
}

void EcgArea::putData(GLfloat *data, int nChannels, int nPoints, int stride){
    for (int a=0; a<12; a++) {
        ecgCurves[a].put(data + stride*a, nPoints);
        endpointCircles[a].setPosition(ecgCurves[a].endpointCoordinates());
    }
}

void EcgArea::draw(){
    if (lastSampleFrequency!=EcgProcessor::instance().getSamplingFrequency()){
        rescale();
    }
    DrawableGroup::draw();
    redrawNeeded=false;
}

void EcgArea::redraw(){
    redrawNeeded=true;
}

bool EcgArea::isRedrawNeeded(){
    return redrawNeeded;
}

void EcgArea::setContentVisible(bool visible){
    for (int a=0; a<ECG_CURVE_COUNT; a++) {
        endpointCircles[a].setVisible(visible);
        ecgCurves[a].setVisible(visible);
        labels[a].setVisible(visible);
    }
}

void EcgArea::deviceConnected(){
    setContentVisible(true);
    disconnectedLabel.setVisible(false);
}

void EcgArea::deviceDisconnected(){
    setContentVisible(false);
    disconnectedLabel.setVisible(true);
}