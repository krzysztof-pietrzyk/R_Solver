// ========================================================================= //
// ============================== ENVIRONMENT ============================== //
// ========================================================================= //

// UnitTest environment
#include "../UnitTestEnv.hpp"

// tested interface
#include "../../grid/GridHash.hpp"

// project includes
#include "../../utils/CachedVector.hpp"

// std includes


// ========================================================================= //
// ============================ MOCKED CLASSES ============================= //
// ========================================================================= //



// ========================================================================= //
// ============================= TEST FIXTURES ============================= //
// ========================================================================= //

class GridHashCreationFixture : public TestWithParam<uint32_t>
{
    // grid size
};

TEST_P(GridHashCreationFixture, Creation)
{
    const uint32_t grid_size = GetParam();
    const uint32_t fields_per_symbol = 6;
    uint32_t expectedHashLength = grid_size / fields_per_symbol;
    if(grid_size % fields_per_symbol != 0)
    {
        expectedHashLength += 1;
    }
    
    GridHash gridHash = GridHash(grid_size);
    ASSERT_EQ(gridHash.Length(), expectedHashLength);
}

INSTANTIATE_TEST_CASE_P(TestsGridHash, GridHashCreationFixture, Values(
    0, 1, 5, 6, 18, 81, 256, 480, 999999, 1000000
));

// ========================================================================= //
// ========================================================================= //
// ========================================================================= //

using CalculateHashFixtureParams = tuple<vector<bool>, string>;

class GridHashCalculateHashFixture : public TestWithParam<CalculateHashFixtureParams>
{
    // is_mine vector, expected hash
};

TEST_P(GridHashCalculateHashFixture, CalculateHash)
{
    const CalculateHashFixtureParams params = GetParam();
    const vector<bool> is_mine = get<0>(params);
    const string expected_hash = get<1>(params);

    const CachedVector mines_vector = CachedVector(is_mine);
    GridHash gridHash = GridHash(mines_vector);

    ASSERT_EQ(gridHash.ToString(), expected_hash);
}

vector<CalculateHashFixtureParams> GetParamsGridHashCalculateHashFixture();

INSTANTIATE_TEST_CASE_P(TestsGridHash, GridHashCalculateHashFixture, ValuesIn(GetParamsGridHashCalculateHashFixture()));

// ========================================================================= //
// ========================================================================= //
// ========================================================================= //

using CalculateHashFromMinesFixtureParams = tuple<vector<uint32_t>, uint32_t, vector<bool>>;

class GridHashCalculateHashFromMinesFixture : public TestWithParam<CalculateHashFromMinesFixtureParams>
{
    // mine_positions vector, grid_size, expected is_mine vector
};

TEST_P(GridHashCalculateHashFromMinesFixture, CalculateHashFromMines)
{
    const CalculateHashFromMinesFixtureParams params = GetParam();
    const vector<uint32_t> mine_positions = get<0>(params);
    const uint32_t grid_size = get<1>(params);
    const vector<bool> expected_is_mine = get<2>(params);

    GridHash gridHash = GridHash(CachedVector(mine_positions, grid_size));
    GridHash expectedGridHash = GridHash(expected_is_mine);
    
    ASSERT_TRUE(gridHash.ToString() == expectedGridHash.ToString());
}

vector<CalculateHashFromMinesFixtureParams> GetParamsGridHashCalculateHashFromMinesFixture();

INSTANTIATE_TEST_CASE_P(TestsGridHash, GridHashCalculateHashFromMinesFixture, ValuesIn(GetParamsGridHashCalculateHashFromMinesFixture()));

// ========================================================================= //
// ========================================================================= //
// ========================================================================= //

using GetMinesFixtureParams = tuple<string, uint32_t, CachedVector>;

class GridHashGetMinesFixture : public TestWithParam<GetMinesFixtureParams>
{
    // input_hash, input_hash_length, expected_mine_positions
};

TEST_P(GridHashGetMinesFixture, GetMines)
{
    const GetMinesFixtureParams params = GetParam();
    const string input_hash = get<0>(params);
    const uint32_t input_hash_length = get<1>(params);
    const CachedVector& expected_mine_positions = get<2>(params);

    GridHash gridHash = GridHash(input_hash, input_hash_length);

    const CachedVector& observed_mine_positions = gridHash.GetMinePositions();

    ASSERT_TRUE(observed_mine_positions == expected_mine_positions);
}

vector<GetMinesFixtureParams> GetParamsGridHashGetMinesFixture();

INSTANTIATE_TEST_CASE_P(TestsGridHash, GridHashGetMinesFixture, ValuesIn(GetParamsGridHashGetMinesFixture()));

// ========================================================================= //
// ============================== TEST CASES =============================== //
// ========================================================================= //



// ========================================================================= //
// =========================== TEST DATA SOURCES =========================== //
// ========================================================================= //

