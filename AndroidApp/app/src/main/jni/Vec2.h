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
};

#endif //ANDROIDAPP_VEC2_H
