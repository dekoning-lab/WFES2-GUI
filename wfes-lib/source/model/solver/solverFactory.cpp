#include "solverFactory.h"

using namespace wfes::solver;
using namespace wfes::mkl;
using namespace wfes::vienna;
using namespace wfes::pardisoproject;

Solver* SolverFactory::createSolver(std::string solver, SparseMatrix& A, llong matrix_type, llong message_level, std::string vienna_solver, std::string preconditioner, llong n_rhs){
    if(solver.compare("MKL") == 0)
        return new MKLSolver(dynamic_cast<SparseMatrixMKL&>(A), matrix_type, message_level, n_rhs);
    else if(solver.compare("ViennaCL") == 0)
        return new SolverViennaCL(dynamic_cast<SparseMatrixViennaCL&>(A), vienna_solver, preconditioner);
    else if(solver.compare("Pardiso") == 0)
        return new PardisoProjectSolver(dynamic_cast<SparseMatrixViennaCL&>(A), matrix_type, message_level, n_rhs);
    else // Default MKL.
        return new MKLSolver(dynamic_cast<SparseMatrixMKL&>(A), matrix_type, message_level, n_rhs);
}
