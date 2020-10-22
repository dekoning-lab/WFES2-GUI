#ifndef WFES_WFAFLE_H
#define WFES_WFAFLE_H

#include "utils/exceptions.h"
#include "utils/types.h"
#include "utils/utils.h"
#include "utils/parsing.h"

#include "model/solver/solver.h"
#include "model/solver/solverFactory.h"

#include "model/sparse-matrix/sparseMatrix.h"
#include "model/sparse-matrix/sparseMatrixFactory.h"

#include "model/wright-fisher/wrightFisher.h"

#include "model/solver/pardiso/solverPardiso.h"
#include "model/sparse-matrix/pardiso/sparseMatrixPardiso.h"

#include <model/executables/wfafle/results/resultsWfafle.h>

#include <utils/observer/subject.h>

#include <model/executables/wfafle/config/configWfafle.h>


class wfafle : public Subject
{
public:
    time_point t_start, t_end;
    llong msg_level;

    ResultsWfafle* execute();

    ResultsWfafle* function();


    void iterate_generations(dvec& x, llong N, llong t, double s, double h, double u, double v, double alpha, bool verbose = false);

    dvec switch_population_size(dvec& x, llong Nx, llong Ny, double s, double h, double u, double v, double alpha, bool verbose = false);


};

#endif // WFES_WFAFLE_H
