/***************************************************************************
                          Event.h  -  description
                             -------------------
    begin                : Sat Feb 14 2004
    copyright            : (C) 2004 by upi
    email                : upi@feel
 ***************************************************************************/


#ifndef EVENT_H
#define EVENT_H

#include "common.h"


struct SMortalEvent
{
	TMortalEventEnum	m_enType;
	int					m_iPlayer;
	int					m_iKey;
};

/** MortalPollEvent works like SDL_PollEvent, except that it
returns an SMortalEvent.
*/
template <typename X>
bool MortalPollEvent(X &game, SMortalEvent& a_roOutEvent )
{
	SDL_Event oEvent;

	while ( SDL_PollEvent( &oEvent ) )
	{
		if ( TranslateEvent(game, &oEvent, &a_roOutEvent ) )
		{
			return true;
		}
	}

	a_roOutEvent.m_enType = Me_NOTHING;
	return false;
}


/** MortalWaitEvent works like SDL_WaitEvent, except that it
returns an SMortalEvent.
*/
template <typename X>
void MortalWaitEvent(X &game, SMortalEvent& a_roOutEvent )
{
	SDL_Event oEvent;

	if ( SDL_WaitEvent( &oEvent ) )
	{
		if ( TranslateEvent(game, &oEvent, &a_roOutEvent ) )
		{
			return;
		}
	}

	a_roOutEvent.m_enType = Me_NOTHING;
	return;
}

#ifndef MAXPLAYERS
#define MAXPLAYERS 4
#endif
template <typename X>
bool FindPlayerKey(X &game, SDL_Keycode a_enKey, int& a_riOutPlayer, int& a_riOutKey )
{
	for (int i=0; i<MAXPLAYERS; i++)
	{
		for (int j=0; j<9; j++ )
		{
			if (game.g_oState->m_aiPlayerKeys[i][j] == a_enKey )
			{
				a_riOutPlayer = i;
				a_riOutKey = j;
				return true;
			}
		}
	}
	return false;
}

/**
TranslateEvent is an important function in the OpenMortal event processing
chain. It takes an SDL_Event and converts it to a game related event. This
allows for the "transparent" handling of joysticks and such.

\param a_poInEvent		The SDL event which is to be translated.
\param a_poOutEvent		The output event.

\returns true if the event could be translated (it was relevant for the game),
or false if it couldn't (a_poOutEvent will be set to Me_NOTHING).
*/
template <typename X>
bool TranslateEvent(X &game, const SDL_Event* a_poInEvent, SMortalEvent* a_poOutEvent )
{
	a_poOutEvent->m_enType = Me_NOTHING;

	switch ( a_poInEvent->type )
	{
	case SDL_QUIT:
		a_poOutEvent->m_enType = Me_QUIT;
		game.g_oState->m_bQuitFlag = true;
		return true;

	case SDL_KEYDOWN:
	{
		SDL_Keycode enKey = a_poInEvent->key.keysym.sym;
		if ( enKey == SDLK_ESCAPE )
		{
			a_poOutEvent->m_enType = Me_MENU;
			return true;
		}
		if ( enKey == 3 )
		{
			a_poOutEvent->m_enType = Me_SKIP;
			return true;
		}

		// Check the player keys
		int iPlayer;
		int iKey;
		bool bFound = FindPlayerKey<X>(game, enKey, iPlayer, iKey );

		if ( bFound )
		{
			a_poOutEvent->m_enType = Me_PLAYERKEYDOWN;
			a_poOutEvent->m_iPlayer = iPlayer;
			a_poOutEvent->m_iKey = iKey;
			return true;
		}
		break;
	}

	case SDL_KEYUP:
	{
		SDL_Keycode enKey = a_poInEvent->key.keysym.sym;
		int iPlayer;
		int iKey;
		bool bFound = FindPlayerKey<X>(game, enKey, iPlayer, iKey );

		if ( bFound )
		{
			a_poOutEvent->m_enType = Me_PLAYERKEYUP;
			a_poOutEvent->m_iPlayer = iPlayer;
			a_poOutEvent->m_iKey = iKey;
			return true;
		}
		break;
	}

	case SDL_JOYAXISMOTION:
	case SDL_JOYBALLMOTION:
	case SDL_JOYHATMOTION:
	case SDL_JOYBUTTONDOWN:
	case SDL_JOYBUTTONUP:
	{
		return NULL; //g_oJoystick.TranslateEvent( a_poInEvent, a_poOutEvent );
	}


	} // switch

	return false;
}

/**
Waits for a key event and returns it.

\param a_bTranslate		If this is true, then keypad events will also be
read and processed info keys (cursor, return and escape).
*/
template <typename X>
SDL_Keycode GetKey( X &game, bool a_bTranslate )
{
	//SGF::CInputMap<TMortalEventEnum> gameInput;
	SDL_Event oSdlEvent;
	SMortalEvent oEvent;

	while (SDL_WaitEvent(&oSdlEvent))
	{
		if ( SDL_KEYDOWN == oSdlEvent.type )
		{
			return oSdlEvent.key.keysym.sym;
		}
		if ( SDL_QUIT == oSdlEvent.type )

		{
			return SDLK_ESCAPE;
		}

		if ( ! a_bTranslate )
		{
			continue;
		}

		// Handle gamepad and others
		TranslateEvent<X>(game, &oSdlEvent, &oEvent );

		switch (oEvent.m_enType)
		{
			case Me_QUIT:
				//g_oState.m_bQuitFlag = true;
				return SDLK_ESCAPE;

			case Me_PLAYERKEYDOWN:
				switch ( oEvent.m_iKey ) {
					case Mk_UP:		return SDLK_UP;
					case Mk_DOWN:	return SDLK_DOWN;
					case Mk_LEFT:	return SDLK_LEFT;
					case Mk_RIGHT:	return SDLK_RIGHT;
					default:		return SDLK_RETURN;
				}
				break;

			case Me_MENU:
				return SDLK_ESCAPE;

			default:
				break;
		}	// switch statement
	}	// Polling events

	// Code will never reach this point, unless there's an error.
	return SDLK_ESCAPE;
}







#endif

