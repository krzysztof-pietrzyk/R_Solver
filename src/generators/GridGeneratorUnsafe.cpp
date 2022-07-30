#include "GridGeneratorUnsafe.hpp"

GridGeneratorUnsafe::GridGeneratorUnsafe(GridSelfGenerated& grid) : GridInternalGenerator(grid)
{
    int64_t r = std::chrono::system_clock::now().time_since_epoch().count();
    rng = std::minstd_rand(r);
    dist = std::uniform_int_distribution<int>(0, INT_MAX - (INT_MAX % grid.S) - 1);
    forced_safe = std::vector<unsigned int>();
    current_max = 0;
}

GridGeneratorUnsafe::~GridGeneratorUnsafe() {}

void GridGeneratorUnsafe::Generate()
{
    unsigned int poll_index = 0;
    unsigned int random_field = 0;

    grid.Clear();
    PrepareSafeFields();

    for(size_t i = 0; i < grid.M; i++)
    {
        // Get random poll_index between 0 and current_max
        poll_index = dist(rng) % current_max;
        // safe_fields[poll_index] is the next generated mine
        random_field = safe_fields[poll_index];
        grid.mines[i] = random_field;
        grid.is_mine[random_field] = true;
        // Move the last value in safe_fields to safe_fields[poll_index] and decrement current_max
        safe_fields[poll_index] = safe_fields[--current_max];
    }

    CopySafeFields();
    grid.hash.SetUpToDate(false);
    grid.CalculateValues();
}

void GridGeneratorUnsafe::SetStartingField(unsigned int starting_field) {}

void GridGeneratorUnsafe::PrepareSafeFields()
{
    current_max = empty_template.size();
    const size_t empty_template_size = empty_template.size();
    for(size_t i = 0; i < empty_template_size; i++) safe_fields[i] = empty_template[i];
}

void GridGeneratorUnsafe::CopySafeFields()
{
    for(size_t i = 0; i < current_max; i++) grid.not_mines[i] = safe_fields[i];
}
