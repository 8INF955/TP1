#include <ostream>
#include <vector>
#include <string>

#include "testIntersects.cpp"
#include "testCollisions.cpp"

int main() {
    std::vector<std::string> errors;

    // Tests sur Intersects
    testIntersects();

    // Tests sur Collider::collide
    testCollisions();

    return EXIT_SUCCESS;
}
