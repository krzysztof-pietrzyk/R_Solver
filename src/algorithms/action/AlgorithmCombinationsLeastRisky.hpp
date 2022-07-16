#ifndef AlgorithmCombinationsLeastRisky_hpp
#define AlgorithmCombinationsLeastRisky_hpp

#include "AlgorithmAction.hpp"

class AlgorithmCombinationsLeastRisky : public AlgorithmAction
{
    /*
    This algorithm goes through face fields and clicks on ONE field, which is
    least likely to be a mine. It's important to note that it ignores all fields
    that are not on the face and it does not perform any other logic - only simple probability.

    When there is no fields on the face (case with an 'island' made by mines),
    this algorithm will do nothing.
    */
    public:

    AlgorithmCombinationsLeastRisky(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmCombinationsLeastRisky();

    protected:

    AlgorithmStatus RunInternal();
};

#endif
