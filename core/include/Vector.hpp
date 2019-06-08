#ifndef SEEDENGINE_INCLUDE_VECTOR_H_
#define SEEDENGINE_INCLUDE_VECTOR_H_

#include <string>
#include <sstream>
#include <stdexcept>
#include <cstdarg>
#include "Math.hpp"
#include "Property.hpp"

using std::string;

namespace seedengine {

    template<
        class V,
        typename T = float,
        unsigned int P = 3,
        typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0
    >
    class Vector {

    public:

        ~Vector() {

        }

        static float angle(const V& x, const V& y) {
            static_assert(std::is_base_of<Vector<V, T, P>, V>::value, "Class V must be a Vector type.");
            return math::acos(dot(x, y)) / magnitude(x) * magnitude(y);
        }

        static float distance(const V& p0, const V& p1) {
            static_assert(std::is_base_of<Vector<V, T, P>, V>::value, "Class V must be a Vector type.");
            return magnitude(p0 - p1);
        }

        static T dot(const V& x, const V& y) {
            static_assert(std::is_base_of<Vector<V, T, P>, V>::value, "Class V must be a Vector type.");
            T t = 0;
            for (int i = 0; i < P; i++) {
                t += x.elements_[i] * y.elements_[i];
            }
            return t;
        }

        static float magnitude(const V& x) {
            static_assert(std::is_base_of<Vector<V, T, P>, V>::value, "Class V must be a Vector type.");
            return math::sqrt(dot(x, x));
        }

        static V normalize(const V& x) {
            static_assert(std::is_base_of<Vector<V, T, P>, V>::value, "Class V must be a Vector type.");
            return x / magnitude(x);
        }

        static V reflect(const V& i, const V& n) {
            static_assert(std::is_base_of<Vector<V, T, P>, V>::value, "Class V must be a Vector type.");
            return i - 2 * dot(n, i) * n;
        }

        static V refract(const V& i, const V& n, const T& eta) {
            static_assert(std::is_base_of<Vector<V, T, P>, V>::value, "Class V must be a Vector type.");
            T t = 1 - eta * eta * (1 - dot(n, i) * dot(n, i));
            if (t < 0) return V();
            else return eta * i - (eta * dot(n, i) + math::sqrt(t)) * n;
        }



        V operator+(const V& vec) const {
            static_assert(std::is_base_of<Vector<V, T, P>, V>::value, "Class V must be a Vector type.");
            V v;
            for (int i = 0; i < P; i++) {
                v.elements_[i] = elements_[i] + vec.elements_[i];
            }
            return v;
        }

        V operator-(const V& vec) const {
            static_assert(std::is_base_of<Vector<V, T, P>, V>::value, "Class V must be a Vector type.");
            V v;
            for (int i = 0; i < P; i++) {
                v.elements_[i] = elements_[i] - vec.elements_[i];
            }
            return v;
        }

        V operator*(const V& vec) const {
            static_assert(std::is_base_of<Vector<V, T, P>, V>::value, "Class V must be a Vector type.");
            V v;
            for (int i = 0; i < P; i++) {
                v.elements_[i] = elements_[i] * vec.elements_[i];
            }
            return v;
        }

        V operator*(const T& scale) const {
            static_assert(std::is_base_of<Vector<V, T, P>, V>::value, "Class V must be a Vector type.");
            V v;
            for (int i = 0; i < P; i++) {
                v.elements_[i] = elements_[i] * scale;
            }
            return v;
        }

        V operator/(const V& vec) const {
            static_assert(std::is_base_of<Vector<V, T, P>, V>::value, "Class V must be a Vector type.");
            V v;
            for (int i = 0; i < P; i++) {
                v.elements_[i] = elements_[i] / vec.elements_[i];
            }
            return v;
        }

        V operator/(const T& scale) const {
            static_assert(std::is_base_of<Vector<V, T, P>, V>::value, "Class V must be a Vector type.");
            V v;
            for (int i = 0; i < P; i++) {
                v.elements_[i] = elements_[i] / scale;
            }
            return v;
        }

        T& operator[](const int& index) const {
            if (index < 0 || index >= P) throw std::out_of_range("Index is out of bounds.");
            return elements_[index];
        }

        bool operator==(const V& vec) const {
            static_assert(std::is_base_of<Vector<V, T, P>, V>::value, "Class V must be a Vector type.");
            bool e = true;
            for (int i = 0; i < P; i++) {
                e &= (elements_[i] == vec.elements_[i]);
            }
            return e;
        }

        operator string() {
            std::stringstream ss("<");
            for (int i = 0; i < P; i++) {
                ss << elements_[i];
                if (i < P - 1) ss << ", ";
            }
            ss << ">";
            return ss.str();

        }

        friend std::ostream& operator<<(std::ostream& os, const Vector<V, T, P>& c);

    protected:

        T elements_[P];

        Vector() : elements_{T()} {

        }

        Vector(T elements[P]) : elements_(elements) {

        }

    };

    template<
        class V,
        typename T = float,
        unsigned int P = 3
    >
    inline std::ostream& operator<<(std::ostream& os, const Vector<V, T, P>& v) {
        os << (string)v;
        return os;
    }


    class Vector2i : public Vector<Vector2i, int, 2> {

    public:

        Vector2i() : Vector2i(0) {}

        Vector2i(int c) : Vector2i(c, c) {}

