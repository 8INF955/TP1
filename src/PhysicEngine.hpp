#ifndef PHYSIC_ENGINE_HPP
#define PHYSIC_ENGINE_HPP

#include "Object.hpp"

template <class T>
struct PhysicEngine {
    static void process(std::vector<Object<T>>& scene, T delta);
}

template <class T>
void PhysicEngine<T>::process(std::vector<Object<T>>& scene, T delta) {
    Vector<T> g(0, 9.81);

    // Pour chaque objet de la scene
    for(auto it = scene.begin(); it != scene.end(); it++) {
        std::vector<Vector<T>> forbidden;
        // Qui n'est pas fixe
        if(!it->fixed) {
            // Le déplacer
            it->speed += g * delta;
            it->collider->move(it->speed * delta);
            // Regarder les autres objets en collision
            std::vector<Object<T>*> touched;
            for(auto it2 = scene.begin(); it2 != scene.end(); it2++) {
                if(it != it2 && Collider<float>::collide(*(it->collider), *(it2->collider))) {
                    touched.push_back(&(*it2));
                }
            }
            // Si il y a une collision détectée
            if(contactedObjects) {
                // Faire le déplacement inverse
                it->collider->move(- it->speed * delta);
                Contact<T> c;
                bool one = false;
                // Calculer la première qui a eu lieu
                for(auto it2 = touched.begin(); it2 != touched.end(); it2++) {
                    auto contact = Collider<T>::contact(*(it->collider),
                            *(it2->collider), it->speed);
                    // Le contact est survenu avant le minimum déjà enregistré
                    if(contact.distance < c.distance && contact.tangent ^ it->speed != 0) {
                        c = contact;
                    }
                }
                // Si on a au moins pu avancer un peu
                if(contact.distance != 0) {
                    
                }
            }
        }
    }
}

#endif
