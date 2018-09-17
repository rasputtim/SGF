/*
  SGF - Super Game Fabric  (https://sourceforge.net/projects/sgfabric/)
  Copyright (C) 2010-2011 Rasputtim <Rasputtim@hotmail.com>

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
#ifndef _S_G_F_configuration_h
#define _S_G_F_configuration_h

#include <map>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <map>

#include "../SGF_Config.h"
#include "../structures/SGF_HashTableFast.h"
#include "../util/SGF_Callback.h"
#include "../input/SGF_Joystick.h"
#include "../input/SGF_Mouse.h"
#include "../input/SGF_Keyboard.h"
#include "../input/SGF_Input.h"
#include "../util/SGF_FontInfo.h"
#include "../objects/SGF_Object.h"
#include "../util/SGF_Path.h"
#include "../structures/SGF_List.h"
#include "../util/SGF_Pointer.h"
#include "SGF_ConfigVars.h"
#define ADDXMLPARAMETER(head,option,parameter) SGF::CGlobalConfiguration::registerConfigValue(head, option, parameter)

using namespace std;
namespace SGF {

class Token;
class CJoystick;

class CInput;
class CFontInfo;
class CBaseObject;


/**
 * \class CGlobalConfiguration
 *
 * \ingroup SGF_Configuration
 *
 * \brief Classe para Sistema de controle de Variáveis e COnfigurações Globais da Engine SGFFabric
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: Rasputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2014
 */
class  SGE_API CGlobalConfiguration: public CSysVarSystem {
public:
/** usado par registrar parâmetros que serão
encontrados nos arquivos de configuração XML de usuários do SGF Fabric
Exemplo:
<head>
<option>
<parameter> VALUE </parameter>
<parameter> VALUE </parameter>
<parameter> VALUE </parameter>
</option>
<parameter> VALUE </parameter>
<option>
<parameter> VALUE </parameter>
<parameter> VALUE </parameter>
</option>
</head>
**/
	typedef map<string , string> confParameter;
	typedef map<string, confParameter> confOption;
	typedef map<string, confOption> confHead;


	CGlobalConfiguration(){ CSysVar::registerGlobalStaticVars();};
	~CGlobalConfiguration(){
	//CList clears itself uppon destruction but not its itens
		m_globalSysVars.deleteContents(false);
	};
	virtual void			init();
	virtual void			Shutdown();
	virtual bool			IsInitialized() const;

	virtual void			Register( CSysVar &cvar );
	//! set the internal CSysvar (The registered one)
	virtual void			setCVarString( const char *name, const char *value, int m_iFlags = 0 );
	virtual void			setCVarBool( const char *name, const bool value, int m_iFlags = 0 );
	virtual void			setCVarInteger( const char *name, const int value, int m_iFlags = 0 );
	virtual void			setCVarFloat( const char *name, const float value, int m_iFlags = 0 );
	//! Get the internal CSysVar (The registered one)
	virtual const char *	getCVarString( const char *name ) const;
	virtual bool			getCVarBool( const char *name ) const;
	virtual int				getCVarInteger( const char *name ) const;
	virtual float			getCVarFloat( const char *name ) const;

	virtual bool			Command( const CCmdArgs &args );

	virtual void			CommandCompletion( void(*callback)( const char *s ) );
	virtual void			ArgCompletion( const char *cmdString, void(*callback)( const char *s ) );

	virtual void			SetModifiedFlags( int m_iFlags );
	virtual int				GetModifiedFlags() const;
	virtual void			ClearModifiedFlags( int m_iFlags );

	virtual void			ResetFlaggedVariables( int m_iFlags );
	virtual void			RemoveFlaggedAutoCompletion( int m_iFlags );
	//virtual void			WriteFlaggedVariables( int m_iFlags, const char *setCmd, idFile *f ) const;

	//virtual const idDict *	MoveCVarsToDict( int m_iFlags ) const;
	//virtual void			SetCVarsFromDict( const idDict &dict );

	//find CSysVar Registered and saved on m_globalSysVars
	virtual CSysVar *		Find( const char *name );
    CSysVar *				FindInternal( const char *name ) const;
	void					setInternal( const char *name, const char *value, int m_iFlags );
	
	//=============CALL BACK SYSTEM=======================

