#ifndef WFES_WFAFLE_H
#define WFES_WFAFLE_H

#include "utils/types.h"
#include "utils/utils.h"
#include "utils/parsing.h"
#include "utils/exceptions.h"

#include <utils/observer/subject.h>

#include "model/wright-fisher/wrightFisher.h"

#include "model/visualization/imageresults.h"

#include "model/executables/wfafle/config/configWfafle.h"
#include "model/executables/wfafle/results/resultsWfafle.h"

/**
 * @brief The wfafle class implements the phase type executables.
 * wfafle: WFAFLE - Wright-Fisher Allele Frequency calculation.
 */
class wfafle : public Subject {
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
         * @brief Starts an execution of a wfafle model.
         * @return Results of the execution.
         */
        ResultsWfafle* execute();

        /**
         * @brief Calculates Wright-Fisher Allele Frequency.
         * @return Results of the execution.
         */
        ResultsWfafle* function();

        /**
         * @brief //TODO fill this.
         * @param x
         * @param N
         * @param t
         * @param s
         * @param h
         * @param u
         * @param v
         * @param alpha
         * @param verbose
         */
        void iterate_generations(dvec& x, llong N, llong t, double s, double h, double u, double v, double alpha, bool verbose = false);

        /**
         * @brief //TODO fill this.
         * @param x
         * @param Nx
         * @param Ny
         * @param s
         * @param h
         * @param u
         * @param v
         * @param alpha
         * @param verbose
         * @return
         */
        dvec switch_population_size(dvec& x, llong Nx, llong Ny, double s, double h, double u, double v, double alpha, bool verbose = false);


};

#endif // WFES_WFAFLE_H
