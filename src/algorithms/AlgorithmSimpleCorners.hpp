#ifndef AlgorithmSimpleCorners_hpp
#define AlgorithmSimpleCorners_hpp

#include "Algorithm.hpp"

class AlgorithmSimpleCorners : public Algorithm
{
    public:

    AlgorithmSimpleCorners(GridManager& grid_);

    ~AlgorithmSimpleCorners();

    bool Run();

    private:

    const unsigned int corners_number;
    std::vector<unsigned int> corners;
};

#endif
