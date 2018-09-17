# -------------------------------------------------------
# cmake build script for sgffabric.
# Written by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(TIMIDITY_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/timidity)
set(TIMIDITY_SRC
${TIMIDITY_DIR}/common.c
${TIMIDITY_DIR}/instrum.c
${TIMIDITY_DIR}/mix.c
${TIMIDITY_DIR}/output.c
${TIMIDITY_DIR}/playmidi.c
${TIMIDITY_DIR}/readmidi.c
${TIMIDITY_DIR}/resample.c
${TIMIDITY_DIR}/tables.c
${TIMIDITY_DIR}/timidity.c
)

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (timidity_module ${TIMIDITY_SRC})

# -------------------------------------------------------
#add_excutable (playmus.c )
#add_excutable (playwave.c)

