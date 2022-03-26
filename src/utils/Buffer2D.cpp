#include "Buffer2D.hpp"

Buffer2D::Buffer2D(unsigned int capacity, unsigned int element_s) 
    : max_capacity(capacity), element_size(element_s)
{
    arr = (Buffer*)malloc(sizeof(Buffer) * capacity);
    for(size_t i = 0; i < max_capacity; i++)
    {
        arr[i] = Buffer(element_size);
    }
}

Buffer2D::~Buffer2D()
{
    delete[] arr;
}

Buffer& Buffer2D::operator [] (unsigned int n)
{
    if(n >= max_capacity) { throw std::invalid_argument("ERROR: Access to Buffer2D out of bounds!"); }
    return arr[n];
}
