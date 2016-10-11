#ifndef CREATE_BALL_EVENT_HANDLER_HPP
#define CREATE_BALL_EVENT_HANDLER_HPP

#include <vector>
#include <memory>
#include <SFML/Window.hpp>
#include "Object.hpp"
#include "EventHandler.hpp"

template <class T>
class CreateBallEventHandler : public EventHandler {
    std::shared_ptr<std::vector<Object<T>>> scene;
    std::shared_ptr<sf::RenderWindow> window;
public:
    CreateBallEventHandler(std::shared_ptr<std::vector<Object<T>>> scene,
            std::shared_ptr<sf::RenderWindow> window):
            scene(scene), window(window) {}

    void handle(sf::Event event);
};

template <class T>
void CreateBallEventHandler<T>::handle(sf::Event event) {
    if(event.type == sf::Event::MouseButtonPressed) {
        scene->emplace_back(Vector<T>(), 1, false);
        scene->back().collider = std::make_shared<CircleCollider<T>>(
                Vector<T>(event.mouseButton.x, event.mouseButton.y), 25);
        scene->back().addPermanentForce(Vector<T>(0, 9.81*5));
    }
    else if(event.type == sf::Event::Closed) {
        window->close();
    }
}

#endif
