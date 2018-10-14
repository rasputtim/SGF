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

#include "sys/SGF_System.h"
#ifdef _WIN32

#include <windows.h>
#include <fstream>
#include <psapi.h>
#pragma comment(lib, "psapi.lib") //added
#include "sys/win32/win_public.h"
#include  <io.h>
using namespace std;
#endif

#include <string>
#include  <stdio.h>
#include  <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include "sys/SGF_System.h"
#include "util/SGF_Debug.h"
#include "util/SGF_StringUtils.h"


namespace SGF{

namespace System{

#if defined  (WIN32) && defined(_MSC_VER)
/*
http://msdn.microsoft.com/en-us/library/windows/desktop/ms684877%28v=vs.85%29.aspx
*/
unsigned long memoryUsage(){
    HANDLE id = GetCurrentProcess();
    PROCESS_MEMORY_COUNTERS info;
    BOOL okay = GetProcessMemoryInfo(id, &info, sizeof(info));
    if (okay){
        return info.WorkingSetSize;
    }
    return 0;
}
#else
unsigned long memoryUsage(){
    return 0;
}

#endif
#ifndef _WIN32
//#ifndef WINDOWS
//#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
 #include <sys/time.h>  
 #include <stdio.h>  

uint64_t currentMicroseconds(){
    struct timeval hold;
    gettimeofday(&hold, NULL);
    return hold.tv_sec * 1000 * 1000 + hold.tv_usec;
}
#else

uint64_t currentMicroseconds(){
    LARGE_INTEGER ticksPerSecond;
    LARGE_INTEGER tick;
    QueryPerformanceFrequency(&ticksPerSecond);
    QueryPerformanceCounter(&tick);
    return (tick.QuadPart)/(ticksPerSecond.QuadPart/1000000);
}
#endif
uint64_t currentSeconds(){
    return currentMicroseconds() / (1000 * 1000);
}



void CSysLocal::DebugPrintf( const char *fmt, ... ) {
	va_list argptr;

	va_start( argptr, fmt );
	// Sys_DebugVPrintf( fmt, argptr );
	va_end( argptr );
}

void CSysLocal::DebugVPrintf( const char *fmt, va_list arg ) {
	// Sys_DebugVPrintf( fmt, arg );
}

double CSysLocal::GetClockTicks() {
#if defined(WINDOWS)
    return System::getClockTicks();
#endif
}

    double CSysLocal::ClockTicksPerSecond() {
#ifndef ANDROID
        return System::getClockTicksPerSecond();
#else
        return 0.0;
#endif
    }

    cpuid_t CSysLocal::GetProcessorId() {

#ifndef ANDROID
        return System::getProcessorId();
#else
        return CPUID_NONE;
#endif
    }

    const char *CSysLocal::GetProcessorString() {
#ifndef ANDROID
        return System::getProcessorString();
#else
        return NULL;
#endif

    }

