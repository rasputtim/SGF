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

#ifndef SGF_TYPES_H_
#define SGF_TYPES_H_
#include <stdio.h>
#include <stdarg.h>
//#include <pstdint.h>   //conflict with SDL_config_windows.h
#ifdef _MSC_VER
#include <string>

#include "../ExternalLibs/SDL2/include/SDL_config_windows.h"
#else
#include <stdint.h>
#include "../ExternalLibs/SDL2/include/SDL_config_windows.h"
#endif
#include <assert.h>
//include this one for MinGW
#include <stdint.h>
///////////////////////////////////////////////////////////
// define alguns tipos
///////////////////////////////////////////////////////////
#ifndef Float64
#define Float64 double
#endif
#ifndef Float32
#define Float32 float
#endif

#define SGF_OK 1
#define SGF_ERROR -1

typedef int8_t					s_byte;
typedef uint8_t					s_ubyte;
typedef int16_t					s_word;
typedef uint16_t				s_uword;
typedef int32_t					s_dword;
typedef uint32_t				s_udword;
typedef int64_t					s_qword;
typedef uint64_t				s_uqword;

typedef uint8_t					SGF_Byte;		// 8 bits
typedef uint16_t				SGF_Word;		// 16 bits
typedef uint32_t				SGF_Dword;     // 32 bits
typedef unsigned int			SGF_Uint;
typedef unsigned long			SGF_Ulong;


#endif
