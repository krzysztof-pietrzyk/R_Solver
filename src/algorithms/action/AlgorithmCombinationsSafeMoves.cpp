#include "AlgorithmCombinationsSafeMoves.hpp"

AlgorithmCombinationsSafeMoves::AlgorithmCombinationsSafeMoves(GridManager& grid_, AlgorithmDataStorage& data_) : AlgorithmAction(grid_, data_) {}

AlgorithmCombinationsSafeMoves::~AlgorithmCombinationsSafeMoves() {}

AlgorithmStatus AlgorithmCombinationsSafeMoves::RunInternal()
{
    const unsigned int number_of_clicks_before = grid.left_click_counter + grid.right_click_counter;

    const long double total_combinations = data.total_combinations;
    const unsigned int face_length = data.face_index;
    for(unsigned int i = 0; i < face_length; i++)
    {
        const unsigned int face_field = data.face[i];
        const long double face_field_combinations = data.field_combinations[face_field];
        if(face_field_combinations == 0.0L) 
        {
            // A mine on this field appears in 0 combinations - it's safe
            grid.LeftClick(face_field);
        }
        else if(face_field_combinations == total_combinations)
        {
            // A mine on this field appears in all combinations - it's a mine
            grid.RightClick(face_field);
        }
    }

    const unsigned int number_of_clicks_after = grid.left_click_counter + grid.right_click_counter;
    if(number_of_clicks_after > number_of_clicks_before) { return AlgorithmStatus::SUCCESS; }
    return AlgorithmStatus::NO_MOVES;
}
