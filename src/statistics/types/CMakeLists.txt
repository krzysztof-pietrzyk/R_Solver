message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

set(CPP_SOURCES_STATISTICS_TYPES
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsType.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsTypeClicks.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsTypeSolver.cpp
    PARENT_SCOPE)
