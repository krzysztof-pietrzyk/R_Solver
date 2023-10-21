message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

set(CPP_SOURCES_ALGORITHMS_ACTION
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmAction.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmFirstMove.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmGiveUp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmSimpleActions.cpp
    PARENT_SCOPE)
