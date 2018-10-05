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

#ifndef __SGF_MATH_SIMD_H__
#define __SGF_MATH_SIMD_H__
#include "../SGF_Config.h"
#include "../util/SGF_UtilStructs.h"

namespace SGF{
/*
===============================================================================

	Single Instruction Multiple Data (SIMD)

	For optimal use data should be aligned on a 16 SGF_Byte boundary.
	All CSIMDProcessor routines are thread safe.

===============================================================================
*/
/**A sigla SIMD (Single Instruction, Multiple Data), descreve um método de operação de
computadores com várias unidades operacionais em computação paralela. Neste modo, a mesma
instrução é aplicada simultaneamente a diversos dados para produzir mais resultados.
O modelo SIMD é adequado para o tratamento de conjuntos regulares de dados, como as matrizes
e vetores. Esse tipo de máquina opera aplicando uma única instrução a um conjunto de elementos
de um vetor. Sendo uma máquina que aplique a n elementos uma determinada instrução e o vetor t
contenha os elementos a serem processados, t terá todos seus elementos calculados n vezes mais
rápido que uma máquina SISD na mesma tarefa.
http://pt.wikipedia.org/wiki/SIMD
*/
class idSIMD {
public:
	static void			Init();
	static void			InitProcessor( const char *module, bool forceGeneric );
	static void			Shutdown();
    //problemas de linkagem entre modulo.
    //todo: solve
    //static void			Test_f( const class CCMDLineArgs &args );
};


/*
===============================================================================

	virtual base class for different SIMD processors

===============================================================================
*/

#if defined (WIN32) && defined(_MSC_VER)
#define VPCALL __fastcall
#else
#define VPCALL
//#define VPCALL __attribute__((fastcall))
#endif

class CVector2D;
class CVector3D;
class CVector4D;
class CVector5D;
class CVector6D;
class CVectorXD;
class CMatriz2D;
class CMatriz3D;
class CMatriz4D;
class CMatriz5D;
class CMatriz6D;
class CMatrizXD;
class CPlane;
class CDrawVertice;
class CJointQuaternion;
class CJointMatriz;
//s struct dominantTri_s;

const int MIXBUFFER_SAMPLES = 4096;

typedef enum {
	SPEAKER_LEFT = 0,
	SPEAKER_RIGHT,
	SPEAKER_CENTER,
	SPEAKER_LFE,
	SPEAKER_BACKLEFT,
	SPEAKER_BACKRIGHT
} speakerLabel;




class CSIMDProcessor {
public:
	CSIMDProcessor():
	cpuid(CPUID_NONE){  }
	CSIMDProcessor(cpuid_t id):
	cpuid(id){  }
	~CSIMDProcessor(){};
	virtual const char * VPCALL		GetName() const = 0;
	virtual void VPCALL Add( float *dst,			const float constant,	const float *src,		const int count ) = 0;
	virtual void VPCALL Add( float *dst,			const float *src0,		const float *src1,		const int count ) = 0;
	virtual void VPCALL Sub( float *dst,			const float constant,	const float *src,		const int count ) = 0;
	virtual void VPCALL Sub( float *dst,			const float *src0,		const float *src1,		const int count ) = 0;
	virtual void VPCALL Mul( float *dst,			const float constant,	const float *src,		const int count ) = 0;
	virtual void VPCALL Mul( float *dst,			const float *src0,		const float *src1,		const int count ) = 0;
	virtual void VPCALL Div( float *dst,			const float constant,	const float *src,		const int count ) = 0;
	virtual void VPCALL Div( float *dst,			const float *src0,		const float *src1,		const int count ) = 0;
	virtual void VPCALL MulAdd( float *dst,			const float constant,	const float *src,		const int count ) = 0;
	virtual void VPCALL MulAdd( float *dst,			const float *src0,		const float *src1,		const int count ) = 0;
	virtual void VPCALL MulSub( float *dst,			const float constant,	const float *src,		const int count ) = 0;
	virtual void VPCALL MulSub( float *dst,			const float *src0,		const float *src1,		const int count ) = 0;

	virtual	void VPCALL Dot( float *dst,			const CVector3D &constant,	const CVector3D *src,		const int count ) = 0;
	virtual	void VPCALL Dot( float *dst,			const CVector3D &constant,	const CPlane *src,		const int count ) = 0;
	virtual void VPCALL Dot( float *dst,			const CVector3D &constant,	const CDrawVertice *src,	const int count ) = 0;
	virtual	void VPCALL Dot( float *dst,			const CPlane &constant,const CVector3D *src,		const int count ) = 0;
	virtual	void VPCALL Dot( float *dst,			const CPlane &constant,const CPlane *src,		const int count ) = 0;
	virtual void VPCALL Dot( float *dst,			const CPlane &constant,const CDrawVertice *src,	const int count ) = 0;
	virtual	void VPCALL Dot( float *dst,			const CVector3D *src0,		const CVector3D *src1,		const int count ) = 0;
	virtual void VPCALL Dot( float &dot,			const float *src1,		const float *src2,		const int count ) = 0;

