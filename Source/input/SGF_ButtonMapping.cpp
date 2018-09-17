#define USE_SDL
#ifdef USE_SDL
#include <string>
#include <vector>
#include <exception>
#include <SDL.h>
#include "input/SGF_ButtonMapping.h"
#include "input/SGF_Joystick.h"
#include "util/SGF_Debug.h"


using ::std::string;
using ::std::vector;

namespace SGF {
class CJoystick;

//-------------DefaultCButtonMapping---------------------------

    CJoystick::Key DefaultButtonMapping::toKey(int button){
        switch (button){
            case 0: return CJoystick::Button1;
            case 1: return CJoystick::Button2;
            case 2: return CJoystick::Button3;
            case 3: return CJoystick::Button4;
            //case 4: return CJoystick::Quit;
            case 5: return CJoystick::Button5;
            case 6: return CJoystick::Button6;
            default: return CJoystick::Invalid;
        }
    }

    void DefaultButtonMapping::hatMotionEvents(int motion, vector<CJoystick::Event> & events){
        bool up = false;
        bool down = false;
        bool left = false;
        bool right = false;
        switch (motion){
            case SDL_HAT_CENTERED: break;
            case SDL_HAT_UP: up = true; break;
            case SDL_HAT_RIGHT: right = true; break;
            case SDL_HAT_DOWN: down = true; break;
            case SDL_HAT_LEFT: left = true; break;
            case SDL_HAT_RIGHTUP: right = true; up = true; break;
            case SDL_HAT_RIGHTDOWN: right = true; down = true; break;
            case SDL_HAT_LEFTUP: left = true; up = true; break;
            case SDL_HAT_LEFTDOWN: left = true; down = true; break;
        }

        events.push_back(CJoystick::Event(CJoystick::Left, left));
        events.push_back(CJoystick::Event(CJoystick::Right, right));
        events.push_back(CJoystick::Event(CJoystick::Down, down));
        events.push_back(CJoystick::Event(CJoystick::Up, up));
    }

    void DefaultButtonMapping::axisMotionEvents(int axis, int motion, vector<CJoystick::Event> & events){

		int tolerance = 10;

		if (axis == -tolerance){
			Debug::debug(Debug::input,__FUNCTION__) << "axis 0: "<< motion <<endl;
            if (motion < 0){
                events.push_back(CJoystick::Event(CJoystick::Left, true));
            } else if (motion > tolerance){
                events.push_back(CJoystick::Event(CJoystick::Right, true));
            }
        } else if (axis == 1){
			Debug::debug(Debug::input,__FUNCTION__) << "axis 1: "<< motion <<endl;
            if (motion < -tolerance){
                events.push_back(CJoystick::Event(CJoystick::Up, true));
            } else if (motion > tolerance){
                events.push_back(CJoystick::Event(CJoystick::Down, true));
            }
        }else if (axis == 2){
            Debug::debug(Debug::input,__FUNCTION__) << "axis 2: "<< motion <<endl;
			if (motion < -tolerance){
	                events.push_back(CJoystick::Event(CJoystick::Axis2D1, true));
            } else if (motion > tolerance){
					events.push_back(CJoystick::Event(CJoystick::Axis2D2, true));
            }
        }else if (axis == 3){
			Debug::debug(Debug::input,__FUNCTION__) << "axis 3: "<< motion <<endl;
            if (motion < -tolerance){
                events.push_back(CJoystick::Event(CJoystick::Axis3D1, true));
            } else if (motion > tolerance){
                events.push_back(CJoystick::Event(CJoystick::Axis3D2, true));
            }
        }else if (axis == 4){
			Debug::debug(Debug::input,__FUNCTION__) << "axis 4: "<< motion <<endl;
            if (motion < -tolerance){
                events.push_back(CJoystick::Event(CJoystick::Axis4D1, true));
            } else if (motion > tolerance){
                events.push_back(CJoystick::Event(CJoystick::Axis4D2, true));
            }
        }

    }


/* used when a ps3 controller is plugged into a usb port of a normal pc */
//-----------------Playstation3Controller---------------------

    int Playstation3Controller::toNative(int button){
        switch (button){
            case 0: return Square;
            case 1: return Cross;
            case 2: return Circle;
            case 3: return Triangle;
            case 4: return Start;
        }

        return button;
    }

    int Playstation3Controller::fromNative(int button){
        switch (button){
            case Square: return 0;
            case Cross: return 1;
            case Circle: return 2;
            case Triangle: return 3;
            case Start: return Start;
            default: return 5;
        }

        return button;
    }

