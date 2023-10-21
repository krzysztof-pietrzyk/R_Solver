#ifndef ALGORITHM_LAYER_TWO_HPP
#define ALGORITHM_LAYER_TWO_HPP

#include "AlgorithmDecision.hpp"

#include <vector>
#include <algorithm>

class AlgorithmLayerTwo : public AlgorithmDecision
{
    /*
    "Layer Two" algorithm implements the medium difficulty player strategy.
    It makes all safe decisions which can be made by considering pairs of neighboring numbered fields.
    */
    public:

    AlgorithmLayerTwo(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmLayerTwo();

    protected:

    AlgorithmStatus Execution() override;

    private:

    SectionsDTO& sections_dto;

    std::vector<uint32_t> not_common_current;
    std::vector<uint32_t> not_common_neighbor;

    uint32_t CompareSections(const Section& a, const Section& b);

    bool IsCurrentSectionValid(const Section& current_section) const;

    bool IsNeighborSectionValid(const Section& current_section, const Section& neighbor_section, const size_t neighbor_section_index) const;

    void ExecNeighborPerspectiveCondition(const Section& current_section, const Section& neighbor_section, const uint32_t common_fields_l);

    void ExecCurrentPerspectiveCondition(const Section& current_section, const Section& neighbor_section, const uint32_t common_fields_l);
};

#endif
