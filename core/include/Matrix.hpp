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
        unsigned int R
    >
    class Matrix final {


    public:

        //float determinant() const;

        //Matrix<R, C> transpose() const;

        //Matrix<C, R> multpilyComponents(const Matrix<C, R>& mat) const;

        //template<typename std::enable_if<C == R, int>::type>
        //Matrix<C, R> inverse() const;

        //template<unsigned int N>
        //Matrix<C, N> operator*(const Matrix<R, N>& mat) const;

        //float[C] operator*(const float[R] v) const;

        //Matrix<C, R> operator*(const float& f) const;

    protected:

        float value[R][C];

    };

    typedef Matrix<2, 2> Matrix2x2;
    typedef Matrix<2, 3> Matrix2x3;
    typedef Matrix<2, 4> Matrix2x4;

    typedef Matrix<2, 2> Matrix2x2;
    typedef Matrix<2, 3> Matrix2x3;
    typedef Matrix<2, 4> Matrix2x4;

    typedef Matrix<3, 2> Matrix3x2;
    typedef Matrix<3, 3> Matrix3x3;
    typedef Matrix<3, 4> Matrix3x4;

    typedef Matrix<4, 2> Matrix4x2;
    typedef Matrix<4, 3> Matrix4x3;
    typedef Matrix<4, 4> Matrix4x4;

    typedef Matrix2x2 Matrix2;
    typedef Matrix3x3 Matrix3;
    typedef Matrix4x4 Matrix4;

}

#endif