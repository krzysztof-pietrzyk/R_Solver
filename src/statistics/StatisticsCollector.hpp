#ifndef STATISTICS_TYPE_HPP
#define STATISTICS_TYPE_HPP

#include "StatisticsLabels.hpp"
#include "elements/StatisticsElementIf.hpp"

#include <map>
#include <iomanip>

class StatisticsCollector
{
    public:

    StatisticsCollector();
    ~StatisticsCollector();

    void Clear();

    void AddElement(Label label, StatisticsElementIf* element);

    const std::map<Label, StatisticsElementIf*>& GetElements() const;

    StatisticsCollector* Clone() const;

    std::string String() const;

    void FlushToOutput(StatisticsCollector* output) const;

    private:

    std::map<Label, StatisticsElementIf*> labelled_elements;
};

#endif
