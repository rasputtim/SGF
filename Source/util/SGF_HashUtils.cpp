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

#include "util/SGF_HashUtils.h"

namespace SGF{
namespace Util{

static char ToLower( char c ) {
	if ( c <= 'Z' && c >= 'A' ) {
		return ( c + ( 'a' - 'A' ) );
	}
	return c;
}
int  getHash( const char *string ) {
	int i, hash = 0;
	for ( i = 0; *string != '\0'; i++ ) {
		hash += ( *string++ ) * ( i + 119 );
	}
	return hash;
}

int getHash( const char *string, int length ) {
	int i, hash = 0;
	for ( i = 0; i < length; i++ ) {
		hash += ( *string++ ) * ( i + 119 );
	}
	return hash;
}

int getIHash( const char *string ) {
	int i, hash = 0;
	for( i = 0; *string != '\0'; i++ ) {
		hash += ToLower( *string++ ) * ( i + 119 );
	}
	return hash;
}

int getIHash( const char *string, int length ) {
	int i, hash = 0;
	for ( i = 0; i < length; i++ ) {
		hash += ToLower( *string++ ) * ( i + 119 );
	}
	return hash;
}

	} //end Util
} //end SGF
