message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

set(CPP_SOURCES_TESTS_UTILS
    ${CMAKE_CURRENT_SOURCE_DIR}/TestsBigNum.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TestsCachedVector.cpp
    PARENT_SCOPE)