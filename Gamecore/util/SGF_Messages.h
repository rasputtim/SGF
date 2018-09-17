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
#ifndef _S_G_F_messages_h
#define _S_G_F_messages_h
#include "../SGF_Config.h"
#include "../graphics/all.h"
#include "../util/SGF_FontSystem.h"
namespace SGF {

class CBitmap;
class CFont;
namespace Messages {

void registerInfo(MessageQueue *);
void unregisterInfo(MessageQueue *);
void info(const string & str);


/**
 * \class CMessages
 *
 * \ingroup SGF_Util
 * 
 * \brief Mensagens a ser enviadas pela Rede
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 12 de fevereiro de 2012
 */
class  SGE_API CMessages{
public:
	CMessages(int width, int height, int opaque = 128);

	virtual inline int getHeight() const {
		return height;
	}
	
	virtual inline int getWidth() const {
		return width;
	}

	virtual void addMessage( const string & s );

	virtual void draw( int x, int y, const CBitmap & work, const CFont & font );

	virtual ~CMessages();

protected:
	int width;
	int height;
    int opaque;
    Colors::ColorDefinition borderColor;
	vector< string > messages;
};

}
} //end SGF
#endif