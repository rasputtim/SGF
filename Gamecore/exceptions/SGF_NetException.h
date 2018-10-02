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
#ifndef _sgf__NET_exception_12345_h
#define _sgf__NET_exception_12345_h
#include "../SGF_Config.h"
#include <string>
#include <exception>
#include "SGF_Exception.h"
namespace SGF {
namespace Exception{


/**
 * \class CNetworkException
 *
 * \ingroup SGF_Exceptions
 * 
 * \brief Excess�o de Rede 
 *
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de fevereiro de 2012
  */


class  CNetworkException: public Exception::CBase{
public:
	CNetworkException( const string message = "" ):
	  CBase("[NETWORK]",0),message(message){}

	inline const string getMessage() const {
		return message;
	}
	
	~CNetworkException() throw();

protected:
	inline void setMessage( const string & m ){
		this->message = m;
	}

private:
	string message;
};


/**
 * \class CNoConnectionsPendingException
 *
 * \ingroup SGF_Exceptions
 * 
 * \brief Excess�o de conex�o pendente de Rede 
 *
 * ocorre quando n�o h� conex�o pendente
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de fevereiro de 2012
  */

class  CNoConnectionsPendingException: public CNetworkException{
public:
	CNoConnectionsPendingException(const string message = ""):
		CNetworkException(message){
	}
};

/**
 * \class CMessageEndException
 *
 * \ingroup SGF_Exceptions
 * 
 * \brief Excess�o de final de mensagem 
 *
 * ocorre quando a conex�o � fechada pelo n� remoto
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de fevereiro de 2012
  */
class  CMessageEndException: public CNetworkException {
public:
    CMessageEndException();
};

/**
 * \class CInvalidPortException
 *
 * \ingroup SGF_Exceptions
 * 
 * \brief Excess�o de porta inv�lida 
 *
 * ocorre quando n�o consegue estabelecer uma conex�o com o servidor
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de fevereiro de 2012
  */
class  CInvalidPortException: public CNetworkException{
public:
	CInvalidPortException( int port, const string message = "" );
};

/**
 * \class CCannotListenException
 *
 * \ingroup SGF_Exceptions
 * 
 * \brief Excess�o de impossibilidade abrir um socket 
 *
 * ocorre quando n�o consegue abrir um socket para ouvir
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de fevereiro de 2012
  */
class  CCannotListenException: public CNetworkException{
public:
	CCannotListenException( const string message = "" ):
		CNetworkException( message ){
	}
};



} // end namespace
} //end SGF
#endif