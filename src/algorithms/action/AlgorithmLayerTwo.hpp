#ifndef AlgorithmLayerTwo_hpp
#define AlgorithmLayerTwo_hpp

#include "AlgorithmAction.hpp"

#include <vector>
#include <algorithm>

class AlgorithmLayerTwo : public AlgorithmAction
{
    /*
    "Layer Two" algorithm implements the medium difficulty player strategy.
    It makes all safe decisions which can be made by considering pairs of neighboring numbered fields.
    */
    public:

    AlgorithmLayerTwo(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmLayerTwo();

    protected:

    std::vector<unsigned int> not_common_current;
    std::vector<unsigned int> not_common_neighbor;

    std::vector<unsigned int>& sections_origins;
    std::vector<Section>& sections;
    std::vector<bool>& is_section_origin;

    void RunInternal();

    unsigned int CompareSections(const Section& a, const Section& b);

    bool IsCurrentSectionValid(const Section& current_section) const;

    bool IsNeighborSectionValid(const Section& current_section, const Section& neighbor_section) const;

    void ExecNeighborPerspectiveCondition(const Section& current_section, const Section& neighbor_section, const unsigned int common_fields_l) const;

    void ExecCurrentPerspectiveCondition(const Section& current_section, const Section& neighbor_section, const unsigned int common_fields_l) const;
};

#endif