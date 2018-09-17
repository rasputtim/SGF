# -------------------------------------------------------
# hawknl cmake build script for sgffabric.
# Written by: Salvatore
# -------------------------------------------------------


set(SDL2_SOURCE_DIR "../SDL2")



# Compiler info
if(CMAKE_COMPILER_IS_GNUCC)
  set(USE_GCC TRUE)
  set(OPT_DEF_ASM TRUE)
elseif(CMAKE_C_COMPILER_ID MATCHES "Clang")
  set(USE_CLANG TRUE)
  set(OPT_DEF_ASM TRUE)
elseif(MSVC_VERSION GREATER 1400) # VisualStudio 8.0+
  set(OPT_DEF_ASM TRUE)
  #set(CMAKE_C_FLAGS "/ZI /WX- /
else()
  set(OPT_DEF_ASM FALSE)
endif()

if(USE_GCC OR USE_CLANG)
  set(OPT_DEF_GCC_ATOMICS ON)
endif()

# Default flags, if not set otherwise
if("$ENV{CFLAGS}" STREQUAL "")
  if(CMAKE_BUILD_TYPE STREQUAL "")
    if(USE_GCC OR USE_CLANG)
      set(CMAKE_C_FLAGS "-g -O3")
    endif()
  endif()
else()
  set(CMAKE_C_FLAGS "$ENV{CFLAGS}")
  list(APPEND EXTRA_CFLAGS "$ENV{CFLAGS}")
endif()
if(NOT ("$ENV{CFLAGS}" STREQUAL "")) # Hackish, but does the trick on Win32
  list(APPEND EXTRA_LDFLAGS "$ENV{LDFLAGS}")
endif()



# Those are used for pkg-config and friends, so that the SDL2.pc, sdl2-config,
# etc. are created correctly.
set(SDL_LIBS "-lSDL2")
set(SDL_CFLAGS "")

# Emscripten toolchain has a nonempty default value for this, and the checks 
# in this file need to change that, so remember the original value, and 
# restore back to that afterwards. For check_function_exists() to work in
# Emscripten, this value must be at its default value.
set(ORIG_CMAKE_REQUIRED_FLAGS ${CMAKE_REQUIRED_FLAGS})

if(CYGWIN)
  # We build SDL on cygwin without the UNIX emulation layer
  include_directories("-I/usr/include/mingw")
  set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} -mno-cygwin")
  check_c_source_compiles("int main(int argc, char **argv) {}"
    HAVE_GCC_NO_CYGWIN)
  set(CMAKE_REQUIRED_FLAGS ${ORIG_CMAKE_REQUIRED_FLAGS})
  if(HAVE_GCC_NO_CYGWIN)
    list(APPEND EXTRA_LDFLAGS "-mno-cygwin")
    list(APPEND SDL_LIBS "-mno-cygwin")
  endif()
  set(SDL_CFLAGS "${SDL_CFLAGS} -I/usr/include/mingw")
endif()

add_definitions(-DUSING_GENERATED_CONFIG_H)
# General includes
include_directories(${SDL2_BINARY_DIR}/include ${SDL2_SOURCE_DIR}/include)
if(USE_GCC OR USE_CLANG)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -idirafter ${SDL2_SOURCE_DIR}/src/video/khronos")
else()
  include_directories(${SDL2_SOURCE_DIR}/src/video/khronos)
endif()

# All these ENABLED_BY_DEFAULT vars will default to ON if not specified, so
#  you only need to have a platform override them if they are disabling.
set(OPT_DEF_ASM TRUE)
if(EMSCRIPTEN)
  # Set up default values for the currently supported set of subsystems:
  # Emscripten/Javascript does not have assembly support, a dynamic library 
  # loading architecture, low-level CPU inspection or multithreading.
  set(OPT_DEF_ASM FALSE)
  set(SDL_SHARED_ENABLED_BY_DEFAULT OFF)
  set(SDL_ATOMIC_ENABLED_BY_DEFAULT OFF)
  set(SDL_THREADS_ENABLED_BY_DEFAULT OFF)
  set(SDL_LOADSO_ENABLED_BY_DEFAULT OFF)
  set(SDL_CPUINFO_ENABLED_BY_DEFAULT OFF)
  set(SDL_DLOPEN_ENABLED_BY_DEFAULT OFF)
