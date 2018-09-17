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


#include "settings.h"
#include "../Gamecore/util/SGF_Debug.h"
#include "PacGlobal.h"


extern Debug::CLog logtxt;

int CPacConfiguration::setPath(int mode,std::string str) {
    int i;

    switch (mode) {
    case MODE_LEVELS:
        for (i=0;i<lvlpathcount;i++) {
            if (lvlpath[i]=="levels/" + str + "/") {
                lvlpathcurrent=i;
                return 0;
            }
        }
        break;
        case MODE_SKINS:
        for (i=0;i<skinspathcount;i++) {
            if (skinspath[i]=="skins/" + str + "/") {
                skinspathcurrent=i;
                return 0;
            }
        }
        break;
        default:
        break;
    }

    return 1;
}

void CPacConfiguration::loadConfigurations(){

	CConfiguration::setUserConfigFile(string("data\\PacManConfig.xml"));
	//! define config parameters
	CConfiguration::registerConfigValue("configuration", "pacman_config", "level_path");
	CConfiguration::registerConfigValue("configuration", "pacman_config", "skins_path");
	CConfiguration::registerConfigValue("configuration", "level_config", "field_width");
	CConfiguration::registerConfigValue("configuration", "level_config", "field_height");
	CConfiguration::registerConfigValue("configuration", "level_config", "tile_size");
	CConfiguration::registerConfigValue("configuration", "level_config", "pac_startx");
	CConfiguration::registerConfigValue("configuration", "level_config", "pac_starty");
	CConfiguration::registerConfigValue("configuration", "level_config", "pac_speed");
	CConfiguration::registerConfigValue("configuration", "level_config", "baddie_startx");
	CConfiguration::registerConfigValue("configuration", "level_config", "baddie_starty");
	CConfiguration::registerConfigValue("configuration", "level_config", "baddie_speed");
	CConfiguration::registerConfigValue("configuration", "level_config", "baddie_iq");
	CConfiguration::registerConfigValue("configuration", "level_config", "vulnerability_duration");
	CConfiguration::registerConfigValue("configuration", "level_config", "gatex");
	CConfiguration::registerConfigValue("configuration", "level_config", "gatey");

	CConfiguration::storeConfigFunction(&pacConfCallback[level_path],"level_path");
	CConfiguration::storeConfigFunction(&pacConfCallback[skins_path],"skins_path");
	CConfiguration::storeConfigFunction(&pacConfCallback[field_width],"field_width");
	CConfiguration::storeConfigFunction(&pacConfCallback[field_height],"field_height");
	CConfiguration::storeConfigFunction(&pacConfCallback[tile_size],"tile_size");
	CConfiguration::storeConfigFunction(&pacConfCallback[pac_startx],"pac_startx");
	CConfiguration::storeConfigFunction(&pacConfCallback[pac_starty],"pac_starty");
	CConfiguration::storeConfigFunction(&pacConfCallback[pac_speed],"pac_speed");
	CConfiguration::storeConfigFunction(&pacConfCallback[baddie_startx],"baddie_startx");
	CConfiguration::storeConfigFunction(&pacConfCallback[baddie_starty],"baddie_starty");
	CConfiguration::storeConfigFunction(&pacConfCallback[baddie_speed],"baddie_speed");
	CConfiguration::storeConfigFunction(&pacConfCallback[baddie_iq],"baddie_iq");
	CConfiguration::storeConfigFunction(&pacConfCallback[vulnerability_duration],"vulnerability_duration");
	CConfiguration::storeConfigFunction(&pacConfCallback[gate_x],"gatex");
	CConfiguration::storeConfigFunction(&pacConfCallback[gate_y],"gatey");
	try{

		CConfiguration::loadUserConfigurations();
		CConfiguration::setUserConfigFile(string(lvlpath[lvlpathcurrent] + CFGFILE));
		CConfiguration::loadUserConfigurations();
		CConfiguration::setUserConfigFile(string("data\\PacManConfig.xml"));
		//loadConfigurations(CConfiguration::getUserConfigFile().path());
		//loadConfigurations( (lvlpath[lvlpathcurrent] + CFGFILE) );
     } catch ( const CLoadException & le ){
        Debug::debug( Debug::gameEngine,__FUNCTION__ )  << "Notice: Could not load configuration file " << Filesystem::getInstance().configFile().path() << ": " << le.getTrace() << endl;
    } catch ( const CTokenException & t ){
        Debug::debug( Debug::gameEngine,__FUNCTION__ ) <<  "Problem Loading Token: " << t.getTrace() << endl;
    }
}

void CPacConfiguration::loadConfigurations(std::string filename){
			CConfiguration::setUserConfigFile(filename);
		    CConfiguration::loadUserConfigurations();
			CConfiguration::setUserConfigFile(string("data\\PacManConfig.xml"));

}


