#ifndef WFES_SWEEP_H
#define WFES_SWEEP_H

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

#include <utils/observer/subject.h>

#include <model/executables/wfes_sweep/results/resultsWfesSweep.h>

#include <model/executables/wfes_sweep/config/configWfesSweep.h>

class wfes_sweep : public Subject
{

public:
    time_point t_start, t_end;
    llong msg_level;
    dvec starting_copies_p;
    llong z;

    ResultsWfesSweep* execute();

    ResultsWfesSweep* fixation();

    void force();
    void calculateStartingCopies();
    void calculateZ();
};

#endif // WFES_SWEEP_H
