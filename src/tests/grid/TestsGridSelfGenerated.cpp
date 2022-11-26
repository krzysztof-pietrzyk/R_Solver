// ========================================================================= //
// ============================== ENVIRONMENT ============================== //
// ========================================================================= //

// UnitTest environment
#include "../UnitTestEnv.hpp"

// Other libraries

// Tested interface
#include "../../grid/GridSelfGenerated.hpp"

// ========================================================================= //
// ============================ MOCKED CLASSES ============================= //
// ========================================================================= //

class MockGridSelfGenerated : public GridSelfGenerated
{
    public:

    MockGridSelfGenerated(uint16_t w, uint16_t h, uint32_t m) : GridSelfGenerated(w, h, m) {}

    vector<uint8_t> GetAllFieldValues()
    {
        return field_values;
    }

    void FindNotMines()
    {
        size_t not_mines_index = 0;
        for(size_t i = 0; i < is_mine.size(); i++)
        {
            if(!is_mine[i])
            {
                if(not_mines_index == not_mines.size()) { throw std::runtime_error("Wrong testing data!"); }
                not_mines[not_mines_index++] = i;
            }
        }
    }
};

// ========================================================================= //
// ============================= TEST FIXTURES ============================= //
// ========================================================================= //

using CalculateValuesFixtureParams = tuple<vector<bool>, vector<uint8_t>, uint16_t, uint16_t, uint32_t>;

class GridSelfGeneratedCalculateValuesFixture : public TestWithParam<CalculateValuesFixtureParams>
{
    // input_is_mine, expected_field_values
};

TEST_P(GridSelfGeneratedCalculateValuesFixture, CalculateValues)
{
    const CalculateValuesFixtureParams params = GetParam();
    const vector<bool> input_is_mine = get<0>(params);
    const vector<uint8_t> expected_field_values = get<1>(params);
    const uint16_t input_width = get<2>(params);
    const uint16_t input_height = get<3>(params);
    const uint32_t input_mines_num = get<4>(params);

    MockGridSelfGenerated grid(input_width, input_height, input_mines_num);

    grid.is_mine.assign(input_is_mine.begin(), input_is_mine.end());
    grid.FindNotMines();

    grid.CalculateValues();

    ASSERT_THAT(grid.GetAllFieldValues(), ElementsAreArray(expected_field_values));
}

vector<CalculateValuesFixtureParams> GetCalculateValuesFixtureParams();

INSTANTIATE_TEST_CASE_P(TestsGridSelfGenerated, GridSelfGeneratedCalculateValuesFixture, ValuesIn(GetCalculateValuesFixtureParams()));

// ========================================================================= //
// ============================== TEST CASES =============================== //
// ========================================================================= //



// ========================================================================= //
// =========================== TEST DATA SOURCES =========================== //
// ========================================================================= //

vector<CalculateValuesFixtureParams> GetCalculateValuesFixtureParams()
{
    vector<CalculateValuesFixtureParams> params = vector<CalculateValuesFixtureParams>();
    params.push_back(CalculateValuesFixtureParams({1, 0}, {0, 1}, 2, 1, 1));
    params.push_back(CalculateValuesFixtureParams({1, 0, 1, 0}, {0, 2, 0, 1}, 4, 1, 2));
    params.push_back(CalculateValuesFixtureParams({1, 1, 0, 0, 0, 0, 1, 0, 0}, {0, 0, 1, 3, 3, 1, 0, 1, 0}, 3, 3, 3));
    params.push_back(CalculateValuesFixtureParams(
        {0, 0, 0, 0, 0, 0, 0, 0, 1,
         0, 1, 0, 0, 0, 0, 0, 0, 1,
         0, 1, 0, 1, 0, 0, 0, 0, 0,
         0, 0, 0, 1, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 1, 0, 0, 1, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 1,
         0, 0, 0, 0, 0, 0, 1, 0, 0},
        {1, 1, 1, 0, 0, 0, 0, 2, 0,
         2, 0, 3, 1, 1, 0, 0, 2, 0,
         2, 0, 4, 0, 2, 0, 0, 1, 1,
         1, 1, 3, 0, 2, 0, 0, 0, 0,
         0, 0, 1, 1, 1, 0, 0, 0, 0,
         0, 0, 1, 1, 1, 1, 1, 1, 0,
         0, 0, 1, 0, 1, 1, 0, 2, 1,
         0, 0, 1, 1, 1, 2, 2, 3, 0,
         0, 0, 0, 0, 0, 1, 0, 2, 1},
        9, 9, 10));
    params.push_back(CalculateValuesFixtureParams(
        {1, 1, 1, 1, 1, 0, 0, 0, 0,
         1, 0, 1, 0, 1, 0, 0, 0, 0,
         1, 1, 1, 0, 1, 0, 0, 0, 0,
         0, 0, 1, 0, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 0, 0,
         0, 8, 0, 7, 0, 3, 0, 0, 0,
         0, 0, 0, 6, 0, 3, 0, 0, 0,
         2, 4, 0, 5, 0, 3, 0, 0, 0,
         0, 1, 1, 4, 0, 3, 0, 0, 0,
         0, 0, 0, 3, 0, 3, 0, 0, 0,
         0, 0, 0, 2, 0, 2, 0, 0, 0,
         0, 0, 0, 1, 1, 1, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0},
        9, 9, 17));
    params.push_back(CalculateValuesFixtureParams(
        {1, 1, 1, 1, 1, 0, 1, 0, 1,
         1, 0, 1, 0, 1, 0, 1, 1, 1,
         1, 1, 1, 0, 1, 0, 0, 0, 0,
         0, 0, 1, 0, 1, 0, 1, 1, 1,
         0, 0, 0, 0, 1, 0, 1, 1, 1,
         0, 0, 0, 0, 1, 0, 1, 1, 1,
         0, 0, 0, 0, 1, 0, 0, 0, 0,
         1, 1, 0, 0, 0, 0, 0, 1, 1,
         0, 1, 0, 0, 0, 0, 0, 1, 1},
        {0, 0, 0, 0, 0, 4, 0, 5, 0,
         0, 8, 0, 7, 0, 5, 0, 0, 0,
         0, 0, 0, 6, 0, 5, 4, 6, 4,
         2, 4, 0, 5, 0, 5, 0, 0, 0,
         0, 1, 1, 4, 0, 6, 0, 0, 0,
         0, 0, 0, 3, 0, 5, 0, 0, 0,
         2, 2, 1, 2, 0, 3, 3, 5, 4,
         0, 0, 2, 1, 1, 1, 2, 0, 0,
         3, 0, 2, 0, 0, 0, 2, 0, 0},
        9, 9, 38));
    return params;
}
