# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(SCRIPT_DIR ${CMAKE_SOURCE_DIR}/Source/script)
set(SCRIPT_SRC
${SCRIPT_DIR}/SGF_Script.cpp
${SCRIPT_DIR}/SGF_Perl.cpp
)

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (script_module ${SCRIPT_SRC})
