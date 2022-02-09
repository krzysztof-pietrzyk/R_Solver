#ifndef AlgorithmRefreshSections_hpp
#define AlgorithmRefreshSections_hpp

#include "Algorithm.hpp"
#include "AlgorithmDataStorage.hpp"

class AlgorithmRefreshSections : public Algorithm
{
    public:

    AlgorithmRefreshSections(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmRefreshSections();

    bool Run();

    protected:

    AlgorithmDataStorage& data;

    unsigned int current_border_field;
    unsigned int neighbor_temp;
    unsigned int neighbor_section_temp;
    unsigned int* neighbors_of_neighbor_temp;
    unsigned char neighbors_of_neighbor_temp_l;
    unsigned int potential_section_neighbor;
    unsigned char section_value_temp;
    unsigned int* border_field_neighbors;
    unsigned char border_field_neighbors_l;
};

#endif
    