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
#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include <stdio.h>
using namespace std;
namespace SGF{

namespace Ast{

class  SGE_API CVariable {
public:
	CVariable(const char *n):
		name(n),
		numberIndex(0),
		stringIndex(0),
		numberIndexFlag(false),
		stringIndexFlag(false) {
	}

	CVariable(const char *n, const int index):
		name(n),
		numberIndex(index),
		stringIndex(0),
		numberIndexFlag(true),
		stringIndexFlag(false) {
	}

	CVariable (const char *n, const char *index):
		name(n),
		numberIndex(0),
		stringIndex(index),
		numberIndexFlag(false),
		stringIndexFlag(true) {
	}

	const char *getName() { return name; }
	int getNumberIndex() { return numberIndex; }
	bool hasNumberIndex() { return numberIndexFlag; }
	const char *getStringIndex() { return stringIndex; }
	bool hasStringIndex() { return stringIndexFlag; }

	void debugExplain() {
		printf("%s", name);
		if (numberIndexFlag)
			printf("(%d)", numberIndex);
		if (stringIndexFlag)
			printf("(%s)", stringIndex);
	}
private:
	const char *name;
	int numberIndex;
	const char *stringIndex;
	bool numberIndexFlag;
	bool stringIndexFlag;
};

} //end ASt
} //end SGF
#endif
