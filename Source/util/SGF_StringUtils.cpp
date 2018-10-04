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


//#include "precompiled.h"
//#pragma hdrstop
#include "util/SGF_StringUtils.h"
#include "math/all.h"
#include "util/SGF_Debug.h"
#include <stdio.h>
#include <stdarg.h>


namespace SGF{

#if !defined( ID_REDIRECT_NEWDELETE ) && !defined( MACOS_X )
	//#define USE_STRING_DATA_ALLOCATOR
#endif

#ifdef USE_STRING_DATA_ALLOCATOR
static CDynamicBlockAlloc<char, 1<<18, 128>	stringDataAllocator;
#endif

CVector4D	g_color_table[16] =
{
	CVector4D(0.0f, 0.0f, 0.0f, 1.0f),
	CVector4D(1.0f, 0.0f, 0.0f, 1.0f), // S_COLOR_RED
	CVector4D(0.0f, 1.0f, 0.0f, 1.0f), // S_COLOR_GREEN
	CVector4D(1.0f, 1.0f, 0.0f, 1.0f), // S_COLOR_YELLOW
	CVector4D(0.0f, 0.0f, 1.0f, 1.0f), // S_COLOR_BLUE
	CVector4D(0.0f, 1.0f, 1.0f, 1.0f), // S_COLOR_CYAN
	CVector4D(1.0f, 0.0f, 1.0f, 1.0f), // S_COLOR_MAGENTA
	CVector4D(1.0f, 1.0f, 1.0f, 1.0f), // S_COLOR_WHITE
	CVector4D(0.5f, 0.5f, 0.5f, 1.0f), // S_COLOR_GRAY
	CVector4D(0.0f, 0.0f, 0.0f, 1.0f), // S_COLOR_BLACK
	CVector4D(0.0f, 0.0f, 0.0f, 1.0f),
	CVector4D(0.0f, 0.0f, 0.0f, 1.0f),
	CVector4D(0.0f, 0.0f, 0.0f, 1.0f),
	CVector4D(0.0f, 0.0f, 0.0f, 1.0f),
	CVector4D(0.0f, 0.0f, 0.0f, 1.0f),
	CVector4D(0.0f, 0.0f, 0.0f, 1.0f),
};

const char *units[2][4] =
{
	{ "B", "KB", "MB", "GB" },
	{ "B/s", "KB/s", "MB/s", "GB/s" }
};

/*
============
CMyString::ColorForIndex
============
*/
CVector4D & CMyString::ColorForIndex( int i ) {
	return g_color_table[ i & 15 ];
}

/**
\brief realocate the memory buffer
\param ammount: amount of memory to alocate
\param keepold: keep old buffer
**/
void CMyString::reAllocate( int amount, bool keepold ) {
	char	*newbuffer;
	int		newsize;
	int		mod;

	//assert( m_pData );
	assert( amount > 0 );

	mod = amount % STR_ALLOC_GRAN;
	if ( !mod ) {
		newsize = amount;
	}
	else {
		newsize = amount + STR_ALLOC_GRAN - mod;
	}
	m_iAllocated = newsize;

#ifdef USE_STRING_DATA_ALLOCATOR
	newbuffer = stringDataAllocator.Alloc( m_iAllocated );
#else
	newbuffer = new char[ m_iAllocated ];
#endif
	if ( keepold && m_pData ) {
		m_pData[ m_iLen ] = '\0';
		strcpy( newbuffer, m_pData );
	}

	if ( m_pData && m_pData != m_cBaseBuffer ) {
#ifdef USE_STRING_DATA_ALLOCATOR
		stringDataAllocator.Free( m_pData );
#else
		delete [] m_pData;
#endif
	}

	m_pData = newbuffer;
}

/**
\brief free allocated string memory 
**/
void CMyString::freeData() {
	if ( m_pData && m_pData != m_cBaseBuffer ) {
#ifdef USE_STRING_DATA_ALLOCATOR
		stringDataAllocator.Free( m_pData );
#else
		delete[] m_pData;
#endif
		m_pData = m_cBaseBuffer;
	}
}

/*
============
CMyString::operator=
============
*/
void CMyString::operator=( const char *text ) {
	int l;
	int diff;
	int i;

	if ( !text ) {
		// safe behaviour if NULL
		ensureAlloced( 1, false );
		m_pData[ 0 ] = '\0';
		m_iLen = 0;
		return;
	}

	if ( text == m_pData ) {
		return; // copying same thing
	}

	// check if we're aliasing
	if ( text >= m_pData && text <= m_pData + m_iLen ) {
		diff = text - m_pData;

		assert( strlen( text ) < (unsigned)m_iLen );

		for ( i = 0; text[ i ]; i++ ) {
			m_pData[ i ] = text[ i ];
		}

		m_pData[ i ] = '\0';

		m_iLen -= diff;

		return;
	}

	l = strlen( text );
	ensureAlloced( l + 1, false );
	strcpy( m_pData, text );
	m_iLen = l;
}

/*
============
CMyString::FindChar

returns -1 if not found otherwise the index of the char
============
*/
int CMyString::FindChar( const char *str, const char c, int start, int end ) {
	int i;

	if ( end == -1 ) {
		end = strlen( str ) - 1;
	}
	for ( i = start; i <= end; i++ ) {
		if ( str[i] == c ) {
			return i;
		}
	}
	return -1;
}

/*
============
CMyString::FindText

returns -1 if not found otherwise the index of the text
============
*/
int CMyString::FindText( const char *str, const char *text, bool casesensitive, int start, int end ) {
	int l, i, j;

	if ( end == -1 ) {
		end = strlen( str );
	}
	l = end - strlen( text );
	for ( i = start; i <= l; i++ ) {
		if ( casesensitive ) {
			for ( j = 0; text[j]; j++ ) {
				if ( str[i+j] != text[j] ) {
					break;
				}
			}
		} else {
			for ( j = 0; text[j]; j++ ) {
				if ( ::toupper( str[i+j] ) != ::toupper( text[j] ) ) {
					break;
				}
			}
		}
		if ( !text[j] ) {
			return i;
		}
	}
	return -1;
}

/*
============
CMyString::Filter

Returns true if the string conforms the given filter.
Several metacharacter may be used in the filter.

*          match any string of zero or more characters
?          match any single character
[abc...]   match any of the enclosed characters; a hyphen can
           be used to specify a range (e.g. a-z, A-Z, 0-9)

============
*/
bool CMyString::Filter( const char *filter, const char *name, bool casesensitive ) {
	CMyString buf;
	int i, found, index;

	while(*filter) {
		if (*filter == '*') {
			filter++;
			buf.Empty();
			for (i = 0; *filter; i++) {
				if ( *filter == '*' || *filter == '?' || (*filter == '[' && *(filter+1) != '[') ) {
					break;
				}
				buf += *filter;
				if ( *filter == '[' ) {
					filter++;
				}
				filter++;
			}
			if ( buf.Length() ) {
				index = CMyString(name).Find( buf.c_str(), casesensitive );
				if ( index == -1 ) {
					return false;
				}
				name += index + strlen(buf);
			}
		}
		else if (*filter == '?') {
			filter++;
			name++;
		}
		else if (*filter == '[') {
			if ( *(filter+1) == '[' ) {
				if ( *name != '[' ) {
					return false;
				}
				filter += 2;
				name++;
			}
			else {
				filter++;
				found = false;
				while(*filter && !found) {
					if (*filter == ']' && *(filter+1) != ']') {
						break;
					}
					if (*(filter+1) == '-' && *(filter+2) && (*(filter+2) != ']' || *(filter+3) == ']')) {
						if (casesensitive) {
							if (*name >= *filter && *name <= *(filter+2)) {
								found = true;
							}
						}
						else {
							if ( ::toupper(*name) >= ::toupper(*filter) && ::toupper(*name) <= ::toupper(*(filter+2)) ) {
								found = true;
							}
						}
						filter += 3;
					}
					else {
						if (casesensitive) {
							if (*filter == *name) {
								found = true;
							}
						}
						else {
							if ( ::toupper(*filter) == ::toupper(*name) ) {
								found = true;
							}
						}
						filter++;
					}
				}
				if (!found) {
					return false;
				}
				while(*filter) {
					if ( *filter == ']' && *(filter+1) != ']' ) {
						break;
					}
					filter++;
				}
				filter++;
				name++;
			}
		}
		else {
			if (casesensitive) {
				if (*filter != *name) {
					return false;
				}
			}
			else {
				if ( ::toupper(*filter) != ::toupper(*name) ) {
					return false;
				}
			}
			filter++;
			name++;
		}
	}
	return true;
}

/*
=============
CMyString::StripMediaName

  makes the string lower case, replaces backslashes with forward slashes, and removes extension
=============
*/
void CMyString::StripMediaName( const char *name, CMyString &mediaName ) {
	char c;

	mediaName.Empty();

	for ( c = *name; c; c = *(++name) ) {
		// truncate at an extension
		if ( c == '.' ) {
			break;
		}
		// convert backslashes to forward slashes
		if ( c == '\\' ) {
			mediaName.Append( '/' );
		} else {
			mediaName.Append( CMyString::ToLower( c ) );
		}
	}
}

/*
=============
CMyString::CheckExtension
=============
*/
bool CMyString::CheckExtension( const char *name, const char *ext ) {
	const char *s1 = name + Length( name ) - 1;
	const char *s2 = ext + Length( ext ) - 1;
	int c1, c2, d;

	do {
		c1 = *s1--;
		c2 = *s2--;

		d = c1 - c2;
		while( d ) {
			if ( c1 <= 'Z' && c1 >= 'A' ) {
				d += ('a' - 'A');
				if ( !d ) {
					break;
				}
			}
			if ( c2 <= 'Z' && c2 >= 'A' ) {
				d -= ('a' - 'A');
				if ( !d ) {
					break;
				}
			}
			return false;
		}
	} while( s1 > name && s2 > ext );

	return ( s1 >= name );
}

/*
=============
CMyString::FloatArrayToString
=============
*/
const char *CMyString::FloatArrayToString( const float *array, const int length, const int precision ) {
	static int index = 0;
	static char str[4][16384];	// in case called by nested functions
	int i, n;
	char format[16], *s;

	// use an array of string so that multiple calls won't collide
	s = str[ index ];
	index = (index + 1) & 3;

	CMyString::snPrintf( format, sizeof( format ), "%%.%df", precision );
	n = CMyString::snPrintf( s, sizeof( str[0] ), format, array[0] );
	if ( precision > 0 ) {
		while( n > 0 && s[n-1] == '0' ) s[--n] = '\0';
		while( n > 0 && s[n-1] == '.' ) s[--n] = '\0';
	}
	CMyString::snPrintf( format, sizeof( format ), " %%.%df", precision );
	for ( i = 1; i < length; i++ ) {
		n += CMyString::snPrintf( s + n, sizeof( str[0] ) - n, format, array[i] );
		if ( precision > 0 ) {
			while( n > 0 && s[n-1] == '0' ) s[--n] = '\0';
			while( n > 0 && s[n-1] == '.' ) s[--n] = '\0';
		}
	}
	return s;
}

/*
============
CMyString::Last

returns -1 if not found otherwise the index of the char
============
*/
int CMyString::Last( const char c ) const {
	int i;

	for( i = Length(); i > 0; i-- ) {
		if ( m_pData[ i - 1 ] == c ) {
			return i - 1;
		}
	}

	return -1;
}

/*
============
CMyString::StripLeading
============
*/
void CMyString::StripLeading( const char c ) {
	while( m_pData[ 0 ] == c ) {
		memmove( &m_pData[ 0 ], &m_pData[ 1 ], m_iLen );
		m_iLen--;
	}
}

/*
============
CMyString::StripLeading
============
*/
void CMyString::StripLeading( const char *string ) {
	int l;

	l = strlen( string );
	if ( l > 0 ) {
		while ( !Cmpn( string, l ) ) {
			memmove( m_pData, m_pData + l, m_iLen - l + 1 );
			m_iLen -= l;
		}
	}
}

/*
============
CMyString::StripLeadingOnce
============
*/
bool CMyString::StripLeadingOnce( const char *string ) {
	int l;

	l = strlen( string );
	if ( ( l > 0 ) && !Cmpn( string, l ) ) {
		memmove( m_pData, m_pData + l, m_iLen - l + 1 );
		m_iLen -= l;
		return true;
	}
	return false;
}

/*
============
CMyString::StripTrailing
============
*/
void CMyString::StripTrailing( const char c ) {
	int i;

	for( i = Length(); i > 0 && m_pData[ i - 1 ] == c; i-- ) {
		m_pData[ i - 1 ] = '\0';
		m_iLen--;
	}
}

/*
============
CMyString::StripLeading
============
*/
void CMyString::StripTrailing( const char *string ) {
	int l;

	l = strlen( string );
	if ( l > 0 ) {
		while ( ( m_iLen >= l ) && !Cmpn( string, m_pData + m_iLen - l, l ) ) {
			m_iLen -= l;
			m_pData[m_iLen] = '\0';
		}
	}
}

/*
============
CMyString::StripTrailingOnce
============
*/
bool CMyString::StripTrailingOnce( const char *string ) {
	int l;

	l = strlen( string );
	if ( ( l > 0 ) && ( m_iLen >= l ) && !Cmpn( string, m_pData + m_iLen - l, l ) ) {
		m_iLen -= l;
		m_pData[m_iLen] = '\0';
		return true;
	}
	return false;
}

/*
============
CMyString::Replace
============
*/
void CMyString::Replace( const char *old, const char *nw ) {
	int		oldLen, newLen, i, j, count;
	CMyString	oldString( m_pData );

	oldLen = strlen( old );
	newLen = strlen( nw );

	// Work out how big the new string will be
	count = 0;
	for( i = 0; i < oldString.Length(); i++ ) {
		if( !CMyString::Cmpn( &oldString[i], old, oldLen ) ) {
			count++;
			i += oldLen - 1;
		}
	}

	if( count ) {
		ensureAlloced( m_iLen + ( ( newLen - oldLen ) * count ) + 2, false );

		// Replace the old data with the new data
		for( i = 0, j = 0; i < oldString.Length(); i++ ) {
			if( !CMyString::Cmpn( &oldString[i], old, oldLen ) ) {
				memcpy( m_pData + j, nw, newLen );
				i += oldLen - 1;
				j += newLen;
			} else {
				m_pData[j] = oldString[i];
				j++;
			}
		}
		m_pData[j] = 0;
		m_iLen = strlen( m_pData );
	}
}

/*
============
CMyString::Mid
============
*/
const char *CMyString::Mid( int start, int len, CMyString &result ) const {
	int i;

	result.Empty();

	i = Length();
	if ( i == 0 || len <= 0 || start >= i ) {
		return NULL;
	}

	if ( start + len >= i ) {
		len = i - start;
	}

	result.Append( &m_pData[ start ], len );
	return result;
}

/*
============
CMyString::Mid
============
*/
CMyString CMyString::Mid( int start, int len ) const {
	int i;
	CMyString result;

	i = Length();
	if ( i == 0 || len <= 0 || start >= i ) {
		return result;
	}

	if ( start + len >= i ) {
		len = i - start;
	}

	result.Append( &m_pData[ start ], len );
	return result;
}

/*
============
CMyString::StripTrailingWhitespace
============
*/
void CMyString::StripTrailingWhitespace( void ) {
	int i;

	// cast to unsigned char to prevent stripping off high-ASCII characters
	for( i = Length(); i > 0 && (unsigned char)(m_pData[ i - 1 ]) <= ' '; i-- ) {
		m_pData[ i - 1 ] = '\0';
		m_iLen--;
	}
}

/*
============
CMyString::StripQuotes

Removes the quotes from the beginning and end of the string
============
*/
CMyString& CMyString::StripQuotes ( void )
{
	if ( m_pData[0] != '\"' )
	{
		return *this;
	}

	// Remove the trailing quote first
	if ( m_pData[m_iLen-1] == '\"' )
	{
		m_pData[m_iLen-1] = '\0';
		m_iLen--;
	}

	// Strip the leading quote now
	m_iLen--;
	memmove( &m_pData[ 0 ], &m_pData[ 1 ], m_iLen );
	m_pData[m_iLen] = '\0';

	return *this;
}

/*
=====================================================================

  filename methods

=====================================================================
*/

/*
============
CMyString::FileNameHash
============
*/
int CMyString::FileNameHash( void ) const {
	int		i;
	long	hash;
	char	letter;

	hash = 0;
	i = 0;
	while( m_pData[i] != '\0' ) {
		letter = CMyString::ToLower( m_pData[i] );
		if ( letter == '.' ) {
			break;				// don't include extension
		}
		if ( letter =='\\' ) {
			letter = '/';
		}
		hash += (long)(letter)*(i+119);
		i++;
	}
	hash &= (FILE_HASH_SIZE-1);
	return hash;
}

/*
============
CMyString::BackSlashesToSlashes
============
*/
CMyString &CMyString::BackSlashesToSlashes( void ) {
	int i;

	for ( i = 0; i < m_iLen; i++ ) {
		if ( m_pData[ i ] == '\\' ) {
			m_pData[ i ] = '/';
		}
	}
	return *this;
}

/*
============
CMyString::SetFileExtension
============
*/
CMyString &CMyString::SetFileExtension( const char *extension ) {
	StripFileExtension();
	if ( *extension != '.' ) {
		Append( '.' );
	}
	Append( extension );
	return *this;
}

/*
============
CMyString::StripFileExtension
============
*/
CMyString &CMyString::StripFileExtension( void ) {
	int i;

	for ( i = m_iLen-1; i >= 0; i-- ) {
		if ( m_pData[i] == '.' ) {
			m_pData[i] = '\0';
			m_iLen = i;
			break;
		}
	}
	return *this;
}

/*
============
CMyString::StripAbsoluteFileExtension
============
*/
CMyString &CMyString::StripAbsoluteFileExtension( void ) {
	int i;

	for ( i = 0; i < m_iLen; i++ ) {
		if ( m_pData[i] == '.' ) {
			m_pData[i] = '\0';
			m_iLen = i;
			break;
		}
	}

	return *this;
}

/*
==================
CMyString::DefaultFileExtension
==================
*/
CMyString &CMyString::DefaultFileExtension( const char *extension ) {
	int i;

	// do nothing if the string already has an extension
	for ( i = m_iLen-1; i >= 0; i-- ) {
		if ( m_pData[i] == '.' ) {
			return *this;
		}
	}
	if ( *extension != '.' ) {
		Append( '.' );
	}
	Append( extension );
	return *this;
}

/*
==================
CMyString::DefaultPath
==================
*/
CMyString &CMyString::DefaultPath( const char *basepath ) {
	if ( ( ( *this )[ 0 ] == '/' ) || ( ( *this )[ 0 ] == '\\' ) ) {
		// absolute path location
		return *this;
	}

	*this = basepath + *this;
	return *this;
}

/*
====================
CMyString::AppendPath
====================
*/
void CMyString::AppendPath( const char *text ) {
	int pos;
	int i = 0;

	if ( text && text[i] ) {
		pos = m_iLen;
		ensureAlloced( m_iLen + strlen( text ) + 2 );

		if ( pos ) {
			if ( m_pData[ pos-1 ] != '/' ) {
				m_pData[ pos++ ] = '/';
			}
		}
		if ( text[i] == '/' ) {
			i++;
		}

		for ( ; text[ i ]; i++ ) {
			if ( text[ i ] == '\\' ) {
				m_pData[ pos++ ] = '/';
			} else {
				m_pData[ pos++ ] = text[ i ];
			}
		}
		m_iLen = pos;
		m_pData[ pos ] = '\0';
	}
}

/*
==================
CMyString::StripFilename
==================
*/
CMyString &CMyString::StripFilename( void ) {
	int pos;

	pos = Length() - 1;
	while( ( pos > 0 ) && ( ( *this )[ pos ] != '/' ) && ( ( *this )[ pos ] != '\\' ) ) {
		pos--;
	}

	if ( pos < 0 ) {
		pos = 0;
	}

	CapLength( pos );
	return *this;
}

/*
==================
CMyString::StripPath
==================
*/
CMyString &CMyString::StripPath( void ) {
	int pos;

	pos = Length();
	while( ( pos > 0 ) && ( ( *this )[ pos - 1 ] != '/' ) && ( ( *this )[ pos - 1 ] != '\\' ) ) {
		pos--;
	}

	*this = Right( Length() - pos );
	return *this;
}

/*
====================
CMyString::ExtractFilePath
====================
*/
void CMyString::ExtractFilePath( CMyString &dest ) const {
	int pos;

	//
	// back up until a \ or the start
	//
	pos = Length();
	while( ( pos > 0 ) && ( ( *this )[ pos - 1 ] != '/' ) && ( ( *this )[ pos - 1 ] != '\\' ) ) {
		pos--;
	}

	Left( pos, dest );
}

/*
====================
CMyString::ExtractFileName
====================
*/
void CMyString::ExtractFileName( CMyString &dest ) const {
	int pos;

	//
	// back up until a \ or the start
	//
	pos = Length() - 1;
	while( ( pos > 0 ) && ( ( *this )[ pos - 1 ] != '/' ) && ( ( *this )[ pos - 1 ] != '\\' ) ) {
		pos--;
	}

	Right( Length() - pos, dest );
}

/*
====================
CMyString::ExtractFileBase
====================
*/
void CMyString::ExtractFileBase( CMyString &dest ) const {
	int pos;
	int start;

	//
	// back up until a \ or the start
	//
	pos = Length() - 1;
	while( ( pos > 0 ) && ( ( *this )[ pos - 1 ] != '/' ) && ( ( *this )[ pos - 1 ] != '\\' ) ) {
		pos--;
	}

	start = pos;
	while( ( pos < Length() ) && ( ( *this )[ pos ] != '.' ) ) {
		pos++;
	}

	Mid( start, pos - start, dest );
}

/*
====================
CMyString::ExtractFileExtension
====================
*/
void CMyString::ExtractFileExtension( CMyString &dest ) const {
	int pos;

	//
	// back up until a . or the start
	//
	pos = Length() - 1;
	while( ( pos > 0 ) && ( ( *this )[ pos - 1 ] != '.' ) ) {
		pos--;
	}

	if ( !pos ) {
		// no extension
		dest.Empty();
	} else {
		Right( Length() - pos, dest );
	}
}


/*
=====================================================================

  char * methods to replace library functions

=====================================================================
*/

/*
============
CMyString::IsNumeric

Checks a string to see if it contains only numerical values.
============
*/
bool CMyString::IsNumeric( const char *s ) {
	int		i;
	bool	dot;

	if ( *s == '-' ) {
		s++;
	}

	dot = false;
	for ( i = 0; s[i]; i++ ) {
		if ( !isdigit( s[i] ) ) {
			if ( ( s[ i ] == '.' ) && !dot ) {
				dot = true;
				continue;
			}
			return false;
		}
	}

	return true;
}

/*
============
CMyString::HasLower

Checks if a string has any lowercase chars
============
*/
bool CMyString::HasLower( const char *s ) {
	if ( !s ) {
		return false;
	}

	while ( *s ) {
		if ( CharIsLower( *s ) ) {
			return true;
		}
		s++;
	}

	return false;
}

/*
============
CMyString::HasUpper

Checks if a string has any uppercase chars
============
*/
bool CMyString::HasUpper( const char *s ) {
	if ( !s ) {
		return false;
	}

	while ( *s ) {
		if ( CharIsUpper( *s ) ) {
			return true;
		}
		s++;
	}

	return false;
}

/*
================
CMyString::Cmp
================
*/
int CMyString::Cmp( const char *s1, const char *s2 ) {
	int c1, c2, d;

	do {
		c1 = *s1++;
		c2 = *s2++;

		d = c1 - c2;
		if ( d ) {
			return ( INTSIGNBITNOTSET( d ) << 1 ) - 1;
		}
	} while( c1 );

	return 0;		// strings are equal
}

/*
================
CMyString::Cmpn
================
*/
int CMyString::Cmpn( const char *s1, const char *s2, int n ) {
	int c1, c2, d;

	assert( n >= 0 );

	do {
		c1 = *s1++;
		c2 = *s2++;

		if ( !n-- ) {
			return 0;		// strings are equal until end point
		}

		d = c1 - c2;
		if ( d ) {
			return ( INTSIGNBITNOTSET( d ) << 1 ) - 1;
		}
	} while( c1 );

	return 0;		// strings are equal
}

/*
================
CMyString::Icmp
================
*/
int CMyString::Icmp( const char *s1, const char *s2 ) {
	int c1, c2, d;

	do {
		c1 = *s1++;
		c2 = *s2++;

		d = c1 - c2;
		while( d ) {
			if ( c1 <= 'Z' && c1 >= 'A' ) {
				d += ('a' - 'A');
				if ( !d ) {
					break;
				}
			}
			if ( c2 <= 'Z' && c2 >= 'A' ) {
				d -= ('a' - 'A');
				if ( !d ) {
					break;
				}
			}
			return ( INTSIGNBITNOTSET( d ) << 1 ) - 1;
		}
	} while( c1 );

	return 0;		// strings are equal
}

/*
================
CMyString::Icmpn
================
*/
int CMyString::Icmpn( const char *s1, const char *s2, int n ) {
	int c1, c2, d;

	assert( n >= 0 );

	do {
		c1 = *s1++;
		c2 = *s2++;

		if ( !n-- ) {
			return 0;		// strings are equal until end point
		}

		d = c1 - c2;
		while( d ) {
			if ( c1 <= 'Z' && c1 >= 'A' ) {
				d += ('a' - 'A');
				if ( !d ) {
					break;
				}
			}
			if ( c2 <= 'Z' && c2 >= 'A' ) {
				d -= ('a' - 'A');
				if ( !d ) {
					break;
				}
			}
			return ( INTSIGNBITNOTSET( d ) << 1 ) - 1;
		}
	} while( c1 );

	return 0;		// strings are equal
}

/*
================
CMyString::Icmp
================
*/
int CMyString::IcmpNoColor( const char *s1, const char *s2 ) {
	int c1, c2, d;

	do {
		while ( CMyString::IsColor( s1 ) ) {
			s1 += 2;
		}
		while ( CMyString::IsColor( s2 ) ) {
			s2 += 2;
		}
		c1 = *s1++;
		c2 = *s2++;

		d = c1 - c2;
		while( d ) {
			if ( c1 <= 'Z' && c1 >= 'A' ) {
				d += ('a' - 'A');
				if ( !d ) {
					break;
				}
			}
			if ( c2 <= 'Z' && c2 >= 'A' ) {
				d -= ('a' - 'A');
				if ( !d ) {
					break;
				}
			}
			return ( INTSIGNBITNOTSET( d ) << 1 ) - 1;
		}
	} while( c1 );

	return 0;		// strings are equal
}

/*
================
CMyString::IcmpPath
================
*/
int CMyString::IcmpPath( const char *s1, const char *s2 ) {
	int c1, c2, d;

#if 0
//#if !defined( _WIN32 )
	Debug::debug(Debug::math,__FUNCTION__) << "WARNING: IcmpPath used on a case-sensitive filesystem?\n" );
#endif

