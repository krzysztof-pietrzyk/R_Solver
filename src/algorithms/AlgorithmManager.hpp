#ifndef AlgorithmManager_hpp
#define AlgorithmManager_hpp

#include "grid/GridManager.hpp"

#include "AlgorithmFactory.hpp"

class AlgorithmManager
{
    /*
    This class holds references to the algorithms and manages interactions between them.
    In other words, it defines in which order the algorithms should be executed.
    */
    public:

    AlgorithmManager(GridManager& grid_);

    ~AlgorithmManager();

    bool RunAll();

    private:

    GridManager* grid;
    AlgorithmFactory* factory;
    AlgorithmDataStorage* data;

    Algorithm* layer_one;
    Algorithm* layer_two;
	Algorithm* simple_corners;
	Algorithm* refresh_border;
    Algorithm* refresh_sections;
    Algorithm* refresh_segments;
    Algorithm* refresh_subsegments;
};

#endif