	//! to get user game config file
	static Filesystem::CAbsolutePath getUserConfigFile();
	//! to set user game config file
	static void setUserConfigFile(string fileName);

	//! to register and find user game properties and values;
	static void registerConfigValue(string head, string option, string parameter);
	static string findConfigValue(string head, string option, string parameter);
	//! to load user configuration file into memory variables
	static void loadUserConfigurations();
	static void loadUserConfigurations(string file);

		//=========SDL Configuration
	static SDLState_t * getsdlConfig();

	static void setSDLInitModules(sdlModules_s &initModules);


private:
	bool					m_bInitialized;
	CList<CEngineSysVar*>	m_globalSysVars;
	CHashTableFast			m_SysVarHash;
	int						m_iModifiedFlags;
	//! to store the user game customized config file
	//static string userConfigFileName;
	//! To save user game customized properties
	static confHead userProperties;
	//! A pointer to the SDL Configuration on the CSDLMAnager Module
	static SDLState_t * sdlConfig;

	
	//! this is for the global Vars
	static void				Toggle_f( const CCmdArgs &args );
	static void				Set_f( const CCmdArgs &args );
	static void				SetS_f( const CCmdArgs &args );
	static void				SetU_f( const CCmdArgs &args );
	static void				SetT_f( const CCmdArgs &args );
	static void				SetA_f( const CCmdArgs &args );
	static void				Reset_f( const CCmdArgs &args );
	static void				ListByFlags( const CCmdArgs &args, cvarFlags_t m_iFlags );
	static void				List_f( const CCmdArgs &args );
	static void				Restart_f( const CCmdArgs &args );
	/**
	\brief metodo callback que muda o FPS se houver uma mudança na variável gameFPS
	**/
	static void             changeFPS(void * arg);
public:

//General and Useful Game Vars
static CEngineSysVar	developer;  //! name of Developer
static CEngineSysVar	g_debug;  //! global debug mode

static CEngineSysVar	g_showPVS;
static CEngineSysVar	g_showTargets;
static CEngineSysVar	g_showTriggers;
static CEngineSysVar	g_showCollisionWorld;
static CEngineSysVar	g_showCollisionModels;
static CEngineSysVar	g_showCollisionTraces;
static CEngineSysVar	g_maxShowDistance;
static CEngineSysVar	g_showEntityInfo;
static CEngineSysVar	g_showviewpos;
static CEngineSysVar	g_showcamerainfo;
static CEngineSysVar	g_showActiveEntities;
static CEngineSysVar	g_showEnemies;

static CEngineSysVar	g_frametime;
static CEngineSysVar	g_timeentities;

static CEngineSysVar	ai_debugScript;
static CEngineSysVar	ai_debugMove;
static CEngineSysVar	ai_debugTrajectory;
static CEngineSysVar	ai_testPredictPath;
static CEngineSysVar	ai_showPaths;
static CEngineSysVar	ai_showObstacleAvoidance;

static CEngineSysVar	g_dvTime;
static CEngineSysVar	g_dvAmplitude;
static CEngineSysVar	g_dvFrequency;

static CEngineSysVar	g_showPlayerShadow;
static CEngineSysVar	g_showHud;
static CEngineSysVar	g_showProjectilePct;

static const char *si_gameTypeArgs[];

static const char *ui_skinArgs[];
static CEngineSysVar g_password;
static CEngineSysVar password;
static CEngineSysVar net_serverDownload;
static CEngineSysVar net_serverDlBaseURL;
static CEngineSysVar net_serverDlTable;
static CEngineSysVar engineName;
static CEngineSysVar engineDate;
static CEngineSysVar g_version;

static CEngineSysVar fullScreen;
static CEngineSysVar gameSpeed;
//! Global Frames por segundo
static CEngineSysVar gameFPS;
static CEngineSysVar gameSkipTicks;
//! Multiplier constant for the menu V2 game logic
static CEngineSysVar gameLoopMultiplier;
static CEngineSysVar gameTitleScreen;
static CEngineSysVar gameLanguage;
/* directory of current game/mod */
static CEngineSysVar gameModDir;
static CEngineSysVar gameFontDirectory;
static CEngineSysVar playMode;
//static CEngineSysVar menu_font;
static CEngineSysVar menuFontSize;
static CEngineSysVar screenWidth;
static CEngineSysVar screenHeight;
static CEngineSysVar volumeSound;
static CEngineSysVar volumeMusic;
//! configuration control 
static CEngineSysVar sgfConfigFileName;
static CEngineSysVar sgfDebugConfigFileName;
static CEngineSysVar sgfCustomConfigFileName;
static CEngineSysVar currentSGFDir;

static CEngineSysVar JoystickEnabled;
static CEngineSysVar MouseEnabled;
static CEngineSysVar numberOfWindows;
static CEngineSysVar initVideo;
static CEngineSysVar initAudio;
static CEngineSysVar initTTF;
static CEngineSysVar initFramerateManager;
static CEngineSysVar initWindows;
static CEngineSysVar initTimers;
static CEngineSysVar initJoystick;
static CEngineSysVar initFastevents;
static CEngineSysVar initNetwork;
static CEngineSysVar initTextsupport;
static CEngineSysVar useSIMDprocessor;
};

