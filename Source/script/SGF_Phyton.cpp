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



#include "script/SGF_Phyton.h"
#include "../util/SGF_Util.h"
#include "../util/SGF_Thread.h"

#ifdef SGF_PHYTON_SCRIPTING


/***************************************************************************
                  PHYTON	BACKEND CLASS IMPLEMENTATION
***************************************************************************/
namespace SGF {

namespace Script {

PyObject * CPhytonEngine::prepareArgList( CList< valueTypePair_t * >  &Arglist) {
	PyObject * pArgs=NULL;

	if( Arglist.getNumElements() > 0 )  {
			PyObject *temp=NULL;
            pArgs = PyTuple_New(Arglist.getNumElements());
            for (int i = 0; i < Arglist.getNumElements(); i++)
            {
			 //valueTypePair_t *ValueTypePair=NULL;
			 //ValueTypePair=Arglist[i];
           
            switch( Arglist[i]->type ) {   // Type to expect.
						  case 's': ;
						  case 'z':{
							   temp = PyBytes_FromString(Arglist[i]->value.charString_);
							   break;
						 }case 'h': ;
						  case'i':{
							  temp = PyLong_FromLong(Arglist[i]->value.int_);
							  break;
						}case 'c':;
						 case 'b':{
							// _my_pValue = PyBytes_FromString( Arglist[i]->value.byte_); 
							 break;
						}case 'l':{
							//PyObject *args = Py_BuildValue( ArgTypes, Arglist[0]->value.long_); 
							break;
						}case 'd':{
							//PyObject *args = Py_BuildValue( ArgTypes, Arglist[0]->value.double_); 
							break;
						}case 'f':{
							 temp = PyLong_FromLong( Arglist[i]->value.float_);
							 break;
						}case 'S':;
						case 'O':{
							//PyObject *args = Py_BuildValue( ArgTypes, Arglist[0]->value.object_); 
							break;
						}case 'N':{
							break;
							//PyObject *args = Py_BuildValue( ArgTypes, Arglist[0]->value.other); 
						}default: {
				/* not implemented yet
				"s#"
				"z#"
				"O&"
				"(items)"
				"[items]"
				"{items}"

					*/

						 break;
						} 
			}       
			
			if (!temp)   {
						 PyErr_Print();
						 return NULL;
                    }
                    PyTuple_SetItem(pArgs, i, temp); 
					temp=NULL;   
             }
             return pArgs;
		
		}
	    return NULL;
}

CPhytonEngine::CPhytonEngine():
CEngine(),
thread(Util::Thread::uninitializedValue)
//_my_pSourceFile(NULL),
//_my_pModule(NULL), 
//_my_pDict(NULL), 
//_my_pFunc(NULL), 
//_my_pValue(NULL),
//_my_pArgs(NULL),
//_my_pClass(NULL)//, 
//_my_Instance(NULL)
{
	//Construct(path,script);
	// Initialize the Python Interpreter
	init();
}

void CPhytonEngine::init(){
	Py_Initialize();
}

void CPhytonEngine::run(long &result,string fileName, string funct, int numOfIntArgs, ...){
	 va_list arguments;   
	 PyObject *pSourceFile,* pModule,* pDict, * pFunc,*pValue, *pArgs ;
	 pSourceFile=pModule=pDict=pFunc=pValue=pArgs=NULL;
	 // A place to store the list of arguments
	 va_start ( arguments, numOfIntArgs );           // Initializing arguments to store all values after num

	// Build the name object
	pSourceFile = PyBytes_FromString(fileName.c_str());

    // Load the module object
    pModule = PyImport_Import(pSourceFile);

    // pDict is a borrowed reference 
    pDict = PyModule_GetDict(pModule);

	 // pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, funct.c_str());

    if (PyCallable_Check(pFunc)) {
		pArgs = NULL;
		// Prepare the argument list for the call
		if( numOfIntArgs > 0 )  {
            pArgs = PyTuple_New(numOfIntArgs);
            for (int i = 0; i < numOfIntArgs; i++)
            {
            pValue = PyLong_FromLong(va_arg ( arguments, int )); // Adds the next value in argument list to sum.;
                    if (!pValue)
                    {
						 PyErr_Print();
                         return ;
                    }
                    PyTuple_SetItem(pArgs, i, pValue);    
            }
            va_end ( arguments ); 
			
		} else {
			pValue = PyObject_CallObject(pFunc, pArgs);
			if (pArgs != NULL) Py_DECREF(pArgs);
		}
		if (pValue != NULL) 
		{
			result = PyLong_AsLong(pValue);
			Py_DECREF(pValue);
			pDict = NULL;
			pFunc = NULL;
			return;
		} else {
			PyErr_Print();
		}
		
	
	} else {
        PyErr_Print();
    }

	pDict = NULL;
	pFunc = NULL;
	return;
}

void CPhytonEngine::clearValue(PyObject * object) {
	if (object == NULL) return;
	Py_DECREF(object);
}


static int
parse_syntax_error(PyObject *err, PyObject **message, const char **filename,
                   int *lineno, int *offset, const char **text)
{
    long hold;
    PyObject *v;
    _Py_IDENTIFIER(msg);
    _Py_IDENTIFIER(filename);
    _Py_IDENTIFIER(lineno);
    _Py_IDENTIFIER(offset);
    _Py_IDENTIFIER(text);

    *message = NULL;

    /* new style errors.  `err' is an instance */
    *message = _PyObject_GetAttrId(err, &PyId_msg);
    if (!*message)
        goto finally;

    v = _PyObject_GetAttrId(err, &PyId_filename);
    if (!v)
        goto finally;
    if (v == Py_None) {
        Py_DECREF(v);
        *filename = NULL;
    }
    else {
        *filename = _PyUnicode_AsString(v);
        Py_DECREF(v);
        if (!*filename)
            goto finally;
    }

    v = _PyObject_GetAttrId(err, &PyId_lineno);
    if (!v)
        goto finally;
    hold = PyLong_AsLong(v);
    Py_DECREF(v);
    if (hold < 0 && PyErr_Occurred())
        goto finally;
    *lineno = (int)hold;

    v = _PyObject_GetAttrId(err, &PyId_offset);
    if (!v)
        goto finally;
    if (v == Py_None) {
        *offset = -1;
        Py_DECREF(v);
    } else {
        hold = PyLong_AsLong(v);
        Py_DECREF(v);
        if (hold < 0 && PyErr_Occurred())
            goto finally;
        *offset = (int)hold;
    }

    v = _PyObject_GetAttrId(err, &PyId_text);
    if (!v)
        goto finally;
    if (v == Py_None) {
        Py_DECREF(v);
        *text = NULL;
    }
    else {
        *text = _PyUnicode_AsString(v);
        Py_DECREF(v);
        if (!*text)
            goto finally;
    }
    return 1;

finally:
    Py_XDECREF(*message);
    return 0;
}
static string
getExceptionString(PyObject *value)
{
	string errorstring;
    int err = 0;
    PyObject *type, *tb;
    _Py_IDENTIFIER(print_file_and_line);

    if (!PyExceptionInstance_Check(value)) {
		errorstring.append("TypeError: print_exception(): Exception expected for value, ");
        errorstring.append(Py_TYPE(value)->tp_name);
		errorstring.append(" found\n");
		return errorstring;
    }

    Py_INCREF(value);
    fflush(stdout);
    type = (PyObject *) Py_TYPE(value);
    tb = PyException_GetTraceback(value);
   // if (tb && tb != Py_None)
     //   err = PyTraceBack_Print(tb, f);
    if (err == 0 &&
        _PyObject_HasAttrId(value, &PyId_print_file_and_line))
    {
      PyObject *message;
        const char *filename, *text;
        int lineno, offset;
        if (parse_syntax_error(value, &message, &filename,
                               &lineno, &offset, &text))
            PyErr_Clear();
        else {
            char buf[10];
			errorstring.append("  File \"");
            if (filename == NULL) {
                errorstring.append("<string>");
			}else {
				errorstring.append(filename);
            }
			errorstring.append("\", line ");
            PyOS_snprintf(buf, sizeof(buf), "%d", lineno);
            errorstring.append(buf);
			errorstring.append("\n");
			if (text != NULL) {}
                //print_error_text(f, offset, text);
            Py_DECREF(value);
            value = message;
            /* Can't be bothered to check all those
               PyFile_WriteString() calls */
            if (PyErr_Occurred())
                err = -1;
        }
    }
    if (err) {
        /* Don't do anything else */
    }
    else {
        PyObject* moduleName;
        char* className;
        _Py_IDENTIFIER(__module__);
        assert(PyExceptionClass_Check(type));
        className = PyExceptionClass_Name(type);
        if (className != NULL) {
            char *dot = strrchr(className, '.');
            if (dot != NULL)
                className = dot+1;
        }

        moduleName = _PyObject_GetAttrId(type, &PyId___module__);
        if (moduleName == NULL || !PyUnicode_Check(moduleName))
        {
            Py_XDECREF(moduleName);
			errorstring.append("<unknown>");
        }
        else {
            char* modstr = _PyUnicode_AsString(moduleName);
            if (modstr && strcmp(modstr, "builtins"))
            {
				errorstring.append(modstr);
                errorstring.append(".");
            }
            Py_DECREF(moduleName);
        }
        if (err == 0) {
            if (className == NULL) {
					  errorstring.append("<unknown>");
            }else {
				errorstring.append(className);
            }
        }
    }
    if (err == 0 && (value != Py_None)) {
        PyObject *s = PyObject_Str(value);
        /* only print colon if the str() of the
           object is not the empty string
        */
        if (s == NULL)
            err = -1;
        else if (!PyUnicode_Check(s) ||
            PyUnicode_GetLength(s) != 0) {
				errorstring.append(": ");
            //err = SGF::Script::PyFile_WriteString(": ", f);
		}
        if (err == 0) {
			char* test = PyUnicode_AsUTF8(s);
			errorstring.append(test);
		}
        Py_XDECREF(s);
    }
    /* try to write a newline in any case */
	errorstring.append("\n");
    Py_XDECREF(tb);
    Py_DECREF(value);
    /* If an error happened here, don't show it.
       XXX This is wrong, but too many callers rely on this behavior. */
    if (err != 0)
        PyErr_Clear();
	return errorstring;
} 

static const char *cause_message =
    "\nThe above exception was the direct cause "
    "of the following exception:\n\n";

static const char *context_message =
    "\nDuring handling of the above exception, "
    "another exception occurred:\n\n";

static string
getExceptionString_recursive(PyObject *value, PyObject *seen)
{
	string errormessage;
    int err = 0, res;
    PyObject *cause, *context;
    //char *cause_message; //salva
    if (seen != NULL) {
        /* Exception chaining */
        if (PySet_Add(seen, value) == -1)
            PyErr_Clear();
        else if (PyExceptionInstance_Check(value)) {
            cause = PyException_GetCause(value);
            context = PyException_GetContext(value);
            if (cause) {
                res = PySet_Contains(seen, cause);
                if (res == -1)
                    PyErr_Clear();
                if (res == 0) {
                    getExceptionString_recursive(
                         cause, seen);
                    errormessage.append(cause_message);
                }
            }
            else if (context &&
                !((PyBaseExceptionObject *)value)->suppress_context) {
                res = PySet_Contains(seen, context);
                if (res == -1)
                    PyErr_Clear();
                if (res == 0) {
                    getExceptionString_recursive(
                        context, seen);
                    errormessage.append(context_message);
                }
            }
            Py_XDECREF(context);
            Py_XDECREF(cause);
        }
    }
    errormessage.append(getExceptionString(value));
    if (err != 0)
        PyErr_Clear();
	return errormessage;
}

static string
get_Error(PyObject *exception, PyObject *value, PyObject *tb)
{
    PyObject *seen;
    //PyObject *f = PySys_GetObject("stderr");
    if (PyExceptionInstance_Check(value)
        && tb != NULL && PyTraceBack_Check(tb)) {
        /* Put the traceback on the exception, otherwise it won't get
           displayed.  See issue #18776. */
        PyObject *cur_tb = PyException_GetTraceback(value);
        if (cur_tb == NULL)
            PyException_SetTraceback(value, tb);
        else
            Py_DECREF(cur_tb);
    }
    //if (f == Py_None) {
        /* pass */
    //}
   // else if (f == NULL) {
   //     _PyObject_Dump(value);
   //     fprintf(stderr, "lost sys.stderr\n");
   // }
    //else {
        /* We choose to ignore seen being possibly NULL, and report
           at least the main exception (it could be a MemoryError).
        */
        seen = PySet_New(NULL);
        if (seen == NULL)
            PyErr_Clear();
        string error = getExceptionString_recursive( value, seen);
        Py_XDECREF(seen);
		return error;
   // }
}

//! return the Python error string
string CPhytonEngine::getPyError(){
		int set_sys_last_vars=1;
			PyObject *exception, *v, *tb, *hook;

    if (PyErr_ExceptionMatches(PyExc_SystemExit)) {
        //handle_system_exit();
    }
    PyErr_Fetch(&exception, &v, &tb);
    if (exception == NULL)
        return "";
    PyErr_NormalizeException(&exception, &v, &tb);
    if (tb == NULL) {
        tb = Py_None;
        Py_INCREF(tb);
    }
    PyException_SetTraceback(v, tb);
    if (exception == NULL)
        return "";
    /* Now we know v != NULL too */
    if (set_sys_last_vars) {
        PySys_SetObject("last_type", exception);
        PySys_SetObject("last_value", v);
        PySys_SetObject("last_traceback", tb);
    }
	string error=get_Error(exception, v, tb);

    Py_XDECREF(exception);
    Py_XDECREF(v);
    Py_XDECREF(tb);
	return error;
}
PyObject * CPhytonEngine::runFunction(string fileName, string funct, char *ArgTypes,... )throw (Exception::CScriptException){
	va_list vl;
	int i,argCount=0;
	PyObject *pSourceFile,* pModule,* pDict, * pFunc,*pValue,*pArgs ;
	pSourceFile=pModule=pDict=pFunc=pValue=pArgs=NULL;
	 CList< valueTypePair_t * > Arglist;

		// Build the name object
        if ((pSourceFile = PyBytes_FromString(fileName.c_str())) == NULL) {
            printf("Error: PyBytes_FromString\n");
			//PyErr_Print();
			throw Exception::CScriptException(__FILE__, __FUNCTION__ ,__LINE__, getPyError() );
            return NULL;
        }

        // Load the module object
        if ((pModule = PyImport_ImportModule(fileName.c_str())) == NULL) {
        //if ((pModule = PyImport_Import(pSourceFile)) == NULL) {
        
			printf("Error: PyImport_Import\n");
			//PyErr_Print();
	        throw Exception::CScriptException(__FILE__, __FUNCTION__ ,__LINE__, getPyError() );
            return NULL;
        }

        // pDict is a borrowed reference 
        if ((pDict = PyModule_GetDict(pModule))==NULL) {
            printf("Error: PyModule_GetDict\n");
			//PyErr_Print();
            throw Exception::CScriptException(__FILE__, __FUNCTION__ ,__LINE__, getPyError() );
            return NULL;
        }

    // pFunc is also a borrowed reference 
	if ((pFunc = PyDict_GetItemString(pDict, funct.c_str()))==NULL) {
            printf("Error: PyDict_GetItemString\n");
			//PyErr_Print();
            throw Exception::CScriptException(__FILE__, __FUNCTION__ ,__LINE__, getPyError() );
            return NULL;
        }
	
   //  ArgTypes is the last argument specified; you must access 
   //  all others using the variable-argument macros.
   va_start( vl, ArgTypes );

   // Step through the list.
   for( i = 0; ArgTypes[i] != '\0'; ++i ) {
       switch( ArgTypes[i] ) {   // Type to expect.
          case 's': 
		  case 'z':{
			valueTypePair_t *ValueTypePair= new valueTypePair_t;
			ValueTypePair->value.charString_= va_arg( vl, char* );
			ValueTypePair->type='z';
			Arglist.insert( ValueTypePair );
			break;
		 }case 'h': 
		  case'i':{
		   valueTypePair_t *ValueTypePair= new valueTypePair_t;
			ValueTypePair->value.int_= va_arg( vl, int );
			ValueTypePair->type='i';
			Arglist.insert( ValueTypePair );
			//printf_s( "%i\n", Printable.i );
			break;
		}case 'c':
		 case 'b':{
			valueTypePair_t *ValueTypePair= new valueTypePair_t;
			ValueTypePair->value.byte_= va_arg( vl, char );
			ValueTypePair->type='b';
			Arglist.insert( ValueTypePair );
			//printf_s( "%i\n", Printable.i );
			break;
		}case 'l':{
			valueTypePair_t *ValueTypePair= new valueTypePair_t;
			ValueTypePair->value.long_= va_arg( vl, long int);
			ValueTypePair->type='l';
			Arglist.insert( ValueTypePair );
			//printf_s( "%i\n", Printable.i );
			break;
		}case 'd':{
			valueTypePair_t *ValueTypePair= new valueTypePair_t;
			ValueTypePair->value.double_ = va_arg( vl, double);
			 ValueTypePair->type='d';
			 Arglist.insert( ValueTypePair );
			 //printf_s( "%f\n", Printable.f );
			break;
		}case 'f':{
			valueTypePair_t *ValueTypePair= new valueTypePair_t;
			ValueTypePair->value.float_ = va_arg( vl, float );
			ValueTypePair->type='f';
			Arglist.insert( ValueTypePair );
			//printf_s( "%f\n", Printable.f );
			break;
		}case 'S':
		case 'O':{
			valueTypePair_t *ValueTypePair= new valueTypePair_t;
			ValueTypePair->value.object_ = va_arg( vl, PyObject *);
			ValueTypePair->type='O';
			Arglist.insert( ValueTypePair );
			//printf_s( "%f\n", Printable.f );
			break;
		}case 'N':{
			valueTypePair_t *ValueTypePair= new valueTypePair_t;
			ValueTypePair->value.object_ = va_arg( vl, PyObject *);
			ValueTypePair->type='N';
			Arglist.insert( ValueTypePair );
			//printf_s( "%f\n", Printable.f );
			break;
		}default: {
/* not implemented yet
"s#"
"z#"
"O&"
"(items)"
"[items]"
"{items}"

	*/
         valueTypePair_t *ValueTypePair= new valueTypePair_t;
		 ValueTypePair->value.other = va_arg( vl, void*);
		 ValueTypePair->type='x';
		 Arglist.insert( ValueTypePair );
		 //printf_s( "%f\n", Printable.f );
		 break;
		}
      }
   }
   va_end( vl );



       if (PyCallable_Check(pFunc)) {
		
		// Prepare the argument list for the call
		if (Arglist.getNumElements() > 0 && (pArgs=prepareArgList( Arglist))== NULL ) {
			Arglist.deleteContents(true);
			pDict = NULL;
			pFunc = NULL;
			// Clean up
			Py_DECREF(pModule);
			Py_DECREF(pSourceFile);
			return NULL;
		}
		pValue = PyObject_CallObject(pFunc, pArgs);
		if (pArgs != NULL) Py_DECREF(pArgs);
		
		if (pValue == NULL)  PyErr_Print();
		//Py_DECREF(_my_pValue); the calling methor must do this
		Arglist.deleteContents(true);
		pDict = NULL;
		pFunc = NULL;
		// Clean up
		Py_DECREF(pModule);
		Py_DECREF(pSourceFile);
		return pValue;
			
		
	
	} else {
        PyErr_Print();
    }
	// Clean up
	Arglist.deleteContents(true);
	pDict = NULL;
	pFunc = NULL;
	Py_DECREF(pModule);
	Py_DECREF(pSourceFile);
	return NULL;
}
PyObject * CPhytonEngine::runMethod( string fileName, string className,string method, char *ArgTypes,... ) throw (Exception::CScriptException){
    PyObject *pSourceFile,*pModule,* pClass, *pInstance,*pDict, *pValue;
	va_list vl;
	CList< valueTypePair_t * > Arglist;
	


		// Build the name of a callable class 
        if ((pSourceFile = PyBytes_FromString(fileName.c_str())) == NULL) {
            printf("Error: PyBytes_FromString\n");
			//PyErr_Print();
			throw Exception::CScriptException(__FILE__, __FUNCTION__ ,__LINE__, getPyError() );
            return NULL;
        }

        // Load the module object
        if ((pModule = PyImport_ImportModule(fileName.c_str())) == NULL) {
        	printf("Error: PyImport_Import\n");
			//PyErr_Print();
			string error = getPyError();
	        throw Exception::CScriptException(__FILE__, __FUNCTION__ ,__LINE__, error );
            return NULL;
        }

        // pDict is a borrowed reference 
        if ((pDict = PyModule_GetDict(pModule))==NULL) {
            printf("Error: PyModule_GetDict\n");
			//PyErr_Print();
            throw Exception::CScriptException(__FILE__, __FUNCTION__ ,__LINE__, getPyError() );
            return NULL;
        }
	// pFunc is also a borrowed reference 
	pClass = PyDict_GetItemString(pDict, className.c_str());

	// Create an instance of the class
    if (PyCallable_Check(pClass))
    {
        pInstance = PyObject_CallObject(pClass, NULL); 
    }

	// Build the parameter list
       //  ArgTypes is the last argument specified; you must access 
   //  all others using the variable-argument macros.
   va_start( vl, ArgTypes );
   int argssize=0;
   // Step through the list.
      // Step through the list.
   for(int i = 0; ArgTypes[i] != '\0'; ++i ) {

	   switch( ArgTypes[i] ) {   // Type to expect.
          case 's': ;
		  case 'z':{
			valueTypePair_t *ValueTypePair= new valueTypePair_t;
			ValueTypePair->value.charString_= va_arg( vl, char* );
			ValueTypePair->type='z';
			Arglist.insert( ValueTypePair );
			break;
		 }case 'h': ;
		  case'i':{
		   valueTypePair_t *ValueTypePair= new valueTypePair_t;
			ValueTypePair->value.int_= va_arg( vl, int );
			ValueTypePair->type='i';
			Arglist.insert( ValueTypePair );
			//printf_s( "%i\n", Printable.i );
			break;
		}case 'c':;
		 case 'b':{
			valueTypePair_t *ValueTypePair= new valueTypePair_t;
			ValueTypePair->value.byte_= va_arg( vl, char );
			ValueTypePair->type='b';
			Arglist.insert( ValueTypePair );
			//printf_s( "%i\n", Printable.i );
			break;
		}case 'l':{
			valueTypePair_t *ValueTypePair= new valueTypePair_t;
			ValueTypePair->value.long_= va_arg( vl, long int);
			ValueTypePair->type='l';
			Arglist.insert( ValueTypePair );
			//printf_s( "%i\n", Printable.i );
			break;
		}case 'd':{
			valueTypePair_t *ValueTypePair= new valueTypePair_t;
			ValueTypePair->value.double_ = va_arg( vl, double);
			 ValueTypePair->type='d';
			 Arglist.insert( ValueTypePair );
			 //printf_s( "%f\n", Printable.f );
			break;
		}case 'f':{
			valueTypePair_t *ValueTypePair= new valueTypePair_t;
			ValueTypePair->value.float_ = va_arg( vl, float );
			ValueTypePair->type='f';
			Arglist.insert( ValueTypePair );
			//printf_s( "%f\n", Printable.f );
			break;
		}case 'S':;
		case 'O':{
			valueTypePair_t *ValueTypePair= new valueTypePair_t;
			ValueTypePair->value.object_ = va_arg( vl, PyObject *);
			ValueTypePair->type='O';
			Arglist.insert( ValueTypePair );
			//printf_s( "%f\n", Printable.f );
			break;
		}case 'N':{
			valueTypePair_t *ValueTypePair= new valueTypePair_t;
			ValueTypePair->value.object_ = va_arg( vl, PyObject *);
			ValueTypePair->type='N';
			Arglist.insert( ValueTypePair );
			//printf_s( "%f\n", Printable.f );
			break;
		}default: {
/* not implemented yet
"s#"
"z#"
"O&"
"(items)"
"[items]"
"{items}"

	*/
         valueTypePair_t *ValueTypePair= new valueTypePair_t;
		 ValueTypePair->value.other = va_arg( vl, void*);
		 ValueTypePair->type='x';
		 Arglist.insert( ValueTypePair );
		 //printf_s( "%f\n", Printable.f );
		 break;
		}
	   }
   } //end for
   va_end( vl );

	PyObject *pArgs;
// Prepare the argument list for the call
		if (Arglist.getNumElements()>0) {
			if ( (pArgs=prepareArgList( Arglist))== NULL ) {
			Arglist.deleteContents(true);
			pDict = NULL;
			//pFunc = NULL;
			// Clean up
			Py_DECREF(pModule);
			Py_DECREF(pSourceFile);
			return NULL;
			}else {
			//PyObject *args = Py_BuildValue("(i)", 7);    
			//PyObject *keywords = PyDict_New();
			//PyDict_SetItemString(keywords, "somearg", Py_True);
			PyObject * met;
			if ((met = PyObject_GetAttrString(pInstance, const_cast<char*>( method.c_str())))==NULL) {
            //PyErr_Print();
            string error = getPyError();
				throw Exception::CScriptException(__FILE__, __FUNCTION__ ,__LINE__, error );
				return NULL;
			}
			
			
			PyObject_Call(met, pArgs, NULL);
			//pValue = PyObject_CallMethod(pInstance, const_cast<char*>( "multiply2"/*method.c_str()*/), "ii",pArgs);
			Py_DECREF(pArgs);
			//Py_DECREF(keywords);
			}
		} else if(Arglist.getNumElements() ==0){
        // Call a method of the class with no parameters
        pValue = PyObject_CallMethod(pInstance, const_cast<char*>( method.c_str()), NULL);
    }else {
		//numero de argumentos maio que 4 , ainda não suportado
	}
    if (pValue != NULL) 
    {
		Py_DECREF(pSourceFile);
		Py_DECREF(pModule);
		//Py_DECREF(pValue);
		Arglist.deleteContents(true);
		return pValue;
        
    }
    else 
    {
        PyErr_Print();
    }
}


PyObject * CPhytonEngine::_runFunctionThreaded(CContext contexto) throw (Exception::CScriptException){
	/* variáveis vem do contexto
	 string fileName, string funct, char *ArgTypes,... 
	*/
	string FileName=contexto.fileName;
	string funct=contexto.functName;
	char *ArgTypes= contexto.ArgTypes;

	PyObject * pValue;
	PyThreadState *mainThreadState, *myThreadState, *tempState;
    PyInterpreterState *mainInterpreterState;
    // Random testing code
    for(int i = 0; i < 15; i++)
    {
        printf("...Printed from my thread.\n");
    SGF::Util::rest(1000);
    }

    // Initialize python inerpreter
    Py_Initialize();
        
    // Initialize thread support
    PyEval_InitThreads();

    // Save a pointer to the main PyThreadState object
    mainThreadState = PyThreadState_Get();

    // Get a reference to the PyInterpreterState
    mainInterpreterState = mainThreadState->interp;

    // Create a thread state object for this thread
    myThreadState = PyThreadState_New(mainInterpreterState);
    
    // Release global lock
    PyEval_ReleaseLock();
    
    // Acquire global lock
    PyEval_AcquireLock();

    // Swap in my thread state
    tempState = PyThreadState_Swap(myThreadState);
	// Now execute some python code (call python functions)

	try {
	pValue=runFunction("py_function","multiply1","ii",8,8);
	
	}catch(Exception::CScriptException e) {
		printf(e.getFullReason().c_str());
	}


	
	 // Swap out the current thread
    PyThreadState_Swap(tempState);

    // Release global lock
    PyEval_ReleaseLock();
    
    // Clean up thread state
    PyThreadState_Clear(myThreadState);
    PyThreadState_Delete(myThreadState);

    Py_Finalize();
    printf("My thread is finishing...\n");
	return pValue;
}
static int runThread1(void *data){
	CPhytonEngine *engine = (CPhytonEngine *)data;
	engine->_runFunctionThreaded(engine->contexto);
	return true;
}
PyObject * CPhytonEngine::runFunctionThreaded( string fileName, string funct, char *ArgTypes,... ) throw (Exception::CScriptException){
    //Create Context to pass to fun function
	contexto.init(fileName,funct,ArgTypes);
	//trava o contexto
	if (!Util::Thread::createThread(&thread, NULL, (Util::Thread::ThreadFunction) runThread1, this)){
             //   Debug::debug(0) << 
		printf("Could not create processing thread");// << std::endl;
            }	
	
	return NULL;
}
void CPhytonEngine::join(){
	Util::Thread::joinThread(thread);
}
PyObject * CPhytonEngine::runMethodThreaded( string fileName, string className,string method, char *ArgTypes,... ) throw (Exception::CScriptException){
	return NULL;
}


CPhytonEngine::~CPhytonEngine()
{
	
		/* 
 * "destroy" objects and free memory allocated for 
 * the script's symbols, etc. 
 */
		/* 
 * free memory allocated for the Interpreter object itself 
 */
 // Clean up
    //Py_DECREF(_my_pModule);
    //_my_pDict = NULL;
	//_my_pFunc = NULL; //function name inside the Source File
	
    // Finish the Python Interpreter
    Py_Finalize();
}


}
}

#endif