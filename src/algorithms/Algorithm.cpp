#include "Algorithm.hpp"

Algorithm::Algorithm(GridAccessPlayerIf& grid_, AlgorithmDataStorage& data_)
    : grid(grid_), data(data_), _grid(grid_), _data(data_), 
    visible(grid_.GetVisibleFields()), flagged(grid_.GetFlaggedFields())
{

}

Algorithm::~Algorithm()
{

}

AlgorithmStatus Algorithm::Run()
{
    AlgorithmStatus execution_result = Execution();
    return execution_result;
}

GridAccessPlayerIf& Algorithm::GetModifiableGridReference() const
{
    return _grid;
}

AlgorithmDataStorage& Algorithm::GetModifiableAlgorithmDataStorageReference() const
{
    return _data;
}
