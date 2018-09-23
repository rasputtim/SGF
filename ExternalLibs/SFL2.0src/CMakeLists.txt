# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(SFL_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/SFL2.0src)
set(SFL_SRC
${SFL_DIR}/sflcons.c
${SFL_DIR}/sflconv.c
${SFL_DIR}/sflcvsb.c
${SFL_DIR}/sfldate.c
${SFL_DIR}/sfldir.c
${SFL_DIR}/sflfile.c
${SFL_DIR}/sfllist.c
${SFL_DIR}/sflmem.c
${SFL_DIR}/sflnode.c
${SFL_DIR}/sflstr.c
${SFL_DIR}/sflsymb.c
${SFL_DIR}/sflsyst.c
${SFL_DIR}/sfltok.c
${SFL_DIR}/sfltron.c
${SFL_DIR}/sfluid.c
)

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (sfl_module ${SFL_SRC})
