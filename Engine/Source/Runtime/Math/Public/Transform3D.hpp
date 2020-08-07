/**
 * Transform3D.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_MATH_TRANSFORM3D_H_
#define SEEDENGINE_INCLUDE_RUNTIME_MATH_TRANSFORM3D_H_

#include "MathAPI.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include "Matrix.hpp"
#include "Vector3.hpp"
#include "Rotator.hpp"
#include "Quaternion.hpp"
#include "StandardFunctions.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API Transform3D final {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Transform3D objects.
             * @details Constructs a new Transform3D with default initialization for all members.
             */
            Transform3D();

            /**
             * @brief Construct a new Transform 3D with specified values.
             * 
             * @param position The position of this transform in local space.
             * @param rotation The rotation of this transform in local space.
             * @param scale The scale of this transform in local space.
             */
            Transform3D(const Vector3& position, const Quaternion& rotation, const Vector3& scale);

            /**
             * @brief Construct a new Transform 3D with specified values.
             * 
             * @param position The position of this transform in local space.
             * @param rotation The euler rotation of this transform in local space.
             * @param scale The scale of this transform in local space.
             */
            Transform3D(const Vector3& position, const Rotator& rotation, const Vector3& scale);

            /**
             * @brief The copy constructor for Transform3D objects.
             * @details Constructs a new Transform3D by copying an existing Transform3D.
             */
            Transform3D(const Transform3D& ref) = default;
            
            /**
             * @brief The move constructor for Transform3D objects.
             * @details Constructs a new Transform3D by moving the data of a Transform3D into this object.
             */
            Transform3D(Transform3D&& ref) = default;

            /**
             * @brief The destructor for Transform3D objects.
             * @details Called when an instance of Transform3D is deleted.
             */
            ~Transform3D();

        // Member Access Functions

            /**
             * @brief Gets the position of this transform in local space.
             * 
             * @return Vector3 The position of this transform in local space.
             */
            Vector3 getPosition() const;
            /**
             * @brief Gets the rotation of this transform in local space.
             * 
             * @return Quaternion The rotation of this transform in local space.
             */
            Quaternion getRotation() const;
            /**
             * @brief Gets the euler angles/rotator of this transform in local space.
             * 
             * @return Rotator The euler angles/rotator of this transform in local space.
             */
            Rotator getEulerRotation() const;
            /**
             * @brief Gets the scale of this transform in local space.
             * 
             * @return Vector3 The scale of this transform in local space.
             */
            Vector3 getScale() const;

            /**
             * @brief Sets the position of this transform in local space.
             * 
             * @param position The new position of this transform in local space.
             */
            void setPosition(const Vector3& position);
            /**
             * @brief Sets the position of this transform in local space.
             * 
             * @param x The new x position of this transform in local space.
             * @param y The new y position of this transform in local space.
             * @param z The new z position of this transform in local space.
             */
            void setPosition(const float& x, const float& y, const float& z);

            /**
             * @brief Sets the quaternion rotation of this transform in local space.
             * 
             * @param rotation The quaternion rotation of this transform in local space.
             */
            void setRotation(const Quaternion& rotation);
            /**
             * @brief Sets the quaternion rotation of this transform in local space.
             * 
             * @param w The new quaternion w of this transform in local space.
             * @param x The new quaternion x of this transform in local space.
             * @param y The new quaternion y of this transform in local space.
             * @param z The new quaternion z of this transform in local space.
             */
            void setRotation(const float& w, const float& x, const float& y, const float& z);

            /**
             * @brief Sets the quaternion rotation of this transform in local space.
             * 
             * @param angle The number of radians to rotate around the specified axis.
             * @param axis The axis about which to rotate.
             */
            void setRotation(const float& angle, const Vector3& axis);

            /**
             * @brief Sets the euler rotation of this transform in local space.
             * 
             * @param rotation The new euler angle rotation of this transform in local space.
             */
            void setEulerRotation(const Rotator& rotation);
            /**
             * @brief Sets the euler rotation of this transform in local space.
             * 
             * @param x The new x rotation of this transform in local space.
             * @param y The new y rotation of this transform in local space.
             * @param z The new z rotation of this transform in local space.
             */
            void setEulerRotation(const float& x, const float& y, const float& z);

            /**
             * @brief Sets the scale of this transform in local space.
             * 
             * @param scale The new scale of this transform in local space.
             */
            void setScale(const Vector3& scale);
            /**
             * @brief Sets the scale of this transform in local space.
             * 
             * @param x The new x scale of this transform in local space.
             * @param y The new y scale of this transform in local space.
             * @param z The new z scale of this transform in local space.
             */
            void setScale(const float& x, const float& y, const float& z);

        // Functions

            /**
             * @brief Translates this transform by the given amount.
             * 
             * @param offset The local space offset to apply to this transform.
             */
            void translate(const Vector3& offset);
            /**
             * @brief Translates this transform by the given amount.
             * 
             * @param x_offset The local space x offset to apply to this transform.
             * @param y_offset The local space y offset to apply to this transform.
             * @param z_offset The local space z offset to apply to this transform.
             */
            void translate(const float& x_offset, const float& y_offset, const float& z_offset);

            /**
             * @brief Rotates this transform by the given amount.
             * 
             * @param rotation The quaternion rotation to apply to this transform.
             */
            void rotate(const Quaternion& rotation);
            /**
             * @brief Rotates this transform by the given amount about the given axis.
             * 
             * @param angle The number of radians to rotate around the specified axis.
             * @param axis The axis about which to rotate.
             */
            void rotate(const float& angle, const Vector3& axis);
            /**
             * @brief Rotates this transform by the given amount.
             * 
             * @param rotation The euler rotation to apply to this transform.
             */
            void rotate(const Rotator& rotation);
            /**
             * @brief Rotates this transform by the given amount.
             * 
             * @param x_rotation The x euler rotation to apply to this transform.
             * @param y_rotation The y euler rotation to apply to this transform.
             * @param z_rotation The z euler rotation to apply to this transform.
             */
            void rotate(const float& x_rotation, const float& y_rotation, const float& z_rotation);

            /**
             * @brief Scales this transform by the given amount.
             * 
             * @param scale The amount to scale this transform.
             */
            void scale(const Vector3& scale);
            /**
             * @brief Scales this transform by the given amount.
             * 
             * @param x_scale The amount to scale this transform along the x axis.
             * @param y_scale The amount to scale this transform along the y axis.
             * @param z_scale The amount to scale this transform along the z axis.
             */
            void scale(const float& x_scale, const float& y_scale, const float& z_scale);
            /**
             * @brief Scales this transform by the given amount.
             * 
             * @param factor The amount to scale this transform by in all directions.
             */
            void scale(const float& factor);


            /**
             * @brief Rotates this transform to look in the specified direction.
             * 
             * @param direction The direction to look.
             * @param up_vector The up vector to refer to during the rotation.
             */
            void lookAt(const Vector3& direction, const Vector3& up_vector);


            /**
             * @brief Gets the transformation/model matrix from this transform.
             * 
             * @return Matrix4 The transformation/model matrix from this transform.
             */
            Matrix4 getTransformationMatrix();

            /**
             * @brief Gets the local forward vector from this transform.
             * 
             * @return Vector3 The local forward vector from this transform.
             */
            Vector3 getForwardVector();

            /**
             * @brief Gets the local up vector from this transform.
             * 
             * @return Vector3 The local up vector from this transform.
             */
            Vector3 getUpVector();

            /**
             * @brief Gets the local right vector from this transform.
             * 
             * @return Vector3 The local right vector from this transform.
             */
            Vector3 getRightVector();

        // Arithmatic Operators

        // Comparison Operators

            bool operator==(const Transform3D& rhs) const;

            bool operator!=(const Transform3D& rhs) const;

        // Assignment Operators

            /**
             * @brief The copy assignment operator for Transform3D objects.
             * @details Reassigns the value of this object by copying the data of a Transform3D into this object.
             */
            Transform3D& operator=(const Transform3D& ref) = default;

            /**
             * @brief The move assignment operator for Transform3D objects.
             * @details Reassigns the value of this object by moving the data of a Transform3D into this object.
             */
            Transform3D& operator=(Transform3D&& ref) = default;

        // Cast Operators

            operator std::string() const;

        // IO Operators

            friend ENGINE_API std::ostream& operator<<(std::ostream& os, const Transform3D& rhs);

        private:

            /**
             * @brief Gets set to true whenever the underlying values of this transform are
             *        changed. Used to signal an update to the transformation matrix.
             */
            bool m_has_changed;

            /** The position of this transform in local space. */
            Vector3 m_position;
            /** The rotation of this transform in local space. */
            Quaternion m_rotation;
            /** The scale of this transform in local space. */
            Vector3 m_scale;

            /** The cached transformation matrix for this transform. */
            Matrix4 m_transform_mat;

            /**
             * @brief Updates and regenerates the cached transformation matrix.
             * 
             */
            void updateTransformMat();


    };

    // Global IO Operators

    ENGINE_API std::ostream& operator<<(std::ostream& os, const Transform3D& rhs);

}

#endif