/*
 * Copyright (c) 2007 Heiko Irrgang
 *
 * The license and distribution terms for this file may be
 * found in the file COPYING in this distribution or at
 * http://agnosent.com/wolfcms/open-source/sge2d/license.html
 */

#include <sge.h>
#include <assert.h>

SGEGAMESTATEMANAGER* sgeGameStateManagerNew(void)
{
	SGEGAMESTATEMANAGER *ret;
	sgeNew(ret, SGEGAMESTATEMANAGER);
	return ret;
}

SGEGAMESTATE* sgeGameStateNew(void)
{
	SGEGAMESTATE *ret;
	sgeNew(ret, SGEGAMESTATE);
	return ret;
}

void sgeGameStateManagerQuit(SGEGAMESTATEMANAGER *manager)
{
	manager->quit = 1;
}

int sgeGameStateManagerChange(SGEGAMESTATEMANAGER *manager, SGEGAMESTATE *next_state)
{
	if (manager->current && manager->current->onStateChange) {
		if (!manager->current->onStateChange(manager->current, next_state)) {
			return 0;
		}
	}
	manager->current = next_state;
	next_state->manager = manager;
	return 1;
}

void sgeGameStateManagerRun(SGEGAMESTATEMANAGER *manager, int fps)
{
	SDL_Event event;
	SGETIMER t;
	sgeClearEvents();
	t=sgeStartRedrawTimer(fps);

	assert(manager->current);
	manager->quit = 0;

	while (SDL_WaitEvent(&event) && !manager->quit) {
		switch (event.type) {
			case SDL_USEREVENT:
				if (event.user.code==SGEREDRAW && manager->current->onRedraw) {
					manager->current->onRedraw(manager->current);
				}
				sgeEventResetInputs(&manager->event_state);
				break;
			case SDL_KEYDOWN:
				if (manager->current->onKeyDown!=NULL) {
					if (manager->current->onKeyDown(manager->current, &event)) {
						break;
					}
				}
				sgeEventApply(&manager->event_state, &event);
				break;
			case SDL_KEYUP:
				if (manager->current->onKeyUp!=NULL) {
					if (manager->current->onKeyUp(manager->current, &event)) {
						break;
					}
				}
				sgeEventApply(&manager->event_state, &event);
				break;
			case SDL_JOYBUTTONUP:
				if (manager->current->onJoystickButtonUp!=NULL) {
					if (manager->current->onJoystickButtonUp(manager->current, &event)) {
						break;
					}
				}
				sgeEventApply(&manager->event_state, &event);
				break;
			case SDL_JOYBUTTONDOWN:
				if (manager->current->onJoystickButtonDown!=NULL) {
					if (manager->current->onJoystickButtonDown(manager->current, &event)) {
						break;
					}
				}
				sgeEventApply(&manager->event_state, &event);
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (manager->current->onMouseDown!=NULL) {
					manager->current->onMouseDown(manager->current, &event);
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (manager->current->onMouseUp!=NULL) {
					manager->current->onMouseUp(manager->current, &event);
				}
				break;
			case SDL_MOUSEMOTION:
				if (manager->current->onMouseMove!=NULL) {
					manager->current->onMouseMove(manager->current, &event);
				}
				break;
			case SDL_JOYAXISMOTION:
				if (manager->current->onJoystickMove!=NULL) {
					manager->current->onJoystickMove(manager->current, &event);
				}
				break;
			case SDL_QUIT:
				manager->quit = 1;
				break;
		}
	}

	sgeStopRedrawTimer(t);
}
