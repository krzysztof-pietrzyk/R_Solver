#ifndef AlgorithmLayerOne_hpp
#define AlgorithmLayerOne_hpp

#include "Algorithm.hpp"
#include "AlgorithmDataStorage.hpp"

class AlgorithmLayerOne : public Algorithm
{
    public:

    AlgorithmLayerOne(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmLayerOne();

    bool Run();

    protected:

    AlgorithmDataStorage& data;

    unsigned int border_field_temp;
    unsigned int neighbor_field_temp;
    unsigned char num_of_neighbors_temp;
    unsigned char field_value_temp;
    const unsigned int* border;
    const unsigned char* neighbors_l;
    const bool* is_flag;
    unsigned int** neighbors;
    const bool* is_visible;
    unsigned int* neighbors_temp;
};

#endif
