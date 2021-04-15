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
#include <cstring>

// Done to fix minor macro definition in GCC library code
#undef minor

namespace seedengine {

// Forward declare Matrix

    template<typename, size_t, size_t>
    class Matrix;

/**
 * The base class of all matrix types containing common behavior and data. Should never
 * be instanced or used by client code, use Matrix<T, R, C> instead.
 * @tparam T The type of element stored in this matrix.
 * @tparam R The number of rows in this matrix.
 * @tparam C The number of columns in this matrix.
 */
    template <typename T, size_t R, size_t C>
    class ENGINE_API MatrixBase {

            // Check template argument validity
            static_assert(R > 0 && C > 0, "Matrices cannot have dimensions of size 0");
            static_assert(std::is_arithmetic_v<T>, "Matrices only support numeric types.");

        public:

            /** The type of element stored in this matrix. */
            using Type = T;
            /** The number of rows in this matrix. */
            static constexpr const size_t Rows = R;
            /** The number of columns in this matrix. */
            static constexpr const size_t Columns = C;
            /** The number of elements in this matrix. */
            static constexpr const size_t Size = R * C;

        protected:

            /** The type of a complete row of the matrix. */
            typedef T RowType[C];

            /** The buffer of elements stored in this matrix. */
            T m_buffer[R][C]{};

            // Constructors

            /**
             * Constructs a new matrix with 0 initialized values.
             */
            MatrixBase() noexcept = default;

            /**
             * Constructs a new MatrixBase with all elements initialized to the provided value.
             * @param value The value to initialize all elements to.
             */
            explicit MatrixBase(const T& value) noexcept {
                for (size_t r = 0; r < R; r++) {
                    for (size_t c = 0; c < C; c++) {
                        m_buffer[r][c] = value;
                    }
                }
            }

            /**
             * Constructs a new MatrixBase by copying the RxC array provided.
             * @param buffer The array to copy.
             */
            MatrixBase(const T (&buffer)[R][C]) noexcept {
                memcpy(m_buffer, buffer, sizeof(T) * Size);
            }

            /**
             * Copy constructs a new MatrixBase instance.
             * @param ref The MatrixBase to copy.
             */
            MatrixBase(const MatrixBase<T, R, C>& ref) noexcept {
                memcpy(m_buffer, ref.m_buffer, sizeof(T) * Size);
            }

            /**
             * Move constructs a new MatrixBase instance.
             * @param ref The MatrixBase to move from.
             */
            MatrixBase(MatrixBase<T, R, C>&& ref) noexcept {
                memcpy(m_buffer, ref.m_buffer, sizeof(T) * Size);
            }

        public:

            // Destructor

            /**
             * Called for every MatrixBase instance at destruction.
             */
            virtual ~MatrixBase() = default;

            // Static functions

            /**
             * Returns true if this type of matrix is square (R = C).
             * @return True if this matrix type is square.
             */
            [[nodiscard]] static constexpr bool IsSquare() {
                return R == C;
            }

            // Member functions

            /**
             * Transposes this matrix into a CxR matrix.
             * @return The transposition of this matrix.
             */
            [[nodiscard]] Matrix<T, C, R> transpose() const {
                Matrix<T, C, R> result;
                for (size_t r = 0; r < R; r++) {
                    for (size_t c = 0; c < C; c++) {
                        result[c][r] = m_buffer[r][c];
                    }
                }
                return result;
            }

            /**
             * Performs a per-element multiplication with another matrix for each corresponding element.
             * @param rhs The element to multiply against.
             * @return The per-element product of the two matrices.
             */
            [[nodiscard]] Matrix<T, R, C> multiplyComponents(const Matrix<T, R, C>& rhs) const {
                Matrix<T, R, C> result;
                for (size_t r = 0; r < R; r++) {
                    for (size_t c = 0; c < C; c++) {
                        result.m_buffer[r][c] = m_buffer[r][c] * rhs.m_buffer[r][c];
                    }
                }
                return result;
            }

