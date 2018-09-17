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
#ifndef _S_G_F_config_Vars_h
#define _S_G_F_config_Vars_h

#include <map>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <map>

#include "../SGF_Config.h"
#include "SGF_SysVars.h"
#include "../structures/SGF_List.h"
#include "../structures/SGF_HashTableFast.h"

using namespace std;
namespace SGF {

class Token;
class CJoystick;
class CInput;
class CFontInfo;
class CBaseObject;

/**
 * \class CEngineSysVar
 *
 * \ingroup SGF_Configuration
 *
 * \brief Classe para Variáveis Globais e da Engine SGFFabric
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: Rasputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2014
 */

class  SGE_API CEngineSysVar : public CSysVar {
	friend class CConfiguration;
	friend class CGlobalConfiguration;
public:
							CEngineSysVar();
							CEngineSysVar( const char *newName, const char *newValue, int newFlags,const char *newDescription ="",callbackVoid_t function =NULL,void *args=NULL );
							CEngineSysVar( const CSysVar *cvar );
	virtual					~CEngineSysVar();

	const char **			CopyValueStrings( const char **strings );
	void					Update( const CSysVar *cvar );
	void					UpdateValue();
	void					UpdateCheat();
	void					SetGlobal( const char *newValue, bool force, bool fromServer );
	void					Reset();

private:
	CMyString					nameString;				// name
	CMyString					resetString;			// resetting will change to this value
	CMyString					valueString;			// value
	CMyString					descriptionString;		// description

	virtual void			internalSetString( const char *newValue );
	virtual void			InternalServerSetString( const char *newValue );
	virtual void			internalSetBool( const bool newValue );
	virtual void			internalSetInteger( const int newValue );
	virtual void			internalSetFloat( const float newValue );
};

/**
 * \class CLocalSysVar
 *
 * \ingroup SGF_Configuration
 *
 * \brief Classe para Variáveis Locais do tipo CSysVar
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: Rasputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2014
 */
class CLocalSysVar : public CSysVar {
	friend class CConfiguration;
	friend class CGlobalConfiguration;
public:
	CLocalSysVar();
	CLocalSysVar( const char *newName, const char *newValue, int newFlags,int index, const char *newDescription ="");
	//Nao esquecer de setar o indice do novo objeto após usar este construtor
	CLocalSysVar( const CSysVar *cvar );
	virtual	~CLocalSysVar();

	const char **		CopyValueStrings( const char **strings );
	void				Update( const CSysVar *cvar );
	void				UpdateValue();
	void				UpdateCheat();
	void				SetLocal( const char *newValue, bool force, bool fromServer );
	void				Reset();
	void				setIndex(int index) { m_iIndex = index;} //Must be set after object instantiation to the clas work properly

	static void			registerLocalStaticVars(int index);
private:
	CMyString			nameString;				// name
	CMyString			resetString;			// resetting will change to this value
	CMyString			valueString;			// value
	CMyString			descriptionString;		// description

	virtual void		internalSetString( const char *newValue );
	virtual void		internalServerSetString( const char *newValue );
	virtual void		internalSetBool( const bool newValue );
	virtual void		internalSetInteger( const int newValue );
	virtual void		internalSetFloat( const float newValue );
	int					m_iIndex;
	static vector<CSysVar *>	m_p_StaticLocalVars;  //! Vetor com as variáveis locais Estáticas
};


} //end namespace SGF
#endif