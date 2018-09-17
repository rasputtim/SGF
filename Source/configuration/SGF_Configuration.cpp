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
#include "configuration/SGF_Configuration.h"
#include "util/SGF_SdlManager.h"
#include "objects/SGF_Object.h"
#include "util/SGF_TokenReader_xml.h"
#include "util/XmlNode/XmlNode.h"

#ifdef _WIN32
#define _WIN32_IE 0x400
#include <shlobj.h>
#endif
#include <cstddef>

#if !defined(nullptr)
#define nullptr NULL
#endif
using namespace std;
namespace SGF {


static const string INPUT_TYPE = "SDL";

class CSDLManager;
class CObject;
class CTokenReaderXML;
bool CConfiguration::save = true;

#if defined(_MSC_VER)
vector<CSysVar *>	CLocalSysVar::m_p_StaticLocalVars(10,nullptr);
#else
vector<CSysVar *>	CLocalSysVar::m_p_StaticLocalVars(10);  // 10 itens com valor NULL

#endif/* text that appears in the config file */
#define define_config(n,str) static const char * config_##n = str
define_config(  ButtonRight,"key-right");
define_config(  ButtonLeft,"key-Left");
define_config(  ButtonUp,"key-up");
define_config(  ButtonDown,"key-down");
define_config(  Button1,"key-action1");
define_config(  Button2,"key-action2");
define_config(  Button3,"key-action3");
define_config(  Button4,"key-action4");
define_config(  Button5,"key-action5");
define_config(  Button6,"key-action5");
define_config(  Button7,"key-action7");
define_config(  Button8,"key-action8");
define_config(  Button9,"key-action9");
define_config(  ButtonJump,"key-jump");
define_config(  ButtonGrab,"key-grab");
define_config(  ButtonStart,"key-start");
define_config(  ButtonSelect,"key-select");
define_config(  ButtonDeal,"key-deal");
define_config(  ButtonBet,"key-bet");
define_config(  ButtonDoubleUP,"key-doubleup");
define_config(  ButtonStand,"key-stand");
define_config(  ButtonOpen,"key-open");
define_config(  ButtonConfig,"key-config");
define_config(  ButtonPause,"key-pause");
define_config(  ButtonReset,"key-reset");
define_config(  ButtonShowGFX,"key-showGFX");
define_config(  ButtonShowFPS,"key-showFPS");
define_config(  ButtonSaveConfig,"key-saveconfig");
define_config(  ButtonLoadConfig,"key-loadconfig");
define_config(  ButtonDebugger,"key-debugger");
define_config(  ButtonToggleConsole,"key-toggleconsole");
define_config(  ButtonReload,"key-reload");
define_config(  ButtonCancel,"key-cancel");
define_config(  ButtonQuit,"key-quit");

//define_config(buttonR1, "buttonR1");
//define_config(buttonR2, "buttonR2");
//define_config(buttonL1, "buttonL1");
//define_config(buttonL2, "buttonL2");
//define_config(buttonstart, "buttonstart");
//define_config(buttonpause, "buttonpause");
//define_config(buttonselect, "buttonselect");
//define_config(buttonquit, "buttonquit");
//define_config(jump, "jump");

define_config(configuration, "configuration");
define_config(current_game, "current-game");
define_config(fullscreen, "fullscreen");
define_config(game_speed, "game-speed");
define_config(game_fps, "game-fps");
define_config(game_skipticks, "game-skipticks");
define_config(keyboard_configuration, "keyboard-configuration");
define_config(mouse_configuration, "mouse-configuration");
define_config(input, "input");
define_config(joystick_configuration, "joystick-configuration");
define_config(menuversion, "menuversion");
define_config(menu_font, "menu-font");
define_config(menu_font_width, "menu-font-width");
define_config(menu_font_height, "menu-font-height");
define_config(number, "number");
define_config(play_mode, "play-mode");
define_config(screen_size, "screen-size");
define_config(sound, "sound");
define_config(music, "music");
define_config(language, "language");
define_config(mugen_motif, "mugen-motif");
define_config(sdl_configuration, "sdl-configuration");
define_config(number_of_windows, "number-of-windows");
define_config(init_video, "init-video");
define_config(init_audio, "init-audio");
define_config(init_ttf, "init-ttf");
define_config(init_framerate, "init-framerate");
define_config(init_window, "init-window");
define_config(init_timer, "init-timer");
define_config(init_joystick, "init-joystick");
define_config(init_fastevents, "init-fastevents");
define_config(init_network, "init-network");
define_config(init_textsupport, "init-textsupport");

#undef def_config

using namespace std;

static const int InvalidKey = 0;
//static const CConfiguration::JoystickInput InvalidJoystick = CJoystick::Invalid;



// INICIALIZAÇÃO DAS VAIÁVEIS ESTÁTICAS DE CONFIGURAÇÃO GLOBAL
//! Map to Save user properties of their own games
CGlobalConfiguration::confHead CGlobalConfiguration::userProperties; 

CEngineSysVar CGlobalConfiguration::g_password(	"g_password",				"",				SYSVAR_ENGINE | SYSVAR_ARCHIVE, "game password" );
CEngineSysVar CGlobalConfiguration::password("password",					"",				SYSVAR_ENGINE | SYSVAR_NOCHEAT, "client password used when connecting" );
CEngineSysVar CGlobalConfiguration::net_serverDownload(	"net_serverDownload",		"0",			SYSVAR_ENGINE | SYSVAR_INTEGER | SYSVAR_ARCHIVE, "enable server download redirects. 0: off 1: redirect to si_serverURL 2: use builtin download. see net_serverDl cvars for configuration" );
CEngineSysVar CGlobalConfiguration::net_serverDlBaseURL("net_serverDlBaseURL",		"",				SYSVAR_ENGINE | SYSVAR_ARCHIVE, "base URL for the download redirection" );
CEngineSysVar CGlobalConfiguration::net_serverDlTable("net_serverDlTable",		"",				SYSVAR_ENGINE | SYSVAR_ARCHIVE, "pak names for which download is provided, seperated by ;" );
CEngineSysVar CGlobalConfiguration::fullScreen("fullscreen","0",SYSVAR_ENGINE | SYSVAR_BOOL,"SET FULLSCREEN MODE");
CEngineSysVar CGlobalConfiguration::gameSpeed("gamespeed","1.0",SYSVAR_ENGINE | SYSVAR_FLOAT,"The game speed");
CEngineSysVar CGlobalConfiguration::gameFPS("gameFPS","40",SYSVAR_ENGINE | SYSVAR_INTEGER,"The game speed",changeFPS);
CEngineSysVar CGlobalConfiguration::gameSkipTicks("Game Loop Skip Ticks","25",SYSVAR_ENGINE | SYSVAR_FLOAT,"1000 / gameFPS");
CEngineSysVar CGlobalConfiguration::gameLoopMultiplier("Multiplier for the Menu game logic","2",SYSVAR_ENGINE | SYSVAR_FLOAT,"(double) 90 / (double) gameFPS");

CEngineSysVar CGlobalConfiguration::gameTitleScreen("gameTitleScreen","SGF Game Fabric - Game Engine",SYSVAR_ENGINE);
CEngineSysVar CGlobalConfiguration::playMode(	"playmode","Network",			SYSVAR_ENGINE ,"Play Mode");
CEngineSysVar CGlobalConfiguration::menuFontSize("menu_font_size","12",			SYSVAR_ENGINE | SYSVAR_INTEGER,"Default Size of the font used by the menu");
CEngineSysVar CGlobalConfiguration::screenWidth(	"screen_width","640",			SYSVAR_ENGINE | SYSVAR_INTEGER,"Width of the window");
CEngineSysVar CGlobalConfiguration::screenHeight(	"screen_height","480",			SYSVAR_ENGINE | SYSVAR_INTEGER,"Height of the window");
CEngineSysVar CGlobalConfiguration::volumeSound("soundVolume","80",			SYSVAR_ENGINE | SYSVAR_INTEGER,"Sound Volume");
CEngineSysVar CGlobalConfiguration::volumeMusic("musicVolume","80",			SYSVAR_ENGINE | SYSVAR_INTEGER,"Music Volume");
CEngineSysVar CGlobalConfiguration::gameLanguage("language","Portuguese",SYSVAR_ENGINE,"Language");
CEngineSysVar CGlobalConfiguration::gameModDir("gameModDir","open",SYSVAR_ENGINE,"directory of current game/mod");

CEngineSysVar CGlobalConfiguration::gameFontDirectory("gameFontDirectory","fonts",SYSVAR_ENGINE);
CEngineSysVar CGlobalConfiguration::sgfConfigFileName ("sgfConfigFileName",SGF_CONFIG_FILE_NAME,SYSVAR_ENGINE,"to store the Engine game configuration file - this is the default");
CEngineSysVar CGlobalConfiguration::sgfDebugConfigFileName ("sgfDebugConfigFileName",SGF_DEBUG_CONFIG_FILE_NAME ,SYSVAR_ENGINE,"to store the Debug game configuration file - this is the default");
CEngineSysVar CGlobalConfiguration::sgfCustomConfigFileName ("sgfCustomConfigFileName",SGF_DEBUG_CONFIG_FILE_NAME ,SYSVAR_ENGINE,"to store the User Custom game configuration file - this is the default");
CEngineSysVar CGlobalConfiguration::currentSGFDir ("currentSGFDir",SGF_CONFIG_FILE_DIR,SYSVAR_ENGINE,"configura o diretório onde estão os arquivos de configuracao do engine ");

CEngineSysVar CGlobalConfiguration::JoystickEnabled("joystickEnabled","0",SYSVAR_ENGINE | SYSVAR_BOOL,"Is joystick enabled ?");
CEngineSysVar CGlobalConfiguration::MouseEnabled("mouseEnabled","0",SYSVAR_ENGINE | SYSVAR_BOOL,"Is mouse enabled ?");
CEngineSysVar CGlobalConfiguration::numberOfWindows("number_of_windows","1",SYSVAR_ENGINE | SYSVAR_INTEGER,"Player default number of lives");
CEngineSysVar CGlobalConfiguration::initVideo("init_video","1",SYSVAR_ENGINE | SYSVAR_BOOL,"");
CEngineSysVar CGlobalConfiguration::initAudio("init_audio","1",SYSVAR_ENGINE | SYSVAR_BOOL,"");
CEngineSysVar CGlobalConfiguration::initTTF("init_ttf","1",SYSVAR_ENGINE | SYSVAR_BOOL,"");
CEngineSysVar CGlobalConfiguration::initFramerateManager("init_framerate","1",SYSVAR_ENGINE | SYSVAR_BOOL,"");
CEngineSysVar CGlobalConfiguration::initWindows("init_window","1",SYSVAR_ENGINE | SYSVAR_BOOL,"");
CEngineSysVar CGlobalConfiguration::initTimers("init_timer","1",SYSVAR_ENGINE | SYSVAR_BOOL,"");
CEngineSysVar CGlobalConfiguration::initJoystick("init_joystick","1",SYSVAR_ENGINE | SYSVAR_BOOL,"");
CEngineSysVar CGlobalConfiguration::initFastevents("init_fastevents","1",SYSVAR_ENGINE | SYSVAR_BOOL,"");
CEngineSysVar CGlobalConfiguration::initNetwork("init_network","1",SYSVAR_ENGINE | SYSVAR_BOOL,"");
CEngineSysVar CGlobalConfiguration::initTextsupport("init_textsupport","1",SYSVAR_ENGINE | SYSVAR_BOOL,"");
CEngineSysVar CGlobalConfiguration::useSIMDprocessor("usesimdprocessor","1",SYSVAR_ENGINE | SYSVAR_BOOL,"use SIMD Processor to MATH calculations");
/** ao criar o estado inicial do SDl que será uilizdo para fazer as inicializações
ele utiliza o tamanho da janela default, configurado nas variáveis screenWidth e screenHeight
estes valores devem ser modificados posteriormente antes da inicialização das janelas
**/
SDLState_t *  CGlobalConfiguration::sdlConfig = CSDLManager::CreateState(SDL_INIT_VIDEO,CConfiguration::numberOfWindows.getInteger());

//=============CALL BACK SYSTEM=======================
/** 
\brief Método que o nome do arquivo de configuração especial definido para o game usuário da Engine
\param fileName: nome do arquivo a ser armazenado
\note este arquivo será carregado depois pelo método loadUserConfigurations()
**/	
void CGlobalConfiguration::setUserConfigFile(string  fileName) {
	sgfCustomConfigFileName.setString(fileName.c_str());

}

#if defined(WIN32) //mingw ou msvc
/** 
\brief Método que rtorna o caminho do arquivo de configuração especial definido para o game usuário da Engine no médoto setUserConfigFile
\note Se o arquivo não existir....
**/	
Filesystem::CAbsolutePath CGlobalConfiguration::getUserConfigFile(){

    ostringstream str;
    char path[MAX_PATH];
    SHGetSpecialFolderPathA(0, path, CSIDL_APPDATA, false);
	const  char * file= sgfCustomConfigFileName.getString();
	string filestr(file);
	str << path << "/" + filestr;
	Filesystem::CAbsolutePath configFilePath;

	 configFilePath = Filesystem::CAbsolutePath(str.str());
    if (configFilePath.exist())
		return Filesystem::CAbsolutePath(str.str());
	else{
		Filesystem::CAbsolutePath tempPath=Filesystem::CAbsolutePath();
		Filesystem::CIsolatedPath isopath(filestr);
		return tempPath.joinToCurrent(isopath);

	}


	/*

	ostringstream str;
	//char path[ MAX_PATH ];
	//SHGetSpecialFolderPathA( 0, path, CSIDL_APPDATA, false );
	const char *path="data";
	str << path << "/sge_user_configuration.xml";
	return str.str();*/
}

#endif

/** método usado par registrar parâmetros que serão
encontrados nos arquivos de configuração XML de usuários  do SGF Fabric
registrados pelo método setUserConfigFile(filename)
\param string head: head XML  do parâmetro a ser registrada
\param string option: option XML do parâmetro a ser registrado
\param string parameter: nome do parâmetro a ser registrado

\note Exemplo de estrutura do arquivo XML:
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

void CGlobalConfiguration::registerConfigValue(string head, string option, string parameter){
	CConfiguration::confHead::iterator first_it = userProperties.find(head);
            if (first_it == userProperties.end()) { //nao achou o head. adicionará um
				    userProperties[head] [option][parameter]="";

			}else{
				confOption::iterator second_it = first_it->second.find(option);
				if (second_it == first_it->second.end())
				{ //nao achou o option . adicionará um
					first_it->second[option][parameter]="";
				}else{
					confParameter::iterator it = second_it->second.find(option);
					if (it == second_it->second.end())
					{//nao achou o parameter . adicionará um
						second_it->second[parameter]="";
					}
                }
            }


}

string CGlobalConfiguration::findConfigValue(string head, string option, string parameter){
	confHead::iterator first_it = userProperties.find(head);
            if (first_it != userProperties.end())
			{ //achou o head. agora achará o option
				confOption::iterator second_it = first_it->second.find(option);
				if (second_it != first_it->second.end())
				{//achou o option. agora achará o parameter
					confParameter::iterator it = second_it->second.find(option);
					if (it != second_it->second.end())
					{ //achou oparameter. agora achará o valor
					return it->second;
					//Set the ColorPallet file the pcx images and extract the images from the sff file
					}
                }
            }

	// não encontrou
	return "";

}

/** 
\brief Método que carrega as configurações definidas pelo programa usuário da Engine SGFFabric
       cada programa usuário pode definir arquivos XML com configuração. Este método carrega esses arquivos
\param file: nome do arquivo a carregar
\note este método preserva o nome do arquivo já cadast
      na variável userConfigFileName.
\note antes de carregar o arquivo, deve se registrar as heads, options e parameters que serão
      encontrados nesse arquivo através do método registerConfigValue
**/
void CGlobalConfiguration::loadUserConfigurations(string file){
	string temp=getUserConfigFile().path();
	setUserConfigFile(file);
	loadUserConfigurations();
	setUserConfigFile(temp);
}
/** 
\brief Método que carrega as configurações definidas pelo programa usuário da Engine SGFFabric
       cada programa usuário pode definir arquivos XML com configuração. Este método carrega esses arquivos
\note carrega o arquivo registrado na variável userConfigFileName.
\note antes de carregar o arquivo, deve se registrar as heads, options e parameters que serão
      encontrados nesse arquivo através do método registerConfigValue
**/
void CGlobalConfiguration::loadUserConfigurations(){
	//! não pode por mensagens de debug neste método. não sei porque ainda????
	Debug::debug( Debug::configuration,__FUNCTION__ ) << "START LOADING USER CONFIGURATIONS: "  << endl;
	//CDisable disable;
//	try{

		//Filesystem::CAbsolutePath file = Filesystem::getInstance().configFile();


		 CTokenReaderXML tr(getUserConfigFile().path());

		 Token * headView = tr.readToken();


      //  if (*head != config_configuration){
       //     throw LoadException(__FILE__, __LINE__, string("Config file ") + Filesystem::getInstance().configFile().path() + " does not use the configuration format" );
        //}else {
			headView->print("");
		//}
			Debug::debug(Debug::configuration,__FUNCTION__) << "SIZE OF USER CONFIGURATION HEADS:  " << userProperties.size() << endl;
			/**
			typedef map<string , string> confParameter;
	typedef map<string, confParameter> confOption;
	typedef map<string, confOption> confHead;
	head->option->parameter
	*/
			for (CConfiguration::confHead::iterator first_it = userProperties.begin();
				first_it != userProperties.end(); first_it++) {
					Debug::debug(Debug::configuration,__FUNCTION__) << " Head Value: " << (first_it->first) << endl;
					if (*headView == first_it->first) {
						//first_it->first = name of the head name
						//first_it->second = the confOption map
						TokenView headx = headView->view();

						while (headx.hasMore()){
						const Token * head;
						headx >> head;
						Debug::debug(Debug::configuration,__FUNCTION__) << "SIZE OF USER CONFIGURATION OPTIONS:  " << first_it->second.size() << endl;
						//head->print(" ");
						//first_it->second.size() = the number of elements on the confOption map
						for (CConfiguration::confOption::iterator second_it =  first_it->second.begin();
						second_it !=  first_it->second.end(); second_it++) {  // para cada option

							if (*head == second_it->first) { // se o token é o nome da opção
								TokenView secondHead = head->view();
								//second_it->first = the name of the option
								//second_it->second = the confParameter map
                                // second_it->second.size() = the number of elements on the confParameter map
								Debug::debug(Debug::configuration,__FUNCTION__) << " Option: " << (second_it->first) << endl;
						        Debug::debug(Debug::configuration,__FUNCTION__) << "SIZE OF USER CONFIGURATION PARAMETERS:  " << second_it->second.size() << endl;

								while (secondHead.hasMore()){
									//string optionName;
									//optionName =*secondHead ;//= nome do parâmetro
									Debug::debug(Debug::configuration,__FUNCTION__) << "PARAMETERS   "  << endl;
									const Token * valueX;
									secondHead >> valueX;
									string paramName = valueX->getName();
									//valueX->view() >> tmpstr;
									CEngineSysVar * customervar=(CEngineSysVar *)SGF::globalSysVarSystem.Find(paramName.c_str());
									// set new value
									if (customervar !=NULL) {
										string valuestr;
											valueX->view() >>valuestr;
											customervar->setString(valuestr.c_str());
											//if there is a callback, run it
											if(customervar->isThereCallBackToObject()) {
											Debug::debug(Debug::configuration,__FUNCTION__) << "WILL RUN THE CALLBACK   "  << endl;
											customervar->runObjCallback(valuestr.c_str());
											Debug::debug(Debug::configuration,__FUNCTION__) << "Value= " << valuestr << endl;

											}
											if(customervar->isThereCallBack()) {
											//não é necessário visto que o parâmetro já é o valor da Sysvar
											customervar->setHandleParam((void *)&valuestr);

											Debug::debug(Debug::configuration,__FUNCTION__) << "WILL RUN THE CALLBACK   "  << endl;
											customervar->runCallback();
											Debug::debug(Debug::configuration,__FUNCTION__) << "Value= " << valuestr << endl;

											}
									}
#if 0
									// valueX->print(" ");
									for (CConfiguration::confParameter::iterator third_it =  second_it->second.begin(); \
									third_it != second_it->second.end();third_it++) {
									Debug::debug(Debug::configuration,__FUNCTION__) << " Parameter: " << (third_it->first) << endl;
										if (*valueX == third_it->first) {
											string tmpstr;
											valueX->view() >> tmpstr;
											runTheCallback(third_it->first, tmpstr);
											Debug::debug(Debug::configuration,__FUNCTION__) << "Value= " << tmpstr << endl;

										} // end third if
								} //end third for
#endif
								}  //end third while

								} //end second if
							}  //end second for
						}  //end first while
					}  //end first if
				} //end first for


	Debug::debug( Debug::configuration,__FUNCTION__ ) << "END LOADING CONFIGURATION "  << endl;

}

void CGlobalConfiguration::setSDLInitModules(sdlModules_s &initModules){
	sdlConfig->initModules.AUDIO=initModules.AUDIO;
	sdlConfig->initModules.FRAMERATEMANAGER=initModules.FRAMERATEMANAGER;
	sdlConfig->initModules.JOYSTICK=initModules.JOYSTICK;
	sdlConfig->initModules.FASTEVENTS=initModules.FASTEVENTS;
	sdlConfig->initModules.TIMER=initModules.TIMER;
	sdlConfig->initModules.TTF=initModules.TTF;
	sdlConfig->initModules.VIDEO=initModules.VIDEO;
	sdlConfig->initModules.WINDOW=initModules.WINDOW;
	sdlConfig->initModules.VIDEO=initModules.TEXTSUPPORT;
	sdlConfig->initModules.WINDOW=initModules.NETWORK;
}























// Cria um Mapa Global indexado por número, com ponteiros para instâncias da classe CConfiguration
// indice 0 = configurações do player 1
// indice 1 = configurações do player 2

Util::CReferenceCount<CFontInfo> CConfiguration::menuFont_v2;
int CConfiguration::menuVersion = 2;
Util::CReferenceCount<Token> CConfiguration::data;
#if defined(_MSC_VER)
vector<CConfiguration*> CConfiguration::ConfigList(10,nullptr);
#else
vector<CConfiguration*> CConfiguration::ConfigList(10);
#endif
//static map< int, CConfiguration * > configs;
//! to store de user game configuration file - this is the default
//string CConfiguration::userConfigFileName = "sge_user_configuration.xml";
map<string, string> CConfiguration::properties;

//map<string, CCallbackBase *> CConfiguration::p_Callback;

/* don't save the configuration while loading it */
class CDisable{
public:
    CDisable(){
        last = CConfiguration::getSave();
        CConfiguration::disableSave();
    }

