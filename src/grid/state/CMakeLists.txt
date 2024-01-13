message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

set(CPP_SOURCES_GRID_STATE
    ${CMAKE_CURRENT_SOURCE_DIR}/GridHash.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GridHashSymbols.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GridState.cpp
    PARENT_SCOPE)
