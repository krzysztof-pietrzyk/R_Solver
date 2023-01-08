#ifndef ALGORITHM_LAYER_ONE_HPP
#define ALGORITHM_LAYER_ONE_HPP

#include "AlgorithmAction.hpp"

#include <tuple>

struct LayerOneFieldSignature
{
    uint32_t field = 0;
    uint8_t flags_count = 0;
    uint8_t not_visible_count = 0;
    uint8_t field_value = 0;
};

class AlgorithmLayerOne : public AlgorithmAction
{
    /* 
    "Layer One" algorithm implements the most simple player strategy.
    It makes all safe decisions which can be made by considering one numbered field at a time.
    Example: If a 2 has exactly two covered fields around it, those two fields should be flagged.
    Example: If a 1 has exactly one flag around it, the remaining fields around it should be uncovered.
    */
    public:

    AlgorithmLayerOne(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmLayerOne();

    protected:

    AlgorithmStatus Execution() override;

    LayerOneFieldSignature GetFieldSignature(const uint32_t border_field) const;

    void CheckForSafeClicks(const LayerOneFieldSignature signature) const;

    void CheckForMines(const LayerOneFieldSignature signature) const;
};

#endif
