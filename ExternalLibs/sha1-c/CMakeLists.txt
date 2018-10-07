# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(SHA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ExternalLibs/sha1-c)
set(SHA_SRC
${SHA_DIR}/sha1.c
)

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (sha_module ${SHA_SRC})
