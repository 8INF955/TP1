#ifndef POLYGON_COLLIDER_HPP
#define POLYGON_COLLIDER_HPP

#include <iostream>
#include <vector>
#include "Collider.hpp"
#include "Vector.hpp"

template <class T>
struct PolygonCollider : public Collider<T> {
    /* ATTRIBUTES */
    std::vector<Vector<T>> points;

    /* CONSTRUCTORS */
    PolygonCollider(Vector<T> center = Vector<T>(), T alpha = 0):
            Collider<T>(center, alpha) {}

    /* ACCESSORS */
    AABB<T> aabb() const;
    std::unique_ptr<sf::Shape> shape() const;

    /* VISITOR PATTERN FOR COLLISION */
    bool collidesWith(const Collider<T>& collider) const;
    bool dispatchCollidesWith(const BoxCollider<T>& collider) const;
    bool dispatchCollidesWith(const CircleCollider<T>& collider) const;
    bool dispatchCollidesWith(const PolygonCollider<T>& collider) const;
};

/* ACCESSORS */
/** aabb
 *
 * Returns the axis align bounding box of the polygon collider.
 */
template <class T>
AABB<T> PolygonCollider<T>::aabb() const {
    if(points.size() == 0) {
        return AABB<T>(this->center, 0, 0);
    }
    auto p = points[0];
    p.rotate(this->alpha);
    T miw = p.x;
    T maw = p.x;
    T mih = p.y;
    T mah = p.y;
    for(auto it = points.begin(); it != points.end(); it++) {
        auto p = *it;
        p.rotate(this->alpha);
        if(p.x < miw) miw = p.x;
        if(p.x > maw) maw = p.x;
        if(p.y < mih) mih = p.y;
        if(p.y > mah) mah = p.y;
    }
    Vector<T> offset((miw + maw) / 2, (mih + mah) / 2);
    return AABB<T>(this->center + offset, maw - miw, mah - mih);
}
/** shape
 *
 * Returns the SFML shape of the polygon collider.
 */
template <class T>
std::unique_ptr<sf::Shape> PolygonCollider<T>::shape() const {
    auto c = std::make_unique<sf::ConvexShape>(points.size());
    for(unsigned int k = 0; k < points.size(); k++) {
        auto p = points[k];
        p.rotate(this->alpha);
        p += this->center;
        c->setPoint(k, sf::Vector2f(p.x, p.y));
    }
    std::unique_ptr<sf::Shape> s = std::move(c);
    return s;
}

/* VISITOR PATTERN */
template <class T>
bool PolygonCollider<T>::collidesWith(const Collider<T>& collider) const {
    return collider.dispatchCollidesWith(*this);
}
template <class T>
bool PolygonCollider<T>::dispatchCollidesWith(const BoxCollider<T>& collider) const {
    return Collider<T>::collide(*this, collider);
}
template <class T>
bool PolygonCollider<T>::dispatchCollidesWith(const CircleCollider<T>& collider) const {
    return Collider<T>::collide(*this, collider);
}
template <class T>
bool PolygonCollider<T>::dispatchCollidesWith(const PolygonCollider<T>& collider) const {
    return Collider<T>::collide(*this, collider);
}

/** operator<<
 *
 * Displays a circle collider.
 */
template <class T>
std::ostream& operator<<(std::ostream& output, PolygonCollider<T>& c) {
    output << "PolygonCollider{" << c.center << " " << c.alpha << "}";
    return output;
}

#endif
