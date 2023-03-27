#ifndef CACHED_VECTOR_HPP
#define CACHED_VECTOR_HPP

#include <vector>
#include <cstdint>
#include <algorithm>

class CachedVector
{
    public:

    const size_t max_size;

    CachedVector(size_t max_size);
    ~CachedVector();

    void Add(uint32_t value);
    void Remove(uint32_t value);
    bool Contains(uint32_t value) const;
    size_t CurrentIndex() const;
    void Clear();
    const std::vector<uint32_t>::iterator Begin();
    const std::vector<uint32_t>::iterator At(size_t index);
    const std::vector<uint32_t>::iterator End();

    protected:

    std::vector<uint32_t> data;
    std::vector<bool> is_present;
    size_t data_index;
};

#endif
