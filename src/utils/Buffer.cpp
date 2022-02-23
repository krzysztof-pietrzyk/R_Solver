#include "Buffer.hpp"

Buffer::Buffer(unsigned int capacity) : max_capacity(capacity)
{
    if(0 == max_capacity) { throw std::invalid_argument("ERROR: Buffer capacity must be greater than 0!"); }
    arr = new unsigned int[max_capacity] {0};
    _len = 0;
}

Buffer::~Buffer()
{
    delete[] arr;
}

void Buffer::operator += (unsigned int x)
{
    if(_len >= max_capacity) { throw std::invalid_argument("ERROR: Buffer is full!"); }
    arr[_len++] = x;
}

const unsigned int Buffer::operator [] (unsigned int n)
{
    if(n >= max_capacity)   { throw std::invalid_argument("ERROR: Access to Buffer out of bounds!"); }
    if(n >= _len)           { throw std::invalid_argument("ERROR: Access to Buffer after last element!"); }
    return arr[n];
}
