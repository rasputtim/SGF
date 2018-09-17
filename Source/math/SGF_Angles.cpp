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

#include "math/SGF_Angles.h"
#include "math/SGF_Quaternion.h"
#include "math/SGF_Rotation.h"

//#pragma hdrstop

#include <float.h>
namespace SGF {
CAngles ang_zero( 0.0f, 0.0f, 0.0f );


/*
=================
CAngles::Normalize360

returns angles normalized to the range [0 <= angle < 360]
=================
*/
CAngles& CAngles::Normalize360() {
	int i;

	for ( i = 0; i < 3; i++ ) {
		if ( ( (*this)[i] >= 360.0f ) || ( (*this)[i] < 0.0f ) ) {
			(*this)[i] -= floor( (*this)[i] / 360.0f ) * 360.0f;

			if ( (*this)[i] >= 360.0f ) {
				(*this)[i] -= 360.0f;
			}
			if ( (*this)[i] < 0.0f ) {
				(*this)[i] += 360.0f;
			}
		}
	}

	return *this;
}

/*
=================
CAngles::Normalize180

returns angles normalized to the range [-180 < angle <= 180]
=================
*/
CAngles& CAngles::Normalize180() {
	Normalize360();

	if ( pitch > 180.0f ) {
		pitch -= 360.0f;
	}
	
	if ( yaw > 180.0f ) {
		yaw -= 360.0f;
	}

	if ( roll > 180.0f ) {
		roll -= 360.0f;
	}
	return *this;
}

/*
=================
CAngles::ToVectors
=================
*/
void CAngles::ToVectors( CVector3D *forward, CVector3D *right, CVector3D *up ) const {
	float sr, sp, sy, cr, cp, cy;
	
	CMath::SinCos( DEG2RAD( yaw ), sy, cy );
	CMath::SinCos( DEG2RAD( pitch ), sp, cp );
	CMath::SinCos( DEG2RAD( roll ), sr, cr );

	if ( forward ) {
		forward->Set( cp * cy, cp * sy, -sp );
	}

	if ( right ) {
		right->Set( -sr * sp * cy + cr * sy, -sr * sp * sy + -cr * cy, -sr * cp );
	}

	if ( up ) {
		up->Set( cr * sp * cy + -sr * -sy, cr * sp * sy + -sr * cy, cr * cp );
	}
}

/*
=================
CAngles::ToForward
=================
*/
CVector3D CAngles::ToForward() const {
	float sp, sy, cp, cy;
	
	CMath::SinCos( DEG2RAD( yaw ), sy, cy );
	CMath::SinCos( DEG2RAD( pitch ), sp, cp );

	return CVector3D( cp * cy, cp * sy, -sp );
}

/*
=================
CAngles::ToQuat
=================
*/
CQuaternion CAngles::ToQuat() const {
	float sx, cx, sy, cy, sz, cz;
	float sxcy, cxcy, sxsy, cxsy;

	CMath::SinCos( DEG2RAD( yaw ) * 0.5f, sz, cz );
	CMath::SinCos( DEG2RAD( pitch ) * 0.5f, sy, cy );
	CMath::SinCos( DEG2RAD( roll ) * 0.5f, sx, cx );

	sxcy = sx * cy;
	cxcy = cx * cy;
	sxsy = sx * sy;
	cxsy = cx * sy;

	return CQuaternion( cxsy*sz - sxcy*cz, -cxsy*cz - sxcy*sz, sxsy*cz - cxcy*sz, cxcy*cz + sxsy*sz );
}

/*
=================
CAngles::ToRotation
=================
*/
CRotation CAngles::ToRotation() const {
	CVector3D vec;
	float angle, w;
	float sx, cx, sy, cy, sz, cz;
	float sxcy, cxcy, sxsy, cxsy;

	if ( pitch == 0.0f ) {
		if ( yaw == 0.0f ) {
			return CRotation( vec3_origin, CVector3D( -1.0f, 0.0f, 0.0f ), roll );
		}
		if ( roll == 0.0f ) {
			return CRotation( vec3_origin, CVector3D( 0.0f, 0.0f, -1.0f ), yaw );
		}
	} else if ( yaw == 0.0f && roll == 0.0f ) {
		return CRotation( vec3_origin, CVector3D( 0.0f, -1.0f, 0.0f ), pitch );
	}

	CMath::SinCos( DEG2RAD( yaw ) * 0.5f, sz, cz );
	CMath::SinCos( DEG2RAD( pitch ) * 0.5f, sy, cy );
	CMath::SinCos( DEG2RAD( roll ) * 0.5f, sx, cx );

	sxcy = sx * cy;
	cxcy = cx * cy;
	sxsy = sx * sy;
	cxsy = cx * sy;

	vec.x =  cxsy * sz - sxcy * cz;
	vec.y = -cxsy * cz - sxcy * sz;
	vec.z =  sxsy * cz - cxcy * sz;
	w =		 cxcy * cz + sxsy * sz;
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
=================
CAngles::ToMat3
=================
*/
CMatriz3D CAngles::ToMat3() const {
	CMatriz3D mat;
	float sr, sp, sy, cr, cp, cy;

	CMath::SinCos( DEG2RAD( yaw ), sy, cy );
	CMath::SinCos( DEG2RAD( pitch ), sp, cp );
	CMath::SinCos( DEG2RAD( roll ), sr, cr );

	mat[ 0 ].Set( cp * cy, cp * sy, -sp );
	mat[ 1 ].Set( sr * sp * cy + cr * -sy, sr * sp * sy + cr * cy, sr * cp );
	mat[ 2 ].Set( cr * sp * cy + -sr * -sy, cr * sp * sy + -sr * cy, cr * cp );

	return mat;
}

/*
=================
CAngles::ToMat4
=================
*/
CMatriz4D CAngles::ToMat4() const {
	return ToMat3().ToMat4();
}

/*
=================
CAngles::ToAngularVelocity
=================
*/
CVector3D CAngles::ToAngularVelocity() const {
	CRotation rotation = CAngles::ToRotation();
	return rotation.GetVec() * DEG2RAD( rotation.GetAngle() );
}

/*
=============
CAngles::ToString
=============
*/
const char *CAngles::ToString( int precision ) const {
	return CMyString::FloatArrayToString( ToFloatPtr(), GetDimension(), precision );
}
} //end SGF