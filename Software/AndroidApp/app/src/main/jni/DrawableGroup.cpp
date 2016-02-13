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
        drawableList[i]->drawIfVisible();
    }
}

void DrawableGroup::contextResized(int w, int h){
    for (int i=0; i<drawableList.size(); i++){
        drawableList[i]->contextResized(w,h);
    }
}
