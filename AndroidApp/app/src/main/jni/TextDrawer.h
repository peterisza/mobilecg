//
// Created by isza on 2016.02.04..
//

#ifndef ANDROIDAPP_TEXTDRAWER_H
#define ANDROIDAPP_TEXTDRAWER_H


#include "TexturedSurface.h"
#include "Image.h"

class TextDrawer: public TexturedSurface {
public:
    TextDrawer();
    TextDrawer& drawText(const char* text);
    TextDrawer& setColor(const Image::Pixel& color);
    TextDrawer& setTextSizeMM(float size);
private:
    void setBitmap(const char* data, int width, int height);
    float textSizeMM;
    int color;
    Image textImage;
};

#endif //ANDROIDAPP_TEXTDRAWER_H
