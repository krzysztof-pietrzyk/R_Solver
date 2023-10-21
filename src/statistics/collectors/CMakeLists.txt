message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(elements)

set(CPP_SOURCES_STATISTICS_COLLECTORS
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsCollector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsCollectorActionsLoss.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsCollectorClicks.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsCollectorDecisions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsCollectorSolver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsCollectorExecutions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsCollectorFieldTypes.cpp
    ${CPP_SOURCES_STATISTICS_COLLECTORS_ELEMENTS}
    PARENT_SCOPE)
