# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(OBJECTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source/objects)
set(OBJECTS_SRC
${OBJECTS_DIR}/SGF_Element.cpp
${OBJECTS_DIR}/SGF_Object.cpp
${OBJECTS_DIR}/SGF_ObjectCollidable.cpp
)

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (objects_module ${OBJECTS_SRC})