    CJoystick::Key Playstation3Controller::toKey(int button){
        switch (button){
            case Square: return CJoystick::Button1;
            case Cross: return CJoystick::Button2;
            case Circle: return CJoystick::Button3;
            case Triangle: return CJoystick::Button4;
            case L1: return CJoystick::Button5;
            case R1: return CJoystick::Button6;
			case L2: return CJoystick::Button7;
			case R2: return CJoystick::Button8;
			case Stick1_L3: return CJoystick::Button9;
			case Stick2_R3: return CJoystick::Button10;
            case Start: return CJoystick::Button11;
            case Select: return CJoystick::Button12;
            case Up: return CJoystick::Up;
            case Down: return CJoystick::Down;
            case Left: return CJoystick::Left;
            case Right: return CJoystick::Right;
            default: return CJoystick::Invalid;
        }
    }


    void Playstation3Controller::axisMotionEvents(int axis, int motion, vector<CJoystick::Event> & events){



}

    void Playstation3Controller::hatMotionEvents(int motion, vector<CJoystick::Event> & events){
    }

//--------------------LogitechPrecision-----------------------

    CJoystick::Key LogitechPrecision::toKey(int button){
        switch (button){
            case Button1: return CJoystick::Button1;
            case Button2: return CJoystick::Button2;
            case Button3: return CJoystick::Button3;
            case Button4: return CJoystick::Button4;
            case L1: return CJoystick::Button5;
            case R1: return CJoystick::Button6;
            //case Start: return CJoystick::Quit;
        }
        return CJoystick::Invalid;
    }

    /* axis 1. negative up, positive down
     * axis 0, negative left, positive right
     */
    void LogitechPrecision::axisMotionEvents(int axis, int motion, vector<CJoystick::Event> & events){
        int tolerance = 10;
        if (axis == 0){
            if (motion < -tolerance){
                events.push_back(CJoystick::Event(CJoystick::Left, true));
            } else if (motion > tolerance){
                events.push_back(CJoystick::Event(CJoystick::Right, true));
            } else {
                /* fake a release for left and right */
                events.push_back(CJoystick::Event(CJoystick::Left, false));
                events.push_back(CJoystick::Event(CJoystick::Right, false));
            }
        } else if (axis == 1){
            if (motion < -tolerance){
                events.push_back(CJoystick::Event(CJoystick::Up, true));
            } else if (motion > tolerance){
                events.push_back(CJoystick::Event(CJoystick::Down, true));
            } else {
                events.push_back(CJoystick::Event(CJoystick::Up, false));
                events.push_back(CJoystick::Event(CJoystick::Down, false));
            }
        }
    }

    void LogitechPrecision::hatMotionEvents(int motion, vector<CJoystick::Event> & events){
    }



//------------ Ps3Controller---------------------
/* used for the ps3 controller with psl1ght's SDL version */

    int Ps3Controller::toNative(int button){
        switch (button){
            case 0: return Square;
            case 1: return Cross;
            case 2: return Circle;
            case 3: return Triangle;
            case 4: return Start;
        }
        return button;
    }

    int Ps3Controller::fromNative(int button){
        switch (button){
            case Square: return 0;
            case Cross: return 1;
            case Circle: return 2;
            case Triangle: return 3;
            case Start: return Start;
            default: return 5;
        }
        return button;
    }

    CJoystick::Key Ps3Controller::toKey(int button){
        switch (button){
            case Square: return CJoystick::Button1;
            case Cross: return CJoystick::Button2;
            case Circle: return CJoystick::Button3;
            case Triangle: return CJoystick::Button4;
            case L1: return CJoystick::Button5;
            case R1: return CJoystick::Button6;
//            case Start: return CJoystick::Quit;
            case Up: return CJoystick::Up;
            case Down: return CJoystick::Down;
            case Left: return CJoystick::Left;
            case Right: return CJoystick::Right;
            default: return CJoystick::Invalid;
        }
    }

    /* TODO */
    void Ps3Controller::axisMotionEvents(int axis, int motion, vector<CJoystick::Event> & events){
    }

    void Ps3Controller::hatMotionEvents(int motion, vector<CJoystick::Event> & events){
    }


//--------------XBox360Controller--------------------------
    CJoystick::Key XBox360Controller::toKey(int button){
        switch (button){
            case A: return CJoystick::Button1;
            case B: return CJoystick::Button2;
            case X: return CJoystick::Button3;
            case Y: return CJoystick::Button4;
            case L1: return CJoystick::Button5;
            case R1: return CJoystick::Button6;
            //case Start: return CJoystick::Quit;
        }
        return CJoystick::Invalid;
    }

    void XBox360Controller::axisMotionEvents(int axis, int motion, vector<CJoystick::Event> & events){
    /* axis 6 and 7 are the hats. sdl passes them as hat events */
    #if 0
        if (axis == 6){
            if (motion < 0){
                events.push_back(CJoystick::Event(CJoystick::Left, true));
            } else if (motion > 0){
                events.push_back(CJoystick::Event(CJoystick::Right, true));
            } else if (motion == 0){
                /* fake a release for left and right */
                events.push_back(CJoystick::Event(CJoystick::Left, false));
                events.push_back(CJoystick::Event(CJoystick::Right, false));
            }
        } else if (axis == 7){
            if (motion < 0){
                events.push_back(CJoystick::Event(CJoystick::Up, true));
            } else if (motion > 0){
                events.push_back(CJoystick::Event(CJoystick::Down, true));
            } else if (motion == 0){
                events.push_back(CJoystick::Event(CJoystick::Up, false));
                events.push_back(CJoystick::Event(CJoystick::Down, false));
            }
        }
        #endif
    }

