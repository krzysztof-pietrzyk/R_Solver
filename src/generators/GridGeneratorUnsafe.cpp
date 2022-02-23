#include "GridGeneratorUnsafe.hpp"

GridGeneratorUnsafe::GridGeneratorUnsafe(GridSelfGenerated& grid) : GridInternalGenerator(grid)
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
    for(unsigned int i = 0; i < empty_template.Len(); i++) safe_fields[i] = empty_template[i];

    grid.Clear();

    for(int i = 0; i < mines_target; i++)
    {
        poll_index = dist(rng) % current_max;
        random_field = safe_fields[poll_index];
        grid.mines += random_field;
        grid.is_mine[random_field] = true;
        safe_fields[poll_index] = safe_fields[--current_max];
    }

    for(unsigned int i = 0; i < current_max; i++) grid.not_mines += safe_fields[i];
    grid.hash_up_to_date = false;
    grid.CalculateValues();
}