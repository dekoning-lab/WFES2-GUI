#include "solverPardisoProject.h"

void wfes::pardisoproject::PardisoProjectSolver::convertToFortranNotation()
{
    for(int i = 0; i < mat->num_non_zeros; i++)
        mat->cols[i] += 1;

    for(int i = 0; i < mat->num_rows+1 ; i++)
        mat->row_index += 1;
}
void wfes::pardisoproject::PardisoProjectSolver::convertToCNotation()
{
    for(int i = 0; i < mat->num_non_zeros; i++)
        mat->cols[i] -= 1;

    for(int i = 0; i < mat->num_rows+1 ; i++)
        mat->row_index -= 1;
}


wfes::pardisoproject::PardisoProjectSolver::PardisoProjectSolver(wfes::vienna::SparseMatrixViennaCL &A, int matrix_type, int message_level, int n_rhs)  :
    Solver(A), mtype(matrix_type), verbose(message_level), n_rhs(n_rhs) {

    mat = dynamic_cast<wfes::vienna::SparseMatrixViennaCL*>(&m);

    // Set some parameters...
    maxfct = 1;         /* Maximum number of numerical factorizations.  */
    mnum   = 1;         /* Which factorization to use. */
    error  = 0;         /* Initialize error flag */

    // Initialize pardiso and read license.
    pardisoinit (pt,  &mtype, &solver, iparm, dparm, &error);

    // Test if there is an error.
    if (error != 0)
    {
        if (error == -10 )
            qDebug() << "[PARDISO]: Error (" << error << ") - No license file found.";
        if (error == -11 )
            qDebug() << "[PARDISO]: Error (" << error << ") - License is expired.";
        if (error == -12 )
            qDebug() << "[PARDISO]: Error (" << error << ") - Wrong username or hostname.";
    }
    else
        qDebug() << "[PARDISO]: License check was successful...";

    // Set number of threads using environment variable.
    qputenv("OMP_NUM_THREADS", "1");
    iparm[2]  = 1;
}

wfes::pardisoproject::PardisoProjectSolver::~PardisoProjectSolver()
{
    int phase = MKL_PARDISO_SOLVER_PHASE_RELEASE_MEMORY_ALL;
    pardiso (pt, &maxfct, &mnum, &mtype, &phase,
              &mat->num_cols, mat->data, mat->row_index, mat->cols, &idum, &n_rhs,
             iparm, &verbose, &ddum, &ddum, &error,  dparm);
}

void wfes::pardisoproject::PardisoProjectSolver::preprocess()
{
    int phase = MKL_PARDISO_SOLVER_PHASE_ANALYSIS;

    qDebug() <<  mat->data[0];

    convertToFortranNotation();

    pardiso (pt, &maxfct, &mnum, &mtype, &phase,
             &(mat->num_cols), mat->data, mat->row_index, mat->cols, &idum, &n_rhs,
             iparm, &verbose, &ddum, &ddum, &error,  dparm);

    if (error != 0) {
        qDebug() << "ERROR during symbolic factorization: " << error;
    }
    qDebug() << "Reordering completed...";
    qDebug() << "Number of nonzeros in factors: " << iparm[17];
    qDebug() << "Number of factorization MFLOPS: " << iparm[18];

    phase = MKL_PARDISO_SOLVER_PHASE_NUMERICAL_FACTORIZATION;

    pardiso (pt, &maxfct, &mnum, &mtype, &phase,
             &mat->num_cols, mat->data, mat->row_index, mat->cols, &idum, &n_rhs,
             iparm, &verbose, &ddum, &ddum, &error, dparm);

    convertToCNotation();

    if (error != 0) {
        qDebug() << "ERROR during numerical factorization: " << error;
    }
    qDebug() << "Factorization completed...";
}

dvec wfes::pardisoproject::PardisoProjectSolver::solve(dvec &b, bool transpose)
{

    convertToFortranNotation();

    int phase = MKL_PARDISO_SOLVER_PHASE_SOLVE_ITERATIVE_REFINEMENT;

    double res[b.size()];

    iparm[7] = 0;       /* Max numbers of iterative refinement steps. */
    if(transpose) iparm[MKL_PARDISO_SOLVE_OPTION] = MKL_PARDISO_SOLVE_TRANSPOSED;
    else iparm[MKL_PARDISO_SOLVE_OPTION] = MKL_PARDISO_DEFAULT;

    pardiso (pt, &maxfct, &mnum, &mtype, &phase,
             &mat->num_cols, mat->data, mat->row_index, mat->cols, &idum, &n_rhs,
             iparm, &verbose, b.data(), res, &error,  dparm);

    if (error != 0) {
        qDebug() << "ERROR during solution: " << error;
    }

    qDebug() << "Solve completed...";

    convertToCNotation();

    dvec ret(b.size());

    for(int i = 0; i < b.size(); i++)
        ret(i) = res[i];

    return ret;
}

dmat wfes::pardisoproject::PardisoProjectSolver::solve_multiple(dmat &b, bool transpose)
{

    int phase = MKL_PARDISO_SOLVER_PHASE_SOLVE_ITERATIVE_REFINEMENT;

    double res[b.size()];

    iparm[7] = 0;       /* Max numbers of iterative refinement steps. */
    if(transpose) iparm[MKL_PARDISO_SOLVE_OPTION] = MKL_PARDISO_SOLVE_TRANSPOSED;
    else iparm[MKL_PARDISO_SOLVE_OPTION] = MKL_PARDISO_DEFAULT;

    pardiso (pt, &maxfct, &mnum, &mtype, &phase,
             &mat->num_cols, mat->data, mat->row_index, mat->cols, &idum, &n_rhs,
             iparm, &verbose, b.data(), res, &error,  dparm);

    if (error != 0) {
        qDebug() << "ERROR during solution: " << error;
    }

    qDebug() << "Solve completed...";

    dmat ret(b.rows(), b.cols());

    for(int i = 0; i < n_rhs; i++) {
        for(int j = 0; j < b.cols(); j++) {
            ret(j, i) = res[i * b.cols() + j];
        }
    }
    return ret;
}

dvec wfes::pardisoproject::PardisoProjectSolver::get_diagonal()
{
    dvec d_factorized(mat->num_cols);
    dvec d_initial(mat->num_cols);

    //pardiso_getdiag(pt, d_factorized.data(), d_initial.data(), &mnum, &error);

    if(error == 1) throw std::runtime_error("PardisoSolver::get_diagonal(): Diagonal information not turned on before pardiso main loop: " + std::to_string(error));

    return d_factorized;
}
