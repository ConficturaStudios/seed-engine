/**
 * Vector2.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_MATH_VECTOR2_H_
#define SEEDENGINE_INCLUDE_RUNTIME_MATH_VECTOR2_H_

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

    /**
     * @brief A 2 Dimentsional vector with components x and y.
     *
     * @see #Vector3
     * @see #Vector4
     * @see #Vector2Int
     * @see #Vector3Int
     * @see #Vector4Int
     */
    class ENGINE_API Vector2 final {

        protected:

            /** The number of components this vector type has. */
            static constexpr const int SIZE = 2;

        public:

        // Constructors

            /**
             * @brief Constructs a new Vector2 initialized to the zero vector.
             * @details Constructs a new Vector2 with x an y both initialized to a value of 0.
             */
            Vector2();

            /**
             * @brief Constructs a new Vector2 with both x and y initialized to the specified value.
             * @details Constructs a new Vector2 with both x and y initialized to the specified value.
             *
             * @param value The value to use when initializing this vector.
             */
            Vector2(const float& value);

            /**
             * @brief Constructs a new Vector2 from the specified values.
             * @details Constructs a new Vector2 with x and y initialized to the specified values.
             *
             * @param x The value to initialize x to.
             * @param y The value to initialize y to.
             */
            Vector2(const float& x, const float& y);

            /**
             * @brief Construct a new Vector2 from an existing float array.
             * @details Constructs a new Vector2 with the buffer copied from the passed array.
             * 
             * @param buffer The array to initialize to.
             */
            Vector2(const float (&buffer)[SIZE]);

            /**
             * @brief Copy construct a new Vector2 from an existing Vector2.
             * @details Constructs a new Vector2 by copying the values stored in an exisiting Vector2.
             * 
             * @param vec The vector to copy.
             */
            Vector2(const Vector2& vec);

            /**
             * @brief Move construct a new Vector2 from an existing Vector2.
             * @details Constructs a new Vector2 by moving the values stored in an exisiting Vector2 rvalue into this object.
             * 
             * @param vec The vector to move.
             */
            Vector2(Vector2&& vec);

        // Properties

            union {
                /** The elements of this vector in a raw buffer array. */
                float buffer[SIZE];
                struct {
                    /** The x component of this vector. */
                    float x;
                    /** The y component of this vector. */
                    float y;
                };
            };

        // Constants

            /** The 2D Up Vector (0, 1). */
            static const Vector2 UP;
            /** The 2D Down Vector (0, -1). */
            static const Vector2 DOWN;
            /** The 2D Left Vector (-1, 0). */
            static const Vector2 LEFT;
            /** The 2D Right Vector (1, 0). */
            static const Vector2 RIGHT;
            /** The 2D One Vector (1, 1). */
            static const Vector2 ONE;
            /** The 2D Zero Vector (0, 0). */
            static const Vector2 ZERO;

        // Static Functions

            /**
             * @brief Calculates the angle between two vectors in radians.
             *
             * @param v0 The first vector.
             * @param v1 The second vector.
             * @return float The angle between the vectors in radians.
             */
            static float angle(const Vector2& v0, const Vector2& v1);

            /**
             * @brief Calculates the distance between two vectors.
             *
             * @param v0 The first vector.
             * @param v1 The second vector.
             * @return float The distance between the two vectos.
             */
            static float distance(const Vector2& v0, const Vector2& v1);

            /**
             * @brief Calculates the dot product of two vectors.
             *
             * @param v0 The first vector.
             * @param v1 The second vector.
             * @return float The dot product the two vectos.
             */
            static float dot(const Vector2& v0, const Vector2& v1);

            /**
             * @brief Returns the magnitude (vector length) of the passed vector.
             *
             * @param v The vector to evaluate.
             * @return float The magnitude (vector length) of the vector.
             */
            static float magnitude(const Vector2& v);

            /**
             * @brief Returns the squared magnitude (vector length) of the passed vector.
             * @details Returns the squared magnitude (vector length) of the passed vector.
             *          This method is faster than magnitude() and is equivalent to dot(v, v).
             *
             * @param v The vector to evaluate.
             * @return float The squared magnitude (vector length) of the vector.
             */
            static float mag2(const Vector2& v);

            /**
             * @brief Returns the normalized version of the passed vector.
             * @details This function calculates the unit vector of length/magnitude 1 that points in the
             *          same direction as the specified vector.
             *
             * @param v The vector to normalize.
             * @return Vector2 The normalized vector.
             */
            static Vector2 normalize(const Vector2& v);

            /**
             * @brief Reflects the incident vector off of a surface with the specified normal.
             *
             * @param incident The incident vector.
             * @param normal The surface normal vector.
             * @return Vector2 The reflection of the incident vector.
             */
            static Vector2 reflect(const Vector2& incident, const Vector2& normal);

            /**
             * @brief Refracts an incident vector based on a surface normal and index of refraction.
             *
             * @param incident The incident vector.
             * @param normal The surface normal vector.
             * @param eta The index of refraction.
             * @return Vector2 The refraction of the incident vector.
             */
            static Vector2 refract(const Vector2& incident, const Vector2& normal, const float& eta);

            /**
             * @brief Projects vector a onto vector b.
             *
             * @param a The vector to project.
             * @param b The vector to project onto.
             * @return Vector2 The projection of a onto b.
             */
            static Vector2 project(const Vector2& a, const Vector2& b);

            /**
             * @brief Orthogonally projects vector a onto vector b.
             *
             * @param a The vector to project.
             * @param b The vector to project onto.
             * @return Vector2 The orthogonal projection of a onto b.
             */
            static Vector2 ortho(const Vector2& a, const Vector2& b);

            /**
             * @brief Rotates the passed vector counterclockwise by the given angle.
             * 
             * @param v The vector to rotate.
             * @param angle The angle to rotate in radians.
             * @return Vector2 The rotated vector.
             */
            static Vector2 rotate(const Vector2& v, const float& angle);

        // Member Functions

            /**
             * @brief Gets the angle in radians between this vector and the specified vector.
             *
             * @param v The vector to check against.
             * @return float The angle in radians between the vectors.
             */
            float angle(const Vector2& v) const;

            /**
             * @brief Gets the distance between this vector and the specified vector.
             *
             * @param v The vector to check against.
             * @return float The distance between this vector and the specified vector.
             */
            float distance(const Vector2& v) const;

            /**
             * @brief Calculates the dot product between this vector and the specified vector.
             *
             * @param v The vector to compute the dot product with.
             * @return float The dot product of this vector and the specified vector.
             */
            float dot(const Vector2& v) const;

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
             * @return Vector2 The normalized version of this vector.
             */
            Vector2 normalize() const;

            /**
             * @brief Gets this vector rotated counterclockwise by the given angle.
             * 
             * @param angle The angle to rotate in radians.
             * @return Vector2 The rotated vector.
             */
            Vector2 rotate(const float& angle) const;

        // Accessor operators

            float& operator[](const int& index);

            const float& operator[](const int& index) const;

        // Arithmatic operators

            Vector2 operator+(const Vector2& vec) const;
            Vector2 operator+(const float& f) const;
            friend ENGINE_API Vector2 operator+(const float& f, const Vector2& vector);

            Vector2 operator-(const Vector2& vec) const;
            Vector2 operator-(const float& f) const;
            friend ENGINE_API Vector2 operator+(const float& f, const Vector2& vector);

            Vector2 operator/(const Vector2& vec) const;
            Vector2 operator/(const float& f) const;
            friend ENGINE_API Vector2 operator/(const float& f, const Vector2& vector);

            Vector2 operator*(const Vector2& vec) const;
            Vector2 operator*(const float& f) const;
            friend ENGINE_API Vector2 operator*(const float& f, const Vector2& vector);

        // Boolean operators

            bool operator==(const Vector2& vec) const;

            bool operator!=(const Vector2& vec) const;

        // Assignment operators

            Vector2& operator=(const Vector2& vec);
            Vector2& operator=(const float& value);

        // Cast operators

            operator Vector3() const;
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

            friend ENGINE_API std::ostream& operator<< (std::ostream& os, const Vector2& c);


    };

    // Global arithmatic operators

    ENGINE_API Vector2 operator+(const float& f, const Vector2& vector);
    ENGINE_API Vector2 operator-(const float& f, const Vector2& vector);
    ENGINE_API Vector2 operator*(const float& f, const Vector2& vector);
    ENGINE_API Vector2 operator/(const float& f, const Vector2& vector);

    // Global IO operators

    ENGINE_API std::ostream& operator<< (std::ostream& os, const Vector2& c);

}

#endif