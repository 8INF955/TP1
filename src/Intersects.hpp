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
    auto ab = b - a; // AB
    auto cd = d - c; // CD
    auto ac = c - a; // AC
    auto ca = -ac;
    auto ad = d - a; // AD
    auto cb = b - c; // CB

    // Cas spécial quand les vecteurs directeurs sont parallèles
    if((ab^cd) == 0) {
        return contains(a, b, c) || contains(a, b, d) || contains(c, d, a) || contains(c, d, b);
    }
    else {
        return ((ab^ac) * (ab^ad) <= 0) && ((cd^ca) * (cd^cb) <= 0);
    }
}

// Collision BoxCollider - Segment
template <class T, class U, class V>
bool intersects(const BoxCollider<T>& c, const Vector<U>& u, const Vector<V>& v) {
    if(contains(c, u) || contains(c, v)) {
        return true;
    }

    auto tl = c.topLeft();
    auto tr = c.topRight();
    auto bl = c.bottomLeft();
    auto br = c.bottomRight();

    return intersects(tl, tr, u, v) || intersects(tr, br, u, v)
        || intersects(br, bl, u, v) || intersects(bl, tl, u, v);
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

    auto tl1 = c1.topLeft();
    auto tr1 = c1.topRight();
    auto bl1 = c1.bottomLeft();
    auto br1 = c1.bottomRight();
    auto tl2 = c2.topLeft();
    auto tr2 = c2.topRight();
    auto bl2 = c2.bottomLeft();
    auto br2 = c2.bottomRight();

    return intersects(c1, tl2, tr2) || intersects(c2, tl1, tr1)
        || intersects(c1, tr2, br2) || intersects(c2, tr1, br1)
        || intersects(c1, br2, bl2) || intersects(c2, br1, bl1)
        || intersects(c1, bl2, tl2) || intersects(c2, bl1, tl1);
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

    auto tl = c1.topLeft();
    auto tr = c1.topRight();
    auto bl = c1.bottomLeft();
    auto br = c1.bottomRight();

    return intersects(c2, tl, tr) || intersects(c2, tr, br)
        || intersects(c2, br, bl) || intersects(c2, bl, tl)
        || contains(c1, c2.center);
}

#endif
