/*
 * Copyright (c) 2007 Heiko Irrgang
 *
 * The license and distribution terms for this file may be
 * found in the file COPYING in this distribution or at
 * http://agnosent.com/wolfcms/open-source/sge2d/license.html
 */

#include <sge.h>

static SGEFADEFX *sgeFadeFXInit(SGEFADEFX *ret, Uint32 type, Uint32 runTime) {
	ret->type=type;
	ret->runTime=runTime;
	ret->startTime=SDL_GetTicks();
	ret->realStartTime=ret->startTime;
	ret->finished=0;
	ret->deleteSurfaces=NO;
	ret->preDelay=0;
	ret->postDelay=0;
	ret->surface=screen;

	switch (type) {
		case SGEFADEFX_FADE:
			ret->updateFunction=sgeFadeFXFadeUpdate;
			break;
		case SGEFADEFX_WIPE_LEFT:
		case SGEFADEFX_WIPE_RIGHT:
		case SGEFADEFX_WIPE_TOP:
		case SGEFADEFX_WIPE_BOTTOM:
		case SGEFADEFX_SCROLL_LEFT:
		case SGEFADEFX_SCROLL_RIGHT:
		case SGEFADEFX_SCROLL_TOP:
		case SGEFADEFX_SCROLL_BOTTOM:
			ret->updateFunction=sgeFadeFXWipeScrollUpdate;
			break;
		default:
			sgeBailOut("Unknown fade effect: %d\n", type);
	}

	return ret;
}

SGEFADEFX *sgeFadeFXNew(Uint32 type, Uint32 runTime, SGESPRITE *source, SGESPRITE *destination) {
	SGEFADEFX *ret;
	sgeNew(ret, SGEFADEFX);
	ret->srcSprite=source;
	ret->dstSprite=destination;
	ret->src=sgeSpriteGetSDLSurface(source);
	ret->dst=sgeSpriteGetSDLSurface(destination);
	return sgeFadeFXInit(ret, type, runTime);
}

SGEFADEFX *sgeFadeFXNewSDLSurface(Uint32 type, Uint32 runTime, SDL_Surface *source, SDL_Surface *destination) {
	SGEFADEFX *ret;
	sgeNew(ret, SGEFADEFX);
	ret->srcSprite=NULL;
	ret->dstSprite=NULL;
	ret->src=source;
	ret->dst=destination;
	return sgeFadeFXInit(ret, type, runTime);
}

void sgeFadeFXDestroy(SGEFADEFX *fx) {
	if (fx->deleteSurfaces) {
		if (fx->srcSprite==NULL) {
			SDL_FreeSurface(fx->src);
			SDL_FreeSurface(fx->dst);
		} else {
			sgeSpriteDestroy(fx->srcSprite);
			sgeSpriteDestroy(fx->dstSprite);
		}
	}
	sgeFree(fx);
}

void sgeFadeFXDraw(SGEFADEFX *fx) {
	if (fx->preDelay>0) {
		if (SDL_GetTicks()-fx->realStartTime>fx->preDelay) {
			fx->preDelay=0;
		}
		fx->startTime=SDL_GetTicks();
		fx->current=0;
	} else {
		fx->current=SDL_GetTicks()-fx->startTime;
	}
	(fx->updateFunction)((void *)fx);
	if (fx->postDelay>0) {
		if (SDL_GetTicks()>(fx->startTime+fx->runTime))
			if (SDL_GetTicks()-(fx->startTime+fx->runTime)>fx->postDelay) {
				fx->finished=1;
			}
	} else {
		if (SDL_GetTicks()-fx->startTime>fx->runTime) {
			fx->finished=1;
		}
	}
}

void sgeFadeFXDeleteSurfaces(SGEFADEFX *fx, Uint8 yesno) {
	fx->deleteSurfaces=yesno;
}

int sgeFadeFXFinished(SGEFADEFX *fx) {
	return fx->finished;
}

void sgeFadeFXPreDelay(SGEFADEFX *fx, Uint32 delay) {
	fx->preDelay=delay;
}

void sgeFadeFXPostDelay(SGEFADEFX *fx, Uint32 delay) {
	fx->postDelay=delay;
}

void sgeFadeFXSetTarget(SGEFADEFX *fx, SDL_Surface *surface) {
	fx->surface=surface;
}

void sgeFadeFXFadeUpdate(void *fxdata) {
	SGEFADEFX *fx=(SGEFADEFX *)fxdata;
	Uint8 alpha;
	SDL_Surface *tmp;

	if (fx->current<fx->runTime) {
		alpha=255*fx->current/fx->runTime;
	} else {
		alpha=255;
	}

	if (alpha<255) {
		SDL_BlitSurface(fx->src,NULL,fx->surface,NULL);
		tmp=sgeChangeSDLSurfaceAlpha(fx->dst,alpha);
		SDL_BlitSurface(tmp,NULL,fx->surface,NULL);
		SDL_FreeSurface(tmp);
	} else {
		SDL_BlitSurface(fx->dst,NULL,fx->surface,NULL);
	}
}

