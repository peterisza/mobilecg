#ifndef ANDROIDAPP_TEXTUREDSURFACE_H
#define ANDROIDAPP_TEXTUREDSURFACE_H

#include <android/asset_manager_jni.h>
#include <string>
#include "DrawableObject.h"
#include <GLES2/gl2.h>

class TexturedSurface:public DrawableObject{
public:
    TexturedSurface();
    virtual void init(AAssetManager *assetManager);
    virtual void glInit();
    virtual void draw();
    virtual void resize(int w, int h);

    void setPosition(float x, float y);
private:
    std::string vertexShader;
    std::string fragmentShader;

    static const GLfloat vertexCoordinates[8];
    GLuint shaderProgram;

    GLuint shader_a_Position;
    GLuint shader_screenSize;
    GLuint shader_position;

    GLfloat screenSize[2];
    GLfloat position[2];
};


#endif //ANDROIDAPP_TEXTUREDSURFACE_H
