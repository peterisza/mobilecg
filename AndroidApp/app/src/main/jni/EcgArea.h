#ifndef ANDROIDAPP_ECGAREA_H
#define ANDROIDAPP_ECGAREA_H


#include "DrawableGroup.h"
#include "GridDrawer.h"
#include "Rect.h"
#include "Vec2.h"
#include "Curve.h"

class EcgArea: public DrawableGroup{
    private:
        EcgArea();

        Rect activeArea;
        Vec2<float> pixelDensity;
        int calculateUnalignedArea(int size, float dpcm);
        GridDrawer grid;
        Curve ecgCurve;

    public:
        static EcgArea &instance();
        virtual void contextResized(int w, int h);

        const Rect &getActiveArea();
        const Vec2<float> &getPixelDensity();



        void setPixelDensity(const Vec2<float> &pixelDensity);

        void putData(GLfloat *data, int nChannels, int nPoints, int stride);
        virtual void init(AAssetManager *assetManager);

};



#endif //ANDROIDAPP_ECGAREA_H
