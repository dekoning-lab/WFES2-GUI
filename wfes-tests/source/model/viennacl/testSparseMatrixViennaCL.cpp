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
    cont = 0;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++) {
            if(eigenDense(i, j) != viennaSparse.vcl_matrix(i, j))
                test = false;
            if(eigenDense(i, j) != viennaSparse.data[cont])
                test = false;
            if(viennaSparse.cols[cont] != j)
                test = false;
            if(j == 8 && viennaSparse.row_index[i+1] != viennaSparse.data[cont])
                test = false;
            cont++;
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
    int cont = 0;
    for(int i = 0; i < sparseMatrix->num_rows; i++){
        for(int j = 0; j < sparseMatrix->num_cols; j++){
            if(i == j){
                if(sparseMatrix->vcl_matrix(i, j) != 3)
                    equals = false;
                if(sparseMatrix->data[cont] != 3 && sparseMatrix->cols[cont] != cont && sparseMatrix->row_index[cont] != cont) {
                    equals = false;
                }
                cont++;
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

    QVERIFY(true);
}

void TestSparseMatrixViennaCL::appendValues_appendRow()
{
    // Create a matrix with space for one empty row.
    SparseMatrixViennaCL sparseMatrix = SparseMatrixViennaCL(2,9);

    // Create a row to append.
    dvec eigenVec = dvec(9);
    for(int i = 0; i < 9; i++){
        eigenVec(i) = 9-i;
    }

    // Create a second row to append.
    dvec eigenVec2 = dvec(9);
    for(int i = 0; i < 9; i++){
        eigenVec2(i) = i;
    }

    // Append row.
    sparseMatrix.appendRow(eigenVec, 0, 9);
    sparseMatrix.appendRow(eigenVec2, 0, 9);

    // Copy to ViennaCL matrix.
    sparseMatrix.vcl_matrix.set(sparseMatrix.row_index, sparseMatrix.cols, sparseMatrix.data, sparseMatrix.num_rows, sparseMatrix.num_cols, sparseMatrix.num_non_zeros);

    // Compare matrixes.
    bool test = true;
    for(int j = 0; j < sparseMatrix.num_cols; j++){
        if(eigenVec(j) != sparseMatrix.vcl_matrix(0, j))
            test = false;
    }
    for(int j = 0; j < sparseMatrix.num_cols; j++){
        if(eigenVec2(j) != sparseMatrix.vcl_matrix(1, j))
            test = false;
    }

    // Test values.
    if(sparseMatrix.vcl_matrix.size1() != 2)
        test = false;
    if(sparseMatrix.vcl_matrix.size2() != 9)
        test = false;
    if(sparseMatrix.vcl_matrix.nnz() != 18)
        test = false;
    if(sparseMatrix.num_rows != 2)
        test = false;
    if(sparseMatrix.num_cols != 9)
        test = false;
    if(sparseMatrix.num_non_zeros != 18)
        test = false;

    QVERIFY(test);
}

void TestSparseMatrixViennaCL::appendValues_appendChunk()
{
    // Create a matrix with space for one empty row.
    SparseMatrixViennaCL sparseMatrix = SparseMatrixViennaCL(2,9);

    // Create a row to append.
    dvec eigenVec = dvec(5);
    for(int i = 0; i < 5; i++){
        eigenVec(i) = 5-i;
    }

    // Create a second row to append.
    dvec eigenVec2 = dvec(4);
    for(int i = 0; i < 4; i++){
        eigenVec2(i) = i;
    }

    sparseMatrix.appendChunk(eigenVec, 0, 0, 5);
    sparseMatrix.appendChunk(eigenVec2, 5, 0, 4);
    sparseMatrix.nextRow();
    sparseMatrix.appendChunk(eigenVec2, 0, 0, 4);
    sparseMatrix.appendChunk(eigenVec, 4, 0, 5);
    sparseMatrix.nextRow();

    // Copy to ViennaCL matrix.
    sparseMatrix.vcl_matrix.set(sparseMatrix.row_index, sparseMatrix.cols, sparseMatrix.data, sparseMatrix.num_rows, sparseMatrix.num_cols, sparseMatrix.num_non_zeros);

    // Compare matrixes.
    bool test = true;
    for(int j = 0; j < 5; j++){
        if(eigenVec(j) != sparseMatrix.vcl_matrix(0, j))
            test = false;
    }
    for(int j = 5; j < sparseMatrix.num_cols; j++){
        if(eigenVec2(j-5) != sparseMatrix.vcl_matrix(0, j))
            test = false;
    }
    for(int j = 0; j < 4; j++){
        if(eigenVec2(j) != sparseMatrix.vcl_matrix(1, j))
            test = false;
    }
    for(int j = 4; j < sparseMatrix.num_cols; j++){
        if(eigenVec(j-4) != sparseMatrix.vcl_matrix(1, j))
            test = false;
    }

    // Test values.
    if(sparseMatrix.vcl_matrix.size1() != 2)
        test = false;
    if(sparseMatrix.vcl_matrix.size2() != 9)
        test = false;
    if(sparseMatrix.vcl_matrix.nnz() != 18)
        test = false;
    if(sparseMatrix.num_rows != 2)
        test = false;
    if(sparseMatrix.num_cols != 9)
        test = false;
    if(sparseMatrix.num_non_zeros != 18)
        test = false;

    QVERIFY(test);
}

void TestSparseMatrixViennaCL::appendValues_appendValue()
{
    // Create a matrix with space for one empty row.
    SparseMatrixViennaCL sparseMatrix = SparseMatrixViennaCL(2,9);

    // Create a row to append.
    dvec eigenVec = dvec(5);
    for(int i = 0; i < 4; i++){
        eigenVec(i) = 4-i;
    }

    // Create a second row to append.
    dvec eigenVec2 = dvec(4);
    for(int i = 0; i < 4; i++){
        eigenVec2(i) = i;
    }

    sparseMatrix.appendChunk(eigenVec, 0, 0, 4);
    sparseMatrix.appendValue(100, 4);
    sparseMatrix.appendChunk(eigenVec2, 5, 0, 4);
    sparseMatrix.nextRow();
    sparseMatrix.appendChunk(eigenVec2, 0, 0, 4);
    sparseMatrix.appendValue(200, 4);
    sparseMatrix.appendChunk(eigenVec, 5, 0, 4);
    sparseMatrix.nextRow();

    // Copy to ViennaCL matrix.
    sparseMatrix.vcl_matrix.set(sparseMatrix.row_index, sparseMatrix.cols, sparseMatrix.data, sparseMatrix.num_rows, sparseMatrix.num_cols, sparseMatrix.num_non_zeros);

    // Compare matrixes.
    bool test = true;
    for(int j = 0; j < 4; j++){
        if(eigenVec(j) != sparseMatrix.vcl_matrix(0, j))
            test = false;
    }
    if(sparseMatrix.vcl_matrix(0, 4) != 100)
        test  = false;
    for(int j = 5; j < sparseMatrix.num_cols; j++){
        if(eigenVec2(j-5) != sparseMatrix.vcl_matrix(0, j))
            test = false;
    }
    for(int j = 0; j < 4; j++){
        if(eigenVec2(j) != sparseMatrix.vcl_matrix(1, j))
            test = false;
    }
    if(sparseMatrix.vcl_matrix(1, 4) != 200)
        test  = false;
    for(int j = 5; j < sparseMatrix.num_cols; j++){
        if(eigenVec(j-5) != sparseMatrix.vcl_matrix(1, j))
            test = false;
    }

    // Test values.
    if(sparseMatrix.vcl_matrix.size1() != 2)
        test = false;
    if(sparseMatrix.vcl_matrix.size2() != 9)
        test = false;
    if(sparseMatrix.vcl_matrix.nnz() != 18)
        test = false;
    if(sparseMatrix.num_rows != 2)
        test = false;
    if(sparseMatrix.num_cols != 9)
        test = false;
    if(sparseMatrix.num_non_zeros != 18)
        test = false;

    QVERIFY(test);
}

void TestSparseMatrixViennaCL::auxiliary_nextRow()
{
    // Create a matrix with space for one empty row.
    SparseMatrixViennaCL sparseMatrix = SparseMatrixViennaCL(2,9);

    // Create a row to append.
    dvec eigenVec = dvec(9);
    for(int i = 0; i < 9; i++){
        eigenVec(i) = 9-i;
    }

    // Create a second row to append.
    dvec eigenVec2 = dvec(9);
    for(int i = 0; i < 9; i++){
        eigenVec2(i) = i;
    }

    bool test = true;

    // Note: This tests compares the protected values of SparseMatrixViennaCL. For testing those values, make them public and uncomment following code fragments.

    /*
    if(sparseMatrix.current_row != 0)
        test = false;
    if(sparseMatrix.full != false)
        test = false;
    if(sparseMatrix.row_index_start != -1)
        test = false;
    */

    // Append row.
    sparseMatrix.appendRow(eigenVec, 0, 9);

    /*
    if(sparseMatrix.current_row != 1)
        test = false;
    if(sparseMatrix.full != false)
        test = false;
    if(sparseMatrix.row_index_start != -1)
        test = false;
    */

    sparseMatrix.appendRow(eigenVec2, 0, 9);

    /*
    if(sparseMatrix.current_row != 2)
        test = false;
    if(sparseMatrix.full != true)
        test = false;
    if(sparseMatrix.row_index_start != -1)
        test = false;
    */

    // Copy to ViennaCL matrix.
    sparseMatrix.vcl_matrix.set(sparseMatrix.row_index, sparseMatrix.cols, sparseMatrix.data, sparseMatrix.num_rows, sparseMatrix.num_cols, sparseMatrix.num_non_zeros);

    // Compare matrixes.
    for(int j = 0; j < sparseMatrix.num_cols; j++){
        if(eigenVec(j) != sparseMatrix.vcl_matrix(0, j))
            test = false;
    }
    for(int j = 0; j < sparseMatrix.num_cols; j++){
        if(eigenVec2(j) != sparseMatrix.vcl_matrix(1, j))
            test = false;
    }

    // Test values.
    if(sparseMatrix.vcl_matrix.size1() != 2)
        test = false;
    if(sparseMatrix.vcl_matrix.size2() != 9)
        test = false;
    if(sparseMatrix.vcl_matrix.nnz() != 18)
        test = false;
    if(sparseMatrix.num_rows != 2)
        test = false;
    if(sparseMatrix.num_cols != 9)
        test = false;
    if(sparseMatrix.num_non_zeros != 18)
        test = false;

    QVERIFY(test);
}

void TestSparseMatrixViennaCL::auxiliary_approxEquals()
{
    // Create a matrix with space for one empty row.
    SparseMatrixViennaCL sparseMatrix = SparseMatrixViennaCL(2,9);
    SparseMatrixViennaCL sparseMatrix2 = SparseMatrixViennaCL(2,9);

    // Create a row to append.
    dvec eigenVec = dvec(9);
    for(int i = 0; i < 9; i++){
        eigenVec(i) = 9-i;
    }

    // Create a second row to append.
    dvec eigenVec2 = dvec(9);
    for(int i = 0; i < 9; i++){
        eigenVec2(i) = i;
    }

    sparseMatrix.appendRow(eigenVec, 0, 9);
    sparseMatrix.appendRow(eigenVec2, 0, 9);
    sparseMatrix2.appendRow(eigenVec, 0, 9);
    sparseMatrix2.appendRow(eigenVec2, 0, 9);

    bool test = true;
    test = sparseMatrix.approxEquals(sparseMatrix2);

    QVERIFY(true);

    sparseMatrix2.data[7] = sparseMatrix.data[7] + 0.1;

    test = !sparseMatrix.approxEquals(sparseMatrix2);

    // The tolerance is compared using < instead of <=, so if the difference is exactly 0.1 it will be marked as not equal, the difference has to be less than 0.1.
    test = !sparseMatrix.approxEquals(sparseMatrix2, 0.1);

    // In this case the tolerance is 0.1 and the difference 0.9, so it is accepted as equal.
    sparseMatrix2.data[7] = sparseMatrix.data[7] + 0.09;
    test = sparseMatrix.approxEquals(sparseMatrix2, 0.1);

    QVERIFY(test);

}

void TestSparseMatrixViennaCL::conversion_dense()
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

    // Compare viennacl matrix with generated dense.
    bool test = true;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++) {
            if(viennaSparse.vcl_matrix(i, j) != viennaSparse.dense()(i, j))
                test = false;
        }
    }

    QVERIFY(test);
}

void TestSparseMatrixViennaCL::conversion_getDiagCopy()
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


    dvec diag = viennaSparse.getDiagCopy();

    bool test = true;
    for(int i = 0; i < diag.size(); i++){
        if(diag(i) != viennaSparse.vcl_matrix(i, i))
            test = false;
    }

    QVERIFY(test);

}

void TestSparseMatrixViennaCL::conversion_getColCopy()
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

    dvec column = viennaSparse.getColCopy(0);

    bool test = true;
    for(int i = 0; i < viennaSparse.num_rows; i++) {
        if(viennaSparse.cols[i] == 0 && (viennaSparse.data[i] != column[i] || viennaSparse.vcl_matrix(i, 0) != column[i]))
            test = false;
    }

    QVERIFY(test);
}


