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
