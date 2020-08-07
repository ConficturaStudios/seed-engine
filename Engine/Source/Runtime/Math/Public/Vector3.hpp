/**
 * Vector3.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_MATH_VECTOR3_H_
#define SEEDENGINE_INCLUDE_RUNTIME_MATH_VECTOR3_H_

#include "MathAPI.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstdarg>
#include <cstring>
#include <utility>
#include "Matrix.hpp"
#include "StandardFunctions.hpp"

namespace seedengine {

    class Vector2;
    class Vector3;
    class Vector4;
    class Vector2Int;
    class Vector3Int;
    class Vector4Int;

    class Quaternion;

    /**
     * @brief A 3 Dimentsional vector with components x, y, and z.
     *
     * @see #Vector2
     * @see #Vector4
     * @see #Vector2Int
     * @see #Vector3Int
     * @see #Vector4Int
     */
    class ENGINE_API Vector3 final {

        protected:

            /** The number of components this vector type has. */
            static constexpr const int SIZE = 3;

        public:

            // Constructors

            /**
             * @brief Constructs a new Vector3 initialized to the zero vector.
             * @details Constructs a new Vector3 with x, y, and z initialized to a value of 0.
             */
            Vector3();

            /**
             * @brief Constructs a new Vector3 with x, y, and z initialized to the specified value.
             * @details Constructs a new Vector3 with x, y, and z initialized to the specified value.
             *
             * @param value The value to use when initializeing this vector.
             */
            Vector3(const float& value);

            /**
             * @brief Constructs a new Vector3 from the specified values.
             * @details Constructs a new Vector3 with x, y, and z initialized to the specified values.
             *
             * @param x The value to initialize x to.
             * @param y The value to initialize y to.
             * @param z The value to initialize z to.
             */
            Vector3(const float& x, const float& y, const float& z);
            
            /**
             * @brief Constructs a new Vector3 by appending a z value to an existing Vector2.
             * @details Constructs a new Vector3 with x and y initialized to a Vector2 and z initialized to the specified value.
             *
             * @param xy The Vector2 to use to initialize x and y.
             * @param z The value to initialize z to.
             */
            Vector3(const Vector2& xy, const float& z);
            
            
            /**
             * @brief Constructs a new Vector3 by prepending a x value to an existing Vector2.
             * @details Constructs a new Vector3 with x initialized to the specified value and y and z initialized to a Vector2.
             *
             * @param x The value to initialize x to.
             * @param yz The Vector2 to use to initialize y and z.
             */
            Vector3(const float& x, const Vector2& yz);

            /**
             * @brief Construct a new Vector3 from an existing float array.
             * @details Constructs a new Vector3 with the buffer copied from the passed array.
             * 
             * @param buffer The array to initialize to.
             */
            Vector3(const float (&buffer)[SIZE]);

            /**
             * @brief Copy construct a new Vector3 from an existing Vector3.
             * @details Constructs a new Vector3 by copying the values stored in an exisiting Vector3.
             * 
             * @param vec The vector to copy.
             */
            Vector3(const Vector3& vec);

            /**
             * @brief Move construct a new Vector3 from an existing Vector3.
             * @details Constructs a new Vector3 by moving the values stored in an exisiting Vector3 rvalue into this object.
             * 
             * @param vec The vector to move.
             */
            Vector3(Vector3&& vec);

            // Properties

            union {
                /** The elements of this vector in a raw buffer array. */
                float buffer[SIZE];
                struct {
                    /** The x component of this vector. */
                    float x;
                    /** The y component of this vector. */
                    float y;
                    /** The z component of this vector. */
                    float z;
                };
            };

            // Constants

            /** The 3D Up Vector (0, 1, 0). */
            static const Vector3 UP;
            /** The 3D Down Vector (0, -1, 0). */
            static const Vector3 DOWN;
            /** The 3D Left Vector (-1, 0, 0). */
            static const Vector3 LEFT;
            /** The 3D Right Vector (1, 0, 0). */
            static const Vector3 RIGHT;
            /** The 3D Forward Vector (0, 0, 1). */
            static const Vector3 FORWARD;
            /** The 3D Right Vector (0, 0, -1). */
            static const Vector3 BACKWARD;
            /** The 3D One Vector (1, 1, 1). */
            static const Vector3 ONE;
            /** The 3D Zero Vector (0, 0, 0). */
            static const Vector3 ZERO;

            // Static Functions

            /**
             * @brief Calculates the angle between two vectors in radians.
             *
             * @param v0 The first vector.
             * @param v1 The second vector.
             * @return float The angle between the vectors in radians.
             */
            static float angle(const Vector3& v0, const Vector3& v1);

            /**
             * @brief Calculates the distance between two vectors.
             *
             * @param v0 The first vector.
             * @param v1 The second vector.
             * @return float The distance between the two vectos.
             */
            static float distance(const Vector3& v0, const Vector3& v1);

            /**
             * @brief Calculates the dot product of two vectors.
             *
             * @param v0 The first vector.
             * @param v1 The second vector.
             * @return float The dot product the two vectos.
             */
            static float dot(const Vector3& v0, const Vector3& v1);

            /**
             * @brief Takes the cross product of two vectors.
             *
             * @param v0 The first vector.
             * @param v1 The second vector.
             * @return Vector3 The vector orthogonal to both v0 and v1.
             */
            static Vector3 cross(const Vector3& v0, const Vector3& v1);

            /**
             * @brief Returns the magnitude (vector length) of the passed vector.
             *
             * @param v The vector to evaluate.
             * @return float The magnitude (vector length) of the vector.
             */
            static float magnitude(const Vector3& v);

            /**
             * @brief Returns the squared magnitude (vector length) of the passed vector.
             * @details Returns the squared magnitude (vector length) of the passed vector.
             *          This method is faster than magnitude() and is equivalent to dot(v, v).
             *
             * @param v The vector to evaluate.
             * @return float The squared magnitude (vector length) of the vector.
             */
            static float mag2(const Vector3& v);

            /**
             * @brief Returns the normalized version of the passed vector.
             * @details This function calculates the unit vector of length/magnitude 1 that points in the
             *          same direction as the specified vector.
             *
             * @param v The vector to normalize.
             * @return Vector3 The normalized vector.
             */
            static Vector3 normalize(const Vector3& v);

            /**
             * @brief Reflects the incident vector off of a surface with the specified normal.
             *
             * @param incident The incident vector.
             * @param normal The surface normal vector.
             * @return Vector3 The reflection of the incident vector.
             */
            static Vector3 reflect(const Vector3& incident, const Vector3& normal);

            /**
             * @brief Refracts an incident vector based on a surface normal and index of refraction.
             *
             * @param incident The incident vector.
             * @param normal The surface normal vector.
             * @param eta The index of refraction.
             * @return Vector3 The refraction of the incident vector.
             */
            static Vector3 refract(const Vector3& incident, const Vector3& normal, const float& eta);

            /**
             * @brief Projects vector a onto vector b.
             *
             * @param a The vector to project.
             * @param b The vector to project onto.
             * @return Vector3 The projection of a onto b.
             */
            static Vector3 project(const Vector3& a, const Vector3& b);

            /**
             * @brief Orthogonally projects vector a onto vector b.
             *
             * @param a The vector to project.
             * @param b The vector to project onto.
             * @return Vector3 The orthogonal projection of a onto b.
             */
            static Vector3 ortho(const Vector3& a, const Vector3& b);

            /**
             * @brief Rotates the passed vector using the given quaternion.
             * 
             * @param v The vector to rotate.
             * @param q The quaternion to rotate by.
             * @return Vector3 The rotated vector.
             */
            static Vector3 rotate(const Vector3& v, const Quaternion& q);

            // Member Functions

            /**
             * @brief Gets the angle in radians between this vector and the specified vector.
             *
             * @param v The vector to check against.
             * @return float The angle in radians between the vectors.
             */
            float angle(const Vector3& v) const;

            /**
             * @brief Gets the distance between this vector and the specified vector.
             *
             * @param v The vector to check against.
             * @return float The distance between this vector and the specified vector.
             */
            float distance(const Vector3& v) const;

            /**
             * @brief Calculates the dot product between this vector and the specified vector.
             *
             * @param v The vector to compute the dot product with.
             * @return float The dot product of this vector and the specified vector.
             */
            float dot(const Vector3& v) const;

            /**
             * @brief Calculates the cross product between this vector and the specified vector.
             *
             * @param v0 The first vector.
             * @param v1 The second vector.
             * @return Vector3 The vector orthogonal to both this and v.
             */
            Vector3 cross(const Vector3& v) const;

            /**
             * @brief Gets the magnitude (vector length) of this vector.
             *
             * @return float The magnitude (vector length) of this vector.
             */
            float magnitude() const;

            /**
             * @brief Gets the squared magnitude (vector length) of this vector.
             *
             * @return float The squared magnitude (vector length) of this vector.
             */
            float mag2() const;

            /**
             * @brief Gets the normalized version of this vector.
             * @details This function calculates the unit vector of length/magnitude 1 that points in the
             *          same direction as this vector.
             *
             * @return Vector3 The normalized version of this vector.
             */
            Vector3 normalize() const;

            /**
             * @brief Gets this vector rotated by the given quaternion.
             * 
             * @param angle The quaternion to rotate by.
             * @return Vector3 The rotated vector.
             */
            Vector3 rotate(const Quaternion& q) const;

            // Accessor operators

            float& operator[](const int& index);

            const float& operator[](const int& index) const;

            // Arithmatic operators

            Vector3 operator+(const Vector3& vec) const;
            Vector3 operator+(const float& f) const;
            friend ENGINE_API Vector3 operator+(const float& f, const Vector3& vector);

            Vector3 operator-(const Vector3& vec) const;
            Vector3 operator-(const float& f) const;
            friend ENGINE_API Vector3 operator+(const float& f, const Vector3& vector);

            Vector3 operator/(const Vector3& vec) const;
            Vector3 operator/(const float& f) const;
            friend ENGINE_API Vector3 operator/(const float& f, const Vector3& vector);

            Vector3 operator*(const Vector3& vec) const;
            Vector3 operator*(const float& f) const;
            friend ENGINE_API Vector3 operator*(const float& f, const Vector3& vector);

            // Boolean operators

            bool operator==(const Vector3& vec) const;

            bool operator!=(const Vector3& vec) const;

            // Assignment operators

            Vector3& operator=(const Vector3& vec);
            Vector3& operator=(const float& value);

            // Cast operators

            operator Vector2() const;
            operator Vector4() const;

            operator Vector2Int() const;
            operator Vector3Int() const;
            operator Vector4Int() const;

            operator Matrix1x2() const;
            operator Matrix1x3() const;
            operator Matrix1x4() const;
            
            operator Matrix2x1() const;
            operator Matrix3x1() const;
            operator Matrix4x1() const;

            operator std::string() const;

            // IO operators

            friend ENGINE_API std::ostream& operator<< (std::ostream& os, const Vector3& c);

    };

    // Global arithmatic operators

    ENGINE_API Vector3 operator+(const float& f, const Vector3& vector);
    ENGINE_API Vector3 operator-(const float& f, const Vector3& vector);
    ENGINE_API Vector3 operator*(const float& f, const Vector3& vector);
    ENGINE_API Vector3 operator/(const float& f, const Vector3& vector);

    // Global IO operators

    ENGINE_API std::ostream& operator<< (std::ostream& os, const Vector3& c);

}

#endif