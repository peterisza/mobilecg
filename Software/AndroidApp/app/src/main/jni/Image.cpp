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
 
#include "Image.h"
#include <string.h>

const Image::Pixel Image::BLACK(0,0,0);
const Image::Pixel Image::WHITE(255,255,255);
const Image::Pixel Image::RED(255,0,0);
const Image::Pixel Image::GREY(100,100,100);

Image::Pixel::Pixel(uint8_t pr, uint8_t pg, uint8_t pb, uint8_t pa){
    r=pr;
    g=pg;
    b=pb;
    a=pa;
}

Image::Pixel::Pixel(): r(0), g(0), b(0), a(1){

}

void Image::resize(int pw, int ph){
    w=pw;
    h=ph;
    data.resize(w*h);
}

void Image::fill(const Image::Pixel &color) {
    std::fill(data.begin(), data.end(), color);
}

void *Image::getData(){
    return data.data();
}

Image::Pixel &Image::operator()(int x, int y){
    return data[w*y+x];
}

void Image::hLine(int y, int xStart, int xEnd, const Pixel &color, int width){
    int len = xEnd-xStart + 1;
    for (int yo=0; yo<width; yo++) {
        Pixel *d = &data[w * (y+yo) + xStart];

        for (int a = 0; a < len; ++a) {
            d[a] = color;
        }
    }
}

void Image::vLine(int x, int yStart, int yEnd, const Pixel &color, int width){
    Pixel *d = &data[w * yStart + x];
    int len=yEnd-yStart+1;
    if (width==1){
        for (int a=0; a<len; a++){
            *d=color;
            d+=w;
        }
    } else {
        for (int a=0; a<len; a++) {
            for (int p = 0; p < width; p++) {
                d[p] = color;
            }
            d+=w;
        }
    }
}

void Image::fill(int xStart, int yStart, int width, int height, const Pixel &color){
    Pixel *d = &data[w * yStart + xStart];
    for (int yo=0; yo<height; yo++){
        for (int xo=0; xo<width; xo++){
            d[xo] = color;
        }
        d+=w;
    }
}

void Image::fill(const Rect &rect, const Pixel &color){
    fill(rect.left(), rect.top(), rect.width(), rect.height(), color);
}

int Image::width(){
    return w;
}

int Image::height(){
    return h;
}

void Image::setBitmap(const char *bitmap) {
    memcpy(&data[0], bitmap, w*h*sizeof(Pixel));
}