            /**
             * Returns a matrix with values calculated using the values of this array passed though a positional
             * function. This function should produce a value from the current value, row index, and column index.
             * @param func The function to use for each element.
             * @return A matrix computed by applying func to each element of this matrix.
             */
            [[nodiscard]] Matrix<T, R, C> positionalFunc(T (*func)(T, size_t, size_t)) {
                Matrix<T, R, C> result;
                for (size_t r = 0; r < R; r++) {
                    for (size_t c = 0; c < C; c++) {
                        result[r][c] = func(m_buffer[r][c], r, c);
                    }
                }
                return result;
            }

            // Arithmetic operators

            /**
             * Adds this matrix with another.
             * @param rhs The matrix to add with.
             * @return The sum of this matrix and rhs.
             */
            [[nodiscard]] Matrix<T, R, C> operator+(const Matrix<T, R, C>& rhs) const {
                Matrix<T, R, C> result;
                for (size_t r = 0; r < R; r++) {
                    for (size_t c = 0; c < C; c++) {
                        // TODO: Evaluate SIMD options
                        result.m_buffer[r][c] = m_buffer[r][c] + rhs.m_buffer[r][c];
                    }
                }
                return result;
            }

            /**
             * Subtracts rhs from this matrix.
             * @param rhs The matrix to subtract.
             * @return The difference of this matrix and rhs.
             */
            [[nodiscard]] Matrix<T, R, C> operator-(const Matrix<T, R, C>& rhs) const {
                Matrix<T, R, C> result;
                for (size_t r = 0; r < R; r++) {
                    for (size_t c = 0; c < C; c++) {
                        result.m_buffer[r][c] = m_buffer[r][c] - rhs.m_buffer[r][c];
                    }
                }
                return result;
            }

            /**
             * Performs a matrix multiplication between this and a CxN matrix, returning a new RxN matrix.
             * @tparam N The number of columns in the right hand side of the product.
             * @param rhs The matrix to multiply with.
             * @return The RxN product of this matrix and rhs.
             */
            template <size_t N>
            [[nodiscard]] Matrix<T, R, N> operator*(const Matrix<T, C, N>& rhs) const {
                Matrix<T, R, N> result;
                for (size_t r = 0; r < R; r++) {
                    for (size_t n = 0; n < N; n++) {
                        for (size_t c = 0; c < C; c++) {
                            result[r][n] += m_buffer[r][c] * rhs[c][n];
                        }
                    }
                }
                return result;
            }

            /**
             * Calculates the scalar product of this matrix and a scalar value.
             * @param scale The scalar value to apply.
             * @return The scalar product of this matrix and scale.
             */
            [[nodiscard]] Matrix<T, R, C> operator*(T scale) const {
                Matrix<T, R, C> result;
                for (size_t r = 0; r < R; r++) {
                    for (size_t c = 0; c < C; c++) {
                        result.m_buffer[r][c] = m_buffer[r][c] * scale;
                    }
                }
                return result;
            }

            /**
             * Calculates the scalar product of this matrix and 1 divided by a scalar value.
             * @param scale The inverse of the scalar value to apply.
             * @return The scalar product of this matrix and 1 / scale.
             */
            [[nodiscard]] Matrix<T, R, C> operator/(T scale) const {
                Matrix<T, R, C> result;
                for (size_t r = 0; r < R; r++) {
                    for (size_t c = 0; c < C; c++) {
                        result.m_buffer[r][c] = m_buffer[r][c] / scale;
                    }
                }
                return result;
            }

            /**
             * Calculates the scalar product of this matrix and a scalar value.
             * @param lhs The scalar to apply.
             * @param rhs The matrix to scale.
             * @return The scalar product of rhs and lhs.
             */
            template <typename, size_t, size_t>
            [[nodiscard]] friend Matrix<T, R, C> operator*(T lhs, const Matrix<T, R, C>& rhs) {
                return rhs * lhs;
            }

