/**
 * Vector4Int.cpp
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

    const Vector4Int Vector4Int::UP = Vector4Int(0, 1, 0, 0);
    const Vector4Int Vector4Int::DOWN = Vector4Int(0, -1, 0, 0);
    const Vector4Int Vector4Int::LEFT = Vector4Int(-1, 0, 0, 0);
    const Vector4Int Vector4Int::RIGHT = Vector4Int(1, 0, 0, 0);
    const Vector4Int Vector4Int::FORWARD = Vector4Int(0, 0, 1, 0);
    const Vector4Int Vector4Int::BACKWARD = Vector4Int(0, 0, -1, 0);
    const Vector4Int Vector4Int::KATA = Vector4Int(0, 0, 0, 1);
    const Vector4Int Vector4Int::ANA = Vector4Int(0, 0, 0, -1);
    const Vector4Int Vector4Int::ONE = Vector4Int(1);
    const Vector4Int Vector4Int::ZERO = Vector4Int(0);

    // Constructors

    Vector4Int::Vector4Int() noexcept = default;

    Vector4Int::Vector4Int(int value) noexcept : Vector4Int(value, value, value, value) {};

    Vector4Int::Vector4Int(int x, int y, int z, int w) noexcept {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    Vector4Int::Vector4Int(const Vector2Int& xy, int z, int w) noexcept {
        this->x = xy.x;
        this->y = xy.y;
        this->z = z;
        this->w = w;
    }
    
    Vector4Int::Vector4Int(int x, const Vector2Int& yz, int w) noexcept {
        this->x = x;
        this->y = yz.x;
        this->z = yz.y;
        this->w = w;
    }

    Vector4Int::Vector4Int(int x, int y, const Vector2Int& zw) noexcept {
        this->x = x;
        this->y = y;
        this->z = zw.x;
        this->w = zw.y;
    }
    
    Vector4Int::Vector4Int(const Vector2Int& xy, const Vector2Int& zw) noexcept {
        this->x = xy.x;
        this->y = xy.y;
        this->z = zw.x;
        this->w = zw.y;
    }
    
    Vector4Int::Vector4Int(const Vector3Int& xyz, int w) noexcept {
        this->x = xyz.x;
        this->y = xyz.y;
        this->z = xyz.z;
        this->w = w;
    }
    
    Vector4Int::Vector4Int(int x, const Vector3Int& yzw) noexcept {
        this->x = x;
        this->y = yzw.x;
        this->z = yzw.y;
        this->w = yzw.z;
    }

    Vector4Int::Vector4Int(const int (&buffer)[SIZE]) {
        this->buffer[0] = buffer[0];
        this->buffer[1] = buffer[1];
        this->buffer[2] = buffer[2];
        this->buffer[3] = buffer[3];
    }

    Vector4Int::Vector4Int(const Vector4Int& vec) noexcept {
        this->buffer[0] = vec.buffer[0];
        this->buffer[1] = vec.buffer[1];
        this->buffer[2] = vec.buffer[2];
        this->buffer[3] = vec.buffer[3];
    }

    Vector4Int::Vector4Int(Vector4Int&& vec) noexcept {
        this->buffer[0] = vec.buffer[0];
        this->buffer[1] = vec.buffer[1];
        this->buffer[2] = vec.buffer[2];
        this->buffer[3] = vec.buffer[3];
    }

    // Static Functions

    float Vector4Int::angle(const Vector4Int& v0, const Vector4Int& v1) {
        return math::acos((float)dot(v0, v1)) / (magnitude(v0) * magnitude(v1));
    }

    float Vector4Int::distance(const Vector4Int& v0, const Vector4Int& v1) {
        return magnitude(v0 - v1);
    }

    int Vector4Int::dot(const Vector4Int& v0, const Vector4Int& v1) {
        int t = 0;
        for (int i = 0; i < SIZE; i++) {
            t += (v0.buffer[i]) * (v1.buffer[i]);
        }
        return t;
    }

    float Vector4Int::magnitude(const Vector4Int& v) {
        return math::sqrt((float)dot(v, v));
    }

    int Vector4Int::mag2(const Vector4Int& v) {
        return dot(v, v);
    }

    // Member Functions

    float Vector4Int::angle(const Vector4Int& v) const {
        return angle(*this, v);
    }

    float Vector4Int::distance(const Vector4Int& v) const {
        return distance(*this, v);
    }

    int Vector4Int::dot(const Vector4Int& v) const {
        return dot(*this, v);
    }

    float Vector4Int::magnitude() const {
        return magnitude(*this);
    }

    int Vector4Int::mag2() const {
        return mag2(*this);
    }

    // Accessor operators

    int& Vector4Int::operator[](int index) {
        if (index < 0 || index >= SIZE) throw std::out_of_range("Attempting to access out of range element.");
        return buffer[index];
    }

    const int& Vector4Int::operator[](int index) const {
        if (index < 0 || index >= SIZE) throw std::out_of_range("Attempting to access out of range element.");
        return buffer[index];
    }

    // Arithmetic operators

    Vector4Int Vector4Int::operator+(const Vector4Int& vec) const {
        Vector4Int v = Vector4Int();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] + vec.buffer[i];
        }
        return v;
    }

    Vector4Int Vector4Int::operator+(int f) const {
        Vector4Int v = Vector4Int();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] + f;
        }
        return v;
    }

    Vector4Int Vector4Int::operator-(const Vector4Int& vec) const {
        Vector4Int v = Vector4Int();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] - vec.buffer[i];
        }
        return v;
    }

    Vector4Int Vector4Int::operator-(int f) const {
        Vector4Int v = Vector4Int();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] - f;
        }
        return v;
    }

    Vector4Int Vector4Int::operator/(const Vector4Int& vec) const {
        Vector4Int v = Vector4Int();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] / vec.buffer[i];
        }
        return v;
    }

    Vector4Int Vector4Int::operator/(int f) const {
        Vector4Int v = Vector4Int();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] / f;
        }
        return v;
    }

    Vector4Int Vector4Int::operator*(const Vector4Int& vec) const {
        Vector4Int v = Vector4Int();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] * vec.buffer[i];
        }
        return v;
    }

    Vector4Int Vector4Int::operator*(int f) const {
        Vector4Int v = Vector4Int();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] * f;
        }
        return v;
    }

    // Boolean operators

    bool Vector4Int::operator==(const Vector4Int& vec) const {
        bool e = true;
        for (int i = 0; i < SIZE; i++) {
            e &= (this->buffer[i] == vec.buffer[i]);
        }
        return e;
    }

    bool Vector4Int::operator!=(const Vector4Int& vec) const {
        return !(*this == vec);
    }

    // Assignment operators

    Vector4Int& Vector4Int::operator=(const Vector4Int& vec) {
        if (this == &vec) return *this;
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
        this->w = vec.w;
        return *this;
    }

    Vector4Int& Vector4Int::operator=(int value) {
        for (int i = 0; i < SIZE; i++) {
            buffer[i] = value;
        }
        return *this;
    }

    // Cast operators

    Vector4Int::operator Vector2() const {
        return Vector2((float)x, (float)y);
    }

    Vector4Int::operator Vector3() const {
        return Vector3((float)x, (float)y, (float)z);
    }

    Vector4Int::operator Vector4() const {
        return Vector4((float)x, (float)y, (float)z, (float)w);
    }

    Vector4Int::operator Vector2Int() const {
        return Vector2Int(x, y);
    }

    Vector4Int::operator Vector3Int() const {
        return Vector3Int(x, y, z);
    }


    Vector4Int::operator Matrix1x2Int() const {
        Matrix1x2Int::Type arr[1][2] = { {x, y} };
        return Matrix1x2Int(arr);
    }

    Vector4Int::operator Matrix1x3Int() const {
        Matrix1x3Int::Type arr[1][3] = { {x, y, z} };
        return Matrix1x3Int(arr);
    }

    Vector4Int::operator Matrix1x4Int() const {
        Matrix1x4Int::Type arr[1][4] = { {x, y, z, w} };
        return Matrix1x4Int(arr);
    }

    Vector4Int::operator Matrix2x1Int() const {
        Matrix2x1Int::Type arr[2][1] = { {x}, {y} };
        return Matrix2x1Int(arr);
    }

    Vector4Int::operator Matrix3x1Int() const {
        Matrix3x1Int::Type arr[3][1] = { {x}, {y}, {z} };
        return Matrix3x1Int(arr);
    }

    Vector4Int::operator Matrix4x1Int() const {
        Matrix4x1Int::Type arr[4][1] = { {x}, {y}, {z}, {w} };
        return Matrix4x1Int(arr);
    }


    Vector4Int::operator ::std::string() const {
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

    ENGINE_API Vector4Int operator+(int f, const Vector4Int& vector) {
        return vector + f;
    }
    ENGINE_API Vector4Int operator-(int f, const Vector4Int& vector) {
        return Vector4Int(f - vector.x, f - vector.y, f - vector.z, f - vector.w);
    }
    ENGINE_API Vector4Int operator*(int f, const Vector4Int& vector) {
        return vector * f;
    }
    ENGINE_API Vector4Int operator/(int f, const Vector4Int& vector) {
        return Vector4Int(f / vector.x, f / vector.y, f / vector.z, f / vector.w);
    }

    // IO operators ----------------------------------------------------------

    ENGINE_API std::ostream& operator<< (std::ostream& os, const Vector4Int& c) {
        os << (std::string)c;
        return os;
    }

}