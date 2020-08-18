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

    QVERIFY(test);
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

void TestSparseMatrixViennaCL::conversion_getRowCopy()
{
    //TODO Not implemented in wfes-lib.
    QVERIFY(true);
}

void TestSparseMatrixViennaCL::operator_multiplyVector()
{
    bool test = true;

    // Create and fill Eigen dense matrix.
    dmat eigenDense = dmat(4, 4);
    int cont = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++) {
            eigenDense(i, j) = cont+1;
            cont++;
        }
    }

    // Create ViennaCL sparse matrix from Eigen dense matrix.
    SparseMatrixViennaCL *viennaSparse = new SparseMatrixViennaCL(eigenDense);

    dvec column = viennaSparse->getColCopy(0);
    dvec res = dvec(column.size());

    // Non zeros non transpose
    // |  1  2  3  4 |   |  1 |   |  90 |
    // |  5  6  7  8 |   |  5 |   | 202 |
    // |  9 10 11 12 | * |  9 | = | 314 |
    // | 13 14 15 16 |   | 13 |   | 426 |

    res = viennaSparse->multiply(column, false);

    if(res[0] != 90)
        test = false;
    if(res[1] != 202)
        test = false;
    if(res[2] != 314)
        test = false;
    if(res[3] != 426)
        test = false;

    // Non zeros transpose
    // | 1 5  9 13 |   |  1 |   | 276 |
    // | 2 6 10 14 |   |  5 |   | 304 |
    // | 3 7 11 15 | * |  9 | = | 314 |
    // | 4 8 12 16 |   | 13 |   | 426 |

    res = viennaSparse->multiply(column, true);

    if(res[0] != 276)
        test = false;
    if(res[1] != 304)
        test = false;
    if(res[2] != 332)
        test = false;
    if(res[3] != 360)
        test = false;

    // Zeros non transpose
    // | 0  2  0  4 |   |  1 |   |  62 |
    // | 5  6  7  8 |   |  5 |   | 202 |
    // | 9 10 11  0 | * |  9 | = | 158 |
    // | 0  0 15 16 |   | 13 |   | 343 |

    // Set new values for zeros.
    eigenDense(0, 0) = 0;
    eigenDense(0, 2) = 0;
    eigenDense(2, 3) = 0;
    eigenDense(3, 0) = 0;
    eigenDense(3, 1) = 0;

    // Create ViennaCL sparse matrix from Eigen dense matrix.
    delete viennaSparse;
    viennaSparse = new SparseMatrixViennaCL(eigenDense);

    res = viennaSparse->multiply(column, false);

    if(res[0] != 62)
        test = false;
    if(res[1] != 202)
        test = false;
    if(res[2] != 158)
        test = false;
    if(res[3] != 343)
        test = false;


    // Zeros transpose
    // | 0 5  9  0 |   |  1 |   | 106 |
    // | 2 6 10  0 |   |  5 |   | 122 |
    // | 0 7 11 15 | * |  9 | = | 329 |
    // | 4 8  0 16 |   | 13 |   | 252 |

    res = viennaSparse->multiply(column, true);

    if(res[0] != 106)
        test = false;
    if(res[1] != 122)
        test = false;
    if(res[2] != 329)
        test = false;
    if(res[3] != 252)
        test = false;

    QVERIFY(test);
}

