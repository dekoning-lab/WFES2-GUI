#include "sparseMatrixViennacl.h"

using namespace wfes::vienna;

SparseMatrixViennaCL::SparseMatrixViennaCL() :
    SparseMatrix(0, 0)
{
    this->vcl_matrix = viennacl::compressed_matrix<double>(0, 0);
}

SparseMatrixViennaCL::SparseMatrixViennaCL(llong num_rows, llong num_cols) :
    SparseMatrix(num_rows, num_cols)
{
    this->vcl_matrix = viennacl::compressed_matrix<double>(num_rows, num_cols);
}

SparseMatrixViennaCL::SparseMatrixViennaCL(dmat &eigenDenseMatrix) :
    SparseMatrix(eigenDenseMatrix.rows(), eigenDenseMatrix.cols())
{
    //TODO
}

SparseMatrix *SparseMatrixViennaCL::LeftPaddedDiagonal(llong dim, double x, llong padLeft)
{
    SparseMatrixViennaCL* I = new SparseMatrixViennaCL(dim, padLeft + dim);
    I->num_non_zeros = dim;

    for(int i = 0; i < I->num_non_zeros; i++) {
        I->vcl_matrix(i, i + padLeft) = x;
    }

    return I;

}

SparseMatrixViennaCL::~SparseMatrixViennaCL()
{

}

void SparseMatrixViennaCL::appendRow(dvec &row, llong col_start, llong size)
{

}

void SparseMatrixViennaCL::appendChunk(dvec &row, llong m0, llong r0, llong size)
{

}

void SparseMatrixViennaCL::appendValue(double value, llong j)
{

}

void SparseMatrixViennaCL::nextRow()
{

}

void SparseMatrixViennaCL::debugPrint()
{

}

bool SparseMatrixViennaCL::approxEquals(const SparseMatrix &rhs, double tol, bool verbose)
{

    return false;
}

dmat SparseMatrixViennaCL::dense()
{
    dmat dense_matrix = dmat(this->vcl_matrix.size1(), this->vcl_matrix.size2());
    for(unsigned long i = 0; i < this->vcl_matrix.size1(); i++) {
        for(unsigned long j = 0; j < this->vcl_matrix.size2(); j++) {
            dense_matrix(i, j) = this->vcl_matrix(i, j);
        }
    }
    return dense_matrix;
}

dvec SparseMatrixViennaCL::getDiagCopy()
{

    return dvec();
}

dvec SparseMatrixViennaCL::getColCopy(llong j)
{

    return dvec();
}

dvec SparseMatrixViennaCL::getRowCopy(llong i)
{

    return dvec();
}

dvec SparseMatrixViennaCL::multiply(dvec &x, bool transpose)
{

    return dvec();
}

void SparseMatrixViennaCL::multiplyInPlaceRep(dvec &x, llong times, bool transpose)
{

}

SparseMatrix *SparseMatrixViennaCL::multiply(SparseMatrix &B, bool transpose)
{

    return new SparseMatrixViennaCL();
}

void SparseMatrixViennaCL::subtractIdentity()
{

}

double SparseMatrixViennaCL::search(llong i, llong j)
{

    return 0.0;
}

void SparseMatrixViennaCL::setValue(double x, llong i, llong j)
{

}

void SparseMatrixViennaCL::saveMarket(std::string path)
{

}
