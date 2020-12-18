#include "resultsWfafs.h"

ResultsWfafs::ResultsWfafs()
    : time(std::nan("")), error("") {}

ResultsWfafs::ResultsWfafs(double time)
    : time(time), error("") {}

ResultsWfafs::ResultsWfafs(std::string error)
    : time(std::nan("")), error(error) {}

ResultsWfafs::ResultsWfafs(dvec probs, double time)
    : time(time), probs(probs), error("") {}

void ResultsWfafs::writeResultsToFile(ResultsWfafs *results, std::string name) {
    // Let empty. This is not necessary since the prob. dist. are written in a file in the main
    // function of wfafs. Next lines remove the unused parameters warning.
    (void)results;
    (void)name;
}

