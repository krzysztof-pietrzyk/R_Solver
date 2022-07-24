#include "GridGeneratorUnsafe.hpp"

#include <vector>
#include <iostream>

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

    std::vector<unsigned int> forced_mines = 
    {
        3, 7, 23, 24, 29, 
        30, 33, 37, 42, 46, 51, 57, 58, 
        62, 64, 66, 69, 70, 71, 75, 76, 79, 81, 84, 
        95, 98, 103, 106, 110, 111, 114, 115, 117, 
        121, 122, 125, 135, 140, 144, 148, 
        153, 161, 162, 166, 177, 179, 
        183,
        213, 217, 219, 237, 
        240, 242, 244, 266, 267, 269, 
        272, 
        301, 318, 319, 323, 327, 
        332, 341, 345, 353, 
        361, 364, 366, 369, 370, 374, 375, 379, 382, 384, 387, 388, 
        392, 396, 397, 400, 401, 402, 405, 409, 410, 412, 415, 416, 
        422, 427, 438, 445, 
        450, 465, 466, 479
    };

    for(size_t i = 0; i < grid.M; i++)
    {
        // safe_fields[poll_index] is the next generated mine
        random_field = forced_mines[i];
        grid.mines[i] = random_field;
        grid.is_mine[random_field] = true;
        // Move the last value in safe_fields to safe_fields[poll_index] and decrement current_max
    }

    CopySafeFields();
    grid.hash_up_to_date = false;
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
    size_t index = 0;
    for(size_t i = 0; i < grid.S; i++)
    {
        if(!grid.is_mine[i]) grid.not_mines[index++] = i;
    }
}
