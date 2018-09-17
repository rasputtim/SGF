/** \defgroup SGF_Input 
 *
 * \brief Teclado, Mouse, Joystick, Eventos
 * 
 */
#define USE_SDL

#ifdef USE_SDL
#include "../../ExternalLibs/SDL2/include/SDL.h"
#endif

#include "SGF_StructsInput.h"
#include "SGF_Keyboard.h"
#include "SGF_Joystick.h"
#include "SGF_Events.h"
#include "SGF_Mouse.h"
#include "SGF_InputManager.h"
#include "SGF_InputMap.h"
#include "SGF_FrameControl.h"
#include "SGF_ButtonMapping.h"
#include "SGF_TextInput.h"
