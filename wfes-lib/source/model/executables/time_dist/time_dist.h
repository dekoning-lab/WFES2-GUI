#ifndef TIMEDIST_H
#define TIMEDIST_H

#include "utils/types.h"
#include "utils/utils.h"
#include "utils/parsing.h"
#include "utils/exceptions.h"

#include <utils/observer/subject.h>

#include "model/wright-fisher/wrightFisher.h"

#include <model/visualization/imageresults.h>
#include <model/visualization/charts/chartResults.h>

#include <model/executables/time_dist/config/configTimeDist.h>
#include <model/executables/time_dist/results/resultsTimeDist.h>
#include <model/executables/time_dist/config/configTimeDistSGV.h>

/**
 * @brief The time_dist class implements the time dist executables.
 * Time Dist.: This calculates the distribution of time to fixation, extinction.
 * Time Dist. SGV: This calculates the distribution of time to substitution under a two-step adaptive model wfes sweep.
 * Time Dist. Skip: This calculates the distribution of time to substitution, but ignores the time spent waiting for mutation.
 * Time Dist. Dual: This calculates the distribution of time to fixation, extinction using a dual mutation model.
 */
class time_dist : public Subject {
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
         * @brief Starts an execution of a Time Dist model.
         * @return Results of the execution.
         */
        ResultsTimeDist* execute();

        /**
         * @brief Calculates the distribution of time to fixation, extinction.
         * @return Results of the execution.
         */
        ResultsTimeDist* timeDist();

        /**
         * @brief Calculates the distribution of time to substitution under a two-step adaptive model wfes sweep.
         * @return Results of the execution.
         */
        ResultsTimeDist* timeDistSGV();

        /**
         * @brief Calculates the distribution of time to substitution, but ignores the time spent waiting for mutation.
         * @return Results of the execution.
         */
        ResultsTimeDist* timeDistSkip();

        /**
         * @brief Calculates the distribution of time to fixation, extinction using a dual mutation model.
         * @return Results of the execution.
         */
        ResultsTimeDist* timeDistDual();
};


#endif // TIMEDIST_H
