/*
  SGF - Super Game Fabric  Super Game Fabric
  Copyright (C) 2010-2011 Rasputtim <raputtim@hotmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

  */

#include "gui/SGF_FadetoolGui.h"
#include "graphics/all.h"
#include "exceptions/all.h"
#include "util/SGF_Util.h"

using namespace std;
namespace SGF{

static Uint8 clamp(Uint8 in, Uint8 low = 0, Uint8 high = 255){
    return static_cast<Uint8>(Util::clamp(static_cast<int>(in),static_cast<int>(low),static_cast<int>(high)));
}

Gui::CFadeTool::CFadeTool():
currentState(FadeIn),
lastState(FadeIn),
fadeTime(0),
fadeInTime(0),
fadeOutTime(0),
fadeInColor(Colors::Transparent),
fadeOutColor(Colors::Transparent){
}

Gui::CFadeTool::~CFadeTool(){
}

void Gui::CFadeTool::act(){
    switch (currentState){
	case FadeIn:
	    fadeTime-=(255/(fadeInTime <= 0 ? 1 : fadeInTime));
	    if (fadeTime<=0){
		setState(NoFade);
	    }
	    break;
	case FadeOut:
	    fadeTime+=(255/(fadeOutTime <= 0 ? 1 : fadeOutTime));
	    if (fadeTime>=255){
		setState(EndFade);
	    }
	    break;
	case NoFade:
	case EndFade:
	default:
	    break;
    }
}

void Gui::CFadeTool::setState( const State & f){
    lastState = currentState;
    currentState = f;

    switch (currentState){
	case FadeIn:
	    fadeTime = 255;
	    break;
	case FadeOut:
	    fadeTime = 0;
	    break;
	case NoFade:
	case EndFade:
	default:
	    fadeTime = 0;
	    break;
    }
}
void Gui::CFadeTool::draw(const CBitmap &bmp){
	bmp.setBitmapMode(CBitmap::DRAW_TYPE_SURFACE);
    switch (currentState){
	case FadeIn:
	    // CBitmap::drawingMode(CBitmap::MODE_TRANS);
	    CBitmap::transBlender(0,0,0,fadeTime);
	    bmp.translucent().rectangleFill(0, 0, bmp.getWidth(),bmp.getHeight(),fadeInColor);
	    // CBitmap::drawingMode(CBitmap::MODE_SOLID);
	    break;
	case FadeOut:
	    // CBitmap::drawingMode(CBitmap::MODE_TRANS);
	    CBitmap::transBlender(0,0,0,fadeTime);
	    bmp.translucent().rectangleFill(0, 0, bmp.getWidth(),bmp.getHeight(),fadeOutColor);
	    // CBitmap::drawingMode(CBitmap::MODE_SOLID);
	    break;
	case NoFade:
	case EndFade:
	default:
	    break;
    }
	bmp.setBitmapMode(CBitmap::DRAW_TYPE_DEFAULT);
}

void Gui::CFadeTool::parseDefaults(const Token * token) throw (CLoadException){
//s    if ( *token != "fade" ){
   //     throw CLoadException(__FILE__, __LINE__, "Not a fader");
  //  }
    /*!
     * (fade
        (in (color 0 0 0) (time 0) )
        (out (color 0 0 0) (time 0) ))
    */
    const Token & ourToken = *token;
    TokenView view = ourToken.view();
    /* FIXME: this code looks like its expecting a structure like
     *  (in (color ...) (out ...))
     * But its not parsing that way, rewrite it
     */
    while (view.hasMore()){
        try{
            const Token * tok;
            view >> tok;
            if (*tok == "in"){
                TokenView inView = tok->view();
                /* FIXME: this loop is pretty wierd, shouldn't the if's be on the outside? */
                while (inView.hasMore()){
                    if (*tok == "color"){
                        int r=0,g=0,b=0;
                        try {
                            inView >> r >> g >> b;
                        } catch (const CTokenException & ex){
                         Debug::debug(1,__FUNCTION__) << "There was a problem with the token. Error was:\n  " << ex.getTrace() << endl;
						}
						Colors::ColorDefinition tempColor = { clamp(r),clamp(g),clamp(b)};
                        setFadeInColor(tempColor);
                    } else if (*tok == "time"){
                        int time=0;
                        try {
                            inView >> time;
                        } catch (const CTokenException & ex){
                         Debug::debug(1,__FUNCTION__) << "There was a problem with the token. Error was:\n  " << ex.getTrace() << endl;
						}
                        setFadeInTime(time);
                    }
                }
            } else if (*tok == "out"){
                /*
                Token & out = *tok;
                while (out.hasTokens()){
                    if (out == "color"){
                        int r=0,g=0,b=0;
                        try {
                            out >> r >> g >> b;
                        } catch (const CTokenException & ex){
                        }
                        setFadeOutColor(CBitmap::makeColor(r,b,g));
                    } else if (out == "time"){
                        int time=0;
                        try {
                            out >> time;
                        } catch (const CTokenException & ex){
                        }
                        setFadeOutTime(time);
                    }
                }
            */
            }
        } catch ( const CTokenException & ex ) {
            throw CLoadException(__FILE__, __LINE__, ex, "Fade tool parse error");
        } catch ( const CLoadException & ex ) {
            throw ex;
        }
    }
}
} //end SGF