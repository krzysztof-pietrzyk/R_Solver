message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

set(CPP_SOURCES_ALGORITHMS_ANALYSIS
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmBorder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmSections.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmSegments.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmSubsegments.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmFace.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmCombinations.cpp
    PARENT_SCOPE)
