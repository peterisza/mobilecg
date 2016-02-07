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
