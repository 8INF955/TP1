#include <iostream>
#include <memory>
#include "Loader.hpp"
#include "Simulation.hpp"
#include "CreateBallEventHandler.hpp"
#include <SFML/Graphics.hpp>

int main() {
    // Chargement de la scene
    auto scene = Loader<float>::loadScene(std::string("scene.txt"));

    // Création de la fenêtre d'affichage
    std::shared_ptr<sf::RenderWindow> window =
        std::make_shared<sf::RenderWindow>(sf::VideoMode(1280, 720), "TP1 PCDJV");
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(60);

    // Création du gestionnaire d'évènements global
    std::shared_ptr<CreateBallEventHandler<float>> eh = std::make_shared<CreateBallEventHandler<float>>(scene, window);

    // Création de la simulation
    Simulation<float> sim(scene, window, std::chrono::duration<double>(0.03), eh);

    sim.start();
    // auto t = sim.start();
    // t.join();

    return EXIT_SUCCESS;
}
