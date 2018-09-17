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

#include "graphics/all.h"
#include "gui/SGF_PopupBox.h"

using namespace std;
using namespace std;
namespace SGF{

using namespace Gui;

CPopupBox::CPopupBox():
fadeState(Closed),
fadeSpeed(12){
}

CPopupBox::CPopupBox( const CPopupBox & copy ):
fadeState(Closed){
    this->fadeSpeed = copy.fadeSpeed;
}

CPopupBox::~CPopupBox(){
}

CPopupBox & CPopupBox::operator=( const CPopupBox & copy){
    this->fadeState = Closed;
    this->fadeSpeed = copy.fadeSpeed;
    return *this;
}

void CPopupBox::act(const CFont & font){
    // do fade
    doFade();
}

void CPopupBox::render(const CBitmap & work){
	Debug::debug(Debug::gui,__FUNCTION__) << "BEGIN  [CBitmap: ( "<<&work <<" )]  " <<  endl;
	    board.render(work);
	Debug::debug(Debug::gui,__FUNCTION__) << "BEGIN  [CBitmap: ( "<<&work <<" )]  " <<  endl;
}

void CPopupBox::open(){
	Debug::debug(Debug::gui,__FUNCTION__) << "BEGIN "<< endl;
    // Set the fade stuff
    fadeState = FadeIn;
	Debug::debug(Debug::gui,__FUNCTION__) << "Will Set up board Location (x,y): "<< location.getX()<< " , " << location.getY() <<  endl;

    board.location = location;
	board.transforms = transforms;
    board.colors = colors;
	Debug::debug(Debug::gui,__FUNCTION__) << "Will Center board Location (x,y): "<< board.location.getX()<< " , " << board.location.getY() <<  endl;
    board.location.center(location);
	Debug::debug(Debug::gui,__FUNCTION__) << "Seted up Centered board Location (x,y): "<< board.location.getX()<< " , " << board.location.getY() <<  endl;

    board.colors.border.a = board.colors.body.a = 0;
	Debug::debug(Debug::menu,__FUNCTION__) << "END "<< endl;
}

void CPopupBox::close(){
    fadeState = FadeOut;
}

void CPopupBox::doFade(){
    switch (fadeState){
        case FadeIn: {
            board.location.growTo(location, 0.0025 * fadeSpeed);
            if (board.colors.border.a < colors.border.a){
                board.colors.border.a += (int)(fadeSpeed/2);
                if (board.colors.border.a >= colors.border.a){
                    board.colors.border.a = colors.border.a;
                }
            }
            if (board.colors.body.a < colors.body.a){
                board.colors.body.a += (int)(fadeSpeed/2);
                if (board.colors.body.a >= colors.body.a){
                    board.colors.body.a = colors.body.a;
                }
            }

            if (board.location == location && board.colors.body.a == colors.body.a && board.colors.border.a == colors.border.a){
                fadeState = Open;
            }

            break;
        }
        case FadeOut: {
            CCoordinate coord;
            coord.center(location);
            board.location.growTo(coord, 0.0025 * fadeSpeed);

            if (board.colors.border.a > 0){
                board.colors.border.a -= (int)(fadeSpeed/2);
                if (board.colors.border.a <= 0){
                    board.colors.border.a = 0;
                }
            }
            if (board.colors.body.a > 0){
                board.colors.body.a -= (int)(fadeSpeed/2);
                if (board.colors.body.a <= 0){
                    board.colors.body.a = 0;
                }
            }
            if (board.location.empty() && board.colors.border.a == 0 && board.colors.body.a == 0){
                fadeState = Closed;
            }
            break;
        }
        case Open:
        case Closed:
        default:
            break;
    }
}
} //end SGF