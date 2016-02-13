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
 
#include "Rect.h"

Rect::Rect(int left, int top, int width, int height){
    _left=left;
    _top=top;

    setWidth(width);
    setHeight(height);
}

Rect::Rect(){
    _left=_right=_top=_bottom=0;
}

void Rect::setTop(int top){
    _top=top;
}

void Rect::setBottom(int bottom){
    _bottom=bottom;
}

void Rect::setLeft(int left){
    _left=left;
}

void Rect::setRight(int right){
    _right=right;
}

int Rect::left() const{
    return _left;
}

int Rect::right() const{
    return _right;
}

int Rect::top() const{
    return _top;
}

int Rect::bottom() const{
    return _bottom;
}

int Rect::height() const{
    return _bottom-_top+1;
}

int Rect::width() const{
    return _right-_left+1;
}

void Rect::setWidth(int width){
    _right=_left+width-1;
}

void Rect::setHeight(int height){
    _bottom=_top+height-1;
}
