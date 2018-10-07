# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
set(MENU_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source/menu)
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

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (menu_module ${MENU_SRC})
