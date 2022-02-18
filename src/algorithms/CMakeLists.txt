project(Algorithms)

set(CPP_SOURCES
    Algorithm.cpp
    AlgorithmDataStorage.cpp
    AlgorithmFactory.cpp
    AlgorithmLayerOne.cpp
    AlgorithmLayerTwo.cpp
    AlgorithmManager.cpp
    AlgorithmRefreshBorder.cpp
    AlgorithmRefreshFace.cpp
    AlgorithmRefreshSections.cpp
    AlgorithmSimpleCorners.cpp)

add_library(${PROJECT_NAME} ${CPP_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC .)
target_include_directories(${PROJECT_NAME} PRIVATE ../grid)

target_link_libraries(${PROJECT_NAME} PRIVATE Grid)