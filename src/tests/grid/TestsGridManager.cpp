// ========================================================================= //
// ============================== ENVIRONMENT ============================== //
// ========================================================================= //

// UnitTest environment
#include "../UnitTestEnv.hpp"

// Other libraries

// Tested interface
#include "../../grid/GridManager.hpp"

// ========================================================================= //
// ============================ MOCKED CLASSES ============================= //
// ========================================================================= //

class MockGridManager : public GridManager
{
    public:

    MockGridManager(unsigned short int w, unsigned short int h, unsigned int m) : GridManager(w, h, m) {};

    MOCK_METHOD(bool, CheckVisible, (unsigned int), (override));
    MOCK_METHOD(void, LeftClick, (unsigned int), (override));
    MOCK_METHOD(void, RightClick, (unsigned int), (override));
};

// ========================================================================= //
// ============================= TEST FIXTURES ============================= //
// ========================================================================= //



// ========================================================================= //
// ============================== TEST CASES =============================== //
// ========================================================================= //

TEST(TestGridManager, FieldValueVisible)
{
    const unsigned short int width = 3, height = 3;
    const unsigned int mines_number = 3, input_field = 3;
    const bool is_visible = true;

    MockGridManager gridManager(width, height, mines_number);

    EXPECT_CALL(gridManager, CheckVisible(input_field)).WillOnce(Return(is_visible));

    EXPECT_NO_THROW(gridManager.FieldValue(input_field));
}

TEST(TestGridManager, FieldValueInvisible)
{
    const unsigned short int width = 3, height = 3;
    const unsigned int mines_number = 3, input_field = 3;
    const bool is_visible = false;

    MockGridManager gridManager(width, height, mines_number);

    EXPECT_CALL(gridManager, CheckVisible(input_field)).WillOnce(Return(is_visible));

    EXPECT_THROW(gridManager.FieldValue(input_field), std::invalid_argument);
}

// ========================================================================= //
// =========================== TEST DATA SOURCES =========================== //
// ========================================================================= //
