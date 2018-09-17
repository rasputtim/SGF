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

#include <math.h>
#include <iostream>
#include "graphics/all.h"
#include "resource/all.h"
#include "level/SGF_LevelUtils.h"
#include "util/SGF_Messages.h"
#include "util/SGF_Loading.h"
#include "util/SGF_FileSystem.h"
#include "util/SGF_FontSystem.h"
#include "util/SGF_Util.h"
#include "SGF_Global.h"
#include "util/SGF_Pointer.h"
#include "util/all_fonts.h"
#include "util/SGF_MessageQueue.h"
#include <vector>
#include "util/SGF_Debug.h"
//#include "tbb/task.h"
//#include "tbb/spin_mutex.h"
//#include "tbb/compat/thread"
#include "resource/all.h"
#include "input/all.h"
#include "input/SGF_Events.h"
using namespace std;
//using namespace tbb;
namespace SGF {

class task;
class mutex;
class thread;
class CBitmap;
class CFontInfo;
class CFont;
class CDraw;
namespace Loader{


//s typedef spin_mutex FreeListMutexType;
// FreeListMutexType loading_screen_mutex;
volatile bool done_loading = true;

typedef struct pair{
	int x, y;
} ppair;

CInfo::CInfo(){
        Messages::registerInfo(&messages);
    }
  /*  //!transfere mensagens pela rede
    bool transferMessages(Messages & box){
        bool did = false;
        while (messages.hasAny()){
            const string & str = messages.get();
            box.addMessage(str);
            did = true;
        }
        return did;
    }*/

CInfo::~CInfo(){
        Messages::unregisterInfo(&messages);


}


void * loadingScreenSimple1(void * arg);

static void setupBackground(const CBitmap & background, int load_x, int load_y, int load_width, int load_height, int infobox_x, int infobox_y, int infoWidth, int infoHeight, const CBitmap & infoBackground, const CBitmap & work){
    //verificar se existe textura no bitmap...
	//background.Blit(0, 0, load_width, load_height, infobox_x, infobox_y); //Blit texture to default render window
	background.setBitmapMode(CBitmap::DRAW_TYPE_TEXTURE);
	//background.fill(0,0,100);
	background.Blit();
	//! este Blit só trabalha com surfaces tanto no modo SDL 1.2 qto 1.3
	// coloca o background na superfície infoBackground
	background.BlitSurface(infobox_x, infobox_y, infoWidth, infoHeight, 0, 0, infoBackground);

	 Colors::ColorDefinition tempcolor2;
	tempcolor2.r=192;
	tempcolor2.g=192;
	tempcolor2.b=192;

	CResource::getDefaultFont()->drawText( 400, 480 - CResource::getDefaultFont()->getHeight() * 5 / 2 - CResource::getDefaultFont()->getHeight(), tempcolor2, background, "SGF Version %s", 0, Global::getVersionString().c_str());
    CResource::getDefaultFont()->drawText( 400, 480 - CResource::getDefaultFont()->getHeight() * 5 / 2, tempcolor2, background, "Made by Rasputtim", 0 );

	background.BlitToScreen();
	//SDL_Delay(1000);
    //! vai limpar o info

}

/* converts a bitmap with some text on it into a sequence of points */
static vector<Gui::CAbsolutePoint> generateFontPixels(const CFont & myFont, const string & message, int width, int height){
  
	int mask =  Colors::makeColor(255,0,255);

	CBitmap letters(width, height);
    letters.setBitmapMode(CBitmap::DRAW_TYPE_SURFACE);
	letters.fill(  CBitmap::makeSDLColor(255,0,255));//CBitmap::MaskColor
	letters.setBitmapMode(CBitmap::DRAW_TYPE_DEFAULT);

    myFont.drawToSurface( 0, 0, CBitmap::makeSDLColor( 255, 255, 255 ), letters, message.c_str(), 0 );
	//myFont.printf( 0, 0, CBitmap::makeColor(255, 255, 255), letters, message.c_str(), 0 );
	//get the pixel 0
	//int pixel0=letters.getPixel(0,0);
	//Debug::debug( 2 ) << "Loader:loading screen // Pixel 0 = "<< pixel0 <<endl;

    vector <Gui::CAbsolutePoint> pixelcolection = letters.getPixelsCoordInverted(mask);
    return pixelcolection;


}

/* shows time elapsed */
class CTimeCounter{
public:
    CTimeCounter():
    work(200, 40){
        start = Global::second_counter;
        last = 0;
    }

    void draw(int x, int y){
		const CFont * font = CResource::getDefaultFont(24, 24);
        if (Global::second_counter != last){
            work.clear();
            last = Global::second_counter;
            font->drawText(0, 0, Colors::makeColor(192, 192, 192), work, "Waiting.. %d", 0, last - start);
            work.BlitAreaToScreen(x, y);
        }
    }

