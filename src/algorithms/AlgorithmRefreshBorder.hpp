#ifndef AlgorithmRefreshBorder_hpp
#define AlgorithmRefreshBorder_hpp

#include "Algorithm.hpp"
#include "AlgorithmDataStorage.hpp"

class AlgorithmRefreshBorder : public Algorithm
{
    public:

    AlgorithmRefreshBorder(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmRefreshBorder();

    bool Run();

    protected:

    AlgorithmDataStorage& data;

    unsigned int border_field_temp;
    unsigned int visible_field_temp;
    unsigned char num_of_neighbors_temp;
    unsigned int neighbor_field_temp;
    unsigned int* border_old;
    unsigned int* border_new;
};

#endif
