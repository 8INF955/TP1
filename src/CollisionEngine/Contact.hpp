#ifndef CONTACT_HPP
#define CONTACT_HPP

#include "Vector.hpp"

template <class T>
struct Contact {
    /* ATTRIBUTES */
    Vector<T> point;
    Vector<T> tangent;
    Vector<T> direction;
    T distance;

    /* CONSTRUCTORS */
    Contact(Vector<T> point = Vector<T>(), Vector<T> tangent = Vector<T>(),
            Vector<T> direction = Vector<T>(), T distance = 0): point(point),
            tangent(tangent), direction(direction), distance(distance) {}
};

#endif
