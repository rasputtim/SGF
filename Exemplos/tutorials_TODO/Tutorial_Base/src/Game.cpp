/*
  SGPacMan - Salvat Game Pacman (https://sourceforge.net/projects/sgfpacman/)
  Copyright (C) 2010-2011 Salvatore Giannotta Filho <a_materasu@hotmail.com>

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
#include "TutGlobal.h"

class CConfiguration;


extern Debug::CLog logtxt;

bool Game::showfps=false;

void Game::editorSave() {
 // Todo
}

void Game::logicEditor() {
//todo
}

void Game::renderEditor() {
    //Todo
}

void Game::initEditor() {
//todo

}
void Game::changeSkin() {
 //todo
}

void Game::run(Game & thisGame){
	Debug::debug(Debug::gameEngine,__FUNCTION__) << " BEGIN RUN THE GAME==========================" << endl;

    struct GameState{
        GameState():
            endMatch(false){
            }

        bool endMatch;
    };

    class Logic: public Input::CLogic {
    public:
        Logic(GameState & state, Game * thisGame):
        state(state),
        pacGame(thisGame),
		xpos(0),
		ypos(0)
		{


            /* FIXME: use an enum here */
			gameInput.set(CKeyboard::Key_UP, 10, false, Up);
			gameInput.set(CKeyboard::Key_DOWN, 10, false, Down);
            gameInput.set(CKeyboard::Key_LEFT, 10, false, Left);
            gameInput.set(CKeyboard::Key_RIGHT, 10, true, Right);
			gameInput.set(CKeyboard::Key_ENTER, 0, true, Select);
			gameInput.set(CKeyboard::Key_ESC, 0, true, 6);
			gameInput.set(CKeyboard::Key_SPACE, 0, true, 7);
			gameInput.set(CKeyboard::Key_P, 0, true, 8);
			gameInput.set(CKeyboard::Key_S, 10, true, 9);
			gameInput.set(CKeyboard::Key_E, 0, true, 10);
			gameInput.set(CKeyboard::Key_W, 0, true, 11);
			gameInput.set(CKeyboard::Key_F, 0, true, 12);
			gameInput.set(CKeyboard::Key_N, 0, true, 13);
			gameInput.set(CKeyboard::Key_L, 0, true, 14);
			gameInput.set(CKeyboard::Key_Q, 0, true, 15);
			gameInput.set(CKeyboard::Key_H, 0, true, 17);
			gameInput.set(CKeyboard::Key_T, 0, true, 18);
			//gameInput.set(CMouse::Key_MoveLEFT, 0, true, Left);
			//gameInput.set(CMouse::key_MoveRIGHT, 0, true, Right);
			gameInput.set(CMouse::Key_LEFT, 0, true, Click);
			//gameInput.set(CMouse::Key_MoveUP,0,true,Up);
			//gameInput.set(CMouse::Key_MoveDOWN,0,true,Down);
            //gameInput.set(CConfiguration::config(0).getJoystickQuit(), 0, true, 4);
            gameInput.set(CKeyboard::Key_F5, 10, true, 5);
        }
		//! Keys
        CInputMap<int> gameInput;
        GameState & state;
        Game *pacGame;
        int xpos;
		int ypos;



     void doInput(){

 	 Debug::debug(Debug::gameEngine,__FUNCTION__) << "BEGIN FASE 1 - Get Events "<<  endl;
	 vector<CInputMap<int>::InputEvent> events = CInputManager::getEvents(gameInput);
	 Debug::debug(Debug::gameEngine,__FUNCTION__) << "END FASE 1 - Got Events: "<< events.size()<<  endl;
	 Debug::debug(Debug::gameEngine,__FUNCTION__) << "BEGIN FASE 2 - Proccess Events "<<  endl;

    for (vector<CInputMap<int>::InputEvent>::iterator it = events.begin(); it != events.end(); it++){
        const CInputMap<int>::InputEvent & event = *it;

		if (!event.enabled){
            continue;
        }

        if (event.out == Cancel){
                 pacGame->doAction(Cancel) ;
        }

       	Debug::debug(Debug::gameEngine,__FUNCTION__) << "Will Begin Doing Actions:  "<< event.out <<  endl;

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
						Debug::debug(Debug::gameEngine,__FUNCTION__) << "Click Detected [x,y] "<< event.mouseXpos << " , "<< event.mouseYpos<<  endl;
						break;
						 }
                case 17: pacGame->doAction(Help); break;
				case 18: pacGame->doAction(TogleSound); break;
                default: break;
            }

		}

		}

        virtual void run(int delay){
            // Do stage logic catch match exception to handle the next match
			Debug::debug(Debug::gameEngine,__FUNCTION__) << " WILL RUN THE STAGE LOGIC=========================" << endl;

			pacGame->processLogic();
            //state.endMatch = stage->isMatchOver();

			Debug::debug(Debug::gameEngine,__FUNCTION__) << " BEGIN DO THE INPUT=========================" << endl;

            doInput();
			Debug::debug(Debug::gameEngine,__FUNCTION__) << " END DO THE INPUT=========================" << endl;

        }

        virtual bool done(){
			return pacGame->getGameControl()->getQuit();
        }

        virtual double ticks(double system){
            return Util::gameTicks(system, 0.1); //0.1 = gamespeed
        }
    };

    class Draw: public Input::CDraw {
    public:
        Draw(Game * stage):
            pacGame(stage),
				work(SGF::CConfiguration::screenWidth.getInteger(),SGF::CConfiguration::screenHeight.getInteger()){
            }

        Game * pacGame;
        SGF::CBitmap work;

        virtual void draw(double fps){
			bool show_fps=true;
			Debug::debug(Debug::gameEngine,__FUNCTION__) << " WILL RENDER EVERYTHING to Work: [(CBitmao:: "<< &work<<" ) (Surface: "<< work.getBitmap()<<" )]=========================" << endl;

			//work.clear();
			pacGame->act();

            Debug::debug(Debug::gameEngine,__FUNCTION__) << " EVERYTHING IS RENDERED =========================" << endl;

			if (show_fps){
				CResource::getDefaultFont()->DrawTextNew(0,pacGame->gameControl->getScreen()->getHeight()-80,Colors::White, work,"%2.2f FPS",fps);

				Debug::debug(Debug::gameEngine,__FUNCTION__) << " FRAME y =========================" <<pacGame->gameControl->getScreen()->getHeight()-100<< endl;
           }
			work.updateTexture();
			work.BlitToScreen();

        }
    };

    GameState state;
    Logic logic(state,&thisGame); // this não pode ser usado aqui por ser um método estático
    Draw draw(&thisGame);
	Debug::debug(Debug::gameEngine,__FUNCTION__) << " BEGIN DRAW =========================" << endl;
	//Executa aqui o loop do Jogo
	Input::SGE_standardLoop(logic, draw);
	Debug::debug(Debug::gameEngine,__FUNCTION__) << " END DRAW =========================" << endl;

	Debug::debug(Debug::gameEngine,__FUNCTION__) << " END RUN THE MATCH==========================" << endl;

}


