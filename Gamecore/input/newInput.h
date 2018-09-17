ifndef _S_G_E_INPUT_H___
#define _S_G_E_INPUT_H___

#include "SDL.h"

class CNewInput
{
public:
    CNewInput();
    ~CNewInput();
    
	/*
        Handle keys being pressed down continuously
    */
	virtual void HandleInput()=0;
	/*
        Handle keys being pressed down continuously
    */
   // virtual void HandleKeyboardRepeating(KEYBOARDDATA *lpKeyBoard);
    
	virtual void HandleKeySingle(SDL_KeyboardEvent key)=0;

	virtual void HandleMouseMotion()=0;

	virtual void HandleMouseSingle()=0;

	virtual void HandleMouseRepeating()=0;
/* don't change these numbers, but you can add to them */
    enum GameInput{
        Unknown = -1,
        Forward = 0,
        Back = 1,
        Up = 2,
        Down = 3,
        ButtonA = 4,
        ButtonB = 5,
        ButtonC = 6,
        ButtonX = 7,
        Grab = 8,
		Attack4 = 9,
        Attack5 = 10,
        Attack6 = 11,
    };

    
};

#endif /*INPUT_H_*/