    ~CDisable(){
        CConfiguration::setSave(last);
    }

    bool last;
};

/* FIXME: move this to some utils module */
static vector<string> split(string str, char splitter){
    vector<string> strings;
    size_t next = str.find(splitter);
    while (next != string::npos){
        strings.push_back(str.substr(0, next));
        str = str.substr(next+1);
        next = str.find(splitter);
    }
    if (str != ""){
        strings.push_back(str);
    }

    return strings;
}

static string last(const vector<string> & what){
    return what.at(what.size() - 1);
}

/* Create a token that contains the entire path.
 * path = "foo/bar/baz"
 * out = (foo (bar (baz)))
 */
static Token * createToken(const string & path){
    vector<string> paths = split(path, '/');
    Token * out = new Token();
    Token * current = out;
    for (vector<string>::iterator it = paths.begin(); it != paths.end(); it++){
        current->addToken(new Token(*it, false));
        if (paths.end() - it > 1){
            Token * next = new Token();
            current->addToken(next);
            current = next;
        }
    }
    return out;
}

/* Create a token with the given path and give it a value */
template <class Value>
static Token * createToken(const string & path, const Value & value){
    Token * out = createToken(path);
    *out << value;
    return out;
}

template <class Value, class Value2>
static Token * createToken(const string & path, const Value & value, const Value2 & value2){
    Token * out = createToken(path);
    *out << value;
    *out << value2;
    return out;
}

static void updateToken(Util::CReferenceCount<Token> data, const string & path, Token * add){
    if (data == NULL){
        delete add;
    }

    Token * found = data->findToken(path);
    /* See if the token already exists. If it does then remove it from its
     * parent and add a new token to the parent with the updated value.
     */
    if (found != NULL){
        Token * parent = found->getParent();
        parent->removeToken(found);
        parent->addToken(add);
    } else {
        const vector<string> paths = split(path, '/');
        Util::CReferenceCount<Token> start = data;
        for (int index = 1; index < paths.size() - 1; index++){
            string where = paths[index];
            Token * next = start->findToken(string("_/") + where);
            if (next == NULL){
                ostringstream out;
                bool first = true;
                for (int from = index; from < paths.size(); from++){
                    if (!first){
                        out << "/";
                    }
                    out << paths[from];
                    first = false;
                }

                /* If we run out of found paths then create a token with an empty
                 * value for the unfound paths we have so far and call updateToken
                 * again. This time the entire path will be there
                 * so the 'found = ...' logic will work.
                 */
                start->addToken(createToken(out.str(), string("")));
                updateToken(data, path, add);
                return;
            } else {
                start = next;
            }
        }

        /* It probably shouldn't be possible to get here. If the entire
         * path was there then the findToken() logic above should have worked.
         */
        start->addToken(add);
    }
}

template <class Value>
static void updateToken( Util::CReferenceCount<Token> data, const string & path, const Value & value){
    if (data == NULL){
        return;
    }

    updateToken(data, path, createToken(last(split(path, '/')), value));
}
/*
string CConfiguration::gameTitleScreen.getString(){
	return "D:\\projetos\\VC10\\GameEngine\\SGFMenu\\Debug\\bin\\Open\\menu\\background.png";
}
*/


void CConfiguration::setPropertySalva(string name, string value){
    properties[name] = value;
}

void CConfiguration::setStringProperty(const string & path, const string & value){
    setPropertySalva(path, value);
}

string CConfiguration::getStringProperty(const string & path, const string & defaultValue){
    if (properties.find(path) == properties.end()){
        properties[path] = defaultValue;
    }
    return properties[path];
}


void CConfiguration::setProperty(const string & name, const string & value){
    updateToken(data.raw(), string(config_configuration) + "/" + name, value);
    sm_saveConfiguration();
}


void CConfiguration::disableSave(){
    save = false;
}

void CConfiguration::setSave(bool what){
    save = what;
}

bool CConfiguration::getSave(){
    return save;
}

