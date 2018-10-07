# cmake/modules/TestSignalType.cmake
#

  MESSAGE(STATUS "Check for signal return type in <signal.h>")
  TRY_COMPILE(CMAKE_TEST_SIGNAL_TYPE
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/TestSignalType.c
    OUTPUT_VARIABLE OUTPUT)
  IF (CMAKE_TEST_SIGNAL_TYPE)
    MESSAGE(STATUS "Check for signal handler return type type void  - found")
    SET (REGSIGTYPE_VOID ON)
    SET (RETSIGTYPE void CACHE INTERNAL
      "Signal return type")
      FILE(APPEND ${CMAKE_BINARY_DIR}/CMakeFiles/CMakeOutput.log
      "Determining if signal handler return type is void passed with "
      "the following output:\n${OUTPUT}\n\n")
  ELSE (CMAKE_TEST_SIGNAL_TYPE)
    MESSAGE(STATUS "Check for signal handler return type type void  - not found")
    SET (REGSIGTYPE_INT ON)
    SET (RETSIGTYPE int CACHE INTERNAL
      "Signal return type")
      FILE(APPEND ${CMAKE_BINARY_DIR}/CMakeFiles/CMakeError.log
      "Determining if signal handler return type is void failed with "
      "the following output:\n${OUTPUT}\n\n")
  ENDIF (CMAKE_TEST_SIGNAL_TYPE)

IF(REGSIGTYPE_VOID)
file(APPEND ${CMAKE_CURRENT_SOURCE_DIR}/config.h "#define RETSIGTYPE void\n" )
ELSE(REGSIGTYPE_VOID)
file(APPEND ${CMAKE_CURRENT_SOURCE_DIR}/config.h "#define RETSIGTYPE int\n" )
ENDIF(REGSIGTYPE_VOID)
