#ifndef ANDROIDAPP_ECGAREA_H
#define ANDROIDAPP_ECGAREA_H


#include "DrawableGroup.h"
#include "GridDrawer.h"
#include "Rect.h"
#include "Vec2.h"

class EcgArea: public DrawableGroup{
    private:
        EcgArea();

        Rect activeArea;
        Vec2<float> pixelDensity;

        int calculateUnalignedArea(int size, float dpcm);

        GridDrawer grid;

    public:
        static EcgArea &instance();
        virtual void contextResized(int w, int h);

        const Rect &getActiveArea();
        const Vec2<float> &getPixelDensity();

        void setPixelDensity(const Vec2<float> &pixelDensity);

};



#endif //ANDROIDAPP_ECGAREA_H
