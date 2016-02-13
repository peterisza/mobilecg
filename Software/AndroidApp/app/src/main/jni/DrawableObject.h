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