void TestSparseMatrixViennaCL::operator_multiplyVectorInPlace()
{
    bool test = true;

    // Create and fill Eigen dense matrix.
    dmat eigenDense = dmat(4, 4);
    int cont = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++) {
            eigenDense(i, j) = cont+1;
            cont++;
        }
    }

    // Create ViennaCL sparse matrix from Eigen dense matrix.
    SparseMatrixViennaCL *viennaSparse = new SparseMatrixViennaCL(eigenDense);

    dvec column = viennaSparse->getColCopy(0);
    dvec res = dvec(column.size());

    // Non zeros non transpose
    // |  1  2  3  4 |   |  1 |   |  90 |
    // |  5  6  7  8 |   |  5 |   | 202 |
    // |  9 10 11 12 | * |  9 | = | 314 |
    // | 13 14 15 16 |   | 13 |   | 426 |

    viennaSparse->multiplyInPlaceRep(column, 1, false);

    if(column[0] != 90)
        test = false;
    if(column[1] != 202)
        test = false;
    if(column[2] != 314)
        test = false;
    if(column[3] != 426)
        test = false;

    // Non zeros transpose
    // | 1 5  9 13 |   |  1 |   | 276 |
    // | 2 6 10 14 |   |  5 |   | 304 |
    // | 3 7 11 15 | * |  9 | = | 314 |
    // | 4 8 12 16 |   | 13 |   | 426 |
    column = viennaSparse->getColCopy(0);

    viennaSparse->multiplyInPlaceRep(column, 1, true);

    if(column[0] != 276)
        test = false;
    if(column[1] != 304)
        test = false;
    if(column[2] != 332)
        test = false;
    if(column[3] != 360)
        test = false;

    // Zeros non transpose
    // | 0  2  0  4 |   |  1 |   |  62 |
    // | 5  6  7  8 |   |  5 |   | 202 |
    // | 9 10 11  0 | * |  9 | = | 158 |
    // | 0  0 15 16 |   | 13 |   | 343 |
    column = viennaSparse->getColCopy(0);

    // Set new values for zeros.
    eigenDense(0, 0) = 0;
    eigenDense(0, 2) = 0;
    eigenDense(2, 3) = 0;
    eigenDense(3, 0) = 0;
    eigenDense(3, 1) = 0;

    // Create ViennaCL sparse matrix from Eigen dense matrix.
    SparseMatrixViennaCL *viennaSparseZeros = new SparseMatrixViennaCL(eigenDense);

    viennaSparseZeros->multiplyInPlaceRep(column, 1, false);

    if(column[0] != 62)
        test = false;
    if(column[1] != 202)
        test = false;
    if(column[2] != 158)
        test = false;
    if(column[3] != 343)
        test = false;

    // Zeros transpose
    // | 0 5  9  0 |   |  1 |   | 106 |
    // | 2 6 10  0 |   |  5 |   | 122 |
    // | 0 7 11 15 | * |  9 | = | 329 |
    // | 4 8  0 16 |   | 13 |   | 252 |
    column = viennaSparse->getColCopy(0);

    viennaSparseZeros->multiplyInPlaceRep(column, 1, true);

    if(column[0] != 106)
        test = false;
    if(column[1] != 122)
        test = false;
    if(column[2] != 329)
        test = false;
    if(column[3] != 252)
        test = false;


    // Zeros non transpose 2 times
    // | 0  2  0  4 |   |  1 |   |  62 |     | 0  2  0  4 |   |  62 |   | 1776 |
    // | 5  6  7  8 |   |  5 |   | 202 |     | 5  6  7  8 |   | 202 |   | 5372 |
    // | 9 10 11  0 | * |  9 | = | 158 |  -> | 9 10 11  0 | * | 158 | = | 4316 |
    // | 0  0 15 16 |   | 13 |   | 343 |     | 0  0 15 16 |   | 343 |   | 7858 |
    column = viennaSparse->getColCopy(0);

    viennaSparseZeros->multiplyInPlaceRep(column, 2, false);

    if(column[0] != 1776)
        test = false;
    if(column[1] != 5372)
        test = false;
    if(column[2] != 4316)
        test = false;
    if(column[3] != 7858)
        test = false;

    // Zeros transpose 3 times
    // | 0 5  9  0 |   |  1 |   | 106 |    | 0 5  9  0 |   | 106 |   | 3571 |    | 0 5  9  0 |   | 3571 |   |  95447 |
    // | 2 6 10  0 |   |  5 |   | 122 |    | 2 6 10  0 |   | 122 |   | 4234 |    | 2 6 10  0 |   | 4234 |   | 115076 |
    // | 0 7 11 15 | * |  9 | = | 329 | -> | 0 7 11 15 | * | 329 | = | 8253 | -> | 0 7 11 15 | * | 8253 | = | 201901 |
    // | 4 8  0 16 |   | 13 |   | 252 |    | 4 8  0 16 |   | 252 |   | 5432 |    | 4 8  0 16 |   | 5432 |   | 135068 |
    column = viennaSparse->getColCopy(0);

    viennaSparseZeros->multiplyInPlaceRep(column, 3, true);

    if(column[0] != 95447)
        test = false;
    if(column[1] != 115076)
        test = false;
    if(column[2] != 201901)
        test = false;
    if(column[3] != 135068)
        test = false;

    delete viennaSparse;
    delete viennaSparseZeros;

    QVERIFY(test);

}

