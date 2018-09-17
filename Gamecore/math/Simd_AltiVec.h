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

#ifndef __MATH_SIMD_ALTIVEC_H__
#define __MATH_SIMD_ALTIVEC_H__
#include "../SGF_Config.h"
namespace SGF {
/*
===============================================================================

	AltiVec implementation of CSIMDProcessor

===============================================================================
*/

// Defines for enabling parts of the library

// Turns on/off the simple math routines (add, sub, div, etc)
#define ENABLE_SIMPLE_MATH	

// Turns on/off the dot routines
#define ENABLE_DOT

// Turns on/off the compare routines
#define ENABLE_COMPARES

// The MinMax routines introduce a couple of bugs. In the bathroom of the alphalabs2 map, the
// wrong surface appears in the mirror at times. It also introduces a noticable delay when map
// data is loaded such as going through doors.
// Turns on/off MinMax routines
//#define ENABLE_MINMAX

// Turns on/off Clamp routines
#define ENABLE_CLAMP

// Turns on/off XXX16 routines
#define ENABLE_16ROUTINES

// Turns on/off LowerTriangularSolve, LowerTriangularSolveTranspose, and MatX_LDLTFactor
#define ENABLE_LOWER_TRIANGULAR

// Turns on/off TracePointCull, DecalPointCull, and OverlayPoint
// The Enable_Cull routines breaks the g_decals functionality, DecalPointCull is
// the likely suspect. Bullet holes do not appear on the walls when this optimization
// is enabled. 
//#define ENABLE_CULL

// Turns on/off DeriveTriPlanes, DeriveTangents, DeriveUnsmoothedTangents, NormalizeTangents
#define ENABLE_DERIVE

// Turns on/off CreateTextureSpaceLightVectors, CreateShadowCache, CreateVertexProgramShadowCache
#define ENABLE_CREATE

// Turns on/off the sound routines
#define ENABLE_SOUND_ROUTINES

// Turns on/off the stuff that isn't on elsewhere
// Currently: BlendJoints, TransformJoints, UntransformJoints, ConvertJointQuatsToJointMats, and
// ConvertJointMatsToJointQuats
#define LIVE_VICARIOUSLY

// This assumes that the dest (and mixBuffer) array to the sound functions is aligned. If this is not true, we take a large
// performance hit from having to do unaligned stores
//#define SOUND_DEST_ALIGNED

// This assumes that the vertexCache array to CreateShadowCache and CreateVertexProgramShadowCache is aligned. If it's not,
// then we take a big performance hit from unaligned stores.
//#define VERTEXCACHE_ALIGNED

// This turns on support for PPC intrinsics in the SIMD_AltiVec.cpp file. Right now it's only used for frsqrte. GCC 
// supports these intrinsics but XLC does not.
//#define PPC_INTRINSICS

// This assumes that the CDrawVertice array that is used in DeriveUnsmoothedTangents is aligned. If its not aligned,
// then we don't get any speedup
//#define DERIVE_UNSMOOTH_DRAWVERT_ALIGNED

// Disable DRAWVERT_PADDED since we disabled the ENABLE_CULL optimizations and the default
// implementation does not allow for the extra padding.
// This assumes that CDrawVertice has been padded by 4 bytes so that xyz always starts at an aligned
// address
//#define DRAWVERT_PADDED

class idSIMD_AltiVec : public CSIMD_Generic {
#if defined(MACOS_X) && defined(__ppc__)
public:

	virtual const char * VPCALL GetName() const;

#ifdef ENABLE_SIMPLE_MATH
	// Basic math, works for both aligned and unaligned data
	virtual void VPCALL Add( float *dst, const float constant, const float *src, const int count );
    virtual void VPCALL Add( float *dst, const float *src0, const float *src1, const int count );
	virtual void VPCALL Sub( float *dst, const float constant, const float *src, const int count );
	virtual void VPCALL Sub( float *dst, const float *src0, const float *src1, const int count );
 	virtual void VPCALL Mul( float *dst, const float constant, const float *src, const int count);
	virtual void VPCALL Mul( float *dst, const float *src0, const float *src1, const int count );
	virtual void VPCALL Div( float *dst, const float constant, const float *divisor, const int count );
	virtual void VPCALL Div( float *dst, const float *src0, const float *src1, const int count ); 
	virtual void VPCALL MulAdd( float *dst, const float constant, const float *src, const int count );
	virtual void VPCALL MulAdd( float *dst, const float *src0, const float *src1, const int count );
	virtual void VPCALL MulSub( float *dst, const float constant, const float *src, const int count );
	virtual void VPCALL MulSub( float *dst, const float *src0, const float *src1, const int count ); 
#endif

#ifdef ENABLE_DOT
	// Dot products, expects data structures in contiguous memory
	virtual void VPCALL Dot( float *dst,			const CVector3D &constant,	const CVector3D *src,		const int count );
	virtual void VPCALL Dot( float *dst,			const CVector3D &constant,	const CPlane *src,		const int count );
	virtual void VPCALL Dot( float *dst,			const CVector3D &constant,	const CDrawVertice *src,	const int count );
	virtual void VPCALL Dot( float *dst,			const CPlane &constant,const CVector3D *src,		const int count );
	virtual void VPCALL Dot( float *dst,			const CPlane &constant,const CPlane *src,		const int count );
	virtual void VPCALL Dot( float *dst,			const CPlane &constant,const CDrawVertice *src,	const int count );
	virtual void VPCALL Dot( float *dst,			const CVector3D *src0,		const CVector3D *src1,		const int count );
	virtual void VPCALL Dot( float &dot,			const float *src1,		const float *src2,		const int count );
#endif

#ifdef ENABLE_COMPARES
	// Comparisons, works for both aligned and unaligned data
	virtual void VPCALL CmpGT( SGF_Byte *dst,			const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpGT( SGF_Byte *dst,			const SGF_Byte bitNum,		const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpGE( SGF_Byte *dst,			const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpGE( SGF_Byte *dst,			const SGF_Byte bitNum,		const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpLT( SGF_Byte *dst,			const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpLT( SGF_Byte *dst,			const SGF_Byte bitNum,		const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpLE( SGF_Byte *dst,			const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpLE( SGF_Byte *dst,			const SGF_Byte bitNum,		const float *src0,		const float constant,	const int count );
#endif

#ifdef ENABLE_MINMAX	
	// Min/Max. Expects data structures in contiguous memory
	virtual void VPCALL MinMax( float &min,			float &max,				const float *src,		const int count );
	virtual	void VPCALL MinMax( CVector2D &min,		CVector2D &max,			const CVector2D *src,		const int count );
	virtual void VPCALL MinMax( CVector3D &min,		CVector3D &max,			const CVector3D *src,		const int count );
	virtual	void VPCALL MinMax( CVector3D &min,		CVector3D &max,			const CDrawVertice *src,	const int count );
	virtual	void VPCALL MinMax( CVector3D &min,		CVector3D &max,			const CDrawVertice *src,	const int *indexes,		const int count );
#endif

#ifdef ENABLE_CLAMP
	// Clamp operations. Works for both aligned and unaligned data
	virtual void VPCALL Clamp( float *dst,			const float *src,		const float min,		const float max,		const int count );
	virtual void VPCALL ClampMin( float *dst,		const float *src,		const float min,		const int count );
	virtual void VPCALL ClampMax( float *dst,		const float *src,		const float max,		const int count );
#endif

    // These are already using memcpy and memset functions. Leaving default implementation
//	virtual void VPCALL Memcpy( void *dst,			const void *src,		const int count );
//	virtual void VPCALL Memset( void *dst,			const int val,			const int count );

#ifdef ENABLE_16ROUTINES
	// Operations that expect 16-SGF_Byte aligned data and 16-SGF_Byte padded memory (with zeros), generally faster
	virtual void VPCALL Zero16( float *dst,			const int count );
	virtual void VPCALL Negate16( float *dst,		const int count );
	virtual void VPCALL Copy16( float *dst,			const float *src,		const int count );
	virtual void VPCALL Add16( float *dst,			const float *src1,		const float *src2,		const int count );
	virtual void VPCALL Sub16( float *dst,			const float *src1,		const float *src2,		const int count );
	virtual void VPCALL Mul16( float *dst,			const float *src1,		const float constant,	const int count );
	virtual void VPCALL AddAssign16( float *dst,	const float *src,		const int count );
	virtual void VPCALL SubAssign16( float *dst,	const float *src,		const int count );
	virtual void VPCALL MulAssign16( float *dst,	const float constant,	const int count );
#endif

//  Most of these deal with tiny matrices or vectors, generally not worth altivec'ing since
//  the scalar code is already really fast

//	virtual void VPCALL MatX_MultiplyVecX( CVectorXD &dst, const CMatrizXD &mat, const CVectorXD &vec );
//	virtual void VPCALL MatX_MultiplyAddVecX( CVectorXD &dst, const CMatrizXD &mat, const CVectorXD &vec );
//	virtual void VPCALL MatX_MultiplySubVecX( CVectorXD &dst, const CMatrizXD &mat, const CVectorXD &vec );
//	virtual void VPCALL MatX_TransposeMultiplyVecX( CVectorXD &dst, const CMatrizXD &mat, const CVectorXD &vec );
//	virtual void VPCALL MatX_TransposeMultiplyAddVecX( CVectorXD &dst, const CMatrizXD &mat, const CVectorXD &vec );
//	virtual void VPCALL MatX_TransposeMultiplySubVecX( CVectorXD &dst, const CMatrizXD &mat, const CVectorXD &vec );
//	virtual void VPCALL MatX_MultiplyMatX( CMatrizXD &dst, const CMatrizXD &m1, const CMatrizXD &m2 );
//	virtual void VPCALL MatX_TransposeMultiplyMatX( CMatrizXD &dst, const CMatrizXD &m1, const CMatrizXD &m2 );

#ifdef ENABLE_LOWER_TRIANGULAR
	virtual void VPCALL MatX_LowerTriangularSolve( const CMatrizXD &L, float *x, const float *b, const int n, int skip = 0 );
	virtual void VPCALL MatX_LowerTriangularSolveTranspose( const CMatrizXD &L, float *x, const float *b, const int n );
	virtual bool VPCALL MatX_LDLTFactor( CMatrizXD &mat, CVectorXD &invDiag, const int n );
#endif
#ifdef LIVE_VICARIOUSLY
	virtual void VPCALL BlendJoints( CJointQuaternion *joints, const CJointQuaternion *blendJoints, const float lerp, const int *index, const int numJoints );
	virtual void VPCALL ConvertJointQuatsToJointMats( CJointMatriz *jointMats, const CJointQuaternion *jointQuats, const int numJoints );
	virtual void VPCALL ConvertJointMatsToJointQuats( CJointQuaternion *jointQuats, const CJointMatriz *jointMats, const int numJoints );
#endif

#ifdef LIVE_VICARIOUSLY
	virtual void VPCALL TransformJoints( CJointMatriz *jointMats, const int *parents, const int firstJoint, const int lastJoint );
	virtual void VPCALL UntransformJoints( CJointMatriz *jointMats, const int *parents, const int firstJoint, const int lastJoint );
	virtual void VPCALL TransformVerts( CDrawVertice *verts, const int numVerts, const CJointMatriz *joints, const CVector4D *weights, const int *index, const int numWeights );
#endif

#ifdef ENABLE_CULL
	virtual void VPCALL TracePointCull( SGF_Byte *cullBits, SGF_Byte &totalOr, const float radius, const CPlane *planes, const CDrawVertice *verts, const int numVerts );
	virtual void VPCALL DecalPointCull( SGF_Byte *cullBits, const CPlane *planes, const CDrawVertice *verts, const int numVerts );
	virtual void VPCALL OverlayPointCull( SGF_Byte *cullBits, CVector2D *texCoords, const CPlane *planes, const CDrawVertice *verts, const int numVerts );
#endif

#ifdef ENABLE_DERIVE
	virtual void VPCALL DeriveTriPlanes( CPlane *planes, const CDrawVertice *verts, const int numVerts, const int *indexes, const int numIndexes );
	virtual void VPCALL DeriveTangents( CPlane *planes, CDrawVertice *verts, const int numVerts, const int *indexes, const int numIndexes );
	virtual void VPCALL DeriveUnsmoothedTangents( CDrawVertice *verts, const dominantTri_s *dominantTris, const int numVerts );
	virtual void VPCALL NormalizeTangents( CDrawVertice *verts, const int numVerts );
#endif	

#ifdef ENABLE_CREATE
	virtual void VPCALL CreateTextureSpaceLightVectors( CVector3D *lightVectors, const CVector3D &lightOrigin, const CDrawVertice *verts, const int numVerts, const int *indexes, const int numIndexes );
	virtual void VPCALL CreateSpecularTextureCoords( CVector4D *texCoords, const CVector3D &lightOrigin, const CVector3D &viewOrigin, const CDrawVertice *verts, const int numVerts, const int *indexes, const int numIndexes );
	virtual int  VPCALL CreateShadowCache( CVector4D *vertexCache, int *vertRemap, const CVector3D &lightOrigin, const CDrawVertice *verts, const int numVerts );
	virtual int  VPCALL CreateVertexProgramShadowCache( CVector4D *vertexCache, const CDrawVertice *verts, const int numVerts );
#endif

#ifdef ENABLE_SOUND_ROUTINES
	// Sound upsampling and mixing routines, works for aligned and unaligned data
	virtual void VPCALL UpSamplePCMTo44kHz( float *dest, const short *pcm, const int numSamples, const int kHz, const int numChannels );
	virtual void VPCALL UpSampleOGGTo44kHz( float *dest, const float * const *ogg, const int numSamples, const int kHz, const int numChannels );
	virtual void VPCALL MixSoundTwoSpeakerMono( float *mixBuffer, const float *samples, const int numSamples, const float lastV[2], const float currentV[2] );
	virtual void VPCALL MixSoundTwoSpeakerStereo( float *mixBuffer, const float *samples, const int numSamples, const float lastV[2], const float currentV[2] );
	virtual void VPCALL MixSoundSixSpeakerMono( float *mixBuffer, const float *samples, const int numSamples, const float lastV[6], const float currentV[6] );
	virtual void VPCALL MixSoundSixSpeakerStereo( float *mixBuffer, const float *samples, const int numSamples, const float lastV[6], const float currentV[6] );
	virtual void VPCALL MixedSoundToSamples( short *samples, const float *mixBuffer, const int numSamples );
#endif
#endif

};
} // end SGF
#endif /* !__MATH_SIMD_ALTIVEC_H__ */