	do {
		c1 = *s1++;
		c2 = *s2++;

		d = c1 - c2;
		while( d ) {
			if ( c1 <= 'Z' && c1 >= 'A' ) {
				d += ('a' - 'A');
				if ( !d ) {
					break;
				}
			}
			if ( c1 == '\\' ) {
				d += ('/' - '\\');
				if ( !d ) {
					break;
				}
			}
			if ( c2 <= 'Z' && c2 >= 'A' ) {
				d -= ('a' - 'A');
				if ( !d ) {
					break;
				}
			}
			if ( c2 == '\\' ) {
				d -= ('/' - '\\');
				if ( !d ) {
					break;
				}
			}
			// make sure folders come first
			while( c1 ) {
				if ( c1 == '/' || c1 == '\\' ) {
					break;
				}
				c1 = *s1++;
			}
			while( c2 ) {
				if ( c2 == '/' || c2 == '\\' ) {
					break;
				}
				c2 = *s2++;
			}
			if ( c1 && !c2 ) {
				return -1;
			} else if ( !c1 && c2 ) {
				return 1;
			}
			// same folder depth so use the regular compare
			return ( INTSIGNBITNOTSET( d ) << 1 ) - 1;
		}
	} while( c1 );

	return 0;
}

/*
================
CMyString::IcmpnPath
================
*/
int CMyString::IcmpnPath( const char *s1, const char *s2, int n ) {
	int c1, c2, d;

#if 0
//#if !defined( _WIN32 )
	Debug::debug(Debug::math,__FUNCTION__) << "WARNING: IcmpPath used on a case-sensitive filesystem?\n" );
