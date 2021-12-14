#include "GridGeneratorUnsafe.hpp"

GridGeneratorUnsafe::GridGeneratorUnsafe(Grid& grid) : GridGenerator(grid)
{
    int64_t r = std::chrono::system_clock::now().time_since_epoch().count();
    rng = std::minstd_rand(r);
    dist = std::uniform_int_distribution<int>(0, INT_MAX - (INT_MAX % grid.S) - 1);
}

GridGeneratorUnsafe::~GridGeneratorUnsafe() {}

void GridGeneratorUnsafe::Generate()
{
    unsigned int current_max = grid.S;
    const unsigned int mines_target = grid.M;
    unsigned int poll_index;
    unsigned int random_field;
    std::copy(empty_template, empty_template + grid.S, safe_fields);

    grid.Clear();

    for(int i = 0; i < mines_target; i++)
    {
        poll_index = dist(rng) % current_max;
        random_field = safe_fields[poll_index];
        grid.mines[i] = random_field;
        grid.is_mine[random_field] = true;
        safe_fields[poll_index] = safe_fields[--current_max];
    }

    std::copy(safe_fields, safe_fields + current_max, grid.not_mines);
    grid.hash_up_to_date = false;
    grid.CalculateValues();
}