# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(GAME_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source/game)
set(GAME_SRC
${GAME_DIR}/SGF_Console.cpp
${GAME_DIR}/SGF_Control.cpp
${GAME_DIR}/SGF_Mod.cpp
${GAME_DIR}/SGF_World.cpp)

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (game_module ${GAME_SRC})
