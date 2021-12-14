set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES
    ./main.cpp
    ./Grid.cpp
    ./GridManager.cpp
    ./GridGeneratorFactory.cpp
    ./GridGenerator.cpp
    ./GridGeneratorUnsafe.cpp
    ./GridGeneratorFromHash.cpp
    ./GridViewFactory.cpp
    ./GridView.cpp
    ./GridViewConsole.cpp
    ./Algorithm.cpp
    ./AlgorithmFactory.cpp
    ./AlgorithmLayerOne.cpp
    ./AlgorithmSimpleCorners.cpp)

add_executable(${BINARY}_run ${SOURCES})
