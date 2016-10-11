#ifndef INTERSECTS_HPP
#define INTERSECTS_HPP

#include <ostream>
#include <cmath>
#include <memory>
#include "Vector.hpp"
#include "Contains.hpp"

template <class T>
class Collider;
template <class T>
class BoxCollider;
template <class T>
class CircleCollider;
template <class T>
class PolygonCollider;

// Collision Segment - Segment
template <class T>
bool intersects(const Vector<T>& a, const Vector<T>& b, const Vector<T>& c, const Vector<T>& d) {
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
template <class T>
bool intersects(const BoxCollider<T>& c, const Vector<T>& u, const Vector<T>& v) {
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
template <class T>
bool intersects(const CircleCollider<T>& c, const Vector<T>& u, const Vector<T>& v) {
    if(contains(c, u) || contains(c, v)) {
        return true;
    }
    auto w = v - u;
    w.normalize();
    auto a = std::abs((c.center - u) ^ w);
    if(a < c.radius) {
        auto p = c.center + w.orth() * a;
        auto q = c.center - w.orth() * a;
        w = v - u;
        auto n2 = w.norm2();
        return ((u-p).norm2() < n2 && (v-p).norm2() < n2)
            || ((u-q).norm2() < n2 && (v-q).norm2() < n2);
    }
    return false;
}

// Collision PolygonCollider - Segment
template <class T>
bool intersects(const PolygonCollider<T>& c, const Vector<T>& u, const Vector<T>& v) {
    if(contains(c, u) || contains(c, v)) {
        return true;
    }
    for(auto it = c.points.begin(); it != c.points.end(); it++) {
        auto it2 = it + 1;
        if(it2 == c.points.end()) it2 = c.points.begin();
        auto p = *it;
        p.rotate(c.alpha);
        auto q = *it2;
        q.rotate(c.alpha);
        if(intersects(u, v, p + c.center, q + c.center)) {
            return true;
        }
    }
    return false;
}

#endif
