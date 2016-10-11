#include <ostream>
#include <math.h>
#include <vector>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "CollisionEngine.hpp"

int main() {
    std::vector<Collider<float>> scene;

    // Le joueur est un carré (qui peut tourner à l'aide de 'A' et 'E')
    PolygonCollider<float> player(Vector<float>(640, 360), 0);
    player.points.emplace_back(0, 0);
    player.points.emplace_back(-50, 25);
    player.points.emplace_back(-25, 0);
    player.points.emplace_back(-50, -25);

    BoxCollider<float> boxObstacle(Vector<float>(100, 100), 50, 50, 0);
    CircleCollider<float> circleObstacle(Vector<float>(400, 250), 100);
    PolygonCollider<float> polygonObstacle(Vector<float>(900, 600), 0);
    polygonObstacle.points.emplace_back(-100, -100);
    polygonObstacle.points.emplace_back(0, -150);
    polygonObstacle.points.emplace_back(100, -100);
    polygonObstacle.points.emplace_back(150, 0);
    polygonObstacle.points.emplace_back(100, 100);
    polygonObstacle.points.emplace_back(-50, 50);

    Vector<float> speed(0, 0);
    Vector<float> acceleration(0, 0);
    Vector<float> mouse(0, 0);

    sf::RenderWindow window(sf::VideoMode(1280, 720), "TP1 PCDJV");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    while (window.isOpen()) {
        /* Gestion des évènements */
        sf::Event event;
        while(window.pollEvent(event)) {
            switch(event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseMoved:
                mouse = Vector<float>(event.mouseMove.x, event.mouseMove.y);
                break;
            default:
                break;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            acceleration.x = -.2;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            acceleration.x = .2;
        }
        else {
            acceleration.x = 0;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            acceleration.y = -.2;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            acceleration.y = .2;
        }
        else {
            acceleration.y = 0;
        }

        /* Movement du joueur */
        if(acceleration.norm2() > 0) {
            acceleration.normalize();
        }
        if(speed.norm2() > 0) {
            speed.normalize(std::max(speed.norm() - 0.7, 0.));
        }
        speed += acceleration;
        if(speed.norm2() > 100) {
            speed.normalize(10);
        }
        player.center += speed;
        player.alpha = (mouse - player.center).angle();

        /* Affichage */
        window.clear(sf::Color(0, 0, 0));

        // Box Obstacle
        auto boxShape = boxObstacle.shape();
        boxShape->setFillColor(sf::Color::Transparent);
        if(Collider<float>::collide(boxObstacle, player)) {
            boxShape->setOutlineColor(sf::Color::Red);
        }
        else {
            boxShape->setOutlineColor(sf::Color::Green);
        }
        boxShape->setOutlineThickness(1);
        window.draw(*boxShape);
        auto aabbBox = boxObstacle.aabb().shape();
        aabbBox->setFillColor(sf::Color::Transparent);
        aabbBox->setOutlineColor(sf::Color(100, 100, 100, 100));
        aabbBox->setOutlineThickness(1);
        window.draw(*aabbBox);

        auto polyShape = polygonObstacle.shape();
        polyShape->setFillColor(sf::Color::Transparent);
        if(Collider<float>::collide(polygonObstacle, player)) {
            polyShape->setOutlineColor(sf::Color::Red);
        }
        else {
            polyShape->setOutlineColor(sf::Color::Green);
        }
        polyShape->setOutlineThickness(1);
        window.draw(*polyShape);
        auto aabbPoly = polygonObstacle.aabb().shape();
        aabbPoly->setFillColor(sf::Color::Transparent);
        aabbPoly->setOutlineColor(sf::Color(100, 100, 100, 100));
        aabbPoly->setOutlineThickness(1);
        window.draw(*aabbPoly);

        // Circle Obstacle
        auto circleShape = circleObstacle.shape();
        circleShape->setFillColor(sf::Color::Transparent);
        if(Collider<float>::collide(player, circleObstacle)) {
            circleShape->setOutlineColor(sf::Color::Red);
        }
        else {
            circleShape->setOutlineColor(sf::Color::Green);
        }
        circleShape->setOutlineThickness(1);
        window.draw(*circleShape);
        boxShape->setOutlineThickness(1);
        window.draw(*boxShape);
        auto aabbCircle = circleObstacle.aabb().shape();
        aabbCircle->setFillColor(sf::Color::Transparent);
        aabbCircle->setOutlineColor(sf::Color(100, 100, 100, 100));
        aabbCircle->setOutlineThickness(1);
        window.draw(*aabbCircle);

        // Player
        auto playerShape = player.shape();
        playerShape->setFillColor(sf::Color::Transparent);
        playerShape->setOutlineColor(sf::Color(255, 255, 0));
        playerShape->setOutlineThickness(1);
        window.draw(*playerShape);
        auto aabbPlayer = player.aabb().shape();
        aabbPlayer->setFillColor(sf::Color::Transparent);
        aabbPlayer->setOutlineColor(sf::Color(100, 100, 100, 100));
        aabbPlayer->setOutlineThickness(1);
        window.draw(*aabbPlayer);

        window.display();
    }

    return EXIT_SUCCESS;
}
