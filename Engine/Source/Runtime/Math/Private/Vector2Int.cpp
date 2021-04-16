/**
 * Vector2Int.cpp
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

    const Vector2Int Vector2Int::UP = Vector2Int(0, 1);
    const Vector2Int Vector2Int::DOWN = Vector2Int(0, -1);
    const Vector2Int Vector2Int::LEFT = Vector2Int(-1, 0);
    const Vector2Int Vector2Int::RIGHT = Vector2Int(1, 0);
    const Vector2Int Vector2Int::ONE = Vector2Int(1);
    const Vector2Int Vector2Int::ZERO = Vector2Int(0);

    // Constructors

    Vector2Int::Vector2Int() noexcept = default;

    Vector2Int::Vector2Int(int value) noexcept : Vector2Int(value, value) {};

    Vector2Int::Vector2Int(int x, int y) noexcept {
        this->x = x;
        this->y = y;
    }

    Vector2Int::Vector2Int(const int (&buffer)[SIZE]) {
        this->buffer[0] = buffer[0];
        this->buffer[1] = buffer[1];
    }

    Vector2Int::Vector2Int(const Vector2Int& vec) noexcept {
        this->buffer[0] = vec.buffer[0];
        this->buffer[1] = vec.buffer[1];
    }

    Vector2Int::Vector2Int(Vector2Int&& vec) noexcept {
        this->buffer[0] = vec.buffer[0];
        this->buffer[1] = vec.buffer[1];
    }

    // Static Functions

    float Vector2Int::angle(const Vector2Int& v0, const Vector2Int& v1) {
        return math::acos((float)dot(v0, v1)) / (magnitude(v0) * magnitude(v1));
    }

    float Vector2Int::distance(const Vector2Int& v0, const Vector2Int& v1) {
        return magnitude(v0 - v1);
    }

    int Vector2Int::dot(const Vector2Int& v0, const Vector2Int& v1) {
        int t = 0;
        for (int i = 0; i < SIZE; i++) {
            t += (v0.buffer[i]) * (v1.buffer[i]);
        }
        return t;
    }

    float Vector2Int::magnitude(const Vector2Int& v) {
        return math::sqrt((float)dot(v, v));
    }

    int Vector2Int::mag2(const Vector2Int& v) {
        return dot(v, v);
    }

    // Member Functions

    float Vector2Int::angle(const Vector2Int& v) const {
        return angle(*this, v);
    }

    float Vector2Int::distance(const Vector2Int& v) const {
        return distance(*this, v);
    }

    int Vector2Int::dot(const Vector2Int& v) const {
        return dot(*this, v);
    }

    float Vector2Int::magnitude() const {
        return magnitude(*this);
    }

    int Vector2Int::mag2() const {
        return mag2(*this);
    }

    // Accessor operators

    int& Vector2Int::operator[](int index) {
        if (index < 0 || index >= SIZE) throw std::out_of_range("Attempting to access out of range element.");
        return buffer[index];
    }

    const int& Vector2Int::operator[](int index) const {
        if (index < 0 || index >= SIZE) throw std::out_of_range("Attempting to access out of range element.");
        return buffer[index];
    }

    // Arithmetic operators

    Vector2Int Vector2Int::operator+(const Vector2Int& vec) const {
        Vector2Int v = Vector2Int();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] + vec.buffer[i];
        }
        return v;
    }

    Vector2Int Vector2Int::operator+(int f) const {
        Vector2Int v = Vector2Int();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] + f;
        }
        return v;
    }

    Vector2Int Vector2Int::operator-(const Vector2Int& vec) const {
        Vector2Int v = Vector2Int();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] - vec.buffer[i];
        }
        return v;
    }

    Vector2Int Vector2Int::operator-(int f) const {
        Vector2Int v = Vector2Int();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] - f;
        }
        return v;
    }

    Vector2Int Vector2Int::operator/(const Vector2Int& vec) const {
        Vector2Int v = Vector2Int();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] / vec.buffer[i];
        }
        return v;
    }

    Vector2Int Vector2Int::operator/(int f) const {
        Vector2Int v = Vector2Int();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] / f;
        }
        return v;
    }

    Vector2Int Vector2Int::operator*(const Vector2Int& vec) const {
        Vector2Int v = Vector2Int();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] * vec.buffer[i];
        }
        return v;
    }

    Vector2Int Vector2Int::operator*(int f) const {
        Vector2Int v = Vector2Int();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] * f;
        }
        return v;
    }

    // Boolean operators

    bool Vector2Int::operator==(const Vector2Int& vec) const {
        bool e = true;
        for (int i = 0; i < SIZE; i++) {
            e &= (this->buffer[i] == vec.buffer[i]);
        }
        return e;
    }

    bool Vector2Int::operator!=(const Vector2Int& vec) const {
        return !(*this == vec);
    }

    // Assignment operators

    Vector2Int& Vector2Int::operator=(const Vector2Int& vec) {
        if (this == &vec) return *this;
        this->x = vec.x;
        this->y = vec.y;
        return *this;
    }

    Vector2Int& Vector2Int::operator=(int value) {
        for (int i = 0; i < SIZE; i++) {
            buffer[i] = value;
        }
        return *this;
    }

    // Cast operators

    Vector2Int::operator Vector2() const {
        return Vector2((float)x, (float)y);
    }

    Vector2Int::operator Vector3() const {
        return Vector3((float)x, (float)y, 0);
    }

    Vector2Int::operator Vector4() const {
        return Vector4((float)x, (float)y, 0, 0);
    }

    Vector2Int::operator Vector3Int() const {
        return Vector3Int(x, y, 0);
    }

    Vector2Int::operator Vector4Int() const {
        return Vector4Int(x, y, 0, 0);
    }


    Vector2Int::operator Matrix1x2Int() const {
        Matrix1x2Int::Type arr[1][2] = { {x, y} };
        return Matrix1x2Int(arr);
    }

    Vector2Int::operator Matrix1x3Int() const {
        Matrix1x3Int::Type arr[1][3] = { {x, y, 0} };
        return Matrix1x3Int(arr);
    }

    Vector2Int::operator Matrix1x4Int() const {
        Matrix1x4Int::Type arr[1][4] = { {x, y, 0, 0} };
        return Matrix1x4Int(arr);
    }

    Vector2Int::operator Matrix2x1Int() const {
        Matrix2x1Int::Type arr[2][1] = { {x}, {y} };
        return Matrix2x1Int(arr);
    }

    Vector2Int::operator Matrix3x1Int() const {
        Matrix3x1Int::Type arr[3][1] = { {x}, {y}, {0} };
        return Matrix3x1Int(arr);
    }

    Vector2Int::operator Matrix4x1Int() const {
        Matrix4x1Int::Type arr[4][1] = { {x}, {y}, {0}, {0} };
        return Matrix4x1Int(arr);
    }


    Vector2Int::operator ::std::string() const {
        std::stringstream ss("");
        ss << "<";
        for (int i = 0; i < SIZE; i++) {
            ss << this->buffer[i];
            if (i < SIZE - 1) ss << ", ";
        }
        ss << ">";
        return ss.str();
    }

    // Arithmetic operators ----------------------------------------------------------

    ENGINE_API Vector2Int operator+(int f, const Vector2Int& vector) {
        return vector + f;
    }
    ENGINE_API Vector2Int operator-(int f, const Vector2Int& vector) {
        return Vector2Int(f - vector.x, f - vector.y);
    }
    ENGINE_API Vector2Int operator*(int f, const Vector2Int& vector) {
        return vector * f;
    }
    ENGINE_API Vector2Int operator/(int f, const Vector2Int& vector) {
        return Vector2Int(f / vector.x, f / vector.y);
    }

    // IO operators ----------------------------------------------------------

    ENGINE_API std::ostream& operator<< (std::ostream& os, const Vector2Int& c) {
        os << (std::string)c;
        return os;
    }

}