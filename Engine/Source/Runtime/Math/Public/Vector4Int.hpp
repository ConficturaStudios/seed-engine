/**
 * Vector4Int.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_MATH_VECTOR4_INT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_MATH_VECTOR4_INT_H_

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
     * @brief A 4 Dimensional integer vector with components x, y, z, and w
     *
     * @see #Vector2
     * @see #Vector3
     * @see #Vector4
     * @see #Vector2Int
     * @see #Vector3Int
     */
    class ENGINE_API Vector4Int final {

        protected:

            /** The number of components this vector type has. */
            static constexpr const int SIZE = 4;

        public:

            // Constructors

            /**
             * @brief Constructs a new Vector4Int initialized to the zero vector.
             * @details Constructs a new Vector4Int with x, y, z, and w initialized to a value of 0.
             */
            Vector4Int() noexcept;

            /**
             * @brief Constructs a new Vector4Int with x, y, z, and w initialized to the specified value.
             * @details Constructs a new Vector4Int with x, y, z, and w initialized to the specified value.
             *
             * @param value The value to use when initializing this vector.
             */
            explicit Vector4Int(int value) noexcept;

            /**
             * @brief Constructs a new Vector4Int from the specified values.
             * @details Constructs a new Vector4Int with x, y, z, and w initialized to the specified values.
             *
             * @param x The value to initialize x to.
             * @param y The value to initialize y to.
             * @param z The value to initialize z to.
             * @param w The value to initialize w to.
             */
            Vector4Int(int x, int y, int z, int w) noexcept;
            
            /**
             * @brief Constructs a new Vector4Int by appending a z and w value to an existing Vector2Int.
             * @details Constructs a new Vector4Int with x and y initialized to a Vector2Int and z and w initialized to the specified value.
             *
             * @param xy The Vector2Int to use to initialize x and y.
             * @param z The value to initialize z to.
             * @param w The value to initialize w to.
             */
            Vector4Int(const Vector2Int& xy, int z, int w) noexcept;
            
            /**
             * @brief Constructs a new Vector4Int by prepending a x value to an existing Vector2Int and appending a w value.
             * @details Constructs a new Vector4Int with x and w initialized to the specified value and y and z initialized to a Vector2Int.
             *
             * @param x The value to initialize x to.
             * @param yz The Vector2Int to use to initialize y and z.
             * @param w The value to initialize w to.
             */
            Vector4Int(int x, const Vector2Int& yz, int w) noexcept;
            
            /**
             * @brief Constructs a new Vector4Int by prepending a x and y value to an existing Vector2Int.
             * @details Constructs a new Vector4Int with x and y initialized to the specified value and z and w initialized to a Vector2Int.
             *
             * @param x The value to initialize x to.
             * @param y The value to initialize y to.
             * @param zw The Vector2Int to use to initialize z and w.
             */
            Vector4Int(int x, int y, const Vector2Int& zw) noexcept;
            
            /**
             * @brief Constructs a new Vector4Int by concatenating two Vector2Ints.
             * @details Constructs a new Vector4Int by concatenating two Vector2Int values.
             *
             * @param xy The Vector2Int to use to initialize x and y.
             * @param zw The Vector2Int to use to initialize z and w.
             */
            Vector4Int(const Vector2Int& xy, const Vector2Int& zw) noexcept;
            
            /**
             * @brief Constructs a new Vector4Int by appending a w value to an existing Vector3Int.
             * @details Constructs a new Vector4Int with x, y, and z initialized to a Vector3Int and w initialized to the specified value.
             *
             * @param xyz The Vector3Int to use to initialize x, y, and z.
             * @param w The value to initialize w to.
             */
            Vector4Int(const Vector3Int& xyz, int w) noexcept;
            
            /**
             * @brief Constructs a new Vector4Int by prepending a x value to an existing Vector3Int.
             * @details Constructs a new Vector4Int with x initialized to the specified value and y, z, and w initialized to a Vector3Int.
             *
             * @param x The value to initialize x to.
             * @param yz The Vector3Int to use to initialize y, z, and w.
             */
            Vector4Int(int x, const Vector3Int& yzw) noexcept;
            
            /**
             * @brief Construct a new Vector4Int from an existing int array.
             * @details Constructs a new Vector4Int with the buffer copied from the passed array.
             * 
             * @param buffer The array to initialize to.
             */
            Vector4Int(const int (&buffer)[SIZE]);

            /**
             * @brief Copy construct a new Vector4Int from an existing Vector4Int.
             * @details Constructs a new Vector4Int by copying the values stored in an existing Vector4Int.
             * 
             * @param vec The vector to copy.
             */
            Vector4Int(const Vector4Int& vec) noexcept;

            /**
             * @brief Move construct a new Vector4Int from an existing Vector4Int.
             * @details Constructs a new Vector4Int by moving the values stored in an existing Vector4Int rvalue into this object.
             * 
             * @param vec The vector to move.
             */
            Vector4Int(Vector4Int&& vec) noexcept;

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
                    /** The w component of this vector. */
                    int w;
                };
            };

            // Constants

            /** The 3D Up Vector (0, 1, 0, 0). */
            static const Vector4Int UP;
            /** The 3D Down Vector (0, -1, 0, 0). */
            static const Vector4Int DOWN;
            /** The 3D Left Vector (-1, 0, 0, 0). */
            static const Vector4Int LEFT;
            /** The 3D Right Vector (1, 0, 0, 0). */
            static const Vector4Int RIGHT;
            /** The 3D Forward Vector (0, 0, 1, 0). */
            static const Vector4Int FORWARD;
            /** The 3D Right Vector (0, 0, -1, 0). */
            static const Vector4Int BACKWARD;
            /** The 3D Forward Vector (0, 0, 0, 1). */
            static const Vector4Int KATA;
            /** The 3D Right Vector (0, 0, 0, -1). */
            static const Vector4Int ANA;
            /** The 3D One Vector (1, 1, 1, 1). */
            static const Vector4Int ONE;
            /** The 3D Zero Vector (0, 0, 0, 0). */
            static const Vector4Int ZERO;

            // Static Functions

            /**
             * @brief Calculates the angle between two vectors in radians.
             *
             * @param v0 The first vector.
             * @param v1 The second vector.
             * @return float The angle between the vectors in radians.
             */
            static float angle(const Vector4Int& v0, const Vector4Int& v1);

            /**
             * @brief Calculates the distance between two vectors.
             *
             * @param v0 The first vector.
             * @param v1 The second vector.
             * @return float The distance between the two vectors.
             */
            static float distance(const Vector4Int& v0, const Vector4Int& v1);

            /**
             * @brief Calculates the dot product of two vectors.
             *
             * @param v0 The first vector.
             * @param v1 The second vector.
             * @return int The dot product the two vectors.
             */
            static int dot(const Vector4Int& v0, const Vector4Int& v1);

            /**
             * @brief Returns the magnitude (vector length) of the passed vector.
             *
             * @param v The vector to evaluate.
             * @return float The magnitude (vector length) of the vector.
             */
            static float magnitude(const Vector4Int& v);

            /**
             * @brief Returns the squared magnitude (vector length) of the passed vector.
             * @details Returns the squared magnitude (vector length) of the passed vector.
             *          This method is faster than magnitude() and is equivalent to dot(v, v).
             *
             * @param v The vector to evaluate.
             * @return int The squared magnitude (vector length) of the vector.
             */
            static int mag2(const Vector4Int& v);

            // Member Functions

            /**
             * @brief Gets the angle in radians between this vector and the specified vector.
             *
             * @param v The vector to check against.
             * @return float The angle in radians between the vectors.
             */
            float angle(const Vector4Int& v) const;

            /**
             * @brief Gets the distance between this vector and the specified vector.
             *
             * @param v The vector to check against.
             * @return float The distance between this vector and the specified vector.
             */
            float distance(const Vector4Int& v) const;

            /**
             * @brief Calculates the dot product between this vector and the specified vector.
             *
             * @param v The vector to compute the dot product with.
             * @return int The dot product of this vector and the specified vector.
             */
            int dot(const Vector4Int& v) const;

            /**
             * @brief Gets the magnitude (vector length) of this vector.
             *
             * @return float The magnitude (vector length) of this vector.
             */
            float magnitude() const;

            /**
             * @brief Gets the squared magnitude (vector length) of this vector.
             *
             * @return int The squared magnitude (vector length) of this vector.
             */
            int mag2() const;

            // Accessor operators

            int& operator[](int index);

            const int& operator[](int index) const;

            // Arithmetic operators

            Vector4Int operator+(const Vector4Int& vec) const;
            Vector4Int operator+(int f) const;
            friend ENGINE_API Vector4Int operator+(int f, const Vector4Int& vector);

            Vector4Int operator-(const Vector4Int& vec) const;
            Vector4Int operator-(int f) const;
            friend ENGINE_API Vector4Int operator+(int f, const Vector4Int& vector);

            Vector4Int operator/(const Vector4Int& vec) const;
            Vector4Int operator/(int f) const;
            friend ENGINE_API Vector4Int operator/(int f, const Vector4Int& vector);

            Vector4Int operator*(const Vector4Int& vec) const;
            Vector4Int operator*(int f) const;
            friend ENGINE_API Vector4Int operator*(int f, const Vector4Int& vector);

            // Boolean operators

            bool operator==(const Vector4Int& vec) const;

            bool operator!=(const Vector4Int& vec) const;

            // Assignment operators

            Vector4Int& operator=(const Vector4Int& vec);
            Vector4Int& operator=(int value);

            // Cast operators

            explicit operator Vector2() const;
            explicit operator Vector3() const;
            explicit operator Vector4() const;

            explicit operator Vector2Int() const;
            explicit operator Vector3Int() const;

            explicit operator Matrix1x2Int() const;
            explicit operator Matrix1x3Int() const;
            explicit operator Matrix1x4Int() const;

            explicit operator Matrix2x1Int() const;
            explicit operator Matrix3x1Int() const;
            explicit operator Matrix4x1Int() const;

            explicit operator ::std::string() const;

            // IO operators

            friend ENGINE_API std::ostream& operator<< (std::ostream& os, const Vector4Int& c);

    };

    // Global arithmetic operators

    ENGINE_API Vector4Int operator+(int f, const Vector4Int& vector);
    ENGINE_API Vector4Int operator-(int f, const Vector4Int& vector);
    ENGINE_API Vector4Int operator*(int f, const Vector4Int& vector);
    ENGINE_API Vector4Int operator/(int f, const Vector4Int& vector);

    // Global IO operators

    ENGINE_API std::ostream& operator<< (std::ostream& os, const Vector4Int& c);

}

#endif