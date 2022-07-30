message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

set(CPP_SOURCES_GRID
    ${CMAKE_CURRENT_SOURCE_DIR}/Grid.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GridManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GridSelfGenerated.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GridHash.cpp
    PARENT_SCOPE)
