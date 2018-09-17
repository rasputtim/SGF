/*
  SGF - Super Game Fabric  (https://sourceforge.net/projects/sgfabric/)
  Copyright (C) 2010-2011 Rasputtim <Rasputtim@hotmail.com>

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

#ifndef _SGF_CVARSYSTEM_H__
#define _SGF_CVARSYSTEM_H__

#include "../SGF_Config.h"
#include "SGF_CmdVars.h"
#include "../util/SGF_Callback.h"  //for callback
#include "../util/SGF_Token.h"
#include "../util/SGF_Pointer.h"
#include <typeinfo>
#ifndef BIT
#define BIT( num )				( 1 << ( num ) )
#endif

namespace SGF{
	class CCmdArgs;






/*
===============================================================================

	System Variables (SysVars) are used to hold scalar or string variables
	that can be changed or displayed at the console as well as accessed
	directly in code.

	SysVars are mostly used to hold settings that can be changed from the
	console or saved to and loaded from configuration files. SysVars are also
	occasionally used to communicate information between different modules
	of the program.

	SysVars are restricted from having the same names as console commands to
	keep the console interface from being ambiguous.

	Todo: {
	SysVars can be accessed from the console in three ways:
	cvarName			prints the current value
	cvarName X			sets the value to X if the variable exists
	set cvarName X		as above, but creates the SysVar if not present
	}
	SysVars may be declared in the global namespace, in classes and in functions.
	However declarations in classes and functions should always be static to
	save space and time. Making SysVars static does not change their
	functionality due to their global nature.
	There is a special case of SysVars that can be local: see CLocalSysvar class
	to understand it;
	Sysvar can not be changed ater declaration unless you use devived class CEngineSysvar

	SysVars should be contructed only through one of the constructors with name,
	value, m_iFlags and description. The name, value and description parameters
	to the constructor have to be static strings, do not use va() or the like
	functions returning a string.

	SysVars may be declared multiple times using the same name string. However,
	they will all reference the same value and changing the value of one SysVar
	changes the value of all SysVars with the same name.

	SysVars should always be declared with the correct type flag: SYSVAR_BOOL,
	SYSVAR_INTEGER or SYSVAR_FLOAT. If no such flag is specified the SysVar
	defaults to type string. If the SYSVAR_BOOL flag is used there is no need
	to specify an argument auto-completion function because the SysVar gets
	one assigned automatically.

	SysVars are automatically range checked based on their type and any min/max
	or valid string set specified in the constructor.

	SysVars are always considered cheats except when SYSVAR_NOCHEAT, SYSVAR_INIT,
	SYSVAR_ROM, SYSVAR_ARCHIVE, SYSVAR_USERINFO, SYSVAR_SERVERINFO, SYSVAR_NETWORKSYNC
	is set.

	Sysvar hava a callback system
	The callback system handle both, static functions or object encapsulated methods
	that must e instantiated befor used.
	Be careful to not confunse the two types of callbacks. if you add handle to static
	callbacks, you only be able to run the static run methods. The same is valid to object
	callbacks. The class do not tell you if you misuse them.
===============================================================================
*/

typedef enum {
	SYSVAR_ALL				= -1,		// all m_iFlags
	SYSVAR_BOOL				= BIT(0),	// variable is a boolean
	SYSVAR_INTEGER			= BIT(1),	// variable is an integer
	SYSVAR_FLOAT			= BIT(2),	// variable is a float
	SYSVAR_SYSTEM			= BIT(3),	// system variable
	SYSVAR_RENDERER			= BIT(4),	// renderer variable
	SYSVAR_SOUND			= BIT(5),	// sound variable
	SYSVAR_GUI				= BIT(6),	// gui variable
	SYSVAR_GAME				= BIT(7),	// game variable
	SYSVAR_TOOL				= BIT(8),	// tool variable
	SYSVAR_USERINFO			= BIT(9),	// sent to servers, available to menu
	SYSVAR_SERVERINFO		= BIT(10),	// sent from servers, available to menu
	SYSVAR_NETWORKSYNC		= BIT(11),	// sysvar is synced from the server to clients
	SYSVAR_STATIC			= BIT(12),	// statically declared, not user created
	SYSVAR_CHEAT			= BIT(13),	// variable is considered a cheat
	SYSVAR_NOCHEAT			= BIT(14),	// variable is not considered a cheat
	SYSVAR_INIT				= BIT(15),	// can only be set from the command-line
	SYSVAR_ROM				= BIT(16),	// display only, cannot be set by user at all
	SYSVAR_ARCHIVE			= BIT(17),	// set to cause it to be saved to a config file
	SYSVAR_MODIFIED			= BIT(18),	// set when the variable is modified
	SYSVAR_LOCAL			= BIT(19),  // indicate tha this var is local to rhe class it is declared (see rules...)
	SYSVAR_ENGINE			= BIT(20),  // this is a engine SYSVAR
} cvarFlags_t;