void sgeFadeFXWipeScrollUpdate(void *fxdata) {
	SGEFADEFX *fx=(SGEFADEFX *)fxdata;
	SDL_Rect srcrectsrc, dstrectsrc, srcrectdst, dstrectdst;
	Uint32 srcwidth, dstwidth;
	Uint32 srcheight, dstheight;

	if (fx->current>fx->runTime) {
		SDL_BlitSurface(fx->dst, NULL, fx->surface, NULL);
		return;
	}

	srcrectsrc.x=0;
	srcrectsrc.y=0;
	srcrectdst.x=0;
	srcrectdst.y=0;
	dstrectsrc.x=0;
	dstrectsrc.y=0;
	dstrectdst.x=0;
	dstrectdst.y=0;


	switch (fx->type) {
		case SGEFADEFX_SCROLL_RIGHT:
			dstwidth=fx->surface->w*fx->current/fx->runTime;
			srcwidth=fx->surface->w-dstwidth;

			srcrectsrc.x=fx->src->w-srcwidth;
			srcrectsrc.w=srcwidth;
			dstrectsrc.w=dstwidth;
			dstrectdst.x=srcwidth+1;

			srcrectsrc.h=fx->src->h;
			dstrectsrc.h=fx->dst->h;
			break;
		case SGEFADEFX_SCROLL_LEFT:
			dstwidth=fx->surface->w*fx->current/fx->runTime;
			srcwidth=fx->surface->w-dstwidth;

			dstrectsrc.x=fx->dst->w-dstwidth;
			dstrectsrc.w=dstwidth;
			srcrectdst.x=dstwidth+1;
			srcrectsrc.w=srcwidth;

			srcrectsrc.h=fx->src->h;
			dstrectsrc.h=fx->dst->h;
			break;
		case SGEFADEFX_SCROLL_TOP:
			dstheight=fx->surface->h*fx->current/fx->runTime;
			srcheight=fx->surface->h-dstheight;

			dstrectsrc.y=fx->dst->h-dstheight;
			dstrectsrc.h=dstheight;
			srcrectdst.y=dstheight+1;
			srcrectsrc.h=srcheight;

			srcrectsrc.w=fx->src->w;
			dstrectsrc.w=fx->dst->w;
			break;
		case SGEFADEFX_SCROLL_BOTTOM:
			dstheight=fx->surface->h*fx->current/fx->runTime;
			srcheight=fx->surface->h-dstheight;

			srcrectsrc.y=fx->src->h-srcheight;
			srcrectsrc.h=srcheight;
			dstrectsrc.h=dstheight;
			dstrectdst.y=srcheight+1;

			srcrectsrc.w=fx->src->w;
			dstrectsrc.w=fx->dst->w;
			break;
		case SGEFADEFX_WIPE_RIGHT:
			dstwidth=fx->surface->w*fx->current/fx->runTime;
			srcwidth=fx->surface->w-dstwidth;

			srcrectsrc.w=srcwidth;

			dstrectsrc.x=srcwidth+1;
			dstrectsrc.w=dstwidth;
			dstrectdst.x=srcwidth+1;

			srcrectsrc.h=fx->src->h;
			dstrectsrc.h=fx->dst->h;
			break;
		case SGEFADEFX_WIPE_TOP:
			dstheight=fx->surface->h*fx->current/fx->runTime;
			srcheight=fx->surface->h-dstheight;

			srcrectsrc.y=dstheight+1;
			srcrectsrc.h=srcheight;
			srcrectdst.y=dstheight+1;

			dstrectsrc.h=dstheight;

			srcrectsrc.w=fx->src->w;
			dstrectsrc.w=fx->dst->w;
			break;
		case SGEFADEFX_WIPE_BOTTOM:
			dstheight=fx->surface->h*fx->current/fx->runTime;
			srcheight=fx->surface->h-dstheight;

			srcrectsrc.h=srcheight;

			dstrectsrc.y=srcheight+1;
			dstrectsrc.h=dstheight;
			dstrectdst.y=srcheight+1;

			srcrectsrc.w=fx->src->w;
			dstrectsrc.w=fx->dst->w;
			break;
		default:
			dstwidth=fx->surface->w*fx->current/fx->runTime;
			srcwidth=fx->surface->w-dstwidth;

			srcrectsrc.x=dstwidth+1;
			srcrectsrc.w=srcwidth;
			srcrectdst.x=dstwidth+1;

			dstrectsrc.w=dstwidth;

			srcrectsrc.h=fx->src->h;
			dstrectsrc.h=fx->dst->h;
			break;
	}

	SDL_BlitSurface(fx->src, &srcrectsrc, fx->surface, &srcrectdst);
	SDL_BlitSurface(fx->dst, &dstrectsrc, fx->surface, &dstrectdst);
}

