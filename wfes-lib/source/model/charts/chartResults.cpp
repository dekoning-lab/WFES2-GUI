#include "chartResults.h"

dvec ChartResults::probabilities = [] {
    dvec tmp(0);
    return tmp;
}();
dvec ChartResults::moments = [] {
    dvec tmp(0);
    return tmp;
}();

ChartResults::ChartResults() {}

dvec ChartResults::getLine(QString id)
{
    if(id.compare("Prob") == 0 && ChartResults::probabilities.size() != 0)
        return probabilities;
    if(id.compare("Moments") == 0 && ChartResults::moments.size() != 0)
        return moments;
    else {
        return dvec(0);
    }
}

void ChartResults::clear()
{
    ChartResults::probabilities = [] {
        dvec tmp(0);
        return tmp;
    }();
    ChartResults::moments = [] {
        dvec tmp(0);
        return tmp;
    }();
}