/*
===============================================================================

	CSysVar

===============================================================================
*/

class CSysVar {
public:
							// Never use the default constructor.
							CSysVar() { assert( typeid( this ) != typeid( CSysVar ) ); }

							// Always use one of the following constructors.
							CSysVar( const char *name, const char *value, int m_iFlags, const char *description,
									callbackArgCompletion_t m_tValueCompletion = NULL , bool local=false, callbackVoid_t function=NULL,void *args=NULL );
							CSysVar( const char *name, const char *value, int m_iFlags, const char *description,
									float m_fValueMin, float m_fValueMax, callbackArgCompletion_t m_tValueCompletion = NULL, bool local=false );
							CSysVar( const char *name, const char *value, int m_iFlags, const char *description,
									const char **m_ValueStrings, callbackArgCompletion_t m_tValueCompletion = NULL , bool local=false);
							CSysVar( const CSysVar *cvar );
	virtual					~CSysVar() {
							removeHandleToObject();
							}

	const char *			getName() const { return m_pInternalVar->m_pName; }
	int						getFlags() const { return m_pInternalVar->m_iFlags; }
	const char *			getDescription() const { return m_pInternalVar->m_pDescription; }
	float					getMinValue() const { return m_pInternalVar->m_fValueMin; }
	float					getMaxValue() const { return m_pInternalVar->m_fValueMax; }
	const char **			getValueStrings() const { return m_ValueStrings; }
	callbackArgCompletion_t	getValueCompletion() const { return m_tValueCompletion; }

	bool					isModified() const { return ( m_pInternalVar->m_iFlags & SYSVAR_MODIFIED ) != 0; }
	void					setModified() { m_pInternalVar->m_iFlags |= SYSVAR_MODIFIED; }
	void					clearModified() { m_pInternalVar->m_iFlags &= ~SYSVAR_MODIFIED; }

	const char *			getString() const { return m_pInternalVar->m_pValue; }
	bool					getBool() const { return ( m_pInternalVar->m_iIntegerValue != 0 ); }
	int						getInteger() const { return m_pInternalVar->m_iIntegerValue; }
	float					getFloat() const { return m_pInternalVar->m_fFloatValue; }

	void					setString( const char *value ) { m_pInternalVar->internalSetString( value ); }
	void					setBool( const bool value ) { m_pInternalVar->internalSetBool( value ); }
	void					setInteger( const int value ) { m_pInternalVar->internalSetInteger( value ); }
	void					setFloat( const float value ) { m_pInternalVar->internalSetFloat( value ); }

