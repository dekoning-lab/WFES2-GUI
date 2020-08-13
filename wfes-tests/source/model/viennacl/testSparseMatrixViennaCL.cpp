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

void TestSparseMatrixViennaCL::createViennaCL_createEmpty()
{
    SparseMatrixViennaCL viennaSparse = SparseMatrixViennaCL();
    bool test = true;
    if(viennaSparse.vcl_matrix.size1() != 0)
        test = false;
    if(viennaSparse.vcl_matrix.size2() != 0)
        test = false;
    if(viennaSparse.vcl_matrix.nnz() != 0)
        test = false;
    if(viennaSparse.num_rows != 0)
        test = false;
    if(viennaSparse.num_cols != 0)
        test = false;
    if(viennaSparse.num_non_zeros != 0)
        test = false;

    QVERIFY(test);
}

void TestSparseMatrixViennaCL::createViennaCL_createWithSize()
{
    SparseMatrixViennaCL viennaSparse = SparseMatrixViennaCL(3, 3);
    bool test = true;
    if(viennaSparse.vcl_matrix.size1() != 3)
        test = false;
    if(viennaSparse.vcl_matrix.size2() != 0)
        test = false;
    if(viennaSparse.vcl_matrix.nnz() != 0)
        test = false;
    if(viennaSparse.num_rows != 3)
        test = false;
    if(viennaSparse.num_cols != 3)
        test = false;
    if(viennaSparse.num_non_zeros != 0)
        test = false;

}

void TestSparseMatrixViennaCL::createViennaCL_createFromEigenDense()
{
    // Create and fill Eigen dense matrix.
    dmat eigenDense = dmat(9, 9);
    int cont = 0;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++) {
            eigenDense(i, j) = cont+1;
            cont++;
        }
    }

    // Create ViennaCL sparse matrix from Eigen dense matrix.
    SparseMatrixViennaCL viennaSparse = SparseMatrixViennaCL(eigenDense);

    // Compare matrixes.
    bool test = true;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++) {
            if(eigenDense(i, j) != viennaSparse.vcl_matrix(i, j))
                test = false;
        }
    }

    // Test values.
    if(viennaSparse.vcl_matrix.size1() != 9)
        test = false;
    if(viennaSparse.vcl_matrix.size2() != 9)
        test = false;
    if(viennaSparse.vcl_matrix.nnz() != 81)
        test = false;
    if(viennaSparse.num_rows != 9)
        test = false;
    if(viennaSparse.num_cols != 9)
        test = false;
    if(viennaSparse.num_non_zeros != 81)
        test = false;

    QVERIFY(test);
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
                if(sparseMatrix->vcl_matrix(i, j) != 3)
                    equals = false;
            } else {
                if(sparseMatrix->vcl_matrix(i, j) != 0)
                    equals = false;
            }
        }
    }

    delete sparseMatrix;

    QVERIFY(equals);

}

void TestSparseMatrixViennaCL::destructMatrix_destructor()
{
    // Destruct not initialized.
    SparseMatrixViennaCL *nonInitializedSparseMatrix = new SparseMatrixViennaCL();
    delete nonInitializedSparseMatrix;

    // Allocated but not initialized.
    SparseMatrixViennaCL *allocatedNotInitializedSparseMatrix = new SparseMatrixViennaCL();
    allocatedNotInitializedSparseMatrix->data = (double*) malloc(2);
    allocatedNotInitializedSparseMatrix->cols = (int*) malloc(2);
    allocatedNotInitializedSparseMatrix->row_index = (int*) malloc(3);
    delete allocatedNotInitializedSparseMatrix;

    // Allocated and initialized
    SparseMatrixViennaCL *allocatedInitializedSparseMatrix = new SparseMatrixViennaCL();
    allocatedInitializedSparseMatrix->data = (double*) malloc(2);
    allocatedInitializedSparseMatrix->data[0] = 2.2;
    allocatedInitializedSparseMatrix->data[1] = 444.2;
    allocatedInitializedSparseMatrix->cols = (int*) malloc(2);
    allocatedInitializedSparseMatrix->cols[0] = 5;
    allocatedInitializedSparseMatrix->cols[0] = 6;
    allocatedInitializedSparseMatrix->row_index = (int*) malloc(3);
    allocatedInitializedSparseMatrix->row_index[0] = 5;
    allocatedInitializedSparseMatrix->row_index[0] = 6;
    delete allocatedInitializedSparseMatrix;
}


