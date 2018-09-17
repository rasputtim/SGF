# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(LISTS_DIR ${CMAKE_SOURCE_DIR}/Source/lists)
set(LISTS_SRC
${LISTS_DIR}/SGF_AirList.cpp
${LISTS_DIR}/SGF_ImageList.cpp
${LISTS_DIR}/SGF_PcxList.cpp
${LISTS_DIR}/SGF_SndList.cpp
)

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (lists_module ${LISTS_SRC})