	void					setInternalVar( CSysVar *cvar ) { m_pInternalVar = cvar; }
	static void				registerGlobalStaticVars();
	CSysVar *				getNext() {return m_pNext;}
	// Sysvar type manipulation
	//return -1 in case of it is a string Sysvar, OTHERWISE RETURN THE CORRESPONIDING TYPE fLAG (SYSVAR_INTEGER, SYSVAR_FLOAT OR SYSVAR_BOOL
	int						getType(); //to know if it is a boool, float, integer or string SysVar
	bool					isBool(){ return  m_iFlags & SYSVAR_BOOL;}; //return true if it is a bool sysvar
	bool					isFloat(){ return  m_iFlags & SYSVAR_FLOAT;}; //return true if it is a float sysvar
	bool					isInteger(){ return  m_iFlags & SYSVAR_INTEGER;}; //return true if it is a integer Sysvar
	bool					isString(){return !isInteger() && !isBool() && !isFloat();}; //return true if it is a string sysvar
	//CallBack system
	/**
	\brief cadastra uma função de callback estática
	\param function função que será cadastrada e será executada apropriadamente
	\note há dois tipos de callback que podem ser utilizados:
	1 - callback para função estática
	2 - callback para um método e uma classe instanciada, ou seja um objeto
	**/
	void					addHandle(callbackVoid_t function){
											m_callback = CallbackVoid(function);
											m_callback.m_bCallback=true;
											if(m_pInternalVar!=NULL)m_pInternalVar->m_callback = CallbackVoid(function);
                                            if(m_pInternalVar!=NULL)m_pInternalVar->m_callback.m_bCallback=true;
											};
	/**
	\brief cadastra uma função de callback para um método de classe instanciada
	\param sfunction função que será cadastrada e será executada apropriadamente
	\param onject ponteiro com o endereço da instância da classe que contém o método que será executado
	\param X tipo da classe
	\note há dois tipos de callback que podem ser utilizados:
	1 - callback para função estática
	2 - callback para um método e uma classe instanciada, ou seja um objeto
	**/
	template <typename X>
	void                    addHandleToObject(X *object, void (X::*sFunction)(const char *Param) ){
							//CCallback<X> *confCalBack=new CCallback<X>();
							//confCalBack->SetCharCallback(object,sFunction);
							m_pObjectCallBack=Util::CReferenceCount<CCallback<X>>(new CCallback<X>());//confCalBack;
							CCallbackBase *temp = m_pObjectCallBack.raw();
							((CCallback<X> *)temp)->SetCharCallback(object,sFunction);
							if(m_pInternalVar!=NULL)m_pInternalVar->m_pObjectCallBack=m_pObjectCallBack;//confCalBack;
							}
							/**
							\brief remove o callback para função estática cadastrado
							**/
	void					removeHandle(); 
							/**
							\brief remove o callback para objeto cadastrado
							**/
	void					removeHandleToObject(); 
							/**
							\brief adiciona o parâmetro que será executado pelo método de callback estático
							**/
	void					setHandleParam(void *data) { m_callback.data=data;} 
							/**
							\brief retorna veradiro se existe uma função de callback cadastrada
							**/
	bool					isThereCallBack(){ return m_callback.m_bCallback;}
							/**
							\brief retorna verdadeiro se existe um método de callback de objeto cadastrada
							**/
	bool					isThereCallBackToObject(){ return (m_pObjectCallBack!=NULL?true:false);}
							/**
							\brief roda o callback para função estática cadastrado com o parÂmetro cadastrado anteriormente no método setHandleParam(void *data)
							\note deve se cadastrar o parâmetro antes de rodar este método
							**/
	void					runCallback();  
							/**
							\brief roda o callback para função estática cadastrado, com o parâmetro passado
							\param param parâmetro que será utilizado para executar a função de callback
							**/
	void					runCallback(void *param); 
							/**
							\brief roda o callback cadastrado com o parâmetro passado
							\param param parâmetro que será utilizado para a execução do callback
							**/
	void					runObjCallback(const char * param); 

