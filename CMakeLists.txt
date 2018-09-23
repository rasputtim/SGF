# -------------------------------------------------------
# Sgffabric cmake build script. Creates makefiles for unix
# based systems, cygwin(sp?) or mingw
#
# Written by: Salvatore
# Modified: 08/27/2018
# -------------------------------------------------------

# -------------------------------------------------------
# Ensure that we are doing an out of source build
# Prevents any mishaps
# Also remove the makefile to regenerate the filelist
# -------------------------------------------------------
cmake_minimum_required(VERSION 3.4.1)

if(EXISTS ${CMAKE_SOURCE_DIR}/CMakeCache.txt)
	file(REMOVE ${CMAKE_SOURCE_DIR}/CMakeCache.txt)
	file(REMOVE_RECURSE ${CMAKE_SOURCE_DIR}/CMakeFiles)
endif(EXISTS ${CMAKE_SOURCE_DIR}/CMakeCache.txt)
if(EXISTS ${CMAKE_BINARY_DIR}/Makefile)
	file(REMOVE ${CMAKE_BINARY_DIR}/Makefile)
endif(EXISTS ${CMAKE_BINARY_DIR}/Makefile)
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	if(UNIX AND NOT CYGWIN)
		message(FATAL_ERROR "Oops. Don't do an in-source build. Create an extra directory change into it and run cmake pointing to the base directory. IE: \nmkdir mybuild && cd mybuild && cmake ../ && make\nYou may need to remove CMakeCache.txt and the CMakeFiles directory in ${CMAKE_SOURCE_DIR} if you can't get rid of this error.")
	else(UNIX AND NOT CYGWIN)
		message(FATAL_ERROR "Oops. Don't do an in-source build. Create an extra directory change into it and run cmake pointing to the base directory. IE: \nmkdir mybuild; cd mybuild; cmakesetup ../\nYou may need to remove CMakeCache.txt and the CMakeFiles directory in  ${CMAKE_SOURCE_DIR} if you can't get rid of this error.")
	endif(UNIX AND NOT CYGWIN)
endif(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})


# -------------------------------------------------------
# Directory in which extra macros can be found
# -------------------------------------------------------
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# -------------------------------------------------------
# Directory in which extra macros can be found
# -------------------------------------------------------
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)


# -------------------------------------------------------
# Add in uninstall target
# -------------------------------------------------------
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

add_custom_target(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")
  
  

# -------------------------------------------------------
# project name
# -------------------------------------------------------
project (sgffabric)

set(PACKAGE_BUGREPORT "rasputtim@hotmail.com")
set(PACKAGE_NAME "sgffabric")
set(PACKAGE_VERSION "2.0.0")
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
set(PACKAGE_TARNAME "${PACKAGE_NAME}")

#-------------------------------------------------------
# Findout Processor architecture
#-------------------------------------------------------
message(STATUS "The Processor is: ${CMAKE_SYSTEM_PROCESSOR}")

if( WIN32 )
message(STATUS "WIN32")
if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
set( WITH_64_BIT 1 )
#set( CMAKE_LIB_ARCH_APPENDIX "em64t" )
else( CMAKE_SIZEOF_VOID_P EQUAL 8 )
set( WITH_64_BIT 0 )
endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )
else( WIN32 )  # this is linux or Mac...
if(APPLE)
#set( CMAKE_LIB_ARCH_APPENDIX "" )
#set( CMAKE_MT_LIB_ARCH_APPENDIX "_t" )
if (CMAKE_SIZEOF_VOID_P MATCHES "8")
MESSAGE("Mac 64")
set( WITH_64_BIT 1 )
else(CMAKE_SIZEOF_VOID_P MATCHES "8")
MESSAGE("Mac 32")
set( WITH_64_BIT 0 )
endif (CMAKE_SIZEOF_VOID_P MATCHES "8")
else(APPLE)
if (CMAKE_SIZEOF_VOID_P MATCHES "8")
MESSAGE("Linux 64")
set(WITH_64_BIT 1 )
#set( CMAKE_LIB_ARCH_APPENDIX "em64t" )
#set( CMAKE_MT_LIB_ARCH_APPENDIX "em64t_t" )
else(CMAKE_SIZEOF_VOID_P MATCHES "8")
MESSAGE("Linux 32")
set(WITH_64_BIT 0 )
endif (CMAKE_SIZEOF_VOID_P MATCHES "8")
endif(APPLE)
endif(WIN32)


MESSAGE("SIZE OF VOID: ${CMAKE_SIZEOF_VOID_P}")
#math(EXPR SIZEOF_VOID_P_BITS "8 * ${CMAKE_SIZEOF_VOID_P}")
#MESSAGE("SIZE OF VOID IN Bits: ${SIZEOF_VOID_P_BITS}")

if(WITH_64_BIT)
    MESSAGE("Adding 64 bit definition to Headers")
    add_definitions(-DSIXTYFOUR_BITSUPPORT)
    #add_definitions(-D64BITSUPPORT)
else(WITH_64_BIT)
    MESSAGE("Adding 32 bit definition to Headers")
    add_definitions(-DTHIRDYTWOBITSUPPORT)
endif(WITH_64_BIT)


# VERIFY THE SYSTEM NAME
message(STATUS "SYSTEM NAME: ${CMAKE_SYSTEM_NAME}")

if(${CMAKE_SYSTEM_NAME} MATCHES "Android")
   set (ANDROID ON)
else()
   set (ANDROID OFF)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
   set (LINUX ON)
else()
   set (LINUX OFF)
endif()


# -------------------------------------------------------
# Outputs Directory
# -------------------------------------------------------

if (ANDROID)

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/libs/Android)
#by default AndroidStudio save the binary file in the folder .externalNativeBuild
#must create a configuration in gradle to copy it to the correct folder
#check build.gradle(Project:KolUtils) file
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/Android)

endif(ANDROID)

if (LINUX)

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/libs/Linux)
#by default Qt Studio save the binary file in the folder build-KolossusUtils-Desktop-Default
#you will also find project files in this folder
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/Linux)

endif(LINUX)


# -------------------------------------------------------
# Including needed macros
# -------------------------------------------------------

include(CheckCXXSourceCompiles)
include(CheckFunctionExists)
include(CheckLibraryExists)
include(CheckIncludeFiles)
include(CheckIncludeFile)
include(CheckSymbolExists)
include(CheckCSourceRuns)
include(CheckCCompilerFlag)
include(CheckTypeSize)
include(CheckStructHasMember)
include(CMakeDependentOption)
include(FindPkgConfig)
include(GNUInstallDirs)
include(CheckCSourceCompiles)
include(CheckCXXSourceCompiles)
message(STATUS "WILL TEST SIGNAL TYPE:")
include(TestSignalType)
include(FindGccAtomic)
include(TestExceptions)
include(FindSysLog)
include(TestBitsAtomic)
include(TestPThreads)

# -------------------------------------------------------
# FIND PACKAGES
# -------------------------------------------------------

find_package(ZLIB)
find_package(PNG)
find_package(FREETYPE)
find_package(Threads)
#find_package(GNUREGEX)
find_package(VORBIS)
find_package(OGG)
find_package(MPG123)
find_package(JPEG9)
find_package(PERL)
find_package(PERLLIBS)
find_package(TIFF)

# -------------------------------------------------------
# Include Source Files
# I do not use the CMakeFile.txt of the subfolders.
#Except for modules OGG anf TIFF
# All source files are listed in this file
# that is i do not use sub modules. maybe I will change this in future
# -------------------------------------------------------
#include(FileList)

mark_as_advanced(CLEAR ZLIB_INCLUDE_DIR)
mark_as_advanced(CLEAR ZLIB_LIBRARY)

mark_as_advanced(CLEAR PNG_PNG_INCLUDE_DIR)
mark_as_advanced(CLEAR PNG_LIBRARY)

# -------------------------------------------------------
# User setable options
# -------------------------------------------------------
option(DEBUG "Compile sgffabric with debug information?" ON)

set(INSTALL_PREFIX "SGF")

if($ENV{DEBUG})
    set(DEBUG ON)
elseif(NOT $ENV{DEBUG})
    set(DEBUG OFF)
endif($ENV{DEBUG})

# VERIFICAR SE A CPU TEM SUPORTE SSE para s flags msse mmmx

if(DEBUG)
# Set defaults preventing destination file conflicts
set(SGF_CMAKE_DEBUG_POSTFIX "d"
    CACHE STRING "Name suffix for debug builds")

