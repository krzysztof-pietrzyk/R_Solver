#include "Algorithm.hpp"

Algorithm::Algorithm(GridManager& grid_, AlgorithmDataStorage& data_)
    : grid(grid_), data(data_), _grid(grid_), _data(data_)
{
    statistics_clicks = new StatisticsTypeClicks();
    statistics_types.push_back(statistics_clicks);
}

Algorithm::~Algorithm()
{
    delete statistics_clicks;
}

void Algorithm::LeftClick(const uint32_t field) const
{
    bool result = _grid.LeftClick(field);
    StatisticsTypeClicks* ref = (StatisticsTypeClicks*)statistics_clicks;
    ref->left_clicks++;
    if(!result)
    {
        ref->wasted_left_clicks++;
    }
}

void Algorithm::RightClick(const uint32_t field) const
{
    bool result = _grid.RightClick(field);
    StatisticsTypeClicks* ref = (StatisticsTypeClicks*)statistics_clicks;
    ref->right_clicks++;
    if(!result)
    {
        ref->wasted_right_clicks++;
    }
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
