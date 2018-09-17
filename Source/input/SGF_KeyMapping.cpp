#define USE_SDL
#ifdef USE_SDL

#include <SDL.h>
#include "input/SGF_KeyMapping.h"
#include "input/SGF_Keyboard.h"

using namespace std;
namespace SGF {
CKeyboard::Key  SDLKeyMapping::toKey(int SDLkeyCode) {
	switch (SDLkeyCode) {
	case SDLK_a: return CKeyboard::Key_A; break;
	case SDLK_b: return CKeyboard::Key_B; break;
case SDLK_c: return CKeyboard::Key_C; break;
case SDLK_d: return CKeyboard::Key_D; break;
case SDLK_e: return CKeyboard::Key_E; break;
case SDLK_f: return CKeyboard::Key_F; break;
case SDLK_g: return CKeyboard::Key_G; break;
case SDLK_h: return CKeyboard::Key_H; break;
case SDLK_i: return CKeyboard::Key_I; break;
case SDLK_j: return CKeyboard::Key_J; break;
case SDLK_k: return CKeyboard::Key_K; break;
case SDLK_l: return CKeyboard::Key_L; break;
case SDLK_m: return CKeyboard::Key_M; break;
case SDLK_n: return CKeyboard::Key_N; break;
case SDLK_o: return CKeyboard::Key_O; break;
case SDLK_p: return CKeyboard::Key_P; break;
case SDLK_q: return CKeyboard::Key_Q; break;
case SDLK_r: return CKeyboard::Key_R; break;
case SDLK_s: return CKeyboard::Key_S; break;
case SDLK_t: return CKeyboard::Key_T; break;
case SDLK_u: return CKeyboard::Key_U; break;
case SDLK_v: return CKeyboard::Key_V; break;
case SDLK_w: return CKeyboard::Key_W; break;
case SDLK_x: return CKeyboard::Key_X; break;
case SDLK_y: return CKeyboard::Key_Y; break;
case SDLK_z: return CKeyboard::Key_Z; break;
case SDLK_0: return CKeyboard::Key_0; break;
case SDLK_1: return CKeyboard::Key_1; break;
case SDLK_2: return CKeyboard::Key_2; break;
case SDLK_3: return CKeyboard::Key_3; break;
case SDLK_4: return CKeyboard::Key_4; break;
case SDLK_5: return CKeyboard::Key_5; break;
case SDLK_6: return CKeyboard::Key_6; break;
case SDLK_7: return CKeyboard::Key_7; break;
case SDLK_8: return CKeyboard::Key_8; break;
case SDLK_9: return CKeyboard::Key_9; break;
case SDLK_KP_0: return CKeyboard::Key_0_PAD; break;
case SDLK_KP_1: return CKeyboard::Key_1_PAD; break;
case SDLK_KP_2: return CKeyboard::Key_2_PAD; break;
case SDLK_KP_3: return CKeyboard::Key_3_PAD; break;
case SDLK_KP_4: return CKeyboard::Key_4_PAD; break;
case SDLK_KP_5: return CKeyboard::Key_5_PAD; break;
case SDLK_KP_6: return CKeyboard::Key_6_PAD; break;
case SDLK_KP_7: return CKeyboard::Key_7_PAD; break;
case SDLK_KP_8: return CKeyboard::Key_8_PAD; break;
case SDLK_KP_9: return CKeyboard::Key_9_PAD; break;
case SDLK_F1: return CKeyboard::Key_F1; break;
case SDLK_F2: return CKeyboard::Key_F2; break;
case SDLK_F3: return CKeyboard::Key_F3; break;
case SDLK_F4: return CKeyboard::Key_F4; break;
case SDLK_F5: return CKeyboard::Key_F5; break;
case SDLK_F6: return CKeyboard::Key_F6; break;
case SDLK_F7: return CKeyboard::Key_F7; break;
case SDLK_F8: return CKeyboard::Key_F8; break;
case SDLK_F9: return CKeyboard::Key_F9; break;
case SDLK_F10: return CKeyboard::Key_F10; break;
case SDLK_F11: return CKeyboard::Key_F11; break;
case SDLK_F12: return CKeyboard::Key_F12; break;
case SDLK_ESCAPE: return CKeyboard::Key_ESC; break;
case SDLK_BACKQUOTE: return CKeyboard::Key_TILDE; break;
case SDLK_MINUS: return CKeyboard::Key_MINUS; break;
case SDLK_EQUALS: return CKeyboard::Key_EQUALS; break;
case SDLK_BACKSPACE: return CKeyboard::Key_BACKSPACE; break;
case SDLK_TAB: return CKeyboard::Key_TAB; break;
case SDLK_LEFTBRACKET: return CKeyboard::Key_OPENBRACE; break;
case SDLK_RIGHTBRACKET: return CKeyboard::Key_CLOSEBRACE; break;
case SDLK_RETURN: return CKeyboard::Key_ENTER; break;
case SDLK_COLON: return CKeyboard::Key_COLON; break;
case SDLK_QUOTE: return CKeyboard::Key_QUOTE; break;
case SDLK_BACKSLASH: return CKeyboard::Key_BACKSLASH; break;
case 999: return CKeyboard::Key_BACKSLASH2; break;
case SDLK_COMMA: return CKeyboard::Key_COMMA; break;
case SDLK_PERIOD: return CKeyboard::Key_STOP; break;
case SDLK_SLASH: return CKeyboard::Key_SLASH; break;
case SDLK_SPACE: return CKeyboard::Key_SPACE; break;
case SDLK_INSERT: return CKeyboard::Key_INSERT; break;
case SDLK_DELETE: return CKeyboard::Key_DEL; break;
case SDLK_HOME: return CKeyboard::Key_HOME; break;
case SDLK_END: return CKeyboard::Key_END; break;
case SDLK_PAGEUP: return CKeyboard::Key_PGUP; break;
case SDLK_PAGEDOWN: return CKeyboard::Key_PGDN; break;
case SDLK_LEFT: return CKeyboard::Key_LEFT; break;
case SDLK_RIGHT: return CKeyboard::Key_RIGHT; break;
case SDLK_UP: return CKeyboard::Key_UP; break;
case SDLK_DOWN: return CKeyboard::Key_DOWN; break;


 case SDLK_KP_PERIOD: return CKeyboard::Key_SLASH_PAD; break;
 case SDLK_ASTERISK: return CKeyboard::Key_ASTERISK; break;
 case SDLK_KP_MINUS: return CKeyboard::Key_MINUS_PAD; break;
 case SDLK_KP_PLUS: return CKeyboard::Key_PLUS_PAD; break;
 case 1000: return CKeyboard::Key_DEL_PAD; break;
 case SDLK_KP_ENTER: return CKeyboard::Key_ENTER_PAD; break;
 case SDLK_PRINTSCREEN: return CKeyboard::Key_PRTSCR; break;
 case SDLK_PAUSE: return CKeyboard::Key_PAUSE; break;
// case KEY_ABNT_C1: return CKeyboard::Key_ABNT_C1; break;
 case 1002: return CKeyboard::Key_YEN; break;
 case 1003: return CKeyboard::Key_KANA; break;
 case 1004: return CKeyboard::Key_CONVERT; break;
 case 1005: return CKeyboard::Key_NOCONVERT; break;
 case SDLK_AT: return CKeyboard::Key_AT; break;
 case SDLK_CARET: return CKeyboard::Key_CIRCUMFLEX; break;
 case 1006: return CKeyboard::Key_COLON2; break;
 case 1007: return CKeyboard::Key_KANJI; break;
 case SDLK_KP_EQUALS: return CKeyboard::Key_EQUALS_PAD; break;
 case 1008: return CKeyboard::Key_BACKQUOTE; break;
 case SDLK_SEMICOLON: return CKeyboard::Key_SEMICOLON; break;
 case 1009: return CKeyboard::Key_COMMAND; break;
// case KEY_UNKNOWN1: return CKeyboard::Key_UNKNOWN1; break;
// case KEY_UNKNOWN2: return CKeyboard::Key_UNKNOWN2; break;
// case KEY_UNKNOWN3: return CKeyboard::Key_UNKNOWN3; break;
// case KEY_UNKNOWN4: return CKeyboard::Key_UNKNOWN4; break;
// case KEY_UNKNOWN5: return CKeyboard::Key_UNKNOWN5; break;
// case KEY_UNKNOWN6: return CKeyboard::Key_UNKNOWN6; break;
// case KEY_UNKNOWN7: return CKeyboard::Key_UNKNOWN7; break;
 case SDLK_UNKNOWN: return CKeyboard::Key_UNKNOWN; break;
 case 1010: return CKeyboard::Key_MODIFIERS; break;
 case SDLK_LSHIFT: return CKeyboard::Key_LSHIFT; break;
 case SDLK_RSHIFT: return CKeyboard::Key_RSHIFT; break;
 case SDLK_LCTRL: return CKeyboard::Key_LCONTROL; break;
 case SDLK_RCTRL: return CKeyboard::Key_RCONTROL; break;
 case SDLK_LALT: return CKeyboard::Key_ALT; break;
 case SDLK_RALT: return CKeyboard::Key_ALTGR; break;
 case SDLK_LGUI: return CKeyboard::Key_LWIN; break;
 case SDLK_RGUI: return CKeyboard::Key_RWIN; break;
 case SDLK_MENU: return CKeyboard::Key_MENU; break;
 case SDLK_SCROLLLOCK: return CKeyboard::Key_SCRLOCK; break;
 case SDLK_NUMLOCKCLEAR: return CKeyboard::Key_NUMLOCK; break;
 case SDLK_CAPSLOCK: return CKeyboard::Key_CAPSLOCK; break;
 default: return CKeyboard::Invalid; break;
}


}
}//end SGF
#endif
 