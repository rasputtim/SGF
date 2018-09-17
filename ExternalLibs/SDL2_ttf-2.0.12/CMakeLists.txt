# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(SDLTTF_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_ttf-2.0.12)

set(SDLTTF_SRC
${SDLTTF_DIR}/SDL_ttf.c
${SDLTTF_DIR}/glfont.c
)

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (sdlttf_module ${SDLTTF_SRC})
