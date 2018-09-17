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

#ifndef __SGF_STRING_UTILS_H__
#define __SGF_STRING_UTILS_H__

#include "SGF_ArgsCmdLine.h"
#include <cstring>
#include <stdio.h>

/*
===============================================================================

	Character string

===============================================================================
*/
#if 0
// these library functions should not be used for cross platform compatibility
#define strcmp			CMyString::Cmp		// use_idStr_Cmp
#define strncmp			use_idStr_Cmpn

#if defined( StrCmpN )
#undef StrCmpN
#endif
#define StrCmpN			use_idStr_Cmpn

#if defined( strcmpi )
#undef strcmpi
#endif
#define strcmpi			use_idStr_Icmp

#if defined( StrCmpI )
#undef StrCmpI
#endif
#define StrCmpI			use_idStr_Icmp

#if defined( StrCmpNI )
#undef StrCmpNI
#endif
#define StrCmpNI		use_idStr_Icmpn

#define stricmp			CMyString::Icmp		// use_idStr_Icmp
#define _stricmp		use_idStr_Icmp
#define strcasecmp		use_idStr_Icmp
#define strnicmp		use_idStr_Icmpn
#define _strnicmp		use_idStr_Icmpn
#define _memicmp		use_idStr_Icmpn
#define snprintf		use_idStr_snPrintf
#define _snprintf		use_idStr_snPrintf
#define vsnprintf		use_idStr_vsnPrintf
#define _vsnprintf		use_idStr_vsnPrintf
#endif
namespace SGF {
class CVector4D;

#ifndef FILE_HASH_SIZE
#define FILE_HASH_SIZE		1024
#endif

// color escape character
const int C_COLOR_ESCAPE			= '^';
const int C_COLOR_DEFAULT			= '0';
const int C_COLOR_RED				= '1';
const int C_COLOR_GREEN				= '2';
const int C_COLOR_YELLOW			= '3';
const int C_COLOR_BLUE				= '4';
const int C_COLOR_CYAN				= '5';
const int C_COLOR_MAGENTA			= '6';
const int C_COLOR_WHITE				= '7';
const int C_COLOR_GRAY				= '8';
const int C_COLOR_BLACK				= '9';

// color escape string
#define S_COLOR_DEFAULT				"^0"
#define S_COLOR_RED					"^1"
#define S_COLOR_GREEN				"^2"
#define S_COLOR_YELLOW				"^3"
#define S_COLOR_BLUE				"^4"
#define S_COLOR_CYAN				"^5"
#define S_COLOR_MAGENTA				"^6"
#define S_COLOR_WHITE				"^7"
#define S_COLOR_GRAY				"^8"
#define S_COLOR_BLACK				"^9"

// make CMyString a multiple of 16 bytes long
// don't make too large to keep memory requirements to a minimum
const int STR_ALLOC_BASE			= 20;
const int STR_ALLOC_GRAN			= 32;

typedef enum {
	MEASURE_SIZE = 0,
	MEASURE_BANDWIDTH
} Measure_t;

class CMyString {

public:
						CMyString();
						CMyString( const CMyString &text );
						CMyString( const CMyString &text, int start, int end );
						CMyString( const char *text );
						CMyString( const char *text, int start, int end );
						explicit CMyString( const bool b );
						explicit CMyString( const char c );
						explicit CMyString( const int i );
						explicit CMyString( const unsigned u );
						explicit CMyString( const float f );
						~CMyString();

	size_t				Size() const;
	const char *		c_str() const;
	operator			const char *() const;
	operator			const char *();

	char				operator[]( int index ) const;
	char &				operator[]( int index );

	void				operator=( const CMyString &text );
	void				operator=( const char *text );
	//void				operator=( const char c);
	void				operator=( char c);

	friend CMyString		operator+( const CMyString &a, const CMyString &b );
	friend CMyString		operator+( const CMyString &a, const char *b );
	friend CMyString		operator+( const char *a, const CMyString &b );

	friend CMyString		operator+( const CMyString &a, const float b );
	friend CMyString		operator+( const CMyString &a, const int b );
	friend CMyString		operator+( const CMyString &a, const unsigned b );
	friend CMyString		operator+( const CMyString &a, const bool b );
	friend CMyString		operator+( const CMyString &a, const char b );
	
	CMyString &				operator<<( const CMyString &a );
	CMyString &				operator<<( const char *a );
	CMyString &				operator<<( const float a );
	CMyString &				operator<<( const char a );
	CMyString &				operator<<( const int a );
	CMyString &				operator<<( const unsigned a );
	CMyString &				operator<<( const bool a );



