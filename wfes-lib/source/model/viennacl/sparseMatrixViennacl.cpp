#include "sparseMatrixViennacl.h"

using namespace wfes::vienna;
using namespace wfes::utils;

SparseMatrixViennaCL::SparseMatrixViennaCL() :
    SparseMatrix(0, 0),
    current_row(0), full(false),
    row_index_start(-1),
    data(nullptr), cols(nullptr), row_index(nullptr)
{

}

SparseMatrixViennaCL::SparseMatrixViennaCL(int numRows, int numCols) :
  SparseMatrix(numRows, numCols),
  current_row(0), full(false),
  row_index_start(-1),
  data(nullptr), cols(nullptr), row_index(nullptr)
{
  data = (double*)malloc(sizeof(double));
  cols = (int*) malloc(sizeof(int));
  row_index = (int*)malloc((numRows + 1) * sizeof(int));

  row_index[0] = 0;
}

SparseMatrixViennaCL::SparseMatrixViennaCL(dmat& eigenDenseMatrix) :
    SparseMatrix(eigenDenseMatrix.rows(), eigenDenseMatrix.cols()),
    current_row(0), full(true),
    row_index_start(-1),
    data(nullptr), cols(nullptr), row_index(nullptr)
{
    int nnz = (eigenDenseMatrix.array() != 0.0).count();
    num_non_zeros = nnz;
    data = (double*)malloc(nnz * sizeof(double));
    cols = (int*)malloc(nnz * sizeof(int));
    row_index = (int*)malloc((num_rows + 1) * sizeof(int));

    int info = 0;
    int* j = (int*)malloc(6 * sizeof(int));
    j[0] = 0; j[1] = 0; j[2] = 0;
    j[3] = 2; j[4] = num_non_zeros; j[5] = 1;

    int num_rows_l = (int)num_rows;
    int num_cols_l = (int)num_cols;
    /*
    mkl_ddnscsr(j, &(num_rows_l), &num_cols_l, eigenDenseMatrix.data(), &num_cols_l, data, cols, row_index, &info);
*/
    free(j);

    if(info != 0) throw std::runtime_error("SparseMatrix::dense(): Error processing row " + std::to_string(info));
/*
    mkl_sparse_d_create_csr(&handler, SPARSE_INDEX_BASE_ZERO, num_rows, num_cols, row_index, row_index + 1, cols, data);
*/
}

SparseMatrix* SparseMatrixViennaCL::LeftPaddedDiagonal(int dim, double x, int padLeft)
{

    SparseMatrixViennaCL* I = new SparseMatrixViennaCL(dim, padLeft + dim);
    I->full = true;
    I->num_non_zeros = dim;

    // could probably use a private constructor here
    double* data_new = (double*)realloc(I->data, I->num_non_zeros* sizeof(double));
    assert(data_new != NULL); I->data = data_new;

    int* cols_new = (int*)realloc(I->cols, I->num_cols * sizeof(int));
    assert(cols_new != NULL); I->cols = cols_new;

    for(int i = 0; i < I->num_non_zeros; i++) {
        I->data[i] = x;
        I->cols[i] = i + padLeft;
        I->row_index[i] = i;
    }
    I->row_index[dim] = I->num_non_zeros;
    /*
    mkl_sparse_d_create_csr(&I->handler, SPARSE_INDEX_BASE_ZERO, I->num_rows, I->num_cols, I->row_index, I->row_index + 1, I->cols, I->data);
    */
    return I;
}

SparseMatrixViennaCL::~SparseMatrixViennaCL(){
    free(data);
    free(cols);
    free(row_index);
}

void SparseMatrixViennaCL::appendRow(dvec &row, int col_start, int size)
{
    appendChunk(row, col_start, col_start, size);
    nextRow();
}

