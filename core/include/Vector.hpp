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
        typename T = float,
        unsigned int P = 3,
        typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0
    >
    class VectorBase {

    public:

        ~VectorBase() {

        }

        static float angle(const VectorBase<T, 3>& x, const VectorBase<T, 3>& y) {
            return math::acos(dot(x, y)) / magnitude(x) * magnitude(y);
        }

        static VectorBase<T, 3> cross(const VectorBase<T, 3>& x, const VectorBase<T, 3>& y) {
            return VectorBase(new T[3] {
                    x[1] * y[2] - x[2] * y[1],
                    x[2] * y[0] - x[0] * y[2],
                    x[0] * y[1] - x[1] * y[0]
                });
        }

        static float distance(const VectorBase<T, P>& p0, const VectorBase<T, P>& p1) {
            return magnitude(p0 - p1);
        }

        static T dot(const VectorBase<T, P>& x, const VectorBase<T, P>& y) {
            T t = 0;
            for (int i = 0; i < P; i++) {
                t += x.elements_[i] * y.elements_[i];
            }
            return v;
        }

        static float magnitude(const VectorBase<T, P>& x) {
            return math::sqrt(dot(x, x));
        }

        static VectorBase<T, P> normalize(const VectorBase<T, P>& x) {
            return x / magnitude(x);
        }

        static VectorBase<T, P> reflect(const VectorBase<T, P>& i, const VectorBase<T, P>& n) {
            return i - 2 * dot(n, i) * n;
        }

        static VectorBase<T, P> refract(const VectorBase<T, P>& i, const VectorBase<T, P>& n, const T& eta) {
            T t = 1 - eta * eta * (1 - dot(n, i) * dot(n, i));
            if (t < 0) return VectorBase<T, P>();
            else return eta * i - (eta * dot(n, i) + math::sqrt(t)) * n;
        }



        VectorBase<T, P> operator+(const VectorBase<T, P>& vec) {
            VectorBase<T, P> v;
            for (int i = 0; i < P; i++) {
                v.elements_[i] = elements_[i] + vec.elements_[i];
            }
            return v;
        }

        VectorBase<T, P> operator-(const VectorBase<T, P>& vec) {
            VectorBase<T, P> v;
            for (int i = 0; i < P; i++) {
                v.elements_[i] = elements_[i] - vec.elements_[i];
            }
            return v;
        }

        VectorBase<T, P> operator*(const VectorBase<T, P>& vec) {
            VectorBase<T, P> v;
            for (int i = 0; i < P; i++) {
                v.elements_[i] = elements_[i] * vec.elements_[i];
            }
            return v;
        }

        VectorBase<T, P> operator*(const T& scale) {
            VectorBase<T, P> v;
            for (int i = 0; i < P; i++) {
                v.elements_[i] = elements_[i] * scale;
            }
            return v;
        }

        VectorBase<T, P> operator/(const VectorBase<T, P>& vec) {
            VectorBase<T, P> v;
            for (int i = 0; i < P; i++) {
                v.elements_[i] = elements_[i] / vec.elements_[i];
            }
            return v;
        }

        VectorBase<T, P> operator/(const T& scale) {
            VectorBase<T, P> v;
            for (int i = 0; i < P; i++) {
                v.elements_[i] = elements_[i] / scale;
            }
            return v;
        }

        T& operator[](const int& index) {
            if (index < 0 || index >= P) throw std::out_of_range("Index is out of bounds.");
            return elements_[index];
        }

        bool operator==(const VectorBase<T, P>& vec) {
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

        template <int U = 2>
        operator VectorBase<T, U>() {
            VectorBase<T, U> u;
            for (int i = 0; i < U; i++) {
                if (i < P) u.elements_[i] = elements_[i];
                else u.elements_[i] = T();
            }
            return u;
        }

    protected:

        T elements_[P];

        VectorBase() : elements_{T()} {

        }

        VectorBase(T elements[P]) : elements_(elements) {

        }

    };

    class Vector2i : public VectorBase<int, 2> {

    public:

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

    class Vector2 : public VectorBase<float, 2> {

    public:

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

    class Vector3i : public VectorBase<int, 3> {

    public:

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
    };

    class Vector3 : public VectorBase<float, 3> {

    public:

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
    };

    class Vector4i : public VectorBase<int, 4> {

    public:

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

    class Vector4 : public VectorBase<float, 4> {

    public:

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

}

#endif