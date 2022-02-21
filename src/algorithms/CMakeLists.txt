message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

set(CPP_SOURCES_ALGORITHMS
    ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmDataStorage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmLayerOne.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmLayerTwo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmRefreshBorder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmRefreshFace.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmRefreshSections.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmSimpleCorners.cpp
    PARENT_SCOPE)