            // Accessors

            /**
             * Accesses a specific element of this matrix by row and column index.
             * @param i The row index.
             * @param j The column index.
             * @return The element at [i, j].
             */
            [[nodiscard]] T& operator()(size_t i, size_t j) {
                return m_buffer[i][j];
            }

            /**
             * Accesses a specific element of this matrix by row and column index.
             * @param i The row index.
             * @param j The column index.
             * @return The element at [i, j].
             */
            [[nodiscard]] const T& operator()(size_t i, size_t j) const {
                return m_buffer[i][j];
            }

            /**
             * Gets the row with the specified index.
             * @param row The row index.
             * @return The row at the specified index.
             */
            [[nodiscard]] RowType& operator[](size_t row) {
                return m_buffer[row]; // TODO: Add debug assertions for range access
            }

            /**
             * Gets the row with the specified index.
             * @param row The row index.
             * @return The row at the specified index.
             */
            [[nodiscard]] const RowType& operator[](size_t row) const {
                return m_buffer[row];
            }

            // Comparison

            /**
             * Checks if this matrix is equal to another.
             * @tparam U The type of data stored in the other matrix.
             * @tparam R2 The number of rows in the other matrix.
             * @tparam C2 The number of columns in the other matrix.
             * @param rhs The matrix to compare with.
             * @return True if the matrices are equal.
             */
            template <typename U, size_t R2, size_t C2>
            [[nodiscard]] bool operator==(const MatrixBase<U, R2, C2>& rhs) const {
                if constexpr (R2 == R && C2 == C && std::is_same_v<T, U>) {
                    return memcmp(m_buffer, rhs.m_buffer, Size * sizeof(T)) == 0;
                } else return false;
            }

            /**
             * Checks if this matrix is not equal to another.
             * @tparam U The type of data stored in the other matrix.
             * @tparam R2 The number of rows in the other matrix.
             * @tparam C2 The number of columns in the other matrix.
             * @param rhs The matrix to compare with.
             * @return True if the matrices are not equal.
             */
            template <typename U, size_t R2, size_t C2>
            [[nodiscard]] bool operator!=(const MatrixBase<U, R2, C2>& rhs) const {
                if constexpr (R2 == R && C2 == C && std::is_same_v<T, U>) {
                    return memcmp(m_buffer, rhs.m_buffer, Size * sizeof(T)) != 0;
                } else return true;
            }

            // Conversion

            // TODO: Replace with ToString template defined in String.hpp
            [[nodiscard]] friend std::string ToString(const Matrix<T, R, C>& matrix) {
                std::stringstream ss("");
                ss << "[ ";
                for (size_t r = 0; r < R; r++) {
                    ss << "[";
                    for (size_t c = 0; c < C; c++) {
                        ss << matrix[r][c];
                        if (c < C - 1) ss << ", ";
                    }
                    ss << "]";
                    if (r < R - 1) ss << ", ";
                }
                ss << " ]";
                return ss.str();
            }

            // TODO: Add +=, -=, *= (T), and /= (T) operator overloads
    };

/**
 * A matrix of R rows and C columns of T typed elements.
 * @tparam T The type of element stored in this matrix.
 * @tparam R The number of rows in this matrix.
 * @tparam C The number of columns in this matrix.
 */
    template <typename T, size_t R, size_t C>
    struct ENGINE_API Matrix final : public MatrixBase<T, R, C> {

