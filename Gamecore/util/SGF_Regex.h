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
#ifndef _mugen_regex_h
#define _mugen_regex_h
#include "../SGF_Config.h"
#include <string>

using namespace std;
namespace SGF {

namespace Util{
	    /* Use a new type so raw strings are not confused for regexes */
    class CRegex{
    public:
        explicit CRegex(const string & input);

        const string & get() const;
    public:
        string data;
    };
	//new
	bool matchRegex(const string & str, const CRegex & regex);
    string captureRegex(const string & str, const CRegex & regex, int capture);

	//old
    bool matchRegex(const string & str, const string & regex);
    string captureRegex(const string & str, const string & regex, int capture);
}
} //end SGF
#endif
