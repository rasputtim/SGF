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
#ifndef gui_fadetool_345543345543_h
#define gui_fadetool_345543345543_h
#include "../SGF_Config.h"
#include "../util/SGF_Token.h"
#include "../graphics/SGF_Color.h"
#include "../exceptions/all.h"

namespace SGF{
class CBitmap;
class Token;

namespace Gui{
/**
 * \class CFadeTool
 *
 * \ingroup SGF_Gui
 * 
 * \brief Utilitário de FadeIn
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */
class  SGE_API CFadeTool{
public:
	CFadeTool();
	virtual ~CFadeTool();

        enum State{
            FadeIn,
            FadeOut,
            NoFade,
            EndFade,
        };
        
        //! Read info from Token
        void parseDefaults(const Token *) throw (CLoadException);
	
	// Fade state
	void setState(const State &);
	
	// update
	void act();
	
	// Fade to whatever state it is at
	virtual void draw(const CBitmap &);
	
	inline const State & getState() const { 
            return currentState; 
        }
	inline void setFadeInTime(const int time){ 
            fadeInTime = time; 
        }
	inline void setFadeOutTime(const int time){ 
            fadeOutTime = time; 
        }
	inline int getFadeInTime() const { 
            return fadeInTime; 
        }
	inline int getFadeOutTime() const { 
            return fadeOutTime; 
        }
	inline void setFadeInColor( Colors::ColorDefinition c ){ 
            fadeInColor = c; 
        }
	inline Colors::ColorDefinition getFadeInColor() const { 
            return fadeInColor; 
        }
	inline void setFadeOutColor( Colors::ColorDefinition c ){ 
            fadeInColor = c; 
        }
	inline Colors::ColorDefinition getFadeOutColor() const { 
            return fadeInColor; 
        }
private:
	
	State currentState;
	State lastState;
	int fadeTime;
	int fadeInTime;
	int fadeOutTime;
	Colors::ColorDefinition fadeInColor;
	Colors::ColorDefinition fadeOutColor;
	
};

}
} //end SGF
#endif
