set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES
    ./main.cpp
    ./Grid.cpp
    ./GridSelfGenerated.cpp
    ./GridManager.cpp
    ./GridGeneratorFactory.cpp
    ./GridGenerator.cpp
    ./GridInternalGenerator.cpp
    ./GridGeneratorUnsafe.cpp
    ./GridGeneratorFromHash.cpp
    ./GridViewFactory.cpp
    ./GridView.cpp
    ./GridViewConsole.cpp
    ./Algorithm.cpp
    ./AlgorithmDataStorage.cpp
    ./AlgorithmFactory.cpp
    ./AlgorithmManager.cpp
    ./AlgorithmRefreshBorder.cpp
    ./AlgorithmRefreshFace.cpp
    ./AlgorithmLayerOne.cpp
    ./AlgorithmSimpleCorners.cpp)

add_executable(${BINARY}_run ${SOURCES})
