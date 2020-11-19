#include "resultsTimeDist.h"

ResultsTimeDist::ResultsTimeDist() : time(std::nan("")), error("") {}

ResultsTimeDist::ResultsTimeDist(dmat probs, double time) : probs(probs), time(time) {}

ResultsTimeDist::ResultsTimeDist(std::string error) : time(std::nan("")), error(error) {}
