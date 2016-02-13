#ifndef ANDROIDAPP_DRAWABLEGROUP_H
#define ANDROIDAPP_DRAWABLEGROUP_H

#include "DrawableObject.h"
#include <vector>

class DrawableGroup:public DrawableObject {
    public:
        virtual void init(AAssetManager *assetManager);
        virtual void glInit();
        virtual void draw();
        virtual void contextResized(int w, int h);

    protected:
        std::vector<DrawableObject*> drawableList;
};


#endif //ANDROIDAPP_DRAWABLEGROUP_H
