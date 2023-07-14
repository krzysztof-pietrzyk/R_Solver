#include "AlgorithmLayerTwo.hpp"

AlgorithmLayerTwo::AlgorithmLayerTwo(GridAccessPlayerIf& grid_, AlgorithmDataStorage& data_)
    : AlgorithmDecision(grid_, data_)
{
    not_common_current = std::vector<uint32_t>();
    not_common_neighbor = std::vector<uint32_t>();
}

AlgorithmLayerTwo::~AlgorithmLayerTwo() {}

AlgorithmStatus AlgorithmLayerTwo::Execution()
{
    const uint32_t sections_origins_index = data.sections_origins_index;
    for(size_t i = 0; i < sections_origins_index; i++)
    {
        const size_t current_section_index = data.sections_origins[i];
        const Section& current_section = data.sections[current_section_index];
        if(!IsCurrentSectionValid(current_section)) { continue; }

        const std::vector<uint32_t>& current_section_neighbors = current_section.neighbors;
        for(size_t j = 0; j < current_section.neighbors_index; j++)
        {
            const size_t neighbor_section_index = current_section_neighbors[j];
            const Section& neighbor_section = data.sections[neighbor_section_index];
            if(!IsNeighborSectionValid(current_section, neighbor_section, neighbor_section_index)) { continue; }

            const uint32_t common_fields_l = CompareSections(current_section, neighbor_section);
            ExecCurrentPerspectiveCondition(current_section, neighbor_section, common_fields_l);
            ExecNeighborPerspectiveCondition(current_section, neighbor_section, common_fields_l);
        }
    }

    return AlgorithmStatus::NO_STATUS;
}

uint32_t AlgorithmLayerTwo::CompareSections(const Section& current_section, const Section& neighbor_section)
{
    // clear the temporary vectors
    not_common_current.clear();
    not_common_neighbor.clear();
    const auto current_section_end = current_section.fields.begin() + current_section.fields_index;
    const auto neighbor_section_end = neighbor_section.fields.begin() + neighbor_section.fields_index;
    // Get current_section - neighbor_section
    std::set_difference(current_section.fields.begin(), current_section_end,
                        neighbor_section.fields.begin(), neighbor_section_end,
                        std::inserter(not_common_current, not_common_current.begin()));
    // get neighbor_section - current_section
    std::set_difference(neighbor_section.fields.begin(), neighbor_section_end,
                        current_section.fields.begin(), current_section_end,
                        std::inserter(not_common_neighbor, not_common_neighbor.begin()));
    const uint32_t current_section_common_l = current_section.fields_index - not_common_current.size();
    const uint32_t neighbor_section_common_l = neighbor_section.fields_index - not_common_neighbor.size();
    if(current_section_common_l != neighbor_section_common_l)
    {
        throw std::runtime_error("ERROR: AlgorithmLayerTwo::CompareSections impossible section!");
    }
    return current_section_common_l;
}

bool AlgorithmLayerTwo::IsCurrentSectionValid(const Section& current_section) const
{
    // ignore sections that have no neighbors
    if(current_section.neighbors_index == 0) { return false; }
    // ignore sections with less than 2 fields
    if(current_section.fields_index < 2) { return false; }
    // else this section is valid
    return true;
}

bool AlgorithmLayerTwo::IsNeighborSectionValid(const Section& current_section, const Section& neighbor_section, const size_t neighbor_section_index) const
{
    // only consider neighbors which are actual section origins
    if(!data.is_section_origin[neighbor_section_index]) { return false; }
    // only compare origin to neighbors with larger field number
    // this assures that each pair of sections is only compared once, not twice
    if(neighbor_section.origin < current_section.origin) { return false; }
    // ignore sections with less than 2 fields
    if(neighbor_section.fields_index < 2) { return false; }
    // else this neighbor is valid
    return true;
}

void AlgorithmLayerTwo::ExecNeighborPerspectiveCondition(const Section& current_section, const Section& neighbor_section, const uint32_t common_fields_l) const
{
    if(neighbor_section.value == current_section.value - current_section.fields_index + common_fields_l)
    {
        for(const uint32_t field : not_common_neighbor) { LeftClick(field); }
        for(const uint32_t field : not_common_current) { RightClick(field); }
    }
}

void AlgorithmLayerTwo::ExecCurrentPerspectiveCondition(const Section& current_section, const Section& neighbor_section, const uint32_t common_fields_l) const
{
    if(current_section.value == neighbor_section.value - neighbor_section.fields_index + common_fields_l)
    {
        for(const uint32_t field : not_common_current) { LeftClick(field); }
        for(const uint32_t field : not_common_neighbor) { RightClick(field); }
    }
}