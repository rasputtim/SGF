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


#ifndef __SGF_MATH_VECTOR_H__
#define __SGF_MATH_VECTOR_H__

#include "../SGF_Config.h"
#include "SGF_Math.h"
#include "../util/SGF_Heap.h"
#include "SGF_Random.h"
#include "SGF_Simd.h"

namespace SGF{
class CSIMDProcessor;

/*
===============================================================================

  Vector classes

===============================================================================
*/

#define VECTOR_EPSILON		0.001f

class CAngles;
class CPolar3D;
class CMatriz3D;
class CPolar3D;

//===============================================================
//
//	CVector2D - 2D vector
//
//===============================================================

class CVector2D {
public:
	float			x;
	float			y;

					CVector2D();
					explicit CVector2D( const float x, const float y );

	void 			Set( const float x, const float y );
	void			Zero();

	float			operator[]( int index ) const;
	float &			operator[]( int index );
	CVector2D			operator-() const;
	float			operator*( const CVector2D &a ) const;
	CVector2D			operator*( const float a ) const;
	CVector2D			operator/( const float a ) const;
	CVector2D			operator+( const CVector2D &a ) const;
	CVector2D			operator-( const CVector2D &a ) const;
	CVector2D &		operator+=( const CVector2D &a );
	CVector2D &		operator-=( const CVector2D &a );
	CVector2D &		operator/=( const CVector2D &a );
	CVector2D &		operator/=( const float a );
	CVector2D &		operator*=( const float a );

	friend CVector2D	operator*( const float a, const CVector2D b );

	bool			Compare( const CVector2D &a ) const;							// exact compare, no epsilon
	bool			Compare( const CVector2D &a, const float epsilon ) const;		// compare with epsilon
	bool			operator==(	const CVector2D &a ) const;						// exact compare, no epsilon
	bool			operator!=(	const CVector2D &a ) const;						// exact compare, no epsilon

	float			Length() const;
	float			LengthFast() const;
	float			LengthSqr() const;
	float			Normalize();			// returns length
	float			NormalizeFast();		// returns length
	CVector2D &		Truncate( float length );	// cap length
	void			Clamp( const CVector2D &min, const CVector2D &max );
	void			Snap();				// snap to closest integer value
	void			SnapInt();			// snap towards integer (floor)

	int				GetDimension() const;

	const float *	ToFloatPtr() const;
	float *			ToFloatPtr();
	const char *	ToString( int precision = 2 ) const;

	void			Lerp( const CVector2D &v1, const CVector2D &v2, const float l );
};

extern CVector2D vec2_origin;
#define vec2_zero vec2_origin

SGF_INLINE_FORCED CVector2D::CVector2D() {
}

SGF_INLINE_FORCED CVector2D::CVector2D( const float x, const float y ) {
	this->x = x;
	this->y = y;
}

SGF_INLINE_FORCED void CVector2D::Set( const float x, const float y ) {
	this->x = x;
	this->y = y;
}

SGF_INLINE_FORCED void CVector2D::Zero() {
	x = y = 0.0f;
}

SGF_INLINE_FORCED bool CVector2D::Compare( const CVector2D &a ) const {
	return ( ( x == a.x ) && ( y == a.y ) );
}

SGF_INLINE_FORCED bool CVector2D::Compare( const CVector2D &a, const float epsilon ) const {
	if ( CMath::Fabs( x - a.x ) > epsilon ) {
		return false;
	}
			
	if ( CMath::Fabs( y - a.y ) > epsilon ) {
		return false;
	}

	return true;
}

SGF_INLINE_FORCED bool CVector2D::operator==( const CVector2D &a ) const {
	return Compare( a );
}

SGF_INLINE_FORCED bool CVector2D::operator!=( const CVector2D &a ) const {
	return !Compare( a );
}

SGF_INLINE_FORCED float CVector2D::operator[]( int index ) const {
	return ( &x )[ index ];
}

SGF_INLINE_FORCED float& CVector2D::operator[]( int index ) {
	return ( &x )[ index ];
}

SGF_INLINE_FORCED float CVector2D::Length() const {
	return ( float )CMath::Sqrt( x * x + y * y );
}

SGF_INLINE_FORCED float CVector2D::LengthFast() const {
	float sqrLength;

	sqrLength = x * x + y * y;
	return sqrLength * CMath::RSqrt( sqrLength );
}

SGF_INLINE_FORCED float CVector2D::LengthSqr() const {
	return ( x * x + y * y );
}

SGF_INLINE_FORCED float CVector2D::Normalize() {
	float sqrLength, invLength;

	sqrLength = x * x + y * y;
	invLength = CMath::InvSqrt( sqrLength );
	x *= invLength;
	y *= invLength;
	return invLength * sqrLength;
}

SGF_INLINE_FORCED float CVector2D::NormalizeFast() {
	float lengthSqr, invLength;

	lengthSqr = x * x + y * y;
	invLength = CMath::RSqrt( lengthSqr );
	x *= invLength;
	y *= invLength;
	return invLength * lengthSqr;
}

SGF_INLINE_FORCED CVector2D &CVector2D::Truncate( float length ) {
	float length2;
	float ilength;

	if ( !length ) {
		Zero();
	}
	else {
		length2 = LengthSqr();
		if ( length2 > length * length ) {
			ilength = length * CMath::InvSqrt( length2 );
			x *= ilength;
			y *= ilength;
		}
	}

	return *this;
}

SGF_INLINE_FORCED void CVector2D::Clamp( const CVector2D &min, const CVector2D &max ) {
	if ( x < min.x ) {
		x = min.x;
	} else if ( x > max.x ) {
		x = max.x;
	}
	if ( y < min.y ) {
		y = min.y;
	} else if ( y > max.y ) {
		y = max.y;
	}
}

SGF_INLINE_FORCED void CVector2D::Snap() {
	x = floor( x + 0.5f );
	y = floor( y + 0.5f );
}

SGF_INLINE_FORCED void CVector2D::SnapInt() {
	x = float( int( x ) );
	y = float( int( y ) );
}

SGF_INLINE_FORCED CVector2D CVector2D::operator-() const {
	return CVector2D( -x, -y );
}
	
SGF_INLINE_FORCED CVector2D CVector2D::operator-( const CVector2D &a ) const {
	return CVector2D( x - a.x, y - a.y );
}

SGF_INLINE_FORCED float CVector2D::operator*( const CVector2D &a ) const {
	return x * a.x + y * a.y;
}

SGF_INLINE_FORCED CVector2D CVector2D::operator*( const float a ) const {
	return CVector2D( x * a, y * a );
}

SGF_INLINE_FORCED CVector2D CVector2D::operator/( const float a ) const {
	float inva = 1.0f / a;
	return CVector2D( x * inva, y * inva );
}

SGF_INLINE_FORCED CVector2D operator*( const float a, const CVector2D b ) {
	return CVector2D( b.x * a, b.y * a );
}

SGF_INLINE_FORCED CVector2D CVector2D::operator+( const CVector2D &a ) const {
	return CVector2D( x + a.x, y + a.y );
}

SGF_INLINE_FORCED CVector2D &CVector2D::operator+=( const CVector2D &a ) {
	x += a.x;
	y += a.y;

	return *this;
}

SGF_INLINE_FORCED CVector2D &CVector2D::operator/=( const CVector2D &a ) {
	x /= a.x;
	y /= a.y;

	return *this;
}

SGF_INLINE_FORCED CVector2D &CVector2D::operator/=( const float a ) {
	float inva = 1.0f / a;
	x *= inva;
	y *= inva;

	return *this;
}

SGF_INLINE_FORCED CVector2D &CVector2D::operator-=( const CVector2D &a ) {
	x -= a.x;
	y -= a.y;

	return *this;
}

SGF_INLINE_FORCED CVector2D &CVector2D::operator*=( const float a ) {
	x *= a;
	y *= a;

	return *this;
}

SGF_INLINE_FORCED int CVector2D::GetDimension() const {
	return 2;
}

SGF_INLINE_FORCED const float *CVector2D::ToFloatPtr() const {
	return &x;
}

SGF_INLINE_FORCED float *CVector2D::ToFloatPtr() {
	return &x;
}


//===============================================================
//
//	CVector3D - 3D vector
//
//===============================================================

class CVector3D {
public:	
	float			x;
	float			y;
	float			z;

