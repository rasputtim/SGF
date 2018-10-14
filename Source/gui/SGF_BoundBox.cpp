/*
  SGF - Super Game Fabric  Super Game Fabric
  Copyright (C) 2010-2011 Rasputtim <raputtim@hotmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

  */

#include "gui/SGF_BoundBox.h"
#include "util/SGF_Util.h"
//#pragma hdrstop
namespace SGF {
	namespace Gui{
CBoundBox bounds_zero( vec3_zero, vec3_zero );

/*
============
CBoundBox::GetRadius
============
*/
float CBoundBox::GetRadius( void ) const {
	int		i;
	float	total, b0, b1;

	total = 0.0f;
	for ( i = 0; i < 3; i++ ) {
		b0 = (float)CMath::Fabs( b[0][i] );
		b1 = (float)CMath::Fabs( b[1][i] );
		if ( b0 > b1 ) {
			total += b0 * b0;
		} else {
			total += b1 * b1;
		}
	}
	return CMath::Sqrt( total );
}

/*
============
CBoundBox::GetRadius
============
*/
float CBoundBox::GetRadius( const CVector3D &center ) const {
	int		i;
	float	total, b0, b1;

	total = 0.0f;
	for ( i = 0; i < 3; i++ ) {
		b0 = (float)CMath::Fabs( center[i] - b[0][i] );
		b1 = (float)CMath::Fabs( b[1][i] - center[i] );
		if ( b0 > b1 ) {
			total += b0 * b0;
		} else {
			total += b1 * b1;
		}
	}
	return CMath::Sqrt( total );
}

/*
================
CBoundBox::PlaneDistance
================
*/
float CBoundBox::PlaneDistance( const CPlane &plane ) const {
	CVector3D center;
	float d1, d2;

	center = ( b[0] + b[1] ) * 0.5f;

	d1 = plane.Distance( center );
	d2 = CMath::Fabs( ( b[1][0] - center[0] ) * plane.Normal()[0] ) +
			CMath::Fabs( ( b[1][1] - center[1] ) * plane.Normal()[1] ) +
				CMath::Fabs( ( b[1][2] - center[2] ) * plane.Normal()[2] );

	if ( d1 - d2 > 0.0f ) {
		return d1 - d2;
	}
	if ( d1 + d2 < 0.0f ) {
		return d1 + d2;
	}
	return 0.0f;
}

/*
================
CBoundBox::PlaneSide
================
*/
int CBoundBox::PlaneSide( const CPlane &plane, const float epsilon ) const {
	CVector3D center;
	float d1, d2;

	center = ( b[0] + b[1] ) * 0.5f;

	d1 = plane.Distance( center );
	d2 = CMath::Fabs( ( b[1][0] - center[0] ) * plane.Normal()[0] ) +
			CMath::Fabs( ( b[1][1] - center[1] ) * plane.Normal()[1] ) +
				CMath::Fabs( ( b[1][2] - center[2] ) * plane.Normal()[2] );

	if ( d1 - d2 > epsilon ) {
		return PLANESIDE_FRONT;
	}
	if ( d1 + d2 < -epsilon ) {
		return PLANESIDE_BACK;
	}
	return PLANESIDE_CROSS;
}

/*
============
CBoundBox::LineIntersection

  Returns true if the line intersects the bounds between the start and end point.
============
*/
bool CBoundBox::LineIntersection( const CVector3D &start, const CVector3D &end ) const {
    float ld[3];
	CVector3D center = ( b[0] + b[1] ) * 0.5f;
	CVector3D extents = b[1] - center;
    CVector3D lineDir = 0.5f * ( end - start );
    CVector3D lineCenter = start + lineDir;
    CVector3D dir = lineCenter - center;

    ld[0] = CMath::Fabs( lineDir[0] );
	if ( CMath::Fabs( dir[0] ) > extents[0] + ld[0] ) {
        return false;
	}

    ld[1] = CMath::Fabs( lineDir[1] );
	if ( CMath::Fabs( dir[1] ) > extents[1] + ld[1] ) {
        return false;
	}

    ld[2] = CMath::Fabs( lineDir[2] );
	if ( CMath::Fabs( dir[2] ) > extents[2] + ld[2] ) {
        return false;
	}

    CVector3D cross = lineDir.Cross( dir );

	if ( CMath::Fabs( cross[0] ) > extents[1] * ld[2] + extents[2] * ld[1] ) {
        return false;
	}

	if ( CMath::Fabs( cross[1] ) > extents[0] * ld[2] + extents[2] * ld[0] ) {
        return false;
	}

	if ( CMath::Fabs( cross[2] ) > extents[0] * ld[1] + extents[1] * ld[0] ) {
        return false;
	}

    return true;
}

/*
============
CBoundBox::RayIntersection

  Returns true if the ray intersects the bounds.
  The ray can intersect the bounds in both directions from the start point.
  If start is inside the bounds it is considered an intersection with scale = 0
============
*/
bool CBoundBox::RayIntersection( const CVector3D &start, const CVector3D &dir, float &scale ) const {
	int i, ax0, ax1, ax2, side, inside;
	float f;
	CVector3D hit;

	ax0 = -1;
	inside = 0;
	for ( i = 0; i < 3; i++ ) {
		if ( start[i] < b[0][i] ) {
			side = 0;
		}
		else if ( start[i] > b[1][i] ) {
			side = 1;
		}
		else {
			inside++;
			continue;
		}
		if ( dir[i] == 0.0f ) {
			continue;
		}
		f = ( start[i] - b[side][i] );
		if ( ax0 < 0 || CMath::Fabs( f ) > CMath::Fabs( scale * dir[i] ) ) {
			scale = - ( f / dir[i] );
			ax0 = i;
		}
	}

	if ( ax0 < 0 ) {
		scale = 0.0f;
		// return true if the start point is inside the bounds
		return ( inside == 3 );
	}

	ax1 = (ax0+1)%3;
	ax2 = (ax0+2)%3;
	hit[ax1] = start[ax1] + scale * dir[ax1];
	hit[ax2] = start[ax2] + scale * dir[ax2];

	return ( hit[ax1] >= b[0][ax1] && hit[ax1] <= b[1][ax1] &&
				hit[ax2] >= b[0][ax2] && hit[ax2] <= b[1][ax2] );
}

/*
============
CBoundBox::FromTransformedBounds
============
*/
void CBoundBox::FromTransformedBounds( const CBoundBox &bounds, const CVector3D &origin, const CMatriz3D &axis ) {
	int i;
	CVector3D center, extents, rotatedExtents;

	center = (bounds[0] + bounds[1]) * 0.5f;
	extents = bounds[1] - center;

	for ( i = 0; i < 3; i++ ) {
		rotatedExtents[i] = CMath::Fabs( extents[0] * axis[0][i] ) +
							CMath::Fabs( extents[1] * axis[1][i] ) +
							CMath::Fabs( extents[2] * axis[2][i] );
	}

	center = origin + center * axis;
	b[0] = center - rotatedExtents;
	b[1] = center + rotatedExtents;
}

/*
============
CBoundBox::FromPoints

  Most tight bounds for a point set.
============
*/

void CBoundBox::FromPoints( const CVector3D *points, const int numPoints ) {
#ifndef ANDROID
	SIMDProcessor->MinMax( b[0], b[1], points, numPoints );
#endif
}

/*
============
CBoundBox::FromPointTranslation

  Most tight bounds for the translational movement of the given point.
============
*/
void CBoundBox::FromPointTranslation( const CVector3D &point, const CVector3D &translation ) {
	int i;

	for ( i = 0; i < 3; i++ ) {
		if ( translation[i] < 0.0f ) {
			b[0][i] = point[i] + translation[i];
			b[1][i] = point[i];
		}
		else {
			b[0][i] = point[i];
			b[1][i] = point[i] + translation[i];
		}
	}
}

/*
============
CBoundBox::FromBoundsTranslation

  Most tight bounds for the translational movement of the given bounds.
============
*/
void CBoundBox::FromBoundsTranslation( const CBoundBox &bounds, const CVector3D &origin, const CMatriz3D &axis, const CVector3D &translation ) {
	int i;

	if ( axis.IsRotated() ) {
		FromTransformedBounds( bounds, origin, axis );
	}
	else {
		b[0] = bounds[0] + origin;
		b[1] = bounds[1] + origin;
	}
	for ( i = 0; i < 3; i++ ) {
		if ( translation[i] < 0.0f ) {
			b[0][i] += translation[i];
		}
		else {
			b[1][i] += translation[i];
		}
	}
}

/*
================
BoundsForPointRotation

  only for rotations < 180 degrees
================
*/
CBoundBox BoundsForPointRotation( const CVector3D &start, const CRotation &rotation ) {
	int i;
	float radiusSqr;
	CVector3D v1, v2;
	CVector3D origin, axis, end;
	CBoundBox bounds;

	end = start * rotation;
	axis = rotation.GetVec();
	origin = rotation.GetOrigin() + axis * ( axis * ( start - rotation.GetOrigin() ) );
	radiusSqr = ( start - origin ).LengthSqr();
	v1 = ( start - origin ).Cross( axis );
	v2 = ( end - origin ).Cross( axis );

	for ( i = 0; i < 3; i++ ) {
		// if the derivative changes sign along this axis during the rotation from start to end
		if ( ( v1[i] > 0.0f && v2[i] < 0.0f ) || ( v1[i] < 0.0f && v2[i] > 0.0f ) ) {
			if ( ( 0.5f * (start[i] + end[i]) - origin[i] ) > 0.0f ) {
				bounds[0][i] = MIN( start[i], end[i] );
				bounds[1][i] = origin[i] + CMath::Sqrt( radiusSqr * ( 1.0f - axis[i] * axis[i] ) );
			}
			else {
				bounds[0][i] = origin[i] - CMath::Sqrt( radiusSqr * ( 1.0f - axis[i] * axis[i] ) );
				bounds[1][i] = MAX( start[i], end[i] );
			}
		}
		else if ( start[i] > end[i] ) {
			bounds[0][i] = end[i];
			bounds[1][i] = start[i];
		}
		else {
			bounds[0][i] = start[i];
			bounds[1][i] = end[i];
		}
	}

	return bounds;
}

/*
============
CBoundBox::FromPointRotation

  Most tight bounds for the rotational movement of the given point.
============
*/
void CBoundBox::FromPointRotation( const CVector3D &point, const CRotation &rotation ) {
	float radius;

	if ( CMath::Fabs( rotation.GetAngle() ) < 180.0f ) {
		(*this) = BoundsForPointRotation( point, rotation );
	}
	else {

		radius = ( point - rotation.GetOrigin() ).Length();

		// FIXME: these bounds are usually way larger
		b[0].Set( -radius, -radius, -radius );
		b[1].Set( radius, radius, radius );
	}
}

/*
============
CBoundBox::FromBoundsRotation

  Most tight bounds for the rotational movement of the given bounds.
============
*/
void CBoundBox::FromBoundsRotation( const CBoundBox &bounds, const CVector3D &origin, const CMatriz3D &axis, const CRotation &rotation ) {
	int i;
	float radius;
	CVector3D point;
	CBoundBox rBounds;

	if ( CMath::Fabs( rotation.GetAngle() ) < 180.0f ) {

		(*this) = BoundsForPointRotation( bounds[0] * axis + origin, rotation );
		for ( i = 1; i < 8; i++ ) {
			point[0] = bounds[(i^(i>>1))&1][0];
			point[1] = bounds[(i>>1)&1][1];
			point[2] = bounds[(i>>2)&1][2];
			(*this) += BoundsForPointRotation( point * axis + origin, rotation );
		}
	}
	else {

		point = (bounds[1] - bounds[0]) * 0.5f;
		radius = (bounds[1] - point).Length() + (point - rotation.GetOrigin()).Length();

		// FIXME: these bounds are usually way larger
		b[0].Set( -radius, -radius, -radius );
		b[1].Set( radius, radius, radius );
	}
}

/*
============
CBoundBox::ToPoints
============
*/
void CBoundBox::ToPoints( CVector3D points[8] ) const {
	for ( int i = 0; i < 8; i++ ) {
		points[i][0] = b[(i^(i>>1))&1][0];
		points[i][1] = b[(i>>1)&1][1];
		points[i][2] = b[(i>>2)&1][2];
	}
}
} // end Gui
} // end SGF