# -------------------------------------------------------
# util cmake build script for sgffabric.
# Written by: Salvatore
# Modified by: Salvatore
# -------------------------------------------------------

# -------------------------------------------------------
# Source directories containing all the necessary .cpp files
# -------------------------------------------------------
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

# -------------------------------------------------------
# Include directory
# -------------------------------------------------------

# -------------------------------------------------------
# module
# -------------------------------------------------------
#add_library (input_module ${INPUT_SRC})
