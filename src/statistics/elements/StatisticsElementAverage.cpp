// implemented header
#include "StatisticsElementAverage.hpp"

// project includes

// std includes


StatisticsElementAverage::StatisticsElementAverage()
{
    total_sum = 0U;
    number_of_entries = 0U;
    average = 0.0;
}

StatisticsElementAverage::~StatisticsElementAverage()
{

}

StatisticsElementIf* StatisticsElementAverage::GetNewInstance()
{
    return new StatisticsElementAverage();
}

std::string StatisticsElementAverage::String() const
{
    std::string return_string;
    if(number_of_entries == 0U)
    {
        return_string = "N/A";
    }
    else
    {
        return_string = std::to_string(average);
    }
    return return_string;
}

bool StatisticsElementAverage::IsEmpty()
{
    return false;
}

void StatisticsElementAverage::FlushToOutput(StatisticsElementIf* output)
{
    StatisticsElementAverage* output_value = ((StatisticsElementAverage*)output);
    mut.lock();
    output_value->total_sum += total_sum;
    output_value->number_of_entries += number_of_entries;
    mut.unlock();
    output_value->UpdateAverage();
}

void StatisticsElementAverage::AddEntryToAverage(uint64_t new_value)
{
    mut.lock();
    total_sum += new_value;
    number_of_entries++;
    mut.unlock();
}

void StatisticsElementAverage::UpdateAverage()
{
    if(number_of_entries > 0U)
    {
        average = (double)total_sum / number_of_entries;
    }
    else
    {
        average = 0.0;
    }
}
