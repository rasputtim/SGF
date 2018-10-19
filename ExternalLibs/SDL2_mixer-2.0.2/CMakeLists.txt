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
set(SDLMIXER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2)


if(SUPPORT_FLAC)
set(FLAC_LIBRARY_PATH external/flac-1.3.2)
endif(SUPPORT_FLAC)

if(SUPPORT_OGG)
set(OGG_LIBRARY_PATH external/libogg-1.3.2)
set(VORBIS_LIBRARY_PATH external/libvorbisidec-1.2.1)
endif(SUPPORT_OGG)

if(SUPPORT_MP3_MPG123)
set(MPG123_LIBRARY_PATH external/mpg123-1.25.6)
endif(SUPPORT_MP3_MPG123)

if(SUPPORT_MOD_MODPLUG)
set(MODPLUG_LIBRARY_PATH external/libmodplug-0.8.9.0)
endif(SUPPORT_MOD_MODPLUG)

if(SUPPORT_TIMIDITY)
add_definitions(-DMUSIC_MID_TIMIDITY)
set(TIMIDITY_LIBRARY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/timidity)
endif(SUPPORT_TIMIDITY) 


if(SUPPORT_FLAC)
include(${FLAC_LIBRARY_PATH})
endif(SUPPORT_FLAC)

if(SUPPORT_OGG)
include(${OGG_LIBRARY_PATH})
include(${VORBIS_LIBRARY_PATH})
endif(SUPPORT_OGG)

if(SUPPORT_MP3_MPG123)
include(${MPG123_LIBRARY_PATH})
endif(SUPPORT_MP3_MPG123)

if(SUPPORT_MOD_MODPLUG)
include(${MODPLUG_LIBRARY_PATH})
endif(SUPPORT_MOD_MODPLUG)

if(SUPPORT_TIMIDITY)
include(${TIMIDITY_LIBRARY_PATH}/CMakeLists.txt)
include_directories(${TIMIDITY_LIBRARY_PATH})
set (MIXER_LOCAL_STATIC_LIBRARIES ${MIXER_LOCAL_STATIC_LIBRARIES} timidity)
endif(SUPPORT_TIMIDITY)


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
target_link_libraries(sdlmixer_module sdl2_static ${MIXER_LOCAL_STATIC_LIBRARIES})
# -------------------------------------------------------

if(NOT ANDROID)

#tests
add_executable(playmus ${SDLMIXER_DIR}/playmus.c)
target_link_libraries(playmus sdlmixer_module)

add_executable(playwave ${SDLMIXER_DIR}/playwave.c)
target_link_libraries(playwave sdlmixer_module)
endif()