extern CGlobalConfiguration globalSysVarSystem;


/*
===============================================================================

	SysVar Registration

	Each DLL using SysVars has to declare a private copy of the static variable
	CSysVar::m_p_StaticVars like this: CSysVar * CSysVar::m_p_StaticVars = NULL;
	Furthermore CSysVar::RegisterStaticVars() has to be called after the
	cvarSystem pointer is set when the DLL is first initialized.

===============================================================================
*/

SGF_INLINE_FORCED void CSysVar::init( const char *name, const char *value, int Flags, const char *description,
							float ValueMin, float ValueMax, const char **ValueStrings, callbackArgCompletion_t ValueCompletionFunction,bool local ) {
	this->m_pName = name;
	this->m_pValue = value;
	this->m_iFlags = Flags;
	this->m_pDescription = description;
	this->m_iFlags = m_iFlags | SYSVAR_STATIC;
	this->m_fValueMin = ValueMin;
	this->m_fValueMax = ValueMax;
	this->m_ValueStrings = ValueStrings;
	this->m_tValueCompletion = ValueCompletionFunction;
	this->m_iIntegerValue = 0;
	this->m_fFloatValue = 0.0f;
	this->m_pInternalVar = this;
	this->m_bLocal= local;
	this->m_pObjectCallBack=Util::CReferenceCount< CCallbackBase >(NULL);
	//! if it is local there is no need for registration
	if (!local) {
			//! if it is a static var
			if ( m_p_StaticVars != (CSysVar *)0xFFFFFFFF ) {
			this->m_pNext = m_p_StaticVars;
			m_p_StaticVars = this;
			} else {
			globalSysVarSystem.Register( *this );
			}
	}
}

SGF_INLINE_FORCED void CSysVar::registerGlobalStaticVars() {
	if ( m_p_StaticVars != (CSysVar *)0xFFFFFFFF ) {
		for ( CSysVar *cvar = m_p_StaticVars; cvar; cvar = cvar->m_pNext ) {
			globalSysVarSystem.Register( *cvar );
		}
		m_p_StaticVars = (CSysVar *)0xFFFFFFFF;
	}
}



/**
 * \class CConfiguration
 *
 * \ingroup SGF_Configuration
 *
 * \brief Esta Classe controla toda a configuração do Jogo, e as variáveis de cada player
 *
 *  Ações como Salvar a Configuração, Carregar a configuração salva
 *  Opções como tamanho de tela, configuração do teclado, mouse e joystick
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: Rasputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
  */

class  SGE_API CConfiguration: public CGlobalConfiguration {
public:
	enum ConfigNumber{
		Player1,
		Player2,
		Player3,
		Player4
	};


protected:
	//Construtores
    CConfiguration(int index);
    CConfiguration( const CConfiguration & config );
    CConfiguration & operator=( const CConfiguration & config );
	//!configure default player keys for this instance of CConfiguration and return it
	CConfiguration defaultPlayerKeys();

    static CConfiguration defaultPlayer1Keys();
    static CConfiguration defaultPlayer2Keys();

	static Token * saveKeyboard( int num, CConfiguration * configuration );
    static Token * saveJoystick( int num, CConfiguration * configuration );
    static Token * saveMouse(int num, CConfiguration * configuration);
    static Token * saveSDL();

	
	static int getKeyToken(int config, const string & name, int defaultValue);