void Game::doAction(Actions Action, int mousex, int mousey) {

	Debug::debug(Debug::gameEngine,__FUNCTION__) << "WILL EXECUTE ACTION:  "<< Action <<  endl;


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
                boost();
                break;
            case Pause:
                if ( getState() == STATE_GAME )
                    pause();
                break;
            case ActionN:

                break;
            case ChangeLevel:
                gameInit();
                break;
            case ChangeSkin:
                changeSkin();
                break;
            case InitEditor:

                break;
            case SaveEditor:
                //                        std::cerr << "w: save map not yet implemented";
                editorSave();
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
                if ( getState() == STATE_GAME )
                    help();
                break;
			case Click:


            break;
			case TogleSound:

			break;
            default:
                break;
            }


}




void Game::clearHscore() {
    //Todo
}

void Game::renderViewHscore() {
	//Todo
}

void Game::setState(int st) {

    if ( st == STATE_GAME ) {

    }
    else if ( st == STATE_STOPPED && state != STATE_STOPPED) {
   }


    state = st;

}

void Game::logicEnterHscore() {
    int j;

    if ( inputwaiting ) {

        switch ( key ) {
        case Right :
            if (hscoreselection==2) hscoreselection=0;
            else hscoreselection++;
            for (j=0;j<3;j++) namecol[j]= 150;
            namecol[ hscoreselection ] = 255;
            break;
        case Left :
            if (hscoreselection==0) hscoreselection=2;
            else hscoreselection--;
            for (j=0;j<3;j++) namecol[j]= 150;
            namecol[ hscoreselection ] = 255;
            break;
        case Down :
            if (name[hscoreselection]=='A') name[hscoreselection]='_';
            else if (name[hscoreselection]=='_') name[hscoreselection]='Z';
            else name[hscoreselection]--;
            break;
        case Up :
            if (name[hscoreselection]=='Z') name[hscoreselection]='_';
            else if (name[hscoreselection]=='_') name[hscoreselection]='A';
            else name[hscoreselection]++;
            break;
        case Select :

        default :
             break;
        }
    }
}
void Game::logicGame() {


    if ( gamestarted && !ispaused ) {
		Debug::debug(Debug::gameEngine,__FUNCTION__) << " WILL START GAME LOGIC" << endl;
		Debug::debug(Debug::gameEngine,__FUNCTION__) << "(1) - GET POSITONS" << endl;
        //////////////////////////////////
        //	GET POSITIONS
        //////////////////////////////////

        //////////////////////////////////
        // MOVE LOGIC
        //////////////////////////////////


        ///////////////////////////////////////////
        //	TIME LOGIC
        ///////////////////////////////////////////


        ///////////////////////////////////////////
        // PACMAN LOCATION LOGIC
        ///////////////////////////////////////////
		Debug::debug(Debug::gameEngine,__FUNCTION__) << "(3) - VERIFY COLISION WITH OTHER OBJECTS" << endl;

        ///////////////////////////////////
        //	OTHER
        ///////////////////////////////////




        //		else (gameControl->getSnd()->modify( 10, 44100 - ((BckgrObj*)objects[BACKGROUND])->getObjCount() * 75) );
    }
}
void Game::renderEnterHscore() {

    // Todo
}
void Game::showEditorHelpScreen() {

						ostringstream out;
						out << "TECLA -> AÇÃO                \n";
						out << "_____________________________\n";
						out << "(H) -> Mostra tela de Help\n";
						out << "(P) -> Pausa o Jogo \n";
						out << "(Q) -> Mostra HSore \n";
						out << "(S) -> Muda Skin\n";
						out << "(E) -> Inicia Editor\n";
						out << "(W) -> Salva Editor \n";
						out << "(F) -> Mostra FPS\n";
						out << "(N) -> Reinicia o Game\n";
						out << "(L) ->  Muda de Level\n";
						out << "(Enter) -> Inicio\n";
						out << "(ESC) -> Sai\n";
						out << "(SPACE) -> Boost \n";


						const CFont *font = (CFont *) CResource::getDefaultFont();
						Util::popup(*font, out.str());
}

