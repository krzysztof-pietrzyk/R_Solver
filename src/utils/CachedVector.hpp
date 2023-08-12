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

    CachedVector(size_t _max_size);
    CachedVector(const std::vector<bool>& _is_present);
    CachedVector(const std::vector<uint32_t>& _data, size_t _max_size);
    CachedVector();
    ~CachedVector();

    void Add(uint32_t value);
    void Remove(uint32_t value);
    bool Contains(uint32_t value) const;
    void Clear();
    size_t Index() const;
    size_t MaxSize() const;

    const std::vector<uint32_t>::iterator begin();
    const std::vector<uint32_t>::iterator at(size_t index);
    const std::vector<uint32_t>::iterator end();

    static void CopyFromTo(const CachedVector& source, CachedVector& destination);

    CachedVector& operator=(const CachedVector& other);
    bool operator==(const CachedVector& other) const;
    const uint32_t& operator[](size_t index) const;

    protected:

    size_t max_size;
    std::vector<uint32_t> data;
    std::vector<bool> is_present;
    size_t data_index;
};

#endif