	virtual	void VPCALL CmpGT( SGF_Byte *dst,			const float *src0,		const float constant,	const int count ) = 0;
	virtual	void VPCALL CmpGT( SGF_Byte *dst,			const SGF_Byte bitNum,		const float *src0,		const float constant,	const int count ) = 0;
	virtual	void VPCALL CmpGE( SGF_Byte *dst,			const float *src0,		const float constant,	const int count ) = 0;
	virtual	void VPCALL CmpGE( SGF_Byte *dst,			const SGF_Byte bitNum,		const float *src0,		const float constant,	const int count ) = 0;
	virtual	void VPCALL CmpLT( SGF_Byte *dst,			const float *src0,		const float constant,	const int count ) = 0;
	virtual	void VPCALL CmpLT( SGF_Byte *dst,			const SGF_Byte bitNum,		const float *src0,		const float constant,	const int count ) = 0;
	virtual	void VPCALL CmpLE( SGF_Byte *dst,			const float *src0,		const float constant,	const int count ) = 0;
	virtual	void VPCALL CmpLE( SGF_Byte *dst,			const SGF_Byte bitNum,		const float *src0,		const float constant,	const int count ) = 0;

	virtual	void VPCALL MinMax( float &min,			float &max,				const float *src,		const int count ) = 0;
	virtual	void VPCALL MinMax( CVector2D &min,		CVector2D &max,			const CVector2D *src,		const int count ) = 0;
	virtual	void VPCALL MinMax( CVector3D &min,		CVector3D &max,			const CVector3D *src,		const int count ) = 0;
	virtual	void VPCALL MinMax( CVector3D &min,		CVector3D &max,			const CDrawVertice *src,	const int count ) = 0;
	virtual	void VPCALL MinMax( CVector3D &min,		CVector3D &max,			const CDrawVertice *src,	const int *indexes,		const int count ) = 0;

	virtual	void VPCALL Clamp( float *dst,			const float *src,		const float min,		const float max,		const int count ) = 0;
	virtual	void VPCALL ClampMin( float *dst,		const float *src,		const float min,		const int count ) = 0;
	virtual	void VPCALL ClampMax( float *dst,		const float *src,		const float max,		const int count ) = 0;

	virtual void VPCALL Memcpy( void *dst,			const void *src,		const int count ) = 0;
	virtual void VPCALL Memset( void *dst,			const int val,			const int count ) = 0;

	// these assume 16 SGF_Byte aligned and 16 SGF_Byte padded memory
	virtual void VPCALL Zero16( float *dst,			const int count ) = 0;
	virtual void VPCALL Negate16( float *dst,		const int count ) = 0;
	virtual void VPCALL Copy16( float *dst,			const float *src,		const int count ) = 0;
	virtual void VPCALL Add16( float *dst,			const float *src1,		const float *src2,		const int count ) = 0;
	virtual void VPCALL Sub16( float *dst,			const float *src1,		const float *src2,		const int count ) = 0;
	virtual void VPCALL Mul16( float *dst,			const float *src1,		const float constant,	const int count ) = 0;
	virtual void VPCALL AddAssign16( float *dst,	const float *src,		const int count ) = 0;
	virtual void VPCALL SubAssign16( float *dst,	const float *src,		const int count ) = 0;
	virtual void VPCALL MulAssign16( float *dst,	const float constant,	const int count ) = 0;

	// CMatrizXD operations
	virtual void VPCALL MatX_MultiplyVecX( CVectorXD &dst, const CMatrizXD &mat, const CVectorXD &vec ) = 0;
	virtual void VPCALL MatX_MultiplyAddVecX( CVectorXD &dst, const CMatrizXD &mat, const CVectorXD &vec ) = 0;
	virtual void VPCALL MatX_MultiplySubVecX( CVectorXD &dst, const CMatrizXD &mat, const CVectorXD &vec ) = 0;
	virtual void VPCALL MatX_TransposeMultiplyVecX( CVectorXD &dst, const CMatrizXD &mat, const CVectorXD &vec ) = 0;
	virtual void VPCALL MatX_TransposeMultiplyAddVecX( CVectorXD &dst, const CMatrizXD &mat, const CVectorXD &vec ) = 0;
	virtual void VPCALL MatX_TransposeMultiplySubVecX( CVectorXD &dst, const CMatrizXD &mat, const CVectorXD &vec ) = 0;
	virtual void VPCALL MatX_MultiplyMatX( CMatrizXD &dst, const CMatrizXD &m1, const CMatrizXD &m2 ) = 0;
	virtual void VPCALL MatX_TransposeMultiplyMatX( CMatrizXD &dst, const CMatrizXD &m1, const CMatrizXD &m2 ) = 0;
	virtual void VPCALL MatX_LowerTriangularSolve( const CMatrizXD &L, float *x, const float *b, const int n, int skip = 0 ) = 0;
	virtual void VPCALL MatX_LowerTriangularSolveTranspose( const CMatrizXD &L, float *x, const float *b, const int n ) = 0;
	virtual bool VPCALL MatX_LDLTFactor( CMatrizXD &mat, CVectorXD &invDiag, const int n ) = 0;

