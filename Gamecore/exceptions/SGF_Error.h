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

#ifndef _sgf_error_12345_h
#define _sgf_error_12345_h

#include "../SGF_Config.h"
#include "SGF_Exception.h"
#include <string>

using namespace std;
namespace SGF {
/**
 * \class CGeneralError
 *
 * \ingroup SGF_Exceptions
 * 
 * \brief Excess�o de Erro Gen�rico 
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
  */

class  SGE_API CGeneralError: public Exception::CBase {
public:
	CGeneralError();
	CGeneralError(const string & reason, const string & where = "?", int line = 0);

	virtual ~CGeneralError() throw();
    
        virtual CBase * copy() const;

        const string getFullReason() const;

        virtual void throwSelf() const {
            throw *this;
        }

	inline const string getReason() const{
            return reason;
	}

protected:
        string reason;
        string where;
        int line;
};
} //end namespace SGF
#endif