#ifndef ANDROIDAPP_DRAWABLEOBJECT_H
#define ANDROIDAPP_DRAWABLEOBJECT_H

#include <android/asset_manager_jni.h>

class DrawableObject{
    public:
        DrawableObject();
        virtual void init(AAssetManager *assetManager)=0;
        virtual void glInit()=0;
        virtual void draw()=0;
        virtual void contextResized(int w, int h){};
        void setZOrder(float z);
        void drawIfVisible();

        void setVisible(bool visible);
        bool getVisible();
    protected:
        float zCoordinate;
        bool visible;
};

#endif //ANDROIDAPP_DRAWABLEOBJECT_H
