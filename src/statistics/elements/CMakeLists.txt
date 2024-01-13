message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

set(CPP_SOURCES_STATISTICS_ELEMENTS
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsElementAverage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsElementCounter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsElementMax.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsElementMin.cpp
    PARENT_SCOPE)
