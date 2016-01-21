#ifndef ANDROIDAPP_RECT_H
#define ANDROIDAPP_RECT_H


class Rect {
    public:
        Rect();
        Rect(int left, int top, int width, int height);
        void setTop(int top);
        void setBottom(int bottom);
        void setLeft(int left);
        void setRight(int right);

        int left() const;
        int right() const;
        int top() const;
        int bottom() const;

        int height() const;
        int width() const;

        void setWidth(int width);
        void setHeight(int height);
    private:
        int _top;
        int _bottom;
        int _left;
        int _right;
};


#endif //ANDROIDAPP_RECT_H
