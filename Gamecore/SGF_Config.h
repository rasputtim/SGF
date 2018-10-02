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

#ifndef SGF_CONFIG_H_MYCONF
#define SGF_CONFIG_H_MYCONF
//  SCRIPTING
#include "SGF_Types.h"

//for SDL_IMAGE

#if defined (__GNUC__) && (__GNUC__ >= 2)
#ifndef __STRICT_ANSI__
#define __STRICT_ANSI__
#endif
#endif

// copy operators
#define SGFCpField(name) name = copy.name;
// copy constructors
#define SGFCpConstr(fieldname) fieldname(copy.fieldname),
#define SGFCpConstrLast(fieldname) fieldname(copy.fieldname)
// == operators
#define SGFequalOper(fieldname)  fieldname == him.fieldname

#define SGF_CONFIG_FILE_DIR "open"
#define SGF_CONFIG_FILE_NAME "sgf_configuration.xml"
#define SGF_DEBUG_CONFIG_FILE_NAME "sgf_debug_conf.xml"

#ifndef WINDOWS
#if defined(WIN32) || defined(WIN64) || defined(_WIN32) || defined(_WIN64)
#define WINDOWS
#endif
#endif
#define ENGINE_VERSION "SGF Game Fabric"
//#ifdef  ENOTSOCK   //stupid perl definition
//#undef  ENOTSOCK
//#endif
#if defined( _DEBUG )
	#define	BUILD_DEBUG	"-debug"
#else
	#define	BUILD_DEBUG "-release"
#endif


#include "util/SGF_Debug.h"
//=====================================
// Thread ssupport
//====================================
//http://stackoverflow.com/questions/331536/windows-threading-beginthread-vs-beginthreadex-vs-createthread-c
#ifdef WINDOWS
//#define USE_BEGIN_THREAD
#endif
#define USE_SDL_THREADS
//========================================
#define SGF_SCRIPTING
#if defined(WINDOWS)
#if defined(_MSC_VER)  //linux will find PERL with cmake script
    #define SGF_PERL_SCRIPTING            
	// Perl script is disabled under mingw. I have com compile perl or to find a reliable perl lib under mingw
	//TODO: include perl support wit Mingw
#endif
//#define SGF_PHYTON_SCRIPTING  //you have to have python installed //deve ter instalado phyton
#endif
#define SGF_USE_INTERNAL_TIMER // usa o timer interno ao invés do SDL

#define USE_FASTEVENTS // utiliza as funções de eventos do FastEvents, que são thread safe, ao invés de usar a biblioteca normal do SDL

#ifndef SGF_INLINE
#ifdef WINDOWS

#define SGF_INLINE __inline
#else
#define SGF_INLINE inline
#endif

#endif
#ifndef SGF_INLINE_FORCED
    #if defined (__WINDOWS__ )
            #if defined(_MSC_VER)
            #define SGF_INLINE_FORCED __forceinline
            #endif
        #else
    #define SGF_INLINE_FORCED inline
    #endif
#endif
///////////////////////////////////////////////
// NETWORK SUPPORT
//////////////////////////////////////////////
#ifndef HAVE_NETWORKING
#define HAVE_NETWORKING
#endif

//////////////////////////////////////////////////
//    FONTS
////////////////////////////////////////////////////
#ifdef WINDOWS
#define DEF_FONT_PATH "C:\\WINDOWS\\FONTS\\"
#else
//Todo: verificar o caminho default das fontes no linux
#define DEF_FONT_PATH "/usr/share/fonts/truetype"
#endif

#define	MAX_STRING_CHARS		1024		// max length of a string

// maximum world size
#define MAX_WORLD_COORD			( 128 * 1024 )
#define MIN_WORLD_COORD			( -128 * 1024 )
#define MAX_WORLD_SIZE			( MAX_WORLD_COORD - MIN_WORLD_COORD )


