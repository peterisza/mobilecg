#ifndef ANDROIDAPP_GRIDDRAWER_H
#define ANDROIDAPP_GRIDDRAWER_H

#include <android/asset_manager_jni.h>
#include <string>
#include "Vec2.h"
#include "TexturedSurface.h"

#include "Image.h"

class GridDrawer:public TexturedSurface {
    public:
        virtual void contextResized(int w, int h);
        void refresh();
    private:
        Image image;
        Vec2<int> size;

        static const Image::Pixel padColor;
        static const Image::Pixel backgroundColor;
        static const Image::Pixel gridMainColor;
        static const Image::Pixel gridSmallColor;

};


#endif //ANDROIDAPP_GRIDDRAWER_H
