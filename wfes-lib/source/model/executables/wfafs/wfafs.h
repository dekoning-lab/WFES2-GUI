#ifndef WFAFS_H
#define WFAFS_H

#include "utils/types.h"
#include "utils/utils.h"
#include "utils/parsing.h"
#include "utils/exceptions.h"

#include <utils/observer/subject.h>

#include "model/wright-fisher/wrightFisher.h"

#include "model/config/globalConfiguration.h"

#include <model/visualization/imageresults.h>
#include <model/visualization/charts/chartResults.h>

#include <model/executables/wfafs/config/configWfafs.h>
#include <model/executables/wfafs/results/resultsWfafs.h>

//TODO Integrate generation of missing matrices and vectors.

/**
 * @brief The wfafs class implements the phase type executables.
 * wfafs: WFAFS - Wright-Fisher approximate spectrum.
 */
class wfafs : public Subject {
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
         * @brief Starts an execution of a wfafs model.
         * @return Results of the execution.
         */
        ResultsWfafs* execute();

        /**
         * @brief Calculates WFAFS - Wright-Fisher approximate spectrum.
         * @return Results of the execution.
         */
        ResultsWfafs* function();

};

#endif // WFAFS_H
