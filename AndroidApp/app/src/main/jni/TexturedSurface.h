#ifndef ANDROIDAPP_TEXTUREDSURFACE_H
#define ANDROIDAPP_TEXTUREDSURFACE_H

#include <android/asset_manager_jni.h>
#include <string>
#include "DrawableObject.h"
#include <GLES2/gl2.h>
#include "Image.h"

class TexturedSurface:public DrawableObject{
public:
    TexturedSurface();
    virtual void init(AAssetManager *assetManager);
    virtual void glInit();
    virtual void draw();
    virtual void contextResized(int w, int h);

    void setPosition(float x, float y);
    void setSize(float w, float h);

    void redraw(Image *image);
private:
    std::string vertexShader;
    std::string fragmentShader;

    static const GLfloat vertexCoordinates[8];
    GLuint shaderProgram;

    GLuint shader_a_Position;
    GLuint shader_screenSize;
    GLuint shader_position;
    GLuint shader_size;
    GLuint vertexBuffer;

    GLuint texture;

    GLfloat screenSize[2];
    GLfloat position[2];

    int width;
    int height;

    Image *image;
    bool imageOnGPU;
};


#endif //ANDROIDAPP_TEXTUREDSURFACE_H
