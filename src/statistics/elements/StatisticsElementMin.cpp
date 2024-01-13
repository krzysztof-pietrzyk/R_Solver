// implemented header
#include "StatisticsElementMin.hpp"

// project includes

// std includes


StatisticsElementMin::StatisticsElementMin()
{
    element_value = UINT64_MAX;
}

StatisticsElementMin::~StatisticsElementMin()
{

}

StatisticsElementIf* StatisticsElementMin::GetNewInstance()
{
    return new StatisticsElementMin();
}

std::string StatisticsElementMin::String() const
{
    std::string return_string;
    if(element_value == UINT64_MAX)
    {
        return_string = "N/A";
    }
    else
    {
        return_string = std::to_string(element_value);
    }
    return return_string;
}

bool StatisticsElementMin::IsEmpty()
{
    return false;
}

void StatisticsElementMin::FlushToOutput(StatisticsElementIf* output)
{
    uint64_t current_value = element_value;
    uint64_t& output_value = ((StatisticsElementMin*)output)->element_value;
    if(current_value < output_value)
    {
        output_value = current_value;
    }
}

void StatisticsElementMin::CompareAndSet(uint64_t new_value)
{
    if(new_value < element_value)
    {
        element_value = new_value;
    }
}
