#ifndef AlgorithmMetrics_hpp
#define AlgorithmMetrics_hpp

// #define GATHER_TIME_METRICS  // Toggle on/off because gathering time metrics significantly slows down the solver

#ifdef GATHER_TIME_METRICS
#include <chrono>
#endif

struct AlgorithmMetrics
{
    unsigned long long times_activated = 0LL;
    unsigned long long left_clicks = 0LL;
    unsigned long long right_clicks = 0LL;

    #ifdef GATHER_TIME_METRICS
    std::chrono::duration<int64_t, std::nano> total_time_running = std::chrono::duration<int64_t, std::nano>(0);
    #endif

    struct AlgorithmMetrics operator+=(AlgorithmMetrics const& other)
    {
        times_activated += other.times_activated;
        left_clicks += other.left_clicks;
        right_clicks += other.right_clicks;

        #ifdef GATHER_TIME_METRICS
        total_time_running += other.total_time_running;
        #endif

        return *this;
    }

    void Clear()
    {
        times_activated = 0LL;
        left_clicks = 0LL;
        right_clicks = 0LL;

        #ifdef GATHER_TIME_METRICS
        total_time_running = std::chrono::duration<int64_t, std::nano>(0);
        #endif
    }
};

#endif
