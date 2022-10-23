#include "AlgorithmRefreshFace.hpp"

AlgorithmRefreshFace::AlgorithmRefreshFace(GridManager& grid_, AlgorithmDataStorage& data_)
    : Algorithm(grid_, data_),
    face(data.face), is_face(data.is_face), segments_face(data.segments_face), sections(data.sections),
    segments(data.segments), segments_l(data.segments_l), segments_starting_indexes(data.segments_starting_indexes) {}

AlgorithmRefreshFace::~AlgorithmRefreshFace() {}

AlgorithmStatus AlgorithmRefreshFace::Run()
{
    Clear();

    const unsigned int segments_max = data.segments_count;
    for(size_t segment_id = 0; segment_id < segments_max; segment_id++)
    {
        const unsigned int segment_begin = segments_starting_indexes[segment_id];
        const unsigned int segment_end = segment_begin + segments_l[segment_id];
        for(size_t section_id = segment_begin; section_id < segment_end; section_id++)
        {
            const unsigned int section_origin = segments[section_id];
            const Section& current_section = sections[section_origin];
            const size_t current_section_l = current_section.fields_index;
            for(size_t field_id = 0; field_id < current_section_l; field_id++)
            {
                const unsigned int section_field = current_section.fields[field_id];

                if(is_face[section_field]) { continue; }
                is_face[section_field] = true;
                face[data.face_index++] = section_field;
                segments_face[segment_id].push_back(section_field);
            }
        }
    }

    return AlgorithmStatus::NO_STATUS;
}

void AlgorithmRefreshFace::Clear()
{
    const unsigned int segments_to_clear = data.segments_count;
    for(size_t segment_id = 0; segment_id < segments_to_clear; segment_id++)
    {
        segments_face[segment_id].clear();
    }
    const unsigned int face_index_max = data.face_index;
    for(size_t face_id = 0; face_id < face_index_max; face_id++)
    {
        is_face[face[face_id]] = false;
    }
    data.face_index = 0;
}
