#ifndef Buffer2D_hpp
#define Buffer2D_hpp

#include <stdexcept>

#include "Buffer.hpp"

class Buffer2D
{
    private:

    Buffer* arr;
    const unsigned int max_capacity;
    const unsigned int element_size;

    public:

    Buffer2D(unsigned int capacity, unsigned int element_s);

    ~Buffer2D();

    Buffer& operator [] (unsigned int n);

    const inline unsigned int Len() { return max_capacity; }
};

#endif
