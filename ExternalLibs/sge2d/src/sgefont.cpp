/*
 * Copyright (c) 2007 Heiko Irrgang
 *
 * The license and distribution terms for this file may be
 * found in the file COPYING in this distribution or at
 * http://agnosent.com/wolfcms/open-source/sge2d/license.html
 */

#include "include\sgefont.h"



SGEFONT *sgeFontNew(int type) {
	SGEFONT *ret;
	sgeNew(ret, SGEFONT);
	ret->type=type;
	ret->alpha=0xff;
	ret->data=NULL;
	return ret;
}

SGEFONT *sgeFontNewFileBitmap(SGEFILE *f, const char *filename) {
	SGEFONT *ret=sgeFontNew(SGEFONT_BITMAP);
	SGEBITMAPFONT *data;
	int i=0;
	char *tmp;
	SGEPIXELINFO *pi;
	SGEBITMAPFONTINFO *fi;
	int offset=0;

	sgeMalloc(tmp,char,strlen(filename)+5);
	strcpy(tmp, filename);
	strcat(tmp,".map");

	sgeNew(data, SGEBITMAPFONT);
	data->bitmap=sgeReadImage(f,filename);
	data->charmap=(unsigned char *)sgeReadFile(f, tmp);
	//data->info=sgeArrayNew();

	for (i=0;i<data->bitmap->w;i++) {
		pi=sgeGetPixel(data->bitmap, i, 0);
		if (
				(
				 (pi->r==255) &&
				 (pi->g==0) &&
				 (pi->b==255) &&
				 (pi->a==255)
				) ||
				(i==data->bitmap->w-1)
		) {
			sgeNew(fi,SGEBITMAPFONTINFO);
			fi->offset=offset;
			fi->width=i-offset-1;
			//sgeArrayAdd(data->info,fi);
			data->info.addElement(fi);
			offset=i+1;
		}
		sgePixelInfoDestroy(pi);
	}

	ret->data=data;
	return ret;
}

SGEFONT *sgeFontNewFile(SGEFILE *f, int type, const char *filename) {
	switch (type) {
		case SGEFONT_BITMAP:
			return sgeFontNewFileBitmap(f, filename);
	}
	return NULL;
}

static void sgeFontDestroyBitmap(SGEFONT *f) {
	SGEBITMAPFONT *bfont;
	SGEBITMAPFONTINFO *bfi;

	bfont=(SGEBITMAPFONT *)f->data;
	SDL_FreeSurface(bfont->bitmap);
	sgeFree(bfont->charmap);
	while (bfont->info.getsize()>0) {
		bfi=bfont->info[0];//sgeArrayGet(bfont->info,0);
		sgeFree(bfi);
		bfont->info.removeElement(0);
		//sgeArrayRemove(bfont->info,0);
	}
	//sgeArrayDestroy(bfont->info);
	sgeFree(bfont);
}

void sgeFontDestroy(SGEFONT *f) {

	if (f->data!=NULL) {
		switch (f->type) {
			case SGEFONT_BITMAP:
				sgeFontDestroyBitmap(f);
				break;
		}
	}
	sgeFree(f);
}

int sgeFontGetLineHeightBitmap(SGEFONT *f) {
	SGEBITMAPFONT *bfont;
	bfont=(SGEBITMAPFONT *)f->data;
	return bfont->bitmap->h;
}

int sgeFontGetLineHeight(SGEFONT *f) {
	if (f->data==NULL) return -1;

	switch (f->type) {
		case SGEFONT_BITMAP:
			return sgeFontGetLineHeightBitmap(f);
	}
	return -1;
}

