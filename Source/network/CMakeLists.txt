# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------


#set (SDL2net_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ExternalLibs/SDL2_net-2.0.1)
#include_directories(${SDL2net_DIR})

#message (STATUS "########   SDL2NET   #####")
#add_subdirectory(${SDL2net_DIR})

set(NETWORK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source/network)
set(NETWORK_SRC
${NETWORK_DIR}/SGF_NetClient.cpp
${NETWORK_DIR}/SGF_NetServer.cpp
${NETWORK_DIR}/SGF_NetChatServer.cpp
${NETWORK_DIR}/SGF_Network.cpp
)

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
add_library (network_module STATIC ${NETWORK_SRC})
target_link_libraries(network_module exceptions_module util_module hawknl_module)
#target_link_libraries(network_module SDL2NET_module)