	CMyString &				operator+=( const CMyString &a );
	CMyString &				operator+=( const char *a );
	CMyString &				operator+=( const float a );
	CMyString &				operator+=( const char a );
	CMyString &				operator+=( const int a );
	CMyString &				operator+=( const unsigned a );
	CMyString &				operator+=( const bool a );

						// case sensitive compare
	friend bool			operator==( const CMyString &a, const CMyString &b );
	friend bool			operator==( const CMyString &a, const char *b );
	friend bool			operator==( const char *a, const CMyString &b );

						// case sensitive compare
	friend bool			operator!=( const CMyString &a, const CMyString &b );
	friend bool			operator!=( const CMyString &a, const char *b );
	friend bool			operator!=( const char *a, const CMyString &b );

						// case sensitive compare
	int					Cmp( const char *text ) const;
	int					Cmpn( const char *text, int n ) const;
	int					CmpPrefix( const char *text ) const;

						// case insensitive compare
	int					Icmp( const char *text ) const;
	int					Icmpn( const char *text, int n ) const;
	int					IcmpPrefix( const char *text ) const;

						// case insensitive compare ignoring color
	int					IcmpNoColor( const char *text ) const;

						// compares paths and makes sure folders come first
	int					IcmpPath( const char *text ) const;
	int					IcmpnPath( const char *text, int n ) const;
	int					IcmpPrefixPath( const char *text ) const;

	int					Length() const;
	int					Allocated() const;
	void				Empty();
	bool				isEmpty() const; //! verify if the string is empty or not
	void				Clear();
	void				Append( const char a );
	void				Append( const CMyString &text );
	void				Append( const char *text );
	void				Append( const char *text, int len );
	void				Insert( const char a, int index );
	void				Insert( const char *text, int index );
	void				ToLower();
	void				ToUpper();
	bool				IsNumeric() const;
	bool				IsColor() const;
	bool				HasLower() const;
	bool				HasUpper() const;
	int					LengthWithoutColors() const;
	CMyString &			RemoveColors();
	void				CapLength( int );
	void				Fill( const char ch, int newlen );

	int					Find( const char c, int start = 0, int end = -1 ) const;
	int					Find( const char *text, bool casesensitive = true, int start = 0, int end = -1 ) const;
	bool				Filter( const char *filter, bool casesensitive ) const;
	int					Last( const char c ) const;						// return the index to the last occurance of 'c', returns -1 if not found
	const char *		Left( int len, CMyString &result ) const;			// store the leftmost 'len' characters in the result
	const char *		Right( int len, CMyString &result ) const;			// store the rightmost 'len' characters in the result
	const char *		Mid( int start, int len, CMyString &result ) const;	// store 'len' characters starting at 'start' in result
	CMyString				Left( int len ) const;							// return the leftmost 'len' characters
	CMyString				Right( int len ) const;							// return the rightmost 'len' characters
	CMyString				Mid( int start, int len ) const;				// return 'len' characters starting at 'start'
	void				StripLeading( const char c );					// strip char from front as many times as the char occurs
	void				StripLeading( const char *string );				// strip string from front as many times as the string occurs
	bool				StripLeadingOnce( const char *string );			// strip string from front just once if it occurs
	void				StripTrailing( const char c );					// strip char from end as many times as the char occurs
	void				StripTrailing( const char *string );			// strip string from end as many times as the string occurs
	bool				StripTrailingOnce( const char *string );		// strip string from end just once if it occurs
	void				Strip( const char c );							// strip char from front and end as many times as the char occurs
	void				Strip( const char *string );					// strip string from front and end as many times as the string occurs
	void				StripTrailingWhitespace();				// strip trailing white space characters
	CMyString &			StripQuotes();							// strip quotes around string
	void				Replace( const char *old, const char *nw );

	// file name methods
	int					FileNameHash() const;						// hash key for the filename (skips extension)
	CMyString &			BackSlashesToSlashes();					// convert slashes
	CMyString &			SetFileExtension( const char *extension );		// set the given file extension
	CMyString &			StripFileExtension();						// remove any file extension
	CMyString &			StripAbsoluteFileExtension();				// remove any file extension looking from front (useful if there are multiple .'s)
	CMyString &			DefaultFileExtension( const char *extension );	// if there's no file extension use the default
	CMyString &			DefaultPath( const char *basepath );			// if there's no path use the default
	void				AppendPath( const char *text );					// append a partial path
	CMyString &			StripFilename();							// remove the filename from a path
	CMyString &			StripPath();								// remove the path from the filename
	void				ExtractFilePath( CMyString &dest ) const;			// copy the file path to another string
	void				ExtractFileName( CMyString &dest ) const;			// copy the filename to another string
	void				ExtractFileBase( CMyString &dest ) const;			// copy the filename minus the extension to another string
	void				ExtractFileExtension( CMyString &dest ) const;		// copy the file extension to another string
	bool				CheckExtension( const char *ext );

