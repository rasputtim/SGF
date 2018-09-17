# -------------------------------------------------------
# cmake build script for sgffabric.
# Written by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(NATIVEMIDI_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/native_midi)
set(NATIVE_MIDI_SRC
${NATIVEMIDI_DIR}/native_midi_common.c
)
# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (nativemidi_module ${NATIVE_MIDI_SRC})

# -------------------------------------------------------
#add_excutable (playmus.c )
#add_excutable (playwave.c)

