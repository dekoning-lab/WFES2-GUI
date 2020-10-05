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

#include "model/pardiso/solverPardiso.h"
#include "model/pardiso/sparseMatrixPardiso.h"

#include "results/resultsWfesSingle.h"

#include <utils/observer/subject.h>


enum ExecutionStatus{
    NONE, STARTING, BUILDING_MATRICES, SOLVING_MATRICES, SAVING_DATA, DONE, ABORTED
};

static const char* ExecutionStatusName[] = { "None", "Starting...", "Building matrices...", "Solving matrices...", "Saving data...", "Done.", "Aborted by user."};

class wfes_single : public Subject{

    public:
        time_point t_start, t_end;
        llong msg_level;
        dvec starting_copies_p;
        llong z;

        Results* execute();

        Results* absorption();

        Results* fixation();

        Results* fundamental();

        Results* equilibrium();

        Results* establishment();

        Results* alleleAge();

        Results* nonAbsorbing();

        void force();
        void calculateStartingCopies();
        void calculateZ();
};

#endif // WFES_SINGLE_H
