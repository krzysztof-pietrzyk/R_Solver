#ifndef ALGORITHM_BORDER_HPP
#define ALGORITHM_BORDER_HPP

// project includes
#include "AlgorithmAnalysis.hpp"

// std includes

// forward declarations


class AlgorithmBorder : public AlgorithmAnalysis
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

    AlgorithmBorder(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmBorder();

    AlgorithmStatus Execution() override;

    private:

    BorderDTO& border_dto;
    std::vector<uint32_t>& border;
    std::vector<bool>& is_border;

    void FilterOldBorderContent(uint32_t& border_index_new) const;

    void AddNewContentToBorder(uint32_t& border_index_new) const;

    bool HasAtLeastOneNotVisibleNeighbor(uint32_t field) const;
};

#endif
