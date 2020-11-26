#ifndef WFAS_H
#define WFAS_H

#include "utils/types.h"
#include "utils/utils.h"
#include "utils/parsing.h"
#include "utils/exceptions.h"

#include <utils/observer/subject.h>

#include "model/wright-fisher/wrightFisher.h"

#include "model/config/globalConfiguration.h"

#include <model/visualization/imageresults.h>
#include <model/visualization/charts/chartResults.h>

#include <model/executables/wfas/config/configWfas.h>
#include <model/executables/wfas/results/resultsWfas.h>

//TODO Integrate generation of missing matrices and vectors.

/**
 * @brief The wfas class implements the phase type executables.
 * wfafle: WFAS - Wright-Fisher approximate spectrum.
 */
class wfas : public Subject {
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
         * @brief Starts an execution of a wfas model.
         * @return Results of the execution.
         */
        ResultsWfas* execute();

        /**
         * @brief Calculates WFAS - Wright-Fisher approximate spectrum.
         * @return Results of the execution.
         */
        ResultsWfas* function();

};

#endif // WFAS_H
