/*
  SGPacMan - Salvat Game Pacman (https://sourceforge.net/projects/sgfpacman/)
  Copyright (C) 2010-2011 Rasputtim <rasputtim@hotmail.com>

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
#ifdef printf
#undef printf
#endif

#include "Game.h"

class CConfiguration;


extern SGF::Debug::CLog logtxt;

bool Game::show_fps=false;


void Game::run(Game & thisGame){
	SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << " BEGIN RUN THE GAME==========================" << endl;

    struct GameState{
        GameState():
            endMatch(false){
            }

        bool endMatch;
    };

    class Logic: public SGF::Input::CLogic {
    public:
        Logic(GameState & state, Game * thisGame):
        state(state),
        pacGame(thisGame),
		xpos(0),
		ypos(0)
		{


            /* FIXME: use an enum here */
			gameInput.set(SGF::CKeyboard::Key_UP, 10, false, Up);
			gameInput.set(SGF::CKeyboard::Key_DOWN, 10, false, Down);
            gameInput.set(SGF::CKeyboard::Key_LEFT, 10, false, Left);
            gameInput.set(SGF::CKeyboard::Key_RIGHT, 10, true, Right);
			gameInput.set(SGF::CKeyboard::Key_ENTER, 0, true, Select);
			gameInput.set(SGF::CKeyboard::Key_ESC, 0, true, 6);
			gameInput.set(SGF::CKeyboard::Key_SPACE, 0, true, 7);
			gameInput.set(SGF::CKeyboard::Key_P, 0, true, 8);
			gameInput.set(SGF::CKeyboard::Key_S, 10, true, 9);
			gameInput.set(SGF::CKeyboard::Key_E, 0, true, 10);
			gameInput.set(SGF::CKeyboard::Key_W, 0, true, 11);
			gameInput.set(SGF::CKeyboard::Key_F, 0, true, 12);
			gameInput.set(SGF::CKeyboard::Key_N, 0, true, 13);
			gameInput.set(SGF::CKeyboard::Key_L, 0, true, 14);
			gameInput.set(SGF::CKeyboard::Key_Q, 0, true, 15);
			gameInput.set(SGF::CKeyboard::Key_H, 0, true, 17);
			gameInput.set(SGF::CKeyboard::Key_T, 0, true, 18);
			//gameInput.set(SGF::CMouse::Key_MoveLEFT, 0, true, Left);
			//gameInput.set(SGF::CMouse::key_MoveRIGHT, 0, true, Right);
			gameInput.set(SGF::CMouse::Key_LEFT, 0, true, Click);
			//gameInput.set(SGF::CMouse::Key_MoveUP,0,true,Up);
			//gameInput.set(SGF::CMouse::Key_MoveDOWN,0,true,Down);
            //gameInput.set(SGF::CConfiguration::config(0).getJoystickQuit(), 0, true, 4);
            gameInput.set(SGF::CKeyboard::Key_F5, 10, true, 5);
        }
		//! Keys
        SGF::CInputMap<int> gameInput;
        GameState & state;
        Game *pacGame;
        int xpos;
		int ypos;



     void doInput(){

 	 SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << "BEGIN FASE 1 - Get Events "<<  endl;
	 vector<SGF::CInputMap<int>::InputEvent> events = SGF::CInputManager::getEvents(gameInput);
	 SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << "END FASE 1 - Got Events: "<< events.size()<<  endl;
	 SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << "BEGIN FASE 2 - Proccess Events "<<  endl;

    for (vector<SGF::CInputMap<int>::InputEvent>::iterator it = events.begin(); it != events.end(); it++){
        const SGF::CInputMap<int>::InputEvent & event = *it;

		if (!event.enabled){
            continue;
        }

        if (event.out == Cancel){
                 pacGame->doAction(Cancel) ;
        }

       	SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << "Will Begin Doing Actions:  "<< event.out <<  endl;

        switch (event.out){
                case Up: pacGame->doAction(Up); break;
                case Down: pacGame->doAction(Down); break;
                case Left: pacGame->doAction(Left); break;
                case Right: pacGame->doAction(Right); break;
				case Select: pacGame->doAction(Select); break;
				case 6: pacGame->doAction(Cancel); break;
				case 7: pacGame->doAction(Modify); break;
				case 8: pacGame->doAction(Pause); break;
				case 9: pacGame->doAction(ChangeSkin); break;
				case 10: pacGame->doAction(InitEditor); break;
				case 11: pacGame->doAction(SaveEditor); break;
				case 12: pacGame->doAction(ShowFPS); break;
				case 13: pacGame->doAction(ActionN); break;
				case 14: pacGame->doAction(ChangeLevel); break;
				case 15: pacGame->doAction(ActionH); break;
                case 16: {
						pacGame->doAction(Click,event.mouseXpos,event.mouseYpos);
						SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << "Click Detected [x,y] "<< event.mouseXpos << " , "<< event.mouseYpos<<  endl;
						break;
						 }
                case 17: pacGame->doAction(Help); break;
				case 18: pacGame->doAction(TogleSound); break;
                default: break;
            }

		}

		}

        virtual void run(int x){
            // Do stage logic catch match exception to handle the next match
			SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << " WILL RUN THE STAGE LOGIC=========================" << endl;

			pacGame->processLogic();
            //state.endMatch = stage->isMatchOver();

			SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << " BEGIN DO THE INPUT=========================" << endl;

            doInput();
			SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << " END DO THE INPUT=========================" << endl;

        }

        virtual bool done(){
			return pacGame->getGameControl()->getQuit();
        }

        virtual double ticks(double system){
            return SGF::Util::gameTicks(system, 1); //0.1 = gamespeed (variation fro 0 to 1)
        }
    };

    class Draw: public SGF::Input::CDraw {
    public:
        Draw(Game * stage):
            pacGame(stage),
			work(SGF::CConfiguration::screenWidth.getInteger(),SGF::CConfiguration::screenHeight.getInteger()){
            }

        Game * pacGame;
        SGF::CBitmap work;

        virtual void draw(double fps){
			bool show_fps=true;
			SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << " WILL RENDER EVERYTHING to Work: [(CBitmao:: "<< &work<<" ) (Surface: "<< work.getBitmap()<<" )]=========================" << endl;

			//work.clear();
			pacGame->act();

            SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << " EVERYTHING IS RENDERED =========================" << endl;

			if (show_fps){
				SGF::CResource::getDefaultFont()->DrawTextNew(0,pacGame->gameControl->getScreen()->getHeight()-80,SGF::Colors::White, work,"%2.2f FPS",fps);

				SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << " FRAME y =========================" <<pacGame->gameControl->getScreen()->getHeight()-100<< endl;
           }
			work.updateTexture();
			work.BlitToScreen();

        }
    };

    GameState state;
    Logic logic(state,&thisGame); // this não pode ser usado aqui por ser um método estático
    Draw draw(&thisGame);
	SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << " BEGIN DRAW =========================" << endl;
	//Executa aqui o loop do Jogo
	SGF::Input::SGE_standardLoop(logic, draw);
	SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << " END DRAW =========================" << endl;

	SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << " END RUN THE MATCH==========================" << endl;

}


