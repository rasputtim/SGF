# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(PCRE_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/pcre)
set(PCRE_SRC
${PCRE_DIR}/pcre_chartables.c
${PCRE_DIR}/pcre_compile.c
${PCRE_DIR}/pcre_config.c
${PCRE_DIR}/pcre_dfa_exec.c
${PCRE_DIR}/pcre_exec.c
${PCRE_DIR}/pcre_fullinfo.c
${PCRE_DIR}/pcre_get.c
${PCRE_DIR}/pcre_globals.c
${PCRE_DIR}/pcre_info.c
${PCRE_DIR}/pcre_maketables.c
${PCRE_DIR}/pcre_newline.c
${PCRE_DIR}/pcre_ord2utf8.c
${PCRE_DIR}/pcreposix.c
${PCRE_DIR}/pcre_refcount.c
${PCRE_DIR}/pcre_study.c
${PCRE_DIR}/pcre_tables.c
${PCRE_DIR}/pcre_try_flipped.c
${PCRE_DIR}/pcre_ucd.c
${PCRE_DIR}/pcre_valid_utf8.c
${PCRE_DIR}/pcre_version.c
${PCRE_DIR}/pcre_xclass.c
)

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (pcre_module ${PCRE_SRC})
