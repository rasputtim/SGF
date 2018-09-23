# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------

set(SDLGFX_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL_gfx-2.0.24)
set(SDLGFX_SRC
${SDLGFX_DIR}/SDL_gfxPrimitives.c
${SDLGFX_DIR}/SDL_gfxBlitFunc.c
${SDLGFX_DIR}/SDL_imageFilter.c
${SDLGFX_DIR}/SDL_rotozoom.c
)
# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (sdlgfx_module ${SDLGFX_SRC})
