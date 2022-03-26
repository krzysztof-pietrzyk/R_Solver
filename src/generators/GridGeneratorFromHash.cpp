#include "GridGeneratorFromHash.hpp"

GridGeneratorFromHash::GridGeneratorFromHash(GridSelfGenerated& grid) : GridInternalGenerator(grid), hash_length(grid.hash_length)
{
    hash = new char[hash_length];
}

GridGeneratorFromHash::~GridGeneratorFromHash()
{
    delete[] hash;
}

void GridGeneratorFromHash::Generate()
{
    SetHash((char*)"D22R82T000@100BQ1P00b800@[QHX20<3P024<P`@@9P@QH318B0`0d@282T8=80HP`0QR40K045:120");
    unsigned int current_field = 0;
    unsigned int current_not_mine_index = 0;
    bool is_mine;
    char current_symbol;

    grid.Clear();

    for(size_t i = 0; i < hash_length - 1; i++)
    {
        current_symbol = hash[i];
        current_symbol = current_symbol - 48;  // zero's ID in ASCII table
        if(i < hash_length - 2)
        {
            for(size_t j = 0; j < 6; j++)
            {
                is_mine = (current_symbol & 32);
                if(is_mine) grid.is_mine[current_field] = is_mine;
                else grid.not_mines[current_not_mine_index++] = current_field;
                current_field++;
                current_symbol = current_symbol << 1;
            }
        }
        else
        {
            unsigned char last_symbol_length = grid.S % 6;
            if(last_symbol_length == 0) last_symbol_length = 6;
            current_symbol = current_symbol << (6 - last_symbol_length);

            for(size_t j = 0; j < last_symbol_length; j++)
            {
                is_mine = (current_symbol & 32);
                if(is_mine) grid.is_mine[current_field] = is_mine;
                else grid.not_mines[current_not_mine_index++] = current_field;
                current_field++;
                current_symbol = current_symbol << 1;
            }
        }
    }

    std::strcpy(grid.hash, hash);
    grid.hash_up_to_date = true;
    grid.CalculateValues();
}

void GridGeneratorFromHash::SetHash(char* new_hash)
{
    strcpy(hash, new_hash);
}
