
#ifndef _TUT_GAME_H_
#define _TUT_GAME_H_

#include "game/SGF_Control.h"
#include "game/SGF_World.h"

namespace SGF {
class CBaseObject;
class CGameControl;
class CBitmap;
class CWorld;
}
class CTutGameControl : public SGF::CGameControl
{


public:
//Contructor Destructor
	//! CMenu_v2 actions

    CTutGameControl();
    ~CTutGameControl();
	// Métodos virtuais herdados da classe Base
	int runMenu() {return true;};
	bool loadConfiguration(){return true;};  //De fato as configurações devems er carregadas antes de inicializar a classe

	//Métodos locais
	void initWindow();
	void setQuit( bool q ) { quit = q; }
	inline bool getQuit() const { return quit; }
	SGF::CBitmap* getWork() { return work;}
	inline SGF::CBitmap *getScreen() {return work;}

protected:


private:
	CInputManager *pCurInputManager;  //! inicializa Inpout Manager
    //////////////
    //Global
    //////////////
	bool  quit;       //if true then quit application
	SGF::CBitmap *work;      //screen bitmap

};

class Game :public CWorld
{
public:
    Game();
    ~Game();
	enum Actions{
			Up,
			Down,
			Left,
			Right,
			Select,
			Back,
			Cancel,
			Modify,
			Pause,
			ChangeSkin,
			InitEditor,
			SaveEditor,
			ShowFPS,
			ActionN,
			ChangeLevel,
			ActionH,
			Click,
			Help,
			TogleSound
		};

	virtual void act() ;
	virtual void draw( SGF::CBitmap * work=NULL );
	void showHelpScreen();
	void showEditorHelpScreen();
	virtual bool isFinished() const {return getGameControl()->getQuit();};

	virtual void reloadLevel();

    //s virtual Script::CEngine * getEngine() const = 0;

	/* upper left hand corner of the screen */
	virtual int getX() {return 0;};
	virtual int getY() {return 0;};
	 /* set to paused */
	virtual void pause() ;
	/* mostra tela de help */
	virtual void help() ;
	virtual bool isPaused() {return ispaused;};


	void renderEnterHscore();
    void renderViewHscore();
	void setGameControl(CTutGameControl * Game) { gameControl=Game;}
	inline CTutGameControl *getGameControl() const { return gameControl;}
	void addMessage(Network::Message m, Network::Socket from = 0, Network::Socket to = 0){};


    void processInput(int k, int ix = -1, int iy = -1);
    void processLogic();
    void logicGame();
    void logicEnterHscore();

    void nextLvl();
    void gameInit(std::string level="", std::string skin="", bool editor=false);

    void boost();

    int  getState() { return state; }
    void setState( int st);

    void toggleFps() { showfps = !showfps; }

    void clearHscore();

    bool isinit;

    void changeSkin();

    void initEditor();
    void renderEditor();
    void logicEditor();
    void editorSave();
    void setEditorPath(std::string path) {editorpath=path;}
	//! Game Loop Process everything
	static void run(Game & thisGame);
	void doAction(Actions Action, int mousex=0, int mousey=0);
    void PrepareShutdown();

private:
	CTutGameControl * gameControl;
    int
            state,
            counter;  //incrementado a cada vez que executa o método render

    std::string
            fps;

    SDL_Rect
            fpsbox,
            scorebox,
            floatingscorebox;

    unsigned int
            ticks;


    ///////////////////////
    // GAME OBJECTS
    //////////////////////

    int
            key,
            score,
            objscore,
            floatingX,
            floatingY,
            floatingscore,
            floatingscorecounter,
            specialspawntime,
            level,
            namecol[3],
            hscoreselection;

    unsigned int
            time,
            oldtime,
            ghosttick,
            fruittick,
            pausetick,
            boosttick;

    bool
            inputwaiting,
            gamestarted,
            showHelp,
            ispaused,
            renderisbusy;
	static bool showfps;
    std::string
            num[10],
            name;

    //////////////////////////////////
    // EDITOR OBJECTS
    //////////////////////////////////

    int
            activetool,
            mouseX,
            mouseY;

    std::string
            editorpath;

};

#endif