void SparseMatrixViennaCL::appendChunk(dvec &row, int m0, int r0, int size)
{
    // Test not full
    assert(!full);
    // Update size
    int new_size = num_non_zeros + size;

    // Get row index start
    row_index_start = positiveMin(row_index_start, num_non_zeros);

    // Insert Columns
    int* cols_new = (int*) realloc(cols, new_size * sizeof(int));
    assert(cols_new != NULL); cols = cols_new;
    lvec col_idx = closedRange(m0, m0 + size);
    memcpy(&cols[num_non_zeros], col_idx.data(), size * sizeof(int));

    // Insert Data
    double* data_new = (double*) realloc(data, new_size * sizeof(double));
    assert(data_new != NULL); data = data_new;
    memcpy(&(data[num_non_zeros]), &(row.data()[r0]), size * sizeof(double));

    num_non_zeros += size;
}

void SparseMatrixViennaCL::appendValue(double value, int j)
{
    int new_size = num_non_zeros + 1;

    row_index_start = positiveMin(row_index_start, num_non_zeros);

    // Columns
    int* cols_new = (int*) realloc(cols, new_size * sizeof(int));
    assert(cols_new != NULL); cols = cols_new;
    cols[new_size - 1] = j;

    // Data
    double* data_new = (double*) realloc(data, new_size * sizeof(double));
    assert(data_new != NULL); data = data_new;
    data[new_size - 1] = value;

    num_non_zeros += 1;
}

void SparseMatrixViennaCL::nextRow()
{
    assert(!full);
    row_index[current_row] = row_index_start;
    current_row += 1;
    row_index_start = -1; // special value - will be reset to min of row_index on next row
    if(current_row == num_rows) {
        // Matrix complete
        full = true;
        row_index[num_rows] = num_non_zeros;
        /*
        mkl_sparse_d_create_csr(&handler, SPARSE_INDEX_BASE_ZERO, num_rows, num_cols, row_index, row_index + 1, cols, data);
        */
    }
}

void SparseMatrixViennaCL::debugPrint()
{
    std::cout << "data:    " << std::endl;
    printBuffer(data, (size_t)num_non_zeros);
    std::cout << "cols:   " << std::endl;
    printBuffer(cols, (size_t)num_non_zeros);
    std::cout << "row_index:  " << std::endl;
    printBuffer(row_index, (size_t)(num_rows + 1));
}

bool SparseMatrixViennaCL::approxEquals(const SparseMatrix &rhs, double tol, bool verbose)
{
    /*
    if(num_rows != static_cast<const SparseMatrixPardiso&>(rhs).num_rows) return false;
    if(num_cols != static_cast<const SparseMatrixPardiso&>(rhs).num_cols) return false;
    if(num_non_zeros != static_cast<const SparseMatrixPardiso&>(rhs).num_non_zeros) return false;

    for (int i = 0; i < num_rows; ++i) {
        for (int j = row_index[i]; j < row_index[i + 1]; ++j) {
            double diff = fabs(data[j] - static_cast<const SparseMatrixPardiso&>(rhs).data[j]);
            if(diff > tol || std::isnan(diff)) {
                if(verbose) {
                    fprintf(stderr, DPF " != " DPF " [%lld] (" DPF ", " DPF ")\n", data[j], static_cast<const SparseMatrixPardiso&>(rhs).data[j], j, diff, tol);
                }
                return false;
            }
        }
    }
    */
    return true;
}

dmat SparseMatrixViennaCL::dense()
{
    dmat dns(num_rows, num_cols);

    int info = 0;
    int* j = (int*)malloc(6 * sizeof(int));
    j[0] = 1; j[1] = 0; j[2] = 0;
    j[3] = 2; j[4] = num_non_zeros; j[5] = 1;

    int num_rows_l = (int)num_rows;
    int num_cols_l = (int)num_cols;
    /*
    mkl_ddnscsr(j, &num_rows_l, &num_cols_l, dns.data(), &num_cols_l, data, cols, row_index, &info);

    free(j);

    if(info != 0) throw std::runtime_error("SparseMatrix::dense(): Error processing row " + std::to_string(info));
*/
    return dns;
}

dvec SparseMatrixViennaCL::getDiagCopy()
{
    assert(num_rows == num_cols);

    dvec diag(num_rows);
    for (int i = 0; i < num_rows; ++i) {
        bool diag_found = false;
        for (int j = row_index[i]; j < row_index[i + 1]; ++j) {
            if (cols[j] == i) {
                diag[i] = data[j];
                diag_found = true;
            }
        }
        if (!diag_found) throw std::runtime_error("Diagonal entry uninitialized " + std::to_string(i));
    }

    return diag;
}

