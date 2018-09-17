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

#ifndef __MATH_PLUECKER_H__
#define __MATH_PLUECKER_H__
#include "../SGF_Config.h"
#include "SGF_Vector.h"
#include "SGF_Matriz.h"
#include "SGF_Angles.h"
#include "../util/SGF_StringUtils.h"

namespace SGF{
/*
===============================================================================

	Pluecker coordinate

===============================================================================
*/

class CPluecker {
public:	
					CPluecker();
					explicit CPluecker( const float *a );
					explicit CPluecker( const CVector3D &start, const CVector3D &end );
					explicit CPluecker( const float a1, const float a2, const float a3, const float a4, const float a5, const float a6 );

	float			operator[]( const int index ) const;
	float &			operator[]( const int index );
	CPluecker		operator-() const;											// flips the direction
	CPluecker		operator*( const float a ) const;
	CPluecker		operator/( const float a ) const;
	float			operator*( const CPluecker &a ) const;						// permuted inner product
	CPluecker		operator-( const CPluecker &a ) const;
	CPluecker		operator+( const CPluecker &a ) const;
	CPluecker &	operator*=( const float a );
	CPluecker &	operator/=( const float a );
	CPluecker &	operator+=( const CPluecker &a );
	CPluecker &	operator-=( const CPluecker &a );

	bool			Compare( const CPluecker &a ) const;						// exact compare, no epsilon
	bool			Compare( const CPluecker &a, const float epsilon ) const;	// compare with epsilon
	bool			operator==(	const CPluecker &a ) const;					// exact compare, no epsilon
	bool			operator!=(	const CPluecker &a ) const;					// exact compare, no epsilon

	void 			Set( const float a1, const float a2, const float a3, const float a4, const float a5, const float a6 );
	void			Zero();

	void			FromLine( const CVector3D &start, const CVector3D &end );			// pluecker from line
	void			FromRay( const CVector3D &start, const CVector3D &dir );			// pluecker from ray
	bool			FromPlanes( const CPlane &p1, const CPlane &p2 );			// pluecker from intersection of planes
	bool			ToLine( CVector3D &start, CVector3D &end ) const;					// pluecker to line
	bool			ToRay( CVector3D &start, CVector3D &dir ) const;					// pluecker to ray
	void			ToDir( CVector3D &dir ) const;									// pluecker to direction
	float			PermutedInnerProduct( const CPluecker &a ) const;			// pluecker permuted inner product
	float			Distance3DSqr( const CPluecker &a ) const;					// pluecker line distance

	float			Length() const;										// pluecker length
	float			LengthSqr() const;									// pluecker squared length
	CPluecker		Normalize() const;									// pluecker normalize
	float			NormalizeSelf();										// pluecker normalize

	int				GetDimension() const;

