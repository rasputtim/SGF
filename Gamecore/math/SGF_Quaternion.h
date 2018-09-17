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

#ifndef __MATH_QUAT_H__
#define __MATH_QUAT_H__
#include "../SGF_Config.h"
#include "SGF_Vector.h"


namespace SGF{
/*
===============================================================================

	Quaternion

===============================================================================
*/


class CVector3D;
class CAngles;
class CRotation;
class CMatriz3D;
class CMatriz4D;
class CCompQuaternion;

class CQuaternion {
public:
	float			x;
	float			y;
	float			z;
	float			w;

					CQuaternion();
					CQuaternion( float x, float y, float z, float w );

	void 			Set( float x, float y, float z, float w );

	float			operator[]( int index ) const;
	float &			operator[]( int index );
	CQuaternion			operator-() const;
	CQuaternion &		operator=( const CQuaternion &a );
	CQuaternion			operator+( const CQuaternion &a ) const;
	CQuaternion &		operator+=( const CQuaternion &a );
	CQuaternion			operator-( const CQuaternion &a ) const;
	CQuaternion &		operator-=( const CQuaternion &a );
	CQuaternion			operator*( const CQuaternion &a ) const;
	CVector3D			operator*( const CVector3D &a ) const;
	CQuaternion			operator*( float a ) const;
	CQuaternion &		operator*=( const CQuaternion &a );
	CQuaternion &		operator*=( float a );

	friend CQuaternion	operator*( const float a, const CQuaternion &b );
	friend CVector3D	operator*( const CVector3D &a, const CQuaternion &b );

	bool			Compare( const CQuaternion &a ) const;						// exact compare, no epsilon
	bool			Compare( const CQuaternion &a, const float epsilon ) const;	// compare with epsilon
	bool			operator==(	const CQuaternion &a ) const;					// exact compare, no epsilon
	bool			operator!=(	const CQuaternion &a ) const;					// exact compare, no epsilon

	CQuaternion			Inverse() const;
	float			Length() const;
	CQuaternion &		Normalize();

	float			CalcW() const;
	int				GetDimension() const;

	CAngles		ToAngles() const;
	CRotation		ToRotation() const;
	CMatriz3D			ToMat3() const;
	CMatriz4D			ToMat4() const;
	CCompQuaternion			ToCQuat() const;
	CVector3D			ToAngularVelocity() const;
	const float *	ToFloatPtr() const;
	float *			ToFloatPtr();
	const char *	ToString( int precision = 2 ) const;

