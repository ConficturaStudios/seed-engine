#ifndef SEEDENGINE_INCLUDE_MATRIX_H_
#define SEEDENGINE_INCLUDE_MATRIX_H_

#include <string>
#include <sstream>
#include <stdexcept>
#include <cstdarg>
#include "Math.hpp"
#include "Property.hpp"
#include "Vector.hpp"

namespace seedengine {

    //TODO: Finish wrapper matrix class.

    template<
        unsigned int C,
        unsigned int R,
        typename T = float,
        typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0
    >
    class Matrix final {

        //typedef Vector<C, T> col_t;
        //typedef Vector<R, T> row_t;

    public:

    protected:

    private:

        //col_t value[R];

    };

    typedef Matrix<2, 2, float> Matrix2x2;
    typedef Matrix<2, 3, float> Matrix2x3;
    typedef Matrix<2, 4, float> Matrix2x4;

    typedef Matrix<2, 2, float> Matrix2x2;
    typedef Matrix<2, 3, float> Matrix2x3;
    typedef Matrix<2, 4, float> Matrix2x4;

    typedef Matrix<3, 2, float> Matrix3x2;
    typedef Matrix<3, 3, float> Matrix3x3;
    typedef Matrix<3, 4, float> Matrix3x4;

    typedef Matrix<4, 2, float> Matrix4x2;
    typedef Matrix<4, 3, float> Matrix4x3;
    typedef Matrix<4, 4, float> Matrix4x4;

    typedef Matrix2x2 Matrix2;
    typedef Matrix3x3 Matrix3;
    typedef Matrix4x4 Matrix4;

}

#endif