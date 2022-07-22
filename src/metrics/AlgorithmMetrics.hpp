#ifndef AlgorithmMetrics_hpp
#define AlgorithmMetrics_hpp

// #define GATHER_TIME_METRICS  // Toggle on/off because gathering time metrics significantly slows down the solver

#ifdef GATHER_TIME_METRICS
#include <chrono>
#endif

#include "Metrics.hpp"

class AlgorithmMetrics : public Metrics
{
    public:

    unsigned long long times_activated = 0LL;
    unsigned long long left_clicks = 0LL;
    unsigned long long right_clicks = 0LL;

    #ifdef GATHER_TIME_METRICS
    std::chrono::duration<int64_t, std::nano> total_time_running = std::chrono::duration<int64_t, std::nano>(0);
    #endif

    AlgorithmMetrics();

    ~AlgorithmMetrics();

    void operator+=(AlgorithmMetrics const& other);

    void Clear();
};

#endif