void TestSparseMatrixViennaCL::operator_multiplyMatrix()
{

    bool test = true;

    // Create and fill Eigen dense matrix.
    dmat eigenDense = dmat(4, 4);
    int cont = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++) {
            eigenDense(i, j) = cont+1;
            cont++;
        }
    }

    // Non zeros non transpose
    // |  1  2  3  4 |   |  1  2  3  4 |   |  90 100 110 120 |
    // |  5  6  7  8 |   |  5  6  7  8 |   | 202 228 254 280 |
    // |  9 10 11 12 | * |  9 10 11 12 | = | 314 356 398 440 |
    // | 13 14 15 16 |   | 13 14 15 16 |   | 426 484 542 600 |

    // Create ViennaCL sparse matrix from Eigen dense matrix.
    SparseMatrixViennaCL viennaSparse = SparseMatrixViennaCL(eigenDense);
    SparseMatrixViennaCL viennaSparse2 = SparseMatrixViennaCL(eigenDense);
    SparseMatrixViennaCL result = *(static_cast<SparseMatrixViennaCL*>(viennaSparse.multiply(viennaSparse2, false)));

    if(result.vcl_matrix(0, 0) != 90)
         test = false;
    if(result.vcl_matrix(0, 1) != 100)
         test = false;
    if(result.vcl_matrix(0, 2) != 110)
         test = false;
    if(result.vcl_matrix(0, 3) != 120)
         test = false;

    if(result.vcl_matrix(1, 0) != 202)
         test = false;
    if(result.vcl_matrix(1, 1) != 228)
         test = false;
    if(result.vcl_matrix(1, 2) != 254)
         test = false;
    if(result.vcl_matrix(1, 3) != 280)
         test = false;

    if(result.vcl_matrix(2, 0) != 314)
         test = false;
    if(result.vcl_matrix(2, 1) != 356)
         test = false;
    if(result.vcl_matrix(2, 2) != 398)
         test = false;
    if(result.vcl_matrix(2, 3) != 440)
         test = false;

    if(result.vcl_matrix(3, 0) != 426)
         test = false;
    if(result.vcl_matrix(3, 1) != 484)
         test = false;
    if(result.vcl_matrix(3, 2) != 542)
         test = false;
    if(result.vcl_matrix(3, 3) != 600)
         test = false;


    // Zeros non transpose
    // | 0  2  0  4 |   | 0  2  0  4 |   |  10  12  74  80 |
    // | 5  6  7  8 |   | 5  6  7  8 |   |  93 116 239 196 |
    // | 9 10 11  0 | * | 9 10 11  0 | = | 149 188 191 116 |
    // | 0  0 15 16 |   | 0  0 15 16 |   | 135 150 405 256 |

    // Set new values for zeros.
    eigenDense(0, 0) = 0;
    eigenDense(0, 2) = 0;
    eigenDense(2, 3) = 0;
    eigenDense(3, 0) = 0;
    eigenDense(3, 1) = 0;

    // Create ViennaCL sparse matrix from Eigen dense matrix.
    SparseMatrixViennaCL viennaSparse3 = SparseMatrixViennaCL(eigenDense);
    SparseMatrixViennaCL viennaSparse4 = SparseMatrixViennaCL(eigenDense);
    SparseMatrixViennaCL result2 = *(static_cast<SparseMatrixViennaCL*>(viennaSparse3.multiply(viennaSparse4, false)));


    if(result2.vcl_matrix(0, 0) != 10)
         test = false;
    if(result2.vcl_matrix(0, 1) != 12)
         test = false;
    if(result2.vcl_matrix(0, 2) != 74)
         test = false;
    if(result2.vcl_matrix(0, 3) != 80)
         test = false;

    if(result2.vcl_matrix(1, 0) != 93)
         test = false;
    if(result2.vcl_matrix(1, 1) != 116)
         test = false;
    if(result2.vcl_matrix(1, 2) != 239)
         test = false;
    if(result2.vcl_matrix(1, 3) != 196)
         test = false;

    if(result2.vcl_matrix(2, 0) != 149)
         test = false;
    if(result2.vcl_matrix(2, 1) != 188)
         test = false;
    if(result2.vcl_matrix(2, 2) != 191)
         test = false;
    if(result2.vcl_matrix(2, 3) != 116)
         test = false;

    if(result2.vcl_matrix(3, 0) != 135)
         test = false;
    if(result2.vcl_matrix(3, 1) != 150)
         test = false;
    if(result2.vcl_matrix(3, 2) != 405)
         test = false;
    if(result2.vcl_matrix(3, 3) != 256)
         test = false;




    // Zeros transpose
    // | 0  5  9  0 |   | 0  2  0  4 |   |  10  12  74  80 |
    // | 2  6 10  0 |   | 5  6  7  8 |   |  93 116 239 196 |
    // | 0  7 11 15 | * | 9 10 11  0 | = | 149 188 191 116 |
    // | 4  8  0 16 |   | 0  0 15 16 |   | 135 150 405 256 |

    // Create ViennaCL sparse matrix from Eigen dense matrix.
    SparseMatrixViennaCL viennaSparse5 = SparseMatrixViennaCL(eigenDense);
    SparseMatrixViennaCL viennaSparse6 = SparseMatrixViennaCL(eigenDense);
    SparseMatrixViennaCL result3 = *(static_cast<SparseMatrixViennaCL*>(viennaSparse3.multiply(viennaSparse4, true)));

    if(result3.vcl_matrix(0, 0) != 106)
         test = false;
    if(result3.vcl_matrix(0, 1) != 120)
         test = false;
    if(result3.vcl_matrix(0, 2) != 134)
         test = false;
    if(result3.vcl_matrix(0, 3) != 40)
         test = false;

    if(result3.vcl_matrix(1, 0) != 120)
         test = false;
    if(result3.vcl_matrix(1, 1) != 140)
         test = false;
    if(result3.vcl_matrix(1, 2) != 152)
         test = false;
    if(result3.vcl_matrix(1, 3) != 56)
         test = false;

    if(result3.vcl_matrix(2, 0) != 134)
         test = false;
    if(result3.vcl_matrix(2, 1) != 152)
         test = false;
    if(result3.vcl_matrix(2, 2) != 395)
         test = false;
    if(result3.vcl_matrix(2, 3) != 296)
         test = false;

    if(result3.vcl_matrix(3, 0) != 40)
         test = false;
    if(result3.vcl_matrix(3, 1) != 56)
         test = false;
    if(result3.vcl_matrix(3, 2) != 296)
         test = false;
    if(result3.vcl_matrix(3, 3) != 336)
         test = false;

    QVERIFY(test);

}

