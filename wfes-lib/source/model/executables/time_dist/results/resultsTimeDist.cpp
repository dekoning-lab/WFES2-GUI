#include "resultsTimeDist.h"

ResultsTimeDist::ResultsTimeDist() : time(std::nan("")), error("") {}

ResultsTimeDist::ResultsTimeDist(double time) : time(time) {}

ResultsTimeDist::ResultsTimeDist(std::string error) : time(std::nan("")), error(error) {}
