#include "SolverThreadData.hpp"

SolverThreadData::SolverThreadData()
{
    mut;
    tries = 0;
    wins = 0;
    completion = 0.0;
}

SolverThreadData::~SolverThreadData() {}
