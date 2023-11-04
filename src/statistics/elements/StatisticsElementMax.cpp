// implemented header
#include "StatisticsElementMax.hpp"

// project includes

// std includes


StatisticsElementMax::StatisticsElementMax()
{
    element_value = 0U;
}

StatisticsElementMax::~StatisticsElementMax()
{

}

StatisticsElementIf* StatisticsElementMax::Clone()
{
    return new StatisticsElementMax();
}

std::string StatisticsElementMax::String() const
{
    return std::to_string(element_value);
}

bool StatisticsElementMax::IsEmpty()
{
    return false;
}

void StatisticsElementMax::FlushToOutput(StatisticsElementIf* output)
{
    uint64_t current_value = element_value;
    uint64_t& output_value = ((StatisticsElementMax*)output)->element_value;
    if(current_value > output_value)
    {
        output_value = current_value;
    }
}

void StatisticsElementMax::CompareAndSet(uint64_t new_value)
{
    if(new_value > element_value)
    {
        element_value = new_value;
    }
}