					CVector3D();
					explicit CVector3D( const float x, const float y, const float z );

	void 			Set( const float x, const float y, const float z );
	void			Zero();

	float			operator[]( const int index ) const;
	float &			operator[]( const int index );
	CVector3D			operator-() const;
	CVector3D &		operator=( const CVector3D &a );		// required because of a msvc 6 & 7 bug
	float			operator*( const CVector3D &a ) const;
	CVector3D			operator*( const float a ) const;
	CVector3D			operator/( const float a ) const;
	CVector3D			operator+( const CVector3D &a ) const;
	CVector3D			operator-( const CVector3D &a ) const;
	CVector3D &		operator+=( const CVector3D &a );
	CVector3D &		operator-=( const CVector3D &a );
	CVector3D &		operator/=( const CVector3D &a );
	CVector3D &		operator/=( const float a );
	CVector3D &		operator*=( const float a );

	friend CVector3D	operator*( const float a, const CVector3D b );

	bool			Compare( const CVector3D &a ) const;							// exact compare, no epsilon
	bool			Compare( const CVector3D &a, const float epsilon ) const;		// compare with epsilon
	bool			operator==(	const CVector3D &a ) const;						// exact compare, no epsilon
	bool			operator!=(	const CVector3D &a ) const;						// exact compare, no epsilon

	bool			FixDegenerateNormal();	// fix degenerate axial cases
	bool			FixDenormals();			// change tiny numbers to zero

	CVector3D			Cross( const CVector3D &a ) const;
	CVector3D &		Cross( const CVector3D &a, const CVector3D &b );
	float			Length() const;
	float			LengthSqr() const;
	float			LengthFast() const;
	float			Normalize();				// returns length
	float			NormalizeFast();			// returns length
	CVector3D &		Truncate( float length );		// cap length
	void			Clamp( const CVector3D &min, const CVector3D &max );
	void			Snap();					// snap to closest integer value
	void			SnapInt();				// snap towards integer (floor)

	int				GetDimension() const;

	float			ToYaw() const;
	float			ToPitch() const;
	CAngles		ToAngles() const;
	CPolar3D		ToPolar() const;
	CMatriz3D			ToMat3() const;		// vector should be normalized
	const CVector2D &	ToVec2() const;
	CVector2D &		ToVec2();
	const float *	ToFloatPtr() const;
	float *			ToFloatPtr();
	const char *	ToString( int precision = 2 ) const;

	void			NormalVectors( CVector3D &left, CVector3D &down ) const;	// vector should be normalized
	void			OrthogonalBasis( CVector3D &left, CVector3D &up ) const;

	void			ProjectOntoPlane( const CVector3D &normal, const float overBounce = 1.0f );
	bool			ProjectAlongPlane( const CVector3D &normal, const float epsilon, const float overBounce = 1.0f );
	void			ProjectSelfOntoSphere( const float radius );

