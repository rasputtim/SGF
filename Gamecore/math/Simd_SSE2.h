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

#ifndef __MATH_SIMD_SSE2_H__
#define __MATH_SIMD_SSE2_H__

#include "../SGF_Config.h"
namespace SGF {
/*
===============================================================================

	SSE2 implementation of CSIMDProcessor

===============================================================================
*/

class CSIMD_SSE2 : public CSIMD_SSE {
public:

	CSIMD_SSE2():CSIMD_SSE(CPUID_SSE2){};
	CSIMD_SSE2(cpuid_t id):CSIMD_SSE(id){};
	~CSIMD_SSE2(){};

#if defined(MACOS_X) && defined(__i386__)
	virtual const char * VPCALL GetName() const;
	virtual void VPCALL CmpLT( SGF_Byte *dst,			const SGF_Byte bitNum,		const float *src0,		const float constant,	const int count );

#elif defined(WIN32)
	virtual const char * VPCALL GetName() const;

	//virtual void VPCALL MatX_LowerTriangularSolve( const CMatrizXD &L, float *x, const float *b, const int n, int skip = 0 );
	//virtual void VPCALL MatX_LowerTriangularSolveTranspose( const CMatrizXD &L, float *x, const float *b, const int n );

	virtual void VPCALL MixedSoundToSamples( short *samples, const float *mixBuffer, const int numSamples );

#endif
};
} //end SGF
#endif /* !__MATH_SIMD_SSE2_H__ */
