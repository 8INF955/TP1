#ifndef CONTAINS_HPP
#define CONTAINS_HPP

#include <math.h>
#include "Vector.hpp"
#include "Collider.hpp"
#include "BoxCollider.hpp"
#include "CircleCollider.hpp"

// Contient Segment - Vector
template <class T, class U, class V>
bool contains(const Vector<T>& a, const Vector<U>& b, const Vector<V>& v) {
    return (std::min(a.x, b.x) <= v.x && v.x <= std::max(a.x, b.x) &&
            std::min(a.y, b.y) <= v.y && v.y <= std::max(a.y, b.y));
}

// Contient BoxCollider - Vector
template <class T, class U>
bool contains(const BoxCollider<T>& c, const Vector<U>& point) {
    if(!contains(c.aabb(), point)) {
        return false;
    }

    auto d = point - c.center;
    d.rotate(- c.alpha);
    return std::abs(d.x) < c.width / 2 && std::abs(d.y) < c.height / 2;
}

// Contient CircleCollider - Vector
template <class T, class U>
bool contains(const CircleCollider<T>& c, const Vector<U>& point) {
    if(!contains(c.aabb(), point)) {
        return false;
    }

    auto d = c.center - point;
    return d.norm() < c.radius;
}

#endif
