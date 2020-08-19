#ifndef SOLVER_H
#define SOLVER_H

#include "model/sparse-matrix/sparseMatrix.h"

using namespace wfes::sparsematrix;

namespace wfes {
    namespace solver {

        /**
         * Abstract class describing a class for solving sparse linear systems.
         */
        class Solver {
            protected:
                /**
                 * @brief Sparse matrix to be solved.
                 */
                SparseMatrix& m;
            public:
                /**
                 * Instantiate the solver.
                 * @param A Sparse matrix for analysis.
                 */
                Solver(SparseMatrix& A);

                /**
                 * Destructor of the solver.
                 */
                virtual ~Solver(){};

                /**
                 * Preprocess data before solving the matrix.
                 */
                virtual void preprocess() = 0;

                /**
                 * Solve the linear system Ax=b.
                 * @param b Vector rhs of the system.
                 * @param transpose Set to true for transposing the matrix before solving.
                 * @return Vector x obtained after solving the system Ax=b.
                 */
                virtual dvec solve(dvec& b, bool transpose = false) =0;

                /**
                 * Solve the linear system AX=B.
                 * @param b Matrix rhs of the system.
                 * @param transpose Set to true for transposing the matrix before solving.
                 * @return Matrix X obtained after solving the system AX=B.
                 */
                virtual dmat solve_multiple(dmat& b, bool transpose = false) = 0;
        };
    }
}
#endif // SOLVER_H
