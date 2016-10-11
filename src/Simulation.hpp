#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <thread>
#include <chrono>
#include "Object.hpp"
#include "EventHandler.hpp"

template <class T>
struct Simulation {
    /* ATTRIBUTES */
    // Les objets de la simulation
    std::shared_ptr<std::vector<Object<T>>> scene;
    // La fenêtre d'affichage SFML
    std::shared_ptr<sf::RenderWindow> window;
    // Le framerate de la simulation
    std::chrono::duration<double> frameRate;
    // Gestionnaire d'évènements global
    std::shared_ptr<EventHandler> globalEventHandler;

    /* CONSTRUCTORS */
    Simulation(std::shared_ptr<std::vector<Object<T>>> scene,
            std::shared_ptr<sf::RenderWindow> window,
            std::chrono::duration<double> frameRate,
            std::shared_ptr<EventHandler> globalEventHandler):
            scene(scene), window(window), frameRate(frameRate),
            globalEventHandler(globalEventHandler) {}

    /* METHODS */
    // std::thread start();
    void start();
    void stop();

private:
    /* ATTRIBUTES */
    bool shouldStop = false;

    /* METHODS */
    void run();
    void runEvents();
    void runPhysic();
    void displayScene();
};

template <class T>
void Simulation<T>::start() {
    if(!scene || !window) {
        throw "La simulation ne peut démarrer sans fenêtre ou sans scène.";
    }
    shouldStop = false;
    // return std::thread(&Simulation<T>::run, this);
    run();
}

template <class T>
void Simulation<T>::run() {
    while(!shouldStop) {
        // Initialisation de l'horloge
        auto startTime = std::chrono::high_resolution_clock::now();

        // Gestion des évènements
        runEvents();
        if(!window->isOpen()) {
            shouldStop = true;
            break;
        }

        // Gestion de la physique
        runPhysic();

        // Affichage de la scène
        displayScene();

        // Calcul du temps pris par la boucle
        auto endTime = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(frameRate - (endTime - startTime));
    }
}

template <class T>
void Simulation<T>::runEvents() {
    if(window->isOpen()) {
        sf::Event event;
        while(window->pollEvent(event)) {
            globalEventHandler->handle(event);
        }
    }
}

template <class T>
void Simulation<T>::runPhysic() {
    for(auto it = scene->begin(); it != scene->end(); it++) {
        it->move(frameRate.count());

        // Calcul des collisions
        for(auto jt = scene->begin(); jt != scene->end(); jt++) {
            // Si collision...
            if(it != jt && Collider<T>::collide(*(it->collider), *(jt->collider))) {
                // Appliquer une force répulsive
                /* TODO
                 * Ici il faudrait calculer la tangente au contact, etc.
                 */
                // !! Calcul stupide !!
                auto dir = (it->collider->center - jt->collider->center);
                dir.normalize(it->speed.norm());
                it->addInstantForce(dir);
            }
        }
    }
}

template <class T>
void Simulation<T>::displayScene() {
    if(window->isOpen()) {
        window->clear(sf::Color::Black);
        for(auto it = scene->begin(); it != scene->end(); it++) {
            auto aabb = it->collider->aabb().shape();
            aabb->setFillColor(sf::Color::Transparent);
            aabb->setOutlineColor(sf::Color(100, 100, 100, 150));
            aabb->setOutlineThickness(1);
            window->draw(*aabb);
            auto shape = it->collider->shape();
            shape->setFillColor(sf::Color::Transparent);
            shape->setOutlineColor(sf::Color::Green);
            shape->setOutlineThickness(1);
            window->draw(*shape);
        }
        window->display();
    }
}

#endif



