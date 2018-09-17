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

#ifndef __VECTORSET_H__
#define __VECTORSET_H__

/*
===============================================================================

	Vector Set

	Creates a set of vectors without duplicates.

===============================================================================
*/

template< class type, int dimension >
class idVectorSet : public CList<type> {
public:
							idVectorSet( void );
							idVectorSet( const type &mins, const type &maxs, const int boxHashSize, const int initialSize );

							// returns total size of allocated memory
	size_t					Allocated( void ) const { return CList<type>::Allocated() + hash.Allocated(); }
							// returns total size of allocated memory including size of type
	size_t					Size( void ) const { return sizeof( *this ) + Allocated(); }

	void					Init( const type &mins, const type &maxs, const int boxHashSize, const int initialSize );
	void					ResizeIndex( const int newSize );
	void					Clear( void );

	int						FindVector( const type &v, const float epsilon );

private:
	idHashIndex				hash;
	type					mins;
	type					maxs;
	int						boxHashSize;
	float					boxInvSize[dimension];
	float					boxHalfSize[dimension];
};

template< class type, int dimension >
SGF_INLINE_FORCED idVectorSet<type,dimension>::idVectorSet( void ) {
	hash.Clear( CMath::IPow( boxHashSize, dimension ), 128 );
	boxHashSize = 16;
	memset( boxInvSize, 0, dimension * sizeof( boxInvSize[0] ) );
	memset( boxHalfSize, 0, dimension * sizeof( boxHalfSize[0] ) );
}

template< class type, int dimension >
SGF_INLINE_FORCED idVectorSet<type,dimension>::idVectorSet( const type &mins, const type &maxs, const int boxHashSize, const int initialSize ) {
	Init( mins, maxs, boxHashSize, initialSize );
}

template< class type, int dimension >
SGF_INLINE_FORCED void idVectorSet<type,dimension>::Init( const type &mins, const type &maxs, const int boxHashSize, const int initialSize ) {
	int i;
	float boxSize;

	CList<type>::AssureSize( initialSize );
	CList<type>::SetNum( 0, false );

	hash.Clear( CMath::IPow( boxHashSize, dimension ), initialSize );

	this->mins = mins;
	this->maxs = maxs;
	this->boxHashSize = boxHashSize;

	for ( i = 0; i < dimension; i++ ) {
		boxSize = ( maxs[i] - mins[i] ) / (float) boxHashSize;
		boxInvSize[i] = 1.0f / boxSize;
		boxHalfSize[i] = boxSize * 0.5f;
	}
}

template< class type, int dimension >
SGF_INLINE_FORCED void idVectorSet<type,dimension>::ResizeIndex( const int newSize ) {
	CList<type>::Resize( newSize );
	hash.ResizeIndex( newSize );
}

template< class type, int dimension >
SGF_INLINE_FORCED void idVectorSet<type,dimension>::Clear( void ) {
	CList<type>::Clear();
	hash.Clear();
}

template< class type, int dimension >
SGF_INLINE_FORCED int idVectorSet<type,dimension>::FindVector( const type &v, const float epsilon ) {
	int i, j, k, hashKey, partialHashKey[dimension];

	for ( i = 0; i < dimension; i++ ) {
		assert( epsilon <= boxHalfSize[i] );
		partialHashKey[i] = (int) ( ( v[i] - mins[i] - boxHalfSize[i] ) * boxInvSize[i] );
	}

	for ( i = 0; i < ( 1 << dimension ); i++ ) {

		hashKey = 0;
		for ( j = 0; j < dimension; j++ ) {
			hashKey *= boxHashSize;
			hashKey += partialHashKey[j] + ( ( i >> j ) & 1 );
		}

		for ( j = hash.First( hashKey ); j >= 0; j = hash.Next( j ) ) {
			const type &lv = (*this)[j];
			for ( k = 0; k < dimension; k++ ) {
				if ( CMath::Fabs( lv[k] - v[k] ) > epsilon ) {
					break;
				}
			}
			if ( k >= dimension ) {
				return j;
			}
		}
	}

	hashKey = 0;
	for ( i = 0; i < dimension; i++ ) {
		hashKey *= boxHashSize;
		hashKey += (int) ( ( v[i] - mins[i] ) * boxInvSize[i] );
	}

	hash.Add( hashKey, CList<type>::Num() );
	this->Append( v );
	return CList<type>::Num()-1;
}


