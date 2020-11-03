#ifndef WFES_SEQUENTIAL_H
#define WFES_SEQUENTIAL_H

#include "utils/exceptions.h"
#include "utils/types.h"
#include "utils/utils.h"
#include "utils/parsing.h"

#include <Eigen/Core>
#include <Eigen/Sparse>

#include "model/solver/solver.h"
#include "model/solver/solverFactory.h"

#include "model/sparse-matrix/sparseMatrix.h"
#include "model/sparse-matrix/sparseMatrixFactory.h"

#include "model/wright-fisher/wrightFisher.h"

#include "model/solver/pardiso/solverPardiso.h"
#include "model/sparse-matrix/pardiso/sparseMatrixPardiso.h"

#include <model/executables/wfes_sequential/results/resultsWfesSequential.h>

#include <utils/observer/subject.h>

#include <model/executables/wfes_sequential/config/configWfesSequential.h>

#include <model/visualization/imageresults.h>

class wfes_sequential : public Subject
{
public:
    time_point t_start, t_end;
    llong msg_level;

    ResultsWfesSequential* execute();

    ResultsWfesSequential* function();

};

#endif // WFES_SEQUENTIAL_H
