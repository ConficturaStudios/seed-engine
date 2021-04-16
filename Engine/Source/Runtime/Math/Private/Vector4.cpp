/**
 * Vector4.cpp
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

    const Vector4 Vector4::UP = Vector4(0, 1, 0, 0);
    const Vector4 Vector4::DOWN = Vector4(0, -1, 0, 0);
    const Vector4 Vector4::LEFT = Vector4(-1, 0, 0, 0);
    const Vector4 Vector4::RIGHT = Vector4(1, 0, 0, 0);
    const Vector4 Vector4::FORWARD = Vector4(0, 0, 1, 0);
    const Vector4 Vector4::BACKWARD = Vector4(0, 0, -1, 0);
    const Vector4 Vector4::KATA = Vector4(0, 0, 0, 1);
    const Vector4 Vector4::ANA = Vector4(0, 0, 0, -1);
    const Vector4 Vector4::ONE = Vector4(1);
    const Vector4 Vector4::ZERO = Vector4(0);

    // Constructors

    Vector4::Vector4() noexcept = default;

    Vector4::Vector4(float value) noexcept : Vector4(value, value, value, value) {};

    Vector4::Vector4(float x, float y, float z, float w) noexcept {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    Vector4::Vector4(const Vector2& xy, float z, float w) noexcept {
        this->x = xy.x;
        this->y = xy.y;
        this->z = z;
        this->w = w;
    }
    
    Vector4::Vector4(float x, const Vector2& yz, float w) noexcept {
        this->x = x;
        this->y = yz.x;
        this->z = yz.y;
        this->w = w;
    }

    Vector4::Vector4(float x, float y, const Vector2& zw) noexcept {
        this->x = x;
        this->y = y;
        this->z = zw.x;
        this->w = zw.y;
    }
    
    Vector4::Vector4(const Vector2& xy, const Vector2& zw) noexcept {
        this->x = xy.x;
        this->y = xy.y;
        this->z = zw.x;
        this->w = zw.y;
    }
    
    Vector4::Vector4(const Vector3& xyz, float w) noexcept {
        this->x = xyz.x;
        this->y = xyz.y;
        this->z = xyz.z;
        this->w = w;
    }
    
    Vector4::Vector4(float x, const Vector3& yzw) noexcept {
        this->x = x;
        this->y = yzw.x;
        this->z = yzw.y;
        this->w = yzw.z;
    }

    Vector4::Vector4(const float (&buffer)[SIZE]) {
        this->buffer[0] = buffer[0];
        this->buffer[1] = buffer[1];
        this->buffer[2] = buffer[2];
        this->buffer[3] = buffer[3];
    }

    Vector4::Vector4(const Vector4& vec) noexcept {
        this->buffer[0] = vec.buffer[0];
        this->buffer[1] = vec.buffer[1];
        this->buffer[2] = vec.buffer[2];
        this->buffer[3] = vec.buffer[3];
    }

    Vector4::Vector4(Vector4&& vec) noexcept {
        this->buffer[0] = vec.buffer[0];
        this->buffer[1] = vec.buffer[1];
        this->buffer[2] = vec.buffer[2];
        this->buffer[3] = vec.buffer[3];
    }

    // Static Functions

    float Vector4::angle(const Vector4& v0, const Vector4& v1) {
        return math::acos(dot(v0, v1)) / (magnitude(v0) * magnitude(v1));
    }

    float Vector4::distance(const Vector4& v0, const Vector4& v1) {
        return magnitude(v0 - v1);
    }

    float Vector4::dot(const Vector4& v0, const Vector4& v1) {
        float t = 0;
        for (int i = 0; i < SIZE; i++) {
            t += (v0.buffer[i]) * (v1.buffer[i]);
        }
        return t;
    }

    float Vector4::magnitude(const Vector4& v) {
        return math::sqrt(dot(v, v));
    }

    float Vector4::mag2(const Vector4& v) {
        return dot(v, v);
    }

    Vector4 Vector4::normalize(const Vector4& v) {
        return v / magnitude(v);
    }

    Vector4 Vector4::reflect(const Vector4& incident, const Vector4& normal) {
        return incident - (2 * dot(normal, incident) * normal);
    }

    Vector4 Vector4::refract(const Vector4& incident, const Vector4& normal, float eta) {
        float d = dot(normal, incident);
        float t = 1 - (eta * eta * (1 - d * d));
        if (t < 0) return Vector4();
        else return (eta * incident) - ((eta * d + math::sqrt(t)) * normal);
    }

    Vector4 Vector4::project(const Vector4& a, const Vector4& b) {
        return b * (dot(a, b) / dot(b, b));
    }

    Vector4 Vector4::ortho(const Vector4& a, const Vector4& b) {
        return a - (b * (dot(a, b) / dot(b, b)));
    }

    // Member Functions

    float Vector4::angle(const Vector4& v) const {
        return angle(*this, v);
    }

    float Vector4::distance(const Vector4& v) const {
        return distance(*this, v);
    }

    float Vector4::dot(const Vector4& v) const {
        return dot(*this, v);
    }

    float Vector4::magnitude() const {
        return magnitude(*this);
    }

    float Vector4::mag2() const {
        return mag2(*this);
    }

    Vector4 Vector4::normalize() const {
        return normalize(*this);
    }

    // Accessor operators

    float& Vector4::operator[](const int& index) {
        if (index < 0 || index >= SIZE) throw std::out_of_range("Attempting to access out of range element.");
        return buffer[index];
    }

    const float& Vector4::operator[](const int& index) const {
        if (index < 0 || index >= SIZE) throw std::out_of_range("Attempting to access out of range element.");
        return buffer[index];
    }

    // Arithmetic operators

    Vector4 Vector4::operator+(const Vector4& vec) const {
        Vector4 v = Vector4();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] + vec.buffer[i];
        }
        return v;
    }

    Vector4 Vector4::operator+(float f) const {
        Vector4 v = Vector4();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] + f;
        }
        return v;
    }

    Vector4 Vector4::operator-(const Vector4& vec) const {
        Vector4 v = Vector4();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] - vec.buffer[i];
        }
        return v;
    }

    Vector4 Vector4::operator-(float f) const {
        Vector4 v = Vector4();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] - f;
        }
        return v;
    }

    Vector4 Vector4::operator/(const Vector4& vec) const {
        Vector4 v = Vector4();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] / vec.buffer[i];
        }
        return v;
    }

    Vector4 Vector4::operator/(float f) const {
        Vector4 v = Vector4();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] / f;
        }
        return v;
    }

    Vector4 Vector4::operator*(const Vector4& vec) const {
        Vector4 v = Vector4();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] * vec.buffer[i];
        }
        return v;
    }

    Vector4 Vector4::operator*(float f) const {
        Vector4 v = Vector4();
        for (int i = 0; i < SIZE; i++) {
            v.buffer[i] = this->buffer[i] * f;
        }
        return v;
    }

    // Boolean operators

    bool Vector4::operator==(const Vector4& vec) const {
        bool e = true;
        for (int i = 0; i < SIZE; i++) {
            e &= (this->buffer[i] == vec.buffer[i]);
        }
        return e;
    }

    bool Vector4::operator!=(const Vector4& vec) const {
        return !(*this == vec);
    }

    // Assignment operators

    Vector4& Vector4::operator=(const Vector4& vec) {
        if (this == &vec) return *this;
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
        this->w = vec.w;
        return *this;
    }

    Vector4& Vector4::operator=(float value) {
        for (int i = 0; i < SIZE; i++) {
            buffer[i] = value;
        }
        return *this;
    }

    // Cast operators

    Vector4::operator Vector2() const {
        return Vector2(x, y);
    }

    Vector4::operator Vector3() const {
        return Vector3(x, y, z);
    }

    Vector4::operator Vector2Int() const {
        return Vector2Int((int)x, (int)y);
    }

    Vector4::operator Vector3Int() const {
        return Vector3Int((int)x, (int)y, (int)z);
    }

    Vector4::operator Vector4Int() const {
        return Vector4Int((int)x, (int)y, (int)z, (int)w);
    }


    Vector4::operator Matrix1x2() const {
        Matrix1x2::Type arr[1][2] = { {x, y} };
        return Matrix1x2(arr);
    }

    Vector4::operator Matrix1x3() const {
        Matrix1x3::Type arr[1][3] = { {x, y, z} };
        return Matrix1x3(arr);
    }

    Vector4::operator Matrix1x4() const {
        Matrix1x4::Type arr[1][4] = { {x, y, z, w} };
        return Matrix1x4(arr);
    }

    Vector4::operator Matrix2x1() const {
        Matrix2x1::Type arr[2][1] = { {x}, {y} };
        return Matrix2x1(arr);
    }

    Vector4::operator Matrix3x1() const {
        Matrix3x1::Type arr[3][1] = { {x}, {y}, {z} };
        return Matrix3x1(arr);
    }

    Vector4::operator Matrix4x1() const {
        Matrix4x1::Type arr[4][1] = { {x}, {y}, {z}, {w} };
        return Matrix4x1(arr);
    }


    Vector4::operator ::std::string() const {
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

    ENGINE_API Vector4 operator+(float f, const Vector4& vector) {
        return vector + f;
    }
    ENGINE_API Vector4 operator-(float f, const Vector4& vector) {
        return Vector4(f - vector.x, f - vector.y, f - vector.z, f - vector.w);
    }
    ENGINE_API Vector4 operator*(float f, const Vector4& vector) {
        return vector * f;
    }
    ENGINE_API Vector4 operator/(float f, const Vector4& vector) {
        return Vector4(f / vector.x, f / vector.y, f / vector.z, f / vector.w);
    }

    // IO operators ----------------------------------------------------------

    ENGINE_API std::ostream& operator<< (std::ostream& os, const Vector4& c) {
        os << (std::string)c;
        return os;
    }

}