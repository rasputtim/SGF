/*
 * Copyright (c) 2007 Heiko Irrgang
 *
 * The license and distribution terms for this file may be
 * found in the file COPYING in this distribution or at
 * http://agnosent.com/wolfcms/open-source/sge2d/license.html
 */

#include <sge.h>

SDL_Surface *screen;

void sgeOpenScreen(const char *title, int width, int height, int depth, int fullscreen) {
	Uint32 flags=_DEFAULT_VIDEOMODE_FLAGS_;

	if (fullscreen) {
		flags|=SDL_FULLSCREEN;
	}

	screen=SDL_SetVideoMode(width, height, depth, flags);
	if (screen==NULL) {
		sgeBailOut("error opening screen: %s\n", SDL_GetError());
	}
	SDL_WM_SetCaption(title, NULL);
}

void sgeHideMouse() {
	SDL_ShowCursor(SDL_DISABLE);
}

void sgeShowMouse() {
	SDL_ShowCursor(SDL_ENABLE);
}

void sgeCloseScreen() {
}

inline void sgeFlip(void) {
        SDL_Flip(screen);
}
