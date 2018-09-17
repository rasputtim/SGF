# - Locate Ogg library
# This module defines
#  JPEG9_LIBRARY, the library to link against
#  JPEG9_FOUND, if false, do not try to link to JPEG9
#  JPEG9_INCLUDE_DIR, where to find headers.


find_path(JPEG9_INCLUDE_DIR
    NAMES
      jconfig.h jpeglib.h
    PATHS
    ${CMAKE_SOURCE_DIR}/ExternalLibs/jpeg-9/
   )
  
find_library(JPEG9_LIBRARY
    NAMES
    jpeg jpeglib
    PATHS
    ${CMAKE_SOURCE_DIR}/ExternalLibs/jpeg-9/.libs/
)
  
if (JPEG9_LIBRARY)
   set(JPEG9_FOUND TRUE)
endif (JPEG9_LIBRARY)
 
 
set(JPEG9_INCLUDE_DIR
     ${JPEG9_INCLUDE_DIR}
)
  
# Find_library will find both turbo jpeg and ordinary jpeg
if (NOT JPEG9_FOUND)
     message(STATUS "Could not find JPEG9: ")
     message(STATUS "Please Bild  Jpeg before build sgffabric ")
else(NOT JPEG9_FOUND)
     message(STATUS "JPEG9 library Found: ${JPEG9_LIBRARY}")
     message(STATUS "JPEG9 include  dir  Found:  ${JPEG9_INCLUDE_DIR}")
endif ()