int sgeFontPrintBitmap(SGEFONT *f, SDL_Surface *dest, int x, int y, const char *text) {
	SGEBITMAPFONT *bfont;
	SGEBITMAPFONTINFO *bfi;
	int i;
	int xx=x;
	int c, idx;
	const char *pos;
	SDL_Rect src, dst;
	SDL_Surface *alphasurface;

	bfont=(SGEBITMAPFONT *)f->data;

	dst.y=y;
	src.h=bfont->bitmap->h;
	src.y=0;

	for (i=0;i<strlen(text);i++) {
		c=text[i];
		pos=strchr((const char *)bfont->charmap, c);
		if (pos!=NULL) {
			idx=pos-(char *)bfont->charmap;
			bfi=bfont->info[idx];//sgeArrayGet(bfont->info, idx);

			dst.x=xx;
			src.x=bfi->offset;
			src.w=bfi->width;
			xx+=bfi->width;

			if (f->alpha==0xff) {
				SDL_BlitSurface(bfont->bitmap, &src, dest, &dst);
			} else {
				alphasurface=sgeChangeSDLSurfaceAlpha(bfont->bitmap, f->alpha);
				SDL_BlitSurface(alphasurface,&src,dest,&dst);
				SDL_FreeSurface(alphasurface);
			}
		}
	}
	return xx-x;
}

int sgeFontPrint(SGEFONT *f, SDL_Surface *dest, int x, int y, const char *text) {
	switch (f->type) {
		case SGEFONT_BITMAP:
			return sgeFontPrintBitmap(f, dest, x, y, text);
	}
	return 0;
}

int sgeFontGetWidth(SGEFONT *f, const char *text) {
	switch (f->type) {
		case SGEFONT_BITMAP:
			return sgeFontGetWidthBitmap(f, text);
	}
	return 0;
}

void sgeFontIgnoreAlpha(SGEFONT *f) {
	SGEBITMAPFONT *bfont;
	bfont=(SGEBITMAPFONT *)f->data;
	sgeIgnoreAlpha(bfont->bitmap);
}

void sgeFontUseAlpha(SGEFONT *f) {
	SGEBITMAPFONT *bfont;
	bfont=(SGEBITMAPFONT *)f->data;
	sgeUseAlpha(bfont->bitmap);
}

int sgeFontGetWidthBitmap(SGEFONT *f, const char *text) {
	SGEBITMAPFONT *bfont;
	SGEBITMAPFONTINFO *bfi;
	int i;
	int c, idx;
	const char *pos;
	int ret=0;

	bfont=(SGEBITMAPFONT *)f->data;

	for (i=0;i<strlen(text);i++) {
		c=text[i];
		pos=strchr((const char *)bfont->charmap, c);
		if (pos!=NULL) {
			idx=pos-(char *)bfont->charmap;
			bfi=bfont->info[idx];//sgeArrayGet(bfont->info, idx);
			ret+=bfi->width;
		}
	}
	return ret;
}

static void sgeFontFXFadeUpdateHelper(void *data, int inout) {
	SGEFONTFX *fx=(SGEFONTFX *)data;
	SGEFONTFXFADEINFO *fadeInfo=(SGEFONTFXFADEINFO *)fx->data;
	SGESPRITE *sprite;
	Uint32 current=SDL_GetTicks()-fx->startTime;
	int per10k;
	int difx, dify;
	int i;
	int charPos=0;
	int finished=0;
	float ymul;
	float ydiv;

	current+=fx->charOffset;
	for (i=0;i<fx->textSprites.getsize();i++) {
		if (current>fx->charOffset) {
			current-=fx->charOffset;
			per10k=sgeFontFXGetPer10K(fx, current, fadeInfo->runtime, i, fx->textSprites.getsize());
		} else {
			per10k=sgeFontFXGetPer10K(fx, 0, fadeInfo->runtime, i, fx->textSprites.getsize());
		}
		if ( (fx->preDelay>0) && (fx->hideOnPreDelay) ) {
			return;
		}
		sprite=fx->textSprites[i];//sgeArrayGet(fx->textSprites,i);
		if (fadeInfo->fade) {
			if (per10k>9999) {
				if (inout==1) {
					sprite->alpha=255;
				} else {
					sprite->alpha=0;
				}
				finished++;
			} else {
				if (inout==1) {
					sprite->alpha=255*per10k/10000;
				} else {
					sprite->alpha=255-(255*per10k/10000);
				}
			}
		} else {
			sprite->alpha=255;
			if (per10k>9999) {
				finished++;
			}
		}
		sgeSpriteDraw(sprite, fx->surface);
		if (per10k<10000) {
			difx=fx->endx-fx->startx;
			dify=fx->endy-fx->starty;
			sprite->x=fx->startx+charPos+(difx*per10k/10000);
			if (fx->movement==SGEFONTFX_MOVE_BOUNCE) {
				if (per10k<4000) {
					ymul=cos(M_PI/180*((float)per10k*90/2000));
				} else if (per10k<8000) {
					ymul=cos(M_PI/180*((float)(per10k-4000)*90/2000));
				} else {
					ymul=cos(M_PI/180*((float)(per10k-8000)*90/2000));
				}
				if (per10k<2000) {
					ydiv=1;
				} else if (per10k<6000) {
					ydiv=.75;
				} else {
					ydiv=.4;
				}
				if (ymul<0) {
					ymul*=-1;
				}
				sprite->y=fx->endy-dify*ymul*ydiv;
			} else {
				sprite->y=fx->starty+(dify*per10k/10000);
			}
		} else {
			sprite->x=fx->endx+charPos;
			sprite->y=fx->endy;
		}
		charPos+=sgeSpriteWidth(sprite);
	}
	if (finished==fx->textSprites.getsize()) {
		sgeFontFXSetFinished(fx);
	}
}

