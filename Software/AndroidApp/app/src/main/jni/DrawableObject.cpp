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