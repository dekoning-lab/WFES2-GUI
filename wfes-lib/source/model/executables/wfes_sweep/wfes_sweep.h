#ifndef WFES_SWEEP_H
#define WFES_SWEEP_H

#include "utils/types.h"
#include "utils/utils.h"
#include "utils/parsing.h"
#include "utils/exceptions.h"

#include <utils/observer/subject.h>

#include "model/wright-fisher/wrightFisher.h"

#include "model/config/globalConfiguration.h"

#include <model/visualization/imageresults.h>

#include <model/executables/wfes_sweep/config/configWfesSweep.h>
#include <model/executables/wfes_sweep/results/resultsWfesSweep.h>

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
        ResultsWfesSweep* fixation(dvec s, dvec u, dvec v);

        /**
         * @brief Calculate starting copies of allele.
         */
        void calculateStartingCopies(dvec s, dvec u, dvec v);

        /**
         * @brief Calculate z.
         */
        void calculateZ();
};

#endif // WFES_SWEEP_H
