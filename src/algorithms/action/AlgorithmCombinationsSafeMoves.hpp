#ifndef AlgorithmCombinationsSafeMoves_hpp
#define AlgorithmCombinationsSafeMoves_hpp

#include "AlgorithmAction.hpp"

class AlgorithmCombinationsSafeMoves : public AlgorithmAction
{
    /*
    This algorithm goes through data about combinations and checks whether there are any
    fields which must be mines or must be safe. It performs left and right clicks accordingly.
    */
    public:

    AlgorithmCombinationsSafeMoves(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmCombinationsSafeMoves();

    protected:

    AlgorithmStatus RunInternal();
};

#endif
