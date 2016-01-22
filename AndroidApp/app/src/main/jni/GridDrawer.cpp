#include "GridDrawer.h"
#include "Helper.h"
#include "EcgArea.h"

//#define POINT_GRID

const Image::Pixel GridDrawer::padColor(0xFF,0xFF,0xE8);
const Image::Pixel GridDrawer::backgroundColor(0xF8,0xFB,0xEF);
const Image::Pixel GridDrawer::gridMainColor(0xA4, 0xA4, 0xA4);

#ifdef POINT_GRID
const Image::Pixel GridDrawer::gridSmallColor(0xA4, 0xA4, 0xA4);
#else
const Image::Pixel GridDrawer::gridSmallColor(0xD4, 0xD4, 0xD4);
#endif

void GridDrawer::contextResized(int w, int h){
    size.w=w;
    size.h=h;

    TexturedSurface::contextResized(w,h);
    setSize(w,h);

    image.resize(w,h);

    refresh();
}


void GridDrawer::refresh(){
    const Vec2<float> &pixelDensity = EcgArea::instance().getPixelDensity();
    const Rect &activeArea = EcgArea::instance().getActiveArea();

    image.fill(activeArea, backgroundColor);

    const float dx=pixelDensity.x;
    const float dy=pixelDensity.y;

    const float smallDx=dx/10.0;
    const float smallDy=dy/10.0;

    const int endX=activeArea.right();
    const int endY=activeArea.bottom();

    const int padX=activeArea.left();
    const int padY=activeArea.top();

    //hide padded margins
    //const QBrush &background=QWidget::palette().background();
    image.fill(0, 0, padX, size.h, padColor);
    image.fill(endX+1, 0, size.w-endX-1, size.h, padColor);
    image.fill(padX, 0, endX-padX+1, padY, padColor);
    image.fill(padX, endY, endX-padX+1, size.h-endY, padColor);

    #ifdef POINT_GRID
        //Draw point grid
        for (float x=padX+smallDx; x<endX-smallDx/2; x+=smallDx){
            for (float y=padY+smallDy; y<endY-smallDy/2; y+=smallDy){
                image(x+1,y)=gridSmallColor;
                image(x,y+1)=gridSmallColor;
                image(x-1,y)=gridSmallColor;
                image(x,y-1)=gridSmallColor;
                image(x,y)=gridSmallColor;
            }
        }
    #else
        //Draw line grid
        for (float x=padX+smallDx; x<endX-smallDx/2; x+=smallDx){
            image.vLine(x, padY, endY, gridSmallColor);
        }

        for (float y=padY+smallDy; y<endY-smallDy/2; y+=smallDy){
            image.hLine(y, padX, endX, gridSmallColor);
        }
    #endif

    //Draw main grid
    for (float x=padX; x<=endX; x+=dx){
        image.vLine(x, padY, endY, gridMainColor);
    }

    for (float y=padY; y<=endY; y+=dy){
        image.hLine(y, padX, endX, gridMainColor);
    }

    redraw(&image);
}
