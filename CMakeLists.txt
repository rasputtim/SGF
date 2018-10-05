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

#enable incremental builiding
set (CMAKE_SKIP_RULE_DEPENDENCY TRUE)

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
    add_definitions(-DANDROID)
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
message (STATUS "Build PNG SUPPORT FOR ANDROID")
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
message (STATUS:  "SGF WILL LOOK FOR LIBRARIES INSTALLED IN THE SYSTEM")
#find_package(ZLIB)  FindZLIB-SGF.cmake
include(FindZLIB-SGF)
find_package(FREETYPE)
find_package(PNG)
find_package(JPEG9)
if(NOT ANDROID)
find_package(TIFF)
endif()
include(FindWEBP)
find_package(Threads)
find_package(VORBIS)
find_package(OGG)
find_package(MPG123)
FIND_PACKAGE (Perl)
FIND_PACKAGE (PerlLibs)



# -------------------------------------------------------
# Include Source Files
# I do not use the CMakeFile.txt of the subfolders.
#Except for modules OGG anf TIFF
# All source files are listed in this file
# that is i do not use sub modules. maybe I will change this in future
# -------------------------------------------------------
#include(FileList)

#TURN BACK ADVANCED VARIABLES, MAKING THEM AVAILABLE TO INCLUDED SUBDIRS
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

            #with warnings
            #set(CMAKE_CXX_FLAGS "-Wall -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -funroll-loops -fexpensive-optimizations -Woverloaded-virtual -g3 -ggdb -std=c++11 -msse3")
            #set(CMAKE_C_FLAGS "-Wall -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -funroll-loops -fexpensive-optimizations -g3 -ggdb -msse3")
            #no warnings
            set(CMAKE_CXX_FLAGS "-w -funroll-loops -fexpensive-optimizations -Woverloaded-virtual -g3 -ggdb -std=c++11 -msse3")
            set(CMAKE_C_FLAGS "-w -funroll-loops -fexpensive-optimizations -g3 -ggdb -msse3")

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

message (STATUS "###########################################################")
message (STATUS "########  SET FLAGS FOR THE NEEDED SEARCHED LIBS      #####")
message (STATUS "########  CHECK IF WE WILL BUID THEM OR NOT           #####")
message (STATUS "###########################################################")



message(STATUS "ZLIB_INCLUDE_DIR: ${ZLIB_INCLUDE_DIR}")

if(PNG_FOUND)
    message(STATUS "LIB PNG found to use with SDL2_image.")
    add_definitions(-DHAVE_PNG)
    set(PNG_DEFINITIONS "")
    message (STATUS "PNG FOUND VERSION: ${PNG_VERSION_STRING}")
