message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(elements)

set(CPP_SOURCES_STATISTICS 
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsAggregator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsCollector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsProducer.cpp
    ${CPP_SOURCES_STATISTICS_ELEMENTS}
    PARENT_SCOPE)
