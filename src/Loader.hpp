#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <regex>
#include <memory>
#include <algorithm>
#include "Object.hpp"
#include "CollisionEngine.hpp"

template <class T>
class Loader {
public:
    static std::shared_ptr<std::vector<Object<T>>> loadScene(const std::string& filename);
};

template <class T>
std::shared_ptr<std::vector<Object<T>>> Loader<T>::loadScene(const std::string& filename) {
    std::shared_ptr<std::vector<Object<float>>> scene = std::make_shared<std::vector<Object<float>>>();
    std::string line;
    std::string num = "(-?[0-9]+\\.?[0-9]*)";
    std::smatch match;
    const std::regex boxColliderRegex("BoxCollider\\{"+num+", "+num+", "+num+", "+num+", "+num+"\\}");
    const std::regex circleColliderRegex("CircleCollider\\{"+num+", "+num+", "+num+"\\}");
    const std::regex polygonColliderRegex("PolygonCollider\\{"+num+", "+num+", "+num+"\\}\\{(.*)\\}");
    std::string vector = "\\{" + num + ", " + num + "\\}";
    const std::regex nextVectorRegex("^" + vector + "(, (.*))?$");

    std::ifstream file(filename, std::ios::app);
    if(!file.is_open()) {
        throw std::string("Can't open file");
    }
    // Parse file
    while(std::getline(file, line)) {
        const std::string s = line;
        // Parse line
        if(s.size() > 0 && s[0] != '#') {
            if(std::regex_search(s, match, boxColliderRegex)) {
                std::string xStr = std::string(match[1]);
                std::string yStr = std::string(match[2]);
                std::string wStr = std::string(match[3]);
                std::string hStr = std::string(match[4]);
                std::string aStr = std::string(match[5]);
                T x = std::stod(xStr);
                T y = std::stod(yStr);
                T w = std::stod(wStr);
                T h = std::stod(hStr);
                T a = std::stod(aStr);
                std::shared_ptr<BoxCollider<T>> box = std::make_shared<BoxCollider<T>>(Vector<T>(x, y), w, h, a);
                scene->emplace_back();
                scene->back().collider = box;

            }
            if(std::regex_search(s, match, circleColliderRegex)) {
                std::string xStr = std::string(match[1]);
                std::string yStr = std::string(match[2]);
                std::string rStr = std::string(match[3]);
                T x = std::stod(xStr);
                T y = std::stod(yStr);
                T r = std::stod(rStr);
                std::shared_ptr<CircleCollider<T>> circle = std::make_shared<CircleCollider<T>>(Vector<T>(x, y), r);
                scene->emplace_back();
                scene->back().collider = circle;
            }
            if(std::regex_search(s, match, polygonColliderRegex)) {
                std::string xStr = std::string(match[1]);
                std::string yStr = std::string(match[2]);
                std::string aStr = std::string(match[3]);
                std::string pts = std::string(match[4]);
                T x = std::stod(xStr);
                T y = std::stod(yStr);
                T a = std::stod(aStr);
                std::shared_ptr<PolygonCollider<T>> poly = std::make_shared<PolygonCollider<T>>(Vector<T>(x, y), a);
                while(std::regex_search(pts, match, nextVectorRegex)) {
                    std::string pxStr = std::string(match[1]);
                    std::string pyStr = std::string(match[2]);
                    pts = std::string(match[4]);
                    T px = std::stod(pxStr);
                    T py = std::stod(pyStr);
                    poly->points.emplace_back(px, py);
                }
                scene->emplace_back();
                scene->back().collider = poly;
            }
        }
    }
    return scene;
}
