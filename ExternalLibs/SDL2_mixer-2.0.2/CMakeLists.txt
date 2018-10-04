# -------------------------------------------------------
# cmake build script for sgffabric.
# Written by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# MSVC FLAGS
# -------------------------------------------------------
#if(NOT MSVC)
#    set(CFLAGS "-W -O2 -Wwrite-strings -Wstrict-prototypes -Wall -funroll-loops -Wmissing-declarations -fomit-frame-pointer -Wno-missing-declarations")
#else(NOT MSVC)
#	set(CFLAGS "-O2")
#endif(NOT MSVC)
#
#remove_definitions(${CXXFLAGS})
#add_definitions(${CFLAGS} -DLOAD_PNG -DLOAD_PCX -DLOAD_GIF)

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(SDLMIXER_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2)

set(SDLMIXER_SRC
${SDLMIXER_DIR}/music.c
${SDLMIXER_DIR}/mixer.c
${SDLMIXER_DIR}/music_ogg.c
${SDLMIXER_DIR}/music_flac.c
${SDLMIXER_DIR}/music_mad.c
${SDLMIXER_DIR}/effect_position.c
${SDLMIXER_DIR}/effects_internal.c
${SDLMIXER_DIR}/effect_stereoreverse.c
${SDLMIXER_DIR}/load_voc.c
${SDLMIXER_DIR}/load_aiff.c
${SDLMIXER_DIR}/music_cmd.c
${SDLMIXER_DIR}/music_mikmod.c
${SDLMIXER_DIR}/music_modplug.c
${SDLMIXER_DIR}/music_mpg123.c
${SDLMIXER_DIR}/music_fluidsynth.c
${SDLMIXER_DIR}/music_nativemidi.c
${SDLMIXER_DIR}/music_ogg.c
${SDLMIXER_DIR}/music_smpeg.c
${SDLMIXER_DIR}/music_timidity.c
${SDLMIXER_DIR}/music_wav.c
${SDLMIXER_DIR}/music_modplug.c
)


# -------------------------------------------------------
# Include directory
# -------------------------------------------------------
include_directories(include ./)

# -------------------------------------------------------
# module
# -------------------------------------------------------
add_library (sdlmixer_module STATIC ${SDLMIXER_SRC})

# -------------------------------------------------------
#add_excutable (playmus.c )
#add_excutable (playwave.c)

