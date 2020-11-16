#ifndef WFES_SWITCHING_H
#define WFES_SWITCHING_H

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

#include <model/executables/wfes_switching/results/resultsWfesSwitching.h>

#include <model/executables/wfes_switching/config/configWfesSwitching.h>

#include <model/visualization/imageresults.h>

class wfes_switching : public Subject
{
public:


    time_point t_start, t_end;
    llong msg_level;

    ResultsWfesSwitching* execute();

    ResultsWfesSwitching* absorption();

    ResultsWfesSwitching* fixation();

};

#endif // WFES_SWITCHING_H
