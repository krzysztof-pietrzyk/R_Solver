message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

set(CPP_SOURCES_GRID
    ${CMAKE_CURRENT_SOURCE_DIR}/Grid.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GridDimensions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GridHash.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GridInternal.cpp
    PARENT_SCOPE)
