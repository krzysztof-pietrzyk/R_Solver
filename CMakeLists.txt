cmake_minimum_required(VERSION 3.1)

project(R_Solver LANGUAGES CXX)

# Command for creating makefiles
# E:\Projects\R_Solver\build>cmake .. -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles"

message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
   message("CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
   message("CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
endif()

#get googletest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG release-1.12.1
)
FetchContent_GetProperties(googletest)
#googletest_POPULATED
#googletest_SOURCE_DIR
#googletest_BUILD_DIR

if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BUILD_DIR})
endif()

message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(src)

set(SOLVER_LIB_NAME ${PROJECT_NAME}_Logic)
set(SOLVER_EXE_NAME ${PROJECT_NAME})
set(UNIT_TEST_RUNNER_NAME ${PROJECT_NAME}_UnitTests)

add_custom_target(UnitTests)
add_dependencies(UnitTests ${UNIT_TEST_RUNNER_NAME})

add_custom_target(App)
add_dependencies(App ${SOLVER_EXE_NAME})

add_library(${SOLVER_LIB_NAME} STATIC ${CPP_SOURCES_LOGIC})

add_executable(${SOLVER_EXE_NAME} ${CPP_SOURCES_APP})
target_link_libraries(${SOLVER_EXE_NAME} ${SOLVER_LIB_NAME})

add_executable(${UNIT_TEST_RUNNER_NAME} ${CPP_SOURCES_TESTS})
target_link_libraries(${UNIT_TEST_RUNNER_NAME} ${SOLVER_LIB_NAME} gtest_main gmock_main)
