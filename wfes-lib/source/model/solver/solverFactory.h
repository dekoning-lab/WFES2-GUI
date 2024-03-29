#ifndef SOLVERFACTORY_H
#define SOLVERFACTORY_H

#include "solver.h"
#include "model/solver/pardiso/solverPardiso.h"
#include "model/solver/viennacl/solverViennaCL.h"

namespace wfes {
    namespace solver {

        /**
         * Instantiates a solver.
         */
        class SolverFactory{
            public:

                /**
                 * Create a solver using different libraries specified by 'solver'. Returns instances of solvers like Pardiso or ViennaCL.
                 * @param solver String with the name of the applied solver.
                 * @param A Sparse matrix for analysis.
                 * @param matrix_type MKL Pardiso type of matrix.
                 * @param message_level Message level for MKL pardiso.
                 * @param vienna_solver Solver used by ViennaCL.
                 * @param preconditioner Preconditioner used by ViennaCL.
                 * @param n_rhs Right side of linear system.
                 * @return A pointer to a solver.
                 */
                static Solver* createSolver(std::string solver, SparseMatrix& A, llong matrix_type = MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, llong message_level = 0LL, std::string vienna_solver = "GMRes", std::string preconditioner = "", llong n_rhs = 1LL);
        };
    }
}

#endif // SOLVERFACTORY_H
