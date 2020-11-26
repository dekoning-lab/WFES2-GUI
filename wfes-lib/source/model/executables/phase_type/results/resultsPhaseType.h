#ifndef RESULTSPHASETYPE_H
#define RESULTSPHASETYPE_H

#include <QStandardPaths>
#include <QTextStream>
#include <QDir>

#include <ctime>

#include <boost/math/special_functions/fpclassify.hpp>

#include <model/executables/phase_type/config/configPhaseType.h>
#include "utils/types.h"

/**
 * @brief The ResultsPhaseType class encapsulates the results generated by an
 * execution of phase type.
 */
class ResultsPhaseType {
    public:
        /**
         * @brief Mean of the calculated moments.
         */
        double mean;

        /**
         * @brief Standard deviation of the calculated moments.
         */
        double std;

        /**
         * @brief Execution time.
         */
        double time;

        /**
         * @brief Probabilities calculated.
         * Column 1 represents time, or each generation.
         * Column 2 represents probability of substitution at a given time.
         * Column 3 is the acumulated value of column 2.
         */
        dmat probs;

        /**
         * @brief Moments calculated.
         */
        dvec moments;

        /**
         * @brief String containing possible errors during execution.
         * This is later shown to the user in a MessageDialog.
         */
        std::string error;

        /**
         * @brief Empty constructor of ResultsPhaseType.
         */
        ResultsPhaseType();

        /**
         * @brief Constructor of ResultsPhaseType with execution time.
         * @param time Execution time.
         */
        ResultsPhaseType(double time);

        /**
         * @brief Constructor of ResultsPhaseType when an error happens during execution.
         * @param error Description of the error or message generated by the error.
         */
        ResultsPhaseType(std::string error);

        /**
         * @brief Constructor of ResultsPhaseType for Phase Type Dist. mode.
         * @param probs Probabilities calculated.
         * @param time Execution time.
         */
        ResultsPhaseType(dmat probs, double time);

        /**
         * @brief Constructor of ResultsPhaseType for Phase Type Moments mode.
         * @param mean Mean of the moments.
         * @param std Standard deviation of the moments.
         * @param moments Moments calculated.
         * @param time Execution time.
         */
        ResultsPhaseType(double mean, double std, dvec moments, double time);

        /**
         * @brief Write results in a CSV file.
         * @param results results to be printed in a CSV file.
         * @param name Name of the file.
         */
        void writeResultsToFile(ResultsPhaseType *results, std::string name);

};


#endif // RESULTSPHASETYPE_H
