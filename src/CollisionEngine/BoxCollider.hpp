#ifndef BOX_COLLIDER_HPP
#define BOX_COLLIDER_HPP

#include <iostream>
#include "Collider.hpp"
#include "Vector.hpp"

template <class T>
struct BoxCollider : public Collider<T> {
    /* ATTRIBUTES */
    T width;
    T height;

    /* CONSTRUCTORS */
    BoxCollider(Vector<T> center = Vector<T>(), T width = 0, T height = 0,
            T alpha = 0): Collider<T>(center, alpha), width{width},
            height{height} {}

    /* ACCESSORS */
    Vector<T> topLeft() const;
    Vector<T> topRight() const;
    Vector<T> bottomRight() const;
    Vector<T> bottomLeft() const;
    AABB<T> aabb() const;
    std::unique_ptr<sf::Shape> shape() const;

    /* VISITOR PATTERN FOR COLLISION */
    bool collidesWith(const Collider<T>& collider) const;
    bool dispatchCollidesWith(const BoxCollider<T>& collider) const;
    bool dispatchCollidesWith(const CircleCollider<T>& collider) const;
    bool dispatchCollidesWith(const PolygonCollider<T>& collider) const;
};

/* ACCESSORS */
/** topLeft
 *
 * Returns top left corner position of the box collider.
 */
template <class T>
Vector<T> BoxCollider<T>::topLeft() const {
    Vector<T> diag(-width / 2, -height / 2);
    diag.rotate(this->alpha);
    return diag + this->center;
}
/** topRight
 *
 * Returns top right corner position of the box collider.
 */
template <class T>
Vector<T> BoxCollider<T>::topRight() const {
    Vector<T> diag(width / 2, -height / 2);
    diag.rotate(this->alpha);
    return diag + this->center;
}
/** bottomRight
 *
 * Returns bottom right corner position of the box collider.
 */
template <class T>
Vector<T> BoxCollider<T>::bottomRight() const {
    Vector<T> diag(width / 2, height / 2);
    diag.rotate(this->alpha);
    return diag + this->center;
}
/** bottomLeft
 *
 * Returns bottom left corner position of the box collider.
 */
template <class T>
Vector<T> BoxCollider<T>::bottomLeft() const {
    Vector<T> diag(-width / 2, height / 2);
    diag.rotate(this->alpha);
    return diag + this->center;
}
/** aabb
 *
 * Returns the axis align bounding box of the box collider.
 */
template <class T>
AABB<T> BoxCollider<T>::aabb() const {
    auto tl = topLeft() - this->center;
    auto tr = topRight() - this->center;

    T w = 2 * std::max(std::abs(tl.x), std::abs(tr.x));
    T h = 2 * std::max(std::abs(tl.y), std::abs(tr.y));

    return AABB<T>(this->center, w, h);
}
/** shape
 *
 * Returns the SFML shape of the box collider.
 */
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

/* VISITOR PATTERN */
template <class T>
bool BoxCollider<T>::collidesWith(const Collider<T>& collider) const {
    return collider.dispatchCollidesWith(*this);
}
template <class T>
bool BoxCollider<T>::dispatchCollidesWith(const BoxCollider<T>& collider) const {
    return Collider<T>::collide(*this, collider);
}
template <class T>
bool BoxCollider<T>::dispatchCollidesWith(const CircleCollider<T>& collider) const {
    return Collider<T>::collide(*this, collider);
}
template <class T>
bool BoxCollider<T>::dispatchCollidesWith(const PolygonCollider<T>& collider) const {
    return Collider<T>::collide(*this, collider);
}


/** operator<<
 *
 * Displays a box collider.
 */
template <class T>
std::ostream& operator<<(std::ostream& output, BoxCollider<T>& c) {
    output << "BoxCollider{" << c.center << " " << c.width
        << " " << c.height << " " << c.alpha << "}";
    return output;
}

#endif
