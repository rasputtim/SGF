# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/Source/external)
set(EXTERNAL_SRC
${EXTERNAL_DIR}/DT_drawtext.c
${EXTERNAL_DIR}/fastevents.c
${EXTERNAL_DIR}/glSDL.c
${EXTERNAL_DIR}/Internal.c
${EXTERNAL_DIR}/scale2x.c
${EXTERNAL_DIR}/scale2xSDL.c
${EXTERNAL_DIR}/SDL_console.c
${EXTERNAL_DIR}/SDL_framerate.c)

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (external_module  )
