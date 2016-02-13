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
 
#ifndef ANDROIDAPP_CURVE_H
#define ANDROIDAPP_CURVE_H

#include "DrawableObject.h"
#include <string>
#include <GLES2/gl2.h>
#include "DataFormat/CircularBuffer.h"
#include <vector>
#include "Vec2.h"

class Curve: public DrawableObject{
    public:
        Curve();

        virtual void init(AAssetManager *assetManager);
        virtual void glInit();
        virtual void draw();
        virtual void contextResized(int w, int h);

        void setPosition(int x, int y);
        void setScale(float x, float y);

        static const float POINT_INVALID;

        void setLength(int lengthInPixels);
        void put(float *data, int n);

        const Vec2 <int> endpointCoordinates();
    private:
        std::string fragmentShader;
        std::string vertexShader;

        Vec2 <GLfloat> screenSize;
        Vec2 <GLfloat> scale;
        Vec2 <GLfloat> position;

        GLfloat color[3];

        GLfloat clearWidthInPoints;

        static std::vector<GLfloat> invalidBuffer;


        CircularBuffer<GLfloat, 12800, true> newPointBuffer;

        int shaderId;
        GLuint shader_a_Position;
        GLuint shader_screenSize;
        GLuint shader_position;
        GLuint shader_scale;
        GLuint shader_color;
        GLuint shader_a_Value;

        GLuint shader_endOffset;
        GLuint shader_pointCount;
        GLuint shader_clearWidth;

        GLuint valueBuffer;

        int requiredNumOfPoints;
        int currNumOfPoints;

        int currWritePos;
        int lengthInPixels;

        Vec2<float> endCoordinates;

        void clear();
        void resizeOnGPU();
        void moveNewDataToGPU();

        static GLuint getXCoordinates(int capacity);
        static GLfloat *xCoordinates;
        static int xCoordinatesLength;
        static GLuint xCoordinatesOnGPU;
};

#endif //ANDROIDAPP_CURVE_H
