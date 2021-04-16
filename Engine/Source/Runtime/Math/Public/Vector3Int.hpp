/**
 * Vector3Int.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_MATH_VECTOR3_INT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_MATH_VECTOR3_INT_H_

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
     * @brief A 3 Dimensional integer vector with components x, y, and z.
     *
     * @see #Vector2
     * @see #Vector3
     * @see #Vector4
     * @see #Vector2Int
     * @see #Vector4Int
     */
    class ENGINE_API Vector3Int final {

        protected:

            /** The number of components this vector type has. */
            static constexpr const int SIZE = 3;

        public:

            // Constructors

            /**
             * @brief Constructs a new Vector3Int initialized to the zero vector.
             * @details Constructs a new Vector3Int with x, y, and z initialized to a value of 0.
             */
            Vector3Int() noexcept;

            /**
             * @brief Constructs a new Vector3Int with x, y, and z initialized to the specified value.
             * @details Constructs a new Vector3Int with x, y, and z initialized to the specified value.
             *
             * @param value The value to use when initializing this vector.
             */
            explicit Vector3Int(int value) noexcept;

            /**
             * @brief Constructs a new Vector3Int from the specified values.
             * @details Constructs a new Vector3Int with x, y, and z initialized to the specified values.
             *
             * @param x The value to initialize x to.
             * @param y The value to initialize y to.
             * @param z The value to initialize z to.
             */
            Vector3Int(int x, int y, int z) noexcept;
            
            /**
             * @brief Constructs a new Vector3Int by appending a z value to an existing Vector2Int.
             * @details Constructs a new Vector3Int with x and y initialized to a Vector2Int and z initialized to the specified value.
             *
             * @param xy The Vector2Int to use to initialize x and y.
             * @param z The value to initialize z to.
             */
            Vector3Int(const Vector2Int& xy, int z) noexcept;
            
            
            /**
             * @brief Constructs a new Vector3Int by prepending a x value to an existing Vector2Int.
             * @details Constructs a new Vector3Int with x initialized to the specified value and y and z initialized to a Vector2Int.
             *
             * @param x The value to initialize x to.
             * @param yz The Vector2Int to use to initialize y and z.
             */
            Vector3Int(int x, const Vector2Int& yz) noexcept;

            /**
             * @brief Construct a new Vector3Int from an existing int array.
             * @details Constructs a new Vector3Int with the buffer copied from the passed array.
             * 
             * @param buffer The array to initialize to.
             */
            Vector3Int(const int (&buffer)[SIZE]);

            /**
             * @brief Copy construct a new Vector3Int from an existing Vector3Int.
             * @details Constructs a new Vector3Int by copying the values stored in an existing Vector3Int.
             * 
             * @param vec The vector to copy.
             */
            Vector3Int(const Vector3Int& vec) noexcept;

            /**
             * @brief Move construct a new Vector3Int from an existing Vector3Int.
             * @details Constructs a new Vector3Int by moving the values stored in an existing Vector3Int rvalue into this object.
             * 
             * @param vec The vector to move.
             */
            Vector3Int(Vector3Int&& vec) noexcept;

            // Properties

            union {
                /** The elements of this vector in a raw buffer array. */
                int buffer[SIZE]{};
                struct {
                    /** The x component of this vector. */
                    int x;
                    /** The y component of this vector. */
                    int y;
                    /** The z component of this vector. */
                    int z;
                };
            };

            // Constants

            /** The 3D Up Vector (0, 1, 0). */
            static const Vector3Int UP;
            /** The 3D Down Vector (0, -1, 0). */
            static const Vector3Int DOWN;
            /** The 3D Left Vector (-1, 0, 0). */
            static const Vector3Int LEFT;
            /** The 3D Right Vector (1, 0, 0). */
            static const Vector3Int RIGHT;
            /** The 3D Forward Vector (0, 0, 1). */
            static const Vector3Int FORWARD;
            /** The 3D Right Vector (0, 0, -1). */
            static const Vector3Int BACKWARD;
            /** The 3D One Vector (1, 1, 1). */
            static const Vector3Int ONE;
            /** The 3D Zero Vector (0, 0, 0). */
            static const Vector3Int ZERO;

            // Static Functions

            /**
             * @brief Calculates the angle between two vectors in radians.
             *
             * @param v0 The first vector.
             * @param v1 The second vector.
             * @return float The angle between the vectors in radians.
             */
            [[nodiscard]] static float angle(const Vector3Int& v0, const Vector3Int& v1);

            /**
             * @brief Calculates the distance between two vectors.
             *
             * @param v0 The first vector.
             * @param v1 The second vector.
             * @return float The distance between the two vectors.
             */
            [[nodiscard]] static float distance(const Vector3Int& v0, const Vector3Int& v1);

            /**
             * @brief Calculates the dot product of two vectors.
             *
             * @param v0 The first vector.
             * @param v1 The second vector.
             * @return int The dot product the two vectors.
             */
            [[nodiscard]] static int dot(const Vector3Int& v0, const Vector3Int& v1);

            /**
             * @brief Takes the cross product of two vectors.
             *
             * @param v0 The first vector.
             * @param v1 The second vector.
             * @return Vector3Int The vector orthogonal to both v0 and v1.
             */
            [[nodiscard]] static Vector3Int cross(const Vector3Int& v0, const Vector3Int& v1);

            /**
             * @brief Returns the magnitude (vector length) of the passed vector.
             *
             * @param v The vector to evaluate.
             * @return float The magnitude (vector length) of the vector.
             */
            [[nodiscard]] static float magnitude(const Vector3Int& v);

            /**
             * @brief Returns the squared magnitude (vector length) of the passed vector.
             * @details Returns the squared magnitude (vector length) of the passed vector.
             *          This method is faster than magnitude() and is equivalent to dot(v, v).
             *
             * @param v The vector to evaluate.
             * @return int The squared magnitude (vector length) of the vector.
             */
            [[nodiscard]] static int mag2(const Vector3Int& v);

            // Member Functions

            /**
             * @brief Gets the angle in radians between this vector and the specified vector.
             *
             * @param v The vector to check against.
             * @return float The angle in radians between the vectors.
             */
            [[nodiscard]] float angle(const Vector3Int& v) const;

            /**
             * @brief Gets the distance between this vector and the specified vector.
             *
             * @param v The vector to check against.
             * @return float The distance between this vector and the specified vector.
             */
            [[nodiscard]] float distance(const Vector3Int& v) const;

            /**
             * @brief Calculates the dot product between this vector and the specified vector.
             *
             * @param v The vector to compute the dot product with.
             * @return int The dot product of this vector and the specified vector.
             */
            [[nodiscard]] int dot(const Vector3Int& v) const;

            /**
             * @brief Calculates the cross product between this vector and the specified vector.
             *
             * @param v0 The first vector.
             * @param v1 The second vector.
             * @return Vector3Int The vector orthogonal to both this and v.
             */
            [[nodiscard]] Vector3Int cross(const Vector3Int& v) const;

            /**
             * @brief Gets the magnitude (vector length) of this vector.
             *
             * @return float The magnitude (vector length) of this vector.
             */
            [[nodiscard]] float magnitude() const;

            /**
             * @brief Gets the squared magnitude (vector length) of this vector.
             *
             * @return int The squared magnitude (vector length) of this vector.
             */
            [[nodiscard]] int mag2() const;

            // Accessor operators

            [[nodiscard]] int& operator[](int index);

            [[nodiscard]] const int& operator[](int index) const;

            // Arithmetic operators

            [[nodiscard]] Vector3Int operator+(const Vector3Int& vec) const;
            [[nodiscard]] Vector3Int operator+(int f) const;
            friend ENGINE_API Vector3Int operator+(int f, const Vector3Int& vector);

            [[nodiscard]] Vector3Int operator-(const Vector3Int& vec) const;
            [[nodiscard]] Vector3Int operator-(int f) const;
            friend ENGINE_API Vector3Int operator+(int f, const Vector3Int& vector);

            [[nodiscard]] Vector3Int operator/(const Vector3Int& vec) const;
            [[nodiscard]] Vector3Int operator/(int f) const;
            friend ENGINE_API Vector3Int operator/(int f, const Vector3Int& vector);

            [[nodiscard]] Vector3Int operator*(const Vector3Int& vec) const;
            [[nodiscard]] Vector3Int operator*(int f) const;
            friend ENGINE_API Vector3Int operator*(int f, const Vector3Int& vector);

            // Boolean operators

            [[nodiscard]] bool operator==(const Vector3Int& vec) const;

            [[nodiscard]] bool operator!=(const Vector3Int& vec) const;

            // Assignment operators

            Vector3Int& operator=(const Vector3Int& vec);
            Vector3Int& operator=(int value);

            // Cast operators

            [[nodiscard]] explicit operator Vector2() const;
            [[nodiscard]] explicit operator Vector3() const;
            [[nodiscard]] explicit operator Vector4() const;

            [[nodiscard]] explicit operator Vector2Int() const;
            [[nodiscard]] explicit operator Vector4Int() const;

            [[nodiscard]] explicit operator Matrix1x2Int() const;
            [[nodiscard]] explicit operator Matrix1x3Int() const;
            [[nodiscard]] explicit operator Matrix1x4Int() const;
            
            [[nodiscard]] explicit operator Matrix2x1Int() const;
            [[nodiscard]] explicit operator Matrix3x1Int() const;
            [[nodiscard]] explicit operator Matrix4x1Int() const;

            [[nodiscard]] explicit operator ::std::string() const;

            // IO operators

            friend ENGINE_API std::ostream& operator<< (std::ostream& os, const Vector3Int& c);

    };

    // Global arithmetic operators

    [[nodiscard]] ENGINE_API Vector3Int operator+(int f, const Vector3Int& vector);
    [[nodiscard]] ENGINE_API Vector3Int operator-(int f, const Vector3Int& vector);
    [[nodiscard]] ENGINE_API Vector3Int operator*(int f, const Vector3Int& vector);
    [[nodiscard]] ENGINE_API Vector3Int operator/(int f, const Vector3Int& vector);

    // Global IO operators

    [[nodiscard]] ENGINE_API std::ostream& operator<< (std::ostream& os, const Vector3Int& c);

}

#endif