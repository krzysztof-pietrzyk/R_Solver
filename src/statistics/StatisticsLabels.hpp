#ifndef STATISTICS_LABELS_HPP
#define STATISTICS_LABELS_HPP

#include <string>

namespace Labels::Data
{
    namespace Clicks
    {
        static const std::string LEFT_CLICKS = "Left clicks";
        static const std::string RIGHT_CLICKS = "Right clicks";
        static const std::string WASTED_LEFT_CLICKS = "Wasted left clicks";
        static const std::string WASTED_RIGHT_CLICKS = "Wasted right clicks";
    }

    namespace Solver
    {
        static const std::string GAMES_PLAYED = "Games played";
        static const std::string GAMES_WON = "Games won";
        static const std::string GAMES_ABANDONED = "Games abandoned";
        static const std::string TOTAL_FIELDS_UNCOVERED = "Total fields uncovered";
    }
}

namespace Labels::Producers
{
    static const std::string SOLVER = "Solver";
}

#endif