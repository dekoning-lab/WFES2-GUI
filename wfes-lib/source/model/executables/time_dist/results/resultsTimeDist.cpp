#include "resultsTimeDist.h"

ResultsTimeDist::ResultsTimeDist()
    : time(std::nan("")), error("") {}

ResultsTimeDist::ResultsTimeDist(dmat probs, double time)
    : time(time), probs(probs) {}

ResultsTimeDist::ResultsTimeDist(std::string error)
    : time(std::nan("")), error(error) {}
