# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(CONFIGURATION_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source/configuration)
set(CONFIGURATION_SRC
${CONFIGURATION_DIR}/SGF_CmdVars.cpp
${CONFIGURATION_DIR}/SGF_ConfigSystem.cpp
${CONFIGURATION_DIR}/SGF_Configuration.cpp
${CONFIGURATION_DIR}/SGF_SysVar.cpp
)

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
add_library (configuration_module STATIC ${CONFIGURATION_SRC})