void Game::showHelpScreen() {

						ostringstream out;
						out << "TECLA -> AÇÃO                \n";
						out << "_____________________________\n";
						out << "(H) -> Mostra tela de Help\n";
						out << "(P) -> Pausa o Jogo \n";
						out << "(Q) -> Mostra HSore \n";
						out << "(S) -> Muda Skin\n";
						out << "(E) -> Inicia Editor\n";
						out << "(W) -> Salva Editor \n";
						out << "(F) -> Mostra FPS\n";
						out << "(N) -> Reinicia o Game\n";
						out << "(L) ->  Muda de Level\n";
						out << "(Enter) -> Inicio\n";
						out << "(ESC) -> Sai\n";
						out << "(SPACE) -> Boost \n";


						const CFont *font = (CFont *) CResource::getDefaultFont();
						Util::popup(*font, out.str());
}
void Game::draw( SGF::CBitmap * work ) {

    std::ostringstream ostr;
    Colors::ColorDefinition col = Colors::White;


	// clear the screen
	gameControl->getWork()->clear();
    //s try {
        // DRAW FIELD + SPRITES


        // DRAW SCORE + INFO


	//if (CResource::getDefaultFont()) {
			//CTTFFont *tempfont=CResource::getDefaultFont();
			//tempfont->printF( scorebox.x,scorebox.y, col, *this->gameControl->getScreen(),"LEVEL: %d   SCORE: %d",level,level,score) ;
			//this->gameControl->getScreen()->Render("TESTE", 100,100,col,tempfont);
//			tempfont->DrawTextNew(scorebox.x,scorebox.y,col,*this->gameControl->getScreen(),"LEVEL: %d   SCORE: %d",level,score);

		//}

        //DRAW SCORE POPUP
        if (floatingscorecounter != 0) {
            std::ostringstream scoretext;

            scoretext << floatingscore;
            floatingscorecounter--;

            floatingscorebox.y--;
			//SDL_SetAlpha(txt,SDL_SRCALPHA,	55+floatingscorecounter*2);
			//if (CResource::getDefaultFont())
			CResource::getDefaultFont()->DrawTextNew(floatingscorebox.x,floatingscorebox.y,col,*this->gameControl->getScreen(),"%s",scoretext.str().c_str());

        }

        // PAUSE

        if ( ispaused ) {

        }


 /*  }

    catch ( CGeneralError& err ) {
        std::cerr << err.getFullReason();
        gameControl->setQuit(true);
        logtxt.print( err.getFullReason() );
    }
    catch ( ... ) {
        Debug::debug(Debug::gameEngine,__FUNCTION__) << "Unexpected exception"<< endl;
		gameControl->setQuit(true);

    } */
}

