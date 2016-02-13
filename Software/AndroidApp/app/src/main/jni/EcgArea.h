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
 
#ifndef ANDROIDAPP_ECGAREA_H
#define ANDROIDAPP_ECGAREA_H


#include "DrawableGroup.h"
#include "GridDrawer.h"
#include "TextDrawer.h"
#include "Rect.h"
#include "Vec2.h"
#include "Curve.h"
#include "Circle.h"

class EcgArea: public DrawableGroup{
    private:
        static const int ECG_CURVE_COUNT = 12;
        const char *labelText[ECG_CURVE_COUNT] = {"I", "II", "III", "aVR", "aVL", "aVF", "V1", "V2", "V3", "V4", "V5", "V6"};

        EcgArea();

        Rect activeArea;
        Vec2<float> pixelDensity;
        int calculateUnalignedArea(int size, float dpcm);
        GridDrawer grid;
        TextDrawer labels[ECG_CURVE_COUNT];
        TextDrawer devLabel;
        TextDrawer disconnectedLabel;

        Curve ecgCurves[ECG_CURVE_COUNT];
        //It is somewhat ugly to use endpoint circles separated from their
        //curves, but it avoids unneccessary shader switches.
        Circle endpointCircles[ECG_CURVE_COUNT];

        float lastSampleFrequency;

        float padInCm;
        bool redrawNeeded;

        void constructLayout();
        void rescale();

        float ecgCmPerMv;
        float ecgCmPerSec;

        Vec2<int> screenSize;

        void setContentVisible(bool visible);
public:
        static EcgArea &instance();
        virtual void contextResized(int w, int h);

        const Rect &getActiveArea();
        const Vec2<float> &getPixelDensity();


        void redraw();
        bool isRedrawNeeded();
        virtual void draw();
        void setPixelDensity(const Vec2<float> &pixelDensity);

        void putData(GLfloat *data, int nChannels, int nPoints, int stride);
        virtual void init(AAssetManager *assetManager);

        void deviceConnected();
        void deviceDisconnected();
};



#endif //ANDROIDAPP_ECGAREA_H
