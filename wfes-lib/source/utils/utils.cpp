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

ivec wfes::utils::closedRangeInt(int start, int stop)
{
    ivec r(stop - start + 1);
    for(int i = start; i <= stop; i++) r(i - start) = i;
    return r;
}

QImage* wfes::utils::generateImage(const dmat &a)
{
    // Get minimum and maximum value
    double max = std::numeric_limits<double>::min();
    double min = std::numeric_limits<double>::max();
    for(int i = 0; i < a.rows(); i++){
        for(int j = 0; j < a.cols(); j++){
            if(a(i, j) < min)
                min = a(i, j);
            if(a(i, j) > max)
                max = a(i, j);
        }
    }

    // Allocate vector of uchar to store pixel values.
    uchar* data = (uchar*) malloc(a.rows() * a.cols() * sizeof(uchar));

    // Get number of bytes per each row.
    int bytesPerLine = (a.rows() * a.cols() * sizeof(uchar)) / a.rows();

    // Calculate pixel values using min and max.
    for(int i = a.rows() * a.cols(); i >= 0 ; i--) {
        double val = a.data()[i] + std::abs(min);
        val = val * 255;
        val = val / (std::abs(min + max));
        // Invert pixel values so higher values are darker.
        data[i] = (uchar) std::abs(255-(val));
        //qDebug() << data[i];
    }

    // Create QImage using vector of pixels.
    QImage* image = new QImage(data, a.cols(), a.rows(), bytesPerLine, QImage::Format_Grayscale8);

    return image;
}


bool wfes::utils::saveImage(QImage *image, std::string path)
{
    return image->save(QString::fromStdString(path), "PNG");
}
