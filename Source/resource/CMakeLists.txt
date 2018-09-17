# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}/Source/resource)
set(RESOURCES_SRC
${RESOURCES_DIR}/SGF_Collector.cpp
${RESOURCES_DIR}/SGF_ResourceManager.cpp
)

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (resources_module ${RESOURCES_SRC})
