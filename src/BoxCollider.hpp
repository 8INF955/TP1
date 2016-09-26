#ifndef BOX_COLLIDER_HPP
#define BOX_COLLIDER_HPP

#include <iostream>
#include "Collider.hpp"
#include "Vector.hpp"

template <class T>
struct BoxCollider : public Collider<T> {

    Vector<T> center;
    T width;
    T height;
    T alpha;

    BoxCollider(std::string name, Vector<T> center = Vector<T>(), T width = 0, T height = 0,
            T alpha = 0): Collider<T>(name), center{center}, width{width}, height{height},
            alpha{alpha} {}

    AABB<T> aabb() const;
};

// Affichage d'un BoxCollider
template <class T>
std::ostream& operator<<(std::ostream& output, BoxCollider<T>& c) {
    output << "BoxCollider{\"" << c.name << "\" " << c.center << " " << c.width
        << " " << c.height << " " << c.alpha << "}";
    return output;
}

template <class T>
AABB<T> BoxCollider<T>::aabb() const {
    auto tl = center + Vector<T>(- width / 2, height / 2);
    auto tr = center + Vector<T>(width / 2, height / 2);
    tl.rotate(alpha);
    tr.rotate(alpha);

    T w = 2 * std::max(std::abs(tl.x), std::abs(tr.x));
    T h = 2 * std::max(std::abs(tl.y), std::abs(tr.y));

    return AABB<T>(center, w, h);
}

#endif
