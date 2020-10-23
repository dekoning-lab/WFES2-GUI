#ifndef RESULTSWFESSEQUENTIAL_H
#define RESULTSWFESSEQUENTIAL_H

#include <source/model/executables/wfes_sequential/config/configWfesSequential.h>

#include <boost/math/special_functions/fpclassify.hpp>

#include "utils/types.h"

#include <QtGui/QImage>

#include <QDir>
#include <QStandardPaths>
#include <QDebug>

class ResultsWfesSequential {
    public:
        double pExt;
        double pFix;
        double pTmo;
        double tExt;
        double tExtStd;
        double tFix;
        double tFixStd;
        double tTmo;
        double tTmoStd;
        double time;

        ResultsWfesSequential();

        ResultsWfesSequential(double time);

        ResultsWfesSequential(double pExt, double pFix, double pTmo, double tExt, double tExtStd, double tFix, double tFixStd, double tTmo, double tTmoStd, double time);

        /**
         * @brief Write results in a CSV file.
         * @param results results to be printed in a CSV file.
         * @param name Name of the file.
         */
        void writeResultsToFile(ResultsWfesSequential *results, std::string name);

};

#endif // RESULTSWFESSEQUENTIAL_H