	/**
	\brief cadastra para executar o callback estático se a variável sofrer alteração
	**/
	void					setOnChangeRunStaticCallback(){m_executeStaticCalbackOnChange=true; }
	/**
	\brief cadastra para executar o callback para objeto se a variável sofrer alteração
	**/
	void					setOnChangeRunObjectCallback(){m_executeObjCalbackOnChange=true;}
	/**
	\brief cadastra para não executar o callback estático se a variável sofrer alteração
	**/
	void					resetOnChangeRunStaticCallback(){m_executeStaticCalbackOnChange=false; }
	/**
	\brief cadastra para não executar o callback para objeto se a variável sofrer alteração
	**/
	void					resetOnChangeRunObjectCallback(){m_executeObjCalbackOnChange=false;}
	/**
	\brief retorna verdadeiro se o OnchangeCallbackEstático estiver settado
	**/
	bool					onChangeRunStaticCallback(){return m_executeStaticCalbackOnChange;}
	/**
	\brief retorna verdadeiro se o OnchangeCallbackObject estiver settado
	**/
	bool					onChangeRunObjectCallback(){return m_executeObjCalbackOnChange;}
	//!hold static callback data
	CallbackVoid			m_callback; 
	//holds information to CallBack to object (initialized classes) methods
	Util::CReferenceCount< CCallbackBase >			m_pObjectCallBack;  
	Token *					serialize(const CSysVar & cvar);

protected:
	int						m_iFlags;				// SYSVAR_? m_iFlags
	float					m_fValueMin;			// minimum value
	float					m_fValueMax;			// maximum value
	callbackArgCompletion_t	m_tValueCompletion;		// value auto-completion function
	int						m_iIntegerValue;		// atoi( string )
	float					m_fFloatValue;			// atof( value )
	bool 					m_bLocal;				// to declare local sysvars
    const char *			m_pName;				// m_pName
	const char *			m_pValue;				// value
	const char *			m_pDescription;			// description
	CSysVar *				m_pInternalVar;			// internal cvar
	CSysVar *				m_pNext;				// next statically declared cvar
	const char **			m_ValueStrings;			// valid value strings
private:
	void					init( const char *name, const char *value, int Flags, const char *description,
									float ValueMin, float ValueMax, const char ** ValueStrings, callbackArgCompletion_t ValueCompletionFunction, bool local );

	virtual void			internalSetString( const char *newValue ) {}
	virtual void			internalSetBool( const bool newValue ) {}
	virtual void			internalSetInteger( const int newValue ) {}
	virtual void			internalSetFloat( const float newValue ) {}

	static CSysVar *		m_p_StaticVars;
	//! se verdadeiro executara o callback estático em qualquer mudança do valor da variável
	bool					m_executeStaticCalbackOnChange;
	//! se verdadeiro executara o callback para objeto em qualquer mudança do valor da variável
	bool					m_executeObjCalbackOnChange;


};
#if !defined(_MSC_VER)
#define SGF_INLINE_FORCED inline
#endif




SGF_INLINE_FORCED CSysVar::CSysVar( const char *name, const char *value, int m_iFlags, const char *description,
							callbackArgCompletion_t m_tValueCompletion , bool local,callbackVoid_t function,void *args ):
m_pObjectCallBack(Util::CReferenceCount<CCallbackBase>(NULL)),
m_pName(NULL),
m_pValue(NULL),
m_pDescription(NULL),
m_pInternalVar(NULL),
m_pNext(NULL),
m_ValueStrings(NULL),
m_executeStaticCalbackOnChange(false),
m_executeObjCalbackOnChange(false)
{
//	if ( !m_tValueCompletion && ( m_iFlags & SYSVAR_BOOL ) ) {
//		m_tValueCompletion = idCmdSystem::ArgCompletion_Boolean;
//	}
	if (function) {
		this->addHandle(function);
		this->setOnChangeRunStaticCallback();
		if (args) this->setHandleParam(args);
	}
	init( name, value, m_iFlags, description, 1, -1, NULL, m_tValueCompletion, local);
	
	
}

SGF_INLINE_FORCED CSysVar::CSysVar( const char *name, const char *value, int m_iFlags, const char *description,
							float m_fValueMin, float m_fValueMax, callbackArgCompletion_t m_tValueCompletion ,bool local):
m_pObjectCallBack(Util::CReferenceCount<CCallbackBase>(NULL)),
m_pName(NULL),
m_pValue(NULL),
m_pDescription(NULL),
m_pInternalVar(NULL),
m_pNext(NULL),
m_ValueStrings(NULL),
m_executeStaticCalbackOnChange(false),
m_executeObjCalbackOnChange(false)
  {
	init( name, value, m_iFlags, description, m_fValueMin, m_fValueMax, NULL, m_tValueCompletion,local );
}

SGF_INLINE_FORCED CSysVar::CSysVar( const char *name, const char *value, int m_iFlags, const char *description,
							const char **m_ValueStrings, callbackArgCompletion_t m_tValueCompletion,bool local ):