CPacConfiguration::CPacConfiguration():
lvlpathcount(0),
    lvlpathcurrent( 0),
    skinspathcount(0),
    skinspathcurrent(0),
    gatex(0),
    gatey(0),
    fieldwidth(0),
    fieldheight(0),
    tilesize(0),
    pacstartx(0),
    pacstarty(0),
    pacspeed(0),
    baddiestartx(0),
    baddiestarty(0),
    baddiespeed(0),
    baddieiq(0),
    vuln_duration(0)
{


pacConfCallback[level_path].SetStringCallback(this, &CPacConfiguration::levelpathCallBack);
pacConfCallback[skins_path].SetStringCallback(this, &CPacConfiguration::skinspathCallBack);
pacConfCallback[field_width].SetStringCallback(this, &CPacConfiguration::fieldwidthCallBack);
pacConfCallback[field_height].SetStringCallback(this, &CPacConfiguration::fieldheightCallBack);
pacConfCallback[tile_size].SetStringCallback(this, &CPacConfiguration::tilesizeCallBack);
pacConfCallback[pac_startx].SetStringCallback(this, &CPacConfiguration::pacstartxCallBack);
pacConfCallback[pac_starty].SetStringCallback(this, &CPacConfiguration::pacstartyCallBack);
pacConfCallback[pac_speed].SetStringCallback(this, &CPacConfiguration::pacspeedCallBack);
pacConfCallback[baddie_startx].SetStringCallback(this, &CPacConfiguration::baddiestartxCallBack);
pacConfCallback[baddie_starty].SetStringCallback(this, &CPacConfiguration::baddiestartyCallBack);
pacConfCallback[baddie_speed].SetStringCallback(this, &CPacConfiguration::baddiespeedCallBack);
pacConfCallback[baddie_iq].SetStringCallback(this, &CPacConfiguration::baddieiqCallBack);
pacConfCallback[vulnerability_duration].SetStringCallback(this, &CPacConfiguration::vuln_durationCallBack);
pacConfCallback[gate_x].SetStringCallback(this, &CPacConfiguration::gatexCallBack);
pacConfCallback[gate_y].SetStringCallback(this, &CPacConfiguration::gateyCallBack);



}

CPacConfiguration::~CPacConfiguration() {}

//----------call back functions

void CPacConfiguration::skinspathCallBack(std::string &stringParam){
	Debug::debug( Debug::configuration,__FUNCTION__ ) << "CALL BACK RODANDO - PARAM: "<< stringParam << endl;
	skinspath.push_back("skins/" + stringParam + "/");
	skinspathcount++;
}
void CPacConfiguration::levelpathCallBack(std::string &stringParam){
	Debug::debug( Debug::configuration,__FUNCTION__ ) << "CALL BACK RODANDO - PARAM: "<< stringParam << endl;
	lvlpath.push_back("levels/" + stringParam + "/");
	lvlpathcount++;
}

void CPacConfiguration::fieldwidthCallBack(std::string &stringParam){
	Debug::debug( Debug::configuration,__FUNCTION__ ) << "CALL BACK RODANDO - PARAM: "<< stringParam << endl;
	fieldwidth=atoi(stringParam.c_str());
}
void CPacConfiguration::fieldheightCallBack(std::string &stringParam){
	Debug::debug( Debug::configuration,__FUNCTION__ ) << "CALL BACK RODANDO - PARAM: "<< stringParam << endl;
	fieldheight=atoi(stringParam.c_str());
}
void CPacConfiguration::tilesizeCallBack(std::string &stringParam){
	Debug::debug( Debug::configuration,__FUNCTION__ ) << "CALL BACK RODANDO - PARAM: "<< stringParam << endl;
	tilesize=atoi(stringParam.c_str());
}
void CPacConfiguration::pacstartxCallBack(std::string &stringParam){
	Debug::debug( Debug::configuration,__FUNCTION__ ) << "CALL BACK RODANDO - PARAM: "<< stringParam << endl;
	pacstartx=atoi(stringParam.c_str());
}
void CPacConfiguration::pacstartyCallBack(std::string &stringParam){
	Debug::debug( Debug::configuration,__FUNCTION__ ) << "CALL BACK RODANDO - PARAM: "<< stringParam << endl;

	pacstarty=atoi(stringParam.c_str());
}
void CPacConfiguration::pacspeedCallBack(std::string &stringParam){
	Debug::debug( Debug::configuration,__FUNCTION__ ) << "CALL BACK RODANDO - PARAM: "<< stringParam << endl;
	pacspeed=atoi(stringParam.c_str());
}
void CPacConfiguration::baddiestartxCallBack(std::string &stringParam){
	Debug::debug( Debug::configuration,__FUNCTION__ ) << "CALL BACK RODANDO - PARAM: "<< stringParam << endl;
	baddiestartx=atoi(stringParam.c_str());
}
void CPacConfiguration::baddiestartyCallBack(std::string &stringParam){
	Debug::debug( Debug::configuration,__FUNCTION__ ) << "CALL BACK RODANDO - PARAM: "<< stringParam << endl;
	baddiestarty=atoi(stringParam.c_str());
}
void CPacConfiguration::baddiespeedCallBack(std::string &stringParam){
	Debug::debug( Debug::configuration,__FUNCTION__ ) << "CALL BACK RODANDO - PARAM: "<< stringParam << endl;
	baddiespeed=atoi(stringParam.c_str());
}
void CPacConfiguration::baddieiqCallBack(std::string &stringParam){
	Debug::debug( Debug::configuration,__FUNCTION__ ) << "CALL BACK RODANDO - PARAM: "<< stringParam << endl;
	baddieiq=atoi(stringParam.c_str());
}
void CPacConfiguration::vuln_durationCallBack(std::string &stringParam){
	Debug::debug( Debug::configuration,__FUNCTION__ ) << "CALL BACK RODANDO - PARAM: "<< stringParam << endl;
	vuln_duration=atoi(stringParam.c_str());
}
void CPacConfiguration::gatexCallBack(std::string &stringParam){
	Debug::debug( Debug::configuration,__FUNCTION__ ) << "CALL BACK RODANDO - PARAM: "<< stringParam << endl;
	gatex=atoi(stringParam.c_str());

}
void CPacConfiguration::gateyCallBack(std::string &stringParam){
	Debug::debug( Debug::configuration,__FUNCTION__ ) << "CALL BACK RODANDO - PARAM: "<< stringParam << endl;

gatey=atoi(stringParam.c_str());
}
