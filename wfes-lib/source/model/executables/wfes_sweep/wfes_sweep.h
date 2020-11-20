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

#include <model/visualization/imageresults.h>

/**
 * @brief The wfes_sweep class implements the wfes sweep executables.
 * Fixation: Only fixation state is absorbing.
 */
class wfes_sweep : public Subject {
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
         * @brief Vector containing starting copies.
         */
        dvec starting_copies_p;

        /**
         * @brief TODO Description of z.
         */
        llong z;

        /**
         * @brief Starts an execution of a wfes sweep model.
         * @return Results of the execution.
         */
        ResultsWfesSweep* execute();

        /**
         * @brief Only fixation state is absorbing.
         * @return Results of the execution.
         */
        ResultsWfesSweep* fixation();

        /**
         * @brief Calculate starting copies of allele.
         */
        void calculateStartingCopies();

        /**
         * @brief Calculate z.
         */
        void calculateZ();
};

#endif // WFES_SWEEP_H
