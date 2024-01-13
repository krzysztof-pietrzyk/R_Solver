#ifndef ALGORITHM_SIMPLE_CORNERS_HPP
#define ALGORITHM_SIMPLE_CORNERS_HPP

// project includes
#include "AlgorithmDecision.hpp"

// std includes

// forward declarations


class AlgorithmSimpleCorners : public AlgorithmDecision
{
    /*
    This algorithm implements the player strategy for simlpy uncovering the four corners of the map.
    Each time this algorithm is executed, one corner is uncovered (if any are left).
    This algorithm performs the first click of the game and is rather rarely use outside of the beginning
    of the game because there are usually better strategies than simply uncovering corners.
    */
    public:

    AlgorithmSimpleCorners(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmSimpleCorners();

    protected:

    std::vector<uint32_t> corners;

    AlgorithmStatus Execution() override;
};

#endif
