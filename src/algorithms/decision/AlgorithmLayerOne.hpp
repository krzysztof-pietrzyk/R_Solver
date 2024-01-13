#ifndef ALGORITHM_LAYER_ONE_HPP
#define ALGORITHM_LAYER_ONE_HPP

// project includes
#include "AlgorithmDecision.hpp"

// std includes

// forward declarations
struct LayerOneFieldSignature;


class AlgorithmLayerOne : public AlgorithmDecision
{
    /* 
    "Layer One" algorithm implements the most simple player strategy.
    It makes all safe decisions which can be made by considering one numbered field at a time.
    Example: If a 2 has exactly two covered fields around it, those two fields should be flagged.
    Example: If a 1 has exactly one flag around it, the remaining fields around it should be uncovered.
    */
    public:

    AlgorithmLayerOne(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmLayerOne();

    protected:

    AlgorithmStatus Execution() override;

    private:

    BorderDTO& border_dto;

    LayerOneFieldSignature GetFieldSignature(const uint32_t border_field) const;

    void CheckForSafeClicks(const LayerOneFieldSignature& signature);

    void CheckForMines(const LayerOneFieldSignature& signature);
};

#endif
