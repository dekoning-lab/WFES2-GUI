#ifndef RESULTSPHASETYPE_H
#define RESULTSPHASETYPE_H

#include "utils/types.h"

#include <QDir>
#include <QStandardPaths>
#include <QDebug>

#include <boost/math/special_functions/fpclassify.hpp>
#include <ctime>

class ResultsPhaseType {
public:
    double mean;
    double std;
    double time;
    dvec moments;

    ResultsPhaseType();

    ResultsPhaseType(double mean, double std, dvec moments, double time);

    ResultsPhaseType(double time);

    /**
     * @brief Write results in a CSV file.
     * @param results results to be printed in a CSV file.
     * @param name Name of the file.
     */
    void writeResultsToFile(ResultsPhaseType *results, std::string name);

};

#endif // RESULTSPHASETYPE_H
