message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(types)

set(CPP_SOURCES_STATISTICS 
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsCollector.cpp
    ${CPP_SOURCES_STATISTICS_TYPES}
    PARENT_SCOPE)
