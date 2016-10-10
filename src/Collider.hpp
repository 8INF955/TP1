#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Vector.hpp"
#include "AABB.hpp"

template <class T>
struct Collider {

    Collider() {};
    virtual AABB<T> aabb() const = 0;
    virtual std::unique_ptr<sf::Shape> shape() const = 0;
};

#endif
