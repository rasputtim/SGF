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
#ifndef _SGF__mugen_exception_h
#define _SGF__mugen_exception_h

#include "SGF_Exception.h"
#include <string>
#include "../SGF_Config.h"

using namespace std;
namespace SGF {
/**
 * \class CMugenException
 *
 * \ingroup SGF_Exceptions
 * 
 * \brief Excessão de problema no MUGEN 
 *
 * Esta Excessão é lançada quando ocorre algo errado no MUGEN 
 *
 * 
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
  */

class  SGE_API CMugenException: public Exception::CBase {
public:
	CMugenException();
	CMugenException(const string & reason, const string & where = "?", int line = 0);

	virtual ~CMugenException() throw();
    
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
class CReloadMugenException: public CMugenException {
public:
    CReloadMugenException();
    virtual ~CReloadMugenException() throw();
};

/* thrown from the compiler/state-controller when mugen code screws up */
class CMugenRuntimeException: public CMugenException {
protected:
    CMugenRuntimeException();
public:
    CMugenRuntimeException(const string & reason, const string & where, int line);

    virtual void throwSelf() const {
        throw *this;
    }
};

/* For errors that we don't care a whole lot about */
class CMugenNormalRuntimeException: public CMugenRuntimeException {
protected:
    CMugenNormalRuntimeException();
public:
    CMugenNormalRuntimeException(const string & reason, const string & where = "?", int line = 0);

    virtual void throwSelf() const {
        throw *this;
    }
};

/* For errors that are serious */
class CMugenFatalRuntimeException: public CMugenRuntimeException {
protected:
    CMugenFatalRuntimeException();
public:
    CMugenFatalRuntimeException(const string & reason, const string & where, int line);

    virtual void throwSelf() const {
        throw *this;
    }
};
} //end namespace SGF
#endif
