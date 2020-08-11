#include "solverViennaCL.h"


using namespace wfes::vienna;

SolverViennaCL::SolverViennaCL(wfes::pardiso::SparseMatrixPardiso &A) : Solver(A)
{

    //Convert into sparse matrix.
    Eigen::SparseMatrix<double, Eigen::RowMajor> sparse_eigen;
    sparse_eigen = A.dense().sparseView();
    //Copy to ViennaCL.
    copy(sparse_eigen, vcl_matrix);

}

SolverViennaCL::~SolverViennaCL()
{

}

void SolverViennaCL::preprocess()
{

}

dvec SolverViennaCL::solve(dvec &b, bool transpose)
{
    wfes::pardiso::SparseMatrixPardiso mat = dynamic_cast<wfes::pardiso::SparseMatrixPardiso&>(m);
    vcl_matrix.set(mat.row_index, mat.cols, mat.data, mat.num_rows, mat.num_cols, mat.num_non_zeros);


}

dmat SolverViennaCL::solve_multiple(dmat &b, bool transpose)
{
    return dmat();
}
