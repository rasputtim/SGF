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


#ifndef _PAC_SETTINGS_H_
#define _PAC_SETTINGS_H_
#include <vector>
#include "../Gamecore/configuration/SGF_Configuration.h"


class CConfiguration;

class CPacConfiguration :public CConfiguration{
public:

	enum configOption{
		level_path,
		skins_path,
		field_width,
		field_height,
		tile_size,
		pac_startx,
		pac_starty,
		pac_speed,
		baddie_startx,
		baddie_starty,
		baddie_speed,
		baddie_iq,
		vulnerability_duration,
		gate_x,
		gate_y
	};
    CPacConfiguration();
    ~CPacConfiguration();
	void loadConfigurations(std::string filename);
    void loadConfigurations();
    //searches for str in level/skinspaths; if successful, sets currently selected path.
    //returns 0 on success, 1 on failure
    int setPath(int mode,std::string str);

    //////////////////////////////
    // VARIABLES	- APP
    //////////////////////////////
    //int
      //      width,
      //      height;

	//////////////////////////////
	//  CALLBAC FUNCTIONS       //
	/////////////////////////////
	void skinspathCallBack(std::string &stringParam);
	void levelpathCallBack(std::string &stringParam);
	void fieldwidthCallBack(std::string &stringParam);
	void fieldheightCallBack(std::string &stringParam);
	void tilesizeCallBack(std::string &stringParam);
	void pacstartxCallBack(std::string &stringParam);
	void pacstartyCallBack(std::string &stringParam);
	void pacspeedCallBack(std::string &stringParam);
	void baddiestartxCallBack(std::string &stringParam);
	void baddiestartyCallBack(std::string &stringParam);
	void baddiespeedCallBack(std::string &stringParam);
	void baddieiqCallBack(std::string &stringParam);
	void vuln_durationCallBack(std::string &stringParam);
	void gatexCallBack(std::string &stringParam);
	void gateyCallBack(std::string &stringParam);
    //////////////////////////////
    // VARIABLES	- GAME
    //////////////////////////////

    int
            fieldwidth,
            fieldheight,
            tilesize,
            gatex,
            gatey,
            pacstartx,
            pacstarty,
            pacspeed,
            baddiestartx,
            baddiestarty,
            baddiespeed,
            baddieiq,
            vuln_duration,

            lvlpathcount,
            lvlpathcurrent,
            skinspathcount,
            skinspathcurrent;

    std::vector<std::string>
            lvlpath,
            skinspath;
private:
	CCallback<CPacConfiguration> pacConfCallback[20];
};


#endif