	void			Lerp( const CVector3D &v1, const CVector3D &v2, const float l );
	void			SLerp( const CVector3D &v1, const CVector3D &v2, const float l );
};

extern CVector3D vec3_origin;
#define vec3_zero vec3_origin

SGF_INLINE_FORCED CVector3D::CVector3D() {
}

SGF_INLINE_FORCED CVector3D::CVector3D( const float x, const float y, const float z ) {
	this->x = x;
	this->y = y;
	this->z = z;
}

SGF_INLINE_FORCED float CVector3D::operator[]( const int index ) const {
	return ( &x )[ index ];
}

SGF_INLINE_FORCED float &CVector3D::operator[]( const int index ) {
	return ( &x )[ index ];
}

SGF_INLINE_FORCED void CVector3D::Set( const float x, const float y, const float z ) {
	this->x = x;
	this->y = y;
	this->z = z;
}

SGF_INLINE_FORCED void CVector3D::Zero() {
	x = y = z = 0.0f;
}

SGF_INLINE_FORCED CVector3D CVector3D::operator-() const {
	return CVector3D( -x, -y, -z );
}

SGF_INLINE_FORCED CVector3D &CVector3D::operator=( const CVector3D &a ) {
	x = a.x;
	y = a.y;
	z = a.z;
	return *this;
}

SGF_INLINE_FORCED CVector3D CVector3D::operator-( const CVector3D &a ) const {
	return CVector3D( x - a.x, y - a.y, z - a.z );
}

SGF_INLINE_FORCED float CVector3D::operator*( const CVector3D &a ) const {
	return x * a.x + y * a.y + z * a.z;
}

SGF_INLINE_FORCED CVector3D CVector3D::operator*( const float a ) const {
	return CVector3D( x * a, y * a, z * a );
}

SGF_INLINE_FORCED CVector3D CVector3D::operator/( const float a ) const {
	float inva = 1.0f / a;
	return CVector3D( x * inva, y * inva, z * inva );
}

SGF_INLINE_FORCED CVector3D operator*( const float a, const CVector3D b ) {
	return CVector3D( b.x * a, b.y * a, b.z * a );
}

SGF_INLINE_FORCED CVector3D CVector3D::operator+( const CVector3D &a ) const {
	return CVector3D( x + a.x, y + a.y, z + a.z );
}

SGF_INLINE_FORCED CVector3D &CVector3D::operator+=( const CVector3D &a ) {
	x += a.x;
	y += a.y;
	z += a.z;

	return *this;
}

SGF_INLINE_FORCED CVector3D &CVector3D::operator/=( const CVector3D &a ) {
	x /= a.x;
	y /= a.y;
	z /= a.z;

	return *this;
}

SGF_INLINE_FORCED CVector3D &CVector3D::operator/=( const float a ) {
	float inva = 1.0f / a;
	x *= inva;
	y *= inva;
	z *= inva;

	return *this;
}

SGF_INLINE_FORCED CVector3D &CVector3D::operator-=( const CVector3D &a ) {
	x -= a.x;
	y -= a.y;
	z -= a.z;

	return *this;
}

SGF_INLINE_FORCED CVector3D &CVector3D::operator*=( const float a ) {
	x *= a;
	y *= a;
	z *= a;

	return *this;
}

SGF_INLINE_FORCED bool CVector3D::Compare( const CVector3D &a ) const {
	return ( ( x == a.x ) && ( y == a.y ) && ( z == a.z ) );
}

SGF_INLINE_FORCED bool CVector3D::Compare( const CVector3D &a, const float epsilon ) const {
	if ( CMath::Fabs( x - a.x ) > epsilon ) {
		return false;
	}
			
	if ( CMath::Fabs( y - a.y ) > epsilon ) {
		return false;
	}

	if ( CMath::Fabs( z - a.z ) > epsilon ) {
		return false;
	}

	return true;
}

SGF_INLINE_FORCED bool CVector3D::operator==( const CVector3D &a ) const {
	return Compare( a );
}

SGF_INLINE_FORCED bool CVector3D::operator!=( const CVector3D &a ) const {
	return !Compare( a );
}

SGF_INLINE_FORCED float CVector3D::NormalizeFast() {
	float sqrLength, invLength;

	sqrLength = x * x + y * y + z * z;
	invLength = CMath::RSqrt( sqrLength );
	x *= invLength;
	y *= invLength;
	z *= invLength;
	return invLength * sqrLength;
}

SGF_INLINE_FORCED bool CVector3D::FixDegenerateNormal() {
	if ( x == 0.0f ) {
		if ( y == 0.0f ) {
			if ( z > 0.0f ) {
				if ( z != 1.0f ) {
					z = 1.0f;
					return true;
				}
			} else {
				if ( z != -1.0f ) {
					z = -1.0f;
					return true;
				}
			}
			return false;
		} else if ( z == 0.0f ) {
			if ( y > 0.0f ) {
				if ( y != 1.0f ) {
					y = 1.0f;
					return true;
				}
			} else {
				if ( y != -1.0f ) {
					y = -1.0f;
					return true;
				}
			}
			return false;
		}
	} else if ( y == 0.0f ) {
		if ( z == 0.0f ) {
			if ( x > 0.0f ) {
				if ( x != 1.0f ) {
					x = 1.0f;
					return true;
				}
			} else {
				if ( x != -1.0f ) {
					x = -1.0f;
					return true;
				}
			}
			return false;
		}
	}
	if ( CMath::Fabs( x ) == 1.0f ) {
		if ( y != 0.0f || z != 0.0f ) {
			y = z = 0.0f;
			return true;
		}
		return false;
	} else if ( CMath::Fabs( y ) == 1.0f ) {
		if ( x != 0.0f || z != 0.0f ) {
			x = z = 0.0f;
			return true;
		}
		return false;
	} else if ( CMath::Fabs( z ) == 1.0f ) {
		if ( x != 0.0f || y != 0.0f ) {
			x = y = 0.0f;
			return true;
		}
		return false;
	}
	return false;
}

SGF_INLINE_FORCED bool CVector3D::FixDenormals() {
	bool denormal = false;
	if ( fabs( x ) < 1e-30f ) {
		x = 0.0f;
		denormal = true;
	}
	if ( fabs( y ) < 1e-30f ) {
		y = 0.0f;
		denormal = true;
	}
	if ( fabs( z ) < 1e-30f ) {
		z = 0.0f;
		denormal = true;
	}
	return denormal;
}

SGF_INLINE_FORCED CVector3D CVector3D::Cross( const CVector3D &a ) const {
	return CVector3D( y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x );
}

SGF_INLINE_FORCED CVector3D &CVector3D::Cross( const CVector3D &a, const CVector3D &b ) {
	x = a.y * b.z - a.z * b.y;
	y = a.z * b.x - a.x * b.z;
	z = a.x * b.y - a.y * b.x;

	return *this;
}

SGF_INLINE_FORCED float CVector3D::Length() const {
	return ( float )CMath::Sqrt( x * x + y * y + z * z );
}

SGF_INLINE_FORCED float CVector3D::LengthSqr() const {
	return ( x * x + y * y + z * z );
}

SGF_INLINE_FORCED float CVector3D::LengthFast() const {
	float sqrLength;

	sqrLength = x * x + y * y + z * z;
	return sqrLength * CMath::RSqrt( sqrLength );
}

SGF_INLINE_FORCED float CVector3D::Normalize() {
	float sqrLength, invLength;

	sqrLength = x * x + y * y + z * z;
	invLength = CMath::InvSqrt( sqrLength );
	x *= invLength;
	y *= invLength;
	z *= invLength;
	return invLength * sqrLength;
}

SGF_INLINE_FORCED CVector3D &CVector3D::Truncate( float length ) {
	float length2;
	float ilength;

	if ( !length ) {
		Zero();
	}
	else {
		length2 = LengthSqr();
		if ( length2 > length * length ) {
			ilength = length * CMath::InvSqrt( length2 );
			x *= ilength;
			y *= ilength;
			z *= ilength;
		}
	}

	return *this;
}

SGF_INLINE_FORCED void CVector3D::Clamp( const CVector3D &min, const CVector3D &max ) {
	if ( x < min.x ) {
		x = min.x;
	} else if ( x > max.x ) {
		x = max.x;
	}
	if ( y < min.y ) {
		y = min.y;
	} else if ( y > max.y ) {
		y = max.y;
	}
	if ( z < min.z ) {
		z = min.z;
	} else if ( z > max.z ) {
		z = max.z;
	}
}

SGF_INLINE_FORCED void CVector3D::Snap() {
	x = floor( x + 0.5f );
	y = floor( y + 0.5f );
	z = floor( z + 0.5f );
}

SGF_INLINE_FORCED void CVector3D::SnapInt() {
	x = float( int( x ) );
	y = float( int( y ) );
	z = float( int( z ) );
}

SGF_INLINE_FORCED int CVector3D::GetDimension() const {
	return 3;
}

SGF_INLINE_FORCED const CVector2D &CVector3D::ToVec2() const {
	return *reinterpret_cast<const CVector2D *>(this);
}

SGF_INLINE_FORCED CVector2D &CVector3D::ToVec2() {
	return *reinterpret_cast<CVector2D *>(this);
}

SGF_INLINE_FORCED const float *CVector3D::ToFloatPtr() const {
	return &x;
}

SGF_INLINE_FORCED float *CVector3D::ToFloatPtr() {
	return &x;
}

SGF_INLINE_FORCED void CVector3D::NormalVectors( CVector3D &left, CVector3D &down ) const {
	float d;

	d = x * x + y * y;
	if ( !d ) {
		left[0] = 1;
		left[1] = 0;
		left[2] = 0;
	} else {
		d = CMath::InvSqrt( d );
		left[0] = -y * d;
		left[1] = x * d;
		left[2] = 0;
	}
	down = left.Cross( *this );
}

SGF_INLINE_FORCED void CVector3D::OrthogonalBasis( CVector3D &left, CVector3D &up ) const {
	float l, s;

	if ( CMath::Fabs( z ) > 0.7f ) {
		l = y * y + z * z;
		s = CMath::InvSqrt( l );
		up[0] = 0;
		up[1] = z * s;
		up[2] = -y * s;
		left[0] = l * s;
		left[1] = -x * up[2];
		left[2] = x * up[1];
	}
	else {
		l = x * x + y * y;
		s = CMath::InvSqrt( l );
		left[0] = -y * s;
		left[1] = x * s;
		left[2] = 0;
		up[0] = -z * left[1];
		up[1] = z * left[0];
		up[2] = l * s;
	}
}

SGF_INLINE_FORCED void CVector3D::ProjectOntoPlane( const CVector3D &normal, const float overBounce ) {
	float backoff;
	
	backoff = *this * normal;
	
	if ( overBounce != 1.0 ) {
		if ( backoff < 0 ) {
			backoff *= overBounce;
		} else {
			backoff /= overBounce;
		}
	}

	*this -= backoff * normal;
}

SGF_INLINE_FORCED bool CVector3D::ProjectAlongPlane( const CVector3D &normal, const float epsilon, const float overBounce ) {
	CVector3D cross;
	float len;

	cross = this->Cross( normal ).Cross( (*this) );
	// normalize so a fixed epsilon can be used
	cross.Normalize();
	len = normal * cross;
	if ( CMath::Fabs( len ) < epsilon ) {
		return false;
	}
	cross *= overBounce * ( normal * (*this) ) / len;
	(*this) -= cross;
	return true;
}


//===============================================================
//
//	CVector4D - 4D vector
//
//===============================================================

class CVector4D {
public:	
	float			x;
	float			y;
	float			z;
	float			w;

					CVector4D();
					explicit CVector4D( const float x, const float y, const float z, const float w );

	void 			Set( const float x, const float y, const float z, const float w );
	void			Zero();

	float			operator[]( const int index ) const;
	float &			operator[]( const int index );
	CVector4D			operator-() const;
	float			operator*( const CVector4D &a ) const;
	CVector4D			operator*( const float a ) const;
	CVector4D			operator/( const float a ) const;
	CVector4D			operator+( const CVector4D &a ) const;
	CVector4D			operator-( const CVector4D &a ) const;
	CVector4D &		operator+=( const CVector4D &a );
	CVector4D &		operator-=( const CVector4D &a );
	CVector4D &		operator/=( const CVector4D &a );
	CVector4D &		operator/=( const float a );
	CVector4D &		operator*=( const float a );

	friend CVector4D	operator*( const float a, const CVector4D b );

	bool			Compare( const CVector4D &a ) const;							// exact compare, no epsilon
	bool			Compare( const CVector4D &a, const float epsilon ) const;		// compare with epsilon
	bool			operator==(	const CVector4D &a ) const;						// exact compare, no epsilon
	bool			operator!=(	const CVector4D &a ) const;						// exact compare, no epsilon

	float			Length() const;
	float			LengthSqr() const;
	float			Normalize();			// returns length
	float			NormalizeFast();		// returns length

	int				GetDimension() const;

	const CVector2D &	ToVec2() const;
	CVector2D &		ToVec2();
	const CVector3D &	ToVec3() const;
	CVector3D &		ToVec3();
	const float *	ToFloatPtr() const;
	float *			ToFloatPtr();
	const char *	ToString( int precision = 2 ) const;

	void			Lerp( const CVector4D &v1, const CVector4D &v2, const float l );
};

extern CVector4D vec4_origin;
#define vec4_zero vec4_origin

SGF_INLINE_FORCED CVector4D::CVector4D() {
}

SGF_INLINE_FORCED CVector4D::CVector4D( const float x, const float y, const float z, const float w ) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

SGF_INLINE_FORCED void CVector4D::Set( const float x, const float y, const float z, const float w ) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

SGF_INLINE_FORCED void CVector4D::Zero() {
	x = y = z = w = 0.0f;
}

SGF_INLINE_FORCED float CVector4D::operator[]( int index ) const {
	return ( &x )[ index ];
}

SGF_INLINE_FORCED float& CVector4D::operator[]( int index ) {
	return ( &x )[ index ];
}

SGF_INLINE_FORCED CVector4D CVector4D::operator-() const {
	return CVector4D( -x, -y, -z, -w );
}

SGF_INLINE_FORCED CVector4D CVector4D::operator-( const CVector4D &a ) const {
	return CVector4D( x - a.x, y - a.y, z - a.z, w - a.w );
}

SGF_INLINE_FORCED float CVector4D::operator*( const CVector4D &a ) const {
	return x * a.x + y * a.y + z * a.z + w * a.w;
}

SGF_INLINE_FORCED CVector4D CVector4D::operator*( const float a ) const {
	return CVector4D( x * a, y * a, z * a, w * a );
}

SGF_INLINE_FORCED CVector4D CVector4D::operator/( const float a ) const {
	float inva = 1.0f / a;
	return CVector4D( x * inva, y * inva, z * inva, w * inva );
}

SGF_INLINE_FORCED CVector4D operator*( const float a, const CVector4D b ) {
	return CVector4D( b.x * a, b.y * a, b.z * a, b.w * a );
}

SGF_INLINE_FORCED CVector4D CVector4D::operator+( const CVector4D &a ) const {
	return CVector4D( x + a.x, y + a.y, z + a.z, w + a.w );
}

SGF_INLINE_FORCED CVector4D &CVector4D::operator+=( const CVector4D &a ) {
	x += a.x;
	y += a.y;
	z += a.z;
	w += a.w;

	return *this;
}

SGF_INLINE_FORCED CVector4D &CVector4D::operator/=( const CVector4D &a ) {
	x /= a.x;
	y /= a.y;
	z /= a.z;
	w /= a.w;

	return *this;
}

SGF_INLINE_FORCED CVector4D &CVector4D::operator/=( const float a ) {
	float inva = 1.0f / a;
	x *= inva;
	y *= inva;
	z *= inva;
	w *= inva;

	return *this;
}

SGF_INLINE_FORCED CVector4D &CVector4D::operator-=( const CVector4D &a ) {
	x -= a.x;
	y -= a.y;
	z -= a.z;
	w -= a.w;

	return *this;
}

SGF_INLINE_FORCED CVector4D &CVector4D::operator*=( const float a ) {
	x *= a;
	y *= a;
	z *= a;
	w *= a;

	return *this;
}

SGF_INLINE_FORCED bool CVector4D::Compare( const CVector4D &a ) const {
	return ( ( x == a.x ) && ( y == a.y ) && ( z == a.z ) && w == a.w );
}

SGF_INLINE_FORCED bool CVector4D::Compare( const CVector4D &a, const float epsilon ) const {
	if ( CMath::Fabs( x - a.x ) > epsilon ) {
		return false;
	}
			
	if ( CMath::Fabs( y - a.y ) > epsilon ) {
		return false;
	}

	if ( CMath::Fabs( z - a.z ) > epsilon ) {
		return false;
	}

	if ( CMath::Fabs( w - a.w ) > epsilon ) {
		return false;
	}

	return true;
}

SGF_INLINE_FORCED bool CVector4D::operator==( const CVector4D &a ) const {
	return Compare( a );
}

SGF_INLINE_FORCED bool CVector4D::operator!=( const CVector4D &a ) const {
	return !Compare( a );
}

SGF_INLINE_FORCED float CVector4D::Length() const {
	return ( float )CMath::Sqrt( x * x + y * y + z * z + w * w );
}

SGF_INLINE_FORCED float CVector4D::LengthSqr() const {
	return ( x * x + y * y + z * z + w * w );
}

SGF_INLINE_FORCED float CVector4D::Normalize() {
	float sqrLength, invLength;

	sqrLength = x * x + y * y + z * z + w * w;
	invLength = CMath::InvSqrt( sqrLength );
	x *= invLength;
	y *= invLength;
	z *= invLength;
	w *= invLength;
	return invLength * sqrLength;
}

SGF_INLINE_FORCED float CVector4D::NormalizeFast() {
	float sqrLength, invLength;

	sqrLength = x * x + y * y + z * z + w * w;
	invLength = CMath::RSqrt( sqrLength );
	x *= invLength;
	y *= invLength;
	z *= invLength;
	w *= invLength;
	return invLength * sqrLength;
}

SGF_INLINE_FORCED int CVector4D::GetDimension() const {
	return 4;
}

SGF_INLINE_FORCED const CVector2D &CVector4D::ToVec2() const {
	return *reinterpret_cast<const CVector2D *>(this);
}

SGF_INLINE_FORCED CVector2D &CVector4D::ToVec2() {
	return *reinterpret_cast<CVector2D *>(this);
}

SGF_INLINE_FORCED const CVector3D &CVector4D::ToVec3() const {
	return *reinterpret_cast<const CVector3D *>(this);
}

SGF_INLINE_FORCED CVector3D &CVector4D::ToVec3() {
	return *reinterpret_cast<CVector3D *>(this);
}

SGF_INLINE_FORCED const float *CVector4D::ToFloatPtr() const {
	return &x;
}

SGF_INLINE_FORCED float *CVector4D::ToFloatPtr() {
	return &x;
}


//===============================================================
//
//	CVector5D - 5D vector
//
//===============================================================

class CVector5D {
public:
	float			x;
	float			y;
	float			z;
	float			s;
	float			t;

					CVector5D();
					explicit CVector5D( const CVector3D &xyz, const CVector2D &st );
					explicit CVector5D( const float x, const float y, const float z, const float s, const float t );

	float			operator[]( int index ) const;
	float &			operator[]( int index );
	CVector5D &		operator=( const CVector3D &a );

	int				GetDimension() const;

	const CVector3D &	ToVec3() const;
	CVector3D &		ToVec3();
	const float *	ToFloatPtr() const;
	float *			ToFloatPtr();
	const char *	ToString( int precision = 2 ) const;

	void			Lerp( const CVector5D &v1, const CVector5D &v2, const float l );
};

extern CVector5D vec5_origin;
#define vec5_zero vec5_origin

SGF_INLINE_FORCED CVector5D::CVector5D() {
}

SGF_INLINE_FORCED CVector5D::CVector5D( const CVector3D &xyz, const CVector2D &st ) {
	x = xyz.x;
	y = xyz.y;
	z = xyz.z;
	s = st[0];
	t = st[1];
}

SGF_INLINE_FORCED CVector5D::CVector5D( const float x, const float y, const float z, const float s, const float t ) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->s = s;
	this->t = t;
}

SGF_INLINE_FORCED float CVector5D::operator[]( int index ) const {
	return ( &x )[ index ];
}

SGF_INLINE_FORCED float& CVector5D::operator[]( int index ) {
	return ( &x )[ index ];
}

SGF_INLINE_FORCED CVector5D &CVector5D::operator=( const CVector3D &a ) { 
	x = a.x;
	y = a.y;
	z = a.z;
	s = t = 0;
	return *this;
}

SGF_INLINE_FORCED int CVector5D::GetDimension() const {
	return 5;
}

SGF_INLINE_FORCED const CVector3D &CVector5D::ToVec3() const {
	return *reinterpret_cast<const CVector3D *>(this);
}

SGF_INLINE_FORCED CVector3D &CVector5D::ToVec3() {
	return *reinterpret_cast<CVector3D *>(this);
}

SGF_INLINE_FORCED const float *CVector5D::ToFloatPtr() const {
	return &x;
}

SGF_INLINE_FORCED float *CVector5D::ToFloatPtr() {
	return &x;
}


//===============================================================
//
//	CVector6D - 6D vector
//
//===============================================================

class CVector6D {
public:	
					CVector6D();
					explicit CVector6D( const float *a );
					explicit CVector6D( const float a1, const float a2, const float a3, const float a4, const float a5, const float a6 );

	void 			Set( const float a1, const float a2, const float a3, const float a4, const float a5, const float a6 );
	void			Zero();

	float			operator[]( const int index ) const;
	float &			operator[]( const int index );
	CVector6D			operator-() const;
	CVector6D			operator*( const float a ) const;
	CVector6D			operator/( const float a ) const;
	float			operator*( const CVector6D &a ) const;
	CVector6D			operator-( const CVector6D &a ) const;
	CVector6D			operator+( const CVector6D &a ) const;
	CVector6D &		operator*=( const float a );
	CVector6D &		operator/=( const float a );
	CVector6D &		operator+=( const CVector6D &a );
	CVector6D &		operator-=( const CVector6D &a );

	friend CVector6D	operator*( const float a, const CVector6D b );

	bool			Compare( const CVector6D &a ) const;							// exact compare, no epsilon
	bool			Compare( const CVector6D &a, const float epsilon ) const;		// compare with epsilon
	bool			operator==(	const CVector6D &a ) const;						// exact compare, no epsilon
	bool			operator!=(	const CVector6D &a ) const;						// exact compare, no epsilon

	float			Length() const;
	float			LengthSqr() const;
	float			Normalize();			// returns length
	float			NormalizeFast();		// returns length

	int				GetDimension() const;

	const CVector3D &	SubVec3( int index ) const;
	CVector3D &		SubVec3( int index );
	const float *	ToFloatPtr() const;
	float *			ToFloatPtr();
	const char *	ToString( int precision = 2 ) const;

private:
	float			p[6];
};

extern CVector6D vec6_origin;
#define vec6_zero vec6_origin
extern CVector6D vec6_infinity;

SGF_INLINE_FORCED CVector6D::CVector6D() {
}

SGF_INLINE_FORCED CVector6D::CVector6D( const float *a ) {
	memcpy( p, a, 6 * sizeof( float ) );
}

SGF_INLINE_FORCED CVector6D::CVector6D( const float a1, const float a2, const float a3, const float a4, const float a5, const float a6 ) {
	p[0] = a1;
	p[1] = a2;
	p[2] = a3;
	p[3] = a4;
	p[4] = a5;
	p[5] = a6;
}

SGF_INLINE_FORCED CVector6D CVector6D::operator-() const {
	return CVector6D( -p[0], -p[1], -p[2], -p[3], -p[4], -p[5] );
}

SGF_INLINE_FORCED float CVector6D::operator[]( const int index ) const {
	return p[index];
}

SGF_INLINE_FORCED float &CVector6D::operator[]( const int index ) {
	return p[index];
}

SGF_INLINE_FORCED CVector6D CVector6D::operator*( const float a ) const {
	return CVector6D( p[0]*a, p[1]*a, p[2]*a, p[3]*a, p[4]*a, p[5]*a );
}

SGF_INLINE_FORCED float CVector6D::operator*( const CVector6D &a ) const {
	return p[0] * a[0] + p[1] * a[1] + p[2] * a[2] + p[3] * a[3] + p[4] * a[4] + p[5] * a[5];
}

SGF_INLINE_FORCED CVector6D CVector6D::operator/( const float a ) const {
	float inva;

	assert( a != 0.0f );
	inva = 1.0f / a;
	return CVector6D( p[0]*inva, p[1]*inva, p[2]*inva, p[3]*inva, p[4]*inva, p[5]*inva );
}

SGF_INLINE_FORCED CVector6D CVector6D::operator+( const CVector6D &a ) const {
	return CVector6D( p[0] + a[0], p[1] + a[1], p[2] + a[2], p[3] + a[3], p[4] + a[4], p[5] + a[5] );
}

SGF_INLINE_FORCED CVector6D CVector6D::operator-( const CVector6D &a ) const {
	return CVector6D( p[0] - a[0], p[1] - a[1], p[2] - a[2], p[3] - a[3], p[4] - a[4], p[5] - a[5] );
}

SGF_INLINE_FORCED CVector6D &CVector6D::operator*=( const float a ) {
	p[0] *= a;
	p[1] *= a;
	p[2] *= a;
	p[3] *= a;
	p[4] *= a;
	p[5] *= a;
	return *this;
}

