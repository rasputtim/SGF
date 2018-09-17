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

#ifndef __MATH_ROTATION_H__
#define __MATH_ROTATION_H__
#include "../SGF_Config.h"
#include "SGF_Vector.h"
#include "SGF_Matriz.h"
#include "SGF_Angles.h"
#include "../util/SGF_StringUtils.h"


/*
===============================================================================

	Describes a complete rotation in degrees about an abritray axis.
	A local rotation matrix is stored for fast rotation of multiple points.

===============================================================================
*/

namespace SGF {
class CAngles;
class CQuaternion;
class CMatriz3D;

class CRotation {

	friend class CAngles;
	friend class CQuaternion;
	friend class CMatriz3D;

public:
						CRotation();
						CRotation( const CVector3D &rotationOrigin, const CVector3D &rotationVec, const float rotationAngle );

	void				Set( const CVector3D &rotationOrigin, const CVector3D &rotationVec, const float rotationAngle );
	void				SetOrigin( const CVector3D &rotationOrigin );
	void				SetVec( const CVector3D &rotationVec );					// has to be normalized
	void				SetVec( const float x, const float y, const float z );	// has to be normalized
	void				SetAngle( const float rotationAngle );
	void				Scale( const float s );
	void				ReCalculateMatrix();
	const CVector3D &		GetOrigin() const;
	const CVector3D &		GetVec() const;
	float				GetAngle() const;

	CRotation			operator-() const;										// flips rotation
	CRotation			operator*( const float s ) const;						// scale rotation
	CRotation			operator/( const float s ) const;						// scale rotation
	CRotation &		operator*=( const float s );							// scale rotation
	CRotation &		operator/=( const float s );							// scale rotation
	CVector3D				operator*( const CVector3D &v ) const;						// rotate vector

	friend CRotation	operator*( const float s, const CRotation &r );		// scale rotation
	friend CVector3D		operator*( const CVector3D &v, const CRotation &r );		// rotate vector
	friend CVector3D &		operator*=( CVector3D &v, const CRotation &r );			// rotate vector

	CAngles			ToAngles() const;
	CQuaternion				ToQuat() const;
	const CMatriz3D &		ToMat3() const;
	CMatriz4D				ToMat4() const;
	CVector3D				ToAngularVelocity() const;

	void				RotatePoint( CVector3D &point ) const;

	void				Normalize180();
	void				Normalize360();

private:
	CVector3D				origin;			// origin of rotation
	CVector3D				vec;			// normalized vector to rotate around
	float				angle;			// angle of rotation in degrees
	mutable CMatriz3D		axis;			// rotation axis
	mutable bool		axisValid;		// true if rotation axis is valid
};


SGF_INLINE_FORCED CRotation::CRotation() {
}

SGF_INLINE_FORCED CRotation::CRotation( const CVector3D &rotationOrigin, const CVector3D &rotationVec, const float rotationAngle ) {
	origin = rotationOrigin;
	vec = rotationVec;
	angle = rotationAngle;
	axisValid = false;
}

SGF_INLINE_FORCED void CRotation::Set( const CVector3D &rotationOrigin, const CVector3D &rotationVec, const float rotationAngle ) {
	origin = rotationOrigin;
	vec = rotationVec;
	angle = rotationAngle;
	axisValid = false;
}

SGF_INLINE_FORCED void CRotation::SetOrigin( const CVector3D &rotationOrigin ) {
	origin = rotationOrigin;
}

SGF_INLINE_FORCED void CRotation::SetVec( const CVector3D &rotationVec ) {
	vec = rotationVec;
	axisValid = false;
}

SGF_INLINE_FORCED void CRotation::SetVec( float x, float y, float z ) {
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
	axisValid = false;
}

SGF_INLINE_FORCED void CRotation::SetAngle( const float rotationAngle ) {
	angle = rotationAngle;
	axisValid = false;
}

SGF_INLINE_FORCED void CRotation::Scale( const float s ) {
	angle *= s;
	axisValid = false;
}

SGF_INLINE_FORCED void CRotation::ReCalculateMatrix() {
	axisValid = false;
	ToMat3();
}

SGF_INLINE_FORCED const CVector3D &CRotation::GetOrigin() const {
	return origin;
}

SGF_INLINE_FORCED const CVector3D &CRotation::GetVec() const  {
	return vec;
}

SGF_INLINE_FORCED float CRotation::GetAngle() const  {
	return angle;
}

SGF_INLINE_FORCED CRotation CRotation::operator-() const {
	return CRotation( origin, vec, -angle );
}

SGF_INLINE_FORCED CRotation CRotation::operator*( const float s ) const {
	return CRotation( origin, vec, angle * s );
}

SGF_INLINE_FORCED CRotation CRotation::operator/( const float s ) const {
	assert( s != 0.0f );
	return CRotation( origin, vec, angle / s );
}

SGF_INLINE_FORCED CRotation &CRotation::operator*=( const float s ) {
	angle *= s;
	axisValid = false;
	return *this;
}

SGF_INLINE_FORCED CRotation &CRotation::operator/=( const float s ) {
	assert( s != 0.0f );
	angle /= s;
	axisValid = false;
	return *this;
}

SGF_INLINE_FORCED CVector3D CRotation::operator*( const CVector3D &v ) const {
	if ( !axisValid ) {
		ToMat3();
	}
	return ((v - origin) * axis + origin);
}

SGF_INLINE_FORCED CRotation operator*( const float s, const CRotation &r ) {
	return r * s;
}

SGF_INLINE_FORCED CVector3D operator*( const CVector3D &v, const CRotation &r ) {
	return r * v;
}

SGF_INLINE_FORCED CVector3D &operator*=( CVector3D &v, const CRotation &r ) {
	v = r * v;
	return v;
}

SGF_INLINE_FORCED void CRotation::RotatePoint( CVector3D &point ) const {
	if ( !axisValid ) {
		ToMat3();
	}
	point = ((point - origin) * axis + origin);
}
} //end SGF
#endif /* !__MATH_ROTATION_H__ */
