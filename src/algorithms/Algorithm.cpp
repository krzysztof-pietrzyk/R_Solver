#include "Algorithm.hpp"

Algorithm::Algorithm(GridManager& grid_, AlgorithmDataStorage& data_)
    : grid(grid_), data(data_), _grid(grid_), _data(data_) {}

Algorithm::~Algorithm() {}

void Algorithm::LeftClick(const unsigned int field) const
{
    _grid.LeftClick(field);
}

void Algorithm::RightClick(const unsigned int field) const
{
    _grid.RightClick(field);
}

unsigned char Algorithm::FieldValue(const unsigned int field) const
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
