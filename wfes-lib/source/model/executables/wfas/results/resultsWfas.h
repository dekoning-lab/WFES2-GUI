#ifndef RESULTSWFAS_H
#define RESULTSWFAS_H

#include "utils/types.h"

#include <QDir>
#include <QStandardPaths>
#include <QDebug>

#include <boost/math/special_functions/fpclassify.hpp>

class ResultsWfas {
    public:
        double time;
        dvec probs;
        std::string error;

        ResultsWfas();

        ResultsWfas(double time);

        ResultsWfas(std::string error);

        ResultsWfas(dvec probs, double time);

        /**
         * @brief Write results in a CSV file.
         * @param results results to be printed in a CSV file.
         * @param name Name of the file.
         */
        void writeResultsToFile(ResultsWfas *results, std::string name);
};

#endif // RESULTSWFAS_H
