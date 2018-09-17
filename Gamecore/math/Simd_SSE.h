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

#ifndef __MATH_SIMD_SSE_H__
#define __MATH_SIMD_SSE_H__
#include "../SGF_Config.h"
namespace SGF {
/*
===============================================================================

	SSE implementation of CSIMDProcessor

===============================================================================
*/

class CSIMD_SSE : public CSIMD_MMX {
public:
	CSIMD_SSE():CSIMD_MMX(CPUID_SSE){};
	CSIMD_SSE(cpuid_t id):CSIMD_MMX(id){};
	~CSIMD_SSE(){};


#if defined(MACOS_X) && defined(__i386__)
	virtual const char * VPCALL GetName() const;
	virtual void VPCALL Dot( float *dst,			const CPlane &constant,const CDrawVertice *src,	const int count );
	virtual	void VPCALL MinMax( CVector3D &min,		CVector3D &max,			const CDrawVertice *src,	const int *indexes,		const int count );
	virtual void VPCALL Dot( float *dst,			const CVector3D &constant,	const CPlane *src,		const int count );
#elif defined(_MSC_VER)
	virtual const char * VPCALL GetName() const;

	virtual void VPCALL Add( float *dst,			const float constant,	const float *src,		const int count );
	virtual void VPCALL Add( float *dst,			const float *src0,		const float *src1,		const int count );
	virtual void VPCALL Sub( float *dst,			const float constant,	const float *src,		const int count );
	virtual void VPCALL Sub( float *dst,			const float *src0,		const float *src1,		const int count );
	virtual void VPCALL Mul( float *dst,			const float constant,	const float *src,		const int count );
	virtual void VPCALL Mul( float *dst,			const float *src0,		const float *src1,		const int count );
	virtual void VPCALL Div( float *dst,			const float constant,	const float *src,		const int count );
	virtual void VPCALL Div( float *dst,			const float *src0,		const float *src1,		const int count );
	virtual void VPCALL MulAdd( float *dst,			const float constant,	const float *src,		const int count );
	virtual void VPCALL MulAdd( float *dst,			const float *src0,		const float *src1,		const int count );
	virtual void VPCALL MulSub( float *dst,			const float constant,	const float *src,		const int count );
	virtual void VPCALL MulSub( float *dst,			const float *src0,		const float *src1,		const int count );

	virtual void VPCALL Dot( float *dst,			const CVector3D &constant,	const CVector3D *src,		const int count );
	virtual void VPCALL Dot( float *dst,			const CVector3D &constant,	const CPlane *src,		const int count );
	virtual void VPCALL Dot( float *dst,			const CVector3D &constant,	const CDrawVertice *src,	const int count );
	virtual void VPCALL Dot( float *dst,			const CPlane &constant,const CVector3D *src,		const int count );
	virtual void VPCALL Dot( float *dst,			const CPlane &constant,const CPlane *src,		const int count );
	virtual void VPCALL Dot( float *dst,			const CPlane &constant,const CDrawVertice *src,	const int count );
	virtual void VPCALL Dot( float *dst,			const CVector3D *src0,		const CVector3D *src1,		const int count );
	virtual void VPCALL Dot( float &dot,			const float *src1,		const float *src2,		const int count );

