#ifndef ALGORITHM_DECISION_HPP
#define ALGORITHM_DECISION_HPP

#include "../Algorithm.hpp"

class AlgorithmDecision : public Algorithm
{
    /* 
    Abstract class for algorithms which take a decision, 
    meaning they decide which fields are safe and which are not.
    */
    public:

    AlgorithmDecision(GridAccessPlayerIf& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmDecision();

    AlgorithmStatus Run() override;

    protected:

    bool LeftClick(const uint32_t field);

    bool RightClick(const uint32_t field);

    private:

    uint64_t left_click_counter;
    uint64_t right_click_counter;
    GridAccessPlayerIf& D_grid;

    AlgorithmStatus CheckGameOverConditions() const;

    AlgorithmStatus GetActionResult(const uint32_t clicks_difference) const;
};

#endif
