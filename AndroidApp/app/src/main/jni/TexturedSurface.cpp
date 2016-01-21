#include "TexturedSurface.h"
#include "Helper.h"
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
}

void TexturedSurface::init(AAssetManager *assetManager){
    vertexShader = helper::loadAsset(assetManager, "texturedSurface.vert");
    fragmentShader = helper::loadAsset(assetManager, "texturedSurface.frag");
}

void TexturedSurface::glInit(){
    shaderProgram = helper::createGlProgram(vertexShader, fragmentShader);

    shader_a_Position=helper::getGlAttributeWithAssert(shaderProgram, "a_Position");
    shader_screenSize=helper::getGlUniformWithAssert(shaderProgram, "screenSize");
    shader_position=helper::getGlUniformWithAssert(shaderProgram, "position");

}

void TexturedSurface::draw(){
    glUseProgram(shaderProgram);

    glVertexAttribPointer(shader_a_Position, 2, GL_FLOAT, GL_FALSE, 0, vertexCoordinates);
    glEnableVertexAttribArray(shader_a_Position);
    glUniform2f(shader_screenSize, screenSize[0],screenSize[1]);
    glUniform3f(shader_position, position[0], position[1], zCoordinate);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void TexturedSurface::resize(int w, int h){
    screenSize[0]=w;
    screenSize[1]=h;
}

void TexturedSurface::setPosition(float x, float y){
    position[0]=x;
    position[1]=y;
}