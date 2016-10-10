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

    BoxCollider(Vector<T> center = Vector<T>(), T width = 0, T height = 0,
            T alpha = 0): Collider<T>(), center{center}, width{width}, height{height},
            alpha{alpha} {}

    Vector<T> topLeft() const;
    Vector<T> topRight() const;
    Vector<T> bottomRight() const;
    Vector<T> bottomLeft() const;

    AABB<T> aabb() const;
    std::unique_ptr<sf::Shape> shape() const;
};

// Coins d'un BoxCollider
template <class T>
Vector<T> BoxCollider<T>::topLeft() const {
    Vector<T> diag(-width / 2, -height / 2);
    diag.rotate(alpha);
    return diag + center;
}

template <class T>
Vector<T> BoxCollider<T>::topRight() const {
    Vector<T> diag(width / 2, -height / 2);
    diag.rotate(alpha);
    return diag + center;
}

template <class T>
Vector<T> BoxCollider<T>::bottomRight() const {
    Vector<T> diag(width / 2, height / 2);
    diag.rotate(alpha);
    return diag + center;
}

template <class T>
Vector<T> BoxCollider<T>::bottomLeft() const {
    Vector<T> diag(-width / 2, height / 2);
    diag.rotate(alpha);
    return diag + center;
}

// Affichage d'un BoxCollider
template <class T>
std::ostream& operator<<(std::ostream& output, BoxCollider<T>& c) {
    output << "BoxCollider{" << c.center << " " << c.width
        << " " << c.height << " " << c.alpha << "}";
    return output;
}

template <class T>
AABB<T> BoxCollider<T>::aabb() const {
    auto tl = topLeft() - center;
    auto tr = topRight() - center;

    T w = 2 * std::max(std::abs(tl.x), std::abs(tr.x));
    T h = 2 * std::max(std::abs(tl.y), std::abs(tr.y));

    return AABB<T>(center, w, h);
}

template <class T>
std::unique_ptr<sf::Shape> BoxCollider<T>::shape() const {
    auto c = std::make_unique<sf::ConvexShape>(4);
    c->setPoint(0, sf::Vector2f(topLeft().x, topLeft().y));
    c->setPoint(1, sf::Vector2f(topRight().x, topRight().y));
    c->setPoint(2, sf::Vector2f(bottomRight().x, bottomRight().y));
    c->setPoint(3, sf::Vector2f(bottomLeft().x, bottomLeft().y));
    std::unique_ptr<sf::Shape> s = std::move(c);
    return s;
}

#endif