#endif

	assert( n >= 0 );

	do {
		c1 = *s1++;
		c2 = *s2++;

		if ( !n-- ) {
			return 0;		// strings are equal until end point
		}

		d = c1 - c2;
		while( d ) {
			if ( c1 <= 'Z' && c1 >= 'A' ) {
				d += ('a' - 'A');
				if ( !d ) {
					break;
				}
			}
			if ( c1 == '\\' ) {
				d += ('/' - '\\');
				if ( !d ) {
					break;
				}
			}
			if ( c2 <= 'Z' && c2 >= 'A' ) {
				d -= ('a' - 'A');
				if ( !d ) {
					break;
				}
			}
			if ( c2 == '\\' ) {
				d -= ('/' - '\\');
				if ( !d ) {
					break;
				}
			}
			// make sure folders come first
			while( c1 ) {
				if ( c1 == '/' || c1 == '\\' ) {
					break;
				}
				c1 = *s1++;
			}
			while( c2 ) {
				if ( c2 == '/' || c2 == '\\' ) {
					break;
				}
				c2 = *s2++;
			}
			if ( c1 && !c2 ) {
				return -1;
			} else if ( !c1 && c2 ) {
				return 1;
			}
			// same folder depth so use the regular compare
			return ( INTSIGNBITNOTSET( d ) << 1 ) - 1;
		}
	} while( c1 );

	return 0;
}

