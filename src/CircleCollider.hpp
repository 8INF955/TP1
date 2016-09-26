#ifndef CIRCLE_COLLIDER_HPP
#define CIRCLE_COLLIDER_HPP

#include <iostream>
#include "Collider.hpp"
#include "Vector.hpp"

template <class T>
struct CircleCollider : public Collider<T> {

    Vector<T> center;
    T radius;

    CircleCollider(std::string name, Vector<T> center = Vector<T>(),
            T radius = 0): Collider<T>(name), center{center}, radius{radius} {}

    AABB<T> aabb() const;
};

// Affichage d'un CircleCollider
template <class T>
std::ostream& operator<<(std::ostream& output, CircleCollider<T>& c) {
    output << "CircleCollider{\"" << c.name << "\" " << c.center << " "
        << c.radius << "}";
    return output;
}

template <class T>
AABB<T> CircleCollider<T>::aabb() const {
    return AABB<T>(center, 2 * radius, 2 * radius);
}


#endif
