#ifndef WFES_WFAFD_H
#define WFES_WFAFD_H

#include "utils/types.h"
#include "utils/utils.h"
#include "utils/parsing.h"
#include "utils/exceptions.h"

#include <utils/observer/subject.h>

#include "model/wright-fisher/wrightFisher.h"

#include "model/config/globalConfiguration.h"

#include "model/visualization/imageresults.h"
#include <model/visualization/charts/chartResults.h>

#include "model/executables/wfafd/config/configWfafd.h"
#include "model/executables/wfafd/results/resultsWfafd.h"

/**
 * @brief The wfafd class implements the phase type executables.
 * wfafd: WFAFD - Wright-Fisher Allele Frequency calculation.
 */
class wfafd : public Subject {
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
         * @brief Starts an execution of a wfafd model.
         * @return Results of the execution.
         */
        ResultsWfafd* execute();

        /**
         * @brief Calculates Wright-Fisher Allele Frequency.
         * @return Results of the execution.
         */
        ResultsWfafd* function();

        /**
         * @brief Iterate over the model t generations.
         * @param x Vector of model.
         * @param N Population size.
         * @param t Max num generations
         * @param s Selection coefficient.
         * @param h Dominance coefficient.
         * @param u Backward mutation rate.
         * @param v Fordward mutation rate.
         * @param alpha Tail truncation weight.
         * @param verbose Obtain verbose information.
         */
        void iterate_generations(dvec& x, llong N, llong t, double s, double h, double u, double v, double alpha, bool verbose = false);

        /**
         * @brief Switch population size between models.
         * @param x Vector of model.
         * @param Nx Population of first model.
         * @param Ny Population of second model.
         * @param s Selection coefficient.
         * @param h Dominance coefficient.
         * @param u Backward mutation rate.
         * @param v Fordward mutation rate.
         * @param alpha Tail truncation weight.
         * @param verbose Obtain verbose information.
         * @return Next vector to analyze
         */
        dvec switch_population_size(dvec& x, llong Nx, llong Ny, double s, double h, double u, double v, double alpha, bool verbose = false);


};

#endif // WFES_WFAFD_H
