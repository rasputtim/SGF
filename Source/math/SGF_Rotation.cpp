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

#include "math/SGF_Rotation.h"
#include "math/SGF_Vector.h"
#include "math/SGF_Matriz.h"
#include "math/SGF_Angles.h"
#include "math/SGF_Quaternion.h"
#include "util/SGF_StringUtils.h"

//#pragma hdrstop
namespace SGF {

/*
============
CRotation::ToAngles
============
*/
CAngles CRotation::ToAngles() const {
	return ToMat3().ToAngles();
}

/*
============
CRotation::ToQuat
============
*/
CQuaternion CRotation::ToQuat() const {
	float a, s, c;

	a = angle * ( CMath::M_DEG2RAD * 0.5f );
	CMath::SinCos( a, s, c );
	return CQuaternion( vec.x * s, vec.y * s, vec.z * s, c );
}

/*
============
CRotation::toMat3
============
*/
const CMatriz3D &CRotation::ToMat3() const {
	float wx, wy, wz;
	float xx, yy, yz;
	float xy, xz, zz;
	float x2, y2, z2;
	float a, c, s, x, y, z;

	if ( axisValid ) {
		return axis;
	}

	a = angle * ( CMath::M_DEG2RAD * 0.5f );
	CMath::SinCos( a, s, c );

	x = vec[0] * s;
	y = vec[1] * s;
	z = vec[2] * s;

	x2 = x + x;
	y2 = y + y;
	z2 = z + z;

	xx = x * x2;
	xy = x * y2;
	xz = x * z2;

	yy = y * y2;
	yz = y * z2;
	zz = z * z2;

	wx = c * x2;
	wy = c * y2;
	wz = c * z2;

	axis[ 0 ][ 0 ] = 1.0f - ( yy + zz );
	axis[ 0 ][ 1 ] = xy - wz;
	axis[ 0 ][ 2 ] = xz + wy;

	axis[ 1 ][ 0 ] = xy + wz;
	axis[ 1 ][ 1 ] = 1.0f - ( xx + zz );
	axis[ 1 ][ 2 ] = yz - wx;

	axis[ 2 ][ 0 ] = xz - wy;
	axis[ 2 ][ 1 ] = yz + wx;
	axis[ 2 ][ 2 ] = 1.0f - ( xx + yy );

	axisValid = true;

	return axis;
}

/*
============
CRotation::ToMat4
============
*/
CMatriz4D CRotation::ToMat4() const {
	return ToMat3().ToMat4();
}

/*
============
CRotation::ToAngularVelocity
============
*/
CVector3D CRotation::ToAngularVelocity() const {
	return vec * DEG2RAD( angle );
}

/*
============
CRotation::Normalize180
============
*/
void CRotation::Normalize180() {
	angle -= floor( angle / 360.0f ) * 360.0f;
	if ( angle > 180.0f ) {
		angle -= 360.0f;
	}
	else if ( angle < -180.0f ) {
		angle += 360.0f;
	}
}

/*
============
CRotation::Normalize360
============
*/
void CRotation::Normalize360() {
	angle -= floor( angle / 360.0f ) * 360.0f;
	if ( angle > 360.0f ) {
		angle -= 360.0f;
	}
	else if ( angle < 0.0f ) {
		angle += 360.0f;
	}
}
} //end SGF