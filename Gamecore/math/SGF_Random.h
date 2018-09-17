/*
  SGF - Super Game Fabric  Super Game Fabric
  Copyright (C) 2010-2011 Rasputtim <raputtim@hotmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the freeMem Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the freeMem Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

  */

#ifndef __MATH_RANDOM_H__
#define __MATH_RANDOM_H__
#include "../SGF_Config.h"
#include "SGF_Math.h"

namespace SGF {
/*
===============================================================================

	Random number generator

===============================================================================
*/

class CRamdom {
public:
						CRamdom( int seed = 0 );

	void				SetSeed( int seed );
	int					GetSeed() const;

	int					RandomInt();			// random integer in the range [0, MAX_RAND]
	int					RandomInt( int max );		// random integer in the range [0, max[
	float				RandomFloat();		// random number in the range [0.0f, 1.0f]
	float				CRandomFloat();		// random number in the range [-1.0f, 1.0f]

	static const int	MAX_RAND = 0x7fff;

private:
	int					seed;
};

SGF_INLINE_FORCED CRamdom::CRamdom( int seed ) {
	this->seed = seed;
}

SGF_INLINE_FORCED void CRamdom::SetSeed( int seed ) {
	this->seed = seed;
}

SGF_INLINE_FORCED int CRamdom::GetSeed() const {
	return seed;
}

SGF_INLINE_FORCED int CRamdom::RandomInt() {
	seed = 69069 * seed + 1;
	return ( seed & CRamdom::MAX_RAND );
}

SGF_INLINE_FORCED int CRamdom::RandomInt( int max ) {
	if ( max == 0 ) {
		return 0;			// avoid divide by zero error
	}
	return RandomInt() % max;
}

SGF_INLINE_FORCED float CRamdom::RandomFloat() {
	return ( RandomInt() / ( float )( CRamdom::MAX_RAND + 1 ) );
}

SGF_INLINE_FORCED float CRamdom::CRandomFloat() {
	return ( 2.0f * ( RandomFloat() - 0.5f ) );
}


/*
===============================================================================

	Random number generator

===============================================================================
*/

class idRandom2 {
public:
							idRandom2( unsigned long seed = 0 );

	void					SetSeed( unsigned long seed );
	unsigned long			GetSeed() const;

	int						RandomInt();			// random integer in the range [0, MAX_RAND]
	int						RandomInt( int max );		// random integer in the range [0, max]
	float					RandomFloat();		// random number in the range [0.0f, 1.0f]
	float					CRandomFloat();		// random number in the range [-1.0f, 1.0f]

	static const int		MAX_RAND = 0x7fff;

private:
	unsigned long			seed;

	static const unsigned long	IEEE_ONE = 0x3f800000;
	static const unsigned long	IEEE_MASK = 0x007fffff;
};

SGF_INLINE_FORCED idRandom2::idRandom2( unsigned long seed ) {
	this->seed = seed;
}

SGF_INLINE_FORCED void idRandom2::SetSeed( unsigned long seed ) {
	this->seed = seed;
}

SGF_INLINE_FORCED unsigned long idRandom2::GetSeed() const {
	return seed;
}

SGF_INLINE_FORCED int idRandom2::RandomInt() {
	seed = 1664525L * seed + 1013904223L;
	return ( (int) seed & idRandom2::MAX_RAND );
}

SGF_INLINE_FORCED int idRandom2::RandomInt( int max ) {
	if ( max == 0 ) {
		return 0;		// avoid divide by zero error
	}
	return ( RandomInt() >> ( 16 - CMath::BitsForInteger( max ) ) ) % max;
}

SGF_INLINE_FORCED float idRandom2::RandomFloat() {
	unsigned long i;
	seed = 1664525L * seed + 1013904223L;
	i = idRandom2::IEEE_ONE | ( seed & idRandom2::IEEE_MASK );
	return ( ( *(float *)&i ) - 1.0f );
}

SGF_INLINE_FORCED float idRandom2::CRandomFloat() {
	unsigned long i;
	seed = 1664525L * seed + 1013904223L;
	i = idRandom2::IEEE_ONE | ( seed & idRandom2::IEEE_MASK );
	return ( 2.0f * ( *(float *)&i ) - 3.0f );
}
} //end SGF
#endif /* !__MATH_RANDOM_H__ */
