#ifndef SEEDENGINE_INCLUDE_VECTOR_H_
#define SEEDENGINE_INCLUDE_VECTOR_H_

#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstdarg>
#include "Math.hpp"
#include "Property.hpp"

using std::string;

namespace seedengine {

    //TODO: Finish class specializations for vector class.

    template <unsigned int P, typename T> class VectorBase {

    protected:

        // The elements of this vector.
        T elements_[P];

        // --- Constructors ---

        VectorBase() : elements_{ T() } {

        }

        VectorBase(T elements[P]) : elements_(elements) {

        }

        template<typename... Args>
        VectorBase(Args&& ... args) : elements_{ T(args)... } {
            static_assert(sizeof...(Args) == P, "Invalid number of constructor arguments.");
        }

    };

    template <typename T> class VectorBase<2, T> {

    public:

        Property<T> x = Property<T>(
            0,
            GET(T) {
                return this->elements_[0];
            },
            SET(T) {
                return this->elements_[0] = value;
            }
        );
        Property<T> y = Property<T>(
            0,
            GET(T) {
                return this->elements_[1];
            },
            SET(T) {
                return this->elements_[1] = value;
            }
        );

    protected:

        // The elements of this vector.
        T elements_[2];

        // --- Constructors ---

        VectorBase() : elements_{ T() } {

        }

        VectorBase(T elements[2]) : elements_(elements) {

        }

        template<typename... Args>
        VectorBase(Args&& ... args) : elements_{ T(args)... } {
            static_assert(sizeof...(Args) == 2, "Invalid number of constructor arguments.");
        }

    };

    template <typename T> class VectorBase<3, T> {

    public:

        Property<T> x = Property<T>(
            0,
            GET(T) {
                return this->elements_[0];
            },
            SET(T) {
                return this->elements_[0] = value;
            }
        );
        Property<T> y = Property<T>(
            0,
            GET(T) {
                return this->elements_[1];
            },
            SET(T) {
                return this->elements_[1] = value;
            }
        );
        Property<T> z = Property<T>(
            0,
            GET(T) {
                return this->elements_[2];
            },
            SET(T) {
                return this->elements_[2] = value;
            }
        );

    protected:

        // The elements of this vector.
        T elements_[3];

        // --- Constructors ---

        VectorBase() : elements_{ T() } {

        }

        VectorBase(T elements[3]) : elements_(elements) {

        }

        template<typename... Args>
        VectorBase(Args&& ... args) : elements_{ T(args)... } {
            static_assert(sizeof...(Args) == 3, "Invalid number of constructor arguments.");
        }

    };

    template <typename T> class VectorBase<4, T> {

    public:

        Property<T> x = Property<T>(
            0,
            GET(T) {
                return this->elements_[0];
            },
            SET(T) {
                return this->elements_[0] = value;
            }
        );
        Property<T> y = Property<T>(
            0,
            GET(T) {
                return this->elements_[1];
            },
            SET(T) {
                return this->elements_[1] = value;
            }
        );
        Property<T> z = Property<T>(
            0,
            GET(T) {
                return this->elements_[2];
            },
            SET(T) {
                return this->elements_[2] = value;
            }
        );
        Property<T> w = Property<T>(
            0,
            GET(T) {
                return this->elements_[3];
            },
            SET(T) {
                return this->elements_[3] = value;
            }
        );

    protected:

        // The elements of this vector.
        T elements_[4];

        // --- Constructors ---

        VectorBase() : elements_{ T() } {

        }

        VectorBase(T elements[4]) : elements_(elements) {

        }

        template<typename... Args>
        VectorBase(Args&& ... args) : elements_{ T(args)... } {
            static_assert(sizeof...(Args) == 4, "Invalid number of constructor arguments.");
        }

    };


    template<
        unsigned int P,
        typename T = float,
        typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0
    >
    class Vector final : public VectorBase<P, T> {

        //TODO: Add x, y, z, w properties in orthogonal vector class specializations
        //TODO: Replace inheritance for VectorN[i] classes with typedefs
        //TODO: Remove template parameter V

        static_assert(P > 0, "Dimension must be greater than 0");

        typedef Vector<P, T> VectorType;

    public:

        // --- Constructors ---

        //TODO: Fix unix base constructor errors.

        Vector() : VectorBase<P, T>() {

        }

        Vector(T elements[P]) : VectorBase<P, T>(elements) {

        }

        template<typename... Args>
        Vector(Args&& ... args) : VectorBase<P, T>(T(args)...) {

        }

        // --- Static Functions ---

        static float angle(const VectorType& v0, const VectorType& v1) {
            return math::acos(dot(v0, v1)) / (magnitude(v0) * magnitude(v1));
        }

        static float distance(const VectorType& v0, const VectorType& v1) {
            return magnitude(v0 - v1);
        }