    static void setKeyToken(int config, const string & name, int value);



public:

	~CConfiguration();
	//Each player has its own cofiguration set wich is stored on this vector
	static vector<CConfiguration *> ConfigList;

	virtual void			init();
	virtual void			shutdown();
	virtual bool			isInitialized() const;

	virtual void			Register( CSysVar &cvar );  //Register Local

	virtual CSysVar *		Find( const char *name );  //!Find return the internal registered CSysVar
    //! set the value of the internal registered CEngineSysvar
    //! so, it is impossible to change the value of an initialized CSysvar. Only changes to the internal registered CSysVar are allowed
	virtual void			setCVarLocalString( const char *name, const char *value, int m_iFlags = 0 );
	virtual void			setCVarLocalBool( const char *name, const bool value, int m_iFlags = 0 );
	virtual void			setCVarLocalInteger( const char *name, const int value, int m_iFlags = 0 );
	virtual void			setCVarLocalFloat( const char *name, const float value, int m_iFlags = 0 );
    //! get the value of the internal registered CEngineSysvar
	virtual const char *	getCVarLocalString( const char *name ) const;
	virtual bool			getCVarLocalBool( const char *name ) const;
	virtual int				getCVarLocalInteger( const char *name ) const;
	virtual float			getCVarLocalFloat( const char *name ) const;

    //! callback system for commands. Not implemented yet
	virtual bool			Command( const CCmdArgs &args );
	virtual void			CommandCompletion( void(*callback)( const char *s ) );
	virtual void			ArgCompletion( const char *cmdString, void(*callback)( const char *s ) );

	virtual void			SetModifiedFlags( int m_iFlags );
	virtual int				GetModifiedFlags() const;
	virtual void			ClearModifiedFlags( int m_iFlags );

	virtual void			ResetFlaggedVariables( int m_iFlags );
	virtual void			RemoveFlaggedAutoCompletion( int m_iFlags );
	
	//! find a local registered ClocalSysVar
	CLocalSysVar *			findLocalInternal( const char *name ) const;
	void					setLocalInternal( const char *name, const char *value, int m_iFlags );

private:
	bool					initialized;
	//! save a list of the internal CLocalSysVars
	//! internal CLocalSysVars are copies of the declared ones created uppon registration time
	CList<CLocalSysVar*>	cvars;
	CHashTableFast			cvarHash;
	int						modifiedFlags;



public:


    typedef SGF::CJoystick::Key JoystickInput;
	typedef SGF::CMouse::Key MouseInput;
	typedef SGF::CKeyboard::Key KeyboardInput;
	typedef SGF::CKeyboard::Mod KeyboardMod;

	static void setStringProperty(const string & path, const string & value);
    static string getStringProperty(const string & path, const string & defaultValue);

	static void setProperty(const string & path, const string & value);
    static string getProperty(const string & path, const string & defaultValue);

    static void setProperty(const string & path, int value);
    static int getProperty(const string & path, int value);

    static void setProperty(const string & path, double value);
    static double getProperty(const string & path, double value);

    static void setProperty(const string & path, bool value);
    static bool getProperty(const string & path, bool value);

    static void setProperty(const string & path, Token * value);
    /**/
	/* Might return NULL */
    static Token * getProperty(const string & path);
	//mINE
	static void setPropertySalva(string name, string value);



	//instancia um objeto da classe CConfiguration e volta a referência
    static CConfiguration * getConfig(int x);
	static void sm_saveConfiguration();
	
	//=======INPUT METHODS======
	/* Este método converte uma Game Key ou user Key para uma tecla do teclado,
	* ou seja, retorna uma tecla do teclado para uma Game Key dada
	*/
	int getKey( CInput::GameKeys which, int hFacing, int vFacing=(int) CBaseObject::FACING_UP ) const;
	/* retorna a tecla correspondente ao nome*/
	KeyboardInput getKey(const char *nameofKey);
	static KeyboardInput  getKey(int config, const char *nameofKey);
	void setKey(const char *nameofKey,KeyboardInput key);
	//static JoystickInput getJoystickKey(int config, const string & name, JoystickInput defaultValue);

    static void setKey(int config, const char *nameofKey, int value);
    //static void setJoystickKey(int config, const string & name, const JoystickInput & what);