        const char *CSysLocal::FPU_GetState() {
#ifndef ANDROID
	return Sys_FPU_GetState();
#else
return NULL;
#endif
}

bool CSysLocal::FPU_StackIsEmpty() {
#ifndef ANDROID
	return fpu_StackIsEmpty();
#else
    return false;
#endif

}

void CSysLocal::FPU_SetFTZ( bool enable ) {
#ifndef ANDROID
	System::fpu_SetFTZ( enable );
#else
    return ;
#endif

}

void CSysLocal::FPU_SetDAZ( bool enable ) {
#ifndef ANDROID
	System::fpu_SetDAZ( enable );
#else
	return ;
#endif
}

bool CSysLocal::LockMemory( void *ptr, int bytes ) {
#ifndef ANDROID
	return System::lockMemory( ptr, bytes );
#else
	return false;
#endif
}

bool CSysLocal::UnlockMemory( void *ptr, int bytes ) {
#ifndef ANDROID
	return System::unlockMemory( ptr, bytes );
#else
	return false;
#endif
}
/*
void CSysLocal::GetCallStack( address_t *callStack, const int callStackSize ) {
	Sys_GetCallStack( callStack, callStackSize );
}

const char * CSysLocal::GetCallStackStr( const address_t *callStack, const int callStackSize ) {
	return Sys_GetCallStackStr( callStack, callStackSize );
}
*/
const char * CSysLocal::GetCallStackCurStr( int depth ) {
    //sal todo:implement to linux:
    //sal 
#if defined(WINDOWS)
	return Sys_GetCallStackCurStr( depth );
#endif
}

void CSysLocal::ShutdownSymbols() {
    //sal todo:implement to linux:
    //sal
#if defined(WINDOWS)
	Sys_ShutdownSymbols();
#endif
}

void * CSysLocal::DLL_Load( const char *dllName ) {
    //sal todo:implement to linux:
    //sal 
#if defined(WINDOWS)
	return Sys_DLL_Load( dllName );
#endif
}

void *CSysLocal::DLL_GetProcAddress( void * dllHandle, const char *procName ) {
    //sal todo:implement to linux:
    //sal 
#if defined(WINDOWS)
	return Sys_DLL_GetProcAddress( dllHandle, procName );
#endif
}

void CSysLocal::DLL_Unload( void * dllHandle ) {
    //sal todo:implement to linux:
    //sal 
#if defined(WINDOWS)
	Sys_DLL_Unload( dllHandle );
#endif
}

void CSysLocal::DLL_GetFileName( const char *baseName, char *dllName, int maxLength ) {
#ifdef _WIN32
	SGF::CMyString::snPrintf( dllName, maxLength, "%s" CPUSTRING ".dll", baseName );
#elif defined( __linux__ )
	SGF::CMyString::snPrintf( dllName, maxLength, "%s" CPUSTRING ".so", baseName );
#elif defined( MACOS_X )
	SGF::CMyString::snPrintf( dllName, maxLength, "%s" ".dylib", baseName );
#else
#error OS define is required
#endif
}


void CSysLocal::FPU_EnableExceptions( int exceptions ) {
#ifndef ANDROID
	fpu_EnableExceptions( exceptions );
#endif
}

/*
=================
timeStampToStr
=================
*/
const char *timeStampToStr( time_t timeStamp ) {
	static char timeString[MAX_STRING_CHARS];
	timeString[0] = '\0';

	tm*	time = localtime( &timeStamp );
	SGF::CMyString out;
	
	SGF::CMyString lang = "english";//s cvarSystem->GetCVarString( "sys_lang" );
	if ( lang.Icmp( "english" ) == 0 ) {
		// english gets "month/day/year  hour:min" + "am" or "pm"
		out = va( "%02d", time->tm_mon + 1 );
		out += "/";
		out += va( "%02d", time->tm_mday );
		out += "/";
		out += va( "%d", time->tm_year + 1900 );
		out += "\t";
		if ( time->tm_hour > 12 ) {
			out += va( "%02d", time->tm_hour - 12 );
		} else if ( time->tm_hour == 0 ) {
				out += "12";
		} else {
			out += va( "%02d", time->tm_hour );
		}
		out += ":";
		out +=va( "%02d", time->tm_min );
		if ( time->tm_hour >= 12 ) {
			out += "pm";
		} else {
			out += "am";
		}
	} else {
		// europeans get "day/month/year  24hour:min"
		out = va( "%02d", time->tm_mday );
		out += "/";
		out += va( "%02d", time->tm_mon + 1 );
		out += "/";
		out += va( "%d", time->tm_year + 1900 );
		out += "\t";
		out += va( "%02d", time->tm_hour );
		out += ":";
		out += va( "%02d", time->tm_min );
	}
	SGF::CMyString::Copynz( timeString, out, sizeof( timeString ) );

	return timeString;
}



#undef std::sprintf

} //end System
} //end SGF
	
	
