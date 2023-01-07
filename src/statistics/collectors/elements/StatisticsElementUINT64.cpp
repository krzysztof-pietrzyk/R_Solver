#include "StatisticsElementUINT64.hpp"

StatisticsElementUINT64::StatisticsElementUINT64()
{
    element_value = 0U;
    Enable();
}

StatisticsElementUINT64::StatisticsElementUINT64(const StatisticsElementUINT64& other)
{
    element_value = other.element_value;
    Enable();
}

StatisticsElementUINT64::~StatisticsElementUINT64() {}

void StatisticsElementUINT64::Enable()
{
    InPlaceAddFunction = &_InPlaceAdd;
    AssignFunction = &_Assign;
}

void StatisticsElementUINT64::Disable()
{
    InPlaceAddFunction = &_DoNothing;
    AssignFunction = &_DoNothing;
}

void StatisticsElementUINT64::Clear()
{
    element_value = 0U;
}

std::string StatisticsElementUINT64::String()
{
    return std::to_string(element_value);
}

void StatisticsElementUINT64::operator+=(const StatisticsElement& other)
{
    element_value += ((StatisticsElementUINT64&)other).element_value;
}

void StatisticsElementUINT64::operator=(const StatisticsElement& other)
{
    element_value = ((StatisticsElementUINT64&)other).element_value;
}

void StatisticsElementUINT64::operator+=(const uint64_t& other) { InPlaceAddFunction(*this, other); }
void StatisticsElementUINT64::operator=(const uint64_t& other) { AssignFunction(*this, other); }

void StatisticsElementUINT64::_InPlaceAdd(const uint64_t& other) { element_value += other; }
void StatisticsElementUINT64::_Assign(const uint64_t& other) { element_value = other; }