	/* Este método converte uma Game Key ou user Key para uma tecla do Joystick,
	* ou seja, retorna uma tecla do Joystick para uma Game Key dada
	*/
	int getJoystickKey(CInput::GameKeys which, int hFacing, int vFacing=(int) CBaseObject::FACING_UP ) const;
	//Retorna a joystick key configurada na CSysVar
	JoystickInput getJoyKey(const char *nameofKey);
	static JoystickInput  getJoyKey(int config, const char *nameofKey);
	void setKey(const char *nameofKey,JoystickInput key);
	/* Este método converte uma Game Key ou user Key para uma tecla do Mouse,
	* ou seja, retorna uma tecla do Mouse para uma Game Key dada
	*/
	int getMouseKey( CInput::GameKeys which, int hFacing, int vFacing=(int) CBaseObject::FACING_UP  ) const;
	//Retorna a mouse key configurada na CSysVar
	MouseInput getMouseKey(const char *nameofKey);
	static MouseInput  getMouseKey(int config, const char *nameofKey);
    void setKey(const char *nameofKey,MouseInput  key);
	static KeyboardInput intToKeyboard(int a);
	static KeyboardMod intToKeyboardMod(int a);
	static JoystickInput intToJoystick(int a);
    static MouseInput intToMouse(int a);

	//=============END INPUT====================


	//=====MENU METHODS===================
	static bool hasMenuFont();
	static Util::CReferenceCount<CFontInfo> getMenuFont_v2();
	static void setMenuFont_v2(const Util::CReferenceCount<CFontInfo> & str);


	//==========CONFIGURATION CONTROL==============
	static Filesystem::CAbsolutePath getEngineConfigFile();
	static Filesystem::CAbsolutePath getDebugConfigFile();
	//! first load debug configuration then load Engine configuration
	static void loadConfigurations()throw (CLoadException);
	static void loadDebugConfiguration()throw (CLoadException);
	static void loadDefaultDebugConfiguration();
	static void loadEngineConfiguration()throw (CLoadException);
	static void loadTesteConfiguration()throw (CLoadException);
    static void disableSave();
    static void setSave(bool what);
    static bool getSave();

private:
	
	// Not static. Deve haver uma instância da classe para inicializá-las

     /* keyboard - To save engine configured keys */
	 
     CLocalSysVar  ButtonRight;
	 CLocalSysVar  ButtonLeft;
	 CLocalSysVar  ButtonUp;
	 CLocalSysVar  ButtonDown;
	 CLocalSysVar  Button1;
	 CLocalSysVar  Button2;
	 CLocalSysVar  Button3;
	 CLocalSysVar  Button4;
	 CLocalSysVar  Button5;
	 CLocalSysVar  Button6;
	 CLocalSysVar  Button7;
	 CLocalSysVar  Button8;
	 CLocalSysVar  Button9;
	 CLocalSysVar  ButtonJump;
	 CLocalSysVar  ButtonGrab;
	 CLocalSysVar  ButtonStart;
	 CLocalSysVar  ButtonSelect;
	 CLocalSysVar  ButtonDeal;
	 CLocalSysVar  ButtonBet;
	 CLocalSysVar  ButtonDoubleUP;
	 CLocalSysVar  ButtonStand;
	 CLocalSysVar  ButtonOpen;
	 CLocalSysVar  ButtonConfig;
	 CLocalSysVar  ButtonPause;
	 CLocalSysVar  ButtonReset;
	 CLocalSysVar  ButtonShowGFX;
	 CLocalSysVar  ButtonShowFPS;
	 CLocalSysVar  ButtonSaveConfig;
	 CLocalSysVar  ButtonLoadConfig;
	 CLocalSysVar  ButtonDebugger;
	 CLocalSysVar  ButtonToggleConsole;
	 CLocalSysVar  ButtonReload;
	 CLocalSysVar  ButtonCancel;
	 CLocalSysVar  ButtonQuit;

	 /* joystick */
	 // DEFINIÇÕES DA CLASSE CConfiguration

