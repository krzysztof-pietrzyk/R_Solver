#include "CachedVector.hpp"

CachedVector::CachedVector(size_t max_size)
    : max_size(max_size)
{
    data = std::vector<uint32_t>(max_size);
    is_present = std::vector<bool>(max_size);
    data_index = 0U;
}

CachedVector::~CachedVector()
{

}

void CachedVector::Add(uint32_t value)
{
    data[data_index++] = value;
    is_present[value] = true;
}

void CachedVector::Remove(uint32_t value)
{
    auto begin = Begin();
    auto end = End();
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
    return is_present[value];
}

size_t CachedVector::CurrentIndex() const
{
    return data_index;
}

void CachedVector::Clear()
{
    for(auto data_iter = Begin(); data_iter != End(); ++data_iter)
    {
        is_present[*data_iter] = false;
    }
    data_index = 0U;
}

const std::vector<uint32_t>::iterator CachedVector::Begin()
{
    return data.begin();
}

const std::vector<uint32_t>::iterator CachedVector::At(size_t index)
{
    return data.begin() + index;
}

const std::vector<uint32_t>::iterator CachedVector::End()
{
    return Begin() + CurrentIndex();
}
