#include "AlgorithmFace.hpp"

AlgorithmFace::AlgorithmFace(GridAlgorithmAnalysisIf& grid_, AlgorithmDataTransfer& data_)
    : Algorithm(grid_, data_),
    D_face_index(GetModifiableAlgorithmDataTransferReference().face_index),
    D_face(GetModifiableAlgorithmDataTransferReference().face),
    D_is_face(GetModifiableAlgorithmDataTransferReference().is_face),
    D_segments_face(GetModifiableAlgorithmDataTransferReference().segments_face)
{
    LOGGER(LogLevel::INIT) << "AlgorithmFace";
}

AlgorithmFace::~AlgorithmFace() {}

AlgorithmStatus AlgorithmFace::Execution()
{
    Clear();

    const uint32_t segments_max = data.segments_count;
    for(size_t segment_id = 0; segment_id < segments_max; segment_id++)
    {
        const uint32_t segment_begin = data.segments_starting_indexes[segment_id];
        const uint32_t segment_end = segment_begin + data.segments_l[segment_id];
        for(size_t section_id = segment_begin; section_id < segment_end; section_id++)
        {
            const uint32_t section_origin = data.segments[section_id];
            const Section& current_section = data.sections[section_origin];
            const size_t current_section_l = current_section.fields_index;
            for(size_t field_id = 0; field_id < current_section_l; field_id++)
            {
                const uint32_t section_field = current_section.fields[field_id];

                if(data.is_face[section_field]) { continue; }
                D_is_face[section_field] = true;
                D_face[D_face_index++] = section_field;
                D_segments_face[segment_id].push_back(section_field);
            }
        }
    }

    return AlgorithmStatus::NO_STATUS;
}

void AlgorithmFace::Clear()
{
    const uint32_t segments_to_clear = data.segments_count;
    for(size_t segment_id = 0; segment_id < segments_to_clear; segment_id++)
    {
        D_segments_face[segment_id].clear();
    }
    const uint32_t face_index_max = data.face_index;
    for(size_t face_id = 0; face_id < face_index_max; face_id++)
    {
        D_is_face[data.face[face_id]] = false;
    }
    D_face_index = 0;
}