/*
=============
CMyString::Copynz

Safe strncpy that ensures a trailing zero
=============
*/
void CMyString::Copynz( char *dest, const char *src, int destsize ) {
	if ( !src ) {
		Debug::debug(Debug::error,__FUNCTION__)<<"CMyString::Copynz: NULL src" <<endl;
		return;
	}
	if ( destsize < 1 ) {
		Debug::debug(Debug::error,__FUNCTION__)<<"CMyString::Copynz: destsize < 1" <<endl;
		return;
	}

	strncpy( dest, src, destsize-1 );
    dest[destsize-1] = 0;
}

/*
================
CMyString::Append

  never goes past bounds or leaves without a terminating 0
================
*/
void CMyString::Append( char *dest, int size, const char *src ) {
	int		l1;

	l1 = strlen( dest );
	if ( l1 >= size ) {
		Debug::debug(Debug::error,__FUNCTION__)<< "CMyString::Append: already overflowed" <<endl;
	}
	CMyString::Copynz( dest + l1, src, size - l1 );
}

/*
================
CMyString::LengthWithoutColors
================
*/
int CMyString::LengthWithoutColors( const char *s ) {
	int m_iLen;
	const char *p;

	if ( !s ) {
		return 0;
	}

	m_iLen = 0;
	p = s;
	while( *p ) {
		if ( CMyString::IsColor( p ) ) {
			p += 2;
			continue;
		}
		p++;
		m_iLen++;
	}

	return m_iLen;
}

