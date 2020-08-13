#include "sparseMatrixViennacl.h"

using namespace wfes::vienna;
using namespace wfes::utils;

SparseMatrixViennaCL::SparseMatrixViennaCL() :
    SparseMatrix(0, 0),
    current_row(0), full(false),
    row_index_start(-1),
    data(nullptr), cols(nullptr), row_index(nullptr)
{
    this->vcl_matrix = viennacl::compressed_matrix<double>(0, 0);
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

  this->vcl_matrix = viennacl::compressed_matrix<double>(num_rows, num_cols);
}

SparseMatrixViennaCL::SparseMatrixViennaCL(dmat& eigenDenseMatrix) :
    SparseMatrix(eigenDenseMatrix.rows(), eigenDenseMatrix.cols()),
    current_row(0), full(true),
    row_index_start(-1),
    data(new double()), cols(new int()), row_index(new int())
{
    Eigen::SparseMatrix<double, Eigen::RowMajor> eigenSparse = eigenDenseMatrix.sparseView();

    eigenSparse.makeCompressed();
    num_non_zeros = eigenSparse.nonZeros();
    num_cols = eigenSparse.cols();
    num_rows = eigenSparse.rows();

    if(eigenSparse.valuePtr() != nullptr)
        memcpy ( data, eigenSparse.valuePtr(), sizeof(double) );
    else
        data = nullptr;

    if(eigenSparse.innerIndexPtr() != nullptr)
        memcpy ( cols, eigenSparse.innerIndexPtr(), sizeof(double) );
    else
        cols = nullptr;

    if(eigenSparse.outerIndexPtr() != nullptr)
        memcpy ( row_index, eigenSparse.outerIndexPtr(), sizeof(double) );
    else
        row_index = nullptr;

    copy(eigenSparse, vcl_matrix);

}

SparseMatrix* SparseMatrixViennaCL::LeftPaddedDiagonal(int dim, double x, int padLeft)
{

    SparseMatrixViennaCL* I = new SparseMatrixViennaCL(dim, padLeft + dim);
    I->full = true;
    I->num_non_zeros = dim;

    // could probably use a private constructor here
    double* data_new = (double*)realloc(I->data, I->num_non_zeros* sizeof(double));
    assert(data_new != nullptr); I->data = data_new;

    int* cols_new = (int*)realloc(I->cols, I->num_cols * sizeof(int));
    assert(cols_new != nullptr); I->cols = cols_new;

    for(int i = 0; i < I->num_non_zeros; i++) {
        I->data[i] = x;
        I->cols[i] = i + padLeft;
        I->row_index[i] = i;
    }
    I->row_index[dim] = I->num_non_zeros;

    I->vcl_matrix.set(I->row_index, I->cols, I->data, I->num_rows, I->num_cols, I->num_non_zeros);

    return I;
}

SparseMatrixViennaCL::~SparseMatrixViennaCL(){
    if(data != nullptr) {
        free(data);
        data = nullptr;
    }
    if(cols != nullptr) {
        free(cols);
        cols = nullptr;
    }
    if(row_index != nullptr) {
        free(row_index);
        row_index = nullptr;
    }
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
    assert(cols_new != nullptr); cols = cols_new;
    ivec col_idx = closedRangeInt(m0, m0 + size);
    memcpy(&cols[num_non_zeros], col_idx.data(), size * sizeof(int));

    // Insert Data
    double* data_new = (double*) realloc(data, new_size * sizeof(double));
    assert(data_new != nullptr); data = data_new;
    memcpy(&(data[num_non_zeros]), &(row.data()[r0]), size * sizeof(double));

    num_non_zeros += size;
}

void SparseMatrixViennaCL::appendValue(double value, int j)
{
    int new_size = num_non_zeros + 1;

    row_index_start = positiveMin(row_index_start, num_non_zeros);

    // Columns
    int* cols_new = (int*) realloc(cols, new_size * sizeof(int));
    assert(cols_new != nullptr); cols = cols_new;
    cols[new_size - 1] = j;

    // Data
    double* data_new = (double*) realloc(data, new_size * sizeof(double));
    assert(data_new != nullptr); data = data_new;
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
    if(num_rows != static_cast<const SparseMatrixViennaCL&>(rhs).num_rows) return false;
    if(num_cols != static_cast<const SparseMatrixViennaCL&>(rhs).num_cols) return false;
    if(num_non_zeros != static_cast<const SparseMatrixViennaCL&>(rhs).num_non_zeros) return false;

    for (int i = 0; i < num_rows; ++i) {
        for (int j = row_index[i]; j < row_index[i + 1]; ++j) {
            double diff = fabs(data[j] - static_cast<const SparseMatrixViennaCL&>(rhs).data[j]);
            if(diff > tol || std::isnan(diff)) {
                if(verbose) {
                    fprintf(stderr, DPF " != " DPF " [%lld] (" DPF ", " DPF ")\n", data[j], static_cast<const SparseMatrixViennaCL&>(rhs).data[j], j, diff, tol);
                }
                return false;
            }
        }
    }
    return true;
}