const std::vector<char> hash_symbols =
{
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    ':', ';', '<', '=', '>', '?', '@', 'A', 'B', 'C', 
    'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 
    'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`', 'a', 
    'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 
    'l', 'm', 'n', 'o'
};

vector<CalculateHashFixtureParams> GetParamsGridHashCalculateHashFixture()
{
    vector<CalculateHashFixtureParams> allHashSymbolsParams = vector<CalculateHashFixtureParams>();

    for(char temp_value = 0; temp_value < hash_symbols.size(); ++temp_value)
    {
        allHashSymbolsParams.push_back(CalculateHashFixtureParams(
            {
                bool(temp_value & 32),
                bool(temp_value & 16),
                bool(temp_value & 8),
                bool(temp_value & 4),
                bool(temp_value & 2),
                bool(temp_value & 1)
            }, string(1, hash_symbols[temp_value])));
    }

    allHashSymbolsParams.push_back(CalculateHashFixtureParams(
        vector<bool>(81, false), "00000000000000"));

    allHashSymbolsParams.push_back(CalculateHashFixtureParams(
        vector<bool>(81, true), "ooooooooooooo7"));

    allHashSymbolsParams.push_back(CalculateHashFixtureParams(
        {0, 1, 0, 0, 0, 0, 1, 1, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 1, 0, 0, 0,
         1, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 1, 0, 0, 0, 0, 0,
         0, 0, 0, 1, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 1, 0, 0, 0,
         0, 1, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 0},
        "@`014040P12002"));

    allHashSymbolsParams.push_back(CalculateHashFixtureParams(
        {0, 0, 0, 0, 0, 1,  0, 0, 0, 0, 1, 0,
         0, 0, 0, 0, 1, 1,  0, 0, 0, 1, 0, 0,
         0, 0, 0, 1, 0, 1,  0, 0, 0, 1, 1, 0,
         0, 0, 0, 1, 1, 1,  0, 0, 1, 0, 0, 0,
         0, 0, 1, 0, 0, 1,  0, 1, 0, 0, 0, 0,
         1, 0, 0, 0, 0, 0},
        "123456789@P"));

    allHashSymbolsParams.push_back(CalculateHashFixtureParams({0, 0, 0, 0, 0, 1}, "1"));
    allHashSymbolsParams.push_back(CalculateHashFixtureParams({0, 0, 0, 0, 0, 1, 1}, "11"));
    allHashSymbolsParams.push_back(CalculateHashFixtureParams({0, 0, 0, 0, 0, 1, 1, 0}, "12"));
    allHashSymbolsParams.push_back(CalculateHashFixtureParams({0, 0, 0, 0, 0, 1, 1, 0, 0}, "14"));
    allHashSymbolsParams.push_back(CalculateHashFixtureParams({0, 0, 0, 0, 0, 1, 1, 0, 0, 0}, "18"));
    allHashSymbolsParams.push_back(CalculateHashFixtureParams({0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}, "1@"));
    allHashSymbolsParams.push_back(CalculateHashFixtureParams({0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0}, "1P"));
    allHashSymbolsParams.push_back(CalculateHashFixtureParams({0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0}, "1P0"));

    return allHashSymbolsParams;
}