void sgeFontFXFadeInUpdate(void *data) {
	sgeFontFXFadeUpdateHelper(data, 1);
}

void sgeFontFXFadeInDestroy(void *data) {
	SGEFONTFXFADEINFO *fadeInfo=(SGEFONTFXFADEINFO *)data;
	sgeFontFXFadeInfoDestroy(fadeInfo);
}

void sgeFontFXFadeOutUpdate(void *data) {
	sgeFontFXFadeUpdateHelper(data, 0);
}

void sgeFontFXFadeOutDestroy(void *data) {
	SGEFONTFXFADEINFO *fadeInfo=(SGEFONTFXFADEINFO *)data;
	sgeFontFXFadeInfoDestroy(fadeInfo);
}

void sgeFontFXFadeInOutUpdate(void *data) {
	SGEFONTFX *fx=(SGEFONTFX *)data;
	SGEFONTFXFADEINOUTINFO *info=(SGEFONTFXFADEINOUTINFO *)fx->data;

	if (info->fadeIn->finished==0) {
		sgeFontFXDraw(info->fadeIn);
		if (info->fadeIn->finished) {
			info->fadeOut->startTime=SDL_GetTicks()-100;
		}
	} else if (info->fadeOut->finished==0) {
		sgeFontFXDraw(info->fadeOut);
	} else {
		sgeFontFXSetFinished(fx);
	}
}

void sgeFontFXFadeInOutDestroy(void *data) {
	SGEFONTFXFADEINOUTINFO *fadeInfo=(SGEFONTFXFADEINOUTINFO *)data;
	sgeFontFXFadeInOutInfoDestroy(fadeInfo);
}

int sgeFontFXGetPer10K(SGEFONTFX *fx, Uint32 current, Uint32 runtime, Uint32 currentElement, Uint32 numberOfElements) {
	Uint32 ticks;
	if (fx->preDelay>0) {
		ticks=SDL_GetTicks();
		if (ticks<fx->startTime+fx->preDelay-current) {
			return 0;
		}
		if (currentElement==numberOfElements-1) {
			fx->startTime=ticks;
			fx->preDelay=0;
		}
		return 0;
	}
	if (current>runtime) return 10000;
	if (fx->movement==SGEFONTFX_MOVE_SLOWDOWN) {
		return (int) (10000*sin(M_PI/180*((float)current*10000/(float)runtime*90/10000)));
	}
	if (fx->movement==SGEFONTFX_MOVE_ACCELERATE) {
		return 10000-(int)(10000*cos(M_PI/180*((float)current*10000/(float)runtime*90/10000)));
	}
	return (int) (current*10000/runtime);
}

