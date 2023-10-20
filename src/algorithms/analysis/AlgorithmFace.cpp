#include "AlgorithmFace.hpp"

AlgorithmFace::AlgorithmFace(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_)
    : AlgorithmAnalysis(grid_, data_),
    sections_dto(data_.sections_dto),
    segments_dto(data_.segments_dto),
    face_dto(data_.face_dto)
{
    LOGGER(LogLevel::INIT) << "AlgorithmFace";
}

AlgorithmFace::~AlgorithmFace() {}

AlgorithmStatus AlgorithmFace::Execution()
{
    Clear();

    const uint32_t segments_max = segments_dto.segments_count;
    for(size_t segment_id = 0; segment_id < segments_max; segment_id++)
    {
        const uint32_t segment_begin = segments_dto.segments_starting_indexes[segment_id];
        const uint32_t segment_end = segment_begin + segments_dto.segments_l[segment_id];
        for(size_t section_id = segment_begin; section_id < segment_end; section_id++)
        {
            const uint32_t section_origin = segments_dto.segments[section_id];
            const Section& current_section = sections_dto.sections[section_origin];
            const size_t current_section_l = current_section.fields_index;
            for(size_t field_id = 0; field_id < current_section_l; field_id++)
            {
                const uint32_t section_field = current_section.fields[field_id];
                if(face_dto.face.Contains(section_field)) { continue; }
                face_dto.face.Add(section_field);
                face_dto.segments_face[segment_id].push_back(section_field);
            }
        }
    }

    return AlgorithmStatus::NO_STATUS;
}

void AlgorithmFace::Clear()
{
    const uint32_t segments_to_clear = segments_dto.segments_count;
    for(size_t segment_id = 0; segment_id < segments_to_clear; segment_id++)
    {
        face_dto.segments_face[segment_id].clear();
    }
    face_dto.face.Clear();
}
