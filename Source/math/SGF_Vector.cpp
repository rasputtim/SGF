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


#include "math/SGF_Vector.h"
#include "util/SGF_StringUtils.h"
#include "math/SGF_Matriz.h"
#include "math/SGF_Angles.h"


namespace SGF {
CVector2D vec2_origin( 0.0f, 0.0f );
CVector3D vec3_origin( 0.0f, 0.0f, 0.0f );
CVector4D vec4_origin( 0.0f, 0.0f, 0.0f, 0.0f );
CVector5D vec5_origin( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f );
CVector6D vec6_origin( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f );
CVector6D vec6_infinity( CMath::INFINITY, CMath::INFINITY, CMath::INFINITY, CMath::INFINITY, CMath::INFINITY, CMath::INFINITY );


//===============================================================
//
//	CVector2D
//
//===============================================================

/*
=============
CVector2D::ToString
=============
*/
const char *CVector2D::ToString( int precision ) const {
	return CMyString::FloatArrayToString( ToFloatPtr(), GetDimension(), precision );
}

/*
=============
Lerp

Linearly inperpolates one vector to another.
=============
*/
void CVector2D::Lerp( const CVector2D &v1, const CVector2D &v2, const float l ) {
	if ( l <= 0.0f ) {
		(*this) = v1;
	} else if ( l >= 1.0f ) {
		(*this) = v2;
	} else {
		(*this) = v1 + l * ( v2 - v1 );
	}
}


//===============================================================
//
//	CVector3D
//
//===============================================================

/*
=============
CVector3D::ToYaw
=============
*/
float CVector3D::ToYaw() const {
	float yaw;
	
	if ( ( y == 0.0f ) && ( x == 0.0f ) ) {
		yaw = 0.0f;
	} else {
		yaw = RAD2DEG( atan2( y, x ) );
		if ( yaw < 0.0f ) {
			yaw += 360.0f;
		}
	}

	return yaw;
}

/*
=============
CVector3D::ToPitch
=============
*/
float CVector3D::ToPitch() const {
	float	forward;
	float	pitch;
	
	if ( ( x == 0.0f ) && ( y == 0.0f ) ) {
		if ( z > 0.0f ) {
			pitch = 90.0f;
		} else {
			pitch = 270.0f;
		}
	} else {
		forward = ( float )CMath::Sqrt( x * x + y * y );
		pitch = RAD2DEG( atan2( z, forward ) );
		if ( pitch < 0.0f ) {
			pitch += 360.0f;
		}
	}

	return pitch;
}

/*
=============
CVector3D::ToAngles
=============
*/
CAngles CVector3D::ToAngles() const {
	float forward;
	float yaw;
	float pitch;
	
	if ( ( x == 0.0f ) && ( y == 0.0f ) ) {
		yaw = 0.0f;
		if ( z > 0.0f ) {
			pitch = 90.0f;
		} else {
			pitch = 270.0f;
		}
	} else {
		yaw = RAD2DEG( atan2( y, x ) );
		if ( yaw < 0.0f ) {
			yaw += 360.0f;
		}

		forward = ( float )CMath::Sqrt( x * x + y * y );
		pitch = RAD2DEG( atan2( z, forward ) );
		if ( pitch < 0.0f ) {
			pitch += 360.0f;
		}
	}

	return CAngles( -pitch, yaw, 0.0f );
}

/*
=============
CVector3D::ToPolar
=============
*/
CPolar3D CVector3D::ToPolar() const {
	float forward;
	float yaw;
	float pitch;
	
	if ( ( x == 0.0f ) && ( y == 0.0f ) ) {
		yaw = 0.0f;
		if ( z > 0.0f ) {
			pitch = 90.0f;
		} else {
			pitch = 270.0f;
		}
	} else {
		yaw = RAD2DEG( atan2( y, x ) );
		if ( yaw < 0.0f ) {
			yaw += 360.0f;
		}

		forward = ( float )CMath::Sqrt( x * x + y * y );
		pitch = RAD2DEG( atan2( z, forward ) );
		if ( pitch < 0.0f ) {
			pitch += 360.0f;
		}
	}
	return CPolar3D( CMath::Sqrt( x * x + y * y + z * z ), yaw, -pitch );
}

/*
=============
CVector3D::ToMat3
=============
*/
CMatriz3D CVector3D::ToMat3() const {
	CMatriz3D	mat;
	float	d;

	mat[0] = *this;
	d = x * x + y * y;
	if ( !d ) {
		mat[1][0] = 1.0f;
		mat[1][1] = 0.0f;
		mat[1][2] = 0.0f;
	} else {
		d = CMath::InvSqrt( d );
		mat[1][0] = -y * d;
		mat[1][1] = x * d;
		mat[1][2] = 0.0f;
	}
	mat[2] = Cross( mat[1] );

	return mat;
}

/*
=============
CVector3D::ToString
=============
*/
const char *CVector3D::ToString( int precision ) const {
	return CMyString::FloatArrayToString( ToFloatPtr(), GetDimension(), precision );
}

/*
=============
Lerp

Linearly inperpolates one vector to another.
=============
*/
void CVector3D::Lerp( const CVector3D &v1, const CVector3D &v2, const float l ) {
	if ( l <= 0.0f ) {
		(*this) = v1;
	} else if ( l >= 1.0f ) {
		(*this) = v2;
	} else {
		(*this) = v1 + l * ( v2 - v1 );
	}
}

/*
=============
SLerp

Spherical linear interpolation from v1 to v2.
Vectors are expected to be normalized.
=============
*/
#define LERP_DELTA 1e-6

void CVector3D::SLerp( const CVector3D &v1, const CVector3D &v2, const float t ) {
	float omega, cosom, sinom, scale0, scale1;

	if ( t <= 0.0f ) {
		(*this) = v1;
		return;
	} else if ( t >= 1.0f ) {
		(*this) = v2;
		return;
	}

	cosom = v1 * v2;
	if ( ( 1.0f - cosom ) > LERP_DELTA ) {
		omega = acos( cosom );
		sinom = sin( omega );
		scale0 = sin( ( 1.0f - t ) * omega ) / sinom;
		scale1 = sin( t * omega ) / sinom;
	} else {
		scale0 = 1.0f - t;
		scale1 = t;
	}

	(*this) = ( v1 * scale0 + v2 * scale1 );
}

/*
=============
ProjectSelfOntoSphere

Projects the z component onto a sphere.
=============
*/
void CVector3D::ProjectSelfOntoSphere( const float radius ) {
	float rsqr = radius * radius;
	float len = Length();
	if ( len  < rsqr * 0.5f ) {
		z = sqrt( rsqr - len );
	} else {
		z = rsqr / ( 2.0f * sqrt( len ) );
	}
}



//===============================================================
//
//	CVector4D
//
//===============================================================

/*
=============
CVector4D::ToString
=============
*/
const char *CVector4D::ToString( int precision ) const {
	return CMyString::FloatArrayToString( ToFloatPtr(), GetDimension(), precision );
}

/*
=============
Lerp

Linearly inperpolates one vector to another.
=============
*/
void CVector4D::Lerp( const CVector4D &v1, const CVector4D &v2, const float l ) {
	if ( l <= 0.0f ) {
		(*this) = v1;
	} else if ( l >= 1.0f ) {
		(*this) = v2;
	} else {
		(*this) = v1 + l * ( v2 - v1 );
	}
}


//===============================================================
//
//	CVector5D
//
//===============================================================

/*
=============
CVector5D::ToString
=============
*/
const char *CVector5D::ToString( int precision ) const {
	return CMyString::FloatArrayToString( ToFloatPtr(), GetDimension(), precision );
}

/*
=============
CVector5D::Lerp
=============
*/
void CVector5D::Lerp( const CVector5D &v1, const CVector5D &v2, const float l ) {
	if ( l <= 0.0f ) {
		(*this) = v1;
	} else if ( l >= 1.0f ) {
		(*this) = v2;
	} else {
		x = v1.x + l * ( v2.x - v1.x );
		y = v1.y + l * ( v2.y - v1.y );
		z = v1.z + l * ( v2.z - v1.z );
		s = v1.s + l * ( v2.s - v1.s );
		t = v1.t + l * ( v2.t - v1.t );
	}
}


//===============================================================
//
//	CVector6D
//
//===============================================================

/*
=============
CVector6D::ToString
=============
*/
const char *CVector6D::ToString( int precision ) const {
	return CMyString::FloatArrayToString( ToFloatPtr(), GetDimension(), precision );
}


//===============================================================
//
//	CVectorXD
//
//===============================================================

float	CVectorXD::temp[VECX_MAX_TEMP+4];
float *	CVectorXD::tempPtr = (float *) ( ( (uintptr_t) CVectorXD::temp + 15 ) & ~15 );
int		CVectorXD::tempIndex = 0;

/*
=============
CVectorXD::ToString
=============
*/
const char *CVectorXD::ToString( int precision ) const {
	return CMyString::FloatArrayToString( ToFloatPtr(), GetDimension(), precision );
}

} //end SGF