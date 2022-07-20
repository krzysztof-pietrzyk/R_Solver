#ifndef AlgorithmMetrics_hpp
#define AlgorithmMetrics_hpp

struct AlgorithmMetrics
{
    unsigned long long times_activated = 0LL;
    unsigned long long left_clicks = 0LL;
    unsigned long long right_clicks = 0LL;

    struct AlgorithmMetrics operator+=(AlgorithmMetrics const& other)
    {
        times_activated += other.times_activated;
        left_clicks += other.left_clicks;
        right_clicks += other.right_clicks;
        return *this;
    }

    void Clear()
    {
        times_activated = 0LL;
        left_clicks = 0LL;
        right_clicks = 0LL;
    }
};

#endif
