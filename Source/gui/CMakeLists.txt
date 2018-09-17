# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
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

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (gui_module ${GUI_SRC})
