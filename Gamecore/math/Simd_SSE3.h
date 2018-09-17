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

#ifndef __MATH_SIMD_SSE3_H__
#define __MATH_SIMD_SSE3_H__

#include "../SGF_Config.h"
namespace SGF {
/*
===============================================================================

	SSE3 implementation of CSIMDProcessor

===============================================================================
*/

class CSIMD_SSE3 : public CSIMD_SSE2 {
public:
	CSIMD_SSE3():CSIMD_SSE2(CPUID_SSE2){};
	CSIMD_SSE3(cpuid_t id):CSIMD_SSE2(id){};
	~CSIMD_SSE3(){};
#if defined(MACOS_X) && defined(__i386__)
	virtual const char * VPCALL GetName() const;

#elif defined(_WIN32)
	virtual const char * VPCALL GetName() const;

	virtual void VPCALL TransformVerts( CDrawVertice *verts, const int numVerts, const CJointMatriz *joints, const CVector4D *weights, const int *index, const int numWeights );

#endif
};
} //end SGF
#endif /* !__MATH_SIMD_SSE3_H__ */
