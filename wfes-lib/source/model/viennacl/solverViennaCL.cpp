#include "solverViennaCL.h"

using namespace wfes::vienna;

SolverViennaCL::SolverViennaCL(SparseMatrixViennaCL &A) : Solver(A)
{

}

SolverViennaCL::~SolverViennaCL()
{

}

void SolverViennaCL::preprocess()
{

}

dvec SolverViennaCL::solve(dvec &b, bool transpose)
{
    return dvec();
}

dmat SolverViennaCL::solve_multiple(dmat &b, bool transpose)
{
    return dmat();
}
