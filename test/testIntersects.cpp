#include <vector>
#include <string>
#include <chrono>

#include <cstdlib>
#include <ctime>

#include "CollisionEngine.hpp"

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

void testIntersects() {
    testIntersectsSegment();
}
