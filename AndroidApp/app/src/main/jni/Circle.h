#ifndef ANDROIDAPP_CIRCLE_H
#define ANDROIDAPP_CIRCLE_H

#include <android/asset_manager_jni.h>
#include <string>
#include "DrawableObject.h"
#include <GLES2/gl2.h>
#include "Image.h"
#include "Vec2.h"

class Circle:public DrawableObject{
public:
    Circle();
    virtual void init(AAssetManager *assetManager);
    virtual void glInit();
    virtual void draw();
    virtual void contextResized(int w, int h);

    void setPosition(const Vec2<int> &position);
    void setSize(float d);

    void setColor(float r, float g, float b);
private:
    std::string vertexShader;
    std::string fragmentShader;

    void initGlBuffers();

    static const GLfloat vertexCoordinates[8];
    int shaderId;

    GLuint shader_a_Position;
    GLuint shader_screenSize;
    GLuint shader_position;
    GLuint shader_size;
    GLuint shader_color;
    GLuint vertexBuffer;

    GLfloat screenSize[2];
    GLfloat position[2];
    GLfloat color[3];

    float size;
};


#endif //ANDROIDAPP_CIRCLE_H
