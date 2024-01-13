message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(state)

set(CPP_SOURCES_GRID
    ${CMAKE_CURRENT_SOURCE_DIR}/Grid.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GridDimensions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GridInternal.cpp
    ${CPP_SOURCES_GRID_STATE}
    PARENT_SCOPE)
