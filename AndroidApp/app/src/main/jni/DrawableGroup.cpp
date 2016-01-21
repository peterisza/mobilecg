#include "DrawableGroup.h"

void DrawableGroup::init(AAssetManager *assetManager){
    for (int i=0; i<drawableList.size(); i++){
        drawableList[i]->init(assetManager);
    }
}

void DrawableGroup::glInit(){
    for (int i=0; i<drawableList.size(); i++){
        drawableList[i]->glInit();
    }
}

void DrawableGroup::draw(){
    for (int i=0; i<drawableList.size(); i++){
        drawableList[i]->draw();
    }
}

void DrawableGroup::contextResized(int w, int h){
    for (int i=0; i<drawableList.size(); i++){
        drawableList[i]->contextResized(w,h);
    }
}
