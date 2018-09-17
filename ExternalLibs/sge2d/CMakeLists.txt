# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(SGE_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d)
set(SGE_SRC
${SGE_DIR}/src/sge_bm_text.cpp
${SGE_DIR}/src/sgearray.c
${SGE_DIR}/src/sgegfx.c
${SGE_DIR}/src/sgeresource.c
${SGE_DIR}/src/sgesprite.c
${SGE_DIR}/src/sgespriteimage.c
)
# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (sge_module ${SGE_SRC})
