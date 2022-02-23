#include "ValueTable.hpp"

ValueTable::ValueTable(unsigned int capacity) : max_capacity(capacity)
{
    if(0 == max_capacity) { throw std::invalid_argument("ERROR: ValueTable capacity must be greater than 0!"); }
    arr = new unsigned int[max_capacity] {0};
}

ValueTable::~ValueTable()
{
    delete[] arr;
}

unsigned int& ValueTable::operator [] (unsigned int n)
{
    if(n >= max_capacity) { throw std::invalid_argument("ERROR: Access to ValueTable out of bounds!"); }
    return arr[n];
}

void ValueTable::Clear()
{
    memset(arr, 0, sizeof(unsigned int) * max_capacity);
}