////////////////////////////////////////////////////////////
// Identify the operating system
////////////////////////////////////////////////////////////
#if defined(WIN32) || defined(__WIN32__)
    #include <malloc.h>

    // Windows
    #define SGE_ON_WINDOWS
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif
    #pragma warning( disable : 4290 )
    #pragma warning( disable : 4800 )
    #pragma warning( disable : 4996 )
    #pragma warning( disable : 4561 )
    #pragma warning( disable : 4503 )
    #define BUILD_OS_ID					0
    #define	CPUSTRING					"x86"
    #define CPU_EASYARGS					1
    #if defined(__GNUC__)  // MinGW
        #define	BUILD_STRING					"win-x86-MinGw"
        #define ALIGN16( x )					__attribute__((  aligned(16)  )) x
        #define ALIGNED                         __attribute__((  aligned(16)  ))
        #define _alloca							alloca
        #define _alloca16( x )					((void *)((((int)alloca( (x)+15 )) + 15) & ~15))
        #define _allocafloat16( x )				((void *)((((uintptr_t)alloca( (x)+15 )) + 15) & ~15))
        #define PACKED							__attribute__((packed))
    #else   //MSVC
        #define	BUILD_STRING					"win-x86"
        #define ALIGN16( x )					__declspec(align(16)) x
        #define ALIGNED                         __declspec(align(16))
        #define PACKED
        #define _alloca16( x )					((void *)((((int)_alloca( (x)+15 )) + 15) & ~15))
        #define _allocafloat16( x )				((void *)((((uintptr_t)alloca( (x)+15 )) + 15) & ~15))
    #endif
    #define PATHSEPERATOR_STR				"\\"
    #define PATHSEPERATOR_CHAR				'\\'

    #define ID_STATIC_TEMPLATE				static

    #define assertmem( x, y )				assert( _CrtIsValidPointer( x, y, true ) )
    #ifndef ASSERT
    #if defined(DEBUG) || defined(_DEBUG)
    #define ASSERT(test) if( !(test) ) { \
	fprintf(stderr,"\nASSERT(%s) FAILS, %s line %d\n",#test,__FILE__, __LINE__); exit(0);}
    #else
    #define ASSERT(test)
    #endif
    #endif

#elif defined(linux) || defined(__linux) && !defined(ANDROID)
#ifndef LINUX
#define LINUX
#endif
// Linux
#ifndef SGE_ON_LINUX
#define SGE_ON_LINUX
#endif

#ifdef __x86_64__
#ifndef BUILD_STRING
	#define	BUILD_STRING			"linux-x86-64"
#endif
	#define BUILD_OS_ID				2
	#define CPUSTRING				"x86-64"
	#define CPU_EASYARGS				1
#elif defined(__ppc__)
	#define	BUILD_STRING			"linux-ppc"
	#define CPUSTRING				"ppc"
	#define CPU_EASYARGS				0

#else
	#define	BUILD_STRING				"linux-x86"
	#define BUILD_OS_ID				2
	#define CPUSTRING				"x86"
	#define CPU_EASYARGS				1
#endif
/**
 *
 *
Alloca allocates memory from Stack rather then heap which is case in malloc. So, when I return from the routine the memory is freed. So, actually this solves my problem of freeing up of dynamically allocated memory . Freeing of memory allocated through malloc is a major headache and if somehow missed leads to all sorts memory problems.
So, my question is that in spite of the above features still alloca use is discouraged, why?
The answer is right there in the man page (at least on Linux):
    RETURN VALUE The alloca() function returns a pointer to the beginning of the allocated space. If the allocation causes stack overflow, program behaviour is undefined.
Which isn't to say it should never be used. One of the OSS projects I work on uses it extensively, and as long as you're not abusing it (alloca'ing huge values), it's fine. Once you go past the "few hundred bytes" mark, it's time to use malloc and friends, instead. You may still get allocation failures, but at least you'll have some indication of the failure instead of just blowing out the stack.
http://stackoverflow.com/questions/1018853/why-is-alloca-not-considered-good-practice
 *
 *
 * **/
#define _alloca							alloca
#define _alloca16( x )					((void *)((((uintptr_t)alloca( (x)+15 )) + 15) & ~15))
#define _allocafloat16( x )				((void *)((((uintptr_t)alloca( (x)+15 )) + 15) & ~15))

#define ALIGN16( x )					__attribute__((  aligned(16)  )) x
#define PACKED							__attribute__((packed))

#define PATHSEPERATOR_STR				"/"
#define PATHSEPERATOR_CHAR				'/'

#define __cdecl
#define ASSERT							assert

#define SGF_INLINE_FORCED						inline
#define ID_STATIC_TEMPLATE

#define assertmem( x, y )


#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)
    // MacOS
    #define SGE_ON_MACOS
    #define BUILD_STRING				"MacOSX-universal"
    #define BUILD_OS_ID					1
    #ifdef __ppc__
	#define	CPUSTRING					"ppc"
	#define CPU_EASYARGS				0
    #elif defined(__i386__) || defined (__i686__)
	#define	CPUSTRING					"x86"
	#define CPU_EASYARGS				1
    #endif

    #define ALIGN16( x )					x __attribute__ ((aligned (16)))

    #ifdef __MWERKS__
    #define PACKED
    #include <alloca.h>
    #else
    #define PACKED							__attribute__((packed))
    #endif

    #define _alloca							alloca
    #define _alloca16( x )					((void *)((((int)alloca( (x)+15 )) + 15) & ~15))

    #define PATHSEPERATOR_STR				"/"
    #define PATHSEPERATOR_CHAR				'/'

    #define __cdecl
    #define ASSERT							assert

    #define SGF_INLINE_FORCED						inline
    #define ID_STATIC_TEMPLATE

    #define assertmem( x, y )

    
#elif defined(ANDROID)    
// Android
#ifndef SGE_ON_ANDROID
#define SGE_ON_ANDROID
#endif


    #ifndef BUILD_STRING
        #define	BUILD_STRING				"Building for Android"
    #endif	
	#define BUILD_OS_ID				3
	#define CPUSTRING				""
	#define CPU_EASYARGS				1

#define _alloca							alloca
#define _alloca16( x )					((void *)((((uintptr_t)alloca( (x)+15 )) + 15) & ~15))
#define _allocafloat16( x )				((void *)((((uintptr_t)alloca( (x)+15 )) + 15) & ~15))

#define ALIGN16( x )					__attribute__((  aligned(16)  )) x
#define PACKED							__attribute__((packed))

#define PATHSEPERATOR_STR				"/"
#define PATHSEPERATOR_CHAR				'/'

#define __cdecl
#define ASSERT							assert

#define SGF_INLINE_FORCED				inline
#define ID_STATIC_TEMPLATE

#define assertmem( x, y )

#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)

    // FreeBSD
    #define SGE_ON_FREEBSD

#else

    // Unsupported system
    #error This operating system is not supported by GF library

#endif

//====================================================================




#ifdef __GNUC__
#define id_attribute(x) __attribute__(x)
#else
#define id_attribute(x)
#endif
///////////////////////////////////////////////////////////
////    FILE SYSTEM
//////////////////////////////////////////////////////////
#ifndef DIR_SEPARATOR
#if defined(__MSDOS) || defined(_WIN32)
	#ifndef DIR_SEPARATOR
	#define DIR_SEPARATOR '\\'
	#endif
#elif defined(_MAC)
/* Not at all sure about this: */
#ifndef DIR_SEPARATOR
#define DIR_SEPARATOR ':'
#endif
#else
#ifndef DIR_SEPARATOR
#define DIR_SEPARATOR '/'
#endif
#endif

#endif
////////////////////////////////////////////////////////////
//  MATH
///////////////////////////////////////////////////////////
#define VECX_SIMD  //use SIMD instructions to math vector calculations

////////////////////////////////////////////////////////////
// Define portable import / export macros
////////////////////////////////////////////////////////////
#if defined(SGE_ON_WINDOWS)

    #ifdef SGE_DYNAMIC

        // Windows platforms
        #ifdef SGE_EXPORTS

            // From DLL side, we must export
            #define SGE_API __declspec(dllexport)

        #else

            // From client application side, we must import
            #define SGE_API __declspec(dllimport)

        #endif

        // For Visual C++ compilers, we also need to turn off this annoying C4251 warning.
        // You can read lots ot different things about it, but the point is the code will
        // just work fine, and so the simplest way to get rid of this warning is to disable it
        #ifdef _MSC_VER

            #pragma warning(disable : 4251)
/* Disable ridiculous warnings so that the code */
/* compiles cleanly using warning level 4.      */

/* nonstandard extension 'single line comment' was used */
#pragma warning(disable: 4001)

// indirection to slightly different base types
#pragma warning(disable: 4057)

// unreferenced formal parameter
#pragma warning(disable: 4100)

// named type definition in parentheses
#pragma warning(disable: 4115)

// nonstandard extension used : nameless struct/union
#pragma warning(disable: 4201)

// nonstandard extension used : benign typedef redefinition
#pragma warning(disable: 4209)

// nonstandard extension used : bit field types other than int
#pragma warning(disable: 4214)

// unreferenced inline function has been removed
#pragma warning(disable: 4514)

// C++ language change: to explicitly specialize class template '%s' use the following syntax:
#pragma warning(disable: 4663)

// Note: Creating precompiled header
#pragma warning(disable: 4699)

// Identifier was truncated to '255' characters in the debug information
#pragma warning(disable: 4786)

//--------------------------------------------------------------------------------------------------
// Do not tolerate the following L4 warnings:

// 'function' : different types for formal and actual parameter 'number'
#pragma warning( error: 4024 )

// formal parameter 'number' different from declaration
#pragma warning( error: 4028 )

// formal parameter 'number' has different type when promoted
#pragma warning( error: 4032 )

// 'identifier1' : 'operator' : different levels of indirection from 'identifier2'
#pragma warning( error: 4047 )

//enumerate 'identifier' in switch of enum 'identifier' is not explicitly handled by a case label
#pragma warning( error: 4061 )

// unreferenced formal parameter
//#pragma warning(disable: 4100)

// unreferenced local variable
//#pragma warning(disable: 4101)

// alignment of a member was sensitive to packing
#pragma warning( error: 4121 )

// logical operation on address of string constant
#pragma warning( error: 4130 )

// const object should be initialized
#pragma warning( error: 4132 )

// An attempt was made to subtract two pointers of different types. (?!)
#pragma warning( error: 4133 )

// local variable is initialized but not referenced
//#pragma warning( error: 4189 )

// nonstandard extension used : float long
#pragma warning( error: 4216 )

// nonstandard extension used : 'identifier' : cannot be initialized using address of automatic variable
#pragma warning( error: 4221 )

// cast truncates constant value
#pragma warning( error: 4310 )

// '==' : operator has no effect; did you intend '='?
#pragma warning( error: 4553 )

// local variable 'identifier' used without having been initialized
#pragma warning( error: 4700 )

// local variable 'identifier' may be used without having been initialized
//#pragma warning( error: 4701 )

// assignment within conditional expression
#pragma warning( error: 4706 )

// not all control paths return a value
#pragma warning( error: 4715 )



        #endif

    #else

        // No specific directive needed for static build
        #define SGE_API

    #endif

#elif defined(ANDROID)

#define SGE_API

#else
    // Other platforms don't need to define anything
    #define SGE_API

#endif

//   TYPES
#if defined(WINDOWS)
#else
typedef unsigned long DWORD;
typedef void* LPVOID;

#endif

#endif
