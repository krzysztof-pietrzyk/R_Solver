project(View)

set(CPP_SOURCES
    GridView.cpp
    GridViewConsole.cpp
    GridViewFactory.cpp)

add_library(${PROJECT_NAME} ${CPP_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC .)
target_include_directories(${PROJECT_NAME} PRIVATE ../grid)

target_link_libraries(${PROJECT_NAME} PRIVATE Grid)