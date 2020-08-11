#ifndef SOLVERVIENNACL_H
#define SOLVERVIENNACL_H

#include "model/solver/solver.h"
#include "sparseMatrixViennacl.h"
#include <viennacl/compressed_matrix.hpp>
#include "utils/types.h"

namespace wfes{
    namespace vienna {

        class SolverViennaCL : public solver::Solver {

            public:
                // ViennaCL compressed matrix.
                viennacl::compressed_matrix<double> vcl_matrix;

                /**
                 * Instantiate the solver and converts from SparseMatrix to viennacl::compressed_matrix.
                 * @param A Sparse matrix for analysis.
                 */
                SolverViennaCL(SparseMatrixViennaCL &A);

                /**
                 * Destructor of ViennaCL solver.
                 */
                ~SolverViennaCL();

                /**
                 * Preprocess data before solving the matrix.
                 */
                void preprocess() override;

                /**
                 * Solve the linear system Ax=b.
                 * @param b Vector rhs of the system.
                 * @param transpose Set to true for transposing the matrix before solving.
                 * @return Vector x obtained after solving the system Ax=b.
                 */
                dvec solve(dvec& b, bool transpose = false) override;

                /**
                 * Solve the linear system AX=B.
                 * @param b Matrix rhs of the system.
                 * @param transpose Set to true for transposing the matrix before solving.
                 * @return Matrix X obtained after solving the system AX=B.
                 */
                dmat solve_multiple(dmat& b, bool transpose = false) override;

        };
    }
}

#endif // SOLVERVIENNACL_H
