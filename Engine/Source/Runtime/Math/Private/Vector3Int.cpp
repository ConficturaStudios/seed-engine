/**
 * Vector3Int.cpp
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

    const Vector3Int Vector3Int::UP = Vector3Int(0, 1, 0);
    const Vector3Int Vector3Int::DOWN = Vector3Int(0, -1, 0);
    const Vector3Int Vector3Int::LEFT = Vector3Int(-1, 0, 0);
    const Vector3Int Vector3Int::RIGHT = Vector3Int(1, 0, 0);
    const Vector3Int Vector3Int::FORWARD = Vector3Int(0, 0, 1);
    const Vector3Int Vector3Int::BACKWARD = Vector3Int(0, 0, -1);
    const Vector3Int Vector3Int::ONE = Vector3Int(1);
    const Vector3Int Vector3Int::ZERO = Vector3Int(0);

    // Constructors

    Vector3Int::Vector3Int() noexcept = default;

    Vector3Int::Vector3Int(int value) noexcept : Vector3Int(value, value, value) {};

    Vector3Int::Vector3Int(int x, int y, int z) noexcept {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3Int::Vector3Int(const Vector2Int& xy, int z) noexcept {
        this->x = xy.x;
        this->y = xy.y;
        this->z = z;
    }

    Vector3Int::Vector3Int(int x, const Vector2Int& yz) noexcept {
        this->x = x;
        this->y = yz.x;
        this->z = yz.y;
    }

    Vector3Int::Vector3Int(const int (&buffer)[SIZE]) {
        this->buffer[0] = buffer[0];
        this->buffer[1] = buffer[1];
        this->buffer[2] = buffer[2];
    }

    Vector3Int::Vector3Int(const Vector3Int& vec) noexcept {
        this->buffer[0] = vec.buffer[0];
        this->buffer[1] = vec.buffer[1];
        this->buffer[2] = vec.buffer[2];
    }

    Vector3Int::Vector3Int(Vector3Int&& vec) noexcept {
        this->buffer[0] = vec.buffer[0];
        this->buffer[1] = vec.buffer[1];
        this->buffer[2] = vec.buffer[2];
    }

    // Static Functions

    float Vector3Int::angle(const Vector3Int& v0, const Vector3Int& v1) {
        return math::acos((float)dot(v0, v1)) / (magnitude(v0) * magnitude(v1));
    }

    float Vector3Int::distance(const Vector3Int& v0, const Vector3Int& v1) {
        return magnitude(v0 - v1);
    }

    int Vector3Int::dot(const Vector3Int& v0, const Vector3Int& v1) {
        int t = 0;
        for (int i = 0; i < SIZE; i++) {
            t += (v0.buffer[i]) * (v1.buffer[i]);
        }
        return t;
    }

    Vector3Int Vector3Int::cross(const Vector3Int& v0, const Vector3Int& v1) {
        return Vector3Int(
            v0.y * v1.z - v0.z * v1.y,
            v0.z * v1.x - v0.x * v1.z,
            v0.x * v1.y - v0.y * v1.x
        );
    }

    float Vector3Int::magnitude(const Vector3Int& v) {
        return math::sqrt((float)dot(v, v));
    }

    int Vector3Int::mag2(const Vector3Int& v) {
        return dot(v, v);
    }

    // Member Functions

    float Vector3Int::angle(const Vector3Int& v) const {
        return angle(*this, v);
    }

    float Vector3Int::distance(const Vector3Int& v) const {
        return distance(*this, v);
    }

    int Vector3Int::dot(const Vector3Int& v) const {
        return dot(*this, v);
    }

    Vector3Int Vector3Int::cross(const Vector3Int& v) const {
        return cross(*this, v);
    }

    float Vector3Int::magnitude() const {
        return magnitude(*this);
    }

    int Vector3Int::mag2() const {
        return mag2(*this);
    }

    // Accessor operators

    int& Vector3Int::operator[](int index) {
        if (index < 0 || index >= SIZE) throw std::out_of_range("Attempting to access out of range element.");
        return buffer[index];
    }

    const int& Vector3Int::operator[](int index) const {
        if (index < 0 || index >= SIZE) throw std::out_of_range("Attempting to access out of range element.");
        return buffer[index];
    }

    // Arithmetic operators

    Vector3Int Vector3Int::operator+(const Vector3Int& vec) const {
        Vector3Int v = Vector3Int();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] + vec.buffer[i];
        }
        return v;
    }

    Vector3Int Vector3Int::operator+(int f) const {
        Vector3Int v = Vector3Int();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] + f;
        }
        return v;
    }

    Vector3Int Vector3Int::operator-(const Vector3Int& vec) const {
        Vector3Int v = Vector3Int();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] - vec.buffer[i];
        }
        return v;
    }

    Vector3Int Vector3Int::operator-(int f) const {
        Vector3Int v = Vector3Int();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] - f;
        }
        return v;
    }

    Vector3Int Vector3Int::operator/(const Vector3Int& vec) const {
        Vector3Int v = Vector3Int();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] / vec.buffer[i];
        }
        return v;
    }

    Vector3Int Vector3Int::operator/(int f) const {
        Vector3Int v = Vector3Int();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] / f;
        }
        return v;
    }

    Vector3Int Vector3Int::operator*(const Vector3Int& vec) const {
        Vector3Int v = Vector3Int();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] * vec.buffer[i];
        }
        return v;
    }

    Vector3Int Vector3Int::operator*(int f) const {
        Vector3Int v = Vector3Int();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] * f;
        }
        return v;
    }

    // Boolean operators

    bool Vector3Int::operator==(const Vector3Int& vec) const {
        bool e = true;
        for (int i = 0; i < SIZE; i++) {
            e &= (this->buffer[i] == vec.buffer[i]);
        }
        return e;
    }

    bool Vector3Int::operator!=(const Vector3Int& vec) const {
        return !(*this == vec);
    }

    // Assignment operators

    Vector3Int& Vector3Int::operator=(const Vector3Int& vec) {
        if (this == &vec) return *this;
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
        return *this;
    }

    Vector3Int& Vector3Int::operator=(int value) {
        for (int i = 0; i < SIZE; i++) {
            buffer[i] = value;
        }
        return *this;
    }

    // Cast operators

    Vector3Int::operator Vector2() const {
        return Vector2((float)x, (float)y);
    }

    Vector3Int::operator Vector3() const {
        return Vector3((float)x, (float)y, (float)z);
    }

    Vector3Int::operator Vector4() const {
        return Vector4((float)x, (float)y, (float)z, 0);
    }

    Vector3Int::operator Vector2Int() const {
        return Vector2Int(x, y);
    }

    Vector3Int::operator Vector4Int() const {
        return Vector4Int(x, y, z, 0);
    }


    Vector3Int::operator Matrix1x2Int() const {
        Matrix1x2Int::Type arr[1][2] = { {x, y} };
        return Matrix1x2Int(arr);
    }

    Vector3Int::operator Matrix1x3Int() const {
        Matrix1x3Int::Type arr[1][3] = { {x, y, z} };
        return Matrix1x3Int(arr);
    }

    Vector3Int::operator Matrix1x4Int() const {
        Matrix1x4Int::Type arr[1][4] = { {x, y, z, 0} };
        return Matrix1x4Int(arr);
    }

    Vector3Int::operator Matrix2x1Int() const {
        Matrix2x1Int::Type arr[2][1] = { {x}, {y} };
        return Matrix2x1Int(arr);
    }

    Vector3Int::operator Matrix3x1Int() const {
        Matrix3x1Int::Type arr[3][1] = { {x}, {y}, {z} };
        return Matrix3x1Int(arr);
    }

    Vector3Int::operator Matrix4x1Int() const {
        Matrix4x1Int::Type arr[4][1] = { {x}, {y}, {z}, {0} };
        return Matrix4x1Int(arr);
    }


    Vector3Int::operator ::std::string() const {
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

    ENGINE_API Vector3Int operator+(int f, const Vector3Int& vector) {
        return vector + f;
    }
    ENGINE_API Vector3Int operator-(int f, const Vector3Int& vector) {
        return Vector3Int(f - vector.x, f - vector.y, f - vector.z);
    }
    ENGINE_API Vector3Int operator*(int f, const Vector3Int& vector) {
        return vector * f;
    }
    ENGINE_API Vector3Int operator/(int f, const Vector3Int& vector) {
        return Vector3Int(f / vector.x, f / vector.y, f / vector.z);
    }

    // IO operators ----------------------------------------------------------

    ENGINE_API std::ostream& operator<< (std::ostream& os, const Vector3Int& c) {
        os << (std::string)c;
        return os;
    }

}