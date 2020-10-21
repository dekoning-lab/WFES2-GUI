#ifndef PHASE_TYPE_H
#define PHASE_TYPE_H

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

#include <model/executables/phase_type/results/resultsPhaseType.h>

#include <utils/observer/subject.h>

#include <model/executables/phase_type/config/configPhaseType.h>


class phase_type : public Subject
{
public:
    time_point t_start, t_end;
    llong msg_level;

    ResultsPhaseType* execute();

    ResultsPhaseType* phaseTypeDist();
    ResultsPhaseType* phaseTypeMoment();
};

#endif // PHASE_TYPE_H