m_pObjectCallBack(Util::CReferenceCount<CCallbackBase>(NULL)),
m_pName(NULL),
m_pValue(NULL),
m_pDescription(NULL),
m_pInternalVar(NULL),
m_pNext(NULL),
m_ValueStrings(NULL),
m_executeStaticCalbackOnChange(false),
m_executeObjCalbackOnChange(false)
{
	init( name, value, m_iFlags, description, 1, -1, m_ValueStrings, m_tValueCompletion, local);
}
//run the static callback method
SGF_INLINE_FORCED void CSysVar::runCallback() {
		m_callback.function(m_callback.data);
}
//run the static callback with void parameter
SGF_INLINE_FORCED void CSysVar::runCallback(void *data) {
		m_callback.function(data);
}
// run the object callback
SGF_INLINE_FORCED void	CSysVar::runObjCallback(const char *Param){
		m_pObjectCallBack->Execute(Param);
}
//!remove handle to static callback
SGF_INLINE_FORCED void	CSysVar::removeHandle() {
		m_callback = CallbackVoid();
		m_callback.m_bCallback=false;
}
//remove handle to object callback
SGF_INLINE_FORCED void	CSysVar::removeHandleToObject() {
	
	m_pObjectCallBack=Util::CReferenceCount<CCallbackBase>(NULL);
		
};

//return -1 in case of it is a string Sysvar
SGF_INLINE_FORCED int CSysVar::getType(){
	if(isBool()) return SYSVAR_BOOL;
	else if (isFloat()) return SYSVAR_FLOAT;
	else if (isInteger()) return SYSVAR_INTEGER;
	else return -1;


}
/**
 * \class CSysVarSystem
 *
 * \ingroup SGF_Configuration
 *
 * \brief Classe Base para o Sistema de controle de Variáveis Globais
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: Rasputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2014
 */

class CSysVarSystem {
public:
	virtual					~CSysVarSystem() {}

	virtual void			init() = 0;
	virtual void			Shutdown() = 0;
	virtual bool			IsInitialized() const = 0;

							// Registers a SysVar.
	virtual void			Register( CSysVar &cvar ) = 0;

							// Finds the SysVar with the given name.
							// Returns NULL if there is no SysVar with the given name.
	virtual CSysVar *		Find( const char *name ) = 0;

							// Sets the value of a SysVar by name.
	virtual void			setCVarString( const char *name, const char *value, int m_iFlags = 0 ) = 0;
	virtual void			setCVarBool( const char *name, const bool value, int m_iFlags = 0 ) = 0;
	virtual void			setCVarInteger( const char *name, const int value, int m_iFlags = 0 ) = 0;
	virtual void			setCVarFloat( const char *name, const float value, int m_iFlags = 0 ) = 0;

							// Gets the value of a SysVar by name.
	virtual const char *	getCVarString( const char *name ) const = 0;
	virtual bool			getCVarBool( const char *name ) const = 0;
	virtual int				getCVarInteger( const char *name ) const = 0;
	virtual float			getCVarFloat( const char *name ) const = 0;

							// Called by the command system when argv(0) doesn't match a known command.
							// Returns true if argv(0) is a variable reference and prints or changes the SysVar.
	virtual bool			Command( const CCmdArgs &args ) = 0;

							// Command and argument completion using callback for each valid string.
	virtual void			CommandCompletion( void(*callback)( const char *s ) ) = 0;
	virtual void			ArgCompletion( const char *cmdString, void(*callback)( const char *s ) ) = 0;

							// Sets/gets/clears modified m_iFlags that tell what kind of SysVars have changed.
	virtual void			SetModifiedFlags( int m_iFlags ) = 0;
	virtual int				GetModifiedFlags() const = 0;
	virtual void			ClearModifiedFlags( int m_iFlags ) = 0;

							// Resets variables with one of the given m_iFlags set.
	virtual void			ResetFlaggedVariables( int m_iFlags ) = 0;

	// Removes auto-completion from the flagged variables.
	virtual void			RemoveFlaggedAutoCompletion( int m_iFlags ) = 0;

	// Writes variables with one of the given m_iFlags set to the given file.
	//virtual void			WriteFlaggedVariables( int m_iFlags, const char *setCmd, idFile *f ) const = 0;

	// Moves SysVars to and from dictionaries.
	//virtual const idDict *	MoveCVarsToDict( int m_iFlags ) const = 0;
	//virtual void			SetCVarsFromDict( const idDict &dict ) = 0;
};

} //end SGF
#endif /* !__CVARSYSTEM_H__ */
