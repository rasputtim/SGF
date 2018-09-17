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

#ifndef __MATH_MATRIX_H__
#define __MATH_MATRIX_H__
#include "../SGF_Config.h"
#include "SGF_Vector.h"
#include "SGF_Simd.h"

namespace SGF{
/*
===============================================================================

  Matrix classes, all matrices are row-major except CMatriz3D

===============================================================================
*/

#define MATRIX_INVERSE_EPSILON		1e-14
#define MATRIX_EPSILON				1e-6

class CAngles;
class CQuaternion;
class CCompQuaternion;
class CRotation;
class CMatriz4D;

//===============================================================
//
//	CMatriz2D - 2x2 matrix
//
//===============================================================

class CMatriz2D {
public:
					CMatriz2D();
					explicit CMatriz2D( const CVector2D &x, const CVector2D &y );
					explicit CMatriz2D( const float xx, const float xy, const float yx, const float yy );
					explicit CMatriz2D( const float src[ 2 ][ 2 ] );

	const CVector2D &	operator[]( int index ) const;
	CVector2D &		operator[]( int index );
	CMatriz2D			operator-() const;
	CMatriz2D			operator*( const float a ) const;
	CVector2D			operator*( const CVector2D &vec ) const;
	CMatriz2D			operator*( const CMatriz2D &a ) const;
	CMatriz2D			operator+( const CMatriz2D &a ) const;
	CMatriz2D			operator-( const CMatriz2D &a ) const;
	CMatriz2D &		operator*=( const float a );
	CMatriz2D &		operator*=( const CMatriz2D &a );
	CMatriz2D &		operator+=( const CMatriz2D &a );
	CMatriz2D &		operator-=( const CMatriz2D &a );

	friend CMatriz2D	operator*( const float a, const CMatriz2D &mat );
	friend CVector2D	operator*( const CVector2D &vec, const CMatriz2D &mat );
	friend CVector2D &	operator*=( CVector2D &vec, const CMatriz2D &mat );

	bool			Compare( const CMatriz2D &a ) const;						// exact compare, no epsilon
	bool			Compare( const CMatriz2D &a, const float epsilon ) const;	// compare with epsilon
	bool			operator==( const CMatriz2D &a ) const;					// exact compare, no epsilon
	bool			operator!=( const CMatriz2D &a ) const;					// exact compare, no epsilon

