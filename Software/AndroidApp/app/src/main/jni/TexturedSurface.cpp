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
 
#include "TexturedSurface.h"
#include "Helper.h"
#include "EcgArea.h"
#include "ShaderBuilder.h"
#include <cassert>

const GLfloat TexturedSurface::vertexCoordinates[8]={
    -0.5f, -0.5f,
    0.5f, -0.5f,
    -0.5f,  0.5f,
    0.5f,  0.5f
};


TexturedSurface::TexturedSurface(){
    position[0]=0;
    position[1]=0;
    redraw(NULL);
}

void TexturedSurface::init(AAssetManager *assetManager){
    vertexShader = helper::loadAsset(assetManager, "texturedSurface.vert");
    fragmentShader = helper::loadAsset(assetManager, "texturedSurface.frag");
}

void TexturedSurface::glInit(){
    shaderId = ShaderBuilder::instance().buildShader("TexturedSurface", vertexShader, fragmentShader);
    GLuint shaderProgram = ShaderBuilder::instance().getShader(shaderId);

    shader_a_Position=helper::getGlAttributeWithAssert(shaderProgram, "a_Position");
    shader_screenSize=helper::getGlUniformWithAssert(shaderProgram, "screenSize");
    shader_position=helper::getGlUniformWithAssert(shaderProgram, "position");
    shader_size=helper::getGlUniformWithAssert(shaderProgram, "size");

    glGenTextures(1, &texture);
    glGenBuffers(1, &vertexBuffer);

    initGlBuffers();
}

void TexturedSurface::initGlBuffers(){
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBindBuffer(GL_ARRAY_BUFFER , vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER , sizeof(vertexCoordinates), vertexCoordinates, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER , 0);
}

void TexturedSurface::draw(){
    bool redraw=false;
    if (EcgArea::instance().isRedrawNeeded()){
        redraw=true;
        initGlBuffers();
    }

    ShaderBuilder::instance().useProgram(shaderId);

    glBindTexture(GL_TEXTURE_2D, texture);
    if ((!imageOnGPU || redraw) && image!=NULL) {
        imageOnGPU=true;

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width(), image->height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     image->getData());
    }


    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(shader_a_Position, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(shader_a_Position);
    glUniform2f(shader_screenSize, screenSize[0],screenSize[1]);
    glUniform3f(shader_position, position[0], position[1], zCoordinate);
    glUniform2f(shader_size, (GLfloat)width,(GLfloat)height);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindBuffer(GL_ARRAY_BUFFER , 0);
}

void TexturedSurface::contextResized(int w, int h){
    screenSize[0]=w;
    screenSize[1]=h;
}

void TexturedSurface::setPosition(float x, float y){
    position[0]=x;
    position[1]=y;
}

void TexturedSurface::setSize(float w, float h){
    width=w;
    height=h;
}

void TexturedSurface::redraw(Image *pimage){
    image=pimage;
    imageOnGPU=false;
}

int TexturedSurface::getHeight() { return height; }

int TexturedSurface::getWidth() { return width; }