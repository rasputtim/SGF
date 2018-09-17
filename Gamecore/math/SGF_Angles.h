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

#ifndef __MATH_ANGLES_H__
#define __MATH_ANGLES_H__
#include "../SGF_Config.h"
#include "SGF_Vector.h"

/*
===============================================================================

	Euler angles

===============================================================================
*/
namespace SGF {
// angle indexes
#define	PITCH				0		// up / down
#define	YAW					1		// left / right
#define	ROLL				2		// fall over


class CVector3D;
class CQuaternion;
class CRotation;
class CMatriz3D;
class CMatriz4D;

class CAngles {
public:
	float			pitch;
	float			yaw;
	float			roll;

					CAngles();
					CAngles( float pitch, float yaw, float roll );
					explicit CAngles( const CVector3D &v );

	void 			Set( float pitch, float yaw, float roll );
	CAngles &		Zero();

	float			operator[]( int index ) const;
	float &			operator[]( int index );
	CAngles		operator-() const;			// negate angles, in general not the inverse rotation
	CAngles &		operator=( const CAngles &a );
	CAngles		operator+( const CAngles &a ) const;
	CAngles &		operator+=( const CAngles &a );
	CAngles		operator-( const CAngles &a ) const;
	CAngles &		operator-=( const CAngles &a );
	CAngles		operator*( const float a ) const;
	CAngles &		operator*=( const float a );
	CAngles		operator/( const float a ) const;
	CAngles &		operator/=( const float a );

	friend CAngles	operator*( const float a, const CAngles &b );

	bool			Compare( const CAngles &a ) const;							// exact compare, no epsilon
	bool			Compare( const CAngles &a, const float epsilon ) const;	// compare with epsilon
	bool			operator==(	const CAngles &a ) const;						// exact compare, no epsilon
	bool			operator!=(	const CAngles &a ) const;						// exact compare, no epsilon

	CAngles &		Normalize360();	// normalizes 'this'
	CAngles &		Normalize180();	// normalizes 'this'

	void			Clamp( const CAngles &min, const CAngles &max );

	int				GetDimension() const;

	void			ToVectors( CVector3D *forward, CVector3D *right = NULL, CVector3D *up = NULL ) const;
	CVector3D			ToForward() const;
	CQuaternion			ToQuat() const;
	CRotation		ToRotation() const;
	CMatriz3D			ToMat3() const;
	CMatriz4D			ToMat4() const;
	CVector3D			ToAngularVelocity() const;
	const float *	ToFloatPtr() const;
	float *			ToFloatPtr();
	const char *	ToString( int precision = 2 ) const;
};

extern CAngles ang_zero;

SGF_INLINE_FORCED CAngles::CAngles() {
}

SGF_INLINE_FORCED CAngles::CAngles( float pitch, float yaw, float roll ) {
	this->pitch = pitch;
	this->yaw	= yaw;
	this->roll	= roll;
}

SGF_INLINE_FORCED CAngles::CAngles( const CVector3D &v ) {
	this->pitch = v[0];
	this->yaw	= v[1];
	this->roll	= v[2];
}

SGF_INLINE_FORCED void CAngles::Set( float pitch, float yaw, float roll ) {
	this->pitch = pitch;
	this->yaw	= yaw;
	this->roll	= roll;
}

SGF_INLINE_FORCED CAngles &CAngles::Zero() {
	pitch = yaw = roll = 0.0f;
	return *this;
}

SGF_INLINE_FORCED float CAngles::operator[]( int index ) const {
	assert( ( index >= 0 ) && ( index < 3 ) );
	return ( &pitch )[ index ];
}

SGF_INLINE_FORCED float &CAngles::operator[]( int index ) {
	assert( ( index >= 0 ) && ( index < 3 ) );
	return ( &pitch )[ index ];
}

SGF_INLINE_FORCED CAngles CAngles::operator-() const {
	return CAngles( -pitch, -yaw, -roll );
}

SGF_INLINE_FORCED CAngles &CAngles::operator=( const CAngles &a ) {
	pitch	= a.pitch;
	yaw		= a.yaw;
	roll	= a.roll;
	return *this;
}

SGF_INLINE_FORCED CAngles CAngles::operator+( const CAngles &a ) const {
	return CAngles( pitch + a.pitch, yaw + a.yaw, roll + a.roll );
}

SGF_INLINE_FORCED CAngles& CAngles::operator+=( const CAngles &a ) {
	pitch	+= a.pitch;
	yaw		+= a.yaw;
	roll	+= a.roll;

	return *this;
}

SGF_INLINE_FORCED CAngles CAngles::operator-( const CAngles &a ) const {
	return CAngles( pitch - a.pitch, yaw - a.yaw, roll - a.roll );
}

SGF_INLINE_FORCED CAngles& CAngles::operator-=( const CAngles &a ) {
	pitch	-= a.pitch;
	yaw		-= a.yaw;
	roll	-= a.roll;

	return *this;
}

SGF_INLINE_FORCED CAngles CAngles::operator*( const float a ) const {
	return CAngles( pitch * a, yaw * a, roll * a );
}

SGF_INLINE_FORCED CAngles& CAngles::operator*=( float a ) {
	pitch	*= a;
	yaw		*= a;
	roll	*= a;
	return *this;
}

SGF_INLINE_FORCED CAngles CAngles::operator/( const float a ) const {
	float inva = 1.0f / a;
	return CAngles( pitch * inva, yaw * inva, roll * inva );
}

SGF_INLINE_FORCED CAngles& CAngles::operator/=( float a ) {
	float inva = 1.0f / a;
	pitch	*= inva;
	yaw		*= inva;
	roll	*= inva;
	return *this;
}

SGF_INLINE_FORCED CAngles operator*( const float a, const CAngles &b ) {
	return CAngles( a * b.pitch, a * b.yaw, a * b.roll );
}

SGF_INLINE_FORCED bool CAngles::Compare( const CAngles &a ) const {
	return ( ( a.pitch == pitch ) && ( a.yaw == yaw ) && ( a.roll == roll ) );
}

SGF_INLINE_FORCED bool CAngles::Compare( const CAngles &a, const float epsilon ) const {
	if ( CMath::Fabs( pitch - a.pitch ) > epsilon ) {
		return false;
	}
			
	if ( CMath::Fabs( yaw - a.yaw ) > epsilon ) {
		return false;
	}

	if ( CMath::Fabs( roll - a.roll ) > epsilon ) {
		return false;
	}

	return true;
}

SGF_INLINE_FORCED bool CAngles::operator==( const CAngles &a ) const {
	return Compare( a );
}

SGF_INLINE_FORCED bool CAngles::operator!=( const CAngles &a ) const {
	return !Compare( a );
}

SGF_INLINE_FORCED void CAngles::Clamp( const CAngles &min, const CAngles &max ) {
	if ( pitch < min.pitch ) {
		pitch = min.pitch;
	} else if ( pitch > max.pitch ) {
		pitch = max.pitch;
	}
	if ( yaw < min.yaw ) {
		yaw = min.yaw;
	} else if ( yaw > max.yaw ) {
		yaw = max.yaw;
	}
	if ( roll < min.roll ) {
		roll = min.roll;
	} else if ( roll > max.roll ) {
		roll = max.roll;
	}
}

SGF_INLINE_FORCED int CAngles::GetDimension() const {
	return 3;
}

SGF_INLINE_FORCED const float *CAngles::ToFloatPtr() const {
	return &pitch;
}

SGF_INLINE_FORCED float *CAngles::ToFloatPtr() {
	return &pitch;
}
} //end SGF
#endif /* !__MATH_ANGLES_H__ */
