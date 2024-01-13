message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

set(CPP_SOURCES_GENERATORS
    ${CMAKE_CURRENT_SOURCE_DIR}/Generator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorExternal.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorInternal.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorLoadState.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorRandom.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorRandomGuaranteedOpening.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorRandomSafe.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorRandomUnsafe.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RandomNumberGenerator.cpp
    PARENT_SCOPE)
