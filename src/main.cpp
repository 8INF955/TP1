#include <ostream>
#include <string>
#include "Intersects.hpp"

int main() {
    Vector<float> a(0, 0);
    Vector<float> b(1, 0);
    Vector<float> c(1, 0);
    Vector<float> d(2, 0);
    std::cout << intersects(a, b, c, d) << std::endl;
    return EXIT_SUCCESS;
}
