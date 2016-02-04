#include "EcgArea.h"
#include "log.h"
#include "EcgProcessor.h"

EcgArea::EcgArea():
        pixelDensity(100,100){

    grid.setZOrder(10);
    drawableList.push_back(&grid);

    for (int a=0; a<ECG_CURVE_COUNT; a++) {
        drawableList.push_back(&ecgCurves[a]);
        ecgCurves[a].setZOrder(0);
    }

    drawableList.push_back(&testText);

    padInCm=0.5;
    ecgCmPerMv = 2.0;
    ecgCmPerSec = 2.5;
    lastSampleFrequency=0;
}

EcgArea &EcgArea::instance(){
    static EcgArea area;
    return area;
}

void EcgArea::init(AAssetManager *assetManager){
    DrawableGroup::init(assetManager);
}

void EcgArea::rescale(){
    lastSampleFrequency=EcgProcessor::instance().getSamplingFrequency();

    float xScale = ecgCmPerSec * pixelDensity.x / lastSampleFrequency;
    float yScale = ecgCmPerMv * pixelDensity.y;

    for (int a=0; a<ECG_CURVE_COUNT; a++)
        ecgCurves[a].setScale(xScale, yScale);
}

void EcgArea::constructLayout(){
    int r,c;
    if (activeArea.width()<activeArea.height()){
        c=2;
    } else {
        c=3;
    }

    r=(ECG_CURVE_COUNT+c-1)/c;

    int padInPixels=padInCm*pixelDensity.x;
    int curveWidth=(activeArea.width()-(c-1)*padInPixels)/c;

    const int yStep = activeArea.height()/r;
    const int xStep = curveWidth+padInPixels;

    for (int a=0; a<ECG_CURVE_COUNT; a++){
        ecgCurves[a].setLength(curveWidth);

        const int x=a / r;
        const int y=a % r;

        const int xCoord=activeArea.left() + x*xStep;
        const int yCoord=activeArea.top() + y*yStep + yStep/2;

        ecgCurves[a].setPosition(xCoord, yCoord);
    }

    testText.setPosition(0, 0);
}

void EcgArea::contextResized(int w, int h){
    int deleteX=calculateUnalignedArea(w, pixelDensity.x);
    int deleteY=calculateUnalignedArea(h, pixelDensity.y);

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
        ecgCurves[a].put(data + stride*(a % 8), nPoints);
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