	 CLocalSysVar  JoyButtonRight;
	 CLocalSysVar  JoyButtonLeft;
	 CLocalSysVar  JoyButtonUp;
	 CLocalSysVar  JoyButtonDown;
	 CLocalSysVar  JoyButton1;
	 CLocalSysVar  JoyButton2;
	 CLocalSysVar  JoyButton3;
	 CLocalSysVar  JoyButton4;
	 CLocalSysVar  JoyButton5;
	 CLocalSysVar  JoyButton6;
	 CLocalSysVar  JoyButton7;
	 CLocalSysVar  JoyButton8;
	 CLocalSysVar  JoyButton9;
	 CLocalSysVar  JoyButtonJump;
	 CLocalSysVar  JoyButtonGrab;
	 CLocalSysVar  JoyButtonStart;
	 CLocalSysVar  JoyButtonSelect;
	 CLocalSysVar  JoyButtonDeal;
	 CLocalSysVar  JoyButtonBet;
	 CLocalSysVar  JoyButtonDoubleUP;
	 CLocalSysVar  JoyButtonStand;
	 CLocalSysVar  JoyButtonOpen;
	 CLocalSysVar  JoyButtonConfig;
	 CLocalSysVar  JoyButtonPause;
	 CLocalSysVar  JoyButtonReset;
	 CLocalSysVar  JoyButtonShowGFX;
	 CLocalSysVar  JoyButtonShowFPS;
	 CLocalSysVar  JoyButtonSaveConfig;
	 CLocalSysVar  JoyButtonLoadConfig;
	 CLocalSysVar  JoyButtonDebugger;
	 CLocalSysVar  JoyButtonToggleConsole;
	 CLocalSysVar  JoyButtonReload;
	 CLocalSysVar  JoyButtonCancel;
	 CLocalSysVar  JoyButtonQuit;

   /* Mouse */
     CLocalSysVar  MouseButtonRight;
	 CLocalSysVar  MouseButtonLeft;
	 CLocalSysVar  MouseButtonUp;
	 CLocalSysVar  MouseButtonDown;
	 CLocalSysVar  MouseButton1;
	 CLocalSysVar  MouseButton2;
	 CLocalSysVar  MouseButton3;
	 CLocalSysVar  MouseButton4;
	 CLocalSysVar  MouseButton5;
	 CLocalSysVar  MouseButton6;
	 CLocalSysVar  MouseButton7;
	 CLocalSysVar  MouseButton8;
	 CLocalSysVar  MouseButton9;
	 CLocalSysVar  MouseButtonJump;
	 CLocalSysVar  MouseButtonGrab;
	 CLocalSysVar  MouseButtonStart;
	 CLocalSysVar  MouseButtonSelect;
	 CLocalSysVar  MouseButtonDeal;
	 CLocalSysVar  MouseButtonBet;
	 CLocalSysVar  MouseButtonDoubleUP;
	 CLocalSysVar  MouseButtonStand;
	 CLocalSysVar  MouseButtonOpen;
	 CLocalSysVar  MouseButtonConfig;
	 CLocalSysVar  MouseButtonPause;
	 CLocalSysVar  MouseButtonReset;
	 CLocalSysVar  MouseButtonShowGFX;
	 CLocalSysVar  MouseButtonShowFPS;
	 CLocalSysVar  MouseButtonSaveConfig;
	 CLocalSysVar  MouseButtonLoadConfig;
	 CLocalSysVar  MouseButtonDebugger;
	 CLocalSysVar  MouseButtonToggleConsole;
	 CLocalSysVar  MouseButtonReload;
	 CLocalSysVar  MouseButtonCancel;
	 CLocalSysVar  MouseButtonQuit;


private:
	/* whether to save the configuration or not */
    static bool save;

	static int menuVersion;
	static Util::CReferenceCount<CFontInfo> menuFont_v2;
//    static int menuFontWidth;
//    static int menuFontHeight;


    static map<string, string> properties;
	

	static ::SGF::Util::CReferenceCount<Token> data;

	int m_iIndex; //index for this confiruration set
};

SGF_INLINE_FORCED void CLocalSysVar::registerLocalStaticVars(int index) {
	if ( m_p_StaticLocalVars[index] != (CSysVar *)0xFFFFFFFF ) {
		for ( CSysVar *cvar = m_p_StaticLocalVars[index]; cvar; cvar = cvar->getNext() ) {
			CConfiguration::ConfigList[index]->Register( *cvar );

		}
		m_p_StaticLocalVars[index] = (CLocalSysVar *)0xFFFFFFFF;
	}
}



} //end namespace SGF
#endif
