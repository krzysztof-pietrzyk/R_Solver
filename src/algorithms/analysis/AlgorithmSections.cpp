// implemented header
#include "AlgorithmSections.hpp"

// project includes
#include "../data/Section.hpp"

// std includes
#include <algorithm>


const uint32_t AlgorithmSections::max_allowed_grid_size = 1048576U;

AlgorithmSections::AlgorithmSections(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_)
    : AlgorithmAnalysis(grid_, data_),
    border_dto(data_.border_dto),
    sections_dto(data_.sections_dto),
    diff_bit_20(1), diff_bit_21(2),
    diff_bit_22(grid_dim.width - 2),
    diff_bit_23(grid_dim.width - 1),
    diff_bit_24(grid_dim.width),
    diff_bit_25(grid_dim.width + 1),
    diff_bit_26(grid_dim.width + 2),
    diff_bit_27(2 * grid_dim.width - 2),
    diff_bit_28(2 * grid_dim.width - 1),
    diff_bit_29(2 * grid_dim.width),
    diff_bit_30(2 * grid_dim.width + 1),
    diff_bit_31(2 * grid_dim.width + 2)
{
    LOGGER(LogLevel::INIT) << "AlgorithmSections";
    LOGGER_ASSERT(grid_dim.size <= max_allowed_grid_size, "AlgorithmSections - Grid size too large");
    sections_hashes = std::vector<uint32_t>(grid_dim.size, 0);
    section_value_temp = 0;
    current_section_hash = 0;
}

AlgorithmSections::~AlgorithmSections() {}

AlgorithmStatus AlgorithmSections::Execution()
{
    sections_dto.Clear();

    const uint32_t border_l = border_dto.index;

    // iterate through border fields
    for(size_t i = 0; i < border_l; i++)
    {
        const uint32_t border_field = border_dto.border[i];
        AnalyzeSection(border_field);
    }

    return AlgorithmStatus::NO_STATUS;
}

void AlgorithmSections::AnalyzeSection(const uint32_t border_field)
{
    Section& current_section = sections_dto.sections[border_field];
    current_section.Clear();
    section_value_temp = grid.GetFieldValue(border_field);
    current_section_hash = 0;
    // iterate through each border field's neigbors
    for(const uint32_t& border_field_neighbor : grid.GetNeighbors(border_field))
    {
        AnalyzeSectionField(border_field, border_field_neighbor, current_section);
    }
    // Check if section is not a duplicate
    if(CheckHashUnique(current_section_hash))
    {
        sections_hashes[sections_dto.sections_origins.Index()] = current_section_hash;
        SaveSectionData(border_field, current_section);
    }
}

void AlgorithmSections::AnalyzeSectionField(const uint32_t border_field, const uint32_t border_field_neighbor, Section& current_section)
{
    // count the number of flags already marked around the border_field
    if(flagged.Contains(border_field_neighbor))
    {
        section_value_temp--;
        return;
    }
    // if this neighbor is already visible, ignore it
    else if(visible.Contains(border_field_neighbor))
    {
        return;
    }
    // add this neighbor to the section
    sections_dto.sections[border_field].AddField(border_field_neighbor);
    // encode data about the section into the hash
    if(sections_dto.sections[border_field].fields_index == 1) { current_section_hash += border_field_neighbor; }
    else { current_section_hash += GetHashBit(border_field_neighbor - current_section.fields[0]); }
    // iterate through the neighbors of that neighbor, in order to determine
    // potential neighbour sections of this section
    for(const uint32_t& section_neighbor : grid.GetNeighbors(border_field_neighbor))
    {
        AnalyzeSectionNeighbor(border_field, section_neighbor, current_section);
    }
}

void AlgorithmSections::AnalyzeSectionNeighbor(const uint32_t border_field, const uint32_t section_neighbor, Section& current_section) const
{
    // if this neighbor is not on border or is the currently considered field, ignore it
    if(!border_dto.is_border[section_neighbor] || section_neighbor == border_field)
    {
        return;
    }
    // ignore duplicate neighbors
    if(current_section.HasNeighbor(section_neighbor))
    {
        return;
    }
    current_section.AddNeighbor(section_neighbor);
}

void AlgorithmSections::SaveSectionData(const uint32_t border_field, Section& current_section) const
{
    // Save all the information about the section
    sections_dto.sections_origins.Add(border_field);
    current_section.value = section_value_temp;
    current_section.origin = border_field;
}

uint32_t AlgorithmSections::GetHashBit(uint32_t difference) const
{
	/* This method will only work as intended if the map has less than 1048576 fields

	Abstract structure of a section:

              XXXX 2^20 2^21
    2^22 2^23 2^24 2^25 2^26
    2^27 2^28 2^29 2^30 2^31

    where XXXX means the first field of section in order from left to right and from top to bottom
    it is assured by the section generating code that the first field in the section is XXXX
    summing the numbers assigned to fields relative to field XXXX encodes information about shape of the section in a unique way
    the goal here is to encode all information about the given section within a single 32bit int hash
    with that achieved it is much faster to compare sections between each other and exclude multiple occurences */

         if(difference == diff_bit_20) return (uint32_t)0b00000000000100000000000000000000;  // 2^20
    else if(difference == diff_bit_21) return (uint32_t)0b00000000001000000000000000000000;  // 2^21
    else if(difference == diff_bit_22) return (uint32_t)0b00000000010000000000000000000000;  // 2^22
    else if(difference == diff_bit_23) return (uint32_t)0b00000000100000000000000000000000;  // 2^23
    else if(difference == diff_bit_24) return (uint32_t)0b00000001000000000000000000000000;  // 2^24
    else if(difference == diff_bit_25) return (uint32_t)0b00000010000000000000000000000000;  // 2^25
    else if(difference == diff_bit_26) return (uint32_t)0b00000100000000000000000000000000;  // 2^26
    else if(difference == diff_bit_27) return (uint32_t)0b00001000000000000000000000000000;  // 2^27
    else if(difference == diff_bit_28) return (uint32_t)0b00010000000000000000000000000000;  // 2^28
    else if(difference == diff_bit_29) return (uint32_t)0b00100000000000000000000000000000;  // 2^29
    else if(difference == diff_bit_30) return (uint32_t)0b01000000000000000000000000000000;  // 2^30
    else if(difference == diff_bit_31) return (uint32_t)0b10000000000000000000000000000000;  // 2^31
    else LOGGER_THROW("AlgorithmFactory::Create - unhandled AlgorithmType");
}

bool AlgorithmSections::CheckHashUnique(uint32_t hash) const
{
    auto end = sections_hashes.begin() + sections_dto.sections_origins.Index();
    return std::find(sections_hashes.begin(), end, hash) == end;
}
