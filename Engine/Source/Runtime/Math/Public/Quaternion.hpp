/**
 * Quaternion.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_MATH_QUATERNION_H_
#define SEEDENGINE_INCLUDE_RUNTIME_MATH_QUATERNION_H_

#include "MathAPI.hpp"
#include <string>
#include <sstream>
#include "Vector3.hpp"
#include "Matrix.hpp"
#include "StandardFunctions.hpp"

namespace seedengine {

    struct Rotator;

    /**
     * @brief A quaternion object for storing 3D rotation information.
     * @details A quaternion which stores an axis (xyz) and w value for 3D rotation.
     * 
     * @see Vector3
     * @see Matrix4
     */
    class ENGINE_API Quaternion final {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Quaternion objects. Initializes to [1 0 0 0].
             * @details Constructs a new Quaternion as a quaternion with no rotation.
             */
            Quaternion();

            /**
             * @brief Construct a new Quaternion object using the passed values.
             * 
             * @param w The rotation amount, equal to cos(angle / 2).
             * @param axis The axis of rotation * sin(angle / 2).
             */
            Quaternion(const float& w, const Vector3& axis);

            /**
             * @brief Construct a new Quaternion object using the passed values.
             * 
             * @param w The rotation amount, equal to cos(angle / 2).
             * @param x The x component of axis of rotation * sin(angle / 2).
             * @param y The y component of axis of rotation * sin(angle / 2).
             * @param z The z component of axis of rotation * sin(angle / 2).
             */
            Quaternion(const float& w, const float& x, const float& y, const float& z);

            /**
             * @brief The copy constructor for Quaternion objects.
             * @details Constructs a new Quaternion by copying an existing Quaternion.
             */
            Quaternion(const Quaternion& ref) = default;
            
            /**
             * @brief The move constructor for Quaternion objects.
             * @details Constructs a new Quaternion by moving the data of a Quaternion into this object.
             */
            Quaternion(Quaternion&& ref) = default;

            /**
             * @brief The destructor for Quaternion objects.
             * @details Called when an instance of Quaternion is deleted.
             */
            ~Quaternion();

        // Constants

            /** The zero rotation quaternion (1, 0, 0, 0). */
            static const Quaternion ZERO;

        // Properties

            /** The amount of roatation about the axis. This is equal to cos(angle / 2). */
            float w;
            /** The axis about which the rotation occurs. */
            Vector3 axis;

        // Static Functions

            /**
             * @brief Creates a new quaternion from an angle and an axis.
             * 
             * @param angle The angle in radians to rotate about the axis.
             * @param axis The axis about which to rotate.
             * @return Quaternion The created quaternion.
             */
            static Quaternion fromAngleAxis(const float& angle, const Vector3& axis);

            /**
             * @brief Gets the angle in radians that the passed quaternion rotates by.
             *
             * @param q The quaternion to evaluate.
             * @return float The angle in radians rotated by this quaternion.
             */
            static float angle(const Quaternion& q);
        
            /**
             * @brief Returns the magnitude (norm/length) of the passed quaternion.
             *
             * @param q The quaternion to evaluate.
             * @return float The magnitude (norm/length) of the quaternion.
             */
            static float magnitude(const Quaternion& q);

            /**
             * @brief Returns the squared magnitude (norm/length) of the passed quaternion.
             * @details Returns the squared magnitude (norm/length) of the passed quaternion.
             *          This method is faster than norm().
             *
             * @param q The quaternion to evaluate.
             * @return float The squared magnitude (norm/length) of the quaternion.
             */
            static float mag2(const Quaternion& q);

            /**
             * @brief Returns the normalized version of the passed quaternion.
             * @details This function calculates the unit quaternion of magnitude 1 that points in the
             *          same direction as the specified quaternion.
             *
             * @param q The quaternion to normalize.
             * @return Quaternion The normalized quaternion.
             */
            static Quaternion normalize(const Quaternion& q);
            
            /**
             * @brief Gets the conjugate of the passed quaternion.
             * @details Gets the conjugate of the passed quaternion, which is equal to
             *          the passed quaternion with its axis multiplied by -1.
             * 
             * @param q The quaternion to normalize.
             * @return Quaternion The conjugate of this quaternion.
             */
            static Quaternion conjugate(const Quaternion& q);

            /**
             * @brief Gets the inverse of the passed quaternion.
             * @details Gets the inverse of the passed quaternion, which is equal to
             *          the conjugate / the magnitude squared of the passed quaternion.
             * 
             * @param q The quaternion to normalize.
             * @return Quaternion The inverse of this quaternion.
             */
            static Quaternion inverse(const Quaternion& q);

            /**
             * @brief Get the rotator/euler angle representation for the passed quaternion.
             * 
             * @param q The quaternion to convert.
             * @return Rotator The euler angle representation of the passed quaternion.
             */
            static Rotator rotator(const Quaternion& q);

            /**
             * @brief Gets the rotation matrix (3x3) generated by the passed quaternion.
             * 
             * @param q The quaternion to use.
             * @return Matrix3 The equivalent rotation matrix to q.
             */
            static Matrix3 matrix3(const Quaternion& q);

            /**
             * @brief Gets the rotation matrix (4x4) generated by the passed quaternion.
             * 
             * @param q The quaternion to use.
             * @return Matrix4 The equivalent rotation matrix to q.
             */
            static Matrix4 matrix4(const Quaternion& q);

        // Member Functions

            /**
             * @brief Gets the angle in radians that this quaternion rotates by.
             *
             * @return float The angle in radians rotated by this quaternion.
             */
            float angle() const;

            /**
             * @brief Gets the magnitude (norm/length) of this quaternion.
             *
             * @return float The magnitude (norm/length) of this quaternion.
             */
            float magnitude() const;

            /**
             * @brief Gets the squared magnitude (norm/length) of this quaternion.
             *
             * @return float The squared magnitude (norm/length) of this quaternion.
             */
            float mag2() const;

            /**
             * @brief Gets the normalized version of this quaternion.
             * @details This function calculates the unit quaternion of magnitude 1 that points in the
             *          same direction as this quaternion.
             *
             * @return Quaternion The normalized version of this quaternion.
             */
            Quaternion normalize() const;

            /**
             * @brief Gets the conjugate of this quaternion.
             * 
             * @return Quaternion The conjugate of this quaternion.
             */
            Quaternion conjugate() const;

            /**
             * @brief Gets the inverse of this quaternion.
             * 
             * @return Quaternion The inverse of this quaternion.
             */
            Quaternion inverse() const;

            /**
             * @brief Get the rotator/euler angle representation for this quaternion.
             * 
             * @return Rotator The euler angle representation of the passed quaternion.
             */
            Rotator rotator() const;

            /**
             * @brief Gets the rotation matrix (3x3) generated by this quaternion.
             * 
             * @return Matrix3 The equivalent rotation matrix to this quaternion.
             */
            Matrix3 matrix3() const;

            /**
             * @brief Gets the rotation matrix (4x4) generated by this quaternion.
             * 
             * @return Matrix4 The equivalent rotation matrix to this quaternion.
             */
            Matrix4 matrix4() const;

        // Arithmatic operators

            Quaternion operator+(const Quaternion& rhs) const;

            Quaternion operator-(const Quaternion& rhs) const;

            Quaternion operator/(const Quaternion& rhs) const;
            Quaternion operator/(const float& f) const;

            Quaternion operator*(const Quaternion& rhs) const;
            Quaternion operator*(const float& f) const;
            friend ENGINE_API Quaternion operator*(const float& f, const Quaternion& rhs);

        // Boolean operators

            bool operator==(const Quaternion& rhs) const;

            bool operator!=(const Quaternion& rhs) const;

        // Assignment operators

            /**
             * @brief The copy assignment operator for Quaternion objects.
             * @details Reassigns the value of this object by copying the data of a Quaternion into this object.
             */
            Quaternion& operator=(const Quaternion& ref) = default;

            /**
             * @brief The move assignment operator for Quaternion objects.
             * @details Reassigns the value of this object by moving the data of a Quaternion into this object.
             */
            Quaternion& operator=(Quaternion&& ref) = default;

        // Cast operators

            operator std::string() const;

        // IO operators

            friend ENGINE_API std::ostream& operator<< (std::ostream& os, const Quaternion& c);

    };

    // Global arithmatic operators

    ENGINE_API Quaternion operator*(const float& f, const Quaternion& rhs);

    // Global IO operators

    ENGINE_API std::ostream& operator<< (std::ostream& os, const Quaternion& c);

}

#endif