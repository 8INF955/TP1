#ifndef INTERSECTS_HPP
#define INTERSECTS_HPP

#include <ostream>
#include <cmath>
#include "Vector.hpp"
#include "Collider.hpp"
#include "BoxCollider.hpp"
#include "CircleCollider.hpp"
#include "Contains.hpp"

// Collision Segment Segment
template <class T, class U, class V, class W>
bool intersects(const Vector<T>& a, const Vector<U>& b, const Vector<V>& c, const Vector<W>& d) {
    auto pi = atan(1) * 4;
    auto v = b - a;
    auto w = d - c;
    auto aab = v.angle();
    auto acd = w.angle();
    auto ca = a - c;
    auto db = b - d;
    auto da = a - d;
    auto cb = b - c;
    auto aca = ca.angle();
    auto adb = db.angle();
    auto ada = da.angle();
    auto acb = cb.angle();
    std::cout << aca << " " << adb << " " << ada << " " << acb << std::endl;
    auto orientation = (aab + acd) / pi;
    // Les vecteurs directeurs sont parallèles
    if(std::floor(orientation) == orientation) {
        std::cout << "//" << std::endl;
        // Les segments ne sont pas sur la même droite
        if(aca != adb || ada != acb) {
            std::cout << "=" << std::endl;
            return false;
        }
        // Les segments sont sur la même droite
        std::cout << "--" << std::endl;
        return aca != acb || adb != ada || aca != ada || adb != acb;
    }
    else {
        std::cout << "X" << std::endl;
        return ((-acb) - (-aab)) * ((-adb) - (-aab)) <= 0 && (adb - (-acd)) * (ada - (-acd)) <= 0;
    }
}

// Collision BoxCollider - Segment
template <class T, class U, class V>
bool intersects(const BoxCollider<T>& c, const Vector<U>& u, const Vector<V>& v) {
    if(contains(c, u)) {
        return true;
    }

    auto w = v - u;

}

// Collision CircleCollider - Segment
template <class T, class U, class V>
bool intersects(const CircleCollider<T>& c, const Vector<U>& u, const Vector<V>& v) {
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
    if(!intersects(c1.aabb(), c2.aabb())) {
        return false;
    }

    auto d = c1.center - c2.center;
    return std::abs(d.x) < (c1.width + c2.width) / 2
        && std::abs(d.y) < (c1.height + c2.height) / 2;
}

// Collision CircleCollider - CircleCollider
template <class T, class U>
bool intersects(const CircleCollider<T>& c1, const CircleCollider<U>& c2) {
    if(!intersects(c1.aabb(), c2.aabb())) {
        return false;
    }

    auto d = c1.center - c2.center;
    return d.norm() < c1.radius + c2.radius;
}

// Collision BoxCollider - CircleCollider
template <class T, class U>
bool intersects(const BoxCollider<T>& c1, const CircleCollider<U>& c2) {
    if(!intersects(c1.aabb(), c2.aabb())) {
        return false;
    }

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
