# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(STRUCTURES_DIR ${CMAKE_SOURCE_DIR}/Source/structures)
set(STRUCTURES_SRC
${STRUCTURES_DIR}/SGF_HashTableFast.cpp
${STRUCTURES_DIR}/SGF_StackString.cpp
)

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (structures_module ${STRUCTURES_SRC})
