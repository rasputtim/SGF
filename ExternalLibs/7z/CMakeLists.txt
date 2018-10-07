# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(7ZIP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ExternalLibs/7z)
set(7ZIP_SRC
${7ZIP_DIR}/7zAlloc.c
${7ZIP_DIR}/7zBuf.c
${7ZIP_DIR}/7zBuf2.c
${7ZIP_DIR}/7zCrc.c
${7ZIP_DIR}/7zCrcOpt.c
${7ZIP_DIR}/7zDec.c
${7ZIP_DIR}/7zIn.c
${7ZIP_DIR}/CpuArch.c
${7ZIP_DIR}/LzmaDec.c
${7ZIP_DIR}/Lzma2Dec.c
${7ZIP_DIR}/Bra.c
${7ZIP_DIR}/Bra86.c
${7ZIP_DIR}/Bcj2.c
${7ZIP_DIR}/7zFile.c
${7ZIP_DIR}/7zStream.c)
# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
add_library (7zip_module STATIC ${7ZIP_SRC})
