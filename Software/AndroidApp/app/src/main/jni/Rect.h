/*
 * This file is part of MobilECG, an open source clinical grade Holter
 * ECG. For more information visit http://mobilecg.hu
 *
 * Copyright (C) 2016  Robert Csordas, Peter Isza
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
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
