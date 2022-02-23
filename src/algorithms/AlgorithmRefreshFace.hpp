#ifndef AlgorithmRefreshFace_hpp
#define AlgorithmRefreshFace_hpp

#include "Algorithm.hpp"
#include "AlgorithmDataStorage.hpp"

class AlgorithmRefreshFace : public Algorithm
{
    public:

    AlgorithmRefreshFace(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmRefreshFace();

    bool Run();

    protected:

    AlgorithmDataStorage& data;

    unsigned int face_field_temp;
    unsigned int visible_field_temp;
    unsigned char num_of_neighbors_temp;
    unsigned int neighbor_field_temp;
    unsigned int* face_old;
    unsigned int* face_new;
};

#endif