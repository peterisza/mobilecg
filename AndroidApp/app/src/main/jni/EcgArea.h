#ifndef ANDROIDAPP_ECGAREA_H
#define ANDROIDAPP_ECGAREA_H


#include "DrawableGroup.h"
#include "GridDrawer.h"
#include "TextDrawer.h"
#include "Rect.h"
#include "Vec2.h"
#include "Curve.h"

class EcgArea: public DrawableGroup{
    private:
        static const int ECG_CURVE_COUNT = 12;
        EcgArea();

        Rect activeArea;
        Vec2<float> pixelDensity;
        int calculateUnalignedArea(int size, float dpcm);
        GridDrawer grid;
        Curve ecgCurves[ECG_CURVE_COUNT];



        float lastSampleFrequency;

        float padInCm;
        bool redrawNeeded;

        void constructLayout();
        void rescale();

        float ecgCmPerMv;
        float ecgCmPerSec;
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

        TextDrawer testText;

};



#endif //ANDROIDAPP_ECGAREA_H
