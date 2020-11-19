#ifndef RESULTSTIMEDIST_H
#define RESULTSTIMEDIST_H

#include <source/model/executables/wfes_single/config/configWfesSingle.h>

#include <boost/math/special_functions/fpclassify.hpp>

#include "utils/types.h"


class ResultsTimeDist
{
public:
    double time;
    dmat probs;
    std::string error;

    ResultsTimeDist();

    ResultsTimeDist(dmat probs, double time);

    ResultsTimeDist(std::string error);
};

#endif // RESULTSTIMEDIST_H