/*
================
CMyString::RemoveColors
================
*/
char *CMyString::RemoveColors( char *string ) {
	char *d;
	char *s;
	int c;

	s = string;
	d = string;
	while( (c = *s) != 0 ) {
		if ( CMyString::IsColor( s ) ) {
			s++;
		}
		else {
			*d++ = c;
		}
		s++;
	}
	*d = '\0';

	return string;
}

/*
================
CMyString::snPrintf
================
*/
int CMyString::snPrintf( char *dest, int size, const char *fmt, ...) {
	int m_iLen;
	va_list argptr;
	char buffer[32000];	// big, but small enough to fit in PPC stack

	va_start( argptr, fmt );
#if defined(_WIN32) && defined(_MSC_VER)
	m_iLen = std::vsprintf( buffer, fmt, argptr );
#else
	m_iLen = vsprintf( buffer, fmt, argptr );
#endif
	va_end( argptr );
	if ( m_iLen >= sizeof( buffer ) ) {
		Debug::debug(Debug::error,__FUNCTION__)<< "CMyString::snPrintf: overflowed buffer" <<endl;
	}
	if ( m_iLen >= size ) {
		Debug::debug(Debug::error,__FUNCTION__)<<"CMyString::snPrintf: overflow of: "<<  m_iLen << " in: "<< size <<endl;
		m_iLen = size;
	}
	CMyString::Copynz( dest, buffer, size );
	return m_iLen;
}

