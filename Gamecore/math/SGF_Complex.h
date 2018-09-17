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

#ifndef __MATH_COMPLEX_H__
#define __MATH_COMPLEX_H__
#include "../SGF_Config.h"
#include "SGF_Math.h"
/*
===============================================================================

  Complex number

===============================================================================
*/
namespace SGF {
class CComplex {
public:
	float				r;		// real part
	float				i;		// imaginary part

						CComplex();
						CComplex( const float r, const float i );

	void 				Set( const float r, const float i );
	void				Zero();

	float				operator[]( int index ) const;
	float &				operator[]( int index );

	CComplex			operator-() const;
	CComplex &			operator=( const CComplex &a );

	CComplex			operator*( const CComplex &a ) const;
	CComplex			operator/( const CComplex &a ) const;
	CComplex			operator+( const CComplex &a ) const;
	CComplex			operator-( const CComplex &a ) const;

	CComplex &			operator*=( const CComplex &a );
	CComplex &			operator/=( const CComplex &a );
	CComplex &			operator+=( const CComplex &a );
	CComplex &			operator-=( const CComplex &a );

	CComplex			operator*( const float a ) const;
	CComplex			operator/( const float a ) const;
	CComplex			operator+( const float a ) const;
	CComplex			operator-( const float a ) const;

	CComplex &			operator*=( const float a );
	CComplex &			operator/=( const float a );
	CComplex &			operator+=( const float a );
	CComplex &			operator-=( const float a );

	friend CComplex	operator*( const float a, const CComplex &b );
	friend CComplex	operator/( const float a, const CComplex &b );
	friend CComplex	operator+( const float a, const CComplex &b );
	friend CComplex	operator-( const float a, const CComplex &b );

	bool				Compare( const CComplex &a ) const;						// exact compare, no epsilon
	bool				Compare( const CComplex &a, const float epsilon ) const;	// compare with epsilon
	bool				operator==(	const CComplex &a ) const;						// exact compare, no epsilon
	bool				operator!=(	const CComplex &a ) const;						// exact compare, no epsilon

	CComplex			Reciprocal() const;
	CComplex			Sqrt() const;
	float				Abs() const;

	int					GetDimension() const;

	const float *		ToFloatPtr() const;
	float *				ToFloatPtr();
	const char *		ToString( int precision = 2 ) const;
};

extern CComplex complex_origin;
#define complex_zero complex_origin

SGF_INLINE_FORCED CComplex::CComplex() {
}

SGF_INLINE_FORCED CComplex::CComplex( const float r, const float i ) {
	this->r = r;
	this->i = i;
}

SGF_INLINE_FORCED void CComplex::Set( const float r, const float i ) {
	this->r = r;
	this->i = i;
}

SGF_INLINE_FORCED void CComplex::Zero() {
	r = i = 0.0f;
}

SGF_INLINE_FORCED float CComplex::operator[]( int index ) const {
	assert( index >= 0 && index < 2 );
	return ( &r )[ index ];
}

SGF_INLINE_FORCED float& CComplex::operator[]( int index ) {
	assert( index >= 0 && index < 2 );
	return ( &r )[ index ];
}

SGF_INLINE_FORCED CComplex CComplex::operator-() const {
	return CComplex( -r, -i );
}

SGF_INLINE_FORCED CComplex &CComplex::operator=( const CComplex &a ) {
	r = a.r;
	i = a.i;
	return *this;
}

SGF_INLINE_FORCED CComplex CComplex::operator*( const CComplex &a ) const {
	return CComplex( r * a.r - i * a.i, i * a.r + r * a.i );
}

SGF_INLINE_FORCED CComplex CComplex::operator/( const CComplex &a ) const {
	float s, t;
	if ( CMath::Fabs( a.r ) >= CMath::Fabs( a.i ) ) {
		s = a.i / a.r;
		t = 1.0f / ( a.r + s * a.i );
		return CComplex( ( r + s * i ) * t, ( i - s * r ) * t );
	} else {
		s = a.r / a.i;
		t = 1.0f / ( s * a.r + a.i );
		return CComplex( ( r * s + i ) * t, ( i * s - r ) * t );
	}
}

SGF_INLINE_FORCED CComplex CComplex::operator+( const CComplex &a ) const {
	return CComplex( r + a.r, i + a.i );
}

SGF_INLINE_FORCED CComplex CComplex::operator-( const CComplex &a ) const {
	return CComplex( r - a.r, i - a.i );
}

SGF_INLINE_FORCED CComplex &CComplex::operator*=( const CComplex &a ) {
	*this = CComplex( r * a.r - i * a.i, i * a.r + r * a.i );
	return *this;
}

SGF_INLINE_FORCED CComplex &CComplex::operator/=( const CComplex &a ) {
	float s, t;
	if ( CMath::Fabs( a.r ) >= CMath::Fabs( a.i ) ) {
		s = a.i / a.r;
		t = 1.0f / ( a.r + s * a.i );
		*this = CComplex( ( r + s * i ) * t, ( i - s * r ) * t );
	} else {
		s = a.r / a.i;
		t = 1.0f / ( s * a.r + a.i );
		*this = CComplex( ( r * s + i ) * t, ( i * s - r ) * t );
	}
	return *this;
}

SGF_INLINE_FORCED CComplex &CComplex::operator+=( const CComplex &a ) {
	r += a.r;
	i += a.i;
	return *this;
}

SGF_INLINE_FORCED CComplex &CComplex::operator-=( const CComplex &a ) {
	r -= a.r;
	i -= a.i;
	return *this;
}

SGF_INLINE_FORCED CComplex CComplex::operator*( const float a ) const {
	return CComplex( r * a, i * a );
}

SGF_INLINE_FORCED CComplex CComplex::operator/( const float a ) const {
	float s = 1.0f / a;
	return CComplex( r * s, i * s );
}

SGF_INLINE_FORCED CComplex CComplex::operator+( const float a ) const {
	return CComplex( r + a, i );
}

SGF_INLINE_FORCED CComplex CComplex::operator-( const float a ) const {
	return CComplex( r - a, i );
}

SGF_INLINE_FORCED CComplex &CComplex::operator*=( const float a ) {
	r *= a;
	i *= a;
	return *this;
}

SGF_INLINE_FORCED CComplex &CComplex::operator/=( const float a ) {
	float s = 1.0f / a;
	r *= s;
	i *= s;
	return *this;
}

SGF_INLINE_FORCED CComplex &CComplex::operator+=( const float a ) {
	r += a;
	return *this;
}

SGF_INLINE_FORCED CComplex &CComplex::operator-=( const float a ) {
	r -= a;
	return *this;
}

SGF_INLINE_FORCED CComplex operator*( const float a, const CComplex &b ) {
	return CComplex( a * b.r, a * b.i );
}

SGF_INLINE_FORCED CComplex operator/( const float a, const CComplex &b ) {
	float s, t;
	if ( CMath::Fabs( b.r ) >= CMath::Fabs( b.i ) ) {
		s = b.i / b.r;
		t = a / ( b.r + s * b.i );
		return CComplex( t, - s * t );
	} else {
		s = b.r / b.i;
		t = a / ( s * b.r + b.i );
		return CComplex( s * t, - t );
	}
}

SGF_INLINE_FORCED CComplex operator+( const float a, const CComplex &b ) {
	return CComplex( a + b.r, b.i );
}

SGF_INLINE_FORCED CComplex operator-( const float a, const CComplex &b ) {
	return CComplex( a - b.r, -b.i );
}

SGF_INLINE_FORCED CComplex CComplex::Reciprocal() const {
	float s, t;
	if ( CMath::Fabs( r ) >= CMath::Fabs( i ) ) {
		s = i / r;
		t = 1.0f / ( r + s * i );
		return CComplex( t, - s * t );
	} else {
		s = r / i;
		t = 1.0f / ( s * r + i );
		return CComplex( s * t, - t );
	}
}

SGF_INLINE_FORCED CComplex CComplex::Sqrt() const {
	float x, y, w;

	if ( r == 0.0f && i == 0.0f ) {
		return CComplex( 0.0f, 0.0f );
	}
	x = CMath::Fabs( r );
	y = CMath::Fabs( i );
	if ( x >= y ) {
		w = y / x;
		w = CMath::Sqrt( x ) * CMath::Sqrt( 0.5f * ( 1.0f + CMath::Sqrt( 1.0f + w * w ) ) );
	} else {
		w = x / y;
		w = CMath::Sqrt( y ) * CMath::Sqrt( 0.5f * ( w + CMath::Sqrt( 1.0f + w * w ) ) );
	}
	if ( w == 0.0f ) {
		return CComplex( 0.0f, 0.0f );
	}
	if ( r >= 0.0f ) {
		return CComplex( w, 0.5f * i / w );
	} else {
		return CComplex( 0.5f * y / w, ( i >= 0.0f ) ? w : -w );
	}
}

SGF_INLINE_FORCED float CComplex::Abs() const {
	float x, y, t;
	x = CMath::Fabs( r );
	y = CMath::Fabs( i );
	if ( x == 0.0f ) {
		return y;
	} else if ( y == 0.0f ) {
		return x;
	} else if ( x > y ) {
		t = y / x;
		return x * CMath::Sqrt( 1.0f + t * t );
	} else {
		t = x / y;
		return y * CMath::Sqrt( 1.0f + t * t );
	}
}

SGF_INLINE_FORCED bool CComplex::Compare( const CComplex &a ) const {
	return ( ( r == a.r ) && ( i == a.i ) );
}

SGF_INLINE_FORCED bool CComplex::Compare( const CComplex &a, const float epsilon ) const {
	if ( CMath::Fabs( r - a.r ) > epsilon ) {
		return false;
	}
	if ( CMath::Fabs( i - a.i ) > epsilon ) {
		return false;
	}
	return true;
}

SGF_INLINE_FORCED bool CComplex::operator==( const CComplex &a ) const {
	return Compare( a );
}

SGF_INLINE_FORCED bool CComplex::operator!=( const CComplex &a ) const {
	return !Compare( a );
}

SGF_INLINE_FORCED int CComplex::GetDimension() const {
	return 2;
}

SGF_INLINE_FORCED const float *CComplex::ToFloatPtr() const {
	return &r;
}

SGF_INLINE_FORCED float *CComplex::ToFloatPtr() {
	return &r;
}
} //end SGF
#endif /* !__MATH_COMPLEX_H__ */
