# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(SPRITE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source/sprite)
set(SPRITE_SRC
${SPRITE_DIR}/SGF_Effects.cpp
${SPRITE_DIR}/SGF_MugenSprite.cpp
${SPRITE_DIR}/SGF_RleSprite.cpp
${SPRITE_DIR}/SGF_SffManager.cpp
${SPRITE_DIR}/SGF_SffSprMan.cpp
)

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (sprite_module ${SPRITE_SRC})
