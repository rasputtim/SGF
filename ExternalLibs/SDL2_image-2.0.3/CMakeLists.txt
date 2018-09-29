# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------




#remove_definitions(${CXXFLAGS})
#add_definitions(${CFLAGS} -DLOAD_PNG -DLOAD_PCX -DLOAD_GIF)

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(SDLIMAGE_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.3)
set(SDLIMAGE_SRC
${SDLIMAGE_DIR}/IMG.c
${SDLIMAGE_DIR}/IMG_bmp.c
${SDLIMAGE_DIR}/IMG_gif.c
${SDLIMAGE_DIR}/IMG_jpg.c
${SDLIMAGE_DIR}/IMG_lbm.c
${SDLIMAGE_DIR}/IMG_pcx.c
${SDLIMAGE_DIR}/IMG_png.c
${SDLIMAGE_DIR}/IMG_pnm.c
${SDLIMAGE_DIR}/IMG_svg.c
${SDLIMAGE_DIR}/IMG_WIC.c
${SDLIMAGE_DIR}/IMG_tga.c
${SDLIMAGE_DIR}/IMG_tif.c
${SDLIMAGE_DIR}/IMG_webp.c
${SDLIMAGE_DIR}/IMG_xcf.c
${SDLIMAGE_DIR}/IMG_xpm.c
${SDLIMAGE_DIR}/IMG_xv.c
${SDLIMAGE_DIR}/IMG_xxx.c)

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (sdlimage_module ${SDLIMAGE_SRC})
