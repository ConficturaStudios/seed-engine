/**
 * Vector2.cpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Vector2Int.hpp"
#include "Vector3Int.hpp"
#include "Vector4Int.hpp"

namespace seedengine {

    // Define constants ------------------------------------------------------

    const Vector2 Vector2::UP = Vector2(0, 1);
    const Vector2 Vector2::DOWN = Vector2(0, -1);
    const Vector2 Vector2::LEFT = Vector2(-1, 0);
    const Vector2 Vector2::RIGHT = Vector2(1, 0);
    const Vector2 Vector2::ONE = Vector2(1);
    const Vector2 Vector2::ZERO = Vector2(0);

    // Constructors

    Vector2::Vector2() : Vector2(0) {};

    Vector2::Vector2(const float& value) : Vector2(value, value) {};

    Vector2::Vector2(const float& x, const float& y) {
        this->x = x;
        this->y = y;
    }

    Vector2::Vector2(const float (&buffer)[SIZE]) {
        this->buffer[0] = buffer[0];
        this->buffer[1] = buffer[1];
    }

    Vector2::Vector2(const Vector2& vec) {
        this->buffer[0] = vec.buffer[0];
        this->buffer[1] = vec.buffer[1];
    }

    Vector2::Vector2(Vector2&& vec) {
        this->buffer[0] = vec.buffer[0];
        this->buffer[1] = vec.buffer[1];
    }

    // Static Functions

    float Vector2::angle(const Vector2& v0, const Vector2& v1) {
        return math::acos(dot(v0, v1)) / (magnitude(v0) * magnitude(v1));
    }

    float Vector2::distance(const Vector2& v0, const Vector2& v1) {
        return magnitude(v0 - v1);
    }

    float Vector2::dot(const Vector2& v0, const Vector2& v1) {
        float t = 0;
        for (int i = 0; i < SIZE; i++) {
            t += (v0.buffer[i]) * (v1.buffer[i]);
        }
        return t;
    }

    float Vector2::magnitude(const Vector2& v) {
        return math::sqrt(dot(v, v));
    }

    float Vector2::mag2(const Vector2& v) {
        return dot(v, v);
    }

    Vector2 Vector2::normalize(const Vector2& v) {
        return v / magnitude(v);
    }

    Vector2 Vector2::reflect(const Vector2& incident, const Vector2& normal) {
        return incident - (2 * dot(normal, incident) * normal);
    }

    Vector2 Vector2::refract(const Vector2& incident, const Vector2& normal, const float& eta) {
        float d = dot(normal, incident);
        float t = 1 - (eta * eta * (1 - d * d));
        if (t < 0) return Vector2();
        else return (eta * incident) - ((eta * d + math::sqrt(t)) * normal);
    }

    Vector2 Vector2::project(const Vector2& a, const Vector2& b) {
        return b * (dot(a, b) / dot(b, b));
    }

    Vector2 Vector2::ortho(const Vector2& a, const Vector2& b) {
        return a - (b * (dot(a, b) / dot(b, b)));
    }

    Vector2 Vector2::rotate(const Vector2& v, const float& angle) {
        return Vector2(
            (math::cos(angle) * v.x) - (math::sin(angle) * v.y),
            (math::sin(angle) * v.x) + (math::cos(angle) * v.y)
        );
    }

    // Member Functions

    float Vector2::angle(const Vector2& v) const {
        return angle(*this, v);
    }

    float Vector2::distance(const Vector2& v) const {
        return distance(*this, v);
    }

    float Vector2::dot(const Vector2& v) const {
        return dot(*this, v);
    }

    float Vector2::magnitude() const {
        return magnitude(*this);
    }

    float Vector2::mag2() const {
        return mag2(*this);
    }

    Vector2 Vector2::normalize() const {
        return normalize(*this);
    }

    Vector2 Vector2::rotate(const float& angle) const {
        return rotate(*this, angle);
    }

    // Accessor operators

    float& Vector2::operator[](const int& index) {
        if (index < 0 || index >= SIZE) throw std::out_of_range("Attempting to access out of range element.");
        return buffer[index];
    }

    const float& Vector2::operator[](const int& index) const {
        if (index < 0 || index >= SIZE) throw std::out_of_range("Attempting to access out of range element.");
        return buffer[index];
    }

    // Arithmatic operators

    Vector2 Vector2::operator+(const Vector2& vec) const {
        Vector2 v = Vector2();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] + vec.buffer[i];
        }
        return v;
    }

    Vector2 Vector2::operator+(const float& f) const {
        Vector2 v = Vector2();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] + f;
        }
        return v;
    }

    Vector2 Vector2::operator-(const Vector2& vec) const {
        Vector2 v = Vector2();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] - vec.buffer[i];
        }
        return v;
    }

    Vector2 Vector2::operator-(const float& f) const {
        Vector2 v = Vector2();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] - f;
        }
        return v;
    }

    Vector2 Vector2::operator/(const Vector2& vec) const {
        Vector2 v = Vector2();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] / vec.buffer[i];
        }
        return v;
    }

    Vector2 Vector2::operator/(const float& f) const {
        Vector2 v = Vector2();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] / f;
        }
        return v;
    }

    Vector2 Vector2::operator*(const Vector2& vec) const {
        Vector2 v = Vector2();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] * vec.buffer[i];
        }
        return v;
    }

    Vector2 Vector2::operator*(const float& f) const {
        Vector2 v = Vector2();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] * f;
        }
        return v;
    }

    // Boolean operators

    bool Vector2::operator==(const Vector2& vec) const {
        bool e = true;
        for (int i = 0; i < SIZE; i++) {
            e &= (this->buffer[i] == vec.buffer[i]);
        }
        return e;
    }

    bool Vector2::operator!=(const Vector2& vec) const {
        return !(*this == vec);
    }

    // Assignment operators

    Vector2& Vector2::operator=(const Vector2& vec) {
        if (this == &vec) return *this;
        this->x = vec.x;
        this->y = vec.y;
        return *this;
    }

    Vector2& Vector2::operator=(const float& value) {
        for (int i = 0; i < SIZE; i++) {
            buffer[i] = value;
        }
        return *this;
    }

    // Cast operators

    Vector2::operator Vector3() const {
        return Vector3(x, y, 0);
    }

    Vector2::operator Vector4() const {
        return Vector4(x, y, 0, 0);
    }

    Vector2::operator Vector2Int() const {
        return Vector2Int((int)x, (int)y);
    }

    Vector2::operator Vector3Int() const {
        return Vector3Int((int)x, (int)y, 0);
    }

    Vector2::operator Vector4Int() const {
        return Vector4Int((int)x, (int)y, 0, 0);
    }


    Vector2::operator Matrix1x2() const {
        Matrix1x2::type arr[1][2] = { {x, y} };
        return Matrix1x2(arr);
    }

    Vector2::operator Matrix1x3() const {
        Matrix1x3::type arr[1][3] = { {x, y, 0} };
        return Matrix1x3(arr);
    }

    Vector2::operator Matrix1x4() const {
        Matrix1x4::type arr[1][4] = { {x, y, 0, 0} };
        return Matrix1x4(arr);
    }

    Vector2::operator Matrix2x1() const {
        Matrix2x1::type arr[2][1] = { {x}, {y} };
        return Matrix2x1(arr);
    }

    Vector2::operator Matrix3x1() const {
        Matrix3x1::type arr[3][1] = { {x}, {y}, {0} };
        return Matrix3x1(arr);
    }

    Vector2::operator Matrix4x1() const {
        Matrix4x1::type arr[4][1] = { {x}, {y}, {0}, {0} };
        return Matrix4x1(arr);
    }


    Vector2::operator std::string() const {
        std::stringstream ss("");
        ss << "<";
        for (int i = 0; i < SIZE; i++) {
            ss << this->buffer[i];
            if (i < SIZE - 1) ss << ", ";
        }
        ss << ">";
        return ss.str();
    }

    // Arithmatic operators ----------------------------------------------------------

    ENGINE_API Vector2 operator+(const float& f, const Vector2& vector) {
        return vector + f;
    }
    ENGINE_API Vector2 operator-(const float& f, const Vector2& vector) {
        return Vector2(f - vector.x, f - vector.y);
    }
    ENGINE_API Vector2 operator*(const float& f, const Vector2& vector) {
        return vector * f;
    }
    ENGINE_API Vector2 operator/(const float& f, const Vector2& vector) {
        return Vector2(f / vector.x, f / vector.y);
    }

    // IO operators ----------------------------------------------------------

    ENGINE_API std::ostream& operator<< (std::ostream& os, const Vector2& c) {
        os << (std::string)c;
        return os;
    }

}