SGEFONTFX *sgeFontFXNew(SGEFONT *f, Uint32 fxtype, Uint8 movement, Uint32 runtime, Uint32 charOffset, int startx, int starty, int endx, int endy, const char *text) {
	SGEFONTFX *ret;
	SDL_Surface *tmp;
	SGESPRITE *sprite;
	SGEFONTFXFADEINFO *fadeInfo;
	SGEFONTFXFADEINOUTINFO *fadeInOutInfo;
	SGEFONTFXCOUNTDOWNINFO *countdownInfo;
	int i;
	int lineheight;
	char buf[2];
	int charPos=0;
	int charWidth;
	const char *usedText;
	Uint32 tmpruntime;

	if (fxtype==SGEFONTFX_COUNTDOWN) {
		charOffset=0;
		usedText=(const char *)&"000000000000";
	} else {
		usedText=text;
	}

	sgeNew(ret,SGEFONTFX);

	ret->type=fxtype;
	ret->runtime=runtime;
	ret->startx=startx;
	ret->starty=starty;
	ret->endx=endx;
	ret->endy=endy;
	ret->charOffset=charOffset;
	ret->finished=0;
	ret->startTime=SDL_GetTicks();
	ret->font=f;
	//s ret->surface=screen;
	ret->text=strdup(usedText);
	//ret->textSprites=sgeArrayNew();
	ret->movement=movement;
	ret->preDelay=0;
	ret->postDelay=0;
	ret->hideOnPreDelay=0;

	lineheight=sgeFontGetLineHeight(ret->font);
	sgeFontIgnoreAlpha(ret->font);
	if (ret->charOffset==0) {
		tmp=sgeCreateSDLSurface(sgeFontGetWidth(ret->font,ret->text),lineheight,32,SDL_HWSURFACE);
		sgeFontPrint(ret->font, tmp, 0, 0, ret->text);
		sprite=sgeSpriteNewSDLSurface(tmp);
		sprite->x=startx;
		sprite->y=starty;
		ret->textSprites.addElement(sprite);
		//sgeArrayAdd(ret->textSprites, sprite);
	} else {
		strcpy(buf," ");
		for (i=0;i<strlen(text);i++) {
			sprintf(buf, "%c",ret->text[i]);
			charWidth=sgeFontGetWidth(ret->font,buf);
			tmp=sgeCreateSDLSurface(charWidth,lineheight,32,SDL_HWSURFACE);
			sgeFontPrint(ret->font, tmp, 0, 0, buf);
			sprite=sgeSpriteNewSDLSurface(tmp);
			sprite->x=startx+charPos;
			sprite->y=starty;
			ret->textSprites.addElement( sprite);
			//sgeArrayAdd(ret->textSprites, sprite);
			charPos+=charWidth;
		}
	}
	sgeFontUseAlpha(ret->font);

	switch (fxtype) {
		case SGEFONTFX_FADE_IN:
			fadeInfo=sgeFontFXFadeInfoNew(runtime);
			ret->data=(void *)fadeInfo;
			ret->updateFunction=sgeFontFXFadeInUpdate;
			ret->freeFunction=sgeFontFXFadeInDestroy;
			break;
		case SGEFONTFX_FADE_OUT:
			fadeInfo=sgeFontFXFadeInfoNew(runtime);
			ret->data=(void *)fadeInfo;
			ret->updateFunction=sgeFontFXFadeOutUpdate;
			ret->freeFunction=sgeFontFXFadeOutDestroy;
			break;
		case SGEFONTFX_FADE_INOUT:
			tmpruntime=runtime>>1;
			fadeInOutInfo=sgeFontFXFadeInOutInfoNew(ret,tmpruntime,runtime-tmpruntime,1);
			ret->data=(void *)fadeInOutInfo;
			ret->updateFunction=sgeFontFXFadeInOutUpdate;
			ret->freeFunction=sgeFontFXFadeInOutDestroy;
			break;
		case SGEFONTFX_MOVE_IN:
			fadeInfo=sgeFontFXFadeInfoNew(runtime);
			fadeInfo->fade=0;
			ret->data=(void *)fadeInfo;
			ret->updateFunction=sgeFontFXFadeInUpdate;
			ret->freeFunction=sgeFontFXFadeInDestroy;
			break;
		case SGEFONTFX_MOVE_OUT:
			fadeInfo=sgeFontFXFadeInfoNew(runtime);
			fadeInfo->fade=0;
			ret->data=(void *)fadeInfo;
			ret->updateFunction=sgeFontFXFadeOutUpdate;
			ret->freeFunction=sgeFontFXFadeOutDestroy;
			break;
		case SGEFONTFX_MOVE_INOUT:
			tmpruntime=runtime>>1;
			fadeInOutInfo=sgeFontFXFadeInOutInfoNew(ret,tmpruntime,runtime-tmpruntime,0);
			ret->data=(void *)fadeInOutInfo;
			ret->updateFunction=sgeFontFXFadeInOutUpdate;
			ret->freeFunction=sgeFontFXFadeInOutDestroy;
			break;
		case SGEFONTFX_COUNTDOWN:
			countdownInfo=sgeFontFXCountdownInfoNew(runtime);
			ret->data=(void *)countdownInfo;
			ret->updateFunction=sgeFontFXCountdownUpdate;
			ret->freeFunction=sgeFontFXCountdownDestroy;
			break;
		default:
			sgeBailOut("Unknown font effect: %d\n", fxtype);
	}
	return ret;
}

