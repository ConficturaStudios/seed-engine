/**
 * Matrix.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_MATH_MATRIX_H_
#define SEEDENGINE_INCLUDE_RUNTIME_MATH_MATRIX_H_

#include "MathAPI.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <cstdarg>
#include <cstring>

namespace seedengine {

    /**
     * @brief A R x C (row major) matrix of T objects
     * 
     * @tparam T The type stored in this matrix. Must be algebraic.
     * @tparam R The number of row in this matrix. Must be greater than or equal to 1.
     * @tparam C The number of columns in this matrix. Must be greater than or equal to 1.
     */
    template<typename T, std::size_t R, std::size_t C>
    class ENGINE_API Matrix final {

        template<typename, std::size_t, std::size_t>
        friend class Matrix;

        private:

        // Properties

            /** The values stored in this matrix. */
            T buffer[R][C]{};

        public:

        // Static traits

            /** The data type stored by this matrix. */
            using type = T;

            /** The number of rows for this matrix type. */
            static constexpr const std::size_t rows = R;

            /** The number of columns for this matrix type. */
            static constexpr const std::size_t columns = C;

            /** The total number of elements for this matrix type. */
            static constexpr const std::size_t size = rows * columns;

            /**
             * @brief Determines if this type constitutes a square matrix.
             * 
             * @return true If the number of rows == the number of columns.
             * @return false If the number of rows and columns are not equal.
             */
            static constexpr const bool isSquare() {
                static_assert(R > 0 && C > 0, "Matrices cannot have dimensions of size 0");
                return R == C;
            }

        // Constructors and destructor

            /**
             * @brief The default constructor for Matrix objects.
             * @details Constructs a new Matrix with default initialization for all elements.
             */
            Matrix() {
                static_assert(R > 0 && C > 0, "Matrices cannot have dimensions of size 0");
                for (std::size_t r = 0; r < R; r++) {
                    for (std::size_t c = 0; c < C; c++) {
                        this->buffer[r][c] = T();
                    }
                }
            }

            /**
             * @brief Constructs a new Matrix with all elements initialized to a set value.
             * 
             * @param value The value to initialize all elements to.
             */
            Matrix(const T& value) {
                static_assert(R > 0 && C > 0, "Matrices cannot have dimensions of size 0");
                for (std::size_t r = 0; r < R; r++) {
                    for (std::size_t c = 0; c < C; c++) {
                        this->buffer[r][c] = value;
                    }
                }
            }

            /**
             * @brief Construct a new Matrix with each alement copied from the passed buffer.
             * 
             * @param buffer The buffer to load.
             */
            Matrix(const T (&buffer)[R][C]) {
                static_assert(R > 0 && C > 0, "Matrices cannot have dimensions of size 0");
                for (std::size_t r = 0; r < R; r++) {
                    for (std::size_t c = 0; c < C; c++) {
                        this->buffer[r][c] = buffer[r][c];
                    }
                }
            }

            /**
             * @brief The copy constructor for Matrix objects.
             * @details Constructs a new Matrix by copying an existing Matrix.
             */
            Matrix(const Matrix<T, R, C>& ref) {
                static_assert(R > 0 && C > 0, "Matrices cannot have dimensions of size 0");
                for (std::size_t r = 0; r < R; r++) {
                    for (std::size_t c = 0; c < C; c++) {
                        this->buffer[r][c] = ref(r, c);
                    }
                }
            }
            
            /**
             * @brief The move constructor for Matrix objects.
             * @details Constructs a new Matrix by moving the data of a Matrix into this object.
             */
            Matrix(Matrix<T, R, C>&& ref) {
                static_assert(R > 0 && C > 0, "Matrices cannot have dimensions of size 0");
                for (std::size_t r = 0; r < R; r++) {
                    for (std::size_t c = 0; c < C; c++) {
                        this->buffer[r][c] = ref(r, c);
                    }
                }
            }

            /**
             * @brief The destructor for Matrix objects.
             * @details Called when an instance of Matrix is deleted.
             */
            ~Matrix() {
                
            }

        // Static Functions
        
            /**
             * @brief Returns the identity matrix for this type if it is square.
             * 
             * @tparam std::enable_if<(isSquare() && R > 0U)>::type SFINAE enable condition.
             * @return Matrix<T, R, C> The identity matrix for this type.
             */
            template<typename = typename std::enable_if<(isSquare() && R > 0U)>::type>
            static Matrix<T, R, C> identity() {
                Matrix<T, R, C> result = Matrix<T, R, C>();
                for (std::size_t i = 0; i < R; i++) {
                    result.buffer[i][i] = 1;
                }
                return result;
            }

        // Functions

            /**
             * @brief Creates the cofactor matrix of this matrix at a given index. This is the matrix of all
             *        elements not sharing a row or column with the one specified.
             * 
             * @tparam std::enable_if<(isSquare() && R > 1U)>::type SFINAE enable condition.
             * 
             * @param row The row to skip.
             * @param column The column to skip.
             * 
             * @return Matrix<T, R - 1U, C - 1U> The cofactor of the specified element.
             */
            template<typename = typename std::enable_if<(isSquare() && R > 1U)>::type>
            Matrix<T, R - 1U, C - 1U> cofactor(const std::size_t& row, const std::size_t& column) const {
                Matrix<T, R - 1U, C - 1U> result = Matrix<T, R - 1U, C - 1U>();

                std::size_t r_i = 0;
                std::size_t c_i = 0;
                for (std::size_t r = 0; r < R; r++) {
                    if (r != row) {
                        for (std::size_t c = 0; c < C; c++) {
                            if (c != column) {
                                result.buffer[r_i][c_i] = this->buffer[r][c] * (T)(((row + column) % 2 == 0) ? 1 : -1);
                                r_i++;
                            }
                        }
                        c_i = 0;
                        r_i++;
                    }
                }
                return result;
            }

            /**
             * @brief Gets the complete cofactor matrix of this matrix.
             * 
             * @tparam std::enable_if<(isSquare() && R > 1U)>::type SFINAE enable condition.
             * 
             * @return Matrix<T, R, C> This matrix's cofactor matrix.
             */
            template<typename = typename std::enable_if<(isSquare() && R > 1U)>::type>
            Matrix<T, R, C> cofactorMatrix() const {
                Matrix<T, R, C> result = Matrix<T, R, C>();
                for (std::size_t r = 0; r < R; r++) {
                    for (std::size_t c = 0; c < C; c++) {
                        result.buffer[r][c] = cofactor(r, c).determinant();
                    }
                }
                return result;
            }

            /**
             * @brief Gets the adjoint matrix of this matrix.
             * 
             * @tparam std::enable_if<(isSquare() && R > 1U)>::type 
             * @return Matrix<T, R, C> The adjoint matrix of this matrix.
             */
            template<typename = typename std::enable_if<(isSquare() && R > 1U)>::type>
            Matrix<T, R, C> adjointMatrix() const {
                return cofactorMatrix().transpose();
            }

            /**
             * @brief Calculates the determinant of this matrix if it is square.
             * 
             * @tparam std::enable_if<(isSquare() && R > 1U)>::type SFINAE enable condition.
             * 
             * @return T The determinant of this matrix.
             */
            template<typename = typename std::enable_if<(isSquare() && R > 1U)>::type>
            T determinant() const {
                /*if (R == 2U && C == 2U) {
                    return this->buffer[0][0] * this->buffer[1][1] - this->buffer[0][1] * this->buffer[1][0];
                }
                else {
                    T result = T();
                    for (std::size_t i = 0; i < C; i++) {

                        result += this->buffer[0][i] * cofactor(0, i).determinant();
                    }
                    return result;
                }*/
                return determinant<T>(*this);
            }

        private:

            /**
             * @brief Calculates the determinant of the passed matrix.
             * 
             * @tparam U The type stored in the passed matrix.
             * @tparam Size The size of each side of the passed matrix.
             * 
             * @param mat The matrix to evaluate
             * @return U The determinant of the matrix.
             */
            template<typename U, std::size_t Size>
            static U determinant(const Matrix<U, Size, Size>& mat) {
                U result = U();
                for (std::size_t i = 0; i < C; i++) {

                    result += mat.buffer[0][i] * determinant(mat.cofactor(0, i));
                }
                return result;
            }

            /**
             * @brief Calculates the determinant of the passed 2x2 matrix.
             * 
             * @tparam U The type stored in the passed matrix.
             * 
             * @param mat The matrix to evaluate
             * @return U The determinant of the matrix.
             */
            template<typename U>
            static U determinant(const Matrix<U, 2U, 2U>& mat) {
                return mat.buffer[0][0] * mat.buffer[1][1] - mat.buffer[0][1] * mat.buffer[1][0];
            }

            /**
             * @brief Calculates the determinant of the passed 1x1 matrix.
             * 
             * @tparam U The type stored in the passed matrix.
             * 
             * @param mat The matrix to evaluate
             * @return U The determinant of the matrix.
             */
            template<typename U>
            static U determinant(const Matrix<U, 1U, 1U>& mat) {
                return U();
            }

            /**
             * @brief Calculates the determinant of the passed 0x0 matrix.
             * 
             * @tparam U The type stored in the passed matrix.
             * 
             * @param mat The matrix to evaluate
             * @return U The determinant of the matrix.
             */
            template<typename U>
            static U determinant(const Matrix<U, 0U, 0U>& mat) {
                return U();
            }

        public:

            /**
             * @brief Returns the transpose of this matrix.
             * 
             * @return Matrix<T, R, C> This R x C matrix transposed to a C x R matrix.
             */
            Matrix<T, C, R> transpose() const {
                Matrix<T, C, R> result = Matrix<T, C, R>();

                for (std::size_t r = 0; r < R; r++) {
                    for (std::size_t c = 0; c < C; c++) {
                        result.buffer[c][r] = this->buffer[r][c];
                    }
                }

                return result;
            }

            /**
             * @brief Computes the product of each component of two matrices.
             * 
             * @param mat The matrix to multiply.
             * @return Matrix<T, R, C> A matrix with elements equal to the component products of the inputs.
             */
            Matrix<T, R, C> multpilyComponents(const Matrix<T, R, C>& mat) const {
                Matrix<T, R, C> result = Matrix<T, R, C>();

                for (std::size_t r = 0; r < R; r++) {
                    for (std::size_t c = 0; c < C; c++) {
                        result.buffer[r][c] = this->buffer[r][c] * mat.buffer[r][c];
                    }
                }

                return result;
            }

            /**
             * @brief Gets the inverse of this matrix.
             * 
             * @tparam std::enable_if<(isSquare() && R > 1U)>::type SFINAE enable condition.
             * 
             * @return Matrix<T, R, C> The inverse of this matrix.
             */
            template<typename = typename std::enable_if<(isSquare() && R > 1U)>::type>
            Matrix<T, R, C> inverse() const {
                T d = determinant();
                if (d == 0) return Matrix(); //TODO: Handle matrix inversion error when det = 0
                else {
                    return adjointMatrix() * (1 / d);
                }
            }

        // Arithmatic Operators

            /**
             * @brief Add two matrices.
             * 
             * @param rhs The right hand side.
             * @return Matrix<T, R, C> The sum of each matrix.
             */
            Matrix<T, R, C> operator+(const Matrix<T, R, C>& rhs) const {
                Matrix<T, R, C> result = Matrix<T, R, C>();

                for (std::size_t r = 0; r < R; r++) {
                    for (std::size_t c = 0; c < C; c++) {
                        result.buffer[r][c] = this->buffer[r][c] + rhs.buffer[r][c];
                    }
                }

                return result;
            }

            /**
             * @brief Subtract two matrices.
             * 
             * @param rhs The right hand side.
             * @return Matrix<T, R, C> The difference of each matrix.
             */
            Matrix<T, R, C> operator-(const Matrix<T, R, C>& rhs) const {
                Matrix<T, R, C> result = Matrix<T, R, C>();

                for (std::size_t r = 0; r < R; r++) {
                    for (std::size_t c = 0; c < C; c++) {
                        result.buffer[r][c] = this->buffer[r][c] - rhs.buffer[r][c];
                    }
                }

                return result;
            }

            /**
             * @brief The matrix multiplication of two matrices.
             * 
             * @tparam N The columns of the right hand side.
             * @param rhs The right hand side.
             * @return Matrix<T, R, N> The matrix product of two matrices.
             */
            template<std::size_t N>
            Matrix<T, R, N> operator*(const Matrix<T, C, N>& rhs) const {
                Matrix<T, R, N> result = Matrix<T, R, N>();

                for (std::size_t c = 0; c < N; c++) {
                    for (std::size_t r = 0; r < R; r++) {

                        T v = 0;
                        for (std::size_t i = 0; i < C; i++) {
                            v += this->buffer[r][i] * rhs.buffer[i][c];
                        }

                        result.buffer[r][c] = v;
                    }
                }

                return result;
            }

            /**
             * @brief The scalar product of a matrix and a float.
             * 
             * @param rhs The right hand side.
             * @return Matrix<T, R, C> This matrix scaled by a float.
             */
            Matrix<T, R, C> operator*(const T& rhs) const {
                Matrix<T, R, C> result = Matrix<T, R, C>();

                for (std::size_t r = 0; r < R; r++) {
                    for (std::size_t c = 0; c < C; c++) {
                        result.buffer[r][c] = this->buffer[r][c] * rhs;
                    }
                }

                return result;
            }

            template<typename, std::size_t, std::size_t>
            friend Matrix<T, R, C> operator*(const T& lhs, const Matrix<T, R, C>& rhs);

        // Accessor operators

            /**
             * @brief A getter for elements of this matrix.
             * 
             * @param row The row index to get.
             * @param column The column index to get.
             * @return T& The value at the specified position.
             */
            T& operator()(const std::size_t& row, const std::size_t& column) {
                if (row >= R || column >= C) throw std::out_of_range("Attempting to access out of range element.");
                return buffer[row][column];
            }

            /**
             * @brief A getter for elements of this matrix.
             * 
             * @param row The row index to get.
             * @param column The column index to get.
             * @return const T& The value at the specified position.
             */
            const T& operator()(const std::size_t& row, const std::size_t& column) const {
                if (row >= R || column >= C) throw std::out_of_range("Attempting to access out of range element.");
                return buffer[row][column];
            }

        // Assignment Operators

            /**
             * @brief The copy assignment operator for Matrix objects.
             * @details Reassigns the value of this object by copying the data of a Matrix into this object.
             */
            Matrix<T, R, C>& operator=(const Matrix<T, R, C>& ref) {
                for (std::size_t r = 0; r < R; r++) {
                    for (std::size_t c = 0; c < C; c++) {
                        this->buffer[r][c] = ref(r, c);
                    }
                }
                return *this;
            }

            /**
             * @brief The move assignment operator for Matrix objects.
             * @details Reassigns the value of this object by moving the data of a Matrix into this object.
             */
            Matrix<T, R, C>& operator=(Matrix<T, R, C>&& ref) {
                for (std::size_t r = 0; r < R; r++) {
                    for (std::size_t c = 0; c < C; c++) {
                        this->buffer[r][c] = ref(r, c);
                    }
                }
                return *this;
            }

        // Cast Operators

            operator std::string() const {
                std::stringstream ss("");
                ss << "[ ";
                for (std::size_t r = 0; r < R; r++) {
                    ss << "[";
                    for (std::size_t c = 0; c < C; c++) {
                        ss << this->buffer[r][c];
                        if (c < C - 1) ss << ", ";
                    }
                    ss << "]";
                    if (r < R - 1) ss << ", ";
                }
                ss << " ]";
                return ss.str();
            }

        // IO Operators

            template<typename, std::size_t, std::size_t>
            friend std::ostream& operator<<(std::ostream& os, const Matrix<T, R, C>& rhs);

    };

    // Global arithmatic operators

    template<typename T, std::size_t R, std::size_t C>
    Matrix<T, R, C> operator*(const T& lhs, const Matrix<T, R, C>& rhs) {
        return rhs * lhs;
    }

    // IO Operators

    template<typename T, std::size_t R, std::size_t C>
    std::ostream& operator<<(std::ostream& os, const Matrix<T, R, C>& rhs) {
        os << (String)rhs;
        return os;
    }

    // Typedefs

    /** A 1x1 float matrix. */
    typedef Matrix<float, 1, 1> Matrix1x1;
    /** A 1x2 float matrix. */
    typedef Matrix<float, 1, 2> Matrix1x2;
    /** A 1x3 float matrix. */
    typedef Matrix<float, 1, 3> Matrix1x3;
    /** A 1x4 float matrix. */
    typedef Matrix<float, 1, 4> Matrix1x4;

    /** A 2x1 float matrix. */
    typedef Matrix<float, 2, 1> Matrix2x1;
    /** A 2x2 float matrix. */
    typedef Matrix<float, 2, 2> Matrix2x2;
    /** A 2x3 float matrix. */
    typedef Matrix<float, 2, 3> Matrix2x3;
    /** A 2x4 float matrix. */
    typedef Matrix<float, 2, 4> Matrix2x4;

    /** A 3x1 float matrix. */
    typedef Matrix<float, 3, 1> Matrix3x1;
    /** A 3x2 float matrix. */
    typedef Matrix<float, 3, 2> Matrix3x2;
    /** A 3x3 float matrix. */
    typedef Matrix<float, 3, 3> Matrix3x3;
    /** A 3x4 float matrix. */
    typedef Matrix<float, 3, 4> Matrix3x4;

    /** A 4x1 float matrix. */
    typedef Matrix<float, 4, 1> Matrix4x1;
    /** A 4x2 float matrix. */
    typedef Matrix<float, 4, 2> Matrix4x2;
    /** A 4x3 float matrix. */
    typedef Matrix<float, 4, 3> Matrix4x3;
    /** A 4x4 float matrix. */
    typedef Matrix<float, 4, 4> Matrix4x4;

    /** A 1x1 float matrix. */
    typedef Matrix1x1 Matrix1;
    /** A 2x2 float matrix. */
    typedef Matrix2x2 Matrix2;
    /** A 3x3 float matrix. */
    typedef Matrix3x3 Matrix3;
    /** A 4x4 float matrix. */
    typedef Matrix4x4 Matrix4;

    /** A 1x1 int matrix. */
    typedef Matrix<int, 1, 1> Matrix1x1Int;
    /** A 1x2 int matrix. */
    typedef Matrix<int, 1, 2> Matrix1x2Int;
    /** A 1x3 int matrix. */
    typedef Matrix<int, 1, 3> Matrix1x3Int;
    /** A 1x4 int matrix. */
    typedef Matrix<int, 1, 4> Matrix1x4Int;

    /** A 2x1 int matrix. */
    typedef Matrix<int, 2, 1> Matrix2x1Int;
    /** A 2x2 int matrix. */
    typedef Matrix<int, 2, 2> Matrix2x2Int;
    /** A 2x3 int matrix. */
    typedef Matrix<int, 2, 3> Matrix2x3Int;
    /** A 2x4 int matrix. */
    typedef Matrix<int, 2, 4> Matrix2x4Int;

    /** A 3x1 int matrix. */
    typedef Matrix<int, 3, 1> Matrix3x1Int;
    /** A 3x2 int matrix. */
    typedef Matrix<int, 3, 2> Matrix3x2Int;
    /** A 3x3 int matrix. */
    typedef Matrix<int, 3, 3> Matrix3x3Int;
    /** A 3x4 int matrix. */
    typedef Matrix<int, 3, 4> Matrix3x4Int;

    /** A 4x1 int matrix. */
    typedef Matrix<int, 4, 1> Matrix4x1Int;
    /** A 4x2 int matrix. */
    typedef Matrix<int, 4, 2> Matrix4x2Int;
    /** A 4x3 int matrix. */
    typedef Matrix<int, 4, 3> Matrix4x3Int;
    /** A 4x4 int matrix. */
    typedef Matrix<int, 4, 4> Matrix4x4Int;

    /** A 1x1 int matrix. */
    typedef Matrix1x1 Matrix1Int;
    /** A 2x2 int matrix. */
    typedef Matrix2x2 Matrix2Int;
    /** A 3x3 int matrix. */
    typedef Matrix3x3 Matrix3Int;
    /** A 4x4 int matrix. */
    typedef Matrix4x4 Matrix4Int;

}

#endif