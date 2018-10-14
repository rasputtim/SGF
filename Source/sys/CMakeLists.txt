# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------


message (STATUS "############## SYS MODULE ####################")
set(SYS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source/sys)
if(ANDROID)
message (STATUS "############## ANDROID SYS MODULE ####################")
set(SYS_SRC
${SYS_DIR}/SGF_System.cpp
)

else()
set(SYS_SRC
${SYS_DIR}/SGF_System.cpp
${SYS_DIR}/linux/SGF_LinShared.cpp
${SYS_DIR}/linux/SGF_LinCpu.cpp
${SYS_DIR}/linux/SGF_Fpu.cpp
)
endif()
# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
add_library (system_module STATIC ${SYS_SRC})
