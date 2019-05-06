#ifndef SEEDENGINE_INCLUDE_CAMERA_H_
#define SEEDENGINE_INCLUDE_CAMERA_H_

#include "Core.hpp"

namespace seedengine {

    class Transform {

    public:

        // Creates a new transform.
        // @param(glm::vec3) position: The position component of this transform.
        // @param(glm::vec3) rotation: The euler rotation component of this transform.
        // @param(glm::vec3) scale: The scale component of this transform.
        Transform(  glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3 scale    = glm::vec3(1.0f, 1.0f, 1.0f))
            : position_(position), euler_rotation_(rotation), scale_(scale) {
            rotation_ = glm::quat(rotation);
        }

        // Creates a new transform.
        // @param(glm::vec3) position: The position component of this transform.
        // @param(glm::quat) rotation: The quaternion rotation component of this transform.
        // @param(glm::vec3) scale: The scale component of this transform.
        Transform(  glm::vec3 position,
                    glm::quat rotation,
                    glm::vec3 scale    = glm::vec3(1.0f, 1.0f, 1.0f))
            : position_(position), rotation_(rotation), scale_(scale) {
            euler_rotation_ = glm::eulerAngles(rotation) * glm::pi<float>() / 180.0f;
        }

        // Gets the position of this transform.
        // @returns: The position of this transform.
        inline glm::vec3 getPosition() { return position_; }
        // Gets the euler rotation of this transform.
        // @returns: The euler rotation of this transform.
        inline glm::vec3 getEulerAngles() { return euler_rotation_; }
        // Gets the quaternion rotation of this transform.
        // @returns: The quaternion rotation of this transform.
        inline glm::quat getRotation() { return rotation_; }
        // Gets the scale of this transform.
        // @returns: The scale of this transform.
        inline glm::vec3 getScale() { return scale_; }

        // Sets the position of the transform.
        // @param(const glm::vec3&) position: The new position.
        void setPosition(const glm::vec3& position) {
            position_ = position;
            translation_ = glm::translate(glm::mat4(), position_);
            updateTransformation();
        }
        // Sets the position of the transform.
        // @param(float) x: The new x position.
        // @param(float) y: The new y position.
        // @param(float) z: The new z position.
        void setPosition(float x, float y, float z) {
            position_.x = x;
            position_.y = y;
            position_.z = z;
            translation_ = glm::translate(glm::mat4(), position_);
            updateTransformation();
        }
        // Sets the scale of the transform.
        // @param(const glm::vec3&) scale: The new scale.
        void setScale(const glm::vec3& scale) {
            scale_ = scale;
            scale_matrix_ = glm::scale(glm::mat4(), scale);
            updateTransformation();
        }
        // Sets the scale of the transform.
        // @param(float) x: The new x scale.
        // @param(float) y: The new y scale.
        // @param(float) z: The new z scale.
        void setScale(float x, float y, float z) {
            scale_.x = x;
            scale_.y = y;
            scale_.z = z;
            scale_matrix_ = glm::scale(glm::mat4(), scale_);
            updateTransformation();
        }
        // Sets the rotation of the transform.
        // @param(const glm::vec3&) rotation: The new rotation.
        void setRotation(const glm::vec3& rotation) {
            euler_rotation_ = rotation;
            rotation_ = glm::quat(rotation);
            rotation_matrix_ = glm::toMat4(rotation_);
            updateTransformation();
        }
        // Sets the rotation of the transform.
        // @param(float) x: The new x rotation.
        // @param(float) y: The new y rotation.
        // @param(float) z: The new z rotation.
        void setRotation(float x, float y, float z) {
            euler_rotation_.x = x;
            euler_rotation_.y = y;
            euler_rotation_.z = z;
            rotation_ = glm::quat(euler_rotation_);
            rotation_matrix_ = glm::toMat4(rotation_);
            updateTransformation();
        }
        // Sets the rotation of the transform by quaternion.
        // @param(const glm::quat&) rotation: The new rotation.
        void setRotation(const glm::quat& rotation) {
            rotation_ = rotation;
            euler_rotation_ = glm::eulerAngles(rotation) * glm::pi<float>() / 180.0f;
            rotation_matrix_ = glm::toMat4(rotation_);
            updateTransformation();
        }
        // Sets the rotation of the transform by quaternion.
        // @param(float) w: The new w rotation.
        // @param(float) x: The new x rotation.
        // @param(float) y: The new y rotation.
        // @param(float) z: The new z rotation.
        void setRotation(float w, float x, float y, float z) {
            rotation_.w = w;
            rotation_.x = x;
            rotation_.y = y;
            rotation_.z = z;
            euler_rotation_ = glm::eulerAngles(rotation_) * glm::pi<float>() / 180.0f;
            rotation_matrix_ = glm::toMat4(rotation_);
            updateTransformation();
        }

        // Gets the transformation/model matrix from this transform.
        // @returns: The transformation/model matrix from this transform.
        inline glm::mat4 getTransformationMatrix() { return transformation_matrix_; }

        // Gets the forward vector from this transform.
        // @returns: The forward vector from this transform.
        inline glm::vec3 getForwardVector() {
            return glm::normalize(glm::vec3(glm::inverse(transformation_matrix_)[2]));
        }
        // Gets the up vector from this transform.
        // @returns: The up vector from this transform.
        inline glm::vec3 getUpVector() {
            return glm::normalize(glm::vec3(glm::inverse(transformation_matrix_)[1]));
        }
        // Gets the right vector from this transform.
        // @returns: The right vector from this transform.
        inline glm::vec3 getRightVector() {
            return glm::normalize(glm::vec3(glm::inverse(transformation_matrix_)[0]));
        }

        //TODO: Provide additional transform functionality such as translate, scale, rotate, etc.
        //TODO: Create operator overloads for the transform class.
        //TODO: Unit test transform class.
        //TODO: Create wrapper classes for GLM vectors, matrices, and quaternions

    private:

        // The position vector.
        glm::vec3 position_;
        // The euler rotation.
        glm::vec3 euler_rotation_;
        // The quaternion rotation.
        glm::quat rotation_;
        // The scale vector.
        glm::vec3 scale_;

        // The translation matrix.
        glm::mat4 translation_;
        // The rotation matrix.
        glm::mat4 rotation_matrix_;
        // The scale matrix.
        glm::mat4 scale_matrix_;
        // The composite transformation/model matrix.
        glm::mat4 transformation_matrix_;

        // Updates the transformation matrix.
        void updateTransformation() {
            transformation_matrix_ = translation_ * rotation_matrix_ * scale_matrix_ * glm::mat4();
        }

    };

}

#endif