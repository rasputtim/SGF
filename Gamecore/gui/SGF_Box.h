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
#ifndef _S_G_F_gui_box_h
#define _S_G_F_gui_box_h

#include <string>
#include "../SGF_Config.h"
#include "SGF_Widget.h"

namespace SGF{
namespace Gui {

/**
 * \class CBox
 *
 * \ingroup SGF_Gui
 * 
 * \brief Caixa
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */

class  SGE_API CBox : public CWidget
{
	public:
		CBox();
		CBox( const CBox & b );
		virtual ~CBox();

		// copy
		CBox &operator=( const CBox &);

		// Logic
		virtual void logic();
		void act(const CFont & font);  //! MENU V2

		// Render
		// Render
		using CWidget::render;
		//virtual void render(const CBitmap *work) {};
		virtual void render(const CBitmap &work);

		// Do a message Dialog centered on the given bitmap
		static void msgDialog(const CBitmap & bmp, const string & message, int radius = 0);
		static void messageDialog(int width, int height, const string & message, int radius = 0);
	protected:
};
} //end namespace Gui
} //end SGF
#endif
