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

// http://docstore.mik.ua/orelly/perl/advprog/ch19_02.htm
// http://www.foo.be/docs/tpj/issues/vol1_4/tpj0104-0009.html



#include "script/SGF_Perl.h"

#ifdef SGF_PERL_SCRIPTING
/***************************************************************************
                  		BACKEND CLASS IMPLEMENTATION
***************************************************************************/


PerlInterpreter*	my_perl;


using namespace std;
namespace SGF {

namespace Script {

/***************************************************************************
                     PUBLIC EXPORTED VARIABLES
***************************************************************************/

//*************************************************************

//***************************************************************
#define PERLEVAL(A) eval_pv(A, TRUE);

#define PERLCALL(PROC,A,B) {							\
    dSP;												\
    ENTER;												\
    SAVETMPS;											\
    PUSHMARK(SP);										\
    XPUSHs(sv_2mortal(newSViv(A)));						\
    XPUSHs(sv_2mortal(newSViv(B)));						\
    PUTBACK ;											\
														\
    call_pv( (PROC),  G_DISCARD );						\
														\
    FREETMPS;											\
    LEAVE;												\
}

/*
CPerlEngine::CPerlEngine(const Filesystem::CAbsolutePath path):
CEngine()
{
	Construct(path.path());
}
*/
CPerlEngine::CPerlEngine(string &path, char *script):
CEngine()
{
	Construct(path,script);
}

CPerlEngine::~CPerlEngine()
{
	if ( NULL != my_perl )
	{
		/* 
 * "destroy" objects and free memory allocated for 
 * the script's symbols, etc. 
 */
		perl_destruct( my_perl );
		/* 
 * free memory allocated for the PerlInterpreter object itself 
 */

		perl_free( my_perl );
		my_perl = NULL;
	}
}


bool CPerlEngine::Construct(string &diretorio, char *script)
{
	if ( my_perl != NULL )
	{
		// Already inited
		return false;
	}
	
	/*//convert const * char to *char
	vector<char> tmp(path.begin(), path.end());
	char * script = &tmp[0];
	script[path.size()] = '\0';
	*/
//	perl_bgx = NULL;
//	perl_doodad_x = NULL;
	
//	string sFileName = "";
//	sFileName += "/script";
//	string dir = Filesystem::getDirName(path);
//	const char *diretorio = dir.c_str();
#ifndef _WIN32_
	chdir( diretorio.c_str());
#endif
	
//	char *perl_argv[] = {"", "-d:Trace", "CPerlEngine.pl"};
//	int perl_argc = 3;

	char *perl_argv[] = {"",script };
	int perl_argc = 2; //o número de arqumentos de argv
	my_perl = perl_alloc();
	if ( my_perl == NULL )
	{
		return false;
	}

	/* 
	* initialize the interpreter, some internal 
	* global variables, and the stack 
	*/ 

	perl_construct( my_perl );
/*
 * perl_parse(my_perl, xs_init, argc, argv, (char **)NULL);
 * initialize some global variables (@ARGV, %INC, etc.)
 * compile the code into perl's internal format 
 * or "parse tree" 
 * 
 * xs_init is a function pointer which is normally
 * used to create the Perl entry point to C libraries,
 * e.g. DynaLoader and static extensions' "bootstrap"
 * methods. argc is the number of elements in the argv
 * array; argv[] contains what is normally the command
 * line arguments passed to the interpreter, e.g.
 *   "/usr/bin/perl", "-e", "print qq(Hello world!)"
 * The final argument may be a char ** array of
 * environment variables. NULL means the current env.
 */
	if ( perl_parse( my_perl, NULL, perl_argc, perl_argv, (char**)NULL ) )
	{
		char *error = SvPV_nolen(get_sv("@", FALSE));
		Debug::debug(SGF::Debug::error,__FUNCTION__) << "Perl Error: " << error  <<endl;
		return false;
	}
	
	/* 
    * interpret the script (walk the parse tree) 
    */
	if ( perl_run( my_perl ) )
	{
		char *error = SvPV_nolen(get_sv("@", FALSE));
		Debug::debug(SGF::Debug::error,__FUNCTION__) << "Perl Error: " << error  <<endl;
		return false;
	}

	return true;
}

/*
Perl provides two API functions to evaluate pieces of Perl code. 
These are eval_sv in perlapi and eval_pv in perlapi.
Arguably, these are the only routines you'll ever need to execute snippets of Perl code from within your C program. 
Your code can be as long as you wish; it can contain multiple statements; 
it can employ use, require, and do to include external Perl files.

eval_pv lets us evaluate individual Perl strings, and then extract variables for coercion into C types.
*/
const char* CPerlEngine::perlEvalF( const char* a_pcFormat, ... )
{
	
	va_list ap;
	va_start( ap, a_pcFormat );
	
	char acBuffer[1024];
	vsnprintf( acBuffer, 1023, a_pcFormat, ap );
	acBuffer[1023] = 0;
	eval_pv(acBuffer,FALSE);
	
	const char *pcError = SvPV_nolen(get_sv("@", FALSE));
	if ( pcError && *pcError )
	{
		//debug( "eval '%s': '%s'\n", acBuffer, pcError );
		//exit(0);
	}
	
	va_end( ap );
	
	return pcError;
}
const char* CPerlEngine::getPerlString( const char* acScalarName )
{
	SV* poScalar = get_sv( acScalarName, FALSE );
	if ( NULL == poScalar )
	{
		return "";
	}
	
	return SvPV_nolen( poScalar );
}


int CPerlEngine::getPerlInt( const char* acScalarName )
{
	SV* poScalar = get_sv( acScalarName, FALSE );
	if ( NULL == poScalar )
	{
		return 0;
	}
	
	return SvIV( poScalar );
}

SV * CPerlEngine::getScalar(char * a_pcScalarName ){
	return get_sv(a_pcScalarName, TRUE);
}

SV * CPerlEngine::getScalarF(char * a_pcScalarName ){
	return get_sv(a_pcScalarName, FALSE);
}

AV * CPerlEngine::getArray(char * a_pcScalarName ){
	return get_av( a_pcScalarName, TRUE );
}
AV * CPerlEngine::getArrayF(const char * a_pcScalarName ){
	return get_av( a_pcScalarName, FALSE );
}

SV * CPerlEngine::fetchAV(AV * a_pcScalarName,int key ){
	return *av_fetch( a_pcScalarName, key, true );
}
SV * CPerlEngine::fetchAVFalse(AV * a_pcScalarName,int key ){
	return *av_fetch( a_pcScalarName, key, false );
}
int CPerlEngine::getArrayLen(AV *array){
	return av_len(array);
}

//http://www.lemoda.net/xs/xs-intro/typemap.html
//must check is var is null before calling the method
int  CPerlEngine::getInt(SV*var) {
	return SvIV(var);
}
double  CPerlEngine::getDouble(SV* var){
	return SvNV(var);
}
char * CPerlEngine::getChar(SV* var){
	return SvPV_nolen(var);	
}
char * CPerlEngine::getCharUTF8(SV* var) {
	return SvPVutf8_nolen(var);	
}
void CPerlEngine::eval(char *a_pcScalarName ){
	PERLEVAL(a_pcScalarName );
}
//! chama a rotina e retorna a variavel
// script: script perl a ser invocado
// variavel_retorno:  variaval a ser pesquisada no script passado
// a_pcText: parâmetro a ser passado para o script

void CPerlEngine::callPerlRoutine(const char* script,const char* script_param){
	dSP ;
	
	ENTER ;
	SAVETMPS ;
	
	PUSHMARK(SP) ;
	XPUSHs(sv_2mortal(newSVpv(script_param, 0)));
	PUTBACK ;
	
	call_pv(script, G_DISCARD);
	FREETMPS ;
	LEAVE ;
}


const char* CPerlEngine::call(const char* script, char*variavel_retorno,SV *perl_variavel, const char* script_param) {

	callPerlRoutine(script,script_param);
	
	if ( NULL == perl_variavel )
	{
		perl_variavel = get_sv(variavel_retorno, TRUE);
	}
	return SvPV_nolen( perl_variavel );

}


const char* CPerlEngine::callUTF8(const char* script, char*variavel_retorno,SV *perl_variavel, const char* script_param) {
	callPerlRoutine(script,script_param);
	if ( NULL == perl_variavel )
	{
		perl_variavel = get_sv(variavel_retorno, TRUE);
	}
	return SvPVutf8_nolen( perl_variavel );

}

} // end namespace
} //end SGF
#endif