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
#ifndef _S_G_F_gui_popup_box_h
#define _S_G_F_gui_popup_box_h

#include <string>
#include <vector>
#include "../SGF_Config.h"
#include "SGF_Widget.h"
#include "SGF_Box.h"

#include "../graphics/all.h"
#include "SGF_Coordinate.h"

namespace SGF{
namespace Gui{
   
/**
 * \class CPopupBox
 *
 * \ingroup SGF_Gui
 * 
 * \brief Caixa de PopUp
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */

class  SGE_API CPopupBox : public CWidget {
    public:
        CPopupBox();
        CPopupBox(const CPopupBox &);
        virtual ~CPopupBox();
        
        //! copy
        CPopupBox &operator=(const CPopupBox &);
        //! Logic
        virtual void act(const CFont &);
        //! Render
        using CWidget::render;
        virtual void render(const CBitmap &);
        //! Open box
	virtual void open();
	//! Close box
	virtual void close();
        //! Is active?
	virtual inline bool isActive(){
	    return (this->fadeState != Closed);
	}
	       virtual inline bool isOpen(){
            return this->fadeState == Open ||
                   this->fadeState == FadeIn;
        }

        //!set fadespeed
        virtual inline void setFadeSpeed(int speed){
            this->fadeSpeed = speed;
        }
        //! Get current box coordinates
        virtual inline const CCoordinate & getArea(){
            return this->board.location;
        }

	virtual inline const Gui::CTransformations & getTransforms(){
	    return this->board.transforms;
	}
    private:
	
	void doFade();
	
	enum FadeState{
	    Closed,
	    FadeIn,
	    Open,
	    FadeOut,
	};
        //! Current fade state
	FadeState fadeState;

        //! Fade speed
	int fadeSpeed;
	
	//! Board
	CBox board;
};

}
} //end SGF
#endif
