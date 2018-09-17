/*
  SGF - Salvat Game Fabric  (https://sourceforge.net/projects/sgfabric/)
  Copyright (C) 2010-2011 Salvatore Giannotta Filho <a_materasu@hotmail.com>

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

#ifndef __MATH_PLANE_H__
#define __MATH_PLANE_H__

/*
===============================================================================

	3D plane with equation: a * x + b * y + c * z + d = 0

===============================================================================
*/


class CVector3D;
class CMatriz3D;

#define	ON_EPSILON					0.1f
#define DEGENERATE_DIST_EPSILON		1e-4f

#define	SIDE_FRONT					0
#define	SIDE_BACK					1
#define	SIDE_ON						2
#define	SIDE_CROSS					3

// plane sides
#define PLANESIDE_FRONT				0
#define PLANESIDE_BACK				1
#define PLANESIDE_ON				2
#define PLANESIDE_CROSS				3

// plane types
#define PLANETYPE_X					0
#define PLANETYPE_Y					1
#define PLANETYPE_Z					2
#define PLANETYPE_NEGX				3
#define PLANETYPE_NEGY				4
#define PLANETYPE_NEGZ				5
#define PLANETYPE_TRUEAXIAL			6	// all types < 6 are true axial planes
#define PLANETYPE_ZEROX				6
#define PLANETYPE_ZEROY				7
#define PLANETYPE_ZEROZ				8
#define PLANETYPE_NONAXIAL			9

class CPlane {
public:
					CPlane( void );
					CPlane( float a, float b, float c, float d );
					CPlane( const CVector3D &normal, const float dist );

	float			operator[]( int index ) const;
	float &			operator[]( int index );
	CPlane			operator-() const;						// flips plane
	CPlane &		operator=( const CVector3D &v );			// sets normal and sets CPlane::d to zero
	CPlane			operator+( const CPlane &p ) const;	// add plane equations
	CPlane			operator-( const CPlane &p ) const;	// subtract plane equations
	CPlane &		operator*=( const CMatriz3D &m );			// Normal() *= m

	bool			Compare( const CPlane &p ) const;						// exact compare, no epsilon
	bool			Compare( const CPlane &p, const float epsilon ) const;	// compare with epsilon
	bool			Compare( const CPlane &p, const float normalEps, const float distEps ) const;	// compare with epsilon
	bool			operator==(	const CPlane &p ) const;					// exact compare, no epsilon
	bool			operator!=(	const CPlane &p ) const;					// exact compare, no epsilon

	void			Zero( void );							// zero plane
	void			SetNormal( const CVector3D &normal );		// sets the normal
	const CVector3D &	Normal( void ) const;					// reference to const normal
	CVector3D &		Normal( void );							// reference to normal
	float			Normalize( bool fixDegenerate = true );	// only normalizes the plane normal, does not adjust d
	bool			FixDegenerateNormal( void );			// fix degenerate normal
	bool			FixDegeneracies( float distEpsilon );	// fix degenerate normal and dist
	float			Dist( void ) const;						// returns: -d
	void			SetDist( const float dist );			// sets: d = -dist
	int				Type( void ) const;						// returns plane type

	bool			FromPoints( const CVector3D &p1, const CVector3D &p2, const CVector3D &p3, bool fixDegenerate = true );
	bool			FromVecs( const CVector3D &dir1, const CVector3D &dir2, const CVector3D &p, bool fixDegenerate = true );
	void			FitThroughPoint( const CVector3D &p );	// assumes normal is valid
	bool			HeightFit( const CVector3D *points, const int numPoints );
	CPlane			Translate( const CVector3D &translation ) const;
	CPlane &		TranslateSelf( const CVector3D &translation );
	CPlane			Rotate( const CVector3D &origin, const CMatriz3D &axis ) const;
	CPlane &		RotateSelf( const CVector3D &origin, const CMatriz3D &axis );

	float			Distance( const CVector3D &v ) const;
	int				Side( const CVector3D &v, const float epsilon = 0.0f ) const;

	bool			LineIntersection( const CVector3D &start, const CVector3D &end ) const;
					// intersection point is start + dir * scale
	bool			RayIntersection( const CVector3D &start, const CVector3D &dir, float &scale ) const;
	bool			PlaneIntersection( const CPlane &plane, CVector3D &start, CVector3D &dir ) const;

