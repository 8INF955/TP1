#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <iostream>
#include "Vector.hpp"
#include "Component.hpp"
#include "AABB.hpp"

template <class T>
struct Collider : Component {

    Collider(std::string name): Component(name) {};
    virtual AABB<T> aabb() const = 0;
};

#endif
