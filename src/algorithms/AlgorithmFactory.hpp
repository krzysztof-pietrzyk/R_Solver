#ifndef ALGORITHM_FACTORY_HPP
#define ALGORITHM_FACTORY_HPP

#include "Algorithm.hpp"
#include "AlgorithmType.hpp"
#include "AlgorithmDataStorage.hpp"

#include "analysis/AlgorithmRefreshBorder.hpp"
#include "analysis/AlgorithmRefreshSections.hpp"
#include "analysis/AlgorithmRefreshSegments.hpp"
#include "analysis/AlgorithmRefreshSubsegments.hpp"
#include "analysis/AlgorithmRefreshFace.hpp"
#include "analysis/AlgorithmRefreshCombinations.hpp"

#include "decision/AlgorithmSimpleCorners.hpp"
#include "decision/AlgorithmLayerOne.hpp"
#include "decision/AlgorithmLayerTwo.hpp"
#include "decision/AlgorithmCombinationsSafeMoves.hpp"
#include "decision/AlgorithmCombinationsLeastRisky.hpp"
#include "decision/AlgorithmGiveUp.hpp"
#include "decision/AlgorithmFirstMove.hpp"

class AlgorithmFactory
{
    /*
    Factory class for creating Algorithm objects.
    */
    public:

    AlgorithmFactory() = delete;

    ~AlgorithmFactory() = delete;

    static Algorithm* Create(AlgorithmType type, GridAccessPlayerIf& grid, AlgorithmDataStorage& data);
};

#endif
