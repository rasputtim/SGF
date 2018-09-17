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

#ifndef __STRLIST_H__
#define __STRLIST_H__
#include "../SGF_Config.h"
#include "SGF_List.h"
#include "../util/SGF_StringUtils.h"

/*
===============================================================================

	stringList_t

===============================================================================
*/
namespace SGF{
typedef CList<CMyString> stringList_t;
typedef CList<CMyString*> stringListPtr_t;
typedef CMyString *strPtr_t;


/*
================
idListSortCompare<strPtr_t>

Compares two pointers to strings. Used to sort a list of string pointers alphabetically in CList<CMyString>::Sort.
================
*/
template<>
SGF_INLINE_FORCED int CListSortCompare<strPtr_t>( const strPtr_t *a, const strPtr_t *b ) {
	return ( *a )->Icmp( **b );
}

/*
================
stringList_t::Sort

Sorts the list of strings alphabetically. Creates a list of pointers to the actual strings and sorts the
pointer list. Then copies the strings into another list using the ordered list of pointers.
================
*/
template<>
SGF_INLINE_FORCED void stringList_t::sort( cmp_t *compare ) {
	int i;

	if ( !m_iNum ) {
		return;
	}

	CList<CMyString>		other;
	CList<strPtr_t>	pointerList;

	pointerList.setNum( m_iNum );
	for( i = 0; i < m_iNum; i++ ) {
		pointerList[ i ] = &( *this )[ i ];
	}

	pointerList.sort();

	other.setNum( m_iNum );
	other.setGranularity( m_iGranularity );
	for( i = 0; i < other.getNum(); i++ ) {
		other[ i ] = *pointerList[ i ];
	}

	this->swapList( other );
}

/*
================
stringList_t::SortSubSection

Sorts a subsection of the list of strings alphabetically.
================
*/
template<>
SGF_INLINE_FORCED void stringList_t::sortSubSection( int startIndex, int endIndex, cmp_t *compare ) {
	int i, s;

	if ( !m_iNum ) {
		return;
	}
	if ( startIndex < 0 ) {
		startIndex = 0;
	}
	if ( endIndex >= m_iNum ) {
		endIndex = m_iNum - 1;
	}
	if ( startIndex >= endIndex ) {
		return;
	}

	CList<CMyString>		other;
	CList<strPtr_t>	pointerList;

	s = endIndex - startIndex + 1;
	other.setNum( s );
	pointerList.setNum( s );
	for( i = 0; i < s; i++ ) {
		other[ i ] = ( *this )[ startIndex + i ];
		pointerList[ i ] = &other[ i ];
	}

	pointerList.sort();

	for( i = 0; i < s; i++ ) {
		(*this)[ startIndex + i ] = *pointerList[ i ];
	}
}

/*
================
stringList_t::Size
================
*/
template<>
SGF_INLINE_FORCED size_t stringList_t::getSize( void ) const {
	size_t s;
	int i;

	s = sizeof( *this );
	for( i = 0; i < getNum(); i++ ) {
		s += ( *this )[ i ].Size();
	}

	return s;
}

/*
===============================================================================

	stringList_t path sorting

===============================================================================
*/

/*
================
idListSortComparePaths

Compares two pointers to strings. Used to sort a list of string pointers alphabetically in CList<CMyString>::Sort.
================
*/
template<class strPtr_t>
SGF_INLINE_FORCED int idListSortComparePaths( const strPtr_t *a, const strPtr_t *b ) {
	return ( *a )->IcmpPath( **b );
}

/*
================
stringList_tSortPaths

Sorts the list of path strings alphabetically and makes sure folders come first.
================
*/
SGF_INLINE_FORCED void stringList_tSortPaths( stringList_t &list ) {
	int i;

	if ( !list.getNum() ) {
		return;
	}

	CList<CMyString>		other;
	CList<strPtr_t>	pointerList;

	pointerList.setNum( list.getNum() );
	for( i = 0; i < list.getNum(); i++ ) {
		pointerList[ i ] = &list[ i ];
	}

	pointerList.sort( idListSortComparePaths<strPtr_t> );

	other.setNum( list.getNum() );
	other.setGranularity( list.getGranularity() );
	for( i = 0; i < other.getNum(); i++ ) {
		other[ i ] = *pointerList[ i ];
	}

	list.swapList( other );
}
} //end SGF
#endif /* !__STRLIST_H__ */
