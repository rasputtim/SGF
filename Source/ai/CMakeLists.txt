# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(AI_SRC
${CMAKE_SOURCE_DIR}/Source/ai/SGF_AstarHeap.cpp
${CMAKE_SOURCE_DIR}/Source/ai/SGF_AstarLib.cpp
${CMAKE_SOURCE_DIR}/Source/ai/SGF_Map.cpp
${CMAKE_SOURCE_DIR}/Source/ai/SGF_PathFinder.cpp)

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (ai_module ${AI_SRC})