	    //static const int CKeyboard::Invalid = 0;
static const CConfiguration::JoystickInput InvalidJoystick = CJoystick::Invalid;

// Objetivo: define as teclas default para esta instância de CConfiguration 
// retorna: o objeto 
CConfiguration CConfiguration::defaultPlayerKeys(){
	 CDisable disable;
	 ButtonRight.setInteger(CKeyboard::Key_RIGHT);
	 ButtonLeft.setInteger(CKeyboard::Key_LEFT);
	 ButtonUp.setInteger(CKeyboard::Key_UP);
	 ButtonDown.setInteger(CKeyboard::Key_DOWN);
	 Button1.setInteger(CKeyboard::Key_Q);
	 Button2.setInteger(CKeyboard::Key_W);
	 Button3.setInteger(CKeyboard::Key_E);
	 Button4.setInteger(CKeyboard::Key_R);
	 Button5.setInteger(CKeyboard::Key_T);
	 Button6.setInteger(CKeyboard::Key_A);
	 Button7.setInteger(CKeyboard::Key_S);
	 Button8.setInteger(CKeyboard::Key_D);
	 Button9.setInteger(CKeyboard::Key_F);
	 ButtonJump.setInteger(CKeyboard::Key_Y);
	 ButtonGrab.setInteger(CKeyboard::Key_SPACE);
	 ButtonStart.setInteger(CKeyboard::Key_ENTER);
	 ButtonSelect.setInteger(CKeyboard::Key_ENTER);
	 ButtonDeal.setInteger(CKeyboard::Key_Z);
	 ButtonBet.setInteger(CKeyboard::Key_X);
	 ButtonDoubleUP.setInteger(CKeyboard::Key_C);
	 ButtonStand.setInteger(CKeyboard::Key_V);
	 ButtonOpen.setInteger(CKeyboard::Key_B);
	 ButtonConfig.setInteger(CKeyboard::Key_F1);
	 ButtonPause.setInteger(CKeyboard::Key_PAUSE);
	 ButtonReset.setInteger(CKeyboard::Key_TAB);
	 ButtonShowGFX.setInteger(CKeyboard::Key_F2);
	 ButtonShowFPS.setInteger(CKeyboard::Key_F3);
	 ButtonSaveConfig.setInteger(CKeyboard::Key_F4);
	 ButtonLoadConfig.setInteger(CKeyboard::Key_F5);
	 ButtonDebugger.setInteger(CKeyboard::Key_F6);
	 ButtonToggleConsole.setInteger(CKeyboard::Key_F7);
	 ButtonReload.setInteger(CKeyboard::Key_F8);
	 ButtonCancel.setInteger(CKeyboard::Key_ESC);
	 ButtonQuit.setInteger(CKeyboard::Key_ESC);
	//setButtonSelect( CKeyboard::Key_ENTER );
	//setButtonQuit( CKeyboard::Key_ESC );
    /* these mappings should agree with input-manager.cpp:convertJoystickKey,
     * but otherwise they are completely arbitrary
     */
	/*
Mapeamento de joystick PS2 para SGF::CJoystick

Botao 1 = Triangulo
Botao 2 = Circulo
Botao 3 = cruz
Botao 4 = quadrado
Botao 5 = L1
Botao 6 = R1
Botao 7 = L2
Botao 8 = R2
Botao 9 = Select
Botao 10 = Start
Botao 11 = L3
Botao 12 = R3


*/

	 JoyButtonRight.setInteger(CJoystick::Right);
	 JoyButtonLeft.setInteger(CJoystick::Left);
	 JoyButtonUp.setInteger(CJoystick::Up);
	 JoyButtonDown.setInteger(CJoystick::Down);
	 JoyButton1.setInteger(CJoystick::Button1);
	 JoyButton2.setInteger(CJoystick::Button2);
	 JoyButton3.setInteger(CJoystick::Button3);
	 JoyButton4.setInteger(CJoystick::Button4);
	 JoyButton5.setInteger(CJoystick::Button5);  //R1
	 JoyButton6.setInteger(CJoystick::Button6);  //L1
	 JoyButtonCancel.setInteger(CJoystick::Button7);  //R2
	 JoyButtonQuit.setInteger(CJoystick::Button8); //L2
	 JoyButton7.setInteger(CJoystick::Button11);  //L3
	 JoyButtonJump.setInteger(CJoystick::Button12); //R3
	 JoyButtonStart.setInteger(CJoystick::Button10);
	 JoyButtonSelect.setInteger(CJoystick::Button9);
	 return *this;
}


// Objetivo: Cria uma instância da Classe CConfiguration e define as teclas default para o Player1
// retorna: o objeto criado
CConfiguration CConfiguration::defaultPlayer1Keys(){
	 CDisable disable;
	 
	 if (ConfigList[ Player1 ]==NULL) new CConfiguration(Player1);

	 ConfigList[ Player1 ]->ButtonRight.setInteger(CKeyboard::Key_RIGHT);
	 ConfigList[ Player1 ]->ButtonLeft.setInteger(CKeyboard::Key_LEFT);
	 ConfigList[ Player1 ]->ButtonUp.setInteger(CKeyboard::Key_UP);
	 ConfigList[ Player1 ]->ButtonDown.setInteger(CKeyboard::Key_DOWN);
	 ConfigList[ Player1 ]->Button1.setInteger(CKeyboard::Key_Q);
	 ConfigList[ Player1 ]->Button2.setInteger(CKeyboard::Key_W);
	 ConfigList[ Player1 ]->Button3.setInteger(CKeyboard::Key_E);
	 ConfigList[ Player1 ]->Button4.setInteger(CKeyboard::Key_R);
	 ConfigList[ Player1 ]->Button5.setInteger(CKeyboard::Key_T);
	 ConfigList[ Player1 ]->Button6.setInteger(CKeyboard::Key_A);
	 ConfigList[ Player1 ]->Button7.setInteger(CKeyboard::Key_S);
	 ConfigList[ Player1 ]->Button8.setInteger(CKeyboard::Key_D);
	 ConfigList[ Player1 ]->Button9.setInteger(CKeyboard::Key_F);
	 ConfigList[ Player1 ]->ButtonJump.setInteger(CKeyboard::Key_Y);
	 ConfigList[ Player1 ]->ButtonGrab.setInteger(CKeyboard::Key_SPACE);
	 ConfigList[ Player1 ]->ButtonStart.setInteger(CKeyboard::Key_ENTER);
	 ConfigList[ Player1 ]->ButtonSelect.setInteger(CKeyboard::Key_ENTER);
	 ConfigList[ Player1 ]->ButtonDeal.setInteger(CKeyboard::Key_Z);
	 ConfigList[ Player1 ]->ButtonBet.setInteger(CKeyboard::Key_X);
	 ConfigList[ Player1 ]->ButtonDoubleUP.setInteger(CKeyboard::Key_C);
	 ConfigList[ Player1 ]->ButtonStand.setInteger(CKeyboard::Key_V);
	 ConfigList[ Player1 ]->ButtonOpen.setInteger(CKeyboard::Key_B);
	 ConfigList[ Player1 ]->ButtonConfig.setInteger(CKeyboard::Key_F1);
	 ConfigList[ Player1 ]->ButtonPause.setInteger(CKeyboard::Key_PAUSE);
	 ConfigList[ Player1 ]->ButtonReset.setInteger(CKeyboard::Key_TAB);
	 ConfigList[ Player1 ]->ButtonShowGFX.setInteger(CKeyboard::Key_F2);
	 ConfigList[ Player1 ]->ButtonShowFPS.setInteger(CKeyboard::Key_F3);
	 ConfigList[ Player1 ]->ButtonSaveConfig.setInteger(CKeyboard::Key_F4);
	 ConfigList[ Player1 ]->ButtonLoadConfig.setInteger(CKeyboard::Key_F5);
	 ConfigList[ Player1 ]->ButtonDebugger.setInteger(CKeyboard::Key_F6);
	 ConfigList[ Player1 ]->ButtonToggleConsole.setInteger(CKeyboard::Key_F7);
	 ConfigList[ Player1 ]->ButtonReload.setInteger(CKeyboard::Key_F8);
	 ConfigList[ Player1 ]->ButtonCancel.setInteger(CKeyboard::Key_ESC);
	 ConfigList[ Player1 ]->ButtonQuit.setInteger(CKeyboard::Key_ESC);
	//ConfigList[ Player1 ]->setButtonSelect( CKeyboard::Key_ENTER );
	//ConfigList[ Player1 ]->setButtonQuit( CKeyboard::Key_ESC );
    /* these mappings should agree with input-manager.cpp:convertJoystickKey,
     * but otherwise they are completely arbitrary
     */
	/*
Mapeamento de joystick PS2 para SGF::CJoystick

Botao 1 = Triangulo
Botao 2 = Circulo
Botao 3 = cruz
Botao 4 = quadrado
Botao 5 = L1
Botao 6 = R1
Botao 7 = L2
Botao 8 = R2
Botao 9 = Select
Botao 10 = Start
Botao 11 = L3
Botao 12 = R3


*/

	 ConfigList[ Player1 ]->JoyButtonRight.setInteger(CJoystick::Right);
	 ConfigList[ Player1 ]->JoyButtonLeft.setInteger(CJoystick::Left);
	 ConfigList[ Player1 ]->JoyButtonUp.setInteger(CJoystick::Up);
	 ConfigList[ Player1 ]->JoyButtonDown.setInteger(CJoystick::Down);
	 ConfigList[ Player1 ]->JoyButton1.setInteger(CJoystick::Button1);
	 ConfigList[ Player1 ]->JoyButton2.setInteger(CJoystick::Button2);
	 ConfigList[ Player1 ]->JoyButton3.setInteger(CJoystick::Button3);
	 ConfigList[ Player1 ]->JoyButton4.setInteger(CJoystick::Button4);
	 ConfigList[ Player1 ]->JoyButton5.setInteger(CJoystick::Button5);  //R1
	 ConfigList[ Player1 ]->JoyButton6.setInteger(CJoystick::Button6);  //L1
	 ConfigList[ Player1 ]->JoyButtonCancel.setInteger(CJoystick::Button7);  //R2
	 ConfigList[ Player1 ]->JoyButtonQuit.setInteger(CJoystick::Button8); //L2
	 ConfigList[ Player1 ]->JoyButton7.setInteger(CJoystick::Button11);  //L3
	 ConfigList[ Player1 ]->JoyButtonJump.setInteger(CJoystick::Button12); //R3
	 ConfigList[ Player1 ]->JoyButtonStart.setInteger(CJoystick::Button10);
	 ConfigList[ Player1 ]->JoyButtonSelect.setInteger(CJoystick::Button9);
	 return *ConfigList[ Player1 ];
}
// Objetivo: Cria uma instância da Classe CConfiguration e define as teclas default para o Player2
// retorna: o objeto criado

CConfiguration CConfiguration::defaultPlayer2Keys(){
	CDisable disable;

	if (ConfigList[ Player2 ]==NULL)  new CConfiguration(1);

	ConfigList[ Player2 ]->ButtonRight.setInteger(CKeyboard::Key_5_PAD);
	ConfigList[ Player2 ]->ButtonLeft.setInteger(CKeyboard::Key_1_PAD);
	ConfigList[ Player2 ]->ButtonUp.setInteger(CKeyboard::Key_5_PAD);
	ConfigList[ Player2 ]->ButtonDown.setInteger(CKeyboard::Key_2_PAD);
	ConfigList[ Player2 ]->Button1.setInteger(CKeyboard::Key_INSERT);
	ConfigList[ Player2 ]->Button2.setInteger(CKeyboard::Key_HOME);
	ConfigList[ Player2 ]->Button3.setInteger(CKeyboard::Key_PGUP);
	ConfigList[ Player2 ]->Button4.setInteger(CKeyboard::Key_DEL);
	ConfigList[ Player2 ]->ButtonJump.setInteger(CKeyboard::Key_END);
	ConfigList[ Player2 ]->ButtonGrab.setInteger(CKeyboard::Key_PGDN);
	ConfigList[ Player2 ]->ButtonStart.setInteger(CKeyboard::Key_ENTER_PAD);
	ConfigList[ Player2 ]->ButtonSelect.setInteger(CKeyboard::Key_ENTER_PAD);
	ConfigList[ Player2 ]->ButtonQuit.setInteger(CKeyboard::Key_ESC);

		/*
Mapeamento de joystick PS2 para SGF::CJoystick

Botao 1 = Triangulo
Botao 2 = Circulo
Botao 3 = cruz
Botao 4 = quadrado
Botao 5 = L1
Botao 6 = R1
Botao 7 = L2
Botao 8 = R2
Botao 9 = Select
Botao 10 = Start
Botao 11 = L3
Botao 12 = R3


*/

	 ConfigList[ Player2 ]->JoyButtonRight.setInteger(CJoystick::Right);
	 ConfigList[ Player2 ]->JoyButtonLeft.setInteger(CJoystick::Left);
	 ConfigList[ Player2 ]->JoyButtonUp.setInteger(CJoystick::Up);
	 ConfigList[ Player2 ]->JoyButtonDown.setInteger(CJoystick::Down);
	 ConfigList[ Player2 ]->JoyButton1.setInteger(CJoystick::Button1);
	 ConfigList[ Player2 ]->JoyButton2.setInteger(CJoystick::Button2);
	 ConfigList[ Player2 ]->JoyButton3.setInteger(CJoystick::Button3);
	 ConfigList[ Player2 ]->JoyButton4.setInteger(CJoystick::Button4);
	 ConfigList[ Player2 ]->JoyButton5.setInteger(CJoystick::Button5);  //R1
	 ConfigList[ Player2 ]->JoyButton6.setInteger(CJoystick::Button6);  //L1
	 ConfigList[ Player2 ]->JoyButtonCancel.setInteger(CJoystick::Button7);  //R2
	 ConfigList[ Player2 ]->JoyButtonQuit.setInteger(CJoystick::Button8); //L2
	 ConfigList[ Player2 ]->JoyButton7.setInteger(CJoystick::Button11);  //L3
	 ConfigList[ Player2 ]->JoyButtonJump.setInteger(CJoystick::Button12); //R3
	 ConfigList[ Player2 ]->JoyButtonStart.setInteger(CJoystick::Button10);
	 ConfigList[ Player2 ]->JoyButtonSelect.setInteger(CJoystick::Button9);

	return *ConfigList[ Player2 ];
}




/**
\brief: Cria um novo objeto do tipo CConfiguration e define as teclas padrão para este objeto, caso seja o player 1 ou 2
// Parâmetro: set=> que define se é o set=0 para o player 1, ou set=1 para o player 2
// Todo: espandir esse método para configurar teclas padrão para outros tipos de objeto, recebendo como parâmetro o tipo do objeto também
**/
CConfiguration * CConfiguration::getConfig( int set ){
	if ( ConfigList[ set ] == NULL ){

		switch( set ){
			case 0 : {
				defaultPlayer1Keys();
				break;
			}
			case 1 : {
				defaultPlayer2Keys();
				break;
			}
		}
	}


	return ConfigList[ set ];
}

/**
\brief Construtor da Classe
\param: index
**/

CConfiguration::CConfiguration(int index):
ButtonRight("key-right","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
ButtonLeft("key-left","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
ButtonUp("key-up","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
ButtonDown("key-down","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
Button1("key-action-1","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
Button2("key-action-2","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
Button3("key-action-3","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
Button4("key-action-4","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
Button5("key-action-5","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
Button6("key-action-6","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
Button7("key-action-7","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
Button8("key-action-8","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
Button9("key-action-9","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
ButtonJump("key-jump","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
ButtonGrab("key-grab","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
ButtonStart("key-start","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
ButtonSelect("key-select","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
ButtonDeal("key-deal","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
ButtonBet("key-bet","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
ButtonDoubleUP("key-double-up","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
ButtonStand("key-stand","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
ButtonOpen("key-open","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
ButtonConfig("key-config","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
ButtonPause("key-pause","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
ButtonReset("key-reset","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
ButtonShowGFX("key-showgfx","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
ButtonShowFPS("key-showfps","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
ButtonSaveConfig("key-saveconfig","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
ButtonLoadConfig("key-loadconfig","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
ButtonDebugger("key-debugger","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
ButtonToggleConsole("key-toggleconsole","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
ButtonReload("key-reload","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
ButtonCancel("key-cancel","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
ButtonQuit("key-quit","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButtonRight("joykey-right","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButtonLeft("joykey-left","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButtonUp("joykey-up","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButtonDown("joykey-down","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButton1("joykey-action-1","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButton2("joykey-action-2","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButton3("joykey-action-3","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButton4("joykey-action-4","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButton5("joykey-action-5","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButton6("joykey-action-6","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButton7("joykey-action-7","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButton8("joykey-action-8","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButton9("joykey-action-9","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButtonJump("joykey-jump","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButtonGrab("joykey-grab","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButtonStart("joykey-start","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButtonSelect("joykey-select","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButtonDeal("joykey-deal","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButtonBet("joykey-bet","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButtonDoubleUP("joykey-double-up","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButtonStand("joykey-stand","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButtonOpen("joykey-open","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButtonConfig("joykey-config","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButtonPause("joykey-pause","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButtonReset("joykey-reset","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButtonShowGFX("joykey-showgfx","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButtonShowFPS("joykey-showfps","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButtonSaveConfig("joykey-saveconfig","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButtonLoadConfig("joykey-loadconfig","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButtonDebugger("joykey-debugger","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButtonToggleConsole("joykey-toggleconsole","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButtonReload("joykey-reload","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButtonCancel("joykey-cancel","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
JoyButtonQuit("joykey-quit","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButtonRight("mousekey-right","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButtonLeft("mousekey-left","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButtonUp("mousekey-up","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButtonDown("mousekey-down","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButton1("mousekey-action-1","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButton2("mousekey-action-2","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButton3("mousekey-action-3","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButton4("mousekey-action-4","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButton5("mousekey-action-5","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButton6("mousekey-action-6","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButton7("mousekey-action-7","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButton8("mousekey-action-8","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButton9("mousekey-action-9","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButtonJump("mousekey-jump","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButtonGrab("mousekey-grab","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButtonStart("mousekey-start","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButtonSelect("mousekey-select","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButtonDeal("mousekey-deal","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButtonBet("mousekey-bet","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButtonDoubleUP("mousekey-double-up","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButtonStand("mousekey-stand","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButtonOpen("mousekey-open","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButtonConfig("mousekey-config","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButtonPause("mousekey-pause","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButtonReset("mousekey-reset","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButtonShowGFX("mousekey-showgfx","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButtonShowFPS("mousekey-showfps","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButtonSaveConfig("mousekey-saveconfig","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButtonLoadConfig("mousekey-loadconfig","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButtonDebugger("mousekey-debugger","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButtonToggleConsole("mousekey-toggleconsole","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButtonReload("mousekey-reload","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButtonCancel("mousekey-cancel","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
MouseButtonQuit("mousekey-quit","-1",SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER,index,""),
m_iIndex(index)
{
	ConfigList[ index ] = this;
	CLocalSysVar::registerLocalStaticVars(index);
	initialized = false;
	modifiedFlags = 0;
	init();
}
// Objetivo: Construtor da Classe
// Parâmetro: outro objeto da classe CConfiguration

CConfiguration::CConfiguration( const CConfiguration & config ):  //passagem por referência
ButtonRight(config.ButtonRight),
ButtonLeft(config.ButtonLeft),
ButtonUp(config.ButtonUp),
ButtonDown(config.ButtonDown),
Button1(config.Button1),
Button2(config.Button2),
Button3(config.Button3),
Button4(config.Button4),
Button5(config.Button5),
Button6(config.Button6),
Button7(config.Button7),
Button8(config.Button8),
Button9(config.Button9),
ButtonJump(config.ButtonJump),
ButtonGrab(config.ButtonGrab),
ButtonStart(config.ButtonStart),
ButtonSelect(config.ButtonSelect),
ButtonDeal(config.ButtonDeal),
ButtonBet(config.ButtonBet),
ButtonDoubleUP(config.ButtonDoubleUP),
ButtonStand(config.ButtonStand),
ButtonOpen(config.ButtonOpen),
ButtonConfig(config.ButtonConfig),
ButtonPause(config.ButtonPause),
ButtonReset(config.ButtonReset),
ButtonShowGFX(config.ButtonShowGFX),
ButtonShowFPS(config.ButtonShowFPS),
ButtonSaveConfig(config.ButtonSaveConfig),
ButtonLoadConfig(config.ButtonLoadConfig),
ButtonDebugger(config.ButtonDebugger),
ButtonToggleConsole(config.ButtonToggleConsole),
ButtonReload(config.ButtonReload),
ButtonCancel(config.ButtonCancel),
ButtonQuit(config.ButtonQuit),
JoyButtonRight(config.JoyButtonRight),
JoyButtonLeft(config.JoyButtonLeft),
JoyButtonUp(config.JoyButtonUp),
JoyButtonDown(config.JoyButtonDown),
JoyButton1(config.JoyButton1),
JoyButton2(config.JoyButton2),
JoyButton3(config.JoyButton3),
JoyButton4(config.JoyButton4),
JoyButton5(config.JoyButton5),
JoyButton6(config.JoyButton6),
JoyButton7(config.JoyButton7),
JoyButton8(config.JoyButton8),
JoyButton9(config.JoyButton9),
JoyButtonJump(config.JoyButtonJump),
JoyButtonGrab(config.JoyButtonGrab),
JoyButtonStart(config.JoyButtonStart),
JoyButtonSelect(config.JoyButtonSelect),
JoyButtonDeal(config.JoyButtonDeal),
JoyButtonBet(config.JoyButtonBet),
JoyButtonDoubleUP(config.JoyButtonDoubleUP),
JoyButtonStand(config.JoyButtonStand),
JoyButtonOpen(config.JoyButtonOpen),
JoyButtonConfig(config.JoyButtonConfig),
JoyButtonPause(config.JoyButtonPause),
JoyButtonReset(config.JoyButtonReset),
JoyButtonShowGFX(config.JoyButtonShowGFX),
JoyButtonShowFPS(config.JoyButtonShowFPS),
JoyButtonSaveConfig(config.JoyButtonSaveConfig),
JoyButtonLoadConfig(config.JoyButtonLoadConfig),
JoyButtonDebugger(config.JoyButtonDebugger),
JoyButtonToggleConsole(config.JoyButtonToggleConsole),
JoyButtonReload(config.JoyButtonReload),
JoyButtonCancel(config.JoyButtonCancel),
JoyButtonQuit(config.JoyButtonQuit),
MouseButtonRight(config.MouseButtonRight),
MouseButtonLeft(config.MouseButtonLeft),
MouseButtonUp(config.MouseButtonUp),
MouseButtonDown(config.MouseButtonDown),
MouseButton1(config.MouseButton1),
MouseButton2(config.MouseButton2),
MouseButton3(config.MouseButton3),
MouseButton4(config.MouseButton4),
MouseButton5(config.MouseButton5),
MouseButton6(config.MouseButton6),
MouseButton7(config.MouseButton7),
MouseButton8(config.MouseButton8),
MouseButton9(config.MouseButton9),
MouseButtonJump(config.MouseButtonJump),
MouseButtonGrab(config.MouseButtonGrab),
MouseButtonStart(config.MouseButtonStart),
MouseButtonSelect(config.MouseButtonSelect),
MouseButtonDeal(config.MouseButtonDeal),
MouseButtonBet(config.MouseButtonBet),
MouseButtonDoubleUP(config.MouseButtonDoubleUP),
MouseButtonStand(config.MouseButtonStand),
MouseButtonOpen(config.MouseButtonOpen),
MouseButtonConfig(config.MouseButtonConfig),
MouseButtonPause(config.MouseButtonPause),
MouseButtonReset(config.MouseButtonReset),
MouseButtonShowGFX(config.MouseButtonShowGFX),
MouseButtonShowFPS(config.MouseButtonShowFPS),
MouseButtonSaveConfig(config.MouseButtonSaveConfig),
MouseButtonLoadConfig(config.MouseButtonLoadConfig),
MouseButtonDebugger(config.MouseButtonDebugger),
MouseButtonToggleConsole(config.MouseButtonToggleConsole),
MouseButtonReload(config.MouseButtonReload),
MouseButtonCancel(config.MouseButtonCancel),
MouseButtonQuit(config.MouseButtonQuit)
{
	init();
    menuFont_v2 = config.menuFont_v2;
}


// Objetido: redefinir o operador = para a classe CConfioguration
CConfiguration & CConfiguration::operator=( const CConfiguration & config ){
	CDisable disable;

	ButtonRight= config.ButtonRight;
	ButtonLeft= config.ButtonLeft;
	ButtonUp= config.ButtonUp;
	ButtonDown= config.ButtonDown;
	Button1= config.Button1;
	Button2= config.Button2;
	Button3= config.Button3;
	Button4= config.Button4;
	Button5= config.Button5;
	Button6= config.Button6;
	Button7= config.Button7;
	Button8= config.Button8;
	Button9= config.Button9;
	ButtonJump= config.ButtonJump;
	ButtonGrab= config.ButtonGrab;
	ButtonStart= config.ButtonStart;
	ButtonSelect= config.ButtonSelect;
	ButtonDeal= config.ButtonDeal;
	ButtonBet= config.ButtonBet;
	ButtonDoubleUP= config.ButtonDoubleUP;
	ButtonStand= config.ButtonStand;
	ButtonOpen= config.ButtonConfig;
	ButtonConfig= config.ButtonConfig;
	ButtonPause= config.ButtonPause;
	ButtonReset= config.ButtonReset;
	ButtonShowGFX= config.ButtonShowGFX;
	ButtonShowFPS= config.ButtonShowFPS;
	ButtonSaveConfig= config.ButtonSaveConfig;
	ButtonLoadConfig= config.ButtonLoadConfig;
	ButtonDebugger= config.ButtonDebugger;
	ButtonToggleConsole= config.ButtonToggleConsole;
	ButtonReload= config.ButtonReload;
	ButtonCancel= config.ButtonCancel;
	ButtonQuit= config.ButtonQuit;

    JoyButtonRight= config.JoyButtonRight;
	JoyButtonLeft= config.JoyButtonLeft;
	JoyButtonUp= config.JoyButtonUp;
	JoyButtonDown= config.JoyButtonDown;
	JoyButton1= config.JoyButton1;
	JoyButton2= config.JoyButton2;
	JoyButton3= config.JoyButton3;
	JoyButton4= config.JoyButton4;
	JoyButton5= config.JoyButton5;
	JoyButton6= config.JoyButton6;
	JoyButton7= config.JoyButton7;
	JoyButton8=config.JoyButton8;
JoyButton9 = config.JoyButton9;
JoyButtonJump = config.JoyButtonJump;
JoyButtonGrab = config.JoyButtonGrab;
JoyButtonStart = config.JoyButtonStart;
JoyButtonSelect = config.JoyButtonSelect;
JoyButtonDeal = config.JoyButtonDeal;
JoyButtonBet = config.JoyButtonBet;
JoyButtonDoubleUP = config.JoyButtonDoubleUP;
JoyButtonStand = config.JoyButtonStand;
JoyButtonOpen = config.JoyButtonOpen;
JoyButtonConfig = config.JoyButtonConfig;
JoyButtonPause = config.JoyButtonPause;
JoyButtonReset = config.JoyButtonReset;
JoyButtonShowGFX = config.JoyButtonShowGFX;
JoyButtonShowFPS = config.JoyButtonShowFPS;
JoyButtonSaveConfig = config.JoyButtonSaveConfig;
JoyButtonLoadConfig = config.JoyButtonLoadConfig;
JoyButtonDebugger = config.JoyButtonDebugger;
JoyButtonToggleConsole = config.JoyButtonToggleConsole;
JoyButtonReload = config.JoyButtonReload;
JoyButtonCancel = config.JoyButtonCancel;
JoyButtonQuit = config.JoyButtonQuit;
MouseButtonRight = config.MouseButtonRight;
MouseButtonLeft = config.MouseButtonLeft;
MouseButtonUp = config.MouseButtonUp;
MouseButtonDown = config.MouseButtonDown;
MouseButton1 = config.MouseButton1;
MouseButton2 = config.MouseButton2;
MouseButton3 = config.MouseButton3;
MouseButton4 = config.MouseButton4;
MouseButton5 = config.MouseButton5;
MouseButton6 = config.MouseButton6;
MouseButton7 = config.MouseButton7;
MouseButton8 = config.MouseButton8;
MouseButton9 = config.MouseButton9;
MouseButtonJump = config.MouseButtonJump;
MouseButtonGrab = config.MouseButtonGrab;
MouseButtonStart = config.MouseButtonStart;
MouseButtonSelect = config.MouseButtonSelect;
MouseButtonDeal = config.MouseButtonDeal;
MouseButtonBet = config.MouseButtonBet;
MouseButtonDoubleUP = config.MouseButtonDoubleUP;
MouseButtonStand = config.MouseButtonStand;
MouseButtonOpen = config.MouseButtonOpen;
MouseButtonConfig = config.MouseButtonConfig;
MouseButtonPause = config.MouseButtonPause;
MouseButtonReset = config.MouseButtonReset;
MouseButtonShowGFX = config.MouseButtonShowGFX;
MouseButtonShowFPS = config.MouseButtonShowFPS;
MouseButtonSaveConfig = config.MouseButtonSaveConfig;
MouseButtonLoadConfig = config.MouseButtonLoadConfig;
MouseButtonDebugger = config.MouseButtonDebugger;
MouseButtonToggleConsole = config.MouseButtonToggleConsole;
MouseButtonReload = config.MouseButtonReload;
MouseButtonCancel = config.MouseButtonCancel;
MouseButtonQuit = config.MouseButtonQuit;

	setMenuFont_v2(config.getMenuFont_v2());
	init();
	return *this;
}

CConfiguration::~CConfiguration(){
	shutdown();
}

int CConfiguration::getJoystickKey(CInput::GameKeys which, int facing, int vFacing) const {
    switch( which ){
        case CInput::Forward : {
                                  if ( facing == CObject::FACING_LEFT )
									  return this->JoyButtonLeft.getInteger();
                                  else 	return this->JoyButtonRight.getInteger();
                              }
        case CInput::Back : {
                               if ( facing == CObject::FACING_LEFT )
                                   return this->JoyButtonRight.getInteger();
                               else	return this->JoyButtonLeft.getInteger();
                           }
        case CInput::Up : {
			if ( facing == CObject::FACING_UP )
                return this->JoyButtonUp.getInteger();
            else 	return this->JoyButtonDown.getInteger();
		}
        case CInput::Down : {
			if ( facing == CObject::FACING_UP )
                return this->JoyButtonDown.getInteger();
            else 	return this->JoyButtonUp.getInteger();
		}
        case CInput::Button1 : return this->JoyButton1.getInteger();
        case CInput::Button2 : return this->JoyButton2.getInteger();
        case CInput::Button3 : return this->JoyButton3.getInteger();
        case CInput::Button4 : return this->JoyButton4.getInteger();
		case CInput::Button5 : return this->JoyButton5.getInteger();
		case CInput::Button6 : return this->JoyButton6.getInteger();
		case CInput::Button7 : return this->JoyButton7.getInteger();
		case CInput::Button8 : return this->JoyButton8.getInteger();
        case CInput::Button9 : return this->JoyButton9.getInteger();
		case CInput::Jump : return this->JoyButtonJump.getInteger();
        case CInput::Grab :  return this->JoyButtonGrab.getInteger();
		case CInput::Start : return this->JoyButtonStart.getInteger();
		case CInput::Select : return this->JoyButtonSelect.getInteger();
		case CInput::Deal :return this->JoyButtonDeal.getInteger();
		case CInput::Bet :return this->JoyButtonBet.getInteger();
		case CInput::DoubleUP :return this->JoyButtonDoubleUP.getInteger();
		case CInput::Stand :return this->JoyButtonStand.getInteger();
		case CInput::Open :return this->JoyButtonOpen.getInteger();
		case CInput::Cancel : return this->JoyButtonCancel.getInteger();
		case CInput::Config :return this->JoyButtonConfig.getInteger();
		case CInput::Pause :return this->JoyButtonPause.getInteger();
		case CInput::Reset :return this->JoyButtonReset.getInteger();
		case CInput::ShowGFX :return this->JoyButtonShowGFX.getInteger();
		case CInput::ShowFPS :return this->JoyButtonShowFPS.getInteger();
		case CInput::SaveConfig :return this->JoyButtonConfig.getInteger();
		case CInput::LoadConfig :return this->JoyButtonLoadConfig.getInteger();
		case CInput::Debugger :return this->JoyButtonSaveConfig.getInteger();
		case CInput::ToggleConsole :return this->JoyButtonToggleConsole.getInteger();
		case CInput::Reload :return this->JoyButtonReload.getInteger();

		default : return CJoystick::Invalid;
    }
   return CJoystick::Invalid; // só para evitar warning do compilador
}

int CConfiguration::getKey( CInput::GameKeys which, int facing, int vFacing ) const {
	switch( which ){
        case CInput::Forward : {
			if ( facing == CObject::FACING_LEFT )
				return this->ButtonLeft.getInteger();
            else 	return this->ButtonRight.getInteger();
		}
        case CInput::Back : {
			if ( facing == CObject::FACING_LEFT )
				return this->ButtonRight.getInteger();
			else	return this->ButtonLeft.getInteger();
		}
        case CInput::Up : {
			if ( facing == CObject::FACING_UP )
                return this->ButtonUp.getInteger();
            else 	return this->ButtonDown.getInteger();
		}
		case CInput::Down : {
			if ( facing == CObject::FACING_UP )
                return this->ButtonDown.getInteger();
            else 	return this->ButtonUp.getInteger();
		}
		case CInput::Button1 : return this->Button1.getInteger();
		case CInput::Button2 : return this->Button2.getInteger();
		case CInput::Button3 : return this->Button3.getInteger();
		case CInput::Button4 : return this->Button4.getInteger();  //jump
		case CInput::Button5 : return this->Button5.getInteger();
		case CInput::Button6 : return this->Button6.getInteger();
		case CInput::Button7 : return this->Button7.getInteger();
		case CInput::Button8 : return this->Button8.getInteger();  //jump
        case CInput::Button9 : return this->Button9.getInteger();  //jump
		case CInput::Grab : return this->ButtonGrab.getInteger();
		case CInput::Start : return this->ButtonStart.getInteger();
		case CInput::Select : return this->ButtonSelect.getInteger();
		case CInput::Deal : return this->ButtonDeal.getInteger();
		case CInput::Bet : return this->ButtonBet.getInteger();
		case CInput::DoubleUP : return this->ButtonDoubleUP.getInteger();
		case CInput::Stand : return this->ButtonStand.getInteger();
		case CInput::Open : return this->ButtonOpen.getInteger();
		case CInput::Cancel : return this->ButtonCancel.getInteger();
		case CInput::Config : return this->ButtonConfig.getInteger();
		case CInput::Pause : return this->ButtonPause.getInteger();
		case CInput::Reset : return this->ButtonReset.getInteger();
		case CInput::ShowGFX : return this->ButtonShowGFX.getInteger();
		case CInput::ShowFPS : return this->ButtonShowFPS.getInteger();
		case CInput::SaveConfig : return this->ButtonSaveConfig.getInteger();
		case CInput::LoadConfig : return this->ButtonLoadConfig.getInteger();
		case CInput::Debugger : return this->ButtonDebugger.getInteger();
		case CInput::ToggleConsole : return this->ButtonToggleConsole.getInteger();
		case CInput::Reload : return this->ButtonReload.getInteger();
		case CInput::Quit : return this->ButtonQuit.getInteger();
		default : return CKeyboard::Invalid;
	}
}
CConfiguration::KeyboardInput  CConfiguration::getKey(int config, const char *nameofKey){
	if ( ConfigList[config]!=NULL) return ConfigList[config]->getKey(nameofKey);
	else return CKeyboard::Invalid;
}
CConfiguration::KeyboardInput CConfiguration::getKey(const char *nameofKey){
	int key=getCVarLocalInteger(nameofKey);
	if (key>0) return intToKeyboard(key);
	else return CKeyboard::Invalid;
}
void CConfiguration::setKey(int config, const char *nameofKey, int value){
	if(ConfigList[config] !=NULL) ConfigList[config]->setCVarLocalInteger(nameofKey,value,SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER);
}
void CConfiguration::setKey(const char *nameofKey,KeyboardInput key){
	setCVarLocalInteger(nameofKey,key,SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER);
}
void CConfiguration::setKey(const char *nameofKey,JoystickInput key){
	setCVarLocalInteger(nameofKey,key,SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER);
}
void CConfiguration::setKey(const char *nameofKey,MouseInput key){
	setCVarLocalInteger(nameofKey,key,SYSVAR_ENGINE|SYSVAR_LOCAL |SYSVAR_INTEGER);
}
CConfiguration::JoystickInput  CConfiguration::getJoyKey(int config, const char *nameofKey){
	if ( ConfigList[config]!=NULL) return intToJoystick(ConfigList[config]->getKey(nameofKey));
	else return CJoystick::Invalid;
}
CConfiguration::JoystickInput CConfiguration::getJoyKey(const char *nameofKey){
	int key=getCVarLocalInteger(nameofKey);
	if (key>0) return intToJoystick(key);
	else return CJoystick::Invalid;
}
CConfiguration::MouseInput  CConfiguration::getMouseKey(int config, const char *nameofKey){
	if ( ConfigList[config]!=NULL) return intToMouse(ConfigList[config]->getKey(nameofKey));
	else return CMouse::Invalid;
}
CConfiguration::MouseInput  CConfiguration::getMouseKey(const char *nameofKey){
	int key=getCVarLocalInteger(nameofKey);
	if (key>0) return intToMouse(key);
	else return CMouse::Invalid;
}
int CConfiguration::getMouseKey( CInput::GameKeys which, int facing , int vFacing) const {
	switch( which ){
        case CInput::Forward : {
			if ( facing == CObject::FACING_LEFT )
                return this->MouseButtonLeft.getInteger();
            else 	return this->MouseButtonRight.getInteger();
		}
        case CInput::Back : {
			if ( facing == CObject::FACING_LEFT )
				return this->MouseButtonRight.getInteger();
			else	return this->MouseButtonLeft.getInteger();
		}
        case CInput::Up : return this->MouseButtonUp.getInteger();
		case CInput::Down : return this->MouseButtonDown.getInteger();
		case CInput::Button1 : return this->MouseButton1.getInteger();
		case CInput::Button2 : return this->MouseButton2.getInteger();
		case CInput::Button3 : return this->MouseButton3.getInteger();
		case CInput::Button4 : return this->MouseButton4.getInteger();
		case CInput::Button5 : return this->MouseButton5.getInteger();
		case CInput::Button6 : return this->MouseButton6.getInteger();
		case CInput::Button7 : return this->MouseButton7.getInteger();
		case CInput::Button8 : return this->MouseButton8.getInteger();  //jump
        case CInput::Button9 : return this->MouseButton9.getInteger();  //jump
		case CInput::Grab : return this->MouseButtonGrab.getInteger();
		case CInput::Start : return this->MouseButtonStart.getInteger();
		case CInput::Select : return this->MouseButtonSelect.getInteger();
		case CInput::Deal : return this->MouseButtonDeal.getInteger();
		case CInput::Bet : return this->MouseButtonBet.getInteger();
		case CInput::DoubleUP : return this->MouseButtonDoubleUP.getInteger();
		case CInput::Stand : return this->MouseButtonStand.getInteger();
		case CInput::Open : return this->MouseButtonOpen.getInteger();
		case CInput::Cancel : return this->MouseButtonCancel.getInteger();
		case CInput::Config : return this->MouseButtonConfig.getInteger();
		case CInput::Pause : return this->MouseButtonPause.getInteger();
		case CInput::Reset : return this->MouseButtonReset.getInteger();
		case CInput::ShowGFX : return this->MouseButtonShowGFX.getInteger();
		case CInput::ShowFPS : return this->MouseButtonShowFPS.getInteger();
		case CInput::SaveConfig : return this->MouseButtonSaveConfig.getInteger();
		case CInput::LoadConfig : return this->MouseButtonLoadConfig.getInteger();
		case CInput::Debugger : return this->MouseButtonDebugger.getInteger();
		case CInput::ToggleConsole : return this->MouseButtonToggleConsole.getInteger();
		case CInput::Reload : return this->MouseButtonReload.getInteger();
		default : return CMouse::Invalid;
	}
	return CMouse::Invalid; // só para evitar warning do compilador
}

bool CConfiguration::hasMenuFont(){
    return menuFont_v2 != NULL;
}

Util::CReferenceCount<CFontInfo> CConfiguration::getMenuFont_v2(){
    return menuFont_v2;
}

void CConfiguration::setMenuFont_v2(const Util::CReferenceCount<CFontInfo> & info){
    Debug::debug(Debug::menu,__FUNCTION__) << "Setting Menu Font V2: "<< &info <<endl;
    menuFont_v2 = info;
    //saveConfiguration();
}

SDLState_t * CGlobalConfiguration::getsdlConfig(){
	return sdlConfig;
}


void CConfiguration::setKeyToken(int config, const string & name, int value){
    if (value != InvalidKey){
        ostringstream path;
        path << config_configuration << "/" << config_input << "/" << config << "/keys/" << name;
        updateToken(data, path.str(), value);
        sm_saveConfiguration();
    }
}

int CConfiguration::getKeyToken(int config, const string & name, int defaultValue){
    ostringstream path;
    path << config_input << "/" << config << "/keys/" << name;
    return getProperty(path.str(), defaultValue);
}




/*

string CConfiguration::gameModDir.getString(){
    return currentGameDir;
}


*/
/* assumes the directory is readable and has a dir/dir.txt in it */
/*
void CConfiguration::gameModDir.setString(const string & str){
    currentGameDir = str;
}
*/

/*
string CConfiguration::gameFontDirectory.getString(){
	return gameFontDirectory;
}
void CConfiguration::setGameFontDirectory(string &dirname){
	gameFontDirectory= dirname;
}

*/

#if defined(WIN32)  //mingw ou msvc
Filesystem::CAbsolutePath CConfiguration::getEngineConfigFile(){
	;
		//! TODO   Método de find para o arquivo de configuração
	CMyString configFileName(sgfConfigFileName.getString());
	CMyString dir_Separator(DIR_SEPARATOR);
	CMyString completeFileName;
	char path[MAX_PATH];
    SHGetSpecialFolderPathA(0, path, CSIDL_APPDATA, false);
    completeFileName << path << dir_Separator << configFileName;
    
	Filesystem::CAbsolutePath configFilePath(completeFileName.c_str());

    if (configFilePath.exist())
		return Filesystem::CAbsolutePath(completeFileName.c_str());
	else
	{
		CMyString dir(currentSGFDir.getString());
		CMyString configFile = dir+dir_Separator+configFileName;
		Filesystem::CAbsolutePath tempPath=Filesystem::CAbsolutePath();
		Filesystem::CIsolatedPath isopath(configFile);
		return tempPath.joinToCurrent(isopath);

	}
	
}

Filesystem::CAbsolutePath CConfiguration::getDebugConfigFile(){

		//! TODO   Método de find para o arquivo de configuração
	CMyString configFileName(sgfDebugConfigFileName.getString());
	CMyString dir_Separator(DIR_SEPARATOR);
    CMyString completeFileName;
	char path[MAX_PATH];
    SHGetSpecialFolderPathA(0, path, CSIDL_APPDATA, false);
    completeFileName << path << dir_Separator << configFileName;
    
	Filesystem::CAbsolutePath configFilePath(completeFileName.c_str());
 if (configFilePath.exist())
		return Filesystem::CAbsolutePath(completeFileName.c_str());
	else
	{
		CMyString dir(currentSGFDir.getString());
		CMyString configFile = dir+dir_Separator+configFileName;
		Filesystem::CAbsolutePath tempPath=Filesystem::CAbsolutePath();
		Filesystem::CIsolatedPath isopath(configFile);
		return tempPath.joinToCurrent(isopath);

	}

}

#else    //linux
static string getConfigFile(){
	ostringstream str;
	str << getenv( "HOME" ) << "/.sgfcfgnrc";
	return str.str();
}


#endif

/* this nonsense is just to convert a regular integer into an enum CJoystick::Key*/
CConfiguration::JoystickInput CConfiguration::intToJoystick(int a){
    switch (a){
        case CJoystick::Up : return CJoystick::Up;  //equivalente a axis 1D1
		case CJoystick::Down : return CJoystick::Down;    //equivalente a axis 1D2
		case CJoystick::Left : return CJoystick::Left;  //equivalente a axis 0D1
		case CJoystick::Right : return CJoystick::Right;  //equivalent a axis 0D2
		case CJoystick::Axis2D1 : return CJoystick::Axis2D1;
		case CJoystick::Axis2D2 : return CJoystick::Axis2D2;
		case CJoystick::Axis3D1 : return CJoystick::Axis3D1;
		case CJoystick::Axis3D2 : return CJoystick::Axis3D2;
		case CJoystick::Axis4D1 : return CJoystick::Axis4D1;
		case CJoystick::Axis4D2 : return CJoystick::Axis4D2;
		case CJoystick::Button1 : return CJoystick::Button1;
		case CJoystick::Button2 : return CJoystick::Button2;
		case CJoystick::Button3 : return CJoystick::Button3;
		case CJoystick::Button4 : return CJoystick::Button4;
		case CJoystick::Button5 : return CJoystick::Button5;
		case CJoystick::Button6 : return CJoystick::Button6;
		case CJoystick::Button7 : return CJoystick::Button7;
        case CJoystick::Button8 : return CJoystick::Button8;
		case CJoystick::Button9 : return CJoystick::Button9;
        case CJoystick::Button10 : return CJoystick::Button10;
		case CJoystick::Button11 : return CJoystick::Button11;
        case CJoystick::Button12 : return CJoystick::Button12;
		case CJoystick::Hat1 : return CJoystick::Hat1;
		case CJoystick::Hat2 : return CJoystick::Hat2;
		case CJoystick::Hat3 : return CJoystick::Hat3;
		case CJoystick::Hat4 : return CJoystick::Hat4;
		case CJoystick::Hat5 : return CJoystick::Hat5;
		case CJoystick::Hat6 : return CJoystick::Hat6;
		case CJoystick::Hat7 : return CJoystick::Hat7;
		case CJoystick::Hat8 : return CJoystick::Hat8;
		case CJoystick::Track1 : return CJoystick::Track1;
		case CJoystick::Track2 : return CJoystick::Track2;
    }
    return CJoystick::Invalid;
}
/* this nonsense is just to convert a regular integer into an enum CJoystick::Key*/
CConfiguration::MouseInput CConfiguration::intToMouse(int a){
	Debug::debug(Debug::input,__FUNCTION__) << "Convert Mouse key: "<< a <<endl;
    switch (a){
        case CMouse::Key_LEFT : return CMouse::Key_LEFT;
        case CMouse::Key_MIDDLE : return CMouse::Key_MIDDLE;
        case CMouse::Key_RIGHT : return CMouse::Key_RIGHT;
        case CMouse::Key_WUP : return CMouse::Key_WUP;
        case CMouse::Key_WDOWN : return CMouse::Key_WDOWN;
		case CMouse::Key_MoveUP : return CMouse::Key_MoveUP;			// Virtual keys switched when mouse move
		case CMouse::Key_MoveDOWN : return CMouse::Key_MoveDOWN;
		case CMouse::Key_MoveLEFT : return CMouse::Key_MoveLEFT;
		case CMouse::key_MoveRIGHT : return CMouse::key_MoveRIGHT;
            }
    return CMouse::Invalid;
}


/* this nonsense is just to convert a regular integer into an enum  CKeyboard::key */
CConfiguration::KeyboardMod CConfiguration::intToKeyboardMod(int a){
    switch (a){
	case CKeyboard::Mod_NONE : return CKeyboard::Mod_NONE;
	case CKeyboard::Mod_NUM : return CKeyboard::Mod_NUM;
	case CKeyboard::Mod_CAPS :return CKeyboard::Mod_CAPS;
	case CKeyboard::Mod_LCTRL :return CKeyboard::Mod_LCTRL;
	case CKeyboard::Mod_RCTRL :return CKeyboard::Mod_RCTRL;
	case CKeyboard::Mod_RSHIFT :return CKeyboard::Mod_RSHIFT;
	case CKeyboard::Mod_LSHIFT :return CKeyboard::Mod_LSHIFT;
	case CKeyboard::Mod_RALT :return CKeyboard::Mod_RALT;
	case CKeyboard::Mod_LALT :return CKeyboard::Mod_LALT;
	case CKeyboard::Mod_RGUI :return CKeyboard::Mod_RGUI;
	case CKeyboard::Mod_LGUI :return CKeyboard::Mod_LGUI;
	case CKeyboard::Mod_MODE :return CKeyboard::Mod_MODE;
	}
    return CKeyboard::ModInvalid;
}


/* this nonsense is just to convert a regular integer into an enum  CKeyboard::key */
CConfiguration::KeyboardInput CConfiguration::intToKeyboard(int a){
    switch (a){
		case CKeyboard::Key_A : return CKeyboard::Key_A;
		case CKeyboard::Key_B : return CKeyboard::Key_B;
		case CKeyboard::Key_C : return CKeyboard::Key_C;
case CKeyboard::Key_D : return CKeyboard::Key_D;
case CKeyboard::Key_E : return CKeyboard::Key_E;
case CKeyboard::Key_F : return CKeyboard::Key_F;
case CKeyboard::Key_G : return CKeyboard::Key_G;
case CKeyboard::Key_H : return CKeyboard::Key_H;
case CKeyboard::Key_I : return CKeyboard::Key_I;
case CKeyboard::Key_J : return CKeyboard::Key_J;
case CKeyboard::Key_K : return CKeyboard::Key_K;
case CKeyboard::Key_L : return CKeyboard::Key_L;
case CKeyboard::Key_M : return CKeyboard::Key_M;
case CKeyboard::Key_N : return CKeyboard::Key_N;
case CKeyboard::Key_O : return CKeyboard::Key_O;
case CKeyboard::Key_P : return CKeyboard::Key_P;
case CKeyboard::Key_Q : return CKeyboard::Key_Q;
case CKeyboard::Key_R : return CKeyboard::Key_R;
case CKeyboard::Key_S : return CKeyboard::Key_S;
case CKeyboard::Key_T : return CKeyboard::Key_T;
case CKeyboard::Key_U : return CKeyboard::Key_U;
case CKeyboard::Key_V : return CKeyboard::Key_V;
case CKeyboard::Key_W : return CKeyboard::Key_W;
case CKeyboard::Key_X : return CKeyboard::Key_X;
case CKeyboard::Key_Y : return CKeyboard::Key_Y;
case CKeyboard::Key_Z : return CKeyboard::Key_Z;
case CKeyboard::Key_0 : return CKeyboard::Key_0;
case CKeyboard::Key_1 : return CKeyboard::Key_1;
case CKeyboard::Key_2 : return CKeyboard::Key_2;
case CKeyboard::Key_3 : return CKeyboard::Key_3;
case CKeyboard::Key_4 : return CKeyboard::Key_4;
case CKeyboard::Key_5 : return CKeyboard::Key_5;
case CKeyboard::Key_6 : return CKeyboard::Key_6;
case CKeyboard::Key_7 : return CKeyboard::Key_7;
case CKeyboard::Key_8 : return CKeyboard::Key_8;
case CKeyboard::Key_9 : return CKeyboard::Key_9;
case CKeyboard::Key_0_PAD : return CKeyboard::Key_0_PAD;
case CKeyboard::Key_1_PAD : return CKeyboard::Key_1_PAD;
case CKeyboard::Key_2_PAD : return CKeyboard::Key_2_PAD;
case CKeyboard::Key_3_PAD : return CKeyboard::Key_3_PAD;
case CKeyboard::Key_4_PAD : return CKeyboard::Key_4_PAD;
case CKeyboard::Key_5_PAD : return CKeyboard::Key_5_PAD;
case CKeyboard::Key_6_PAD : return CKeyboard::Key_6_PAD;
case CKeyboard::Key_7_PAD : return CKeyboard::Key_7_PAD;
case CKeyboard::Key_8_PAD : return CKeyboard::Key_8_PAD;
case CKeyboard::Key_9_PAD : return CKeyboard::Key_9_PAD;
case CKeyboard::Key_F1 : return CKeyboard::Key_F1;
case CKeyboard::Key_F2 : return CKeyboard::Key_F2;
case CKeyboard::Key_F3 : return CKeyboard::Key_F3;
case CKeyboard::Key_F4 : return CKeyboard::Key_F4;
case CKeyboard::Key_F5 : return CKeyboard::Key_F5;
case CKeyboard::Key_F6 : return CKeyboard::Key_F6;
case CKeyboard::Key_F7 : return CKeyboard::Key_F7;
case CKeyboard::Key_F8 : return CKeyboard::Key_F8;
case CKeyboard::Key_F9 : return CKeyboard::Key_F9;
case CKeyboard::Key_F10 : return CKeyboard::Key_F10;
case CKeyboard::Key_F11 : return CKeyboard::Key_F11;
case CKeyboard::Key_F12 : return CKeyboard::Key_F12;
case CKeyboard::Key_ESC : return CKeyboard::Key_ESC;
case CKeyboard::Key_TILDE : return CKeyboard::Key_TILDE;
case CKeyboard::Key_MINUS : return CKeyboard::Key_MINUS;
case CKeyboard::Key_EQUALS : return CKeyboard::Key_EQUALS;
case CKeyboard::Key_BACKSPACE : return CKeyboard::Key_BACKSPACE;
case CKeyboard::Key_TAB : return CKeyboard::Key_TAB;
case CKeyboard::Key_OPENBRACE : return CKeyboard::Key_OPENBRACE;
case CKeyboard::Key_CLOSEBRACE : return CKeyboard::Key_CLOSEBRACE;
case CKeyboard::Key_ENTER : return CKeyboard::Key_ENTER;
case CKeyboard::Key_COLON : return CKeyboard::Key_COLON;
case CKeyboard::Key_QUOTE : return CKeyboard::Key_QUOTE;
case CKeyboard::Key_BACKSLASH : return CKeyboard::Key_BACKSLASH;
//case CKeyboard::Key_BACKSLASH2 = ::Key_BACKSLASH2;
case CKeyboard::Key_COMMA : return CKeyboard::Key_COMMA;
case CKeyboard::Key_STOP : return CKeyboard::Key_STOP;
case CKeyboard::Key_SLASH : return CKeyboard::Key_SLASH;
case CKeyboard::Key_SPACE : return CKeyboard::Key_SPACE;
case CKeyboard::Key_INSERT : return CKeyboard::Key_INSERT;
case CKeyboard::Key_DEL : return CKeyboard::Key_DEL;
case CKeyboard::Key_HOME : return CKeyboard::Key_HOME;
case CKeyboard::Key_END : return CKeyboard::Key_END;
case CKeyboard::Key_PGUP : return CKeyboard::Key_PGUP;
case CKeyboard::Key_PGDN : return CKeyboard::Key_PGDN;
case CKeyboard::Key_LEFT : return CKeyboard::Key_LEFT;
case CKeyboard::Key_RIGHT : return CKeyboard::Key_RIGHT;
case CKeyboard::Key_UP : return CKeyboard::Key_UP;
case CKeyboard::Key_DOWN : return CKeyboard::Key_DOWN;
case CKeyboard::Key_SLASH_PAD : return CKeyboard::Key_SLASH_PAD;
case CKeyboard::Key_ASTERISK : return CKeyboard::Key_ASTERISK;
case CKeyboard::Key_MINUS_PAD : return CKeyboard::Key_MINUS_PAD;
case CKeyboard::Key_PLUS_PAD : return CKeyboard::Key_PLUS_PAD;
//case CKeyboard::Key_DEL_PAD = ::Key_DEL_PAD;
case CKeyboard::Key_ENTER_PAD : return CKeyboard::Key_ENTER_PAD;
case CKeyboard::Key_PRTSCR : return CKeyboard::Key_PRTSCR;
case CKeyboard::Key_PAUSE : return CKeyboard::Key_PAUSE;
//case CKeyboard::Key_ABNT_C1 = ::Key_ABNT_C1;
//case CKeyboard::Key_YEN = ::Key_YEN;
//case CKeyboard::Key_KANA = ::Key_KANA;
//case CKeyboard::Key_CONVERT = ::Key_CONVERT;
//case CKeyboard::Key_NOCONVERT = ::Key_NOCONVERT;
case CKeyboard::Key_AT : return CKeyboard::Key_AT;
case CKeyboard::Key_CIRCUMFLEX : return CKeyboard::Key_CIRCUMFLEX;
//case CKeyboard::Key_COLON2 = ::Key_KEY_COLON2;
//case CKeyboard::Key_KANJI = ::Key_KEY_KANJI;
case CKeyboard::Key_EQUALS_PAD : return CKeyboard::Key_EQUALS_PAD;
//Scase CKeyboard::Key_BACKQUOTE : return CKeyboard::Key_BACKQUOTE;
case CKeyboard::Key_SEMICOLON : return CKeyboard::Key_SEMICOLON;
//Scase CKeyboard::Key_COMMAND : return CKeyboard::Key_COMMAND;
//case CKeyboard::Key_UNKNOWN1 = ::KEY_UNKNOWN1;
//case CKeyboard::Key_UNKNOWN2 = ::KEY_UNKNOWN2;
//case CKeyboard::Key_UNKNOWN3 = ::KEY_UNKNOWN3;
//case CKeyboard::Key_UNKNOWN4 = ::KEY_UNKNOWN4;
//case CKeyboard::Key_UNKNOWN5 = ::KEY_UNKNOWN5;
//case CKeyboard::Key_UNKNOWN6 = ::KEY_UNKNOWN6;
//case CKeyboard::Key_UNKNOWN7 = ::KEY_UNKNOWN7;
case CKeyboard::Key_UNKNOWN : return CKeyboard::Key_UNKNOWN;
//case CKeyboard::Key_MODIFIERS = ::Key_MODIFIERS;
case CKeyboard::Key_LSHIFT : return CKeyboard::Key_LSHIFT;
case CKeyboard::Key_RSHIFT : return CKeyboard::Key_RSHIFT;
case CKeyboard::Key_LCONTROL : return CKeyboard::Key_LCONTROL;
case CKeyboard::Key_RCONTROL : return CKeyboard::Key_RCONTROL;
case CKeyboard::Key_ALT : return CKeyboard::Key_ALT;
case CKeyboard::Key_ALTGR : return CKeyboard::Key_ALTGR;
case CKeyboard::Key_LWIN : return CKeyboard::Key_LWIN;
case CKeyboard::Key_RWIN : return CKeyboard::Key_RWIN;
case CKeyboard::Key_MENU : return CKeyboard::Key_MENU;
case CKeyboard::Key_SCRLOCK : return CKeyboard::Key_SCRLOCK;
case CKeyboard::Key_NUMLOCK : return CKeyboard::Key_NUMLOCK;
case CKeyboard::Key_CAPSLOCK : return CKeyboard::Key_CAPSLOCK;



			//Todo: complete the keys

    }
    return CKeyboard::Invalid;
}
#if 0
//todo: coorrect load and save confiruration
static Token * removeDuplicates(Token * token){
    /* TODO */
    return token;
}
void CConfiguration::loadConfigurations(){
    data = new Token();
    *data << config_configuration;

    try{
        Filesystem::CAbsolutePath file = Filesystem::getInstance().configFile();
        TokenReader tr;
        Token * head = tr.readTokenFromFile(file.path());

        if (*head != config_configuration){
            throw CLoadException(__FILE__, __LINE__, string("Config file ") + Storage::instance().configFile().path() + " does not use the configuration format" );
        }

        /* Store the entire configuration tree */
        data = removeDuplicates(head->copy());
    } catch ( const CLoadException & le ){
        Debug::debug( Debug::error,__FUNCTION__ ) << "Notice: Could not load configuration file " << Storage::instance().configFile().path() << ": " << le.getTrace() << endl;
    } catch ( const CTokenException & t ){
        Debug::debug( Debug::error,__FUNCTION__ ) << "Notice: could not open configuration file '" << Storage::instance().configFile().path() << "': " << t.getTrace() << endl;
    }
}
#endif
//! Default debug is all debug is turned on
/*
<type> file </type>
<filename> debug.txt </filename>
<bitmap> 1 </bitmap>
<font> 1 </font>
<gui> 1 </gui>
<input> 1 </input>
<compilers> 1 </compilers>
<configuration> 1 </configuration>
<parsers> 1 </parsers>
<lists> 1 </lists>
<menu> 1 </menu>
<network> 1 </network>
<resources> 1 </resources>
<objects> 1 </objects>
<exceptions> 1 </exceptions>
<environment> 1 </environment>
<filesystem> 1 </filesystem>
<sound> 1 </sound>
<console> 1 </console>
<gameEngine> 1 </gameEngine>
<sdlmanager> 1 </sdlmanager>
<xml> 1 </xml>
<gameObject> 1 </gameObject>
<gameStage> 1 </gameStage>
<gameStateMachine> 1 </gameStateMachine>
<gameStory> 1 </gameStory>
<gameConfiguration> 1 </gameConfiguration>
<error> 1 </error>
*/
void CConfiguration::loadDefaultDebugConfiguration(){
Debug::setDebugMethod(Debug::File);
Debug::setFilename("debug.txt");
Debug::setDebug(Debug::environment);
Debug::setDebug(Debug::bitmap);
Debug::setDebug(Debug::font);
Debug::setDebug(Debug::gui);
Debug::setDebug(Debug::input);
Debug::setDebug(Debug::compilers);
Debug::setDebug(Debug::configuration);
Debug::setDebug(Debug::parsers);
Debug::setDebug(Debug::lists);
Debug::setDebug(Debug::menu);
Debug::setDebug(Debug::network);
Debug::setDebug(Debug::resources);
Debug::setDebug(Debug::objects);
Debug::setDebug(Debug::exceptions);
Debug::setDebug(Debug::environment);
Debug::setDebug(Debug::filesystem);
Debug::setDebug(Debug::sound);
Debug::setDebug(Debug::console);
Debug::setDebug(Debug::gameEngine);
Debug::setDebug(Debug::sdlmanager);
Debug::setDebug(Debug::xml);
Debug::setDebug(Debug::gameObject);
Debug::setDebug(Debug::gameStage);
Debug::setDebug(Debug::gameStateMachine);
Debug::setDebug(Debug::gameStory);
Debug::setDebug(Debug::gameConfiguration);
Debug::setDebug(Debug::error);
}

void CConfiguration::loadDebugConfiguration() throw (CLoadException){
	    //cout << "WILL LOAD DEBUG CONFIGURATION" << endl;
		Filesystem::CAbsolutePath DebugFile = getDebugConfigFile();

		if (!DebugFile.exist()) {

			Debug::debug(Debug::error,__FUNCTION__) << string("Debug Config file  Does Not Exist - Using Default Configuration Parâmeters" );
			loadDefaultDebugConfiguration();
			return;
		}
		CTokenReaderXML tr(DebugFile.path());
        Token * head = tr.readToken();

        if (*head != "configuration"){
			Debug::debug(Debug::error,__FUNCTION__) << string("Debug file ") + DebugFile.path() + " does not use the configuration format" << endl;
            throw CLoadException(__FILE__, __LINE__, string("Debug file ") + DebugFile.path() + " does not use the configuration format" );
        }else {
			head->print("");
		}

        TokenView view = head->view();


		while (view.hasMore()){
            const Token * n;
            view >> n;
            /* these operate on the global vars directly
             * to avoid calling saveConfiguration
             * if setFoo() was called
             */

            if ( *n == "debug-configuration" ){

                TokenView debugView = n->view();



				while (debugView.hasMore()){
                    const Token * thing;
					int temp;
					string _string;

                    debugView >> thing;

                    if ( *thing == "type"){
                        thing->view() >> _string;
						if (_string == "file") Debug::setDebugMethod(Debug::File);
						else Debug::setDebugMethod(Debug::Default);
                    } else if (*thing == "filename"){
                        thing->view() >> _string;
						Debug::setFilename(_string);
						//Debug::setDebugAll();
                    }else if ( *thing == "bitmap"){

						int x;
						thing->view() >> _string;

					   if(temp == 1) {
							 Debug::setDebug(Debug::bitmap);
						 }else {
							 Debug::resetDebug(Debug::bitmap);
						 }
                    }

					else if ( *thing == "font"){
                       thing->view() >> temp;
					   if(temp == 1) {
							 Debug::setDebug(Debug::font);
						 }else {
							 Debug::resetDebug(Debug::font);
						 }
                    } else if ( *thing == "gui"){
                        thing->view() >> temp;
					    if(temp == 1) {
							 Debug::setDebug(Debug::gui);
						 }else {
							 Debug::resetDebug(Debug::gui);
						 }
                    } else if ( *thing == "input"){
                        thing->view() >> temp;
						if(temp == 1) {
							 Debug::setDebug(Debug::input);
						 }else {
							 Debug::resetDebug(Debug::input);
						 }
                    }else if ( *thing == "compilers"){

                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::compilers);
						 }else {
							 Debug::resetDebug(Debug::compilers);
						 }
                    } else if ( *thing == "configuration"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::configuration);
						 }else {
							 Debug::resetDebug(Debug::configuration);
						 }
                    } else if ( *thing == "parsers"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::parsers);
						 }else {
							 Debug::resetDebug(Debug::parsers);
						 }
                    } else if ( *thing == "lists"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::lists);
						 }else {
							 Debug::resetDebug(Debug::lists);
						 }
                    }else if ( *thing == "menu"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::menu);
						 }else {
							 Debug::resetDebug(Debug::menu);
						 }
                    }else if ( *thing == "network"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::network);
						 }else {
							 Debug::resetDebug(Debug::network);
						 }
                    }else if ( *thing == "resources"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::resources);
						 }else {
							 Debug::resetDebug(Debug::resources);
						 }
                    }else if ( *thing == "objects"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::objects);
						 }else {
							 Debug::resetDebug(Debug::objects);
						 }
                    }else if ( *thing == "exceptions"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::exceptions);
						 }else {
							 Debug::resetDebug(Debug::exceptions);
						 }
                    }else if ( *thing == "environment"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::environment);
						 }else {
							 Debug::resetDebug(Debug::environment);
						 }
                    }else if ( *thing == "filesystem"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::filesystem);
						 }else {
							 Debug::resetDebug(Debug::filesystem);
						 }
                    }else if ( *thing == "sound"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::sound);
						 }else {
							 Debug::resetDebug(Debug::sound);
						 }
                    }else if ( *thing == "console"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::console);
						 }else {
							 Debug::resetDebug(Debug::console);
						 }
                    }else if ( *thing == "gameengine"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::gameEngine);
						 }else {
							 Debug::resetDebug(Debug::gameEngine);
						 }
                    }else if ( *thing == "sdlmanager"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::sdlmanager);
						 }else {
							 Debug::resetDebug(Debug::sdlmanager);
						 }
                    }else if ( *thing == "xml"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::xml);
						 }else {
							 Debug::resetDebug(Debug::xml);
						 }
					}else if ( *thing == "gameobject"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::gameObject);
						 }else {
							 Debug::resetDebug(Debug::gameObject);
						 }
                    }else if ( *thing == "gamestage"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::gameStage);
						 }else {
							 Debug::resetDebug(Debug::gameStage);
						 }
                    }else if ( *thing == "gamestatemachine"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::gameStateMachine);
						 }else {
							 Debug::resetDebug(Debug::gameStateMachine);
						 }
                    }else if ( *thing == "gamestory"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::gameStory);
						 }else {
							 Debug::resetDebug(Debug::gameStory);
						 }
                    }else if ( *thing == "gameconfiguration"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::gameConfiguration);
						 }else {
							 Debug::resetDebug(Debug::gameConfiguration);
						 }
                    }

			   }

            }

		}



}

void CConfiguration::loadTesteConfiguration()throw (CLoadException){
	    //cout << "WILL LOAD DEBUG CONFIGURATION" << endl;
		Filesystem::CAbsolutePath DebugFile = getDebugConfigFile();

		if (!DebugFile.exist()) throw CLoadException(__FILE__, __LINE__, string("Debug Config file  Does Not Exist - Using Default Configuration Parâmeters" ));

		CTokenReaderXML tr("\\open\\teste.xml");
        Token * head = tr.readToken();

        if (*head != "configuration"){
			Debug::debug(Debug::error,__FUNCTION__) << string("Debug file ") + DebugFile.path() + " does not use the configuration format" << endl;
            throw CLoadException(__FILE__, __LINE__, string("Debug file ") + DebugFile.path() + " does not use the configuration format" );
        }else {
			head->print("");
		}

        TokenView view = head->view();


		while (view.hasMore()){
            const Token * n;
            view >> n;
            /* these operate on the global vars directly
             * to avoid calling saveConfiguration
             * if setFoo() was called
             */

            if ( *n == "debug-configuration" ){

                TokenView debugView = n->view();



				while (debugView.hasMore()){
                    const Token * thing;
					int temp;
					string _string;

                    debugView >> thing;

                    if ( *thing == "type"){
                        thing->view() >> _string;
						if (_string == "file") Debug::setDebugMethod(Debug::File);
						else Debug::setDebugMethod(Debug::Default);
                    } else if (*thing == "filename"){
                        thing->view() >> _string;
						Debug::setFilename(_string);
						//Debug::setDebugAll();
                    }else if ( *thing == "bitmap"){

						int x;
						thing->view() >> _string;

					   if(temp == 1) {
							 Debug::setDebug(Debug::bitmap);
						 }else {
							 Debug::resetDebug(Debug::bitmap);
						 }
                    }

					else if ( *thing == "font"){
                       thing->view() >> temp;
					   if(temp == 1) {
							 Debug::setDebug(Debug::font);
						 }else {
							 Debug::resetDebug(Debug::font);
						 }
                    } else if ( *thing == "gui"){
                        thing->view() >> temp;
					    if(temp == 1) {
							 Debug::setDebug(Debug::gui);
						 }else {
							 Debug::resetDebug(Debug::gui);
						 }
                    } else if ( *thing == "input"){
                        thing->view() >> temp;
						if(temp == 1) {
							 Debug::setDebug(Debug::input);
						 }else {
							 Debug::resetDebug(Debug::input);
						 }
                    }else if ( *thing == "compilers"){

                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::compilers);
						 }else {
							 Debug::resetDebug(Debug::compilers);
						 }
                    } else if ( *thing == "configuration"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::configuration);
						 }else {
							 Debug::resetDebug(Debug::configuration);
						 }
                    } else if ( *thing == "parsers"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::parsers);
						 }else {
							 Debug::resetDebug(Debug::parsers);
						 }
                    } else if ( *thing == "lists"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::lists);
						 }else {
							 Debug::resetDebug(Debug::lists);
						 }
                    }else if ( *thing == "menu"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::menu);
						 }else {
							 Debug::resetDebug(Debug::menu);
						 }
                    }else if ( *thing == "network"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::network);
						 }else {
							 Debug::resetDebug(Debug::network);
						 }
                    }else if ( *thing == "resources"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::resources);
						 }else {
							 Debug::resetDebug(Debug::resources);
						 }
                    }else if ( *thing == "objects"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::objects);
						 }else {
							 Debug::resetDebug(Debug::objects);
						 }
                    }else if ( *thing == "exceptions"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::exceptions);
						 }else {
							 Debug::resetDebug(Debug::exceptions);
						 }
                    }else if ( *thing == "environment"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::environment);
						 }else {
							 Debug::resetDebug(Debug::environment);
						 }
                    }else if ( *thing == "filesystem"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::filesystem);
						 }else {
							 Debug::resetDebug(Debug::filesystem);
						 }
                    }else if ( *thing == "sound"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::sound);
						 }else {
							 Debug::resetDebug(Debug::sound);
						 }
                    }else if ( *thing == "console"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::console);
						 }else {
							 Debug::resetDebug(Debug::console);
						 }
                    }else if ( *thing == "gameengine"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::gameEngine);
						 }else {
							 Debug::resetDebug(Debug::gameEngine);
						 }
                    }else if ( *thing == "sdlmanager"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::sdlmanager);
						 }else {
							 Debug::resetDebug(Debug::sdlmanager);
						 }
                    }else if ( *thing == "xml"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::xml);
						 }else {
							 Debug::resetDebug(Debug::xml);
						 }
					}else if ( *thing == "gameobject"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::gameObject);
						 }else {
							 Debug::resetDebug(Debug::gameObject);
						 }
                    }else if ( *thing == "gamestage"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::gameStage);
						 }else {
							 Debug::resetDebug(Debug::gameStage);
						 }
                    }else if ( *thing == "gamestatemachine"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::gameStateMachine);
						 }else {
							 Debug::resetDebug(Debug::gameStateMachine);
						 }
                    }else if ( *thing == "gamestory"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::gameStory);
						 }else {
							 Debug::resetDebug(Debug::gameStory);
						 }
                    }else if ( *thing == "gameconfiguration"){
                         thing->view() >> temp;
						 if(temp == 1) {
							 Debug::setDebug(Debug::gameConfiguration);
						 }else {
							 Debug::resetDebug(Debug::gameConfiguration);
						 }
                    }

			   }

            }

		}



}

