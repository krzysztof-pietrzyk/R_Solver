#ifndef AlgorithmSimpleCorners_hpp
#define AlgorithmSimpleCorners_hpp

#include "AlgorithmAction.hpp"

class AlgorithmSimpleCorners : public AlgorithmAction
{
    /*
    This algorithm implements the player strategy for simlpy uncovering the four corners of the map.
    Each time this algorithm is executed, one corner is uncovered (if any are left).
    This algorithm performs the first click of the game and is rather rarely use outside of the beginning
    of the game because there are usually better strategies than simply uncovering corners.
    */
    public:

    AlgorithmSimpleCorners(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmSimpleCorners();

    protected:

    const unsigned int corners_number;
    std::vector<unsigned int> corners;

    void RunInternal();

    unsigned int GetCorner() const;
};

#endif
