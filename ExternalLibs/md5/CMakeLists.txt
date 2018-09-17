# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(MD5_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/md5)
set(MD5_SRC
${MD5_DIR}/md5.c
)
# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (md5_module ${MD5_SRC})
