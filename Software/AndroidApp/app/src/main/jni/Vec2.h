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
 
#ifndef ANDROIDAPP_VEC2_H
#define ANDROIDAPP_VEC2_H

template <class type> struct Vec2{
    type x;
    type y;

    type &w;
    type &h;

    Vec2(): w(x), h(y){
        x=y=0;
    }

    Vec2(const type &px, const type &py): w(x), h(y){
        x=px;
        y=py;
    }

    type &operator [](int elem){
        return elem ? y : x;
    }

    const type &operator [](int elem) const{
        return elem ? y : x;
    }

    Vec2<type> &operator=(const Vec2<type> &other){
        this->x=other.x;
        this->y=other.y;

        return *this;
    }

    Vec2<type> &operator*(const type &other){
        this->x*=other;
        this->y*=other;

        return *this;
    }

    Vec2<type> &operator/(const type &other){
        this->x/=other;
        this->y/=other;

        return *this;
    }
};

#endif //ANDROIDAPP_VEC2_H
