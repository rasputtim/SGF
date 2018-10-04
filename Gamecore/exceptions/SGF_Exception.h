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
#ifndef _sgf__exception_12345_h
#define _sgf__exception_12345_h

#include <string>
#include <exception>
#include "../SGF_Config.h"


using namespace std;
namespace SGF {
namespace Exception{

/**
 * \class CBase
 *
 * \ingroup SGF_Exceptions
 * 
 * \brief Classe Base para todas as Excess�es 
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
  */

	/*
	http://www.learncpp.com/cpp-tutorial/154-uncaught-exceptions-catch-all-handlers-and-exception-specifiers/
	*/

class  CBase: public ::std::exception {
public:
    CBase(const string & file, int line);
    CBase(const string & file, int line, const CBase & nested);
    CBase(const CBase & copy);

    /* if we use operator= then we get a bunch of warnings from gcc */
    virtual void set(const CBase & nested);

    virtual void throwSelf() const {
        throw *this;
    }

    const string getTrace() const;

    virtual ~CBase() throw ();
protected:

    virtual const string getReason() const;

    virtual CBase * copy() const;

    string file;
    int line;
    CBase * nested;
};


/**
 * \class Return
 *
 * \ingroup SGF_Exceptions
 * 
 * This exception is thrown when the user wants to return to the previous menu or
 * whatever from some menu or the game by through some abnormal means (like
 * pressing ESC). If there is an "exit" button in the menu then usually you shouldn't
 * throw this exception, just return as normal.
 *
 * \brief Classe Base para todas as Excess�es 
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
  */
class  Return: public CBase {
public:
    Return(const string & file, int line);
    Return(const string & file, int line, const CBase & nested);
    virtual ~Return() throw();
    virtual void throwSelf() const;
protected:
    virtual CBase * copy() const;
};

 

/**
 * \class Quit
 *
 * \ingroup SGF_Exceptions
 * 
 * \brief Classe Base para todas as Excess�es 
 *
 * Tenta Sair de um menu, ou qualquer coisa. 
 *
 * \note Maybe this should derive from MenuException?
 * 
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
  */

class  Quit: public CBase {
public:
    Quit(const string & file, int line);
    Quit(const string & file, int line, const CBase & nested);
    virtual ~Quit() throw();
    virtual void throwSelf() const;
protected:
    virtual CBase * copy() const;
};


/**
 * \class CShutdownException
 *
 * \ingroup SGF_Exceptions
 * 
 * \brief Excess?o Desligamento 
 *
 * This exception is thrown when the user clicks the X button on window
 * or otherwise wants to immediately shutdown the program.
 * If you catch this exception to do something then you must throw it again.
 * 
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

class  CShutdownException: public ::std::exception {
public:
	CShutdownException():exception(){}

	virtual ~CShutdownException() throw(){}
};

}
} //end namespace SGF
#endif