void CConfiguration::loadEngineConfiguration() throw (CLoadException) {

	//Filesystem::CAbsolutePath ConfigFile = Filesystem::getInstance().configFile();
	Filesystem::CAbsolutePath ConfigFile = getEngineConfigFile();

	if (!ConfigFile.exist()) throw CLoadException(__FILE__, __LINE__, string("Config file  Does Not Exist - Using Default Configuration Parâmeters" ));

		CTokenReaderXML tr(ConfigFile.path());
        Token * head = tr.readToken();

        if (*head != config_configuration){
            throw CLoadException(__FILE__, __LINE__, string("Config file ") + Filesystem::getInstance().configFile().path() + " does not use the configuration format" );
        }else {
			head->print("");
		}

        TokenView view = head->view();


		while (view.hasMore()){
            const Token * n;
            view >> n;
            /* these operate on the global vars directly
             * to avoid calling saveConfiguration
             * if setFoo() was called
             */
            if ( *n == config_keyboard_configuration ){
                int number, key1,key2,key3,key4,key5,
					key6,key7,key8,key9,key10,
					key11,key12,key13,key14,key15,key16,
					key17,key18,key19,key20,
					key21,key22,key23,key24,key25,
					key26,key27,key28,key29,key30,
					 key31,key32,key33,key34= -1;

                // before the 'version' key was added all backends were

                TokenView keyboardView = n->view();
                while (keyboardView.hasMore()){
                    const Token * thing;
					int temp;
                    keyboardView >> thing;
                    if ( *thing == config_number){
                        thing->view() >> number;

                    } else if (*thing == config_input){
                        thing->view() >> temp;
						//input= intToKeyboard(temp);

					}else if ( *thing == config_ButtonRight){
						 thing->view() >> key1;


					}else if ( *thing == config_ButtonLeft){
						 thing->view() >> key2;

					}else if ( *thing == config_ButtonUp){
						 thing->view() >> key3;

					}else if ( *thing == config_ButtonDown){
						 thing->view() >> key4;

					}else if ( *thing == config_Button1){
						 thing->view() >> key5;

					}else if ( *thing == config_Button2){
						 thing->view() >> key6;

					}else if ( *thing == config_Button3){
						 thing->view() >> key7;

					}else if ( *thing == config_Button4){
						 thing->view() >> key8;

					}else if ( *thing == config_Button5){
						 thing->view() >> key9;

					}else if ( *thing == config_Button6){
						 thing->view() >> key10;

					}else if ( *thing == config_Button7){
						 thing->view() >> key11;

					}else if ( *thing == config_Button8){
						 thing->view() >> key12;

					}else if ( *thing == config_Button9){
						 thing->view() >> key13;

					}else if ( *thing == config_ButtonJump){
						 thing->view() >> key14;

					}else if ( *thing == config_ButtonGrab){
						 thing->view() >> key15;

					}else if ( *thing == config_ButtonStart){
						 thing->view() >> key16;

					}else if ( *thing == config_ButtonSelect){
						 thing->view() >> key17;

					}else if ( *thing == config_ButtonDeal){
						 thing->view() >> key18;

					}else if ( *thing == config_ButtonBet){
						 thing->view() >> key19;

					}else if ( *thing == config_ButtonDoubleUP){
						 thing->view() >> key20;

					}else if ( *thing == config_ButtonStand){
						 thing->view() >> key21;

					}else if ( *thing == config_ButtonOpen){
						 thing->view() >> key22;

					}else if ( *thing == config_ButtonConfig){
						 thing->view() >> key23;

					}else if ( *thing == config_ButtonPause){
						 thing->view() >> key24;

					}else if ( *thing == config_ButtonReset){
						 thing->view() >> key25;

					}else if ( *thing == config_ButtonShowGFX){
						 thing->view() >> key26;

					}else if ( *thing == config_ButtonShowFPS){
						 thing->view() >> key27;

					}else if ( *thing == config_ButtonSaveConfig){
						 thing->view() >> key28;

					}else if ( *thing == config_ButtonLoadConfig){
						 thing->view() >> key29;

					}else if ( *thing == config_ButtonDebugger){
						 thing->view() >> key30;

					}else if ( *thing == config_ButtonToggleConsole){
						 thing->view() >> key31;

					}else if ( *thing == config_ButtonReload){
						 thing->view() >> key32;

					}else if ( *thing == config_ButtonCancel){
						 thing->view() >> key33;

					}else if ( *thing == config_ButtonQuit){
						 thing->view() >> key34;



					}
                } //end while
                if ( number == -1 ){
                    /* should use config_number here */
                    throw CLoadException(__FILE__, __LINE__, string("Config file ") + Filesystem::getInstance().configFile().path() + " does not specifiy (number #) for a keyboard-configuration" );
                }else{
					if(ConfigList[number]==NULL) CConfiguration * myconfig = getConfig(number);


					if(ConfigList[number]!=NULL) {
					ConfigList[number]->ButtonRight.setInteger(key1);
					ConfigList[number]->ButtonLeft.setInteger(key2);
					ConfigList[number]->ButtonUp.setInteger(key3);
					ConfigList[number]->ButtonDown.setInteger(key4);
					ConfigList[number]->Button1.setInteger(key5);
					ConfigList[number]->Button2.setInteger(key6);
					ConfigList[number]->Button3.setInteger(key7);
					ConfigList[number]->Button4.setInteger(key8);
					ConfigList[number]->Button5.setInteger(key9);
					ConfigList[number]->Button6.setInteger(key10);
					ConfigList[number]->Button7.setInteger(key11);
					ConfigList[number]->Button8.setInteger(key12);
					ConfigList[number]->Button9.setInteger(key13);
					ConfigList[number]->ButtonJump.setInteger(key14);
					ConfigList[number]->ButtonGrab.setInteger(key15);
					ConfigList[number]->ButtonStart.setInteger(key16);
					ConfigList[number]->ButtonSelect.setInteger(key17);
					ConfigList[number]->ButtonDeal.setInteger(key18);
					ConfigList[number]->ButtonBet.setInteger(key19);
					ConfigList[number]->ButtonDoubleUP.setInteger(key20);
					ConfigList[number]->ButtonStand.setInteger(key21);
					ConfigList[number]->ButtonOpen.setInteger(key22);
					ConfigList[number]->ButtonConfig.setInteger(key23);
					ConfigList[number]->ButtonPause.setInteger(key24);
					ConfigList[number]->ButtonReset.setInteger(key25);
					ConfigList[number]->ButtonShowGFX.setInteger(key26);
					ConfigList[number]->ButtonShowFPS.setInteger(key27);
					ConfigList[number]->ButtonSaveConfig.setInteger(key28);
					ConfigList[number]->ButtonLoadConfig.setInteger(key29);
					ConfigList[number]->ButtonDebugger.setInteger(key30);
					ConfigList[number]->ButtonToggleConsole.setInteger(key31);
					ConfigList[number]->ButtonReload.setInteger(key32);
					ConfigList[number]->ButtonCancel.setInteger(key33);
					ConfigList[number]->ButtonQuit.setInteger(key34);
					}
				}

            } else if ( *n == config_joystick_configuration ){
                int number = -1;
				 JoystickInput key1,key2,key3,key4,key5,
					key6,key7,key8,key9,key10,
					key11,key12,key13,key14,key15,key16,
					key17,key18,key19,key20,
					key21,key22,key23,key24,key25,
					key26,key27,key28,key29,key30,
					key31,key32,key33,key34= InvalidJoystick;

                TokenView joystickView = n->view();
                while (joystickView.hasMore()){
                    int temp;
                    const Token * thing;
                    joystickView >> thing;
                    if ( *thing == config_number){
                        thing->view() >>  number;

                    } else if (*thing == config_input){
                        thing->view() >> temp;
						//input= intToKeyboard(temp);

					}else if ( *thing == config_ButtonRight){
						 thing->view() >> temp;
						 key1 = intToJoystick(temp);


					}else if ( *thing == config_ButtonLeft){
						 thing->view() >> temp;
						 key2= intToJoystick(temp);

					}else if ( *thing == config_ButtonUp){
						 thing->view() >> temp;
						 key3= intToJoystick(temp);

					}else if ( *thing == config_ButtonDown){
						 thing->view() >> temp;
						 key4= intToJoystick(temp);

					}else if ( *thing == config_Button1){
						 thing->view() >> temp;
						 key5= intToJoystick(temp);

					}else if ( *thing == config_Button2){
						 thing->view() >> temp;
						 key6= intToJoystick(temp);

					}else if ( *thing == config_Button3){
						 thing->view() >> temp;
						 key7= intToJoystick(temp);

					}else if ( *thing == config_Button4){
						 thing->view() >> temp;
						 key8= intToJoystick(temp);

					}else if ( *thing == config_Button5){
						 thing->view() >> temp;
						 key9= intToJoystick(temp);

					}else if ( *thing == config_Button6){
						 thing->view() >> temp;
						 key10= intToJoystick(temp);

					}else if ( *thing == config_Button7){
						 thing->view() >> temp;
						 key11= intToJoystick(temp);

					}else if ( *thing == config_Button8){
						 thing->view() >> temp;
						 key12= intToJoystick(temp);

					}else if ( *thing == config_Button9){
						 thing->view() >> temp;
						 key13= intToJoystick(temp);

					}else if ( *thing == config_ButtonJump){
						 thing->view() >> temp;
						 key14= intToJoystick(temp);

					}else if ( *thing == config_ButtonGrab){
						 thing->view() >> temp;
						 key15= intToJoystick(temp);

					}else if ( *thing == config_ButtonStart){
						 thing->view() >> temp;
						 key16= intToJoystick(temp);

					}else if ( *thing == config_ButtonSelect){
						 thing->view() >> temp;
						 key17= intToJoystick(temp);

					}else if ( *thing == config_ButtonDeal){
						 thing->view() >> temp;
						 key18= intToJoystick(temp);

					}else if ( *thing == config_ButtonBet){
						 thing->view() >> temp;
						 key19= intToJoystick(temp);

					}else if ( *thing == config_ButtonDoubleUP){
						 thing->view() >> temp;
						 key20= intToJoystick(temp);

					}else if ( *thing == config_ButtonStand){
						 thing->view() >> temp;
						 key21= intToJoystick(temp);

					}else if ( *thing == config_ButtonOpen){
						 thing->view() >> temp;
						 key22= intToJoystick(temp);

					}else if ( *thing == config_ButtonConfig){
						 thing->view() >> temp;
						 key23= intToJoystick(temp);

					}else if ( *thing == config_ButtonPause){
						 thing->view() >> temp;
						 key24= intToJoystick(temp);

					}else if ( *thing == config_ButtonReset){
						 thing->view() >> temp;
						 key25= intToJoystick(temp);

					}else if ( *thing == config_ButtonShowGFX){
						 thing->view() >> temp;
						 key26= intToJoystick(temp);

					}else if ( *thing == config_ButtonShowFPS){
						 thing->view() >> temp;
						 key27= intToJoystick(temp);

					}else if ( *thing == config_ButtonSaveConfig){
						 thing->view() >> temp;
						 key28= intToJoystick(temp);

					}else if ( *thing == config_ButtonLoadConfig){
						 thing->view() >> temp;
						 key29= intToJoystick(temp);

					}else if ( *thing == config_ButtonDebugger){
						 thing->view() >> temp;
						 key30= intToJoystick(temp);

					}else if ( *thing == config_ButtonToggleConsole){
						 thing->view() >> temp;
						 key31= intToJoystick(temp);

					}else if ( *thing == config_ButtonReload){
						 thing->view() >> temp;
						 key32= intToJoystick(temp);

					}else if ( *thing == config_ButtonCancel){
						 thing->view() >> temp;
						 key33= intToJoystick(temp);

					}else if ( *thing == config_ButtonQuit){
						 thing->view() >> temp;
						 key34= intToJoystick(temp);
					}


                } //end while
                if ( number == -1 ){
                    /* should use config_number here */
                    throw CLoadException(__FILE__, __LINE__, string("Config file ") + Filesystem::getInstance().configFile().path() + " does not specifiy (number #) for a joystick-configuration" );
                }else{
					if(ConfigList[number]==NULL) CConfiguration * myconfig = getConfig(number);

					if(ConfigList[number]!=NULL) {
					ConfigList[number]->JoyButtonRight.setInteger(key1);
					ConfigList[number]->JoyButtonLeft.setInteger(key2);
					ConfigList[number]->JoyButtonUp.setInteger(key3);
					ConfigList[number]->JoyButtonDown.setInteger(key4);
					ConfigList[number]->JoyButton1.setInteger(key5);
					ConfigList[number]->JoyButton2.setInteger(key6);
					ConfigList[number]->JoyButton3.setInteger(key7);
					ConfigList[number]->JoyButton4.setInteger(key8);
					ConfigList[number]->JoyButton5.setInteger(key9);
					ConfigList[number]->JoyButton6.setInteger(key10);
					ConfigList[number]->JoyButton7.setInteger(key11);
					ConfigList[number]->JoyButtonJump.setInteger(key14);
					ConfigList[number]->JoyButtonStart.setInteger(key16);
					ConfigList[number]->JoyButtonSelect.setInteger(key17);
					ConfigList[number]->JoyButtonCancel.setInteger(key33);
					ConfigList[number]->JoyButtonQuit.setInteger(key34);
					}
				}



            } else if ( *n == config_game_speed){
				int gamespeed;
				n->view() >> gamespeed;
				gameSpeed.setInteger(gamespeed);
            }else if ( *n == config_game_fps){
				int gamefps;
				n->view() >> gamefps;
				gameFPS.setInteger(gamefps);
            }else if ( *n == config_game_skipticks){
				double gameskeep;
				n->view() >> gameskeep;
				gameSkipTicks.setFloat(gameskeep);
            } else if ( *n == config_fullscreen){
				bool fullscreen;
				n->view() >> fullscreen;
				fullScreen.setBool(fullscreen);
            } else if (*n == config_menu_font){
                string font;
                n->view() >> font;
           //s     setMenuFont_v1(font);
				//TODO: Fix MenuFontV2
				//setMenuFont_v2(font);
            }else if (*n == config_menuversion){
                int version;
                n->view() >> version;
		//s		setMenuVersion(version);
            }else if (*n == config_sound){
                int x;
                n->view() >> x;
				volumeSound.setInteger(x);
            } else if (*n == config_language){
                string what;
                n->view() >> what;
				gameLanguage.setString(what.c_str());
            } else if (*n == config_music){
                int x;
                n->view() >> x;
				volumeMusic.setInteger(x);
            } else if (*n == config_mugen_motif){
                string motif;
                n->view() >> motif;
        //s        setMugenMotif(motif);
            } else if (*n == config_menu_font_width){
                int x;
                n->view() >> x;
				menuFontSize.setInteger(x);
            } else if (*n == config_menu_font_height){
                int x;
                n->view() >> x;
				menuFontSize.setInteger(x);
            } else if (*n == config_current_game){
                string game;
                n->view() >> game;
				gameModDir.setString(game.c_str());
            } else if (*n == config_screen_size){
                int w, h;
                n->view() >> w >> h;
				screenWidth.setInteger(w);
            } else if (*n == config_play_mode){
                string mode;
                n->view() >> mode;
				playMode.setString(mode.c_str());
            }else if ( *n == config_sdl_configuration ){
                int number = -1;
                sdlModules_s initModules;
				//int number_of_windows = 1;
				numberOfWindows.setInteger(1);
                TokenView sdlView = n->view();
                while (sdlView.hasMore()){
                    //int temp;
                    const Token * thing;
                    sdlView >> thing;
                    if ( *thing == config_init_video){
						thing->view() >> initModules.VIDEO;
                    } else if (*thing == config_init_audio){
						thing->view() >> initModules.AUDIO;
                    }else if (*thing == config_init_fastevents){
						thing->view() >> initModules.FASTEVENTS;
                    } else if ( *thing == config_init_ttf){
						thing->view() >> initModules.TTF;
                    } else if ( *thing == config_init_framerate){
						thing->view() >> initModules.FRAMERATEMANAGER;
                    } else if ( *thing == config_init_window){
						thing->view() >> initModules.WINDOW;
                    } else if ( *thing == config_init_timer){
						thing->view() >> initModules.TIMER;
                    } else if ( *thing == config_init_joystick){
						thing->view() >> initModules.JOYSTICK;
                    }else if ( *thing == config_init_network){
						thing->view() >> initModules.NETWORK;
                    } else if ( *thing == config_init_textsupport){
						thing->view() >> initModules.TEXTSUPPORT;
                    }  else if ( *thing == config_number_of_windows){
						int x;
						thing->view() >> x;
				//s		setSDLNumberOfWindows(x);
                    }
                }
		//s		setSDLInitModules(initModules);

            } else {
                string value;
                try{
                    n->view() >> value;
                    CConfiguration::setProperty(n->getName(), value);
                } catch (const CTokenException & e){
                    /* ignore errors */
                }
            }
        }

}

