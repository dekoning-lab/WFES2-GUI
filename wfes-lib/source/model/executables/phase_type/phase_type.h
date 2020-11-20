#ifndef PHASE_TYPE_H
#define PHASE_TYPE_H

#include "utils/types.h"
#include "utils/utils.h"
#include "utils/parsing.h"
#include "utils/exceptions.h"

#include "utils/observer/subject.h"

#include "model/wright-fisher/wrightFisher.h"

#include <model/visualization/imageresults.h>

#include "model/executables/phase_type/config/configPhaseType.h"
#include "model/executables/phase_type/results/resultsPhaseType.h"

/**
 * @brief The phase_type class implements the phase type executables.
 * Phase Type Dist.: This calculates the distribution of time to substitution.
 * Phase Type Moments: This calculates arbitrary number of raw moments of the distribution of time to substitution.
 */
class phase_type : public Subject {
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
         * @brief Starts an execution of a Phase Type model.
         * @return Results of the execution.
         */
        ResultsPhaseType* execute();

        /**
         * @brief Calculates the distribution of time to substitution.
         * @return Results of the execution.
         */
        ResultsPhaseType* phaseTypeDist();

        /**
         * @brief Calculates arbitrary number of raw moments of the distribution of time to substitution.
         * @return Results of the execution.
         */
        ResultsPhaseType* phaseTypeMoment();
};

#endif // PHASE_TYPE_H
