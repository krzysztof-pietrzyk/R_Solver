#ifndef Buffer_hpp
#define Buffer_hpp

#include <stdexcept>

class Buffer
{
    private:

    unsigned int* arr;
    unsigned int _len;
    unsigned int max_capacity;

    public:

    Buffer(unsigned int capacity);

    ~Buffer();

    void operator += (unsigned int x);

    const unsigned int operator [] (unsigned int n);

    void Clear() { _len = 0; }

    const inline unsigned int Len() { return _len; }

};

#endif
