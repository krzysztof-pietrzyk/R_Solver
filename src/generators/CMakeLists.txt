project(Generators)

set(CPP_SOURCES
    GridGenerator.cpp
    GridGeneratorFactory.cpp
    GridGeneratorFromHash.cpp
    GridGeneratorUnsafe.cpp
    GridInternalGenerator.cpp)

add_library(${PROJECT_NAME} ${CPP_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC .)
target_include_directories(${PROJECT_NAME} PRIVATE ../grid)

target_link_libraries(${PROJECT_NAME} PRIVATE Grid)