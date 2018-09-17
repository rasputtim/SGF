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
#ifndef _S_G_F_CALLBACK_H
#define _S_G_F_CALLBACK_H

#include "../SGF_Config.h"
#include "SGF_Debug.h"

//how to use: http://www.codeguru.com/cpp/cpp/cpp_mfc/callbacks/article.php/c4129

using namespace ::std;
namespace SGF {
class CCmdArgs;
/**
 * \class CCallbackBase
 *
 * \ingroup SGF_Util
 *
 * \brief Classe Base para CallBacks
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CCallbackBase
{
    public:
		CCallbackBase(){};
		virtual ~CCallbackBase(){};
        virtual void Execute(int Param) const =0;
		virtual void Execute(string &StringParam)const=0;
		virtual void Execute(const char *charParam) const = 0;
		virtual void Execute(void *voidParam) const = 0;
		virtual void Execute()const=0;
		virtual bool isThereStringCB()=0;
		virtual bool isThereVoidCB()=0;
		virtual bool isThereIntCB()=0;
		virtual bool isThereCharCB()=0;
		virtual bool isThereGeneralCB()=0;
};

typedef void (*callbackVoid_t)(void * arg);
typedef void (*callbackCstr_t)(const char *arg );
typedef void (*callbackInt_t)(int args);
typedef void (*callbackStr_t)(string &args);
typedef void (*callbackNoArg_t)();

// argument completion function
typedef void (*callbackArgCompletion_t)( const CCmdArgs &args, callbackCstr_t function );


struct CallbackVoid{
    CallbackVoid():
        function(0),
        data(0),
		m_bCallback(false){
        }

    CallbackVoid(callbackVoid_t function, void * data):
        function(function),
        data(data),
		m_bCallback(true){
        }
	CallbackVoid(callbackVoid_t function):
        function(function),
        data(0),
		m_bCallback(true){
    }
	CallbackVoid & operator = ( const  CallbackVoid& source ){
		function=source.function;
		data=source.data;
		m_bCallback=source.m_bCallback;
		return *this;
	}
    callbackVoid_t function;
    void * data;
	bool  m_bCallback;  //true if a callback handler is registered
	
};
struct CallbackCstr{
    CallbackCstr():
        function(0),
        data(0),
		m_bCallback(false){
        }

    CallbackCstr(callbackCstr_t function, void * data):
        function(function),
        data(data),
		m_bCallback(true){
        }
	CallbackCstr(callbackCstr_t function):
        function(function),
        data(0),
		m_bCallback(true){
    }
	CallbackCstr & operator = ( const  CallbackCstr& source ){
		function=source.function;
		data=source.data;
		m_bCallback=source.m_bCallback;
		return *this;
	}
    callbackCstr_t function;
    void * data;
	bool  m_bCallback;  //true if a callback handler is registered
	
};
struct CallbackInt{
    CallbackInt():
        function(0),
        data(0),
		m_bCallback(false){
        }

    CallbackInt(callbackInt_t function, void * data):
        function(function),
        data(data),
		m_bCallback(true){
        }
	CallbackInt(callbackInt_t function):
        function(function),
        data(0),
		m_bCallback(true){
    }
	CallbackInt & operator = ( const  CallbackInt& source ){
		function=source.function;
		data=source.data;
		m_bCallback=source.m_bCallback;
		return *this;
	}
    callbackInt_t function;
    void * data;
	bool  m_bCallback;  //true if a callback handler is registered
	
};
struct CallbackStr{
    CallbackStr():
        function(0),
        data(0),
		m_bCallback(false){
        }

    CallbackStr(callbackStr_t function, void * data):
        function(function),
        data(data),
		m_bCallback(true){
        }
	CallbackStr(callbackStr_t function):
        function(function),
        data(0),
		m_bCallback(true){
    }
	CallbackStr & operator = ( const  CallbackStr& source ){
		function=source.function;
		data=source.data;
		m_bCallback=source.m_bCallback;
		return *this;
	}
    callbackStr_t function;
    void * data;
	bool  m_bCallback;  //true if a callback handler is registered
	
};

/**
 * \class CCallback
 *
 * \ingroup SGF_Util
 *
 * \brief Classe De Registro e Execução de CallBack entre classes
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
template <class CallInstance>
class  SGE_API CCallback : public CCallbackBase
{
    public:
        CCallback():
		cInst(0),
		pFunction(0),// constructor
		stringFunction(0),
		charFunction(0),
		genFunction(0),
		voidFunction(0)
        {

        }

        typedef void (CallInstance::*tFunction)(int args);
		typedef void (CallInstance::*sFunction)(string &args);
		typedef void (CallInstance::*cFunction)(const char *args);
		typedef void (CallInstance::*vFunction)(void *args);
		typedef void (CallInstance::*gFunction)();
		/** Método que executa o callback passando um parâmetro do tipo int
		* \param Param: parâmetro tipo int que será passado paã o método do CallBack
		*/
        virtual void Execute(int Param) const
        {
            if (pFunction) (cInst->*pFunction)(Param);
            else
			Debug::debug(Debug::error,__FUNCTION__) << "ERROR : the callback function has not been defined !!!!"  <<endl;

        }
		/** Método que executa o callback passando um parâmetro do tipo string
		* \param StringParam: parÂmetro tipo string que será passado para o método do CallBack
		*/

