#ifndef STATISTICS_TYPE_HPP
#define STATISTICS_TYPE_HPP

// project includes
#include "../utils/Label.hpp"

// std includes
#include <map>
#include <string>

// forward declarations
class StatisticsElementIf;


class StatisticsCollector
{
    public:

    StatisticsCollector();

    ~StatisticsCollector();

    void AddElement(Label label, StatisticsElementIf* element);

    StatisticsCollector* Clone() const;

    std::string String() const;

    void FlushToOutput(const StatisticsCollector* output) const;

    private:

    std::map<Label, StatisticsElementIf*> labelled_elements;
};

#endif
