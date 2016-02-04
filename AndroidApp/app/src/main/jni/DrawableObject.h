#ifndef ANDROIDAPP_DRAWABLEOBJECT_H
#define ANDROIDAPP_DRAWABLEOBJECT_H

#include <android/asset_manager_jni.h>

class DrawableObject{
    public:
        virtual void init(AAssetManager *assetManager)=0;
        virtual void glInit()=0;
        virtual void draw()=0;
        virtual void contextResized(int w, int h){};
        void setZOrder(float z);

    protected:
        float zCoordinate;
};

#endif //ANDROIDAPP_DRAWABLEOBJECT_H
