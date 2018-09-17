# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(OGG_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/external/libogg-1.3.2/)

set(OGG_SRC
${OGG_DIR}/src/bitwise.c
${OGG_DIR}/src/framing.c
)
# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (ai_module ${AI_SRC})
