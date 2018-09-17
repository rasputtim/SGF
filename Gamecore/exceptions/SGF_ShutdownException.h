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
#ifndef _S_G_F_shutdown_exception_h
#define _S_G_F_shutdown_exception_h

#include <exception>
#include "../SGF_Config.h"

namespace SGF {

/**
 * \class CShutdownException
 *
 * \ingroup SGF_Exceptions
 * 
 * \brief Excessão Desligamento 
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

class  SGE_API CShutdownException: public ::std::exception {
public:
	CShutdownException():exception(){}

	virtual ~CShutdownException() throw(){}
};
} //end SGF
#endif