viennacl::compressed_matrix<double> SparseMatrixViennaCL::get_viennacl_matrix()
{
    return vcl_matrix;
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
    //TODO Implementation (Not used).
    return dvec();
}

dvec SparseMatrixViennaCL::multiply(dvec &x, bool transpose)
{
    // Eigen vector to ViennaCL vector.
    viennacl::vector<double> vcl_vec(x.size());
    copy(x, vcl_vec);

    viennacl::vector<double> vcl_res;

    //Transpose if necessary.
    if(transpose) {
       viennacl::compressed_matrix<double> vcl_transposed(vcl_matrix.size1(), vcl_matrix.size2());
       viennacl::linalg::detail::amg::amg_transpose(vcl_matrix, vcl_transposed);
       // Multiply transposed.
       vcl_res = viennacl::linalg::prod(vcl_transposed, vcl_vec);
    } else {
        // Multiply non transposed.
        vcl_res = viennacl::linalg::prod(vcl_matrix, vcl_vec);
    }

    // Copy result to eigen vector.
    Eigen::VectorXd res;
    copy(res, vcl_res);

    return res;
}

void SparseMatrixViennaCL::multiplyInPlaceRep(dvec &x, int times, bool transpose)
{
    // Eigen vector to ViennaCL vector.
    viennacl::vector<double> vcl_vec(x.size());
    copy(x, vcl_vec);

    viennacl::vector<double> vcl_res_aux;

    // Iterate requested times.
    for(int i = 0; i < times; i++) {
        //Transpose if necessary.
        if(transpose) {
           viennacl::compressed_matrix<double> vcl_transposed(vcl_matrix.size1(), vcl_matrix.size2());
           viennacl::linalg::detail::amg::amg_transpose(vcl_matrix, vcl_transposed);
           // Multiply transposed.
           vcl_res_aux = viennacl::linalg::prod(vcl_transposed, vcl_vec);
           vcl_vec = vcl_res_aux;
        } else {
            // Multiply non transposed.
            vcl_res_aux = viennacl::linalg::prod(vcl_matrix, vcl_vec);
            vcl_vec = vcl_res_aux;
        }
    }
    // Copy result back to eigen vector.
    copy(vcl_vec, x);
}

SparseMatrix* SparseMatrixViennaCL::multiply(SparseMatrix &B, bool transpose)
{
    //
    SparseMatrixViennaCL* res = new SparseMatrixViennaCL(0, 0);

    //Transpose if necessary.
    if(transpose) {
       viennacl::compressed_matrix<double> vcl_transposed(vcl_matrix.size1(), vcl_matrix.size2());
       viennacl::linalg::detail::amg::amg_transpose(vcl_matrix, vcl_transposed);
       // Multiply transposed.
       res->vcl_matrix = viennacl::linalg::prod(vcl_transposed, static_cast<SparseMatrixViennaCL&>(B).get_viennacl_matrix());
    } else {
        // Multiply non transposed.
        res->vcl_matrix = viennacl::linalg::prod(vcl_matrix, static_cast<SparseMatrixViennaCL&>(B).get_viennacl_matrix());
    }

    // TODO IMPORTANT! Copy result to buffers. See how to access ViennaCL buffers.
    res->num_rows = res->vcl_matrix.size1();
    res->num_cols = res->vcl_matrix.size2();
    res->num_non_zeros = res->vcl_matrix.nnz();

    Eigen::SparseMatrix<double, Eigen::RowMajor> eigenSparse;
    copy(res->vcl_matrix, eigenSparse);
    eigenSparse.makeCompressed();

    data = eigenSparse.valuePtr();
    cols = eigenSparse.innerIndexPtr();
    row_index = eigenSparse.outerIndexPtr();

    return res;
}

void SparseMatrixViennaCL::subtractIdentity()
{
    for (int i = 0; i < num_rows; ++i) {
        for (int j = row_index[i]; j < row_index[i + 1]; ++j) {
            if (i == cols[j]) data[j] = 1.0 - data[j];
            else data[j] = -data[j];
        }
    }
    vcl_matrix.set(row_index, cols, data, num_rows, num_cols, num_non_zeros);
}

double SparseMatrixViennaCL::search(int i, int j)
{
    //if(i >= current_row) return NAN;
    for(int k = row_index[i]; k < row_index[i + 1]; k++) {
        if (cols[k] == j) {
            return data[k];
        }
    }
    return 0; // was not found
}

void SparseMatrixViennaCL::setValue(double x, int i, int j)
{
    //TODO Implementation (Not used).
}

void SparseMatrixViennaCL::saveMarket(std::string path)
{
    FILE* out = fopen(path.c_str(), "w");
    fprintf(out, "%%%%MatrixMarket matrix coordinate real general\n");

    for (int i = 0; i < num_rows; ++i) {
        for (int j = row_index[i]; j < row_index[i + 1]; ++j) {
        }
    }
    fclose(out);
}
