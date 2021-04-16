/**
 * Vector3.cpp
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

#include "Quaternion.hpp"

namespace seedengine {

    // Define constants ------------------------------------------------------

    const Vector3 Vector3::UP = Vector3(0, 1, 0);
    const Vector3 Vector3::DOWN = Vector3(0, -1, 0);
    const Vector3 Vector3::LEFT = Vector3(-1, 0, 0);
    const Vector3 Vector3::RIGHT = Vector3(1, 0, 0);
    const Vector3 Vector3::FORWARD = Vector3(0, 0, 1);
    const Vector3 Vector3::BACKWARD = Vector3(0, 0, -1);
    const Vector3 Vector3::ONE = Vector3(1);
    const Vector3 Vector3::ZERO = Vector3(0);

    // Constructors

    Vector3::Vector3() noexcept = default;

    Vector3::Vector3(float value) noexcept : Vector3(value, value, value) {};

    Vector3::Vector3(float x, float y, float z) noexcept {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3::Vector3(const Vector2& xy, float z) noexcept {
        this->x = xy.x;
        this->y = xy.y;
        this->z = z;
    }

    Vector3::Vector3(float x, const Vector2& yz) noexcept {
        this->x = x;
        this->y = yz.x;
        this->z = yz.y;
    }

    Vector3::Vector3(const float (&buffer)[SIZE]) {
        this->buffer[0] = buffer[0];
        this->buffer[1] = buffer[1];
        this->buffer[2] = buffer[2];
    }

    Vector3::Vector3(const Vector3& vec) noexcept {
        this->buffer[0] = vec.buffer[0];
        this->buffer[1] = vec.buffer[1];
        this->buffer[2] = vec.buffer[2];
    }

    Vector3::Vector3(Vector3&& vec) noexcept {
        this->buffer[0] = vec.buffer[0];
        this->buffer[1] = vec.buffer[1];
        this->buffer[2] = vec.buffer[2];
    }

    // Static Functions

    float Vector3::angle(const Vector3& v0, const Vector3& v1) {
        return math::acos(dot(v0, v1)) / (magnitude(v0) * magnitude(v1));
    }

    float Vector3::distance(const Vector3& v0, const Vector3& v1) {
        return magnitude(v0 - v1);
    }

    float Vector3::dot(const Vector3& v0, const Vector3& v1) {
        float t = 0;
        for (int i = 0; i < SIZE; i++) {
            t += (v0.buffer[i]) * (v1.buffer[i]);
        }
        return t;
    }

    Vector3 Vector3::cross(const Vector3& v0, const Vector3& v1) {
        return Vector3(
            v0.y * v1.z - v0.z * v1.y,
            v0.z * v1.x - v0.x * v1.z,
            v0.x * v1.y - v0.y * v1.x
        );
    }

    float Vector3::magnitude(const Vector3& v) {
        return math::sqrt(dot(v, v));
    }

    float Vector3::mag2(const Vector3& v) {
        return dot(v, v);
    }

    Vector3 Vector3::normalize(const Vector3& v) {
        return v / magnitude(v);
    }

    Vector3 Vector3::reflect(const Vector3& incident, const Vector3& normal) {
        return incident - (2 * dot(normal, incident) * normal);
    }

    Vector3 Vector3::refract(const Vector3& incident, const Vector3& normal, float eta) {
        float d = dot(normal, incident);
        float t = 1 - (eta * eta * (1 - d * d));
        if (t < 0) return Vector3();
        else return (eta * incident) - ((eta * d + math::sqrt(t)) * normal);
    }

    Vector3 Vector3::project(const Vector3& a, const Vector3& b) {
        return b * (dot(a, b) / dot(b, b));
    }

    Vector3 Vector3::ortho(const Vector3& a, const Vector3& b) {
        return a - (b * (dot(a, b) / dot(b, b)));
    }

    Vector3 Vector3::rotate(const Vector3& v, const Quaternion& q) {
        Quaternion qn = Quaternion(q.w, q.axis.normalize());
        Quaternion qi = qn.inverse();
        return ((qn * Quaternion(0, v)) * qi).axis;
    }

    // Member Functions

    float Vector3::angle(const Vector3& v) const {
        return angle(*this, v);
    }

    float Vector3::distance(const Vector3& v) const {
        return distance(*this, v);
    }

    float Vector3::dot(const Vector3& v) const {
        return dot(*this, v);
    }

    Vector3 Vector3::cross(const Vector3& v) const {
        return cross(*this, v);
    }

    float Vector3::magnitude() const {
        return magnitude(*this);
    }

    float Vector3::mag2() const {
        return mag2(*this);
    }

    Vector3 Vector3::normalize() const {
        return normalize(*this);
    }

    Vector3 Vector3::rotate(const Quaternion& q) const {
        return rotate(*this, q);
    }

    // Accessor operators

    float& Vector3::operator[](const int& index) {
        if (index < 0 || index >= SIZE) throw std::out_of_range("Attempting to access out of range element.");
        return buffer[index];
    }

    const float& Vector3::operator[](const int& index) const {
        if (index < 0 || index >= SIZE) throw std::out_of_range("Attempting to access out of range element.");
        return buffer[index];
    }

    // Arithmetic operators

    Vector3 Vector3::operator+(const Vector3& vec) const {
        Vector3 v = Vector3();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] + vec.buffer[i];
        }
        return v;
    }

    Vector3 Vector3::operator+(float f) const {
        Vector3 v = Vector3();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] + f;
        }
        return v;
    }

    Vector3 Vector3::operator-(const Vector3& vec) const {
        Vector3 v = Vector3();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] - vec.buffer[i];
        }
        return v;
    }

    Vector3 Vector3::operator-(float f) const {
        Vector3 v = Vector3();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] - f;
        }
        return v;
    }

    Vector3 Vector3::operator/(const Vector3& vec) const {
        Vector3 v = Vector3();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] / vec.buffer[i];
        }
        return v;
    }

    Vector3 Vector3::operator/(float f) const {
        Vector3 v = Vector3();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] / f;
        }
        return v;
    }

    Vector3 Vector3::operator*(const Vector3& vec) const {
        Vector3 v = Vector3();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] * vec.buffer[i];
        }
        return v;
    }

    Vector3 Vector3::operator*(float f) const {
        Vector3 v = Vector3();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] * f;
        }
        return v;
    }

    // Boolean operators

    bool Vector3::operator==(const Vector3& vec) const {
        bool e = true;
        for (int i = 0; i < SIZE; i++) {
            e &= (this->buffer[i] == vec.buffer[i]);
        }
        return e;
    }

    bool Vector3::operator!=(const Vector3& vec) const {
        return !(*this == vec);
    }

    // Assignment operators

    Vector3& Vector3::operator=(const Vector3& vec) {
        if (this == &vec) return *this;
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
        return *this;
    }

    Vector3& Vector3::operator=(float value) {
        for (int i = 0; i < SIZE; i++) {
            buffer[i] = value;
        }
        return *this;
    }

    // Cast operators

    Vector3::operator Vector2() const {
        return Vector2(x, y);
    }

    Vector3::operator Vector4() const {
        return Vector4(x, y, z, 0);
    }

    Vector3::operator Vector2Int() const {
        return Vector2Int((int)x, (int)y);
    }

    Vector3::operator Vector3Int() const {
        return Vector3Int((int)x, (int)y, (int)z);
    }

    Vector3::operator Vector4Int() const {
        return Vector4Int((int)x, (int)y, (int)z, 0);
    }


    Vector3::operator Matrix1x2() const {
        Matrix1x2::Type arr[1][2] = { {x, y} };
        return Matrix1x2(arr);
    }

    Vector3::operator Matrix1x3() const {
        Matrix1x3::Type arr[1][3] = { {x, y, z} };
        return Matrix1x3(arr);
    }

    Vector3::operator Matrix1x4() const {
        Matrix1x4::Type arr[1][4] = { {x, y, z, 0} };
        return Matrix1x4(arr);
    }

    Vector3::operator Matrix2x1() const {
        Matrix2x1::Type arr[2][1] = { {x}, {y} };
        return Matrix2x1(arr);
    }

    Vector3::operator Matrix3x1() const {
        Matrix3x1::Type arr[3][1] = { {x}, {y}, {z} };
        return Matrix3x1(arr);
    }

    Vector3::operator Matrix4x1() const {
        Matrix4x1::Type arr[4][1] = { {x}, {y}, {z}, {0} };
        return Matrix4x1(arr);
    }


    Vector3::operator ::std::string() const {
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

    ENGINE_API Vector3 operator+(float f, const Vector3& vector) {
        return vector + f;
    }
    ENGINE_API Vector3 operator-(float f, const Vector3& vector) {
        return Vector3(f - vector.x, f - vector.y, f - vector.z);
    }
    ENGINE_API Vector3 operator*(float f, const Vector3& vector) {
        return vector * f;
    }
    ENGINE_API Vector3 operator/(float f, const Vector3& vector) {
        return Vector3(f / vector.x, f / vector.y, f / vector.z);
    }

    // IO operators ----------------------------------------------------------

    ENGINE_API std::ostream& operator<< (std::ostream& os, const Vector3& c) {
        os << (std::string)c;
        return os;
    }

}