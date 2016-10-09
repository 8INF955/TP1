#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <iostream>
#include "Vector.hpp"
#include "AABB.hpp"

template <class T>
struct Collider {

    Collider() {};
    virtual AABB<T> aabb() const = 0;
};

#endif
