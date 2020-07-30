#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iterator>
#include <exception>

namespace wfes {
    namespace exception{

        class Error : public std::runtime_error
        {
            public:
                Error(const std::string &problem) : std::runtime_error(problem) {}
                virtual ~Error() {}
        };

    }
}

#endif // EXCEPTIONS_H