void CConfiguration::loadConfigurations() throw (CLoadException){

	
	Debug::debug( Debug::configuration,__FUNCTION__ ) << "START LOADING CONFIGURATION "  << endl;
	CDisable disable;
	try{
		loadDebugConfiguration();
		loadEngineConfiguration();

    } catch ( const CLoadException & le ){
        Debug::debug( Debug::configuration,__FUNCTION__ )  << "Notice: Could not load configuration file " << Filesystem::getInstance().configFile().path() << ": " << le.getTrace() << endl;
    } catch ( const CTokenException & t ){
        Debug::debug( Debug::configuration,__FUNCTION__ ) <<  "Problem Loading Token: " << t.getTrace() << endl;
    } catch (...) {
		Debug::debug( Debug::configuration,__FUNCTION__ ) <<  "Unknow Problem Loading Token: " << endl;
	}
	Debug::debug( Debug::configuration,__FUNCTION__ ) << "END LOADING CONFIGURATION "  << endl;
}


/* todo: combine saveKeyboard and saveJoystick, probably using a templated function */
Token * CConfiguration::saveKeyboard( int num, CConfiguration * configuration ){
    typedef KeyboardInput (CConfiguration::*get_func)() const;
    Token * config = new Token();

    config->addToken( new Token(config_keyboard_configuration, false ) );
    Token * number = new Token();
    *number << config_number;
    config->addToken( number );
    *number << num;

    const char * xml_token_names[] = {
	config_ButtonRight,
	config_ButtonLeft,
	config_ButtonUp,
	config_ButtonDown,
	config_Button1,
	config_Button2,
	config_Button3,
	config_Button4,
	config_Button5,
	config_Button6,
	config_Button7,
	config_Button8,
	config_Button9,
	config_ButtonJump,
	config_ButtonGrab,
	config_ButtonStart,
	config_ButtonSelect,
	config_ButtonDeal,
	config_ButtonBet,
	config_ButtonDoubleUP,
	config_ButtonStand,
	config_ButtonOpen,
	config_ButtonConfig,
	config_ButtonPause,
	config_ButtonReset,
	config_ButtonShowGFX,
	config_ButtonShowFPS,
	config_ButtonSaveConfig,
	config_ButtonLoadConfig,
	config_ButtonDebugger,
	config_ButtonToggleConsole,
	config_ButtonReload,
	config_ButtonCancel,
	config_ButtonQuit,
	};
/*
    get_func funcs[] = {&CConfiguration::getLeft, &CConfiguration::getRight,
                        &CConfiguration::getUp, &CConfiguration::getDown,
                        &CConfiguration::getButtonA, &CConfiguration::getButtonB,
                        &CConfiguration::getButtonC, &CConfiguration::getButtonX,
    };*/
	CLocalSysVar  *vars[] = {&ConfigList[num]->ButtonRight,
	&ConfigList[num]->ButtonLeft,
	&ConfigList[num]->ButtonUp,
	&ConfigList[num]->ButtonDown,
	&ConfigList[num]->Button1,
	&ConfigList[num]->Button2,
	&ConfigList[num]->Button3,
	&ConfigList[num]->Button4,
	&ConfigList[num]->Button5,
	&ConfigList[num]->Button6,
	&ConfigList[num]->Button7,
	&ConfigList[num]->Button8,
	&ConfigList[num]->Button9,
	&ConfigList[num]->ButtonJump,
	&ConfigList[num]->ButtonGrab,
	&ConfigList[num]->ButtonStart,
	&ConfigList[num]->ButtonSelect,
	&ConfigList[num]->ButtonDeal,
	&ConfigList[num]->ButtonBet,
	&ConfigList[num]->ButtonDoubleUP,
	&ConfigList[num]->ButtonStand,
	&ConfigList[num]->ButtonOpen,
	&ConfigList[num]->ButtonConfig,
	&ConfigList[num]->ButtonPause,
	&ConfigList[num]->ButtonReset,
	&ConfigList[num]->ButtonShowGFX,
	&ConfigList[num]->ButtonShowFPS,
	&ConfigList[num]->ButtonSaveConfig,
	&ConfigList[num]->ButtonLoadConfig,
	&ConfigList[num]->ButtonDebugger,
	&ConfigList[num]->ButtonToggleConsole,
	&ConfigList[num]->ButtonReload,
	&ConfigList[num]->ButtonCancel,
	&ConfigList[num]->ButtonQuit,
	};
    for ( unsigned int i = 0; i < sizeof(xml_token_names)/sizeof(char*); i++ ){
        Token * button = new Token();
        //*button << func_names[ i ] << (configuration->*(funcs[i]))();
		*button << xml_token_names[ i ] << vars[i]->getInteger();
        config->addToken( button );
    }

    return config;
}

