project(Grid)

set(CPP_SOURCES
    Grid.cpp
    GridManager.cpp
    GridSelfGenerated.cpp)

add_library(${PROJECT_NAME} ${CPP_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC .)