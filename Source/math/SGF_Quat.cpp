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


#include "math/SGF_Quaternion.h"
#include "math/SGF_Vector.h"
#include "math/SGF_Matriz.h"
#include "math/SGF_Angles.h"
#include "util/SGF_StringUtils.h"
#include "math/SGF_Rotation.h"

//#pragma hdrstop
namespace SGF {
/*
=====================
CQuaternion::ToAngles
=====================
*/
CAngles CQuaternion::ToAngles( void ) const {
	return ToMat3().ToAngles();
}

/*
=====================
CQuaternion::ToRotation
=====================
*/
CRotation CQuaternion::ToRotation( void ) const {
	CVector3D vec;
	float angle;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	angle = CMath::ACos( w );
	if ( angle == 0.0f ) {
		vec.Set( 0.0f, 0.0f, 1.0f );
	} else {
		//vec *= (1.0f / sin( angle ));
		vec.Normalize();
		vec.FixDegenerateNormal();
		angle *= 2.0f * CMath::M_RAD2DEG;
	}
	return CRotation( vec3_origin, vec, angle );
}

/*
=====================
CQuaternion::ToMat3
=====================
*/
CMatriz3D CQuaternion::ToMat3( void ) const {
	CMatriz3D	mat;
	float	wx, wy, wz;
	float	xx, yy, yz;
	float	xy, xz, zz;
	float	x2, y2, z2;

	x2 = x + x;
	y2 = y + y;
	z2 = z + z;

	xx = x * x2;
	xy = x * y2;
	xz = x * z2;

	yy = y * y2;
	yz = y * z2;
	zz = z * z2;

	wx = w * x2;
	wy = w * y2;
	wz = w * z2;

	mat[ 0 ][ 0 ] = 1.0f - ( yy + zz );
	mat[ 0 ][ 1 ] = xy - wz;
	mat[ 0 ][ 2 ] = xz + wy;

	mat[ 1 ][ 0 ] = xy + wz;
	mat[ 1 ][ 1 ] = 1.0f - ( xx + zz );
	mat[ 1 ][ 2 ] = yz - wx;

	mat[ 2 ][ 0 ] = xz - wy;
	mat[ 2 ][ 1 ] = yz + wx;
	mat[ 2 ][ 2 ] = 1.0f - ( xx + yy );

	return mat;
}

/*
=====================
CQuaternion::ToMat4
=====================
*/
CMatriz4D CQuaternion::ToMat4( void ) const {
	return ToMat3().ToMat4();
}

/*
=====================
CQuaternion::ToCQuat
=====================
*/
CCompQuaternion CQuaternion::ToCQuat( void ) const {
	if ( w < 0.0f ) {
		return CCompQuaternion( -x, -y, -z );
	}
	return CCompQuaternion( x, y, z );
}

/*
============
CQuaternion::ToAngularVelocity
============
*/
CVector3D CQuaternion::ToAngularVelocity( void ) const {
	CVector3D vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	vec.Normalize();
	return vec * CMath::ACos( w );
}

/*
=============
CQuaternion::ToString
=============
*/
const char *CQuaternion::ToString( int precision ) const {
	return CMyString::FloatArrayToString( ToFloatPtr(), GetDimension(), precision );
}

/*
=====================
CQuaternion::Slerp

Spherical linear interpolation between two quaternions.
=====================
*/
CQuaternion &CQuaternion::Slerp( const CQuaternion &from, const CQuaternion &to, float t ) {
	CQuaternion	temp;
	float	omega, cosom, sinom, scale0, scale1;

	if ( t <= 0.0f ) {
		*this = from;
		return *this;
	}

	if ( t >= 1.0f ) {
		*this = to;
		return *this;
	}

	if ( from == to ) {
		*this = to;
		return *this;
	}

	cosom = from.x * to.x + from.y * to.y + from.z * to.z + from.w * to.w;
	if ( cosom < 0.0f ) {
		temp = -to;
		cosom = -cosom;
	} else {
		temp = to;
	}

	if ( ( 1.0f - cosom ) > 1e-6f ) {
#if 0
		omega = acos( cosom );
		sinom = 1.0f / sin( omega );
		scale0 = sin( ( 1.0f - t ) * omega ) * sinom;
		scale1 = sin( t * omega ) * sinom;
#else
		scale0 = 1.0f - cosom * cosom;
		sinom = CMath::InvSqrt( scale0 );
		omega = CMath::ATan16( scale0 * sinom, cosom );
		scale0 = CMath::Sin16( ( 1.0f - t ) * omega ) * sinom;
		scale1 = CMath::Sin16( t * omega ) * sinom;
#endif
	} else {
		scale0 = 1.0f - t;
		scale1 = t;
	}

	*this = ( scale0 * from ) + ( scale1 * temp );
	return *this;
}

/*
=============
CCompQuaternion::ToAngles
=============
*/
CAngles CCompQuaternion::ToAngles( void ) const {
	return ToQuat().ToAngles();
}

/*
=============
CCompQuaternion::ToRotation
=============
*/
CRotation CCompQuaternion::ToRotation( void ) const {
	return ToQuat().ToRotation();
}

/*
=============
CCompQuaternion::ToMat3
=============
*/
CMatriz3D CCompQuaternion::ToMat3( void ) const {
	return ToQuat().ToMat3();
}

/*
=============
CCompQuaternion::ToMat4
=============
*/
CMatriz4D CCompQuaternion::ToMat4( void ) const {
	return ToQuat().ToMat4();
}

/*
=============
CCompQuaternion::ToString
=============
*/
const char *CCompQuaternion::ToString( int precision ) const {
	return CMyString::FloatArrayToString( ToFloatPtr(), GetDimension(), precision );
}
}