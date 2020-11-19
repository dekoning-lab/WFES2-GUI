#ifndef CHARTRESULTS_H
#define CHARTRESULTS_H

#include <source/utils/types.h>

#include <QString>

class ChartResults
{
public:
    static dvec probabilities;
    static dvec moments;

    ChartResults();
    static dvec getLine(QString id);
    static void clear();
};

#endif // CHARTRESULTS_H
