message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

set(CPP_SOURCES_ALGORITHMS_ANALYSIS
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmRefreshBorder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmRefreshSections.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmRefreshSegments.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmRefreshSubsegments.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmRefreshFace.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmRefreshCombinations.cpp
    PARENT_SCOPE)
