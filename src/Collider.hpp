#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <iostream>
#include "Vector.hpp"
#include "Component.hpp"

struct Collider : Component {

    Collider(std::string name): Component(name) {};
};

// Affichage d'un Collider
std::ostream& operator<<(std::ostream& output, Collider& c) {
    output << "Collider{\"" << c.name << "\"}";
    return output;
}

#endif