void Game::doAction(Actions Action, int mousex, int mousey) {

	SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << "WILL EXECUTE ACTION:  "<< Action <<  endl;


        switch(Action) {


            case Cancel:
                gameControl->setQuit(true);
                break;
            case Up:
                processInput(Up);
                break;
            case Down:
                processInput(Down);
                break;
            case Left:
                processInput(Left);
				break;
            case Right:
                processInput(Right);
                break;
            case Modify:
                break;
            case Pause:
                break;
            case ActionN:

                break;
            case ChangeLevel:
                gameInit();
                break;
            case ChangeSkin:
                break;
            case InitEditor:

                break;
            case SaveEditor:
                break;
            case ShowFPS:
                toggleFps();
                break;
            case ActionH:
                break;
            case Select:
                processInput(Select);
                break;
            case Help:
                break;
			case Click:

            break;
			case TogleSound:

			break;
            default:
                break;
            }


}

void Game::logicGame() {

    if ( gamestarted ) {
		SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << " WILL START GAME LOGIC" << endl;
		SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << "(1) - GET POSITONS" << endl;
		SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << "(3) - VERIFY COLISION WITH OTHER OBJECTS" << endl;
    }
}


void Game::draw( SGF::CBitmap * work ) {

    std::ostringstream ostr;
    SGF::Colors::ColorDefinition col = SGF::Colors::White;


	// clear the screen
	gameControl->getWork()->clear();
			int version = 1;
			SGF::CTTFFont *tempfont=SGF::CResource::getDefaultFont();
			tempfont->DrawTextNew( 0,10, col, *this->gameControl->getScreen(),"SGF - TUTORIAL 0%d ",version) ;


}



