// implemented header
#include "StatisticsElementCounter.hpp"

// project includes

// std includes


StatisticsElementCounter::StatisticsElementCounter()
{
    element_value = 0U;
    last_read_value = 0U;
}

StatisticsElementCounter::~StatisticsElementCounter()
{

}

StatisticsElementIf* StatisticsElementCounter::GetNewInstance()
{
    return new StatisticsElementCounter();
}

std::string StatisticsElementCounter::String() const
{
    return std::to_string(element_value);
}

bool StatisticsElementCounter::IsEmpty()
{
    return element_value == 0U;
}

void StatisticsElementCounter::FlushToOutput(StatisticsElementIf* output)
{
    // temp is needed because FlushToOutput is called from a different thread
    // This assures that the value stays correct, even if element_value is modified in the meantime
    uint64_t temp = element_value;
    ((StatisticsElementCounter*)output)->element_value += temp - last_read_value;
    last_read_value = temp;
}

void StatisticsElementCounter::operator+=(const uint64_t other)
{
    element_value += other;
}

void StatisticsElementCounter::operator=(const uint64_t other)
{
    element_value = other;
}
