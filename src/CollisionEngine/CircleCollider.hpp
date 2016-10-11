#ifndef CIRCLE_COLLIDER_HPP
#define CIRCLE_COLLIDER_HPP

#include <iostream>
#include "Collider.hpp"
#include "Vector.hpp"

template <class T>
struct CircleCollider : public Collider<T> {
    /* ATTRIBUTES */
    T radius;

    /* CONSTRUCTORS */
    CircleCollider(Vector<T> center = Vector<T>(), T radius = 0):
            Collider<T>(center), radius{radius} {}

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
 * Returns the axis align bounding box of the circle collider.
 */
template <class T>
AABB<T> CircleCollider<T>::aabb() const {
    return AABB<T>(this->center, 2 * radius, 2 * radius);
}
/** shape
 *
 * Returns the SFML shape of the circle collider.
 */
template <class T>
std::unique_ptr<sf::Shape> CircleCollider<T>::shape() const {
    auto c = std::make_unique<sf::CircleShape>(radius);
    c->setPosition(sf::Vector2f(this->center.x-radius, this->center.y-radius));
    std::unique_ptr<sf::Shape> s = std::move(c);
    return s;
}

/* VISITOR PATTERN */
template <class T>
bool CircleCollider<T>::collidesWith(const Collider<T>& collider) const {
    return collider.dispatchCollidesWith(*this);
}
template <class T>
bool CircleCollider<T>::dispatchCollidesWith(const BoxCollider<T>& collider) const {
    return Collider<T>::collide(*this, collider);
}
template <class T>
bool CircleCollider<T>::dispatchCollidesWith(const CircleCollider<T>& collider) const {
    return Collider<T>::collide(*this, collider);
}
template <class T>
bool CircleCollider<T>::dispatchCollidesWith(const PolygonCollider<T>& collider) const {
    return Collider<T>::collide(*this, collider);
}

/** operator<<
 *
 * Displays a circle collider.
 */
template <class T>
std::ostream& operator<<(std::ostream& output, CircleCollider<T>& c) {
    output << "CircleCollider{" << c.center << " " << c.radius << "}";
    return output;
}

#endif
