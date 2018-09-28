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

#include "math/SGF_Simd.h"
//#pragma hdrstop

#include "math/Simd_Generic.h"
//#include "math/Simd_MMX.h"
//#include "math/Simd_3DNow.h"
//#include "math/Simd_SSE.h"
//#include "math/Simd_SSE2.h"
//#include "math/Simd_SSE3.h"
//#include "math/Simd_AltiVec.h"
#include "math/SGF_Random.h"
#include "math/SGF_Math.h"
#include "math/SGF_Vector.h"
#include "math/SGF_Matriz.h"
#include "math/SGF_Plane.h"
#include "math/SGF_Angles.h"
#include "util/SGF_StringUtils.h"
#include "util/SGF_ArgsCmdLine.h"
#include "geometry/SGF_DrawVert.h"
#include "geometry/SGF_JointTransform.h"
#include "sys/SGF_System.h"


namespace SGF {
CSIMDProcessor	*	processor = NULL;			// pointer to SIMD processor
CSIMDProcessor *	generic = NULL;				// pointer to generic SIMD implementation
CSIMDProcessor *	SIMDProcessor = NULL;


/*
================
idSIMD::Init
================
*/
void idSIMD::Init() {
	generic = new CSIMD_Generic;
	generic->cpuid = CPUID_GENERIC;
	processor = NULL;
	SIMDProcessor = generic;
}

/*
============
idSIMD::InitProcessor
============
*/
void idSIMD::InitProcessor( const char *module, bool forceGeneric ) {
	cpuid_t cpuid;
	CSIMDProcessor *newProcessor;

	cpuid = System::getProcessorId();

	if ( forceGeneric ) {

		newProcessor = generic;

	} else {

		if ( !processor ) {
			if ( ( cpuid & CPUID_ALTIVEC ) ) {
//				processor = new idSIMD_AltiVec;
			} else if ( ( cpuid & CPUID_MMX ) && ( cpuid & CPUID_SSE ) && ( cpuid & CPUID_SSE2 ) && ( cpuid & CPUID_SSE3 ) ) {
                //processor = new CSIMD_SSE3;
			} else if ( ( cpuid & CPUID_MMX ) && ( cpuid & CPUID_SSE ) && ( cpuid & CPUID_SSE2 ) ) {
                //processor = new CSIMD_SSE2;
			} else if ( ( cpuid & CPUID_MMX ) && ( cpuid & CPUID_SSE ) ) {
                //processor = new CSIMD_SSE;
			} else if ( ( cpuid & CPUID_MMX ) && ( cpuid & CPUID_3DNOW ) ) {
                //processor = new CSIMD_3DNow;
			} else if ( ( cpuid & CPUID_MMX ) ) {
                //processor = new CSIMD_MMX;
			} else {
				processor = generic;
			}
			processor->cpuid = cpuid;
		}

		newProcessor = processor;
	}

	if ( newProcessor != SIMDProcessor ) {
		SIMDProcessor = newProcessor;
		Debug::debug(Debug::math,__FUNCTION__) <<  module << " using "  << SIMDProcessor->GetName()<<" for SIMD processing"<< endl;
	}

	if ( cpuid & CPUID_FTZ ) {
		System::fpu_SetFTZ( true );
		Debug::debug(Debug::math,__FUNCTION__) << "enabled Flush-To-Zero mode" <<endl;
	}

	if ( cpuid & CPUID_DAZ ) {
		System::fpu_SetDAZ( true );
		Debug::debug(Debug::math,__FUNCTION__) << "enabled Denormals-Are-Zero mode\n" <<endl;
	}
}

/*
================
idSIMD::Shutdown
================
*/
void idSIMD::Shutdown() {
	if ( processor != generic ) {
		delete processor;
	}
	delete generic;
	generic = NULL;
	processor = NULL;
	SIMDProcessor = NULL;
}


//===============================================================
//
// Test code
//
//===============================================================

#define COUNT		1024		// data count
#define NUMTESTS	2048		// number of tests

#define RANDOM_SEED		1013904223L	//((int)idLib::sys->GetClockTicks())

CSIMDProcessor *p_simd;
CSIMDProcessor *p_generic;
long baseClocks = 0;

#if defined(_WIN32) && defined(_MSC_VER)

#define TIME_TYPE int

#pragma warning(disable : 4731)     // frame pointer register 'ebx' modified by inline assembly code

long saved_ebx = 0;

#define StartRecordTime( start )			\
	__asm mov saved_ebx, ebx				\
	__asm xor eax, eax						\
	__asm cpuid								\
	__asm rdtsc								\
	__asm mov start, eax					\
	__asm xor eax, eax						\
	__asm cpuid

#define StopRecordTime( end )				\
	__asm xor eax, eax						\
	__asm cpuid								\
	__asm rdtsc								\
	__asm mov end, eax						\
	__asm mov ebx, saved_ebx				\
	__asm xor eax, eax						\
	__asm cpuid

#elif MACOS_X

#include <stdlib.h>
#include <unistd.h>			// this is for sleep()
#include <sys/time.h>
#include <sys/resource.h>
#include <mach/mach_time.h>

double ticksPerNanosecond;

#define TIME_TYPE uint64_t

#ifdef __MWERKS__ //time_in_millisec is missing
/*

    .text
	.align 2
	.globl _GetTB
_GetTB:

loop:
	        mftbu   r4	;  load from TBU
	        mftb    r5	;  load from TBL
	        mftbu   r6	;  load from TBU
	        cmpw    r6, r4	;  see if old == new
	        bne     loop	;  if not, carry occured, therefore loop

	        stw     r4, 0(r3)
	        stw     r5, 4(r3)

done:
	        blr		;  return

*/
typedef struct {
	unsigned int hi;
	unsigned int lo;
} U64;


asm void GetTB(U64 *in)
{
	nofralloc			// suppress prolog
	machine 603			// allows the use of mftb & mftbu functions

loop:
	mftbu	r5			// grab the upper time base register (TBU)
	mftb	r4			// grab the lower time base register (TBL)
	mftbu	r6			// grab the upper time base register (TBU) again

	cmpw	r6,r5		// see if old TBU == new TBU
	bne-	loop		// loop if carry occurred (predict branch not taken)

	stw  	r4,4(r3)	// store TBL in the low 32 bits of the return value
	stw  	r5,0(r3)	// store TBU in the high 32 bits of the return value

	blr
}




double TBToDoubleNano( U64 startTime, U64 stopTime, double ticksPerNanosecond );

#if __MWERKS__
asm void GetTB( U64 * );
#else
void GetTB( U64 * );
#endif

double TBToDoubleNano( U64 startTime, U64 stopTime, double ticksPerNanosecond ) {
	#define K_2POWER32 4294967296.0
	#define TICKS_PER_NANOSECOND 0.025
	double nanoTime;
	U64 diffTime;

	// calc the difference in TB ticks
	diffTime.hi = stopTime.hi - startTime.hi;
	diffTime.lo = stopTime.lo - startTime.lo;

	// convert TB ticks into time
	nanoTime = (double)(diffTime.hi)*((double)K_2POWER32) + (double)(diffTime.lo);
	nanoTime = nanoTime/ticksPerNanosecond;
	return (nanoTime);
}

TIME_TYPE time_in_millisec() {
	#define K_2POWER32 4294967296.0
	#define TICKS_PER_NANOSECOND 0.025

	U64 the_time;
	double nanoTime, milliTime;

	GetTB( &the_time );

	// convert TB ticks into time
	nanoTime = (double)(the_time.hi)*((double)K_2POWER32) + (double)(the_time.lo);
	nanoTime = nanoTime/ticksPerNanosecond;

	// nanoseconds are 1 billionth of a second. I want milliseconds
	milliTime = nanoTime * 1000000.0;

	printf( "ticks per nanosec -- %lf\n", ticksPerNanosecond );
	printf( "nanoTime is %lf -- milliTime is %lf -- as int is %i\n", nanoTime, milliTime, (int)milliTime );

	return (int)milliTime;
}

#define StartRecordTime( start )			\
	start = time_in_millisec();

#define StopRecordTime( end )				\
	end = time_in_millisec();


#else
#define StartRecordTime( start )			\
	start = mach_absolute_time();

#define StopRecordTime( end )				\
	end = mach_absolute_time();
#endif
#else

#define TIME_TYPE int

#define StartRecordTime( start )			\
	start = 0;

#define StopRecordTime( end )				\
	end = 1;

#endif

#define GetBest( start, end, best )			\
	if ( !best || end - start < best ) {	\
		best = end - start;					\
	}


/*
============
PrintClocks
============
*/
void PrintClocks( const char *string, int dataCount, int clocks, int otherClocks = 0 ) {
	int i;

	Debug::debug(Debug::math,__FUNCTION__) << string <<endl;
	for ( i = CMyString::LengthWithoutColors(string); i < 48; i++ ) {
		Debug::debug(Debug::math,__FUNCTION__) <<" "<<endl;
	}
	clocks -= baseClocks;
	if ( otherClocks && clocks ) {
		otherClocks -= baseClocks;
		int p = (int) ( (float) ( otherClocks - clocks ) * 100.0f / (float) otherClocks );
		Debug::debug(Debug::math,__FUNCTION__) << "c = %4d"<< dataCount<<" , clcks = %5d: "<< clocks <<", %d%%\n"<<  p<<endl;
	} else {
		Debug::debug(Debug::math,__FUNCTION__) << "c = %4d "<<  dataCount<< ", clcks = %5d\n"<< clocks <<endl;
	}
}

/*
============
GetBaseClocks
============
*/
void GetBaseClocks() {
	int i, start, end, bestClocks;

	bestClocks = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
	}
	baseClocks = bestClocks;
}

