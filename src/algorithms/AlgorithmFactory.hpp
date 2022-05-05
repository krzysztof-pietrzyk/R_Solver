#ifndef AlgorithmFactory_hpp
#define AlgorithmFactory_hpp

#include <stdexcept>

#include "Algorithm.hpp"
#include "AlgorithmDataStorage.hpp"
#include "AlgorithmRefreshBorder.hpp"
#include "AlgorithmRefreshSections.hpp"
#include "AlgorithmRefreshSegments.hpp"
#include "AlgorithmOptimizedSegments.hpp"
#include "AlgorithmRefreshCombinations.hpp"
#include "AlgorithmLayerOne.hpp"
#include "AlgorithmLayerTwo.hpp"
#include "AlgorithmSimpleCorners.hpp"

enum AlgorithmType
{
    ALGORITHM_REFRESH_BORDER,
    ALGORITHM_REFRESH_SECTIONS,
    ALGORITHM_REFRESH_SEGMENTS,
    ALGORITHM_OPTIMIZED_SEGMENTS,
    ALGORITHM_REFRESH_COMBINATIONS,
    ALGORITHM_LAYER_ONE,
    ALGORITHM_LAYER_TWO,
    ALGORITHM_SIMPLE_CORNERS
};

class AlgorithmFactory
{
    /*
    Factory class for creating Algorithm objects.
    */
    public:

    ~AlgorithmFactory();

    AlgorithmFactory(GridManager& grid_, AlgorithmDataStorage& data_);

    Algorithm* Create(AlgorithmType type);

    private:

    GridManager& grid;
    AlgorithmDataStorage& data;
};

#endif
