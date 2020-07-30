#ifndef SOLVERPARDISO_H
#define SOLVERPARDISO_H

#include "model/pardiso/sparseMatrixPardiso.h"
#include "model/solver/solver.h"
#include "utils/types.h"
#include "MKL_Consts.h"

namespace wfes{
    namespace pardiso {

        class PardisoSolver : public solver::Solver {

                llong size;
                llong n_right_hand_sides;
                llong max_factors;
                llong matrix_type;
                llong matrix_number;
                llong error;
                llong message_level;
                llong phase;

                lvec control;
                lvec internal;
                dvec workspace;

            public:
                PardisoSolver(SparseMatrixPardiso& A, llong matrix_type, llong message_level, llong n_rhs = 1);
                ~PardisoSolver();
                void preprocess() override;
                dvec solve(dvec& b, bool transpose = false) override;
                dmat solve_multiple(dmat& b, bool transpose = false) override;
                dvec get_diagonal();
        };
    }
}

#endif // SOLVERPARDISO_H
