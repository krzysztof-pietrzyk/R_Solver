#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include "../utils/Logger.hpp"
#include "../grid/GridAccessPlayerIf.hpp"
#include "../statistics/StatisticsProducer.hpp"
#include "../statistics/collectors/StatisticsCollectorExecutions.hpp"

#include "AlgorithmDataTransfer.hpp"
#include "AlgorithmStatus.hpp"

class Algorithm : public StatisticsProducer
{
    /*
    Abstract base class for algorithm objects.
    Each algorithm has a Run() method, which executes the algorithm
    Algorithms have access to AlgorithmDataTransfer and GridManager
    */
    public:
    
    Algorithm(GridAccessPlayerIf& grid_, AlgorithmDataTransfer& data_);

    ~Algorithm();

    virtual AlgorithmStatus Run();

    protected:

    const GridAccessPlayerIf& grid;
    const AlgorithmDataTransfer& data;
    const CachedVector& visible;
    const CachedVector& flagged;
    const GridDimensions grid_dim;
    StatisticsCollectorExecutions* statistics_executions;

    virtual AlgorithmStatus Execution() = 0;

    GridAccessPlayerIf& GetModifiableGridReference() const;

    AlgorithmDataTransfer& GetModifiableAlgorithmDataTransferReference() const;

    private:

    GridAccessPlayerIf& _grid;

    AlgorithmDataTransfer& _data;
};

#endif
