/**
 * Vector4.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_MATH_VECTOR4_H_
#define SEEDENGINE_INCLUDE_RUNTIME_MATH_VECTOR4_H_

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
     * @brief A 4 Dimentsional vector with components x, y, z, and w
     *
     * @see #Vector2
     * @see #Vector3
     * @see #Vector2Int
     * @see #Vector3Int
     * @see #Vector4Int
     */
    class ENGINE_API Vector4 final {

        protected:

            /** The number of components this vector type has. */
            static constexpr const int SIZE = 4;

        public:

            // Constructors

            /**
             * @brief Constructs a new Vector4 initialized to the zero vector.
             * @details Constructs a new Vector4 with x, y, z, and w initialized to a value of 0.
             */
            Vector4();

            /**
             * @brief Constructs a new Vector4 with x, y, z, and w initialized to the specified value.
             * @details Constructs a new Vector4 with x, y, z, and w initialized to the specified value.
             *
             * @param value The value to use when initializeing this vector.
             */
            Vector4(const float& value);

            /**
             * @brief Constructs a new Vector4 from the specified values.
             * @details Constructs a new Vector4 with x, y, z, and w initialized to the specified values.
             *
             * @param x The value to initialize x to.
             * @param y The value to initialize y to.
             * @param z The value to initialize z to.
             * @param w The value to initialize w to.
             */
            Vector4(const float& x, const float& y, const float& z, const float& w);
            
            /**
             * @brief Constructs a new Vector4 by appending a z and w value to an existing Vector2.
             * @details Constructs a new Vector4 with x and y initialized to a Vector2 and z and w initialized to the specified value.
             *
             * @param xy The Vector2 to use to initialize x and y.
             * @param z The value to initialize z to.
             * @param w The value to initialize w to.
             */
            Vector4(const Vector2& xy, const float& z, const float& w);
            
            /**
             * @brief Constructs a new Vector4 by prepending a x value to an existing Vector2 and appending a w value.
             * @details Constructs a new Vector4 with x and w initialized to the specified value and y and z initialized to a Vector2.
             *
             * @param x The value to initialize x to.
             * @param yz The Vector2 to use to initialize y and z.
             * @param w The value to initialize w to.
             */
            Vector4(const float& x, const Vector2& yz, const float& w);
            
            /**
             * @brief Constructs a new Vector4 by prepending a x and y value to an existing Vector2.
             * @details Constructs a new Vector4 with x and y initialized to the specified value and z and w initialized to a Vector2.
             *
             * @param x The value to initialize x to.
             * @param y The value to initialize y to.
             * @param zw The Vector2 to use to initialize z and w.
             */
            Vector4(const float& x, const float& y, const Vector2& zw);
            
            /**
             * @brief Constructs a new Vector4 by concatinating two Vector2s.
             * @details Constructs a new Vector4 by concatinating two Vector2 values.
             *
             * @param xy The Vector2 to use to initialize x and y.
             * @param zw The Vector2 to use to initialize z and w.
             */
            Vector4(const Vector2& xy, const Vector2& zw);
            
            /**
             * @brief Constructs a new Vector4 by appending a w value to an existing Vector3.
             * @details Constructs a new Vector4 with x, y, and z initialized to a Vector3 and w initialized to the specified value.
             *
             * @param xyz The Vector3 to use to initialize x, y, and z.
             * @param w The value to initialize w to.
             */
            Vector4(const Vector3& xyz, const float& w);
            
            /**
             * @brief Constructs a new Vector4 by prepending a x value to an existing Vector3.
             * @details Constructs a new Vector4 with x initialized to the specified value and y, z, and w initialized to a Vector3.
             *
             * @param x The value to initialize x to.
             * @param yz The Vector3 to use to initialize y, z, and w.
             */
            Vector4(const float& x, const Vector3& yzw);
            
            /**
             * @brief Construct a new Vector4 from an existing float array.
             * @details Constructs a new Vector4 with the buffer copied from the passed array.
             * 
             * @param buffer The array to initialize to.
             */
            Vector4(const float (&buffer)[SIZE]);

            /**
             * @brief Copy construct a new Vector4 from an existing Vector4.
             * @details Constructs a new Vector4 by copying the values stored in an exisiting Vector4.
             * 
             * @param vec The vector to copy.
             */
            Vector4(const Vector4& vec);

            /**
             * @brief Move construct a new Vector4 from an existing Vector4.
             * @details Constructs a new Vector4 by moving the values stored in an exisiting Vector4 rvalue into this object.
             * 
             * @param vec The vector to move.
             */
            Vector4(Vector4&& vec);

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
                    /** The w component of this vector. */
                    float w;
                };
            };

            // Constants

            /** The 3D Up Vector (0, 1, 0, 0). */
            static const Vector4 UP;
            /** The 3D Down Vector (0, -1, 0, 0). */
            static const Vector4 DOWN;
            /** The 3D Left Vector (-1, 0, 0, 0). */
            static const Vector4 LEFT;
            /** The 3D Right Vector (1, 0, 0, 0). */
            static const Vector4 RIGHT;
            /** The 3D Forward Vector (0, 0, 1, 0). */
            static const Vector4 FORWARD;
            /** The 3D Right Vector (0, 0, -1, 0). */
            static const Vector4 BACKWARD;
            /** The 3D Forward Vector (0, 0, 0, 1). */
            static const Vector4 KATA;
            /** The 3D Right Vector (0, 0, 0, -1). */
            static const Vector4 ANA;
            /** The 3D One Vector (1, 1, 1, 1). */
            static const Vector4 ONE;
            /** The 3D Zero Vector (0, 0, 0, 0). */
            static const Vector4 ZERO;

            // Static Functions

            /**
             * @brief Calculates the angle between two vectors in radians.
             *
             * @param v0 The first vector.
             * @param v1 The second vector.
             * @return float The angle between the vectors in radians.
             */
            static float angle(const Vector4& v0, const Vector4& v1);

            /**
             * @brief Calculates the distance between two vectors.
             *
             * @param v0 The first vector.
             * @param v1 The second vector.
             * @return float The distance between the two vectos.
             */
            static float distance(const Vector4& v0, const Vector4& v1);

            /**
             * @brief Calculates the dot product of two vectors.
             *
             * @param v0 The first vector.
             * @param v1 The second vector.
             * @return float The dot product the two vectos.
             */
            static float dot(const Vector4& v0, const Vector4& v1);

            /**
             * @brief Returns the magnitude (vector length) of the passed vector.
             *
             * @param v The vector to evaluate.
             * @return float The magnitude (vector length) of the vector.
             */
            static float magnitude(const Vector4& v);

            /**
             * @brief Returns the squared magnitude (vector length) of the passed vector.
             * @details Returns the squared magnitude (vector length) of the passed vector.
             *          This method is faster than magnitude() and is equivalent to dot(v, v).
             *
             * @param v The vector to evaluate.
             * @return float The squared magnitude (vector length) of the vector.
             */
            static float mag2(const Vector4& v);

            /**
             * @brief Returns the normalized version of the passed vector.
             * @details This function calculates the unit vector of length/magnitude 1 that points in the
             *          same direction as the specified vector.
             *
             * @param v The vector to normalize.
             * @return Vector4 The normalized vector.
             */
            static Vector4 normalize(const Vector4& v);

            /**
             * @brief Reflects the incident vector off of a surface with the specified normal.
             *
             * @param incident The incident vector.
             * @param normal The surface normal vector.
             * @return Vector4 The reflection of the incident vector.
             */
            static Vector4 reflect(const Vector4& incident, const Vector4& normal);

            /**
             * @brief Refracts an incident vector based on a surface normal and index of refraction.
             *
             * @param incident The incident vector.
             * @param normal The surface normal vector.
             * @param eta The index of refraction.
             * @return Vector4 The refraction of the incident vector.
             */
            static Vector4 refract(const Vector4& incident, const Vector4& normal, const float& eta);

            /**
             * @brief Projects vector a onto vector b.
             *
             * @param a The vector to project.
             * @param b The vector to project onto.
             * @return Vector4 The projection of a onto b.
             */
            static Vector4 project(const Vector4& a, const Vector4& b);

            /**
             * @brief Orthogonally projects vector a onto vector b.
             *
             * @param a The vector to project.
             * @param b The vector to project onto.
             * @return Vector4 The orthogonal projection of a onto b.
             */
            static Vector4 ortho(const Vector4& a, const Vector4& b);

            // Member Functions

            /**
             * @brief Gets the angle in radians between this vector and the specified vector.
             *
             * @param v The vector to check against.
             * @return float The angle in radians between the vectors.
             */
            float angle(const Vector4& v) const;

            /**
             * @brief Gets the distance between this vector and the specified vector.
             *
             * @param v The vector to check against.
             * @return float The distance between this vector and the specified vector.
             */
            float distance(const Vector4& v) const;

            /**
             * @brief Calculates the dot product between this vector and the specified vector.
             *
             * @param v The vector to compute the dot product with.
             * @return float The dot product of this vector and the specified vector.
             */
            float dot(const Vector4& v) const;

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
             * @return Vector4 The normalized version of this vector.
             */
            Vector4 normalize() const;

            // Accessor operators

            float& operator[](const int& index);

            const float& operator[](const int& index) const;

            // Arithmatic operators

            Vector4 operator+(const Vector4& vec) const;
            Vector4 operator+(const float& f) const;
            friend ENGINE_API Vector4 operator+(const float& f, const Vector4& vector);

            Vector4 operator-(const Vector4& vec) const;
            Vector4 operator-(const float& f) const;
            friend ENGINE_API Vector4 operator+(const float& f, const Vector4& vector);

            Vector4 operator/(const Vector4& vec) const;
            Vector4 operator/(const float& f) const;
            friend ENGINE_API Vector4 operator/(const float& f, const Vector4& vector);

            Vector4 operator*(const Vector4& vec) const;
            Vector4 operator*(const float& f) const;
            friend ENGINE_API Vector4 operator*(const float& f, const Vector4& vector);

            // Boolean operators

            bool operator==(const Vector4& vec) const;

            bool operator!=(const Vector4& vec) const;

            // Assignment operators

            Vector4& operator=(const Vector4& vec);
            Vector4& operator=(const float& value);

            // Cast operators

            operator Vector2() const;
            operator Vector3() const;

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

            friend ENGINE_API std::ostream& operator<< (std::ostream& os, const Vector4& c);

    };

    // Global arithmatic operators

    ENGINE_API Vector4 operator+(const float& f, const Vector4& vector);
    ENGINE_API Vector4 operator-(const float& f, const Vector4& vector);
    ENGINE_API Vector4 operator*(const float& f, const Vector4& vector);
    ENGINE_API Vector4 operator/(const float& f, const Vector4& vector);

    // Global IO operators

    ENGINE_API std::ostream& operator<< (std::ostream& os, const Vector4& c);
}

#endif