	CBitmap work;
    //Graphics::Bitmap work;
    unsigned int start;
    unsigned int last;
};




//! cria um novo trhead (task) para executar a rotina loadingScreen que é passada como argumento
/*void startLoading( void * arg){

	FreeListMutexType::scoped_lock lock;
    lock.acquire(loading_screen_mutex);
	done_loading = false;
	lock.release();
	Debug::debug(701) << "Loader::startLoading: " <<  endl;
	//tbb::tbb_thread loading2(loadingScreen,arg);

	//CLoadingScreen& a = *new(tbb::task::allocate_root()) CLoadingScreen(arg);
	//tbb::task::spawn_root_and_wait(a);

	Debug::debug(701) << "Loader::startLoading // LOADED: "  <<  endl;

} */




CLoadingContext::CLoadingContext():
finished(false){
    Util::Thread::initializeLock(&lock);
}

CLoadingContext::~CLoadingContext(){
}

void CLoadingContext::doLoad(){
    this->load();
    Util::Thread::acquireLock(&lock);
    finished = true;
    Util::Thread::releaseLock(&lock);
}

bool CLoadingContext::done(){
    bool ok = false;
    Util::Thread::acquireLock(&lock);
    ok = this->finished;
    Util::Thread::releaseLock(&lock);
    return ok;
}

void * CLoadingContext::load_it(void * arg){
    CLoadingContext * context = (CLoadingContext*) arg;
    context->doLoad();
    return NULL;
}


static void showLoadMessage(){
    int screenX = 80;
    int screenY = 50;
	//Graphics::Bitmap work(110, 50);
    CBitmap work(110, 50);
    work.BlitFromScreen(screenX, screenY);
    //Graphics::Bitmap top(110, 50);
	CBitmap top(110, 50);
    top.fill(CBitmap::makeColor(0, 0, 0));
    CResource::getDefaultFont(8,8)->drawText(10, 5, CBitmap::makeColor(192, 192, 192), top, "Loading", 0);
    //Graphics::Bitmap::transBlender(0, 0, 0, 200);
	CBitmap::transBlender(0, 0, 0, 200);
    top.translucent().draw(0, 0, work);
    work.BlitAreaToScreen(screenX, screenY);
}
static void loadingScreenSimpleX1(CLoadingContext & context, const Level::CLevelInfo & levelInfo){
    // todo: iMPLEMENT
	/*Bitmap work(40, 40);
    Bitmap original(40, 40);
    original.BlitFromScreen(0, 0);
    Global::speed_counter = 0;
    int angle = 0;
    int color1 = Bitmap::makeColor(0, 0, 0);
    int color2 = Bitmap::makeColor(0x00, 0x99, 0xff);
    int color3 = Bitmap::makeColor(0xff, 0x22, 0x33);
    int color4 = Bitmap::makeColor(0x44, 0x77, 0x33);
    // the length of this array is the number of circles to show
    int colors[4] = {color1, color2, color3, color4};
    Bitmap::transBlender(0, 0, 0, 64);
    // speed of rotation
    int speed = 7;
    while (! context.done()){
        bool draw = false;

        if (Global::speed_counter > 0){
            double think = Global::speed_counter;
            Global::speed_counter = 0;
            draw = true;

            while (think > 0){
                angle += speed;
                think -= 1;
            }
        } else {
            Util::rest(1);
        }

        if (draw){
            int max = sizeof(colors) / sizeof(int);
            double middleX = work.getWidth() / 2;
            double middleY = work.getHeight() / 2;
            original.Blit(work);
            for (int i = 0; i < max; i++){
                double x = cos(Util::radians(angle + 360 / max * i)) * 15;
                double y = sin(Util::radians(angle + 360 / max * i)) * 15;
                //! ghost circle
                work.translucent().circleFill(middleX + x, middleY + y, 2, colors[i]);
                x = cos(Util::radians(angle + speed + 360 / max * i)) * 15;
                y = sin(Util::radians(angle + speed + 360 / max * i)) * 15;
                //! real circle
                work.circleFill(middleX + x, middleY + y, 2, colors[i]);
            }
            work.BlitAreaToScreen(0, 0);
        }
    } */
}

static void loadingScreen1(CLoadingContext & context, const Level::CLevelInfo & levelInfo){
	Debug::debug(Debug::resources,__FUNCTION__) << "Carregando tela "<< endl;
	/*
	int load_x = 80;
    int load_y = 220;
    const int infobox_width = 300;
    const int infobox_height = 150;
    Info info;
    const CFont & myFont = Font::getFont(string(Global::DEFAULT_FONT), 24, 24);
    const CFont & infoFont = Font::getFont(string(Global::DEFAULT_FONT), 24, 24);

    if (levelInfo.getPositionX() != -1){
        load_x = levelInfo.getPositionX();
    }

    if (levelInfo.getPositionY() != -1){
        load_y = levelInfo.getPositionY();
    }

    // const char * the_string = (arg != NULL) ? (const char *) arg : "Loading...";
    int load_width = myFont.textLength(levelInfo.loadingMessage().c_str());
    int load_height = myFont.getHeight(levelInfo.loadingMessage().c_str());

    const int infobox_x = load_x;
    const int infobox_y = load_y + load_height * 2;

    Global::debug(2) << "loading screen" << endl;

    CBitmap work(load_width, load_height);

    vector<ppair> pairs = generateFontPixels(myFont, levelInfo.loadingMessage(), load_width, load_height);

    Messages infobox(infobox_width, infobox_height);
    CBitmap infoWork(infobox_width, infobox_height);
    CBitmap infoBackground(infobox_width, infobox_height);

    const int MAX_COLOR = 200;

    // blend from dark grey to light red
    CEffects::Gradient gradient(MAX_COLOR, Bitmap::makeColor(16, 16, 16), Bitmap::makeColor(192, 8, 8));

    Global::speed_counter = 0;

    if (levelInfo.getBackground() != 0){
        setupBackground(*levelInfo.getBackground(), load_x, load_y, load_width, load_height, infobox_x, infobox_y, infoBackground.getWidth(), infoBackground.getHeight(), infoBackground, work);
    } else {
        setupBackground(CBitmap(levelInfo.loadingBackground().path()), load_x, load_y, load_width, load_height, infobox_x, infobox_y, infoBackground.getWidth(), infoBackground.getHeight(), infoBackground, work);
    }

    TimeCounter counter;

    bool firstDraw = true;

    while (! context.done()){

        // true if a logic loop has passed
        bool draw = firstDraw;

        // will be true if any new info messages appeared
        bool drawInfo = firstDraw;
        firstDraw = false;
        if ( Global::speed_counter > 0 ){
            double think = Global::speed_counter;
            Global::speed_counter = 0;
            draw = true;

            while ( think > 0 ){
                gradient.backward();
                think -= 1;
            }

            // if no new messages appeared this will be false
            drawInfo = info.transferMessages(infobox);
        } else {
            Util::rest( 1 );
        }

        if (draw){
            for ( vector< ppair >::iterator it = pairs.begin(); it != pairs.end(); it++ ){
                int color = gradient.current(it->x);
                work.putPixelSurface(it->x, it->y, color);
            }

            // counter.draw(200, 100);

            // we might not have to draw the whole info box again if no new
             // messages appeared.

            if (drawInfo){
                infoBackground.Blit(infoWork);

                // cheesy hack to change the font size. the font
                 // should store the size and change it on its own

                CFont::getFont(string(Global::DEFAULT_FONT), 13, 13);
                infobox.draw(0, 0, infoWork, infoFont);
                CFont::getFont(string(Global::DEFAULT_FONT), 24, 24);
                infoWork.BlitAreaToScreen(infobox_x, infobox_y);
            }
            // work already contains the correct background
            // work.Blit( load_x, load_y, *Bitmap::Screen );
            work.BlitAreaToScreen(load_x, load_y);
        }
    } */
}

// solução de colocar pixels na surface: http://slouken.blogspot.com/2011/02/streaming-textures-with-sdl-13.html

enum LoadingKeys{
    Activate
};

static void loadingScreen0(CLoadingContext & context, const Level::CLevelInfo & levelInfo){

	int load_x = 80;
    int load_y = 220;
    const int infobox_width = 300;
    const int infobox_height = 150;
	Util::CReferenceCount<CFontInfo> myFontInfo;
	Util::CReferenceCount<CFontInfo> infoFontInfo;
	if(CFontList::GetInstance()->isAvailable("arial.ttf")) {
	myFontInfo = CFontList::GetInstance()->findFont("arial.ttf");
	myFontInfo->setWidth(24);
	myFontInfo->setHeight(24);
	}
	if(CFontList::GetInstance()->isAvailable("arial.ttf")) {
	infoFontInfo = CFontList::GetInstance()->findFont("arial.ttf");
	}

	const CFont & myFont = myFontInfo->get();
	Debug::debug(Debug::resources,__FUNCTION__) << "Carregando tela Screen0 - x: "<< load_x << endl;

    if (levelInfo.getPositionX() != -1){
        load_x = levelInfo.getPositionX();
    }

    if (levelInfo.getPositionY() != -1){
        load_y = levelInfo.getPositionY();
    }
	Debug::debug(10,__FUNCTION__ ) << "LevelInfo X: "<< load_x << endl;
    Debug::debug(10,__FUNCTION__ ) << "LevelInfo Y: "<< load_y << endl;
//	Debug::debug(10,__FUNCTION__ ) << "LevelInfo PlayerPath: "<< levelInfo.getPlayerPath() << endl;
	Debug::debug(10,__FUNCTION__ ) << "LevelInfo Loading Message: "<< levelInfo.loadingMessage() << endl;


	 // const char * the_string = (arg != NULL) ? (const char *) arg : "Loading...";
	int load_width = myFont.getTextLength(levelInfo.loadingMessage().c_str());
    int load_height = myFont.getTextHeight(levelInfo.loadingMessage().c_str());

    //const int infobox_x = load_x;
    //const int infobox_y = load_y + load_height * 2;

    //Debug::debug( 2 ) << "loading screen" << endl;

	//usa como default a janela 0, ou Screen[0]
    CBitmap work( load_width, load_height );
    CBitmap infoWork(infobox_width, infobox_height);
    CBitmap infoBackground(infobox_width, infobox_height);
	//vector<ppair> pairs = generateFontPixels(myFont, levelInfo.loadingMessage(), load_width, load_height);

	const int MAX_COLOR = 200;

    // Colors::ColorDefinition colors[ MAX_COLOR ];
    // Colors::ColorDefinition c1 = CBitmap::makeSDLColor( 16, 16, 16 );
    // Colors::ColorDefinition c2 = CBitmap::makeSDLColor( 192, 8, 8 );
    // blend from dark grey to light red
    //Util::blend_palette( colors, MAX_COLOR / 2, c1, c2 );
    //Util::blend_palette( colors + MAX_COLOR / 2, MAX_COLOR / 2, c2, c1 );

	/* blend from dark grey to light red */
    Effects::Gradient gradient(MAX_COLOR, Colors::makeColor(16, 16, 16), Colors::makeColor(192, 8, 8));

    struct State{
        bool drawInfo;
    };



   class Logic: public Input::CLogic {
    public:
        Logic(CLoadingContext & context, State & state, Effects::Gradient & gradient/*, Messages & infoBox*/):
        context(context),
        state(state),
        gradient(gradient),
        //infobox(infoBox),
        active(false){
            input.set(CKeyboard::Key_SPACE, 0, true, Activate);
            input.set(CKeyboard::Key_ENTER, 0, true, Activate);
            input.set(CJoystick::Button1, 0, true, Activate);
        }

        CLoadingContext & context;
        State & state;
        Effects::Gradient & gradient;
        //MessageInfo info;
        //Messages & infobox;
        bool active;
        CInputMap<LoadingKeys> input;

        void doInput(){
            class Handler: public CInputHandler<LoadingKeys> {
            public:
                Handler(bool & active):
                    active(active){
                    }

                bool & active;

                void press(const LoadingKeys & out, CKeyboard::unicode_t unicode){
                    if (out == Activate){
                        /* the info box can't really be turned off because once
                         * its drawn it will remain there. the background would
                         * have to be drawn on top of it to remove the old
                         * info box. maybe do this in the future, if so use
                         *   active = ! active
                         * to toggle it.
                         */
                        active = true;
                    }
                }

                void release(const LoadingKeys & out, CKeyboard::unicode_t unicode){
                }
            };

            Handler handler(active);
            CInputManager::handleEvents(input, handler);
        }

        void run(int){
            gradient.backward();
            doInput();
            state.drawInfo = active && (/*info.transferMessages(infobox) || */state.drawInfo);
        }

        double ticks(double system){
            return system;
        }

        bool done(){
            return context.done();
        }
    };

   class Draw: public Input::CDraw {
    public:
        Draw(const Level::CLevelInfo & levelInfo, State & state, /*Messages & infobox,*/ Effects::Gradient & gradient, int load_width, int load_height, int infobox_width, int infobox_height, int load_x, int load_y, CBitmap *_work,CBitmap & _infoWork):
            levelInfo(levelInfo),
            gradient(gradient),
            state(state),
            //infobox(infobox),
			//infoWork(*CBitmap::Screen[0]/*Graphics::screenParameter.current()*/, load_x, load_y + load_height * 2, infobox_width, infobox_height),
            infoWork(_infoWork),
			infoBackground(infobox_width, infobox_height),
			screen(_work),
            infobox_x(load_x),
            infobox_y(load_y + load_height * 2),
            load_x(load_x),
            load_y(load_y),
            load_width(load_width),
            load_height(load_height){
				Util::CReferenceCount<CFontInfo> myFontinfo;
				if(CFontList::GetInstance()->isAvailable("arial.ttf")) {
				myFontinfo = CFontList::GetInstance()->findFont("arial.ttf");
				myFontinfo->setWidth(24);
				myFontinfo->setHeight(24);
				}
				const CFont & myFont = myFontinfo->get();
				pairs = generateFontPixels(myFont, levelInfo.loadingMessage(), load_width, load_height);
			}

        const Level::CLevelInfo & levelInfo;
        Effects::Gradient & gradient;
        State & state;
        //Messages & infobox;
        CBitmap & infoWork;
        CBitmap infoBackground;
		CBitmap * screen;
        //vector<ppair> pairs;
		vector<Gui::CAbsolutePoint> pairs;
        const int infobox_x;
        const int infobox_y;
        const int load_x;
        const int load_y;
        const int load_width;
        const int load_height;

        void drawFirst(const CBitmap & screen){
            if (levelInfo.getBackground() != 0){
					Debug::debug(Debug::resources,__FUNCTION__) << "Using Levelinfo Background" << endl;
					Loader::setupBackground(*levelInfo.getBackground(), load_x, load_y, load_width, load_height, infobox_x, infobox_y, infoBackground.getWidth(), infoBackground.getHeight(), infoBackground, screen);
					//setupBackground(*levelInfo.getBackground(), load_x, load_y, load_width, load_height, infobox_x, infobox_y, infoBackground.getWidth(), infoBackground.getHeight(), infoBackground, screen);
            } else {
					Debug::debug(Debug::resources,__FUNCTION__) << "Using Levelinfo Background New" << endl;
					Loader::setupBackground(CBitmap(levelInfo.loadingBackground()), load_x, load_y, load_width, load_height, infobox_x, infobox_y, infoBackground.getWidth(), infoBackground.getHeight(), infoBackground, screen);
			//        setupBackground(CBitmap(levelInfo.loadingBackground().path()), load_x, load_y, load_width, load_height, infobox_x, infobox_y, infoBackground.getWidth(), infoBackground.getHeight(), infoBackground, screen);
			}
		}
        void draw(double fps){
			for ( vector< Gui::CAbsolutePoint >::iterator it = pairs.begin(); it != pairs.end(); it++ ){
                Colors::ColorDefinition color = gradient.current(it->x);
                //Colors::ColorDefinition color = colors[ (it->x - mover + MAX_COLOR) % MAX_COLOR ];
				//Debug::debug( 2 ) << "Loader:loading screen // Put Pixel to Work (x,y) = "<< "( "<<  it->x<<","<< it->y <<" ) "<<  endl;
				screen->putPixelTexture( it->x, it->y, color.r,color.g,color.b );
            }
            

            if (state.drawInfo){
				//s infoBackground.Blit(infoWork); //! este método só trabalha com a Surface
				Util::CReferenceCount<CFontInfo> myFontinfo;

				if(CFontList::GetInstance()->isAvailable("arial.ttf")) {
				myFontinfo = CFontList::GetInstance()->findFont("arial.ttf");
				myFontinfo->setWidth(24);
				myFontinfo->setHeight(24);
				}


			    //const CFont & infoFont = myFontinfo->get();
                /* cheesy hack to change the font size. the font
                 * should store the size and change it on its own
                 */
                //sCFont::getFont(string(Global::DEFAULT_FONT), 13, 13);
                //sinfobox.draw(0, 0, infoWork, infoFont);
                //sCFont::getFont(string(Global::DEFAULT_FONT), 24, 24);
                //s infoWork.updateTexture();
                //s infoWork.BlitAreaToScreen(infobox_x, infobox_y);
				//s infoWork.BlitToScreen();

                state.drawInfo = false;
            }
            /* work already contains the correct background */
            // work.Blit( load_x, load_y, *Bitmap::Screen );
            // work.BlitToScreen();
 			screen->BlitAreaToScreen( load_x, load_y );
            screen->BlitToScreen();
        }
    };

   State state;
    // state.drawInfo = true;
    Logic logic(context, state, gradient/*, infobox*/);
    Draw draw(levelInfo, state/*, infobox*/,gradient, load_width, load_height, infobox_width, infobox_height, load_x, load_y,&work,infoWork);

    Input::SGE_standardLoop(logic, draw);


#if 0
   if (levelInfo.getBackground() != 0){
		Debug::debug(Debug::resources,__FUNCTION__) << "Using Levelinfo Background" << endl;
		Loader::setupBackground(*levelInfo.getBackground(), load_x, load_y, load_width, load_height, infobox_x, infobox_y, infoBackground.getWidth(), infoBackground.getHeight(), infoBackground, work);
    } else {
        Debug::debug(Debug::resources,__FUNCTION__) << "Using Levelinfo Background New" << endl;
		Loader::setupBackground(CBitmap(levelInfo.loadingBackground()), load_x, load_y, load_width, load_height, infobox_x, infobox_y, infoBackground.getWidth(), infoBackground.getHeight(), infoBackground, work);

        //CBitmap background(levelInfo.loadingBackground());
        //background.Blit(load_x, load_y, load_width, load_height, 0, 0, work);
        //Font::getDefaultFont().printf( 400, 480 - Font::getDefaultFont().getHeight() * 5 / 2 - Font::getDefaultFont().getHeight(), Colors::makeColor( 192, 192, 192 ), background, "SGF version %s", 0, Global::getVersionString().c_str());
        //Font::getDefaultFont().printf( 400, 480 - Font::getDefaultFont().getHeight() * 5 / 2, Colors::makeColor( 192, 192, 192 ), background, "Made by Jon Rafkind", 0 );
        //background.BlitToScreen();
        //background.Blit(infobox_x, infobox_y, infoBackground.getWidth(), infoBackground.getHeight(), 0, 0, infoBackground);

    }


    bool quit = false;

    // keeps the colors moving
    static unsigned mover = 0;
    bool firstDraw = true;

    while ( ! context.done() ){

        bool draw = false;
        bool drawInfo = firstDraw;
        firstDraw = false;
        if ( Global::speed_counter > 0 ){
            double think = Global::speed_counter;
            Global::speed_counter = 0;
            draw = true;

            while ( think > 0 ){
                mover = (mover + 1) % MAX_COLOR;
                think -= 1;
            }
            //drawInfo = info.transferMessages(infobox);
        } else {
            Util::rest( 1 );
        }

        if ( draw ){
            //desenha a listra movimentante na tela
			//Debug::debug( 2 ) << "Loader:loading screen // Put Pixel to Work  "<<  endl;

			for ( vector< ppair >::iterator it = pairs.begin(); it != pairs.end(); it++ ){
                 Colors::ColorDefinition color = colors[ (it->x - mover + MAX_COLOR) % MAX_COLOR ];

				//Debug::debug( 2 ) << "Loader:loading screen // Put Pixel to Work (x,y) = "<< "( "<<  it->x<<","<< it->y <<" ) "<<  endl;

				work.putPixelTexture( it->x, it->y, color.r,color.g,color.b );
            }



            if (drawInfo){
                infoBackground.Blit(infoWork); //! este método só trabalha com a Surface

                // cheesy hack to change the font size. the font
                // should store the size and change it on its own

                // CResource::getTTFont(fontName, 13, 13);

                //infobox.draw(0, 0, infoWork, infoFont);
                // CResource::getTTFont(fontName, 24, 24);

				 //s infoWork.updateTexture();
                 //s infoWork.BlitAreaToScreen(infobox_x, infobox_y);
				 //s infoWork.BlitToScreen();
            }

			work.BlitAreaToScreen( load_x, load_y );
            work.BlitToScreen();

        }
	} //end while
#endif
    Debug::debug(2100,__FUNCTION__ ) << "screen ENDING TASK" << endl;

}

void loadScreen(CLoadingContext & context, const Level::CLevelInfo & info, Kind kind){
   Debug::debug(1,__FUNCTION__) << "loadScreen(CLoadingContext & context, const Level::CLevelInfo & info, Kind kind)" << endl;
	Util::Thread::ThreadId_t loadingThread;
    bool created = Util::Thread::createThread(&loadingThread, NULL, (Util::Thread::ThreadFunction) CLoadingContext::load_it, &context);
    if (!created){
        Debug::debug(1,__FUNCTION__) << "Could not create loading thread. Loading will occur in the main thread" << endl;
        showLoadMessage();
        CLoadingContext::load_it(&context);
        // throw CLoadException(__FILE__, __LINE__, "Could not create loader thread");
    } else {
		CInputManager::deferResizeEvents(true);
		kind=Default;
		Debug::debug(Debug::error,__FUNCTION__) << "New thread created. Loading will occur in the new thread. Screen Tipe: "<< kind << endl;

		 switch (kind){
            case Default:
				Debug::debug(Debug::error,__FUNCTION__) << "Will Start LoadScreen0" << endl;
				loadingScreen0(context, info); break;  // TODO: IMPLEMENTAR LOADSCREEN1
            case SimpleCircle: loadingScreenSimpleX1(context, info); break;
            default:
				Debug::debug(Debug::error,__FUNCTION__) << "Will Start LoadScreen0" << endl;

				loadingScreen1(context, info); break;
        }

        Util::Thread::joinThread(loadingThread);
		CInputManager::deferResizeEvents(false);
    }
}


// Using TBB

void stopLoading(){
   // FreeListMutexType::scoped_lock lock;
    //lock.acquire(loading_screen_mutex);
    done_loading = true;
	Debug::debug(1,__FUNCTION__) << "stopLoading() // done_loading= " <<  done_loading << endl;

	//lock.release();
}
#if 0
CLoadingScreen::CLoadingScreen( void * _arg ):
	arg(_arg),
	load_x(80),
    load_y(220),
    infobox_width(300),
	infobox_height(150),
	myFont(NULL),
	infoFont(NULL),
	fontName (Filesystem::CRelativePath(string(DEF_FONT_PATH)+"arial.ttf").completePath()){
		try {
			myFont = CResource::getTTFont(fontName, 24, 24);

			}catch (Exception::Filesystem::CNotFound &ex) {
				 ostringstream out;
				 out << "CFont not found " << ex.getTrace()<< endl;
				 Debug::debug(Debug::font,__FUNCTION__) << out.str() << endl;
			}
		try {
			infoFont = CResource::getTTFont(fontName, 24, 24);

			}catch (Exception::Filesystem::CNotFound &ex) {
				 ostringstream out;
				 out << "CFont not found " << ex.getTrace()<< endl;
				 Debug::debug(Debug::font,__FUNCTION__) << out.str() << endl;
			}
	Debug::debug(2100,__FUNCTION__ ) << endl;
	}

