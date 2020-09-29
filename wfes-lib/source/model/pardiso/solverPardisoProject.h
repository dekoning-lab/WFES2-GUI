#ifndef SOLVERPARDISOPROJECT_H
#define SOLVERPARDISOPROJECT_H

#include <QDebug>

#include "model/solver/solver.h"
#include "model/viennacl/sparseMatrixViennacl.h"

#include "model/mkl/MKL_Consts.h"

#include "config/config.h"

/* PARDISO prototype. */
extern "C" void pardisoinit (void   *, int    *,   int *, int *, double *, int *);
extern "C" void pardiso     (void   *, int    *,   int *, int *,    int *, int *,
                  double *, int    *,    int *, int *,   int *, int *,
                     int *, double *, double *, int *, double *);
extern "C" void pardiso_chkmatrix  (int *, int *, double *, int *, int *, int *);
extern "C" void pardiso_chkvec     (int *, int *, double *, int *);
extern "C" void pardiso_printstats (int *, int *, double *, int *, int *, int *, double *, int *);

namespace wfes{
    namespace pardisoproject {

        class PardisoProjectSolver : public solver::Solver {
            private:
                // Internal solver memory pointer pt.
                void *pt[64];
                // Real unsymmetric matrix.
                int mtype = 11;
                // Sparse direct solver.
                int solver = 0;
                // Pardiso integer control parameters.
                int iparm[64];
                // Pardiso double control parameters.
                double dparm[64];
                // Error parameter.
                int error = 0;
                // Message level.
                int verbose = 0;
                // Number of right hand sides.
                int n_rhs;
                // Maximum number of numerical factorizations.
                int maxfct;
                // Which factorization to use.
                int mnum;
                // Matrix in format of ViennaCL.
                wfes::vienna::SparseMatrixViennaCL *mat;

                void convertToFortranNotation();

                void convertToCNotation();


                double   ddum;              /* Double dummy */
                int      idum;              /* Integer dummy. */
            public:
                /**
                 * @brief Constructor of class PardisoProjectSolver.
                 * @param A Sparse matrix to solve.
                 * @param matrix_type Defines the matrix type, which influences the pivoting method. (From MKL Pardiso documentation). The possible values can be seen in MKL_Consts.h.
                 * @param message_level Message level information. 0 for no information and 1 for verbose. (From MKL Pardiso documentation).
                 * @param n_rhs Number of right-hand sides that need to be solved for. (From MKL Pardiso documentation).
                 */
                PardisoProjectSolver(wfes::vienna::SparseMatrixViennaCL& A, int matrix_type, int message_level, int n_rhs = 1);

                /**
                 * Constructor of class PardisoSolver.
                 */
                ~PardisoProjectSolver();

                /**
                 * @brief Preprocess steps over the matrix before solving.
                 */
                void preprocess() override;

                /**
                 * @brief Solve the matrix for one right hand side.
                 * @param b Right hand side of the matrix.
                 * @param transpose True if the matrix needs to be transposed.
                 * @return Solution of the equation (Ax+b).
                 */
                dvec solve(dvec& b, bool transpose = false) override;

                /**
                 * @brief Solve the matrix for multiple right hand sides.
                 * @param b Right hand sides of the matrix.
                 * @param transpose True if the matrix needs to be transposed.
                 * @return Solution of the equation (AX=B).
                 */
                dmat solve_multiple(dmat& b, bool transpose = false) override;

                /**
                 * @brief Get diagonal of the matrix.
                 * @return Diagonal of the matrix as a vector.
                 */
                dvec get_diagonal();
        };

    }
}
#endif // SOLVERPARDISOPROJECT_H
