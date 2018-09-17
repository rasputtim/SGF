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
#ifndef _MODIFIER_H_
#define _MODIFIER_H_

using namespace std;
namespace SGF{

namespace Ast{

class  SGE_API CModifier {
public:
	CModifier(const char m, const int c):
		modifierChar(m),
		count(c) {}

	char getModifierChar() { return modifierChar; }
	int getCount() { return count; }

private:
	char modifierChar;
	int count;
};

} //end ASt
} //end SGF

#endif
