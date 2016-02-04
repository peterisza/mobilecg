//
// Created by isza on 2016.02.04..
//

#ifndef ANDROIDAPP_TEXTDRAWER_H
#define ANDROIDAPP_TEXTDRAWER_H


#include "TexturedSurface.h"
#include "Image.h"

class TextDrawer: public TexturedSurface {
public:
    void drawText(const char* text);
    //void setColor(const Image::Pixel& color);
    //void refresh();
    void setBitmap(const char* data, int width, int height);
private:
    int textSize;
    Image textImage;
};

#endif //ANDROIDAPP_TEXTDRAWER_H
