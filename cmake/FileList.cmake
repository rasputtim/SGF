set(AI_SRC
${CMAKE_SOURCE_DIR}/Source/ai/SGF_AstarHeap.cpp
${CMAKE_SOURCE_DIR}/Source/ai/SGF_AstarLib.cpp
${CMAKE_SOURCE_DIR}/Source/ai/SGF_Map.cpp
${CMAKE_SOURCE_DIR}/Source/ai/SGF_PathFinder.cpp)

set(CONFIGURATION_DIR ${CMAKE_SOURCE_DIR}/Source/configuration)
set(CONFIGURATION_SRC
${CONFIGURATION_DIR}/SGF_CmdVars.cpp
${CONFIGURATION_DIR}/SGF_ConfigSystem.cpp
${CONFIGURATION_DIR}/SGF_Configuration.cpp
${CONFIGURATION_DIR}/SGF_SysVar.cpp
)

set(EXCEPTIONS_DIR ${CMAKE_SOURCE_DIR}/Source/exceptions)
set(EXCEPTIONS_SRC
${EXCEPTIONS_DIR}/SGF_Error.cpp
${EXCEPTIONS_DIR}/SGF_Exception.cpp
${EXCEPTIONS_DIR}/SGF_LoadException.cpp
${EXCEPTIONS_DIR}/SGF_MugenException.cpp
${EXCEPTIONS_DIR}/SGF_NetException.cpp
${EXCEPTIONS_DIR}/SGF_TokenException.cpp
${EXCEPTIONS_DIR}/SGF_FileExceptions.cpp)

set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/Source/external)
set(EXTERNAL_SRC
${EXTERNAL_DIR}/DT_drawtext.c
${EXTERNAL_DIR}/fastevents.c
${EXTERNAL_DIR}/glSDL.c
${EXTERNAL_DIR}/Internal.c
${EXTERNAL_DIR}/scale2x.c
${EXTERNAL_DIR}/scale2xSDL.c
${EXTERNAL_DIR}/SDL_console.c
${EXTERNAL_DIR}/SDL_framerate.c)

set(GAME_DIR ${CMAKE_SOURCE_DIR}/Source/game)
set(GAME_SRC
${GAME_DIR}/SGF_Console.cpp
${GAME_DIR}/SGF_Control.cpp
${GAME_DIR}/SGF_Mod.cpp
${GAME_DIR}/SGF_World.cpp)

set(GRAPHICS_DIR ${CMAKE_SOURCE_DIR}/Source/graphics)
set(GRAPHICS_SRC
${GRAPHICS_DIR}/SGF_Bitmap.cpp
${GRAPHICS_DIR}/SGF_Color.cpp
${GRAPHICS_DIR}/SGF_FireEffect.cpp
${GRAPHICS_DIR}/SGF_GradientEffect.cpp
${GRAPHICS_DIR}/SGF_LitBitmap.cpp
${GRAPHICS_DIR}/SGF_Poligon.cpp
${GRAPHICS_DIR}/SGF_TransBitmap.cpp)

set(GUI_DIR ${CMAKE_SOURCE_DIR}/Source/gui)
set(GUI_SRC
${GUI_DIR}/SGF_BoundBox.cpp
${GUI_DIR}/SGF_Box.cpp
${GUI_DIR}/SGF_ContextBox.cpp
${GUI_DIR}/SGF_Coordinate.cpp
${GUI_DIR}/SGF_FadeToolGui.cpp
${GUI_DIR}/SGF_GuiAnimation.cpp
${GUI_DIR}/SGF_GuiTimer.cpp
${GUI_DIR}/SGF_LineEdit.cpp
${GUI_DIR}/SGF_PopupBox.cpp
${GUI_DIR}/SGF_RectArea.cpp
${GUI_DIR}/SGF_ScrollList.cpp
${GUI_DIR}/SGF_SelectList.cpp
${GUI_DIR}/SGF_TabbedBox.cpp
${GUI_DIR}/SGF_Widget.cpp
)

set(INPUT_DIR ${CMAKE_SOURCE_DIR}/Source/input)
set(INPUT_SRC
${INPUT_DIR}/SGF_ButtonMapping.cpp
${INPUT_DIR}/SGF_Events.cpp
${INPUT_DIR}/SGF_Input.cpp
${INPUT_DIR}/SGF_InputManager.cpp
${INPUT_DIR}/SGF_InputSource.cpp
${INPUT_DIR}/SGF_Joystick.cpp
${INPUT_DIR}/SGF_Keyboard.cpp
${INPUT_DIR}/SGF_KeyMapping.cpp
${INPUT_DIR}/SGF_Mouse.cpp
${INPUT_DIR}/SGF_TextInput.cpp
)

