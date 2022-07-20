message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(action)
add_subdirectory(analysis)

set(CPP_SOURCES_ALGORITHMS
    ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmDataStorage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmManager.cpp
    ${CPP_SOURCES_ALGORITHMS_ACTION}
    ${CPP_SOURCES_ALGORITHMS_ANALYSIS}
    PARENT_SCOPE)
