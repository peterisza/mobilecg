#include "EcgArea.h"
#include "log.h"

EcgArea::EcgArea():
        pixelDensity(100,100){

    grid.setZOrder(10);
    drawableList.push_back(&grid);
    drawableList.push_back(&ecgCurve);

    ecgCurve.setZOrder(0);
}

EcgArea &EcgArea::instance(){
    static EcgArea area;
    return area;
}

void EcgArea::init(AAssetManager *assetManager){
    DrawableGroup::init(assetManager);

    ecgCurve.setLength(500);
}

void EcgArea::contextResized(int w, int h){
    int deleteX=calculateUnalignedArea(w, pixelDensity.x);
    int deleteY=calculateUnalignedArea(h, pixelDensity.y);

    activeArea=Rect(deleteX/2, deleteY/2, w-deleteX+1, h+1-deleteY);

    DrawableGroup::contextResized(w,h);
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
}

void EcgArea::putData(GLfloat *data, int nChannels, int nPoints){
    for (int a=0; a<nPoints; a++) {

        ecgCurve.put(data, nPoints);
    }

}