# cmake/modules/TestExceptions.cmake
#

  MESSAGE(STATUS "Check for exceptions enabled")
  TRY_COMPILE(CMAKE_TEST_EXCEPTIONS_ENABLED
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/TestExceptions.cpp
    OUTPUT_VARIABLE OUTPUT)
  IF (CMAKE_TEST_EXCEPTIONS_ENABLED)
    MESSAGE(STATUS "Check for EXCEPTIONS ENABLED  - ENABLED")
    SET (EXCEPTIONS_ENABLED ON)
      FILE(APPEND ${CMAKE_BINARY_DIR}/CMakeFiles/CMakeOutput.log
      "Determining if exceptions are enabled with "
      "the following output:\n${OUTPUT}\n\n")
  ELSE (CMAKE_TEST_EXCEPTIONS_ENABLED)
    MESSAGE(STATUS "Check for siEXCEPTIONS ENABLED  - DISABLED")
  ENDIF (CMAKE_TEST_EXCEPTIONS_ENABLED)

IF(EXCEPTIONS_ENABLED)
file(APPEND ${CMAKE_CURRENT_SOURCE_DIR}/config.h "#define KOL_EXCEPTIONS_ENABLED 1\n" )
ENDIF(EXCEPTIONS_ENABLED)