	CQuaternion &		Slerp( const CQuaternion &from, const CQuaternion &to, float t );
};

SGF_INLINE_FORCED CQuaternion::CQuaternion() {
}

SGF_INLINE_FORCED CQuaternion::CQuaternion( float x, float y, float z, float w ) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

SGF_INLINE_FORCED float CQuaternion::operator[]( int index ) const {
	assert( ( index >= 0 ) && ( index < 4 ) );
	return ( &x )[ index ];
}

SGF_INLINE_FORCED float& CQuaternion::operator[]( int index ) {
	assert( ( index >= 0 ) && ( index < 4 ) );
	return ( &x )[ index ];
}

SGF_INLINE_FORCED CQuaternion CQuaternion::operator-() const {
	return CQuaternion( -x, -y, -z, -w );
}

SGF_INLINE_FORCED CQuaternion &CQuaternion::operator=( const CQuaternion &a ) {
	x = a.x;
	y = a.y;
	z = a.z;
	w = a.w;

	return *this;
}

SGF_INLINE_FORCED CQuaternion CQuaternion::operator+( const CQuaternion &a ) const {
	return CQuaternion( x + a.x, y + a.y, z + a.z, w + a.w );
}

SGF_INLINE_FORCED CQuaternion& CQuaternion::operator+=( const CQuaternion &a ) {
	x += a.x;
	y += a.y;
	z += a.z;
	w += a.w;

	return *this;
}

SGF_INLINE_FORCED CQuaternion CQuaternion::operator-( const CQuaternion &a ) const {
	return CQuaternion( x - a.x, y - a.y, z - a.z, w - a.w );
}

SGF_INLINE_FORCED CQuaternion& CQuaternion::operator-=( const CQuaternion &a ) {
	x -= a.x;
	y -= a.y;
	z -= a.z;
	w -= a.w;

	return *this;
}

SGF_INLINE_FORCED CQuaternion CQuaternion::operator*( const CQuaternion &a ) const {
	return CQuaternion(	w*a.x + x*a.w + y*a.z - z*a.y,
					w*a.y + y*a.w + z*a.x - x*a.z,
					w*a.z + z*a.w + x*a.y - y*a.x,
					w*a.w - x*a.x - y*a.y - z*a.z );
}

SGF_INLINE_FORCED CVector3D CQuaternion::operator*( const CVector3D &a ) const {
#if 0
	// it's faster to do the conversion to a 3x3 matrix and multiply the vector by this 3x3 matrix
	return ( ToMat3() * a );
#else
	// result = this->Inverse() * CQuaternion( a.x, a.y, a.z, 0.0f ) * (*this)
	float xxzz = x*x - z*z;
	float wwyy = w*w - y*y;

	float xw2 = x*w*2.0f;
	float xy2 = x*y*2.0f;
	float xz2 = x*z*2.0f;
	float yw2 = y*w*2.0f;
	float yz2 = y*z*2.0f;
	float zw2 = z*w*2.0f;

	return CVector3D(
		(xxzz + wwyy)*a.x		+ (xy2 + zw2)*a.y		+ (xz2 - yw2)*a.z,
		(xy2 - zw2)*a.x			+ (y*y+w*w-x*x-z*z)*a.y	+ (yz2 + xw2)*a.z,
		(xz2 + yw2)*a.x			+ (yz2 - xw2)*a.y		+ (wwyy - xxzz)*a.z
	);
#endif
}

SGF_INLINE_FORCED CQuaternion CQuaternion::operator*( float a ) const {
	return CQuaternion( x * a, y * a, z * a, w * a );
}

SGF_INLINE_FORCED CQuaternion operator*( const float a, const CQuaternion &b ) {
	return b * a;
}

SGF_INLINE_FORCED CVector3D operator*( const CVector3D &a, const CQuaternion &b ) {
	return b * a;
}

SGF_INLINE_FORCED CQuaternion& CQuaternion::operator*=( const CQuaternion &a ) {
	*this = *this * a;

	return *this;
}

SGF_INLINE_FORCED CQuaternion& CQuaternion::operator*=( float a ) {
	x *= a;
	y *= a;
	z *= a;
	w *= a;

	return *this;
}

SGF_INLINE_FORCED bool CQuaternion::Compare( const CQuaternion &a ) const {
	return ( ( x == a.x ) && ( y == a.y ) && ( z == a.z ) && ( w == a.w ) );
}

SGF_INLINE_FORCED bool CQuaternion::Compare( const CQuaternion &a, const float epsilon ) const {
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

SGF_INLINE_FORCED bool CQuaternion::operator==( const CQuaternion &a ) const {
	return Compare( a );
}

SGF_INLINE_FORCED bool CQuaternion::operator!=( const CQuaternion &a ) const {
	return !Compare( a );
}

SGF_INLINE_FORCED void CQuaternion::Set( float x, float y, float z, float w ) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

SGF_INLINE_FORCED CQuaternion CQuaternion::Inverse() const {
	return CQuaternion( -x, -y, -z, w );
}

SGF_INLINE_FORCED float CQuaternion::Length() const {
	float len;

	len = x * x + y * y + z * z + w * w;
	return CMath::Sqrt( len );
}

SGF_INLINE_FORCED CQuaternion& CQuaternion::Normalize() {
	float len;
	float ilength;

	len = this->Length();
	if ( len ) {
		ilength = 1 / len;
		x *= ilength;
		y *= ilength;
		z *= ilength;
		w *= ilength;
	}
	return *this;
}

SGF_INLINE_FORCED float CQuaternion::CalcW() const {
	// take the absolute value because floating point rounding may cause the dot of x,y,z to be larger than 1
	return sqrt( fabs( 1.0f - ( x * x + y * y + z * z ) ) );
}

SGF_INLINE_FORCED int CQuaternion::GetDimension() const {
	return 4;
}

SGF_INLINE_FORCED const float *CQuaternion::ToFloatPtr() const {
	return &x;
}

SGF_INLINE_FORCED float *CQuaternion::ToFloatPtr() {
	return &x;
}


/*
===============================================================================

	Compressed quaternion

===============================================================================
*/

class CCompQuaternion {
public:
	float			x;
	float			y;
	float			z;

					CCompQuaternion();
					CCompQuaternion( float x, float y, float z );

	void 			Set( float x, float y, float z );

	float			operator[]( int index ) const;
	float &			operator[]( int index );

	bool			Compare( const CCompQuaternion &a ) const;						// exact compare, no epsilon
	bool			Compare( const CCompQuaternion &a, const float epsilon ) const;	// compare with epsilon
	bool			operator==(	const CCompQuaternion &a ) const;					// exact compare, no epsilon
	bool			operator!=(	const CCompQuaternion &a ) const;					// exact compare, no epsilon

	int				GetDimension() const;

	CAngles		ToAngles() const;
	CRotation		ToRotation() const;
	CMatriz3D			ToMat3() const;
	CMatriz4D			ToMat4() const;
	CQuaternion			ToQuat() const;
	const float *	ToFloatPtr() const;
	float *			ToFloatPtr();
	const char *	ToString( int precision = 2 ) const;
};

SGF_INLINE_FORCED CCompQuaternion::CCompQuaternion() {
}

SGF_INLINE_FORCED CCompQuaternion::CCompQuaternion( float x, float y, float z ) {
	this->x = x;
	this->y = y;
	this->z = z;
}

SGF_INLINE_FORCED void CCompQuaternion::Set( float x, float y, float z ) {
	this->x = x;
	this->y = y;
	this->z = z;
}

SGF_INLINE_FORCED float CCompQuaternion::operator[]( int index ) const {
	assert( ( index >= 0 ) && ( index < 3 ) );
	return ( &x )[ index ];
}

SGF_INLINE_FORCED float& CCompQuaternion::operator[]( int index ) {
	assert( ( index >= 0 ) && ( index < 3 ) );
	return ( &x )[ index ];
}

SGF_INLINE_FORCED bool CCompQuaternion::Compare( const CCompQuaternion &a ) const {
	return ( ( x == a.x ) && ( y == a.y ) && ( z == a.z ) );
}

SGF_INLINE_FORCED bool CCompQuaternion::Compare( const CCompQuaternion &a, const float epsilon ) const {
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

SGF_INLINE_FORCED bool CCompQuaternion::operator==( const CCompQuaternion &a ) const {
	return Compare( a );
}

SGF_INLINE_FORCED bool CCompQuaternion::operator!=( const CCompQuaternion &a ) const {
	return !Compare( a );
}

SGF_INLINE_FORCED int CCompQuaternion::GetDimension() const {
	return 3;
}

SGF_INLINE_FORCED CQuaternion CCompQuaternion::ToQuat() const {
	// take the absolute value because floating point rounding may cause the dot of x,y,z to be larger than 1
	return CQuaternion( x, y, z, sqrt( fabs( 1.0f - ( x * x + y * y + z * z ) ) ) );
}

SGF_INLINE_FORCED const float *CCompQuaternion::ToFloatPtr() const {
	return &x;
}

SGF_INLINE_FORCED float *CCompQuaternion::ToFloatPtr() {
	return &x;
}
} //end SGF
#endif /* !__MATH_QUAT_H__ */