        /**
         * Constructs a new matrix with 0 initialized values.
         */
        Matrix() noexcept = default;
        /**
         * Constructs a new matrix with all elements initialized to the provided value.
         * @param value The value to initialize all elements to.
         */
        explicit Matrix(const T& value) noexcept : MatrixBase<T, R, C>(value) {}
        /**
         * Constructs a new matrix by copying the RxC array provided.
         * @param buffer The array to copy.
         */
        Matrix(const T (&buffer)[R][C]) noexcept : MatrixBase<T, R, C>(buffer) {}
        /**
         * Copy constructs a new matrix instance.
         * @param ref The matrix to copy.
         */
        Matrix(const Matrix<T, R, C>& ref) noexcept : MatrixBase<T, R, C>(ref) {}
        /**
         * Move constructs a new matrix instance.
         * @param ref The matrix to move from.
         */
        Matrix(Matrix<T, R, C>&& ref) noexcept : MatrixBase<T, R, C>(ref) {}
    };

/**
 * A 1x1 matrix of T typed elements.
 * @tparam T The type of elements stored by this matrix.
 */
    template <typename T>
    struct ENGINE_API Matrix<T, 1, 1> final : public MatrixBase<T, 1, 1> {

        /**
         * Constructs a new matrix with 0 initialized values.
         */
        Matrix() noexcept = default;

        /**
         * Constructs a new matrix with all elements initialized to the provided value.
         * @param value The value to initialize all elements to.
         */
        explicit Matrix(const T& value) noexcept : MatrixBase<T, 1, 1>(value) {}

        /**
         * Constructs a new matrix by copying the 1x1 array provided.
         * @param buffer The array to copy.
         */
        Matrix(const T (&buffer)[1][1]) noexcept : MatrixBase<T, 1, 1>(buffer) {}

        /**
         * Copy constructs a new matrix instance.
         * @param ref The matrix to copy.
         */
        Matrix(const Matrix<T, 1, 1>& ref) noexcept : MatrixBase<T, 1, 1>(ref) {}

        /**
         * Move constructs a new matrix instance.
         * @param ref The matrix to move from.
         */
        Matrix(Matrix<T, 1, 1>&& ref) noexcept : MatrixBase<T, 1, 1>(ref) {}

        /**
         * Returns the identity matrix for this square matrix type.
         * @return The identity matrix.
         */
        [[nodiscard]] static constexpr Matrix<T, 1, 1> Identity() {
            Matrix<T, 1, 1> matrix;
            matrix.m_buffer[0][0] = 1;
            return matrix;
        }

        /**
         * Returns true if this matrix is invertible.
         * @return True if this matrix is invertible.
         */
        [[nodiscard]] bool invertible() const {
            return determinant() != 0;
        }

        /**
         * Returns the inverse of this matrix if it exists, or a zero filled matrix if it does not.
         * @return The inverse of this matrix.
         */
        [[nodiscard]] Matrix<T, 1, 1> inverse() const {
            Matrix<T, 1, 1> matrix;
            T det = determinant();
            if (det != 0) // TODO: Handle non-invertible case
                matrix.m_buffer[0][0] = 1 / det;
            return matrix;
        }

        /**
         * Calculates and returns the determinant of this matrix.
         * @return The determinant of this matrix.
         */
        [[nodiscard]] T determinant() const {
            return this->m_buffer[0][0];
        }
    };

/**
 * A square matrix of size NxN with T typed elements.
 * @tparam T The type of element stored in this matrix.
 * @tparam N The number or rows or columns in this matrix.
 */
    template <typename T, size_t N>
    struct ENGINE_API Matrix<T, N, N> final : public MatrixBase<T, N, N> {

        /**
         * Constructs a new matrix with 0 initialized values.
         */
        Matrix() noexcept = default;

        /**
         * Constructs a new matrix with all elements initialized to the provided value.
         * @param value The value to initialize all elements to.
         */
        explicit Matrix(const T& value) noexcept : MatrixBase<T, N, N>(value) {}

        /**
         * Constructs a new matrix by copying the NxN array provided.
         * @param buffer The array to copy.
         */
        Matrix(const T (&buffer)[N][N]) noexcept : MatrixBase<T, N, N>(buffer) {}

