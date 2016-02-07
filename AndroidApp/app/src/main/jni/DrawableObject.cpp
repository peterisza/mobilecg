#include "DrawableObject.h"

void DrawableObject::setZOrder(float z){
    zCoordinate=0.001f*z;
}

DrawableObject::DrawableObject(){
    visible=true;
}

void DrawableObject::drawIfVisible(){
    if (visible)
        draw();
}

void DrawableObject::setVisible(bool pVisible){
    visible = pVisible;
}

bool DrawableObject::getVisible(){
    return visible;
};