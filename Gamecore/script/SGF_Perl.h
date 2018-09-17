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

/**
This file helps include perl.h
The windows version of perl.h contains a lot of stupid #defines, this
file helps undefine them.
*/
 #include <string>

#ifndef _S_G_F_PERL_SCRIPTING_h
#define _S_G_F_PERL_SCRIPTING_h

#include "../SGF_Config.h"

#ifdef SGF_SCRIPTING
#include "SGF_Scripting.h"



#ifdef SGF_PERL_SCRIPTING
	//load the library
	//#pragma comment(lib,"perl58")
	


#ifdef _WIN32

#pragma comment(lib,"perl56")
#include "../../ExternalLibs/perl56/win32/CORE/EXTERN.h"
#include "../../ExternalLibs/perl56/win32/CORE/perl.h"

#undef bool
#undef chdir
#undef close
#undef eof
#undef shutdown
#define vsnprintf _vsnprintf
#else
#include "EXTERN.h"  //must be load first
#include <perl.h>
#endif

using namespace std;
namespace SGF {
namespace Script {


/**
 * \class CEngine
 *
 * \ingroup SGF_Scripting
 * 
 * \brief Classe Base para  Script com Perl
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de abril de 2012
 */
class SGE_API CPerlEngine : public CEngine
{
public:

	// Lifecycle
	
	//CPerlEngine(const Filesystem::CAbsolutePath path);
	CPerlEngine(std::string & diretorio, char *script);
	
	~CPerlEngine();
	bool Construct(std::string &diretorio, char *script);
	void init(){};
	void shutdown(){};
	void tick(){};


	// Miscellaneous
	
	const char* perlEvalF( const char* a_pcFormat, ... );
	const char* getPerlString( const char* a_pcScalarName );
	int getPerlInt( const char* a_pcScalarName );
	/*
	Datatypes
	Perl has three typedefs that handle Perl's three main data types:
    SV Scalar Value
    AV Array Value
    HV Hash Value
	*/
	//============== Scalar Methods ============
	/*
	An SV can be created and loaded with one command. 
	There are five types of values that can be loaded: 
	an integer value (IV), 
	an unsigned integer value (UV), 
	a double (NV), 
	a string (PV), 
	and another scalar (SV).
	*/
	//! creating scalars

	//!getting scalars
	static SV * getScalar(char * ScalarName );
	static SV * getScalarF(char * ScalarName );

	//============== Array methods ===========
	//! creating aRRAYS


	static AV * getArray(char * ScalarName );
	static AV * getArrayF(const char * ScalarName );

	static SV * fetchAV(AV * ArrayName,int key );
	static SV * fetchAVFalse(AV * ArrayName,int key );
	static int getArrayLen(AV *Arrayname);

	//============== Hash methods =========
	//!convert SV to C types

	static int  getInt(SV*);
	static double  getDouble(SV*);
	static char * getChar(SV*);
	static char * getCharUTF8(SV*);

	void eval(char *a_pcScalarName );


	//=======routines============
	static void callPerlRoutine(const char* script,const char* script_param);
	static const char* call(const char* script,char*variavel_retorno,SV *perl_variavel, const char* a_pcText);
	static const char* callUTF8(const char* script, char*variavel_retorno,SV *perl_variavel, const char* script_param);

	//work with game variables
/*	void makeMyScalar(char * varName){ my_ScalarList[varName]=NULL;}; //todo verificar se já há um scalar com o mesmo nome antes
	void getMyScalarFromPerl(char *varName){ my_ScalarList[varName]=getScalar(varName);}
	int getMyScalarIntValue(char * varName){ return getInt( my_ScalarList[varName] );}
	SV * getMyScalar(char * varName) { return my_ScalarList[varName];};
private:

	map<char*,SV *> my_ScalarList;
	map<char*,AV *> my_ArrayList;
	map<char*,HV *> my_HashList;
*/
};


} //end scripting
} //end SGF

#endif
#endif
#endif