    void XBox360Controller::hatMotionEvents(int motion, vector<CJoystick::Event> & events){
        bool up = false;
        bool down = false;
        bool left = false;
        bool right = false;
        switch (motion){
            case SDL_HAT_CENTERED: break;
            case SDL_HAT_UP: up = true; break;
            case SDL_HAT_RIGHT: right = true; break;
            case SDL_HAT_DOWN: down = true; break;
            case SDL_HAT_LEFT: left = true; break;
            case SDL_HAT_RIGHTUP: right = true; up = true; break;
            case SDL_HAT_RIGHTDOWN: right = true; down = true; break;
            case SDL_HAT_LEFTUP: left = true; up = true; break;
            case SDL_HAT_LEFTDOWN: left = true; down = true; break;
        }

        events.push_back(CJoystick::Event(CJoystick::Left, left));
        events.push_back(CJoystick::Event(CJoystick::Right, right));
        events.push_back(CJoystick::Event(CJoystick::Down, down));
        events.push_back(CJoystick::Event(CJoystick::Up, up));
    }


   //---------Wiimote-----------------------
    CJoystick::Key Wiimote::toKey(int button){
        switch (button){
            case A: return CJoystick::Button1;
            case B: return CJoystick::Button2;
            case Button1: return CJoystick::Button3;
            case Button2: return CJoystick::Button4;
            case Minus: return CJoystick::Button5;
            case Plus: return CJoystick::Button6;
            //case Home: return CJoystick::Quit;
        }
        return CJoystick::Invalid;
    }

    void Wiimote::axisMotionEvents(int axis, int motion, vector<CJoystick::Event> & events){
    }

    void Wiimote::hatMotionEvents(int motion, vector<CJoystick::Event> & events){
        /* rotate all the directions 90 degrees */
        bool up = false; // right
        bool down = false; // left
        bool left = false; // up
        bool right = false; // down
        switch (motion){
            case SDL_HAT_CENTERED: break;
            case SDL_HAT_UP: up = true; break;
            case SDL_HAT_RIGHT: right = true; break;
            case SDL_HAT_DOWN: down = true; break;
            case SDL_HAT_LEFT: left = true; break;
            case SDL_HAT_RIGHTUP: up = true; right = true; break;
            case SDL_HAT_RIGHTDOWN: down = true; right = true; break;
            case SDL_HAT_LEFTUP: up = true; left = true; break;
            case SDL_HAT_LEFTDOWN: down = true; left = true; break;
        }

        events.push_back(CJoystick::Event(CJoystick::Left, left));
        events.push_back(CJoystick::Event(CJoystick::Right, right));
        events.push_back(CJoystick::Event(CJoystick::Down, down));
        events.push_back(CJoystick::Event(CJoystick::Up, up));
    }

	//===========GamecubePad

    CJoystick::Key GamecubePad::toKey(int button){
        switch (button){
            case A: return CJoystick::Button1;
            case B: return CJoystick::Button2;
            case X: return CJoystick::Button3;
            case Y: return CJoystick::Button4;
            case Z: return CJoystick::Button5;
//            case Start: return CJoystick::Quit;
        }
        return CJoystick::Invalid;
    }

    void GamecubePad::axisMotionEvents(int axis, int motion, vector<CJoystick::Event> & events){
        // printf("axis %d motion %d\n", axis, motion);
    }

    void GamecubePad::hatMotionEvents(int motion, vector<CJoystick::Event> & events){
        bool up = false;
        bool down = false;
        bool left = false;
        bool right = false;
        switch (motion){
            case SDL_HAT_CENTERED: break;
            case SDL_HAT_UP: up = true; break;
            case SDL_HAT_RIGHT: right = true; break;
            case SDL_HAT_DOWN: down = true; break;
            case SDL_HAT_LEFT: left = true; break;
            case SDL_HAT_RIGHTUP: right = true; up = true; break;
            case SDL_HAT_RIGHTDOWN: right = true; down = true; break;
            case SDL_HAT_LEFTUP: left = true; up = true; break;
            case SDL_HAT_LEFTDOWN: left = true; down = true; break;
        }

        events.push_back(CJoystick::Event(CJoystick::Left, left));
        events.push_back(CJoystick::Event(CJoystick::Right, right));
        events.push_back(CJoystick::Event(CJoystick::Down, down));
        events.push_back(CJoystick::Event(CJoystick::Up, up));
    }

	} //end SGF
#endif
