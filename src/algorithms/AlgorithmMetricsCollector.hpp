#ifndef AlgorithmMetricsCollector_hpp
#define AlgorithmMetricsCollector_hpp

#include <map>

#include "Algorithm.hpp"
#include "AlgorithmType.hpp"
#include "AlgorithmDataStorage.hpp"

class AlgorithmMetricsCollector
{
    public:

    AlgorithmMetricsCollector(std::map<AlgorithmType, Algorithm*>& algorithms_);

    ~AlgorithmMetricsCollector();

    void UpdateMetrics();

    protected:

    std::map<AlgorithmType, Algorithm*>& algorithms;

    std::map<AlgorithmType, AlgorithmMetrics> algorithm_metrics;
};

#endif
