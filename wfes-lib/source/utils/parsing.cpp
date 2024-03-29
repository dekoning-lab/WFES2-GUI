#include "parsing.h"

template<>
llong from_string<llong>(std::string const& str, size_t* pos) {
    return stoll(str, pos, 10);
}

template<>
int from_string<int>(std::string const& str, size_t* pos) {
    return stoi(str, pos, 10);
}

template<>
double from_string<double>(std::string const& str, size_t* pos) {
    return stod(str, pos);
}

void TokenReader::split_string(const std::string &s, char delim, std::back_insert_iterator<std::deque<std::string>> result) {
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::deque<std::string> TokenReader::split(const std::string &s, char delim) {
    std::deque<std::string> elems;
    split_string(s, delim, back_inserter(elems));
    return elems;
}

template <>
const char* string_format<double>() { return DPF; }

template <>
const char* string_format<llong>() { return LPF; }

dvec load_csv_row_vector(const std::string file, llong rows) {
    std::ifstream in(file);
    std::vector<double> numbers;

    try {
        for (std::string token; std::getline(in, token, ','); ) {
            numbers.push_back(std::stod(token));
        }
    } catch (const std::invalid_argument&) {
        throw std::runtime_error("Error loading csv file: Argument is invalid.\n");
    } catch (const std::out_of_range&) {
        throw std::runtime_error("Error loading csv file: Argument is out of range for a double.\n");
    }

    llong row = numbers.size();
    if (rows > 1 && rows != row) throw std::runtime_error("Error loading csv file: Row size does not match the requested size.");
    return Eigen::Map<dvec>(numbers.data(), numbers.size());
}

dvec load_csv_col_vector(const std::string file, llong rows) {
    std::ifstream in(file);
    std::vector<double> numbers;

    try {
        for (std::string token; std::getline(in, token); ) {
            numbers.push_back(std::stod(token));
        }
    } catch (const std::invalid_argument&) {
        throw std::runtime_error("Error loading csv file: Argument is invalid.\n");
    } catch (const std::out_of_range&) {
        throw std::runtime_error("Error loading csv file: Argument is out of range for a double.\n");
    }

    llong row = numbers.size();
    if (rows > 1 && rows != row) throw std::runtime_error("Error loading csv file: Column size does not match the requested size.");
    return Eigen::Map<dvec>(numbers.data(), numbers.size());
}

dmat load_csv_matrix(const std::string file, llong rows, llong cols) {
    std::ifstream in(file);
    std::vector<double> numbers;

    llong row = 0;
    try {
        for (std::string line; std::getline(in, line); row++) {
            std::stringstream line_stream(line);
            for (std::string token; std::getline(line_stream, token, ','); ) {
                numbers.push_back(std::stod(token));
            }
        }
    } catch (const std::invalid_argument&) {
        throw std::runtime_error("Error loading csv file: Argument is invalid.\n");
    } catch (const std::out_of_range&) {
        throw std::runtime_error("Error loading csv file: Argument is out of range for a double.\n");
    }

    llong col = numbers.size() / row;
    if (rows > 1 && rows != row) throw std::runtime_error("Error loading csv file: Row size does not match the requested size.");
    if (cols > 1 && cols != col) throw std::runtime_error("Error loading csv file: Column size does not match the requested size.");
    return Eigen::Map<dmat>(numbers.data(), row, col);
}

