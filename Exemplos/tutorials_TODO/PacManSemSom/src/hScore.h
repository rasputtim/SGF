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

#pragma once

#include <string>
#include <fstream>
#include <iomanip>

#define MAXENTRIES 8


class hScore
{
private:
    std::string
            name[MAXENTRIES];
    unsigned long
            score[MAXENTRIES];
    char
            filename[20];
public:
    hScore();
    ~hScore();

    void add(std::string, unsigned int);

    std::string getName(int);

    int getScore(int);

    int save();
    int load();
    void clear();

    bool onlist(unsigned int) const;

    void setfilename(std::string fn);
};