	// char * methods to replace library functions
	static int			Length( const char *s );
	static char *		ToLower( char *s );
	static char *		ToUpper( char *s );
	static bool			IsNumeric( const char *s );
	static bool			IsColor( const char *s );
	static bool			HasLower( const char *s );
	static bool			HasUpper( const char *s );
	static int			LengthWithoutColors( const char *s );
	static char *		RemoveColors( char *s );
	static int			Cmp( const char *s1, const char *s2 );
	static int			Cmpn( const char *s1, const char *s2, int n );
	static int			Icmp( const char *s1, const char *s2 );
	static int			Icmpn( const char *s1, const char *s2, int n );
	static int			IcmpNoColor( const char *s1, const char *s2 );
	static int			IcmpPath( const char *s1, const char *s2 );			// compares paths and makes sure folders come first
	static int			IcmpnPath( const char *s1, const char *s2, int n );	// compares paths and makes sure folders come first
	static void			Append( char *dest, int size, const char *src );
	static void			Copynz( char *dest, const char *src, int destsize );
	static int			snPrintf( char *dest, int size, const char *fmt, ... ) id_attribute((format(printf,3,4)));
	static int			vsnPrintf( char *dest, int size, const char *fmt, va_list argptr );
	static int			FindChar( const char *str, const char c, int start = 0, int end = -1 );
	static int			FindText( const char *str, const char *text, bool casesensitive = true, int start = 0, int end = -1 );
	static bool			Filter( const char *filter, const char *name, bool casesensitive );
	static void			StripMediaName( const char *name, CMyString &mediaName );
	static bool			CheckExtension( const char *name, const char *ext );
	static const char *	FloatArrayToString( const float *array, const int length, const int precision );

	// hash keys
	static int			Hash( const char *string );
	static int			Hash( const char *string, int length );
	static int			IHash( const char *string );					// case insensitive
	static int			IHash( const char *string, int length );		// case insensitive

	// character methods
	static char			ToLower( char c );
	static char			ToUpper( char c );
	static bool			CharIsPrintable( int c );
	static bool			CharIsLower( int c );
	static bool			CharIsUpper( int c );
	static bool			CharIsAlpha( int c );
	static bool			CharIsNumeric( int c );
	static bool			CharIsNewLine( char c );
	static bool			CharIsTab( char c );
	static int			ColorIndex( int c );
	static CVector4D &		ColorForIndex( int i );

	friend int			sprintf( CMyString &dest, const char *fmt, ... );
	friend int			vsprintf( CMyString &dest, const char *fmt, va_list ap );

	void				reAllocate( int amount, bool keepold );				// reallocate string data buffer
	void				freeData();									// free allocated string memory

						// format value in the given measurement with the best unit, returns the best unit
	int					BestUnit( const char *format, float value, Measure_t measure );
						// format value in the requested unit and measurement
	void				SetUnit( const char *format, float value, int unit, Measure_t measure );

	static void			InitMemory();
	static void			ShutdownMemory();
	static void			PurgeMemory();
	static void			ShowMemoryUsage_f( const CCMDLineArgs &args );

	int					DynamicMemoryUsed() const;
	static CMyString	FormatNumber( int number );

protected:

	void				init();	//! initialize string using base buffer
	void				ensureAlloced( int amount, bool keepold = true );	//! ensure string data buffer is large anough

