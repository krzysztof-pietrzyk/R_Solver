#include "AlgorithmMetrics.hpp"

AlgorithmMetrics::AlgorithmMetrics() : Metrics()
{
    times_activated = 0LL;
    left_clicks = 0LL;
    right_clicks = 0LL;

    #ifdef GATHER_TIME_METRICS
    total_time_running = std::chrono::duration<int64_t, std::nano>(0);
    #endif
}

AlgorithmMetrics::~AlgorithmMetrics()
{

}

void AlgorithmMetrics::operator+=(AlgorithmMetrics const& other)
{
    times_activated += other.times_activated;
    left_clicks += other.left_clicks;
    right_clicks += other.right_clicks;

    #ifdef GATHER_TIME_METRICS
    total_time_running += other.total_time_running;
    #endif
}

void AlgorithmMetrics::Clear()
{
    times_activated = 0LL;
    left_clicks = 0LL;
    right_clicks = 0LL;

    #ifdef GATHER_TIME_METRICS
    total_time_running = std::chrono::duration<int64_t, std::nano>(0);
    #endif
}