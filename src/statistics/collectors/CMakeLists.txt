message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

set(CPP_SOURCES_STATISTICS_COLLECTORS
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsCollector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsCollectorClicks.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsCollectorSolver.cpp
    PARENT_SCOPE)