	int				GetDimension( void ) const;

	const CVector4D &	ToVec4( void ) const;
	CVector4D &		ToVec4( void );
	const float *	ToFloatPtr( void ) const;
	float *			ToFloatPtr( void );
	const char *	ToString( int precision = 2 ) const;

private:
	float			a;
	float			b;
	float			c;
	float			d;
};

extern CPlane plane_origin;
#define plane_zero plane_origin

SGF_INLINE_FORCED CPlane::CPlane( void ) {
}

SGF_INLINE_FORCED CPlane::CPlane( float a, float b, float c, float d ) {
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
}

SGF_INLINE_FORCED CPlane::CPlane( const CVector3D &normal, const float dist ) {
	this->a = normal.x;
	this->b = normal.y;
	this->c = normal.z;
	this->d = -dist;
}

SGF_INLINE_FORCED float CPlane::operator[]( int index ) const {
	return ( &a )[ index ];
}

SGF_INLINE_FORCED float& CPlane::operator[]( int index ) {
	return ( &a )[ index ];
}

SGF_INLINE_FORCED CPlane CPlane::operator-() const {
	return CPlane( -a, -b, -c, -d );
}

SGF_INLINE_FORCED CPlane &CPlane::operator=( const CVector3D &v ) { 
	a = v.x;
	b = v.y;
	c = v.z;
	d = 0;
	return *this;
}

SGF_INLINE_FORCED CPlane CPlane::operator+( const CPlane &p ) const {
	return CPlane( a + p.a, b + p.b, c + p.c, d + p.d );
}

SGF_INLINE_FORCED CPlane CPlane::operator-( const CPlane &p ) const {
	return CPlane( a - p.a, b - p.b, c - p.c, d - p.d );
}

SGF_INLINE_FORCED CPlane &CPlane::operator*=( const CMatriz3D &m ) {
	Normal() *= m;
	return *this;
}

SGF_INLINE_FORCED bool CPlane::Compare( const CPlane &p ) const {
	return ( a == p.a && b == p.b && c == p.c && d == p.d );
}

SGF_INLINE_FORCED bool CPlane::Compare( const CPlane &p, const float epsilon ) const {
	if ( CMath::Fabs( a - p.a ) > epsilon ) {
		return false;
	}
			
	if ( CMath::Fabs( b - p.b ) > epsilon ) {
		return false;
	}

	if ( CMath::Fabs( c - p.c ) > epsilon ) {
		return false;
	}

	if ( CMath::Fabs( d - p.d ) > epsilon ) {
		return false;
	}

	return true;
}

SGF_INLINE_FORCED bool CPlane::Compare( const CPlane &p, const float normalEps, const float distEps ) const {
	if ( CMath::Fabs( d - p.d ) > distEps ) {
		return false;
	}
	if ( !Normal().Compare( p.Normal(), normalEps ) ) {
		return false;
	}
	return true;
}

SGF_INLINE_FORCED bool CPlane::operator==( const CPlane &p ) const {
	return Compare( p );
}

SGF_INLINE_FORCED bool CPlane::operator!=( const CPlane &p ) const {
	return !Compare( p );
}

SGF_INLINE_FORCED void CPlane::Zero( void ) {
	a = b = c = d = 0.0f;
}

SGF_INLINE_FORCED void CPlane::SetNormal( const CVector3D &normal ) {
	a = normal.x;
	b = normal.y;
	c = normal.z;
}

SGF_INLINE_FORCED const CVector3D &CPlane::Normal( void ) const {
	return *reinterpret_cast<const CVector3D *>(&a);
}

SGF_INLINE_FORCED CVector3D &CPlane::Normal( void ) {
	return *reinterpret_cast<CVector3D *>(&a);
}

SGF_INLINE_FORCED float CPlane::Normalize( bool fixDegenerate ) {
	float length = reinterpret_cast<CVector3D *>(&a)->Normalize();

	if ( fixDegenerate ) {
		FixDegenerateNormal();
	}
	return length;
}

SGF_INLINE_FORCED bool CPlane::FixDegenerateNormal( void ) {
	return Normal().FixDegenerateNormal();
}

SGF_INLINE_FORCED bool CPlane::FixDegeneracies( float distEpsilon ) {
	bool fixedNormal = FixDegenerateNormal();
	// only fix dist if the normal was degenerate
	if ( fixedNormal ) {
		if ( CMath::Fabs( d - CMath::Rint( d ) ) < distEpsilon ) {
			d = CMath::Rint( d );
		}
	}
	return fixedNormal;
}