/*
============
CMyString::vsnPrintf

vsnprintf portability:

C99 standard: vsnprintf returns the number of characters (excluding the trailing
'\0') which would have been written to the final string if enough space had been available
snprintf and vsnprintf do not write more than size bytes (including the trailing '\0')

win32: _vsnprintf returns the number of characters written, not including the terminating null character,
or a negative value if an output error occurs. If the number of characters to write exceeds count, then count
characters are written and -1 is returned and no trailing '\0' is added.

CMyString::vsnPrintf: always appends a trailing '\0', returns number of characters written (not including terminal \0)
or returns -1 on failure or if the buffer would be overflowed.
============
*/
int CMyString::vsnPrintf( char *dest, int size, const char *fmt, va_list argptr ) {
	int ret;

#ifdef _WIN32
#undef _vsnprintf
	ret = _vsnprintf( dest, size-1, fmt, argptr );
#define _vsnprintf	use_idStr_vsnPrintf
#else
#undef vsnprintf
	ret = vsnprintf( dest, size, fmt, argptr );
#define vsnprintf	use_idStr_vsnPrintf
#endif
	dest[size-1] = '\0';
	if ( ret < 0 || ret >= size ) {
		return -1;
	}
	return ret;
}

/*
============
sprintf

Sets the value of the string using a printf interface.
============
*/
int sprintf( CMyString &string, const char *fmt, ... ) {
	int l;
	va_list argptr;
	char buffer[32000];

	va_start( argptr, fmt );
	l = CMyString::vsnPrintf( buffer, sizeof(buffer)-1, fmt, argptr );
	va_end( argptr );
	buffer[sizeof(buffer)-1] = '\0';

	string = buffer;
	return l;
}

