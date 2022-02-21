message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

set(CPP_SOURCES_SOLVER 
    ${CMAKE_CURRENT_SOURCE_DIR}/Solver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SolverThreadData.cpp
    PARENT_SCOPE)
