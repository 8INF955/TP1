#ifndef CIRCLE_COLLIDER_HPP
#define CIRCLE_COLLIDER_HPP

#include <iostream>
#include "Collider.hpp"
#include "Vector.hpp"

template <class T>
struct CircleCollider : Collider {

    Vector<T> center;
    T radius;

    CircleCollider(std::string name, Vector<T> center = Vector<T>(),
            T radius = 0): Collider(name), center{center}, radius{radius} {}
};

// Affichage d'un CircleCollider
template <class T>
std::ostream& operator<<(std::ostream& output, CircleCollider<T>& c) {
    output << "CircleCollider{\"" << c.name << "\" " << c.center << " "
        << c.radius << "}";
    return output;
}

#endif
