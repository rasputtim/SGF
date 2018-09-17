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


#ifndef __SGF_STATICLIST_H__
#define __SGF_STATICLIST_H__

namespace SGF {
/*
===============================================================================

	Static list template
	A non-growing, memset-able list using no memory allocation.

===============================================================================
*/

template<class ItemType,int size>
class CStaticList {
public:

						CStaticList();
						CStaticList( const CStaticList<ItemType,size> &other );
						~CStaticList<ItemType,size>();

	void				Clear();										// marks the list as empty.  does not deallocate or intialize data.
	int					Num() const;									// returns number of elements in list
	int					Max() const;									// returns the maximum number of elements in the list
	void				SetNum( int newnum );								// set number of elements in list

	size_t				Allocated() const;							// returns total size of allocated memory
	size_t				Size() const;									// returns total size of allocated memory including size of list ItemType
	size_t				MemoryUsed() const;							// returns size of the used elements in the list

	const ItemType &	operator[]( int index ) const;
	ItemType &			operator[]( int index );

	ItemType *			Ptr();										// returns a pointer to the list
	const ItemType *	Ptr() const;									// returns a pointer to the list
	ItemType *			Alloc();										// returns reference to a new data element at the end of the list.  returns NULL when full.
	int					Append( const ItemType & obj );							// append element
	int					Append( const CStaticList<ItemType,size> &other );		// append list
	int					AddUnique( const ItemType & obj );						// add unique element
	int					Insert( const ItemType & obj, int index );				// insert the element at the given index
	int					FindIndex( const ItemType & obj ) const;				// find the index for the given element
	ItemType *			Find( ItemType const & obj ) const;						// find pointer to the given element
	int					FindNull() const;								// find the index for the first NULL pointer in the list
	int					IndexOf( const ItemType *obj ) const;					// returns the index for the pointer to an element in the list
	bool				RemoveIndex( int index );							// remove the element at the given index
	bool				Remove( const ItemType & obj );							// remove the element
	void				Swap( CStaticList<ItemType,size> &other );				// swap the contents of the lists
	void				DeleteContents( bool clear );						// delete the contents of the list

private:
	int					num;
	ItemType 			list[ size ];
};

/*
================
CStaticList<ItemType,size>::CStaticList()
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED CStaticList<ItemType,size>::CStaticList() {
	num = 0;
}

/*
================
CStaticList<ItemType,size>::CStaticList( const CStaticList<ItemType,size> &other )
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED CStaticList<ItemType,size>::CStaticList( const CStaticList<ItemType,size> &other ) {
	*this = other;
}

/*
================
CStaticList<ItemType,size>::~CStaticList<ItemType,size>
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED CStaticList<ItemType,size>::~CStaticList() {
}

/*
================
CStaticList<ItemType,size>::Clear

Sets the number of elements in the list to 0.  Assumes that ItemType automatically handles freeing up memory.
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED void CStaticList<ItemType,size>::Clear() {
	num	= 0;
}

/*
================
CStaticList<ItemType,size>::DeleteContents

Calls the destructor of all elements in the list.  Conditionally frees up memory used by the list.
Note that this only works on lists containing pointers to objects and will cause a compiler error
if called with non-pointers.  Since the list was not responsible for allocating the object, it has
no information on whether the object still exists or not, so care must be taken to ensure that
the pointers are still valid when this function is called.  Function will set all pointers in the
list to NULL.
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED void CStaticList<ItemType,size>::DeleteContents( bool clear ) {
	int i;

	for( i = 0; i < size; i++ ) {
		delete list[ i ];
		list[ i ] = NULL;
	}

	if ( clear ) {
		Clear();
	} else {
		memset( list, 0, sizeof( list ) );
	}
}

/*
================
CStaticList<ItemType,size>::Num

Returns the number of elements currently contained in the list.
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED int CStaticList<ItemType,size>::Num() const {
	return num;
}

/*
================
CStaticList<ItemType,size>::Num

Returns the maximum number of elements in the list.
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED int CStaticList<ItemType,size>::Max() const {
	return size;
}

/*
================
CStaticList<ItemType>::Allocated
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED size_t CStaticList<ItemType,size>::Allocated() const {
	return size * sizeof( ItemType );
}

/*
================
CStaticList<ItemType>::Size
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED size_t CStaticList<ItemType,size>::Size() const {
	return sizeof( CStaticList<ItemType,size> ) + Allocated();
}

/*
================
CStaticList<ItemType,size>::Num
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED size_t CStaticList<ItemType,size>::MemoryUsed() const {
	return num * sizeof( list[ 0 ] );
}

/*
================
CStaticList<ItemType,size>::SetNum

Set number of elements in list.
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED void CStaticList<ItemType,size>::SetNum( int newnum ) {
	assert( newnum >= 0 );
	assert( newnum <= size );
	num = newnum;
}

/*
================
CStaticList<ItemType,size>::operator[] const

Access operator.  Index must be within range or an assert will be issued in debug builds.
Release builds do no range checking.
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED const ItemType &CStaticList<ItemType,size>::operator[]( int index ) const {
	assert( index >= 0 );
	assert( index < num );

	return list[ index ];
}

/*
================
CStaticList<ItemType,size>::operator[]

Access operator.  Index must be within range or an assert will be issued in debug builds.
Release builds do no range checking.
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED ItemType &CStaticList<ItemType,size>::operator[]( int index ) {
	assert( index >= 0 );
	assert( index < num );

	return list[ index ];
}

/*
================
CStaticList<ItemType,size>::Ptr

Returns a pointer to the begining of the array.  Useful for iterating through the list in loops.

Note: may return NULL if the list is empty.

FIXME: Create an iterator template for this kind of thing.
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED ItemType *CStaticList<ItemType,size>::Ptr() {
	return &list[ 0 ];
}

/*
================
CStaticList<ItemType,size>::Ptr

Returns a pointer to the begining of the array.  Useful for iterating through the list in loops.

Note: may return NULL if the list is empty.

FIXME: Create an iterator template for this kind of thing.
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED const ItemType *CStaticList<ItemType,size>::Ptr() const {
	return &list[ 0 ];
}

/*
================
CStaticList<ItemType,size>::Alloc

Returns a pointer to a new data element at the end of the list.
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED ItemType *CStaticList<ItemType,size>::Alloc() {
	if ( num >= size ) {
		return NULL;
	}

	return &list[ num++ ];
}

/*
================
CStaticList<ItemType,size>::Append

Increases the size of the list by one element and copies the supplied data into it.

Returns the index of the new element, or -1 when list is full.
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED int CStaticList<ItemType,size>::Append( ItemType const & obj ) {
	assert( num < size );
	if ( num < size ) {
		list[ num ] = obj;
		num++;
		return num - 1;
	}

	return -1;
}


/*
================
CStaticList<ItemType,size>::Insert

Increases the size of the list by at leat one element if necessary 
and inserts the supplied data into it.

Returns the index of the new element, or -1 when list is full.
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED int CStaticList<ItemType,size>::Insert( ItemType const & obj, int index ) {
	int i;

	assert( num < size );
	if ( num >= size ) {
		return -1;
	}

	assert( index >= 0 );
	if ( index < 0 ) {
		index = 0;
	} else if ( index > num ) {
		index = num;
	}

	for( i = num; i > index; --i ) {
		list[i] = list[i-1];
	}

	num++;
	list[index] = obj;
	return index;
}

/*
================
CStaticList<ItemType,size>::Append

adds the other list to this one

Returns the size of the new combined list
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED int CStaticList<ItemType,size>::Append( const CStaticList<ItemType,size> &other ) {
	int i;
	int n = other.Num();

	if ( num + n > size ) {
		n = size - num;
	}
	for( i = 0; i < n; i++ ) {
		list[i + num] = other.list[i];
	}
	num += n;
	return Num();
}

/*
================
CStaticList<ItemType,size>::AddUnique

Adds the data to the list if it doesn't already exist.  Returns the index of the data in the list.
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED int CStaticList<ItemType,size>::AddUnique( ItemType const & obj ) {
	int index;

	index = FindIndex( obj );
	if ( index < 0 ) {
		index = Append( obj );
	}

	return index;
}

/*
================
CStaticList<ItemType,size>::FindIndex

Searches for the specified data in the list and returns it's index.  Returns -1 if the data is not found.
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED int CStaticList<ItemType,size>::FindIndex( ItemType const & obj ) const {
	int i;

	for( i = 0; i < num; i++ ) {
		if ( list[ i ] == obj ) {
			return i;
		}
	}

	// Not found
	return -1;
}

/*
================
CStaticList<ItemType,size>::Find

Searches for the specified data in the list and returns it's address. Returns NULL if the data is not found.
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED ItemType *CStaticList<ItemType,size>::Find( ItemType const & obj ) const {
	int i;

	i = FindIndex( obj );
	if ( i >= 0 ) {
		return &list[ i ];
	}

	return NULL;
}

/*
================
CStaticList<ItemType,size>::FindNull

Searches for a NULL pointer in the list.  Returns -1 if NULL is not found.

NOTE: This function can only be called on lists containing pointers. Calling it
on non-pointer lists will cause a compiler error.
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED int CStaticList<ItemType,size>::FindNull() const {
	int i;

	for( i = 0; i < num; i++ ) {
		if ( list[ i ] == NULL ) {
			return i;
		}
	}

	// Not found
	return -1;
}

/*
================
CStaticList<ItemType,size>::IndexOf

Takes a pointer to an element in the list and returns the index of the element.
This is NOT a guarantee that the object is really in the list. 
Function will assert in debug builds if pointer is outside the bounds of the list,
but remains silent in release builds.
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED int CStaticList<ItemType,size>::IndexOf( ItemType const *objptr ) const {
	int index;

	index = objptr - list;

	assert( index >= 0 );
	assert( index < num );

	return index;
}

/*
================
CStaticList<ItemType,size>::RemoveIndex

Removes the element at the specified index and moves all data following the element down to fill in the gap.
The number of elements in the list is reduced by one.  Returns false if the index is outside the bounds of the list.
Note that the element is not destroyed, so any memory used by it may not be freed until the destruction of the list.
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED bool CStaticList<ItemType,size>::RemoveIndex( int index ) {
	int i;

	assert( index >= 0 );
	assert( index < num );

	if ( ( index < 0 ) || ( index >= num ) ) {
		return false;
	}

	num--;
	for( i = index; i < num; i++ ) {
		list[ i ] = list[ i + 1 ];
	}

	return true;
}

/*
================
CStaticList<ItemType,size>::Remove

Removes the element if it is found within the list and moves all data following the element down to fill in the gap.
The number of elements in the list is reduced by one.  Returns false if the data is not found in the list.  Note that
the element is not destroyed, so any memory used by it may not be freed until the destruction of the list.
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED bool CStaticList<ItemType,size>::Remove( ItemType const & obj ) {
	int index;

	index = FindIndex( obj );
	if ( index >= 0 ) {
		return RemoveIndex( index );
	}
	
	return false;
}

/*
================
CStaticList<ItemType,size>::Swap

Swaps the contents of two lists
================
*/
template<class ItemType,int size>
SGF_INLINE_FORCED void CStaticList<ItemType,size>::Swap( CStaticList<ItemType,size> &other ) {
	CStaticList<ItemType,size> temp = *this;
	*this = other;
	other = temp;
}
} //end SGF
#endif /* !__STATICLIST_H__ */
