#include <vector>
#include <string>
#include <chrono>

#include <cstdlib>
#include <ctime>

#include "CollisionEngine.hpp"

void testCollisionsBoxCollider() {
    std::cout << "==== BoxCollider ====" << std::endl;
    auto mark = "✗";

    mark = "✓";
    BoxCollider<float> box1(Vector<float>(0, 0), 2, 2, 0);
    BoxCollider<float> box2(Vector<float>(0, 0), 2, 2, 0);
    if(!Collider<float>::collide(box1, box2)) {
        mark = "✗";
    }
    std::cout << "[" << mark << "] same BoxCollider" << std::endl;

    mark = "✓";
    box1 = BoxCollider<float>(Vector<float>(0, 0), float(2), float(2), float(0));
    box2 = BoxCollider<float>(Vector<float>(0, 0), float(2), float(2), float(1.4));
    if(!Collider<float>::collide(box1, box2)) {
        mark = "✗";
    }
    std::cout << "[" << mark << "] turned BoxCollider" << std::endl;

    mark = "✓";
    box1 = BoxCollider<float>(Vector<float>(0, 0), float(2), float(2), float(0));
    box2 = BoxCollider<float>(Vector<float>(2.1, 0), float(2), float(2), float(0));
    if(Collider<float>::collide(box1, box2)) {
        mark = "✗";
    }
    std::cout << "[" << mark << "] translated BoxCollider" << std::endl;

    mark = "✓";
    box1 = BoxCollider<float>(Vector<float>(0, 0), float(2), float(2), float(0));
    box2 = BoxCollider<float>(Vector<float>(2.1, 0), float(2), float(2), float(1));
    if(!Collider<float>::collide(box1, box2)) {
        mark = "✗";
    }
    std::cout << "[" << mark << "] translated turned BoxCollider" << std::endl;

}

void testCollisionsCircleCollider() {
    std::cout << "==== CircleCollider ====" << std::endl;
    auto mark = "✗";

    mark = "✓";
    CircleCollider<float> cir1(Vector<float>(0, 0), 50);
    CircleCollider<float> cir2(Vector<float>(0, 0), 50);
    if(!Collider<float>::collide(cir1, cir2)) {
        mark = "✗";
    }
    std::cout << "[" << mark << "] same CircleCollider" << std::endl;

    mark = "✓";
    cir1 = CircleCollider<float>(Vector<float>(0, 0), 50);
    cir2 = CircleCollider<float>(Vector<float>(0, 0), 100);
    if(!Collider<float>::collide(cir1, cir2)) {
        mark = "✗";
    }
    std::cout << "[" << mark << "] small CircleCollider in big one" << std::endl;

    mark = "✓";
    cir1 = CircleCollider<float>(Vector<float>(0, 0), 50);
    cir2 = CircleCollider<float>(Vector<float>(0, 100), 50);
    if(!Collider<float>::collide(cir1, cir2)) {
        mark = "✗";
    }
    std::cout << "[" << mark << "] just touching CircleCollider" << std::endl;

    mark = "✓";
    cir1 = CircleCollider<float>(Vector<float>(0, 0), 50);
    cir2 = CircleCollider<float>(Vector<float>(20, 70), 50);
    if(!Collider<float>::collide(cir1, cir2)) {
        mark = "✗";
    }
    std::cout << "[" << mark << "] touching CircleCollider" << std::endl;

    mark = "✓";
    cir1 = CircleCollider<float>(Vector<float>(0, 0), 50);
    cir2 = CircleCollider<float>(Vector<float>(90, 90), 50);
    if(Collider<float>::collide(cir1, cir2)) {
        mark = "✗";
    }
    std::cout << "[" << mark << "] aabb touching but not CircleCollider" << std::endl;

    mark = "✓";
    cir1 = CircleCollider<float>(Vector<float>(0, 0), 50);
    cir2 = CircleCollider<float>(Vector<float>(1000, 1000), 50);
    if(Collider<float>::collide(cir1, cir2)) {
        mark = "✗";
    }
    std::cout << "[" << mark << "] far CircleCollider" << std::endl;
}

void testCollisionsPolygonCollider() {
    std::cout << "==== PolygonCollider ====" << std::endl;
    std::cout << "... none yet !" << std::endl;
}

void testCollisionsCrossCollider() {
    std::cout << "==== Mutliple types of Collider ====" << std::endl;
    std::cout << "... none yet !" << std::endl;
}

void testCollisions() {
    testCollisionsBoxCollider();
    testCollisionsCircleCollider();
    testCollisionsPolygonCollider();
    testCollisionsCrossCollider();
}