	// rendering
	virtual void VPCALL BlendJoints( CJointQuaternion *joints, const CJointQuaternion *blendJoints, const float lerp, const int *index, const int numJoints ) = 0;
	virtual void VPCALL ConvertJointQuatsToJointMats( CJointMatriz *jointMats, const CJointQuaternion *jointQuats, const int numJoints ) = 0;
	virtual void VPCALL ConvertJointMatsToJointQuats( CJointQuaternion *jointQuats, const CJointMatriz *jointMats, const int numJoints ) = 0;
	virtual void VPCALL TransformJoints( CJointMatriz *jointMats, const int *parents, const int firstJoint, const int lastJoint ) = 0;
	virtual void VPCALL UntransformJoints( CJointMatriz *jointMats, const int *parents, const int firstJoint, const int lastJoint ) = 0;
	virtual void VPCALL TransformVerts( CDrawVertice *verts, const int numVerts, const CJointMatriz *joints, const CVector4D *weights, const int *index, const int numWeights ) = 0;
	virtual void VPCALL TracePointCull( SGF_Byte *cullBits, SGF_Byte &totalOr, const float radius, const CPlane *planes, const CDrawVertice *verts, const int numVerts ) = 0;
	virtual void VPCALL DecalPointCull( SGF_Byte *cullBits, const CPlane *planes, const CDrawVertice *verts, const int numVerts ) = 0;
	virtual void VPCALL OverlayPointCull( SGF_Byte *cullBits, CVector2D *texCoords, const CPlane *planes, const CDrawVertice *verts, const int numVerts ) = 0;
	virtual void VPCALL DeriveTriPlanes( CPlane *planes, const CDrawVertice *verts, const int numVerts, const int *indexes, const int numIndexes ) = 0;
	virtual void VPCALL DeriveTangents( CPlane *planes, CDrawVertice *verts, const int numVerts, const int *indexes, const int numIndexes ) = 0;
	//virtual void VPCALL DeriveUnsmoothedTangents( CDrawVertice *verts, const dominantTri_s *dominantTris, const int numVerts ) = 0;
	virtual void VPCALL NormalizeTangents( CDrawVertice *verts, const int numVerts ) = 0;
	virtual void VPCALL CreateTextureSpaceLightVectors( CVector3D *lightVectors, const CVector3D &lightOrigin, const CDrawVertice *verts, const int numVerts, const int *indexes, const int numIndexes ) = 0;
	virtual void VPCALL CreateSpecularTextureCoords( CVector4D *texCoords, const CVector3D &lightOrigin, const CVector3D &viewOrigin, const CDrawVertice *verts, const int numVerts, const int *indexes, const int numIndexes ) = 0;
	virtual int  VPCALL CreateShadowCache( CVector4D *vertexCache, int *vertRemap, const CVector3D &lightOrigin, const CDrawVertice *verts, const int numVerts ) = 0;
	virtual int  VPCALL CreateVertexProgramShadowCache( CVector4D *vertexCache, const CDrawVertice *verts, const int numVerts ) = 0;

	// sound mixing
	virtual void VPCALL UpSamplePCMTo44kHz( float *dest, const short *pcm, const int numSamples, const int kHz, const int numChannels ) = 0;
	virtual void VPCALL UpSampleOGGTo44kHz( float *dest, const float * const *ogg, const int numSamples, const int kHz, const int numChannels ) = 0;
	virtual void VPCALL MixSoundTwoSpeakerMono( float *mixBuffer, const float *samples, const int numSamples, const float lastV[2], const float currentV[2] ) = 0;
	virtual void VPCALL MixSoundTwoSpeakerStereo( float *mixBuffer, const float *samples, const int numSamples, const float lastV[2], const float currentV[2] ) = 0;
	virtual void VPCALL MixSoundSixSpeakerMono( float *mixBuffer, const float *samples, const int numSamples, const float lastV[6], const float currentV[6] ) = 0;
	virtual void VPCALL MixSoundSixSpeakerStereo( float *mixBuffer, const float *samples, const int numSamples, const float lastV[6], const float currentV[6] ) = 0;
	virtual void VPCALL MixedSoundToSamples( short *samples, const float *mixBuffer, const int numSamples ) = 0;

public:

	cpuid_t	cpuid;

};

// pointer to SIMD processor
extern CSIMDProcessor *SIMDProcessor;
} //end SGF
#endif /* !__SGF_MATH_SIMD_H__ */
