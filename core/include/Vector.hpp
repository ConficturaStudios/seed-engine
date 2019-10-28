#ifndef SEEDENGINE_INCLUDE_VECTOR_H_
#define SEEDENGINE_INCLUDE_VECTOR_H_

#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstdarg>
#include "Math.hpp"

using std::string;

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
    class Vector2 final {

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
         * @param value The value to use when initializeing this vector.
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

        // Properties

        /** The x component of this vector. */
        float x;
        /** The y component of this vector. */
        float y;

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
         * @brief Gets the normalized version of this vector.
         * @details This function calculates the unit vector of length/magnitude 1 that points in the
         *          same direction as this vector.
         *
         * @return Vector2 The normalized version of this vector.
         */
        Vector2 normalize() const;

        // Accessor operators

        float& operator[](const int& index);

        const float& operator[](const int& index) const;

        // Arithmatic operators

        Vector2 operator+(const Vector2& vec) const;
        Vector2 operator+(const float& f) const;
        friend Vector2 operator+(const float& f, const Vector2& vector);

        Vector2 operator-(const Vector2& vec) const;
        Vector2 operator-(const float& f) const;
        friend Vector2 operator+(const float& f, const Vector2& vector);

        Vector2 operator/(const Vector2& vec) const;
        Vector2 operator/(const float& f) const;
        friend Vector2 operator/(const float& f, const Vector2& vector);

        Vector2 operator*(const Vector2& vec) const;
        Vector2 operator*(const float& f) const;
        friend Vector2 operator*(const float& f, const Vector2& vector);

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

        operator string() const;

        // IO operators

        friend std::ostream& operator<< (std::ostream& os, const Vector2& c);

    protected:

        /** An array of pointers used to reference the x and y properties with the [] operator. */
        float* elements_[2];
        /** The number of components this vector type has. */
        static const int SIZE = 2;

    };

    /**
     * @brief A 3 Dimentsional vector with components x, y, and z.
     *
     * @see #Vector2
     * @see #Vector4
     * @see #Vector2Int
     * @see #Vector3Int
     * @see #Vector4Int
     */
    class Vector3 final {

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

        // Properties

        /** The x component of this vector. */
        float x;
        /** The y component of this vector. */
        float y;
        /** The z component of this vector. */
        float z;

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
         * @brief Gets the normalized version of this vector.
         * @details This function calculates the unit vector of length/magnitude 1 that points in the
         *          same direction as this vector.
         *
         * @return Vector3 The normalized version of this vector.
         */
        Vector3 normalize() const;

        // Accessor operators

        float& operator[](const int& index);

        const float& operator[](const int& index) const;

        // Arithmatic operators

        Vector3 operator+(const Vector3& vec) const;
        Vector3 operator+(const float& f) const;
        friend Vector3 operator+(const float& f, const Vector3& vector);

        Vector3 operator-(const Vector3& vec) const;
        Vector3 operator-(const float& f) const;
        friend Vector3 operator+(const float& f, const Vector3& vector);

        Vector3 operator/(const Vector3& vec) const;
        Vector3 operator/(const float& f) const;
        friend Vector3 operator/(const float& f, const Vector3& vector);

        Vector3 operator*(const Vector3& vec) const;
        Vector3 operator*(const float& f) const;
        friend Vector3 operator*(const float& f, const Vector3& vector);

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

        operator string() const;

        // IO operators

        friend std::ostream& operator<< (std::ostream& os, const Vector3& c);

    protected:

        /** An array of pointers used to reference the x, y, and z properties with the [] operator. */
        float* elements_[3];
        /** The number of components this vector type has. */
        static const int SIZE = 3;

    };

    /**
     * @brief A 4 Dimentsional vector with components x, y, z, and w
     *
     * @see #Vector2
     * @see #Vector3
     * @see #Vector2Int
     * @see #Vector3Int
     * @see #Vector4Int
     */
    class Vector4 final {

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

        // Properties

        /** The x component of this vector. */
        float x;
        /** The y component of this vector. */
        float y;
        /** The z component of this vector. */
        float z;
        /** The w component of this vector. */
        float w;

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
        friend Vector4 operator+(const float& f, const Vector4& vector);

        Vector4 operator-(const Vector4& vec) const;
        Vector4 operator-(const float& f) const;
        friend Vector4 operator+(const float& f, const Vector4& vector);

        Vector4 operator/(const Vector4& vec) const;
        Vector4 operator/(const float& f) const;
        friend Vector4 operator/(const float& f, const Vector4& vector);

        Vector4 operator*(const Vector4& vec) const;
        Vector4 operator*(const float& f) const;
        friend Vector4 operator*(const float& f, const Vector4& vector);

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

        operator string() const;

        // IO operators

        friend std::ostream& operator<< (std::ostream& os, const Vector4& c);

    protected:

        /** An array of pointers used to reference the x, y, z, and w properties with the [] operator. */
        float* elements_[4];
        /** The number of components this vector type has. */
        static const int SIZE = 4;

    };

    /**
     * @brief A 2 Dimentsional integer vector with components x and y.
     *
     * @see #Vector2
     * @see #Vector3
     * @see #Vector4
     * @see #Vector3Int
     * @see #Vector4Int
     */
    class Vector2Int final {

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

        // Properties

        /** The x component of this vector. */
        int x;
        /** The y component of this vector. */
        int y;

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

        // Accessor operators

        int& operator[](const int& index);

        const int& operator[](const int& index) const;

        // Arithmatic operators

        Vector2Int operator+(const Vector2Int& vec) const;
        Vector2Int operator+(const int& f) const;
        friend Vector2Int operator+(const int& f, const Vector2Int& vector);

        Vector2Int operator-(const Vector2Int& vec) const;
        Vector2Int operator-(const int& f) const;
        friend Vector2Int operator+(const int& f, const Vector2Int& vector);

        Vector2Int operator/(const Vector2Int& vec) const;
        Vector2Int operator/(const int& f) const;
        friend Vector2Int operator/(const int& f, const Vector2Int& vector);

        Vector2Int operator*(const Vector2Int& vec) const;
        Vector2Int operator*(const int& f) const;
        friend Vector2Int operator*(const int& f, const Vector2Int& vector);

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

        operator string() const;

        // IO operators

        friend std::ostream& operator<< (std::ostream& os, const Vector2Int& c);

    protected:

        /** An array of pointers used to reference the x and y properties with the [] operator. */
        int* elements_[2];
        /** The number of components this vector type has. */
        static const int SIZE = 2;

    };

    /**
     * @brief A 3 Dimentsional integer vector with components x, y, and z.
     *
     * @see #Vector2
     * @see #Vector3
     * @see #Vector4
     * @see #Vector2Int
     * @see #Vector4Int
     */
    class Vector3Int final {

    public:

        // Constructors

        /**
         * @brief Constructs a new Vector3Int initialized to the zero vector.
         * @details Constructs a new Vector3Int with x, y, and z initialized to a value of 0.
         */
        Vector3Int();

        /**
         * @brief Constructs a new Vector3Int with x, y, and z initialized to the specified value.
         * @details Constructs a new Vector3Int with x, y, and z initialized to the specified value.
         *
         * @param value The value to use when initializeing this vector.
         */
        Vector3Int(const int& value);

        /**
         * @brief Constructs a new Vector3Int from the specified values.
         * @details Constructs a new Vector3Int with x, y, and z initialized to the specified values.
         *
         * @param x The value to initialize x to.
         * @param y The value to initialize y to.
         * @param z The value to initialize z to.
         */
        Vector3Int(const int& x, const int& y, const int& z);

        // Properties

        /** The x component of this vector. */
        int x;
        /** The y component of this vector. */
        int y;
        /** The z component of this vector. */
        int z;

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
        static float angle(const Vector3Int& v0, const Vector3Int& v1);

        /**
         * @brief Calculates the distance between two vectors.
         *
         * @param v0 The first vector.
         * @param v1 The second vector.
         * @return float The distance between the two vectos.
         */
        static float distance(const Vector3Int& v0, const Vector3Int& v1);

        /**
         * @brief Calculates the dot product of two vectors.
         *
         * @param v0 The first vector.
         * @param v1 The second vector.
         * @return int The dot product the two vectos.
         */
        static int dot(const Vector3Int& v0, const Vector3Int& v1);

        /**
         * @brief Takes the cross product of two vectors.
         *
         * @param v0 The first vector.
         * @param v1 The second vector.
         * @return Vector3Int The vector orthogonal to both v0 and v1.
         */
        static Vector3Int cross(const Vector3Int& v0, const Vector3Int& v1);

        /**
         * @brief Returns the magnitude (vector length) of the passed vector.
         *
         * @param v The vector to evaluate.
         * @return float The magnitude (vector length) of the vector.
         */
        static float magnitude(const Vector3Int& v);

        // Member Functions

        /**
         * @brief Gets the angle in radians between this vector and the specified vector.
         *
         * @param v The vector to check against.
         * @return float The angle in radians between the vectors.
         */
        float angle(const Vector3Int& v) const;

        /**
         * @brief Gets the distance between this vector and the specified vector.
         *
         * @param v The vector to check against.
         * @return float The distance between this vector and the specified vector.
         */
        float distance(const Vector3Int& v) const;

        /**
         * @brief Calculates the dot product between this vector and the specified vector.
         *
         * @param v The vector to compute the dot product with.
         * @return int The dot product of this vector and the specified vector.
         */
        int dot(const Vector3Int& v) const;

        /**
         * @brief Calculates the cross product between this vector and the specified vector.
         *
         * @param v0 The first vector.
         * @param v1 The second vector.
         * @return Vector3Int The vector orthogonal to both this and v.
         */
        Vector3Int cross(const Vector3Int& v) const;

        /**
         * @brief Gets the magnitude (vector length) of this vector.
         *
         * @return float The magnitude (vector length) of this vector.
         */
        float magnitude() const;

        // Accessor operators

        int& operator[](const int& index);

        const int& operator[](const int& index) const;

        // Arithmatic operators

        Vector3Int operator+(const Vector3Int& vec) const;
        Vector3Int operator+(const int& f) const;
        friend Vector3Int operator+(const int& f, const Vector3Int& vector);

        Vector3Int operator-(const Vector3Int& vec) const;
        Vector3Int operator-(const int& f) const;
        friend Vector3Int operator+(const int& f, const Vector3Int& vector);

        Vector3Int operator/(const Vector3Int& vec) const;
        Vector3Int operator/(const int& f) const;
        friend Vector3Int operator/(const int& f, const Vector3Int& vector);

        Vector3Int operator*(const Vector3Int& vec) const;
        Vector3Int operator*(const int& f) const;
        friend Vector3Int operator*(const int& f, const Vector3Int& vector);

        // Boolean operators

        bool operator==(const Vector3Int& vec) const;

        bool operator!=(const Vector3Int& vec) const;

        // Assignment operators

        Vector3Int& operator=(const Vector3Int& vec);
        Vector3Int& operator=(const int& value);

        // Cast operators

        operator Vector2() const;
        operator Vector3() const;
        operator Vector4() const;

        operator Vector2Int() const;
        operator Vector4Int() const;

        operator string() const;

        // IO operators

        friend std::ostream& operator<< (std::ostream& os, const Vector3Int& c);

    protected:

        /** An array of pointers used to reference the x, y, and z properties with the [] operator. */
        int* elements_[3];
        /** The number of components this vector type has. */
        static const int SIZE = 3;

    };

    /**
     * @brief A 4 Dimentsional integer vector with components x, y, z, and w
     *
     * @see #Vector2
     * @see #Vector3
     * @see #Vector4
     * @see #Vector2Int
     * @see #Vector3Int
     */
    class Vector4Int final {

    public:

        // Constructors

        /**
         * @brief Constructs a new Vector4Int initialized to the zero vector.
         * @details Constructs a new Vector4Int with x, y, z, and w initialized to a value of 0.
         */
        Vector4Int();

        /**
         * @brief Constructs a new Vector4Int with x, y, z, and w initialized to the specified value.
         * @details Constructs a new Vector4Int with x, y, z, and w initialized to the specified value.
         *
         * @param value The value to use when initializeing this vector.
         */
        Vector4Int(const int& value);

        /**
         * @brief Constructs a new Vector4Int from the specified values.
         * @details Constructs a new Vector4Int with x, y, z, and w initialized to the specified values.
         *
         * @param x The value to initialize x to.
         * @param y The value to initialize y to.
         * @param z The value to initialize z to.
         * @param w The value to initialize w to.
         */
        Vector4Int(const int& x, const int& y, const int& z, const int& w);

        // Properties

        /** The x component of this vector. */
        int x;
        /** The y component of this vector. */
        int y;
        /** The z component of this vector. */
        int z;
        /** The w component of this vector. */
        int w;

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
         * @return float The distance between the two vectos.
         */
        static float distance(const Vector4Int& v0, const Vector4Int& v1);

        /**
         * @brief Calculates the dot product of two vectors.
         *
         * @param v0 The first vector.
         * @param v1 The second vector.
         * @return int The dot product the two vectos.
         */
        static int dot(const Vector4Int& v0, const Vector4Int& v1);

        /**
         * @brief Returns the magnitude (vector length) of the passed vector.
         *
         * @param v The vector to evaluate.
         * @return float The magnitude (vector length) of the vector.
         */
        static float magnitude(const Vector4Int& v);

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

        // Accessor operators

        int& operator[](const int& index);

        const int& operator[](const int& index) const;

        // Arithmatic operators

        Vector4Int operator+(const Vector4Int& vec) const;
        Vector4Int operator+(const int& f) const;
        friend Vector4Int operator+(const int& f, const Vector4Int& vector);

        Vector4Int operator-(const Vector4Int& vec) const;
        Vector4Int operator-(const int& f) const;
        friend Vector4Int operator+(const int& f, const Vector4Int& vector);

        Vector4Int operator/(const Vector4Int& vec) const;
        Vector4Int operator/(const int& f) const;
        friend Vector4Int operator/(const int& f, const Vector4Int& vector);

        Vector4Int operator*(const Vector4Int& vec) const;
        Vector4Int operator*(const int& f) const;
        friend Vector4Int operator*(const int& f, const Vector4Int& vector);

        // Boolean operators

        bool operator==(const Vector4Int& vec) const;

        bool operator!=(const Vector4Int& vec) const;

        // Assignment operators

        Vector4Int& operator=(const Vector4Int& vec);
        Vector4Int& operator=(const int& value);

        // Cast operators

        operator Vector2() const;
        operator Vector3() const;
        operator Vector4() const;

        operator Vector2Int() const;
        operator Vector3Int() const;

        operator string() const;

        // IO operators

        friend std::ostream& operator<< (std::ostream& os, const Vector4Int& c);

    protected:

        /** An array of pointers used to reference the x, y, z, and w properties with the [] operator. */
        int* elements_[4];
        /** The number of components this vector type has. */
        static const int SIZE = 4;

    };

    // Global arithmatic operators

    Vector2 operator+(const float& f, const Vector2& vector);
    Vector2 operator-(const float& f, const Vector2& vector);
    Vector2 operator*(const float& f, const Vector2& vector);
    Vector2 operator/(const float& f, const Vector2& vector);

    Vector3 operator+(const float& f, const Vector3& vector);
    Vector3 operator-(const float& f, const Vector3& vector);
    Vector3 operator*(const float& f, const Vector3& vector);
    Vector3 operator/(const float& f, const Vector3& vector);

    Vector4 operator+(const float& f, const Vector4& vector);
    Vector4 operator-(const float& f, const Vector4& vector);
    Vector4 operator*(const float& f, const Vector4& vector);
    Vector4 operator/(const float& f, const Vector4& vector);

    Vector2Int operator+(const float& f, const Vector2Int& vector);
    Vector2Int operator-(const float& f, const Vector2Int& vector);
    Vector2Int operator*(const float& f, const Vector2Int& vector);
    Vector2Int operator/(const float& f, const Vector2Int& vector);

    Vector3Int operator+(const float& f, const Vector3Int& vector);
    Vector3Int operator-(const float& f, const Vector3Int& vector);
    Vector3Int operator*(const float& f, const Vector3Int& vector);
    Vector3Int operator/(const float& f, const Vector3Int& vector);

    Vector4Int operator+(const float& f, const Vector4Int& vector);
    Vector4Int operator-(const float& f, const Vector4Int& vector);
    Vector4Int operator*(const float& f, const Vector4Int& vector);
    Vector4Int operator/(const float& f, const Vector4Int& vector);

    // Global IO operators

    std::ostream& operator<< (std::ostream& os, const Vector2& c);
    std::ostream& operator<< (std::ostream& os, const Vector3& c);
    std::ostream& operator<< (std::ostream& os, const Vector4& c);
    std::ostream& operator<< (std::ostream& os, const Vector2Int& c);
    std::ostream& operator<< (std::ostream& os, const Vector3Int& c);
    std::ostream& operator<< (std::ostream& os, const Vector4Int& c);

}
#endif