#ifndef ANDROIDAPP_CURVE_H
#define ANDROIDAPP_CURVE_H

#include "DrawableObject.h"
#include <string>
#include <GLES2/gl2.h>

class Curve: DrawableObject{
    public:
        virtual void init(AAssetManager *assetManager);
        virtual void glInit();
        virtual void draw();
        virtual void contextResized(int w, int h);
    private:
        std::string fragmentShader;
        std::string vertexShader;

        GLuint shaderProgram;
        GLuint shader_a_Position;
        GLuint shader_screenSize;
        GLuint shader_position;
        GLuint shader_scale;
        GLuint shader_color;
        GLuint shader_a_Value;

        static GLuint getXCoordinates();
        static GLfloat *xCoordinates;
        static int xCoordinatesLength;
        static GLuint xCoordinatesOnGPU;
};

#endif //ANDROIDAPP_CURVE_H
