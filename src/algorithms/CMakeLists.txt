message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(analysis)
add_subdirectory(data_transfer_objects)
add_subdirectory(decision)

set(CPP_SOURCES_ALGORITHMS
    ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmExecutor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlgorithmTransitionManager.cpp
    ${CPP_SOURCES_ALGORITHMS_ANALYSIS}
    ${CPP_SOURCES_ALGORITHMS_DATA_TRANSFER_OBJECTS}
    ${CPP_SOURCES_ALGORITHMS_DECISION}
    PARENT_SCOPE)
