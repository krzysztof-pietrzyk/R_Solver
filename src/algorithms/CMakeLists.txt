message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(decision)
add_subdirectory(analysis)

set(CPP_SOURCES_ALGORITHMS
    ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmDataTransfer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmExecutor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmTransitionManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Section.cpp
    ${CPP_SOURCES_ALGORITHMS_DECISION}
    ${CPP_SOURCES_ALGORITHMS_ANALYSIS}
    PARENT_SCOPE)
