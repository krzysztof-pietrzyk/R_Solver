#ifndef AlgorithmManager_hpp
#define AlgorithmManager_hpp

#include "GridManager.hpp"
#include "AlgorithmFactory.hpp"

class AlgorithmManager
{
    public:

    AlgorithmManager(GridManager& grid_);

    ~AlgorithmManager();

    bool RunAll();

    private:

    GridManager* grid;
    AlgorithmFactory* factory;
    AlgorithmDataStorage* data;

    Algorithm* layer_one;
	Algorithm* simple_corners;
	Algorithm* refresh_border;
    Algorithm* refresh_sections;
};

#endif