SGF_INLINE_FORCED float CPlane::Dist( void ) const {
	return -d;
}

SGF_INLINE_FORCED void CPlane::SetDist( const float dist ) {
	d = -dist;
}

SGF_INLINE_FORCED bool CPlane::FromPoints( const CVector3D &p1, const CVector3D &p2, const CVector3D &p3, bool fixDegenerate ) {
	Normal() = (p1 - p2).Cross( p3 - p2 );
	if ( Normalize( fixDegenerate ) == 0.0f ) {
		return false;
	}
	d = -( Normal() * p2 );
	return true;
}

SGF_INLINE_FORCED bool CPlane::FromVecs( const CVector3D &dir1, const CVector3D &dir2, const CVector3D &p, bool fixDegenerate ) {
	Normal() = dir1.Cross( dir2 );
	if ( Normalize( fixDegenerate ) == 0.0f ) {
		return false;
	}
	d = -( Normal() * p );
	return true;
}

SGF_INLINE_FORCED void CPlane::FitThroughPoint( const CVector3D &p ) {
	d = -( Normal() * p );
}

SGF_INLINE_FORCED CPlane CPlane::Translate( const CVector3D &translation ) const {
	return CPlane( a, b, c, d - translation * Normal() );
}

SGF_INLINE_FORCED CPlane &CPlane::TranslateSelf( const CVector3D &translation ) {
	d -= translation * Normal();
	return *this;
}

SGF_INLINE_FORCED CPlane CPlane::Rotate( const CVector3D &origin, const CMatriz3D &axis ) const {
	CPlane p;
	p.Normal() = Normal() * axis;
	p.d = d + origin * Normal() - origin * p.Normal();
	return p;
}

SGF_INLINE_FORCED CPlane &CPlane::RotateSelf( const CVector3D &origin, const CMatriz3D &axis ) {
	d += origin * Normal();
	Normal() *= axis;
	d -= origin * Normal();
	return *this;
}

SGF_INLINE_FORCED float CPlane::Distance( const CVector3D &v ) const {
	return a * v.x + b * v.y + c * v.z + d;
}

SGF_INLINE_FORCED int CPlane::Side( const CVector3D &v, const float epsilon ) const {
	float dist = Distance( v );
	if ( dist > epsilon ) {
		return PLANESIDE_FRONT;
	}
	else if ( dist < -epsilon ) {
		return PLANESIDE_BACK;
	}
	else {
		return PLANESIDE_ON;
	}
}

SGF_INLINE_FORCED bool CPlane::LineIntersection( const CVector3D &start, const CVector3D &end ) const {
	float d1, d2, fraction;

	d1 = Normal() * start + d;
	d2 = Normal() * end + d;
	if ( d1 == d2 ) {
		return false;
	}
	if ( d1 > 0.0f && d2 > 0.0f ) {
		return false;
	}
	if ( d1 < 0.0f && d2 < 0.0f ) {
		return false;
	}
	fraction = ( d1 / ( d1 - d2 ) );
	return ( fraction >= 0.0f && fraction <= 1.0f );
}

SGF_INLINE_FORCED bool CPlane::RayIntersection( const CVector3D &start, const CVector3D &dir, float &scale ) const {
	float d1, d2;

	d1 = Normal() * start + d;
	d2 = Normal() * dir;
	if ( d2 == 0.0f ) {
		return false;
	}
	scale = -( d1 / d2 );
	return true;
}

SGF_INLINE_FORCED int CPlane::GetDimension( void ) const {
	return 4;
}

SGF_INLINE_FORCED const CVector4D &CPlane::ToVec4( void ) const {
	return *reinterpret_cast<const CVector4D *>(&a);
}

SGF_INLINE_FORCED CVector4D &CPlane::ToVec4( void ) {
	return *reinterpret_cast<CVector4D *>(&a);
}

SGF_INLINE_FORCED const float *CPlane::ToFloatPtr( void ) const {
	return reinterpret_cast<const float *>(&a);
}

SGF_INLINE_FORCED float *CPlane::ToFloatPtr( void ) {
	return reinterpret_cast<float *>(&a);
}

#endif /* !__MATH_PLANE_H__ */
