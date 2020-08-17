#include "solverFactory.h"

using namespace wfes::solver;
using namespace wfes::pardiso;
using namespace wfes::vienna;

Solver* SolverFactory::createSolver(std::string solver, SparseMatrix& A, llong matrix_type, llong message_level, std::string vienna_solver, std::string preconditioner, llong n_rhs){
    if(solver.compare("Pardiso") == 0)
        return new PardisoSolver(dynamic_cast<SparseMatrixPardiso&>(A), matrix_type, message_level, n_rhs);
    else if(solver.compare("ViennaCL") == 0)
        return new SolverViennaCL(dynamic_cast<SparseMatrixViennaCL&>(A), vienna_solver, preconditioner);
    else // Default Pardiso.
        return new PardisoSolver(dynamic_cast<SparseMatrixPardiso&>(A), matrix_type, message_level, n_rhs);
}
