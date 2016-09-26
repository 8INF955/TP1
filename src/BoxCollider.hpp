#ifndef BOX_COLLIDER_HPP
#define BOX_COLLIDER_HPP

#include <iostream>
#include "Collider.hpp"
#include "Vector.hpp"

template <class T>
struct BoxCollider : Collider {

    Vector<T> center;
    T width;
    T height;

    BoxCollider(std::string name, Vector<T> center = Vector<T>(), T width = 0,
            T height = 0): Collider(name), center{center}, width{width},
        height{height} {}

    Vector<T> topLeftCorner() const {
        return this->center + Vector<T>(- this->width / 2, this->height / 2);
    }

    Vector<T> topRightCorner() const {
        return this->center + Vector<T>(this->width / 2, this->height / 2);
    }

    Vector<T> bottomLeftCorner() const {
        return this->center + Vector<T>(- this->width / 2, - this->height / 2);
    }

    Vector<T> bottomRightCorner() const {
        return this->center + Vector<T>(this->width / 2, - this->height / 2);
    }
};

// Affichage d'un BoxCollider
template <class T>
std::ostream& operator<<(std::ostream& output, BoxCollider<T>& c) {
    output << "BoxCollider{\"" << c.name << "\" " << c.center << " " << c.width
        << " " << c.height << "}";
    return output;
}

#endif
