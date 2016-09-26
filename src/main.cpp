#include <ostream>
#include "Vector.hpp"
#include "BoxCollider.hpp"
#include "CircleCollider.hpp"
#include "Intersects.hpp"
#include <string>

int main() {
    BoxCollider<float> box("box", Vector<float>(2, 0), 2, 1);
    CircleCollider<float> circle("circle", Vector<float>(0, 0), 1);

    std::cout << intersects(box, circle) << std::endl;
    return EXIT_SUCCESS;
}
