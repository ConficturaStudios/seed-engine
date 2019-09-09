#ifndef SEEDENGINE_INCLUDE_TRANSFORM_H_
#define SEEDENGINE_INCLUDE_TRANSFORM_H_

#include "Core.hpp"

namespace seedengine {

    class Transform {

    public:

        //TODO: Switch from glm classes to custom classes

        /**
         * @brief Creates a new transform.
         * 
         * @param position The position component of this transform.
         * @param rotation The euler rotation component of this transform.
         * @param scale The scale component of this transform.
         */
        Transform(  const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
                    const glm::vec3& rotation = glm::vec3(0.0f, 0.0f, 0.0f),
                    const glm::vec3& scale    = glm::vec3(1.0f, 1.0f, 1.0f));

        /**
         * @brief Creates a new transform.
         * 
         * @param position The position component of this transform.
         * @param rotation The quaternion rotation component of this transform.
         * @param scale The scale component of this transform.
         */
        Transform(  const glm::vec3& position,
                    const glm::quat& rotation,
                    const glm::vec3& scale    = glm::vec3(1.0f, 1.0f, 1.0f));

        /**
         * @brief Gets the position of this transform.
         * 
         * @return glm::vec3 The position of this transform.
         */
        inline glm::vec3 getPosition() const { return position_; }
        /**
         * @brief Gets the euler rotation of this transform.
         * 
         * @return glm::vec3 The euler rotation of this transform.
         */
        inline glm::vec3 getEulerAngles() const { return euler_rotation_; }
        /**
         * @brief Gets the quaternion rotation of this transform.
         * 
         * @return glm::quat The quaternion rotation of this transform.
         */
        inline glm::quat getRotation() const { return rotation_; }
        /**
         * @brief Gets the scale of this transform.
         * 
         * @return glm::vec3 The scale of this transform.
         */
        inline glm::vec3 getScale() const { return scale_; }

        /**
         * @brief Sets the position of the transform.
         * 
         * @param position The new position.
         */
        void setPosition(const glm::vec3& position) {
            position_ = position;
            translation_ = glm::translate(glm::mat4(), position_);
            updateTransformation();
        }
        /**
         * @brief Sets the position of the transform.
         * 
         * @param x The new x position.
         * @param y The new y position.
         * @param z The new z position.
         */
        void setPosition(float x, float y, float z) {
            position_.x = x;
            position_.y = y;
            position_.z = z;
            translation_ = glm::translate(glm::mat4(1.0f), position_);
            updateTransformation();
        }
        /**
         * @brief Sets the scale of the transform.
         * 
         * @param scale The new scale.
         */
        void setScale(const glm::vec3& scale) {
            scale_ = scale;
            scale_matrix_ = glm::scale(glm::mat4(1.0f), scale);
            updateTransformation();
        }
        /**
         * @brief Sets the scale of the transform.
         * 
         * @param x The new x scale.
         * @param y The new y scale.
         * @param z The new z scale.
         */
        void setScale(float x, float y, float z) {
            scale_.x = x;
            scale_.y = y;
            scale_.z = z;
            scale_matrix_ = glm::scale(glm::mat4(1.0f), scale_);
            updateTransformation();
        }
        /**
         * @brief Sets the rotation of the transform.
         * 
         * @param rotation The new rotation.
         */
        void setRotation(const glm::vec3& rotation) {
            euler_rotation_ = rotation;
            rotation_ = glm::quat(rotation * glm::pi<float>() / 180.0f);
            rotation_matrix_ = glm::toMat4(rotation_);
            updateTransformation();
        }
        /**
         * @brief Sets the rotation of the transform.
         * 
         * @param x The new x rotation.
         * @param y The new y rotation.
         * @param z The new z rotation.
         */
        void setRotation(float x, float y, float z) {
            euler_rotation_.x = x;
            euler_rotation_.y = y;
            euler_rotation_.z = z;
            rotation_ = glm::quat(euler_rotation_ * glm::pi<float>() / 180.0f);
            rotation_matrix_ = glm::toMat4(rotation_);
            updateTransformation();
        }
        /**
         * @brief Sets the rotation of the transform by quaternion.
         * 
         * @param rotation The new rotation.
         */
        void setRotation(const glm::quat& rotation) {
            rotation_ = rotation;
            euler_rotation_ = glm::eulerAngles(rotation) / glm::pi<float>() * 180.0f;
            rotation_matrix_ = glm::toMat4(rotation_);
            updateTransformation();
        }
        /**
         * @brief Set the Rotation object
         * 
         * @param w The new w rotation.
         * @param x The new x rotation.
         * @param y The new y rotation.
         * @param z The new z rotation.
         */
        void setRotation(float w, float x, float y, float z) {
            rotation_.w = w;
            rotation_.x = x;
            rotation_.y = y;
            rotation_.z = z;
            euler_rotation_ = glm::eulerAngles(rotation_) / glm::pi<float>() * 180.0f;
            rotation_matrix_ = glm::toMat4(rotation_);
            updateTransformation();
        }

        /**
         * @brief Gets the transformation/model matrix from this transform.
         * 
         * @return glm::mat4 The transformation/model matrix from this transform.
         */
        inline glm::mat4 getTransformationMatrix() const { return transformation_matrix_; }

        /**
         * @brief Gets the local forward vector from this transform.
         * 
         * @return glm::vec3 The local forward vector from this transform.
         */
        inline glm::vec3 getForwardVector() const {
            return glm::normalize(glm::vec3(glm::inverse(transformation_matrix_)[2]));
        }
        /**
         * @brief Gets the local up vector from this transform.
         * 
         * @return glm::vec3 The local up vector from this transform.
         */
        inline glm::vec3 getUpVector() const {
            return glm::normalize(glm::vec3(glm::inverse(transformation_matrix_)[1]));
        }
        /**
         * @brief Gets the local right vector from this transform.
         * 
         * @return glm::vec3 The local right vector from this transform.
         */
        inline glm::vec3 getRightVector() const {
            return glm::normalize(glm::vec3(glm::inverse(transformation_matrix_)[0]));
        }

        //TODO: Provide additional transform functionality such as translate, scale, rotate, etc.
        //TODO: Create operator overloads for the transform class.
        //TODO: Unit test transform class.
        //TODO: Create wrapper classes for GLM vectors, matrices, and quaternions

    private:

        /** The position vector. */
        glm::vec3 position_;
        /** The euler rotation. */
        glm::vec3 euler_rotation_;
        /** The quaternion rotation. */
        glm::quat rotation_;
        /** The scale vector. */
        glm::vec3 scale_;

        /** The translation matrix. */
        glm::mat4 translation_;
        /** The rotation matrix. */
        glm::mat4 rotation_matrix_;
        /** The scale matrix. */
        glm::mat4 scale_matrix_;
        /** The composite transformation/model matrix. */
        glm::mat4 transformation_matrix_;

        /** Updates the transformation matrix. */
        void updateTransformation() {
            transformation_matrix_ = translation_ * rotation_matrix_ * scale_matrix_ * glm::mat4(1.0f);
        }

    };

}

#endif