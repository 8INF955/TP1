#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>
#include <string>

struct Component {

    Component(std::string name): name{name} {};

    std::string name;
};

// Affichage d'un Component
std::ostream& operator<<(std::ostream& output, Component& u) {
    output << "Component{\"" << u.name << "\"}";
    return output;
}

#endif
