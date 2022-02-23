#include "Buffer2D.hpp"

Buffer2D::Buffer2D(unsigned int capacity, unsigned int element_s) 
    : max_capacity(capacity), element_size(element_s)
{
    if(0 == max_capacity) { throw std::invalid_argument("ERROR: Buffer2D capacity must be greater than 0!"); }
    if(0 == element_size) { throw std::invalid_argument("ERROR: Buffer2D element size must be greater than 0!"); }
    arr = std::vector<Buffer>();
    for(unsigned int i = 0; i < max_capacity; i++)
    {
        arr.push_back(Buffer(element_size));
    }
}

Buffer2D::~Buffer2D()
{

}

Buffer& Buffer2D::operator [] (unsigned int n)
{
    if(n >= max_capacity) { throw std::invalid_argument("ERROR: Access to Buffer2D out of bounds!"); }
    return arr[n];
}
