#ifndef CONTAINS_HPP
#define CONTAINS_HPP

#include "Vector.hpp"
#include "Collider.hpp"
#include "BoxCollider.hpp"
#include "CircleCollider.hpp"

// Contient BoxCollider - Vector
template <class T, class U>
bool contains(const BoxCollider<T>& c, const Vector<U>& v) {
    auto d = c.center - v;
    return std::abs(d.x) < c.width / 2 && std::abs(d.y) < c.height / 2;
}

// Contient CircleCollider - Vector
template <class T, class U>
bool contains(const CircleCollider<T>& c, const Vector<U>& v) {
    auto d = c.center - v;
    return d.norm() < c.radius;
}

#endif
