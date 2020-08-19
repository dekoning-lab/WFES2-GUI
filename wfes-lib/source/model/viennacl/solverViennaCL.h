#ifndef SOLVERVIENNACL_H
#define SOLVERVIENNACL_H

#define VIENNACL_HAVE_EIGEN 1
#define VIENNACL_WITH_OPENCL 1

#include "model/solver/solver.h"
#include "sparseMatrixViennacl.h"
#include <viennacl/compressed_matrix.hpp>
#include "utils/types.h"
#include "config/config.h"

#include "viennacl/linalg/amg.hpp"
#include "viennacl/linalg/cg.hpp"
#include <viennacl/linalg/bicgstab.hpp>
#include <viennacl/linalg/gmres.hpp>
#include <viennacl/linalg/mixed_precision_cg.hpp>
#include <viennacl/linalg/jacobi_precond.hpp>
#include <viennacl/linalg/ilu.hpp>

#include "QDebug"
namespace wfes{
    namespace vienna {

        class SolverViennaCL : public solver::Solver {

            public:
            // Solver to use.
            std::string solver;
            //Preconditioner to use.
            std::string preconditioner;

                /**
                 * Instantiate the solver and converts from SparseMatrix to viennacl::compressed_matrix.
                 * @param A Sparse matrix for analysis.
                 * @param solver Solver to use.
                 * @param preconditioner Preconditioner to use.
                 */
                SolverViennaCL(wfes::vienna::SparseMatrixViennaCL &A, std::string solver, std::string preconditioner);

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

                dvec solve_mixed_cg(dvec& b, bool transpose = false);
                dvec solve_cg(dvec& b, bool transpose = false);
                dvec solve_bicgstab(dvec& b, bool transpose = false);
                dvec solve_gmres(dvec& b, bool transpose = false);

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