vector<CalculateHashFromMinesFixtureParams> GetParamsGridHashCalculateHashFromMinesFixture()
{
    vector<CalculateHashFromMinesFixtureParams> minePositionsParams = vector<CalculateHashFromMinesFixtureParams>();

    minePositionsParams.push_back(CalculateHashFromMinesFixtureParams({    }, 6,  {0, 0, 0, 0, 0, 0}));
    minePositionsParams.push_back(CalculateHashFromMinesFixtureParams({0   }, 6,  {1, 0, 0, 0, 0, 0}));
    minePositionsParams.push_back(CalculateHashFromMinesFixtureParams({1   }, 6,  {0, 1, 0, 0, 0, 0}));
    minePositionsParams.push_back(CalculateHashFromMinesFixtureParams({2   }, 6,  {0, 0, 1, 0, 0, 0}));
    minePositionsParams.push_back(CalculateHashFromMinesFixtureParams({3   }, 6,  {0, 0, 0, 1, 0, 0}));
    minePositionsParams.push_back(CalculateHashFromMinesFixtureParams({4   }, 6,  {0, 0, 0, 0, 1, 0}));
    minePositionsParams.push_back(CalculateHashFromMinesFixtureParams({5   }, 6,  {0, 0, 0, 0, 0, 1}));
    minePositionsParams.push_back(CalculateHashFromMinesFixtureParams({5, 6}, 7,  {0, 0, 0, 0, 0, 1, 1}));
    minePositionsParams.push_back(CalculateHashFromMinesFixtureParams({5, 6}, 8,  {0, 0, 0, 0, 0, 1, 1, 0}));
    minePositionsParams.push_back(CalculateHashFromMinesFixtureParams({5, 6}, 9,  {0, 0, 0, 0, 0, 1, 1, 0, 0}));
    minePositionsParams.push_back(CalculateHashFromMinesFixtureParams({5, 6}, 10, {0, 0, 0, 0, 0, 1, 1, 0, 0, 0}));
    minePositionsParams.push_back(CalculateHashFromMinesFixtureParams({5, 6}, 11, {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}));
    minePositionsParams.push_back(CalculateHashFromMinesFixtureParams({5, 6}, 12, {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0}));
    minePositionsParams.push_back(CalculateHashFromMinesFixtureParams({5, 6}, 13, {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0}));

    minePositionsParams.push_back(CalculateHashFromMinesFixtureParams(
        {}, 81, vector<bool>(81, false)
    ));

    minePositionsParams.push_back(CalculateHashFromMinesFixtureParams(
        {0, 1, 2, 3, 4, 5, 6, 7, 8,
         9, 10, 11, 12, 13, 14, 15, 16, 17,
         18, 19, 20, 21, 22, 23, 24, 25, 26,
         27, 28, 29, 30, 31, 32, 33, 34, 35,
         36, 37, 38, 39, 40, 41, 42, 43, 44,
         45, 46, 47, 48, 49, 50, 51, 52, 53,
         54, 55, 56, 57, 58, 59, 60, 61, 62,
         63, 64, 65, 66, 67, 68, 69, 70, 71,
         72, 73, 74, 75, 76, 77, 78, 79, 80}, 
        81, 
        vector<bool>(81, true)
    ));

    minePositionsParams.push_back(CalculateHashFromMinesFixtureParams(
        {1, 6, 7, 23, 27, 39, 48, 59, 64, 79},
        81, 
        {0, 1, 0, 0, 0, 0, 1, 1, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 1, 0, 0, 0,
         1, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 1, 0, 0, 0, 0, 0,
         0, 0, 0, 1, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 1, 0, 0, 0,
         0, 1, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 0}
    ));

    minePositionsParams.push_back(CalculateHashFromMinesFixtureParams(
        {5, 10, 16, 17, 21, 27, 29, 33, 34, 39, 40, 41, 44, 50, 53, 55, 60},
        66,
        {0, 0, 0, 0, 0, 1,  0, 0, 0, 0, 1, 0,
         0, 0, 0, 0, 1, 1,  0, 0, 0, 1, 0, 0,
         0, 0, 0, 1, 0, 1,  0, 0, 0, 1, 1, 0,
         0, 0, 0, 1, 1, 1,  0, 0, 1, 0, 0, 0,
         0, 0, 1, 0, 0, 1,  0, 1, 0, 0, 0, 0,
         1, 0, 0, 0, 0, 0}
    ));

    return minePositionsParams;
}

vector<GetMinesFixtureParams> GetParamsGridHashGetMinesFixture()
{
    vector<GetMinesFixtureParams> hashToMinesParams = vector<GetMinesFixtureParams>();

    for(char temp_value = 0; temp_value < hash_symbols.size(); ++temp_value)
    {
        hashToMinesParams.push_back(GetMinesFixtureParams(
            string(1, hash_symbols[temp_value]), 6,
            CachedVector({
                bool(temp_value & 32),
                bool(temp_value & 16),
                bool(temp_value & 8),
                bool(temp_value & 4),
                bool(temp_value & 2),
                bool(temp_value & 1)
            })
        ));
    }

    hashToMinesParams.push_back(GetMinesFixtureParams(
        "00000000000000", 81,
        vector<bool>(81, false)
    ));

    hashToMinesParams.push_back(GetMinesFixtureParams(
        "ooooooooooooo7", 81,
        vector<bool>(81, true)
    ));

    hashToMinesParams.push_back(GetMinesFixtureParams(
        "@`014040P12002", 81,
        CachedVector(
        {0, 1, 0, 0, 0, 0, 1, 1, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 1, 0, 0, 0,
         1, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 1, 0, 0, 0, 0, 0,
         0, 0, 0, 1, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 1, 0, 0, 0,
         0, 1, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 0})
    ));

    hashToMinesParams.push_back(GetMinesFixtureParams(
        "123456789@P", 66,
        CachedVector(
        {0, 0, 0, 0, 0, 1,  0, 0, 0, 0, 1, 0,
         0, 0, 0, 0, 1, 1,  0, 0, 0, 1, 0, 0,
         0, 0, 0, 1, 0, 1,  0, 0, 0, 1, 1, 0,
         0, 0, 0, 1, 1, 1,  0, 0, 1, 0, 0, 0,
         0, 0, 1, 0, 0, 1,  0, 1, 0, 0, 0, 0,
         1, 0, 0, 0, 0, 0})
    ));

    return hashToMinesParams;
}
