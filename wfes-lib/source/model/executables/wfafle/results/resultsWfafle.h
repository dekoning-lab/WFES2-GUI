#ifndef RESULTSWFAFLE_H
#define RESULTSWFAFLE_H

#include "utils/types.h"

#include <QDir>
#include <QStandardPaths>
#include <QDebug>

#include <boost/math/special_functions/fpclassify.hpp>

class ResultsWfafle {
    public:
        double time;
        dvec probs;
        std::string error;
        ResultsWfafle();

        ResultsWfafle(double time);

        ResultsWfafle(std::string error);

        ResultsWfafle(dvec probs, double time);

        /**
         * @brief Write results in a CSV file.
         * @param results results to be printed in a CSV file.
         * @param name Name of the file.
         */
        void writeResultsToFile(ResultsWfafle *results, std::string name);
};

#endif // RESULTSWFAFLE_H
