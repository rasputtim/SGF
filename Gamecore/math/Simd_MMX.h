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

#ifndef __MATH_SIMD_MMX_H__
#define __MATH_SIMD_MMX_H__
#include "../SGF_Config.h"
namespace SGF {
/*
===============================================================================

	MMX implementation of CSIMDProcessor

===============================================================================
*/

class CSIMD_MMX : public CSIMD_Generic {
public:
	CSIMD_MMX():CSIMD_Generic(CPUID_MMX){};
	CSIMD_MMX(cpuid_t id):CSIMD_Generic(id){};
	~CSIMD_MMX(){};

#if defined(MACOS_X) && defined(__i686__)
	virtual const char * VPCALL GetName() const;

#else
	virtual const char * VPCALL GetName() const;

	virtual void VPCALL Memcpy( void *dst,			const void *src,		const int count );
	virtual void VPCALL Memset( void *dst,			const int val,			const int count );

#endif
};
} //end SGF
#endif /* !__MATH_SIMD_MMX_H__ */
