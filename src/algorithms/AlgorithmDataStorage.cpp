#include "AlgorithmDataStorage.hpp"

AlgorithmDataStorage::AlgorithmDataStorage(GridManager& grid)
{
    is_face = new bool[grid.S] {false};
    face_internal_0 = new unsigned int[grid.S] {0};
    face_internal_1 = new unsigned int[grid.S] {0};
    face = face_internal_0;
    face_internal_indicator = false;
    face_index = 0;
    last_read_index_face = 0;

    is_border = new bool[grid.S] {0};
    border_internal_0 = new unsigned int[grid.S] {0};
    border_internal_1 = new unsigned int[grid.S] {0};
    border = border_internal_0;
    border_internal_indicator = false;
    border_index = 0;
    last_read_index_border = 0;
    last_read_index_border_flags = 0;

    sections_big = new unsigned int[grid.S * 8] {0};
    sections = new unsigned int*[grid.S];
    for(int i = 0; i < grid.S; i++) sections[i] = sections_big + i * 8;
    sections_l = new unsigned char[grid.S] {0};
    sections_values = new unsigned char[grid.S] {0};

    sections_neighbors_big = new unsigned int[grid.S * 16] {0};
    sections_neighbors = new unsigned int*[grid.S];
    for(int i = 0; i < grid.S; i++) sections_neighbors[i] = sections_neighbors_big + i * 16;
    sections_neighbors_l = new unsigned char[grid.S] {0};
}

AlgorithmDataStorage::~AlgorithmDataStorage()
{
    delete[] is_face;
    delete[] face_internal_0;
    delete[] face_internal_1;
    delete[] is_border;
    delete[] border_internal_0;
    delete[] border_internal_1;
    delete[] sections_big;
    delete[] sections;
    delete[] sections_l;
    delete[] sections_values;
    delete[] sections_neighbors_big;
    delete[] sections_neighbors;
    delete[] sections_neighbors_l;
}

void AlgorithmDataStorage::Clear()
{
    for(int i = 0; i < face_index; i++) is_face[face[i]] = false;
    for(int i = 0; i < border_index; i++) is_border[border[i]] = false;
    face_index = 0;
    border_index = 0;
    last_read_index_face = 0;
    last_read_index_border = 0;
    last_read_index_border_flags = 0;
}
