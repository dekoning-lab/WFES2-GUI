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
    sparseMatrix = new SparseMatrixViennaCL();

    sparseMatrix = dynamic_cast<SparseMatrixViennaCL*>(sparseMatrix->LeftPaddedDiagonal(3, 3, 0));

    bool equals = true;
    for(int i = 0; i < sparseMatrix->num_rows; i++){
        for(int j = 0; j < sparseMatrix->num_cols; j++){
            qDebug() << sparseMatrix->dense()(i, j) << ", ";
            if(i == j){
                if(sparseMatrix->dense()(i, j) != 3)
                    equals = false;
            } else {
                if(sparseMatrix->dense()(i, j) != 0)
                    equals = false;
            }
        }
        qDebug() << "/n ";
    }

    qDebug() << "lib.execute();/n";
    lib.execute();
    qDebug() << "lib.execute() exit;/n";
    QVERIFY(equals);

}

void TestSparseMatrixViennaCL::testmatrix()
{

    QVERIFY(true);
}
