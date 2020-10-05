#ifndef WRIGHTFISHER_H
#define WRIGHTFISHER_H

#include "model/pardiso/solverPardiso.h"
#include <model/pardiso/sparseMatrixPardiso.h>

#include "model/solver/solver.h"
#include "model/solver/solverFactory.h"

#include "model/sparse-matrix/sparseMatrix.h"
#include <model/sparse-matrix/sparseMatrixFactory.h>

#include "utils/types.h"

#include "rdist.h"

#include "config/config.h"

#include <mkl.h>

namespace wfes{
    namespace wrightfisher {


        /**
         * @brief Enumeration containing possible absorption types.
         */
        enum absorption_type { NON_ABSORBING = 0, EXTINCTION_ONLY, FIXATION_ONLY, BOTH_ABSORBING };


        /**
         * @brief Get number corresponding to each absorption type.
         */
        inline int n_absorbing(absorption_type a_t) {
            switch (a_t) {
            case NON_ABSORBING:
                return 0;
            case EXTINCTION_ONLY:
                return 1;
            case FIXATION_ONLY:
                return 1;
            case BOTH_ABSORBING:
                return 2;
            default:
                //TODO Show as exception in GUI dialog.
                throw std::runtime_error("Unknown absorption type");
            }
        }

        /**
         * @brief Get description of each absorption type.
         */
        inline std::string absorption_type_desc(absorption_type a_t) {
            switch (a_t) {
            case NON_ABSORBING:
                return "No absorbing boundaries";
            case EXTINCTION_ONLY:
                return "Only extinction boundary is absorbing";
            case FIXATION_ONLY:
                return "Only fixation boundary is absorbing";
            case BOTH_ABSORBING:
                return "Both extinction and fixation boundaries are absorbing";
            default:
                //TODO Show as exception in GUI dialog.
                throw std::runtime_error("Unknown absorption type");
            }
        }

        class Row {
          protected:
            mutable bool valid = true;

          public:
            int start;
            int end;
            int size;
            double weight;
            dvec Q;

            Row(int start, int end)
                : start(start), end(end), size(end - start + 1), weight(1), Q(end - start + 1) {}
            Row() : start(0), end(0), size(0), weight(0), Q(0) {}

            Row(const Row &r) : start(r.start), end(r.end), size(r.size), weight(r.weight), Q(r.Q) {
                r.valid = false;
            }
        };

        struct Matrix {
          protected:
            mutable bool valid = true;

          public:
            int n_row;
            int n_col;
            int n_abs;
            smat *Q;
            dmat R;

            Matrix(std::string library, int n_row, int n_col, int n_abs)
                : n_row(n_row), n_col(n_col), n_abs(n_abs), R(n_row, n_abs) {
                Q = wfes::sparsematrix::SparseMatrixFactory::createSparseMatrix(library, n_row, n_col);
                R.setZero();
            }

            Matrix(const Matrix &m) : n_row(m.n_row), n_col(m.n_col), n_abs(m.n_abs), Q(m.Q), R(m.R) {
                m.valid = false;
            }

            ~Matrix(){
                delete dynamic_cast<wfes::pardiso::SparseMatrixPardiso*>(Q);
            }
        };

        double psi_diploid(const int i, const int N, const double s = 0, const double h = 0.5,
                           const double u = 1e-9, const double v = 1e-9);
        Row binom_row(const int size, const double p, const double alpha = 1e-20);

        // Harrod matrix to solve for equilibrium distribution
        Matrix EquilibriumSolvingMatrix(const int N, const double s = 0, const double h = 0.5,
                                        const double u = 1e-9, const double v = 1e-9,
                                        const double alpha = 1e-20, const bool verbose = false,
                                        const int block_size = 100, std::string library = "Pardiso");
        dmat Equilibrium(int N, double s = 0, double h = 0.5, double u = 1e-9, double v = 1e-9,
                         double alpha = 1e-20, bool verbose = false, std::string library = "Pardiso");

        // Single - one matrix of a given absorption type
        Matrix Single(const int Nx, const int Ny, const absorption_type a_t, const double s = 0,
                      const double h = 0.5, const double u = 1e-9, const double v = 1e-9,
                      const bool recurrent_mutation = true, const double alpha = 1e-20,
                      const bool verbose = false, const int block_size = 100, std::string library = "Pardiso");

        // Bounce - mutation return to a non-zero count
        Matrix Bounce(const int Nx, const int Ny, const double s = 0, const double h = 0.5,
                      const double u = 1e-9, const double v = 1e-9, const bool recurrent_mutation = true,
                      const double alpha = 1e-20, const bool verbose = false, const int block_size = 100, std::string library = "Pardiso");

        // Dual mutation - 0 copies only absorbing after the first mutation
        Matrix DualMutation(const int Nx, const int Ny, const double s = 0, const double h = 0.5,
                            const double u = 1e-9, const double v = 1e-9,
                            const bool recurrent_mutation = true, const double alpha = 1e-20,
                            const bool verbose = false, const int block_size = 100, std::string library = "Pardiso");

        // Single but with entries larger than `t` summed into the fixation state
        Matrix Truncated(const int Nx, const int Ny, const int t, const double s, const double h,
                         const double u, const double v, bool recurrent_mutation = true,
                         const double alpha = 1e-20, const bool verbose = false,
                         const int block_size = 100, std::string library = "Pardiso");

        // Switching - each sub-model is of the same absorbing type
        Matrix Switching(const lvec &N, const absorption_type a_t, const dvec &s, const dvec &h,
                         const dvec &u, const dvec &v, const dmat &switching, const double alpha = 1e-20,
                         const bool verbose = false, const int block_size = 100, std::string library = "Pardiso");

        // Two-model Switching: A is of type `NON_ABSORBING`, B is of type `FIXATION_ONLY`
        Matrix NonAbsorbingToFixationOnly(const int N, const dvec &s, const dvec &h, const dvec &u,
                                          const dvec &v, const dmat &switching, const double alpha = 1e-20,
                                          const bool verbose = false, const int block_size = 100, std::string library = "Pardiso");

        // Two-model Switching: A is of type `NON_ABSORBING`, B is of type `BOTH_ABSORBING`
        Matrix NonAbsorbingToBothAbsorbing(const int N, const dvec &s, const dvec &h, const dvec &u,
                                           const dvec &v, const dmat &switching, const double alpha = 1e-20,
                                           const bool verbose = false, const int block_size = 100, std::string library = "Pardiso");

    }
}

#endif // WRIGHTFISHER_H
