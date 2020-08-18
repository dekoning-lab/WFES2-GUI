#include "testSparseMatrixPardiso.h"

using namespace wfes::pardiso;

static TestSparseMatrixPardiso instance;

TestSparseMatrixPardiso::TestSparseMatrixPardiso() : TestSuite("TestSparseMatrixPardiso")
{

}

void TestSparseMatrixPardiso::initTestCase()
{

}

void TestSparseMatrixPardiso::cleanUpTestCase()
{

}

void TestSparseMatrixPardiso::init()
{

}

void TestSparseMatrixPardiso::cleanup()
{

}

void TestSparseMatrixPardiso::createMatrix_createDiagMatrix()
{
    SparseMatrixPardiso *sparseMatrix = new SparseMatrixPardiso();

    sparseMatrix = dynamic_cast<SparseMatrixPardiso*>(sparseMatrix->LeftPaddedDiagonal(3, 3, 0));

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
