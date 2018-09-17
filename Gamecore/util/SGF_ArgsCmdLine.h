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

#ifndef __CMDARGS_H__
#define __CMDARGS_H__
#include "../SGF_Config.h"

namespace SGF{
/*
===============================================================================

	Command arguments.

===============================================================================
*/

class CCMDLineArgs {
public:
							CCMDLineArgs( void ) { argc = 0; }
							CCMDLineArgs( const char *text, bool keepAsStrings ) { TokenizeString( text, keepAsStrings ); }

	void					operator=( const CCMDLineArgs &args );

							// The functions that execute commands get their parameters with these functions.
	int						Argc( void ) const { return argc; }
							// Argv() will return an empty string, not NULL if arg >= argc.
	const char *			Argv( int arg ) const { return ( arg >= 0 && arg < argc ) ? argv[arg] : ""; }
							// Returns a single string containing argv(start) to argv(end)
							// escapeArgs is a fugly way to put the string back into a state ready to tokenize again
	const char *			Args( int start = 1, int end = -1, bool escapeArgs = false ) const;

							// Takes a null terminated string and breaks the string up into arg tokens.
							// Does not need to be /n terminated.
							// Set keepAsStrings to true to only seperate tokens from whitespace and comments, ignoring punctuation
	void					TokenizeString( const char *text, bool keepAsStrings );

	void					AppendArg( const char *text );
	void					Clear( void ) { argc = 0; }
	const char **			GetArgs( int *argc );

private:
	static const int		MAX_COMMAND_ARGS = 64;
	static const int		MAX_COMMAND_STRING = 2 * MAX_STRING_CHARS;

	int						argc;								// number of arguments
	char *					argv[MAX_COMMAND_ARGS];				// points into tokenized
	char					tokenized[MAX_COMMAND_STRING];		// will have 0 bytes inserted
};
} //end SGF
#endif /* !__CMDARGS_H__ */
