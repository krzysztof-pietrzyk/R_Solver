#ifndef ALGORITHM_FACTORY_HPP
#define ALGORITHM_FACTORY_HPP

#include "Algorithm.hpp"
#include "AlgorithmType.hpp"
#include "data/AlgorithmDataTransfer.hpp"

#include "analysis/AlgorithmBorder.hpp"
#include "analysis/AlgorithmSections.hpp"
#include "analysis/AlgorithmSegments.hpp"
#include "analysis/AlgorithmSubsegments.hpp"
#include "analysis/AlgorithmFace.hpp"
#include "analysis/AlgorithmCombinations.hpp"

#include "decision/AlgorithmSimpleCorners.hpp"
#include "decision/AlgorithmLayerOne.hpp"
#include "decision/AlgorithmLayerTwo.hpp"
#include "decision/AlgorithmCombinationsSafeMoves.hpp"
#include "decision/AlgorithmCombinationsLeastRisky.hpp"

#include "action/AlgorithmGiveUp.hpp"
#include "action/AlgorithmFirstMove.hpp"
#include "action/AlgorithmSimpleActions.hpp"

class AlgorithmFactory
{
    /*
    Factory class for creating Algorithm objects.
    */
    public:

    AlgorithmFactory() = delete;

    ~AlgorithmFactory() = delete;

    static Algorithm* Create(AlgorithmType type, GridAlgorithmIf& grid, AlgorithmDataTransfer& data);
};

#endif
