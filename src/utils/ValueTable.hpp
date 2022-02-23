#ifndef ValueTable_hpp
#define ValueTable_hpp

#include <stdexcept>
#include <cstring>

class ValueTable
{
    private:

    unsigned int* arr;
    unsigned int max_capacity;

    public:

    ValueTable(unsigned int capacity);

    ~ValueTable();

    unsigned int& operator [] (unsigned int n);

    void Clear();

    const inline unsigned int Len() { return max_capacity; }

};


#endif