        static T dot(const VectorType& v0, const VectorType& v1) {
            T t = 0;
            for (int i = 0; i < P; i++) {
                t += v0.elements_[i] * v1.elements_[i];
            }
            return t;
        }

        static float magnitude(const VectorType& v) {
            return math::sqrt(dot(v, v));
        }

        static VectorType normalize(const VectorType& v) {
            return v / magnitude(v);
        }

        static VectorType reflect(const VectorType& i, const VectorType& n) {
            return i - 2 * dot(n, i) * n;
        }

        static VectorType refract(const VectorType& i, const VectorType& n, const T& eta) {
            T t = 1 - eta * eta * (1 - dot(n, i) * dot(n, i));
            if (t < 0) return VectorType();
            else return eta * i - (eta * dot(n, i) + math::sqrt(t)) * n;
        }

        // --- Member Functions ---

        inline float angle(const VectorType& v) {
            return angle(*this, v);
        }

        inline float distance(const VectorType& v) {
            return distance(*this, v);
        }

        inline T dot(const VectorType& v) {
            return dot(*this, v);
        }

        inline float magnitude() {
            return magnitude(*this);
        }

        inline VectorType normalize() {
            return normalize(*this);
        }

        // --- Template Dependent Methods ---

        static VectorType cross(const VectorType& a, const VectorType& b) {
            static_assert(P == 3, "The cross product can only be applied to a 3 dimensional vector.");
            return VectorType(
                a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x
            );
        }

        inline VectorType cross(const VectorType & v) {
            static_assert(P == 3, "The cross product can only be applied to a 3 dimensional vector.");
            return cross(*this, v);
        }

        // --- Operators ---

        VectorType operator+(const VectorType& vec) const {
            VectorType v;
            for (int i = 0; i < P; i++) {
                v.elements_[i] = this->elements_[i] + vec.elements_[i];
            }
            return v;
        }

        VectorType operator-(const VectorType& vec) const {
            VectorType v;
            for (int i = 0; i < P; i++) {
                v.elements_[i] = this->elements_[i] - vec.elements_[i];
            }
            return v;
        }

        VectorType operator*(const VectorType& vec) const {
            VectorType v;
            for (int i = 0; i < P; i++) {
                v.elements_[i] = this->elements_[i] * vec.elements_[i];
            }
            return v;
        }

        VectorType operator*(const T& scale) const {
            VectorType v;
            for (int i = 0; i < P; i++) {
                v.elements_[i] = this->elements_[i] * scale;
            }
            return v;
        }

        VectorType operator/(const VectorType& vec) const {
            VectorType v;
            for (int i = 0; i < P; i++) {
                v.elements_[i] = this->elements_[i] / vec.elements_[i];
            }
            return v;
        }

        VectorType operator/(const T& scale) const {
            VectorType v;
            for (int i = 0; i < P; i++) {
                v.elements_[i] = this->elements_[i] / scale;
            }
            return v;
        }

        T& operator[](const int& index) const {
            if (index < 0 || index >= P) throw std::out_of_range("Index is out of bounds.");
            return this->elements_[index];
        }

        bool operator==(const VectorType& vec) const {
            bool e = true;
            for (int i = 0; i < P; i++) {
                e &= (this->elements_[i] == vec.elements_[i]);
            }
            return e;
        }

        bool operator!=(const VectorType& vec) const {
            return !(*this == vec);
        }

        operator string() {
            std::stringstream ss("<");
            for (int i = 0; i < P; i++) {
                ss << this->elements_[i];
                if (i < P - 1) ss << ", ";
            }
            ss << ">";
            return ss.str();

        }

        friend std::ostream& operator<<(const std::ostream& os, const VectorType& c);

    };

    typedef Vector<2, int  > Vector2i;
    typedef Vector<2, float> Vector2;
    typedef Vector<3, int  > Vector3i;
    typedef Vector<3, float> Vector3;
    typedef Vector<4, int  > Vector4i;
    typedef Vector<4, float> Vector4;

    template<
        unsigned int P,
        typename T = float
    >
    inline std::ostream& operator<<(const std::ostream& os, const Vector<P, T>& v) {
        os << (string)v;
        return os;
    }

    namespace math {

        // lerp
        template<
            unsigned int P,
            typename T = float,
            typename std::enable_if<std::is_arithmetic<T>::value, int>::type
        >
        inline T lerp(const Vector<P, T>& a, const Vector<P, T>& b, const float& t) { return a + t * (b - a); }

        // moveTowards
        template<
            unsigned int P,
            typename T = float,
            typename std::enable_if<std::is_arithmetic<T>::value, int>::type
        >
        inline T moveTowards(const Vector<P, T>& current, const Vector<P, T>& target, const float& rate) {
            float mag = (target - current).magnitude;
            return (mag <= rate || mag == 0) ? target : current + ((target - current) / mag) * rate;
        }

    }

}

#endif