set(LEVEL_DIR ${CMAKE_SOURCE_DIR}/Source/level)
set(LEVEL_SRC
${LEVEL_DIR}/SGF_LevelUtils.cpp
)

set(LISTS_DIR ${CMAKE_SOURCE_DIR}/Source/lists)
set(LISTS_SRC
${LISTS_DIR}/SGF_AirList.cpp
${LISTS_DIR}/SGF_ImageList.cpp
${LISTS_DIR}/SGF_PcxList.cpp
${LISTS_DIR}/SGF_SndList.cpp
)

set(MATH_DIR ${CMAKE_SOURCE_DIR}/Source/math)
set(MATH_SRC
${MATH_DIR}/SGF_Angles.cpp
${MATH_DIR}/SGF_Complex.cpp
${MATH_DIR}/SGF_Lcp.cpp
${MATH_DIR}/SGF_Math.cpp
${MATH_DIR}/SGF_Matriz.cpp
${MATH_DIR}/SGF_Ode.cpp
${MATH_DIR}/SGF_Plane.cpp
${MATH_DIR}/SGF_Pluecker.cpp
${MATH_DIR}/SGF_Polynomial.cpp
${MATH_DIR}/SGF_Quat.cpp
${MATH_DIR}/SGF_Rotation.cpp
${MATH_DIR}/SGF_Simd.cpp
${MATH_DIR}/SGF_Simd_3DNow.cpp
${MATH_DIR}/SGF_Simd_Generic.cpp
${MATH_DIR}/SGF_Simd_AltiVec.cpp
${MATH_DIR}/SGF_Simd_MMX.cpp
${MATH_DIR}/SGF_Simd_SSE.cpp
${MATH_DIR}/SGF_Simd_SSE2.cpp
${MATH_DIR}/SGF_Simd_SSE3.cpp
${MATH_DIR}/SGF_Vector.cpp
)


set(MENU_DIR ${CMAKE_SOURCE_DIR}/Source/menu)
set(MENU_SRC
${MENU_DIR}/SGF_ActionFactory.cpp
${MENU_DIR}/SGF_ActionSpeed.cpp
${MENU_DIR}/SGF_MenuAction.cpp
${MENU_DIR}/SGF_MenuAnimation.cpp
${MENU_DIR}/SGF_MenuGlobal.cpp
${MENU_DIR}/SGF_MenuOption.cpp
${MENU_DIR}/SGF_MenuV2.cpp
${MENU_DIR}/SGF_OptionScreenSize.cpp
${MENU_DIR}/SGF_OptionAdventure.cpp
${MENU_DIR}/SGF_OptionAdventureCpu.cpp
${MENU_DIR}/SGF_OptionChangeMod.cpp
${MENU_DIR}/SGF_OptionConfig.cpp
${MENU_DIR}/SGF_OptionCredits.cpp
${MENU_DIR}/SGF_OptionDummy.cpp
${MENU_DIR}/SGF_OptionFactory.cpp
${MENU_DIR}/SGF_OptionFullScreen.cpp
${MENU_DIR}/SGF_OptionInvencible.cpp
${MENU_DIR}/SGF_OptionJoystick.cpp
${MENU_DIR}/SGF_OptionKey.cpp
${MENU_DIR}/SGF_OptionLevel.cpp
${MENU_DIR}/SGF_OptionLives.cpp
${MENU_DIR}/SGF_OptionMenu.cpp
${MENU_DIR}/SGF_OptionNetworkHost.cpp
${MENU_DIR}/SGF_OptionNetworkJoin.cpp
${MENU_DIR}/SGF_OptionNpcBuddies.cpp
${MENU_DIR}/SGF_OptionPlaymode.cpp
${MENU_DIR}/SGF_OptionSelectFontV2.cpp
${MENU_DIR}/SGF_OptionSpeed.cpp
${MENU_DIR}/SGF_OptionTabMenu.cpp
${MENU_DIR}/SGF_OptionVersus.cpp
)

set(MORTAL_DIR ${CMAKE_SOURCE_DIR}/Source/mortal)
set(MORTAL_SRC
${MORTAL_DIR}/gfx.cpp
)


set(MUGEN_DIR ${CMAKE_SOURCE_DIR}/Source/mugen)
set(MUGEN_AST_SRC
${MUGEN_DIR}/Ast/Ast.cpp
${MUGEN_DIR}/Ast/AstManager.cpp
)

set(NETWORK_DIR ${CMAKE_SOURCE_DIR}/Source/network)
set(NETWORK_SRC
${NETWORK_DIR}/SGF_NetClient.cpp
${NETWORK_DIR}/SGF_NetServer.cpp
${NETWORK_DIR}/SGF_NetChatServer.cpp
${NETWORK_DIR}/SGF_Network.cpp
)