	int					m_iLen;   //! the string lenght
	char *				m_pData;  //! the C String 
	int					m_iAllocated;  //! ammount of memory allocateb by m_pData
	char				m_cBaseBuffer[ STR_ALLOC_BASE ]; //! base buffer for string
};

char *					va( const char *fmt, ... ) id_attribute((format(printf,1,2)));
#if !defined(_MSC_VER)
#define SGF_INLINE_FORCED inline
#endif
/**
\brief ensure string data buffer is large anough
**/
SGF_INLINE_FORCED void CMyString::ensureAlloced( int amount, bool keepold ) {
	if ( amount > m_iAllocated ) {
		reAllocate( amount, keepold );
	}
}
/**
\brief init the string buffer
**/
SGF_INLINE_FORCED void CMyString::init() {
	m_iLen = 0;
	m_iAllocated = STR_ALLOC_BASE;
	m_pData = m_cBaseBuffer;
	m_pData[ 0 ] = '\0';
#ifdef ID_DEBUG_UNINITIALIZED_MEMORY
	memset( baseBuffer, 0, sizeof( baseBuffer ) );
#endif
}

SGF_INLINE_FORCED CMyString::CMyString() {
	init();
}

SGF_INLINE_FORCED CMyString::CMyString( const CMyString &text ) {
	int l;

	init();
	l = text.Length();
	ensureAlloced( l + 1 );
	strcpy( m_pData, text.m_pData );
	m_iLen = l;
}

SGF_INLINE_FORCED CMyString::CMyString( const CMyString &text, int start, int end ) {
	int i;
	int l;

	init();
	if ( end > text.Length() ) {
		end = text.Length();
	}
	if ( start > text.Length() ) {
		start = text.Length();
	} else if ( start < 0 ) {
		start = 0;
	}

	l = end - start;
	if ( l < 0 ) {
		l = 0;
	}

	ensureAlloced( l + 1 );

	for ( i = 0; i < l; i++ ) {
		m_pData[ i ] = text[ start + i ];
	}

	m_pData[ l ] = '\0';
	m_iLen = l;
}

SGF_INLINE_FORCED CMyString::CMyString( const char *text ) {
	int l;

	init();
	if ( text ) {

#ifdef _WIN32
	l = std::strlen( text );
#else
	l = strlen( text );
#endif
		ensureAlloced( l + 1 );
		strcpy( m_pData, text );
		m_iLen = l;
	}
}

SGF_INLINE_FORCED CMyString::CMyString( const char *text, int start, int end ) {
	int i;
#ifdef _WIN32
	int l = std::strlen( text );
#else
	int l = strlen( text );
#endif
	init();
	if ( end > l ) {
		end = l;
	}
	if ( start > l ) {
		start = l;
	} else if ( start < 0 ) {
		start = 0;
	}

	l = end - start;
	if ( l < 0 ) {
		l = 0;
	}

	ensureAlloced( l + 1 );

	for ( i = 0; i < l; i++ ) {
		m_pData[ i ] = text[ start + i ];
	}

	m_pData[ l ] = '\0';
	m_iLen = l;
}

SGF_INLINE_FORCED CMyString::CMyString( const bool b ) {
	init();
	ensureAlloced( 2 );
	m_pData[ 0 ] = b ? '1' : '0';
	m_pData[ 1 ] = '\0';
	m_iLen = 1;
}

SGF_INLINE_FORCED CMyString::CMyString( const char c ) {
	init();
	ensureAlloced( 2 );
	m_pData[ 0 ] = c;
	m_pData[ 1 ] = '\0';
	m_iLen = 1;
}

SGF_INLINE_FORCED CMyString::CMyString( const int i ) {
	char text[ 64 ];
	int l;

	init();
#if defined(_MSC_VER)
	l = std::sprintf( text, "%d", i );
#else
	l = sprintf( text, "%d", i );
#endif

	ensureAlloced( l + 1 );
	strcpy( m_pData, text );
	m_iLen = l;
}

SGF_INLINE_FORCED CMyString::CMyString( const unsigned u ) {
	char text[ 64 ];
	int l;

	init();
#if defined(_MSC_VER)
	l = std::sprintf( text, "%u", u );
#else
	l = sprintf( text, "%u", u );
#endif
	ensureAlloced( l + 1 );
	strcpy( m_pData, text );
	m_iLen = l;
}

SGF_INLINE_FORCED CMyString::CMyString( const float f ) {
	char text[ 64 ];
	int l;

	init();
	l = CMyString::snPrintf( text, sizeof( text ), "%f", f );
	while( l > 0 && text[l-1] == '0' ) text[--l] = '\0';
	while( l > 0 && text[l-1] == '.' ) text[--l] = '\0';
	ensureAlloced( l + 1 );
	strcpy( m_pData, text );
	m_iLen = l;
}

SGF_INLINE_FORCED CMyString::~CMyString() {
	freeData();
}

SGF_INLINE_FORCED size_t CMyString::Size() const {
	return sizeof( *this ) + Allocated();
}

SGF_INLINE_FORCED const char *CMyString::c_str() const {
	return m_pData;
}

SGF_INLINE_FORCED CMyString::operator const char *() {
	return c_str();
}

SGF_INLINE_FORCED CMyString::operator const char *() const {
	return c_str();
}

SGF_INLINE_FORCED char CMyString::operator[]( int index ) const {
	assert( ( index >= 0 ) && ( index <= m_iLen ) );
	return m_pData[ index ];
}

SGF_INLINE_FORCED char &CMyString::operator[]( int index ) {
	assert( ( index >= 0 ) && ( index <= m_iLen ) );
	return m_pData[ index ];
}

SGF_INLINE_FORCED void CMyString::operator=( const CMyString &text ) {
	int l;

	l = text.Length();
	ensureAlloced( l + 1, false );
	memcpy( m_pData, text.m_pData, l );
	m_pData[l] = '\0';
	m_iLen = l;
}
SGF_INLINE_FORCED void	CMyString::operator=( char c){
	ensureAlloced( 2 );
	m_pData[ 0 ] = c;
	m_pData[ 1 ] = '\0';
	m_iLen = 1;
}

SGF_INLINE_FORCED CMyString operator+( const CMyString &a, const CMyString &b ) {
	CMyString result( a );
	result.Append( b );
	return result;
}

SGF_INLINE_FORCED CMyString operator+( const CMyString &a, const char *b ) {
	CMyString result( a );
	result.Append( b );
	return result;
}

SGF_INLINE_FORCED CMyString operator+( const char *a, const CMyString &b ) {
	CMyString result( a );
	result.Append( b );
	return result;
}

SGF_INLINE_FORCED CMyString operator+( const CMyString &a, const bool b ) {
	CMyString result( a );
	result.Append( b ? "true" : "false" );
	return result;
}

SGF_INLINE_FORCED CMyString operator+( const CMyString &a, const char b ) {
	CMyString result( a );
	result.Append( b );
	return result;
}

SGF_INLINE_FORCED CMyString operator+( const CMyString &a, const float b ) {
	char	text[ 64 ];
	CMyString	result( a );
#if defined(_MSC_VER)
	std::sprintf( text, "%f", b );
#else
	sprintf( text, "%f", b );
#endif
	result.Append( text );

	return result;
}

SGF_INLINE_FORCED CMyString operator+( const CMyString &a, const int b ) {
	char	text[ 64 ];
	CMyString	result( a );
#if defined(_MSC_VER)
	std::sprintf( text, "%d", b );
#else
	sprintf( text, "%d", b );
#endif

	result.Append( text );

	return result;
}

SGF_INLINE_FORCED CMyString operator+( const CMyString &a, const unsigned b ) {
	char	text[ 64 ];
	CMyString	result( a );
#if defined(_MSC_VER)
	std::sprintf( text, "%u", b );
#else
	sprintf( text, "%u", b );
#endif

	result.Append( text );

	return result;
}

SGF_INLINE_FORCED CMyString &CMyString::operator+=( const float a ) {
	char text[ 64 ];
#if defined(_MSC_VER)
	std::sprintf( text, "%f", a );
#else
	sprintf( text, "%f", a );
#endif

	Append( text );

	return *this;
}

SGF_INLINE_FORCED CMyString &CMyString::operator+=( const int a ) {
	char text[ 64 ];
#if defined(_MSC_VER)
	std::sprintf( text, "%d", a );
#else
	sprintf( text, "%d", a );
#endif

	Append( text );

	return *this;
}

SGF_INLINE_FORCED CMyString &CMyString::operator+=( const unsigned a ) {
	char text[ 64 ];
#if defined(_MSC_VER)
	std::sprintf( text, "%u", a );
#else
	sprintf( text, "%u", a );
#endif
	Append( text );

	return *this;
}

SGF_INLINE_FORCED CMyString &CMyString::operator+=( const CMyString &a ) {
	Append( a );
	return *this;
}

SGF_INLINE_FORCED CMyString &CMyString::operator+=( const char *a ) {
	Append( a );
	return *this;
}

SGF_INLINE_FORCED CMyString &CMyString::operator+=( const char a ) {
	Append( a );
	return *this;
}

SGF_INLINE_FORCED CMyString &CMyString::operator+=( const bool a ) {
	Append( a ? "true" : "false" );
	return *this;
}

SGF_INLINE_FORCED CMyString &CMyString::operator<<( const CMyString &a ){
	Append( a );
	return *this;
}

SGF_INLINE_FORCED CMyString &CMyString::operator<<( const float a ) {
	char text[ 64 ];
#if defined(_MSC_VER)
	std::sprintf( text, "%f", a );
#else
	sprintf( text, "%f", a );
#endif

	Append( text );

	return *this;
}

SGF_INLINE_FORCED CMyString &CMyString::operator<<( const int a ) {
	char text[ 64 ];
#if defined(_MSC_VER)
	std::sprintf( text, "%d", a );
#else
	sprintf( text, "%d", a );
#endif

	Append( text );

	return *this;
}

SGF_INLINE_FORCED CMyString &CMyString::operator<<( const unsigned a ) {
	char text[ 64 ];
#if defined(_MSC_VER)
	std::sprintf( text, "%u", a );
#else
	sprintf( text, "%u", a );
#endif
	Append( text );

	return *this;
}

SGF_INLINE_FORCED CMyString &CMyString::operator<<( const char *a ) {
	Append( a );
	return *this;
}

SGF_INLINE_FORCED CMyString &CMyString::operator<<( const char a ) {
	Append( a );
	return *this;
}

SGF_INLINE_FORCED CMyString &CMyString::operator<<( const bool a ) {
	Append( a ? "true" : "false" );
	return *this;
}


SGF_INLINE_FORCED bool operator==( const CMyString &a, const CMyString &b ) {
	return ( !CMyString::Cmp( a.m_pData, b.m_pData ) );
}

SGF_INLINE_FORCED bool operator==( const CMyString &a, const char *b ) {
	assert( b );
	return ( !CMyString::Cmp( a.m_pData, b ) );
}

SGF_INLINE_FORCED bool operator==( const char *a, const CMyString &b ) {
	assert( a );
	return ( !CMyString::Cmp( a, b.m_pData ) );
}

SGF_INLINE_FORCED bool operator!=( const CMyString &a, const CMyString &b ) {
	return !( a == b );
}

SGF_INLINE_FORCED bool operator!=( const CMyString &a, const char *b ) {
	return !( a == b );
}

SGF_INLINE_FORCED bool operator!=( const char *a, const CMyString &b ) {
	return !( a == b );
}

SGF_INLINE_FORCED int CMyString::Cmp( const char *text ) const {
	assert( text );
	return CMyString::Cmp( m_pData, text );
}

SGF_INLINE_FORCED int CMyString::Cmpn( const char *text, int n ) const {
	assert( text );
	return CMyString::Cmpn( m_pData, text, n );
}

SGF_INLINE_FORCED int CMyString::CmpPrefix( const char *text ) const {
	assert( text );
#ifdef WIN32
	return CMyString::Cmpn( m_pData, text, std::strlen( text ) );
#else
	return CMyString::Cmpn( m_pData, text, strlen( text ) );
#endif

}

SGF_INLINE_FORCED int CMyString::Icmp( const char *text ) const {
	assert( text );
	return CMyString::Icmp( m_pData, text );
}

SGF_INLINE_FORCED int CMyString::Icmpn( const char *text, int n ) const {
	assert( text );
	return CMyString::Icmpn( m_pData, text, n );
}

SGF_INLINE_FORCED int CMyString::IcmpPrefix( const char *text ) const {
	assert( text );
#ifdef WIN32
	return CMyString::Icmpn( m_pData, text, std::strlen( text ) );
#else
	return CMyString::Icmpn( m_pData, text, strlen( text ) );
#endif

}

SGF_INLINE_FORCED int CMyString::IcmpNoColor( const char *text ) const {
	assert( text );
	return CMyString::IcmpNoColor( m_pData, text );
}

SGF_INLINE_FORCED int CMyString::IcmpPath( const char *text ) const {
	assert( text );
	return CMyString::IcmpPath( m_pData, text );
}

SGF_INLINE_FORCED int CMyString::IcmpnPath( const char *text, int n ) const {
	assert( text );
	return CMyString::IcmpnPath( m_pData, text, n );
}

SGF_INLINE_FORCED int CMyString::IcmpPrefixPath( const char *text ) const {
	assert( text );
#ifdef WIN32
	return CMyString::IcmpnPath( m_pData, text, std::strlen( text ) );
#else
	return CMyString::IcmpnPath( m_pData, text, strlen( text ) );
#endif

}

SGF_INLINE_FORCED int CMyString::Length() const {
	return m_iLen;
}

SGF_INLINE_FORCED int CMyString::Allocated() const {
	if ( m_pData != m_cBaseBuffer ) {
		return m_iAllocated;
	} else {
		return 0;
	}
}
//! clean the String
SGF_INLINE_FORCED void CMyString::Empty() {
	ensureAlloced( 1 );
	m_pData[ 0 ] = '\0';
	m_iLen = 0;
}
//! verify if the string is empty or not
SGF_INLINE_FORCED bool CMyString::isEmpty() const {
	return ( CMyString::Cmp( m_pData, "" ) == 0 );
}

SGF_INLINE_FORCED void CMyString::Clear() {
	freeData();
	init();
}

SGF_INLINE_FORCED void CMyString::Append( const char a ) {
	ensureAlloced( m_iLen + 2 );
	m_pData[ m_iLen ] = a;
	m_iLen++;
	m_pData[ m_iLen ] = '\0';
}

SGF_INLINE_FORCED void CMyString::Append( const CMyString &text ) {
	int newLen;
	int i;

	newLen = m_iLen + text.Length();
	ensureAlloced( newLen + 1 );
	for ( i = 0; i < text.m_iLen; i++ ) {
		m_pData[ m_iLen + i ] = text[ i ];
	}
	m_iLen = newLen;
	m_pData[ m_iLen ] = '\0';
}

SGF_INLINE_FORCED void CMyString::Append( const char *text ) {
	int newLen;
	int i;

	if ( text ) {
#ifdef WIN32
	newLen = m_iLen + std::strlen( text );
#else
	newLen = m_iLen + strlen( text );
#endif

		ensureAlloced( newLen + 1 );
		for ( i = 0; text[ i ]; i++ ) {
			m_pData[ m_iLen + i ] = text[ i ];
		}
		m_iLen = newLen;
		m_pData[ m_iLen ] = '\0';
	}
}

SGF_INLINE_FORCED void CMyString::Append( const char *text, int l ) {
	int newLen;
	int i;

	if ( text && l ) {
		newLen = m_iLen + l;
		ensureAlloced( newLen + 1 );
		for ( i = 0; text[ i ] && i < l; i++ ) {
			m_pData[ m_iLen + i ] = text[ i ];
		}
		m_iLen = newLen;
		m_pData[ m_iLen ] = '\0';
	}
}

SGF_INLINE_FORCED void CMyString::Insert( const char a, int index ) {
	int i, l;

	if ( index < 0 ) {
		index = 0;
	} else if ( index > m_iLen ) {
		index = m_iLen;
	}

	l = 1;
	ensureAlloced( m_iLen + l + 1 );
	for ( i = m_iLen; i >= index; i-- ) {
		m_pData[i+l] = m_pData[i];
	}
	m_pData[index] = a;
	m_iLen++;
}

SGF_INLINE_FORCED void CMyString::Insert( const char *text, int index ) {
	int i, l;

	if ( index < 0 ) {
		index = 0;
	} else if ( index > m_iLen ) {
		index = m_iLen;
	}
#ifdef WIN32
	l = std::strlen( text );
#else
	l = strlen( text );
#endif


	ensureAlloced( m_iLen + l + 1 );
	for ( i = m_iLen; i >= index; i-- ) {
		m_pData[i+l] = m_pData[i];
	}
	for ( i = 0; i < l; i++ ) {
		m_pData[index+i] = text[i];
	}
	m_iLen += l;
}

SGF_INLINE_FORCED void CMyString::ToLower() {
	for (int i = 0; m_pData[i]; i++ ) {
		if ( CharIsUpper( m_pData[i] ) ) {
			m_pData[i] += ( 'a' - 'A' );
		}
	}
}

SGF_INLINE_FORCED void CMyString::ToUpper() {
	for (int i = 0; m_pData[i]; i++ ) {
		if ( CharIsLower( m_pData[i] ) ) {
			m_pData[i] -= ( 'a' - 'A' );
		}
	}
}

SGF_INLINE_FORCED bool CMyString::IsNumeric() const {
	return CMyString::IsNumeric( m_pData );
}

SGF_INLINE_FORCED bool CMyString::IsColor() const {
	return CMyString::IsColor( m_pData );
}

SGF_INLINE_FORCED bool CMyString::HasLower() const {
	return CMyString::HasLower( m_pData );
}

SGF_INLINE_FORCED bool CMyString::HasUpper() const {
	return CMyString::HasUpper( m_pData );
}

SGF_INLINE_FORCED CMyString &CMyString::RemoveColors() {
	CMyString::RemoveColors( m_pData );
	m_iLen = Length( m_pData );
	return *this;
}

SGF_INLINE_FORCED int CMyString::LengthWithoutColors() const {
	return CMyString::LengthWithoutColors( m_pData );
}

SGF_INLINE_FORCED void CMyString::CapLength( int newlen ) {
	if ( m_iLen <= newlen ) {
		return;
	}
	m_pData[ newlen ] = 0;
	m_iLen = newlen;
}

SGF_INLINE_FORCED void CMyString::Fill( const char ch, int newlen ) {
	ensureAlloced( newlen + 1 );
	m_iLen = newlen;
	memset( m_pData, ch, m_iLen );
	m_pData[ m_iLen ] = 0;
}

SGF_INLINE_FORCED int CMyString::Find( const char c, int start, int end ) const {
	if ( end == -1 ) {
		end = m_iLen;
	}
	return CMyString::FindChar( m_pData, c, start, end );
}

SGF_INLINE_FORCED int CMyString::Find( const char *text, bool casesensitive, int start, int end ) const {
	if ( end == -1 ) {
		end = m_iLen;
	}
	return CMyString::FindText( m_pData, text, casesensitive, start, end );
}

SGF_INLINE_FORCED bool CMyString::Filter( const char *filter, bool casesensitive ) const {
	return CMyString::Filter( filter, m_pData, casesensitive );
}

SGF_INLINE_FORCED const char *CMyString::Left( int m_iLen, CMyString &result ) const {
	return Mid( 0, m_iLen, result );
}

SGF_INLINE_FORCED const char *CMyString::Right( int len, CMyString &result ) const {
	if ( len >= Length() ) {
		result = *this;
		return result;
	}
	return Mid( Length() - len, len, result );
}

SGF_INLINE_FORCED CMyString CMyString::Left( int len ) const {
	return Mid( 0, len );
}

SGF_INLINE_FORCED CMyString CMyString::Right( int len ) const {
	if ( len >= Length() ) {
		return *this;
	}
	return Mid( Length() - len, len );
}

SGF_INLINE_FORCED void CMyString::Strip( const char c ) {
	StripLeading( c );
	StripTrailing( c );
}

SGF_INLINE_FORCED void CMyString::Strip( const char *string ) {
	StripLeading( string );
	StripTrailing( string );
}

SGF_INLINE_FORCED bool CMyString::CheckExtension( const char *ext ) {
	return CMyString::CheckExtension( m_pData, ext );
}

SGF_INLINE_FORCED int CMyString::Length( const char *s ) {
	int i;
	for ( i = 0; s[i]; i++ ) {}
	return i;
}

SGF_INLINE_FORCED char *CMyString::ToLower( char *s ) {
	for ( int i = 0; s[i]; i++ ) {
		if ( CharIsUpper( s[i] ) ) {
			s[i] += ( 'a' - 'A' );
		}
	}
	return s;
}

SGF_INLINE_FORCED char *CMyString::ToUpper( char *s ) {
	for ( int i = 0; s[i]; i++ ) {
		if ( CharIsLower( s[i] ) ) {
			s[i] -= ( 'a' - 'A' );
		}
	}
	return s;
}

SGF_INLINE_FORCED int CMyString::Hash( const char *string ) {
	int i, hash = 0;
	for ( i = 0; *string != '\0'; i++ ) {
		hash += ( *string++ ) * ( i + 119 );
	}
	return hash;
}

SGF_INLINE_FORCED int CMyString::Hash( const char *string, int length ) {
	int i, hash = 0;
	for ( i = 0; i < length; i++ ) {
		hash += ( *string++ ) * ( i + 119 );
	}
	return hash;
}

SGF_INLINE_FORCED int CMyString::IHash( const char *string ) {
	int i, hash = 0;
	for( i = 0; *string != '\0'; i++ ) {
		hash += ToLower( *string++ ) * ( i + 119 );
	}
	return hash;
}

SGF_INLINE_FORCED int CMyString::IHash( const char *string, int length ) {
	int i, hash = 0;
	for ( i = 0; i < length; i++ ) {
		hash += ToLower( *string++ ) * ( i + 119 );
	}
	return hash;
}

SGF_INLINE_FORCED bool CMyString::IsColor( const char *s ) {
	return ( s[0] == C_COLOR_ESCAPE && s[1] != '\0' && s[1] != ' ' );
}

SGF_INLINE_FORCED char CMyString::ToLower( char c ) {
	if ( c <= 'Z' && c >= 'A' ) {
		return ( c + ( 'a' - 'A' ) );
	}
	return c;
}

SGF_INLINE_FORCED char CMyString::ToUpper( char c ) {
	if ( c >= 'a' && c <= 'z' ) {
		return ( c - ( 'a' - 'A' ) );
	}
	return c;
}

SGF_INLINE_FORCED bool CMyString::CharIsPrintable( int c ) {
	// test for regular ascii and western European high-ascii chars
	return ( c >= 0x20 && c <= 0x7E ) || ( c >= 0xA1 && c <= 0xFF );
}

SGF_INLINE_FORCED bool CMyString::CharIsLower( int c ) {
	// test for regular ascii and western European high-ascii chars
	return ( c >= 'a' && c <= 'z' ) || ( c >= 0xE0 && c <= 0xFF );
}

SGF_INLINE_FORCED bool CMyString::CharIsUpper( int c ) {
	// test for regular ascii and western European high-ascii chars
	return ( c <= 'Z' && c >= 'A' ) || ( c >= 0xC0 && c <= 0xDF );
}

SGF_INLINE_FORCED bool CMyString::CharIsAlpha( int c ) {
	// test for regular ascii and western European high-ascii chars
	return ( ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) ||
			 ( c >= 0xC0 && c <= 0xFF ) );
}

SGF_INLINE_FORCED bool CMyString::CharIsNumeric( int c ) {
	return ( c <= '9' && c >= '0' );
}

SGF_INLINE_FORCED bool CMyString::CharIsNewLine( char c ) {
	return ( c == '\n' || c == '\r' || c == '\v' );
}

SGF_INLINE_FORCED bool CMyString::CharIsTab( char c ) {
	return ( c == '\t' );
}

SGF_INLINE_FORCED int CMyString::ColorIndex( int c ) {
	return ( c & 15 );
}

SGF_INLINE_FORCED int CMyString::DynamicMemoryUsed() const {
	return ( m_pData == m_cBaseBuffer ) ? 0 : m_iAllocated;
}
} // end SGF

#endif /* !__SGF_STRING_UTILS_H__ */
