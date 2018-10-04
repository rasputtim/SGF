set(MINIZIP_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/zip)
set(MINIZIP_SRC
${MINIZIP_DIR}/ioapi.c
${MINIZIP_DIR}/unzip.c
${MINIZIP_DIR}/zip.c)
# -------------------------------------------------------
# Include directory
# -------------------------------------------------------
# include_directories(include include/internal)

# -------------------------------------------------------
# module
# -------------------------------------------------------
add_library (minizip_module STATIC ${MINIZIP_SRC})