set(OBJECTS_DIR ${CMAKE_SOURCE_DIR}/Source/objects)
set(OBJECTS_SRC
${OBJECTS_DIR}/SGF_Element.cpp
${OBJECTS_DIR}/SGF_Object.cpp
${OBJECTS_DIR}/SGF_ObjectCollidable.cpp

)

set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}/Source/resource)
set(RESOURCES_SRC
${RESOURCES_DIR}/SGF_Collector.cpp
${RESOURCES_DIR}/SGF_ResourceManager.cpp
)

set(SCRIPT_DIR ${CMAKE_SOURCE_DIR}/Source/script)
set(SCRIPT_SRC
${SCRIPT_DIR}/SGF_Script.cpp
${SCRIPT_DIR}/SGF_Perl.cpp
)

set(SPRITE_DIR ${CMAKE_SOURCE_DIR}/Source/sprite)
set(SPRITE_SRC
${SPRITE_DIR}/SGF_Effects.cpp
${SPRITE_DIR}/SGF_MugenSprite.cpp
${SPRITE_DIR}/SGF_RleSprite.cpp
${SPRITE_DIR}/SGF_SffManager.cpp
${SPRITE_DIR}/SGF_SffSprMan.cpp
)


set(SYS_DIR ${CMAKE_SOURCE_DIR}/Source/sys)
set(SYS_SRC
${SYS_DIR}/SGF_System.cpp
${SYS_DIR}/linux/SGF_LinShared.cpp
${SYS_DIR}/linux/SGF_LinCpu.cpp
${SYS_DIR}/linux/SGF_Fpu.cpp
)


set(UTIL_DIR ${CMAKE_SOURCE_DIR}/Source/util)
set(UTIL_SRC
${UTIL_DIR}/XmlNode/XmlNode.cpp
${UTIL_DIR}/SGF_ArgsCmdLine.cpp
${UTIL_DIR}/SGF_AudioSystem.cpp
${UTIL_DIR}/SGF_Debug.cpp
${UTIL_DIR}/SGF_Directory.cpp
${UTIL_DIR}/SGF_Ebox.cpp
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
${UTIL_DIR}/SGF_Path.cpp
${UTIL_DIR}/SGF_Regex.cpp
${UTIL_DIR}/SGF_SdlManager.cpp
${UTIL_DIR}/SGF_SndManager.cpp
${UTIL_DIR}/SGF_SoundManager.cpp
${UTIL_DIR}/SGF_StringUtils.cpp
${UTIL_DIR}/SGF_Thread.cpp
${UTIL_DIR}/SGF_Timedif.cpp
${UTIL_DIR}/SGF_Timer.cpp
${UTIL_DIR}/SGF_Token.cpp
${UTIL_DIR}/SGF_TokenReader_xml.cpp
${UTIL_DIR}/SGF_Utf.cpp
${UTIL_DIR}/SGF_Util.cpp
${UTIL_DIR}/SGF_Xmltools.cpp
)

set(WINDOWS_DIR ${CMAKE_SOURCE_DIR}/Source/windows)
set(WINDOWS_SRC
${WINDOWS_DIR}/system.cpp
${WINDOWS_DIR}/funcs.cpp
)
##external libs sources
set(7ZIP_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/7z)
set(7ZIP_SRC
${7ZIP_DIR}/7zAlloc.c
${7ZIP_DIR}/7zBuf.c
${7ZIP_DIR}/7zBuf2.c
${7ZIP_DIR}/7zCrc.c
${7ZIP_DIR}/7zCrcOpt.c
${7ZIP_DIR}/7zDec.c
${7ZIP_DIR}/7zIn.c
${7ZIP_DIR}/CpuArch.c
${7ZIP_DIR}/LzmaDec.c
${7ZIP_DIR}/Lzma2Dec.c
${7ZIP_DIR}/Bra.c
${7ZIP_DIR}/Bra86.c
${7ZIP_DIR}/Bcj2.c
${7ZIP_DIR}/7zFile.c
${7ZIP_DIR}/7zStream.c)

set(HAWKNL_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/hawknl)

set(HAWKNL_SRC
${HAWKNL_DIR}/src/crc.cpp
${HAWKNL_DIR}/src/err.cpp
${HAWKNL_DIR}/src/errorstr.cpp
${HAWKNL_DIR}/src/group.cpp
${HAWKNL_DIR}/src/ipx.cpp
${HAWKNL_DIR}/src/loopback.cpp
${HAWKNL_DIR}/src/nl.cpp
${HAWKNL_DIR}/src/nltime.cpp
${HAWKNL_DIR}/src/sock.cpp)

