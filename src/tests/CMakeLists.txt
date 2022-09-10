message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(grid)

set(CPP_SOURCES_TESTS
    ${CPP_SOURCES_TESTS_GRID}
    ${CMAKE_CURRENT_SOURCE_DIR}/UnitTestRunner.cpp
    PARENT_SCOPE)
