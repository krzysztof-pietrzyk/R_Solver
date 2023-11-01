#ifndef ALGORITHM_FACTORY_HPP
#define ALGORITHM_FACTORY_HPP

// project includes
#include "Algorithm.hpp"
#include "AlgorithmType.hpp"
#include "data/AlgorithmDataTransfer.hpp"
#include "../grid/GridAlgorithmIf.hpp"

// std includes

// forward declarations


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
