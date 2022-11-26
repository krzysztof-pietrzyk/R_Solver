#include "Algorithm.hpp"

Algorithm::Algorithm(GridManager& grid_, AlgorithmDataStorage& data_)
    : grid(grid_), data(data_), _grid(grid_), _data(data_) {}

Algorithm::~Algorithm() {}

void Algorithm::LeftClick(const uint32_t field) const
{
    _grid.LeftClick(field);
}

void Algorithm::RightClick(const uint32_t field) const
{
    _grid.RightClick(field);
}

uint8_t Algorithm::FieldValue(const uint32_t field) const
{
    return _grid.FieldValue(field);
}

GridManager& Algorithm::GetModifiableGridManagerReference() const
{
    return _grid;
}

AlgorithmDataStorage& Algorithm::GetModifiableAlgorithmDataStorageReference() const
{
    return _data;
}
