#include "solverViennaCL.h"


using namespace wfes::vienna;

SolverViennaCL::SolverViennaCL(SparseMatrixViennaCL &A, std::string solver, std::string preconditioner) : Solver(A), solver(solver), preconditioner(preconditioner)
{

#ifdef VIENNACL_WITH_OPENMP
    omp_set_num_threads(wfes::config::Config::n_threads);
#endif

}

SolverViennaCL::~SolverViennaCL()
{

}

void SolverViennaCL::preprocess()
{

}

dvec SolverViennaCL::solve(dvec &b, bool transpose)
{
    dvec res = dvec(b.size());

    if(this->solver.compare("MixedCG") == 0) {
        res = solve_mixed_cg(b, transpose);
    }
    else if(this->solver.compare("CG") == 0) {
        res = solve_cg(b, transpose);
    }
    else if(this->solver.compare("BicGStab") == 0) {
        res = solve_bicgstab(b, transpose);
    }
    else if(this->solver.compare("GMRes") == 0) {
        res = solve_gmres(b, transpose);
    }
    return res;
}

dvec SolverViennaCL::solve_mixed_cg(dvec &b, bool transpose)
{

    // Eigen vector to ViennaCL vector.
    viennacl::vector<double> vcl_vec(b.size());
    copy(b, vcl_vec);

    viennacl::vector<double> vcl_res = viennacl::vector<double>(b.size());

    wfes::vienna::SparseMatrixViennaCL mat = static_cast<wfes::vienna::SparseMatrixViennaCL&>(m);

    if(transpose) {
        viennacl::compressed_matrix<double> vcl_transposed(mat.vcl_matrix.size1(), mat.vcl_matrix.size2());
        viennacl::linalg::detail::amg::amg_transpose(mat.vcl_matrix, vcl_transposed);
        // Solve transposed.
        vcl_res = viennacl::linalg::solve(vcl_transposed, vcl_vec, viennacl::linalg::mixed_precision_cg_tag());
    } else {
        // Solve non transposed.
        vcl_res = viennacl::linalg::solve(mat.vcl_matrix, vcl_vec, viennacl::linalg::mixed_precision_cg_tag());
    }

    dvec res = dvec(b.size());
    copy(vcl_res, res);

    return res;
}

dvec SolverViennaCL::solve_cg(dvec &b, bool transpose)
{
    // Eigen vector to ViennaCL vector.
    viennacl::vector<double> vcl_vec(b.size());
    copy(b, vcl_vec);

    viennacl::vector<double> vcl_res = viennacl::vector<double>(b.size());

    wfes::vienna::SparseMatrixViennaCL mat = static_cast<wfes::vienna::SparseMatrixViennaCL&>(m);

    if(transpose) {
        viennacl::compressed_matrix<double> vcl_transposed(mat.vcl_matrix.size1(), mat.vcl_matrix.size2());
        viennacl::linalg::detail::amg::amg_transpose(mat.vcl_matrix, vcl_transposed);
        // Solve transposed.
        vcl_res = viennacl::linalg::solve(vcl_transposed, vcl_vec, viennacl::linalg::cg_tag());
    } else {
        // Solve non transposed.
        vcl_res = viennacl::linalg::solve(mat.vcl_matrix, vcl_vec, viennacl::linalg::cg_tag());
    }

    dvec res = dvec(b.size());
    copy(vcl_res, res);

    return res;
}

dvec SolverViennaCL::solve_bicgstab(dvec &b, bool transpose)
{
    // Eigen vector to ViennaCL vector.
    viennacl::vector<double> vcl_vec(b.size());
    copy(b, vcl_vec);

    viennacl::vector<double> vcl_res = viennacl::vector<double>(b.size());
    viennacl::linalg::bicgstab_tag my_bicgstab_tag(1e-5, 200, 100);

    wfes::vienna::SparseMatrixViennaCL mat = static_cast<wfes::vienna::SparseMatrixViennaCL&>(m);

    if(transpose) {
        viennacl::compressed_matrix<double> vcl_transposed(mat.vcl_matrix.size1(), mat.vcl_matrix.size2());
        viennacl::linalg::detail::amg::amg_transpose(mat.vcl_matrix, vcl_transposed);
        // Solve transposed.
        vcl_res = viennacl::linalg::solve(vcl_transposed, vcl_vec, my_bicgstab_tag);
    } else {
        // Solve non transposed.
        vcl_res = viennacl::linalg::solve(mat.vcl_matrix, vcl_vec, my_bicgstab_tag);
    }

    dvec res = dvec(b.size());
    copy(vcl_res, res);

    return res;
}

dvec SolverViennaCL::solve_gmres(dvec &b, bool transpose)
{
    // Eigen vector to ViennaCL vector.
    viennacl::vector<double> vcl_vec(b.size());
    copy(b, vcl_vec);

    viennacl::vector<double> vcl_res = viennacl::vector<double>(b.size());
    viennacl::linalg::gmres_tag my_gmres_tag(1e-5, 200, 100);

    wfes::vienna::SparseMatrixViennaCL mat = static_cast<wfes::vienna::SparseMatrixViennaCL&>(m);

    viennacl::linalg::chow_patel_tag chow_patel_ilu_config;
    chow_patel_ilu_config.sweeps(1);       // nonlinear sweeps
    chow_patel_ilu_config.jacobi_iters(1); // Jacobi iterations per triangular 'solve' Rx=r

    if(transpose) {
        viennacl::compressed_matrix<double> vcl_transposed(mat.vcl_matrix.size1(), mat.vcl_matrix.size2());
        viennacl::linalg::detail::amg::amg_transpose(mat.vcl_matrix, vcl_transposed);

        // create and compute preconditioner:
        viennacl::linalg::chow_patel_ilu_precond< viennacl::compressed_matrix<double> > chow_patel_ilu(vcl_transposed, chow_patel_ilu_config);

        // Solve transposed.
        vcl_res = viennacl::linalg::solve(vcl_transposed, vcl_vec, my_gmres_tag, chow_patel_ilu);
    } else {
        // create and compute preconditioner:
        viennacl::linalg::chow_patel_ilu_precond< viennacl::compressed_matrix<double> > chow_patel_ilu(mat.vcl_matrix, chow_patel_ilu_config);

        // Solve non transposed.
        vcl_res = viennacl::linalg::solve(mat.vcl_matrix, vcl_vec, my_gmres_tag, chow_patel_ilu);
    }

    dvec res = dvec(b.size());
    copy(vcl_res, res);

    return res;
}

dmat SolverViennaCL::solve_multiple(dmat &b, bool transpose)
{
    return dmat();
}
