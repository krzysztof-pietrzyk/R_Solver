project(R_Solver)

set(CPP_SOURCES
    main.cpp)

add_executable(${PROJECT_NAME} ${CPP_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Solver)