set(MD5_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/md5)
set(MD5_SRC
${MD5_DIR}/md5.c
)

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

set(SHA_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/sha1-c)
set(SHA_SRC
${SHA_DIR}/sha.c
${SHA_DIR}/sha1.c
)

set(SFL_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/sha1-c)
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

set(SGE_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/sge2d)
set(SGE_SRC
${SGE_DIR}/src/sge_bm_text.cpp
${SGE_DIR}/src/sgearray.c
${SGE_DIR}/src/sgegfx.c
${SGE_DIR}/src/sgeresource.c
${SGE_DIR}/src/sgesprite.c
${SGE_DIR}/src/sgespriteimage.c
)

set(MINIZIP_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/zip)
set(MINIZIP_SRC
${MINIZIP_DIR}/ioapi.c
${MINIZIP_DIR}/unzip.c
${MINIZIP_DIR}/zip.c)

set(SDLGFX_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL_gfx-2.0.24)
set(SDLGFX_SRC
${SDLGFX_DIR}/SDL_gfxPrimitives.c
${SDLGFX_DIR}/SDL_imageFilter.c
${SDLGFX_DIR}/SDL_rotozoom.c
)

set(TIMIDITY_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.0/timidity)
set(TIMIDITY_SRC
${TIMIDITY_DIR}/common.c
${TIMIDITY_DIR}/ctrlmode.c
${TIMIDITY_DIR}/filter.c
${TIMIDITY_DIR}/instrum.c
${TIMIDITY_DIR}/mix.c
${TIMIDITY_DIR}/output.c
${TIMIDITY_DIR}/playmidi.c
${TIMIDITY_DIR}/readmidi.c
${TIMIDITY_DIR}/resample.c
${TIMIDITY_DIR}/sdl_a.c
${TIMIDITY_DIR}/sdl_c.c
${TIMIDITY_DIR}/tables.c
${TIMIDITY_DIR}/timidity.c
)


#add_subdirectory(${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.0/native_midi)
set(NATIVEMIDI_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.0/native_midi)
set(NATIVE_MIDI_SRC
${NATIVEMIDI_DIR}/native_midi_common.c
)

# SDL2
set(SDLIMAGE_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_image-2.0.0)
set(SDLIMAGE_SRC
${SDLIMAGE_DIR}/IMG.c
${SDLIMAGE_DIR}/IMG_bmp.c
${SDLIMAGE_DIR}/IMG_gif.c
${SDLIMAGE_DIR}/IMG_jpg.c
${SDLIMAGE_DIR}/IMG_lbm.c
${SDLIMAGE_DIR}/IMG_pcx.c
${SDLIMAGE_DIR}/IMG_png.c
${SDLIMAGE_DIR}/IMG_pnm.c
${SDLIMAGE_DIR}/IMG_tga.c
${SDLIMAGE_DIR}/IMG_tif.c
${SDLIMAGE_DIR}/IMG_webp.c
${SDLIMAGE_DIR}/IMG_xcf.c
${SDLIMAGE_DIR}/IMG_xpm.c
${SDLIMAGE_DIR}/IMG_xv.c
${SDLIMAGE_DIR}/IMG_xxx.c)

set(SDLMIXER_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_mixer-2.0.2)

set(SDLMIXER_SRC
${SDLMIXER_DIR}/music.c
${SDLMIXER_DIR}/mixer.c
${SDLMIXER_DIR}/music_ogg.c
${SDLMIXER_DIR}/music_flac.c
${SDLMIXER_DIR}/music_mad.c
${SDLMIXER_DIR}/dynamic_ogg.c
${SDLMIXER_DIR}/effect_position.c
${SDLMIXER_DIR}/effects_internal.c
${SDLMIXER_DIR}/effect_stereoreverse.c
${SDLMIXER_DIR}/load_voc.c
${SDLMIXER_DIR}/load_ogg.c
${SDLMIXER_DIR}/load_aiff.c
${SDLMIXER_DIR}/wavestream.c
${SDLMIXER_DIR}/fluidsynth.c
${SDLMIXER_DIR}/load_flac.c
${SDLMIXER_DIR}/music_cmd.c
${SDLMIXER_DIR}/music_mod.c
${SDLMIXER_DIR}/music_modplug.c
)

set(SDLTTF_DIR ${CMAKE_SOURCE_DIR}/ExternalLibs/SDL2_ttf-2.0.12)

set(SDLTTF_SRC
${SDLTTF_DIR}/SDL_ttf.c
${SDLTTF_DIR}/glfont.c
)







