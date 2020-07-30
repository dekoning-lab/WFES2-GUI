#ifndef WFES_SINGLE_H
#define WFES_SINGLE_H

#include "config/config.h"

#include "utils/exceptions.h"
#include "utils/types.h"
#include "utils/utils.h"
#include "utils/parsing.h"

#include "model/solver/solver.h"
#include "model/solver/solverFactory.h"

#include "model/sparse-matrix/sparseMatrix.h"
#include "model/sparse-matrix/sparseMatrixFactory.h"

#include "model/wright-fisher/wrightFisher.h"

#include "model/pardiso/solverPardiso.h"
#include "model/pardiso/sparseMatrixPardiso.h"

class wfes_single{
    public:
        void execute();
};

#endif // WFES_SINGLE_H
