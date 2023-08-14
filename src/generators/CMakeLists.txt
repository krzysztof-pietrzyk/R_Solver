message("Entering directory ${CMAKE_CURRENT_SOURCE_DIR}")

set(CPP_SOURCES_GENERATORS
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorInternal.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorRandom.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorRandomGuaranteedOpening.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorRandomSafe.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorRandomUnsafe.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RandomNumberGenerator.cpp
    PARENT_SCOPE)
