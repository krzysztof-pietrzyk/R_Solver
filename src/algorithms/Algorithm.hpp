#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include "../utils/Logger.hpp"
#include "../grid/GridAccessPlayerIf.hpp"
#include "../statistics/StatisticsProducer.hpp"
#include "../statistics/collectors/StatisticsCollectorExecutions.hpp"

#include "AlgorithmDataStorage.hpp"
#include "AlgorithmStatus.hpp"

class Algorithm : public StatisticsProducer
{
    /*
    Abstract base class for algorithm objects.
    Each algorithm has a Run() method, which executes the algorithm
    Algorithms have access to AlgorithmDataStorage and GridManager
    */
    public:
    
    Algorithm(GridAccessPlayerIf& grid_, AlgorithmDataStorage& data_);

    ~Algorithm();

    virtual AlgorithmStatus Run();

    protected:

    const GridAccessPlayerIf& grid;
    const AlgorithmDataStorage& data;
    const CachedVector& visible;
    const CachedVector& flagged;
    StatisticsCollectorExecutions* statistics_executions;

    virtual AlgorithmStatus Execution() = 0;

    GridAccessPlayerIf& GetModifiableGridReference() const;

    AlgorithmDataStorage& GetModifiableAlgorithmDataStorageReference() const;

    private:

    GridAccessPlayerIf& _grid;

    AlgorithmDataStorage& _data;
};

#endif
