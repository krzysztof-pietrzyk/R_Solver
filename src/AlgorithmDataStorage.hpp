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
    bool* is_border;

    unsigned int* face_internal_0;
    unsigned int* face_internal_1;
    unsigned int* border_internal_0;
    unsigned int* border_internal_1;
    bool face_internal_indicator;
    bool border_internal_indicator;

    AlgorithmDataStorage(GridManager& grid);

    ~AlgorithmDataStorage();

    void Clear();
};

#endif
