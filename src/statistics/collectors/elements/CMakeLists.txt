message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

set(CPP_SOURCES_STATISTICS_COLLECTORS_ELEMENTS
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsElement.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsElementCounter.cpp
    PARENT_SCOPE)
