#ifndef BitMask_hpp
#define BitMask_hpp

#include <stdexcept>
#include <cstring>

class BitMask
{
    private:

    bool* arr;
    const unsigned int max_capacity;

    public:

    BitMask(unsigned int capacity);

    ~BitMask();

    bool& operator [] (unsigned int n);

    void Clear();  // Set all elements to 0

    const inline unsigned int Len() { return max_capacity; }

};

#endif
