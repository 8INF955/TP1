#ifndef CIRCLE_COLLIDER_HPP
#define CIRCLE_COLLIDER_HPP

#include <iostream>
#include "Collider.hpp"
#include "Vector.hpp"

template <class T>
struct CircleCollider : public Collider<T> {

    Vector<T> center;
    T radius;

    CircleCollider(Vector<T> center = Vector<T>(),
            T radius = 0): Collider<T>(), center{center}, radius{radius} {}

    AABB<T> aabb() const;
    std::unique_ptr<sf::Shape> shape() const;
};

// Affichage d'un CircleCollider
template <class T>
std::ostream& operator<<(std::ostream& output, CircleCollider<T>& c) {
    output << "CircleCollider{" << c.center << " " << c.radius << "}";
    return output;
}

template <class T>
AABB<T> CircleCollider<T>::aabb() const {
    return AABB<T>(center, 2 * radius, 2 * radius);
}

template <class T>
std::unique_ptr<sf::Shape> CircleCollider<T>::shape() const {
    auto c = std::make_unique<sf::CircleShape>(radius);
    c->setPosition(sf::Vector2f(center.x-radius, center.y-radius));
    std::unique_ptr<sf::Shape> s = std::move(c);
    return s;
}

#endif
