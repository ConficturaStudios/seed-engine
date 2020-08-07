/**
 * Quaternion.cpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "Quaternion.hpp"
#include "Rotator.hpp"

namespace seedengine {

    // Define constants ------------------------------------------------------

    const Quaternion Quaternion::ZERO = Quaternion(1, 0, 0, 0);

    // Constructors

    Quaternion::Quaternion() {
        this->w = 1.0f;
        this->axis = Vector3(0);
    }

    Quaternion::Quaternion(const float& w, const Vector3& axis) {
        this->w = w;
        this->axis = axis;
    }

    Quaternion::Quaternion(const float& w, const float& x, const float& y, const float& z) {
        this->w = w;
        this->axis = Vector3(x, y, z);
    }

    Quaternion::~Quaternion() {

    }

    Quaternion Quaternion::fromAngleAxis(const float& angle, const Vector3& axis) {
        float h_a = angle * 0.5f;
        float s = math::sin(h_a);
        float c = math::cos(h_a);
        return Quaternion(c, axis * s);
    }

    float Quaternion::angle(const Quaternion& q) {
        return 2.0f * math::acos(q.w);
    }

    float Quaternion::magnitude(const Quaternion& q) {
        return math::sqrt(q.w * q.w + q.axis.mag2());
    }

    float Quaternion::mag2(const Quaternion& q) {
        return q.w * q.w + q.axis.mag2();
    }

    Quaternion Quaternion::normalize(const Quaternion& q) {
        return q / magnitude(q);
    }
    
    Quaternion Quaternion::conjugate(const Quaternion& q) {
        return Quaternion(q.w, -1.0f * q.axis);
    }

    Quaternion Quaternion::inverse(const Quaternion& q) {
        return conjugate(q) / mag2(q);
    }

    Rotator Quaternion::rotator(const Quaternion& q) {
        Rotator r;

        float sx_cy = 2.0f * (q.w * q.axis.x + q.axis.y * q.axis.z);
        float cx_cy = 1.0f - 2.0f * (q.axis.x * q.axis.x + q.axis.y * q.axis.y);
        r.x = math::toDegrees(math::atan2(sx_cy, cx_cy));

        float sy = 2.0f * (q.w * q.axis.y - q.axis.z * q.axis.x);
        r.y = math::toDegrees((math::abs(sy) >= 1.0f) ? math::sign(sy) * (math::PI / 2.0f) : math::asin(sy));

        float sz_cy = 2.0f * (q.w * q.axis.z + q.axis.x * q.axis.y);
        float cz_cy = 1.0f - 2.0f * (q.axis.y * q.axis.y + q.axis.z * q.axis.z);
        r.z = math::toDegrees(math::atan2(sz_cy, cz_cy));

        return r;
    }

    Matrix3 Quaternion::matrix3(const Quaternion& q) {
        float w2 = q.w * q.w;
        float x2 = q.axis.x * q.axis.x;
        float y2 = q.axis.y * q.axis.y;
        float z2 = q.axis.z * q.axis.z;

        float _2xy = 2.0f * q.axis.x * q.axis.y;
        float _2wz = 2.0f * q.w      * q.axis.z;
        float _2xz = 2.0f * q.axis.x * q.axis.z;
        float _2wy = 2.0f * q.w      * q.axis.y;
        float _2yz = 2.0f * q.axis.y * q.axis.z;
        float _2wx = 2.0f * q.w      * q.axis.x;

        return Matrix3({
            { (w2 + x2 - y2 - z2), (_2xy - _2wz)      , (_2xz + _2wy)      },
            { (_2xy + _2wz)      , (w2 - x2 + y2 - z2), (_2yz + _2wx)      },
            { (_2xz - _2wy)      , (_2yz - _2wx)      , (w2 - x2 - y2 + z2)}
        });
    }

    Matrix4 Quaternion::matrix4(const Quaternion& q) {
        float w2 = q.w * q.w;
        float x2 = q.axis.x * q.axis.x;
        float y2 = q.axis.y * q.axis.y;
        float z2 = q.axis.z * q.axis.z;

        float _2xy = 2.0f * q.axis.x * q.axis.y;
        float _2wz = 2.0f * q.w      * q.axis.z;
        float _2xz = 2.0f * q.axis.x * q.axis.z;
        float _2wy = 2.0f * q.w      * q.axis.y;
        float _2yz = 2.0f * q.axis.y * q.axis.z;
        float _2wx = 2.0f * q.w      * q.axis.x;

        return Matrix4({
            { (w2 + x2 - y2 - z2), (_2xy - _2wz)      , (_2xz + _2wy)      , 0 },
            { (_2xy + _2wz)      , (w2 - x2 + y2 - z2), (_2yz + _2wx)      , 0 },
            { (_2xz - _2wy)      , (_2yz - _2wx)      , (w2 - x2 - y2 + z2), 0 },
            { 0                  , 0                  , 0                  , 1 }
        });
    }

    float Quaternion::angle() const {
        return angle(*this);
    }

    float Quaternion::magnitude() const {
        return magnitude(*this);
    }

    float Quaternion::mag2() const {
        return mag2(*this);
    }

    Quaternion Quaternion::normalize() const {
        return normalize(*this);
    }

    Quaternion Quaternion::conjugate() const {
        return conjugate(*this);
    }

    Quaternion Quaternion::inverse() const {
        return inverse(*this);
    }

    Rotator Quaternion::rotator() const {
        return rotator(*this);
    }

    Matrix3 Quaternion::matrix3() const {
        return matrix3(*this);
    }

    Matrix4 Quaternion::matrix4() const {
        return matrix4(*this);
    }

    Quaternion Quaternion::operator+(const Quaternion& rhs) const {
        return Quaternion(w + rhs.w, axis + rhs.axis);
    }

    Quaternion Quaternion::operator-(const Quaternion& rhs) const {
        return Quaternion(w - rhs.w, axis - rhs.axis);
    }

    Quaternion Quaternion::operator/(const Quaternion& rhs) const {
        return (*this) * rhs.inverse();
    }

    Quaternion Quaternion::operator/(const float& f) const {
        return Quaternion(w / f, axis / f);
    }


    Quaternion Quaternion::operator*(const Quaternion& rhs) const {
        return Quaternion( (w * rhs.w) - axis.dot(rhs.axis),
            (w * rhs.axis) + (rhs.w * axis) + axis.cross(rhs.axis) );
    }

    Quaternion Quaternion::operator*(const float& f) const {
        return Quaternion(w * f, axis * f);
    }

    bool Quaternion::operator==(const Quaternion& rhs) const {
        return w == rhs.w && axis == rhs.axis;
    }

    bool Quaternion::operator!=(const Quaternion& rhs) const {
        return w != rhs.w && axis != rhs.axis;
    }

    Quaternion::operator std::string() const {
        std::stringstream ss("");
        ss << "[";
        ss << this->w;
        ss << " ";
        for (int i = 0; i < 3; i++) {
            ss << this->axis[i];
            if (i < 2) ss << " ";
        }
        ss << "]";
        return ss.str();
    }

    ENGINE_API Quaternion operator*(const float& f, const Quaternion& rhs) {
        return rhs * f;
    }

    ENGINE_API std::ostream& operator<< (std::ostream& os, const Quaternion& c) {
        os << (std::string)c;
        return os;
    }

}