#include "BitMask.hpp"

BitMask::BitMask(unsigned int capacity) : max_capacity(capacity)
{
    if(0 == max_capacity) { throw std::invalid_argument("ERROR: BitMask capacity must be greater than 0!"); }
    arr = new bool[max_capacity] {0};
}

BitMask::~BitMask()
{
    delete[] arr;
}

bool& BitMask::operator [] (unsigned int n)
{
    if(n >= max_capacity) { throw std::invalid_argument("ERROR: Access to BitMask out of bounds!"); }
    return arr[n];
}

void BitMask::Clear()
{
    memset(arr, false, sizeof(bool) * max_capacity);
}