mark_as_advanced(CMAKE_IMPORT_LIBRARY_SUFFIX SGF_CMAKE_DEBUG_POSTFIX)

    add_definitions(-DDEBUG)
     message(STATUS "====================COMPILING WITH DEBUG INFORMATION====================================")
    if (ANDROID)
        #set(CMAKE_CXX_FLAGS "-Wall -Wno-unused-variable -Wno-unused-function -funroll-loops -Woverloaded-virtual -g3 -ggdb -std=c++11 ")
        #set(CMAKE_C_FLAGS "-Wall -Wno-unused-variable -Wno-unused-function -funroll-loops -g3 -ggdb")
    else()
    
            set(CMAKE_CXX_FLAGS "-Wall -Wno-unused-variable -Wno-unused-function -funroll-loops -fexpensive-optimizations -Woverloaded-virtual -g3 -ggdb -std=c++11 -msse3")
            set(CMAKE_C_FLAGS "-Wall -Wno-unused-variable -Wno-unused-function -funroll-loops -fexpensive-optimizations -g3 -ggdb -msse3")
            
            if(WITH_64_BIT)  #cross compilling to 32bit 
            set(ADITIONAL_CXX_FLAGS "-m32")
            set(ADITIONAL_LINK_FLAGS "-m32")
            else(WITH_64_BIT)
            set(ADITIONAL_CXX_FLAGS "")
            set(ADITIONAL_LINK_FLAGS "")
            endif(WITH_64_BIT)
    endif()
    
    
else(DEBUG)
 message(STATUS "====================COMPILING WITHOUT DEBUG INFORMATION====================================")
    if (ANDROID)
        #set(CMAKE_CXX_FLAGS "-O2 -Wall -Wno-unused-variable -Wno-unused-function -funroll-loops  -Woverloaded-virtual -std=c++11 ")
        #set(CMAKE_C_FLAGS "-O2 -Wall -Wno-unused-variable -Wno-unused-function -funroll-loops ")

    else()
        set(CMAKE_CXX_FLAGS "-O2 -Wall -Wno-unused-variable -Wno-unused-function -funroll-loops -fexpensive-optimizations -Woverloaded-virtual -std=c++11 -msse3")
        set(CMAKE_C_FLAGS "-O2 -Wall -Wno-unused-variable -Wno-unused-function -funroll-loops -fexpensive-optimizations -msse3")

        if(WITH_64_BIT)
        set(ADITIONAL_CXX_FLAGS "-m32")
        set(ADITIONAL_LINK_FLAGS "-m32")
        else(WITH_64_BIT)
        set(ADITIONAL_CXX_FLAGS "")
        set(ADITIONAL_LINK_FLAGS "")
        endif(WITH_64_BIT)
    endif()
endif(DEBUG)
   # -------------------------------------------------------
# MSVC FLAGS
# -------------------------------------------------------
#if(NOT MSVC)
#	set(CFLAGS "-W -O2 -Wwrite-strings -Wstrict-prototypes -Wall -funroll-loops -Wmissing-declarations -fomit-frame-pointer -Wno-missing-declarations")
#else(NOT MSVC)
#	set(CFLAGS "-O2")
#endif(NOT MSVC) 
    
    
# FIXME: not sure if this is in the right place
add_definitions(-DHAVE_NETWORKING)

option(USE_SDL ON)

if($ENV{SDL})
    set(USE_SDL ON)
elseif(NOT $ENV{SDL})
    set(USE_SDL OFF)
endif($ENV{SDL})

if(JPEG9_FOUND)
    message(STATUS "LIB jpeg9 found to use with SDL2_image.")
    add_definitions(-DHAVE_JPEG)
    set(JPEG9_LIBS ${JPEG9_LIBRARY})
    set(JPEG9_INCLUDES ${JPEG9_INCLUDE_DIR})
else(JPEG9_FOUND)
    message(STATUS "LIB jpeg9 NOT found to use with SDL2_image. I Will build tiff internally")
    set(JPEG9_LIBS "")
    set(JPEG9_INCLUDES "")
endif(JPEG9_FOUND)


if(EXISTS ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/external/libogg-1.3.2/include/ogg/config_types.h)
        file(REMOVE ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/external/libogg-1.3.2/include/ogg/config_types.h)
endif(EXISTS ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/external/libogg-1.3.2/include/ogg/config_types.h)

if(OGG_FOUND)
    message(STATUS "LIB OGG found to use with SDL2_MIXER.")
    add_definitions(-DHAVE_OGG)
    set(OGG_LIBS ${OGG_LIBRARY} ${VORBIS_LIBRARIES})
    set(OGG_INCLUDES ${OGG_INCLUDE_DIR} ${VORBIS_INCLUDE_DIR})
    set(OGG_INTERNAL OFF)
    set(OGG_SRC "")
else(OGG_FOUND)
    message(STATUS "LIB OGG NOT found to use with SDL2_MIXER. I Will build tiff internally")
    #use internal ogg_module
    set(OGG_INCLUDES ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/external/libogg-1.3.2/include/)
    set(OGG_LIBS "")
    set(OGG_INTERNAL ON)
    file(APPEND ${OGG_INCLUDES}/ogg/config_types.h "#ifndef __CONFIG_TYPES_H__ \n")
    file(APPEND ${OGG_INCLUDES}/ogg/config_types.h "#define __CONFIG_TYPES_H__ \n")
    file(APPEND ${OGG_INCLUDES}/ogg/config_types.h "#include \"SGF_Types.h\" \n")
    file(APPEND ${OGG_INCLUDES}/ogg/config_types.h "typedef int64_t ogg_int64_t; \n" )
    file(APPEND ${OGG_INCLUDES}/ogg/config_types.h "typedef uint16_t ogg_uint16_t; \n" )
    file(APPEND ${OGG_INCLUDES}/ogg/config_types.h "typedef int32_t ogg_int32_t; \n" )
    file(APPEND ${OGG_INCLUDES}/ogg/config_types.h "typedef uint32_t ogg_uint32_t; \n" )
    file(APPEND ${OGG_INCLUDES}/ogg/config_types.h "typedef int16_t ogg_int16_t; \n" )
    file(APPEND ${OGG_INCLUDES}/ogg/config_types.h "#endif \n")

endif(OGG_FOUND)

if(TIFF_FOUND)
    add_definitions(-DHAVE_OGG)
    set(TIFF_LIBS ${TIFF_LIBRARY} ${TIFF_LIBRARIES})
    set(TIFF_INCLUDES ${TIFF_INCLUDE_DIR})
    set(TIFF_INTERNAL OFF)
    message(STATUS "LIB TIFF found to use with SDL2_image.")
    set(TIFF_SRC "")
else(TIFF_FOUND)
    #use internal tiff_module
    message(STATUS "LIB TIFF not found. I Will build tiff internally to use with SDL2_image.")
    set(TIFF_INCLUDES ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.0/external/tiff-4.0.3/libtiff/)
    set(TIFF_LIBS "")
    set(TIFF_INTERNAL ON)
endif(TIFF_FOUND)



#i WILL BUILD sdl2 INTERNALLY
#if(USE_SDL)
    # packages
    #find_package(SDL2)
    # sdl
    #add_definitions(-DUSE_SDL)
    #if(NOT SDL_FOUND)
    #    message(FATAL_ERROR "Couldn't find SDL2.")
    #else(NOT SDL_FOUND)    
    #    message("SDL2 found SDL2.")
    #endif(NOT SDL_FOUND)
    
    # SET Mixer definition
    if (MAD_FOUND)
	add_definitions(-DMP3_MAD_MUSIC)
    endif(MAD_FOUND)
    
    set(GRAPHICS_LIBRARIES sfl_module sprig_module sdl_stretch_module image_module mixer_module ${SDL_LIBRARY})
    set(GRAPHICS_INCLUDES ${SDL_INCLUDE_DIR})
    if (APPLE)
	add_definitions(-DUSE_SDL_MAIN)
    endif(APPLE)
#endif(USE_SDL)

if(MPG123_FOUND)
    add_definitions(-DHAVE_MP3_MPG123)
    set(MP3_LIBS ${MPG123_LIBRARY})
    set(MP3_INCLUDES ${MPG123_INCLUDE_DIR})
else(MPG123_FOUND)
    if (SDL_FOUND)
	# Try looking for libmad instead only if SDL is available
	find_package(MAD)
	if (MAD_FOUND)
	    add_definitions(-DHAVE_MP3_MAD)
	    set(MP3_LIBS ${MAD_LIBRARY})
	    set(MP3_INCLUDES ${MAD_INCLUDE_DIR})
	else(MAD_FOUND)
	    set(MP3_LIBS "")
	    set(MP3_INCLUDES "")
	endif(MAD_FOUND)
    endif (SDL_FOUND)
endif(MPG123_FOUND)
#PERL
if(PERL_FOUND)
    add_definitions(-DHAVE_PERL)
else(PERL_FOUND)
endif(PERL_FOUND)