	virtual void VPCALL CmpGT( SGF_Byte *dst,			const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpGT( SGF_Byte *dst,			const SGF_Byte bitNum,		const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpGE( SGF_Byte *dst,			const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpGE( SGF_Byte *dst,			const SGF_Byte bitNum,		const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpLT( SGF_Byte *dst,			const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpLT( SGF_Byte *dst,			const SGF_Byte bitNum,		const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpLE( SGF_Byte *dst,			const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpLE( SGF_Byte *dst,			const SGF_Byte bitNum,		const float *src0,		const float constant,	const int count );

	virtual void VPCALL MinMax( float &min,			float &max,				const float *src,		const int count );
	virtual	void VPCALL MinMax( CVector2D &min,		CVector2D &max,			const CVector2D *src,		const int count );
	virtual void VPCALL MinMax( CVector3D &min,		CVector3D &max,			const CVector3D *src,		const int count );
	virtual	void VPCALL MinMax( CVector3D &min,		CVector3D &max,			const CDrawVertice *src,	const int count );
	virtual	void VPCALL MinMax( CVector3D &min,		CVector3D &max,			const CDrawVertice *src,	const int *indexes,		const int count );

	virtual void VPCALL Clamp( float *dst,			const float *src,		const float min,		const float max,		const int count );
	virtual void VPCALL ClampMin( float *dst,		const float *src,		const float min,		const int count );
	virtual void VPCALL ClampMax( float *dst,		const float *src,		const float max,		const int count );

	virtual void VPCALL Zero16( float *dst,			const int count );
	virtual void VPCALL Negate16( float *dst,		const int count );
	virtual void VPCALL Copy16( float *dst,			const float *src,		const int count );
	virtual void VPCALL Add16( float *dst,			const float *src1,		const float *src2,		const int count );
	virtual void VPCALL Sub16( float *dst,			const float *src1,		const float *src2,		const int count );
	virtual void VPCALL Mul16( float *dst,			const float *src1,		const float constant,	const int count );
	virtual void VPCALL AddAssign16( float *dst,	const float *src,		const int count );
	virtual void VPCALL SubAssign16( float *dst,	const float *src,		const int count );
	virtual void VPCALL MulAssign16( float *dst,	const float constant,	const int count );

	virtual void VPCALL MatX_MultiplyVecX( CVectorXD &dst, const CMatrizXD &mat, const CVectorXD &vec );
	virtual void VPCALL MatX_MultiplyAddVecX( CVectorXD &dst, const CMatrizXD &mat, const CVectorXD &vec );
	virtual void VPCALL MatX_MultiplySubVecX( CVectorXD &dst, const CMatrizXD &mat, const CVectorXD &vec );
	virtual void VPCALL MatX_TransposeMultiplyVecX( CVectorXD &dst, const CMatrizXD &mat, const CVectorXD &vec );
	virtual void VPCALL MatX_TransposeMultiplyAddVecX( CVectorXD &dst, const CMatrizXD &mat, const CVectorXD &vec );
	virtual void VPCALL MatX_TransposeMultiplySubVecX( CVectorXD &dst, const CMatrizXD &mat, const CVectorXD &vec );
	virtual void VPCALL MatX_MultiplyMatX( CMatrizXD &dst, const CMatrizXD &m1, const CMatrizXD &m2 );
	virtual void VPCALL MatX_TransposeMultiplyMatX( CMatrizXD &dst, const CMatrizXD &m1, const CMatrizXD &m2 );
	virtual void VPCALL MatX_LowerTriangularSolve( const CMatrizXD &L, float *x, const float *b, const int n, int skip = 0 );
	virtual void VPCALL MatX_LowerTriangularSolveTranspose( const CMatrizXD &L, float *x, const float *b, const int n );
	virtual bool VPCALL MatX_LDLTFactor( CMatrizXD &mat, CVectorXD &invDiag, const int n );

	virtual void VPCALL BlendJoints( CJointQuaternion *joints, const CJointQuaternion *blendJoints, const float lerp, const int *index, const int numJoints );
	virtual void VPCALL ConvertJointQuatsToJointMats( CJointMatriz *jointMats, const CJointQuaternion *jointQuats, const int numJoints );
	virtual void VPCALL ConvertJointMatsToJointQuats( CJointQuaternion *jointQuats, const CJointMatriz *jointMats, const int numJoints );
	virtual void VPCALL TransformJoints( CJointMatriz *jointMats, const int *parents, const int firstJoint, const int lastJoint );
	virtual void VPCALL UntransformJoints( CJointMatriz *jointMats, const int *parents, const int firstJoint, const int lastJoint );
	virtual void VPCALL TransformVerts( CDrawVertice *verts, const int numVerts, const CJointMatriz *joints, const CVector4D *weights, const int *index, const int numWeights );
	virtual void VPCALL TracePointCull( SGF_Byte *cullBits, SGF_Byte &totalOr, const float radius, const CPlane *planes, const CDrawVertice *verts, const int numVerts );
	virtual void VPCALL DecalPointCull( SGF_Byte *cullBits, const CPlane *planes, const CDrawVertice *verts, const int numVerts );
	virtual void VPCALL OverlayPointCull( SGF_Byte *cullBits, CVector2D *texCoords, const CPlane *planes, const CDrawVertice *verts, const int numVerts );
	virtual void VPCALL DeriveTriPlanes( CPlane *planes, const CDrawVertice *verts, const int numVerts, const int *indexes, const int numIndexes );
	virtual void VPCALL DeriveTangents( CPlane *planes, CDrawVertice *verts, const int numVerts, const int *indexes, const int numIndexes );
	//virtual void VPCALL DeriveUnsmoothedTangents( CDrawVertice *verts, const dominantTri_s *dominantTris, const int numVerts );
	virtual void VPCALL NormalizeTangents( CDrawVertice *verts, const int numVerts );
	virtual void VPCALL CreateTextureSpaceLightVectors( CVector3D *lightVectors, const CVector3D &lightOrigin, const CDrawVertice *verts, const int numVerts, const int *indexes, const int numIndexes );
	virtual void VPCALL CreateSpecularTextureCoords( CVector4D *texCoords, const CVector3D &lightOrigin, const CVector3D &viewOrigin, const CDrawVertice *verts, const int numVerts, const int *indexes, const int numIndexes );
	virtual int  VPCALL CreateShadowCache( CVector4D *vertexCache, int *vertRemap, const CVector3D &lightOrigin, const CDrawVertice *verts, const int numVerts );
	virtual int  VPCALL CreateVertexProgramShadowCache( CVector4D *vertexCache, const CDrawVertice *verts, const int numVerts );

	virtual void VPCALL UpSamplePCMTo44kHz( float *dest, const short *pcm, const int numSamples, const int kHz, const int numChannels );
	virtual void VPCALL UpSampleOGGTo44kHz( float *dest, const float * const *ogg, const int numSamples, const int kHz, const int numChannels );
	virtual void VPCALL MixSoundTwoSpeakerMono( float *mixBuffer, const float *samples, const int numSamples, const float lastV[2], const float currentV[2] );
	virtual void VPCALL MixSoundTwoSpeakerStereo( float *mixBuffer, const float *samples, const int numSamples, const float lastV[2], const float currentV[2] );
	virtual void VPCALL MixSoundSixSpeakerMono( float *mixBuffer, const float *samples, const int numSamples, const float lastV[6], const float currentV[6] );
	virtual void VPCALL MixSoundSixSpeakerStereo( float *mixBuffer, const float *samples, const int numSamples, const float lastV[6], const float currentV[6] );
	virtual void VPCALL MixedSoundToSamples( short *samples, const float *mixBuffer, const int numSamples );

#elif defined(WIN32)  //TODO IMPLEMENT GNUC Methods
    virtual const char * VPCALL GetName() const;

#endif
};
} // end SGF
#endif /* !__MATH_SIMD_SSE_H__ */
