#include "sparseMatrixFactory.h"

using namespace wfes::sparsematrix;
using namespace wfes::mkl;
using namespace wfes::vienna;

SparseMatrix* SparseMatrixFactory::createSparseMatrix(std::string library, llong numRows, llong numCols)
{
    if(library.compare("MKL") == 0){
        return new SparseMatrixMKL(numRows, numCols);
    } else if(library.compare("ViennaCL") == 0){
        return new SparseMatrixViennaCL(numRows, numCols);
    } else if(library.compare("Pardiso") == 0){
        return new SparseMatrixViennaCL(numRows, numCols);
    } else {
        // Default case.
        return new SparseMatrixMKL(numRows, numCols);
    }
}

SparseMatrix* SparseMatrixFactory::createSparseMatrix(std::string library, dmat eigenSparseMatrix)
{
    if(library.compare("MKL") == 0){
        return new SparseMatrixMKL(eigenSparseMatrix);
    }else if(library.compare("ViennaCL") == 0){
        return new SparseMatrixViennaCL(eigenSparseMatrix);
    }else if(library.compare("Pardiso") == 0){
        return new SparseMatrixViennaCL(eigenSparseMatrix);
    } else {
        // Default case.
        return new SparseMatrixMKL(eigenSparseMatrix);
    }
}
