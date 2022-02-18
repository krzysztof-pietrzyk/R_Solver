project(Utils)

set(CPP_SOURCES
    BitMask.cpp
    Buffer.cpp
    Buffer2D.cpp)

add_library(${PROJECT_NAME} ${CPP_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC .)