message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(grid)
add_subdirectory(utils)

set(CPP_SOURCES_TESTS
    ${CPP_SOURCES_TESTS_GRID}
    ${CPP_SOURCES_TESTS_UTILS}
    ${CMAKE_CURRENT_SOURCE_DIR}/UnitTestRunner.cpp
    PARENT_SCOPE)