/*
============
TestAdd
============
*/
void TestAdd() {
	int i;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( float fdst0[COUNT] );
	ALIGN16( float fdst1[COUNT] );
	ALIGN16( float fsrc0[COUNT] );
	ALIGN16( float fsrc1[COUNT] );
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i < COUNT; i++ ) {
		fsrc0[i] = srnd.CRandomFloat() * 10.0f;
		fsrc1[i] = srnd.CRandomFloat() * 10.0f;
	}

	Debug::debug(Debug::math,__FUNCTION__) <<"====================================" <<endl;

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->Add( fdst0, 4.0f, fsrc1, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->Add( float + float[] )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->Add( fdst1, 4.0f, fsrc1, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( CMath::Fabs( fdst0[i] - fdst1[i] ) > 1e-5f ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->Add( float + float[] ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->Add( fdst0, fsrc0, fsrc1, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->Add( float[] + float[] )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->Add( fdst1, fsrc0, fsrc1, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( CMath::Fabs( fdst0[i] - fdst1[i] ) > 1e-5f ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->Add( float[] + float[] ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );
}

/*
============
TestSub
============
*/
void TestSub() {
	int i;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( float fdst0[COUNT] );
	ALIGN16( float fdst1[COUNT] );
	ALIGN16( float fsrc0[COUNT] );
	ALIGN16( float fsrc1[COUNT] );
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i < COUNT; i++ ) {
		fsrc0[i] = srnd.CRandomFloat() * 10.0f;
		fsrc1[i] = srnd.CRandomFloat() * 10.0f;
	}

	Debug::debug(Debug::math,__FUNCTION__) <<"====================================\n" <<endl;

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->Sub( fdst0, 4.0f, fsrc1, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->Sub( float + float[] )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->Sub( fdst1, 4.0f, fsrc1, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( CMath::Fabs( fdst0[i] - fdst1[i] ) > 1e-5f ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->Sub( float + float[] ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->Sub( fdst0, fsrc0, fsrc1, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->Sub( float[] + float[] )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->Sub( fdst1, fsrc0, fsrc1, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( CMath::Fabs( fdst0[i] - fdst1[i] ) > 1e-5f ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->Sub( float[] + float[] ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );
}

/*
============
TestMul
============
*/
void TestMul() {
	int i;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( float fdst0[COUNT] );
	ALIGN16( float fdst1[COUNT] );
	ALIGN16( float fsrc0[COUNT] );
	ALIGN16( float fsrc1[COUNT] );
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i < COUNT; i++ ) {
		fsrc0[i] = srnd.CRandomFloat() * 10.0f;
		fsrc1[i] = srnd.CRandomFloat() * 10.0f;
	}

	Debug::debug(Debug::math,__FUNCTION__) <<"====================================" <<endl;

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->Mul( fdst0, 4.0f, fsrc1, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->Mul( float * float[] )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->Mul( fdst1, 4.0f, fsrc1, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( CMath::Fabs( fdst0[i] - fdst1[i] ) > 1e-5f ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->Mul( float * float[] ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );


	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->Mul( fdst0, fsrc0, fsrc1, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->Mul( float[] * float[] )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->Mul( fdst1, fsrc0, fsrc1, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( CMath::Fabs( fdst0[i] - fdst1[i] ) > 1e-5f ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->Mul( float[] * float[] ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );
}

/*
============
TestDiv
============
*/
void TestDiv() {
	int i;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( float fdst0[COUNT] );
	ALIGN16( float fdst1[COUNT] );
	ALIGN16( float fsrc0[COUNT] );
	ALIGN16( float fsrc1[COUNT] );
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i < COUNT; i++ ) {
		fsrc0[i] = srnd.CRandomFloat() * 10.0f;
		do {
			fsrc1[i] = srnd.CRandomFloat() * 10.0f;
		} while( CMath::Fabs( fsrc1[i] ) < 0.1f );
	}

	Debug::debug(Debug::math,__FUNCTION__) <<"===================================="<<endl;


	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->Div( fdst0, 4.0f, fsrc1, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->Div( float * float[] )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->Div( fdst1, 4.0f, fsrc1, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( CMath::Fabs( fdst0[i] - fdst1[i] ) > 1e-5f ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->Div( float * float[] ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );


	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->Div( fdst0, fsrc0, fsrc1, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->Div( float[] * float[] )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->Div( fdst1, fsrc0, fsrc1, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( CMath::Fabs( fdst0[i] - fdst1[i] ) > 1e-3f ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->Div( float[] * float[] ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );
}

/*
============
TestMulAdd
============
*/
void TestMulAdd() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( float fdst0[COUNT] );
	ALIGN16( float fdst1[COUNT] );
	ALIGN16( float fsrc0[COUNT] );
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i < COUNT; i++ ) {
		fsrc0[i] = srnd.CRandomFloat() * 10.0f;
	}

	Debug::debug(Debug::math,__FUNCTION__) <<"====================================" <<endl;

	for ( j = 0; j < 50 && j < COUNT; j++ ) {

		bestClocksGeneric = 0;
		for ( i = 0; i < NUMTESTS; i++ ) {
			for ( int k = 0; k < COUNT; k++ ) {
				fdst0[k] = k;
			}
			StartRecordTime( start );
			p_generic->MulAdd( fdst0, 0.123f, fsrc0, j );
			StopRecordTime( end );
			GetBest( start, end, bestClocksGeneric );
		}
		PrintClocks( va( "generic->MulAdd( float * float[%2d] )", j ), 1, bestClocksGeneric );

		bestClocksSIMD = 0;
		for ( i = 0; i < NUMTESTS; i++ ) {
			for ( int k = 0; k < COUNT; k++ ) {
				fdst1[k] = k;
			}
			StartRecordTime( start );
			p_simd->MulAdd( fdst1, 0.123f, fsrc0, j );
			StopRecordTime( end );
			GetBest( start, end, bestClocksSIMD );
		}

		for ( i = 0; i < COUNT; i++ ) {
			if ( CMath::Fabs( fdst0[i] - fdst1[i] ) > 1e-5f ) {
				break;
			}
		}
		result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
		PrintClocks( va( "   simd->MulAdd( float * float[%2d] ) %s", j, result ), 1, bestClocksSIMD, bestClocksGeneric );
	}
}

/*
============
TestMulSub
============
*/
void TestMulSub() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( float fdst0[COUNT] );
	ALIGN16( float fdst1[COUNT] );
	ALIGN16( float fsrc0[COUNT] );
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i < COUNT; i++ ) {
		fsrc0[i] = srnd.CRandomFloat() * 10.0f;
	}

	Debug::debug(Debug::math,__FUNCTION__) <<"====================================" <<endl;

	for ( j = 0; j < 50 && j < COUNT; j++ ) {

		bestClocksGeneric = 0;
		for ( i = 0; i < NUMTESTS; i++ ) {
			for ( int k = 0; k < COUNT; k++ ) {
				fdst0[k] = k;
			}
			StartRecordTime( start );
			p_generic->MulSub( fdst0, 0.123f, fsrc0, j );
			StopRecordTime( end );
			GetBest( start, end, bestClocksGeneric );
		}
		PrintClocks( va( "generic->MulSub( float * float[%2d] )", j ), 1, bestClocksGeneric );

		bestClocksSIMD = 0;
		for ( i = 0; i < NUMTESTS; i++ ) {
			for ( int k = 0; k < COUNT; k++ ) {
				fdst1[k] = k;
			}
			StartRecordTime( start );
			p_simd->MulSub( fdst1, 0.123f, fsrc0, j );
			StopRecordTime( end );
			GetBest( start, end, bestClocksSIMD );
		}

		for ( i = 0; i < COUNT; i++ ) {
			if ( CMath::Fabs( fdst0[i] - fdst1[i] ) > 1e-5f ) {
				break;
			}
		}
		result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
		PrintClocks( va( "   simd->MulSub( float * float[%2d] ) %s", j, result ), 1, bestClocksSIMD, bestClocksGeneric );
	}
}

/*
============
TestDot
============
*/
void TestDot() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( float fdst0[COUNT] );
	ALIGN16( float fdst1[COUNT] );
	ALIGN16( float fsrc0[COUNT] );
	ALIGN16( float fsrc1[COUNT] );
	ALIGN16( CVector3D v3src0[COUNT] );
	ALIGN16( CVector3D v3src1[COUNT] );
	ALIGN16( CVector3D v3constant ) ( 1.0f, 2.0f, 3.0f );
	ALIGN16( CPlane v4src0[COUNT] );
	ALIGN16( CPlane v4constant ) (1.0f, 2.0f, 3.0f, 4.0f);
	ALIGN16( CDrawVertice drawVerts[COUNT] );
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i < COUNT; i++ ) {
		fsrc0[i] = srnd.CRandomFloat() * 10.0f;
		fsrc1[i] = srnd.CRandomFloat() * 10.0f;
		v3src0[i][0] = srnd.CRandomFloat() * 10.0f;
		v3src0[i][1] = srnd.CRandomFloat() * 10.0f;
		v3src0[i][2] = srnd.CRandomFloat() * 10.0f;
		v3src1[i][0] = srnd.CRandomFloat() * 10.0f;
		v3src1[i][1] = srnd.CRandomFloat() * 10.0f;
		v3src1[i][2] = srnd.CRandomFloat() * 10.0f;
		v4src0[i] = v3src0[i];
		v4src0[i][3] = srnd.CRandomFloat() * 10.0f;
		drawVerts[i].xyz = v3src0[i];
	}

	Debug::debug(Debug::math,__FUNCTION__) <<"====================================" <<endl;


	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->Dot( fdst0, v3constant, v3src0, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->Dot( CVector3D * CVector3D[] )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->Dot( fdst1, v3constant, v3src0, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( CMath::Fabs( fdst0[i] - fdst1[i] ) > 1e-5f ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->Dot( CVector3D * CVector3D[] ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );


	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->Dot( fdst0, v3constant, v4src0, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->Dot( CVector3D * CPlane[] )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->Dot( fdst1, v3constant, v4src0, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( CMath::Fabs( fdst0[i] - fdst1[i] ) > 1e-5f ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->Dot( CVector3D * CPlane[] ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );


	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->Dot( fdst0, v3constant, drawVerts, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->Dot( CVector3D * CDrawVertice[] )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->Dot( fdst1, v3constant, drawVerts, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( CMath::Fabs( fdst0[i] - fdst1[i] ) > 1e-5f ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->Dot( CVector3D * CDrawVertice[] ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );


	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->Dot( fdst0, v4constant, v3src0, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->Dot( CPlane * CVector3D[] )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->Dot( fdst1, v4constant, v3src0, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( CMath::Fabs( fdst0[i] - fdst1[i] ) > 1e-5f ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->Dot( CPlane * CVector3D[] ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );


	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->Dot( fdst0, v4constant, v4src0, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->Dot( CPlane * CPlane[] )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->Dot( fdst1, v4constant, v4src0, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( CMath::Fabs( fdst0[i] - fdst1[i] ) > 1e-5f ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->Dot( CPlane * CPlane[] ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );


	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->Dot( fdst0, v4constant, drawVerts, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->Dot( CPlane * CDrawVertice[] )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->Dot( fdst1, v4constant, drawVerts, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( CMath::Fabs( fdst0[i] - fdst1[i] ) > 1e-5f ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->Dot( CPlane * CDrawVertice[] ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );


	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->Dot( fdst0, v3src0, v3src1, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->Dot( CVector3D[] * CVector3D[] )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->Dot( fdst1, v3src0, v3src1, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( CMath::Fabs( fdst0[i] - fdst1[i] ) > 1e-4f ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->Dot( CVector3D[] * CVector3D[] ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );


	Debug::debug(Debug::math,__FUNCTION__) <<"====================================" <<endl;

	float dot1 = 0.0f, dot2 = 0.0f;
	for ( j = 0; j < 50 && j < COUNT; j++ ) {

		bestClocksGeneric = 0;
		for ( i = 0; i < NUMTESTS; i++ ) {
			StartRecordTime( start );
			p_generic->Dot( dot1, fsrc0, fsrc1, j );
			StopRecordTime( end );
			GetBest( start, end, bestClocksGeneric );
		}
		PrintClocks( va( "generic->Dot( float[%2d] * float[%2d] )", j, j ), 1, bestClocksGeneric );

		bestClocksSIMD = 0;
		for ( i = 0; i < NUMTESTS; i++ ) {
			StartRecordTime( start );
			p_simd->Dot( dot2, fsrc0, fsrc1, j );
			StopRecordTime( end );
			GetBest( start, end, bestClocksSIMD );
		}
		result = CMath::Fabs( dot1 - dot2 ) < 1e-4f ? "ok" : S_COLOR_RED"X";
		PrintClocks( va( "   simd->Dot( float[%2d] * float[%2d] ) %s", j, j, result ), 1, bestClocksSIMD, bestClocksGeneric );
	}
}

/*
============
TestCompare
============
*/
void TestCompare() {
	int i;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( float fsrc0[COUNT] );
	ALIGN16( SGF_Byte bytedst[COUNT] );
	ALIGN16( SGF_Byte bytedst2[COUNT] );
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i < COUNT; i++ ) {
		fsrc0[i] = srnd.CRandomFloat() * 10.0f;
	}

	Debug::debug(Debug::math,__FUNCTION__) <<"====================================\n" <<endl;

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->CmpGT( bytedst, fsrc0, 0.0f, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->CmpGT( float[] >= float )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->CmpGT( bytedst2, fsrc0, 0.0f, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( bytedst[i] != bytedst2[i] ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->CmpGT( float[] >= float ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		memset( bytedst, 0, COUNT );
		StartRecordTime( start );
		p_generic->CmpGT( bytedst, 2, fsrc0, 0.0f, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->CmpGT( 2, float[] >= float )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		memset( bytedst2, 0, COUNT );
		StartRecordTime( start );
		p_simd->CmpGT( bytedst2, 2, fsrc0, 0.0f, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( bytedst[i] != bytedst2[i] ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->CmpGT( 2, float[] >= float ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );

	// ======================

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->CmpGE( bytedst, fsrc0, 0.0f, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->CmpGE( float[] >= float )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->CmpGE( bytedst2, fsrc0, 0.0f, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( bytedst[i] != bytedst2[i] ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->CmpGE( float[] >= float ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		memset( bytedst, 0, COUNT );
		StartRecordTime( start );
		p_generic->CmpGE( bytedst, 2, fsrc0, 0.0f, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->CmpGE( 2, float[] >= float )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		memset( bytedst2, 0, COUNT );
		StartRecordTime( start );
		p_simd->CmpGE( bytedst2, 2, fsrc0, 0.0f, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( bytedst[i] != bytedst2[i] ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->CmpGE( 2, float[] >= float ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );

	// ======================

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->CmpLT( bytedst, fsrc0, 0.0f, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->CmpLT( float[] >= float )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->CmpLT( bytedst2, fsrc0, 0.0f, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( bytedst[i] != bytedst2[i] ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->CmpLT( float[] >= float ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		memset( bytedst, 0, COUNT );
		StartRecordTime( start );
		p_generic->CmpLT( bytedst, 2, fsrc0, 0.0f, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->CmpLT( 2, float[] >= float )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		memset( bytedst2, 0, COUNT );
		StartRecordTime( start );
		p_simd->CmpLT( bytedst2, 2, fsrc0, 0.0f, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( bytedst[i] != bytedst2[i] ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->CmpLT( 2, float[] >= float ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );

	// ======================

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->CmpLE( bytedst, fsrc0, 0.0f, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->CmpLE( float[] >= float )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->CmpLE( bytedst2, fsrc0, 0.0f, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( bytedst[i] != bytedst2[i] ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->CmpLE( float[] >= float ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		memset( bytedst, 0, COUNT );
		StartRecordTime( start );
		p_generic->CmpLE( bytedst, 2, fsrc0, 0.0f, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->CmpLE( 2, float[] >= float )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		memset( bytedst2, 0, COUNT );
		StartRecordTime( start );
		p_simd->CmpLE( bytedst2, 2, fsrc0, 0.0f, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( bytedst[i] != bytedst2[i] ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->CmpLE( 2, float[] >= float ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );
}

/*
============
TestMinMax
============
*/
void TestMinMax() {
	int i;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( float fsrc0[COUNT] );
	ALIGN16( CVector2D v2src0[COUNT] );
	ALIGN16( CVector3D v3src0[COUNT] );
	ALIGN16( CDrawVertice drawVerts[COUNT] );
	ALIGN16( int indexes[COUNT] );
	float min = 0.0f, max = 0.0f, min2 = 0.0f, max2 = 0.0f;
	CVector2D v2min, v2max, v2min2, v2max2;
	CVector3D vmin, vmax, vmin2, vmax2;
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i < COUNT; i++ ) {
		fsrc0[i] = srnd.CRandomFloat() * 10.0f;
		v2src0[i][0] = srnd.CRandomFloat() * 10.0f;
		v2src0[i][1] = srnd.CRandomFloat() * 10.0f;
		v3src0[i][0] = srnd.CRandomFloat() * 10.0f;
		v3src0[i][1] = srnd.CRandomFloat() * 10.0f;
		v3src0[i][2] = srnd.CRandomFloat() * 10.0f;
		drawVerts[i].xyz = v3src0[i];
		indexes[i] = i;
	}

	Debug::debug(Debug::math,__FUNCTION__) <<"====================================\n"<<endl;

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		min = CMath::INFINITY;
		max = -CMath::INFINITY;
		StartRecordTime( start );
		p_generic->MinMax( min, max, fsrc0, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->MinMax( float[] )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->MinMax( min2, max2, fsrc0, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	result = ( min == min2 && max == max2 ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->MinMax( float[] ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->MinMax( v2min, v2max, v2src0, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->MinMax( CVector2D[] )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->MinMax( v2min2, v2max2, v2src0, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	result = ( v2min == v2min2 && v2max == v2max2 ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->MinMax( CVector2D[] ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->MinMax( vmin, vmax, v3src0, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->MinMax( CVector3D[] )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->MinMax( vmin2, vmax2, v3src0, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	result = ( vmin == vmin2 && vmax == vmax2 ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->MinMax( CVector3D[] ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->MinMax( vmin, vmax, drawVerts, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->MinMax( CDrawVertice[] )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->MinMax( vmin2, vmax2, drawVerts, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	result = ( vmin == vmin2 && vmax == vmax2 ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->MinMax( CDrawVertice[] ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->MinMax( vmin, vmax, drawVerts, indexes, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->MinMax( CDrawVertice[], indexes[] )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->MinMax( vmin2, vmax2, drawVerts, indexes, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	result = ( vmin == vmin2 && vmax == vmax2 ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->MinMax( CDrawVertice[], indexes[] ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );
}

/*
============
TestClamp
============
*/
void TestClamp() {
	int i;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( float fdst0[COUNT] );
	ALIGN16( float fdst1[COUNT] );
	ALIGN16( float fsrc0[COUNT] );
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i < COUNT; i++ ) {
		fsrc0[i] = srnd.CRandomFloat() * 10.0f;
	}

	Debug::debug(Debug::math,__FUNCTION__) <<"====================================\n"<<endl;

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->Clamp( fdst0, fsrc0, -1.0f, 1.0f, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->Clamp( float[] )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->Clamp( fdst1, fsrc0, -1.0f, 1.0f, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( fdst0[i] != fdst1[i] ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->Clamp( float[] ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );


	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->ClampMin( fdst0, fsrc0, -1.0f, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->ClampMin( float[] )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->ClampMin( fdst1, fsrc0, -1.0f, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( fdst0[i] != fdst1[i] ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->ClampMin( float[] ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );


	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->ClampMax( fdst0, fsrc0, 1.0f, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->ClampMax( float[] )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->ClampMax( fdst1, fsrc0, 1.0f, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( fdst0[i] != fdst1[i] ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->ClampMax( float[] ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );
}

/*
============
TestMemcpy
============
*/
void TestMemcpy() {
	int i, j;
	SGF_Byte test0[8192];
	SGF_Byte test1[8192];

	CRamdom random( RANDOM_SEED );

	Debug::debug(Debug::math,__FUNCTION__) <<"====================================\n" <<endl;

	for ( i = 5; i < 8192; i += 31 ) {
		for ( j = 0; j < i; j++ ) {
			test0[j] = random.RandomInt( 255 );
		}
		p_simd->Memcpy( test1, test0, 8192 );
		for ( j = 0; j < i; j++ ) {
			if ( test1[j] != test0[j] ) {
				Debug::debug(Debug::math,__FUNCTION__) << "   simd->Memcpy() "<< S_COLOR_RED<<"X\n" <<endl;
				return;
			}
		}
	}
	Debug::debug(Debug::math,__FUNCTION__) << "   simd->Memcpy() ok\n"<<endl;
}

/*
============
TestMemset
============
*/
void TestMemset() {
	int i, j, k;
	SGF_Byte test[8192];

	for ( i = 0; i < 8192; i++ ) {
		test[i] = 0;
	}

	for ( i = 5; i < 8192; i += 31 ) {
		for ( j = -1; j <= 1; j++ ) {
			p_simd->Memset( test, j, i );
			for ( k = 0; k < i; k++ ) {
				if ( test[k] != (SGF_Byte)j ) {
					Debug::debug(Debug::math,__FUNCTION__) << "   simd->Memset() "<< S_COLOR_RED<< "X\n" <<endl;
					return;
				}
			}
		}
	}
	Debug::debug(Debug::math,__FUNCTION__) << "   simd->Memset() ok\n" <<endl;
}

#define	MATX_SIMD_EPSILON			1e-5f

/*
============
TestMatXMultiplyVecX
============
*/
void TestMatXMultiplyVecX() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	const char *result;
	CMatrizXD mat;
	CVectorXD src(6);
	CVectorXD dst(6);
	CVectorXD tst(6);

	src[0] = 1.0f;
	src[1] = 2.0f;
	src[2] = 3.0f;
	src[3] = 4.0f;
	src[4] = 5.0f;
	src[5] = 6.0f;

	Debug::debug(Debug::math,__FUNCTION__) <<"================= NxN * Nx1 ===================\n"<<endl;

	for ( i = 1; i <= 6; i++ ) {
		mat.Random( i, i, RANDOM_SEED, -10.0f, 10.0f );

		bestClocksGeneric = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			dst.Zero();
			StartRecordTime( start );
			p_generic->MatX_MultiplyVecX( dst, mat, src );
			StopRecordTime( end );
			GetBest( start, end, bestClocksGeneric );
		}
		tst = dst;

		PrintClocks( va( "generic->MatX_MultiplyVecX %dx%d*%dx1", i, i, i ), 1, bestClocksGeneric );

		bestClocksSIMD = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			dst.Zero();
			StartRecordTime( start );
			p_simd->MatX_MultiplyVecX( dst, mat, src );
			StopRecordTime( end );
			GetBest( start, end, bestClocksSIMD );
		}

		result = dst.Compare( tst, MATX_SIMD_EPSILON ) ? "ok" : S_COLOR_RED"X";
		PrintClocks( va( "   simd->MatX_MultiplyVecX %dx%d*%dx1 %s", i, i, i, result ), 1, bestClocksSIMD, bestClocksGeneric );
	}

	Debug::debug(Debug::math,__FUNCTION__) <<"================= Nx6 * 6x1 ===================\n" <<endl;

	for ( i = 1; i <= 6; i++ ) {
		mat.Random( i, 6, RANDOM_SEED, -10.0f, 10.0f );

		bestClocksGeneric = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			dst.Zero();
			StartRecordTime( start );
			p_generic->MatX_MultiplyVecX( dst, mat, src );
			StopRecordTime( end );
			GetBest( start, end, bestClocksGeneric );
		}
		tst = dst;

		PrintClocks( va( "generic->MatX_MultiplyVecX %dx6*6x1", i ), 1, bestClocksGeneric );

		bestClocksSIMD = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			dst.Zero();
			StartRecordTime( start );
			p_simd->MatX_MultiplyVecX( dst, mat, src );
			StopRecordTime( end );
			GetBest( start, end, bestClocksSIMD );
		}

		result = dst.Compare( tst, MATX_SIMD_EPSILON ) ? "ok" : S_COLOR_RED"X";
		PrintClocks( va( "   simd->MatX_MultiplyVecX %dx6*6x1 %s", i, result ), 1, bestClocksSIMD, bestClocksGeneric );
	}

	Debug::debug(Debug::math,__FUNCTION__) <<"================= 6xN * Nx1 ===================\n"<<endl;

	for ( i = 1; i <= 6; i++ ) {
		mat.Random( 6, i, RANDOM_SEED, -10.0f, 10.0f );

		bestClocksGeneric = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			dst.Zero();
			StartRecordTime( start );
			p_generic->MatX_MultiplyVecX( dst, mat, src );
			StopRecordTime( end );
			GetBest( start, end, bestClocksGeneric );
		}
		tst = dst;

		PrintClocks( va( "generic->MatX_MultiplyVecX 6x%d*%dx1", i, i ), 1, bestClocksGeneric );

		bestClocksSIMD = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			StartRecordTime( start );
			p_simd->MatX_MultiplyVecX( dst, mat, src );
			StopRecordTime( end );
			GetBest( start, end, bestClocksSIMD );
		}

		result = dst.Compare( tst, MATX_SIMD_EPSILON ) ? "ok" : S_COLOR_RED"X";
		PrintClocks( va( "   simd->MatX_MultiplyVecX 6x%d*%dx1 %s", i, i, result ), 1, bestClocksSIMD, bestClocksGeneric );
	}
}

/*
============
TestMatXMultiplyAddVecX
============
*/
void TestMatXMultiplyAddVecX() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	const char *result;
	CMatrizXD mat;
	CVectorXD src(6);
	CVectorXD dst(6);
	CVectorXD tst(6);

	src[0] = 1.0f;
	src[1] = 2.0f;
	src[2] = 3.0f;
	src[3] = 4.0f;
	src[4] = 5.0f;
	src[5] = 6.0f;

	Debug::debug(Debug::math,__FUNCTION__) <<"================= NxN * Nx1 ===================\n" <<endl;

	for ( i = 1; i <= 6; i++ ) {
		mat.Random( i, i, RANDOM_SEED, -10.0f, 10.0f );

		bestClocksGeneric = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			dst.Zero();
			StartRecordTime( start );
			p_generic->MatX_MultiplyAddVecX( dst, mat, src );
			StopRecordTime( end );
			GetBest( start, end, bestClocksGeneric );
		}
		tst = dst;

		PrintClocks( va( "generic->MatX_MultiplyAddVecX %dx%d*%dx1", i, i, i ), 1, bestClocksGeneric );

		bestClocksSIMD = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			dst.Zero();
			StartRecordTime( start );
			p_simd->MatX_MultiplyAddVecX( dst, mat, src );
			StopRecordTime( end );
			GetBest( start, end, bestClocksSIMD );
		}

		result = dst.Compare( tst, MATX_SIMD_EPSILON ) ? "ok" : S_COLOR_RED"X";
		PrintClocks( va( "   simd->MatX_MultiplyAddVecX %dx%d*%dx1 %s", i, i, i, result ), 1, bestClocksSIMD, bestClocksGeneric );
	}

	Debug::debug(Debug::math,__FUNCTION__) <<"================= Nx6 * 6x1 ===================\n" <<endl;

	for ( i = 1; i <= 6; i++ ) {
		mat.Random( i, 6, RANDOM_SEED, -10.0f, 10.0f );

		bestClocksGeneric = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			dst.Zero();
			StartRecordTime( start );
			p_generic->MatX_MultiplyAddVecX( dst, mat, src );
			StopRecordTime( end );
			GetBest( start, end, bestClocksGeneric );
		}
		tst = dst;

		PrintClocks( va( "generic->MatX_MultiplyAddVecX %dx6*6x1", i ), 1, bestClocksGeneric );

		bestClocksSIMD = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			dst.Zero();
			StartRecordTime( start );
			p_simd->MatX_MultiplyAddVecX( dst, mat, src );
			StopRecordTime( end );
			GetBest( start, end, bestClocksSIMD );
		}

		result = dst.Compare( tst, MATX_SIMD_EPSILON ) ? "ok" : S_COLOR_RED"X";
		PrintClocks( va( "   simd->MatX_MultiplyAddVecX %dx6*6x1 %s", i, result ), 1, bestClocksSIMD, bestClocksGeneric );
	}

	Debug::debug(Debug::math,__FUNCTION__) <<"================= 6xN * Nx1 ===================\n" <<endl;

	for ( i = 1; i <= 6; i++ ) {
		mat.Random( 6, i, RANDOM_SEED, -10.0f, 10.0f );

		bestClocksGeneric = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			dst.Zero();
			StartRecordTime( start );
			p_generic->MatX_MultiplyAddVecX( dst, mat, src );
			StopRecordTime( end );
			GetBest( start, end, bestClocksGeneric );
		}
		tst = dst;

		PrintClocks( va( "generic->MatX_MultiplyAddVecX 6x%d*%dx1", i, i ), 1, bestClocksGeneric );

		bestClocksSIMD = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			dst.Zero();
			StartRecordTime( start );
			p_simd->MatX_MultiplyAddVecX( dst, mat, src );
			StopRecordTime( end );
			GetBest( start, end, bestClocksSIMD );
		}

		result = dst.Compare( tst, MATX_SIMD_EPSILON ) ? "ok" : S_COLOR_RED"X";
		PrintClocks( va( "   simd->MatX_MultiplyAddVecX 6x%d*%dx1 %s", i, i, result ), 1, bestClocksSIMD, bestClocksGeneric );
	}
}

/*
============
TestMatXTransposeMultiplyVecX
============
*/
void TestMatXTransposeMultiplyVecX() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	const char *result;
	CMatrizXD mat;
	CVectorXD src(6);
	CVectorXD dst(6);
	CVectorXD tst(6);

	src[0] = 1.0f;
	src[1] = 2.0f;
	src[2] = 3.0f;
	src[3] = 4.0f;
	src[4] = 5.0f;
	src[5] = 6.0f;

	Debug::debug(Debug::math,__FUNCTION__) <<"================= Nx6 * Nx1 ===================\n"<<endl;

	for ( i = 1; i <= 6; i++ ) {
		mat.Random( i, 6, RANDOM_SEED, -10.0f, 10.0f );

		bestClocksGeneric = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			dst.Zero();
			StartRecordTime( start );
			p_generic->MatX_TransposeMultiplyVecX( dst, mat, src );
			StopRecordTime( end );
			GetBest( start, end, bestClocksGeneric );
		}
		tst = dst;

		PrintClocks( va( "generic->MatX_TransposeMulVecX %dx6*%dx1", i, i ), 1, bestClocksGeneric );

		bestClocksSIMD = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			dst.Zero();
			StartRecordTime( start );
			p_simd->MatX_TransposeMultiplyVecX( dst, mat, src );
			StopRecordTime( end );
			GetBest( start, end, bestClocksSIMD );
		}

		result = dst.Compare( tst, MATX_SIMD_EPSILON ) ? "ok" : S_COLOR_RED"X";
		PrintClocks( va( "   simd->MatX_TransposeMulVecX %dx6*%dx1 %s", i, i, result ), 1, bestClocksSIMD, bestClocksGeneric );
	}

	Debug::debug(Debug::math,__FUNCTION__) <<"================= 6xN * 6x1 ===================\n" <<endl;

	for ( i = 1; i <= 6; i++ ) {
		mat.Random( 6, i, RANDOM_SEED, -10.0f, 10.0f );

		bestClocksGeneric = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			dst.Zero();
			StartRecordTime( start );
			p_generic->MatX_TransposeMultiplyVecX( dst, mat, src );
			StopRecordTime( end );
			GetBest( start, end, bestClocksGeneric );
		}
		tst = dst;

		PrintClocks( va( "generic->MatX_TransposeMulVecX 6x%d*6x1", i ), 1, bestClocksGeneric );

		bestClocksSIMD = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			dst.Zero();
			StartRecordTime( start );
			p_simd->MatX_TransposeMultiplyVecX( dst, mat, src );
			StopRecordTime( end );
			GetBest( start, end, bestClocksSIMD );
		}

		result = dst.Compare( tst, MATX_SIMD_EPSILON ) ? "ok" : S_COLOR_RED"X";
		PrintClocks( va( "   simd->MatX_TransposeMulVecX 6x%d*6x1 %s", i, result ), 1, bestClocksSIMD, bestClocksGeneric );
	}
}

/*
============
TestMatXTransposeMultiplyAddVecX
============
*/
void TestMatXTransposeMultiplyAddVecX() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	const char *result;
	CMatrizXD mat;
	CVectorXD src(6);
	CVectorXD dst(6);
	CVectorXD tst(6);

	src[0] = 1.0f;
	src[1] = 2.0f;
	src[2] = 3.0f;
	src[3] = 4.0f;
	src[4] = 5.0f;
	src[5] = 6.0f;

	Debug::debug(Debug::math,__FUNCTION__) <<"================= Nx6 * Nx1 ===================\n" <<endl;

	for ( i = 1; i <= 6; i++ ) {
		mat.Random( i, 6, RANDOM_SEED, -10.0f, 10.0f );

		bestClocksGeneric = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			dst.Zero();
			StartRecordTime( start );
			p_generic->MatX_TransposeMultiplyAddVecX( dst, mat, src );
			StopRecordTime( end );
			GetBest( start, end, bestClocksGeneric );
		}
		tst = dst;

		PrintClocks( va( "generic->MatX_TransposeMulAddVecX %dx6*%dx1", i, i ), 1, bestClocksGeneric );

		bestClocksSIMD = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			dst.Zero();
			StartRecordTime( start );
			p_simd->MatX_TransposeMultiplyAddVecX( dst, mat, src );
			StopRecordTime( end );
			GetBest( start, end, bestClocksSIMD );
		}

		result = dst.Compare( tst, MATX_SIMD_EPSILON ) ? "ok" : S_COLOR_RED"X";
		PrintClocks( va( "   simd->MatX_TransposeMulAddVecX %dx6*%dx1 %s", i, i, result ), 1, bestClocksSIMD, bestClocksGeneric );
	}

	Debug::debug(Debug::math,__FUNCTION__) <<"================= 6xN * 6x1 ===================\n" <<endl;

	for ( i = 1; i <= 6; i++ ) {
		mat.Random( 6, i, RANDOM_SEED, -10.0f, 10.0f );

		bestClocksGeneric = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			dst.Zero();
			StartRecordTime( start );
			p_generic->MatX_TransposeMultiplyAddVecX( dst, mat, src );
			StopRecordTime( end );
			GetBest( start, end, bestClocksGeneric );
		}
		tst = dst;

		PrintClocks( va( "generic->MatX_TransposeMulAddVecX 6x%d*6x1", i ), 1, bestClocksGeneric );

		bestClocksSIMD = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			dst.Zero();
			StartRecordTime( start );
			p_simd->MatX_TransposeMultiplyAddVecX( dst, mat, src );
			StopRecordTime( end );
			GetBest( start, end, bestClocksSIMD );
		}

		result = dst.Compare( tst, MATX_SIMD_EPSILON ) ? "ok" : S_COLOR_RED"X";
		PrintClocks( va( "   simd->MatX_TransposeMulAddVecX 6x%d*6x1 %s", i, result ), 1, bestClocksSIMD, bestClocksGeneric );
	}
}

/*
============
TestMatXMultiplyMatX
============
*/
#define TEST_VALUE_RANGE			10.0f
#define	MATX_MATX_SIMD_EPSILON		1e-4f

void TestMatXMultiplyMatX() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	const char *result;
	CMatrizXD m1, m2, dst, tst;

	Debug::debug(Debug::math,__FUNCTION__) <<"================= NxN * Nx6 ===================" <<endl;

	// NxN * Nx6
	for ( i = 1; i <= 5; i++ ) {
		m1.Random( i, i, RANDOM_SEED, -TEST_VALUE_RANGE, TEST_VALUE_RANGE );
		m2.Random( i, 6, RANDOM_SEED, -TEST_VALUE_RANGE, TEST_VALUE_RANGE );
		dst.SetSize( i, 6 );

		bestClocksGeneric = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			StartRecordTime( start );
			p_generic->MatX_MultiplyMatX( dst, m1, m2 );
			StopRecordTime( end );
			GetBest( start, end, bestClocksGeneric );
		}
		tst = dst;

		PrintClocks( va( "generic->MatX_MultiplyMatX %dx%d*%dx6", i, i, i ), 1, bestClocksGeneric );

		bestClocksSIMD = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			StartRecordTime( start );
			p_simd->MatX_MultiplyMatX( dst, m1, m2 );
			StopRecordTime( end );
			GetBest( start, end, bestClocksSIMD );
		}

		result = dst.Compare( tst, MATX_MATX_SIMD_EPSILON ) ? "ok" : S_COLOR_RED"X";
		PrintClocks( va( "   simd->MatX_MultiplyMatX %dx%d*%dx6 %s", i, i, i, result ), 1, bestClocksSIMD, bestClocksGeneric );
	}

	Debug::debug(Debug::math,__FUNCTION__) <<"================= 6xN * Nx6 ===================\n" <<endl;

	// 6xN * Nx6
	for ( i = 1; i <= 5; i++ ) {
		m1.Random( 6, i, RANDOM_SEED, -TEST_VALUE_RANGE, TEST_VALUE_RANGE );
		m2.Random( i, 6, RANDOM_SEED, -TEST_VALUE_RANGE, TEST_VALUE_RANGE );
		dst.SetSize( 6, 6 );

		bestClocksGeneric = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			StartRecordTime( start );
			p_generic->MatX_MultiplyMatX( dst, m1, m2 );
			StopRecordTime( end );
			GetBest( start, end, bestClocksGeneric );
		}
		tst = dst;

		PrintClocks( va( "generic->MatX_MultiplyMatX 6x%d*%dx6", i, i ), 1, bestClocksGeneric );

		bestClocksSIMD = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			StartRecordTime( start );
			p_simd->MatX_MultiplyMatX( dst, m1, m2 );
			StopRecordTime( end );
			GetBest( start, end, bestClocksSIMD );
		}

		result = dst.Compare( tst, MATX_MATX_SIMD_EPSILON ) ? "ok" : S_COLOR_RED"X";
		PrintClocks( va( "   simd->MatX_MultiplyMatX 6x%d*%dx6 %s", i, i, result ), 1, bestClocksSIMD, bestClocksGeneric );
	}

	Debug::debug(Debug::math,__FUNCTION__) <<"================= Nx6 * 6xN ===================\n" <<endl;

	// Nx6 * 6xN
	for ( i = 1; i <= 5; i++ ) {
		m1.Random( i, 6, RANDOM_SEED, -TEST_VALUE_RANGE, TEST_VALUE_RANGE );
		m2.Random( 6, i, RANDOM_SEED, -TEST_VALUE_RANGE, TEST_VALUE_RANGE );
		dst.SetSize( i, i );

		bestClocksGeneric = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			StartRecordTime( start );
			p_generic->MatX_MultiplyMatX( dst, m1, m2 );
			StopRecordTime( end );
			GetBest( start, end, bestClocksGeneric );
		}
		tst = dst;

		PrintClocks( va( "generic->MatX_MultiplyMatX %dx6*6x%d", i, i ), 1, bestClocksGeneric );

		bestClocksSIMD = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			StartRecordTime( start );
			p_simd->MatX_MultiplyMatX( dst, m1, m2 );
			StopRecordTime( end );
			GetBest( start, end, bestClocksSIMD );
		}

		result = dst.Compare( tst, MATX_MATX_SIMD_EPSILON ) ? "ok" : S_COLOR_RED"X";
		PrintClocks( va( "   simd->MatX_MultiplyMatX %dx6*6x%d %s", i, i, result ), 1, bestClocksSIMD, bestClocksGeneric );
	}

	Debug::debug(Debug::math,__FUNCTION__) <<"================= 6x6 * 6xN ===================\n" <<endl;

	// 6x6 * 6xN
	for ( i = 1; i <= 6; i++ ) {
		m1.Random( 6, 6, RANDOM_SEED, -TEST_VALUE_RANGE, TEST_VALUE_RANGE );
		m2.Random( 6, i, RANDOM_SEED, -TEST_VALUE_RANGE, TEST_VALUE_RANGE );
		dst.SetSize( 6, i );

		bestClocksGeneric = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			StartRecordTime( start );
			p_generic->MatX_MultiplyMatX( dst, m1, m2 );
			StopRecordTime( end );
			GetBest( start, end, bestClocksGeneric );
		}
		tst = dst;

		PrintClocks( va( "generic->MatX_MultiplyMatX 6x6*6x%d", i ), 1, bestClocksGeneric );

		bestClocksSIMD = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			StartRecordTime( start );
			p_simd->MatX_MultiplyMatX( dst, m1, m2 );
			StopRecordTime( end );
			GetBest( start, end, bestClocksSIMD );
		}

		result = dst.Compare( tst, MATX_MATX_SIMD_EPSILON ) ? "ok" : S_COLOR_RED"X";
		PrintClocks( va( "   simd->MatX_MultiplyMatX 6x6*6x%d %s", i, result ), 1, bestClocksSIMD, bestClocksGeneric );
	}
}

/*
============
TestMatXTransposeMultiplyMatX
============
*/
void TestMatXTransposeMultiplyMatX() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	const char *result;
	CMatrizXD m1, m2, dst, tst;

	Debug::debug(Debug::math,__FUNCTION__) <<"================= Nx6 * NxN ===================\n" <<endl;

	// Nx6 * NxN
	for ( i = 1; i <= 5; i++ ) {
		m1.Random( i, 6, RANDOM_SEED, -TEST_VALUE_RANGE, TEST_VALUE_RANGE );
		m2.Random( i, i, RANDOM_SEED, -TEST_VALUE_RANGE, TEST_VALUE_RANGE );
		dst.SetSize( 6, i );

		bestClocksGeneric = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			StartRecordTime( start );
			p_generic->MatX_TransposeMultiplyMatX( dst, m1, m2 );
			StopRecordTime( end );
			GetBest( start, end, bestClocksGeneric );
		}
		tst = dst;

		PrintClocks( va( "generic->MatX_TransMultiplyMatX %dx6*%dx%d", i, i, i ), 1, bestClocksGeneric );

		bestClocksSIMD = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			StartRecordTime( start );
			p_simd->MatX_TransposeMultiplyMatX( dst, m1, m2 );
			StopRecordTime( end );
			GetBest( start, end, bestClocksSIMD );
		}

		result = dst.Compare( tst, MATX_MATX_SIMD_EPSILON ) ? "ok" : S_COLOR_RED"X";
		PrintClocks( va( "   simd->MatX_TransMultiplyMatX %dx6*%dx%d %s", i, i, i, result ), 1, bestClocksSIMD, bestClocksGeneric );
	}

	Debug::debug(Debug::math,__FUNCTION__) <<"================= 6xN * 6x6 ===================\n" <<endl;

	// 6xN * 6x6
	for ( i = 1; i <= 6; i++ ) {
		m1.Random( 6, i, RANDOM_SEED, -TEST_VALUE_RANGE, TEST_VALUE_RANGE );
		m2.Random( 6, 6, RANDOM_SEED, -TEST_VALUE_RANGE, TEST_VALUE_RANGE );
		dst.SetSize( i, 6 );

		bestClocksGeneric = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			StartRecordTime( start );
			p_generic->MatX_TransposeMultiplyMatX( dst, m1, m2 );
			StopRecordTime( end );
			GetBest( start, end, bestClocksGeneric );
		}
		tst = dst;

		PrintClocks( va( "generic->MatX_TransMultiplyMatX 6x%d*6x6", i ), 1, bestClocksGeneric );

		bestClocksSIMD = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			StartRecordTime( start );
			p_simd->MatX_TransposeMultiplyMatX( dst, m1, m2 );
			StopRecordTime( end );
			GetBest( start, end, bestClocksSIMD );
		}

		result = dst.Compare( tst, MATX_MATX_SIMD_EPSILON ) ? "ok" : S_COLOR_RED"X";
		PrintClocks( va( "   simd->MatX_TransMultiplyMatX 6x%d*6x6 %s", i, result ), 1, bestClocksSIMD, bestClocksGeneric );
	}
}

#define MATX_LTS_SIMD_EPSILON		1.0f
#define MATX_LTS_SOLVE_SIZE			100

/*
============
TestMatXLowerTriangularSolve
============
*/
void TestMatXLowerTriangularSolve() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	const char *result;
	CMatrizXD L;
	CVectorXD x, b, tst;

	Debug::debug(Debug::math,__FUNCTION__) <<"====================================\n" <<endl;

	L.Random( MATX_LTS_SOLVE_SIZE, MATX_LTS_SOLVE_SIZE, 0, -1.0f, 1.0f );
	x.SetSize( MATX_LTS_SOLVE_SIZE );
	b.Random( MATX_LTS_SOLVE_SIZE, 0, -1.0f, 1.0f );

	for ( i = 1; i < MATX_LTS_SOLVE_SIZE; i++ ) {

		x.Zero( i );

		bestClocksGeneric = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			StartRecordTime( start );
			p_generic->MatX_LowerTriangularSolve( L, x.ToFloatPtr(), b.ToFloatPtr(), i );
			StopRecordTime( end );
			GetBest( start, end, bestClocksGeneric );
		}
		tst = x;
		x.Zero();

		PrintClocks( va( "generic->MatX_LowerTriangularSolve %dx%d", i, i ), 1, bestClocksGeneric );

		bestClocksSIMD = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			StartRecordTime( start );
			p_simd->MatX_LowerTriangularSolve( L, x.ToFloatPtr(), b.ToFloatPtr(), i );
			StopRecordTime( end );
			GetBest( start, end, bestClocksSIMD );
		}

		result = x.Compare( tst, MATX_LTS_SIMD_EPSILON ) ? "ok" : S_COLOR_RED"X";
		PrintClocks( va( "   simd->MatX_LowerTriangularSolve %dx%d %s", i, i, result ), 1, bestClocksSIMD, bestClocksGeneric );
	}
}

/*
============
TestMatXLowerTriangularSolveTranspose
============
*/
void TestMatXLowerTriangularSolveTranspose() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	const char *result;
	CMatrizXD L;
	CVectorXD x, b, tst;

	Debug::debug(Debug::math,__FUNCTION__) <<"====================================\n" <<endl;

	L.Random( MATX_LTS_SOLVE_SIZE, MATX_LTS_SOLVE_SIZE, 0, -1.0f, 1.0f );
	x.SetSize( MATX_LTS_SOLVE_SIZE );
	b.Random( MATX_LTS_SOLVE_SIZE, 0, -1.0f, 1.0f );

	for ( i = 1; i < MATX_LTS_SOLVE_SIZE; i++ ) {

		x.Zero( i );

		bestClocksGeneric = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			StartRecordTime( start );
			p_generic->MatX_LowerTriangularSolveTranspose( L, x.ToFloatPtr(), b.ToFloatPtr(), i );
			StopRecordTime( end );
			GetBest( start, end, bestClocksGeneric );
		}
		tst = x;
		x.Zero();

		PrintClocks( va( "generic->MatX_LowerTriangularSolveT %dx%d", i, i ), 1, bestClocksGeneric );

		bestClocksSIMD = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			StartRecordTime( start );
			p_simd->MatX_LowerTriangularSolveTranspose( L, x.ToFloatPtr(), b.ToFloatPtr(), i );
			StopRecordTime( end );
			GetBest( start, end, bestClocksSIMD );
		}

		result = x.Compare( tst, MATX_LTS_SIMD_EPSILON ) ? "ok" : S_COLOR_RED"X";
		PrintClocks( va( "   simd->MatX_LowerTriangularSolveT %dx%d %s", i, i, result ), 1, bestClocksSIMD, bestClocksGeneric );
	}
}

#define MATX_LDLT_SIMD_EPSILON			0.1f
#define MATX_LDLT_FACTOR_SOLVE_SIZE		64

/*
============
TestMatXLDLTFactor
============
*/
void TestMatXLDLTFactor() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	const char *result;
	CMatrizXD src, original, mat1, mat2;
	CVectorXD invDiag1, invDiag2;

	Debug::debug(Debug::math,__FUNCTION__) <<"====================================\n" <<endl;

	original.SetSize( MATX_LDLT_FACTOR_SOLVE_SIZE, MATX_LDLT_FACTOR_SOLVE_SIZE );
	src.Random( MATX_LDLT_FACTOR_SOLVE_SIZE, MATX_LDLT_FACTOR_SOLVE_SIZE, 0, -1.0f, 1.0f );
	src.TransposeMultiply( original, src );

	for ( i = 1; i < MATX_LDLT_FACTOR_SOLVE_SIZE; i++ ) {

		bestClocksGeneric = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			mat1 = original;
			invDiag1.Zero( MATX_LDLT_FACTOR_SOLVE_SIZE );
			StartRecordTime( start );
			p_generic->MatX_LDLTFactor( mat1, invDiag1, i );
			StopRecordTime( end );
			GetBest( start, end, bestClocksGeneric );
		}

		PrintClocks( va( "generic->MatX_LDLTFactor %dx%d", i, i ), 1, bestClocksGeneric );

		bestClocksSIMD = 0;
		for ( j = 0; j < NUMTESTS; j++ ) {
			mat2 = original;
			invDiag2.Zero( MATX_LDLT_FACTOR_SOLVE_SIZE );
			StartRecordTime( start );
			p_simd->MatX_LDLTFactor( mat2, invDiag2, i );
			StopRecordTime( end );
			GetBest( start, end, bestClocksSIMD );
		}

		result = mat1.Compare( mat2, MATX_LDLT_SIMD_EPSILON ) && invDiag1.Compare( invDiag2, MATX_LDLT_SIMD_EPSILON ) ? "ok" : S_COLOR_RED"X";
		PrintClocks( va( "   simd->MatX_LDLTFactor %dx%d %s", i, i, result ), 1, bestClocksSIMD, bestClocksGeneric );
	}
}

/*
============
TestBlendJoints
============
*/
void TestBlendJoints() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( CJointQuaternion baseJoints[COUNT] );
	ALIGN16( CJointQuaternion joints1[COUNT] );
	ALIGN16( CJointQuaternion joints2[COUNT] );
	ALIGN16( CJointQuaternion blendJoints[COUNT] );
	ALIGN16( int index[COUNT] );
	float lerp = 0.3f;
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i < COUNT; i++ ) {
		CAngles angles;
		angles[0] = srnd.CRandomFloat() * 180.0f;
		angles[1] = srnd.CRandomFloat() * 180.0f;
		angles[2] = srnd.CRandomFloat() * 180.0f;
		baseJoints[i].q = angles.ToQuat();
		baseJoints[i].t[0] = srnd.CRandomFloat() * 10.0f;
		baseJoints[i].t[1] = srnd.CRandomFloat() * 10.0f;
		baseJoints[i].t[2] = srnd.CRandomFloat() * 10.0f;
		angles[0] = srnd.CRandomFloat() * 180.0f;
		angles[1] = srnd.CRandomFloat() * 180.0f;
		angles[2] = srnd.CRandomFloat() * 180.0f;
		blendJoints[i].q = angles.ToQuat();
		blendJoints[i].t[0] = srnd.CRandomFloat() * 10.0f;
		blendJoints[i].t[1] = srnd.CRandomFloat() * 10.0f;
		blendJoints[i].t[2] = srnd.CRandomFloat() * 10.0f;
		index[i] = i;
	}

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		for ( j = 0; j < COUNT; j++ ) {
			joints1[j] = baseJoints[j];
		}
		StartRecordTime( start );
		p_generic->BlendJoints( joints1, blendJoints, lerp, index, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->BlendJoints()", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		for ( j = 0; j < COUNT; j++ ) {
			joints2[j] = baseJoints[j];
		}
		StartRecordTime( start );
		p_simd->BlendJoints( joints2, blendJoints, lerp, index, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( !joints1[i].t.Compare( joints2[i].t, 1e-3f ) ) {
			break;
		}
		if ( !joints1[i].q.Compare( joints2[i].q, 1e-2f ) ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->BlendJoints() %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );
}

/*
============
TestConvertJointQuatsToJointMats
============
*/
void TestConvertJointQuatsToJointMats() {
	int i;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( CJointQuaternion baseJoints[COUNT] );
	ALIGN16( CJointMatriz joints1[COUNT] );
	ALIGN16( CJointMatriz joints2[COUNT] );
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i < COUNT; i++ ) {
		CAngles angles;
		angles[0] = srnd.CRandomFloat() * 180.0f;
		angles[1] = srnd.CRandomFloat() * 180.0f;
		angles[2] = srnd.CRandomFloat() * 180.0f;
		baseJoints[i].q = angles.ToQuat();
		baseJoints[i].t[0] = srnd.CRandomFloat() * 10.0f;
		baseJoints[i].t[1] = srnd.CRandomFloat() * 10.0f;
		baseJoints[i].t[2] = srnd.CRandomFloat() * 10.0f;
	}

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->ConvertJointQuatsToJointMats( joints1, baseJoints, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->ConvertJointQuatsToJointMats()", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->ConvertJointQuatsToJointMats( joints2, baseJoints, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( !joints1[i].Compare( joints2[i], 1e-4f ) ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->ConvertJointQuatsToJointMats() %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );
}

/*
============
TestConvertJointMatsToJointQuats
============
*/
void TestConvertJointMatsToJointQuats() {
	int i;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( CJointMatriz baseJoints[COUNT] );
	ALIGN16( CJointQuaternion joints1[COUNT] );
	ALIGN16( CJointQuaternion joints2[COUNT] );
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i < COUNT; i++ ) {
		CAngles angles;
		angles[0] = srnd.CRandomFloat() * 180.0f;
		angles[1] = srnd.CRandomFloat() * 180.0f;
		angles[2] = srnd.CRandomFloat() * 180.0f;
		baseJoints[i].SetRotation( angles.ToMat3() );
		CVector3D v;
		v[0] = srnd.CRandomFloat() * 10.0f;
		v[1] = srnd.CRandomFloat() * 10.0f;
		v[2] = srnd.CRandomFloat() * 10.0f;
		baseJoints[i].SetTranslation( v );
	}

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->ConvertJointMatsToJointQuats( joints1, baseJoints, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->ConvertJointMatsToJointQuats()", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->ConvertJointMatsToJointQuats( joints2, baseJoints, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( !joints1[i].q.Compare( joints2[i].q, 1e-4f ) ) {
			Debug::debug(Debug::math,__FUNCTION__) <<"ConvertJointMatsToJointQuats: broken q: "<< i <<endl;
			break;
		}
		if ( !joints1[i].t.Compare( joints2[i].t, 1e-4f ) ) {
			Debug::debug(Debug::math,__FUNCTION__) <<"ConvertJointMatsToJointQuats: broken t: " << i <<endl;
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->ConvertJointMatsToJointQuats() %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );
}

/*
============
TestTransformJoints
============
*/
void TestTransformJoints() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( CJointMatriz joints[COUNT+1] );
	ALIGN16( CJointMatriz joints1[COUNT+1] );
	ALIGN16( CJointMatriz joints2[COUNT+1] );
	ALIGN16( int parents[COUNT+1] );
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i <= COUNT; i++ ) {
		CAngles angles;
		angles[0] = srnd.CRandomFloat() * 180.0f;
		angles[1] = srnd.CRandomFloat() * 180.0f;
		angles[2] = srnd.CRandomFloat() * 180.0f;
		joints[i].SetRotation( angles.ToMat3() );
		CVector3D v;
		v[0] = srnd.CRandomFloat() * 2.0f;
		v[1] = srnd.CRandomFloat() * 2.0f;
		v[2] = srnd.CRandomFloat() * 2.0f;
		joints[i].SetTranslation( v );
		parents[i] = i - 1;
	}

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		for ( j = 0; j <= COUNT; j++ ) {
			joints1[j] = joints[j];
		}
		StartRecordTime( start );
		p_generic->TransformJoints( joints1, parents, 1, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->TransformJoints()", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		for ( j = 0; j <= COUNT; j++ ) {
			joints2[j] = joints[j];
		}
		StartRecordTime( start );
		p_simd->TransformJoints( joints2, parents, 1, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( !joints1[i+1].Compare( joints2[i+1], 1e-4f ) ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->TransformJoints() %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );
}

/*
============
TestUntransformJoints
============
*/
void TestUntransformJoints() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( CJointMatriz joints[COUNT+1] );
	ALIGN16( CJointMatriz joints1[COUNT+1] );
	ALIGN16( CJointMatriz joints2[COUNT+1] );
	ALIGN16( int parents[COUNT+1] );
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i <= COUNT; i++ ) {
		CAngles angles;
		angles[0] = srnd.CRandomFloat() * 180.0f;
		angles[1] = srnd.CRandomFloat() * 180.0f;
		angles[2] = srnd.CRandomFloat() * 180.0f;
		joints[i].SetRotation( angles.ToMat3() );
		CVector3D v;
		v[0] = srnd.CRandomFloat() * 2.0f;
		v[1] = srnd.CRandomFloat() * 2.0f;
		v[2] = srnd.CRandomFloat() * 2.0f;
		joints[i].SetTranslation( v );
		parents[i] = i - 1;
	}

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		for ( j = 0; j <= COUNT; j++ ) {
			joints1[j] = joints[j];
		}
		StartRecordTime( start );
		p_generic->UntransformJoints( joints1, parents, 1, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->UntransformJoints()", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		for ( j = 0; j <= COUNT; j++ ) {
			joints2[j] = joints[j];
		}
		StartRecordTime( start );
		p_simd->UntransformJoints( joints2, parents, 1, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( !joints1[i+1].Compare( joints2[i+1], 1e-4f ) ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->UntransformJoints() %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );
}

/*
============
TestTransformVerts
============
*/
#define NUMJOINTS	64
#define NUMVERTS	COUNT/2
void TestTransformVerts() {
	int i;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( CDrawVertice drawVerts1[NUMVERTS] );
	ALIGN16( CDrawVertice drawVerts2[NUMVERTS] );
	ALIGN16( CJointMatriz joints[NUMJOINTS] );
	ALIGN16( CVector4D weights[COUNT] );
	ALIGN16( int weightIndex[COUNT*2] );
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i < NUMJOINTS; i++ ) {
		CAngles angles;
		angles[0] = srnd.CRandomFloat() * 180.0f;
		angles[1] = srnd.CRandomFloat() * 180.0f;
		angles[2] = srnd.CRandomFloat() * 180.0f;
		joints[i].SetRotation( angles.ToMat3() );
		CVector3D v;
		v[0] = srnd.CRandomFloat() * 2.0f;
		v[1] = srnd.CRandomFloat() * 2.0f;
		v[2] = srnd.CRandomFloat() * 2.0f;
		joints[i].SetTranslation( v );
	}

	for ( i = 0; i < COUNT; i++ ) {
		weights[i][0] = srnd.CRandomFloat() * 2.0f;
		weights[i][1] = srnd.CRandomFloat() * 2.0f;
		weights[i][2] = srnd.CRandomFloat() * 2.0f;
		weights[i][3] = srnd.CRandomFloat();
		weightIndex[i*2+0] = ( i * NUMJOINTS / COUNT ) * sizeof( CJointMatriz );
		weightIndex[i*2+1] = i & 1;
	}

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->TransformVerts( drawVerts1, NUMVERTS, joints, weights, weightIndex, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->TransformVerts()", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->TransformVerts( drawVerts2, NUMVERTS, joints, weights, weightIndex, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < NUMVERTS; i++ ) {
		if ( !drawVerts1[i].xyz.Compare( drawVerts2[i].xyz, 0.5f ) ) {
			break;
		}
	}
	result = ( i >= NUMVERTS ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->TransformVerts() %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );
}

/*
============
TestTracePointCull
============
*/
void TestTracePointCull() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( CPlane planes[4] );
	ALIGN16( CDrawVertice drawVerts[COUNT] );
	ALIGN16( SGF_Byte cullBits1[COUNT] );
	ALIGN16( SGF_Byte cullBits2[COUNT] );
	SGF_Byte totalOr1 = 0, totalOr2 = 0;
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	planes[0].SetNormal( CVector3D(  1,  0, 0 ) );
	planes[1].SetNormal( CVector3D( -1,  0, 0 ) );
	planes[2].SetNormal( CVector3D(  0,  1, 0 ) );
	planes[3].SetNormal( CVector3D(  0, -1, 0 ) );
	planes[0][3] = -5.3f;
	planes[1][3] = 5.3f;
	planes[2][3] = -3.4f;
	planes[3][3] = 3.4f;

	for ( i = 0; i < COUNT; i++ ) {
		for ( j = 0; j < 3; j++ ) {
			drawVerts[i].xyz[j] = srnd.CRandomFloat() * 10.0f;
		}
	}

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->TracePointCull( cullBits1, totalOr1, 0.0f, planes, drawVerts, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->TracePointCull()", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->TracePointCull( cullBits2, totalOr2, 0.0f, planes, drawVerts, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( cullBits1[i] != cullBits2[i] ) {
			break;
		}
	}
	result = ( i >= COUNT && totalOr1 == totalOr2 ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->TracePointCull() %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );
}

/*
============
TestDecalPointCull
============
*/
void TestDecalPointCull() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( CPlane planes[6] );
	ALIGN16( CDrawVertice drawVerts[COUNT] );
	ALIGN16( SGF_Byte cullBits1[COUNT] );
	ALIGN16( SGF_Byte cullBits2[COUNT] );
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	planes[0].SetNormal( CVector3D(  1,  0,  0 ) );
	planes[1].SetNormal( CVector3D( -1,  0,  0 ) );
	planes[2].SetNormal( CVector3D(  0,  1,  0 ) );
	planes[3].SetNormal( CVector3D(  0, -1,  0 ) );
	planes[4].SetNormal( CVector3D(  0,  0,  1 ) );
	planes[5].SetNormal( CVector3D(  0,  0, -1 ) );
	planes[0][3] = -5.3f;
	planes[1][3] = 5.3f;
	planes[2][3] = -4.4f;
	planes[3][3] = 4.4f;
	planes[4][3] = -3.5f;
	planes[5][3] = 3.5f;

	for ( i = 0; i < COUNT; i++ ) {
		for ( j = 0; j < 3; j++ ) {
			drawVerts[i].xyz[j] = srnd.CRandomFloat() * 10.0f;
		}
	}

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->DecalPointCull( cullBits1, planes, drawVerts, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->DecalPointCull()", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->DecalPointCull( cullBits2, planes, drawVerts, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( cullBits1[i] != cullBits2[i] ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->DecalPointCull() %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );
}

/*
============
TestOverlayPointCull
============
*/
void TestOverlayPointCull() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( CPlane planes[2] );
	ALIGN16( CDrawVertice drawVerts[COUNT] );
	ALIGN16( SGF_Byte cullBits1[COUNT] );
	ALIGN16( SGF_Byte cullBits2[COUNT] );
	ALIGN16( CVector2D texCoords1[COUNT] );
	ALIGN16( CVector2D texCoords2[COUNT] );
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	planes[0].SetNormal( CVector3D( 0.3f, 0.2f, 0.9f ) );
	planes[1].SetNormal( CVector3D( 0.9f, 0.2f, 0.3f ) );
	planes[0][3] = -5.3f;
	planes[1][3] = -4.3f;

	for ( i = 0; i < COUNT; i++ ) {
		for ( j = 0; j < 3; j++ ) {
			drawVerts[i].xyz[j] = srnd.CRandomFloat() * 10.0f;
		}
	}

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->OverlayPointCull( cullBits1, texCoords1, planes, drawVerts, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->OverlayPointCull()", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->OverlayPointCull( cullBits2, texCoords2, planes, drawVerts, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( cullBits1[i] != cullBits2[i] ) {
			break;
		}
		if ( !texCoords1[i].Compare( texCoords2[i], 1e-4f ) ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->OverlayPointCull() %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );
}

/*
============
TestDeriveTriPlanes
============
*/
void TestDeriveTriPlanes() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( CDrawVertice drawVerts1[COUNT] );
	ALIGN16( CDrawVertice drawVerts2[COUNT] );
	ALIGN16( CPlane planes1[COUNT] );
	ALIGN16( CPlane planes2[COUNT] );
	ALIGN16( int indexes[COUNT*3] );
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i < COUNT; i++ ) {
		for ( j = 0; j < 3; j++ ) {
			drawVerts1[i].xyz[j] = srnd.CRandomFloat() * 10.0f;
		}
		for ( j = 0; j < 2; j++ ) {
			drawVerts1[i].st[j] = srnd.CRandomFloat();
		}
		drawVerts2[i] = drawVerts1[i];
	}

	for ( i = 0; i < COUNT; i++ ) {
		indexes[i*3+0] = ( i + 0 ) % COUNT;
		indexes[i*3+1] = ( i + 1 ) % COUNT;
		indexes[i*3+2] = ( i + 2 ) % COUNT;
	}

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->DeriveTriPlanes( planes1, drawVerts1, COUNT, indexes, COUNT*3 );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->DeriveTriPlanes()", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->DeriveTriPlanes( planes2, drawVerts2, COUNT, indexes, COUNT*3 );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( !planes1[i].Compare( planes2[i], 1e-1f, 1e-1f ) ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->DeriveTriPlanes() %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );
}

/*
============
TestDeriveTangents
============
*/
void TestDeriveTangents() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( CDrawVertice drawVerts1[COUNT] );
	ALIGN16( CDrawVertice drawVerts2[COUNT] );
	ALIGN16( CPlane planes1[COUNT] );
	ALIGN16( CPlane planes2[COUNT] );
	ALIGN16( int indexes[COUNT*3] );
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i < COUNT; i++ ) {
		for ( j = 0; j < 3; j++ ) {
			drawVerts1[i].xyz[j] = srnd.CRandomFloat() * 10.0f;
		}
		for ( j = 0; j < 2; j++ ) {
			drawVerts1[i].st[j] = srnd.CRandomFloat();
		}
		drawVerts2[i] = drawVerts1[i];
	}

	for ( i = 0; i < COUNT; i++ ) {
		indexes[i*3+0] = ( i + 0 ) % COUNT;
		indexes[i*3+1] = ( i + 1 ) % COUNT;
		indexes[i*3+2] = ( i + 2 ) % COUNT;
	}

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->DeriveTangents( planes1, drawVerts1, COUNT, indexes, COUNT*3 );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->DeriveTangents()", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->DeriveTangents( planes2, drawVerts2, COUNT, indexes, COUNT*3 );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		CVector3D v1, v2;

		v1 = drawVerts1[i].normal;
		v1.Normalize();
		v2 = drawVerts2[i].normal;
		v2.Normalize();
		if ( !v1.Compare( v2, 1e-1f ) ) {
			Debug::debug(Debug::math,__FUNCTION__) <<"DeriveTangents: broken at tangent0: "<< i<< " -- expecting "<< v1.ToString()<<" got: " <<v2.ToString()<<endl;
			break;
		}
		v1 = drawVerts1[i].tangents[0];
		v1.Normalize();
		v2 = drawVerts2[i].tangents[0];
		v2.Normalize();
		if ( !v1.Compare( v2, 1e-1f ) ) {
			Debug::debug(Debug::math,__FUNCTION__) <<"DeriveTangents: broken at tangent0: "<< i<< " -- expecting "<< v1.ToString()<<" got: " <<v2.ToString()<<endl;
			break;
		}
		v1 = drawVerts1[i].tangents[1];
		v1.Normalize();
		v2 = drawVerts2[i].tangents[1];
		v2.Normalize();
		if ( !v1.Compare( v2, 1e-1f ) ) {
			Debug::debug(Debug::math,__FUNCTION__) <<"DeriveTangents: broken at tangent1: "<< i<<" -- expecting " << v1.ToString()<<" got: "<< v2.ToString()<<endl;
			break;
		}
		if ( !planes1[i].Compare( planes2[i], 1e-1f, 1e-1f ) ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->DeriveTangents() %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );
}

/*
============
TestDeriveUnsmoothedTangents
============
*/
/*
void TestDeriveUnsmoothedTangents() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( CDrawVertice drawVerts1[COUNT] );
	ALIGN16( CDrawVertice drawVerts2[COUNT] );
	ALIGN16( dominantTri_s dominantTris[COUNT] );
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i < COUNT; i++ ) {
		for ( j = 0; j < 3; j++ ) {
			drawVerts1[i].xyz[j] = srnd.CRandomFloat() * 10.0f;
		}
		for ( j = 0; j < 2; j++ ) {
			drawVerts1[i].st[j] = srnd.CRandomFloat();
		}
		drawVerts2[i] = drawVerts1[i];

		dominantTris[i].v2 = ( i + 1 + srnd.RandomInt( 8 ) ) % COUNT;
		dominantTris[i].v3 = ( i + 9 + srnd.RandomInt( 8 ) ) % COUNT;
		dominantTris[i].normalizationScale[0] = srnd.CRandomFloat();
		dominantTris[i].normalizationScale[1] = srnd.CRandomFloat();
		dominantTris[i].normalizationScale[2] = srnd.CRandomFloat();
	}

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->DeriveUnsmoothedTangents( drawVerts1, dominantTris, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->DeriveUnsmoothedTangents()", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->DeriveUnsmoothedTangents( drawVerts2, dominantTris, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		CVector3D v1, v2;

		v1 = drawVerts1[i].normal;
		v1.Normalize();
		v2 = drawVerts2[i].normal;
		v2.Normalize();
		if ( !v1.Compare( v2, 1e-1f ) ) {
			break;
		}
		v1 = drawVerts1[i].tangents[0];
		v1.Normalize();
		v2 = drawVerts2[i].tangents[0];
		v2.Normalize();
		if ( !v1.Compare( v2, 1e-1f ) ) {
			break;
		}
		v1 = drawVerts1[i].tangents[1];
		v1.Normalize();
		v2 = drawVerts2[i].tangents[1];
		v2.Normalize();
		if ( !v1.Compare( v2, 1e-1f ) ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->DeriveUnsmoothedTangents() %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );
}
*/
/*
============
TestNormalizeTangents
============
*/
void TestNormalizeTangents() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( CDrawVertice drawVerts1[COUNT] );
	ALIGN16( CDrawVertice drawVerts2[COUNT] );
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i < COUNT; i++ ) {
		for ( j = 0; j < 3; j++ ) {
			drawVerts1[i].normal[j] = srnd.CRandomFloat() * 10.0f;
			drawVerts1[i].tangents[0][j] = srnd.CRandomFloat() * 10.0f;
			drawVerts1[i].tangents[1][j] = srnd.CRandomFloat() * 10.0f;
		}
		drawVerts2[i] = drawVerts1[i];
	}

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->NormalizeTangents( drawVerts1, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->NormalizeTangents()", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->NormalizeTangents( drawVerts2, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( !drawVerts1[i].normal.Compare( drawVerts2[i].normal, 1e-2f ) ) {
			break;
		}
		if ( !drawVerts1[i].tangents[0].Compare( drawVerts2[i].tangents[0], 1e-2f ) ) {
			break;
		}
		if ( !drawVerts1[i].tangents[1].Compare( drawVerts2[i].tangents[1], 1e-2f ) ) {
			break;
		}

		// since we're doing a lot of unaligned work, added this check to
		// make sure xyz wasn't getting overwritten
		if ( !drawVerts1[i].xyz.Compare( drawVerts2[i].xyz, 1e-2f ) ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->NormalizeTangents() %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );
}

/*
============
TestGetTextureSpaceLightVectors
============
*/
void TestGetTextureSpaceLightVectors() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( CDrawVertice drawVerts[COUNT] );
	ALIGN16( CVector4D texCoords1[COUNT] );
	ALIGN16( CVector4D texCoords2[COUNT] );
	ALIGN16( int indexes[COUNT*3] );
	ALIGN16( CVector3D lightVectors1[COUNT] );
	ALIGN16( CVector3D lightVectors2[COUNT] );
	CVector3D lightOrigin;
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i < COUNT; i++ ) {
		for ( j = 0; j < 3; j++ ) {
			drawVerts[i].xyz[j] = srnd.CRandomFloat() * 100.0f;
			drawVerts[i].normal[j] = srnd.CRandomFloat();
			drawVerts[i].tangents[0][j] = srnd.CRandomFloat();
			drawVerts[i].tangents[1][j] = srnd.CRandomFloat();
		}
	}

	for ( i = 0; i < COUNT; i++ ) {
		indexes[i*3+0] = ( i + 0 ) % COUNT;
		indexes[i*3+1] = ( i + 1 ) % COUNT;
		indexes[i*3+2] = ( i + 2 ) % COUNT;
	}

	lightOrigin[0] = srnd.CRandomFloat() * 100.0f;
	lightOrigin[1] = srnd.CRandomFloat() * 100.0f;
	lightOrigin[2] = srnd.CRandomFloat() * 100.0f;

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->CreateTextureSpaceLightVectors( lightVectors1, lightOrigin, drawVerts, COUNT, indexes, COUNT*3 );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->CreateTextureSpaceLightVectors()", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->CreateTextureSpaceLightVectors( lightVectors2, lightOrigin, drawVerts, COUNT, indexes, COUNT*3 );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( !lightVectors1[i].Compare( lightVectors2[i], 1e-4f ) ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->CreateTextureSpaceLightVectors() %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );
}

/*
============
TestGetSpecularTextureCoords
============
*/
void TestGetSpecularTextureCoords() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( CDrawVertice drawVerts[COUNT] );
	ALIGN16( CVector4D texCoords1[COUNT] );
	ALIGN16( CVector4D texCoords2[COUNT] );
	ALIGN16( int indexes[COUNT*3] );
	ALIGN16( CVector3D lightVectors1[COUNT] );
	ALIGN16( CVector3D lightVectors2[COUNT] );
	CVector3D lightOrigin, viewOrigin;
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i < COUNT; i++ ) {
		for ( j = 0; j < 3; j++ ) {
			drawVerts[i].xyz[j] = srnd.CRandomFloat() * 100.0f;
			drawVerts[i].normal[j] = srnd.CRandomFloat();
			drawVerts[i].tangents[0][j] = srnd.CRandomFloat();
			drawVerts[i].tangents[1][j] = srnd.CRandomFloat();
		}
	}

	for ( i = 0; i < COUNT; i++ ) {
		indexes[i*3+0] = ( i + 0 ) % COUNT;
		indexes[i*3+1] = ( i + 1 ) % COUNT;
		indexes[i*3+2] = ( i + 2 ) % COUNT;
	}

	lightOrigin[0] = srnd.CRandomFloat() * 100.0f;
	lightOrigin[1] = srnd.CRandomFloat() * 100.0f;
	lightOrigin[2] = srnd.CRandomFloat() * 100.0f;
	viewOrigin[0] = srnd.CRandomFloat() * 100.0f;
	viewOrigin[1] = srnd.CRandomFloat() * 100.0f;
	viewOrigin[2] = srnd.CRandomFloat() * 100.0f;

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->CreateSpecularTextureCoords( texCoords1, lightOrigin, viewOrigin, drawVerts, COUNT, indexes, COUNT*3 );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->CreateSpecularTextureCoords()", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->CreateSpecularTextureCoords( texCoords2, lightOrigin, viewOrigin, drawVerts, COUNT, indexes, COUNT*3 );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( !texCoords1[i].Compare( texCoords2[i], 1e-2f ) ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->CreateSpecularTextureCoords() %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );
}

/*
============
TestCreateShadowCache
============
*/
void TestCreateShadowCache() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( CDrawVertice drawVerts[COUNT] );
	ALIGN16( CVector4D vertexCache1[COUNT*2] );
	ALIGN16( CVector4D vertexCache2[COUNT*2] );
	ALIGN16( int originalVertRemap[COUNT] );
	ALIGN16( int vertRemap1[COUNT] );
	ALIGN16( int vertRemap2[COUNT] );
	ALIGN16( CVector3D lightOrigin );
	int numVerts1 = 0, numVerts2 = 0;
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i < COUNT; i++ ) {
		drawVerts[i].xyz[0] = srnd.CRandomFloat() * 100.0f;
		drawVerts[i].xyz[1] = srnd.CRandomFloat() * 100.0f;
		drawVerts[i].xyz[2] = srnd.CRandomFloat() * 100.0f;
		originalVertRemap[i] = ( srnd.CRandomFloat() > 0.0f ) ? -1 : 0;
	}
	lightOrigin[0] = srnd.CRandomFloat() * 100.0f;
	lightOrigin[1] = srnd.CRandomFloat() * 100.0f;
	lightOrigin[2] = srnd.CRandomFloat() * 100.0f;

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		for ( j = 0; j < COUNT; j++ ) {
			vertRemap1[j] = originalVertRemap[j];
		}
		StartRecordTime( start );
		numVerts1 =p_generic->CreateShadowCache( vertexCache1, vertRemap1, lightOrigin, drawVerts, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->CreateShadowCache()", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		for ( j = 0; j < COUNT; j++ ) {
			vertRemap2[j] = originalVertRemap[j];
		}
		StartRecordTime( start );
		numVerts2 = p_simd->CreateShadowCache( vertexCache2, vertRemap2, lightOrigin, drawVerts, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( i < ( numVerts1 / 2 ) ) {
			if ( !vertexCache1[i*2+0].Compare( vertexCache2[i*2+0], 1e-2f ) ) {
				break;
			}
			if ( !vertexCache1[i*2+1].Compare( vertexCache2[i*2+1], 1e-2f ) ) {
				break;
			}
		}
		if ( vertRemap1[i] != vertRemap2[i] ) {
			break;
		}
	}

	result = ( i >= COUNT && numVerts1 == numVerts2 ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->CreateShadowCache() %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_generic->CreateVertexProgramShadowCache( vertexCache1, drawVerts, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->CreateVertexProgramShadowCache()", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		p_simd->CreateVertexProgramShadowCache( vertexCache2, drawVerts, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( !vertexCache1[i*2+0].Compare( vertexCache2[i*2+0], 1e-2f ) ) {
			break;
		}
		if ( !vertexCache1[i*2+1].Compare( vertexCache2[i*2+1], 1e-2f ) ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->CreateVertexProgramShadowCache() %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );
}

/*
============
TestSoundUpSampling
============
*/
#define SOUND_UPSAMPLE_EPSILON		1.0f

void TestSoundUpSampling() {
	int i;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( short pcm[MIXBUFFER_SAMPLES*2] );
	ALIGN16( float ogg0[MIXBUFFER_SAMPLES*2] );
	ALIGN16( float ogg1[MIXBUFFER_SAMPLES*2] );
	ALIGN16( float samples1[MIXBUFFER_SAMPLES*2] );
	ALIGN16( float samples2[MIXBUFFER_SAMPLES*2] );
	float *ogg[2];
	int kHz, numSpeakers;
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i < MIXBUFFER_SAMPLES*2; i++ ) {
		pcm[i] = srnd.RandomInt( (1<<16) ) - (1<<15);
		ogg0[i] = srnd.RandomFloat();
		ogg1[i] = srnd.RandomFloat();
	}

	ogg[0] = ogg0;
	ogg[1] = ogg1;

	for ( numSpeakers = 1; numSpeakers <= 2; numSpeakers++ ) {

		for ( kHz = 11025; kHz <= 44100; kHz *= 2 ) {
			bestClocksGeneric = 0;
			for ( i = 0; i < NUMTESTS; i++ ) {
				StartRecordTime( start );
				p_generic->UpSamplePCMTo44kHz( samples1, pcm, MIXBUFFER_SAMPLES*numSpeakers*kHz/44100, kHz, numSpeakers );
				StopRecordTime( end );
				GetBest( start, end, bestClocksGeneric );
			}
			PrintClocks( va( "generic->UpSamplePCMTo44kHz( %d, %d )", kHz, numSpeakers ), MIXBUFFER_SAMPLES*numSpeakers*kHz/44100, bestClocksGeneric );

			bestClocksSIMD = 0;
			for ( i = 0; i < NUMTESTS; i++ ) {
				StartRecordTime( start );
				p_simd->UpSamplePCMTo44kHz( samples2, pcm, MIXBUFFER_SAMPLES*numSpeakers*kHz/44100, kHz, numSpeakers );
				StopRecordTime( end );
				GetBest( start, end, bestClocksSIMD );
			}

			for ( i = 0; i < MIXBUFFER_SAMPLES*numSpeakers; i++ ) {
				if ( CMath::Fabs( samples1[i] - samples2[i] ) > SOUND_UPSAMPLE_EPSILON ) {
					break;
				}
			}
			result = ( i >= MIXBUFFER_SAMPLES*numSpeakers ) ? "ok" : S_COLOR_RED"X";
			PrintClocks( va( "   simd->UpSamplePCMTo44kHz( %d, %d ) %s", kHz, numSpeakers, result ), MIXBUFFER_SAMPLES*numSpeakers*kHz/44100, bestClocksSIMD, bestClocksGeneric );
		}
	}

	for ( numSpeakers = 1; numSpeakers <= 2; numSpeakers++ ) {

		for ( kHz = 11025; kHz <= 44100; kHz *= 2 ) {
			bestClocksGeneric = 0;
			for ( i = 0; i < NUMTESTS; i++ ) {
				StartRecordTime( start );
				p_generic->UpSampleOGGTo44kHz( samples1, ogg, MIXBUFFER_SAMPLES*numSpeakers*kHz/44100, kHz, numSpeakers );
				StopRecordTime( end );
				GetBest( start, end, bestClocksGeneric );
			}
			PrintClocks( va( "generic->UpSampleOGGTo44kHz( %d, %d )", kHz, numSpeakers ), MIXBUFFER_SAMPLES*numSpeakers*kHz/44100, bestClocksGeneric );

			bestClocksSIMD = 0;
			for ( i = 0; i < NUMTESTS; i++ ) {
				StartRecordTime( start );
				p_simd->UpSampleOGGTo44kHz( samples2, ogg, MIXBUFFER_SAMPLES*numSpeakers*kHz/44100, kHz, numSpeakers );
				StopRecordTime( end );
				GetBest( start, end, bestClocksSIMD );
			}

			for ( i = 0; i < MIXBUFFER_SAMPLES*numSpeakers; i++ ) {
				if ( CMath::Fabs( samples1[i] - samples2[i] ) > SOUND_UPSAMPLE_EPSILON ) {
					break;
				}
			}
			result = ( i >= MIXBUFFER_SAMPLES ) ? "ok" : S_COLOR_RED"X";
			PrintClocks( va( "   simd->UpSampleOGGTo44kHz( %d, %d ) %s", kHz, numSpeakers, result ), MIXBUFFER_SAMPLES*numSpeakers*kHz/44100, bestClocksSIMD, bestClocksGeneric );
		}
	}
}

/*
============
TestSoundMixing
============
*/
#define SOUND_MIX_EPSILON		2.0f

void TestSoundMixing() {
	int i, j;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( float origMixBuffer[MIXBUFFER_SAMPLES*6] );
	ALIGN16( float mixBuffer1[MIXBUFFER_SAMPLES*6] );
	ALIGN16( float mixBuffer2[MIXBUFFER_SAMPLES*6] );
	ALIGN16( float samples[MIXBUFFER_SAMPLES*6] );
	ALIGN16( short outSamples1[MIXBUFFER_SAMPLES*6] );
	ALIGN16( short outSamples2[MIXBUFFER_SAMPLES*6] );
	float lastV[6];
	float currentV[6];
	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i < 6; i++ ) {
		lastV[i] = srnd.CRandomFloat();
		currentV[i] = srnd.CRandomFloat();
	}

	for ( i = 0; i < MIXBUFFER_SAMPLES*6; i++ ) {
		origMixBuffer[i] = srnd.CRandomFloat();
		samples[i] = srnd.RandomInt( (1<<16) ) - (1<<15);
	}

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		for ( j = 0; j < MIXBUFFER_SAMPLES*6; j++ ) {
			mixBuffer1[j] = origMixBuffer[j];
		}
		StartRecordTime( start );
		p_generic->MixSoundTwoSpeakerMono( mixBuffer1, samples, MIXBUFFER_SAMPLES, lastV, currentV );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->MixSoundTwoSpeakerMono()", MIXBUFFER_SAMPLES, bestClocksGeneric );


	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		for ( j = 0; j < MIXBUFFER_SAMPLES*6; j++ ) {
			mixBuffer2[j] = origMixBuffer[j];
		}
		StartRecordTime( start );
		p_simd->MixSoundTwoSpeakerMono( mixBuffer2, samples, MIXBUFFER_SAMPLES, lastV, currentV );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < MIXBUFFER_SAMPLES*6; i++ ) {
		if ( CMath::Fabs( mixBuffer1[i] - mixBuffer2[i] ) > SOUND_MIX_EPSILON ) {
			break;
		}
	}
	result = ( i >= MIXBUFFER_SAMPLES*6 ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->MixSoundTwoSpeakerMono() %s", result ), MIXBUFFER_SAMPLES, bestClocksSIMD, bestClocksGeneric );

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		for ( j = 0; j < MIXBUFFER_SAMPLES*6; j++ ) {
			mixBuffer1[j] = origMixBuffer[j];
		}
		StartRecordTime( start );
		p_generic->MixSoundTwoSpeakerStereo( mixBuffer1, samples, MIXBUFFER_SAMPLES, lastV, currentV );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->MixSoundTwoSpeakerStereo()", MIXBUFFER_SAMPLES, bestClocksGeneric );


	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		for ( j = 0; j < MIXBUFFER_SAMPLES*6; j++ ) {
			mixBuffer2[j] = origMixBuffer[j];
		}
		StartRecordTime( start );
		p_simd->MixSoundTwoSpeakerStereo( mixBuffer2, samples, MIXBUFFER_SAMPLES, lastV, currentV );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < MIXBUFFER_SAMPLES*6; i++ ) {
		if ( CMath::Fabs( mixBuffer1[i] - mixBuffer2[i] ) > SOUND_MIX_EPSILON ) {
			break;
		}
	}
	result = ( i >= MIXBUFFER_SAMPLES*6 ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->MixSoundTwoSpeakerStereo() %s", result ), MIXBUFFER_SAMPLES, bestClocksSIMD, bestClocksGeneric );


	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		for ( j = 0; j < MIXBUFFER_SAMPLES*6; j++ ) {
			mixBuffer1[j] = origMixBuffer[j];
		}
		StartRecordTime( start );
		p_generic->MixSoundSixSpeakerMono( mixBuffer1, samples, MIXBUFFER_SAMPLES, lastV, currentV );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->MixSoundSixSpeakerMono()", MIXBUFFER_SAMPLES, bestClocksGeneric );


	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		for ( j = 0; j < MIXBUFFER_SAMPLES*6; j++ ) {
			mixBuffer2[j] = origMixBuffer[j];
		}
		StartRecordTime( start );
		p_simd->MixSoundSixSpeakerMono( mixBuffer2, samples, MIXBUFFER_SAMPLES, lastV, currentV );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < MIXBUFFER_SAMPLES*6; i++ ) {
		if ( CMath::Fabs( mixBuffer1[i] - mixBuffer2[i] ) > SOUND_MIX_EPSILON ) {
			break;
		}
	}
	result = ( i >= MIXBUFFER_SAMPLES*6 ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->MixSoundSixSpeakerMono() %s", result ), MIXBUFFER_SAMPLES, bestClocksSIMD, bestClocksGeneric );

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		for ( j = 0; j < MIXBUFFER_SAMPLES*6; j++ ) {
			mixBuffer1[j] = origMixBuffer[j];
		}
		StartRecordTime( start );
		p_generic->MixSoundSixSpeakerStereo( mixBuffer1, samples, MIXBUFFER_SAMPLES, lastV, currentV );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->MixSoundSixSpeakerStereo()", MIXBUFFER_SAMPLES, bestClocksGeneric );


	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		for ( j = 0; j < MIXBUFFER_SAMPLES*6; j++ ) {
			mixBuffer2[j] = origMixBuffer[j];
		}
		StartRecordTime( start );
		p_simd->MixSoundSixSpeakerStereo( mixBuffer2, samples, MIXBUFFER_SAMPLES, lastV, currentV );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < MIXBUFFER_SAMPLES*6; i++ ) {
		if ( CMath::Fabs( mixBuffer1[i] - mixBuffer2[i] ) > SOUND_MIX_EPSILON ) {
			break;
		}
	}
	result = ( i >= MIXBUFFER_SAMPLES*6 ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->MixSoundSixSpeakerStereo() %s", result ), MIXBUFFER_SAMPLES, bestClocksSIMD, bestClocksGeneric );


	for ( i = 0; i < MIXBUFFER_SAMPLES*6; i++ ) {
		origMixBuffer[i] = srnd.RandomInt( (1<<17) ) - (1<<16);
	}

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		for ( j = 0; j < MIXBUFFER_SAMPLES*6; j++ ) {
			mixBuffer1[j] = origMixBuffer[j];
		}
		StartRecordTime( start );
		p_generic->MixedSoundToSamples( outSamples1, mixBuffer1, MIXBUFFER_SAMPLES*6 );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->MixedSoundToSamples()", MIXBUFFER_SAMPLES, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		for ( j = 0; j < MIXBUFFER_SAMPLES*6; j++ ) {
			mixBuffer2[j] = origMixBuffer[j];
		}
		StartRecordTime( start );
		p_simd->MixedSoundToSamples( outSamples2, mixBuffer2, MIXBUFFER_SAMPLES*6 );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < MIXBUFFER_SAMPLES*6; i++ ) {
		if ( outSamples1[i] != outSamples2[i] ) {
			break;
		}
	}
	result = ( i >= MIXBUFFER_SAMPLES*6 ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->MixedSoundToSamples() %s", result ), MIXBUFFER_SAMPLES, bestClocksSIMD, bestClocksGeneric );
}

/*
============
TestMath
============
*/
void TestMath() {
	int i;
	TIME_TYPE start, end, bestClocks;

	Debug::debug(Debug::math,__FUNCTION__) <<"====================================\n" <<endl;

	float tst = -1.0f;
	float tst2 = 1.0f;
	float testvar = 1.0f;
	CRamdom rnd;

	bestClocks = 0;
	tst = rnd.CRandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		tst = fabs( tst );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst;
		tst = rnd.CRandomFloat();
	}
	PrintClocks( "            fabs( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = rnd.CRandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		int tmp = * ( int * ) &tst;
		tmp &= 0x7FFFFFFF;
		tst = * ( float * ) &tmp;
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst;
		tst = rnd.CRandomFloat();
	}
	PrintClocks( "    CMath::Fabs( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = 10.0f + 100.0f * rnd.RandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		tst = sqrt( tst );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst * 0.01f;
		tst = 10.0f + 100.0f * rnd.RandomFloat();
	}
	PrintClocks( "            sqrt( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = rnd.RandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		tst = CMath::Sqrt( tst );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst;
		tst = rnd.RandomFloat();
	}
	PrintClocks( "    CMath::Sqrt( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = rnd.RandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		tst = CMath::Sqrt16( tst );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst;
		tst = rnd.RandomFloat();
	}
	PrintClocks( "  CMath::Sqrt16( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = rnd.RandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		tst = CMath::Sqrt64( tst );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst;
		tst = rnd.RandomFloat();
	}
	PrintClocks( "  CMath::Sqrt64( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = rnd.RandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		tst = tst * CMath::RSqrt( tst );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst;
		tst = rnd.RandomFloat();
	}
	PrintClocks( "   CMath::RSqrt( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = rnd.CRandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		tst = CMath::Sin( tst );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst;
		tst = rnd.CRandomFloat();
	}
	PrintClocks( "     CMath::Sin( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = rnd.CRandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		tst = CMath::Sin16( tst );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst;
		tst = rnd.CRandomFloat();
	}
	PrintClocks( "   CMath::Sin16( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = rnd.CRandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		tst = CMath::Cos( tst );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst;
		tst = rnd.CRandomFloat();
	}
	PrintClocks( "     CMath::Cos( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = rnd.CRandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		tst = CMath::Cos16( tst );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst;
		tst = rnd.CRandomFloat();
	}
	PrintClocks( "   CMath::Cos16( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = rnd.CRandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		CMath::SinCos( tst, tst, tst2 );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst;
		tst = rnd.CRandomFloat();
	}
	PrintClocks( "  CMath::SinCos( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = rnd.CRandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		CMath::SinCos16( tst, tst, tst2 );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst;
		tst = rnd.CRandomFloat();
	}
	PrintClocks( "CMath::SinCos16( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = rnd.CRandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		tst = CMath::Tan( tst );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst;
		tst = rnd.CRandomFloat();
	}
	PrintClocks( "     CMath::Tan( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = rnd.CRandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		tst = CMath::Tan16( tst );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst;
		tst = rnd.CRandomFloat();
	}
	PrintClocks( "   CMath::Tan16( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = rnd.CRandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		tst = CMath::ASin( tst );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst * ( 1.0f / CMath::PI );
		tst = rnd.CRandomFloat();
	}
	PrintClocks( "    CMath::ASin( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = rnd.CRandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		tst = CMath::ASin16( tst );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst * ( 1.0f / CMath::PI );
		tst = rnd.CRandomFloat();
	}
	PrintClocks( "  CMath::ASin16( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = rnd.CRandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		tst = CMath::ACos( tst );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst * ( 1.0f / CMath::PI );
		tst = rnd.CRandomFloat();
	}
	PrintClocks( "    CMath::ACos( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = rnd.CRandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		tst = CMath::ACos16( tst );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst * ( 1.0f / CMath::PI );
		tst = rnd.CRandomFloat();
	}
	PrintClocks( "  CMath::ACos16( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = rnd.CRandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		tst = CMath::ATan( tst );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst;
		tst = rnd.CRandomFloat();
	}
	PrintClocks( "    CMath::ATan( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = rnd.CRandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		tst = CMath::ATan16( tst );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst;
		tst = rnd.CRandomFloat();
	}
	PrintClocks( "  CMath::ATan16( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = rnd.CRandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		tst = CMath::Pow( 2.7f, tst );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst * 0.1f;
		tst = rnd.CRandomFloat();
	}
	PrintClocks( "    CMath::Pow( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = rnd.CRandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		tst = CMath::Pow16( 2.7f, tst );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst * 0.1f;
		tst = rnd.CRandomFloat();
	}
	PrintClocks( "  CMath::Pow16( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = rnd.CRandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		tst = CMath::Exp( tst );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst * 0.1f;
		tst = rnd.CRandomFloat();
	}
	PrintClocks( "    CMath::Exp( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = rnd.CRandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		tst = CMath::Exp16( tst );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst * 0.1f;
		tst = rnd.CRandomFloat();
	}
	PrintClocks( "  CMath::Exp16( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = rnd.CRandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		tst = fabs( tst ) + 1.0f;
		StartRecordTime( start );
		tst = CMath::Log( tst );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst;
		tst = rnd.CRandomFloat();
	}
	PrintClocks( "    CMath::Log( tst )", 1, bestClocks );

	bestClocks = 0;
	tst = rnd.CRandomFloat();
	for ( i = 0; i < NUMTESTS; i++ ) {
		tst = fabs( tst ) + 1.0f;
		StartRecordTime( start );
		tst = CMath::Log16( tst );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
		testvar = ( testvar + tst ) * tst;
		tst = rnd.CRandomFloat();
	}
	PrintClocks( "  CMath::Log16( tst )", 1, bestClocks );

      //todo: solve problem in android
		//  Debug::debug(Debug::math,__FUNCTION__) << "testvar = "<< (float)testvar<<endl;

	CMatriz3D resultMat3;
	CQuaternion fromQuat, toQuat, resultQuat;
	CCompQuaternion cq;
	CAngles ang;

	fromQuat = CAngles( 30, 45, 0 ).ToQuat();
	toQuat = CAngles( 45, 0, 0 ).ToQuat();
	cq = CAngles( 30, 45, 0 ).ToQuat().ToCQuat();
	ang = CAngles( 30, 40, 50 );

	bestClocks = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		resultMat3 = fromQuat.ToMat3();
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
	}
	PrintClocks( "       CQuaternion::ToMat3()", 1, bestClocks );

	bestClocks = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		resultQuat.Slerp( fromQuat, toQuat, 0.3f );
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
	}
	PrintClocks( "        CQuaternion::Slerp()", 1, bestClocks );

	bestClocks = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		resultQuat = cq.ToQuat();
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
	}
	PrintClocks( "      CCompQuaternion::ToQuat()", 1, bestClocks );

	bestClocks = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		resultQuat = ang.ToQuat();
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
	}
	PrintClocks( "     CAngles::ToQuat()", 1, bestClocks );

	bestClocks = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {
		StartRecordTime( start );
		resultMat3 = ang.ToMat3();
		StopRecordTime( end );
		GetBest( start, end, bestClocks );
	}
	PrintClocks( "     CAngles::ToMat3()", 1, bestClocks );
}

/*
============
TestNegate
============
*/

// this wasn't previously in the test
void TestNegate() {
	int i;
	TIME_TYPE start, end, bestClocksGeneric, bestClocksSIMD;
	ALIGN16( float fsrc0[COUNT] );
	ALIGN16( float fsrc1[COUNT] );
	ALIGN16( float fsrc2[COUNT] );

	const char *result;

	CRamdom srnd( RANDOM_SEED );

	for ( i = 0; i < COUNT; i++ ) {
		fsrc0[i] = fsrc1[i] = fsrc2[i] = srnd.CRandomFloat() * 10.0f;
		//fsrc1[i] = srnd.CRandomFloat() * 10.0f;
	}

	Debug::debug(Debug::math,__FUNCTION__) <<"====================================\n" <<endl;

	bestClocksGeneric = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {

		memcpy( &fsrc1[0], &fsrc0[0], COUNT * sizeof(float) );

		StartRecordTime( start );
		p_generic->Negate16( fsrc1, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksGeneric );
	}
	PrintClocks( "generic->Negate16( float[] )", COUNT, bestClocksGeneric );

	bestClocksSIMD = 0;
	for ( i = 0; i < NUMTESTS; i++ ) {

		memcpy( &fsrc2[0], &fsrc0[0], COUNT * sizeof(float) );

		StartRecordTime( start );
		p_simd->Negate16( fsrc2, COUNT );
		StopRecordTime( end );
		GetBest( start, end, bestClocksSIMD );
	}

	for ( i = 0; i < COUNT; i++ ) {
		if ( fsrc1[i] != fsrc2[i] ) {
			break;
		}
	}
	result = ( i >= COUNT ) ? "ok" : S_COLOR_RED"X";
	PrintClocks( va( "   simd->Negate16( float[] ) %s", result ), COUNT, bestClocksSIMD, bestClocksGeneric );
}


/*
============
idSIMD::Test_f
============
*/
void idSIMD::Test_f( const CCMDLineArgs &args ) {

#ifdef _WIN32
	SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL );
#endif /* _WIN32 */

	p_simd = processor;
	p_generic = generic;

	if ( CMyString::Length( args.Argv( 1 ) ) != 0 ) {
		cpuid_t cpuid = System::getProcessorId();
		CMyString argString = args.Args();

		argString.Replace( " ", "" );

		if ( CMyString::Icmp( argString, "MMX" ) == 0 ) {
			if ( !( cpuid & CPUID_MMX ) ) {
				Debug::debug(Debug::math,__FUNCTION__) << "CPU does not support MMX\n" <<endl;
				return;
			}
            //p_simd = new CSIMD_MMX;
		} else if ( CMyString::Icmp( argString, "3DNow" ) == 0 ) {
			if ( !( cpuid & CPUID_MMX ) || !( cpuid & CPUID_3DNOW ) ) {
				Debug::debug(Debug::math,__FUNCTION__) << "CPU does not support MMX & 3DNow\n"  <<endl;
				return;
			}
            //p_simd = new CSIMD_3DNow;
		} else if ( CMyString::Icmp( argString, "SSE" ) == 0 ) {
			if ( !( cpuid & CPUID_MMX ) || !( cpuid & CPUID_SSE ) ) {
				Debug::debug(Debug::math,__FUNCTION__) << "CPU does not support MMX & SSE\n" <<endl;
				return;
			}
            //p_simd = new CSIMD_SSE;
		} else if ( CMyString::Icmp( argString, "SSE2" ) == 0 ) {
			if ( !( cpuid & CPUID_MMX ) || !( cpuid & CPUID_SSE ) || !( cpuid & CPUID_SSE2 ) ) {
				Debug::debug(Debug::math,__FUNCTION__) << "CPU does not support MMX & SSE & SSE2\n"  <<endl;
				return;
			}
            //p_simd = new CSIMD_SSE2;
		} else if ( CMyString::Icmp( argString, "SSE3" ) == 0 ) {
			if ( !( cpuid & CPUID_MMX ) || !( cpuid & CPUID_SSE ) || !( cpuid & CPUID_SSE2 ) || !( cpuid & CPUID_SSE3 ) ) {
				Debug::debug(Debug::math,__FUNCTION__) << "CPU does not support MMX & SSE & SSE2 & SSE3\n"  <<endl;
				return;
			}
            //p_simd = new CSIMD_SSE3();
		} else if ( CMyString::Icmp( argString, "AltiVec" ) == 0 ) {
			if ( !( cpuid & CPUID_ALTIVEC ) ) {
				Debug::debug(Debug::math,__FUNCTION__) << "CPU does not support AltiVec\n"  <<endl;
				return;
			}
            //p_simd = new idSIMD_AltiVec();
		} else {
			Debug::debug(Debug::math,__FUNCTION__) << "invalid argument, use: MMX, 3DNow, SSE, SSE2, SSE3, AltiVec\n"  <<endl;
			return;
		}
	}

	//idLib::common->SetRefreshOnPrint( true );

	Debug::debug(Debug::math,__FUNCTION__) << "using %s for SIMD processing: "<< p_simd->GetName() <<endl;

	GetBaseClocks();

	TestMath();
	TestAdd();
	TestSub();
	TestMul();
	TestDiv();
	TestMulAdd();
	TestMulSub();
	TestDot();
	TestCompare();
	TestMinMax();
	TestClamp();
	TestMemcpy();
	TestMemset();
	TestNegate();

	TestMatXMultiplyVecX();
	TestMatXMultiplyAddVecX();
	TestMatXTransposeMultiplyVecX();
	TestMatXTransposeMultiplyAddVecX();
	TestMatXMultiplyMatX();
	TestMatXTransposeMultiplyMatX();
	TestMatXLowerTriangularSolve();
	TestMatXLowerTriangularSolveTranspose();
	TestMatXLDLTFactor();

	Debug::debug(Debug::math,__FUNCTION__) <<"====================================\n" <<endl;

	TestBlendJoints();
	TestConvertJointQuatsToJointMats();
	TestConvertJointMatsToJointQuats();
	TestTransformJoints();
	TestUntransformJoints();
	TestTransformVerts();
	TestTracePointCull();
	TestDecalPointCull();
	TestOverlayPointCull();
	TestDeriveTriPlanes();
	TestDeriveTangents();
	//s TestDeriveUnsmoothedTangents();
	TestNormalizeTangents();
	TestGetTextureSpaceLightVectors();
	TestGetSpecularTextureCoords();
	TestCreateShadowCache();

	Debug::debug(Debug::math,__FUNCTION__) <<"====================================\n" <<endl;

	TestSoundUpSampling();
	TestSoundMixing();

	//idLib::common->SetRefreshOnPrint( false );

	if ( p_simd != processor ) {
		delete p_simd;
	}
	p_simd = NULL;
	p_generic = NULL;

#ifdef _WIN32
	SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_NORMAL );
#endif /* _WIN32 */
}
} //end SGF
