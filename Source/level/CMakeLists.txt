# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(LEVEL_DIR ${CMAKE_SOURCE_DIR}/Source/level)
set(LEVEL_SRC
${LEVEL_DIR}/SGF_LevelUtils.cpp
)

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (level_module ${LEVEL_SRC})
