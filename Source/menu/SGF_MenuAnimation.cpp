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
#include "menu/SGF_MenuAnimation.h"

#include <vector>
#include <math.h>
#include <sstream>
#include "util/SGF_Token.h"
#include "graphics/all.h"
#include "SGF_Global.h"
#include "resource/all.h"

using namespace std;
namespace SGF {

// Temporary solution
static void renderSprite(const CBitmap *pBmp, const int x, const int y, const int alpha, const bool hflip, const bool vflip, CBitmap *work){
    if (alpha != 255){
	CBitmap::transBlender( 0, 0, 0, alpha );
	if (hflip && !vflip){
		pBmp->translucent().drawHFlip(x,y, *work);
	} else if (!hflip && vflip){
	    pBmp->translucent().drawVFlip(x,y, *work);
	} else if (hflip && vflip){
	    pBmp->translucent().drawHVFlip(x,y, *work);
	} else if (!hflip && !vflip){
	    pBmp->translucent().draw(x,y, *work);
	}
    }
    else {
	if (hflip && !vflip){
	    pBmp->drawHFlip(x,y,NULL, *work);
	} else if (!hflip && vflip){
	    pBmp->drawVFlip(x,y,NULL, *work);
	} else if (hflip && vflip){
	    pBmp->drawHVFlip(x,y,NULL, *work);
	} else if (!hflip && !vflip){
	    pBmp->draw(x,y,NULL, *work);
	}
    }
}

MenuPoint::MenuPoint():x(0),y(0){}
MenuArea::MenuArea():x1(0),y1(0),x2(0),y2(0){}

CMenuFrame::CMenuFrame( const Token *the_token, imageMap &images) throw(CLoadException):
pBmp(0),
time(0),
horizontalFlip(false),
verticalFlip(false),
alpha(255){
    Debug::debug(Debug::menu,__FUNCTION__) << "CONSTRUCTOR // CMenuFrame //" << endl;
	if ( *the_token != "frame" ){
        throw CLoadException(__FILE__, __LINE__,"Not an frame");
    }
    Token tok(*the_token);
    /* The usual setup of an animation frame is
    // use image -1 to not draw anything, it can be used to get a blinking effect
    (frame (image NUM) (alpha NUM) (offset x y) (hflip 0|1) (vflip 0|1) (time NUM))
    */
		TokenView view = tok.view();
      while ( view.hasMore()){
        try{
            const Token * token;
            view >> token;
            if (*token == "image"){
                // get the number
                int num;
                token->view() >> num;
                // now assign the bitmap
                pBmp = images[num];
            } else if (*token == "alpha"){
                // get alpha
                token->view()  >> alpha;
            } else if (*token == "offset"){
                // Get the offset location it defaults to 0,0
                token->view()  >> offset.x >> offset.y;
            } else if (*token == "hflip"){
                // horizontal flip
                token->view()  >> horizontalFlip;
            } else if (*token == "vflip"){
                // horizontal flip
                token->view()  >> verticalFlip;
            } else if (*token == "time"){
                // time to display
                token->view()  >> time;
            } else {
                Debug::debug( 3,__FUNCTION__ ) << "CMenuFrame::CMenuFrame - Unhandled menu attribute"<<": "<<endl;
               // if (Debug::getDebug() >= 3){
               //     token->print(" ");
               // }
            }
        } catch ( const CTokenException & ex ) {
            string m( "CMenuFrame::CMenuFrame - Menu::CMenu_v1 parse error: " );
            m += ex.getTrace();
            throw CLoadException(__FILE__, __LINE__, m);
        } catch ( const CLoadException & ex ) {
            throw ex;
        }
    }
}

CMenuFrame::~CMenuFrame(){
}

void CMenuFrame::act(const double xvel, const double yvel){
    Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN // CMenuFrame::act //" << endl;
	scrollOffset.x +=xvel;
    scrollOffset.y +=yvel;
    if (scrollOffset.x >=pBmp->getWidth()){
	scrollOffset.x = 0;
    } else if (scrollOffset.x <= -(pBmp->getWidth())){
	scrollOffset.x = 0;
    }
    if (scrollOffset.y >=pBmp->getHeight()){
	scrollOffset.y = 0;
    } else if (scrollOffset.y <= -(pBmp->getHeight())){
	scrollOffset.y = 0;
    }
	Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN // CMenuFrame::act //" << endl;
}

static bool closeFloat(double a, double b){
    const double epsilon = 0.001;
    return fabs(a-b) < epsilon;
}

void CMenuFrame::draw(const int xaxis, const int yaxis, CBitmap *work){
Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN // CMenuFrame::draw //" << endl;
	if (!pBmp)return;

    if (!closeFloat(scrollOffset.x, 0) || !closeFloat(scrollOffset.y, 0)){

        // Lets do some scrolling
        CBitmap temp = CBitmap::temporaryBitmap(pBmp->getWidth(), pBmp->getHeight());
        MenuPoint loc;
        if (scrollOffset.x < 0){
            loc.x = scrollOffset.x + pBmp->getWidth();
        } else if (scrollOffset.x > 0){
            loc.x = scrollOffset.x - pBmp->getWidth();
        }
        if (scrollOffset.y < 0){
            loc.y = scrollOffset.y + pBmp->getHeight();
        } else if (scrollOffset.y > 0){
            loc.y = scrollOffset.y - pBmp->getHeight();
        }
        pBmp->BlitSurface((int) scrollOffset.x, (int) scrollOffset.y, temp);
        pBmp->BlitSurface((int) scrollOffset.x, (int) loc.y, temp);
        pBmp->BlitSurface((int) loc.x, (int) scrollOffset.y, temp);
        pBmp->BlitSurface((int) loc.x, (int) loc.y, temp);

        renderSprite(&temp, (int)(xaxis+offset.x), (int)(yaxis+offset.y), alpha, horizontalFlip, verticalFlip, work);

    } else {
        renderSprite(pBmp, (int)(xaxis+offset.x), (int)(yaxis+offset.y), alpha, horizontalFlip, verticalFlip, work);
    }
 Debug::debug(Debug::menu,__FUNCTION__) << "END // CMenuFrame::draw //" << endl;
}

CMenuAnimation::CMenuAnimation(const Token *the_token) throw(CLoadException):
id(0),
location(0),
ticks(0),
currentFrame(0),
loop(0),
allowReset(true){
    images[-1] = 0;
    string basedir = "";
    if ( *the_token != "anim" ){
        throw CLoadException(__FILE__, __LINE__,"Not an animation");
    }
    /* The usual setup of an animation is
	The images must be listed prior to listing any frames, basedir can be used to set the directory where the images are located
	loop will begin at the subsequent frame listed after loop
	axis is the location in which the drawing must be placed
	location - used to render in background or foreground (0 == background [default]| 1 == foreground)
	reset - used to allow resetting of animation (0 == no | 1 == yes [default])
	velocity - used to get a wrapping scroll effect while animating
	(anim (id NUM)
	      (location NUM)
	      (basedir LOCATION)
	      (image NUM FILE)
	      (velocity x y)
	      (axis x y)
	      (frame "Read comments above in constructor")
	      (loop)
	      (reset NUM)
	      (window x1 y1 x2 y2))
    */
    Token tok(*the_token);

    TokenView view = tok.view();
      while ( view.hasMore()){
        try{
            const Token * token;
            view >> token;
            if (*token == "id"){
                // get the id
                token->view()  >> id;
            } else if (*token == "location"){
                // get the location
                token->view()  >> location;
            } else if (*token == "basedir"){
                // set the base directory for loading images
                token->view()  >> basedir;
            } else if (*token == "image"){
                // add bitmaps by number to the map
                int number;
                string temp;
                token->view()  >> number >> temp;
                CBitmap *pBmp = CResource::getBitmap((basedir + temp));
                if (pBmp->getError()){
                    delete pBmp;
                } else {
                    images[number] = pBmp;
                }
            } else if (*token == "axis"){
                // Get the axis location it defaults to 0,0
                token->view()  >> axis.x >> axis.y;
            } else if (*token == "window"){
                // time to display
                token->view()  >> window.x1 >> window.y1 >> window.x2 >> window.y2;
            } else if (*token == "velocity"){
                // This allows the animation to get a wrapping scroll action going on
                token->view()  >> velocity.x >> velocity.y;
            } else if (*token == "frame"){
                // new frame
                CMenuFrame *frame = new CMenuFrame(token,images);
                frames.push_back(frame);
            } else if (*token == "loop"){
                // start loop here
                loop = frames.size();
            } else if (*token == "reset"){
                // Allow reset of animation
                token->view()  >> allowReset;
            } else {
                Debug::debug( 3 ) << "CMenuAnimation::CMenuAnimation - Unhandled menu attribute"<<": "<<endl;
               // if (Debug::getDebug() >= 3){
               //     token->print(" ");
               // }
            }
        } catch ( const CTokenException & ex ) {
            string m( "CMenuAnimation::CMenuAnimation( - Menu::CMenu_v1 parse error: " );
            m += ex.getTrace();
            throw CLoadException(__FILE__, __LINE__, m);
        } catch ( const CLoadException & ex ) {
            throw ex;
        }
    }
    if (loop >= frames.size()){
        ostringstream out;
        out << "Loop location is larger than the number of frames. Loop"<<": " << loop << " " <<"Frames"<<": " << frames.size();
        throw CLoadException(__FILE__, __LINE__,out.str());
    }
}

CMenuAnimation::~CMenuAnimation(){
    for (vector<CMenuFrame *>::iterator i = frames.begin(); i != frames.end(); ++i){
	if (*i){
	    delete *i;
	}
    }
    for (imageMap::iterator i = images.begin(); i != images.end(); ++i){
	if (i->second){
	    delete i->second;
	}
    }
}
void CMenuAnimation::act(){
    // Used for scrolling
    for (vector<CMenuFrame *>::iterator i = frames.begin(); i != frames.end(); ++i){
	(*i)->act(velocity.x, velocity.y);
    }
    if( frames[currentFrame]->time != -1 ){
	ticks++;
	if(ticks >= frames[currentFrame]->time){
		ticks = 0;
		forwardFrame();
	}
    }
}
void CMenuAnimation::draw(CBitmap *work){
    /* should use sub-bitmaps here */
     // Set clip from the axis default is 0,0,bitmap width, bitmap height
    work->setClipRect(window.x1,window.y1,work->getWidth() + window.x2,work->getHeight() + window.y2);
    frames[currentFrame]->draw((int) axis.x, (int) axis.y,work);
    work->setClipRect(0,0,work->getWidth(),work->getHeight());
}

void CMenuAnimation::forwardFrame(){
    if (currentFrame < frames.size() -1){
        currentFrame++;
    } else {
        currentFrame = loop;
    }
}
void CMenuAnimation::backFrame(){
    if (currentFrame > loop){
	currentFrame--;
    } else {
	currentFrame = frames.size() - 1;
    }
}


} //end SGF