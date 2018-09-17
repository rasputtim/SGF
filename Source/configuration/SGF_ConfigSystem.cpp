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

#include "configuration/SGF_SysVars.h"
#include "configuration/SGF_Configuration.h"
#include "util/SGF_StringUtils.h"
#include "util/SGF_Heap.h"
#include "structures/SGF_List.h"
#include "structures/SGF_HashTableFast.h"
#include "structures/SGF_ListString.h"
#include "util/SGF_SdlManager.h"
//#pragma hdrstop

namespace SGF {
	//! ao criar um objeto CSysvar ele cria uma lista ligada;
	//! depois de registrar as variáeis estaticas seta o valor de staticvars para 0xFFFFFFFF

CSysVar * CSysVar::m_p_StaticVars = NULL;
//CSysVarSystem *				cvarSystem = NULL;
//CSysVar com_forceGenericSIMD( "com_forceGenericSIMD", "0", SYSVAR_BOOL|SYSVAR_SYSTEM, "force generic platform independent SIMD" );
//! Cria um objeto Global de Configuração da Engine,
//! que aarmazenará as variáveis globais
CGlobalConfiguration	globalSysVarSystem;

#define NUM_COLUMNS				77		// 78 - 1
#define NUM_NAME_CHARS			33
#define NUM_DESCRIPTION_CHARS	( NUM_COLUMNS - NUM_NAME_CHARS )
/*
#define FORMAT_STRING			"%-32s "


/*
============
CEngineSysVar::CEngineSysVar
============
*/
CEngineSysVar::CEngineSysVar() {
}

/*
============
CEngineSysVar::CEngineSysVar
============
*/

CEngineSysVar::CEngineSysVar( const char *newName, const char *newValue, int newFlags, const char *newDescription ,callbackVoid_t function,void *args  ):
CSysVar(newName,newValue,( newFlags & ~SYSVAR_STATIC ),newDescription,NULL,false,function,args){
	nameString = newName;
	valueString = newValue;
	resetString = newValue;
	descriptionString = newDescription;
	//m_iFlags = ( newFlags & ~SYSVAR_STATIC ) | SYSVAR_MODIFIED;
	m_fValueMin = 1;
	m_fValueMax = -1;
	m_ValueStrings = NULL;
	m_tValueCompletion = 0;
	UpdateValue();
	UpdateCheat();
	if (!m_pInternalVar) m_pInternalVar = this; //The address of the New CSysvar created upon registration
	m_bLocal=false;

}

/*
============
CEngineSysVar::CEngineSysVar
============
*/
CEngineSysVar::CEngineSysVar( const CSysVar *cvar ):
CSysVar(cvar){
	nameString = cvar->getName();
	valueString = cvar->getString();
	resetString = cvar->getString();
	descriptionString = cvar->getDescription();
	m_ValueStrings = CopyValueStrings( cvar->getValueStrings() );
	UpdateValue();
	UpdateCheat();
	m_pInternalVar = this;
		

}

/*
============
CEngineSysVar::~CEngineSysVar
============
*/
CEngineSysVar::~CEngineSysVar() {
	Mem_Free( m_ValueStrings );
	m_ValueStrings = NULL;
}


/*
============
CEngineSysVar::CopyValueStrings
============
*/
const char **CEngineSysVar::CopyValueStrings( const char **strings ) {
	int i, totalLength;
	const char **ptr;
	char *str;

	if ( !strings ) {
		return NULL;
	}

	totalLength = 0;
	for ( i = 0; strings[i] != NULL; i++ ) {
		totalLength += CMyString::Length( strings[i] ) + 1;
	}

	ptr = (const char **) Mem_Alloc( ( i + 1 ) * sizeof( char * ) + totalLength );
	str = (char *) (((SGF_Byte *)ptr) + ( i + 1 ) * sizeof( char * ) );

	for ( i = 0; strings[i] != NULL; i++ ) {
		ptr[i] = str;
		strcpy( str, strings[i] );
		str += CMyString::Length( strings[i] ) + 1;
	}
	ptr[i] = NULL;

	return ptr;
}

/*
============
CEngineSysVar::Update
============
*/
void CEngineSysVar::Update( const CSysVar *cvarToUpdate ) {

	// if this is a statically declared variable
	if ( cvarToUpdate->getFlags() & SYSVAR_STATIC ) {

		if ( m_iFlags & SYSVAR_STATIC ) {

			// the code has more than one static declaration of the same variable, make sure they have the same properties
			if ( resetString.Icmp( cvarToUpdate->getString() ) != 0 ) {
				Debug::debug(Debug::configuration,__FUNCTION__)<< "SysVar "<< nameString.c_str() << " declared multiple times with different initial value"<< endl;
			}
			if ( ( m_iFlags & (SYSVAR_BOOL|SYSVAR_INTEGER|SYSVAR_FLOAT) ) != ( cvarToUpdate->getFlags() & (SYSVAR_BOOL|SYSVAR_INTEGER|SYSVAR_FLOAT) ) ) {
				Debug::debug(Debug::configuration,__FUNCTION__)<< "SysVar "<< nameString.c_str() << " declared multiple times with different type"<< endl;
			}
			if ( m_fValueMin != cvarToUpdate->getMinValue() || m_fValueMax != cvarToUpdate->getMaxValue() ) {
				Debug::debug(Debug::configuration,__FUNCTION__)<< "SysVar "<< nameString.c_str() << " declared multiple times with different minimum/maximum"<< endl;
			}

		}

		// the code is now specifying a variable that the user already set a value for, take the new value as the reset value
		resetString = cvarToUpdate->getString();
		descriptionString = cvarToUpdate->getDescription();
		m_pDescription = descriptionString.c_str();
		m_fValueMin = cvarToUpdate->getMinValue();
		m_fValueMax = cvarToUpdate->getMaxValue();
		Mem_Free( m_ValueStrings );
		m_ValueStrings = CopyValueStrings( cvarToUpdate->getValueStrings() );
		m_tValueCompletion = cvarToUpdate->getValueCompletion();
		UpdateValue();
		globalSysVarSystem.SetModifiedFlags( cvarToUpdate->getFlags() );
	}

	m_iFlags |= cvarToUpdate->getFlags();
	m_callback= cvarToUpdate->m_callback;
	UpdateCheat();

	// only allow one non-empty reset string without a warning
	if ( resetString.Length() == 0 ) {
		resetString = cvarToUpdate->getString();
	} else if ( cvarToUpdate->getString()[0] && resetString.Cmp( cvarToUpdate->getString() ) != 0 ) {
		Debug::debug(Debug::configuration,__FUNCTION__)<< "cvar \""<<nameString.c_str() <<"\" given initial values: \""<< resetString.c_str()<<"\" and \""<< cvarToUpdate->getString()<< "\""<<endl;
	}
}

/*
============
CEngineSysVar::UpdateValue
============
*/
void CEngineSysVar::UpdateValue() {
	bool clamped = false;

	if ( m_iFlags & SYSVAR_BOOL ) {
		m_iIntegerValue = ( atoi( m_pValue ) != 0 );
		m_fFloatValue = m_iIntegerValue;
		if ( CMyString::Icmp( m_pValue, "0" ) != 0 && CMyString::Icmp( m_pValue, "1" ) != 0 ) {
			valueString = CMyString( (bool)( m_iIntegerValue != 0 ) );
			m_pValue = valueString.c_str();
		}
	} else if ( m_iFlags & SYSVAR_INTEGER ) {
		m_iIntegerValue = (int)atoi( m_pValue );
		if ( m_fValueMin < m_fValueMax ) {
			if ( m_iIntegerValue < m_fValueMin ) {
				m_iIntegerValue = (int)m_fValueMin;
				clamped = true;
			} else if ( m_iIntegerValue > m_fValueMax ) {
				m_iIntegerValue = (int)m_fValueMax;
				clamped = true;
			}
		}
		if ( clamped || !CMyString::IsNumeric( m_pValue ) || CMyString::FindChar( m_pValue, '.' ) ) {
			valueString = CMyString( m_iIntegerValue );
			m_pValue = valueString.c_str();
		}
		m_fFloatValue = (float)m_iIntegerValue;
	} else if ( m_iFlags & SYSVAR_FLOAT ) {
		m_fFloatValue = (float)atof( m_pValue );
		if ( m_fValueMin < m_fValueMax ) {
			if ( m_fFloatValue < m_fValueMin ) {
				m_fFloatValue = m_fValueMin;
				clamped = true;
			} else if ( m_fFloatValue > m_fValueMax ) {
				m_fFloatValue = m_fValueMax;
				clamped = true;
			}
		}
		if ( clamped || !CMyString::IsNumeric( m_pValue ) ) {
			valueString = CMyString( m_fFloatValue );
			m_pValue = valueString.c_str();
		}
		m_iIntegerValue = (int)m_fFloatValue;
	} else {
		if ( m_ValueStrings && m_ValueStrings[0] ) {
			m_iIntegerValue = 0;
			for ( int i = 0; m_ValueStrings[i]; i++ ) {
				if ( valueString.Icmp( m_ValueStrings[i] ) == 0 ) {
					m_iIntegerValue = i;
					break;
				}
			}
			valueString = m_ValueStrings[m_iIntegerValue];
			m_pValue = valueString.c_str();
			m_fFloatValue = (float)m_iIntegerValue;
		} else if ( valueString.Length() < 32 ) {
			m_fFloatValue = (float)atof( m_pValue );
			m_iIntegerValue = (int)m_fFloatValue;
		} else {
			m_fFloatValue = 0.0f;
			m_iIntegerValue = 0;
		}
	}
}

/*
============
CEngineSysVar::UpdateCheat
============
*/
void CEngineSysVar::UpdateCheat() {
	// all variables are considered cheats except for a few types
	if ( m_iFlags & ( SYSVAR_NOCHEAT | SYSVAR_INIT | SYSVAR_ROM | SYSVAR_ARCHIVE | SYSVAR_USERINFO | SYSVAR_SERVERINFO | SYSVAR_NETWORKSYNC ) ) {
		m_iFlags &= ~SYSVAR_CHEAT;
	} else {
		m_iFlags |= SYSVAR_CHEAT;
	}
}

/*
============
CEngineSysVar::Set
============
*/
void CEngineSysVar::SetGlobal( const char *newValue, bool force, bool fromServer ) {
#if 0
	if ( session && session->IsMultiplayer() && !fromServer ) {
#ifndef ID_TYPEINFO
		if ( ( m_iFlags & SYSVAR_NETWORKSYNC ) && idAsyncNetwork::client.IsActive() ) {
			common->Printf( "%s is a synced over the network and cannot be changed on a multiplayer client.\n", nameString.c_str() );
#if ID_ALLOW_CHEATS
			common->Printf( "ID_ALLOW_CHEATS override!\n" );
#else
			return;
#endif
		}
#endif
		if ( ( m_iFlags & SYSVAR_CHEAT ) && !cvarSystem->GetCVarBool( "net_allowCheats" ) ) {
			common->Printf( "%s cannot be changed in multiplayer.\n", nameString.c_str() );
#if ID_ALLOW_CHEATS
			common->Printf( "ID_ALLOW_CHEATS override!\n" );
#else
			return;
#endif
		}
	}
#endif
	if ( !newValue ) {
		newValue = resetString.c_str();
	}

	if ( !force ) {
		if ( m_iFlags & SYSVAR_ROM ) {
			//s common->Printf( "%s is read only.\n", nameString.c_str() );
			return;
		}

		if ( m_iFlags & SYSVAR_INIT ) {
			//s common->Printf( "%s is write protected.\n", nameString.c_str() );
			return;
		}
	}
	// se não houve mudança no valor, retorna
	if ( valueString.Icmp( newValue ) == 0 ) {
		return;
	}
	//se houve mudança no valor, continua
	valueString = newValue;
	m_pValue = valueString.c_str();
	UpdateValue();

	setModified();

	globalSysVarSystem.SetModifiedFlags( m_iFlags );
	if (this->onChangeRunObjectCallback() && isThereCallBackToObject()) this->runObjCallback(NULL);
	if (this->onChangeRunStaticCallback() && isThereCallBack()) this->runCallback();

}

/*
============
CEngineSysVar::Reset
============
*/
void CEngineSysVar::Reset() {
	valueString = resetString;
	m_pValue = valueString.c_str();
	UpdateValue();
}

/*
============
CEngineSysVar::internalSetString
============
*/
void CEngineSysVar::internalSetString( const char *newValue ) {
	SetGlobal( newValue, true, false );
}

/*
===============
CEngineSysVar::InternalServerSetString
===============
*/
void CEngineSysVar::InternalServerSetString( const char *newValue ) {
	SetGlobal( newValue, true, true );
}

/*
============
CEngineSysVar::internalSetBool
============
*/
void CEngineSysVar::internalSetBool( const bool newValue ) {
	SetGlobal( CMyString( newValue ), true, false );
}

/*
============
CEngineSysVar::internalSetInteger
============
*/
void CEngineSysVar::internalSetInteger( const int newValue ) {
	SetGlobal( CMyString( newValue ), true, false );
}

/*
============
CEngineSysVar::internalSetFloat
============
*/
void CEngineSysVar::internalSetFloat( const float newValue ) {
	SetGlobal( CMyString( newValue ), true, false );
}
//================LOCAL SYSVAR=======================

/*
============
CLocalSysVar::CLocalSysVar
============
*/
CLocalSysVar::CLocalSysVar() {
 // memset(&m_p_StaticLocalVars, 0, sizeof m_p_StaticLocalVars);
}

/*
============
CLocalSysVar::CLocalSysVar
============
*/

CLocalSysVar::CLocalSysVar( const char *newName, const char *newValue, int newFlags, int index,const char *newDescription  ):
	CSysVar(newName,newValue,( newFlags & ~SYSVAR_STATIC ),newDescription,NULL,true){
	//memset(&m_p_StaticLocalVars, 0, sizeof m_p_StaticLocalVars);
	nameString = newName;
	//m_pName = nameString.c_str();
	valueString = newValue;
	//m_pValue = valueString.c_str();
	resetString = newValue;
	descriptionString = newDescription;
	m_pDescription = descriptionString.c_str();
	//m_iFlags = ( newFlags & ~SYSVAR_STATIC ) | SYSVAR_MODIFIED;
	m_fValueMin = 1;
	m_fValueMax = -1;
	m_ValueStrings = NULL;
	m_tValueCompletion = 0;
	UpdateValue();
	UpdateCheat();
	m_iIndex=index;
	m_pInternalVar = this;
	if ( m_p_StaticLocalVars[index] != (CLocalSysVar *)0xFFFFFFFF ) {
			this->m_pNext = m_p_StaticLocalVars[index];
			m_p_StaticLocalVars[index] = this;
		} else {

			CConfiguration::ConfigList[index]->Register( *this );
		}

}

/*
============
CLocalSysVar::CLocalSysVar
============
*/
CLocalSysVar::CLocalSysVar( const CSysVar *cvar ):
CSysVar(cvar) {
	nameString = cvar->getName();
	valueString = cvar->getString();
	resetString = cvar->getString();
	descriptionString = cvar->getDescription();
	m_ValueStrings = CopyValueStrings( cvar->getValueStrings() );
	UpdateValue();
	UpdateCheat();
	m_pInternalVar = this;
	m_bLocal=true;
	
}

/*
============
CLocalSysVar::~CLocalSysVar
============
*/
CLocalSysVar::~CLocalSysVar() {
	Mem_Free( m_ValueStrings );
	m_ValueStrings = NULL;
}


/*
============
CLocalSysVar::CopyValueStrings
============
*/
const char **CLocalSysVar::CopyValueStrings( const char **strings ) {
	int i, totalLength;
	const char **ptr;
	char *str;

	if ( !strings ) {
		return NULL;
	}

	totalLength = 0;
	for ( i = 0; strings[i] != NULL; i++ ) {
		totalLength += CMyString::Length( strings[i] ) + 1;
	}

	ptr = (const char **) Mem_Alloc( ( i + 1 ) * sizeof( char * ) + totalLength );
	str = (char *) (((SGF_Byte *)ptr) + ( i + 1 ) * sizeof( char * ) );

	for ( i = 0; strings[i] != NULL; i++ ) {
		ptr[i] = str;
		strcpy( str, strings[i] );
		str += CMyString::Length( strings[i] ) + 1;
	}
	ptr[i] = NULL;

	return ptr;
}

/*
============
CLocalSysVar::Update
============
*/
void CLocalSysVar::Update( const CSysVar *cvarToUpdate ) {

	// if this is a statically declared variable
	if ( cvarToUpdate->getFlags() & SYSVAR_STATIC ) {

		if ( m_iFlags & SYSVAR_STATIC ) {

			// the code has more than one static declaration of the same variable, make sure they have the same properties
			if ( resetString.Icmp( cvarToUpdate->getString() ) != 0 ) {
				Debug::debug(Debug::configuration,__FUNCTION__)<< "SysVar "<< nameString.c_str() << " declared multiple times with different initial value"<< endl;
			}
			if ( ( m_iFlags & (SYSVAR_BOOL|SYSVAR_INTEGER|SYSVAR_FLOAT) ) != ( cvarToUpdate->getFlags() & (SYSVAR_BOOL|SYSVAR_INTEGER|SYSVAR_FLOAT) ) ) {
				Debug::debug(Debug::configuration,__FUNCTION__)<< "SysVar "<< nameString.c_str() << " declared multiple times with different type"<< endl;
			}
			if ( m_fValueMin != cvarToUpdate->getMinValue() || m_fValueMax != cvarToUpdate->getMaxValue() ) {
				Debug::debug(Debug::configuration,__FUNCTION__)<< "SysVar "<< nameString.c_str() << " declared multiple times with different minimum/maximum"<< endl;
			}

		}

		// the code is now specifying a variable that the user already set a value for, take the new value as the reset value
		resetString = cvarToUpdate->getString();
		descriptionString = cvarToUpdate->getDescription();
		m_pDescription = descriptionString.c_str();
		m_fValueMin = cvarToUpdate->getMinValue();
		m_fValueMax = cvarToUpdate->getMaxValue();
		Mem_Free( m_ValueStrings );
		m_ValueStrings = CopyValueStrings( cvarToUpdate->getValueStrings() );
		m_tValueCompletion = cvarToUpdate->getValueCompletion();
		UpdateValue();
		if (m_iIndex <0) throw Exception::Return("Index Not Set",__LINE__);
		CConfiguration::ConfigList[m_iIndex]->SetModifiedFlags( cvarToUpdate->getFlags() );
	}

	m_iFlags |= cvarToUpdate->getFlags();

	UpdateCheat();

	// only allow one non-empty reset string without a warning
	if ( resetString.Length() == 0 ) {
		resetString = cvarToUpdate->getString();
	} else if ( cvarToUpdate->getString()[0] && resetString.Cmp( cvarToUpdate->getString() ) != 0 ) {
		Debug::debug(Debug::configuration,__FUNCTION__)<< "cvar \""<<nameString.c_str() <<"\" given initial values: \""<< resetString.c_str()<<"\" and \""<< cvarToUpdate->getString()<< "\""<<endl;
	}
}

/*
============
CLocalSysVar::UpdateValue
============
*/
void CLocalSysVar::UpdateValue() {
	bool clamped = false;

	if ( m_iFlags & SYSVAR_BOOL ) {
		m_iIntegerValue = ( atoi( m_pValue ) != 0 );
		m_fFloatValue = m_iIntegerValue;
		if ( CMyString::Icmp( m_pValue, "0" ) != 0 && CMyString::Icmp( m_pValue, "1" ) != 0 ) {
			valueString = CMyString( (bool)( m_iIntegerValue != 0 ) );
			m_pValue = valueString.c_str();
		}
	} else if ( m_iFlags & SYSVAR_INTEGER ) {
		m_iIntegerValue = (int)atoi( m_pValue );
		if ( m_fValueMin < m_fValueMax ) {
			if ( m_iIntegerValue < m_fValueMin ) {
				m_iIntegerValue = (int)m_fValueMin;
				clamped = true;
			} else if ( m_iIntegerValue > m_fValueMax ) {
				m_iIntegerValue = (int)m_fValueMax;
				clamped = true;
			}
		}
		if ( clamped || !CMyString::IsNumeric( m_pValue ) || CMyString::FindChar( m_pValue, '.' ) ) {
			valueString = CMyString( m_iIntegerValue );
			m_pValue = valueString.c_str();
		}
		m_fFloatValue = (float)m_iIntegerValue;
	} else if ( m_iFlags & SYSVAR_FLOAT ) {
		m_fFloatValue = (float)atof( m_pValue );
		if ( m_fValueMin < m_fValueMax ) {
			if ( m_fFloatValue < m_fValueMin ) {
				m_fFloatValue = m_fValueMin;
				clamped = true;
			} else if ( m_fFloatValue > m_fValueMax ) {
				m_fFloatValue = m_fValueMax;
				clamped = true;
			}
		}
		if ( clamped || !CMyString::IsNumeric( m_pValue ) ) {
			valueString = CMyString( m_fFloatValue );
			m_pValue = valueString.c_str();
		}
		m_iIntegerValue = (int)m_fFloatValue;
	} else {
		if ( m_ValueStrings && m_ValueStrings[0] ) {
			m_iIntegerValue = 0;
			for ( int i = 0; m_ValueStrings[i]; i++ ) {
				if ( valueString.Icmp( m_ValueStrings[i] ) == 0 ) {
					m_iIntegerValue = i;
					break;
				}
			}
			valueString = m_ValueStrings[m_iIntegerValue];
			m_pValue = valueString.c_str();
			m_fFloatValue = (float)m_iIntegerValue;
		} else if ( valueString.Length() < 32 ) {
			m_fFloatValue = (float)atof( m_pValue );
			m_iIntegerValue = (int)m_fFloatValue;
		} else {
			m_fFloatValue = 0.0f;
			m_iIntegerValue = 0;
		}
	}
}

/*
============
CLocalSysVar::UpdateCheat
============
*/
void CLocalSysVar::UpdateCheat() {
	// all variables are considered cheats except for a few types
	if ( m_iFlags & ( SYSVAR_NOCHEAT | SYSVAR_INIT | SYSVAR_ROM | SYSVAR_ARCHIVE | SYSVAR_USERINFO | SYSVAR_SERVERINFO | SYSVAR_NETWORKSYNC ) ) {
		m_iFlags &= ~SYSVAR_CHEAT;
	} else {
		m_iFlags |= SYSVAR_CHEAT;
	}
}

/*
============
CLocalSysVar::Set
============
*/
void CLocalSysVar::SetLocal( const char *newValue, bool force, bool fromServer ) {
#if 0
	if ( session && session->IsMultiplayer() && !fromServer ) {
#ifndef ID_TYPEINFO
		if ( ( m_iFlags & SYSVAR_NETWORKSYNC ) && idAsyncNetwork::client.IsActive() ) {
			common->Printf( "%s is a synced over the network and cannot be changed on a multiplayer client.\n", nameString.c_str() );
#if ID_ALLOW_CHEATS
			common->Printf( "ID_ALLOW_CHEATS override!\n" );
#else
			return;
#endif
		}
#endif
		if ( ( m_iFlags & SYSVAR_CHEAT ) && !cvarSystem->GetCVarBool( "net_allowCheats" ) ) {
			common->Printf( "%s cannot be changed in multiplayer.\n", nameString.c_str() );
#if ID_ALLOW_CHEATS
			common->Printf( "ID_ALLOW_CHEATS override!\n" );
#else
			return;
#endif
		}
	}
#endif
	if ( !newValue ) {
		newValue = resetString.c_str();
	}

	if ( !force ) {
		if ( m_iFlags & SYSVAR_ROM ) {
			//s common->Printf( "%s is read only.\n", nameString.c_str() );
			return;
		}

		if ( m_iFlags & SYSVAR_INIT ) {
			//s common->Printf( "%s is write protected.\n", nameString.c_str() );
			return;
		}
	}

	if ( valueString.Icmp( newValue ) == 0 ) {
		return;
	}

	valueString = newValue;
	m_pValue = valueString.c_str();
	UpdateValue();

	setModified();
	if (this->onChangeRunObjectCallback() && isThereCallBackToObject()) this->runObjCallback(NULL);
	if (this->onChangeRunStaticCallback() && isThereCallBack()) this->runCallback();

	if (m_iIndex <0) throw Exception::Return("Index Not Set",__LINE__);
	CConfiguration::ConfigList[m_iIndex]->SetModifiedFlags( m_iFlags );
}

/*
============
CLocalSysVar::Reset
============
*/
void CLocalSysVar::Reset() {
	valueString = resetString;
	m_pValue = valueString.c_str();
	UpdateValue();
}

/*
============
CLocalSysVar::internalSetString
============
*/
void CLocalSysVar::internalSetString( const char *newValue ) {
	SetLocal( newValue, true, false );
}

/*
===============
CLocalSysVar::InternalServerSetString
===============
*/
void CLocalSysVar::internalServerSetString( const char *newValue ) {
	SetLocal( newValue, true, true );
}

/*
============
CLocalSysVar::internalSetBool
============
*/
void CLocalSysVar::internalSetBool( const bool newValue ) {
	SetLocal( CMyString( newValue ), true, false );
}

/*
============
CLocalSysVar::internalSetInteger
============
*/
void CLocalSysVar::internalSetInteger( const int newValue ) {
	SetLocal( CMyString( newValue ), true, false );
}

/*
============
CLocalSysVar::internalSetFloat
============
*/
void CLocalSysVar::internalSetFloat( const float newValue ) {
	SetLocal( CMyString( newValue ), true, false );
}




//===================END LOCAL SYSVAR
//=============GLOBALCONFIGURATION=================

/*
============
CGlobalConfiguration::FindInternal
============
*/
CSysVar *CGlobalConfiguration::FindInternal( const char *name ) const {
	int hash = m_SysVarHash.generate_Key( name, false );
	for ( int i = m_SysVarHash.getFirst( hash ); i != -1; i = m_SysVarHash.getNext( i ) ) {
		if ( ((CEngineSysVar *)m_globalSysVars[i])->nameString.Icmp( name ) == 0 ) {
			return m_globalSysVars[i];
		}
	}
	return NULL;
}


/** @fn setInternal( const char *name, const char *value, int m_iFlags )
\brief Método que muda o nome e valor de uma variável registrada como internal Csysvar
\param name: nome da variável
\param value: valor da variável
\param m_iFlags: flags
\note Se a variável interna não existir, então ela é criada e adicionada à lista (registrada)
**/
void CGlobalConfiguration::setInternal( const char *name, const char *value, int m_iFlags ) {
	int hash;
	CEngineSysVar *internal;

	internal = (CEngineSysVar *)FindInternal( name );
	//If find the cvar, update its values
	if ( internal ) {
		internal->internalSetString( value );
		internal->m_iFlags |= m_iFlags & ~SYSVAR_STATIC;
		internal->UpdateCheat();
	} else { //if do not find create one
		internal = new CEngineSysVar( name, value, m_iFlags );
		hash = m_SysVarHash.generate_Key( internal->nameString.c_str(), false );
		m_SysVarHash.Add( hash, m_globalSysVars.append( internal ) );
	}
}



/*
============
CGlobalConfiguration::init
============
*/
void CGlobalConfiguration::init() {

	m_iModifiedFlags = 0;

	//cmdSystem->AddCommand( "toggle", Toggle_f, CMD_FL_SYSTEM, "toggles a cvar" );
	//cmdSystem->AddCommand( "set", Set_f, CMD_FL_SYSTEM, "sets a cvar" );
	//cmdSystem->AddCommand( "sets", SetS_f, CMD_FL_SYSTEM, "sets a cvar and m_iFlags it as server info" );
	//cmdSystem->AddCommand( "setu", SetU_f, CMD_FL_SYSTEM, "sets a cvar and m_iFlags it as user info" );
	//cmdSystem->AddCommand( "sett", SetT_f, CMD_FL_SYSTEM, "sets a cvar and m_iFlags it as tool" );
	//cmdSystem->AddCommand( "seta", SetA_f, CMD_FL_SYSTEM, "sets a cvar and m_iFlags it as archive" );
	//cmdSystem->AddCommand( "reset", Reset_f, CMD_FL_SYSTEM, "resets a cvar" );
	//cmdSystem->AddCommand( "listCvars", List_f, CMD_FL_SYSTEM, "lists cvars" );
	//cmdSystem->AddCommand( "cvar_restart", Restart_f, CMD_FL_SYSTEM, "restart the cvar system" );

	m_bInitialized = true;
}

/*
============
CGlobalConfiguration::Shutdown
============
*/
void CGlobalConfiguration::Shutdown() {
	m_globalSysVars.deleteContents( true );
	m_SysVarHash.freeMem();
	//moveCVarsToDict.Clear();
	m_bInitialized = false;
}

/*
============
CGlobalConfiguration::IsInitialized
============
*/
bool CGlobalConfiguration::IsInitialized() const {
	return m_bInitialized;
}

/*
============
CGlobalConfiguration::Register
============
*/
void CGlobalConfiguration::Register( CSysVar &cvarToRegister ) {
	int hash;
	CEngineSysVar *internal;

	cvarToRegister.setInternalVar( &cvarToRegister );

	internal = (CEngineSysVar *)FindInternal( cvarToRegister.getName() );
	//! se a variável já existe, apenas update do seu valor e avisa que é uma duplicata via debug
	if ( internal ) {
		internal->Update( &cvarToRegister );
	} else {
		internal = new CEngineSysVar ( &cvarToRegister );
		hash = m_SysVarHash.generate_Key( internal->nameString.c_str(), false );
		m_SysVarHash.Add( hash, m_globalSysVars.append( internal ) ); //adiciona na lista local
	}

	cvarToRegister.setInternalVar( internal );
}

/*
============
CGlobalConfiguration::Find
============
*/
CSysVar *CGlobalConfiguration::Find( const char *name ) {
	return FindInternal( name );
}


/** @fn setCVarString( const char *name, const char *value, int m_iFlags )
\brief Método que muda o nome e valor de uma variável tipo String registrada como internal Csysvar
\param name: nome da variável
\param value: valor da variável
\param m_iFlags: flags
\note Se a variável interna não existir, então ela é criada e adicionada à lista (registrada)
**/
void CGlobalConfiguration::setCVarString( const char *name, const char *value, int m_iFlags ) {
	setInternal( name, value, m_iFlags );
}

/** @fn setCVarBool( const char *name, const bool value, int m_iFlags )
\brief Método que muda o nome e valor de uma variável tipo Bool registrada como internal Csysvar
\param name: nome da variável
\param value: valor da variável (bool)
\param m_iFlags: flags
\note Se a variável interna não existir, então ela é criada e adicionada à lista (registrada)
**/
void CGlobalConfiguration::setCVarBool( const char *name, const bool value, int m_iFlags ) {
	setInternal( name, CMyString( value ), m_iFlags );
}

/** @fn setCVarInteger( const char *name, const int value, int m_iFlags )
\brief Método que muda o nome e valor de uma variável tipo Integer registrada como internal Csysvar
\param name: nome da variável
\param value: valor da variável (integer)
\param m_iFlags: flags
\note Se a variável interna não existir, então ela é criada e adicionada à lista (registrada)
**/
void CGlobalConfiguration::setCVarInteger( const char *name, const int value, int m_iFlags ) {
	setInternal( name, CMyString( value ), m_iFlags );
}

/** @fn setCVarFloat( const char *name, const float value, int m_iFlags )
\brief Método que muda o nome e valor de uma variável tipo Float registrada como internal Csysvar
\param name: nome da variável
\param value: valor da variável (Float)
\param m_iFlags: flags
\note Se a variável interna não existir, então ela é criada e adicionada à lista (registrada)
**/
void CGlobalConfiguration::setCVarFloat( const char *name, const float value, int m_iFlags ) {
	setInternal( name, CMyString( value ), m_iFlags );
}

/** 
\brief Método que retorna o valor String de uma variável CSysVar
\param name: nome da variável
\note Só retorna o valor da variável interna, aquela registada
**/
const char *CGlobalConfiguration::getCVarString( const char *name ) const {
	CEngineSysVar *internal = (CEngineSysVar *)FindInternal( name );
	if ( internal ) {
		return internal->getString();
	}
	return "";
}

/** 
\brief Método que retorna o valor Bool de uma variável CSysVar
\param name: nome da variável
\note Só retorna o valor da variável interna, aquela registada
**/
bool CGlobalConfiguration::getCVarBool( const char *name ) const {
	CEngineSysVar *internal = (CEngineSysVar *)FindInternal( name );
	if ( internal ) {
		return internal->getBool();
	}
	return false;
}

/** 
\brief Método que retorna o valor Integer de uma variável CSysVar
\param name: nome da variável
\note Só retorna o valor da variável interna, aquela registada
**/
int CGlobalConfiguration::getCVarInteger( const char *name ) const {
	CEngineSysVar *internal = (CEngineSysVar *)FindInternal( name );
	if ( internal ) {
		return internal->getInteger();
	}
	return 0;
}

/** 
\brief Método que retorna o valor Float de uma variável CSysVar
\param name: nome da variável
\note Só retorna o valor da variável interna, aquela registada
**/
float CGlobalConfiguration::getCVarFloat( const char *name ) const {
	CEngineSysVar *internal = (CEngineSysVar *)FindInternal( name );
	if ( internal ) {
		return internal->getFloat();
	}
	return 0.0f;
}

/*
============
CGlobalConfiguration::Command
============
*/
bool CGlobalConfiguration::Command( const CCmdArgs &args ) {
	CEngineSysVar *internal;

	internal = (CEngineSysVar *)FindInternal( args.getArgv( 0 ) );

	if ( internal == NULL ) {
		return false;
	}

	if ( args.getArgc() == 1 ) {
		// print the variable
		//TODO PRINT TO CONSOLE
		//common->Printf( "\"%s\" is:\"%s\"" S_COLOR_WHITE " default:\"%s\"\n",
		//			internal->nameString.c_str(), internal->valueString.c_str(), internal->resetString.c_str() );
		if ( CMyString::Length( internal->getDescription() ) > 0 ) {
			//TODO PRINT TO CONSOLE
		//common->Printf( S_COLOR_WHITE "%s\n", internal->getDescription() );
		}
	} else {
		// set the value
		internal->SetGlobal( args.getArgs(), false, false );
	}
	return true;
}

/*
============
CGlobalConfiguration::CommandCompletion
============
*/
void CGlobalConfiguration::CommandCompletion( void(*callback)( const char *s ) ) {
	for( int i = 0; i < m_globalSysVars.getNum(); i++ ) {
		callback( m_globalSysVars[i]->getName() ); //chama a função de completar o comando com o nome da variável como parâmetro
	}
}

/*
============
CGlobalConfiguration::ArgCompletion
============
*/
void CGlobalConfiguration::ArgCompletion( const char *cmdString, void(*callback)( const char *s ) ) {
	CCmdArgs args;

	args.tokenizeString( cmdString, false );

	for( int i = 0; i < m_globalSysVars.getNum(); i++ ) {
		if ( !m_globalSysVars[i]->m_tValueCompletion ) {
			continue;
		}
		if ( CMyString::Icmp( args.getArgv( 0 ), m_globalSysVars[i]->nameString.c_str() ) == 0 ) {
			m_globalSysVars[i]->m_tValueCompletion( args, callback );
			break;
		}
	}
}

/*
============
CGlobalConfiguration::SetModifiedFlags
============
*/
void CGlobalConfiguration::SetModifiedFlags( int m_iFlags ) {
	m_iModifiedFlags |= m_iFlags;
}

/*
============
CGlobalConfiguration::GetModifiedFlags
============
*/
int CGlobalConfiguration::GetModifiedFlags() const {
	return m_iModifiedFlags;
}

/*
============
CGlobalConfiguration::ClearModifiedFlags
============
*/
void CGlobalConfiguration::ClearModifiedFlags( int m_iFlags ) {
	m_iModifiedFlags &= ~m_iFlags;
}

/*
============
CGlobalConfiguration::ResetFlaggedVariables
============
*/
void CGlobalConfiguration::ResetFlaggedVariables( int m_iFlags ) {
	for( int i = 0; i < m_globalSysVars.getNum(); i++ ) {
		CEngineSysVar *cvar = m_globalSysVars[i];
		if ( cvar->getFlags() & m_iFlags ) {
			cvar->SetGlobal( NULL, true, true );
		}
	}

}

/*
============
CGlobalConfiguration::RemoveFlaggedAutoCompletion
============
*/
void CGlobalConfiguration::RemoveFlaggedAutoCompletion( int m_iFlags ) {
	for( int i = 0; i < m_globalSysVars.getNum(); i++ ) {
		CEngineSysVar *cvar = (CEngineSysVar *)m_globalSysVars[i];
		if ( cvar->getFlags() & m_iFlags ) {
			cvar->m_tValueCompletion = NULL;
		}
	}
}

/*
============
CGlobalConfiguration::Toggle_f
============
*/
void CGlobalConfiguration::Toggle_f( const CCmdArgs &args ) {
	int argc, i;
	float current, set;
	const char *text;

	argc = args.getArgc();
	if ( argc < 2 ) {
		//TODO PRINT TO CONSOLE
		//->Printf ("usage:\n"
		//	"   toggle <variable>  - toggles between 0 and 1\n"
		//	"   toggle <variable> <value> - toggles between 0 and <value>\n"
		//	"   toggle <variable> [string 1] [string 2]...[string n] - cycles through all strings\n");
		return;
	}

	CEngineSysVar *cvar =( CEngineSysVar *) globalSysVarSystem.FindInternal( args.getArgv( 1 ) );

	if ( cvar == NULL ) {
		Debug::debug(Debug::configuration,__FUNCTION__)<< "Toggle_f: cvar \""<<args.getArgv( 1 )<<"\" not found"<<endl;
		return;
	}

	if ( argc > 3 ) {
		// cycle through multiple values
		text = cvar->getString();
		for( i = 2; i < argc; i++ ) {
			if ( !CMyString::Icmp( text, args.getArgv( i ) ) ) {
				// point to next value
				i++;
				break;
			}
		}
		if ( i >= argc ) {
			i = 2;
		}

		//TODO PRINT TO CONSOLE
		//common->Printf( "set %s = %s\n", args.getArgv(1), args.getArgv( i ) );
		cvar->SetGlobal( va("%s", args.getArgv( i ) ), false, false );
	} else {
		// toggle between 0 and 1
		current = cvar->getFloat();
		if ( argc == 3 ) {
			set = atof( args.getArgv( 2 ) );
		} else {
			set = 1.0f;
		}
		if ( current == 0.0f ) {
			current = set;
		} else {
			current = 0.0f;
		}
		//TODO PRINT TO CONSOLE
		//common->Printf( "set %s = %f\n", args.getArgv(1), current );
		cvar->SetGlobal( CMyString( current ), false, false );
	}
}

/*
============
CGlobalConfiguration::Set_f
============
*/
void CGlobalConfiguration::Set_f( const CCmdArgs &args ) {
	const char *str;

	str = args.getArgs( 2, args.getArgc() - 1 );
	globalSysVarSystem.setCVarString( args.getArgv(1), str );
}

/*
============
CGlobalConfiguration::SetS_f
============
*/
void CGlobalConfiguration::SetS_f( const CCmdArgs &args ) {
	CEngineSysVar *cvar;

	Set_f( args );
	cvar = (CEngineSysVar *)globalSysVarSystem.FindInternal( args.getArgv( 1 ) );
	if ( !cvar ) {
		return;
	}
	cvar->m_iFlags |= SYSVAR_SERVERINFO | SYSVAR_ARCHIVE;
}

/*
============
CGlobalConfiguration::SetU_f
============
*/
void CGlobalConfiguration::SetU_f( const CCmdArgs &args ) {
	CEngineSysVar *cvar;

	Set_f( args );
	cvar = (CEngineSysVar *)globalSysVarSystem.FindInternal( args.getArgv( 1 ) );
	if ( !cvar ) {
		return;
	}
	cvar->m_iFlags |= SYSVAR_USERINFO | SYSVAR_ARCHIVE;
}

/*
============
CGlobalConfiguration::SetT_f
============
*/
void CGlobalConfiguration::SetT_f( const CCmdArgs &args ) {
	CEngineSysVar *cvar;

	Set_f( args );
	cvar = (CEngineSysVar *)globalSysVarSystem.FindInternal( args.getArgv( 1 ) );
	if ( !cvar ) {
		return;
	}
	cvar->m_iFlags |= SYSVAR_TOOL;
}

/*
============
CGlobalConfiguration::SetA_f
============
*/
void CGlobalConfiguration::SetA_f( const CCmdArgs &args ) {
	CEngineSysVar *cvar;

	Set_f( args );
	cvar = (CEngineSysVar *)globalSysVarSystem.FindInternal( args.getArgv( 1 ) );
	if ( !cvar ) {
		return;
	}

	// FIXME: enable this for ship, so mods can store extra data
	// but during development we don't want obsolete cvars to continue
	// to be saved
//	cvar->m_iFlags |= SYSVAR_ARCHIVE;
}

/*
============
CGlobalConfiguration::Reset_f
============
*/
void CGlobalConfiguration::Reset_f( const CCmdArgs &args ) {
	CEngineSysVar *cvar;

	if ( args.getArgc() != 2 ) {
		//TODO PRINT TO CONSOLE
		//common->Printf ("usage: reset <variable>\n");
		return;
	}
	cvar =(CEngineSysVar *) globalSysVarSystem.FindInternal( args.getArgv( 1 ) );
	if ( !cvar ) {
		return;
	}

	cvar->Reset();
}

/*
============
CGlobalConfiguration::ListByFlags
============
*/
// NOTE: the const wonkyness is required to make msvc happy
template<>
SGF_INLINE_FORCED int CListSortCompare( const CEngineSysVar * const *a, const CEngineSysVar * const *b ) {
	return CMyString::Icmp( (*a)->getName(), (*b)->getName() );
}

void CGlobalConfiguration::ListByFlags( const CCmdArgs &args, cvarFlags_t m_iFlags ) {
	int i, argNum;
	CMyString match, indent, string;
	const CEngineSysVar *cvar;
	CList<const CEngineSysVar *>cvarList;

	enum {
		SHOW_VALUE,
		SHOW_DESCRIPTION,
		SHOW_TYPE,
		SHOW_FLAGS
	} show;

	argNum = 1;
	show = SHOW_VALUE;

	if ( CMyString::Icmp( args.getArgv( argNum ), "-" ) == 0 || CMyString::Icmp( args.getArgv( argNum ), "/" ) == 0 ) {
		if ( CMyString::Icmp( args.getArgv( argNum + 1 ), "help" ) == 0 || CMyString::Icmp( args.getArgv( argNum + 1 ), "?" ) == 0 ) {
			argNum = 3;
			show = SHOW_DESCRIPTION;
		} else if ( CMyString::Icmp( args.getArgv( argNum + 1 ), "type" ) == 0 || CMyString::Icmp( args.getArgv( argNum + 1 ), "range" ) == 0 ) {
			argNum = 3;
			show = SHOW_TYPE;
		} else if ( CMyString::Icmp( args.getArgv( argNum + 1 ), "m_iFlags" ) == 0 ) {
			argNum = 3;
			show = SHOW_FLAGS;
		}
	}

	if ( args.getArgc() > argNum ) {
		match = args.getArgs( argNum, -1 );
		match.Replace( " ", "" );
	} else {
		match = "";
	}

	for ( i = 0; i < globalSysVarSystem.m_globalSysVars.getNum(); i++ ) {
		cvar = (CEngineSysVar *)globalSysVarSystem.m_globalSysVars[i];

		if ( !( cvar->getFlags() & m_iFlags ) ) {
			continue;
		}

		if ( match.Length() && !cvar->nameString.Filter( match, false ) ) {
			continue;
		}

		cvarList.append( cvar );
	}

	cvarList.sort();

	switch( show ) {
		case SHOW_VALUE: {
			for ( i = 0; i < cvarList.getNum(); i++ ) {
				cvar = cvarList[i];
				//TODO PRINT TO CONSOLE
		//common->Printf( FORMAT_STRING S_COLOR_WHITE "\"%s\"\n", cvar->nameString.c_str(), cvar->valueString.c_str() );
			}
			break;
		}
		case SHOW_DESCRIPTION: {
			indent.Fill( ' ', NUM_NAME_CHARS );
			indent.Insert( "\n", 0 );

			for ( i = 0; i < cvarList.getNum(); i++ ) {
				cvar = cvarList[i];
				//TODO PRINT TO CONSOLE
		//common->Printf( FORMAT_STRING S_COLOR_WHITE "%s\n", cvar->nameString.c_str(), CreateColumn( cvar->getDescription(), NUM_DESCRIPTION_CHARS, indent, string ) );
			}
			break;
		}
		case SHOW_TYPE: {
			for ( i = 0; i < cvarList.getNum(); i++ ) {
				cvar = cvarList[i];
				if ( cvar->getFlags() & SYSVAR_BOOL ) {
					//TODO PRINT TO CONSOLE
		//common->Printf( FORMAT_STRING S_COLOR_CYAN "bool\n", cvar->getName() );
				} else if ( cvar->getFlags() & SYSVAR_INTEGER ) {
					if ( cvar->getMinValue() < cvar->getMaxValue() ) {
						//TODO PRINT TO CONSOLE
		//common->Printf( FORMAT_STRING S_COLOR_GREEN "int " S_COLOR_WHITE "[%d, %d]\n", cvar->getName(), (int) cvar->getMinValue(), (int) cvar->getMaxValue() );
					} else {
						//TODO PRINT TO CONSOLE
		//common->Printf( FORMAT_STRING S_COLOR_GREEN "int\n", cvar->getName() );
					}
				} else if ( cvar->getFlags() & SYSVAR_FLOAT ) {
					if ( cvar->getMinValue() < cvar->getMaxValue() ) {
						//TODO PRINT TO CONSOLE
		//common->Printf( FORMAT_STRING S_COLOR_RED "float " S_COLOR_WHITE "[%s, %s]\n", cvar->getName(), CMyString( cvar->getMinValue() ).c_str(), CMyString( cvar->getMaxValue() ).c_str() );
					} else {
						//TODO PRINT TO CONSOLE
		//common->Printf( FORMAT_STRING S_COLOR_RED "float\n", cvar->getName() );
					}
				} else if ( cvar->getValueStrings() ) {
					//TODO PRINT TO CONSOLE
		//common->Printf( FORMAT_STRING S_COLOR_WHITE "string " S_COLOR_WHITE "[", cvar->getName() );
					for ( int j = 0; cvar->getValueStrings()[j] != NULL; j++ ) {
						if ( j ) {
							//TODO PRINT TO CONSOLE
		//common->Printf( S_COLOR_WHITE ", %s", cvar->getValueStrings()[j] );
						} else {
							//TODO PRINT TO CONSOLE
		//common->Printf( S_COLOR_WHITE "%s", cvar->getValueStrings()[j] );
						}
					}
					//TODO PRINT TO CONSOLE
		//common->Printf( S_COLOR_WHITE "]\n" );
				} else {
					//TODO PRINT TO CONSOLE
		//common->Printf( FORMAT_STRING S_COLOR_WHITE "string\n", cvar->getName() );
				}
			}
			break;
		}
		case SHOW_FLAGS: {
			for ( i = 0; i < cvarList.getNum(); i++ ) {
				cvar = cvarList[i];
				//TODO PRINT TO CONSOLE
		//common->Printf( FORMAT_STRING, cvar->getName() );
				string = "";
				if ( cvar->getFlags() & SYSVAR_BOOL ) {
					string += S_COLOR_CYAN "B ";
				} else if ( cvar->getFlags() & SYSVAR_INTEGER ) {
					string += S_COLOR_GREEN "I ";
				} else if ( cvar->getFlags() & SYSVAR_FLOAT ) {
					string += S_COLOR_RED "F ";
				} else {
					string += S_COLOR_WHITE "S ";
				}
				if ( cvar->getFlags() & SYSVAR_SYSTEM ) {
					string += S_COLOR_WHITE "SYS  ";
				} else if ( cvar->getFlags() & SYSVAR_RENDERER ) {
					string += S_COLOR_WHITE "RNDR ";
				} else if ( cvar->getFlags() & SYSVAR_SOUND ) {
					string += S_COLOR_WHITE "SND  ";
				} else if ( cvar->getFlags() & SYSVAR_GUI ) {
					string += S_COLOR_WHITE "GUI  ";
				} else if ( cvar->getFlags() & SYSVAR_GAME ) {
					string += S_COLOR_WHITE "GAME ";
				} else if ( cvar->getFlags() & SYSVAR_TOOL ) {
					string += S_COLOR_WHITE "TOOL ";
				} else {
					string += S_COLOR_WHITE "     ";
				}
				string += ( cvar->getFlags() & SYSVAR_USERINFO ) ?	"UI "	: "   ";
				string += ( cvar->getFlags() & SYSVAR_SERVERINFO ) ?	"SI "	: "   ";
				string += ( cvar->getFlags() & SYSVAR_STATIC ) ?		"ST "	: "   ";
				string += ( cvar->getFlags() & SYSVAR_CHEAT ) ?		"CH "	: "   ";
				string += ( cvar->getFlags() & SYSVAR_INIT ) ?		"IN "	: "   ";
				string += ( cvar->getFlags() & SYSVAR_ROM ) ?			"RO "	: "   ";
				string += ( cvar->getFlags() & SYSVAR_ARCHIVE ) ?		"AR "	: "   ";
				string += ( cvar->getFlags() & SYSVAR_MODIFIED ) ?	"MO "	: "   ";
				string += "\n";
				//TODO PRINT TO CONSOLE
		//common->Printf( string );
			}
			break;
		}
	}

	//TODO PRINT TO CONSOLE
		//common->Printf( "\n%i cvars listed\n\n", cvarList.getNum() );
	//TODO PRINT TO CONSOLE
		//common->Printf(	"listCvar [search string]          = list cvar values\n"
		//		"listCvar -help [search string]    = list cvar descriptions\n"
		//		"listCvar -type [search string]    = list cvar types\n"
		//		"listCvar -m_iFlags [search string]   = list cvar m_iFlags\n" );
}

/*
============
CGlobalConfiguration::List_f
============
*/
void CGlobalConfiguration::List_f( const CCmdArgs &args ) {
	ListByFlags( args, SYSVAR_ALL );
}

void CGlobalConfiguration::changeFPS(void * arg){
	Debug::debug(Debug::error, __FUNCTION__) << "WILL CHANGE FPS HERE"<< endl;
	CSDLManager::GetInstance()->changeGameFPS();
}
/*
============
CGlobalConfiguration::Restart_f
============
*/
void CGlobalConfiguration::Restart_f( const CCmdArgs &args ) {
	int i, hash;
	CEngineSysVar *cvar;

	for ( i = 0; i < globalSysVarSystem.m_globalSysVars.getNum(); i++ ) {
		cvar = (CEngineSysVar *)globalSysVarSystem.m_globalSysVars[i];

		// don't mess with rom values
		if ( cvar->m_iFlags & ( SYSVAR_ROM | SYSVAR_INIT ) ) {
			continue;
		}

		// throw out any variables the user created
		if ( !( cvar->m_iFlags & SYSVAR_STATIC ) ) {
			hash = globalSysVarSystem.m_SysVarHash.generate_Key( cvar->nameString, false );
			delete cvar;
			globalSysVarSystem.m_globalSysVars.removeIndex( i );
			globalSysVarSystem.m_SysVarHash.removeIndex( hash, i );
			i--;
			continue;
		}

		cvar->Reset();
	}
}

//================END GLOBAL CONFIGURATION


const char *CreateColumn( const char *text, int columnWidth, const char *indent, CMyString &string ) {
	int i, lastLine;

	string.Clear();
	for ( lastLine = i = 0; text[i] != '\0'; i++ ) {
		if ( i - lastLine >= columnWidth || text[i] == '\n' ) {
			while( i > 0 && text[i] > ' ' && text[i] != '/' && text[i] != ',' && text[i] != '\\' ) {
				i--;
			}
			while( lastLine < i ) {
				string.Append( text[lastLine++] );
			}
			string.Append( indent );
			lastLine++;
		}
	}
	while( lastLine < i ) {
		string.Append( text[lastLine++] );
	}
	return string.c_str();
}

/** 
\brief Método que acha uma variável registrada no vetor local da classe pelo nome
\param name: nome da variável
\note Se a variável Local não existir, retorna NULL
**/
CLocalSysVar *CConfiguration::findLocalInternal( const char *name ) const {
	int hash = cvarHash.generate_Key( name, false );
	for ( int i = cvarHash.getFirst( hash ); i != -1; i = cvarHash.getNext( i ) ) {
		if ( ((CLocalSysVar *)cvars[i])->nameString.Icmp( name ) == 0 ) {
			return cvars[i];
		}
	}
	return NULL;
}

/** 
\brief Método que muda o nome e valor interno de uma variável Local d CLocal tipo CSysVar desta Classe
\param name: nome da variável
\param value: valor da variável
\param m_iFlags: flags
\note Se a variável Local não existir, então ela é criada e adicionada à lista (registrada)
**/
void CConfiguration::setLocalInternal( const char *name, const char *value, int m_iFlags ) {
	int hash;
	CLocalSysVar *internal;

	internal = findLocalInternal( name );

	if ( internal ) {
		internal->internalSetString( value );
		internal->m_iFlags |= m_iFlags & ~SYSVAR_STATIC;
		internal->UpdateCheat();
	} else {
		internal = new CLocalSysVar( name, value, m_iFlags, m_iIndex );
		hash = cvarHash.generate_Key( internal->nameString.c_str(), false );
		cvarHash.Add( hash, cvars.append( internal ) );
	}
}



/*
============
CConfiguration::init
============
*/
void CConfiguration::init() {

	modifiedFlags = 0;
	initialized = true;
}

/*
============
CConfiguration::Shutdown
============
*/
void CConfiguration::shutdown() {
	cvars.deleteContents( true );
	cvarHash.freeMem();
	initialized = false;
}

/*
============
CConfiguration::IsInitialized
============
*/
bool CConfiguration::isInitialized() const {
	return initialized;
}

/** 
\brief Método que cria uma cópia da ClocalSysvar e registra-a no vetor
\param cvarToRegister: referÊncia da variável a ser registrada
\note Se a variável já existir, então ela é apenas atualizada
**/
void CConfiguration::Register( CSysVar &cvarToRegister ) {
	int hash;
	CLocalSysVar *internal;

	cvarToRegister.setInternalVar( &cvarToRegister );

	internal = findLocalInternal( cvarToRegister.getName() );
	//Se a variável já foi registrada, apenas faz o update
	//Senão, cria uma nova variável interna e registra 
	if ( internal ) {
		internal->Update( &cvarToRegister );
	} else {
		internal = new CLocalSysVar ( &cvarToRegister );
		internal->setIndex(m_iIndex);
		hash = cvarHash.generate_Key( internal->nameString.c_str(), false );
		cvarHash.Add( hash, cvars.append( internal ) ); //adiciona na lista local
	}

	cvarToRegister.setInternalVar( internal );
}

/** 
\brief Método que acha uma variável CLocalSysVar Registrada anteriormente pelo seu nome
\param name: nome da variável a ser encontrada
\note Se a variável não existir, então retorna NULL
**/
CSysVar *CConfiguration::Find( const char *name ) {
	return findLocalInternal( name );
}

/** 
\brief Método que muda o nome e valor de uma variável tipo String registrada como internal CLocalSysvar
\param name: nome da variável
\param value: valor da variável
\param m_iFlags: flags
\note Se a variável interna não existir, então ela é criada e adicionada à lista (registrada)
**/
void CConfiguration::setCVarLocalString( const char *name, const char *value, int m_iFlags ) {
	setLocalInternal( name, value, m_iFlags );
}

/** 
\brief Método que muda o nome e valor de uma variável tipo Bool registrada como internal CLocalSysvar
\param name: nome da variável
\param value: valor da variável
\param m_iFlags: flags
\note Se a variável interna não existir, então ela é criada e adicionada à lista (registrada)
**/
void CConfiguration::setCVarLocalBool( const char *name, const bool value, int m_iFlags ) {
	setLocalInternal( name, CMyString( value ), m_iFlags );
}

/** 
\brief Método que muda o nome e valor de uma variável tipo Integer registrada como internal CLocalSysvar
\param name: nome da variável
\param value: valor da variável
\param m_iFlags: flags
\note Se a variável interna não existir, então ela é criada e adicionada à lista (registrada)
**/
void CConfiguration::setCVarLocalInteger( const char *name, const int value, int m_iFlags ) {
	setLocalInternal( name, CMyString( value ), m_iFlags );
}

/** 
\brief Método que muda o nome e valor de uma variável tipo Float registrada como internal CLocalSysvar
\param name: nome da variável
\param value: valor da variável
\param m_iFlags: flags
\note Se a variável interna não existir, então ela é criada e adicionada à lista (registrada)
**/
void CConfiguration::setCVarLocalFloat( const char *name, const float value, int m_iFlags ) {
	setLocalInternal( name, CMyString( value ), m_iFlags );
}

/** 
\brief Método que retorna o valor String de uma variável CLocalSysVar desta classe
\param name: nome da variável
\note Só retorna o valor da variável interna, aquela registada
**/
const char *CConfiguration::getCVarLocalString( const char *name ) const {
	CLocalSysVar *internal = (CLocalSysVar *)findLocalInternal( name );
	if ( internal ) {
		return internal->getString();
	}
	return "";
}

/** 
\brief Método que retorna o valor Bool de uma variável CLocalSysVar desta classe
\param name: nome da variável
\note Só retorna o valor da variável interna, aquela registada
**/
bool CConfiguration::getCVarLocalBool( const char *name ) const {
	CLocalSysVar *internal = (CLocalSysVar *)findLocalInternal( name );
	if ( internal ) {
		return internal->getBool();
	}
	return false;
}

/** 
\brief Método que retorna o valor Integer de uma variável CLocalSysVar desta classe
\param name: nome da variável
\note Só retorna o valor da variável interna, aquela registada
**/
int CConfiguration::getCVarLocalInteger( const char *name ) const {
	CLocalSysVar *internal = (CLocalSysVar *)findLocalInternal( name );
	if ( internal ) {
		return internal->getInteger();
	}
	return 0;
}

/** 
\brief Método que retorna o valor Float de uma variável CLocalSysVar desta classe
\param name: nome da variável
\note Só retorna o valor da variável interna, aquela registada
**/
float CConfiguration::getCVarLocalFloat( const char *name ) const {
	CLocalSysVar *internal = (CLocalSysVar *)findLocalInternal( name );
	if ( internal ) {
		return internal->getFloat();
	}
	return 0.0f;
}

/*
============
CConfiguration::Command
============
*/
bool CConfiguration::Command( const CCmdArgs &args ) {
/*	CEngineSysVar *internal;

	internal = (CEngineSysVar *)FindInternal( args.getArgv( 0 ) );

	if ( internal == NULL ) {
		return false;
	}

	if ( args.getArgc() == 1 ) {
		// print the variable
		//TODO PRINT TO CONSOLE
		//common->Printf( "\"%s\" is:\"%s\"" S_COLOR_WHITE " default:\"%s\"\n",
		//			internal->nameString.c_str(), internal->valueString.c_str(), internal->resetString.c_str() );
		if ( CMyString::Length( internal->getDescription() ) > 0 ) {
			//TODO PRINT TO CONSOLE
		//common->Printf( S_COLOR_WHITE "%s\n", internal->getDescription() );
		}
	} else {
		// set the value
		internal->SetGlobal( args.getArgs(), false, false );
	}
	return true;
	*/
	return false;
}

/*
============
CConfiguration::CommandCompletion
============
*/
void CConfiguration::CommandCompletion( void(*callback)( const char *s ) ) {
/*	for( int i = 0; i < cvars.getNum(); i++ ) {
		callback( cvars[i]->getName() );
	}*/
}

/*
============
CConfiguration::ArgCompletion
============
*/
void CConfiguration::ArgCompletion( const char *cmdString, void(*callback)( const char *s ) ) {
/*	CCmdArgs args;

	args.tokenizeString( cmdString, false );

	for( int i = 0; i < cvars.getNum(); i++ ) {
		if ( !cvars[i]->m_tValueCompletion ) {
			continue;
		}
		if ( CMyString::Icmp( args.getArgv( 0 ), cvars[i]->nameString.c_str() ) == 0 ) {
			cvars[i]->m_tValueCompletion( args, callback );
			break;
		}
	}
	*/
}

/*
============
CConfiguration::SetModifiedFlags
============
*/
void CConfiguration::SetModifiedFlags( int m_iFlags ) {
	modifiedFlags |= m_iFlags;
}

/*
============
CConfiguration::GetModifiedFlags
============
*/
int CConfiguration::GetModifiedFlags() const {
	return modifiedFlags;
}

/*
============
CConfiguration::ClearModifiedFlags
============
*/
void CConfiguration::ClearModifiedFlags( int m_iFlags ) {
	modifiedFlags &= ~m_iFlags;
}

/*
============
CConfiguration::ResetFlaggedVariables
============
*/
void CConfiguration::ResetFlaggedVariables( int m_iFlags ) {
	for( int i = 0; i < cvars.getNum(); i++ ) {
		CLocalSysVar *cvar = cvars[i];
		if ( cvar->getFlags() & m_iFlags ) {
			cvar->SetLocal( NULL, true, true );
		}
	}

}

/*
============
CConfiguration::RemoveFlaggedAutoCompletion
============
*/
void CConfiguration::RemoveFlaggedAutoCompletion( int m_iFlags ) {
	for( int i = 0; i < cvars.getNum(); i++ ) {
		CLocalSysVar *cvar = (CLocalSysVar *)cvars[i];
		if ( cvar->getFlags() & m_iFlags ) {
			cvar->m_tValueCompletion = NULL;
		}
	}
}

/*
============
CConfiguration::WriteFlaggedVariables

Appends lines containing "set variable value" for all variables
with the "m_iFlags" flag set to true.
============
*/
/*
void CConfiguration::WriteFlaggedVariables( int m_iFlags, const char *setCmd, idFile *f ) const {
	for( int i = 0; i < cvars.getNum(); i++ ) {
		CEngineSysVar *cvar = cvars[i];
		if ( cvar->getFlags() & m_iFlags ) {
			f->Printf( "%s %s \"%s\"\n", setCmd, cvar->getName(), cvar->getString() );
		}
	}
}
*/
/*
============
CConfiguration::MoveCVarsToDict
============
*/
/*
const idDict* CConfiguration::MoveCVarsToDict( int m_iFlags ) const {
	moveCVarsToDict.Clear();
	for( int i = 0; i < cvars.getNum(); i++ ) {
		CSysVar *cvar = cvars[i];
		if ( cvar->getFlags() & m_iFlags ) {
			moveCVarsToDict.Set( cvar->getName(), cvar->getString() );
		}
	}
	return &moveCVarsToDict;
}
*/
/*
============
CConfiguration::SetCVarsFromDict
============
*/
/*
void CConfiguration::SetCVarsFromDict( const idDict &dict ) {
	CEngineSysVar *internal;

	for( int i = 0; i < dict.GetNumKeyVals(); i++ ) {
		const idKeyValue *kv = dict.GetKeyVal( i );
		internal = FindInternal( kv->GetKey() );
		if ( internal ) {
			internal->InternalServerSetString( kv->GetValue() );
		}
	}
}
*/


} //end SGF
