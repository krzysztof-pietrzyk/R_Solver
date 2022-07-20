#include "AlgorithmRefreshFace.hpp"

AlgorithmRefreshFace::AlgorithmRefreshFace(GridManager& grid_, AlgorithmDataStorage& data_) : Algorithm(grid_, data_)
{

}

AlgorithmRefreshFace::~AlgorithmRefreshFace() {}

AlgorithmStatus AlgorithmRefreshFace::RunInternal()
{
    Clear();

    const unsigned int segments_max = data.segments_count;
    for(size_t segment_id = 0; segment_id < segments_max; segment_id++)
    {
        const unsigned int segment_begin = data.segments_starting_indexes[segment_id];
        const unsigned int segment_end = segment_begin + data.segments_l[segment_id];
        for(size_t section_id = segment_begin; section_id < segment_end; section_id++)
        {
            const unsigned int section_origin = data.segments[section_id];
            const unsigned int section_begin = section_origin * MAX_SECTION_LENGTH;
            const unsigned int section_end = section_begin + data.sections_l[section_origin];
            for(size_t field_id = section_begin; field_id < section_end; field_id++)
            {
                const unsigned int section_field = data.sections[field_id];

                if(data.is_face[section_field]) { continue; }
                data.is_face[section_field] = true;
                data.face[data.face_index++] = section_field;
                data.segments_face[segment_id].push_back(section_field);
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
        data.segments_face[segment_id].clear();
    }
    const unsigned int face_index_max = data.face_index;
    for(size_t face_id = 0; face_id < face_index_max; face_id++)
    {
        data.is_face[data.face[face_id]] = false;
    }
    data.face.clear();
    data.face_index = 0;
}
