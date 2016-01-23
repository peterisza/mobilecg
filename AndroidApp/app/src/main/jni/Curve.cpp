#include "Curve.h"
#include "EcgArea.h"
#include "Helper.h"
#include <algorithm>

int Curve::xCoordinatesLength=0;
GLfloat *Curve::xCoordinates=NULL;
GLuint Curve::xCoordinatesOnGPU=0;

GLuint Curve::getXCoordinates(){
    const Rect &activeArea = EcgArea::instance().getActiveArea();
    int capacity = std::min(std::max(activeArea.width(), activeArea.height()), 10000);

    if (capacity>xCoordinatesLength){
        if (xCoordinatesLength==0){
            glGenBuffers(1, &xCoordinatesOnGPU);
        } else {
            delete [] xCoordinates;
        }

        xCoordinates = new GLfloat[capacity];
        xCoordinatesLength = capacity;

        for (int a=0; a<capacity; a++){
            xCoordinates[a]=a;
        }

        glBindBuffer(GL_ARRAY_BUFFER , xCoordinatesOnGPU);
        glBufferData(GL_ARRAY_BUFFER , sizeof(GLfloat)*capacity, xCoordinates, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER , 0);
    }

    return xCoordinatesOnGPU;
}

void Curve::init(AAssetManager *assetManager){
    vertexShader = helper::loadAsset(assetManager, "texturedSurface.vert");
    fragmentShader = helper::loadAsset(assetManager, "texturedSurface.frag");
}

void Curve::glInit(){
    shaderProgram = helper::createGlProgram(vertexShader, fragmentShader);

    shader_a_Position=helper::getGlAttributeWithAssert(shaderProgram, "a_Position");
    shader_screenSize=helper::getGlUniformWithAssert(shaderProgram, "screenSize");
    shader_position=helper::getGlUniformWithAssert(shaderProgram, "position");
    shader_scale=helper::getGlUniformWithAssert(shaderProgram, "scale");
    shader_color=helper::getGlUniformWithAssert(shaderProgram, "color");
    shader_a_Value=helper::getGlUniformWithAssert(shaderProgram, "a_Value");

    getXCoordinates();
}

void Curve::draw(){
    glUseProgram(shaderProgram);

    glBindBuffer(GL_ARRAY_BUFFER, getXCoordinates());
    glVertexAttribPointer(shader_a_Position, 1, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(shader_a_Position);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void Curve::contextResized(int w, int h){

}