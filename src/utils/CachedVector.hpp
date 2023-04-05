#ifndef CACHED_VECTOR_HPP
#define CACHED_VECTOR_HPP

#include <vector>
#include <cstdint>
#include <algorithm>
#include <stdexcept>

// #define SAFE_CACHED_VECTOR

class CachedVector
{
    public:

    CachedVector(size_t max_size);
    CachedVector();
    ~CachedVector();

    void Add(uint32_t value);
    void Remove(uint32_t value);
    bool Contains(uint32_t value) const;
    void Clear();
    size_t CurrentIndex() const;
    size_t MaxSize() const;

    const std::vector<uint32_t>::iterator Begin();
    const std::vector<uint32_t>::iterator At(size_t index);
    const std::vector<uint32_t>::iterator End();

    static void MoveFromTo(const CachedVector& source, CachedVector& destination);

    void operator=(const CachedVector& other);

    protected:

    const size_t max_size;
    std::vector<uint32_t> data;
    std::vector<bool> is_present;
    size_t data_index;
};

#endif
