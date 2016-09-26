#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <cmath>

template <class T>
struct Vector {
    Vector(T x = 0, T y = 0): x{x}, y{y} {};
    Vector(const Vector& v): x{v.x}, y{v.y} {};

    decltype(std::declval<T>()*std::declval<T>()) norm() const;
    decltype(std::declval<T>()*std::declval<T>()) norm2() const;
    decltype(std::atan2(std::declval<T>(), std::declval<T>())) angle() const;

    void normalize(T n = 1);

    T x;
    T y;
};

// Norme d'un vecteur
template <class T>
decltype(std::declval<T>()*std::declval<T>()) Vector<T>::norm() const {
    return std::sqrt(x * x + y * y);
}

// Norme au carré d'un vecteur
template <class T>
decltype(std::declval<T>()*std::declval<T>()) Vector<T>::norm2() const {
    return x * x + y * y;
}

// Angle avec l'horizontale d'un vecteur
template <class T>
decltype(std::atan2(std::declval<T>(), std::declval<T>())) Vector<T>::angle() const {
    return std::atan2(y, x);
}

// Normalisation d'un vecteur - ATTENTION selon le type
template <class T>
void Vector<T>::normalize(T n) {
    n /= norm();
    x *= n;
    y *= n;
}

/* **************************************************************** */

// Somme entre deux vecteurs
template <class T, class U>
Vector<decltype(std::declval<T>()+std::declval<U>())> operator+(
        const Vector<T>& u, const Vector<U>& v) {
    return {u.x + v.x, u.y + v.y};
}
template <class T, class U>
Vector<T>& operator+=(Vector<T>& u, const Vector<U>& v) {
    u.x += v.x;
    u.y += v.y;
    return u;
}

// Somme entre un vecteur et autre chose
template <class T, class U>
Vector<decltype(std::declval<T>()+std::declval<U>())> operator+(
        const Vector<T>& u, const U& a) {
    return {u.x + a, u.y + a};
}
template <class T, class U>
Vector<T>& operator+=(Vector<T>& u, const U& a) {
    u.x += a;
    u.y += a;
    return u;
}

// Soustraction entre deux vecteurs
template <class T, class U>
Vector<decltype(std::declval<T>()-std::declval<U>())> operator-(
        const Vector<T>& u, const Vector<U>& v) {
    return {u.x - v.x, u.y - v.y};
}
template <class T, class U>
Vector<T>& operator-=(Vector<T>& u, const Vector<U>& v) {
    u.x -= v.x;
    u.y -= v.y;
    return u;
}

// Soustraction entre un vecteur et autre chose
template <class T, class U>
Vector<decltype(std::declval<T>()-std::declval<U>())> operator-(
        const Vector<T>& u, const U& a) {
    return {u.x - a, u.y - a};
}
template <class T, class U>
Vector<T>& operator-=(Vector<T>& u, const U& a) {
    u.x -= a;
    u.y -= a;
    return u;
}

// Multiplication entre deux vecteurs
template <class T, class U>
Vector<decltype(std::declval<T>()*std::declval<U>())> operator*(
        const Vector<T>& u, const Vector<U>& v) {
    return {u.x * v.x, u.y * v.y};
}
template <class T, class U>
Vector<T>& operator*=(Vector<T>& u, const Vector<U>& v) {
    u.x *= v.x;
    u.y *= v.y;
    return u;
}

// Multiplication entre un vecteur et autre chose
template <class T, class U>
Vector<decltype(std::declval<T>()*std::declval<U>())> operator*(
        const Vector<T>& u, const U& a) {
    return {u.x * a, u.y * a};
}
template <class T, class U>
Vector<T>& operator*=(Vector<T>& u, const U& a) {
    u.x *= a;
    u.y *= a;
    return u;
}

// Division entre deux vecteurs
template <class T, class U>
Vector<decltype(std::declval<T>()/std::declval<U>())> operator/(
        const Vector<T>& u, const Vector<U>& v) {
    return {u.x / v.x, u.y / v.y};
}
template <class T, class U>
Vector<T>& operator/=(Vector<T>& u, const Vector<U>& v) {
    u.x /= v.x;
    u.y /= v.y;
    return u;
}

// Division entre un vecteur et autre chose
template <class T, class U>
Vector<decltype(std::declval<T>()/std::declval<U>())> operator/(
        const Vector<T>& u, const U& a) {
    return {u.x / a, u.y / a};
}
template <class T, class U>
Vector<T>& operator/=(Vector<T>& u, const U& a) {
    u.x /= a;
    u.y /= a;
    return u;
}

// Produit scalaire entre deux vecteurs
template <class T, class U>
decltype(std::declval<T>()*std::declval<U>()) operator|(
        const Vector<T>& u, const Vector<U>& v) {
    return u.x * v.x + u.y * v.y;
}


// Produit cartésien entre deux vecteurs
template <class T, class U>
decltype(std::declval<T>()*std::declval<U>()) operator^(
        const Vector<T>& u, const Vector<U>& v) {
    return u.x * v.y - u.y * v.x;
}

// Affichage d'un vecteur
template <class T>
std::ostream& operator<<(std::ostream& output, const Vector<T>& u) {
    output << "{" << u.x << ", " << u.y << "}";
    return output;
}

#endif