else(PNG_FOUND)
    add_definitions(-DHAVE_PNG)
    message(STATUS "LIB PNG NOT found to use for SDL2_image. I Will build PNG internally")
    set(PNG_LIBRARY "png_static")
    set(PNG_PNG_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.3/external/libpng-1.6.32")
    message(STATUS "PNG_PNG_INCLUDE_DIR: ${PNG_PNG_INCLUDE_DIR}")
    set(PNG_INTERNAL ON)
endif(PNG_FOUND)


#if(NOT ANDROID)
    if(TIFF_FOUND)
        if(NOT ANDROID)
        add_definitions(-DLOAD_TIF)
        #add_definitions(-LOAD_TIF_DYNAMIC="libtiff-5.dll")
        endif()
        set(TIFF_LIBRARY ${TIFF_LIBRARY} ${TIFF_LIBRARIES})
        set(TIFF_INTERNAL OFF)
        message(STATUS "LIB TIFF found to use with SDL2_image.")
        set(TIFF_SRC "")
    else(TIFF_FOUND)
        #use internal tiff_module
        if(NOT ANDROID)
        add_definitions(-DLOAD_TIF)
        #add_definitions(-LOAD_TIF_DYNAMIC="libtiff-5.dll")
        endif()
        message(STATUS "LIB TIFF not found. I Will build tiff internally.")
        set(TIFF_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.3/external/tiff-4.0.8/libtiff/)
        set(TIFF_LIBRARY "tiff")
        set(TIFF_INTERNAL ON)
    endif(TIFF_FOUND)
#endif()


if(JPEG9_FOUND)
    message(STATUS "LIB jpeg9 found to use with SDL2_image.")
    add_definitions(-DHAVE_JPEG)
    set(JPEG_LIBRARY ${JPEG9_LIBRARY})
    set(JPEG_INCLUDE_DIR ${JPEG9_INCLUDE_DIR})
else(JPEG9_FOUND)
    add_definitions(-DHAVE_JPEG)
    message(STATUS "LIB jpeg9 NOT found to use with SDL2_image. I Will build jpeg internally")
    set(JPEG_LIBRARY "jpeg_static")
    set(JPEG_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.3/external/jpeg-9b/")
    set(JPEG_INTERNAL ON)
endif(JPEG9_FOUND)


if(WEBP_FOUND)
    message(STATUS "LIB WEBP found to use with SDL2_image.")
    add_definitions(-DHAVE_WEBP)
    set(WEBP_DEFINITIONS "")
    set(WEBP_LIBRARY ${WEBP_LIBRARY})
    set(WEBP_INCLUDE_DIR ${WEBP_INCLUDE_DIR})

else(WEBP_FOUND)
    message(STATUS "LIB WEBP NOT found to use with SDL2_image. I Will build WEBP internally")
    set(WEBP_LIBRARY "")
    set(WEBP_INCLUDE_DIR "")
    set(WEBP_INTERNAL ON)
endif(WEBP_FOUND)



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
    message(STATUS "LIB OGG NOT found to use with SDL2_MIXER. I Will build ogg internally")
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
        if(EXISTS ${CMAKE_SOURCE_DIR}/ExternalLibs/freetype-2.9.1/include/ft2build.h)
            file(RENAME ${CMAKE_SOURCE_DIR}/ExternalLibs/freetype-2.9.1/include/ft2build.h  ${CMAKE_SOURCE_DIR}/ExternalLibs/freetype-2.9.1/include/ft2build-orig.h )
        endif()
        set(FREETYPE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/freetype-2.9.1/include
            ${PROJECT_BINARY_DIR}/include/freetype/config)
        #set(FREETYPE_INCLUDE_DIR ${PROJECT_BINARY_DIR}/include/freetype/config)
    set(FREETYPE_LIBS "")
    set(FREETYPE_INTERNAL ON)
endif(NOT FREETYPE_FOUND)




message (STATUS "###########################################################")
message (STATUS "########  SET PATH AND SYSTEM SETUP                   #####")
message (STATUS "###########################################################")


#-------------------------------------------------------
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


message (STATUS "###########################################################")
message (STATUS "########   ADDING PRE-PROCESSOR COMPILE DEFINITIONS   #####")
message (STATUS "###########################################################")


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



message (STATUS "###########################################################")
message (STATUS "########   INCLUDING FOLDERS AND FILES                #####")
message (STATUS "###########################################################")


# -------------------------------------------------------
# Include directory & Files
# List of preprocessor include file search directories.
# -------------------------------------------------------

if (PERLLIBS_FOUND)
include_directories(${CMAKE_SOURCE_DIR}/ExternalLibs/perl56
${PERL_INCLUDE_DIR}
${PERL_INCLUDE_DIRS}
)
endif()

if(FREETYPE_INTERNAL)
include_directories(${CMAKE_SOURCE_DIR}/ExternalLibs/ExternalLibs/freetype-2.9.1/include/
${FREETYPE_INCLUDE_DIR})
endif()

if(WEBP_INTERNAL)
    include_directories(${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.3/external/libwebp-0.6.0/src)
else(WEBP_INTERNAL)
    include_directories(${WEBP_INCLUDE_DIR})
endif(WEBP_INTERNAL)


# ZLIB
include_directories(${ZLIB_INCLUDE_DIRS})




message(STATUS "PNG_PNG_INCLUDE_DIR: ${PNG_PNG_INCLUDE_DIR}")
if(PNG_INTERNAL)
    include_directories(${PNG_PNG_INCLUDE_DIR})
else(PNG_INTERNAL)
    include_directories(${PNG_PNG_INCLUDE_DIR})
endif(PNG_INTERNAL)


include_directories(${CMAKE_SOURCE_DIR}/Gamecore
${CMAKE_SOURCE_DIR}/Gamecore/compiler
${CMAKE_SOURCE_DIR}/Header
${CMAKE_SOURCE_DIR}/ExternalLibs/7z
${CMAKE_SOURCE_DIR}/ExternalLibs/hawkln
${CMAKE_SOURCE_DIR}/ExternalLibs/md5
${CMAKE_SOURCE_DIR}/ExternalLibs/pcre
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_SGF
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2/include
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL_gfx-2.0.24
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.3
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/timidity
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/native_midi
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/external
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_ttf-2.0.12
${CMAKE_SOURCE_DIR}/ExternalLibs/SFL2.0src
${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/include
${CMAKE_SOURCE_DIR}/ExternalLibs/sha1-c
${CMAKE_SOURCE_DIR}/ExternalLibs/zip
${GRAPHICS_INCLUDES}
${OGG_INCLUDES}
${MP3_INCLUDES}
${JPEG_INCLUDE_DIR}
${TIFF_INCLUDE_DIR}# todo: Build the library
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/external/libvorbisidec-1.2.1
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/external/smpeg2-2.0.0
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/external/flac-1.2.1
${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/external/libmikmod-3.1.12/include/
#expat
${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/lib/
${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/
)

# -------------------------------------------------------
# Put the linked libraries together
# -------------------------------------------------------
#set(REQUIRED_LIBS ${GRAPHICS_LIBRARIES}  ${CMAKE_THREAD_LIBS_INIT} ${FREETYPE_LIBRARIES}
#${ZLIB_LIBRARY} ${OGG_LIBS} ${MP3_LIBS} ${WIN_LIB} ${WINSOCK}
#${PERL_LIBRARIES})

# -------------------------------------------------------
# Instalation HEADER Files used in the install target
# -------------------------------------------------------

#include(sgf_install_headers.cmake)
# -------------------------------------------------------
# generated Header Files
# -------------------------------------------------------
if(!ZLIB_FOUND)
    if(NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
        # If we're doing an out of source build and the user has a zconf.h
        # in their source tree...
        if(EXISTS ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.3/external/zlib-1.2.11/zconf.h)
            message(STATUS "Renaming")
            message(STATUS "    ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.3/external/zlib-1.2.11/zconf.h")
            message(STATUS "to 'zconf.h.included' because this file is included with zlib")
            message(STATUS "but CMake generates it automatically in the build directory.")
            file(RENAME ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.3/external/zlib-1.2.11/zconf.h ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.3/external/zlib-1.2.11/zconf.h.included)
      endif()
    endif()
endif(!ZLIB_FOUND)




# -------------------------------------------------------
# ADD SOURCE FILES OTHER THAN THE ONES IN FILELIST.CMAKE
# SGF   add_subdirectory
# Add a subdirectory to the build. The source_dir specifies the directory in which the source CMakeLists.txt and code files are located.
# -------------------------------------------------------

## For compiling MUGEN COmpilers
set(COMPILERS_MUGEN_DIR ${CMAKE_SOURCE_DIR}/Gamecore/compiler )
set(COMPILERS_MUGEN_HDR
${COMPILERS_MUGEN_DIR}/AirCompiler/airparser.tab.h
${COMPILERS_MUGEN_DIR}/AirCompiler/air_driver.h
${COMPILERS_MUGEN_DIR}/AirCompiler/airScanner.h
${COMPILERS_MUGEN_DIR}/CMDCompiler/cmdparser.tab.h
${COMPILERS_MUGEN_DIR}/CMDCompiler/cmdScanner.h
${COMPILERS_MUGEN_DIR}/CMDCompiler/cmd_driver.h
${COMPILERS_MUGEN_DIR}/CMDCompiler/comScanner.h
${COMPILERS_MUGEN_DIR}/CMDCompiler/SGF_CMDFlexLexer.h
${COMPILERS_MUGEN_DIR}/COMCompiler/comparser.tab.h
${COMPILERS_MUGEN_DIR}/COMCompiler/comScanner.h
${COMPILERS_MUGEN_DIR}/COMCompiler/com_driver.h
${COMPILERS_MUGEN_DIR}/COMCompiler/SGF_COMFlexLexer.h
${COMPILERS_MUGEN_DIR}/DefCompiler/defparser.tab.h
${COMPILERS_MUGEN_DIR}/DefCompiler/defScanner.h
${COMPILERS_MUGEN_DIR}/DefCompiler/def_driver.h
${COMPILERS_MUGEN_DIR}/DefCompiler/SGF_DEFFlexLexer.h)

set(COMPILERS_MUGEN_SRC
${COMPILERS_MUGEN_DIR}/AirCompiler/airparser.tab.cpp
${COMPILERS_MUGEN_DIR}/AirCompiler/air_driver.cc
${COMPILERS_MUGEN_DIR}/AirCompiler/lex.Air.cc
${COMPILERS_MUGEN_DIR}/CMDCompiler/cmdparser.tab.cpp
${COMPILERS_MUGEN_DIR}/CMDCompiler/cmd_driver.cc
${COMPILERS_MUGEN_DIR}/CMDCompiler/lex.Cmd.cc
${COMPILERS_MUGEN_DIR}/COMCompiler/comparser.tab.cpp
${COMPILERS_MUGEN_DIR}/COMCompiler/com_driver.cc
${COMPILERS_MUGEN_DIR}/COMCompiler/lex.Com.cc
${COMPILERS_MUGEN_DIR}/DefCompiler/defparser.tab.cpp
${COMPILERS_MUGEN_DIR}/DefCompiler/def_driver.cc
${COMPILERS_MUGEN_DIR}/DefCompiler/lex.Def.cc
)


message (STATUS "###########################################################")
message (STATUS "########   ADDING SUB DIRECTORIES                 #####")
message (STATUS "########   INCLUDING CHILD CMakeFile.txt          #####")
message (STATUS "###########################################################")



message (STATUS "########   EXPAT   #####")

#expat
#add_subdirectory(${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/ConfigureChecks.cmake)
message("ADDING expat_config.h")
configure_file(${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/expat_config.h.cmake ${CMAKE_SOURCE_DIR}/ExternalLibs/expat-2.1.0/expat_config.h)
add_definitions(-DHAVE_EXPAT_CONFIG_H)
add_definitions(-DHAVE_MEMMOVE)

message (STATUS "########   SDL_IMAGE   #####")

if(EXISTS ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.3/external/zlib-1.2.11/zconf.h)
        file(REMOVE ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.3/external/zlib-1.2.11/zconf.h)
endif(EXISTS ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.3/external/zlib-1.2.11/zconf.h)

add_subdirectory(${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.3/external/zlib-1.2.11)
message (STATUS "WILL BUILD FREETYPE")
#add_subdirectory(${CMAKE_SOURCE_DIR}/ExternalLibs/freetype-2.9.1)


message (STATUS "########   SGF INTERNAL   #####")

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

include(${CMAKE_SOURCE_DIR}/Source/util/CMakeLists.txt) #(get variables needed)
if(NOT ANDROID)
    include(${CMAKE_SOURCE_DIR}/Source/sys/CMakeLists.txt) #(get variables needed)
    include(${CMAKE_SOURCE_DIR}/Source/windows/CMakeLists.txt) #(get variables needed)
endif()
include(${CMAKE_SOURCE_DIR}/Source/structures/CMakeLists.txt) #(get variables needed)

message (STATUS "########   OTHER EXTERNAL LIBS    #####")

include(${CMAKE_SOURCE_DIR}/ExternalLibs/7z/CMakeLists.txt) #(get variables needed)
if(NOT ANDROID)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/hawknl/CMakeLists.txt) #(get variables needed)
endif()
include(${CMAKE_SOURCE_DIR}/ExternalLibs/md5/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/pcre/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/sha1-c/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/zip/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/SDL_gfx-2.0.24/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/timidity/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/native_midi/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.3/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_ttf-2.0.12/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_ttf-2.0.12/CMakeLists.txt) #(get variables needed)
include(${CMAKE_SOURCE_DIR}/ExternalLibs/SFL2.0src/CMakeLists.txt) #(get variables needed)

message (STATUS "########   SDL2    #####")
message(STATUS "ZLIB_FOUND HERE is:  ${ZLIB_FOUND}")
include(${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2/CMakeLists.txt) #(get variables needed)
add_library(sdl2_static STATIC ${SDL2_SOURCE_FILES})
target_link_libraries(sdl2_static ${EXTRA_LIBS})

message (STATUS "########   FREETYPE   #####")


if(FREETYPE_INTERNAL)
message(STATUS "ZLIB_FOUND HERE is:  ${ZLIB_FOUND}")
include(${CMAKE_SOURCE_DIR}/ExternalLibs/freetype-2.9.1/CMakeLists-sgf.txt) #(get variables needed)
add_library( freetype_static STATIC
    ${FREE_PRIVATE_HEADERS}
    ${FREE_PUBLIC_HEADERS}
    ${FREE_PUBLIC_CONFIG_HEADERS}
    ${FREE_BASE_SRCS}    )
#include_directories( PRIVATE "${FREE_SOURCE_DIR}/include")

endif(FREETYPE_INTERNAL)

message (STATUS "########   JPEG   #####")

if(JPEG_INTERNAL)
include(${JPEG_INCLUDE_DIR}/CMakeLists.txt) #(get variables needed)
include_directories( PRIVATE ${JPEG_DIR})
endif(JPEG_INTERNAL)

 message (STATUS "########   OGG   #####")
if(OGG_INTERNAL)
    include(${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2/external/libogg-1.3.2/CMakeLists.txt) #(get variables needed from ogg)
endif(OGG_INTERNAL)




#if(NOT ANDROID)
    message (STATUS "########   TIFF   #####")
    if(TIFF_INTERNAL)
        add_subdirectory(${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.3/external/tiff-4.0.8/)
    endif(TIFF_INTERNAL)
#endif()

 message (STATUS "########   PNG   #####")
if(PNG_INTERNAL)
add_subdirectory(${PNG_PNG_INCLUDE_DIR})
endif(PNG_INTERNAL)

 message (STATUS "########   WEBP   #####")

if(WEBP_INTERNAL)
add_subdirectory(${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.3/external/libwebp-0.6.0/)
endif(WEBP_INTERNAL)








message (STATUS "###########################################################")
message (STATUS "########   ADDING SOURCE FILES TO BUILD THE LIB       #####")
message (STATUS "###########################################################")


message(STATUS "Including files to build SDL: ${SDL2_SOURCE_FILES}")
#message(STATUS "Including files to build EXPAT: ${expat_SRCS}")
message(STATUS "Including files to build AI module: ${AI_SRC}")
message(STATUS "Including files to build Configuration Module: ${CONFIGURATION_SRC}")
message(STATUS "Including files to build Envirownment Module: ${ENVIRONMENT_SRC}")
#message(STATUS "Including files to build Exceptions Module: ${EXCEPTIONS_SRC}")
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
message(STATUS "Including files to build Network Hawknl Module: ${HAWKNL_SRC}")
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
message(STATUS "Including files to build JPEG Module: ${JPEG_SRC}")

if(OGG_INTERNAL)
message(STATUS "Including files to build OGG module: ${OGG_SRC}")
endif()
if(NOT ANDROID)
    if(TIFF_INTERNAL)
        message(STATUS "Including files to build TIFF module: ${TIFF_SRC_SRC}")
    endif()
endif()



# Ensure that the extra cflags are used at compile time
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS}")

#do not include TTF sources when there is the library
if(!FREETYPE_INTERNAL)
        set(FREE_BASE_SRCS "")
        set(FREE_PRIVATE_HEADERS "")
        set(FREE_PUBLIC_HEADERS "")
        set(FREE_PUBLIC_CONFIG_HEADERS "")

else()

        include_directories( PRIVATE "${CMAKE_BINARY_DIR}/include")
        #include_directories( PRIVATE "${FREE_SOURCE_DIR}/include")

        add_definitions(-DFT2_BUILD_LIBRARY)


endif(!FREETYPE_INTERNAL)

if(!JPEG_INTERNAL)
        set(JPEG_SRC "")
else()
endif(!JPEG_INTERNAL)



if(ANDROID)
#set(COMPILERS_MUGEN_SRC "")
set(NETWORK_SRC "")
set(WINDOWS_SRC "")
set(SYS_SRC "")
set (HAWKNL_SRC "")
endif(ANDROID)

message (STATUS "###########################################################")
message (STATUS "########   ADDING TARGETS                             #####")
message (STATUS "###########################################################")

set(SGF_EXTRA_LIBS ${EXTRA_LIBS} freetype_static 7zip_module minizip_module exceptions_module configuration_module util_module)

message(STATUS "")
message(STATUS " CFLAGS:        ${CMAKE_C_FLAGS}")
message(STATUS " CXXFLAGS:      ${CMAKE_CXX_FLAGS}")
message(STATUS " EXTRA_CFLAGS:  ${EXTRA_CFLAGS}")
message(STATUS " EXTRA_CXXFLAGS:  ${EXTRA_CXXFLAGS}")
message(STATUS " EXTRA_LDFLAGS: ${EXTRA_LDFLAGS}")
message(STATUS " EXTRA_LIBS:    ${EXTRA_LIBS}")
message(STATUS " SGF_EXTRA_LIBS:    ${SGF_EXTRA_LIBS}")
message(STATUS "")
message(STATUS " Build Shared Library: ${SGF_SHARED}")
message(STATUS " Build Static Library: ${SGF_STATIC}")




#sgffabric library
# The extension is already found. Any number of sources could be listed here.
add_library (sgffabric STATIC ${CMAKE_SOURCE_DIR}/Source/SGF_Global.cpp
#for freetype
#${FREE_PRIVATE_HEADERS}
#${FREE_PUBLIC_HEADERS}
#${FREE_PUBLIC_CONFIG_HEADERS}
#${FREE_BASE_SRCS}
#end freetype
${COMPILERS_MUGEN_SRC}

 ${AI_SRC}  ${ENVIRONMENT_SRC}
${GAME_SRC}  ${GUI_SRC} ${INPUT_SRC} ${LEVEL_SRC}
${LISTS_SRC}  ${MENU_SRC} ${MORTAL_SRC} ${MUGEN_AST_SRC}
${OBJECTS_SRC} ${RESOURCES_SRC} ${SCRIPT_SRC} ${SPRITE_SRC} ${STRUCTURES_SRC}
 ${WINDOWS_SRC}
 #external Libs
  ${MD5_SRC} ${PCRE_SRC} ${SGE_SRC} ${SHA_SRC}
${SDLGFX_SRC} ${TIMIDITY_SRC} ${NATIVE_MIDI_SRC}
${SDLIMAGE_SRC} ${SDLTTF_SRC} ${OGG_SRC}
${JPEG_SRC}
${CONFIGURATION_SRC}
#${UTIL_SRC} ${MINIZIP_SRC} ${7ZIP_SRC} ${SFL_SRC} ${expat_SRCS} ${SDLMIXER_SRC} ${SFL_SRC}}${SDL2_SOURCE_FILES}
${EXTERNAL_SRC} ${MATH_SRC} ${SYS_SRC} ${GRAPHICS_SRC} ${NETWORK_SRC} ${HAWKNL_SRC}
)







# to compile 64 bit
#set_target_properties(sgffabric PROPERTIES  LINK_FLAGS "-Wl,--wrap=open -Wl,--wrap=read -Wl,--wrap=close -Wl,--wrap=lseek -Wl,--wrap=lstat -Wl,--wrap=access")

#to compile for 32bits
#set_target_properties(sgffabric PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32, -Wl,--wrap=open -Wl,--wrap=read -Wl,--wrap=close -Wl,--wrap=lseek -Wl,--wrap=lstat -Wl,--wrap=access")
#set_target_properties(sgffabric PROPERTIES COMPILE_FLAGS ${ADITIONAL_CXX_FLAGS} LINK_FLAGS "${ADITIONAL_LINK_FLAGS}, -Wl,--wrap=open -Wl,--wrap=read -Wl,--wrap=close -Wl,--wrap=lseek -Wl,--wrap=lstat -Wl,--wrap=access")

#target_link_libraries( ${GROUP_START} sdl ${GROUP_END} ${REQUIRED_LIBS})

if(PERLLIBS_FOUND)
    include_directories(${PERL_INCLUDE_PATH})
    message (STATUS "ADDING Perl Link Lybrary to target sgffabric"  )
    target_link_libraries(sgffabric ${PERL_LIBRARY})
endif()



set(_INSTALL_LIBS "sgffabric" ${_INSTALL_LIBS})
target_link_libraries(sgffabric sdl2_static ${SGF_EXTRA_LIBS} ${EXTRA_LDFLAGS})

#libc for opendir

#target_link_libraries(sgffabric -glibc)


if(OGG_INTERNAL)
set(OGG_INTERNAL_LIB "ogg_module")
else(OGG_INTERNAL)
set(OGG_INTERNAL_LIB "")
endif(OGG_INTERNAL)

if(NOT ANDROID)
    if(TIFF_INTERNAL)
            #set(TIFF_LIBRARY "tiff_module")
            #if(EXISTS ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.3/external/tiff-4.0.8/libtiff/tif_config.h)
            #        file(REMOVE ${CMAKE_SOURCE_DIR}ExternalLibs/SDL2_image-2.0.3/external/tiff-4.0.8/libtiff/tif_config.h)
            #endif(EXISTS ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.3/external/tiff-4.0.8/libtiff/tif_config.h)
            #if(EXISTS ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.3/external/tiff-4.0.8/libtiff/tiffconf.h)
            #        file(REMOVE ${CMAKE_SOURCE_DIR}ExternalLibs/SDL2_image-2.0.3/external/tiff-4.0.8/libtiff/tiffconf.h)
            #endif(EXISTS ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.3/external/tiff-4.0.8/libtiff/tiffconf.h)

    else(TIFF_INTERNAL)

    endif(TIFF_INTERNAL)
else()
set(TIFF_LIBRARY "")
endif()
#add_executable (test src/test.cpp)
target_link_libraries(sgffabric ${ZLIB_LIBRARIES} webp ${PNG_LIBRARY} ${TIFF_LIBRARY} ${JPEG_LIBRARY})


if(ANDROID)
      find_library(OpenGLES1_LIBRARY GLESv1_CM)
      find_library(OpenGLES2_LIBRARY GLESv2)
      target_link_libraries(sgffabric ${OpenGLES1_LIBRARY} ${OpenGLES2_LIBRARY})

else()
find_package(OpenGL)
if(OPENGL_FOUND)
  include_directories(${OPENGL_INCLUDE_DIR})
  link_directories(${OPENGL_LIBRARIES})
  message (STATUS "ADDING GL Link Lybrary to target sgffabric"  )
  target_link_libraries(sgffabric ${OPENGL_LIBRARIES})
endif(OPENGL_FOUND)
endif()


################  EXAMPLES ##################################################
#if(!ANDROID)
include_directories(${CMAKE_SOURCE_DIR}/Exemplos/Tutorial_01-CriarJanela/src)
add_executable (createWindow ${CMAKE_SOURCE_DIR}/Exemplos/Tutorial_01-CriarJanela/src/main.cpp ${CMAKE_SOURCE_DIR}/Exemplos/Tutorial_01-CriarJanela/src/Game.cpp)
target_link_libraries(createWindow sgffabric)


#endif()



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
    install(FILES ${SGF_SDLIMAGE_HDRS} DESTINATION "${INSTALL_INC_DIR}/${INSTALL_PREFIX}/ExternalLibs/SDL2_image-2.0.3")
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