void sgeFontFXDraw(SGEFONTFX *fx) {
	(fx->updateFunction)((void *)fx);
}

void sgeFontFXDestroy(SGEFONTFX *fx) {
	int i;
	SGESPRITE *sprite;

	for (i=fx->textSprites.getsize()-1;i>-1;i--) {
		sprite=fx->textSprites[i];//sgeArrayGet(fx->textSprites,i);
		sgeSpriteDestroy(sprite);
		fx->textSprites.removeElement(i);
		//sgeArrayRemove(fx->textSprites,i);
	}
	//sgeArrayDestroy(fx->textSprites);
	sgeFree(fx->text);
	(fx->freeFunction)(fx->data);
	sgeFree(fx);
}

SGEFONTFXFADEINFO *sgeFontFXFadeInfoNew(Uint32 runtime) {
	SGEFONTFXFADEINFO *ret;
	sgeNew(ret, SGEFONTFXFADEINFO);
	ret->runtime=runtime;
	ret->fade=1;
	return ret;
}

void sgeFontFXFadeInfoDestroy(SGEFONTFXFADEINFO *fi) {
	sgeFree(fi);
}

SGEFONTFXFADEINOUTINFO *sgeFontFXFadeInOutInfoNew(SGEFONTFX *fx, Uint32 runtimein, Uint32 runtimeout,Uint8 fade) {
	SGEFONTFXFADEINOUTINFO *ret;
	int difxhalf, difyhalf;
	Uint8 movementin;
	Uint8 movementout;
	Uint32 effectin,effectout;

	difxhalf=(fx->endx-fx->startx)/2;
	difyhalf=(fx->endy-fx->starty)/2;

	switch (fx->movement) {
		case SGEFONTFX_MOVE_SLOWDOWN:
			movementin=SGEFONTFX_MOVE_SLOWDOWN;
			movementout=SGEFONTFX_MOVE_ACCELERATE;
			break;
		case SGEFONTFX_MOVE_ACCELERATE:
			movementin=SGEFONTFX_MOVE_ACCELERATE;
			movementout=SGEFONTFX_MOVE_SLOWDOWN;
			break;
		default:
			movementin=fx->movement;
			movementout=fx->movement;
			break;
	}

	sgeNew(ret, SGEFONTFXFADEINOUTINFO);
	if (fade) {
		effectin=SGEFONTFX_FADE_IN;
		effectout=SGEFONTFX_FADE_OUT;
	} else {
		effectin=SGEFONTFX_MOVE_IN;
		effectout=SGEFONTFX_MOVE_OUT;
	}
	ret->fadeIn=sgeFontFXNew(fx->font, effectin, movementin, runtimein, fx->charOffset, fx->startx, fx->starty, fx->startx+difxhalf, fx->starty+difyhalf, fx->text);
	ret->fadeOut=sgeFontFXNew(fx->font, effectout, movementout, runtimeout, fx->charOffset, fx->startx+difxhalf, fx->starty+difyhalf, fx->endx, fx->endy, fx->text);
	return ret;
}