SGF_INLINE_FORCED CVector6D &CVector6D::operator/=( const float a ) {
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

SGF_INLINE_FORCED CVector6D &CVector6D::operator+=( const CVector6D &a ) {
	p[0] += a[0];
	p[1] += a[1];
	p[2] += a[2];
	p[3] += a[3];
	p[4] += a[4];
	p[5] += a[5];
	return *this;
}

SGF_INLINE_FORCED CVector6D &CVector6D::operator-=( const CVector6D &a ) {
	p[0] -= a[0];
	p[1] -= a[1];
	p[2] -= a[2];
	p[3] -= a[3];
	p[4] -= a[4];
	p[5] -= a[5];
	return *this;
}

SGF_INLINE_FORCED CVector6D operator*( const float a, const CVector6D b ) {
	return b * a;
}

SGF_INLINE_FORCED bool CVector6D::Compare( const CVector6D &a ) const {
	return ( ( p[0] == a[0] ) && ( p[1] == a[1] ) && ( p[2] == a[2] ) &&
			( p[3] == a[3] ) && ( p[4] == a[4] ) && ( p[5] == a[5] ) );
}

SGF_INLINE_FORCED bool CVector6D::Compare( const CVector6D &a, const float epsilon ) const {
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

SGF_INLINE_FORCED bool CVector6D::operator==( const CVector6D &a ) const {
	return Compare( a );
}

SGF_INLINE_FORCED bool CVector6D::operator!=( const CVector6D &a ) const {
	return !Compare( a );
}

SGF_INLINE_FORCED void CVector6D::Set( const float a1, const float a2, const float a3, const float a4, const float a5, const float a6 ) {
	p[0] = a1;
	p[1] = a2;
	p[2] = a3;
	p[3] = a4;
	p[4] = a5;
	p[5] = a6;
}

SGF_INLINE_FORCED void CVector6D::Zero() {
	p[0] = p[1] = p[2] = p[3] = p[4] = p[5] = 0.0f;
}

SGF_INLINE_FORCED float CVector6D::Length() const {
	return ( float )CMath::Sqrt( p[0] * p[0] + p[1] * p[1] + p[2] * p[2] + p[3] * p[3] + p[4] * p[4] + p[5] * p[5] );
}

SGF_INLINE_FORCED float CVector6D::LengthSqr() const {
	return ( p[0] * p[0] + p[1] * p[1] + p[2] * p[2] + p[3] * p[3] + p[4] * p[4] + p[5] * p[5] );
}

SGF_INLINE_FORCED float CVector6D::Normalize() {
	float sqrLength, invLength;

	sqrLength = p[0] * p[0] + p[1] * p[1] + p[2] * p[2] + p[3] * p[3] + p[4] * p[4] + p[5] * p[5];
	invLength = CMath::InvSqrt( sqrLength );
	p[0] *= invLength;
	p[1] *= invLength;
	p[2] *= invLength;
	p[3] *= invLength;
	p[4] *= invLength;
	p[5] *= invLength;
	return invLength * sqrLength;
}

SGF_INLINE_FORCED float CVector6D::NormalizeFast() {
	float sqrLength, invLength;

	sqrLength = p[0] * p[0] + p[1] * p[1] + p[2] * p[2] + p[3] * p[3] + p[4] * p[4] + p[5] * p[5];
	invLength = CMath::RSqrt( sqrLength );
	p[0] *= invLength;
	p[1] *= invLength;
	p[2] *= invLength;
	p[3] *= invLength;
	p[4] *= invLength;
	p[5] *= invLength;
	return invLength * sqrLength;
}

SGF_INLINE_FORCED int CVector6D::GetDimension() const {
	return 6;
}

SGF_INLINE_FORCED const CVector3D &CVector6D::SubVec3( int index ) const {
	return *reinterpret_cast<const CVector3D *>(p + index * 3);
}

SGF_INLINE_FORCED CVector3D &CVector6D::SubVec3( int index ) {
	return *reinterpret_cast<CVector3D *>(p + index * 3);
}

SGF_INLINE_FORCED const float *CVector6D::ToFloatPtr() const {
	return p;
}

SGF_INLINE_FORCED float *CVector6D::ToFloatPtr() {
	return p;
}


//===============================================================
//
//	CVectorXD - arbitrary sized vector
//
//  The vector lives on 16 SGF_Byte aligned and 16 SGF_Byte padded memory.
//
//	NOTE: due to the temporary memory pool CVectorXD cannot be used by multiple threads
//
//===============================================================

#define VECX_MAX_TEMP		1024
#define VECX_QUAD( x )		( ( ( ( x ) + 3 ) & ~3 ) * sizeof( float ) )
#define VECX_CLEAREND()		int s = size; while( s < ( ( s + 3) & ~3 ) ) { p[s++] = 0.0f; }
#define VECX_ALLOCA( n )	( (float *) _alloca16( VECX_QUAD( n ) ) )
#define VECX_ALLOCAFLOAT( n )	( (float *) _allocafloat16( VECX_QUAD( n ) ) )
class CVectorXD {
	friend class CMatrizXD;

public:	
					CVectorXD();
					explicit CVectorXD( int length );
					explicit CVectorXD( int length, float *data );
					~CVectorXD();

	float			operator[]( const int index ) const;
	float &			operator[]( const int index );
	CVectorXD			operator-() const;
	CVectorXD &		operator=( const CVectorXD &a );
	CVectorXD			operator*( const float a ) const;
	CVectorXD			operator/( const float a ) const;
	float			operator*( const CVectorXD &a ) const;
	CVectorXD			operator-( const CVectorXD &a ) const;
	CVectorXD			operator+( const CVectorXD &a ) const;
	CVectorXD &		operator*=( const float a );
	CVectorXD &		operator/=( const float a );
	CVectorXD &		operator+=( const CVectorXD &a );
	CVectorXD &		operator-=( const CVectorXD &a );

	friend CVectorXD	operator*( const float a, const CVectorXD b );

	bool			Compare( const CVectorXD &a ) const;							// exact compare, no epsilon
	bool			Compare( const CVectorXD &a, const float epsilon ) const;		// compare with epsilon
	bool			operator==(	const CVectorXD &a ) const;						// exact compare, no epsilon
	bool			operator!=(	const CVectorXD &a ) const;						// exact compare, no epsilon

	void			SetSize( int size );
	void			ChangeSize( int size, bool makeZero = false );
	int				GetSize() const { return size; }
	void			SetData( int length, float *data );
	void			Zero();
	void			Zero( int length );
	void			Random( int seed, float l = 0.0f, float u = 1.0f );
	void			Random( int length, int seed, float l = 0.0f, float u = 1.0f );
	void			Negate();
	void			Clamp( float min, float max );
	CVectorXD &		SwapElements( int e1, int e2 );

	float			Length() const;
	float			LengthSqr() const;
	CVectorXD			Normalize() const;
	float			NormalizeSelf();

	int				GetDimension() const;

	const CVector3D &	SubVec3( int index ) const;
	CVector3D &		SubVec3( int index );
	const CVector6D &	SubVec6( int index ) const;
	CVector6D &		SubVec6( int index );
	const float *	ToFloatPtr() const;
	float *			ToFloatPtr();
	const char *	ToString( int precision = 2 ) const;
	void			SetTempSize( int size );   //Shoud be private but matriz use it
private:
	int				size;					// size of the vector
	int				alloced;				// if -1 p points to data set with SetData
	float *			p;						// memory the vector is stored

	static float	temp[VECX_MAX_TEMP+4];	// used to store intermediate results
	static float *	tempPtr;				// pointer to 16 SGF_Byte aligned temporary memory
	static int		tempIndex;				// index into memory pool, wraps around


	
};


SGF_INLINE_FORCED CVectorXD::CVectorXD() {
	size = alloced = 0;
	p = NULL;
}

SGF_INLINE_FORCED CVectorXD::CVectorXD( int length ) {
	size = alloced = 0;
	p = NULL;
	SetSize( length );
}

SGF_INLINE_FORCED CVectorXD::CVectorXD( int length, float *data ) {
	size = alloced = 0;
	p = NULL;
	SetData( length, data );
}

SGF_INLINE_FORCED CVectorXD::~CVectorXD() {
	// if not temp memory
	if ( p && ( p < CVectorXD::tempPtr || p >= CVectorXD::tempPtr + VECX_MAX_TEMP ) && alloced != -1 ) {
		Mem_Free16( p );
	}
}

SGF_INLINE_FORCED float CVectorXD::operator[]( const int index ) const {
	assert( index >= 0 && index < size );
	return p[index];
}

SGF_INLINE_FORCED float &CVectorXD::operator[]( const int index ) {
	assert( index >= 0 && index < size );
	return p[index];
}

SGF_INLINE_FORCED CVectorXD CVectorXD::operator-() const {
	int i;
	CVectorXD m;

	m.SetTempSize( size );
	for ( i = 0; i < size; i++ ) {
		m.p[i] = -p[i];
	}
	return m;
}

SGF_INLINE_FORCED CVectorXD &CVectorXD::operator=( const CVectorXD &a ) { 
	SetSize( a.size );
#ifdef VECX_SIMD
	SIMDProcessor->Copy16( p, a.p, a.size );
#else
	memcpy( p, a.p, a.size * sizeof( float ) );
#endif
	CVectorXD::tempIndex = 0;
	return *this;
}

SGF_INLINE_FORCED CVectorXD CVectorXD::operator+( const CVectorXD &a ) const {
	CVectorXD m;

	assert( size == a.size );
	m.SetTempSize( size );
#ifdef VECX_SIMD
	SIMDProcessor->Add16( m.p, p, a.p, size );
#else
	int i;
	for ( i = 0; i < size; i++ ) {
		m.p[i] = p[i] + a.p[i];
	}
#endif
	return m;
}

SGF_INLINE_FORCED CVectorXD CVectorXD::operator-( const CVectorXD &a ) const {
	CVectorXD m;

	assert( size == a.size );
	m.SetTempSize( size );
#ifdef VECX_SIMD
	SIMDProcessor->Sub16( m.p, p, a.p, size );
#else
	int i;
	for ( i = 0; i < size; i++ ) {
		m.p[i] = p[i] - a.p[i];
	}
#endif
	return m;
}

SGF_INLINE_FORCED CVectorXD &CVectorXD::operator+=( const CVectorXD &a ) {
	assert( size == a.size );
#ifdef VECX_SIMD
	SIMDProcessor->AddAssign16( p, a.p, size );
#else
	int i;
	for ( i = 0; i < size; i++ ) {
		p[i] += a.p[i];
	}
#endif
	CVectorXD::tempIndex = 0;
	return *this;
}

SGF_INLINE_FORCED CVectorXD &CVectorXD::operator-=( const CVectorXD &a ) {
	assert( size == a.size );
#ifdef VECX_SIMD
	SIMDProcessor->SubAssign16( p, a.p, size );
#else
	int i;
	for ( i = 0; i < size; i++ ) {
		p[i] -= a.p[i];
	}
#endif
	CVectorXD::tempIndex = 0;
	return *this;
}

SGF_INLINE_FORCED CVectorXD CVectorXD::operator*( const float a ) const {
	CVectorXD m;

	m.SetTempSize( size );
#ifdef VECX_SIMD
	SIMDProcessor->Mul16( m.p, p, a, size );
#else
	int i;
	for ( i = 0; i < size; i++ ) {
		m.p[i] = p[i] * a;
	}
#endif
	return m;
}

SGF_INLINE_FORCED CVectorXD &CVectorXD::operator*=( const float a ) {
#ifdef VECX_SIMD
	SIMDProcessor->MulAssign16( p, a, size );
#else
	int i;
	for ( i = 0; i < size; i++ ) {
		p[i] *= a;
	}
#endif
	return *this;
}

SGF_INLINE_FORCED CVectorXD CVectorXD::operator/( const float a ) const {
	assert( a != 0.0f );
	return (*this) * ( 1.0f / a );
}

SGF_INLINE_FORCED CVectorXD &CVectorXD::operator/=( const float a ) {
	assert( a != 0.0f );
	(*this) *= ( 1.0f / a );
	return *this;
}

SGF_INLINE_FORCED CVectorXD operator*( const float a, const CVectorXD b ) {
	return b * a;
}

SGF_INLINE_FORCED float CVectorXD::operator*( const CVectorXD &a ) const {
	int i;
	float sum = 0.0f;

	assert( size == a.size );
	for ( i = 0; i < size; i++ ) {
		sum += p[i] * a.p[i];
	}
	return sum;
}

SGF_INLINE_FORCED bool CVectorXD::Compare( const CVectorXD &a ) const {
	int i;

	assert( size == a.size );
	for ( i = 0; i < size; i++ ) {
		if ( p[i] != a.p[i] ) {
			return false;
		}
	}
	return true;
}

SGF_INLINE_FORCED bool CVectorXD::Compare( const CVectorXD &a, const float epsilon ) const {
	int i;

	assert( size == a.size );
	for ( i = 0; i < size; i++ ) {
		if ( CMath::Fabs( p[i] - a.p[i] ) > epsilon ) {
			return false;
		}
	}
	return true;
}

SGF_INLINE_FORCED bool CVectorXD::operator==( const CVectorXD &a ) const {
	return Compare( a );
}

SGF_INLINE_FORCED bool CVectorXD::operator!=( const CVectorXD &a ) const {
	return !Compare( a );
}

SGF_INLINE_FORCED void CVectorXD::SetSize( int newSize ) {
	int alloc = ( newSize + 3 ) & ~3;
	if ( alloc > alloced && alloced != -1 ) {
		if ( p ) {
			Mem_Free16( p );
		}
		p = (float *) Mem_Alloc16( alloc * sizeof( float ) );
		alloced = alloc;
	}
	size = newSize;
	VECX_CLEAREND();
}

SGF_INLINE_FORCED void CVectorXD::ChangeSize( int newSize, bool makeZero ) {
	int alloc = ( newSize + 3 ) & ~3;
	if ( alloc > alloced && alloced != -1 ) {
		float *oldVec = p;
		p = (float *) Mem_Alloc16( alloc * sizeof( float ) );
		alloced = alloc;
		if ( oldVec ) {
			for ( int i = 0; i < size; i++ ) {
				p[i] = oldVec[i];
			}
			Mem_Free16( oldVec );
		}
		if ( makeZero ) {
			// zero any new elements
			for ( int i = size; i < newSize; i++ ) {
				p[i] = 0.0f;
			}
		}
	}
	size = newSize;
	VECX_CLEAREND();
}

SGF_INLINE_FORCED void CVectorXD::SetTempSize( int newSize ) {

	size = newSize;
	alloced = ( newSize + 3 ) & ~3;
	assert( alloced < VECX_MAX_TEMP );
	if ( CVectorXD::tempIndex + alloced > VECX_MAX_TEMP ) {
		CVectorXD::tempIndex = 0;
	}
	p = CVectorXD::tempPtr + CVectorXD::tempIndex;
	CVectorXD::tempIndex += alloced;
	VECX_CLEAREND();
}

SGF_INLINE_FORCED void CVectorXD::SetData( int length, float *data ) {
	if ( p && ( p < CVectorXD::tempPtr || p >= CVectorXD::tempPtr + VECX_MAX_TEMP ) && alloced != -1 ) {
		Mem_Free16( p );
	}
	
#ifdef _WIN32 
	assert( ( ( (int) data ) & 15 ) == 0 ); // data must be 16 SGF_Byte aligned
#else
	assert( ( ( (uintptr_t) data ) & 15 ) == 0 ); // data must be 16 byte aligned
#endif	


	p = data;
	size = length;
	alloced = -1;
	VECX_CLEAREND();
}

SGF_INLINE_FORCED void CVectorXD::Zero() {
#ifdef VECX_SIMD
	SIMDProcessor->Zero16( p, size );
#else
	memset( p, 0, size * sizeof( float ) );
#endif
}

SGF_INLINE_FORCED void CVectorXD::Zero( int length ) {
	SetSize( length );
#ifdef VECX_SIMD
	SIMDProcessor->Zero16( p, length );
#else
	memset( p, 0, size * sizeof( float ) );
#endif
}

SGF_INLINE_FORCED void CVectorXD::Random( int seed, float l, float u ) {
	int i;
	float c;
	CRamdom rnd( seed );

	c = u - l;
	for ( i = 0; i < size; i++ ) {
		p[i] = l + rnd.RandomFloat() * c;
	}
}

SGF_INLINE_FORCED void CVectorXD::Random( int length, int seed, float l, float u ) {
	int i;
	float c;
	CRamdom rnd( seed );

	SetSize( length );
	c = u - l;
	for ( i = 0; i < size; i++ ) {
		p[i] = l + rnd.RandomFloat() * c;
	}
}

SGF_INLINE_FORCED void CVectorXD::Negate() {
#ifdef VECX_SIMD
	SIMDProcessor->Negate16( p, size );
#else
	int i;
	for ( i = 0; i < size; i++ ) {
		p[i] = -p[i];
	}
#endif
}

SGF_INLINE_FORCED void CVectorXD::Clamp( float min, float max ) {
	int i;
	for ( i = 0; i < size; i++ ) {
		if ( p[i] < min ) {
			p[i] = min;
		} else if ( p[i] > max ) {
			p[i] = max;
		}
	}
}

SGF_INLINE_FORCED CVectorXD &CVectorXD::SwapElements( int e1, int e2 ) {
	float tmp;
	tmp = p[e1];
	p[e1] = p[e2];
	p[e2] = tmp;
	return *this;
}

SGF_INLINE_FORCED float CVectorXD::Length() const {
	int i;
	float sum = 0.0f;

	for ( i = 0; i < size; i++ ) {
		sum += p[i] * p[i];
	}
	return CMath::Sqrt( sum );
}

SGF_INLINE_FORCED float CVectorXD::LengthSqr() const {
	int i;
	float sum = 0.0f;

	for ( i = 0; i < size; i++ ) {
		sum += p[i] * p[i];
	}
	return sum;
}

SGF_INLINE_FORCED CVectorXD CVectorXD::Normalize() const {
	int i;
	CVectorXD m;
	float invSqrt, sum = 0.0f;

	m.SetTempSize( size );
	for ( i = 0; i < size; i++ ) {
		sum += p[i] * p[i];
	}
	invSqrt = CMath::InvSqrt( sum );
	for ( i = 0; i < size; i++ ) {
		m.p[i] = p[i] * invSqrt;
	}
	return m;
}

SGF_INLINE_FORCED float CVectorXD::NormalizeSelf() {
	float invSqrt, sum = 0.0f;
	int i;
	for ( i = 0; i < size; i++ ) {
		sum += p[i] * p[i];
	}
	invSqrt = CMath::InvSqrt( sum );
	for ( i = 0; i < size; i++ ) {
		p[i] *= invSqrt;
	}
	return invSqrt * sum;
}

SGF_INLINE_FORCED int CVectorXD::GetDimension() const {
	return size;
}

SGF_INLINE_FORCED CVector3D &CVectorXD::SubVec3( int index ) {
	assert( index >= 0 && index * 3 + 3 <= size );
	return *reinterpret_cast<CVector3D *>(p + index * 3);
}

SGF_INLINE_FORCED const CVector3D &CVectorXD::SubVec3( int index ) const {
	assert( index >= 0 && index * 3 + 3 <= size );
	return *reinterpret_cast<const CVector3D *>(p + index * 3);
}

SGF_INLINE_FORCED CVector6D &CVectorXD::SubVec6( int index ) {
	assert( index >= 0 && index * 6 + 6 <= size );
	return *reinterpret_cast<CVector6D *>(p + index * 6);
}

SGF_INLINE_FORCED const CVector6D &CVectorXD::SubVec6( int index ) const {
	assert( index >= 0 && index * 6 + 6 <= size );
	return *reinterpret_cast<const CVector6D *>(p + index * 6);
}

SGF_INLINE_FORCED const float *CVectorXD::ToFloatPtr() const {
	return p;
}

SGF_INLINE_FORCED float *CVectorXD::ToFloatPtr() {
	return p;
}


//===============================================================
//
//	CPolar3D
//
//===============================================================

class CPolar3D {
public:	
	float			radius, theta, phi;

					CPolar3D();
					explicit CPolar3D( const float radius, const float theta, const float phi );

	void 			Set( const float radius, const float theta, const float phi );

	float			operator[]( const int index ) const;
	float &			operator[]( const int index );
	CPolar3D		operator-() const;
	CPolar3D &		operator=( const CPolar3D &a );

	CVector3D			ToVec3() const;
};

SGF_INLINE_FORCED CPolar3D::CPolar3D() {
}

SGF_INLINE_FORCED CPolar3D::CPolar3D( const float radius, const float theta, const float phi ) {
	assert( radius > 0 );
	this->radius = radius;
	this->theta = theta;
	this->phi = phi;
}
	
SGF_INLINE_FORCED void CPolar3D::Set( const float radius, const float theta, const float phi ) {
	assert( radius > 0 );
	this->radius = radius;
	this->theta = theta;
	this->phi = phi;
}

SGF_INLINE_FORCED float CPolar3D::operator[]( const int index ) const {
	return ( &radius )[ index ];
}

SGF_INLINE_FORCED float &CPolar3D::operator[]( const int index ) {
	return ( &radius )[ index ];
}

SGF_INLINE_FORCED CPolar3D CPolar3D::operator-() const {
	return CPolar3D( radius, -theta, -phi );
}

SGF_INLINE_FORCED CPolar3D &CPolar3D::operator=( const CPolar3D &a ) { 
	radius = a.radius;
	theta = a.theta;
	phi = a.phi;
	return *this;
}

SGF_INLINE_FORCED CVector3D CPolar3D::ToVec3() const {
	float sp, cp, st, ct;
	CMath::SinCos( phi, sp, cp );
	CMath::SinCos( theta, st, ct );
 	return CVector3D( cp * radius * ct, cp * radius * st, radius * sp );
}


/*
===============================================================================

	Old 3D vector macros, should no longer be used.

===============================================================================
*/

#define DotProduct( a, b)			((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VectorSubtract( a, b, c )	((c)[0]=(a)[0]-(b)[0],(c)[1]=(a)[1]-(b)[1],(c)[2]=(a)[2]-(b)[2])
#define VectorAdd( a, b, c )		((c)[0]=(a)[0]+(b)[0],(c)[1]=(a)[1]+(b)[1],(c)[2]=(a)[2]+(b)[2])
#define	VectorScale( v, s, o )		((o)[0]=(v)[0]*(s),(o)[1]=(v)[1]*(s),(o)[2]=(v)[2]*(s))
#define	VectorMA( v, s, b, o )		((o)[0]=(v)[0]+(b)[0]*(s),(o)[1]=(v)[1]+(b)[1]*(s),(o)[2]=(v)[2]+(b)[2]*(s))
#define VectorCopy( a, b )			((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2])

} //end SGF
#endif /* !__SGF_MATH_VECTOR_H__ */
