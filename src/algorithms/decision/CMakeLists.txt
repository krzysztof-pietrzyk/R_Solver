message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

set(CPP_SOURCES_ALGORITHMS_DECISION
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmCombinationsLeastRisky.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmCombinationsSafeMoves.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmDecision.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmLayerOne.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmLayerTwo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmSimpleCorners.cpp
    PARENT_SCOPE)
