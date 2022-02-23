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
    unsigned int num_of_neighbors_temp;
    unsigned char field_value_temp;
    const unsigned int* border;
};

#endif
