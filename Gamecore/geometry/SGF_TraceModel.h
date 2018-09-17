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

#ifndef __TRACEMODEL_H__
#define __TRACEMODEL_H__

#include "../SGF_Config.h"
#include "../math/SGF_Vector.h"
#include "../gui/SGF_BoundBox.h"


namespace SGF {

/*
===============================================================================

	A trace model is an arbitrary polygonal model which is used by the
	collision detection system to find collisions, contacts or the contents
	of a volume. For collision detection speed reasons the number of vertices
	and edges are limited. The trace model can have any shape. However convex
	models are usually preferred.

===============================================================================
*/

class CVector3D;
class CMatriz3D;
namespace Gui {
class CBoundBox;
}

// trace model type
typedef enum {
	TRM_INVALID,		// invalid trm
	TRM_BOX,			// box
	TRM_OCTAHEDRON,		// octahedron
	TRM_DODECAHEDRON,	// dodecahedron
	TRM_CYLINDER,		// cylinder approximation
	TRM_CONE,			// cone approximation
	TRM_BONE,			// two tetrahedrons attached to each other
	TRM_POLYGON,		// arbitrary convex polygon
	TRM_POLYGONVOLUME,	// volume for arbitrary convex polygon
	TRM_CUSTOM			// loaded from map model or ASE/LWO
} traceModel_t;

// these are bit cache limits
#define MAX_TRACEMODEL_VERTS		32
#define MAX_TRACEMODEL_EDGES		32
#define MAX_TRACEMODEL_POLYS		16
#define MAX_TRACEMODEL_POLYEDGES	16

typedef CVector3D traceModelVert_t;

typedef struct {
	int					v[2];
	CVector3D				normal;
} traceModelEdge_t;

typedef struct {
	CVector3D				normal;
	float				dist;
	Gui::CBoundBox			bounds;
	int					numEdges;
	int					edges[MAX_TRACEMODEL_POLYEDGES];
} traceModelPoly_t;

class idTraceModel {

public:
	traceModel_t		type;
	int					numVerts;
	traceModelVert_t	verts[MAX_TRACEMODEL_VERTS];
	int					numEdges;
	traceModelEdge_t	edges[MAX_TRACEMODEL_EDGES+1];
	int					numPolys;
	traceModelPoly_t	polys[MAX_TRACEMODEL_POLYS];
	CVector3D				offset;			// offset to center of model
	Gui::CBoundBox			bounds;			// bounds of model
	bool				isConvex;		// true when model is convex

public:
						idTraceModel( void );
						// axial bounding box
						idTraceModel( const Gui::CBoundBox &boxBounds );
						// cylinder approximation
						idTraceModel( const Gui::CBoundBox &cylBounds, const int numSides );
						// bone
						idTraceModel( const float length, const float width );

						// axial box
	void				SetupBox( const Gui::CBoundBox &boxBounds );
	void				SetupBox( const float size );
						// octahedron
	void				SetupOctahedron( const Gui::CBoundBox &octBounds );
	void				SetupOctahedron( const float size );
						// dodecahedron
	void				SetupDodecahedron( const Gui::CBoundBox &dodBounds );
	void				SetupDodecahedron( const float size );
						// cylinder approximation
	void				SetupCylinder( const Gui::CBoundBox &cylBounds, const int numSides );
	void				SetupCylinder( const float height, const float width, const int numSides );
						// cone approximation
	void				SetupCone( const Gui::CBoundBox &coneBounds, const int numSides );
	void				SetupCone( const float height, const float width, const int numSides );
						// two tetrahedrons attached to each other
	void				SetupBone( const float length, const float width );
						// arbitrary convex polygon
	void				SetupPolygon( const CVector3D *v, const int count );
//s	void				SetupPolygon( const idWinding &w );
						// generate edge normals
	int					GenerateEdgeNormals( void );
						// translate the trm
	void				Translate( const CVector3D &translation );
						// rotate the trm
	void				Rotate( const CMatriz3D &rotation );
						// shrink the model m units on all sides
	void				Shrink( const float m );
						// compare
	bool				Compare( const idTraceModel &trm ) const;
	bool				operator==(	const idTraceModel &trm ) const;
	bool				operator!=(	const idTraceModel &trm ) const;
						// get the area of one of the polygons
	float				GetPolygonArea( int polyNum ) const;
						// get the silhouette edges
	int					GetProjectionSilhouetteEdges( const CVector3D &projectionOrigin, int silEdges[MAX_TRACEMODEL_EDGES] ) const;
	int					GetParallelProjectionSilhouetteEdges( const CVector3D &projectionDir, int silEdges[MAX_TRACEMODEL_EDGES] ) const;
						// calculate mass properties assuming an uniform density
	void				GetMassProperties( const float density, float &mass, CVector3D &centerOfMass, CMatriz3D &inertiaTensor ) const;

private:
	void				InitBox( void );
	void				InitOctahedron( void );
	void				InitDodecahedron( void );
	void				InitBone( void );

	void				ProjectionIntegrals( int polyNum, int a, int b, struct projectionIntegrals_s &integrals ) const;
	void				PolygonIntegrals( int polyNum, int a, int b, int c, struct polygonIntegrals_s &integrals ) const;
	void				VolumeIntegrals( struct volumeIntegrals_s &integrals ) const;
	void				VolumeFromPolygon( idTraceModel &trm, float thickness ) const;
	int					GetOrderedSilhouetteEdges( const int edgeIsSilEdge[MAX_TRACEMODEL_EDGES+1], int silEdges[MAX_TRACEMODEL_EDGES] ) const;
};


SGF_INLINE_FORCED idTraceModel::idTraceModel( void ) {
	type = TRM_INVALID;
	numVerts = numEdges = numPolys = 0;
	bounds.Zero();
}

SGF_INLINE_FORCED idTraceModel::idTraceModel( const Gui::CBoundBox &boxBounds ) {
	InitBox();
	SetupBox( boxBounds );
}

SGF_INLINE_FORCED idTraceModel::idTraceModel( const Gui::CBoundBox &cylBounds, const int numSides ) {
	SetupCylinder( cylBounds, numSides );
}

SGF_INLINE_FORCED idTraceModel::idTraceModel( const float length, const float width ) {
	InitBone();
	SetupBone( length, width );
}

SGF_INLINE_FORCED bool idTraceModel::operator==( const idTraceModel &trm ) const {
	return Compare( trm );
}

SGF_INLINE_FORCED bool idTraceModel::operator!=( const idTraceModel &trm ) const {
	return !Compare( trm );
}
} //end SGF
#endif /* !__TRACEMODEL_H__ */

