#ifndef WFES_SINGLE_H
#define WFES_SINGLE_H

#include "source/model/executables/wfes_single/config/configWfesSingle.h"

#include "utils/exceptions.h"
#include "utils/types.h"
#include "utils/utils.h"
#include "utils/parsing.h"

#include "model/solver/solver.h"
#include "model/solver/solverFactory.h"

#include "model/sparse-matrix/sparseMatrix.h"
#include "model/sparse-matrix/sparseMatrixFactory.h"

#include "model/wright-fisher/wrightFisher.h"

#include "model/solver/pardiso/solverPardiso.h"
#include "model/sparse-matrix/pardiso/sparseMatrixPardiso.h"

#include "results/resultsWfesSingle.h"

#include <utils/observer/subject.h>

#include <source/model/executables/wfes_single/config/configWfesSingle.h>

#include <model/visualization/imageresults.h>

class wfes_single : public Subject{

    public:
        time_point t_start, t_end;
        llong msg_level;
        dvec starting_copies_p;
        llong z;

        ResultsWfesSingle* execute();

        ResultsWfesSingle* absorption();

        ResultsWfesSingle* fixation();

        ResultsWfesSingle* fundamental();

        ResultsWfesSingle* equilibrium();

        ResultsWfesSingle* establishment();

        ResultsWfesSingle* alleleAge();

        ResultsWfesSingle* nonAbsorbing();

        void force();
        void calculateStartingCopies();
        void calculateZ();
};

#endif // WFES_SINGLE_H
