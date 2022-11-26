// ========================================================================= //
// ============================== ENVIRONMENT ============================== //
// ========================================================================= //

// UnitTest environment
#include "../UnitTestEnv.hpp"

// Other libraries

// Tested interface
#include "../../grid/Grid.hpp"

// ========================================================================= //
// ============================ MOCKED CLASSES ============================= //
// ========================================================================= //

class MockGrid : public Grid
{
    public:

    MockGrid(unsigned short int w, unsigned short int h, unsigned int m) : Grid(w, h, m) {}

    MOCK_METHOD(void, LeftClick, (unsigned int), (override));
    MOCK_METHOD(void, RightClick, (unsigned int), (override));
};

// ========================================================================= //
// ============================= TEST FIXTURES ============================= //
// ========================================================================= //

using CreationFixtureParams = tuple<unsigned short, unsigned short, unsigned int, bool>;

class GridCreationFixture : public TestWithParam<CreationFixtureParams>
{
    // width, height, mines_num, isExpectedThrow
};

TEST_P(GridCreationFixture, Creation)
{
    CreationFixtureParams test_params = GetParam();
    const unsigned short width = get<0>(test_params);
    const unsigned short height = get<1>(test_params);
    const unsigned int mines_num = get<2>(test_params);
    const bool isExpectedThorw = get<3>(test_params);

    if(isExpectedThorw)
    {
        ASSERT_THROW(MockGrid grid(width, height, mines_num), std::invalid_argument);
    }
    else
    {
        ASSERT_NO_THROW(MockGrid grid(width, height, mines_num));
    }
}

INSTANTIATE_TEST_CASE_P(TestsGrid, GridCreationFixture, Values(
    CreationFixtureParams(1, 1, 1, true),
    CreationFixtureParams(1, 1, 0, true),
    CreationFixtureParams(3, 0, 1, true),
    CreationFixtureParams(0, 3, 1, true),
    CreationFixtureParams(3, 3, 0, true),
    CreationFixtureParams(3, 3, 9, true),
    CreationFixtureParams(3, 3, 10, true),
    CreationFixtureParams(3, 3, 8, false),
    CreationFixtureParams(9, 9, 10, false),
    CreationFixtureParams(16, 16, 40, false),
    CreationFixtureParams(30, 16, 99, false),
    CreationFixtureParams(80, 80, 999, false),
    CreationFixtureParams(1024, 3, 100, false),
    CreationFixtureParams(1025, 3, 100, true),
    CreationFixtureParams(3, 1024, 100, false),
    CreationFixtureParams(3, 1025, 100, true)
));

// ========================================================================= //
// ============================== TEST CASES =============================== //
// ========================================================================= //

TEST(TestsGrid, FindNeighbors3x3)
{
    const unsigned short width = 3, height = 3;
    const unsigned int mines_num = 3;
    MockGrid grid(width, height, mines_num);

    ASSERT_THAT(grid.neighbors, ElementsAre(
        ElementsAre(1, 3, 4),
        ElementsAre(0, 2, 3, 4, 5),
        ElementsAre(1, 4, 5),
        ElementsAre(0, 1, 4, 6, 7),
        ElementsAre(0, 1, 2, 3, 5, 6, 7, 8),
        ElementsAre(1, 2, 4, 7, 8),
        ElementsAre(3, 4, 7),
        ElementsAre(3, 4, 5, 6, 8),
        ElementsAre(4, 5, 7)
    ));
}

TEST(TestsGrid, FindNeighbors1x3)
{
    const unsigned short width = 1, height = 3;
    const unsigned int mines_num = 1;
    MockGrid grid(width, height, mines_num);

    ASSERT_THAT(grid.neighbors, ElementsAre(
        ElementsAre(1),
        ElementsAre(0, 2),
        ElementsAre(1)
    ));
}

TEST(TestsGrid, FindNeighbors3x1)
{
    const unsigned short width = 3, height = 1;
    const unsigned int mines_num = 1;
    MockGrid grid(width, height, mines_num);

    ASSERT_THAT(grid.neighbors, ElementsAre(
        ElementsAre(1),
        ElementsAre(0, 2),
        ElementsAre(1)
    ));
}

TEST(TestsGrid, FindNeighbors2x2)
{
    const unsigned short width = 2, height = 2;
    const unsigned int mines_num = 1;
    MockGrid grid(width, height, mines_num);

    ASSERT_THAT(grid.neighbors, ElementsAre(
        ElementsAre(1, 2, 3),
        ElementsAre(0, 2, 3),
        ElementsAre(0, 1, 3),
        ElementsAre(0, 1, 2)
    ));
}

// ========================================================================= //
// =========================== TEST DATA SOURCES =========================== //
// ========================================================================= //
