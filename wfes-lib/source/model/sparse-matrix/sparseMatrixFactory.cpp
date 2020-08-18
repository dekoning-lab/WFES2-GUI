#include "sparseMatrixFactory.h"

using namespace wfes::sparsematrix;
using namespace wfes::pardiso;
using namespace wfes::vienna;

SparseMatrix* SparseMatrixFactory::createSparseMatrix(std::string library, llong numRows, llong numCols)
{
    if(library.compare("Pardiso") == 0){
        return new SparseMatrixPardiso(numRows, numCols);
    } else if(library.compare("ViennaCL") == 0){
        return new SparseMatrixViennaCL(numRows, numCols);
    } else {
        // Default case.
        return new SparseMatrixPardiso(numRows, numCols);
    }
}

SparseMatrix* SparseMatrixFactory::createSparseMatrix(std::string library, dmat eigenSparseMatrix)
{
    if(library.compare("Pardiso") == 0){
        return new SparseMatrixPardiso(eigenSparseMatrix);
    }else if(library.compare("ViennaCL") == 0){
        return new SparseMatrixViennaCL(eigenSparseMatrix);
    } else {
        // Default case.
        return new SparseMatrixPardiso(eigenSparseMatrix);
    }
}
