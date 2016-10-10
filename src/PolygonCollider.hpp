#ifndef POLYGON_COLLIDER_HPP
#define POLYGON_COLLIDER_HPP

#include <iostream>
#include <vector>
#include "Collider.hpp"
#include "Vector.hpp"

template <class T>
struct PolygonCollider : public Collider<T> {
    Vector<T> center;
    std::vector<Vector<T>> points;
    T alpha;

    PolygonCollider(Vector<T> center = Vector<T>(), T alpha = 0): Collider<T>(),
            center(center), alpha(alpha) {}

    AABB<T> aabb() const;
    std::unique_ptr<sf::Shape> shape() const;
};

template <class T>
std::ostream& operator<<(std::ostream& output, PolygonCollider<T>& c) {
    output << "PolygonCollider{" << c.center << " " << c.alpha << "}";
    return output;
}

template <class T>
AABB<T> PolygonCollider<T>::aabb() const {
    if(points.size() == 0) {
        return AABB<T>(center, 0, 0);
    }
    auto p = points[0];
    p.rotate(alpha);
    T miw = p.x;
    T maw = p.x;
    T mih = p.y;
    T mah = p.y;
    for(auto it = points.begin(); it != points.end(); it++) {
        auto p = *it;
        p.rotate(alpha);
        if(p.x < miw) miw = p.x;
        if(p.x > maw) maw = p.x;
        if(p.y < mih) mih = p.y;
        if(p.y > mah) mah = p.y;
    }
    Vector<T> offset((miw + maw) / 2, (mih + mah) / 2);
    return AABB<T>(center + offset, maw - miw, mah - mih);
}

template <class T>
std::unique_ptr<sf::Shape> PolygonCollider<T>::shape() const {
    auto c = std::make_unique<sf::ConvexShape>(points.size());
    for(unsigned int k = 0; k < points.size(); k++) {
        auto p = points[k];
        p.rotate(alpha);
        p += center;
        c->setPoint(k, sf::Vector2f(p.x, p.y));
    }
    std::unique_ptr<sf::Shape> s = std::move(c);
    return s;
}

#endif