	void			Zero();
	void			Identity();
	bool			IsIdentity( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsSymmetric( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsDiagonal( const float epsilon = MATRIX_EPSILON ) const;

	float			Trace() const;
	float			Determinant() const;
	CMatriz2D			Transpose() const;	// returns transpose
	CMatriz2D &		TransposeSelf();
	CMatriz2D			Inverse() const;		// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseSelf();		// returns false if determinant is zero
	CMatriz2D			InverseFast() const;	// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseFastSelf();	// returns false if determinant is zero

	int				GetDimension() const;

	const float *	ToFloatPtr() const;
	float *			ToFloatPtr();
	const char *	ToString( int precision = 2 ) const;

private:
	CVector2D			mat[ 2 ];
};

extern CMatriz2D mat2_zero;
extern CMatriz2D mat2_identity;
#define mat2_default	mat2_identity

SGF_INLINE_FORCED CMatriz2D::CMatriz2D() {
}

SGF_INLINE_FORCED CMatriz2D::CMatriz2D( const CVector2D &x, const CVector2D &y ) {
	mat[ 0 ].x = x.x; mat[ 0 ].y = x.y;
	mat[ 1 ].x = y.x; mat[ 1 ].y = y.y;
}

SGF_INLINE_FORCED CMatriz2D::CMatriz2D( const float xx, const float xy, const float yx, const float yy ) {
	mat[ 0 ].x = xx; mat[ 0 ].y = xy;
	mat[ 1 ].x = yx; mat[ 1 ].y = yy;
}

SGF_INLINE_FORCED CMatriz2D::CMatriz2D( const float src[ 2 ][ 2 ] ) {
	memcpy( mat, src, 2 * 2 * sizeof( float ) );
}

SGF_INLINE_FORCED const CVector2D &CMatriz2D::operator[]( int index ) const {
	//assert( ( index >= 0 ) && ( index < 2 ) );
	return mat[ index ];
}

SGF_INLINE_FORCED CVector2D &CMatriz2D::operator[]( int index ) {
	//assert( ( index >= 0 ) && ( index < 2 ) );
	return mat[ index ];
}

SGF_INLINE_FORCED CMatriz2D CMatriz2D::operator-() const {
	return CMatriz2D(	-mat[0][0], -mat[0][1],
					-mat[1][0], -mat[1][1] );
}

SGF_INLINE_FORCED CVector2D CMatriz2D::operator*( const CVector2D &vec ) const {
	return CVector2D(
		mat[ 0 ].x * vec.x + mat[ 0 ].y * vec.y,
		mat[ 1 ].x * vec.x + mat[ 1 ].y * vec.y );
}

SGF_INLINE_FORCED CMatriz2D CMatriz2D::operator*( const CMatriz2D &a ) const {
	return CMatriz2D(
		mat[0].x * a[0].x + mat[0].y * a[1].x,
		mat[0].x * a[0].y + mat[0].y * a[1].y,
		mat[1].x * a[0].x + mat[1].y * a[1].x,
		mat[1].x * a[0].y + mat[1].y * a[1].y );
}

SGF_INLINE_FORCED CMatriz2D CMatriz2D::operator*( const float a ) const {
	return CMatriz2D(
		mat[0].x * a, mat[0].y * a, 
		mat[1].x * a, mat[1].y * a );
}

SGF_INLINE_FORCED CMatriz2D CMatriz2D::operator+( const CMatriz2D &a ) const {
	return CMatriz2D(
		mat[0].x + a[0].x, mat[0].y + a[0].y, 
		mat[1].x + a[1].x, mat[1].y + a[1].y );
}
    
SGF_INLINE_FORCED CMatriz2D CMatriz2D::operator-( const CMatriz2D &a ) const {
	return CMatriz2D(
		mat[0].x - a[0].x, mat[0].y - a[0].y,
		mat[1].x - a[1].x, mat[1].y - a[1].y );
}

SGF_INLINE_FORCED CMatriz2D &CMatriz2D::operator*=( const float a ) {
	mat[0].x *= a; mat[0].y *= a;
	mat[1].x *= a; mat[1].y *= a;

    return *this;
}

SGF_INLINE_FORCED CMatriz2D &CMatriz2D::operator*=( const CMatriz2D &a ) {
	float x, y;
	x = mat[0].x; y = mat[0].y;
	mat[0].x = x * a[0].x + y * a[1].x;
	mat[0].y = x * a[0].y + y * a[1].y;
	x = mat[1].x; y = mat[1].y;
	mat[1].x = x * a[0].x + y * a[1].x;
	mat[1].y = x * a[0].y + y * a[1].y;
	return *this;
}

SGF_INLINE_FORCED CMatriz2D &CMatriz2D::operator+=( const CMatriz2D &a ) {
	mat[0].x += a[0].x; mat[0].y += a[0].y;
	mat[1].x += a[1].x; mat[1].y += a[1].y;

    return *this;
}

SGF_INLINE_FORCED CMatriz2D &CMatriz2D::operator-=( const CMatriz2D &a ) {
	mat[0].x -= a[0].x; mat[0].y -= a[0].y;
	mat[1].x -= a[1].x; mat[1].y -= a[1].y;

    return *this;
}

SGF_INLINE_FORCED CVector2D operator*( const CVector2D &vec, const CMatriz2D &mat ) {
	return mat * vec;
}

SGF_INLINE_FORCED CMatriz2D operator*( const float a, CMatriz2D const &mat ) {
	return mat * a;
}

SGF_INLINE_FORCED CVector2D &operator*=( CVector2D &vec, const CMatriz2D &mat ) {
	vec = mat * vec;
	return vec;
}

SGF_INLINE_FORCED bool CMatriz2D::Compare( const CMatriz2D &a ) const {
	if ( mat[0].Compare( a[0] ) &&
		mat[1].Compare( a[1] ) ) {
		return true;
	}
	return false;
}

SGF_INLINE_FORCED bool CMatriz2D::Compare( const CMatriz2D &a, const float epsilon ) const {
	if ( mat[0].Compare( a[0], epsilon ) &&
		mat[1].Compare( a[1], epsilon ) ) {
		return true;
	}
	return false;
}

SGF_INLINE_FORCED bool CMatriz2D::operator==( const CMatriz2D &a ) const {
	return Compare( a );
}

SGF_INLINE_FORCED bool CMatriz2D::operator!=( const CMatriz2D &a ) const {
	return !Compare( a );
}

SGF_INLINE_FORCED void CMatriz2D::Zero() {
	mat[0].Zero();
	mat[1].Zero();
}

SGF_INLINE_FORCED void CMatriz2D::Identity() {
	*this = mat2_identity;
}

SGF_INLINE_FORCED bool CMatriz2D::IsIdentity( const float epsilon ) const {
	return Compare( mat2_identity, epsilon );
}

SGF_INLINE_FORCED bool CMatriz2D::IsSymmetric( const float epsilon ) const {
	return ( CMath::Fabs( mat[0][1] - mat[1][0] ) < epsilon );
}

SGF_INLINE_FORCED bool CMatriz2D::IsDiagonal( const float epsilon ) const {
	if ( CMath::Fabs( mat[0][1] ) > epsilon ||
		CMath::Fabs( mat[1][0] ) > epsilon ) {
		return false;
	}
	return true;
}

SGF_INLINE_FORCED float CMatriz2D::Trace() const {
	return ( mat[0][0] + mat[1][1] );
}

SGF_INLINE_FORCED float CMatriz2D::Determinant() const {
	return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
}

SGF_INLINE_FORCED CMatriz2D CMatriz2D::Transpose() const {
	return CMatriz2D(	mat[0][0], mat[1][0],
					mat[0][1], mat[1][1] );
}

SGF_INLINE_FORCED CMatriz2D &CMatriz2D::TransposeSelf() {
	float tmp;

	tmp = mat[0][1];
	mat[0][1] = mat[1][0];
	mat[1][0] = tmp;

	return *this;
}

SGF_INLINE_FORCED CMatriz2D CMatriz2D::Inverse() const {
	CMatriz2D invMat;

	invMat = *this;
	int r = invMat.InverseSelf();
	assert( r );
	return invMat;
}

SGF_INLINE_FORCED CMatriz2D CMatriz2D::InverseFast() const {
	CMatriz2D invMat;

	invMat = *this;
	int r = invMat.InverseFastSelf();
	assert( r );
	return invMat;
}

SGF_INLINE_FORCED int CMatriz2D::GetDimension() const {
	return 4;
}

SGF_INLINE_FORCED const float *CMatriz2D::ToFloatPtr() const {
	return mat[0].ToFloatPtr();
}

SGF_INLINE_FORCED float *CMatriz2D::ToFloatPtr() {
	return mat[0].ToFloatPtr();
}


//===============================================================
//
//	CMatriz3D - 3x3 matrix
//
//	NOTE:	matrix is column-major
//
//===============================================================

class CMatriz3D {
public:
					CMatriz3D();
					explicit CMatriz3D( const CVector3D &x, const CVector3D &y, const CVector3D &z );
					explicit CMatriz3D( const float xx, const float xy, const float xz, const float yx, const float yy, const float yz, const float zx, const float zy, const float zz );
					explicit CMatriz3D( const float src[ 3 ][ 3 ] );

	const CVector3D &	operator[]( int index ) const;
	CVector3D &		operator[]( int index );
	CMatriz3D			operator-() const;
	CMatriz3D			operator*( const float a ) const;
	CVector3D			operator*( const CVector3D &vec ) const;
	CMatriz3D			operator*( const CMatriz3D &a ) const;
	CMatriz3D			operator+( const CMatriz3D &a ) const;
	CMatriz3D			operator-( const CMatriz3D &a ) const;
	CMatriz3D &		operator*=( const float a );
	CMatriz3D &		operator*=( const CMatriz3D &a );
	CMatriz3D &		operator+=( const CMatriz3D &a );
	CMatriz3D &		operator-=( const CMatriz3D &a );

	friend CMatriz3D	operator*( const float a, const CMatriz3D &mat );
	friend CVector3D	operator*( const CVector3D &vec, const CMatriz3D &mat );
	friend CVector3D &	operator*=( CVector3D &vec, const CMatriz3D &mat );

	bool			Compare( const CMatriz3D &a ) const;						// exact compare, no epsilon
	bool			Compare( const CMatriz3D &a, const float epsilon ) const;	// compare with epsilon
	bool			operator==( const CMatriz3D &a ) const;					// exact compare, no epsilon
	bool			operator!=( const CMatriz3D &a ) const;					// exact compare, no epsilon

	void			Zero();
	void			Identity();
	bool			IsIdentity( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsSymmetric( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsDiagonal( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsRotated() const;

	void			ProjectVector( const CVector3D &src, CVector3D &dst ) const;
	void			UnprojectVector( const CVector3D &src, CVector3D &dst ) const;

	bool			FixDegeneracies();	// fix degenerate axial cases
	bool			FixDenormals();		// change tiny numbers to zero

	float			Trace() const;
	float			Determinant() const;
	CMatriz3D			OrthoNormalize() const;
	CMatriz3D &		OrthoNormalizeSelf();
	CMatriz3D			Transpose() const;	// returns transpose
	CMatriz3D &		TransposeSelf();
	CMatriz3D			Inverse() const;		// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseSelf();		// returns false if determinant is zero
	CMatriz3D			InverseFast() const;	// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseFastSelf();	// returns false if determinant is zero
	CMatriz3D			TransposeMultiply( const CMatriz3D &b ) const;

	CMatriz3D			InertiaTranslate( const float mass, const CVector3D &centerOfMass, const CVector3D &translation ) const;
	CMatriz3D &		InertiaTranslateSelf( const float mass, const CVector3D &centerOfMass, const CVector3D &translation );
	CMatriz3D			InertiaRotate( const CMatriz3D &rotation ) const;
	CMatriz3D &		InertiaRotateSelf( const CMatriz3D &rotation );

	int				GetDimension() const;

	CAngles		ToAngles() const;
	CQuaternion			ToQuat() const;
	CCompQuaternion			ToCQuat() const;
	CRotation		ToRotation() const;
	CMatriz4D			ToMat4() const;
	CVector3D			ToAngularVelocity() const;
	const float *	ToFloatPtr() const;
	float *			ToFloatPtr();
	const char *	ToString( int precision = 2 ) const;

	friend void		TransposeMultiply( const CMatriz3D &inv, const CMatriz3D &b, CMatriz3D &dst );
	friend CMatriz3D	SkewSymmetric( CVector3D const &src );

private:
	CVector3D			mat[ 3 ];
};

extern CMatriz3D mat3_zero;
extern CMatriz3D mat3_identity;
#define mat3_default	mat3_identity

SGF_INLINE_FORCED CMatriz3D::CMatriz3D() {
}

SGF_INLINE_FORCED CMatriz3D::CMatriz3D( const CVector3D &x, const CVector3D &y, const CVector3D &z ) {
	mat[ 0 ].x = x.x; mat[ 0 ].y = x.y; mat[ 0 ].z = x.z;
	mat[ 1 ].x = y.x; mat[ 1 ].y = y.y; mat[ 1 ].z = y.z;
	mat[ 2 ].x = z.x; mat[ 2 ].y = z.y; mat[ 2 ].z = z.z;
}

SGF_INLINE_FORCED CMatriz3D::CMatriz3D( const float xx, const float xy, const float xz, const float yx, const float yy, const float yz, const float zx, const float zy, const float zz ) {
	mat[ 0 ].x = xx; mat[ 0 ].y = xy; mat[ 0 ].z = xz;
	mat[ 1 ].x = yx; mat[ 1 ].y = yy; mat[ 1 ].z = yz;
	mat[ 2 ].x = zx; mat[ 2 ].y = zy; mat[ 2 ].z = zz;
}

SGF_INLINE_FORCED CMatriz3D::CMatriz3D( const float src[ 3 ][ 3 ] ) {
	memcpy( mat, src, 3 * 3 * sizeof( float ) );
}

SGF_INLINE_FORCED const CVector3D &CMatriz3D::operator[]( int index ) const {
	//assert( ( index >= 0 ) && ( index < 3 ) );
	return mat[ index ];
}

SGF_INLINE_FORCED CVector3D &CMatriz3D::operator[]( int index ) {
	//assert( ( index >= 0 ) && ( index < 3 ) );
	return mat[ index ];
}

SGF_INLINE_FORCED CMatriz3D CMatriz3D::operator-() const {
	return CMatriz3D(	-mat[0][0], -mat[0][1], -mat[0][2],
					-mat[1][0], -mat[1][1], -mat[1][2],
					-mat[2][0], -mat[2][1], -mat[2][2] );
}

SGF_INLINE_FORCED CVector3D CMatriz3D::operator*( const CVector3D &vec ) const {
	return CVector3D(
		mat[ 0 ].x * vec.x + mat[ 1 ].x * vec.y + mat[ 2 ].x * vec.z,
		mat[ 0 ].y * vec.x + mat[ 1 ].y * vec.y + mat[ 2 ].y * vec.z,
		mat[ 0 ].z * vec.x + mat[ 1 ].z * vec.y + mat[ 2 ].z * vec.z );
}

SGF_INLINE_FORCED CMatriz3D CMatriz3D::operator*( const CMatriz3D &a ) const {
	int i, j;
	const float *m1Ptr, *m2Ptr;
	float *dstPtr;
	CMatriz3D dst;

	m1Ptr = reinterpret_cast<const float *>(this);
	m2Ptr = reinterpret_cast<const float *>(&a);
	dstPtr = reinterpret_cast<float *>(&dst);

	for ( i = 0; i < 3; i++ ) {
		for ( j = 0; j < 3; j++ ) {
			*dstPtr = m1Ptr[0] * m2Ptr[ 0 * 3 + j ]
					+ m1Ptr[1] * m2Ptr[ 1 * 3 + j ]
					+ m1Ptr[2] * m2Ptr[ 2 * 3 + j ];
			dstPtr++;
		}
		m1Ptr += 3;
	}
	return dst;
}

SGF_INLINE_FORCED CMatriz3D CMatriz3D::operator*( const float a ) const {
	return CMatriz3D(
		mat[0].x * a, mat[0].y * a, mat[0].z * a,
		mat[1].x * a, mat[1].y * a, mat[1].z * a,
		mat[2].x * a, mat[2].y * a, mat[2].z * a );
}

SGF_INLINE_FORCED CMatriz3D CMatriz3D::operator+( const CMatriz3D &a ) const {
	return CMatriz3D(
		mat[0].x + a[0].x, mat[0].y + a[0].y, mat[0].z + a[0].z,
		mat[1].x + a[1].x, mat[1].y + a[1].y, mat[1].z + a[1].z,
		mat[2].x + a[2].x, mat[2].y + a[2].y, mat[2].z + a[2].z );
}
    
SGF_INLINE_FORCED CMatriz3D CMatriz3D::operator-( const CMatriz3D &a ) const {
	return CMatriz3D(
		mat[0].x - a[0].x, mat[0].y - a[0].y, mat[0].z - a[0].z,
		mat[1].x - a[1].x, mat[1].y - a[1].y, mat[1].z - a[1].z,
		mat[2].x - a[2].x, mat[2].y - a[2].y, mat[2].z - a[2].z );
}

SGF_INLINE_FORCED CMatriz3D &CMatriz3D::operator*=( const float a ) {
	mat[0].x *= a; mat[0].y *= a; mat[0].z *= a;
	mat[1].x *= a; mat[1].y *= a; mat[1].z *= a; 
	mat[2].x *= a; mat[2].y *= a; mat[2].z *= a;

    return *this;
}

SGF_INLINE_FORCED CMatriz3D &CMatriz3D::operator*=( const CMatriz3D &a ) {
	int i, j;
	const float *m2Ptr;
	float *m1Ptr, dst[3];

	m1Ptr = reinterpret_cast<float *>(this);
	m2Ptr = reinterpret_cast<const float *>(&a);

	for ( i = 0; i < 3; i++ ) {
		for ( j = 0; j < 3; j++ ) {
			dst[j]  = m1Ptr[0] * m2Ptr[ 0 * 3 + j ]
					+ m1Ptr[1] * m2Ptr[ 1 * 3 + j ]
					+ m1Ptr[2] * m2Ptr[ 2 * 3 + j ];
		}
		m1Ptr[0] = dst[0]; m1Ptr[1] = dst[1]; m1Ptr[2] = dst[2];
		m1Ptr += 3;
	}
	return *this;
}

SGF_INLINE_FORCED CMatriz3D &CMatriz3D::operator+=( const CMatriz3D &a ) {
	mat[0].x += a[0].x; mat[0].y += a[0].y; mat[0].z += a[0].z;
	mat[1].x += a[1].x; mat[1].y += a[1].y; mat[1].z += a[1].z;
	mat[2].x += a[2].x; mat[2].y += a[2].y; mat[2].z += a[2].z;

    return *this;
}

SGF_INLINE_FORCED CMatriz3D &CMatriz3D::operator-=( const CMatriz3D &a ) {
	mat[0].x -= a[0].x; mat[0].y -= a[0].y; mat[0].z -= a[0].z;
	mat[1].x -= a[1].x; mat[1].y -= a[1].y; mat[1].z -= a[1].z;
	mat[2].x -= a[2].x; mat[2].y -= a[2].y; mat[2].z -= a[2].z;

    return *this;
}

SGF_INLINE_FORCED CVector3D operator*( const CVector3D &vec, const CMatriz3D &mat ) {
	return mat * vec;
}

SGF_INLINE_FORCED CMatriz3D operator*( const float a, const CMatriz3D &mat ) {
	return mat * a;
}

SGF_INLINE_FORCED CVector3D &operator*=( CVector3D &vec, const CMatriz3D &mat ) {
	float x = mat[ 0 ].x * vec.x + mat[ 1 ].x * vec.y + mat[ 2 ].x * vec.z;
	float y = mat[ 0 ].y * vec.x + mat[ 1 ].y * vec.y + mat[ 2 ].y * vec.z;
	vec.z = mat[ 0 ].z * vec.x + mat[ 1 ].z * vec.y + mat[ 2 ].z * vec.z;
	vec.x = x;
	vec.y = y;
	return vec;
}

SGF_INLINE_FORCED bool CMatriz3D::Compare( const CMatriz3D &a ) const {
	if ( mat[0].Compare( a[0] ) &&
		mat[1].Compare( a[1] ) &&
		mat[2].Compare( a[2] ) ) {
		return true;
	}
	return false;
}

SGF_INLINE_FORCED bool CMatriz3D::Compare( const CMatriz3D &a, const float epsilon ) const {
	if ( mat[0].Compare( a[0], epsilon ) &&
		mat[1].Compare( a[1], epsilon ) &&
		mat[2].Compare( a[2], epsilon ) ) {
		return true;
	}
	return false;
}

SGF_INLINE_FORCED bool CMatriz3D::operator==( const CMatriz3D &a ) const {
	return Compare( a );
}

SGF_INLINE_FORCED bool CMatriz3D::operator!=( const CMatriz3D &a ) const {
	return !Compare( a );
}

SGF_INLINE_FORCED void CMatriz3D::Zero() {
	memset( mat, 0, sizeof( CMatriz3D ) );
}

SGF_INLINE_FORCED void CMatriz3D::Identity() {
	*this = mat3_identity;
}

SGF_INLINE_FORCED bool CMatriz3D::IsIdentity( const float epsilon ) const {
	return Compare( mat3_identity, epsilon );
}

SGF_INLINE_FORCED bool CMatriz3D::IsSymmetric( const float epsilon ) const {
	if ( CMath::Fabs( mat[0][1] - mat[1][0] ) > epsilon ) {
		return false;
	}
	if ( CMath::Fabs( mat[0][2] - mat[2][0] ) > epsilon ) {
		return false;
	}
	if ( CMath::Fabs( mat[1][2] - mat[2][1] ) > epsilon ) {
		return false;
	}
	return true;
}

SGF_INLINE_FORCED bool CMatriz3D::IsDiagonal( const float epsilon ) const {
	if ( CMath::Fabs( mat[0][1] ) > epsilon ||
		CMath::Fabs( mat[0][2] ) > epsilon ||
		CMath::Fabs( mat[1][0] ) > epsilon ||
		CMath::Fabs( mat[1][2] ) > epsilon ||
		CMath::Fabs( mat[2][0] ) > epsilon ||
		CMath::Fabs( mat[2][1] ) > epsilon ) {
		return false;
	}
	return true;
}

SGF_INLINE_FORCED bool CMatriz3D::IsRotated() const {
	return !Compare( mat3_identity );
}

SGF_INLINE_FORCED void CMatriz3D::ProjectVector( const CVector3D &src, CVector3D &dst ) const {
	dst.x = src * mat[ 0 ];
	dst.y = src * mat[ 1 ];
	dst.z = src * mat[ 2 ];
}

SGF_INLINE_FORCED void CMatriz3D::UnprojectVector( const CVector3D &src, CVector3D &dst ) const {
	dst = mat[ 0 ] * src.x + mat[ 1 ] * src.y + mat[ 2 ] * src.z;
}

SGF_INLINE_FORCED bool CMatriz3D::FixDegeneracies() {
	bool r = mat[0].FixDegenerateNormal();
	r |= mat[1].FixDegenerateNormal();
	r |= mat[2].FixDegenerateNormal();
	return r;
}

SGF_INLINE_FORCED bool CMatriz3D::FixDenormals() {
	bool r = mat[0].FixDenormals();
	r |= mat[1].FixDenormals();
	r |= mat[2].FixDenormals();
	return r;
}

SGF_INLINE_FORCED float CMatriz3D::Trace() const {
	return ( mat[0][0] + mat[1][1] + mat[2][2] );
}

SGF_INLINE_FORCED CMatriz3D CMatriz3D::OrthoNormalize() const {
	CMatriz3D ortho;

	ortho = *this;
	ortho[ 0 ].Normalize();
	ortho[ 2 ].Cross( mat[ 0 ], mat[ 1 ] );
	ortho[ 2 ].Normalize();
	ortho[ 1 ].Cross( mat[ 2 ], mat[ 0 ] );
	ortho[ 1 ].Normalize();
	return ortho;
}

SGF_INLINE_FORCED CMatriz3D &CMatriz3D::OrthoNormalizeSelf() {
	mat[ 0 ].Normalize();
	mat[ 2 ].Cross( mat[ 0 ], mat[ 1 ] );
	mat[ 2 ].Normalize();
	mat[ 1 ].Cross( mat[ 2 ], mat[ 0 ] );
	mat[ 1 ].Normalize();
	return *this;
}

SGF_INLINE_FORCED CMatriz3D CMatriz3D::Transpose() const {
	return CMatriz3D(	mat[0][0], mat[1][0], mat[2][0],
					mat[0][1], mat[1][1], mat[2][1],
					mat[0][2], mat[1][2], mat[2][2] );
}

SGF_INLINE_FORCED CMatriz3D &CMatriz3D::TransposeSelf() {
	float tmp0, tmp1, tmp2;

	tmp0 = mat[0][1];
	mat[0][1] = mat[1][0];
	mat[1][0] = tmp0;
	tmp1 = mat[0][2];
	mat[0][2] = mat[2][0];
	mat[2][0] = tmp1;
	tmp2 = mat[1][2];
	mat[1][2] = mat[2][1];
	mat[2][1] = tmp2;

	return *this;
}

SGF_INLINE_FORCED CMatriz3D CMatriz3D::Inverse() const {
	CMatriz3D invMat;

	invMat = *this;
	int r = invMat.InverseSelf();
	assert( r );
	return invMat;
}

SGF_INLINE_FORCED CMatriz3D CMatriz3D::InverseFast() const {
	CMatriz3D invMat;

	invMat = *this;
	int r = invMat.InverseFastSelf();
	assert( r );
	return invMat;
}

SGF_INLINE_FORCED CMatriz3D CMatriz3D::TransposeMultiply( const CMatriz3D &b ) const {
	return CMatriz3D(	mat[0].x * b[0].x + mat[1].x * b[1].x + mat[2].x * b[2].x,
					mat[0].x * b[0].y + mat[1].x * b[1].y + mat[2].x * b[2].y,
					mat[0].x * b[0].z + mat[1].x * b[1].z + mat[2].x * b[2].z,
					mat[0].y * b[0].x + mat[1].y * b[1].x + mat[2].y * b[2].x,
					mat[0].y * b[0].y + mat[1].y * b[1].y + mat[2].y * b[2].y,
					mat[0].y * b[0].z + mat[1].y * b[1].z + mat[2].y * b[2].z,
					mat[0].z * b[0].x + mat[1].z * b[1].x + mat[2].z * b[2].x,
					mat[0].z * b[0].y + mat[1].z * b[1].y + mat[2].z * b[2].y,
					mat[0].z * b[0].z + mat[1].z * b[1].z + mat[2].z * b[2].z );
}

SGF_INLINE_FORCED void TransposeMultiply( const CMatriz3D &transpose, const CMatriz3D &b, CMatriz3D &dst ) {
	dst[0].x = transpose[0].x * b[0].x + transpose[1].x * b[1].x + transpose[2].x * b[2].x;
	dst[0].y = transpose[0].x * b[0].y + transpose[1].x * b[1].y + transpose[2].x * b[2].y;
	dst[0].z = transpose[0].x * b[0].z + transpose[1].x * b[1].z + transpose[2].x * b[2].z;
	dst[1].x = transpose[0].y * b[0].x + transpose[1].y * b[1].x + transpose[2].y * b[2].x;
	dst[1].y = transpose[0].y * b[0].y + transpose[1].y * b[1].y + transpose[2].y * b[2].y;
	dst[1].z = transpose[0].y * b[0].z + transpose[1].y * b[1].z + transpose[2].y * b[2].z;
	dst[2].x = transpose[0].z * b[0].x + transpose[1].z * b[1].x + transpose[2].z * b[2].x;
	dst[2].y = transpose[0].z * b[0].y + transpose[1].z * b[1].y + transpose[2].z * b[2].y;
	dst[2].z = transpose[0].z * b[0].z + transpose[1].z * b[1].z + transpose[2].z * b[2].z;
}

SGF_INLINE_FORCED CMatriz3D SkewSymmetric( CVector3D const &src ) {
	return CMatriz3D( 0.0f, -src.z,  src.y, src.z,   0.0f, -src.x, -src.y,  src.x,   0.0f );
}

SGF_INLINE_FORCED int CMatriz3D::GetDimension() const {
	return 9;
}

SGF_INLINE_FORCED const float *CMatriz3D::ToFloatPtr() const {
	return mat[0].ToFloatPtr();
}

SGF_INLINE_FORCED float *CMatriz3D::ToFloatPtr() {
	return mat[0].ToFloatPtr();
}


//===============================================================
//
//	CMatriz4D - 4x4 matrix
//
//===============================================================

class CMatriz4D {
public:
					CMatriz4D();
					explicit CMatriz4D( const CVector4D &x, const CVector4D &y, const CVector4D &z, const CVector4D &w );
					explicit CMatriz4D(const float xx, const float xy, const float xz, const float xw,
									const float yx, const float yy, const float yz, const float yw,
									const float zx, const float zy, const float zz, const float zw,
									const float wx, const float wy, const float wz, const float ww );
					explicit CMatriz4D( const CMatriz3D &rotation, const CVector3D &translation );
					explicit CMatriz4D( const float src[ 4 ][ 4 ] );

	const CVector4D &	operator[]( int index ) const;
	CVector4D &		operator[]( int index );
	CMatriz4D			operator*( const float a ) const;
	CVector4D			operator*( const CVector4D &vec ) const;
	CVector3D			operator*( const CVector3D &vec ) const;
	CMatriz4D			operator*( const CMatriz4D &a ) const;
	CMatriz4D			operator+( const CMatriz4D &a ) const;
	CMatriz4D			operator-( const CMatriz4D &a ) const;
	CMatriz4D &		operator*=( const float a );
	CMatriz4D &		operator*=( const CMatriz4D &a );
	CMatriz4D &		operator+=( const CMatriz4D &a );
	CMatriz4D &		operator-=( const CMatriz4D &a );

	friend CMatriz4D	operator*( const float a, const CMatriz4D &mat );
	friend CVector4D	operator*( const CVector4D &vec, const CMatriz4D &mat );
	friend CVector3D	operator*( const CVector3D &vec, const CMatriz4D &mat );
	friend CVector4D &	operator*=( CVector4D &vec, const CMatriz4D &mat );
	friend CVector3D &	operator*=( CVector3D &vec, const CMatriz4D &mat );

	bool			Compare( const CMatriz4D &a ) const;						// exact compare, no epsilon
	bool			Compare( const CMatriz4D &a, const float epsilon ) const;	// compare with epsilon
	bool			operator==( const CMatriz4D &a ) const;					// exact compare, no epsilon
	bool			operator!=( const CMatriz4D &a ) const;					// exact compare, no epsilon

	void			Zero();
	void			Identity();
	bool			IsIdentity( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsSymmetric( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsDiagonal( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsRotated() const;

	void			ProjectVector( const CVector4D &src, CVector4D &dst ) const;
	void			UnprojectVector( const CVector4D &src, CVector4D &dst ) const;

	float			Trace() const;
	float			Determinant() const;
	CMatriz4D			Transpose() const;	// returns transpose
	CMatriz4D &		TransposeSelf();
	CMatriz4D			Inverse() const;		// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseSelf();		// returns false if determinant is zero
	CMatriz4D			InverseFast() const;	// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseFastSelf();	// returns false if determinant is zero
	CMatriz4D			TransposeMultiply( const CMatriz4D &b ) const;

	int				GetDimension() const;

	const float *	ToFloatPtr() const;
	float *			ToFloatPtr();
	const char *	ToString( int precision = 2 ) const;

private:
	CVector4D			mat[ 4 ];
};

extern CMatriz4D mat4_zero;
extern CMatriz4D mat4_identity;
#define mat4_default	mat4_identity

SGF_INLINE_FORCED CMatriz4D::CMatriz4D() {
}

SGF_INLINE_FORCED CMatriz4D::CMatriz4D( const CVector4D &x, const CVector4D &y, const CVector4D &z, const CVector4D &w ) {
	mat[ 0 ] = x;
	mat[ 1 ] = y;
	mat[ 2 ] = z;
	mat[ 3 ] = w;
}

SGF_INLINE_FORCED CMatriz4D::CMatriz4D( const float xx, const float xy, const float xz, const float xw,
							const float yx, const float yy, const float yz, const float yw,
							const float zx, const float zy, const float zz, const float zw,
							const float wx, const float wy, const float wz, const float ww ) {
	mat[0][0] = xx; mat[0][1] = xy; mat[0][2] = xz; mat[0][3] = xw;
	mat[1][0] = yx; mat[1][1] = yy; mat[1][2] = yz; mat[1][3] = yw;
	mat[2][0] = zx; mat[2][1] = zy; mat[2][2] = zz; mat[2][3] = zw;
	mat[3][0] = wx; mat[3][1] = wy; mat[3][2] = wz; mat[3][3] = ww;
}

SGF_INLINE_FORCED CMatriz4D::CMatriz4D( const CMatriz3D &rotation, const CVector3D &translation ) {
	// NOTE: CMatriz3D is transposed because it is column-major
	mat[ 0 ][ 0 ] = rotation[0][0];
	mat[ 0 ][ 1 ] = rotation[1][0];
	mat[ 0 ][ 2 ] = rotation[2][0];
	mat[ 0 ][ 3 ] = translation[0];
	mat[ 1 ][ 0 ] = rotation[0][1];
	mat[ 1 ][ 1 ] = rotation[1][1];
	mat[ 1 ][ 2 ] = rotation[2][1];
	mat[ 1 ][ 3 ] = translation[1];
	mat[ 2 ][ 0 ] = rotation[0][2];
	mat[ 2 ][ 1 ] = rotation[1][2];
	mat[ 2 ][ 2 ] = rotation[2][2];
	mat[ 2 ][ 3 ] = translation[2];
	mat[ 3 ][ 0 ] = 0.0f;
	mat[ 3 ][ 1 ] = 0.0f;
	mat[ 3 ][ 2 ] = 0.0f;
	mat[ 3 ][ 3 ] = 1.0f;
}

SGF_INLINE_FORCED CMatriz4D::CMatriz4D( const float src[ 4 ][ 4 ] ) {
	memcpy( mat, src, 4 * 4 * sizeof( float ) );
}

SGF_INLINE_FORCED const CVector4D &CMatriz4D::operator[]( int index ) const {
	//assert( ( index >= 0 ) && ( index < 4 ) );
	return mat[ index ];
}

SGF_INLINE_FORCED CVector4D &CMatriz4D::operator[]( int index ) {
	//assert( ( index >= 0 ) && ( index < 4 ) );
	return mat[ index ];
}

SGF_INLINE_FORCED CMatriz4D CMatriz4D::operator*( const float a ) const {
	return CMatriz4D(
		mat[0].x * a, mat[0].y * a, mat[0].z * a, mat[0].w * a,
		mat[1].x * a, mat[1].y * a, mat[1].z * a, mat[1].w * a,
		mat[2].x * a, mat[2].y * a, mat[2].z * a, mat[2].w * a,
		mat[3].x * a, mat[3].y * a, mat[3].z * a, mat[3].w * a );
}

SGF_INLINE_FORCED CVector4D CMatriz4D::operator*( const CVector4D &vec ) const {
	return CVector4D(
		mat[ 0 ].x * vec.x + mat[ 0 ].y * vec.y + mat[ 0 ].z * vec.z + mat[ 0 ].w * vec.w,
		mat[ 1 ].x * vec.x + mat[ 1 ].y * vec.y + mat[ 1 ].z * vec.z + mat[ 1 ].w * vec.w,
		mat[ 2 ].x * vec.x + mat[ 2 ].y * vec.y + mat[ 2 ].z * vec.z + mat[ 2 ].w * vec.w,
		mat[ 3 ].x * vec.x + mat[ 3 ].y * vec.y + mat[ 3 ].z * vec.z + mat[ 3 ].w * vec.w );
}

SGF_INLINE_FORCED CVector3D CMatriz4D::operator*( const CVector3D &vec ) const {
	float s = mat[ 3 ].x * vec.x + mat[ 3 ].y * vec.y + mat[ 3 ].z * vec.z + mat[ 3 ].w;
	if ( s == 0.0f ) {
		return CVector3D( 0.0f, 0.0f, 0.0f );
	}
	if ( s == 1.0f ) {
		return CVector3D(
			mat[ 0 ].x * vec.x + mat[ 0 ].y * vec.y + mat[ 0 ].z * vec.z + mat[ 0 ].w,
			mat[ 1 ].x * vec.x + mat[ 1 ].y * vec.y + mat[ 1 ].z * vec.z + mat[ 1 ].w,
			mat[ 2 ].x * vec.x + mat[ 2 ].y * vec.y + mat[ 2 ].z * vec.z + mat[ 2 ].w );
	}
	else {
		float invS = 1.0f / s;
		return CVector3D(
			(mat[ 0 ].x * vec.x + mat[ 0 ].y * vec.y + mat[ 0 ].z * vec.z + mat[ 0 ].w) * invS,
			(mat[ 1 ].x * vec.x + mat[ 1 ].y * vec.y + mat[ 1 ].z * vec.z + mat[ 1 ].w) * invS,
			(mat[ 2 ].x * vec.x + mat[ 2 ].y * vec.y + mat[ 2 ].z * vec.z + mat[ 2 ].w) * invS );
	}
}

SGF_INLINE_FORCED CMatriz4D CMatriz4D::operator*( const CMatriz4D &a ) const {
	int i, j;
	const float *m1Ptr, *m2Ptr;
	float *dstPtr;
	CMatriz4D dst;

	m1Ptr = reinterpret_cast<const float *>(this);
	m2Ptr = reinterpret_cast<const float *>(&a);
	dstPtr = reinterpret_cast<float *>(&dst);

	for ( i = 0; i < 4; i++ ) {
		for ( j = 0; j < 4; j++ ) {
			*dstPtr = m1Ptr[0] * m2Ptr[ 0 * 4 + j ]
					+ m1Ptr[1] * m2Ptr[ 1 * 4 + j ]
					+ m1Ptr[2] * m2Ptr[ 2 * 4 + j ]
					+ m1Ptr[3] * m2Ptr[ 3 * 4 + j ];
			dstPtr++;
		}
		m1Ptr += 4;
	}
	return dst;
}

SGF_INLINE_FORCED CMatriz4D CMatriz4D::operator+( const CMatriz4D &a ) const {
	return CMatriz4D( 
		mat[0].x + a[0].x, mat[0].y + a[0].y, mat[0].z + a[0].z, mat[0].w + a[0].w,
		mat[1].x + a[1].x, mat[1].y + a[1].y, mat[1].z + a[1].z, mat[1].w + a[1].w,
		mat[2].x + a[2].x, mat[2].y + a[2].y, mat[2].z + a[2].z, mat[2].w + a[2].w,
		mat[3].x + a[3].x, mat[3].y + a[3].y, mat[3].z + a[3].z, mat[3].w + a[3].w );
}
    
SGF_INLINE_FORCED CMatriz4D CMatriz4D::operator-( const CMatriz4D &a ) const {
	return CMatriz4D( 
		mat[0].x - a[0].x, mat[0].y - a[0].y, mat[0].z - a[0].z, mat[0].w - a[0].w,
		mat[1].x - a[1].x, mat[1].y - a[1].y, mat[1].z - a[1].z, mat[1].w - a[1].w,
		mat[2].x - a[2].x, mat[2].y - a[2].y, mat[2].z - a[2].z, mat[2].w - a[2].w,
		mat[3].x - a[3].x, mat[3].y - a[3].y, mat[3].z - a[3].z, mat[3].w - a[3].w );
}

SGF_INLINE_FORCED CMatriz4D &CMatriz4D::operator*=( const float a ) {
	mat[0].x *= a; mat[0].y *= a; mat[0].z *= a; mat[0].w *= a;
	mat[1].x *= a; mat[1].y *= a; mat[1].z *= a; mat[1].w *= a;
	mat[2].x *= a; mat[2].y *= a; mat[2].z *= a; mat[2].w *= a;
	mat[3].x *= a; mat[3].y *= a; mat[3].z *= a; mat[3].w *= a;
    return *this;
}

SGF_INLINE_FORCED CMatriz4D &CMatriz4D::operator*=( const CMatriz4D &a ) {
	*this = (*this) * a;
	return *this;
}

SGF_INLINE_FORCED CMatriz4D &CMatriz4D::operator+=( const CMatriz4D &a ) {
	mat[0].x += a[0].x; mat[0].y += a[0].y; mat[0].z += a[0].z; mat[0].w += a[0].w;
	mat[1].x += a[1].x; mat[1].y += a[1].y; mat[1].z += a[1].z; mat[1].w += a[1].w;
	mat[2].x += a[2].x; mat[2].y += a[2].y; mat[2].z += a[2].z; mat[2].w += a[2].w;
	mat[3].x += a[3].x; mat[3].y += a[3].y; mat[3].z += a[3].z; mat[3].w += a[3].w;
    return *this;
}

SGF_INLINE_FORCED CMatriz4D &CMatriz4D::operator-=( const CMatriz4D &a ) {
	mat[0].x -= a[0].x; mat[0].y -= a[0].y; mat[0].z -= a[0].z; mat[0].w -= a[0].w;
	mat[1].x -= a[1].x; mat[1].y -= a[1].y; mat[1].z -= a[1].z; mat[1].w -= a[1].w;
	mat[2].x -= a[2].x; mat[2].y -= a[2].y; mat[2].z -= a[2].z; mat[2].w -= a[2].w;
	mat[3].x -= a[3].x; mat[3].y -= a[3].y; mat[3].z -= a[3].z; mat[3].w -= a[3].w;
    return *this;
}

SGF_INLINE_FORCED CMatriz4D operator*( const float a, const CMatriz4D &mat ) {
	return mat * a;
}

SGF_INLINE_FORCED CVector4D operator*( const CVector4D &vec, const CMatriz4D &mat ) {
	return mat * vec;
}

SGF_INLINE_FORCED CVector3D operator*( const CVector3D &vec, const CMatriz4D &mat ) {
	return mat * vec;
}

SGF_INLINE_FORCED CVector4D &operator*=( CVector4D &vec, const CMatriz4D &mat ) {
	vec = mat * vec;
	return vec;
}

SGF_INLINE_FORCED CVector3D &operator*=( CVector3D &vec, const CMatriz4D &mat ) {
	vec = mat * vec;
	return vec;
}

SGF_INLINE_FORCED bool CMatriz4D::Compare( const CMatriz4D &a ) const {
	SGF_Dword i;
	const float *ptr1, *ptr2;

	ptr1 = reinterpret_cast<const float *>(mat);
	ptr2 = reinterpret_cast<const float *>(a.mat);
	for ( i = 0; i < 4*4; i++ ) {
		if ( ptr1[i] != ptr2[i] ) {
			return false;
		}
	}
	return true;
}

SGF_INLINE_FORCED bool CMatriz4D::Compare( const CMatriz4D &a, const float epsilon ) const {
	SGF_Dword i;
	const float *ptr1, *ptr2;

	ptr1 = reinterpret_cast<const float *>(mat);
	ptr2 = reinterpret_cast<const float *>(a.mat);
	for ( i = 0; i < 4*4; i++ ) {
		if ( CMath::Fabs( ptr1[i] - ptr2[i] ) > epsilon ) {
			return false;
		}
	}
	return true;
}

SGF_INLINE_FORCED bool CMatriz4D::operator==( const CMatriz4D &a ) const {
	return Compare( a );
}

SGF_INLINE_FORCED bool CMatriz4D::operator!=( const CMatriz4D &a ) const {
	return !Compare( a );
}

SGF_INLINE_FORCED void CMatriz4D::Zero() {
	memset( mat, 0, sizeof( CMatriz4D ) );
}

SGF_INLINE_FORCED void CMatriz4D::Identity() {
	*this = mat4_identity;
}

SGF_INLINE_FORCED bool CMatriz4D::IsIdentity( const float epsilon ) const {
	return Compare( mat4_identity, epsilon );
}

SGF_INLINE_FORCED bool CMatriz4D::IsSymmetric( const float epsilon ) const {
	for ( int i = 1; i < 4; i++ ) {
		for ( int j = 0; j < i; j++ ) {
			if ( CMath::Fabs( mat[i][j] - mat[j][i] ) > epsilon ) {
				return false;
			}
		}
	}
	return true;
}

SGF_INLINE_FORCED bool CMatriz4D::IsDiagonal( const float epsilon ) const {
	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			if ( i != j && CMath::Fabs( mat[i][j] ) > epsilon ) {
				return false;
			}
		}
	}
	return true;
}

SGF_INLINE_FORCED bool CMatriz4D::IsRotated() const {
	if ( !mat[ 0 ][ 1 ] && !mat[ 0 ][ 2 ] &&
		!mat[ 1 ][ 0 ] && !mat[ 1 ][ 2 ] &&
		!mat[ 2 ][ 0 ] && !mat[ 2 ][ 1 ] ) {
		return false;
	}
	return true;
}

SGF_INLINE_FORCED void CMatriz4D::ProjectVector( const CVector4D &src, CVector4D &dst ) const {
	dst.x = src * mat[ 0 ];
	dst.y = src * mat[ 1 ];
	dst.z = src * mat[ 2 ];
	dst.w = src * mat[ 3 ];
}

SGF_INLINE_FORCED void CMatriz4D::UnprojectVector( const CVector4D &src, CVector4D &dst ) const {
	dst = mat[ 0 ] * src.x + mat[ 1 ] * src.y + mat[ 2 ] * src.z + mat[ 3 ] * src.w;
}

SGF_INLINE_FORCED float CMatriz4D::Trace() const {
	return ( mat[0][0] + mat[1][1] + mat[2][2] + mat[3][3] );
}

SGF_INLINE_FORCED CMatriz4D CMatriz4D::Inverse() const {
	CMatriz4D invMat;

	invMat = *this;
	int r = invMat.InverseSelf();
	assert( r );
	return invMat;
}

SGF_INLINE_FORCED CMatriz4D CMatriz4D::InverseFast() const {
	CMatriz4D invMat;

	invMat = *this;
	int r = invMat.InverseFastSelf();
	assert( r );
	return invMat;
}

SGF_INLINE_FORCED CMatriz4D CMatriz3D::ToMat4() const {
	// NOTE: CMatriz3D is transposed because it is column-major
	return CMatriz4D(	mat[0][0],	mat[1][0],	mat[2][0],	0.0f,
					mat[0][1],	mat[1][1],	mat[2][1],	0.0f,
					mat[0][2],	mat[1][2],	mat[2][2],	0.0f,
					0.0f,		0.0f,		0.0f,		1.0f );
}

SGF_INLINE_FORCED int CMatriz4D::GetDimension() const {
	return 16;
}

SGF_INLINE_FORCED const float *CMatriz4D::ToFloatPtr() const {
	return mat[0].ToFloatPtr();
}

SGF_INLINE_FORCED float *CMatriz4D::ToFloatPtr() {
	return mat[0].ToFloatPtr();
}


//===============================================================
//
//	CMatriz5D - 5x5 matrix
//
//===============================================================

class CMatriz5D {
public:
					CMatriz5D();
					explicit CMatriz5D( const CVector5D &v0, const CVector5D &v1, const CVector5D &v2, const CVector5D &v3, const CVector5D &v4 );
					explicit CMatriz5D( const float src[ 5 ][ 5 ] );

	const CVector5D &	operator[]( int index ) const;
	CVector5D &		operator[]( int index );
	CMatriz5D			operator*( const float a ) const;
	CVector5D			operator*( const CVector5D &vec ) const;
	CMatriz5D			operator*( const CMatriz5D &a ) const;
	CMatriz5D			operator+( const CMatriz5D &a ) const;
	CMatriz5D			operator-( const CMatriz5D &a ) const;
	CMatriz5D &		operator*=( const float a );
	CMatriz5D &		operator*=( const CMatriz5D &a );
	CMatriz5D &		operator+=( const CMatriz5D &a );
	CMatriz5D &		operator-=( const CMatriz5D &a );

	friend CMatriz5D	operator*( const float a, const CMatriz5D &mat );
	friend CVector5D	operator*( const CVector5D &vec, const CMatriz5D &mat );
	friend CVector5D &	operator*=( CVector5D &vec, const CMatriz5D &mat );

	bool			Compare( const CMatriz5D &a ) const;						// exact compare, no epsilon
	bool			Compare( const CMatriz5D &a, const float epsilon ) const;	// compare with epsilon
	bool			operator==( const CMatriz5D &a ) const;					// exact compare, no epsilon
	bool			operator!=( const CMatriz5D &a ) const;					// exact compare, no epsilon

	void			Zero();
	void			Identity();
	bool			IsIdentity( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsSymmetric( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsDiagonal( const float epsilon = MATRIX_EPSILON ) const;

	float			Trace() const;
	float			Determinant() const;
	CMatriz5D			Transpose() const;	// returns transpose
	CMatriz5D &		TransposeSelf();
	CMatriz5D			Inverse() const;		// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseSelf();		// returns false if determinant is zero
	CMatriz5D			InverseFast() const;	// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseFastSelf();	// returns false if determinant is zero

	int				GetDimension() const;

	const float *	ToFloatPtr() const;
	float *			ToFloatPtr();
	const char *	ToString( int precision = 2 ) const;

private:
	CVector5D			mat[ 5 ];
};

extern CMatriz5D mat5_zero;
extern CMatriz5D mat5_identity;
#define mat5_default	mat5_identity

SGF_INLINE_FORCED CMatriz5D::CMatriz5D() {
}

SGF_INLINE_FORCED CMatriz5D::CMatriz5D( const float src[ 5 ][ 5 ] ) {
	memcpy( mat, src, 5 * 5 * sizeof( float ) );
}

SGF_INLINE_FORCED CMatriz5D::CMatriz5D( const CVector5D &v0, const CVector5D &v1, const CVector5D &v2, const CVector5D &v3, const CVector5D &v4 ) {
	mat[0] = v0;
	mat[1] = v1;
	mat[2] = v2;
	mat[3] = v3;
	mat[4] = v4;
}

SGF_INLINE_FORCED const CVector5D &CMatriz5D::operator[]( int index ) const {
	//assert( ( index >= 0 ) && ( index < 5 ) );
	return mat[ index ];
}

SGF_INLINE_FORCED CVector5D &CMatriz5D::operator[]( int index ) {
	//assert( ( index >= 0 ) && ( index < 5 ) );
	return mat[ index ];
}

SGF_INLINE_FORCED CMatriz5D CMatriz5D::operator*( const CMatriz5D &a ) const {
	int i, j;
	const float *m1Ptr, *m2Ptr;
	float *dstPtr;
	CMatriz5D dst;

	m1Ptr = reinterpret_cast<const float *>(this);
	m2Ptr = reinterpret_cast<const float *>(&a);
	dstPtr = reinterpret_cast<float *>(&dst);

	for ( i = 0; i < 5; i++ ) {
		for ( j = 0; j < 5; j++ ) {
			*dstPtr = m1Ptr[0] * m2Ptr[ 0 * 5 + j ]
					+ m1Ptr[1] * m2Ptr[ 1 * 5 + j ]
					+ m1Ptr[2] * m2Ptr[ 2 * 5 + j ]
					+ m1Ptr[3] * m2Ptr[ 3 * 5 + j ]
					+ m1Ptr[4] * m2Ptr[ 4 * 5 + j ];
			dstPtr++;
		}
		m1Ptr += 5;
	}
	return dst;
}

SGF_INLINE_FORCED CMatriz5D CMatriz5D::operator*( const float a ) const {
	return CMatriz5D(
		CVector5D( mat[0][0] * a, mat[0][1] * a, mat[0][2] * a, mat[0][3] * a, mat[0][4] * a ),
		CVector5D( mat[1][0] * a, mat[1][1] * a, mat[1][2] * a, mat[1][3] * a, mat[1][4] * a ),
		CVector5D( mat[2][0] * a, mat[2][1] * a, mat[2][2] * a, mat[2][3] * a, mat[2][4] * a ),
		CVector5D( mat[3][0] * a, mat[3][1] * a, mat[3][2] * a, mat[3][3] * a, mat[3][4] * a ),
		CVector5D( mat[4][0] * a, mat[4][1] * a, mat[4][2] * a, mat[4][3] * a, mat[4][4] * a ) );
}

SGF_INLINE_FORCED CVector5D CMatriz5D::operator*( const CVector5D &vec ) const {
	return CVector5D(
		mat[0][0] * vec[0] + mat[0][1] * vec[1] + mat[0][2] * vec[2] + mat[0][3] * vec[3] + mat[0][4] * vec[4],
		mat[1][0] * vec[0] + mat[1][1] * vec[1] + mat[1][2] * vec[2] + mat[1][3] * vec[3] + mat[1][4] * vec[4],
		mat[2][0] * vec[0] + mat[2][1] * vec[1] + mat[2][2] * vec[2] + mat[2][3] * vec[3] + mat[2][4] * vec[4],
		mat[3][0] * vec[0] + mat[3][1] * vec[1] + mat[3][2] * vec[2] + mat[3][3] * vec[3] + mat[3][4] * vec[4],
		mat[4][0] * vec[0] + mat[4][1] * vec[1] + mat[4][2] * vec[2] + mat[4][3] * vec[3] + mat[4][4] * vec[4] );
}

SGF_INLINE_FORCED CMatriz5D CMatriz5D::operator+( const CMatriz5D &a ) const {
	return CMatriz5D(
		CVector5D( mat[0][0] + a[0][0], mat[0][1] + a[0][1], mat[0][2] + a[0][2], mat[0][3] + a[0][3], mat[0][4] + a[0][4] ),
		CVector5D( mat[1][0] + a[1][0], mat[1][1] + a[1][1], mat[1][2] + a[1][2], mat[1][3] + a[1][3], mat[1][4] + a[1][4] ),
		CVector5D( mat[2][0] + a[2][0], mat[2][1] + a[2][1], mat[2][2] + a[2][2], mat[2][3] + a[2][3], mat[2][4] + a[2][4] ),
		CVector5D( mat[3][0] + a[3][0], mat[3][1] + a[3][1], mat[3][2] + a[3][2], mat[3][3] + a[3][3], mat[3][4] + a[3][4] ),
		CVector5D( mat[4][0] + a[4][0], mat[4][1] + a[4][1], mat[4][2] + a[4][2], mat[4][3] + a[4][3], mat[4][4] + a[4][4] ) );
}

SGF_INLINE_FORCED CMatriz5D CMatriz5D::operator-( const CMatriz5D &a ) const {
	return CMatriz5D(
		CVector5D( mat[0][0] - a[0][0], mat[0][1] - a[0][1], mat[0][2] - a[0][2], mat[0][3] - a[0][3], mat[0][4] - a[0][4] ),
		CVector5D( mat[1][0] - a[1][0], mat[1][1] - a[1][1], mat[1][2] - a[1][2], mat[1][3] - a[1][3], mat[1][4] - a[1][4] ),
		CVector5D( mat[2][0] - a[2][0], mat[2][1] - a[2][1], mat[2][2] - a[2][2], mat[2][3] - a[2][3], mat[2][4] - a[2][4] ),
		CVector5D( mat[3][0] - a[3][0], mat[3][1] - a[3][1], mat[3][2] - a[3][2], mat[3][3] - a[3][3], mat[3][4] - a[3][4] ),
		CVector5D( mat[4][0] - a[4][0], mat[4][1] - a[4][1], mat[4][2] - a[4][2], mat[4][3] - a[4][3], mat[4][4] - a[4][4] ) );
}

SGF_INLINE_FORCED CMatriz5D &CMatriz5D::operator*=( const float a ) {
	mat[0][0] *= a; mat[0][1] *= a; mat[0][2] *= a; mat[0][3] *= a; mat[0][4] *= a;
	mat[1][0] *= a; mat[1][1] *= a; mat[1][2] *= a; mat[1][3] *= a; mat[1][4] *= a;
	mat[2][0] *= a; mat[2][1] *= a; mat[2][2] *= a; mat[2][3] *= a; mat[2][4] *= a;
	mat[3][0] *= a; mat[3][1] *= a; mat[3][2] *= a; mat[3][3] *= a; mat[3][4] *= a;
	mat[4][0] *= a; mat[4][1] *= a; mat[4][2] *= a; mat[4][3] *= a; mat[4][4] *= a;
	return *this;
}

SGF_INLINE_FORCED CMatriz5D &CMatriz5D::operator*=( const CMatriz5D &a ) {
	*this = *this * a;
	return *this;
}

SGF_INLINE_FORCED CMatriz5D &CMatriz5D::operator+=( const CMatriz5D &a ) {
	mat[0][0] += a[0][0]; mat[0][1] += a[0][1]; mat[0][2] += a[0][2]; mat[0][3] += a[0][3]; mat[0][4] += a[0][4];
	mat[1][0] += a[1][0]; mat[1][1] += a[1][1]; mat[1][2] += a[1][2]; mat[1][3] += a[1][3]; mat[1][4] += a[1][4];
	mat[2][0] += a[2][0]; mat[2][1] += a[2][1]; mat[2][2] += a[2][2]; mat[2][3] += a[2][3]; mat[2][4] += a[2][4];
	mat[3][0] += a[3][0]; mat[3][1] += a[3][1]; mat[3][2] += a[3][2]; mat[3][3] += a[3][3]; mat[3][4] += a[3][4];
	mat[4][0] += a[4][0]; mat[4][1] += a[4][1]; mat[4][2] += a[4][2]; mat[4][3] += a[4][3]; mat[4][4] += a[4][4];
	return *this;
}

SGF_INLINE_FORCED CMatriz5D &CMatriz5D::operator-=( const CMatriz5D &a ) {
	mat[0][0] -= a[0][0]; mat[0][1] -= a[0][1]; mat[0][2] -= a[0][2]; mat[0][3] -= a[0][3]; mat[0][4] -= a[0][4];
	mat[1][0] -= a[1][0]; mat[1][1] -= a[1][1]; mat[1][2] -= a[1][2]; mat[1][3] -= a[1][3]; mat[1][4] -= a[1][4];
	mat[2][0] -= a[2][0]; mat[2][1] -= a[2][1]; mat[2][2] -= a[2][2]; mat[2][3] -= a[2][3]; mat[2][4] -= a[2][4];
	mat[3][0] -= a[3][0]; mat[3][1] -= a[3][1]; mat[3][2] -= a[3][2]; mat[3][3] -= a[3][3]; mat[3][4] -= a[3][4];
	mat[4][0] -= a[4][0]; mat[4][1] -= a[4][1]; mat[4][2] -= a[4][2]; mat[4][3] -= a[4][3]; mat[4][4] -= a[4][4];
	return *this;
}

SGF_INLINE_FORCED CVector5D operator*( const CVector5D &vec, const CMatriz5D &mat ) {
	return mat * vec;
}

SGF_INLINE_FORCED CMatriz5D operator*( const float a, CMatriz5D const &mat ) {
	return mat * a;
}

SGF_INLINE_FORCED CVector5D &operator*=( CVector5D &vec, const CMatriz5D &mat ) {
	vec = mat * vec;
	return vec;
}

SGF_INLINE_FORCED bool CMatriz5D::Compare( const CMatriz5D &a ) const {
	SGF_Dword i;
	const float *ptr1, *ptr2;

	ptr1 = reinterpret_cast<const float *>(mat);
	ptr2 = reinterpret_cast<const float *>(a.mat);
	for ( i = 0; i < 5*5; i++ ) {
		if ( ptr1[i] != ptr2[i] ) {
			return false;
		}
	}
	return true;
}

SGF_INLINE_FORCED bool CMatriz5D::Compare( const CMatriz5D &a, const float epsilon ) const {
	SGF_Dword i;
	const float *ptr1, *ptr2;

	ptr1 = reinterpret_cast<const float *>(mat);
	ptr2 = reinterpret_cast<const float *>(a.mat);
	for ( i = 0; i < 5*5; i++ ) {
		if ( CMath::Fabs( ptr1[i] - ptr2[i] ) > epsilon ) {
			return false;
		}
	}
	return true;
}

SGF_INLINE_FORCED bool CMatriz5D::operator==( const CMatriz5D &a ) const {
	return Compare( a );
}

SGF_INLINE_FORCED bool CMatriz5D::operator!=( const CMatriz5D &a ) const {
	return !Compare( a );
}

SGF_INLINE_FORCED void CMatriz5D::Zero() {
	memset( mat, 0, sizeof( CMatriz5D ) );
}

SGF_INLINE_FORCED void CMatriz5D::Identity() {
	*this = mat5_identity;
}

SGF_INLINE_FORCED bool CMatriz5D::IsIdentity( const float epsilon ) const {
	return Compare( mat5_identity, epsilon );
}

SGF_INLINE_FORCED bool CMatriz5D::IsSymmetric( const float epsilon ) const {
	for ( int i = 1; i < 5; i++ ) {
		for ( int j = 0; j < i; j++ ) {
			if ( CMath::Fabs( mat[i][j] - mat[j][i] ) > epsilon ) {
				return false;
			}
		}
	}
	return true;
}

SGF_INLINE_FORCED bool CMatriz5D::IsDiagonal( const float epsilon ) const {
	for ( int i = 0; i < 5; i++ ) {
		for ( int j = 0; j < 5; j++ ) {
			if ( i != j && CMath::Fabs( mat[i][j] ) > epsilon ) {
				return false;
			}
		}
	}
	return true;
}

SGF_INLINE_FORCED float CMatriz5D::Trace() const {
	return ( mat[0][0] + mat[1][1] + mat[2][2] + mat[3][3] + mat[4][4] );
}

SGF_INLINE_FORCED CMatriz5D CMatriz5D::Inverse() const {
	CMatriz5D invMat;

	invMat = *this;
	int r = invMat.InverseSelf();
	assert( r );
	return invMat;
}

SGF_INLINE_FORCED CMatriz5D CMatriz5D::InverseFast() const {
	CMatriz5D invMat;

	invMat = *this;
	int r = invMat.InverseFastSelf();
	assert( r );
	return invMat;
}

SGF_INLINE_FORCED int CMatriz5D::GetDimension() const {
	return 25;
}

SGF_INLINE_FORCED const float *CMatriz5D::ToFloatPtr() const {
	return mat[0].ToFloatPtr();
}

SGF_INLINE_FORCED float *CMatriz5D::ToFloatPtr() {
	return mat[0].ToFloatPtr();
}


//===============================================================
//
//	CMatriz6D - 6x6 matrix
//
//===============================================================

class CMatriz6D {
public:
					CMatriz6D();
					explicit CMatriz6D( const CVector6D &v0, const CVector6D &v1, const CVector6D &v2, const CVector6D &v3, const CVector6D &v4, const CVector6D &v5 );
					explicit CMatriz6D( const CMatriz3D &m0, const CMatriz3D &m1, const CMatriz3D &m2, const CMatriz3D &m3 );
					explicit CMatriz6D( const float src[ 6 ][ 6 ] );

	const CVector6D &	operator[]( int index ) const;
	CVector6D &		operator[]( int index );
	CMatriz6D			operator*( const float a ) const;
	CVector6D			operator*( const CVector6D &vec ) const;
	CMatriz6D			operator*( const CMatriz6D &a ) const;
	CMatriz6D			operator+( const CMatriz6D &a ) const;
	CMatriz6D			operator-( const CMatriz6D &a ) const;
	CMatriz6D &		operator*=( const float a );
	CMatriz6D &		operator*=( const CMatriz6D &a );
	CMatriz6D &		operator+=( const CMatriz6D &a );
	CMatriz6D &		operator-=( const CMatriz6D &a );

	friend CMatriz6D	operator*( const float a, const CMatriz6D &mat );
	friend CVector6D	operator*( const CVector6D &vec, const CMatriz6D &mat );
	friend CVector6D &	operator*=( CVector6D &vec, const CMatriz6D &mat );

	bool			Compare( const CMatriz6D &a ) const;						// exact compare, no epsilon
	bool			Compare( const CMatriz6D &a, const float epsilon ) const;	// compare with epsilon
	bool			operator==( const CMatriz6D &a ) const;					// exact compare, no epsilon
	bool			operator!=( const CMatriz6D &a ) const;					// exact compare, no epsilon

	void			Zero();
	void			Identity();
	bool			IsIdentity( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsSymmetric( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsDiagonal( const float epsilon = MATRIX_EPSILON ) const;

	CMatriz3D			SubMat3( int n ) const;
	float			Trace() const;
	float			Determinant() const;
	CMatriz6D			Transpose() const;	// returns transpose
	CMatriz6D &		TransposeSelf();
	CMatriz6D			Inverse() const;		// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseSelf();		// returns false if determinant is zero
	CMatriz6D			InverseFast() const;	// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseFastSelf();	// returns false if determinant is zero

	int				GetDimension() const;

	const float *	ToFloatPtr() const;
	float *			ToFloatPtr();
	const char *	ToString( int precision = 2 ) const;

private:
	CVector6D			mat[ 6 ];
};

extern CMatriz6D mat6_zero;
extern CMatriz6D mat6_identity;
#define mat6_default	mat6_identity

SGF_INLINE_FORCED CMatriz6D::CMatriz6D() {
}

SGF_INLINE_FORCED CMatriz6D::CMatriz6D( const CMatriz3D &m0, const CMatriz3D &m1, const CMatriz3D &m2, const CMatriz3D &m3 ) {
	mat[0] = CVector6D( m0[0][0], m0[0][1], m0[0][2], m1[0][0], m1[0][1], m1[0][2] );
	mat[1] = CVector6D( m0[1][0], m0[1][1], m0[1][2], m1[1][0], m1[1][1], m1[1][2] );
	mat[2] = CVector6D( m0[2][0], m0[2][1], m0[2][2], m1[2][0], m1[2][1], m1[2][2] );
	mat[3] = CVector6D( m2[0][0], m2[0][1], m2[0][2], m3[0][0], m3[0][1], m3[0][2] );
	mat[4] = CVector6D( m2[1][0], m2[1][1], m2[1][2], m3[1][0], m3[1][1], m3[1][2] );
	mat[5] = CVector6D( m2[2][0], m2[2][1], m2[2][2], m3[2][0], m3[2][1], m3[2][2] );
}

SGF_INLINE_FORCED CMatriz6D::CMatriz6D( const CVector6D &v0, const CVector6D &v1, const CVector6D &v2, const CVector6D &v3, const CVector6D &v4, const CVector6D &v5 ) {
	mat[0] = v0;
	mat[1] = v1;
	mat[2] = v2;
	mat[3] = v3;
	mat[4] = v4;
	mat[5] = v5;
}

SGF_INLINE_FORCED CMatriz6D::CMatriz6D( const float src[ 6 ][ 6 ] ) {
	memcpy( mat, src, 6 * 6 * sizeof( float ) );
}

SGF_INLINE_FORCED const CVector6D &CMatriz6D::operator[]( int index ) const {
	//assert( ( index >= 0 ) && ( index < 6 ) );
	return mat[ index ];
}

SGF_INLINE_FORCED CVector6D &CMatriz6D::operator[]( int index ) {
	//assert( ( index >= 0 ) && ( index < 6 ) );
	return mat[ index ];
}

SGF_INLINE_FORCED CMatriz6D CMatriz6D::operator*( const CMatriz6D &a ) const {
	int i, j;
	const float *m1Ptr, *m2Ptr;
	float *dstPtr;
	CMatriz6D dst;

	m1Ptr = reinterpret_cast<const float *>(this);
	m2Ptr = reinterpret_cast<const float *>(&a);
	dstPtr = reinterpret_cast<float *>(&dst);

	for ( i = 0; i < 6; i++ ) {
		for ( j = 0; j < 6; j++ ) {
			*dstPtr = m1Ptr[0] * m2Ptr[ 0 * 6 + j ]
					+ m1Ptr[1] * m2Ptr[ 1 * 6 + j ]
					+ m1Ptr[2] * m2Ptr[ 2 * 6 + j ]
					+ m1Ptr[3] * m2Ptr[ 3 * 6 + j ]
					+ m1Ptr[4] * m2Ptr[ 4 * 6 + j ]
					+ m1Ptr[5] * m2Ptr[ 5 * 6 + j ];
			dstPtr++;
		}
		m1Ptr += 6;
	}
	return dst;
}

SGF_INLINE_FORCED CMatriz6D CMatriz6D::operator*( const float a ) const {
	return CMatriz6D(
		CVector6D( mat[0][0] * a, mat[0][1] * a, mat[0][2] * a, mat[0][3] * a, mat[0][4] * a, mat[0][5] * a ),
		CVector6D( mat[1][0] * a, mat[1][1] * a, mat[1][2] * a, mat[1][3] * a, mat[1][4] * a, mat[1][5] * a ),
		CVector6D( mat[2][0] * a, mat[2][1] * a, mat[2][2] * a, mat[2][3] * a, mat[2][4] * a, mat[2][5] * a ),
		CVector6D( mat[3][0] * a, mat[3][1] * a, mat[3][2] * a, mat[3][3] * a, mat[3][4] * a, mat[3][5] * a ),
		CVector6D( mat[4][0] * a, mat[4][1] * a, mat[4][2] * a, mat[4][3] * a, mat[4][4] * a, mat[4][5] * a ),
		CVector6D( mat[5][0] * a, mat[5][1] * a, mat[5][2] * a, mat[5][3] * a, mat[5][4] * a, mat[5][5] * a ) );
}

SGF_INLINE_FORCED CVector6D CMatriz6D::operator*( const CVector6D &vec ) const {
	return CVector6D(
		mat[0][0] * vec[0] + mat[0][1] * vec[1] + mat[0][2] * vec[2] + mat[0][3] * vec[3] + mat[0][4] * vec[4] + mat[0][5] * vec[5],
		mat[1][0] * vec[0] + mat[1][1] * vec[1] + mat[1][2] * vec[2] + mat[1][3] * vec[3] + mat[1][4] * vec[4] + mat[1][5] * vec[5],
		mat[2][0] * vec[0] + mat[2][1] * vec[1] + mat[2][2] * vec[2] + mat[2][3] * vec[3] + mat[2][4] * vec[4] + mat[2][5] * vec[5],
		mat[3][0] * vec[0] + mat[3][1] * vec[1] + mat[3][2] * vec[2] + mat[3][3] * vec[3] + mat[3][4] * vec[4] + mat[3][5] * vec[5],
		mat[4][0] * vec[0] + mat[4][1] * vec[1] + mat[4][2] * vec[2] + mat[4][3] * vec[3] + mat[4][4] * vec[4] + mat[4][5] * vec[5],
		mat[5][0] * vec[0] + mat[5][1] * vec[1] + mat[5][2] * vec[2] + mat[5][3] * vec[3] + mat[5][4] * vec[4] + mat[5][5] * vec[5] );
}

SGF_INLINE_FORCED CMatriz6D CMatriz6D::operator+( const CMatriz6D &a ) const {
	return CMatriz6D(
		CVector6D( mat[0][0] + a[0][0], mat[0][1] + a[0][1], mat[0][2] + a[0][2], mat[0][3] + a[0][3], mat[0][4] + a[0][4], mat[0][5] + a[0][5] ),
		CVector6D( mat[1][0] + a[1][0], mat[1][1] + a[1][1], mat[1][2] + a[1][2], mat[1][3] + a[1][3], mat[1][4] + a[1][4], mat[1][5] + a[1][5] ),
		CVector6D( mat[2][0] + a[2][0], mat[2][1] + a[2][1], mat[2][2] + a[2][2], mat[2][3] + a[2][3], mat[2][4] + a[2][4], mat[2][5] + a[2][5] ),
		CVector6D( mat[3][0] + a[3][0], mat[3][1] + a[3][1], mat[3][2] + a[3][2], mat[3][3] + a[3][3], mat[3][4] + a[3][4], mat[3][5] + a[3][5] ),
		CVector6D( mat[4][0] + a[4][0], mat[4][1] + a[4][1], mat[4][2] + a[4][2], mat[4][3] + a[4][3], mat[4][4] + a[4][4], mat[4][5] + a[4][5] ),
		CVector6D( mat[5][0] + a[5][0], mat[5][1] + a[5][1], mat[5][2] + a[5][2], mat[5][3] + a[5][3], mat[5][4] + a[5][4], mat[5][5] + a[5][5] ) );
}

SGF_INLINE_FORCED CMatriz6D CMatriz6D::operator-( const CMatriz6D &a ) const {
	return CMatriz6D(
		CVector6D( mat[0][0] - a[0][0], mat[0][1] - a[0][1], mat[0][2] - a[0][2], mat[0][3] - a[0][3], mat[0][4] - a[0][4], mat[0][5] - a[0][5] ),
		CVector6D( mat[1][0] - a[1][0], mat[1][1] - a[1][1], mat[1][2] - a[1][2], mat[1][3] - a[1][3], mat[1][4] - a[1][4], mat[1][5] - a[1][5] ),
		CVector6D( mat[2][0] - a[2][0], mat[2][1] - a[2][1], mat[2][2] - a[2][2], mat[2][3] - a[2][3], mat[2][4] - a[2][4], mat[2][5] - a[2][5] ),
		CVector6D( mat[3][0] - a[3][0], mat[3][1] - a[3][1], mat[3][2] - a[3][2], mat[3][3] - a[3][3], mat[3][4] - a[3][4], mat[3][5] - a[3][5] ),
		CVector6D( mat[4][0] - a[4][0], mat[4][1] - a[4][1], mat[4][2] - a[4][2], mat[4][3] - a[4][3], mat[4][4] - a[4][4], mat[4][5] - a[4][5] ),
		CVector6D( mat[5][0] - a[5][0], mat[5][1] - a[5][1], mat[5][2] - a[5][2], mat[5][3] - a[5][3], mat[5][4] - a[5][4], mat[5][5] - a[5][5] ) );
}

SGF_INLINE_FORCED CMatriz6D &CMatriz6D::operator*=( const float a ) {
	mat[0][0] *= a; mat[0][1] *= a; mat[0][2] *= a; mat[0][3] *= a; mat[0][4] *= a; mat[0][5] *= a;
	mat[1][0] *= a; mat[1][1] *= a; mat[1][2] *= a; mat[1][3] *= a; mat[1][4] *= a; mat[1][5] *= a;
	mat[2][0] *= a; mat[2][1] *= a; mat[2][2] *= a; mat[2][3] *= a; mat[2][4] *= a; mat[2][5] *= a;
	mat[3][0] *= a; mat[3][1] *= a; mat[3][2] *= a; mat[3][3] *= a; mat[3][4] *= a; mat[3][5] *= a;
	mat[4][0] *= a; mat[4][1] *= a; mat[4][2] *= a; mat[4][3] *= a; mat[4][4] *= a; mat[4][5] *= a;
	mat[5][0] *= a; mat[5][1] *= a; mat[5][2] *= a; mat[5][3] *= a; mat[5][4] *= a; mat[5][5] *= a;
	return *this;
}

SGF_INLINE_FORCED CMatriz6D &CMatriz6D::operator*=( const CMatriz6D &a ) {
	*this = *this * a;
	return *this;
}

SGF_INLINE_FORCED CMatriz6D &CMatriz6D::operator+=( const CMatriz6D &a ) {
	mat[0][0] += a[0][0]; mat[0][1] += a[0][1]; mat[0][2] += a[0][2]; mat[0][3] += a[0][3]; mat[0][4] += a[0][4]; mat[0][5] += a[0][5];
	mat[1][0] += a[1][0]; mat[1][1] += a[1][1]; mat[1][2] += a[1][2]; mat[1][3] += a[1][3]; mat[1][4] += a[1][4]; mat[1][5] += a[1][5];
	mat[2][0] += a[2][0]; mat[2][1] += a[2][1]; mat[2][2] += a[2][2]; mat[2][3] += a[2][3]; mat[2][4] += a[2][4]; mat[2][5] += a[2][5];
	mat[3][0] += a[3][0]; mat[3][1] += a[3][1]; mat[3][2] += a[3][2]; mat[3][3] += a[3][3]; mat[3][4] += a[3][4]; mat[3][5] += a[3][5];
	mat[4][0] += a[4][0]; mat[4][1] += a[4][1]; mat[4][2] += a[4][2]; mat[4][3] += a[4][3]; mat[4][4] += a[4][4]; mat[4][5] += a[4][5];
	mat[5][0] += a[5][0]; mat[5][1] += a[5][1]; mat[5][2] += a[5][2]; mat[5][3] += a[5][3]; mat[5][4] += a[5][4]; mat[5][5] += a[5][5];
	return *this;
}

SGF_INLINE_FORCED CMatriz6D &CMatriz6D::operator-=( const CMatriz6D &a ) {
	mat[0][0] -= a[0][0]; mat[0][1] -= a[0][1]; mat[0][2] -= a[0][2]; mat[0][3] -= a[0][3]; mat[0][4] -= a[0][4]; mat[0][5] -= a[0][5];
	mat[1][0] -= a[1][0]; mat[1][1] -= a[1][1]; mat[1][2] -= a[1][2]; mat[1][3] -= a[1][3]; mat[1][4] -= a[1][4]; mat[1][5] -= a[1][5];
	mat[2][0] -= a[2][0]; mat[2][1] -= a[2][1]; mat[2][2] -= a[2][2]; mat[2][3] -= a[2][3]; mat[2][4] -= a[2][4]; mat[2][5] -= a[2][5];
	mat[3][0] -= a[3][0]; mat[3][1] -= a[3][1]; mat[3][2] -= a[3][2]; mat[3][3] -= a[3][3]; mat[3][4] -= a[3][4]; mat[3][5] -= a[3][5];
	mat[4][0] -= a[4][0]; mat[4][1] -= a[4][1]; mat[4][2] -= a[4][2]; mat[4][3] -= a[4][3]; mat[4][4] -= a[4][4]; mat[4][5] -= a[4][5];
	mat[5][0] -= a[5][0]; mat[5][1] -= a[5][1]; mat[5][2] -= a[5][2]; mat[5][3] -= a[5][3]; mat[5][4] -= a[5][4]; mat[5][5] -= a[5][5];
	return *this;
}

SGF_INLINE_FORCED CVector6D operator*( const CVector6D &vec, const CMatriz6D &mat ) {
	return mat * vec;
}

SGF_INLINE_FORCED CMatriz6D operator*( const float a, CMatriz6D const &mat ) {
	return mat * a;
}

SGF_INLINE_FORCED CVector6D &operator*=( CVector6D &vec, const CMatriz6D &mat ) {
	vec = mat * vec;
	return vec;
}

SGF_INLINE_FORCED bool CMatriz6D::Compare( const CMatriz6D &a ) const {
	SGF_Dword i;
	const float *ptr1, *ptr2;

	ptr1 = reinterpret_cast<const float *>(mat);
	ptr2 = reinterpret_cast<const float *>(a.mat);
	for ( i = 0; i < 6*6; i++ ) {
		if ( ptr1[i] != ptr2[i] ) {
			return false;
		}
	}
	return true;
}

SGF_INLINE_FORCED bool CMatriz6D::Compare( const CMatriz6D &a, const float epsilon ) const {
	SGF_Dword i;
	const float *ptr1, *ptr2;

	ptr1 = reinterpret_cast<const float *>(mat);
	ptr2 = reinterpret_cast<const float *>(a.mat);
	for ( i = 0; i < 6*6; i++ ) {
		if ( CMath::Fabs( ptr1[i] - ptr2[i] ) > epsilon ) {
			return false;
		}
	}
	return true;
}

SGF_INLINE_FORCED bool CMatriz6D::operator==( const CMatriz6D &a ) const {
	return Compare( a );
}

SGF_INLINE_FORCED bool CMatriz6D::operator!=( const CMatriz6D &a ) const {
	return !Compare( a );
}

SGF_INLINE_FORCED void CMatriz6D::Zero() {
	memset( mat, 0, sizeof( CMatriz6D ) );
}

SGF_INLINE_FORCED void CMatriz6D::Identity() {
	*this = mat6_identity;
}

SGF_INLINE_FORCED bool CMatriz6D::IsIdentity( const float epsilon ) const {
	return Compare( mat6_identity, epsilon );
}

SGF_INLINE_FORCED bool CMatriz6D::IsSymmetric( const float epsilon ) const {
	for ( int i = 1; i < 6; i++ ) {
		for ( int j = 0; j < i; j++ ) {
			if ( CMath::Fabs( mat[i][j] - mat[j][i] ) > epsilon ) {
				return false;
			}
		}
	}
	return true;
}

SGF_INLINE_FORCED bool CMatriz6D::IsDiagonal( const float epsilon ) const {
	for ( int i = 0; i < 6; i++ ) {
		for ( int j = 0; j < 6; j++ ) {
			if ( i != j && CMath::Fabs( mat[i][j] ) > epsilon ) {
				return false;
			}
		}
	}
	return true;
}

SGF_INLINE_FORCED CMatriz3D CMatriz6D::SubMat3( int n ) const {
	assert( n >= 0 && n < 4 );
	int b0 = ((n & 2) >> 1) * 3;
	int b1 = (n & 1) * 3;
	return CMatriz3D(
		mat[b0 + 0][b1 + 0], mat[b0 + 0][b1 + 1], mat[b0 + 0][b1 + 2],
		mat[b0 + 1][b1 + 0], mat[b0 + 1][b1 + 1], mat[b0 + 1][b1 + 2],
		mat[b0 + 2][b1 + 0], mat[b0 + 2][b1 + 1], mat[b0 + 2][b1 + 2] );
}

SGF_INLINE_FORCED float CMatriz6D::Trace() const {
	return ( mat[0][0] + mat[1][1] + mat[2][2] + mat[3][3] + mat[4][4] + mat[5][5] );
}

SGF_INLINE_FORCED CMatriz6D CMatriz6D::Inverse() const {
	CMatriz6D invMat;

	invMat = *this;
	int r = invMat.InverseSelf();
	assert( r );
	return invMat;
}

SGF_INLINE_FORCED CMatriz6D CMatriz6D::InverseFast() const {
	CMatriz6D invMat;

	invMat = *this;
	int r = invMat.InverseFastSelf();
	assert( r );
	return invMat;
}

SGF_INLINE_FORCED int CMatriz6D::GetDimension() const {
	return 36;
}

SGF_INLINE_FORCED const float *CMatriz6D::ToFloatPtr() const {
	return mat[0].ToFloatPtr();
}

SGF_INLINE_FORCED float *CMatriz6D::ToFloatPtr() {
	return mat[0].ToFloatPtr();
}


//===============================================================
//
//	CMatrizXD - arbitrary sized dense real matrix
//
//  The matrix lives on 16 byte aligned and 16 byte padded memory.
//
//	NOTE: due to the temporary memory pool CMatrizXD cannot be used by multiple threads.
//
//===============================================================

#define MATX_MAX_TEMP		1024
#define MATX_QUAD( x )		( ( ( ( x ) + 3 ) & ~3 ) * sizeof( float ) )
#define MATX_CLEAREND()		int s = numRows * numColumns; while( s < ( ( s + 3 ) & ~3 ) ) { mat[s++] = 0.0f; }
#define MATX_ALLOCA( n )	( (float *) _alloca16( MATX_QUAD( n ) ) )
#define MATX_ALLOCAFLOAT( n )	( (float *) _allocafloat16( MATX_QUAD( n ) ) )
#define MATX_SIMD

class CMatrizXD {
public:
					CMatrizXD();
					explicit CMatrizXD( int rows, int columns );
					explicit CMatrizXD( int rows, int columns, float *src );
					~CMatrizXD();

	void			Set( int rows, int columns, const float *src );
	void			Set( const CMatriz3D &m1, const CMatriz3D &m2 );
	void			Set( const CMatriz3D &m1, const CMatriz3D &m2, const CMatriz3D &m3, const CMatriz3D &m4 );

	const float *	operator[]( int index ) const;
	float *			operator[]( int index );
	CMatrizXD &		operator=( const CMatrizXD &a );
	CMatrizXD			operator*( const float a ) const;
	CVectorXD			operator*( const CVectorXD &vec ) const;
	CMatrizXD			operator*( const CMatrizXD &a ) const;
	CMatrizXD			operator+( const CMatrizXD &a ) const;
	CMatrizXD			operator-( const CMatrizXD &a ) const;
	CMatrizXD &		operator*=( const float a );
	CMatrizXD &		operator*=( const CMatrizXD &a );
	CMatrizXD &		operator+=( const CMatrizXD &a );
	CMatrizXD &		operator-=( const CMatrizXD &a );

	friend CMatrizXD	operator*( const float a, const CMatrizXD &m );
	friend CVectorXD	operator*( const CVectorXD &vec, const CMatrizXD &m );
	friend CVectorXD &	operator*=( CVectorXD &vec, const CMatrizXD &m );

	bool			Compare( const CMatrizXD &a ) const;								// exact compare, no epsilon
	bool			Compare( const CMatrizXD &a, const float epsilon ) const;			// compare with epsilon
	bool			operator==( const CMatrizXD &a ) const;							// exact compare, no epsilon
	bool			operator!=( const CMatrizXD &a ) const;							// exact compare, no epsilon

	void			SetSize( int rows, int columns );								// set the number of rows/columns
	void			ChangeSize( int rows, int columns, bool makeZero = false );		// change the size keeping data intact where possible
	int				GetNumRows() const { return numRows; }					// get the number of rows
	int				GetNumColumns() const { return numColumns; }				// get the number of columns
	void			SetData( int rows, int columns, float *data );					// set float array pointer
	void			Zero();													// clear matrix
	void			Zero( int rows, int columns );									// set size and clear matrix
	void			Identity();												// clear to identity matrix
	void			Identity( int rows, int columns );								// set size and clear to identity matrix
	void			Diag( const CVectorXD &v );										// create diagonal matrix from vector
	void			Random( int seed, float l = 0.0f, float u = 1.0f );				// fill matrix with random values
	void			Random( int rows, int columns, int seed, float l = 0.0f, float u = 1.0f );
	void			Negate();													// (*this) = - (*this)
	void			Clamp( float min, float max );									// clamp all values
	CMatrizXD &		SwapRows( int r1, int r2 );										// swap rows
	CMatrizXD &		SwapColumns( int r1, int r2 );									// swap columns
	CMatrizXD &		SwapRowsColumns( int r1, int r2 );								// swap rows and columns
	CMatrizXD &		RemoveRow( int r );												// remove a row
	CMatrizXD &		RemoveColumn( int r );											// remove a column
	CMatrizXD &		RemoveRowColumn( int r );										// remove a row and column
	void			ClearUpperTriangle();										// clear the upper triangle
	void			ClearLowerTriangle();										// clear the lower triangle
	void			SquareSubMatrix( const CMatrizXD &m, int size );					// get square sub-matrix from 0,0 to size,size
	float			MaxDifference( const CMatrizXD &m ) const;							// return maximum element difference between this and m

	bool			IsSquare() const { return ( numRows == numColumns ); }
	bool			IsZero( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsIdentity( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsDiagonal( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsTriDiagonal( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsSymmetric( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsOrthogonal( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsOrthonormal( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsPMatrix( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsZMatrix( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsPositiveDefinite( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsSymmetricPositiveDefinite( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsPositiveSemiDefinite( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsSymmetricPositiveSemiDefinite( const float epsilon = MATRIX_EPSILON ) const;

	float			Trace() const;											// returns product of diagonal elements
	float			Determinant() const;										// returns determinant of matrix
	CMatrizXD			Transpose() const;										// returns transpose
	CMatrizXD &		TransposeSelf();											// transposes the matrix itself
	CMatrizXD			Inverse() const;											// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseSelf();											// returns false if determinant is zero
	CMatrizXD			InverseFast() const;										// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseFastSelf();										// returns false if determinant is zero

	bool			LowerTriangularInverse();									// in-place inversion, returns false if determinant is zero
	bool			UpperTriangularInverse();									// in-place inversion, returns false if determinant is zero

	CVectorXD			Multiply( const CVectorXD &vec ) const;							// (*this) * vec
	CVectorXD			TransposeMultiply( const CVectorXD &vec ) const;					// this->Transpose() * vec

	CMatrizXD			Multiply( const CMatrizXD &a ) const;								// (*this) * a
	CMatrizXD			TransposeMultiply( const CMatrizXD &a ) const;						// this->Transpose() * a

	void			Multiply( CVectorXD &dst, const CVectorXD &vec ) const;				// dst = (*this) * vec
	void			MultiplyAdd( CVectorXD &dst, const CVectorXD &vec ) const;			// dst += (*this) * vec
	void			MultiplySub( CVectorXD &dst, const CVectorXD &vec ) const;			// dst -= (*this) * vec
	void			TransposeMultiply( CVectorXD &dst, const CVectorXD &vec ) const;		// dst = this->Transpose() * vec
	void			TransposeMultiplyAdd( CVectorXD &dst, const CVectorXD &vec ) const;	// dst += this->Transpose() * vec
	void			TransposeMultiplySub( CVectorXD &dst, const CVectorXD &vec ) const;	// dst -= this->Transpose() * vec

	void			Multiply( CMatrizXD &dst, const CMatrizXD &a ) const;					// dst = (*this) * a
	void			TransposeMultiply( CMatrizXD &dst, const CMatrizXD &a ) const;		// dst = this->Transpose() * a

	int				GetDimension() const;										// returns total number of values in matrix

	const CVector6D &	SubVec6( int row ) const;										// interpret beginning of row as a const CVector6D
	CVector6D &		SubVec6( int row );												// interpret beginning of row as an CVector6D
	const CVectorXD	SubVecX( int row ) const;										// interpret complete row as a const CVectorXD
	CVectorXD			SubVecX( int row );												// interpret complete row as an CVectorXD
	const float *	ToFloatPtr() const;										// pointer to const matrix float array
	float *			ToFloatPtr();												// pointer to matrix float array
	const char *	ToString( int precision = 2 ) const;

	void			Update_RankOne( const CVectorXD &v, const CVectorXD &w, float alpha );
	void			Update_RankOneSymmetric( const CVectorXD &v, float alpha );
	void			Update_RowColumn( const CVectorXD &v, const CVectorXD &w, int r );
	void			Update_RowColumnSymmetric( const CVectorXD &v, int r );
	void			Update_Increment( const CVectorXD &v, const CVectorXD &w );
	void			Update_IncrementSymmetric( const CVectorXD &v );
	void			Update_Decrement( int r );

	bool			Inverse_GaussJordan();					// invert in-place with Gauss-Jordan elimination
	bool			Inverse_UpdateRankOne( const CVectorXD &v, const CVectorXD &w, float alpha );
	bool			Inverse_UpdateRowColumn( const CVectorXD &v, const CVectorXD &w, int r );
	bool			Inverse_UpdateIncrement( const CVectorXD &v, const CVectorXD &w );
	bool			Inverse_UpdateDecrement( const CVectorXD &v, const CVectorXD &w, int r );
	void			Inverse_Solve( CVectorXD &x, const CVectorXD &b ) const;

	bool			LU_Factor( int *index, float *det = NULL );		// factor in-place: L * U
	bool			LU_UpdateRankOne( const CVectorXD &v, const CVectorXD &w, float alpha, int *index );
	bool			LU_UpdateRowColumn( const CVectorXD &v, const CVectorXD &w, int r, int *index );
	bool			LU_UpdateIncrement( const CVectorXD &v, const CVectorXD &w, int *index );
	bool			LU_UpdateDecrement( const CVectorXD &v, const CVectorXD &w, const CVectorXD &u, int r, int *index );
	void			LU_Solve( CVectorXD &x, const CVectorXD &b, const int *index ) const;
	void			LU_Inverse( CMatrizXD &inv, const int *index ) const;
	void			LU_UnpackFactors( CMatrizXD &L, CMatrizXD &U ) const;
	void			LU_MultiplyFactors( CMatrizXD &m, const int *index ) const;

	bool			QR_Factor( CVectorXD &c, CVectorXD &d );				// factor in-place: Q * R
	bool			QR_UpdateRankOne( CMatrizXD &R, const CVectorXD &v, const CVectorXD &w, float alpha );
	bool			QR_UpdateRowColumn( CMatrizXD &R, const CVectorXD &v, const CVectorXD &w, int r );
	bool			QR_UpdateIncrement( CMatrizXD &R, const CVectorXD &v, const CVectorXD &w );
	bool			QR_UpdateDecrement( CMatrizXD &R, const CVectorXD &v, const CVectorXD &w, int r );
	void			QR_Solve( CVectorXD &x, const CVectorXD &b, const CVectorXD &c, const CVectorXD &d ) const;
	void			QR_Solve( CVectorXD &x, const CVectorXD &b, const CMatrizXD &R ) const;
	void			QR_Inverse( CMatrizXD &inv, const CVectorXD &c, const CVectorXD &d ) const;
	void			QR_UnpackFactors( CMatrizXD &Q, CMatrizXD &R, const CVectorXD &c, const CVectorXD &d ) const;
	void			QR_MultiplyFactors( CMatrizXD &m, const CVectorXD &c, const CVectorXD &d ) const;

	bool			SVD_Factor( CVectorXD &w, CMatrizXD &V );				// factor in-place: U * Diag(w) * V.Transpose()
	void			SVD_Solve( CVectorXD &x, const CVectorXD &b, const CVectorXD &w, const CMatrizXD &V ) const;
	void			SVD_Inverse( CMatrizXD &inv, const CVectorXD &w, const CMatrizXD &V ) const;
	void			SVD_MultiplyFactors( CMatrizXD &m, const CVectorXD &w, const CMatrizXD &V ) const;

	bool			Cholesky_Factor();						// factor in-place: L * L.Transpose()
	bool			Cholesky_UpdateRankOne( const CVectorXD &v, float alpha, int offset = 0 );
	bool			Cholesky_UpdateRowColumn( const CVectorXD &v, int r );
	bool			Cholesky_UpdateIncrement( const CVectorXD &v );
	bool			Cholesky_UpdateDecrement( const CVectorXD &v, int r );
	void			Cholesky_Solve( CVectorXD &x, const CVectorXD &b ) const;
	void			Cholesky_Inverse( CMatrizXD &inv ) const;
	void			Cholesky_MultiplyFactors( CMatrizXD &m ) const;

	bool			LDLT_Factor();							// factor in-place: L * D * L.Transpose()
	bool			LDLT_UpdateRankOne( const CVectorXD &v, float alpha, int offset = 0 );
	bool			LDLT_UpdateRowColumn( const CVectorXD &v, int r );
	bool			LDLT_UpdateIncrement( const CVectorXD &v );
	bool			LDLT_UpdateDecrement( const CVectorXD &v, int r );
	void			LDLT_Solve( CVectorXD &x, const CVectorXD &b ) const;
	void			LDLT_Inverse( CMatrizXD &inv ) const;
	void			LDLT_UnpackFactors( CMatrizXD &L, CMatrizXD &D ) const;
	void			LDLT_MultiplyFactors( CMatrizXD &m ) const;

	void			TriDiagonal_ClearTriangles();
	bool			TriDiagonal_Solve( CVectorXD &x, const CVectorXD &b ) const;
	void			TriDiagonal_Inverse( CMatrizXD &inv ) const;

	bool			Eigen_SolveSymmetricTriDiagonal( CVectorXD &eigenValues );
	bool			Eigen_SolveSymmetric( CVectorXD &eigenValues );
	bool			Eigen_Solve( CVectorXD &realEigenValues, CVectorXD &imaginaryEigenValues );
	void			Eigen_SortIncreasing( CVectorXD &eigenValues );
	void			Eigen_SortDecreasing( CVectorXD &eigenValues );

	static void		Test();

private:
	int				numRows;				// number of rows
	int				numColumns;				// number of columns
	int				alloced;				// floats allocated, if -1 then mat points to data set with SetData
	float *			mat;					// memory the matrix is stored

	static float	temp[MATX_MAX_TEMP+4];	// used to store intermediate results
	static float *	tempPtr;				// pointer to 16 byte aligned temporary memory
	static int		tempIndex;				// index into memory pool, wraps around

private:
	void			SetTempSize( int rows, int columns );
	float			DeterminantGeneric() const;
	bool			InverseSelfGeneric();
	void			QR_Rotate( CMatrizXD &R, int i, float a, float b );
	float			Pythag( float a, float b ) const;
	void			SVD_BiDiag( CVectorXD &w, CVectorXD &rv1, float &anorm );
	void			SVD_InitialWV( CVectorXD &w, CMatrizXD &V, CVectorXD &rv1 );
	void			HouseholderReduction( CVectorXD &diag, CVectorXD &subd );
	bool			QL( CVectorXD &diag, CVectorXD &subd );
	void			HessenbergReduction( CMatrizXD &H );
	void			ComplexDivision( float xr, float xi, float yr, float yi, float &cdivr, float &cdivi );
	bool			HessenbergToRealSchur( CMatrizXD &H, CVectorXD &realEigenValues, CVectorXD &imaginaryEigenValues );
};

SGF_INLINE_FORCED CMatrizXD::CMatrizXD() {
	numRows = numColumns = alloced = 0;
	mat = NULL;
}

SGF_INLINE_FORCED CMatrizXD::~CMatrizXD() {
	// if not temp memory
	if ( mat != NULL && ( mat < CMatrizXD::tempPtr || mat > CMatrizXD::tempPtr + MATX_MAX_TEMP ) && alloced != -1 ) {
		Mem_Free16( mat );
	}
}

SGF_INLINE_FORCED CMatrizXD::CMatrizXD( int rows, int columns ) {
	numRows = numColumns = alloced = 0;
	mat = NULL;
	SetSize( rows, columns );
}

SGF_INLINE_FORCED CMatrizXD::CMatrizXD( int rows, int columns, float *src ) {
	numRows = numColumns = alloced = 0;
	mat = NULL;
	SetData( rows, columns, src );
}

SGF_INLINE_FORCED void CMatrizXD::Set( int rows, int columns, const float *src ) {
	SetSize( rows, columns );
	memcpy( this->mat, src, rows * columns * sizeof( float ) );
}

SGF_INLINE_FORCED void CMatrizXD::Set( const CMatriz3D &m1, const CMatriz3D &m2 ) {
	int i, j;

	SetSize( 3, 6 );
	for ( i = 0; i < 3; i++ ) {
		for ( j = 0; j < 3; j++ ) {
			mat[(i+0) * numColumns + (j+0)] = m1[i][j];
			mat[(i+0) * numColumns + (j+3)] = m2[i][j];
		}
	}
}

SGF_INLINE_FORCED void CMatrizXD::Set( const CMatriz3D &m1, const CMatriz3D &m2, const CMatriz3D &m3, const CMatriz3D &m4 ) {
	int i, j;

	SetSize( 6, 6 );
	for ( i = 0; i < 3; i++ ) {
		for ( j = 0; j < 3; j++ ) {
			mat[(i+0) * numColumns + (j+0)] = m1[i][j];
			mat[(i+0) * numColumns + (j+3)] = m2[i][j];
			mat[(i+3) * numColumns + (j+0)] = m3[i][j];
			mat[(i+3) * numColumns + (j+3)] = m4[i][j];
		}
	}
}

SGF_INLINE_FORCED const float *CMatrizXD::operator[]( int index ) const {
	assert( ( index >= 0 ) && ( index < numRows ) );
	return mat + index * numColumns;
}

SGF_INLINE_FORCED float *CMatrizXD::operator[]( int index ) {
	assert( ( index >= 0 ) && ( index < numRows ) );
	return mat + index * numColumns;
}

SGF_INLINE_FORCED CMatrizXD &CMatrizXD::operator=( const CMatrizXD &a ) {
	SetSize( a.numRows, a.numColumns );
#ifdef MATX_SIMD
	SIMDProcessor->Copy16( mat, a.mat, a.numRows * a.numColumns );
#else
	memcpy( mat, a.mat, a.numRows * a.numColumns * sizeof( float ) );
#endif
	CMatrizXD::tempIndex = 0;
	return *this;
}

SGF_INLINE_FORCED CMatrizXD CMatrizXD::operator*( const float a ) const {
	CMatrizXD m;

	m.SetTempSize( numRows, numColumns );
#ifdef MATX_SIMD
	SIMDProcessor->Mul16( m.mat, mat, a, numRows * numColumns );
#else
	int i, s;
	s = numRows * numColumns;
	for ( i = 0; i < s; i++ ) {
		m.mat[i] = mat[i] * a;
	}
#endif
	return m;
}

SGF_INLINE_FORCED CVectorXD CMatrizXD::operator*( const CVectorXD &vec ) const {
	CVectorXD dst;

	assert( numColumns == vec.GetSize() );

	dst.SetTempSize( numRows );
#ifdef MATX_SIMD
	SIMDProcessor->MatX_MultiplyVecX( dst, *this, vec );
#else
	Multiply( dst, vec );
#endif
	return dst;
}

SGF_INLINE_FORCED CMatrizXD CMatrizXD::operator*( const CMatrizXD &a ) const {
	CMatrizXD dst;

	assert( numColumns == a.numRows );

	dst.SetTempSize( numRows, a.numColumns );
#ifdef MATX_SIMD
	SIMDProcessor->MatX_MultiplyMatX( dst, *this, a );
#else
	Multiply( dst, a );
#endif
	return dst;
}

SGF_INLINE_FORCED CMatrizXD CMatrizXD::operator+( const CMatrizXD &a ) const {
	CMatrizXD m;

	assert( numRows == a.numRows && numColumns == a.numColumns );
	m.SetTempSize( numRows, numColumns );
#ifdef MATX_SIMD
	SIMDProcessor->Add16( m.mat, mat, a.mat, numRows * numColumns );
#else
	int i, s;
	s = numRows * numColumns;
	for ( i = 0; i < s; i++ ) {
		m.mat[i] = mat[i] + a.mat[i];
	}
#endif
	return m;
}

SGF_INLINE_FORCED CMatrizXD CMatrizXD::operator-( const CMatrizXD &a ) const {
	CMatrizXD m;

	assert( numRows == a.numRows && numColumns == a.numColumns );
	m.SetTempSize( numRows, numColumns );
#ifdef MATX_SIMD
	SIMDProcessor->Sub16( m.mat, mat, a.mat, numRows * numColumns );
#else
	int i, s;
	s = numRows * numColumns;
	for ( i = 0; i < s; i++ ) {
		m.mat[i] = mat[i] - a.mat[i];
	}
#endif
	return m;
}

SGF_INLINE_FORCED CMatrizXD &CMatrizXD::operator*=( const float a ) {
#ifdef MATX_SIMD
	SIMDProcessor->MulAssign16( mat, a, numRows * numColumns );
#else
	int i, s;
	s = numRows * numColumns;
	for ( i = 0; i < s; i++ ) {
		mat[i] *= a;
	}
#endif
	CMatrizXD::tempIndex = 0;
	return *this;
}

SGF_INLINE_FORCED CMatrizXD &CMatrizXD::operator*=( const CMatrizXD &a ) {
	*this = *this * a;
	CMatrizXD::tempIndex = 0;
	return *this;
}

SGF_INLINE_FORCED CMatrizXD &CMatrizXD::operator+=( const CMatrizXD &a ) {
	assert( numRows == a.numRows && numColumns == a.numColumns );
#ifdef MATX_SIMD
	SIMDProcessor->AddAssign16( mat, a.mat, numRows * numColumns );
#else
	int i, s;
	s = numRows * numColumns;
	for ( i = 0; i < s; i++ ) {
		mat[i] += a.mat[i];
	}
#endif
	CMatrizXD::tempIndex = 0;
	return *this;
}

SGF_INLINE_FORCED CMatrizXD &CMatrizXD::operator-=( const CMatrizXD &a ) {
	assert( numRows == a.numRows && numColumns == a.numColumns );
#ifdef MATX_SIMD
	SIMDProcessor->SubAssign16( mat, a.mat, numRows * numColumns );
#else
	int i, s;
	s = numRows * numColumns;
	for ( i = 0; i < s; i++ ) {
		mat[i] -= a.mat[i];
	}
#endif
	CMatrizXD::tempIndex = 0;
	return *this;
}

SGF_INLINE_FORCED CMatrizXD operator*( const float a, CMatrizXD const &m ) {
	return m * a;
}

SGF_INLINE_FORCED CVectorXD operator*( const CVectorXD &vec, const CMatrizXD &m ) {
	return m * vec;
}

SGF_INLINE_FORCED CVectorXD &operator*=( CVectorXD &vec, const CMatrizXD &m ) {
	vec = m * vec;
	return vec;
}

SGF_INLINE_FORCED bool CMatrizXD::Compare( const CMatrizXD &a ) const {
	int i, s;

	assert( numRows == a.numRows && numColumns == a.numColumns );

	s = numRows * numColumns;
	for ( i = 0; i < s; i++ ) {
		if ( mat[i] != a.mat[i] ) {
			return false;
		}
	}
	return true;
}

SGF_INLINE_FORCED bool CMatrizXD::Compare( const CMatrizXD &a, const float epsilon ) const {
	int i, s;

	assert( numRows == a.numRows && numColumns == a.numColumns );

	s = numRows * numColumns;
	for ( i = 0; i < s; i++ ) {
		if ( CMath::Fabs( mat[i] - a.mat[i] ) > epsilon ) {
			return false;
		}
	}
	return true;
}

SGF_INLINE_FORCED bool CMatrizXD::operator==( const CMatrizXD &a ) const {
	return Compare( a );
}

SGF_INLINE_FORCED bool CMatrizXD::operator!=( const CMatrizXD &a ) const {
	return !Compare( a );
}

SGF_INLINE_FORCED void CMatrizXD::SetSize( int rows, int columns ) {
	assert( mat < CMatrizXD::tempPtr || mat > CMatrizXD::tempPtr + MATX_MAX_TEMP );
	int alloc = ( rows * columns + 3 ) & ~3;
	if ( alloc > alloced && alloced != -1 ) {
		if ( mat != NULL ) {
			Mem_Free16( mat );
		}
		mat = (float *) Mem_Alloc16( alloc * sizeof( float ) );
		alloced = alloc;
	}
	numRows = rows;
	numColumns = columns;
	MATX_CLEAREND();
}

SGF_INLINE_FORCED void CMatrizXD::SetTempSize( int rows, int columns ) {
	int newSize;

	newSize = ( rows * columns + 3 ) & ~3;
	assert( newSize < MATX_MAX_TEMP );
	if ( CMatrizXD::tempIndex + newSize > MATX_MAX_TEMP ) {
		CMatrizXD::tempIndex = 0;
	}
	mat = CMatrizXD::tempPtr + CMatrizXD::tempIndex;
	CMatrizXD::tempIndex += newSize;
	alloced = newSize;
	numRows = rows;
	numColumns = columns;
	MATX_CLEAREND();
}

SGF_INLINE_FORCED void CMatrizXD::SetData( int rows, int columns, float *data ) {
	assert( mat < CMatrizXD::tempPtr || mat > CMatrizXD::tempPtr + MATX_MAX_TEMP );
	if ( mat != NULL && alloced != -1 ) {
		Mem_Free16( mat );
	}
#ifdef _WIN32 
	assert( ( ( (int) data ) & 15 ) == 0 ); // data must be 16 byte aligned
#else
	assert( ( ( (uintptr_t) data ) & 15 ) == 0 ); // data must be 16 byte aligned
#endif	
	mat = data;
	alloced = -1;
	numRows = rows;
	numColumns = columns;
	MATX_CLEAREND();
}

SGF_INLINE_FORCED void CMatrizXD::Zero() {
#ifdef MATX_SIMD
	SIMDProcessor->Zero16( mat, numRows * numColumns );
#else
	memset( mat, 0, numRows * numColumns * sizeof( float ) );
#endif
}

SGF_INLINE_FORCED void CMatrizXD::Zero( int rows, int columns ) {
	SetSize( rows, columns );
#ifdef MATX_SIMD
	SIMDProcessor->Zero16( mat, numRows * numColumns );
#else
	memset( mat, 0, rows * columns * sizeof( float ) );
#endif
}

SGF_INLINE_FORCED void CMatrizXD::Identity() {
	assert( numRows == numColumns );
#ifdef MATX_SIMD
	SIMDProcessor->Zero16( mat, numRows * numColumns );
#else
	memset( mat, 0, numRows * numColumns * sizeof( float ) );
#endif
	for ( int i = 0; i < numRows; i++ ) {
		mat[i * numColumns + i] = 1.0f;
	}
}

SGF_INLINE_FORCED void CMatrizXD::Identity( int rows, int columns ) {
	assert( rows == columns );
	SetSize( rows, columns );
	CMatrizXD::Identity();
}

SGF_INLINE_FORCED void CMatrizXD::Diag( const CVectorXD &v ) {
	Zero( v.GetSize(), v.GetSize() );
	for ( int i = 0; i < v.GetSize(); i++ ) {
		mat[i * numColumns + i] = v[i];
	}
}

SGF_INLINE_FORCED void CMatrizXD::Random( int seed, float l, float u ) {
	int i, s;
	float c;
	CRamdom rnd(seed);

	c = u - l;
	s = numRows * numColumns;
	for ( i = 0; i < s; i++ ) {
		mat[i] = l + rnd.RandomFloat() * c;
	}
}

SGF_INLINE_FORCED void CMatrizXD::Random( int rows, int columns, int seed, float l, float u ) {
	int i, s;
	float c;
	CRamdom rnd(seed);

	SetSize( rows, columns );
	c = u - l;
	s = numRows * numColumns;
	for ( i = 0; i < s; i++ ) {
		mat[i] = l + rnd.RandomFloat() * c;
	}
}

SGF_INLINE_FORCED void CMatrizXD::Negate() {
#ifdef MATX_SIMD
	SIMDProcessor->Negate16( mat, numRows * numColumns );
#else
	int i, s;
	s = numRows * numColumns;
	for ( i = 0; i < s; i++ ) {
		mat[i] = -mat[i];
	}
#endif
}

SGF_INLINE_FORCED void CMatrizXD::Clamp( float min, float max ) {
	int i, s;
	s = numRows * numColumns;
	for ( i = 0; i < s; i++ ) {
		if ( mat[i] < min ) {
			mat[i] = min;
		} else if ( mat[i] > max ) {
			mat[i] = max;
		}
	}
}

SGF_INLINE_FORCED CMatrizXD &CMatrizXD::SwapRows( int r1, int r2 ) {
	float *ptr;
	
	//
	//
#ifdef _WIN32
	ptr = (float *) _alloca16( numColumns * sizeof( float ) );
#else
	ptr = ((float *)((((uintptr_t)alloca( (numColumns * sizeof( float ))+15 )) + 15) & ~15));
	
#endif	
	memcpy( ptr, mat + r1 * numColumns, numColumns * sizeof( float ) );
	memcpy( mat + r1 * numColumns, mat + r2 * numColumns, numColumns * sizeof( float ) );
	memcpy( mat + r2 * numColumns, ptr, numColumns * sizeof( float ) );

	return *this;
}

SGF_INLINE_FORCED CMatrizXD &CMatrizXD::SwapColumns( int r1, int r2 ) {
	int i;
	float tmp, *ptr;

	for ( i = 0; i < numRows; i++ ) {
		ptr = mat + i * numColumns;
		tmp = ptr[r1];
		ptr[r1] = ptr[r2];
		ptr[r2] = tmp;
	}

	return *this;
}

SGF_INLINE_FORCED CMatrizXD &CMatrizXD::SwapRowsColumns( int r1, int r2 ) {

	SwapRows( r1, r2 );
	SwapColumns( r1, r2 );
	return *this;
}

SGF_INLINE_FORCED void CMatrizXD::ClearUpperTriangle() {
	assert( numRows == numColumns );
	for ( int i = numRows-2; i >= 0; i-- ) {
		memset( mat + i * numColumns + i + 1, 0, (numColumns - 1 - i) * sizeof(float) );
	}
}

SGF_INLINE_FORCED void CMatrizXD::ClearLowerTriangle() {
	assert( numRows == numColumns );
	for ( int i = 1; i < numRows; i++ ) {
		memset( mat + i * numColumns, 0, i * sizeof(float) );
	}
}

SGF_INLINE_FORCED void CMatrizXD::SquareSubMatrix( const CMatrizXD &m, int size ) {
	int i;
	assert( size <= m.numRows && size <= m.numColumns );
	SetSize( size, size );
	for ( i = 0; i < size; i++ ) {
		memcpy( mat + i * numColumns, m.mat + i * m.numColumns, size * sizeof( float ) );
	}
}

SGF_INLINE_FORCED float CMatrizXD::MaxDifference( const CMatrizXD &m ) const {
	int i, j;
	float diff, maxDiff;

	assert( numRows == m.numRows && numColumns == m.numColumns );

	maxDiff = -1.0f;
	for ( i = 0; i < numRows; i++ ) {
		for ( j = 0; j < numColumns; j++ ) {
			diff = CMath::Fabs( mat[ i * numColumns + j ] - m[i][j] );
			if ( maxDiff < 0.0f || diff > maxDiff ) {
				maxDiff = diff;
			}
		}
	}
	return maxDiff;
}

SGF_INLINE_FORCED bool CMatrizXD::IsZero( const float epsilon ) const {
	// returns true if (*this) == Zero
	for ( int i = 0; i < numRows; i++ ) {
		for ( int j = 0; j < numColumns; j++ ) {
			if ( CMath::Fabs( mat[i * numColumns + j] ) > epsilon ) {
				return false;
			}
		}
	}
	return true;
}

SGF_INLINE_FORCED bool CMatrizXD::IsIdentity( const float epsilon ) const {
	// returns true if (*this) == Identity
	assert( numRows == numColumns );
	for ( int i = 0; i < numRows; i++ ) {
		for ( int j = 0; j < numColumns; j++ ) {
			if ( CMath::Fabs( mat[i * numColumns + j] - (float)( i == j ) ) > epsilon ) {
				return false;
			}
		}
	}
	return true;
}

SGF_INLINE_FORCED bool CMatrizXD::IsDiagonal( const float epsilon ) const {
	// returns true if all elements are zero except for the elements on the diagonal
	assert( numRows == numColumns );
	for ( int i = 0; i < numRows; i++ ) {
		for ( int j = 0; j < numColumns; j++ ) {
			if ( i != j && CMath::Fabs( mat[i * numColumns + j] ) > epsilon ) {
				return false;
			}
		}
	}
	return true;
}

SGF_INLINE_FORCED bool CMatrizXD::IsTriDiagonal( const float epsilon ) const {
	// returns true if all elements are zero except for the elements on the diagonal plus or minus one column

	if ( numRows != numColumns ) {
		return false;
	}
	for ( int i = 0; i < numRows-2; i++ ) {
		for ( int j = i+2; j < numColumns; j++ ) {
			if ( CMath::Fabs( (*this)[i][j] ) > epsilon ) {
				return false;
			}
			if ( CMath::Fabs( (*this)[j][i] ) > epsilon ) {
				return false;
			}
		}
	}
	return true;
}

SGF_INLINE_FORCED bool CMatrizXD::IsSymmetric( const float epsilon ) const {
	// (*this)[i][j] == (*this)[j][i]
	if ( numRows != numColumns ) {
		return false;
	}
	for ( int i = 0; i < numRows; i++ ) {
		for ( int j = 0; j < numColumns; j++ ) {
			if ( CMath::Fabs( mat[ i * numColumns + j ] - mat[ j * numColumns + i ] ) > epsilon ) {
				return false;
			}
		}
	}
	return true;
}

SGF_INLINE_FORCED float CMatrizXD::Trace() const {
	float trace = 0.0f;

	assert( numRows == numColumns );

	// sum of elements on the diagonal
	for ( int i = 0; i < numRows; i++ ) {
		trace += mat[i * numRows + i];
	}
	return trace;
}

SGF_INLINE_FORCED float CMatrizXD::Determinant() const {

	assert( numRows == numColumns );

	switch( numRows ) {
		case 1:
			return mat[0];
		case 2:
			return reinterpret_cast<const CMatriz2D *>(mat)->Determinant();
		case 3:
			return reinterpret_cast<const CMatriz3D *>(mat)->Determinant();
		case 4:
			return reinterpret_cast<const CMatriz4D *>(mat)->Determinant();
		case 5:
			return reinterpret_cast<const CMatriz5D *>(mat)->Determinant();
		case 6:
			return reinterpret_cast<const CMatriz6D *>(mat)->Determinant();
		default:
			return DeterminantGeneric();
	}
	return 0.0f;
}

SGF_INLINE_FORCED CMatrizXD CMatrizXD::Transpose() const {
	CMatrizXD transpose;
	int i, j;

	transpose.SetTempSize( numColumns, numRows );

	for ( i = 0; i < numRows; i++ ) {
		for ( j = 0; j < numColumns; j++ ) {
			transpose.mat[j * transpose.numColumns + i] = mat[i * numColumns + j];
		}
	}

	return transpose;
}

SGF_INLINE_FORCED CMatrizXD &CMatrizXD::TransposeSelf() {
	*this = Transpose();
	return *this;
}

SGF_INLINE_FORCED CMatrizXD CMatrizXD::Inverse() const {
	CMatrizXD invMat;

	invMat.SetTempSize( numRows, numColumns );
	memcpy( invMat.mat, mat, numRows * numColumns * sizeof( float ) );
	int r = invMat.InverseSelf();
	assert( r );
	return invMat;
}

SGF_INLINE_FORCED bool CMatrizXD::InverseSelf() {

	assert( numRows == numColumns );

	switch( numRows ) {
		case 1:
			if ( CMath::Fabs( mat[0] ) < MATRIX_INVERSE_EPSILON ) {
				return false;
			}
			mat[0] = 1.0f / mat[0];
			return true;
		case 2:
			return reinterpret_cast<CMatriz2D *>(mat)->InverseSelf();
		case 3:
			return reinterpret_cast<CMatriz3D *>(mat)->InverseSelf();
		case 4:
			return reinterpret_cast<CMatriz4D *>(mat)->InverseSelf();
		case 5:
			return reinterpret_cast<CMatriz5D *>(mat)->InverseSelf();
		case 6:
			return reinterpret_cast<CMatriz6D *>(mat)->InverseSelf();
		default:
			return InverseSelfGeneric();
	}
}

SGF_INLINE_FORCED CMatrizXD CMatrizXD::InverseFast() const {
	CMatrizXD invMat;

	invMat.SetTempSize( numRows, numColumns );
	memcpy( invMat.mat, mat, numRows * numColumns * sizeof( float ) );
	int r = invMat.InverseFastSelf();
	assert( r );
	return invMat;
}

SGF_INLINE_FORCED bool CMatrizXD::InverseFastSelf() {

	assert( numRows == numColumns );

	switch( numRows ) {
		case 1:
			if ( CMath::Fabs( mat[0] ) < MATRIX_INVERSE_EPSILON ) {
				return false;
			}
			mat[0] = 1.0f / mat[0];
			return true;
		case 2:
			return reinterpret_cast<CMatriz2D *>(mat)->InverseFastSelf();
		case 3:
			return reinterpret_cast<CMatriz3D *>(mat)->InverseFastSelf();
		case 4:
			return reinterpret_cast<CMatriz4D *>(mat)->InverseFastSelf();
		case 5:
			return reinterpret_cast<CMatriz5D *>(mat)->InverseFastSelf();
		case 6:
			return reinterpret_cast<CMatriz6D *>(mat)->InverseFastSelf();
		default:
			return InverseSelfGeneric();
	}
	return false;
}

SGF_INLINE_FORCED CVectorXD CMatrizXD::Multiply( const CVectorXD &vec ) const {
	CVectorXD dst;

	assert( numColumns == vec.GetSize() );

	dst.SetTempSize( numRows );
#ifdef MATX_SIMD
	SIMDProcessor->MatX_MultiplyVecX( dst, *this, vec );
#else
	Multiply( dst, vec );
#endif
	return dst;
}

SGF_INLINE_FORCED CMatrizXD CMatrizXD::Multiply( const CMatrizXD &a ) const {
	CMatrizXD dst;

	assert( numColumns == a.numRows );

	dst.SetTempSize( numRows, a.numColumns );
#ifdef MATX_SIMD
	SIMDProcessor->MatX_MultiplyMatX( dst, *this, a );
#else
	Multiply( dst, a );
#endif
	return dst;
}

SGF_INLINE_FORCED CVectorXD CMatrizXD::TransposeMultiply( const CVectorXD &vec ) const {
	CVectorXD dst;

	assert( numRows == vec.GetSize() );

	dst.SetTempSize( numColumns );
#ifdef MATX_SIMD
	SIMDProcessor->MatX_TransposeMultiplyVecX( dst, *this, vec );
#else
	TransposeMultiply( dst, vec );
#endif
	return dst;
}

SGF_INLINE_FORCED CMatrizXD CMatrizXD::TransposeMultiply( const CMatrizXD &a ) const {
	CMatrizXD dst;

	assert( numRows == a.numRows );

	dst.SetTempSize( numColumns, a.numColumns );
#ifdef MATX_SIMD
	SIMDProcessor->MatX_TransposeMultiplyMatX( dst, *this, a );
#else
	TransposeMultiply( dst, a );
#endif
	return dst;
}

SGF_INLINE_FORCED void CMatrizXD::Multiply( CVectorXD &dst, const CVectorXD &vec ) const {
#ifdef MATX_SIMD
	SIMDProcessor->MatX_MultiplyVecX( dst, *this, vec );
#else
	int i, j;
	const float *mPtr, *vPtr;
	float *dstPtr;

	mPtr = mat;
	vPtr = vec.ToFloatPtr();
	dstPtr = dst.ToFloatPtr();
	for ( i = 0; i < numRows; i++ ) {
		float sum = mPtr[0] * vPtr[0];
		for ( j = 1; j < numColumns; j++ ) {
			sum += mPtr[j] * vPtr[j];
		}
		dstPtr[i] = sum;
		mPtr += numColumns;
	}
#endif
}

SGF_INLINE_FORCED void CMatrizXD::MultiplyAdd( CVectorXD &dst, const CVectorXD &vec ) const {
#ifdef MATX_SIMD
	SIMDProcessor->MatX_MultiplyAddVecX( dst, *this, vec );
#else
	int i, j;
	const float *mPtr, *vPtr;
	float *dstPtr;

	mPtr = mat;
	vPtr = vec.ToFloatPtr();
	dstPtr = dst.ToFloatPtr();
	for ( i = 0; i < numRows; i++ ) {
		float sum = mPtr[0] * vPtr[0];
		for ( j = 1; j < numColumns; j++ ) {
			sum += mPtr[j] * vPtr[j];
		}
		dstPtr[i] += sum;
		mPtr += numColumns;
	}
#endif
}

SGF_INLINE_FORCED void CMatrizXD::MultiplySub( CVectorXD &dst, const CVectorXD &vec ) const {
#ifdef MATX_SIMD
	SIMDProcessor->MatX_MultiplySubVecX( dst, *this, vec );
#else
	int i, j;
	const float *mPtr, *vPtr;
	float *dstPtr;

	mPtr = mat;
	vPtr = vec.ToFloatPtr();
	dstPtr = dst.ToFloatPtr();
	for ( i = 0; i < numRows; i++ ) {
		float sum = mPtr[0] * vPtr[0];
		for ( j = 1; j < numColumns; j++ ) {
			sum += mPtr[j] * vPtr[j];
		}
		dstPtr[i] -= sum;
		mPtr += numColumns;
	}
#endif
}

SGF_INLINE_FORCED void CMatrizXD::TransposeMultiply( CVectorXD &dst, const CVectorXD &vec ) const {
#ifdef MATX_SIMD
	SIMDProcessor->MatX_TransposeMultiplyVecX( dst, *this, vec );
#else
	int i, j;
	const float *mPtr, *vPtr;
	float *dstPtr;

	vPtr = vec.ToFloatPtr();
	dstPtr = dst.ToFloatPtr();
	for ( i = 0; i < numColumns; i++ ) {
		mPtr = mat + i;
		float sum = mPtr[0] * vPtr[0];
		for ( j = 1; j < numRows; j++ ) {
			mPtr += numColumns;
			sum += mPtr[0] * vPtr[j];
		}
		dstPtr[i] = sum;
	}
#endif
}

SGF_INLINE_FORCED void CMatrizXD::TransposeMultiplyAdd( CVectorXD &dst, const CVectorXD &vec ) const {
#ifdef MATX_SIMD
	SIMDProcessor->MatX_TransposeMultiplyAddVecX( dst, *this, vec );
#else
	int i, j;
	const float *mPtr, *vPtr;
	float *dstPtr;

	vPtr = vec.ToFloatPtr();
	dstPtr = dst.ToFloatPtr();
	for ( i = 0; i < numColumns; i++ ) {
		mPtr = mat + i;
		float sum = mPtr[0] * vPtr[0];
		for ( j = 1; j < numRows; j++ ) {
			mPtr += numColumns;
			sum += mPtr[0] * vPtr[j];
		}
		dstPtr[i] += sum;
	}
#endif
}

SGF_INLINE_FORCED void CMatrizXD::TransposeMultiplySub( CVectorXD &dst, const CVectorXD &vec ) const {
#ifdef MATX_SIMD
	SIMDProcessor->MatX_TransposeMultiplySubVecX( dst, *this, vec );
#else
	int i, j;
	const float *mPtr, *vPtr;
	float *dstPtr;

	vPtr = vec.ToFloatPtr();
	dstPtr = dst.ToFloatPtr();
	for ( i = 0; i < numColumns; i++ ) {
		mPtr = mat + i;
		float sum = mPtr[0] * vPtr[0];
		for ( j = 1; j < numRows; j++ ) {
			mPtr += numColumns;
			sum += mPtr[0] * vPtr[j];
		}
		dstPtr[i] -= sum;
	}
#endif
}

SGF_INLINE_FORCED void CMatrizXD::Multiply( CMatrizXD &dst, const CMatrizXD &a ) const {
#ifdef MATX_SIMD
	SIMDProcessor->MatX_MultiplyMatX( dst, *this, a );
#else
	int i, j, k, l, n;
	float *dstPtr;
	const float *m1Ptr, *m2Ptr;
	double sum;

	assert( numColumns == a.numRows );

	dstPtr = dst.ToFloatPtr();
	m1Ptr = ToFloatPtr();
	m2Ptr = a.ToFloatPtr();
	k = numRows;
	l = a.GetNumColumns();

	for ( i = 0; i < k; i++ ) {
		for ( j = 0; j < l; j++ ) {
			m2Ptr = a.ToFloatPtr() + j;
			sum = m1Ptr[0] * m2Ptr[0];
			for ( n = 1; n < numColumns; n++ ) {
				m2Ptr += l;
				sum += m1Ptr[n] * m2Ptr[0];
			}
			*dstPtr++ = sum;
		}
		m1Ptr += numColumns;
	}
#endif
}

SGF_INLINE_FORCED void CMatrizXD::TransposeMultiply( CMatrizXD &dst, const CMatrizXD &a ) const {
#ifdef MATX_SIMD
	SIMDProcessor->MatX_TransposeMultiplyMatX( dst, *this, a );
#else
	int i, j, k, l, n;
	float *dstPtr;
	const float *m1Ptr, *m2Ptr;
	double sum;

	assert( numRows == a.numRows );

	dstPtr = dst.ToFloatPtr();
	m1Ptr = ToFloatPtr();
	k = numColumns;
	l = a.numColumns;

	for ( i = 0; i < k; i++ ) {
		for ( j = 0; j < l; j++ ) {
			m1Ptr = ToFloatPtr() + i;
			m2Ptr = a.ToFloatPtr() + j;
			sum = m1Ptr[0] * m2Ptr[0];
			for ( n = 1; n < numRows; n++ ) {
				m1Ptr += numColumns;
				m2Ptr += a.numColumns;
				sum += m1Ptr[0] * m2Ptr[0];
			}
			*dstPtr++ = sum;
		}
	}
#endif
}

SGF_INLINE_FORCED int CMatrizXD::GetDimension() const {
	return numRows * numColumns;
}

SGF_INLINE_FORCED const CVector6D &CMatrizXD::SubVec6( int row ) const {
	assert( numColumns >= 6 && row >= 0 && row < numRows );
	return *reinterpret_cast<const CVector6D *>(mat + row * numColumns);
}

SGF_INLINE_FORCED CVector6D &CMatrizXD::SubVec6( int row ) {
	assert( numColumns >= 6 && row >= 0 && row < numRows );
	return *reinterpret_cast<CVector6D *>(mat + row * numColumns);
}

SGF_INLINE_FORCED const CVectorXD CMatrizXD::SubVecX( int row ) const {
	CVectorXD v;
	assert( row >= 0 && row < numRows );
	v.SetData( numColumns, mat + row * numColumns );
	return v;
}

SGF_INLINE_FORCED CVectorXD CMatrizXD::SubVecX( int row ) {
	CVectorXD v;
	assert( row >= 0 && row < numRows );
	v.SetData( numColumns, mat + row * numColumns );
	return v;
}

SGF_INLINE_FORCED const float *CMatrizXD::ToFloatPtr() const {
	return mat;
}

SGF_INLINE_FORCED float *CMatrizXD::ToFloatPtr() {
	return mat;
}
} //end SGF
#endif /* !__MATH_MATRIX_H__ */