        Vector2i(int x, int y) {
            this->x = x;
            this->y = y;
        }

        Property<int> x = Property<int>(
                0,
                GET(int) {
                    return this->elements_[0];
                },
                SET(int) {
                    return this->elements_[0] = value;
                }
            );
        Property<int> y = Property<int>(
                0,
                GET(int) {
                    return this->elements_[1];
                },
                SET(int) {
                    return this->elements_[1] = value;
                }
        );

    };

    class Vector2 : public Vector<Vector2, float, 2> {

    public:

        Vector2() : Vector2(0) {}

        Vector2(float c) : Vector2(c, c) {}

        Vector2(float x, float y) {
            this->x = x;
            this->y = y;
        }

        Property<float> x = Property<float>(
            0,
            GET(float) {
                return this->elements_[0];
            },
            SET(float) {
                return this->elements_[0] = value;
            }
        );
        Property<float> y = Property<float>(
            0,
            GET(float) {
                return this->elements_[1];
            },
            SET(float) {
                return this->elements_[1] = value;
            }
        );
    };

    class Vector3i : public Vector<Vector3i, int, 3> {

    public:

        Vector3i() : Vector3i(0) {}

        Vector3i(int c) : Vector3i(c, c, c) {}

        Vector3i(int x, int y, int z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        Property<int> x = Property<int>(
            0,
            GET(int) {
                return this->elements_[0];
            },
            SET(int) {
                return this->elements_[0] = value;
            }
        );
        Property<int> y = Property<int>(
            0,
            GET(int) {
                return this->elements_[1];
            },
            SET(int) {
                return this->elements_[1] = value;
            }
        );
        Property<int> z = Property<int>(
            0,
            GET(int) {
                return this->elements_[2];
            },
            SET(int) {
                return this->elements_[2] = value;
            }
        );

        static Vector3i cross(const Vector3i& a, const Vector3i& b) {
            return Vector3i(
                a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x
            );
        }
    };

    class Vector3 : public Vector<Vector3, float, 3> {

    public:

        Vector3() : Vector3(0) {}

        Vector3(float c) : Vector3(c, c, c) {}

        Vector3(float x, float y, float z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        Property<float> x = Property<float>(
            0,
            GET(float) {
                return this->elements_[0];
            },
            SET(float) {
                return this->elements_[0] = value;
            }
        );
        Property<float> y = Property<float>(
            0,
            GET(float) {
                return this->elements_[1];
            },
            SET(float) {
                return this->elements_[1] = value;
            }
        );
        Property<float> z = Property<float>(
            0,
            GET(float) {
                return this->elements_[2];
            },
            SET(float) {
                return this->elements_[2] = value;
            }
        );

        static Vector3 cross(const Vector3& a, const Vector3& b) {
            return Vector3(
                    a.y * b.z - a.z * b.y,
                    a.z * b.x - a.x * b.z,
                    a.x * b.y - a.y * b.x
                );
        }
    };

    class Vector4i : public Vector<Vector4i, int, 4> {

    public:

        Vector4i() : Vector4i(0) {}

        Vector4i(int c) : Vector4i(c, c, c, c) {}

        Vector4i(int x, int y, int z, int w) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }

        Property<int> x = Property<int>(
            0,
            GET(int) {
                return this->elements_[0];
            },
            SET(int) {
                return this->elements_[0] = value;
            }
        );
        Property<int> y = Property<int>(
            0,
            GET(int) {
                return this->elements_[1];
            },
            SET(int) {
                return this->elements_[1] = value;
            }
        );
        Property<int> z = Property<int>(
            0,
            GET(int) {
                return this->elements_[2];
            },
            SET(int) {
                return this->elements_[2] = value;
            }
        );
        Property<int> w = Property<int>(
            0,
            GET(int) {
                return this->elements_[3];
            },
            SET(int) {
                return this->elements_[3] = value;
            }
        );
    };

    class Vector4 : public Vector<Vector4, float, 4> {

    public:

        Vector4() : Vector4(0) {}

        Vector4(float c) : Vector4(c, c, c, c) {}

        Vector4(float x, float y, float z, float w) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }

        Property<float> x = Property<float>(
            0,
            GET(float) {
                return this->elements_[0];
            },
            SET(float) {
                return this->elements_[0] = value;
            }
        );
        Property<float> y = Property<float>(
            0,
            GET(float) {
                return this->elements_[1];
            },
            SET(float) {
                return this->elements_[1] = value;
            }
        );
        Property<float> z = Property<float>(
            0,
            GET(float) {
                return this->elements_[2];
            },
            SET(float) {
                return this->elements_[2] = value;
            }
        );
        Property<float> w = Property<float>(
            0,
            GET(float) {
                return this->elements_[3];
            },
            SET(float) {
                return this->elements_[3] = value;
            }
        );
    };

    namespace math {

        // lerp
        template <typename T = float, typename std::enable_if<std::is_base_of<Vector<T>, T>::value, int>::type = 0>
        inline T lerp(const T& a, const T& b, const float& t) { return a + t * (b - a); }

        // moveTowards
        template <typename T = float, typename std::enable_if<std::is_base_of<Vector<T>, T>::value, int>::type = 0>
        inline T moveTowards(const T& current, const T& target, const float& rate) {
            float mag = (target - current).magnitude;
            return (mag <= rate || mag == 0) ? target : current + ((target - current) / mag) * rate;
        }

    }

}

#endif