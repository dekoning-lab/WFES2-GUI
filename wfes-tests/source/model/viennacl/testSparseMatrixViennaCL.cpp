#include "testSparseMatrixViennaCL.h"

using namespace wfes::vienna;

static TestSparseMatrixViennaCL instance;

TestSparseMatrixViennaCL::TestSparseMatrixViennaCL() : TestSuite("TestSparseMatrixViennaCL")
{

}

void TestSparseMatrixViennaCL::initTestCase()
{

}

void TestSparseMatrixViennaCL::cleanUpTestCase()
{

}

void TestSparseMatrixViennaCL::init()
{

}

void TestSparseMatrixViennaCL::cleanup()
{

}

void TestSparseMatrixViennaCL::createMatrix_createDiagMatrix()
{
    // Create Matrix.
    SparseMatrixViennaCL *sparseMatrix = new SparseMatrixViennaCL();
    sparseMatrix = dynamic_cast<SparseMatrixViennaCL*>(sparseMatrix->LeftPaddedDiagonal(3, 3, 0));

    // Test if created properly.
    bool equals = true;
    for(int i = 0; i < sparseMatrix->num_rows; i++){
        for(int j = 0; j < sparseMatrix->num_cols; j++){
            if(i == j){
                if(sparseMatrix->dense()(i, j) != 3)
                    equals = false;
            } else {
                if(sparseMatrix->dense()(i, j) != 0)
                    equals = false;
            }
        }
    }

    delete sparseMatrix;

    QVERIFY(equals);

}

void TestSparseMatrixViennaCL::createViennaCL_createFromEigenDense()
{
    // Create and fill Eigen dense matrix.
    dmat eigenDense = dmat(9, 9);
    int cont = 0;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++) {
            eigenDense(i, j) = cont;
            cont++;
        }
    }

    // Create ViennaCL sparse matrix from Eigen dense matrix.
    SparseMatrixViennaCL viennaSparse = SparseMatrixViennaCL(eigenDense);

    // Compare matrixes.
    bool equals = true;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++) {
            if(eigenDense(i, j) != viennaSparse.vcl_matrix(i, j))
                equals = false;
        }
    }

    QVERIFY(equals);
}

