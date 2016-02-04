#ifndef ANDROIDAPP_IMAGE_H
#define ANDROIDAPP_IMAGE_H

#include <cstdint>
#include <vector>
#include "Rect.h"

class Image {
    public:
        Image() {}

        struct Pixel{
            uint8_t r;
            uint8_t g;
            uint8_t b;
            uint8_t a;

            Pixel();
            Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a=255);
        } __attribute__((packed));

        static const Pixel BLACK;
        static const Pixel WHITE;
        static const Pixel RED;

        void resize(int w, int h);
        void *getData();

        void fill(const Pixel &color);

        Pixel &operator()(int x, int y);
        void hLine(int y, int xStart, int xEnd, const Pixel &color, int width=1);
        void vLine(int x, int yStart, int yEnd, const Pixel &color, int width=1);

        void fill(int xStart, int yStart, int width, int height, const Pixel &color);
        void fill(const Rect &rect, const Pixel &color);

        int width();
        int height();

        void setBitmap(const char* bitmap);
    private:
        int w;
        int h;
        std::vector <Pixel> data;
};


#endif //ANDROIDAPP_IMAGE_H