endif()

if (NOT DEFINED SDL_SHARED_ENABLED_BY_DEFAULT)
    set(SDL_SHARED_ENABLED_BY_DEFAULT ON)
endif()

set(SDL_SUBSYSTEMS
    Atomic Audio Video Render Events Joystick Haptic Power Threads Timers
    File Loadso CPUinfo Filesystem Dlopen)
foreach(_SUB ${SDL_SUBSYSTEMS})
  string(TOUPPER ${_SUB} _OPT)
  if (NOT DEFINED SDL_${_OPT}_ENABLED_BY_DEFAULT)
    set(SDL_${_OPT}_ENABLED_BY_DEFAULT ON)
  endif()
  option(SDL_${_OPT} "Enable the ${_SUB} subsystem" ${SDL_${_OPT}_ENABLED_BY_DEFAULT})
endforeach()

option_string(ASSERTIONS "Enable internal sanity checks (auto/disabled/release/enabled/paranoid)" "auto")
#set_option(DEPENDENCY_TRACKING "Use gcc -MMD -MT dependency tracking" ON)
set_option(LIBC                "Use the system C library" ${OPT_DEF_LIBC})
set_option(GCC_ATOMICS         "Use gcc builtin atomics" ${OPT_DEF_GCC_ATOMICS})
set_option(ASSEMBLY            "Enable assembly routines" ${OPT_DEF_ASM})
set_option(SSEMATH             "Allow GCC to use SSE floating point math" ${OPT_DEF_SSEMATH})
set_option(MMX                 "Use MMX assembly routines" ${OPT_DEF_ASM})
set_option(3DNOW               "Use 3Dnow! MMX assembly routines" ${OPT_DEF_ASM})
set_option(SSE                 "Use SSE assembly routines" ${OPT_DEF_ASM})
set_option(SSE2                "Use SSE2 assembly routines" ${OPT_DEF_SSEMATH})
set_option(SSE3                "Use SSE3 assembly routines" ${OPT_DEF_SSEMATH})
set_option(ALTIVEC             "Use Altivec assembly routines" ${OPT_DEF_ASM})
set_option(DISKAUDIO           "Support the disk writer audio driver" ON)
set_option(DUMMYAUDIO          "Support the dummy audio driver" ON)
set_option(VIDEO_DIRECTFB      "Use DirectFB video driver" OFF)
dep_option(DIRECTFB_SHARED     "Dynamically load directfb support" ON "VIDEO_DIRECTFB" OFF)
set_option(VIDEO_DUMMY         "Use dummy video driver" ON)
set_option(VIDEO_OPENGL        "Include OpenGL support" ON)
set_option(VIDEO_OPENGLES      "Include OpenGL ES support" ON)
set_option(PTHREADS            "Use POSIX threads for multi-threading" ${SDL_PTHREADS_ENABLED_BY_DEFAULT})
dep_option(PTHREADS_SEM        "Use pthread semaphores" ON "PTHREADS" OFF)
set_option(SDL_DLOPEN          "Use dlopen for shared object loading" ${SDL_DLOPEN_ENABLED_BY_DEFAULT})
set_option(OSS                 "Support the OSS audio API" ${UNIX_SYS})
set_option(ALSA                "Support the ALSA audio API" ${UNIX_SYS})
dep_option(ALSA_SHARED         "Dynamically load ALSA audio support" ON "ALSA" OFF)
set_option(JACK                "Support the JACK audio API" ${UNIX_SYS})
dep_option(JACK_SHARED         "Dynamically load JACK audio support" ON "JACK" OFF)
set_option(ESD                 "Support the Enlightened Sound Daemon" ${UNIX_SYS})
dep_option(ESD_SHARED          "Dynamically load ESD audio support" ON "ESD" OFF)
set_option(PULSEAUDIO          "Use PulseAudio" ${UNIX_SYS})
dep_option(PULSEAUDIO_SHARED   "Dynamically load PulseAudio support" ON "PULSEAUDIO" OFF)
set_option(ARTS                "Support the Analog Real Time Synthesizer" ${UNIX_SYS})
dep_option(ARTS_SHARED         "Dynamically load aRts audio support" ON "ARTS" OFF)
set_option(NAS                 "Support the NAS audio API" ${UNIX_SYS})
set_option(NAS_SHARED          "Dynamically load NAS audio API" ${UNIX_SYS})
set_option(SNDIO               "Support the sndio audio API" ${UNIX_SYS})
set_option(FUSIONSOUND         "Use FusionSound audio driver" OFF)
dep_option(FUSIONSOUND_SHARED  "Dynamically load fusionsound audio support" ON "FUSIONSOUND" OFF)
set_option(LIBSAMPLERATE       "Use libsamplerate for audio rate conversion" ${UNIX_SYS})
dep_option(LIBSAMPLERATE_SHARED "Dynamically load libsamplerate" ON "LIBSAMPLERATE" OFF)
set_option(RPATH               "Use an rpath when linking SDL" ${UNIX_SYS})
set_option(CLOCK_GETTIME       "Use clock_gettime() instead of gettimeofday()" OFF)
set_option(INPUT_TSLIB         "Use the Touchscreen library for input" ${UNIX_SYS})
set_option(VIDEO_X11           "Use X11 video driver" ${UNIX_SYS})
set_option(VIDEO_WAYLAND       "Use Wayland video driver" ${UNIX_SYS})
dep_option(WAYLAND_SHARED      "Dynamically load Wayland support" ON "VIDEO_WAYLAND" OFF)
dep_option(VIDEO_WAYLAND_QT_TOUCH  "QtWayland server support for Wayland video driver" ON "VIDEO_WAYLAND" OFF)
set_option(VIDEO_MIR           "Use Mir video driver" ${UNIX_SYS})
dep_option(MIR_SHARED          "Dynamically load Mir support" ON "VIDEO_MIR" OFF)
set_option(VIDEO_RPI           "Use Raspberry Pi video driver" ${UNIX_SYS})
dep_option(X11_SHARED          "Dynamically load X11 support" ON "VIDEO_X11" OFF)
set(SDL_X11_OPTIONS Xcursor Xinerama XInput Xrandr Xscrnsaver XShape Xvm)
foreach(_SUB ${SDL_X11_OPTIONS})
  string(TOUPPER "VIDEO_X11_${_SUB}" _OPT)
  dep_option(${_OPT}           "Enable ${_SUB} support" ON "VIDEO_X11" OFF)
endforeach()
set_option(VIDEO_COCOA         "Use Cocoa video driver" ${APPLE})
set_option(DIRECTX             "Use DirectX for Windows audio/video" ${WINDOWS})
set_option(RENDER_D3D          "Enable the Direct3D render driver" ${WINDOWS})
set_option(VIDEO_VIVANTE       "Use Vivante EGL video driver" ${UNIX_SYS})
dep_option(VIDEO_VULKAN        "Enable Vulkan support" ON "ANDROID OR APPLE OR LINUX OR WINDOWS" OFF)
set_option(VIDEO_KMSDRM        "Use KMS DRM video driver" ${UNIX_SYS})
dep_option(KMSDRM_SHARED       "Dynamically load KMS DRM support" ON "VIDEO_KMSDRM" OFF)





# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(SDL_SRC
src/crc.cpp
src/err.cpp
src/errorstr.cpp
src/group.cpp
src/ipx.cpp
src/loopback.cpp
src/nl.cpp
src/nltime.cpp
src/sock.cpp)

#src/htcondition.cpp
#src/hthread.cpp
#src/htmutex.cpp

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------
#include_directories(include hawknl)

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (hawknl_module ${HAWKNL_SRC})

