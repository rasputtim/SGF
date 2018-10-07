# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(UTIL_DIR ${CMAKE_SOURCE_DIR}/Source/util)
set(UTIL_SRC
${UTIL_DIR}/XmlNode/XmlNode.cpp
${UTIL_DIR}/SGF_ArgsCmdLine.cpp
${UTIL_DIR}/SGF_AudioSystem.cpp
${UTIL_DIR}/SGF_Debug.cpp
${UTIL_DIR}/SGF_Directory.cpp
${UTIL_DIR}/SGF_Ebox.cpp
${UTIL_DIR}/SGF_FilesystemBase.cpp
${UTIL_DIR}/SGF_FileSystem.cpp
${UTIL_DIR}/SGF_FontInfo.cpp
${UTIL_DIR}/SGF_FontSystem.cpp
${UTIL_DIR}/SGF_HashUtils.cpp
${UTIL_DIR}/SGF_Heap.cpp
${UTIL_DIR}/SGF_LanguageString.cpp
${UTIL_DIR}/SGF_Loading.cpp
${UTIL_DIR}/SGF_MessageQueue.cpp
${UTIL_DIR}/SGF_Messages.cpp
${UTIL_DIR}/SGF_MugenSound.cpp
${UTIL_DIR}/SGF_Mutex.cpp
${UTIL_DIR}/SGF_Path.cpp
${UTIL_DIR}/SGF_Regex.cpp
${UTIL_DIR}/SGF_SdlManager.cpp
${UTIL_DIR}/SGF_SndManager.cpp
${UTIL_DIR}/SGF_SoundManager.cpp
${UTIL_DIR}/SGF_StringUtils.cpp
${UTIL_DIR}/SGF_Task.cpp
${UTIL_DIR}/SGF_Thread.cpp
${UTIL_DIR}/SGF_Timedif.cpp
${UTIL_DIR}/SGF_Timer.cpp
${UTIL_DIR}/SGF_Token.cpp
${UTIL_DIR}/SGF_TokenReader_xml.cpp
${UTIL_DIR}/SGF_Utf.cpp
${UTIL_DIR}/SGF_UtilStructs.cpp
${UTIL_DIR}/SGF_Util.cpp
${UTIL_DIR}/SGF_Xmltools.cpp
)

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------
#include_directories(include include/internal)

# -------------------------------------------------------
# module
# -------------------------------------------------------
add_library (util_module STATIC  ${UTIL_SRC})
target_link_libraries(util_module minizip_module 7zip_module sfl_module expat sdlmixer_module  math_module external_module graphics_module network_module  exceptions_module sdl2_static)
if(NOT ANDROID)
target_link_libraries(util_module hawknl_module system_module)
endif()
