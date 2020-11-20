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

/**
 * @brief The wfes_sweep class implements the wfes sweep executables.
 * Fixation: Only fixation state is absorbing.
 * Absorption: Both fixation and extinction states are absorbing.
 */
class wfes_switching : public Subject {
    public:
    /**
     * @brief Starting point of measuring execution time.
     */
    time_point t_start;

    /**
     * @brief Ending point of measuring execution time.
     */
    time_point t_end;

    /**
     * @brief Verbose level.
     */
    llong msg_level;

    /**
     * @brief Starts an execution of a wfes single model.
     * @return Results of the execution.
     */
    ResultsWfesSwitching* execute();

    /**
     * @brief Both fixation and extinction states are absorbing.
     * @return Results of the execution.
     */
    ResultsWfesSwitching* absorption();

    /**
     * @brief Only fixation state is absorbing.
     * @return Results of the execution.
     */
    ResultsWfesSwitching* fixation();

};

#endif // WFES_SWITCHING_H
