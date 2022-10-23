#ifndef AlgorithmCombinationsLeastRisky_hpp
#define AlgorithmCombinationsLeastRisky_hpp

#include "AlgorithmAction.hpp"

class AlgorithmCombinationsLeastRisky : public AlgorithmAction
{
    public:

    AlgorithmCombinationsLeastRisky(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmCombinationsLeastRisky();

    protected:

    const std::vector<unsigned int>& face;
    const std::vector<long double>& field_combinations;

    void RunInternal();

    unsigned int FindSafestField() const;
};

#endif
