#ifndef STATISTICS_LABELS_HPP
#define STATISTICS_LABELS_HPP

// project includes
#include "../utils/Label.hpp"

// std includes

// forward declarations


namespace Labels
{
    namespace Collectors
    {
        namespace Clicks
        {
            static const Label LEFT_CLICKS = "Left clicks";
            static const Label RIGHT_CLICKS = "Right clicks";
            static const Label WASTED_LEFT_CLICKS = "Wasted left clicks";
            static const Label WASTED_RIGHT_CLICKS = "Wasted right clicks";
            static const Label TIMES_LOST = "Times caused a loss";
        }

        namespace Solver
        {
            static const Label GAMES_PLAYED = "Games played";
            static const Label GAMES_WON = "Games won";
            static const Label GAMES_LOST = "Games lost";
            static const Label TOTAL_FIELDS_UNCOVERED = "Total fields uncovered";
            static const Label TOTAL_MINES_FLAGGED = "Total mines flagged";
            static const Label BEST_WIN_STREAK = "Best win streak";
            static const Label BEST_OF_100 = "Best wins in 100 games";
            static const Label AVERAGE_WIN_STREAK = "Average win streak";
            static const Label AVERAGE_WIN_RATE = "Average win rate";
        }

        namespace Executions
        {
            static const Label EXECUTIONS = "Times executed";
            static const Label NO_MOVES = "Status 'no moves'";
            static const Label SUCCESS = "Status 'success'";
            static const Label FAILURE = "Status 'failure'";
            static const Label GAME_WON = "Status 'game won'";
            static const Label GAME_LOST = "Status 'game lost'";
        }

        namespace ActionsLoss
        {
            static const Label SIMPLE_CORNERS = "Loss from decision: Simple corners";
            static const Label LEAST_RISKY = "Loss from decision: Least risky";
            static const Label OTHER = "Loss from decision: Other";
        }

        namespace Decisions
        {
            static const Label LEFT_CLICKS = "Decisions: Left clicks";
            static const Label RIGHT_CLICKS = "Decisions: Right clicks";
        }

        namespace Generator
        {
            static const Label ZERO = "Total 0_zeros";
            static const Label ONE = "Total 1_ones";
            static const Label TWO = "Total 2_twos";
            static const Label THREE = "Total 3_threes";
            static const Label FOUR = "Total 4_fours";
            static const Label FIVE = "Total 5_fives";
            static const Label SIX = "Total 6_sixes";
            static const Label SEVEN = "Total 7_sevens";
            static const Label EIGHT = "Total 8_eights";
        }
    }

    namespace Producers
    {
        static const Label SOLVER = "Solver";
        static const Label GENERATOR = "Generator";
    }
}

#endif