dvec SparseMatrixViennaCL::getColCopy(int c)
{
    dvec column = dvec::Zero(num_rows);
    for(int i = 0; i < num_rows; i++) {
        for(int j = row_index[i]; j < row_index[i + 1]; j++) {
            if (cols[j] == c) {
                column[i] = data[j];
                break;
            }
        }
    }
    return column;
}

dvec SparseMatrixViennaCL::getRowCopy(int i)
{
    //TODO
    return dvec();
}

dvec SparseMatrixViennaCL::multiply(dvec &x, bool transpose)
{

    int v_size = transpose ? num_cols : num_rows;
    transpose ? assert(x.size() == num_rows) : assert(x.size() == num_cols);
    dvec y(v_size);
/*
    struct matrix_descr descr = {.type = SPARSE_MATRIX_TYPE_GENERAL};
    sparse_operation_t op = transpose ? SPARSE_OPERATION_TRANSPOSE : SPARSE_OPERATION_NON_TRANSPOSE;

    mkl_sparse_d_mv(op, 1, handler, descr, x.data(), 0, y.data());
*/
    return y;
}

void SparseMatrixViennaCL::multiplyInPlaceRep(dvec &x, int times, bool transpose)
{
    /*
    transpose ? assert(x.size() == num_rows) : assert(x.size() == num_cols);
    dvec workspace(x.size());

    struct matrix_descr descr = {.type = SPARSE_MATRIX_TYPE_GENERAL};
    sparse_operation_t op = transpose ? SPARSE_OPERATION_TRANSPOSE : SPARSE_OPERATION_NON_TRANSPOSE;

    for(int i = 0; i < times; i++) {
        // it's not safe to write into the same memory - need to swap
        mkl_sparse_d_mv(op, 1, handler, descr, x.data(), 0, workspace.data());
        x = workspace;
    }*/
}

SparseMatrix* SparseMatrixViennaCL::multiply(SparseMatrix &B, bool transpose)
{

    sparse_operation_t op = transpose ? SPARSE_OPERATION_TRANSPOSE : SPARSE_OPERATION_NON_TRANSPOSE;

    SparseMatrixViennaCL *C = new SparseMatrixViennaCL(num_rows, static_cast<SparseMatrixViennaCL&>(B).num_cols);
/*
    sparse_status_t info = mkl_sparse_spmm(op, handler, static_cast<SparseMatrixViennaCL&>(B).handler, &C->handler);

    if(info != SPARSE_STATUS_SUCCESS) throw std::runtime_error("SparseMatrix::multiply(sparse): " + std::to_string(info));
*/
    return C;
}

void SparseMatrixViennaCL::subtractIdentity()
{
    for (int i = 0; i < num_rows; ++i) {
        for (int j = row_index[i]; j < row_index[i + 1]; ++j) {
            if (i == cols[j]) data[j] = 1.0 - data[j];
            else data[j] = -data[j];
        }
    }
}

double SparseMatrixViennaCL::search(int i, int j)
{
    if(i >= current_row) return NAN;
    for(int k = row_index[i]; k < row_index[i + 1]; k++) {
        if (cols[k] == j) {
            return data[k];
        }
    }
    return 0; // was not found
}

void SparseMatrixViennaCL::setValue(double x, int i, int j)
{
    //TODO
}

void SparseMatrixViennaCL::saveMarket(std::string path)
{
    FILE* out = fopen(path.c_str(), "w");
    fprintf(out, "%%%%MatrixMarket matrix coordinate real general\n");


    int num_rows_l = (int)num_rows;
    int num_cols_l = (int)num_cols;
    int num_non_zeros_l = (int)num_non_zeros;

    fprintf(out, LPF "\t" LPF "\t" LPF "\n", num_rows_l, num_cols_l, num_non_zeros_l);

    for (int i = 0; i < num_rows; ++i) {
        for (int j = row_index[i]; j < row_index[i + 1]; ++j) {
            fprintf(out, LPF "\t" LPF "\t" DPF "\n", i + 1, (int)cols[j] + 1, data[j]);
        }
    }
    fclose(out);
}
