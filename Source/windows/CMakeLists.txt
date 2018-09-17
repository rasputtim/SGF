# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(WINDOWS_DIR ${CMAKE_SOURCE_DIR}/Source/windows)
set(WINDOWS_SRC
${WINDOWS_DIR}/system.cpp
${WINDOWS_DIR}/funcs.cpp
)

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (windows_module ${WINDOWS_SRC})
