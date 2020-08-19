#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include "utils/types.h"

#include <Eigen/SparseCore>

namespace wfes {
    namespace sparsematrix{

        /**
         * @brief Abstract class that represents a Sparse Matrix.
         */
        class SparseMatrix {
            public: // Parammeters
                /**
                 * @brief Number of non-zero elements in the matrix.
                 */
                int num_non_zeros;
                /**
                 * @brief Number of rows in the matrix.
                 */
                int num_rows;
                /**
                 * @brief Number of columns in the matrix.
                 */
                int num_cols;

            public: // Constructors and destructors.
                /**
                 * @brief Empty constructor of a Sparse Matrix.
                 * @param numRows Number of rows in the matrix.
                 * @param numCols Number of columns in the matrix.
                 */
                SparseMatrix(int num_rows, int num_cols);

                /**
                 * @brief Create a Sparse Matrix containing only a padded diagonal.
                 * @param dim Number of rows in the matrix.
                 * @param x Value of the elements in the diagonal.
                 * @param padLeft Number of positions padded in the left.
                 * @return
                 */
                virtual SparseMatrix* LeftPaddedDiagonal(int dim, double x, int padLeft) = 0;

                /**
                 * @brief Destructor of a Sparse Matrix. Even when it is not used, it has to be defined.
                 */
                virtual ~SparseMatrix() {};

            public: // Append functions.

                /**
                 * @brief Append a row to a matrix from a vector specifying where a row starts in the vector and the size of the row.
                 * @param row Vector containing the row.
                 * @param col_start Position in the vector where the row starts.
                 * @param size Number of elements in the row.
                 */
                virtual void appendRow(dvec& row, int col_start, int size) = 0;

                /**
                 * @brief Append a chunk of a row to a matrix from a vector specifying where the row starts in the vector and where it has to be copied in the matrix.
                 * @param row Vector containing the chunk of the row.
                 * @param m0 Position in the matrix where the chunk has to be copied.
                 * @param r0 Position in the vector where the chunk starts.
                 * @param size Number of elements in the chunk.
                 */
                virtual void appendChunk(dvec& row, int m0, int r0, int size) = 0;

                /**
                 * @brief Append a value to the matrix in the position (i, j).
                 * @param value Value appended to the matrix.
                 * @param j Column of the appended element.
                 */
                virtual void appendValue(double value, int j) = 0;

            public: // Auxiliary functions.

                /**
                 * @brief Update currentRow and rowIndexStart for the next row.
                 */
                virtual void nextRow() = 0;

                /**
                 * @brief Print vectors rowIndex, data and cols.
                 */
                virtual void debugPrint() = 0;

                /**
                 * @brief Test if the matrix is approximatelly equal to another matrix using a tolerance value.
                 * @param rhs Another matrix.
                 * @param tol Tolerance value when comparing elements of the matrixes.
                 * @param verbose Show verbose information.
                 * @return
                 */
                virtual bool approxEquals(const SparseMatrix& rhs, double tol = 1e-10, bool verbose = false) = 0;

            public: // Convert data

                /**
                 * @brief Return the dense version of the matrix as an Eigen matrix.
                 * @return Matrix in dense form.
                 */
                virtual dmat dense() = 0;

                /**
                 * @brief Get a copy of the diagonal of the matrix inside a vector.
                 * @return Copy of the diagonal of the matrix.
                 */
                virtual dvec getDiagCopy() = 0;

                /**
                 * @brief Get a copy of a column of the matrix inside a vector.
                 * @param j Column that we want to copy.
                 * @return Copy of the column j.
                 */
                virtual dvec getColCopy(int j) = 0;

                /**
                 * @brief Get a copy of a row of the matrix inside a vector.
                 * @param i Row that we want to copy.
                 * @return Copy of the row i.
                 */
                virtual dvec getRowCopy(int i) = 0;

            public: //Operators

                /**
                 * @brief Multiply the matrix by a vector.
                 * @param x Vector to multiply by.
                 * @param transpose Convert the matrix to transpose.
                 * @return Vector resulting of calculating M*b.
                 */
                virtual dvec multiply(dvec& x, bool transpose = false) = 0;

                /**
                 * @brief Multiply the matrix by a vector a determined number of times. The result overwrites the vector.
                 * @param x Vector to multiply by.
                 * @param times Number of times that the multiplication is done.
                 * @param transpose Convert the matrix to transpose.
                 */
                virtual void multiplyInPlaceRep(dvec& x, int times, bool transpose = false) = 0;

                /**
                 * @brief Multiply matrix by another matrix.
                 * @param B Matrix to multiply by.
                 * @param transpose Convert the matrix to transpose.
                 * @return Matrix resulting of calculating M*B.
                 */
                virtual SparseMatrix* multiply(SparseMatrix& B, bool transpose = false) = 0;

                /**
                 * @brief Substract the matrix (Q) from an identity matrix (I) of same dimensions. (I - Q).
                 */
                virtual void subtractIdentity() = 0;

                /**
                 * @brief Get the element in the position i, j.
                 * @param i Row in which the element is.
                 * @param j Column in which the element is.
                 */
                virtual double search(int i, int j) = 0;

                /**
                 * @brief Set a value in the position (i, j).
                 * @param x Value to set in the matrix.
                 * @param i Position i of the matrix.
                 * @param j Position j of the matrix.
                 */
                virtual void setValue(double x, int i, int j) = 0;
            public: // I/O operators.

                /**
                 * @brief Save matrix into a file.
                 * @param path Path of the file.
                 */
                virtual void saveMarket(std::string path) = 0;

        };

    }
}

typedef wfes::sparsematrix::SparseMatrix smat;

#endif // SPARSEMATRIX_H
