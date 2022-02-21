message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(algorithms)
add_subdirectory(app)
add_subdirectory(generators)
add_subdirectory(grid)
add_subdirectory(solver)
add_subdirectory(utils)
add_subdirectory(view)

set(CPP_SOURCES_ALL
   ${CPP_SOURCES_ALGORITHMS}
   ${CPP_SOURCES_APP}
   ${CPP_SOURCES_GENERATORS}
   ${CPP_SOURCES_GRID}
   ${CPP_SOURCES_SOLVER}
   ${CPP_SOURCES_UTILS}
   ${CPP_SOURCES_VIEW})

add_executable(${PROJECT_NAME} ${CPP_SOURCES_ALL})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
