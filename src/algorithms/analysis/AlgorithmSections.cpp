#include "AlgorithmSections.hpp"

AlgorithmSections::AlgorithmSections(GridAccessPlayerIf& grid_, AlgorithmDataStorage& data_)
    : Algorithm(grid_, data_),
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
    diff_bit_31(2 * grid_dim.width + 2),
    D_sections_origins_index(GetModifiableAlgorithmDataStorageReference().sections_origins_index),
    D_is_section_origin(GetModifiableAlgorithmDataStorageReference().is_section_origin),
    D_sections_origins(GetModifiableAlgorithmDataStorageReference().sections_origins),
    D_sections(GetModifiableAlgorithmDataStorageReference().sections)
{
    LOGGER(LogLevel::INIT) << "AlgorithmSections";
    LOGGER_ASSERT(grid_dim.size <= MAX_ALLOWED_GRID_SIZE, "AlgorithmSections - Grid size too large");
    sections_hashes = std::vector<uint32_t>(grid_dim.size, 0);
    section_value_temp = 0;
    current_section_hash = 0;
}

AlgorithmSections::~AlgorithmSections() {}

AlgorithmStatus AlgorithmSections::Execution()
{
    Clear();

    const uint32_t border_l = data.border_index;

    // iterate through border fields
    for(size_t i = 0; i < border_l; i++)
    {
        const uint32_t border_field = data.border[i];
        AnalyzeSection(border_field);
    }

    return AlgorithmStatus::NO_STATUS;
}

void AlgorithmSections::Clear()
{
    for(size_t i = 0; i < data.sections_origins_index; i++)
    {
        const uint32_t section_origin = data.sections_origins[i];
        D_is_section_origin[section_origin] = false;
        D_sections[section_origin].fields_index = 0;
        D_sections[section_origin].neighbors_index = 0;
    }
    D_sections_origins_index = 0;
}

void AlgorithmSections::AnalyzeSection(const uint32_t border_field)
{
        Section& current_section = D_sections[border_field];
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
            sections_hashes[data.sections_origins_index] = current_section_hash;
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
    D_sections[border_field].AddField(border_field_neighbor);
    // encode data about the section into the hash
    if(data.sections[border_field].fields_index == 1) { current_section_hash += border_field_neighbor; }
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
    if(!data.is_border[section_neighbor] || section_neighbor == border_field) { return; }
    // ignore duplicate neighbors
    if(current_section.HasNeighbor(section_neighbor)) { return; }
    current_section.AddNeighbor(section_neighbor);
}

void AlgorithmSections::SaveSectionData(const uint32_t border_field, Section& current_section) const
{
    // Save all the information about the section
    D_sections_origins[D_sections_origins_index++] = border_field;
    D_is_section_origin[border_field] = true;
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
    auto end = sections_hashes.begin() + data.sections_origins_index;
    return std::find(sections_hashes.begin(), end, hash) == end;
}
