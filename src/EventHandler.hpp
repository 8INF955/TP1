#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include <SFML/Window.hpp>

class EventHandler {
public:
    EventHandler() {};
    virtual void handle(sf::Event) = 0;
};

#endif
