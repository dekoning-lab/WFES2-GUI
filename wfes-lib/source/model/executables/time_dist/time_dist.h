#ifndef TIMEDIST_H
#define TIMEDIST_H

#include "utils/exceptions.h"
#include "utils/types.h"
#include "utils/utils.h"
#include "utils/parsing.h"

#include "model/wright-fisher/wrightFisher.h"

#include <utils/observer/subject.h>

#include <model/executables/time_dist/results/resultsTimeDist.h>


class time_dist : public Subject{

    public:
        time_point t_start, t_end;
        llong msg_level;
        dvec starting_copies_p;
        llong z;

        ResultsTimeDist* execute();

        ResultsTimeDist* timeDist();

        ResultsTimeDist* timeDistSGV();

        ResultsTimeDist* timeDistSkip();

        ResultsTimeDist* timeDistDual();
};


#endif // TIMEDIST_H
