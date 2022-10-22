#ifndef AlgorithmRefreshBorder_hpp
#define AlgorithmRefreshBorder_hpp

#include "../Algorithm.hpp"

class AlgorithmRefreshBorder : public Algorithm
{
    /*
    This algorithm gathers information about the "border", which is
    the set of numbered, uncovered fields, which have at least one covered non-flag neighbor.
    For optimization, there are two vectors containing the border fields. Instead of
    analyzing all fields each time, we can check which fields were previously considered border and
    copy only the ones that are still border to the second vector. Then the algorithm looks only
    at fields which were uncovered since last time this algorithm was executed and decides whether
    they should be added to the border vector or not. After each execution, the vectors switch roles.
    At algorithm execution, the previously up-to-date vector is being used as "historical data"
    to speed up filling the second vector with new up-to-date data.
    */
    public:

    AlgorithmRefreshBorder(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmRefreshBorder();

    AlgorithmStatus Run();

    protected:

    void FilterOldBorderContent(std::vector<unsigned int>& border, unsigned int& border_index_new) const;

    void AddNewContentToBorder(std::vector<unsigned int>& border, unsigned int& border_index_new) const;
};

#endif
