#include "utils.h"

void wfes::utils::writeMatrixToFile(const dmat &A, std::string path, bool append)
{
    if (path == "stdout") {
        std::cout << A.format(CSVFormat) << std::endl;
    } else {
        std::ios_base::openmode mode = append ? std::ios_base::app : std::ios_base::out;
        std::ofstream file(path, mode);
        if (file.is_open()) file << A.format(CSVFormat) << std::endl;
    }
}

void wfes::utils::writeVectorMapToFile(const std::map<llong, dvec> &A, std::string path, bool append)
{
    if (path == "stdout") {
        for(auto const &item : A) {
            llong key = item.first;
            dvec value = item.second;
            std::cout << key << ", " << value.format(CSVRowFormat) << std::endl;
        }
    } else {
        std::ios_base::openmode mode = append ? std::ios_base::app : std::ios_base::out;
        std::ofstream file(path, mode);
        if (file.is_open()) {
            for(auto const &item : A) {
                llong key = item.first;
                dvec value = item.second;
                file << key << ", " << value.format(CSVRowFormat) << std::endl;
            }
        }
    }
}

void wfes::utils::writeVectorToFile(const dvec &A, std::string path, bool append)
{
    if (path == "stdout") {
        std::cout << A.format(CSVRowFormat) << std::endl;
    } else {
        std::ios_base::openmode mode = append ? std::ios_base::app : std::ios_base::out;
        std::ofstream file(path, mode);
        if (file.is_open()) file << A.format(CSVRowFormat) << std::endl;
    }
}

void wfes::utils::printVector(const dvec &src, const char *prefix, const char *postfix, const char *delim)
{
    size_t size = src.size();
    printf("%s", prefix);
    for(size_t i = 0; i < size - 1; i++) {
        printf(DPF, src(i));
        printf("%s ", delim);
    }
    printf(DPF, src(size-1));
    printf("%s", postfix);
}

void wfes::utils::printVector(const lvec &src, const char *prefix, const char *postfix, const char *delim)
{
    size_t size = src.size();
    printf("%s", prefix);
    for(size_t i = 0; i < size - 1; i++) {
        printf(LPF, src(i));
        printf("%s ", delim);
    }
    printf(LPF, src(size-1));
    printf("%s", postfix);
}

llong wfes::utils::positiveMin(llong a, llong b)
{
    if (a == 0 && b == 0) return 0;
    if (a >= 0 && b <  0) return a;
    if (a <  0 && b >= 0) return b;
    if (a <= b) return a;
    else return b;
}

bool wfes::utils::approxEq(const dvec &a, const dvec &b, double tol)
{
    return ((a - b).array().abs() < tol).all();
}

bool wfes::utils::approxEq(const dmat &a, const dmat &b, double tol)
{
    return ((a - b).array().abs() < tol).all();
}

double wfes::utils::totalDiff(const dmat &a, const dmat &b)
{
    return (a - b).array().abs().sum();
}

lvec wfes::utils::startIndeces(lvec n)
{
    lvec si = lvec::Zero(n.size());
    for (llong i = 1; i < n.size(); i++) {
        si[i] = si[i-1] + n[i-1];
    }
    return si;
}

lvec wfes::utils::endIndeces(lvec n)
{
    lvec ei = lvec::Zero(n.size());
    ei(0) = n[0];
    for (llong i = 1; i < n.size(); i++) {
        ei[i] = ei[i-1] + n[i];
    }
    return ei;
}

lvec wfes::utils::rangeStep(llong a, llong b, llong s)
{
    lvec r = lvec::Zero(ceil((b-a)/double(s)));
    for(llong v = a, i = 0; v < b; v += s, i++) {
        r[i] = v;
    }
    return r;
}

lvec wfes::utils::closedRange(llong start, llong stop)
{
    lvec r(stop - start + 1);
    for(llong i = start; i <= stop; i++) r(i - start) = i;
    return r;
}

void wfes::utils::writeResultsToFile(Results *results, std::string path)
{
    std::ofstream myfile;
    myfile.open (path);
    myfile << "Result, Value" << "\n";

    if(!std::isnan(results->pExt))
        myfile << "P_ext, " << results->pExt << "\n";

    if(!std::isnan(results->pFix))
        myfile << "P_fix, " << results->pFix << "\n";

    if(!std::isnan(results->tAbs))
        myfile << "T_abs, " << results->tAbs << "\n";

    if(!std::isnan(results->tAbsStd))
        myfile << "T_abs_std, " << results->tAbsStd << "\n";

    if(!std::isnan(results->tExt))
        myfile << "T_ext, " << results->tExt << "\n";

    if(!std::isnan(results->tExtStd))
        myfile << "T_ext_std, " << results->tExtStd << "\n";

    if(!std::isnan(results->nExt))
        myfile << "N_ext, " << results->nExt << "\n";

    if(!std::isnan(results->tFix))
        myfile << "T_fix, " << results->tFix << "\n";

    if(!std::isnan(results->tFixStd))
        myfile << "T_fix_std, " << results->tFixStd << "\n";

    if(!std::isnan(results->rate))
        myfile << "Rate, " << results->rate << "\n";

    if(!std::isnan(results->freqMut))
        myfile << "E[freq mut], " << results->freqMut << "\n";

    if(!std::isnan(results->freqWt))
        myfile << "E[freq  wt], " << results->freqWt << "\n";

    if(!std::isnan(results->fEst))
        myfile << "F_est, " << results->fEst << "\n";

    if(!std::isnan(results->pEst))
        myfile << "P_est, " << results->fEst << "\n";

    if(!std::isnan(results->tSeg))
        myfile << "T_seg, " << results->tSeg << "\n";

    if(!std::isnan(results->tSegStd))
        myfile << "T_seg_std, " << results->tSegStd << "\n";

    if(!std::isnan(results->tSegExt))
        myfile << "T_seg_ext, " << results->tSegExt << "\n";

    if(!std::isnan(results->tSegExtStd))
        myfile << "T_seg_ext_std, " << results->tSegExtStd << "\n";

    if(!std::isnan(results->tSegFix))
        myfile << "T_seg_fix, " << results->tSegFix << "\n";

    if(!std::isnan(results->tSegFixStd))
        myfile << "T_seg_fix_std, " << results->tSegFixStd << "\n";

    if(!std::isnan(results->tEst))
        myfile << "T_est, " << results->tEst << "\n";

    if(!std::isnan(results->tEstStd))
        myfile << "T_est_std, " << results->tEstStd << "\n";

    if(!std::isnan(results->eAlleleAge))
        myfile << "E(A), " << results->eAlleleAge << "\n";

    if(!std::isnan(results->sAlleleAge))
        myfile << "S(A), " << results->sAlleleAge << "\n";


    myfile.close();
}