		virtual void Execute(string &StringParam)const
		{
            if (stringFunction) (cInst->*stringFunction)(StringParam);
            else
			Debug::debug(Debug::error,__FUNCTION__) << "ERROR : the callback function has not been defined !!!!"  <<endl;

        }
		
		/** Método que executa o callback passando um parâmetro do tipo const char *
		* \param charParam: parâmetro tipo const char * que será passado para o método do CallBack
		*/

		virtual void Execute(const char * charParam)const
		{
            if (charFunction) (cInst->*charFunction)(charParam);
            else
			Debug::debug(Debug::error,__FUNCTION__) << "ERROR : the callback function has not been defined !!!!"  <<endl;

        }
		/** Método que executa o callback com parâmetros void *
		* \param oidvParam: parâmetro tipo void * que será passado para o método do CallBack
		*/

		virtual void Execute(void *voidParam)const
		{
            if (voidFunction) (cInst->*voidFunction)(voidParam);
            else
			Debug::debug(Debug::error,__FUNCTION__) << "ERROR : the callback function has not been defined !!!!"  <<endl;

        }
		/** Método que executa o callback sem parâmetros
		*/

		virtual void Execute()const
		{
            if (genFunction) (cInst->*genFunction)();
            else
			Debug::debug(Debug::error,__FUNCTION__) << "ERROR : the callback function has not been defined !!!!"  <<endl;

        }
		/** \brief método que inicializa o ponteiro que aponta para a função de retorno (CallBack)ncom parâmetro tipo int
		* \param cInstancePointer: endereço que contém a instância do objeto que irá executar a função de callback
		* \param pFunctionPointer: endereço do método que ira ser chamado a execução. Função de callback
		*/
        void SetIntCallback (CallInstance  *cInstancePointer,
                          tFunction   pFunctionPointer)
        {
            cInst     = cInstancePointer;
            pFunction = pFunctionPointer;

        }
		/** \brief método que inicializa o ponteiro que aponta para a função de retorno (CallBack) com parâmetro tipo string
		* \param cInstancePointer: endereço que contém a instância do objeto que irá executar a função de callback
		* \param pFunctionPointer: endereço do método que ira ser chamado a execução. Função de callback
		*/
		void SetStringCallback (CallInstance  *cInstancePointer,
                          sFunction   pFunctionPointer)
        {
            cInst     = cInstancePointer;
            stringFunction = pFunctionPointer;

        }
		/** \brief método que inicializa o ponteiro que aponta para a função de retorno (CallBack)ncom parâmetro tipo cont *char
		* \param cInstancePointer: endereço que contém a instância do objeto que irá executar a função de callback
		* \param cFunctionPointer: endereço do método que ira ser chamado a execução. Função de callback
		*/
        void SetCharCallback (CallInstance  *cInstancePointer,
                          cFunction   cFunctionPointer)
        {
            cInst     = cInstancePointer;
            charFunction = cFunctionPointer;

        }
		/** \brief método que inicializa o ponteiro que aponta para a função de retorno (CallBack) sem parâmetros
		* \param cInstancePointer: endereço que contém a instância do objeto que irá executar a função de callback
		* \param gFunctionPointer: endereço do método que ira ser chamado a execução. Função de callback
		*/
        void SetGenCallback (CallInstance  *cInstancePointer,
                          gFunction   gFunctionPointer)
        {
            cInst     = cInstancePointer;
            genFunction = gFunctionPointer;

        }
		/** \brief método que inicializa o ponteiro que aponta para a função de retorno (CallBack) com parâmetro do tipo void *
		* \param cInstancePointer: endereço que contém a instância do objeto que irá executar a função de callback
		* \param vFunctionPointer: endereço do método que ira ser chamado a execução. Função de callback
		*/
        void SetVoidCallback (CallInstance  *cInstancePointer,
                          gFunction   vFunctionPointer)
        {
            cInst     = cInstancePointer;
            voidFunction = vFunctionPointer;

        }
		virtual bool isThereStringCB(){if(stringFunction==NULL)return false;else return true;};
		virtual bool isThereVoidCB(){if(voidFunction==NULL)return false;else return true;};
		virtual bool isThereIntCB(){if(pFunction==NULL)return false;else return true;};
		virtual bool isThereCharCB(){if(charFunction==NULL)return false;else return true;};
		virtual bool isThereGeneralCB(){if(genFunction==NULL)return false;else return true;};
    private:
        CallInstance  *cInst;
        tFunction  pFunction;
		sFunction  stringFunction;
		cFunction  charFunction;
		gFunction  genFunction;
		vFunction  voidFunction;
};
} //end SGF
#endif