Token * CConfiguration::saveJoystick( int num, CConfiguration * configuration ){
    typedef JoystickInput (CConfiguration::*get_func)() const;
    Token * config = new Token();

    config->addToken( new Token(config_joystick_configuration, false ) );
    Token * number = new Token();
    *number << config_number;
    config->addToken( number );
    *number << num;

        const char * xml_token_names[] = {
	config_ButtonRight,
	config_ButtonLeft,
	config_ButtonUp,
	config_ButtonDown,
	config_Button1,
	config_Button2,
	config_Button3,
	config_Button4,
	config_Button5,
	config_Button6,
	config_Button7,
	config_Button8,
	config_Button9,
	config_ButtonJump,
	config_ButtonGrab,
	config_ButtonStart,
	config_ButtonSelect,
	config_ButtonDeal,
	config_ButtonBet,
	config_ButtonDoubleUP,
	config_ButtonStand,
	config_ButtonOpen,
	config_ButtonConfig,
	config_ButtonPause,
	config_ButtonReset,
	config_ButtonShowGFX,
	config_ButtonShowFPS,
	config_ButtonSaveConfig,
	config_ButtonLoadConfig,
	config_ButtonDebugger,
	config_ButtonToggleConsole,
	config_ButtonReload,
	config_ButtonCancel,
	config_ButtonQuit,
	};
/*
    get_func funcs[] = {&CConfiguration::getJoystickLeft, &CConfiguration::getJoystickRight,
                        &CConfiguration::getJoystickUp, &CConfiguration::getJoystickDown,
                        &CConfiguration::getJoystickButtonA, &CConfiguration::getJoystickButtonB,
                        &CConfiguration::getJoystickButtonC, &CConfiguration::getJoystickButtonX,
						&CConfiguration::getJoystickButtonStart//, &CConfiguration::getJoystickButtonPause
    };*/

	CLocalSysVar  *vars[] = {&ConfigList[num]->JoyButtonRight,
	&ConfigList[num]->JoyButtonLeft,
	&ConfigList[num]->JoyButtonUp,
	&ConfigList[num]->JoyButtonDown,
	&ConfigList[num]->JoyButton1,
	&ConfigList[num]->JoyButton2,
	&ConfigList[num]->JoyButton3,
	&ConfigList[num]->JoyButton4,
	&ConfigList[num]->JoyButton5,
	&ConfigList[num]->JoyButton6,
	&ConfigList[num]->JoyButton7,
	&ConfigList[num]->JoyButtonJump,
	&ConfigList[num]->JoyButtonStart,
	&ConfigList[num]->JoyButtonSelect,
	&ConfigList[num]->JoyButtonCancel,
	&ConfigList[num]->JoyButtonQuit,
	};

    for ( unsigned int i = 0; i < sizeof(xml_token_names)/sizeof(char*); i++ ){
        Token * button = new Token();
        //*button << xml_token_names[ i ] << (configuration->*(funcs[i]))();
        *button << xml_token_names[ i ] << vars[i]->getInteger();
		config->addToken( button );
    }

    return config;
}

