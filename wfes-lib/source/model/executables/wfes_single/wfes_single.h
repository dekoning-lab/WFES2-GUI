#ifndef WFES_SINGLE_H
#define WFES_SINGLE_H

#include "utils/types.h"
#include "utils/utils.h"
#include "utils/parsing.h"
#include "utils/exceptions.h"

#include <utils/observer/subject.h>

#include "model/wright-fisher/wrightFisher.h"

#include "model/config/globalConfiguration.h"

#include <model/visualization/imageresults.h>

#include "model/sparse-matrix/sparseMatrix.h"
#include "model/sparse-matrix/sparseMatrixFactory.h"

#include "model/executables/wfes_single/config/configWfesSingle.h"
#include "model/executables/wfes_single/results/resultsWfesSingle.h"

/**
 * @brief The wfes_single class implements the wfes single executables.
 * Absorption: Both fixation and extinction states are absorbing.
 * Fixation: Only fixation state is absorbing.
 * Fundamental: Calculate the entire fundamental matrix (slow).
 * Equilibrium: Calculate the equilibrium distribtion of allele states.
 * Establishment: Calculate establishment properties.
 * Allele Age: Calculate age of an allele.
 * Non Absorbing: Build a non-absorbing WF matrix.
 */
class wfes_single : public Subject{

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
         * @brief Starts an execution of a wfes single model.
         * @return Results of the execution.
         */
        ResultsWfesSingle* execute();

        /**
         * @brief Both fixation and extinction states are absorbing.
         * @return Results of the execution.
         */
        ResultsWfesSingle* absorption();

        /**
         * @brief Only fixation state is absorbing.
         * @return Results of the execution.
         */
        ResultsWfesSingle* fixation();

        /**
         * @brief Calculate the entire fundamental matrix (slow).
         * @return Results of the execution.
         */
        ResultsWfesSingle* fundamental();

        /**
         * @brief Calculate the equilibrium distribtion of allele states.
         * @return Results of the execution.
         */
        ResultsWfesSingle* equilibrium();

        /**
         * @brief Calculate establishment properties.
         * @return Results of the execution.
         */
        ResultsWfesSingle* establishment();

        /**
         * @brief Calculate age of an allele.
         * @return Results of the execution.
         */
        ResultsWfesSingle* alleleAge();

        /**
         * @brief Build a non-absorbing WF matrix.
         * @return Results of the execution.
         */
        ResultsWfesSingle* nonAbsorbing();

        /**
         * @brief Calculate starting copies of allele.
         */
        void calculateStartingCopies();

        /**
         * @brief Calculate z.
         */
        void calculateZ();
};

#endif // WFES_SINGLE_H
