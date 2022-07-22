message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

set(CPP_SOURCES_METRICS
    ${CMAKE_CURRENT_SOURCE_DIR}/Metrics.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmMetrics.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmMetricsCollector.cpp
    PARENT_SCOPE)
