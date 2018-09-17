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
This file helps include phyton.h
*/
 #include <string>

#ifndef _S_G_F_PHYTON_SCRIPTING_h
#define _S_G_F_PHYTON_SCRIPTING_h

#include "../SGF_Config.h"

#ifdef SGF_PHYTON_SCRIPTING
#include "SGF_Scripting.h"
#include <Python.h>
#include "../configuration/SGF_SysVars.h"
#include "structures/SGF_List.h"
#include "exceptions/all.h"
using namespace std;
namespace SGF {
namespace Script {

 /**
 * \class CPhytonEngine
 *
 * \ingroup SGF_Scripting 
 * 
 * \brief Interface entre C++ e Phyton 
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 10 de Janeiro de 2014
  */
class SGE_API CPhytonEngine : public CEngine
{
private:
	class CContext {
	public:
		CContext(){};
		~CContext(){};
		void init(string filename, string funct, char *argtypes,... ){
			fileName=filename;
			functName=funct;
			ArgTypes= argtypes;
		}
	//private:
	string fileName;
	string functName;
	char *ArgTypes; 

	};

	/*
"s" (string) [char *]
    Convert a null-terminated C string to a Python object. If the C string pointer is NULL, None is returned.

"s#" (string) [char *, int]
    Convert a C string and its length to a Python object. If the C string pointer is NULL, the length is ignored and None is returned.

"z" (string or None) [char *]
    Same as "s".

"z#" (string or None) [char *, int]
    Same as "s#".

"i" (integer) [int]
    Convert a plain C int to a Python integer object.

"b" (integer) [char]
    Same as "i".

"h" (integer) [short int]
    Same as "i".

"l" (integer) [long int]
    Convert a C long int to a Python integer object.

"c" (string of length 1) [char]
    Convert a C int representing a character to a Python string of length 1.

"d" (float) [double]
    Convert a C double to a Python floating point number.

"f" (float) [float]
    Same as "d".

"O" (object) [PyObject *]
    Pass a Python object untouched (except for its reference count, which is incremented by one). If the object passed in is a NULL pointer, it is assumed that this was caused because the call producing the argument found an error and set an exception. Therefore, Py_BuildValue() will return NULL but won't raise an exception. If no exception has been raised yet, PyExc_SystemError is set.

"S" (object) [PyObject *]
    Same as "O".

"N" (object) [PyObject *]
    Same as "O", except it doesn't increment the reference count on the object. Useful when the object is created by a call to an object constructor in the argument list.

"O&" (object) [converter, anything]
    Convert anything to a Python object through a converter function. The function is called with anything (which should be compatible with void *) as its argument and should return a ``new'' Python object, or NULL if an error occurred.

"(items)" (tuple) [matching-items]
    Convert a sequence of C values to a Python tuple with the same number of items.

"[items]" (list) [matching-items]
    Convert a sequence of C values to a Python list with the same number of items.

"{items}" (dictionary) [matching-items] 

	*/
	
	union type_t {
         int     int_;
         float   float_;
         char    *charString_;  //string c (/0 terminated)
         string   *string_; 
		 char    byte_;
		 double  double_;
		 PyObject *object_;
		 void     *other;
		 long int long_;
      };
	 struct valueTypePair_t{
		 type_t value;
		 char type;
	 };
public:
	//CPerlEngine(const Filesystem::CAbsolutePath path);
	CPhytonEngine();
	
	~CPhytonEngine();
	//bool Construct(std::string &diretorio, char *script);
	void init();
	void shutdown(){};
    //virtual void shutdown() = 0;
	void tick(){};

/** \brief roda uma função dentro de um arquivo phyton
\param result: where the result of python function will be stored
\param fileName: nome do arquivo phyton sem a extenção
\param funct: nome da função a ser executada
\param numOfIntArgs: número de arqumentos a serem passados para a função phyton
\param ...: argumentos a serem passados para a função phyton
\note os argumentos devem ser todos do tipo integer.
*/
	void run(long &result,string fileName, string funct, int numOfIntArgs=0,... ); //... args

/** \brief roda uma função dentro de um arquivo phyton
\param result: where the result of python function will be stored
\param fileName: nome do arquivo phyton sem a extenção
\param funct: nome da função a ser executada
\param ArgTypes: número de arqumentos a serem passados para a função phyton
\param args...: número variável de argumentos a serem passados para a função phyton
\note   run takes a format string (ArgTypes) of the form
   "ifcs", where each character specifies the
   type of the argument in that position.

  i = int
  f = float
  c = string C (char *)
  s = string C++

  Following the format specification is a variable 
  list of arguments. Each argument corresponds to 
  a format character in the format string to which 
 the ArgTypes parameter points
 \note remember to Py_DECREF(the return of this method) after using it
*/
	PyObject * runFunction( string fileName, string funct, char *ArgTypes,... ) throw (Exception::CScriptException);

	PyObject * runMethod( string fileName, string className,string method, char *ArgTypes,... ) throw (Exception::CScriptException);

	PyObject * runFunctionThreaded( string fileName, string funct, char *ArgTypes,... ) throw (Exception::CScriptException);
	PyObject * _runFunctionThreaded(CContext contexto) throw (Exception::CScriptException);

	PyObject * runMethodThreaded( string fileName, string className,string method, char *ArgTypes,... ) throw (Exception::CScriptException);
	

	//! limpa memória utilizada pelo objeto e o delete
	void clearValue(PyObject *);
	//! return the Python error string
	string getPyError();
	CContext contexto;
	void join();
	protected:
		 /*! Display thread */
    Util::Thread::ThreadId_t thread;
	
private:
	
	PyObject * prepareArgList( CList< valueTypePair_t * >  &Arglist);
	//PyObject *_my_pSourceFile;  //phyton Source File name without extention
	//PyObject *_my_pModule;
	//PyObject *_my_pDict;
	//PyObject *_my_pFunc; //function name inside the Source File
	//PyObject *_my_pValue;
	//PyObject *_my_pArgs;
	//PyObject *_my_pClass;
	//PyObject *_my_pInstance;
};

} //end Scripting
} //end SGF
#endif //SGF_SCRIPTING
#endif //_S_G_F_PHYTON_SCRIPTING_h