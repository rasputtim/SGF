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
#include "menu/SGF_OptionCredits.h"


using namespace std;
namespace SGF {

namespace Menu {
COptionCredits::COptionCredits(const Gui::CContextBox & parent,const  Token * token ) throw( CLoadException ):
CMenuOption(parent,token),
background_bitmap(0),
music("")
{
color.r=255;
color.g=255;
color.b=255;
title.r=0;
title.g=255;
title.b=255;
	/* Always */
	credits.push_back("SGF - Super Game Fabric  Super Game Fabric");
	credits.push_back("");
	credits.push_back("Programming");
	credits.push_back("Rasputtim ");
	credits.push_back("");
	credits.push_back("Contributions");
	credits.push_back("");
	credits.push_back("");
	credits.push_back("Level design");
	credits.push_back("Rasputtim ");
	credits.push_back("");
	credits.push_back("Music");
	credits.push_back("aqua.s3m - Purple Motion");
	credits.push_back("c_heaven.xm - One Man Project");
	credits.push_back("elw-sick.xm - elwood");
	credits.push_back("experience.xm - elwood");
	credits.push_back("fall.xm - elwood");
	credits.push_back("kajahtaa.xm - cube");
	credits.push_back("kilimanz.mod - ???");
	credits.push_back("SM_TechTown.it - SaMPLeMaSTeR");
	credits.push_back("");
	credits.push_back("Email: rasputtim@hotmail.com");
	credits.push_back("");

	if ( *token != "credits" )
		throw CLoadException(__FILE__, __LINE__,"Not a credit menu");

        readName(token);

	TokenView view = token->view();
    while (view.hasMore()){
		try{
			const Token * tok;
			view >> tok;
			if ( *tok == "music" ) {
				/* Set music for credits */
				tok->view() >> music;
			} else if ( *tok == "background" ) {
				/* Create an image and push it back on to vector */
				string temp;
				tok->view() >> temp;
				if ( background_bitmap ){
					delete background_bitmap;
				}
				try {
						background_bitmap = CResource::getBitmap(temp);

				}catch (Exception::Filesystem::CNotFound &ex) {
					Debug::debug(Debug::gui,__FUNCTION__ ) << "CBITMAP NOT FOUND: "<< endl;
					Debug::debug(Debug::menu,__FUNCTION__) << "Problem loading background CBitmap: " << temp << endl;
					background_bitmap = NULL;
					throw ex;
				}

			} else if ( *tok == "additional" ) {
				string str;
				TokenView additionalView = tok->view();
				while (additionalView.hasMore() ){
					additionalView >> str;
					credits.push_back(str);
				}
			} else if ( *tok == "titlecolor" ) {
				int r,b,g;
				tok->view() >> r >> g >> b;
				title.r = r;
				title.g = g;
				title.b = b;
			} else if ( *tok == "color" ) {
				int r,b,g;
				tok->view() >> r >> g >> b;
				color.r = r;
				color.g = g;
				color.b = b;
			} else {
				Debug::debug(Debug::menu,__FUNCTION__) <<"Unhandled menu attribute: "<<endl;
                                //if (Debug::getDebug() >= 3){
                                //    tok->print(" ");
                                //}
			}
		} catch ( const CTokenException & ex ) {
			string m( "COptionCredits::COptionCredits - Menu::CMenu_v1 parse error: " );
			m += ex.getTrace();
			throw CLoadException(__FILE__, __LINE__, m);
		} catch ( const CLoadException & ex ) {
			throw ex;
		}
	}

    input.set(CKeyboard::Key_ESC, 0, true, Exit);
    input.set(CJoystick::Button2, 0, true, Exit);
}

COptionCredits::~COptionCredits(){
	if ( background_bitmap ){
		delete background_bitmap;
	}
}

void COptionCredits::logic(){
}
#if 0
void COptionCredits::run( bool &endGame ){
	Debug::debug(Debug::menu,__FUNCTION__)  << "endgame:"<< endGame << endl;

	CKeyboard key;

    const int maxCredits = credits.size();

    //Global::speed_counter = 0;
    double min_y = SCREEN_H;

    /* use CBitmap::temporaryBitmap here? */
    CBitmap tmp(SCREEN_W, SCREEN_H);
    CBitmap fireWork(SCREEN_W, SCREEN_H);
    if (! music.empty()){
        CMenuGlobals::setMusic(music);
    }

    SGF::CFire fire;

    //const Font & vFont = Font::getFont(Menu::CMenu_v1::getFont(), Menu::CMenu_v1::getFontWidth(), Menu::CMenu_v1::getFontHeight());
   	CTTFFont * vFont = NULL;
	try {
			vFont = CResource::getTTFont(Menu::CMenu_v1::getFont(), Menu::CMenu_v1::getFontWidth(),Menu::CMenu_v1::getFontHeight());

			}catch (Exception::Filesystem::CNotFound &ex) {
				 ostringstream out;
				 out << "CFont not found " << ex.getTrace()<< endl;
				 Debug::debug(Debug::font,__FUNCTION__) << out.str() << endl;
			}
    bool quit = false;

    CBitmap::transBlender(0, 0, 0, 128);

    double think = 0;
	// Control loop
    while (!quit){
        Debug::debug(Debug::menu,__FUNCTION__) << "Loop While- quit="<< quit << endl;
	    Debug::debug(Debug::menu,__FUNCTION__)  << "BitMap tmp="<< &tmp << endl;
	    // Check Input

		CInputManager::HandleNonEventInput();
		CInputMap<CreditKey>::Output out = CInputManager::getMap(input);
        quit = out[Exit];

        // Think
		Debug::debug(Debug::menu,__FUNCTION__) << "  " << "nFrameCount: "<< CSDLManager::nFrameCount << endl;

        if (CSDLManager::nFrameCount > 5){
			think += CSDLManager::nFrameCount * Global::LOGIC_MULTIPLIER;
        Debug::debug(Debug::menu,__FUNCTION__) << "  " << "nFrameCount: "<< CSDLManager::nFrameCount << endl;
	    Debug::debug(Debug::menu,__FUNCTION__) << "  " << "think: "<< think << endl;

            while (think >= 14.0){
            Debug::debug(Debug::menu,__FUNCTION__) << "  " << "while think: "<< think << endl;

				think -= 1;
                min_y -= 0.9;
                if (min_y < -(int)(maxCredits * vFont->getHeight() * 1.1)){
                    min_y = SCREEN_H;
                }
                fire.update();
            }


        }
        // Render everything
		if (1){
            if (background_bitmap ){
               background_bitmap->Blit();  //! Blit no modo de compatibilidade SDL
            } else {
                tmp.fill(Colors::makeColor(0,0,0));
            }
            fire.draw(fireWork);
			fireWork.translucent().draw(0, 0, tmp);
            int y = (int) min_y;
            vector<string>::iterator b = credits.begin();
            vector<string>::iterator e = credits.end();
            bool isTitle = true;
            for ( /**/ ; b != e; b++ ){
                if ( isTitle ){
                    Debug::debug(Debug::menu,__FUNCTION__) << "  " << "Printing: "<< (*b) << endl;

					// Todo: Verificar porque o cgg não reconhece printf
                vFont->printf( 100, y, title, tmp, (*b), 0 );
                    isTitle = false;
                } else {
                     Debug::debug(Debug::menu,__FUNCTION__) << "  " << "Printing: "<< (*b) << endl;
					 // Todo: Verificar porque o cgg não reconhece printf
                vFont->printf( 100, y, color, tmp, (*b), 0 );
                }
                y += vFont->getHeight() + 2;

                if ( (*b).empty() ){
                    isTitle = true;
                }
            }
            //fire.draw(tmp);
        }
		// Control FPS
		CSDLManager::FPS_Manager();
        // Render to Screen
		tmp.BlitToScreen();
    }

    CInputManager::waitForRelease(input, Exit);
}
#endif
void COptionCredits::run(const Menu::CContext & context){
 /*   // Keyboard key;
    CBitmap backgroundImage(Filesystem::getInstance().find(background).path());

    const int maxCredits = credits.size();

    Global::speed_counter = 0;
    double min_y = SCREEN_H;

    // use Bitmap::temporaryBitmap here? no! BlitToScreen uses temporaryBitmap
    const CBitmap tmp(Menu::CMenu_v2::Width, Menu::CMenu_v2::Height);
    // Bitmap fireWork(GFX_X, GFX_Y);
    if (! music.empty()){
        //MenuGlobals::setMusic(music);
        if (CMusic::loadSong(Filesystem::getInstance().find(Filesystem::CRelativePath(music)).path())){
	    CMusic::pause();
	   CMusic::play();
	}
    }

    SGF::CFire fire;

    //const CFont & vFont = CConfiguration::getMenuFont()->get(context.getFont()->get());
	const CFont & vFont = *CResource::getDefaultFont();

    bool quit = false;

    CBitmap::transBlender(0, 0, 0, 128);

    double think = 0;
    while (!quit){

        CInputManager::HandleNonEventInput();
        vector<CInputMap<CreditKey>::InputEvent> out = CInputManager::getEvents(input);
        for (vector<CInputMap<CreditKey>::InputEvent>::iterator it = out.begin(); it != out.end(); it++){
            const CInputMap<CreditKey>::InputEvent & event = *it;
            if (event.enabled){
                if (event.out == Exit){
                    quit = true;
                }
            }
        }

        bool draw = false;
        if (Global::speed_counter > 0){
            think += Global::speed_counter * Global::LOGIC_MULTIPLIER;
            draw = true;

            while (think >= 1.0){
                think -= 1;
                min_y -= 0.9;
                if (min_y < -(int)(maxCredits * vFont.getHeight() * 1.1)){
                    min_y = SCREEN_H;
                }
                fire.update();
            }

            Global::speed_counter = 0;
        }

        if (draw){

            backgroundImage.Blit(tmp);


           // fire.draw(fireWork);
           // fireWork.drawTrans(0, 0, tmp);


            int y = (int) min_y;
            vector<string>::iterator b = credits.begin();
            vector<string>::iterator e = credits.end();
            bool isTitle = true;
            for (  ; b != e; b++ ){
                if ( isTitle ){
                    vFont.printf( 100, y, title, tmp, (*b), 0 );
                    isTitle = false;
                } else {
                    vFont.printf( 100, y, color, tmp, (*b), 0 );
                }
                y += vFont.getHeight() + 2;

                if ( (*b).empty() ){
                    isTitle = true;
                }
            }

            fire.draw(tmp);

            tmp.BlitToScreen();
        } else {
            Util::rest(1);
        }
    }

    CInputManager::waitForRelease(input, Exit);
    throw Menu::CReload(__FILE__, __LINE__);
    // throw Exception::Return(__FILE__, __LINE__);  */
}
}
} //end SGF