        /**
         * Copy constructs a new matrix instance.
         * @param ref The matrix to copy.
         */
        Matrix(const Matrix<T, N, N>& ref) noexcept : MatrixBase<T, N, N>(ref) {}

        /**
         * Move constructs a new matrix instance.
         * @param ref The matrix to move from.
         */
        Matrix(Matrix<T, N, N>&& ref) noexcept : MatrixBase<T, N, N>(ref) {}

        /**
         * Returns the identity matrix for this square matrix type.
         * @return The identity matrix.
         */
        [[nodiscard]] static constexpr Matrix<T, N, N> Identity() {
            Matrix<T, N, N> matrix;
            for (size_t i = 0; i < N; i++) {
                matrix.m_buffer[i][i] = 1;
            }
            return matrix;
        }

        /**
         * Calculates the minor of the specified row and column.
         * @param row The row to exclude.
         * @param col The column to exclude.
         * @return The minor matrix of the specified row and column.
         */
        [[nodiscard]] Matrix<T, N - 1, N - 1> minorMatrix(size_t row, size_t col) const {
            Matrix<T, N - 1, N - 1> matrix;
            int r = 0;
            int c = 0;
            for (size_t i = 0; i < N; i++) {
                if (i != row) {
                    for (size_t j = 0; j < N; j++) {
                        if (j != col) {
                            matrix[r][c++] = this->m_buffer[i][j];
                        }
                    }
                    c = 0;
                    r++;
                }
            }
            return matrix;
        }

        /**
         * Returns the determinant of the minor matrix or the specified row and column.
         * @param row The row to exclude.
         * @param col The column to exclude.
         * @return The determinant of the minor matrix or the specified row and column.
         */
        [[nodiscard]] T minor(size_t row, size_t col) const {
            return minorMatrix(row, col).determinant();
        }

        /**
         * Returns the cofactor of the specified row and column.
         * @param row The row to consider.
         * @param col The column to consider.
         * @return The cofactor of the specified row and column.
         */
        [[nodiscard]] T cofactor(size_t row, size_t col) const {
            return (((row + col) % 2) ? -1 : 1) * minor(row, col);
        }

        /**
         * Returns the matrix of all cofactors of this matrix.
         * @return The matrix of all cofactors of this matrix.
         */
        [[nodiscard]] Matrix<T, N, N> cofactorMatrix() const {
            Matrix<T, N, N> result = Matrix<T, N, N>();
            for (size_t r = 0; r < N; r++) {
                for (size_t c = 0; c < N; c++) {
                    result.m_buffer[r][c] = cofactor(r, c);
                }
            }
            return result;
        }

        /**
         * Returns the adjoint of the matrix, equal to the transpose of the cofactor matrix.
         * @return The adjoint matrix of this matrix.
         */
        [[nodiscard]] Matrix<T, N, N> adjoint() const {
            return cofactorMatrix().transpose();
        }

        /**
         * Returns true if this matrix is invertible.
         * @return True if this matrix is invertible.
         */
        [[nodiscard]] bool invertible() const {
            return determinant() != 0;
        }

        /**
         * Returns the inverse of this matrix if it exists, or a zero filled matrix if it does not.
         * @return The inverse of this matrix.
         */
        [[nodiscard]] Matrix<T, N, N> inverse() const {
            Matrix<T, N, N> matrix;
            T det = determinant();
            if (det != 0) // TODO: Handle non-invertible case
                return adjoint() * (1 / det);
            return matrix;
        }

        /**
         * Calculates and returns the determinant of this matrix.
         * @return The determinant of this matrix.
         */
        [[nodiscard]] T determinant() const {
            if constexpr (N == 2)
                return this->m_buffer[0][0] * this->m_buffer[1][1] - this->m_buffer[0][1] * this->m_buffer[1][0];
            else {
                T result = 0;
                for (std::size_t i = 0; i < N; i++) {
                    result += this->m_buffer[0][i] * cofactor(0, i);
                }
                return result;
            }
        }
    };

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