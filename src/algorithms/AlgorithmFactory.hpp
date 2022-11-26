#ifndef ALGORITHM_FACTORY_HPP
#define ALGORITHM_FACTORY_HPP

#include <stdexcept>

#include "Algorithm.hpp"
#include "AlgorithmType.hpp"
#include "AlgorithmDataStorage.hpp"

#include "analysis/AlgorithmRefreshBorder.hpp"
#include "analysis/AlgorithmRefreshSections.hpp"
#include "analysis/AlgorithmRefreshSegments.hpp"
#include "analysis/AlgorithmRefreshSubsegments.hpp"
#include "analysis/AlgorithmRefreshFace.hpp"
#include "analysis/AlgorithmRefreshCombinations.hpp"

#include "action/AlgorithmSimpleCorners.hpp"
#include "action/AlgorithmLayerOne.hpp"
#include "action/AlgorithmLayerTwo.hpp"
#include "action/AlgorithmCombinationsSafeMoves.hpp"
#include "action/AlgorithmCombinationsLeastRisky.hpp"
#include "action/AlgorithmGiveUp.hpp"
#include "action/AlgorithmFirstMove.hpp"

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
