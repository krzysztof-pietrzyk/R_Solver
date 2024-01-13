#ifndef ALGORITHM_COMBINATIONS_UTILS_HPP
#define ALGORITHM_COMBINATIONS_UTILS_HPP

// project includes

// std includes
#include <stdexcept>

// forward declarations


enum class FieldState
{
    UNASSIGNED,
    MINE,
    SAFE
};

class FailSafeException : public std::runtime_error
{
    public:

    FailSafeException() throw()
        : std::runtime_error("Too much data to process.")
    {

    }
};

#endif
