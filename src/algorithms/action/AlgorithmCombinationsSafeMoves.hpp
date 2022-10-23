#ifndef AlgorithmCombinationsSafeMoves_hpp
#define AlgorithmCombinationsSafeMoves_hpp

#include "AlgorithmAction.hpp"

class AlgorithmCombinationsSafeMoves : public AlgorithmAction
{
    public:

    AlgorithmCombinationsSafeMoves(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmCombinationsSafeMoves();

    protected:

    const std::vector<unsigned int>& face;
    const std::vector<long double>& field_combinations;

    void RunInternal();
};

#endif