void Game::boost() {

}
void Game::help() {

    if ( !ispaused ) {
        ispaused = true;

        pausetick = SDL_GetTicks();
		showHelp = true;

    }
    else {
        ispaused = false;
		showHelp = false;

        int delta( SDL_GetTicks() - pausetick );

        ghosttick += delta;
        fruittick += delta;
        boosttick += delta;


    }
}
void Game::pause() {

    if ( !ispaused ) {
        ispaused = true;

        pausetick = SDL_GetTicks();


    }
    else {
        ispaused = false;

        int delta( SDL_GetTicks() - pausetick );

        ghosttick += delta;
        fruittick += delta;
        boosttick += delta;


    }
}
void Game::nextLvl() {
    std::string tmpstr;


    try {
        level++;

        objscore*=2;


        floatingscorecounter = 0;
        floatingscore = 0;
        time = oldtime = SDL_GetTicks();
        ghosttick = 0;

        if (ispaused) pause();


        SDL_Delay(1000);


        act();

        //emptyMsgPump();
        inputwaiting = false;
        gamestarted = false;
    }
    catch ( CGeneralError &err) {
        std::cerr << err.getFullReason();
        gameControl->setQuit(true);
        //logtxt.print( err.getFullReason() );
    }
    catch ( ... ) {
        std::cerr << "Unexpected exception in Game::nextLvl()";
        gameControl->setQuit(true);
        //logtxt.print( "Unexpected error in Game::nextLvl()" );
    }
}

void Game::gameInit(std::string level, std::string skin, bool editor) {
    std::string tmpstr;

    // try {
        isinit=false;
        //m_Game.getSnd()->stop();

       // if ( !settings.loadConfigurations(tmpstr) )
         //   throw CGeneralError("CGeneralError loading level settings");

        //resetting variables
        score=0;
        floatingscorecounter = 0;
        floatingscore = 0;
        objscore = 200;
        inputwaiting = false;
        gamestarted = false;
        time = oldtime = SDL_GetTicks();
        showHelp = false;
        setState( STATE_GAME);
        name = "AAA";
        namecol[0] = 255;
        namecol[1] = 150;
        namecol[2] = 150;
        hscoreselection = 0;


        if ( ispaused )
            pause();




        //DYNAMIC OBJECTS INIT

		Debug::debug(Debug::gameEngine,__FUNCTION__) << " WILL DELETE OBJECTS==========================" << endl;



		Debug::debug(Debug::gameEngine,__FUNCTION__) << "END DELETING OBJECTS==========================" << endl;
	    Debug::debug(Debug::gameEngine,__FUNCTION__) << "Unloading complete" << endl;

        //if level has different field size than currently selected, setup new window with proper size


        // INIT MAPS

        //logtxt.print("Maps loaded");

        //loading level graphics

        //logtxt.print("Level background loaded");


		setState( STATE_STOPPED);

        //create pacman + ghosts




        //logtxt.print("Objects loaded");

        //calculate special fruit spawn time

        if (!editor) act();

        //emptyMsgPump();
        inputwaiting = false;
        gamestarted = false;

        isinit = true;


    /*}
    catch ( CGeneralError &err) {
        std::cerr << err.getFullReason();
        gameControl->setQuit(true);
        logtxt.print( err.getFullReason() );
    }
    catch ( ... ) {
        std::cerr << "Unexpected exception in Game::gameInit()";
        gameControl->setQuit(true);
        logtxt.print( "Unexpected error in Game::gameInit()" );
    } */
}


void Game::reloadLevel() {	// vars and positions when pacman dies during level

    SDL_Delay(1000);
	//! toca o som 9

    // setting vars
    floatingscorecounter= 0;
    floatingscore= 0;
    ghosttick = 0;
    showHelp = false;

    if (ispaused) pause();


   act();
    //emptyMsgPump();
    gamestarted= false;
    inputwaiting = false;
}
void Game::processInput(int k, int ix, int iy) {

    inputwaiting = true;

    key = k;
    if ( key == Click ) {
        mouseX = ix;
        mouseY = iy;
    }

    if ( !gamestarted && !ispaused ) {
        gamestarted = true;
        if ( state == STATE_STOPPED || state == STATE_GAME )
            setState( STATE_GAME );
    }
}