void sgeFontFXFadeInOutInfoDestroy(SGEFONTFXFADEINOUTINFO *fi) {
	sgeFontFXDestroy(fi->fadeIn);
	sgeFontFXDestroy(fi->fadeOut);
	sgeFree(fi);
}

SGEFONTFXCOUNTDOWNINFO *sgeFontFXCountdownInfoNew(Uint32 runtime) {
	SGEFONTFXCOUNTDOWNINFO *ret;
	sgeNew(ret, SGEFONTFXCOUNTDOWNINFO);
	ret->start=10;
	ret->end=0;
	ret->runtime=runtime;
	return ret;
}

void sgeFontFXCountdownInfoDestroy(SGEFONTFXCOUNTDOWNINFO *fi) {
	sgeFree(fi);
}

void sgeFontFXCountdownUpdate(void *data) {
	SGEFONTFX *fx=(SGEFONTFX *)data;
	SGEFONTFXCOUNTDOWNINFO *info=(SGEFONTFXCOUNTDOWNINFO *)fx->data;
	Sint32 tmp=info->end-info->start;
	Uint32 current=SDL_GetTicks()-fx->startTime;
	int per10k;
	char buf[256];
	SGESPRITE *sprite;
	SDL_Surface *surface;
	int difx, dify;

	per10k=sgeFontFXGetPer10K(fx, current, info->runtime, 0, 1);
	if ( (fx->preDelay>0) && (fx->hideOnPreDelay) ) {
		return;
	}
	if (per10k>9999) {
		sgeFontFXSetFinished(fx);
		sprintf(buf, "%d", info->end);
	} else {
		if (abs(tmp)>100000) {
			sprintf(buf, "%d", (int) (info->start+(tmp/10000*per10k)));
		} else {
			sprintf(buf, "%d", (int) (info->start+(tmp*per10k/10000)));
		}
	}
	sprite=fx->textSprites[0];//sgeArrayGet(fx->textSprites,0);
	difx=fx->endx-fx->startx;
	dify=fx->endy-fx->starty;
	sprite->x=fx->startx+(difx*per10k/10000);
	sprite->y=fx->starty+(dify*per10k/10000);

	surface=sgeSpriteGetSDLSurface(sprite);
	sgeFillRect(surface, 0, 0, surface->w, surface->h, sgeMakeColor(surface,0x00,0x00,0x00,0x00));
	sgeFontIgnoreAlpha(fx->font);
	sgeFontPrint(fx->font, surface, 0, 0, buf);
	sgeSpriteDraw(sprite, fx->surface);
	sgeFontUseAlpha(fx->font);
}

void sgeFontFXCountdownDestroy(void *data) {
	SGEFONTFXCOUNTDOWNINFO *info=(SGEFONTFXCOUNTDOWNINFO *)data;
	sgeFontFXCountdownInfoDestroy(info);
}

void sgeFontFXCountdownSetValues(SGEFONTFX *fx, Sint32 start, Sint32 end) {
	SGEFONTFXCOUNTDOWNINFO *fi=(SGEFONTFXCOUNTDOWNINFO *)fx->data;
	fi->start=start;
	fi->end=end;
}

void sgeFontFXPreDelay(SGEFONTFX *fx, Uint32 delay) {
	fx->preDelay=delay;
}

void sgeFontFXPostDelay(SGEFONTFX *fx, Uint32 delay) {
	fx->postDelay=delay;
}

void sgeFontFXSetFinished(SGEFONTFX *fx) {
	if (!fx->finished) fx->finishTime=SDL_GetTicks();
	fx->finished=1;
}

int sgeFontFXFinished(SGEFONTFX *fx) {
	if ( (fx->finished) && (SDL_GetTicks()>=fx->finishTime+fx->postDelay) ) {
		return 1;
	}
	return 0;
}

void sgeFontFXHideOnPreDelay(SGEFONTFX *fx, Uint8 yesno) {
	fx->hideOnPreDelay=yesno;
}

void sgeFontFXSetTarget(SGEFONTFX *fx, SDL_Surface *surface) {
	fx->surface=surface;
}