/*
===============================================================================

	Vector Subset

	Creates a subset without duplicates from an existing list with vectors.

===============================================================================
*/

template< class type, int dimension >
class idVectorSubset {
public:
							idVectorSubset( void );
							idVectorSubset( const type &mins, const type &maxs, const int boxHashSize, const int initialSize );

							// returns total size of allocated memory
	size_t					Allocated( void ) const { return CList<type>::Allocated() + hash.Allocated(); }
							// returns total size of allocated memory including size of type
	size_t					Size( void ) const { return sizeof( *this ) + Allocated(); }

	void					Init( const type &mins, const type &maxs, const int boxHashSize, const int initialSize );
	void					Clear( void );

							// returns either vectorNum or an index to a previously found vector
	int						FindVector( const type *vectorList, const int vectorNum, const float epsilon );

private:
	idHashIndex				hash;
	type					mins;
	type					maxs;
	int						boxHashSize;
	float					boxInvSize[dimension];
	float					boxHalfSize[dimension];
};

template< class type, int dimension >
SGF_INLINE_FORCED idVectorSubset<type,dimension>::idVectorSubset( void ) {
	hash.Clear( CMath::IPow( boxHashSize, dimension ), 128 );
	boxHashSize = 16;
	memset( boxInvSize, 0, dimension * sizeof( boxInvSize[0] ) );
	memset( boxHalfSize, 0, dimension * sizeof( boxHalfSize[0] ) );
}

template< class type, int dimension >
SGF_INLINE_FORCED idVectorSubset<type,dimension>::idVectorSubset( const type &mins, const type &maxs, const int boxHashSize, const int initialSize ) {
	Init( mins, maxs, boxHashSize, initialSize );
}

template< class type, int dimension >
SGF_INLINE_FORCED void idVectorSubset<type,dimension>::Init( const type &mins, const type &maxs, const int boxHashSize, const int initialSize ) {
	int i;
	float boxSize;

	hash.Clear( CMath::IPow( boxHashSize, dimension ), initialSize );

	this->mins = mins;
	this->maxs = maxs;
	this->boxHashSize = boxHashSize;

	for ( i = 0; i < dimension; i++ ) {
		boxSize = ( maxs[i] - mins[i] ) / (float) boxHashSize;
		boxInvSize[i] = 1.0f / boxSize;
		boxHalfSize[i] = boxSize * 0.5f;
	}
}

template< class type, int dimension >
SGF_INLINE_FORCED void idVectorSubset<type,dimension>::Clear( void ) {
	CList<type>::Clear();
	hash.Clear();
}

template< class type, int dimension >
SGF_INLINE_FORCED int idVectorSubset<type,dimension>::FindVector( const type *vectorList, const int vectorNum, const float epsilon ) {
	int i, j, k, hashKey, partialHashKey[dimension];
	const type &v = vectorList[vectorNum];

	for ( i = 0; i < dimension; i++ ) {
		assert( epsilon <= boxHalfSize[i] );
		partialHashKey[i] = (int) ( ( v[i] - mins[i] - boxHalfSize[i] ) * boxInvSize[i] );
	}

	for ( i = 0; i < ( 1 << dimension ); i++ ) {

		hashKey = 0;
		for ( j = 0; j < dimension; j++ ) {
			hashKey *= boxHashSize;
			hashKey += partialHashKey[j] + ( ( i >> j ) & 1 );
		}

		for ( j = hash.First( hashKey ); j >= 0; j = hash.Next( j ) ) {
			const type &lv = vectorList[j];
			for ( k = 0; k < dimension; k++ ) {
				if ( CMath::Fabs( lv[k] - v[k] ) > epsilon ) {
					break;
				}
			}
			if ( k >= dimension ) {
				return j;
			}
		}
	}

	hashKey = 0;
	for ( i = 0; i < dimension; i++ ) {
		hashKey *= boxHashSize;
		hashKey += (int) ( ( v[i] - mins[i] ) * boxInvSize[i] );
	}

	hash.Add( hashKey, vectorNum );
	return vectorNum;
}

#endif /* !__VECTORSET_H__ */