void Game::gameInit() {
    std::string tmpstr;

        isinit=false;
         inputwaiting = false;
        gamestarted = false;
        time = oldtime = SDL_GetTicks();
		name = "AAA";
        namecol[0] = 255;
        namecol[1] = 150;
        namecol[2] = 150;

        act();

        inputwaiting = false;
        gamestarted = false;

        isinit = true;

}


void Game::processInput(int k, int ix, int iy) {

    inputwaiting = true;

    key = k;
    if ( key == Click ) {
        mouseX = ix;
        mouseY = iy;
    }

    if ( !gamestarted  ) {
        gamestarted = true;

    }
}

void Game::processLogic() {

    time = SDL_GetTicks();

    logicGame();

    oldtime = time;
    inputwaiting = false;
}

void Game::act() {
	SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << "BEGIN RENDER GAME"<< endl;

    if ( !renderisbusy ) {
            renderisbusy = true;
            draw();
            renderisbusy = false;
        }
 	SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << "END RENDER GAME"<< endl;
}

Game::Game()
:   isinit(false),
    counter(0),
    inputwaiting(false),
    gamestarted(false),
    renderisbusy(false)
{
    int i;

    time = oldtime = ticks = SDL_GetTicks();

    fps = "loading";

    for (i=0;i<10;i++)
        num[i]='0'+i;

    name = "AAA";
    namecol[0] = 255;
    namecol[1] = 150;
    namecol[2] = 150;
}

Game::~Game()
{


}

//Constructor
CTutGameControl::CTutGameControl():
pCurInputManager(SGF::CInputManager::GetInstance()),  //! Deve inicializar o Input Manager
quit(false),
work(NULL)

{

}

//Destructor
CTutGameControl::~CTutGameControl()
{
	 SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << "BEGIN Deleting CTutGameControl" << endl;
	try {

		SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << "END Deleting CTutGameControl" << endl;

    }

    catch ( SGF::CGeneralError& err ) {
        std::cerr << (err.getFullReason() );
        setQuit(true);
        logtxt.print( err.getFullReason() );
    }
    catch (...) {
        SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << "Unexpected exception";
        setQuit(true);
        //logtxt.print( "Unexpected exception in App::~App()" );
    }
	SGF::Debug::debug(SGF::Debug::gameEngine,__FUNCTION__) << "END Deleting CTutGameControl" << endl;
}





void  CTutGameControl::initWindow() {
    try {

		if ( work )
            delete work;
		work = new SGF::CBitmap(SGF::CConfiguration::screenWidth.getInteger(),SGF::CConfiguration::screenHeight.getInteger());
		logtxt.print("WORK CREATED");

        if (work == NULL)
            throw SGF::CGeneralError("CGeneralError while setting video mode");

        logtxt.print("Work Bitmap CREATED Sucessfully");
    }
    catch ( SGF::CGeneralError& err ) {
        std::cerr << (err.getFullReason() );
        //setQuit(true);
        logtxt.print( err.getFullReason() );
    }
    catch (...) {
        std::cerr << "Unexpected exception in: "<< __FUNCTION__;
        //setQuit(true);
        logtxt.print( "Unexpected exception in CTutGameControl::App()" );
    }
}
