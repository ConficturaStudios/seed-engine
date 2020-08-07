/**
 * Vector2Int.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_MATH_VECTOR2_INT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_MATH_VECTOR2_INT_H_

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
     * @brief A 2 Dimentsional integer vector with components x and y.
     *
     * @see #Vector2
     * @see #Vector3
     * @see #Vector4
     * @see #Vector3Int
     * @see #Vector4Int
     */
    class ENGINE_API Vector2Int final {

        protected:
        
            /** The number of components this vector type has. */
            static constexpr const int SIZE = 2;

        public:

            // Constructors

            /**
             * @brief Constructs a new Vector2Int initialized to the zero vector.
             * @details Constructs a new Vector2Int with x an y both initialized to a value of 0.
             */
            Vector2Int();

            /**
             * @brief Constructs a new Vector2Int with both x and y initialized to the specified value.
             * @details Constructs a new Vector2Int with both x and y initialized to the specified value.
             *
             * @param value The value to use when initializeing this vector.
             */
            Vector2Int(const int& value);

            /**
             * @brief Constructs a new Vector2Int from the specified values.
             * @details Constructs a new Vector2Int with x and y initialized to the specified values.
             *
             * @param x The value to initialize x to.
             * @param y The value to initialize y to.
             */
            Vector2Int(const int& x, const int& y);

            /**
             * @brief Construct a new Vector2Int from an existing int array.
             * @details Constructs a new Vector2Int with the buffer copied from the passed array.
             * 
             * @param buffer The array to initialize to.
             */
            Vector2Int(const int (&buffer)[SIZE]);

            /**
             * @brief Copy construct a new Vector2Int from an existing Vector2Int.
             * @details Constructs a new Vector2Int by copying the values stored in an exisiting Vector2Int.
             * 
             * @param vec The vector to copy.
             */
            Vector2Int(const Vector2Int& vec);

            /**
             * @brief Move construct a new Vector2Int from an existing Vector2Int.
             * @details Constructs a new Vector2Int by moving the values stored in an exisiting Vector2Int rvalue into this object.
             * 
             * @param vec The vector to move.
             */
            Vector2Int(Vector2Int&& vec);

            // Properties

            union {
                /** The elements of this vector in a raw buffer array. */
                int buffer[SIZE];
                struct {
                    /** The x component of this vector. */
                    int x;
                    /** The y component of this vector. */
                    int y;
                };
            };

            // Constants

            /** The 2D Up Vector (0, 1). */
            static const Vector2Int UP;
            /** The 2D Down Vector (0, -1). */
            static const Vector2Int DOWN;
            /** The 2D Left Vector (-1, 0). */
            static const Vector2Int LEFT;
            /** The 2D Right Vector (1, 0). */
            static const Vector2Int RIGHT;
            /** The 2D One Vector (1, 1). */
            static const Vector2Int ONE;
            /** The 2D Zero Vector (0, 0). */
            static const Vector2Int ZERO;

            // Static Functions

            /**
             * @brief Calculates the angle between two vectors in radians.
             *
             * @param v0 The first vector.
             * @param v1 The second vector.
             * @return float The angle between the vectors in radians.
             */
            static float angle(const Vector2Int& v0, const Vector2Int& v1);

            /**
             * @brief Calculates the distance between two vectors.
             *
             * @param v0 The first vector.
             * @param v1 The second vector.
             * @return float The distance between the two vectos.
             */
            static float distance(const Vector2Int& v0, const Vector2Int& v1);

            /**
             * @brief Calculates the dot product of two vectors.
             *
             * @param v0 The first vector.
             * @param v1 The second vector.
             * @return int The dot product the two vectos.
             */
            static int dot(const Vector2Int& v0, const Vector2Int& v1);

            /**
             * @brief Returns the magnitude (vector length) of the passed vector.
             *
             * @param v The vector to evaluate.
             * @return float The magnitude (vector length) of the vector.
             */
            static float magnitude(const Vector2Int& v);

            /**
             * @brief Returns the squared magnitude (vector length) of the passed vector.
             * @details Returns the squared magnitude (vector length) of the passed vector.
             *          This method is faster than magnitude() and is equivalent to dot(v, v).
             *
             * @param v The vector to evaluate.
             * @return int The squared magnitude (vector length) of the vector.
             */
            static int mag2(const Vector2Int& v);

            // Member Functions

            /**
             * @brief Gets the angle in radians between this vector and the specified vector.
             *
             * @param v The vector to check against.
             * @return float The angle in radians between the vectors.
             */
            float angle(const Vector2Int& v) const;

            /**
             * @brief Gets the distance between this vector and the specified vector.
             *
             * @param v The vector to check against.
             * @return float The distance between this vector and the specified vector.
             */
            float distance(const Vector2Int& v) const;

            /**
             * @brief Calculates the dot product between this vector and the specified vector.
             *
             * @param v The vector to compute the dot product with.
             * @return int The dot product of this vector and the specified vector.
             */
            int dot(const Vector2Int& v) const;

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

            int& operator[](const int& index);

            const int& operator[](const int& index) const;

            // Arithmatic operators

            Vector2Int operator+(const Vector2Int& vec) const;
            Vector2Int operator+(const int& f) const;
            friend ENGINE_API Vector2Int operator+(const int& f, const Vector2Int& vector);

            Vector2Int operator-(const Vector2Int& vec) const;
            Vector2Int operator-(const int& f) const;
            friend ENGINE_API Vector2Int operator+(const int& f, const Vector2Int& vector);

            Vector2Int operator/(const Vector2Int& vec) const;
            Vector2Int operator/(const int& f) const;
            friend ENGINE_API Vector2Int operator/(const int& f, const Vector2Int& vector);

            Vector2Int operator*(const Vector2Int& vec) const;
            Vector2Int operator*(const int& f) const;
            friend ENGINE_API Vector2Int operator*(const int& f, const Vector2Int& vector);

            // Boolean operators

            bool operator==(const Vector2Int& vec) const;

            bool operator!=(const Vector2Int& vec) const;

            // Assignment operators

            Vector2Int& operator=(const Vector2Int& vec);
            Vector2Int& operator=(const int& value);

            // Cast operators

            operator Vector2() const;
            operator Vector3() const;
            operator Vector4() const;

            operator Vector3Int() const;
            operator Vector4Int() const;

            operator Matrix1x2Int() const;
            operator Matrix1x3Int() const;
            operator Matrix1x4Int() const;
            
            operator Matrix2x1Int() const;
            operator Matrix3x1Int() const;
            operator Matrix4x1Int() const;

            operator std::string() const;

            // IO operators

            friend ENGINE_API std::ostream& operator<< (std::ostream& os, const Vector2Int& c);

    };

    // Global arithmatic operators

    ENGINE_API Vector2Int operator+(const int& f, const Vector2Int& vector);
    ENGINE_API Vector2Int operator-(const int& f, const Vector2Int& vector);
    ENGINE_API Vector2Int operator*(const int& f, const Vector2Int& vector);
    ENGINE_API Vector2Int operator/(const int& f, const Vector2Int& vector);

    // Global IO operators

    ENGINE_API std::ostream& operator<< (std::ostream& os, const Vector2Int& c);

}

#endif