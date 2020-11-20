#ifndef WFES_SEQUENTIAL_H
#define WFES_SEQUENTIAL_H

#include "utils/types.h"
#include "utils/utils.h"
#include "utils/parsing.h"
#include "utils/exceptions.h"

#include <utils/observer/subject.h>

#include "model/wright-fisher/wrightFisher.h"

#include "model/visualization/imageresults.h"

#include <model/executables/wfes_sequential/config/configWfesSequential.h>
#include <model/executables/wfes_sequential/results/resultsWfesSequential.h>

/**
 * @brief The wfes_sequential class implements the wfes sequential executables.
 * Wfes Sequential: Implements calculations for a set of standard Wright-Fisher models sequentially.
 */
class wfes_sequential : public Subject {
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
         * @brief Starts an execution of a wfes sequential model.
         * @return Results of the execution.
         */
        ResultsWfesSequential* execute();

        /**
         * @brief Implements calculations for a set of standard Wright-Fisher models sequentially.
         * @return Results of the execution.
         */
        ResultsWfesSequential* function();

};

#endif // WFES_SEQUENTIAL_H