void Game::processLogic() {

    time = SDL_GetTicks();

    if ( state == STATE_GAME ) logicGame();

    oldtime = time;
    inputwaiting = false;
}

void Game::act() {
	Debug::debug(Debug::gameEngine,__FUNCTION__) << "BEGIN RENDER GAME"<< endl;

    Colors::ColorDefinition
            col;

    col.r = col.g = col.b = 255;

   /* if (counter == 100) {   // a cada 100 execuções de render ele pega o valor de FPS
        fps = getFPS();
        counter = 0;
    } */

 //   try {
        if ( !renderisbusy ) {
            renderisbusy = true;

            ////////////////////////////////
            // STATE SWITCH
            ////////////////////////////////

            if ( (state == STATE_GAME) || (state == STATE_STOPPED) ) draw();


            if ( showfps ) {
				//if (CResource::getDefaultFont())
				CResource::getDefaultFont()->DrawTextNew(fpsbox.x,fpsbox.y,col,*this->gameControl->getScreen(),"%s",fps.c_str());

            }


            renderisbusy = false;
      //      counter++;
        }
  /*  }
    catch ( CGeneralError& err ) {
        //std::cerr << err.getFullReason();
        gameControl->setQuit(true);
         Debug::debug(Debug::gameEngine,__FUNCTION__) << err.getFullReason() << endl;
    }
    catch ( ... ) {
        gameControl->setQuit(true);
        Debug::debug(Debug::gameEngine,__FUNCTION__) << "Unexpected exception in Game::Render"<< endl;

    } */
	Debug::debug(Debug::gameEngine,__FUNCTION__) << "END RENDER GAME"<< endl;
}


void Game::PrepareShutdown() {

}

Game::Game()
:   isinit(false),
    state(STATE_STOPPED),
    counter(0),
    objscore(200),
    floatingscore(0),
    floatingscorecounter(0),
    level(1),
    hscoreselection(0),
    inputwaiting(false),
    gamestarted(false),
    showHelp(false),
	ispaused(false),
    renderisbusy(false)

{
    int i;

    time = oldtime = ticks = SDL_GetTicks();

    fps = "loading";

    fpsbox.x= 10;
    fpsbox.w = 290;
    fpsbox.y = 10;
    fpsbox.h = 190;


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
pCurInputManager(CInputManager::GetInstance()),  //! Deve inicializar o Input Manager
quit(false),
work(NULL)

{

}

//Destructor
CTutGameControl::~CTutGameControl()
{
	 Debug::debug(Debug::gameEngine,__FUNCTION__) << "BEGIN Deleting CTutGameControl" << endl;
	try {

		Debug::debug(Debug::gameEngine,__FUNCTION__) << "END Deleting CTutGameControl" << endl;

    }

    catch ( CGeneralError& err ) {
        std::cerr << (err.getFullReason() );
        setQuit(true);
        //logtxt.print( err.getFullReason() );
    }
    catch (...) {
        Debug::debug(Debug::gameEngine,__FUNCTION__) << "Unexpected exception";
        setQuit(true);
        //logtxt.print( "Unexpected exception in App::~App()" );
    }
	Debug::debug(Debug::gameEngine,__FUNCTION__) << "END Deleting CTutGameControl" << endl;
}





void  CTutGameControl::initWindow() {
    try {

		if ( work )
            delete work;
		work = new SGF::CBitmap(SGF::CConfiguration::screenWidth.getInteger(),SGF::CConfiguration::screenHeight.getInteger()+EXTRA_Y_SPACE);
		//logtxt.print("WORK CREATED");

        if (work == NULL)
            throw CGeneralError("CGeneralError while setting video mode");

        //logtxt.print("Work Bitmap CREATED Sucessfully");
    }
    catch ( CGeneralError& err ) {
        std::cerr << (err.getFullReason() );
        //setQuit(true);
        //logtxt.print( err.getFullReason() );
    }
    catch (...) {
        std::cerr << "Unexpected exception in: "<< __FUNCTION__;
        //setQuit(true);
        //logtxt.print( "Unexpected exception in CTutGameControl::App()" );
    }
}
