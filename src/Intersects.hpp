#ifndef INTERSECTS_HPP
#define INTERSECTS_HPP

#include <ostream>
#include "Vector.hpp"
#include "Collider.hpp"
#include "BoxCollider.hpp"
#include "CircleCollider.hpp"
#include "Contains.hpp"

// Collision CircleCollider - Segment
template <class T, class U, class V>
bool intersects(const CircleCollider<T>& c, const Vector<U>& u,
        const Vector<V>& v) {
    auto w = v - u;
    w.normalize();
    auto a = (c.center - u) | w;
    if(0 < a && a < (v - u).norm()) {
        auto p = w * a;
        return (p - c.center).norm() < c.radius;
    }
    return contains(c, u) || contains(c, v);
}

// Collision BoxCollider - BoxCollider
template <class T, class U>
bool intersects(const BoxCollider<T>& c1, const BoxCollider<U>& c2) {
    auto d = c1.center - c2.center;
    return std::abs(d.x) < (c1.width + c2.width) / 2
        && std::abs(d.y) < (c1.height + c2.height) / 2;
}

// Collision CircleCollider - CircleCollider
template <class T, class U>
bool intersects(const CircleCollider<T>& c1, const CircleCollider<U>& c2) {
    auto d = c1.center - c2.center;
    return d.norm() < c1.radius + c2.radius;
}

// Collision BoxCollider - CircleCollider
template <class T, class U>
bool intersects(const BoxCollider<T>& c1, const CircleCollider<U>& c2) {
    // Le cercle touche un bord du rectangle
    if(intersects(c2, c1.topLeftCorner(), c1.topRightCorner())
        || intersects(c2, c1.topRightCorner(), c1.bottomRightCorner())
        || intersects(c2, c1.bottomRightCorner(), c1.bottomLeftCorner())
        || intersects(c2, c1.bottomLeftCorner(), c1.topLeftCorner())) {
        std::cout << "edge !" << std::endl;
        return true;
    }
    // Le rectangle contient le centre du cercle
    std::cout << "center ?" << std::endl;
    return contains(c1, c2.center);
}



#endif
