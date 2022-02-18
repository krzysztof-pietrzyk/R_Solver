project(Solver)

set(CPP_SOURCES
    Solver.cpp
    SolverThreadData.cpp)

add_library(${PROJECT_NAME} ${CPP_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC .)
target_include_directories(${PROJECT_NAME} PUBLIC ../algorithms)
target_include_directories(${PROJECT_NAME} PUBLIC ../view)
target_include_directories(${PROJECT_NAME} PUBLIC ../generators)
target_include_directories(${PROJECT_NAME} PUBLIC ../grid)

target_link_libraries(${PROJECT_NAME} PRIVATE Algorithms)
target_link_libraries(${PROJECT_NAME} PRIVATE View)
target_link_libraries(${PROJECT_NAME} PRIVATE Generators)
target_link_libraries(${PROJECT_NAME} PRIVATE Grid)