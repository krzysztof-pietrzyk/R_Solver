message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

set(CPP_SOURCES_UTILS 
    ${CMAKE_CURRENT_SOURCE_DIR}/BigNum.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CachedVector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Logger.cpp
    PARENT_SCOPE)
