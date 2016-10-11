#ifndef CONTAINS_HPP
#define CONTAINS_HPP

#include <math.h>
#include "Vector.hpp"

template<class T>
class BoxCollider;
template<class T>
class CircleCollider;
template<class T>
class PolygonCollider;

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

// Semi-ouvert contient Segment - Vector
template <class T, class U, class V>
bool semiContains(const Vector<T>& a, const Vector<U>& b, const Vector<V>& v) {
    return ((a.x <= v.x || b.x < v.x) && (v.x <= a.x || v.x < b.x) &&
            (a.y <= v.y || b.y < v.y) && (v.y <= a.y || v.y < b.y));
}

// Semi-ouvert intersection Segment - Segment
template <class T, class U, class V, class W>
bool semiIntersects(const Vector<T>& a, const Vector<U>& b, const Vector<V>& c, const Vector<W>& d) {
    auto ab = b - a;
    auto cd = d - c;
    auto ac = c - a;
    auto ca = -ac;
    auto ad = d - a;
    auto cb = b - c;

    // Cas spécial quand les vecteurs directeurs sont parallèles
    if((ab^cd) == 0) {
        return contains(a, b, c) || semiContains(c, d, a) || semiContains(c, d, b);
    }
    else {
        // ab^ad != 0 => d n'appartient pas à ab
        return ((ab^ac) * (ab^ad) <= 0) && ((cd^ca) * (cd^cb) <= 0) && (ab^ad) != 0;
    }
}

// Contient PolygonCollider - Vector
template <class T, class U>
bool contains(const PolygonCollider<T>& c, const Vector<U>& point) {
    if(c.points.size() == 0) {
        return false;
    }

    // Calcul du point de départ du raycast
    T min = 0;
    for(auto it = c.points.begin(); it != c.points.end(); it++) {
        auto p = *it;
        p.rotate(c.alpha);
        if(p.x < min) min = p.x;
    }
    // Décallage de epsilon sur le côté
    min *= 2;
    // Point de départ du raycast
    Vector<U> out(c.center.x + min, point.y);

    // Nombre d'intersections du raycast avec le polygon
    int n = 0;

    for(auto it = c.points.begin(); it != c.points.end(); it++) {
        auto it2 = it + 1;
        if(it2 == c.points.end()) it2 = c.points.begin();
        auto p = *it;
        p.rotate(c.alpha);
        auto q = *it2;
        q.rotate(c.alpha);
        if(semiIntersects(out, point, p + c.center, q + c.center)) n++;
    }

    return n % 2 == 1;
}

#endif
