message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

set(CPP_SOURCES_TESTS_GRID
    ${CMAKE_CURRENT_SOURCE_DIR}/TestsGrid.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TestsGridHash.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TestsGridManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TestsGridSelfGenerated.cpp
    PARENT_SCOPE)