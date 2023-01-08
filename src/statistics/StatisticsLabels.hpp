#ifndef STATISTICS_LABELS_HPP
#define STATISTICS_LABELS_HPP

#include "../utils/Label.hpp"

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
        }

        namespace Solver
        {
            static const Label GAMES_PLAYED = "Games played";
            static const Label GAMES_WON = "Games won";
            static const Label GAMES_ABANDONED = "Games abandoned";
            static const Label TOTAL_FIELDS_UNCOVERED = "Total fields uncovered";
        }

        namespace Executions
        {
            static const Label EXECUTIONS = "Times executed";
        }
    }

    namespace Producers
    {
        static const Label SOLVER = "Solver";
    }
}

#endif
