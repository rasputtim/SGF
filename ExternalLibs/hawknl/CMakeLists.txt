# -------------------------------------------------------
# hawknl cmake build script for sgffabric.
# Written by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Set some specific stuff for hawknl
# -------------------------------------------------------
#if(NOT MSVC)
#	set(CFLAGS "-W -O2 -Wwrite-strings -Wstrict-prototypes -Wall -funroll-loops -Wmissing-declarations -fomit-frame-pointer -Wno-missing-declarations")
#else(NOT MSVC)
#	set(CFLAGS "-O2")
#endif(NOT MSVC)

#remove_definitions(${CXXFLAGS})
#add_definitions(${CFLAGS})

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(HAWKNL_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/hawknl)

set(HAWKNL_SRC
${HAWKNL_DIR}/src/crc.cpp
${HAWKNL_DIR}/src/err.cpp
${HAWKNL_DIR}/src/errorstr.cpp
${HAWKNL_DIR}/src/group.cpp
${HAWKNL_DIR}/src/ipx.cpp
${HAWKNL_DIR}/src/loopback.cpp
${HAWKNL_DIR}/src/nl.cpp
${HAWKNL_DIR}/src/nltime.cpp
${HAWKNL_DIR}/src/sock.cpp)

#src/htcondition.cpp
#src/hthread.cpp
#src/htmutex.cpp

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------
#include_directories(include hawknl)

# -------------------------------------------------------
# module
# -------------------------------------------------------
add_library (hawknl_module STATIC ${HAWKNL_SRC})

