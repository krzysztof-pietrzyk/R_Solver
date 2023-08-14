#include "CachedVector.hpp"

CachedVector::CachedVector(size_t _max_size)
{
    max_size = _max_size;
    data = std::vector<uint32_t>(max_size, 0U);
    is_present = std::vector<bool>(max_size, false);
    data_index = 0U;
}

CachedVector::CachedVector(const std::vector<bool>& _is_present)
{
    max_size = _is_present.size();
    data = std::vector<uint32_t>(max_size, 0U);
    is_present = std::vector<bool>(max_size, false);
    data_index = 0U;
    for(size_t i = 0; i < max_size; i++)
    {
        if(_is_present[i])
        {
            Add(i);
        }
    }
}

CachedVector::CachedVector(const std::vector<uint32_t>& _data, size_t _max_size)
{
    max_size = _max_size;
    data = std::vector<uint32_t>(max_size, 0U);
    is_present = std::vector<bool>(max_size, false);
    data_index = 0U;
    for(size_t i = 0; i < _data.size(); i++)
    {
        Add(_data[i]);
    }
}

CachedVector::CachedVector() : CachedVector(1U)
{

}

CachedVector::~CachedVector()
{

}

void CachedVector::Add(uint32_t value)
{
    #ifdef SAFE_CACHED_VECTOR
    LOGGER_ASSERT(data_index < max_size, "CachedVector::Add - Exceeded max size");
    #endif
    data[data_index++] = value;
    is_present[value] = true;
}

void CachedVector::Remove(uint32_t value)
{
    auto begin = this->begin();
    auto end = this->end();
    #ifdef SAFE_CACHED_VECTOR
    LOGGER_ASSERT(begin != end, "CachedVector::Remove - Removing from empty vector");
    #endif
    auto position_iter = std::find(begin, end, value);
    if(position_iter != end)
    {
        size_t index_to_remove = position_iter - begin;
        data[index_to_remove] = data[--data_index];
        is_present[value] = false;
    }
}

bool CachedVector::Contains(uint32_t value) const
{
    #ifdef SAFE_CACHED_VECTOR
    LOGGER_ASSERT(value < max_size, "CachedVector::Contains - Exceeded max size");
    #endif
    return is_present[value];
}

void CachedVector::Clear()
{
    for(auto data_iter = this->begin(); data_iter != this->end(); ++data_iter)
    {
        is_present[*data_iter] = false;
    }
    data_index = 0U;
}

size_t CachedVector::Index() const
{
    return data_index;
}

size_t CachedVector::MaxSize() const
{
    return max_size;
}

const std::vector<uint32_t>::iterator CachedVector::begin()
{
    return data.begin();
}

const std::vector<uint32_t>::iterator CachedVector::at(size_t index)
{
    #ifdef SAFE_CACHED_VECTOR
    LOGGER_ASSERT(index < max_size, "CachedVector::At - Exceeded max size");
    #endif
    return data.begin() + index;
}

const std::vector<uint32_t>::iterator CachedVector::end()
{
    return begin() + Index();
}

void CachedVector::CopyFromTo(const CachedVector& source, CachedVector& destination)
{
    #ifdef SAFE_CACHED_VECTOR
    LOGGER_ASSERT(source.max_size == destination.max_size, "CachedVector::CopyFromTo - source and destination have different sizes");
    #endif
    for(size_t i = 0U; i < source.max_size; i++)
    {
        destination.data[i] = source.data[i];
        destination.is_present[i] = source.is_present[i];
    }
    destination.data_index = source.data_index;
}

CachedVector& CachedVector::operator=(const CachedVector& other)
{
    if(this == &other)
    {
        return *this;
    }

    if(max_size != other.max_size)
    {
        max_size = other.max_size;
        data = std::vector<uint32_t>(max_size, 0U);
        is_present = std::vector<bool>(max_size, false);
        data_index = 0U;
    }

    CachedVector::CopyFromTo(other, *this);
    return *this;
}

bool CachedVector::operator==(const CachedVector& other) const
{
    return data == other.data 
        && is_present == other.is_present
        && data_index == other.data_index;
}

const uint32_t& CachedVector::operator[](size_t index) const
{
    return data[index];
}
