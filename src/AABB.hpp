#ifndef AABB_HPP
#define AABB_HPP

#include <iostream>
#include "Vector.hpp"

template <class T>
struct AABB {

    Vector<T> center;
    T width;
    T height;

    AABB(Vector<T> center = Vector<T>(), T width = 0, T height = 0):
            center{center}, width{width}, height{height} {}

    std::unique_ptr<sf::Shape> shape() const;
};

// Intersection entre AABBs
template <class T, class U>
bool intersects(const AABB<T>& c1, const AABB<U>& c2) {
    auto d = c1.center - c2.center;
    return std::abs(d.x) <= (c1.width + c2.width) / 2
        && std::abs(d.y) <= (c1.height + c2.height) / 2;
}

template <class T>
std::unique_ptr<sf::Shape> AABB<T>::shape() const {
    auto c = std::make_unique<sf::RectangleShape>(sf::Vector2f(width, height));
    c->setPosition(sf::Vector2f(center.x-width/2, center.y-height/2));
    std::unique_ptr<sf::Shape> s = std::move(c);
    return s;
}

// Affichage d'une AABB
template <class T>
std::ostream& operator<<(std::ostream& output, AABB<T>& a) {
    output << "BoxCollider{\"" << a.name << "\" " << a.center << " " << a.width
        << " " << a.height << "}";
    return output;
}

template <class T, class U>
bool contains(const AABB<T>& aabb, const Vector<U>& point) {
    auto d = aabb.center - point;
    return std::abs(d.x) <= aabb.width / 2 && std::abs(d.y) <= aabb.height / 2;
}

#endif
