message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

set(CPP_SOURCES_ALGORITHMS_ACTION
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmAction.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmLayerOne.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmLayerTwo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmSimpleCorners.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmCombinationsSafeMoves.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmCombinationsLeastRisky.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmGiveUp.cpp
    PARENT_SCOPE)