/*
============
vsprintf

Sets the value of the string using a vprintf interface.
============
*/
int vsprintf( CMyString &string, const char *fmt, va_list argptr ) {
	int l;
	char buffer[32000];

	l = CMyString::vsnPrintf( buffer, sizeof(buffer)-1, fmt, argptr );
	buffer[sizeof(buffer)-1] = '\0';

	string = buffer;
	return l;
}

/*
============
va

does a varargs printf into a temp buffer
NOTE: not thread safe
============
*/
char *va( const char *fmt, ... ) {
	va_list argptr;
	static int index = 0;
	static char string[4][16384];	// in case called by nested functions
	char *buf;

	buf = string[index];
	index = (index + 1) & 3;


	va_start( argptr, fmt );
	::vsprintf( buf, fmt, argptr );
	va_end( argptr );

	return buf;
}



/*
============
CMyString::BestUnit
============
*/
int CMyString::BestUnit( const char *format, float value, Measure_t measure ) {
	int unit = 1;
	while ( unit <= 3 && ( 1 << ( unit * 10 ) < value ) ) {
		unit++;
	}
	unit--;
	value /= 1 << ( unit * 10 );
	sprintf( *this, format, value );
	*this += " ";
	*this += units[ measure ][ unit ];
	return unit;
}