void TestSparseMatrixViennaCL::operator_substractIdentity()
{

    bool test = true;

    // Create and fill Eigen dense matrix.
    dmat eigenDense = dmat(4, 4);
    int cont = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++) {
            eigenDense(i, j) = cont+1;
            cont++;
        }
    }

    // Create ViennaCL sparse matrix from Eigen dense matrix.
    SparseMatrixViennaCL viennaSparse = SparseMatrixViennaCL(eigenDense);
    SparseMatrixViennaCL viennaSparse2 = SparseMatrixViennaCL(eigenDense);
    viennaSparse.subtractIdentity();

    // Compare viennacl matrix with generated dense.
    for(unsigned long i = 0; i < viennaSparse.vcl_matrix.size1(); i++){
        for(unsigned long j = 0; j < viennaSparse.vcl_matrix.size2(); j++) {
            if(i == j && ((1 - viennaSparse2.vcl_matrix(i, j)) != viennaSparse.vcl_matrix(i, j)))
                test = false;
            if(i != j && ((0 - viennaSparse2.vcl_matrix(i, j)) != viennaSparse.vcl_matrix(i, j)))
                test = false;
        }
    }

    QVERIFY(test);
}

void TestSparseMatrixViennaCL::operator_search()
{

    bool test = true;

    // Create and fill Eigen dense matrix.
    dmat eigenDense = dmat(4, 4);
    int cont = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++) {
            eigenDense(i, j) = cont+1;
            cont++;
        }
    }

    // Set new values for zeros.
    eigenDense(0, 0) = 0;
    eigenDense(0, 2) = 0;
    eigenDense(2, 3) = 0;
    eigenDense(3, 0) = 0;
    eigenDense(3, 1) = 0;


    // Create ViennaCL sparse matrix from Eigen dense matrix.
    SparseMatrixViennaCL viennaSparse = SparseMatrixViennaCL(eigenDense);

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++) {
            if(viennaSparse.vcl_matrix(i, j) != viennaSparse.search(i, j))
                test = false;
        }
    }

    QVERIFY(test);

}

void TestSparseMatrixViennaCL::operator_setValue()
{
    //TODO Not implemented in wfes-lib.
    QVERIFY(true);
}

void TestSparseMatrixViennaCL::inout_saveMarket()
{
    // Create and fill Eigen dense matrix.
    dmat eigenDense = dmat(4, 4);
    int cont = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++) {
            eigenDense(i, j) = cont+1;
            cont++;
        }
    }

    // Set new values for zeros.
    eigenDense(0, 0) = 0;
    eigenDense(0, 2) = 0;
    eigenDense(2, 3) = 0;
    eigenDense(3, 0) = 0;
    eigenDense(3, 1) = 0;


    // Create ViennaCL sparse matrix from Eigen dense matrix.
    SparseMatrixViennaCL viennaSparse = SparseMatrixViennaCL(eigenDense);

    viennaSparse.saveMarket("savedFile.csv");

    // Verify that the generated file has the requested information.
    QVERIFY(true);
}


