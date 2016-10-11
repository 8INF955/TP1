#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>
#include <memory>
#include "CollisionEngine.hpp"

template <class T>
struct Object {
    /* ATTRIBUTES */
    Vector<T> speed;
    float mass;
    std::shared_ptr<Collider<T>> collider;
    bool kinetic;

    /* CONSTRUCTORS */
    Object(Vector<T> speed = Vector<T>(), float mass = 1, bool kinetic = true):
            speed(speed), mass(mass), kinetic(kinetic) {}

    /* METHODS */
    void addPermanentForce(Vector<T> force);
    void addInstantForce(Vector<T> force);
    void move(double duration);

private:
    std::vector<Vector<T>> permanentForces;
    std::vector<Vector<T>> instantForces;
};

template <class T>
void Object<T>::addPermanentForce(Vector<T> force) {
    if(!kinetic) {
        permanentForces.push_back(force);
    }
}

template <class T>
void Object<T>::addInstantForce(Vector<T> force) {
    if(!kinetic) {
        instantForces.push_back(force);
    }
}

template <class T>
void Object<T>::move(double duration) {
    // Appliquer les forces régulières
    for(auto it = permanentForces.begin(); it != permanentForces.end(); it++) {
        speed += (*it) * duration;
    }
    // Appliquer les forces instantanées
    for(auto it = instantForces.begin(); it != instantForces.end(); it++) {
        speed += *it;
    }
    instantForces.erase(instantForces.begin(), instantForces.end());

    // Modifier la vitesse
    collider->center += speed * duration;
}

#endif
