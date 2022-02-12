#ifndef AlgorithmDataStorage_hpp
#define AlgorithmDataStorage_hpp

#include "GridManager.hpp"

class AlgorithmDataStorage
{
    public:

    unsigned int* face;
    unsigned int face_index;
    unsigned int last_read_index_face;
    bool* is_face;

    unsigned int* border;
    unsigned int border_index;
    unsigned int last_read_index_border;
    unsigned int last_read_index_border_flags;
    bool* is_border;

    unsigned int* face_internal_0;
    unsigned int* face_internal_1;
    unsigned int* border_internal_0;
    unsigned int* border_internal_1;
    bool face_internal_indicator;
    bool border_internal_indicator;
    
    unsigned int* sections_big;
    unsigned int** sections;
    unsigned char* sections_l;
    unsigned char* sections_values;

    unsigned int* sections_neighbors_big;
    unsigned int** sections_neighbors;
    unsigned char* sections_neighbors_l;

    AlgorithmDataStorage(GridManager& grid);

    ~AlgorithmDataStorage();

    void Clear();
};

#endif