if(PERLLIBS_FOUND)
    add_definitions(-DSGF_PERL_SCRIPTING)
    message("PERL LIBRARY FOUND - BUILDING WITH PERL SUPPORT")
    message(STATUS "PERL library Found: ${PERL_LIBRARY}")
    message(STATUS "PERL include  dir  Found:  ${PERL_INCLUDE_PATH}")
    message(STATUS "PERL Version: ${PERL_VERSION_STRING}")
    # Introduced after CMake 2.6.4 to bring module into compliance
    set(PERL_INCLUDE_DIR ${PERL_INCLUDE_PATH})
    set(PERL_INCLUDE_DIRS ${PERL_INCLUDE_PATH})
    set(PERL_LIBRARIES ${PERL_LIBRARY})
    # For backward compatibility with CMake before 2.8.8
    set(PERL_VERSION ${PERL_VERSION_STRING})
else(PERLLIBS_FOUND)
    message(WARNING "Couldn't find Perl Libs")
    message(WARNING "Building Without PERL Support")
    set(PERL_LIBS "")
    set(PERL_INCLUDES "")
endif(PERLLIBS_FOUND)
# freetype
if(NOT FREETYPE_FOUND)
	message(STATUS "LIB freetype not found. I Will build FREEtYPE internally.")
        set(FREETYPE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/freetype-2.9.1/include/)
    set(FREETYPE_LIBS "")
    set(FREETYPE_INTERNAL ON)
endif(NOT FREETYPE_FOUND)
if(NOT PNG_FOUND)
	message(STATUS "LIB PNG not found. I Will build PNG internally.")
	set(PNG_INCLUDES ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.0/external/libpng-1.6.2/)
    set(PNG_LIBS "")
    set(PNG_INTERNAL ON)
endif(NOT PNG_FOUND)
# regex
#if(NOT GNUREGEX_FOUND)
#	message(FATAL_ERROR "Couldn't find GNU Regex")
#endif(NOT GNUREGEX_FOUND)

# -------------------------------------------------------
# Paths and system setup
# -------------------------------------------------------

# -------------------------------------------------------
# MINGW
# -------------------------------------------------------

if(MINGW OR CYGWIN)
	# -------------------------------------------------------
	# Take those user options and set the necessary compile time preprocessors
	# -------------------------------------------------------
	add_definitions(-DWINDOWS)
	set(WIN_LIB -lgdi32 -luser32 -lwsock32)
	 set(CMAKE_THREAD_LIBS_INIT -lpthreadGC2)
else(MINGW OR CYGWIN)
	 set(CMAKE_THREAD_LIBS_INIT -lpthread)


remove_definitions(${CXXFLAGS})
add_definitions(${CFLAGS} -DLOAD_PNG -DLOAD_PCX -DLOAD_GIF)

endif(MINGW OR CYGWIN)

# -------------------------------------------------------
# Apple OSX
# -------------------------------------------------------

if(APPLE)
	# -------------------------------------------------------
    # Added stuff for osx
	# -------------------------------------------------------
	set(WIN_LIB "-framework Carbon")
	add_definitions(-DMACOSX)
        
        # Groups
        set(GROUP_START "-Wl,-all_load")
        set(GROUP_END "")
else(APPLE)
        # Groups
        set(GROUP_START "-Wl,--start-group")
        set(GROUP_END "-Wl,--end-group")
endif(APPLE)

#  Vstudio definitions
#_DEBUG
#WIN32
#_WINDOWS
#SDL_Image      preprocessors
add_definitions(-DLOAD_BMP)
add_definitions(-DLOAD_GIF)
add_definitions(-DLOAD_JPG)
#add_definitions(-LOAD_JPG_DYNAMIC="libjpeg-8.dll")
add_definitions(-DLOAD_LBM)
add_definitions(-DLOAD_PCX)
add_definitions(-DLOAD_PNG)
#add_definitions(-LOAD_PNG_DYNAMIC="libpng15-15.dll")
add_definitions(-DLOAD_PNM)
add_definitions(-DLOAD_TGA)
add_definitions(-DLOAD_TIF)
#add_definitions(-LOAD_TIF_DYNAMIC="libtiff-5.dll")
add_definitions(-DLOAD_XPM)
add_definitions(-DLOAD_WEBP)
#add_definitions(-LOAD_WEBP_DYNAMIC="libwebp-2.dll")
add_definitions(-DLOAD_XV)
#add_definitions(-PNG_USE_DLL)
#----------------------------------------
#add_definitions(-_CRT_SECURE_NO_WARNINGS)
# SDL_Mixer definitions
add_definitions(-DWAV_MUSIC)
add_definitions(-DMOD_MUSIC)
#add_definitions(-MOD_DYNAMIC="mikmod.dll")
add_definitions(-DMID_MUSIC)
add_definitions(-DUSE_TIMIDITY_MIDI)
#add this to use  FLUIDSYNTH_MIDI
#add_definitions(-DUSE_FLUIDSYNTH_MIDI)
add_definitions(-DUSE_NATIVE_MIDI)
#add definition to bildcommand  supports an external command for playing music */
add_definitions(-DCMD_MUSIC)
#ifdef CMD_MUSIC
##To play MIDI files, you'll need to get a complete set of GUS patches
##from: http://www.libsdl.org/projects/mixer/timidity/timidity.tar.gz
##and unpack them in /usr/local/lib under UNIX, and C:\ under Win32.

add_definitions(-DOGG_MUSIC)
add_definitions(-DOGG_USE_TREMOR)
#windows use dinamic
#add_definitions(-OGG_DYNAMIC="libvorbisfile-3.dll")
add_definitions(-DMP3_MUSIC)
#add this if use libmad to play mp3 music // find libmad first
#add_definitions(-DMP3_MAD_MUSIC)
#add_definitions(-MP3_DYNAMIC="smpeg.dll")
#add_definitions(-XMLTOKAPI=__declspec(dllimport))
#add_definitions(-XML_DTD)
#add_definitions(-ZLIB_WINAPI)
#add_definitions(-_CRT_NONSTDC_NO_DEPRECATE)
#add_definitions(-_CRT_SECURE_NO_DEPRECATE)
#add_definitions(-_CRT_NONSTDC_NO_WARNINGS)


