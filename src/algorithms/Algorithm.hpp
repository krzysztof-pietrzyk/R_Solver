#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

// project includes
#include "AlgorithmStatus.hpp"
#include "data/AlgorithmDataTransfer.hpp"
#include "../grid/GridDimensions.hpp"
#include "../statistics/StatisticsProducer.hpp"
#include "../utils/Logger.hpp"

// std includes

// forward declarations
class GridCommonIf;
class StatisticsElementCounter;


class Algorithm : public StatisticsProducer
{
    /*
    Abstract base class for algorithm objects.
    Each algorithm has a Run() method, which executes the algorithm
    Algorithms have access to AlgorithmDataTransfer and GridManager
    */
    public:
    
    Algorithm(const GridCommonIf& grid_, AlgorithmDataTransfer& data_);

    ~Algorithm();

    virtual AlgorithmStatus Run();

    protected:

    AlgorithmDataTransfer& data;
    const GridDimensions grid_dim;

    virtual AlgorithmStatus Execution() = 0;

    void UpdateExecutionStatistics(AlgorithmStatus status);

    private:

    StatisticsElementCounter* counter_executions;
    StatisticsElementCounter* counter_success;
    StatisticsElementCounter* counter_no_moves;
    StatisticsElementCounter* counter_failure;
    StatisticsElementCounter* counter_won;
    StatisticsElementCounter* counter_lost;

    void CreateStatisticsElements();
};

#endif