	const float *	ToFloatPtr() const;
	float *			ToFloatPtr();
	const char *	ToString( int precision = 2 ) const;

private:
	float			p[6];
};

extern CPluecker pluecker_origin;
#define pluecker_zero pluecker_origin

SGF_INLINE_FORCED CPluecker::CPluecker() {
}

SGF_INLINE_FORCED CPluecker::CPluecker( const float *a ) {
	memcpy( p, a, 6 * sizeof( float ) );
}

SGF_INLINE_FORCED CPluecker::CPluecker( const CVector3D &start, const CVector3D &end ) {
	FromLine( start, end );
}

SGF_INLINE_FORCED CPluecker::CPluecker( const float a1, const float a2, const float a3, const float a4, const float a5, const float a6 ) {
	p[0] = a1;
	p[1] = a2;
	p[2] = a3;
	p[3] = a4;
	p[4] = a5;
	p[5] = a6;
}

SGF_INLINE_FORCED CPluecker CPluecker::operator-() const {
	return CPluecker( -p[0], -p[1], -p[2], -p[3], -p[4], -p[5] );
}

SGF_INLINE_FORCED float CPluecker::operator[]( const int index ) const {
	return p[index];
}

SGF_INLINE_FORCED float &CPluecker::operator[]( const int index ) {
	return p[index];
}

SGF_INLINE_FORCED CPluecker CPluecker::operator*( const float a ) const {
	return CPluecker( p[0]*a, p[1]*a, p[2]*a, p[3]*a, p[4]*a, p[5]*a );
}

SGF_INLINE_FORCED float CPluecker::operator*( const CPluecker &a ) const {
	return p[0] * a.p[4] + p[1] * a.p[5] + p[2] * a.p[3] + p[4] * a.p[0] + p[5] * a.p[1] + p[3] * a.p[2];
}

SGF_INLINE_FORCED CPluecker CPluecker::operator/( const float a ) const {
	float inva;

	assert( a != 0.0f );
	inva = 1.0f / a;
	return CPluecker( p[0]*inva, p[1]*inva, p[2]*inva, p[3]*inva, p[4]*inva, p[5]*inva );
}

SGF_INLINE_FORCED CPluecker CPluecker::operator+( const CPluecker &a ) const {
	return CPluecker( p[0] + a[0], p[1] + a[1], p[2] + a[2], p[3] + a[3], p[4] + a[4], p[5] + a[5] );
}

SGF_INLINE_FORCED CPluecker CPluecker::operator-( const CPluecker &a ) const {
	return CPluecker( p[0] - a[0], p[1] - a[1], p[2] - a[2], p[3] - a[3], p[4] - a[4], p[5] - a[5] );
}

SGF_INLINE_FORCED CPluecker &CPluecker::operator*=( const float a ) {
	p[0] *= a;
	p[1] *= a;
	p[2] *= a;
	p[3] *= a;
	p[4] *= a;
	p[5] *= a;
	return *this;
}

SGF_INLINE_FORCED CPluecker &CPluecker::operator/=( const float a ) {
	float inva;

	assert( a != 0.0f );
	inva = 1.0f / a;
	p[0] *= inva;
	p[1] *= inva;
	p[2] *= inva;
	p[3] *= inva;
	p[4] *= inva;
	p[5] *= inva;
	return *this;
}

SGF_INLINE_FORCED CPluecker &CPluecker::operator+=( const CPluecker &a ) {
	p[0] += a[0];
	p[1] += a[1];
	p[2] += a[2];
	p[3] += a[3];
	p[4] += a[4];
	p[5] += a[5];
	return *this;
}

SGF_INLINE_FORCED CPluecker &CPluecker::operator-=( const CPluecker &a ) {
	p[0] -= a[0];
	p[1] -= a[1];
	p[2] -= a[2];
	p[3] -= a[3];
	p[4] -= a[4];
	p[5] -= a[5];
	return *this;
}

SGF_INLINE_FORCED bool CPluecker::Compare( const CPluecker &a ) const {
	return ( ( p[0] == a[0] ) && ( p[1] == a[1] ) && ( p[2] == a[2] ) &&
			( p[3] == a[3] ) && ( p[4] == a[4] ) && ( p[5] == a[5] ) );
}

SGF_INLINE_FORCED bool CPluecker::Compare( const CPluecker &a, const float epsilon ) const {
	if ( CMath::Fabs( p[0] - a[0] ) > epsilon ) {
		return false;
	}
			
	if ( CMath::Fabs( p[1] - a[1] ) > epsilon ) {
		return false;
	}

	if ( CMath::Fabs( p[2] - a[2] ) > epsilon ) {
		return false;
	}

	if ( CMath::Fabs( p[3] - a[3] ) > epsilon ) {
		return false;
	}

	if ( CMath::Fabs( p[4] - a[4] ) > epsilon ) {
		return false;
	}

	if ( CMath::Fabs( p[5] - a[5] ) > epsilon ) {
		return false;
	}

	return true;
}

SGF_INLINE_FORCED bool CPluecker::operator==( const CPluecker &a ) const {
	return Compare( a );
}

SGF_INLINE_FORCED bool CPluecker::operator!=( const CPluecker &a ) const {
	return !Compare( a );
}

SGF_INLINE_FORCED void CPluecker::Set( const float a1, const float a2, const float a3, const float a4, const float a5, const float a6 ) {
	p[0] = a1;
	p[1] = a2;
	p[2] = a3;
	p[3] = a4;
	p[4] = a5;
	p[5] = a6;
}

SGF_INLINE_FORCED void CPluecker::Zero() {
	p[0] = p[1] = p[2] = p[3] = p[4] = p[5] = 0.0f;
}

SGF_INLINE_FORCED void CPluecker::FromLine( const CVector3D &start, const CVector3D &end ) {
	p[0] = start[0] * end[1] - end[0] * start[1];
	p[1] = start[0] * end[2] - end[0] * start[2];
	p[2] = start[0] - end[0];
	p[3] = start[1] * end[2] - end[1] * start[2];
	p[4] = start[2] - end[2];
	p[5] = end[1] - start[1];
}

SGF_INLINE_FORCED void CPluecker::FromRay( const CVector3D &start, const CVector3D &dir ) {
	p[0] = start[0] * dir[1] - dir[0] * start[1];
	p[1] = start[0] * dir[2] - dir[0] * start[2];
	p[2] = -dir[0];
	p[3] = start[1] * dir[2] - dir[1] * start[2];
	p[4] = -dir[2];
	p[5] = dir[1];
}

SGF_INLINE_FORCED bool CPluecker::ToLine( CVector3D &start, CVector3D &end ) const {
	CVector3D dir1, dir2;
	float d;

	dir1[0] = p[3];
	dir1[1] = -p[1];
	dir1[2] = p[0];

	dir2[0] = -p[2];
	dir2[1] = p[5];
	dir2[2] = -p[4];

	d = dir2 * dir2;
	if ( d == 0.0f ) {
		return false; // pluecker coordinate does not represent a line
	}

	start = dir2.Cross(dir1) * (1.0f / d);
	end = start + dir2;
	return true;
}

SGF_INLINE_FORCED bool CPluecker::ToRay( CVector3D &start, CVector3D &dir ) const {
	CVector3D dir1;
	float d;

	dir1[0] = p[3];
	dir1[1] = -p[1];
	dir1[2] = p[0];

	dir[0] = -p[2];
	dir[1] = p[5];
	dir[2] = -p[4];

	d = dir * dir;
	if ( d == 0.0f ) {
		return false; // pluecker coordinate does not represent a line
	}

	start = dir.Cross(dir1) * (1.0f / d);
	return true;
}

SGF_INLINE_FORCED void CPluecker::ToDir( CVector3D &dir ) const {
	dir[0] = -p[2];
	dir[1] = p[5];
	dir[2] = -p[4];
}

SGF_INLINE_FORCED float CPluecker::PermutedInnerProduct( const CPluecker &a ) const {
	return p[0] * a.p[4] + p[1] * a.p[5] + p[2] * a.p[3] + p[4] * a.p[0] + p[5] * a.p[1] + p[3] * a.p[2];
}

SGF_INLINE_FORCED float CPluecker::Length() const {
	return ( float )CMath::Sqrt( p[5] * p[5] + p[4] * p[4] + p[2] * p[2] );
}

SGF_INLINE_FORCED float CPluecker::LengthSqr() const {
	return ( p[5] * p[5] + p[4] * p[4] + p[2] * p[2] );
}

SGF_INLINE_FORCED float CPluecker::NormalizeSelf() {
	float l, d;

	l = LengthSqr();
	if ( l == 0.0f ) {
		return l; // pluecker coordinate does not represent a line
	}
	d = CMath::InvSqrt( l );
	p[0] *= d;
	p[1] *= d;
	p[2] *= d;
	p[3] *= d;
	p[4] *= d;
	p[5] *= d;
	return d * l;
}

SGF_INLINE_FORCED CPluecker CPluecker::Normalize() const {
	float d;

	d = LengthSqr();
	if ( d == 0.0f ) {
		return *this; // pluecker coordinate does not represent a line
	}
	d = CMath::InvSqrt( d );
	return CPluecker( p[0]*d, p[1]*d, p[2]*d, p[3]*d, p[4]*d, p[5]*d );
}

SGF_INLINE_FORCED int CPluecker::GetDimension() const {
	return 6;
}

SGF_INLINE_FORCED const float *CPluecker::ToFloatPtr() const {
	return p;
}

SGF_INLINE_FORCED float *CPluecker::ToFloatPtr() {
	return p;
}
} //end SGF
#endif /* !__MATH_PLUECKER_H__ */