Token * CConfiguration::saveMouse(int num, CConfiguration * configuration){
	typedef MouseInput (CConfiguration::*get_func)() const;

    Token * config = new Token();
	config->addToken( new Token(config_mouse_configuration, false ) );

    Token * number = new Token();
    *number << config_number;
    config->addToken( number );
    *number << num;

/*
    const char * func_names[] = {config_left, config_right,
		config_up, config_down ,config_buttonA, config_buttonB,
                                 config_buttonC, config_buttonX};

    get_func funcs[] = {&CConfiguration::getMouseLeft, &CConfiguration::getMouseRight,
                        &CConfiguration::getMouseUp, &CConfiguration::getMouseDown,
                        &CConfiguration::getMouseButtonA, &CConfiguration::getMouseButtonB,
                        &CConfiguration::getMouseButtonC, &CConfiguration::getMouseButtonX,
						&CConfiguration::getMouseButtonStart, &CConfiguration::getMouseButtonPause
    };
*/


    const char * xml_token_names[] = {
	config_ButtonRight,
	config_ButtonLeft,
	config_ButtonUp,
	config_ButtonDown,
	config_Button1,
	config_Button2,
	config_Button3,
	config_Button4,
	config_Button5,
	config_Button6,
	config_Button7,
	config_Button8,
	config_Button9,
	config_ButtonJump,
	config_ButtonGrab,
	config_ButtonStart,
	config_ButtonSelect,
	config_ButtonDeal,
	config_ButtonBet,
	config_ButtonDoubleUP,
	config_ButtonStand,
	config_ButtonOpen,
	config_ButtonConfig,
	config_ButtonPause,
	config_ButtonReset,
	config_ButtonShowGFX,
	config_ButtonShowFPS,
	config_ButtonSaveConfig,
	config_ButtonLoadConfig,
	config_ButtonDebugger,
	config_ButtonToggleConsole,
	config_ButtonReload,
	config_ButtonCancel,
	config_ButtonQuit,
	};
/*
    get_func funcs[] = {&CConfiguration::getJoystickLeft, &CConfiguration::getJoystickRight,
                        &CConfiguration::getJoystickUp, &CConfiguration::getJoystickDown,
                        &CConfiguration::getJoystickButtonA, &CConfiguration::getJoystickButtonB,
                        &CConfiguration::getJoystickButtonC, &CConfiguration::getJoystickButtonX,
						&CConfiguration::getJoystickButtonStart//, &CConfiguration::getJoystickButtonPause
    };*/

	CLocalSysVar  *vars[] = {&ConfigList[num]->ButtonRight,
	&ConfigList[num]->ButtonLeft,
	&ConfigList[num]->ButtonUp,
	&ConfigList[num]->ButtonDown,
	&ConfigList[num]->Button1,
	&ConfigList[num]->Button2,
	&ConfigList[num]->Button3,
	&ConfigList[num]->Button4,
	&ConfigList[num]->Button5,
	&ConfigList[num]->Button6,
	&ConfigList[num]->Button7,
	&ConfigList[num]->ButtonJump,
	&ConfigList[num]->ButtonStart,
	&ConfigList[num]->ButtonSelect,
	&ConfigList[num]->ButtonCancel,
	&ConfigList[num]->ButtonQuit,
	};
    for ( unsigned int i = 0; i < sizeof(vars)/sizeof(char*); i++ ){
        Token * button = new Token();
        //*button << func_names[ i ] << (configuration->*(funcs[i]))();
		*button << xml_token_names[ i ] << vars[i]->getInteger();
        config->addToken( button );
    }

    return config;
}

