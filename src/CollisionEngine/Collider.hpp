#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <iostream>
#include <cmath>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Vector.hpp"
#include "AABB.hpp"
#include "Contains.hpp"
#include "Intersects.hpp"

template<class T>
class BoxCollider;
template<class T>
class CircleCollider;
template<class T>
class PolygonCollider;

template<class T>
struct Collider {
    Vector<T> center;
    T alpha;

    /* CONSTRUCTORS */
    Collider(Vector<T> center = Vector<T>(), T alpha = 0): center(center), alpha(alpha) {};

    /* METHODS */
    void move(const Vector<T>& movement);
    void localMove(const Vector<T>& localMovement);
    void rotate(T beta);
    virtual AABB<T> aabb() const = 0;
    virtual std::unique_ptr<sf::Shape> shape() const = 0;

    /* VISITOR PATTERN */
    virtual bool collidesWith(const Collider<T>& collider) const = 0;
    virtual bool dispatchCollidesWith(const BoxCollider<T>& collider) const = 0;
    virtual bool dispatchCollidesWith(const CircleCollider<T>& collider) const = 0;
    virtual bool dispatchCollidesWith(const PolygonCollider<T>& collider) const = 0;

    /* STATIC METHODS */
    static bool collide(const Collider<T>& c1, const Collider<T>& c2);
    static bool collide(const BoxCollider<T>& c1, const BoxCollider<T>& c2);
    static bool collide(const BoxCollider<T>& c1, const CircleCollider<T>& c2);
    static bool collide(const BoxCollider<T>& c1, const PolygonCollider<T>& c2);
    static bool collide(const CircleCollider<T>& c1, const BoxCollider<T>& c2);
    static bool collide(const CircleCollider<T>& c1, const CircleCollider<T>& c2);
    static bool collide(const CircleCollider<T>& c1, const PolygonCollider<T>& c2);
    static bool collide(const PolygonCollider<T>& c1, const BoxCollider<T>& c2);
    static bool collide(const PolygonCollider<T>& c1, const CircleCollider<T>& c2);
    static bool collide(const PolygonCollider<T>& c1, const PolygonCollider<T>& c2);
};
/* METHODS */
template <class T>
void Collider<T>::move(const Vector<T>& movement) {
    center += movement;
}
template <class T>
void Collider<T>::localMove(const Vector<T>& localMovement) {
    auto movement = localMovement;
    movement.rotate(alpha);
    center += movement;
}
template <class T>
void Collider<T>::rotate(T beta) {
    alpha += beta;
}

/* VISITOR PATTERN */
template <class T>
bool Collider<T>::collide(const Collider<T>& c1, const Collider<T>& c2) {
    return c1.collidesWith(c2);
}
template <class T>
bool Collider<T>::collide(const BoxCollider<T>& c1, const BoxCollider<T>& c2) {
    if(!AABB<T>::intersects(c1.aabb(), c2.aabb())) {
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
template <class T>
bool Collider<T>::collide(const BoxCollider<T>& c1, const CircleCollider<T>& c2) {
    if(!AABB<T>::intersects(c1.aabb(), c2.aabb())) {
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
template <class T>
bool Collider<T>::collide(const BoxCollider<T>& c1, const PolygonCollider<T>& c2) {
    if(!AABB<T>::intersects(c1.aabb(), c2.aabb())) {
        return false;
    }

    auto tl = c1.topLeft();
    if(contains(c2, tl)) {
        return true;
    }

    for(auto it = c2.points.begin(); it != c2.points.end(); it++) {
        auto it2 = it + 1;
        if(it2 == c2.points.end()) it2 = c2.points.begin();
        auto p = *it;
        p.rotate(c2.alpha);
        auto q = *it2;
        q.rotate(c2.alpha);
        if(intersects(c1, p + c2.center, q + c2.center)) {
            return true;
        }
    }
    return false;
}
template <class T>
bool Collider<T>::collide(const CircleCollider<T>& c1, const BoxCollider<T>& c2) {
    return Collider<T>::collide(c2, c1);
}
template <class T>
bool Collider<T>::collide(const CircleCollider<T>& c1, const CircleCollider<T>& c2) {
    /* Plus coûteux
    if(!AABB<T>::intersects(c1.aabb(), c2.aabb())) {
        return false;
    }
    */

    auto d = c1.center - c2.center;
    return d.norm() <= c1.radius + c2.radius;
}
template <class T>
bool Collider<T>::collide(const CircleCollider<T>& c1, const PolygonCollider<T>& c2) {
    if(!AABB<T>::intersects(c1.aabb(), c2.aabb())) {
        return false;
    }

    if(contains(c2, c1.center)) {
        return true;
    }

    for(auto it = c2.points.begin(); it != c2.points.end(); it++) {
        auto it2 = it + 1;
        if(it2 == c2.points.end()) it2 = c2.points.begin();
        auto p = *it;
        p.rotate(c2.alpha);
        auto q = *it2;
        q.rotate(c2.alpha);
        if(intersects(c1, p + c2.center, q + c2.center)) {
            return true;
        }
    }
    return false;
}
template <class T>
bool Collider<T>::collide(const PolygonCollider<T>& c1, const BoxCollider<T>& c2) {
    return Collider<T>::collide(c2, c1);
}
template <class T>
bool Collider<T>::collide(const PolygonCollider<T>& c1, const CircleCollider<T>& c2) {
    return Collider<T>::collide(c2, c1);
}
template <class T>
bool Collider<T>::collide(const PolygonCollider<T>& c1, const PolygonCollider<T>& c2) {
    // Pre-check le nombre de points : si 0 pas la peine de continuer
    if(c2.points.size() == 0 || c1.points.size() == 0) {
        return false;
    }
    if(!AABB<T>::intersects(c1.aabb(), c2.aabb())) {
        return false;
    }

    auto point = c2.points[0];
    point.rotate(c2.alpha);
    if(contains(c1, point + c2.center)) {
        return true;
    }

    for(auto it = c1.points.begin(); it != c1.points.end(); it++) {
        auto it2 = it + 1;
        if(it2 == c1.points.end()) it2 = c1.points.begin();
        auto p = *it;
        p.rotate(c1.alpha);
        auto q = *it2;
        q.rotate(c1.alpha);
        if(intersects(c2, p + c1.center, q + c1.center)) {
            return true;
        }
    }
    return false;
}

#endif
