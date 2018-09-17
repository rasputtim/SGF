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

#ifndef _S_G_F_network_client_h
#define _S_G_F_network_client_h

#include "../SGF_Config.h"

#include <string>

using namespace std;
namespace SGF{

namespace Network{
	/** \brief inicializa o cliente de conexões de rede
	*/
	void SGE_API networkClient();
	/** \brief roda o cliente de conexões de rede
	* \param name: nome do cliente
	* \param host: host
	* \param port: porta
	*/
	void runClient(const string & name, const string & host, const string & port);

//s extern const char * propertyLastClientName;
//s extern const char * propertyLastClientHost;
//s extern const char * propertyLastClientPort;

}
} // end SGF
#endif