Token * CConfiguration::saveSDL(){

	SDLState_t *stateSDL = getsdlConfig() ;
	Token * config = new Token();
	config->addToken( new Token(config_sdl_configuration, false ) );
	Token * numwindows = new Token();
	*numwindows << config_number_of_windows << stateSDL->num_windows;
	 config->addToken( numwindows );
	Token * video = new Token();
	*video << config_init_video << (stateSDL->initModules.VIDEO ? 1 : 0);
	config->addToken( video );
	Token * fastevents = new Token();
	*fastevents << config_init_fastevents << (stateSDL->initModules.FASTEVENTS ? 1 : 0);
	config->addToken( fastevents );
	Token * audio = new Token();
	*audio << config_init_audio << (stateSDL->initModules.AUDIO ? 1 : 0);
	config->addToken( audio );
	Token * ttf  = new Token();
	*ttf << config_init_ttf << (stateSDL->initModules.TTF ? 1 : 0);
	config->addToken( ttf );
	Token * framerate  = new Token();
	*framerate << config_init_framerate <<(stateSDL->initModules.FRAMERATEMANAGER ? 1 : 0);
	config->addToken( framerate );
	Token * window  = new Token();
	*window << config_init_window << (stateSDL->initModules.WINDOW ? 1 : 0);
	config->addToken( window );
	Token *timer  = new Token();
	*timer << config_init_timer << (stateSDL->initModules.TIMER ? 1 : 0);
	config->addToken( timer );
	Token * joystick = new Token();
	*joystick << config_init_joystick << (stateSDL->initModules.JOYSTICK ? 1 : 0);
    config->addToken( joystick );
	Token * text = new Token();
	*text << config_init_textsupport << (stateSDL->initModules.TEXTSUPPORT ? 1 : 0);
    config->addToken( text);
	Token * network = new Token();
	*network << config_init_network << (stateSDL->initModules.NETWORK ? 1 : 0);
    config->addToken( network );
	return config;
}



void CConfiguration::sm_saveConfiguration(){
	Debug::debug( Debug::configuration,__FUNCTION__ ) <<  "BEGIN SAVING CONFIGURATION "  << endl;
	if (!save){
        return;
    }
    // head will delete all these tokens in its destructor
    Token head;
    head << config_configuration;
	int size;
	for ( size= 0; size < ConfigList.size(); size++) {

		Util::CReferenceCount<CConfiguration> configuration = ConfigList[size];
        head.addToken(saveKeyboard(size, configuration.raw()));
        head.addToken(saveJoystick(size, configuration.raw()));
		head.addToken(saveMouse(size, configuration.raw()));
    }

	head.addToken(saveSDL());
	Token * language = new Token();
	*language << config_language << CConfiguration::gameLanguage.getString();
    head.addToken( language );


	Token * menuversion = new Token();
//s	*menuversion << config_menuversion << CConfiguration::getMenuVersion();
    head.addToken( menuversion );

	Token *sound = new Token();
	*sound << config_sound << CConfiguration::volumeSound.getInteger();
    head.addToken( sound );

	Token *music = new Token();
	*music << config_music << CConfiguration::volumeMusic.getInteger();
    head.addToken( music );

    Token * speed = new Token();
	*speed << config_game_speed << CConfiguration::gameSpeed.getFloat();
    head.addToken( speed );

    Token * invincible = new Token();
//s    *invincible << config_invincible << CConfiguration::getInvincible();
    head.addToken( invincible );

    Token * fullscreen = new Token();
   *fullscreen << config_fullscreen << CConfiguration::fullScreen.getBool();
    head.addToken( fullscreen );

    Token * screen = new Token();
    *screen << config_screen_size << CConfiguration::screenWidth.getInteger()<< " " << CConfiguration::screenHeight.getInteger();
    head.addToken(screen);

/*    if (CConfiguration::getMenuFont_v1() != ""){
        Token * font = new Token();
        *font << config_menu_font << CConfiguration::getMenuFont_v1();
        head.addToken(font);
    } */
	if (CConfiguration::getMenuFont_v2() != NULL){
        // FIXME
        //
        //Token * font = new Token();
        //*font << config_menu_font << Configuration::getMenuFont();
        //head.addToken(font);

    }
    {
        Token * width = new Token();
        *width << config_menu_font_width << CConfiguration::menuFontSize.getInteger();
        head.addToken(width);
    }

    {
        Token * height = new Token();
        *height << config_menu_font_height << CConfiguration::menuFontSize.getInteger();
        head.addToken(height);
    }

    Token * mode = new Token();
    string smode;
/*s    if (CConfiguration::getPlayMode() == CConfiguration::Cooperative){
        smode = config_cooperative;
    } else if (CConfiguration::getPlayMode() == CConfiguration::FreeForAll){
        smode = config_free_for_all;
    }*/
    *mode << config_play_mode << smode;
    head.addToken(mode);

    Token * game = new Token();
    *game << config_current_game << CConfiguration::gameModDir.getString();
    head.addToken(game);

    Token * npc = new Token();
//s    *npc << config_npc_buddies << CConfiguration::getNpcBuddies();
    head.addToken( npc );
	// outras propriedades
    for (map<string, string>::iterator it = properties.begin(); it != properties.end(); it++){
        string name = (*it).first;
        string value = (*it).second;
        Token * property = new Token();
        *property << name << value;
        head.addToken(property);
    }
	// save configuration to XML File
    ofstream out( getEngineConfigFile().path().c_str(), ios::trunc | ios::out );
    if ( ! out.bad() ){
		data->toString(out, string(""));
        head.toString(out, string("") );
		out << endl;
        out.close();
    }
	Debug::debug( Debug::configuration,__FUNCTION__ ) <<  "END SAVING CONFIGURATION "  << endl;
}






static Token * getPropertyX(Token * data, const string & path){
    return data->findToken(string(config_configuration) + "/" + path);
}

template <class Out>
static Out getPropertyX(Token * data, const string & path, const Out & defaultValue){
    if (data == NULL){
        return defaultValue;
    }
    Out out;
    if (data->match(string(config_configuration) + "/" + path, out)){
        return out;
    }
    updateToken(data, string(config_configuration) + "/" + path, defaultValue);
    return defaultValue;
}

int CConfiguration::getProperty(const string & path, int defaultValue){
    return getPropertyX(data.raw(), path, defaultValue);
}

void CConfiguration::setProperty(const string & path, int value){
    updateToken(data.raw(), string(config_configuration) + "/" + path, value);
    sm_saveConfiguration();
}

void CConfiguration::setProperty(const string & path, Token * value){
    updateToken(data.raw(), string(config_configuration) + "/" + path, value);
    sm_saveConfiguration();
}

Token * CConfiguration::getProperty(const string & path){
    return getPropertyX(data.raw(),path);
}

double CConfiguration::getProperty(const string & path, double defaultValue){
    return getPropertyX(data.raw(), path, defaultValue);
}

void CConfiguration::setProperty(const string & path, double value){
    updateToken(data.raw(), string(config_configuration) + "/" + path, value);
    sm_saveConfiguration();
}

bool CConfiguration::getProperty(const string & path, bool defaultValue){
    return getPropertyX(data.raw(), path, defaultValue);
}

void CConfiguration::setProperty(const string & path, bool value){
    updateToken(data.raw(), string(config_configuration) + "/" + path, value);
    sm_saveConfiguration();
}

string CConfiguration::getProperty(const string & path, const string & defaultValue){
    return getPropertyX(data.raw(), path, defaultValue);
}

} //end SGF
