# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(GRAPHICS_DIR ${CMAKE_SOURCE_DIR}/Source/graphics)
set(GRAPHICS_SRC
${GRAPHICS_DIR}/SGF_Bitmap.cpp
${GRAPHICS_DIR}/SGF_Color.cpp
${GRAPHICS_DIR}/SGF_FireEffect.cpp
${GRAPHICS_DIR}/SGF_GradientEffect.cpp
${GRAPHICS_DIR}/SGF_LitBitmap.cpp
${GRAPHICS_DIR}/SGF_Poligon.cpp
${GRAPHICS_DIR}/SGF_TransBitmap.cpp)

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (graphics_module ${GRAPHICS_SRC})
