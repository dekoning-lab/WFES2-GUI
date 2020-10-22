#ifndef WFAS_H
#define WFAS_H

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

#include <model/executables/wfafle/results/resultsWfas.h>

#include <utils/observer/subject.h>

#include <model/executables/wfafle/config/configWfas.h>


class wfas
{
public:
    wfas();
};

#endif // WFAS_H
