#include <vector>
#include <string>
#include <chrono>

#include "Vector.hpp"
#include <cstdlib>
#include <ctime>

#include "Intersects.hpp"

float r(float min = -100, float max = 100) {
    return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX/(min-max));
}

void testIntersectsSegment() {
    std::cout << "==== Segment ====" << std::endl;
    auto mark = "✗";

    mark = "✓";
    if(!intersects(Vector<float>(0, 0), Vector<float>(1, 0),
                  Vector<float>(1, 0), Vector<float>(2, 0))) {
        mark = "✗";
    }
    std::cout << "[" << mark << "] colinear end/end touching segments" << std::endl;

    mark = "✓";
    if(!intersects(Vector<float>(0, 0), Vector<float>(1, 0),
                  Vector<float>(1, 0), Vector<float>(2, 1))) {
        mark = "✗";
    }
    std::cout << "[" << mark << "] non-colinear end/end touching segments" << std::endl;

    mark = "✓";
    if(!intersects(Vector<float>(0, 0), Vector<float>(1, 0),
                  Vector<float>(0, -1), Vector<float>(2, 1))) {
        mark = "✗";
    }
    std::cout << "[" << mark << "] non-colinear end/mid touching segments" << std::endl;

    mark = "✓";
    if(intersects(Vector<float>(0, 0), Vector<float>(1, 0),
                  Vector<float>(0, -1), Vector<float>(2.1, 1))) {
        mark = "✗";
    }
    std::cout << "[" << mark << "] non-colinear non-touching segments" << std::endl;

    mark = "✓";
    if(intersects(Vector<float>(0, 0), Vector<float>(1, 0),
                  Vector<float>(0, 1), Vector<float>(1, 1))) {
        mark = "✗";
    }
    std::cout << "[" << mark << "] parallel segments" << std::endl;

    mark = "✓";
    if(!intersects(Vector<float>(0, 0), Vector<float>(2, 0),
                  Vector<float>(1, 0), Vector<float>(3, 0))) {
        mark = "✗";
    }
    std::cout << "[" << mark << "] colinear mid/mid touching segments" << std::endl;

    mark = "✓";
    if(intersects(Vector<float>(0, 0), Vector<float>(1, 0),
                  Vector<float>(2, 0), Vector<float>(3, 0))) {
        mark = "✗";
    }
    std::cout << "[" << mark << "] colinear non-touching segments" << std::endl;

    mark = "✓";
    if(intersects(Vector<float>(0, 0), Vector<float>(2, 0),
                  Vector<float>(1, 1), Vector<float>(3, 1))) {
        mark = "✗";
    }
    std::cout << "[" << mark << "] parallel segments" << std::endl;

    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    int k = 0;
    do {
        intersects(Vector<float>(r(), r()), Vector<float>(r(), r()),
                Vector<float>(r(), r()), Vector<float>(r(), r()));
        end = std::chrono::steady_clock::now();
        diff = end - start;
        k++;

    } while(std::chrono::duration<double>(diff).count() < 1);
    std::cout << "Did " << k << " Segment intersections in 1s." << std::endl;
}

void testIntersectsBoxCollider() {
    std::cout << "==== BoxCollider ====" << std::endl;
    auto mark = "✗";

    mark = "✓";
    BoxCollider<float> box1(Vector<float>(0, 0), 2, 2, 0);
    BoxCollider<float> box2(Vector<float>(0, 0), 2, 2, 0);
    if(!intersects(box1, box2)) {
        mark = "✗";
    }
    std::cout << "[" << mark << "] same BoxCollider" << std::endl;

    mark = "✓";
    box1 = BoxCollider<float>(Vector<float>(0, 0), float(2), float(2), float(0));
    box2 = BoxCollider<float>(Vector<float>(0, 0), float(2), float(2), float(1.4));
    if(!intersects(box1, box2)) {
        mark = "✗";
    }
    std::cout << "[" << mark << "] turned BoxCollider" << std::endl;

    mark = "✓";
    box1 = BoxCollider<float>(Vector<float>(0, 0), float(2), float(2), float(0));
    box2 = BoxCollider<float>(Vector<float>(2.1, 0), float(2), float(2), float(0));
    if(intersects(box1, box2)) {
        mark = "✗";
    }
    std::cout << "[" << mark << "] translated BoxCollider" << std::endl;

    mark = "✓";
    box1 = BoxCollider<float>(Vector<float>(0, 0), float(2), float(2), float(0));
    box2 = BoxCollider<float>(Vector<float>(2.1, 0), float(2), float(2), float(1));
    if(!intersects(box1, box2)) {
        mark = "✗";
    }
    std::cout << "[" << mark << "] translated turned BoxCollider" << std::endl;

}

void testIntersects() {
    testIntersectsSegment();
    testIntersectsBoxCollider();
}
