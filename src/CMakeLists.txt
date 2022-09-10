message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(algorithms)
add_subdirectory(app)
add_subdirectory(generators)
add_subdirectory(grid)
add_subdirectory(solver)
add_subdirectory(tests)
add_subdirectory(utils)
add_subdirectory(view)

set(CPP_SOURCES_LOGIC
   ${CPP_SOURCES_ALGORITHMS}
   ${CPP_SOURCES_GENERATORS}
   ${CPP_SOURCES_GRID}
   ${CPP_SOURCES_SOLVER}
   ${CPP_SOURCES_UTILS}
   ${CPP_SOURCES_VIEW}
   PARENT_SCOPE)

set(CPP_SOURCES_APP ${CPP_SOURCES_APP} PARENT_SCOPE)
set(CPP_SOURCES_TESTS ${CPP_SOURCES_TESTS} PARENT_SCOPE)