# -------------------------------------------------------
# Include directory & Files
# List of preprocessor include file search directories.
# -------------------------------------------------------
include_directories(${CMAKE_SOURCE_DIR}/Gamecore 
${CMAKE_SOURCE_DIR}/Header 
${CMAKE_SOURCE_DIR}/ExternalLibs/7z
${CMAKE_SOURCE_DIR}/ExternalLibs/hawkln
${CMAKE_SOURCE_DIR}/ExternalLibs/md5 
${CMAKE_SOURCE_DIR}/ExternalLibs/pcre 
${CMAKE_SOURCE_DIR}/ExternalLibs/perl56
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_SGF
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2/include
#${CMAKE_SOURCE_DIR}/ExternalLibs/Regex 
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL_gfx-2.0.24
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.0
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.0/external/libwebp-0.3.0/src/
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.0/external/zlib-1.2.8
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.0/external/libpng-1.6.2/
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/timidity
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/native_midi
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/external
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_ttf-2.0.12
if(FREETYPE_INTERNAL)
${CMAKE_SOURCE_DIR}/ExternalLibs/ExternalLibs/freetype-2.9.1/include/
endif()
${CMAKE_SOURCE_DIR}/ExternalLibs/SFL2.0src
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include
${CMAKE_SOURCE_DIR}/ExternalLibs/sha1-c
${CMAKE_SOURCE_DIR}/ExternalLibs/zip
${GRAPHICS_INCLUDES} 
${FREETYPE_INCLUDE_DIR} 
${OGG_INCLUDES} 
${MP3_INCLUDES}
${PERL_INCLUDE_DIR}
${PERL_INCLUDE_DIRS}
${JPEG9_INCLUDES}
${TIFF_INCLUDES}
# todo: Build the library
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/external/libvorbisidec-1.2.1
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/external/smpeg2-2.0.0
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/external/flac-1.2.1
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/external/libmikmod-3.1.12/include/
#expat
${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/lib/
${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/
)


set(SGF_PUBLIC_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/SGF.h
${CMAKE_SOURCE_DIR}/Gamecore/tiffconfig.h
${CMAKE_SOURCE_DIR}/Gamecore/SGF_Config.h
${CMAKE_SOURCE_DIR}/Gamecore/SGF_Global.h
${CMAKE_SOURCE_DIR}/Gamecore/SGF_Types.h)
set(SGF_AI_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/ai/all.h
${CMAKE_SOURCE_DIR}/Gamecore/ai/SGF_AstarHeap.h
${CMAKE_SOURCE_DIR}/Gamecore/ai/SGF_AstarLib.h
${CMAKE_SOURCE_DIR}/Gamecore/ai/SGF_Behavior.h
${CMAKE_SOURCE_DIR}/Gamecore/ai/SGF_Map.h
${CMAKE_SOURCE_DIR}/Gamecore/ai/SGF_PathFinder.h

)
set(SGF_CONFIGURATION_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/configuration/all.h
${CMAKE_SOURCE_DIR}/Gamecore/configuration/SGF_CmdVars.h
${CMAKE_SOURCE_DIR}/Gamecore/configuration/SGF_Configuration.h
${CMAKE_SOURCE_DIR}/Gamecore/configuration/SGF_SysVars.h
${CMAKE_SOURCE_DIR}/Gamecore/configuration/SGF_SysVarsyyy.h

)
set(SGF_ENVIRONMENT_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/environment/all.h
)
set(SGF_EXCEPTIONS_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/exceptions/all.h
${CMAKE_SOURCE_DIR}/Gamecore/exceptions/SGF_Error.h
${CMAKE_SOURCE_DIR}/Gamecore/exceptions/SGF_Exception.h
${CMAKE_SOURCE_DIR}/Gamecore/exceptions/SGF_FileExceptions.h
${CMAKE_SOURCE_DIR}/Gamecore/exceptions/SGF_LoadException.h
${CMAKE_SOURCE_DIR}/Gamecore/exceptions/SGF_MenuException.h
${CMAKE_SOURCE_DIR}/Gamecore/exceptions/SGF_MugenException.h
${CMAKE_SOURCE_DIR}/Gamecore/exceptions/SGF_NetException.h
${CMAKE_SOURCE_DIR}/Gamecore/exceptions/SGF_ShutdownException.h
${CMAKE_SOURCE_DIR}/Gamecore/exceptions/SGF_TokenException.h

)
set(SGF_EXTERNAL_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/external/all.h
${CMAKE_SOURCE_DIR}/Gamecore/external/DT_drawtext.h
${CMAKE_SOURCE_DIR}/Gamecore/external/SDL_console.h
${CMAKE_SOURCE_DIR}/Gamecore/external/SDL_framerate.h
${CMAKE_SOURCE_DIR}/Gamecore/external/fastevents.h
${CMAKE_SOURCE_DIR}/Gamecore/external/glSDL.h
${CMAKE_SOURCE_DIR}/Gamecore/external/internal.h
${CMAKE_SOURCE_DIR}/Gamecore/external/scale2x.h

)
set(SGF_GAME_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/game/all.h
${CMAKE_SOURCE_DIR}/Gamecore/game/SGF_Command.h
${CMAKE_SOURCE_DIR}/Gamecore/game/SGF_Console.h
${CMAKE_SOURCE_DIR}/Gamecore/game/SGF_Control.h
${CMAKE_SOURCE_DIR}/Gamecore/game/SGF_Mod.h
${CMAKE_SOURCE_DIR}/Gamecore/game/SGF_Stage.h
${CMAKE_SOURCE_DIR}/Gamecore/game/SGF_World.h

)
set(SGF_GEOMETRY_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/geometry/all.h
${CMAKE_SOURCE_DIR}/Gamecore/geometry/SGF_DrawVert.h
${CMAKE_SOURCE_DIR}/Gamecore/geometry/SGF_JointTransform.h
${CMAKE_SOURCE_DIR}/Gamecore/geometry/SGF_TraceModel.h
)
set(SGF_GRAPHICS_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/graphics/all.h
${CMAKE_SOURCE_DIR}/Gamecore/graphics/SGF_Bitmap.h
${CMAKE_SOURCE_DIR}/Gamecore/graphics/SGF_Color.h
${CMAKE_SOURCE_DIR}/Gamecore/graphics/SGF_FireEffect.h
${CMAKE_SOURCE_DIR}/Gamecore/graphics/SGF_GradientEffect.h
${CMAKE_SOURCE_DIR}/Gamecore/graphics/SGF_LitBitmap.h
${CMAKE_SOURCE_DIR}/Gamecore/graphics/SGF_Poligon.h
${CMAKE_SOURCE_DIR}/Gamecore/graphics/SGF_TransBitmap.h

)
set(SGF_GUI_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/gui/all.h
${CMAKE_SOURCE_DIR}/Gamecore/gui/SGF_BoundBox.h
${CMAKE_SOURCE_DIR}/Gamecore/gui/SGF_Box.h
${CMAKE_SOURCE_DIR}/Gamecore/gui/SGF_ContextBox.h
${CMAKE_SOURCE_DIR}/Gamecore/gui/SGF_Coordinate.h
${CMAKE_SOURCE_DIR}/Gamecore/gui/SGF_FadetoolGui.h
${CMAKE_SOURCE_DIR}/Gamecore/gui/SGF_GuiAnimation.h
${CMAKE_SOURCE_DIR}/Gamecore/gui/SGF_GuiTimer.h
${CMAKE_SOURCE_DIR}/Gamecore/gui/SGF_LineEdit.h
${CMAKE_SOURCE_DIR}/Gamecore/gui/SGF_PopupBox.h
${CMAKE_SOURCE_DIR}/Gamecore/gui/SGF_Rectarea.h
${CMAKE_SOURCE_DIR}/Gamecore/gui/SGF_ScrollList.h
${CMAKE_SOURCE_DIR}/Gamecore/gui/SGF_SelectList.h
${CMAKE_SOURCE_DIR}/Gamecore/gui/SGF_TabbedBox.h
${CMAKE_SOURCE_DIR}/Gamecore/gui/SGF_Widget.h

)
set(SGF_INPUT_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/input/all.h
${CMAKE_SOURCE_DIR}/Gamecore/input/SGF_ButtonMapping.h
${CMAKE_SOURCE_DIR}/Gamecore/input/SGF_Events.h
${CMAKE_SOURCE_DIR}/Gamecore/input/SGF_FrameControl.h
${CMAKE_SOURCE_DIR}/Gamecore/input/SGF_Input.h
${CMAKE_SOURCE_DIR}/Gamecore/input/SGF_InputManager.h
${CMAKE_SOURCE_DIR}/Gamecore/input/SGF_InputMap.h
${CMAKE_SOURCE_DIR}/Gamecore/input/SGF_InputSource.h
${CMAKE_SOURCE_DIR}/Gamecore/input/SGF_Joystick.h
${CMAKE_SOURCE_DIR}/Gamecore/input/SGF_KeyMapping.h
${CMAKE_SOURCE_DIR}/Gamecore/input/SGF_Keyboard.h
${CMAKE_SOURCE_DIR}/Gamecore/input/SGF_Mouse.h
${CMAKE_SOURCE_DIR}/Gamecore/input/SGF_PSPJoystick.h
${CMAKE_SOURCE_DIR}/Gamecore/input/SGF_StructsInput.h
${CMAKE_SOURCE_DIR}/Gamecore/input/SGF_TextInput.h
${CMAKE_SOURCE_DIR}/Gamecore/input/SGF_WIIJoystick.h
${CMAKE_SOURCE_DIR}/Gamecore/input/newInput.h
${CMAKE_SOURCE_DIR}/Gamecore/input/sdl-joystick.h

)
set(SGF_LEVEL_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/level/all.h
${CMAKE_SOURCE_DIR}/Gamecore/level/SGF_LevelUtils.h
)
set(SGF_LISTS_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/lists/all.h
${CMAKE_SOURCE_DIR}/Gamecore/lists/SGF_AirList.h
${CMAKE_SOURCE_DIR}/Gamecore/lists/SGF_ImageList.h
${CMAKE_SOURCE_DIR}/Gamecore/lists/SGF_PcxList.h
${CMAKE_SOURCE_DIR}/Gamecore/lists/SGF_SndList.h
${CMAKE_SOURCE_DIR}/Gamecore/lists/liststructs.h

)
set(SGF_MATH_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/math/all.h
${CMAKE_SOURCE_DIR}/Gamecore/math/Plane.h
${CMAKE_SOURCE_DIR}/Gamecore/math/SGF_Angles.h
${CMAKE_SOURCE_DIR}/Gamecore/math/SGF_Complex.h
${CMAKE_SOURCE_DIR}/Gamecore/math/SGF_Curve.h
${CMAKE_SOURCE_DIR}/Gamecore/math/SGF_Extrapolate.h
${CMAKE_SOURCE_DIR}/Gamecore/math/SGF_Interpolation.h
${CMAKE_SOURCE_DIR}/Gamecore/math/SGF_Lincp.h
${CMAKE_SOURCE_DIR}/Gamecore/math/SGF_Math.h
${CMAKE_SOURCE_DIR}/Gamecore/math/SGF_Matriz.h
${CMAKE_SOURCE_DIR}/Gamecore/math/SGF_Odife.h
${CMAKE_SOURCE_DIR}/Gamecore/math/SGF_Plane.h
${CMAKE_SOURCE_DIR}/Gamecore/math/SGF_PlaneList.h
${CMAKE_SOURCE_DIR}/Gamecore/math/SGF_Pluecker.h
${CMAKE_SOURCE_DIR}/Gamecore/math/SGF_Polynomial.h
${CMAKE_SOURCE_DIR}/Gamecore/math/SGF_Quaternion.h
${CMAKE_SOURCE_DIR}/Gamecore/math/SGF_Random.h
${CMAKE_SOURCE_DIR}/Gamecore/math/SGF_Rotation.h
${CMAKE_SOURCE_DIR}/Gamecore/math/SGF_Simd.h
${CMAKE_SOURCE_DIR}/Gamecore/math/SGF_Vector.h
${CMAKE_SOURCE_DIR}/Gamecore/math/Simd_3DNow.h
${CMAKE_SOURCE_DIR}/Gamecore/math/Simd_AltiVec.h
${CMAKE_SOURCE_DIR}/Gamecore/math/Simd_Generic.h
${CMAKE_SOURCE_DIR}/Gamecore/math/Simd_MMX.h
${CMAKE_SOURCE_DIR}/Gamecore/math/Simd_SSE.h
${CMAKE_SOURCE_DIR}/Gamecore/math/Simd_SSE2.h
${CMAKE_SOURCE_DIR}/Gamecore/math/Simd_SSE3.h

)
set(SGF_MENU_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/menu/all.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_ActionFactory.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_ActionSpeed.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_Menu.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_MenuAction.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_MenuAnimation.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_MenuGlobal.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_MenuOption.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_MenuV2.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_OptionAdventure.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_OptionAdventureCpu.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_OptionChangeMod.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_OptionConfig.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_OptionCredits.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_OptionDummy.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_OptionFactory.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_OptionFullScreen.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_OptionFullscreen.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_OptionInvencible.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_OptionJoystick.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_OptionKey.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_OptionLevel.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_OptionLives.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_OptionMenu.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_OptionNetworkHost.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_OptionNetworkJoin.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_OptionNpcBuddies.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_OptionPlayMode.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_OptionQuit.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_OptionScreenSize.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_OptionSelectFontV2.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_OptionSpeed.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_OptionTabMenu.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_OptionVersus.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_StructsMenu.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/SGF_TabMenu.h
${CMAKE_SOURCE_DIR}/Gamecore/menu/options.h

)
set(SGF_MUGEN_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/all.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/Configuration.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/Expression.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/Modifier.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/Section.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/Stack.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/Value.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/argument.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/ast.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/astManager.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/attribute-array.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/attribute-keyword.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/attribute-simple.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/attribute.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/collectable.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/exception.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/extra.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/filename.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/function.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/helper.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/hitdef.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/identifier.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/key.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/keyword-array.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/keyword.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/number.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/operand.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/range.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/resource.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/string.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/value-list.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/variable.h
${CMAKE_SOURCE_DIR}/Gamecore/mugen/Ast/walker.h

)
set(SGF_MUGEN2_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/mugen/gc.h
)
set(SGF_NETWORK_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/network/all.h
${CMAKE_SOURCE_DIR}/Gamecore/network/SGF_NetChat.h
${CMAKE_SOURCE_DIR}/Gamecore/network/SGF_NetChatClient.h
${CMAKE_SOURCE_DIR}/Gamecore/network/SGF_NetChatServer.h
${CMAKE_SOURCE_DIR}/Gamecore/network/SGF_NetChatWidget.h
${CMAKE_SOURCE_DIR}/Gamecore/network/SGF_NetClient.h
${CMAKE_SOURCE_DIR}/Gamecore/network/SGF_NetServer.h
${CMAKE_SOURCE_DIR}/Gamecore/network/SGF_Network.h

)
set(SGF_OBJECTS_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/objects/all.h
${CMAKE_SOURCE_DIR}/Gamecore/objects/SGF_Element.h
${CMAKE_SOURCE_DIR}/Gamecore/objects/SGF_Object.h
${CMAKE_SOURCE_DIR}/Gamecore/objects/SGF_ObjectCollidable.h
${CMAKE_SOURCE_DIR}/Gamecore/objects/SGF_ObjectMessages.h
${CMAKE_SOURCE_DIR}/Gamecore/objects/SGF_ObjectNonAttack.h

)
set(SGF_RESOURCE_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/resource/all.h
${CMAKE_SOURCE_DIR}/Gamecore/resource/SGF_Collector.h
${CMAKE_SOURCE_DIR}/Gamecore/resource/SGF_FontRender.h
${CMAKE_SOURCE_DIR}/Gamecore/resource/SGF_ResourceManager.h

)
set(SGF_SCRIPT_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/script/all.h
${CMAKE_SOURCE_DIR}/Gamecore/script/SGF_Perl.h
${CMAKE_SOURCE_DIR}/Gamecore/script/SGF_Scripting.h

)
set(SGF_SPRITE_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/sprite/all.h
${CMAKE_SOURCE_DIR}/Gamecore/sprite/DrawRle.h
${CMAKE_SOURCE_DIR}/Gamecore/sprite/SGF_Efects.h
${CMAKE_SOURCE_DIR}/Gamecore/sprite/SGF_MugenSprite.h
${CMAKE_SOURCE_DIR}/Gamecore/sprite/SGF_RleSprite.h
${CMAKE_SOURCE_DIR}/Gamecore/sprite/SGF_SffManager.h
${CMAKE_SOURCE_DIR}/Gamecore/sprite/SGF_SffSprMan.h
${CMAKE_SOURCE_DIR}/Gamecore/sprite/defs.h
${CMAKE_SOURCE_DIR}/Gamecore/sprite/sprite.h

)
set(SGF_STRUCTURES_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/structures/all.h
${CMAKE_SOURCE_DIR}/Gamecore/structures/BTree.h
${CMAKE_SOURCE_DIR}/Gamecore/structures/BinSearch.h
${CMAKE_SOURCE_DIR}/Gamecore/structures/Hierarchy.h
${CMAKE_SOURCE_DIR}/Gamecore/structures/SGF_BHeap.h
${CMAKE_SOURCE_DIR}/Gamecore/structures/SGF_Btree.h
${CMAKE_SOURCE_DIR}/Gamecore/structures/SGF_Btree_old.h
${CMAKE_SOURCE_DIR}/Gamecore/structures/SGF_DynamicArray.h
${CMAKE_SOURCE_DIR}/Gamecore/structures/SGF_HashTable.h
${CMAKE_SOURCE_DIR}/Gamecore/structures/SGF_HashTableFast.h
${CMAKE_SOURCE_DIR}/Gamecore/structures/SGF_LinkList.h
${CMAKE_SOURCE_DIR}/Gamecore/structures/SGF_List.h
${CMAKE_SOURCE_DIR}/Gamecore/structures/SGF_ListString.h
${CMAKE_SOURCE_DIR}/Gamecore/structures/SGF_Parameter.h
${CMAKE_SOURCE_DIR}/Gamecore/structures/SGF_Queue.h
${CMAKE_SOURCE_DIR}/Gamecore/structures/SGF_Stack.h
${CMAKE_SOURCE_DIR}/Gamecore/structures/SGF_StackString.h
${CMAKE_SOURCE_DIR}/Gamecore/structures/StaticList.h
${CMAKE_SOURCE_DIR}/Gamecore/structures/StrPool.h
${CMAKE_SOURCE_DIR}/Gamecore/structures/VectorSet.h

)
set(SGF_SYS_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/sys/all.h
${CMAKE_SOURCE_DIR}/Gamecore/sys/SGF_System.h
)
set(SGF_UTIL_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/util/all.h
${CMAKE_SOURCE_DIR}/Gamecore/util/AirManager.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_ArgsCmdLine.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_AudioSystem.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_BHeap.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_Callback.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_Compress.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_Debug.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_Displayable.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_Ebox.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_FileSystem.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_FilesystemBase.cpp
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_FilesystemBase.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_FontInfo.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_FontSystem.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_HashUtils.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_Heap.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_LanguageString.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_Loading.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_MessageQueue.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_Messages.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_MugenSound.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_Parameter.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_Path.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_Pointer.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_Regex.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_SdlManager.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_SndManager.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_SoundManager.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_StringUtils.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_Thread.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_Timedif.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_Timer.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_Token.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_TokenReader_xml.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_Utf.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_Util.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_UtilStructs.h
${CMAKE_SOURCE_DIR}/Gamecore/util/SGF_Xmltools.h
${CMAKE_SOURCE_DIR}/Gamecore/util/all_fonts.h
${CMAKE_SOURCE_DIR}/Gamecore/util/all_messages.h
${CMAKE_SOURCE_DIR}/Gamecore/util/all_sound.h
${CMAKE_SOURCE_DIR}/Gamecore/util/tokenreader.h
${CMAKE_SOURCE_DIR}/Gamecore/util/XmlNode/CmnHdr.h
${CMAKE_SOURCE_DIR}/Gamecore/util/XmlNode/Portable.h
${CMAKE_SOURCE_DIR}/Gamecore/util/XmlNode/XmlNode.h


)
set(SGF_SDLMIXER_HDRS
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/SDL_mixer.h
)
set(SGF_SDLIMAGE_HDRS
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.0/SDL_image.h  
 )
 
#BUILD png library INTERNAL 
if(PNG_INTERNAL)

endif(PNG_INTERNAL)
 
#BUILD FREETYPE LIBRARY INTERNAL
if(FREETYPE_INTERNAL)

endif(FREETYPE_INTERNAL) 
 
set(SGF_SDLTTF_HDRS
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_ttf-2.0.12/SDL_ttf.h
)
set(SGF_GFX_HDRS
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL_gfx-2.0.24/SDL_framerate.h
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL_gfx-2.0.24/SDL_gfxBlitFunc.h
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL_gfx-2.0.24/SDL_gfxPrimitives.h
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL_gfx-2.0.24/SDL_gfxPrimitives_font.h
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL_gfx-2.0.24/SDL_imageFilter.h
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL_gfx-2.0.24/SDL_rotozoom.h
)

set( SGF_COMPILER_CMD_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/compiler/CmdCompiler/cmd_driver.h
)
set( SGF_COMPILER_DEF_HDRS   
${CMAKE_SOURCE_DIR}/Gamecore/compiler/DefCompiler/def_driver.h
)
set( SGF_COMPILER_AIR_HDRS
${CMAKE_SOURCE_DIR}/Gamecore/compiler/AirCompiler/air_driver.h
)

set( SGF_HAWKNL_HDRS

${CMAKE_SOURCE_DIR}/ExternalLibs/hawknl/hawknl/group.h
${CMAKE_SOURCE_DIR}/ExternalLibs/hawknl/hawknl/hawklib.h
${CMAKE_SOURCE_DIR}/ExternalLibs/hawknl/hawknl/hawkthreads.h
${CMAKE_SOURCE_DIR}/ExternalLibs/hawknl/hawknl/htinternal.h
${CMAKE_SOURCE_DIR}/ExternalLibs/hawknl/hawknl/ipx.h
${CMAKE_SOURCE_DIR}/ExternalLibs/hawknl/hawknl/loopback.h
${CMAKE_SOURCE_DIR}/ExternalLibs/hawknl/hawknl/nl.h
${CMAKE_SOURCE_DIR}/ExternalLibs/hawknl/hawknl/nlinternal.h
${CMAKE_SOURCE_DIR}/ExternalLibs/hawknl/hawknl/parallel.h
${CMAKE_SOURCE_DIR}/ExternalLibs/hawknl/hawknl/serial.h
${CMAKE_SOURCE_DIR}/ExternalLibs/hawknl/hawknl/sock.h
${CMAKE_SOURCE_DIR}/ExternalLibs/hawknl/hawknl/wsock.h
)

set( SGF_EXPATL_HDRS
${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/lib/amigaconfig.h
${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/lib/ascii.h
${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/lib/asciitab.h
${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/lib/expat.h
${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/lib/expat_external.h
${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/lib/iasciitab.h
${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/lib/internal.h
${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/lib/latin1tab.h
${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/lib/macconfig.h
${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/lib/nametab.h
${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/lib/utf8tab.h
${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/lib/winconfig.h
${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/lib/xmlrole.h
${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/lib/xmltok.h
${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/lib/xmltok_impl.h
)
set( SGF_SGE_HDRS
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include/sge.h
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include/sge_bm_text.h
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include/sgearray.h
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include/sgecontrol.h
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include/sgedefines.h
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include/sgeevent.h
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include/sgefadefx.h
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include/sgefont.h
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include/sgegamestate.h
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include/sgegfx.h
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include/sgegp2x.h
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include/sgeinit.h
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include/sgelist.h
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include/sgemisc.h
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include/sgeparticles.h
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include/sgepathfinder.h
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include/sgeresource.h
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include/sgescreen.h
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include/sgesound.h
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include/sgesprite.h
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include/sgespritegroup.h
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include/sgespriteimage.h
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include/sgestage.h
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include/sgestring.h
)

# -------------------------------------------------------
# Put the linked libraries together
# -------------------------------------------------------
set(REQUIRED_LIBS ${GRAPHICS_LIBRARIES}  ${CMAKE_THREAD_LIBS_INIT} ${FREETYPE_LIBRARIES} 
${ZLIB_LIBRARY} ${OGG_LIBS} ${MP3_LIBS} ${WIN_LIB} ${WINSOCK}
${PERL_LIBRARIES})


# -------------------------------------------------------
# ADD SOURCE FILES OTHER THAN THE ONES IN FILELIST.CMAKE
# SGF   add_subdirectory
# Add a subdirectory to the build. The source_dir specifies the directory in which the source CMakeLists.txt and code files are located.
# -------------------------------------------------------
#add_library (main_module ${ALL_SRC})
# build directories



#expat
#add_subdirectory(${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/ConfigureChecks.cmake)
message("ADDING expat_config.h")
configure_file(${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/expat_config.h.cmake ${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/expat_config.h)
add_definitions(-DHAVE_EXPAT_CONFIG_H)
add_definitions(-DHAVE_MEMMOVE)

add_subdirectory(${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.0/external/zlib-1.2.8)
message (STATUS "WILL BUILD FREETYPE")
#add_subdirectory(${CMAKE_SOURCE_DIR}/ExternalLibs/freetype-2.9.1)

if(FREETYPE_INTERNAL)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/freetype-2.9.1/CMakeLists-sgf.txt) #(get variables needed)

include_directories( PRIVATE "${FREE_SOURCE_DIR}/include")


include_directories(${FREE_PRIVATE_HEADERS}
                    ${FREE_PUBLIC_HEADERS}
                    ${FREE_PUBLIC_CONFIG_HEADERS})
endif(FREETYPE_INTERNAL)

include(${CMAKE_SOURCE_DIR}/Source/ai/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/Source/configuration/CMakeLists.txt) #(get variables needed)
#include(${CMAKE_SOURCE_DIR}/Source/environment/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/Source/exceptions/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/Source/external/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/Source/game/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/Source/geometry/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/Source/graphics/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/Source/gui/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/Source/input/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/Source/level/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/Source/lists/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/Source/math/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/Source/menu/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/Source/mortal/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/Source/mugen/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/Source/network/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/Source/objects/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/Source/resource/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/Source/script/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/Source/sprite/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/Source/sys/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/Source/util/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/Source/windows/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/7z/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/hawknl/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/md5/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/pcre/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/sha1-c/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/zip/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/SDL_gfx-2.0.24/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/timidity/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/native_midi/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.0/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_ttf-2.0.12/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_ttf-2.0.12/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/SFL2.0src/CMakeLists.txt) #(get variables needed)

message(STATUS "ADDING SDL2 CMAKELIST.TXT")
include(${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/Source/structures/CMakeLists.txt) #(get variables needed)

if(OGG_INTERNAL)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/external/libogg-1.3.2/CMakeLists.txt) #(get variables needed from ogg)
endif(OGG_INTERNAL)
if(TIFF_INTERNAL)
add_subdirectory(${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.0/external/tiff-4.0.3)
endif(TIFF_INTERNAL)






#Minizip
#add_subdirectory(${CMAKE_SOURCE_DIR}/ExternalLibs/zip)





# source files
if(NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
    # If we're doing an out of source build and the user has a zconf.h
    # in their source tree...
    if(EXISTS ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.0/external/zlib-1.2.8/zconf.h)
        message(STATUS "Renaming")
        message(STATUS "    ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.0/external/zlib-1.2.8/zconf.h")
        message(STATUS "to 'zconf.h.included' because this file is included with zlib")
        message(STATUS "but CMake generates it automatically in the build directory.")
        file(RENAME ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.0/external/zlib-1.2.8/zconf.h ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.0/external/zlib-1.2.8/zconf.h.included)
  endif()
endif()

set(ZLIB_PC ${CMAKE_CURRENT_BINARY_DIR}/zlib.pc)
configure_file( ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.0/external/zlib-1.2.8/zlib.pc.cmakein
		${ZLIB_PC} @ONLY)
configure_file(	${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.0/external/zlib-1.2.8/zconf.h.cmakein
		${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.0/external/zlib-1.2.8/zconf.h @ONLY)



message(STATUS "Including files to build SDL: ${SDL2_SOURCE_FILES}")
message(STATUS "Including files to build EXPAT: ${expat_SRCS}")
message(STATUS "Including files to build AI module: ${AI_SRC}")
message(STATUS "Including files to build Configuration Module: ${CONFIGURATION_SRC}")
message(STATUS "Including files to build Envirownment Module: ${ENVIRONMENT_SRC}")
message(STATUS "Including files to build Exceptions Module: ${EXCEPTIONS_SRC}")
message(STATUS "Including files to build External Modue: ${EXTERNAL_SRC}")
message(STATUS "Including files to build Game Module: ${GAME_SRC}")
message(STATUS "Including files to build Graphics Module: ${GRAPHICS_SRC}")
message(STATUS "Including files to build Gui Module: ${GUI_SRC}")
message(STATUS "Including files to build Input Module: ${INPUT_SRC}")
message(STATUS "Including files to build Level Module: ${LEVEL_SRC}")
message(STATUS "Including files to build Lists Module: ${LISTS_SRC}")
message(STATUS "Including files to build Math Module: ${MATH_SRC}")
message(STATUS "Including files to build Menu Module: ${MENU_SRC}")
message(STATUS "Including files to build Mortal Module: ${MORTAL_SRC}")
message(STATUS "Including files to build Mugen Module: ${MUGEN_AST_SRC}")
message(STATUS "Including files to build Network Module: ${NETWORK_SRC}")
message(STATUS "Including files to build Objects Module: ${OBJECTS_SRC}")
message(STATUS "Including files to build Resources Module: ${RESOURCES_SRC}")
message(STATUS "Including files to build Script Module: ${SCRIPT_SRC}")
message(STATUS "Including files to build Sprte Module: ${SPRITE_SRC}")
message(STATUS "Including files to build Structures Module: ${STRUCTURES_SRC}")
message(STATUS "Including files to build Sys Module: ${SYS_SRC}")
message(STATUS "Including files to build Utils Module: ${UTIL_SRC}")
message(STATUS "Including files to build Windows Module: ${WINDOWS_SRC}")
message(STATUS "Including files to build SFL Module: ${SFL_SRC}")
message(STATUS "Including files to build FREETYPE Module: ${FREE_BASE_SRCS}")


if(OGG_INTERNAL)
message(STATUS "Including files to build OGG module: ${OGG_SRC}")
endif()
if(TIFF_INTERNAL)
message(STATUS "Including files to build TIFF module: ${TIFF_SRC_SRC}")

endif()


#${AI_SRC} ${CONFIGURATION_SRC} ${ENVIRONMENT_SRC} ${EXCEPTIONS_SRC} ${EXTERNAL_SRC}
#${GAME_SRC} ${GRAPHICS_SRC} ${GUI_SRC} ${INPUT_SRC} ${LEVEL_SRC}
#${LISTS_SRC} ${MATH_SRC} ${MENU_SRC} ${MORTAL_SRC} ${MUGEN_AST_SRC} ${NETWORK_SRC}
#${OBJECTS_SRC} ${RESOURCES_SRC} ${SCRIPT_SRC} ${SPRITE_SRC} ${STRUCTURES_SRC}
#${SYS_SRC} ${UTIL_SRC} ${WINDOWS_SRC}

# add_library(algif_module src/util/gif/algif.c src/util/gif/gif.c src/util/gif/lzw.c)

# GME Library
#add_library(gme_module src/util/sound/gme/Ay_Apu.cpp src/util/sound/gme/Ay_Cpu.cpp src/util/sound/gme/Ay_Emu.cpp src/util/sound/gme/Blip_Buffer.cpp src/util/sound/gme/Classic_Emu.cpp src/util/sound/gme/Data_Reader.cpp src/util/sound/gme/Dual_Resampler.cpp src/util/sound/gme/Effects_Buffer.cpp src/util/sound/gme/Fir_Resampler.cpp src/util/sound/gme/Gb_Apu.cpp src/util/sound/gme/Gb_Cpu.cpp src/util/sound/gme/Gb_Oscs.cpp src/util/sound/gme/Gbs_Emu.cpp src/util/sound/gme/gme.cpp src/util/sound/gme/Gme_File.cpp src/util/sound/gme/Gym_Emu.cpp src/util/sound/gme/Hes_Apu.cpp src/util/sound/gme/Hes_Cpu.cpp src/util/sound/gme/Hes_Emu.cpp src/util/sound/gme/Kss_Cpu.cpp src/util/sound/gme/Kss_Emu.cpp src/util/sound/gme/Kss_Scc_Apu.cpp src/util/sound/gme/M3u_Playlist.cpp src/util/sound/gme/Multi_Buffer.cpp src/util/sound/gme/Music_Emu.cpp src/util/sound/gme/Nes_Apu.cpp src/util/sound/gme/Nes_Cpu.cpp src/util/sound/gme/Nes_Fme7_Apu.cpp src/util/sound/gme/Nes_Namco_Apu.cpp src/util/sound/gme/Nes_Oscs.cpp src/util/sound/gme/Nes_Vrc6_Apu.cpp src/util/sound/gme/Nsfe_Emu.cpp src/util/sound/gme/Nsf_Emu.cpp src/util/sound/gme/Sap_Apu.cpp src/util/sound/gme/Sap_Cpu.cpp src/util/sound/gme/Sap_Emu.cpp src/util/sound/gme/Sms_Apu.cpp src/util/sound/gme/Snes_Spc.cpp src/util/sound/gme/Spc_Cpu.cpp src/util/sound/gme/Spc_Dsp.cpp src/util/sound/gme/Spc_Emu.cpp src/util/sound/gme/Vgm_Emu.cpp src/util/sound/gme/Vgm_Emu_Impl.cpp src/util/sound/gme/Ym2413_Emu.cpp src/util/sound/gme/Ym2612_Emu.cpp)

#Script directory
# add_subdirectory(${CMAKE_SOURCE_DIR}/Source/script)

# add_library(mugen_module ${MUGEN_SRC})
#add_library(platformer_module ${PLATFORMER_SRC})
#add_library(pcre_module ExternalLibs/pcre/pcre_chartables.c ExternalLibs/pcre/pcre_compile.c ExternalLibs/pcre/pcre_config.c ExternalLibs/pcre/pcre_dfa_exec.c ExternalLibs/pcre/pcre_exec.c ExternalLibs/pcre/pcre_fullinfo.c ExternalLibs/pcre/pcre_get.c ExternalLibs/pcre/pcre_globals.c ExternalLibs/pcre/pcre_info.c ExternalLibs/pcre/pcre_maketables.c ExternalLibs/pcre/pcre_newline.c ExternalLibs/pcre/pcre_ord2utf8.c ExternalLibs/pcre/pcreposix.c ExternalLibs/pcre/pcre_refcount.c ExternalLibs/pcre/pcre_study.c ExternalLibs/pcre/pcre_tables.c ExternalLibs/pcre/pcre_try_flipped.c ExternalLibs/pcre/pcre_ucd.c ExternalLibs/pcre/pcre_valid_utf8.c ExternalLibs/pcre/pcre_version.c ExternalLibs/pcre/pcre_xclass.c)

   # IMAGE
    #add_subdirectory(${CMAKE_SOURCE_DIR}/src/util/graphics/sdl/image)
    # SFL
    #add_subdirectory(${CMAKE_SOURCE_DIR}/src/util/sfl)
    # Stretch
    #add_subdirectory(${CMAKE_SOURCE_DIR}/src/util/graphics/sdl/stretch)
    # SPRIG
    #add_library(sprig_module src/util/graphics/sdl/sprig/SPG_extended.c src/util/graphics/sdl/sprig/SPG_primitives.c src/util/graphics/sdl/sprig/SPG_misc.c src/util/graphics/sdl/sprig/SPG_rotation.c src/util/graphics/sdl/sprig/SPG_polygon.c src/util/graphics/sdl/sprig/SPG_surface.c)
    # Mixer
    #add_subdirectory(${CMAKE_SOURCE_DIR}/src/util/sound/sdl/mixer)
    # add_library(mixer_module src/util/sound/sdl/mixer/music.c src/util/sound/sdl/mixer/mixer.c src/util/sound/sdl/mixer/music_ogg.c src/util/sound/sdl/mixer/music_flac.c src/util/sound/sdl/mixer/music_mad.c src/util/sound/sdl/mixer/dynamic_ogg.c src/util/sound/sdl/mixer/effect_position.c src/util/sound/sdl/mixer/effects_internal.c src/util/sound/sdl/mixer/effect_stereoreverse.c src/util/sound/sdl/mixer/load_voc.c src/util/sound/sdl/mixer/load_aiff.c src/util/sound/sdl/mixer/wavestream.c src/util/sound/sdl/mixer/load_ogg.c src/util/sound/sdl/mixer/convert.cpp)

    # Ensure that the extra cflags are used at compile time
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS}")

    #do not include TTF sources when there is the library
    if(!FREETYPE_INTERNAL)
        set(FREE_BASE_SRCS "")
    else()

        include_directories( PRIVATE "${CMAKE_BINARY_DIR}/include")
        include_directories( PRIVATE "${FREE_SOURCE_DIR}/include")


        include_directories(${FREE_SGF_HEADERS}
                            ${FREE_PRIVATE_HEADERS}
                            ${FREE_PUBLIC_HEADERS}
                            ${FREE_PUBLIC_CONFIG_HEADERS})

                        add_definitions(-DFT2_BUILD_LIBRARY)

 #   target_compile_definitions(
  #    sgffabric PRIVATE FT2_BUILD_LIBRARY)


    endif(!FREETYPE_INTERNAL)
#sgffabric library
# The extension is already found. Any number of sources could be listed here.
add_library (sgffabric STATIC ${CMAKE_SOURCE_DIR}/Source/SGF_Global.cpp
${FREE_BASE_SRCS}

${expat_SRCS}
${SDL2_SOURCE_FILES} ${CONFIGURATION_SRC} ${AI_SRC}  ${ENVIRONMENT_SRC} ${EXCEPTIONS_SRC} ${EXTERNAL_SRC}
${GAME_SRC} ${GRAPHICS_SRC} ${GUI_SRC} ${INPUT_SRC} ${LEVEL_SRC}
${LISTS_SRC} ${MATH_SRC} ${MENU_SRC} ${MORTAL_SRC} ${MUGEN_AST_SRC} ${NETWORK_SRC}
${OBJECTS_SRC} ${RESOURCES_SRC} ${SCRIPT_SRC} ${SPRITE_SRC} ${STRUCTURES_SRC}
${SYS_SRC} ${UTIL_SRC} ${WINDOWS_SRC}
#external Libs
${7ZIP_SRC} ${HAWKNL_SRC} ${MD5_SRC} ${PCRE_SRC} ${SGE_SRC} ${SHA_SRC} ${SFL_SRC}
${MINIZIP_SRC} ${SDLGFX_SRC} ${TIMIDITY_SRC} ${NATIVE_MIDI_SRC}
${SDLIMAGE_SRC} ${SDLMIXER_SRC} ${SDLTTF_SRC} ${OGG_SRC} ${TIFF_SRC} ${SFL_SRC}

)







# to compile 64 bit
#set_target_properties(sgffabric PROPERTIES  LINK_FLAGS "-Wl,--wrap=open -Wl,--wrap=read -Wl,--wrap=close -Wl,--wrap=lseek -Wl,--wrap=lstat -Wl,--wrap=access")

#to compile for 32bits
#set_target_properties(sgffabric PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32, -Wl,--wrap=open -Wl,--wrap=read -Wl,--wrap=close -Wl,--wrap=lseek -Wl,--wrap=lstat -Wl,--wrap=access")
#set_target_properties(sgffabric PROPERTIES COMPILE_FLAGS ${ADITIONAL_CXX_FLAGS} LINK_FLAGS "${ADITIONAL_LINK_FLAGS}, -Wl,--wrap=open -Wl,--wrap=read -Wl,--wrap=close -Wl,--wrap=lseek -Wl,--wrap=lstat -Wl,--wrap=access")

#target_link_libraries( ${GROUP_START} sdl ${GROUP_END} ${REQUIRED_LIBS})

find_package(OpenGL)
if(OPENGL_FOUND)
  include_directories(${OPENGL_INCLUDE_DIR})
  link_directories(${OPENGL_LIBRARIES})
  message (STATUS "ADDING GL Link Lybrary to target sgffabric"  )
  target_link_libraries(sgffabric ${OPENGL_LIBRARIES})
endif(OPENGL_FOUND)

set(_INSTALL_LIBS "sgffabric" ${_INSTALL_LIBS})
target_link_libraries(sgffabric ${EXTRA_LIBS} ${EXTRA_LDFLAGS})

#libc for opendir

#target_link_libraries(sgffabric -glibc)


if(OGG_INTERNAL)
set(OGG_INTERNAL_LIB "ogg_module")
else(OGG_INTERNAL)
set(OGG_INTERNAL_LIB "")
endif(OGG_INTERNAL)
if(TIFF_INTERNAL)
set(TIFF_INTERNAL_LIB "tiff_module")
else(TIFF_INTERNAL)
set(TIFF_INTERNAL_LIB "")
endif(TIFF_INTERNAL)
#add_executable (test src/test.cpp)
target_link_libraries(sgffabric zlibstatic
#sdlgfx_module
#sdlttf_module
#sdlmixer_module
#${REQUIRED_LIBS}
#${OGG_INTERNAL_LIB}
#${TIFF_INTERNAL_LIB}
)


################  EXAMPLES ##################################################
include_directories(${CMAKE_SOURCE_DIR}/Exemplos/Tutorial_01-CriarJanela/src)
add_executable (createWindow ${CMAKE_SOURCE_DIR}/Exemplos/Tutorial_01-CriarJanela/src/main.cpp ${CMAKE_SOURCE_DIR}/Exemplos/Tutorial_01-CriarJanela/src/Game.cpp)
target_link_libraries(createWindow sgffabric)




if(NOT SKIP_INSTALL_LIBRARIES AND NOT SKIP_INSTALL_ALL )
    install(TARGETS sgffabric
        RUNTIME DESTINATION "${INSTALL_BIN_DIR}"
        ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
        LIBRARY DESTINATION "${INSTALL_LIB_DIR}" )
endif()
if(NOT SKIP_INSTALL_HEADERS AND NOT SKIP_INSTALL_ALL )
    #install(FILES ${SGF_PUBLIC_HDRS} DESTINATION "${INSTALL_INC_DIR}"  RENAME sgffabric.h)
    install(FILES ${SGF_PUBLIC_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}")
    install(FILES ${SGF_AI_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/ai")
    install(FILES ${SGF_CONFIGURATION_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/configuration")
    install(FILES ${SGF_ENVIRONMENT_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/environment")
    install(FILES ${SGF_EXCEPTIONS_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/exceptions")
    install(FILES ${SGF_EXTERNAL_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/external")
    install(FILES ${SGF_GAME_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/game")
    install(FILES ${SGF_GEOMETRY_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/geometry")
    install(FILES ${SGF_GRAPHICS_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/graphics")
    install(FILES ${SGF_GUI_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/gui")
    install(FILES ${SGF_INPUT_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/input")
    install(FILES ${SGF_LEVEL_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/level")
    install(FILES ${SGF_LISTS_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/lists")
    install(FILES ${SGF_MATH_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/math")
    install(FILES ${SGF_MENU_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/menu")
    install(FILES ${SGF_MUGEN_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/mugen/Ast")
    install(FILES ${SGF_MUGEN2_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/mugen")
    install(FILES ${SGF_NETWORK_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/network")
    install(FILES ${SGF_OBJECTS_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/objects")
    install(FILES ${SGF_RESOURCE_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/resource")
    install(FILES ${SGF_SCRIPT_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/script")
    install(FILES ${SGF_SPRITE_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/sprite")
    install(FILES ${SGF_STRUCTURES_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/structures")
    install(FILES ${SGF_SYS_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/sys")
    install(FILES ${SGF_UTIL_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/util")
    install(FILES ${SGF_COMPILER_CMD_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/compiler/CmdCompiler")
    install(FILES ${SGF_COMPILER_DEF_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/compiler/DefCompiler")
    install(FILES ${SGF_COMPILER_AIR_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/compiler/AirCompiler")
    install(FILES ${SGF_SDLMIXER_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/ExternalLibs/SDL2_mixer-2.0.2")
    install(FILES ${SGF_SDLIMAGE_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/ExternalLibs/SDL2_image-2.0.0")
    install(FILES ${SGF_SDLTTF_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/ExternalLibs/SDL2_ttf-2.0.12")
    install(FILES ${SGF_GFX_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/ExternalLibs/SDL_gfx-2.0.24")
    install(FILES ${SGF_HAWKNL_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/ExternalLibs/hawknl/hawknl")
    install(FILES ${SGF_EXPATL_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/ExternalLibs/expat-2.1.0/lib")
    install(FILES ${SGF_SGE_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/ExternalLibs/sge2d/include") 
endif()
#man
if(NOT SKIP_INSTALL_FILES AND NOT SKIP_INSTALL_ALL )
   # install(FILES sgf.3 DESTINATION "${INSTALL_MAN_DIR}/man3")
endif()


#add_executable (menutest src/menu/menutest.cpp)
#target_link_libraries(menutest main_module dumb_module hawknl_module ${REQUIRED_LIBS})

#if (NOT USE_SDL)
#    add_executable (mugentest src/mugen/test.cpp)
#    target_link_libraries(mugentest ${GROUP_START} base_module level_module factory_module object_module util_module loadpng_module 
#        menu_module env_module network_module gui_module script_module game_module mugen_module ogg_module trigger_module pcre_module dumb_module hawknl_module gme_module ${GROUP_END} ${REQUIRED_LIBS})
#endif (NOT USE_SDL)


