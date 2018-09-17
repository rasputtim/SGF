# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(NETWORK_DIR ${CMAKE_SOURCE_DIR}/Source/network)
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
#add_library (network_module ${NETWORK_SRC})
