#ifndef ALGORITHM_BORDER_HPP
#define ALGORITHM_BORDER_HPP

#include "../Algorithm.hpp"

class AlgorithmBorder : public Algorithm
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

    AlgorithmBorder(GridAlgorithmAnalysisIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmBorder();

    AlgorithmStatus Execution() override;

    protected:

    void FilterOldBorderContent(uint32_t& border_index_new) const;

    void AddNewContentToBorder(uint32_t& border_index_new) const;

    private:

    uint32_t& D_border_index;
    uint32_t& D_border_last_visible_fields_index;
    std::vector<uint32_t>& D_border;
    std::vector<bool>& D_is_border;

    bool HasAtLeastOneNotVisibleNeighbor(uint32_t field) const;
};

#endif
