#include "AlgorithmMetricsCollector.hpp"

AlgorithmMetricsCollector::AlgorithmMetricsCollector(std::map<AlgorithmType, Algorithm*>& algorithms_)
    : algorithms(algorithms_)
{
    algorithm_metrics = std::map<AlgorithmType, AlgorithmMetrics>();
}

AlgorithmMetricsCollector::~AlgorithmMetricsCollector() {}

void AlgorithmMetricsCollector::UpdateMetrics()
{
    for(auto iter = algorithms.begin(); iter != algorithms.end(); ++iter)
    {
        algorithm_metrics[iter->first] += iter->second->metrics;
        iter->second->metrics.Clear();
    }
}
