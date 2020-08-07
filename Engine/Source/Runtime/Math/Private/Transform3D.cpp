/**
 * Transform3D.cpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "Transform3D.hpp"

namespace seedengine {

    Transform3D::Transform3D() {
        this->m_position = Vector3::ZERO;
        this->m_rotation = Quaternion::ZERO;
        this->m_scale = Vector3::ONE;
        this->m_has_changed = false;
        updateTransformMat();
    }

    Transform3D::Transform3D(const Vector3& position,
                                const Quaternion& rotation = Quaternion::ZERO,
                                const Vector3& scale = Vector3::ONE) {
        this->m_position = position;
        this->m_rotation = rotation;
        this->m_scale = scale;
        this->m_has_changed = false;
        updateTransformMat();
    }

    Transform3D::Transform3D(const Vector3& position,
                                const Rotator& rotation,
                                const Vector3& scale = Vector3::ONE) {
        this->m_position = position;
        this->m_rotation = (Quaternion)rotation;
        this->m_scale = scale;
        this->m_has_changed = false;
        updateTransformMat();
    }

    Transform3D::~Transform3D() {
        
    }

// Member Access Functions

    Vector3 Transform3D::getPosition() const {
        return m_position;
    }
    
    Quaternion Transform3D::getRotation() const {
        return m_rotation;
    }
    
    Rotator Transform3D::getEulerRotation() const {
        return m_rotation.rotator();
    }
    
    Vector3 Transform3D::getScale() const {
        return m_scale;
    }

    
    void Transform3D::setPosition(const Vector3& position) {
        this->m_position = position;
        m_has_changed = true;
    }
    
    void Transform3D::setPosition(const float& x, const float& y, const float& z) {
        this->m_position = Vector3(x, y, z);
        m_has_changed = true;
    }

    
    void Transform3D::setRotation(const Quaternion& rotation) {
        this->m_rotation = rotation;
        m_has_changed = true;
    }
    
    void Transform3D::setRotation(const float& w, const float& x, const float& y, const float& z) {
        this->m_rotation = Quaternion(w, x, y, z);
        m_has_changed = true;
    }

    void Transform3D::setRotation(const float& angle, const Vector3& axis) {
        this->m_rotation = Quaternion::fromAngleAxis(angle, axis);
        m_has_changed = true;
    }

    
    void Transform3D::setEulerRotation(const Rotator& rotation) {
        this->m_rotation = (Quaternion)rotation;
        m_has_changed = true;
    }
    
    void Transform3D::setEulerRotation(const float& x, const float& y, const float& z) {
        this->m_rotation = (Quaternion)Rotator({x, y, z});
        m_has_changed = true;
    }

    
    void Transform3D::setScale(const Vector3& scale) {
        this->m_scale = scale;
        m_has_changed = true;
    }
    
    void Transform3D::setScale(const float& x, const float& y, const float& z) {
        this->m_scale = Vector3(x, y, z);
        m_has_changed = true;
    }

// Functions

    
    void Transform3D::translate(const Vector3& offset) {
        this->m_position = this->m_position + offset;
        m_has_changed = true;
    }
    
    void Transform3D::translate(const float& x_offset, const float& y_offset, const float& z_offset) {
        this->m_position = this->m_position + Vector3(x_offset, y_offset, z_offset);
        m_has_changed = true;
    }

    
    void Transform3D::rotate(const Quaternion& rotation) {
        this->m_rotation = rotation * this->m_rotation;
        m_has_changed = true;
    }

    void Transform3D::rotate(const float& angle, const Vector3& axis) {
        this->m_rotation = Quaternion::fromAngleAxis(angle, axis) * this->m_rotation;
        m_has_changed = true;
    }
    
    void Transform3D::rotate(const Rotator& rotation) {
        this->m_rotation = (Quaternion)rotation * this->m_rotation;
        m_has_changed = true;
    }
    
    void Transform3D::rotate(const float& x_rotation, const float& y_rotation, const float& z_rotation) {
        this->m_rotation = (Quaternion)Rotator({x_rotation, y_rotation, z_rotation}) * this->m_rotation;
        m_has_changed = true;
    }

    
    void Transform3D::scale(const Vector3& scale) {
        this->m_scale = this->m_scale * scale;
        m_has_changed = true;
    }
    
    void Transform3D::scale(const float& x_scale, const float& y_scale, const float& z_scale) {
        this->m_scale = this->m_scale * Vector3(x_scale, y_scale, z_scale);
        m_has_changed = true;
    }
    
    void Transform3D::scale(const float& factor) {
        this->m_scale = this->m_scale * factor;
        m_has_changed = true;
    }

    void Transform3D::lookAt(const Vector3& direction, const Vector3& up_vector) {
        Vector3 dir_n = direction.normalize();
        Vector3 forward = getForwardVector();
        Vector3 axis = forward.cross(dir_n);
        if (axis.mag2() == 0) axis = up_vector.normalize();
        float angle = math::acos(forward.dot(dir_n));
        this->rotate(angle, axis);
    }


    Matrix4 Transform3D::getTransformationMatrix() {
        if (m_has_changed) updateTransformMat();
        return m_transform_mat;
    }

    Vector3 Transform3D::getForwardVector() {
        static std::size_t i = 0; // (1,0,0) x
        if (m_has_changed) updateTransformMat();
        return Vector3(m_transform_mat(i, 0), m_transform_mat(i, 1), m_transform_mat(i, 2)).normalize();
    }

    Vector3 Transform3D::getUpVector() {
        static std::size_t i = 1; // (0,1,0) y
        if (m_has_changed) updateTransformMat();
        return Vector3(m_transform_mat(i, 0), m_transform_mat(i, 1), m_transform_mat(i, 2)).normalize();
    }

    Vector3 Transform3D::getRightVector() {
        static std::size_t i = 2; // (0,0,1) z
        if (m_has_changed) updateTransformMat();
        return Vector3(m_transform_mat(i, 0), m_transform_mat(i, 1), m_transform_mat(i, 2)).normalize();
    }

// Comparison Operators

    bool Transform3D::operator==(const Transform3D& rhs) const {
        return m_position == rhs.m_position && m_rotation == rhs.m_rotation && m_scale == rhs.m_scale;
    }

    bool Transform3D::operator!=(const Transform3D& rhs) const {
        return m_position != rhs.m_position || m_rotation != rhs.m_rotation || m_scale != rhs.m_scale;
    }

// Cast Operators

    Transform3D::operator std::string() const {
        std::stringstream ss("");
        ss << "[ ";
        ss << (std::string)m_position;
        ss << ", ";
        ss << (std::string)m_rotation;
        ss << ", ";
        ss << (std::string)m_scale;
        ss << " ]";
        return ss.str();
    }

// Private Functions

    void Transform3D::updateTransformMat() {
        Matrix4 translation_mat = Matrix4({
            { 1, 0, 0, m_position.x },
            { 0, 1, 0, m_position.y },
            { 0, 0, 1, m_position.z },
            { 0, 0, 0, 1            }
        });
        Matrix4 rotation_mat = m_rotation.matrix4();
        Matrix4 scale_mat = Matrix4({
            { m_scale.x, 0        , 0        , 0},
            { 0        , m_scale.y, 0        , 0 },
            { 0        , 0        , m_scale.z, 0 },
            { 0        , 0        , 0        , 1 }
        });

        this->m_transform_mat = translation_mat * rotation_mat * scale_mat;

        m_has_changed = false;
    }

    // Global IO Operators

    ENGINE_API std::ostream& operator<<(std::ostream& os, const Transform3D& rhs) {
        os << (std::string)rhs;
        return os;
    }

}