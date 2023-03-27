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

    MockGridManager(uint16_t w, uint16_t h, uint32_t m) : GridManager(w, h, m) {};

    MOCK_METHOD(bool, CheckVisible, (uint32_t), (override));
    MOCK_METHOD(bool, LeftClick, (uint32_t), (override));
    MOCK_METHOD(bool, RightClick, (uint32_t), (override));
};

// ========================================================================= //
// ============================= TEST FIXTURES ============================= //
// ========================================================================= //



// ========================================================================= //
// ============================== TEST CASES =============================== //
// ========================================================================= //

TEST(TestGridManager, FieldValueVisible)
{
    const uint16_t width = 3, height = 3;
    const uint32_t mines_number = 3, input_field = 3;
    const bool is_visible = true;

    MockGridManager gridManager(width, height, mines_number);

    EXPECT_CALL(gridManager, CheckVisible(input_field)).WillOnce(Return(is_visible));

    EXPECT_NO_THROW(gridManager.FieldValue(input_field));
}

TEST(TestGridManager, FieldValueInvisible)
{
    const uint16_t width = 3, height = 3;
    const uint32_t mines_number = 3, input_field = 3;
    const bool is_visible = false;

    MockGridManager gridManager(width, height, mines_number);

    EXPECT_CALL(gridManager, CheckVisible(input_field)).WillOnce(Return(is_visible));

    EXPECT_THROW(gridManager.FieldValue(input_field), std::invalid_argument);
}

// ========================================================================= //
// =========================== TEST DATA SOURCES =========================== //
// ========================================================================= //
