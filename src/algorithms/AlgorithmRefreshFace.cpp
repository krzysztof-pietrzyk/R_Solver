#include "AlgorithmRefreshFace.hpp"

AlgorithmRefreshFace::AlgorithmRefreshFace(GridManager& grid_, AlgorithmDataStorage& data_) : Algorithm(grid_), data(data_)
{
    unsigned int face_field_temp = 0;
    unsigned int visible_field_temp = 0;
    unsigned char num_of_neighbors_temp = 0;
    unsigned int neighbor_field_temp = 0;
    unsigned int* neighbors_temp = nullptr;
    unsigned int* face_old = nullptr;
    unsigned int* face_new = nullptr;
}

AlgorithmRefreshFace::~AlgorithmRefreshFace() {}

bool AlgorithmRefreshFace::Run()
{
    if(data.last_read_index_face == grid.visible_fields_index) return true;
    
    const unsigned int face_index_old = data.face_index;
    const unsigned int visible_fields_new_index = grid.visible_fields_index;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int face_index_new = 0;

    face_old = data.face_internal_indicator ? data.face_internal_0 : data.face_internal_1;
    face_new = data.face_internal_indicator ? data.face_internal_1 : data.face_internal_0;
    
    for(i = 0; i < face_index_old; i++)
    {
        face_field_temp = face_old[i];
        if(!grid.is_visible[face_field_temp] && !grid.is_flag[face_field_temp]) face_new[face_index_new++] = face_field_temp;
        else data.is_face[face_field_temp] = false;
    }

    for(i = data.last_read_index_face; i < visible_fields_new_index; i++)
    {
        visible_field_temp = grid.visible_fields[i];
        num_of_neighbors_temp = grid.neighbors_l[visible_field_temp];
        neighbors_temp = grid.neighbors[visible_field_temp];
        for(j = 0; j < num_of_neighbors_temp; j++)
        {
            neighbor_field_temp = neighbors_temp[j];
            if(!grid.is_visible[neighbor_field_temp] && !grid.is_flag[neighbor_field_temp] && !data.is_face[neighbor_field_temp])
            {
                data.is_face[neighbor_field_temp] = true;
                face_new[face_index_new++] = neighbor_field_temp;
            }
        }
    }

    data.last_read_index_face = visible_fields_new_index;
    data.face = face_new;
    data.face_internal_indicator = !data.face_internal_indicator;
    data.face_index = face_index_new;
    return true;
}