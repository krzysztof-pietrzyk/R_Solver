message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

set(CPP_SOURCES_GENERATORS
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorInternal.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorRandom.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorRandomGuaranteedOpening.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorRandomSafe.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorRandomUnsafe.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RandomNumberGenerator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GridGenerator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GridGeneratorFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GridGeneratorFromHash.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GridGeneratorUnsafe.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GridGeneratorSafe.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GridInternalGenerator.cpp
    PARENT_SCOPE)
