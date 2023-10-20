#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include "../utils/Logger.hpp"
#include "../grid/GridCommonIf.hpp"
#include "../statistics/StatisticsProducer.hpp"
#include "../statistics/collectors/StatisticsCollectorExecutions.hpp"

#include "data/AlgorithmDataTransfer.hpp"
#include "AlgorithmStatus.hpp"

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
    StatisticsCollectorExecutions* statistics_executions;

    virtual AlgorithmStatus Execution() = 0;
};

#endif
