message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

set(CPP_SOURCES_ALGORITHMS_ACTION
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmAction.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmLayerOne.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmLayerTwo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmSimpleCorners.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmSureMovesFromCombinations.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmSafestMoveFromCombinations.cpp
    PARENT_SCOPE)