	tbb::task* CLoadingScreen::execute() { // Overrides virtual function task::execute
	//Level::CLevelInfo *testelevelInfo = (Level::CLevelInfo*) arg;
	if (arg != NULL){
        Debug::debug(2100,__FUNCTION__ ) << "Info= " << arg << endl;
    	levelInfo = *(Level::CLevelInfo*) arg;
	}
	Debug::debug(2100,__FUNCTION__ ) << "LevelInfo X: "<< levelInfo.getPositionX() << endl;
    Debug::debug(2100,__FUNCTION__ ) << "LevelInfo Y: "<< levelInfo.getPositionY() << endl;
	Debug::debug(2100,__FUNCTION__ ) << "LevelInfo PlayerPath: "<< levelInfo.getPlayerPath() << endl;
	Debug::debug(2100,__FUNCTION__ ) << "LevelInfo Loading Message: "<< levelInfo.loadingMessage() << endl;
	if (levelInfo.getPositionX() != -1){
        load_x = levelInfo.getPositionX();
    }

    if (levelInfo.getPositionY() != -1){
        load_y = levelInfo.getPositionY();
    }

    // const char * the_string = (arg != NULL) ? (const char *) arg : "Loading...";
    int load_width = myFont->textLength(levelInfo.loadingMessage().c_str());
    int load_height = myFont->getHeight(levelInfo.loadingMessage().c_str());

    const int infobox_x = load_x;
    const int infobox_y = load_y + load_height * 2;

    //Debug::debug( 2 ) << "loading screen" << endl;

	//usa como default a janela 0, ou Screen[0]
    CBitmap work( load_width, load_height );
    CBitmap letters( load_width, load_height );

    //Messages infobox(infobox_width, infobox_height);
    CBitmap infoWork(infobox_width, infobox_height);
    CBitmap infoBackground(infobox_width, infobox_height);
	//work.fillSurface( CBitmap::makeSDLColor(255,0,255));
	letters.setBitmapMode(CBitmap::DRAW_TYPE_SURFACE);
	letters.fill(  CBitmap::makeSDLColor(255,0,255));//CBitmap::MaskColor
	letters.setBitmapMode(CBitmap::DRAW_TYPE_DEFAULT);

	//myFont->printf( 0, 0, CBitmap::makeSDLColor( 255, 255, 255 ), letters, levelInfo.loadingMessage().c_str(), 0 );
	myFont->printfToSurface( 0, 0, CBitmap::makeSDLColor( 255, 255, 255 ), letters, levelInfo.loadingMessage().c_str(), 0 );
	vector< ppair > pairs;
    // store every pixel we need to draw from letters
	//get the pixel 0
	//int pixel0=letters.getPixel(0,0);
	//Debug::debug( 2 ) << "Loader:loading screen // Pixel 0 = "<< pixel0 <<endl;

	int mask =  Colors::makeColor(255,0,255);
    for ( int x = 0; x < letters.getWidth(); x++ ){
        for ( int y = 0; y < letters.getHeight(); y++ ){
            int pixel = letters.getPixel( x, y );
            //Debug::debug( 2 ) << "Loader:loading screen // Letters Pixel | Mask = "<< pixel <<" | "<< Colors::makeColor(255,0,255) << endl;

			if ( pixel !=  mask){
                Debug::debug(2100,__FUNCTION__ ) << " Creating Letters: Putting Pixel (x,y) = "<<"( "<<x<<","<<y<<" )" << endl;
				ppair p;
                p.x = x;
                p.y = y;
                pairs.push_back( p );
            }
        }
    }

    const int MAX_COLOR = 200;

     Colors::ColorDefinition colors[ MAX_COLOR ];
     Colors::ColorDefinition c1 = CBitmap::makeSDLColor( 16, 16, 16 );
     Colors::ColorDefinition c2 = CBitmap::makeSDLColor( 192, 8, 8 );
    // blend from dark grey to light red
    Util::blend_palette( colors, MAX_COLOR / 2, c1, c2 );
    Util::blend_palette( colors + MAX_COLOR / 2, MAX_COLOR / 2, c2, c1 );

    Global::speed_counter = 0;

    if (levelInfo.getBackground() != 0){
		Loader::setupBackground(*levelInfo.getBackground(), load_x, load_y, load_width, load_height, infobox_x, infobox_y, infoBackground.getWidth(), infoBackground.getHeight(), infoBackground, work);
    } else {
        Loader::setupBackground(CBitmap(levelInfo.loadingBackground()), load_x, load_y, load_width, load_height, infobox_x, infobox_y, infoBackground.getWidth(), infoBackground.getHeight(), infoBackground, work);

        //CBitmap background(levelInfo.loadingBackground());
        //background.Blit(load_x, load_y, load_width, load_height, 0, 0, work);
        //Font::getDefaultFont().printf( 400, 480 - Font::getDefaultFont().getHeight() * 5 / 2 - Font::getDefaultFont().getHeight(), Colors::makeColor( 192, 192, 192 ), background, "SGF version %s", 0, Global::getVersionString().c_str());
        //Font::getDefaultFont().printf( 400, 480 - Font::getDefaultFont().getHeight() * 5 / 2, Colors::makeColor( 192, 192, 192 ), background, "Made by Rasputtim", 0 );
        //background.BlitToScreen();
        //background.Blit(infobox_x, infobox_y, infoBackground.getWidth(), infoBackground.getHeight(), 0, 0, infoBackground);

    }
    bool quit = false;

    // keeps the colors moving
    static unsigned mover = 0;
    bool firstDraw = true;

    while ( ! quit ){

        bool draw = false;
        bool drawInfo = firstDraw;
        firstDraw = false;
        if ( Global::speed_counter > 0 ){
            double think = Global::speed_counter;
            Global::speed_counter = 0;
            draw = true;

            while ( think > 0 ){
                mover = (mover + 1) % MAX_COLOR;
                think -= 1;
            }
            //drawInfo = info.transferMessages(infobox);
        } else {
            Util::rest( 1 );
        }

        if ( draw ){
            //desenha a listra movimentante na tela
			//Debug::debug( 2 ) << "Loader:loading screen // Put Pixel to Work  "<<  endl;

			for ( vector< ppair >::iterator it = pairs.begin(); it != pairs.end(); it++ ){
                 Colors::ColorDefinition color = colors[ (it->x - mover + MAX_COLOR) % MAX_COLOR ];
				//! putpixel só funciona para a surface  e não para a textura
				//Debug::debug( 2 ) << "Loader:loading screen // Put Pixel to Work (x,y) = "<< "( "<<  it->x<<","<< it->y <<" ) "<<  endl;

				work.putPixelSurface( it->x, it->y, color.r,color.g,color.b );
            }

            if (drawInfo){
                infoBackground.Blit(infoWork); //! este método só trabalha com a Surface

                // cheesy hack to change the font size. the font
                // should store the size and change it on its own

                 // Não entendi oporque eu fiz isso aqui embaixo?
				 //TODO:: SOLVE THIS
                 CResource::getTTFont(fontName, 13, 13);

                //infobox.draw(0, 0, infoWork, infoFont);
                 CResource::getTTFont(fontName, 24, 24);
				 infoWork.updateTexture();
                 infoWork.BlitAreaToScreen(infobox_x, infobox_y);
				 infoWork.BlitToScreen();
            }
            // work already contains the correct background
            // work.Blit( load_x, load_y, *CBitmap::Screen );
			//work.applyDefTrans();
			work.updateTexture();
			//!realmente não colocaa área  na tela...
			work.BlitAreaToScreen( load_x, load_y );
            work.BlitToScreen();

        }

		FreeListMutexType::scoped_lock lock;
        lock.acquire(loading_screen_mutex);
        quit = done_loading;
		Debug::debug(2100,__FUNCTION__ ) << "screen done loading=" << quit << endl;
		if (quit) {
		 Debug::debug(2100,__FUNCTION__ ) << "screen quit=" << quit << endl;
		}
        lock.release();
	}

    Debug::debug(2100,__FUNCTION__ ) << "screen ENDING TASK" << endl;
    return NULL;
}
#endif
}
} //end SGF