/*
============
CMyString::SetUnit
============
*/
void CMyString::SetUnit( const char *format, float value, int unit, Measure_t measure ) {
	value /= 1 << ( unit * 10 );
	sprintf( *this, format, value );
	*this += " ";
	*this += units[ measure ][ unit ];
}

/*
================
CMyString::InitMemory
================
*/
void CMyString::InitMemory( void ) {
#ifdef USE_STRING_DATA_ALLOCATOR
	stringDataAllocator.Init();
#endif
}

/*
================
CMyString::ShutdownMemory
================
*/
void CMyString::ShutdownMemory( void ) {
#ifdef USE_STRING_DATA_ALLOCATOR
	stringDataAllocator.Shutdown();
#endif
}

/*
================
CMyString::PurgeMemory
================
*/
void CMyString::PurgeMemory( void ) {
#ifdef USE_STRING_DATA_ALLOCATOR
	stringDataAllocator.FreeEmptyBaseBlocks();
#endif
}

/*
================
CMyString::ShowMemoryUsage_f
================
*/
void CMyString::ShowMemoryUsage_f( const CCMDLineArgs &args ) {
#ifdef USE_STRING_DATA_ALLOCATOR
	Debug::debug(Debug::math,__FUNCTION__) << "%6d KB string memory (%d KB free in %d blocks, %d empty base blocks)\n",
		stringDataAllocator.GetBaseBlockMemory() >> 10, stringDataAllocator.GetFreeBlockMemory() >> 10,
			stringDataAllocator.GetNumFreeBlocks(), stringDataAllocator.GetNumEmptyBaseBlocks() );
#endif
}

/*
================
CMyString::FormatNumber
================
*/
struct formatList_t {
	int			gran;
	int			count;
};

// elements of list need to decend in size
formatList_t formatList[] = {
	{ 1000000000, 0 },
	{ 1000000, 0 },
	{ 1000, 0 }
};

int numFormatList = sizeof(formatList) / sizeof( formatList[0] );


CMyString CMyString::FormatNumber( int number ) {
	CMyString string;
	bool hit;

	// reset
	for ( int i = 0; i < numFormatList; i++ ) {
		formatList_t *li = formatList + i;
		li->count = 0;
	}

	// main loop
	do {
		hit = false;

		for ( int i = 0; i < numFormatList; i++ ) {
			formatList_t *li = formatList + i;

			if ( number >= li->gran ) {
				li->count++;
				number -= li->gran;
				hit = true;
				break;
			}
		}
	} while ( hit );

	// print out
	bool found = false;

	for ( int i = 0; i < numFormatList; i++ ) {
		formatList_t *li = formatList + i;

		if ( li->count ) {
			if ( !found ) {
				string += va( "%i,", li->count );
			} else {
				string += va( "%3.3i,", li->count );
			}
			found = true;
		}
		else if ( found ) {
			string += va( "%3.3i,", li->count );
		}
	}

	if ( found ) {
		string += va( "%3.3i", number );
	}
	else {
		string += va( "%i", number );
	}

	// pad to proper size
	int count = 11 - string.Length();

	for ( int i = 0; i < count; i++ ) {
		string.Insert( " ", 0 );
	}

	return string;
}

} //end SGF
