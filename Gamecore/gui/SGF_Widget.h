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
#ifndef _gui_widget_h
#define _gui_widget_h
#include "../SGF_Config.h"
#include "SGF_Rectarea.h"
#include "SGF_Coordinate.h"
#include "../graphics/all.h"
#include "../exceptions/all.h"
#include "../SGF_Global.h"
#include "../util/SGF_Token.h"
#include "../util/SGF_Pointer.h"
#include "../../ExternalLibs/SDL2/include/SDL.h"

namespace SGF{
class CBitmap;
class CFont;
class CCoordinate;
class Token;

namespace Gui {
struct ColorInfo{
    ColorInfo():
	body(Colors::Transparent),
    border(Colors::Transparent)
        {
        }

    Colors::ColorDefinition body;
    Colors::ColorDefinition border;

};

/*! Trasformations for widgets
 *  Eventually this could be expanded and used as something to perform changes on widgets but for now it remains to be just a place holder
 *  ************************
 *  radius - rounded corners
 */
class CTransformations{
public:
    CTransformations();
    CTransformations(const CTransformations &);
    virtual ~CTransformations();

    CTransformations & operator=(const CTransformations &);

    virtual inline void setRadius(double radius){
	this->radius = radius;
    }
    virtual inline double getRadius() const{
	return this->radius;
    }
private:
    double radius;
};



/**
 * \class CWidget
 *
 * \ingroup SGF_Gui
 *
 * \brief Classe Base para Classes de coisas de Gui
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */

class  SGE_API CWidget
{
	public:
		CWidget();
		CWidget( const CWidget & w );
		virtual ~CWidget();

		// copy
		CWidget &operator=( const CWidget &);

		// position info
		RectArea position;  // To use with menu V1
		 //! New position data
		CCoordinate location; // to use with Menu V2

		void setCoordinates(const Token * token) throw(CLoadException);
        void setColors(const Token * token);
        void setTransforms(const Token * token);


        //! Colors
        ColorInfo colors;

		 //! Transformations
         CTransformations transforms;

        // Logic
        virtual void act(const CFont &)=0;

        // Render
        virtual void render(const CBitmap &) = 0;
        /* default behavior is just to call render() */
        virtual void render(const CBitmap &, const CFont &);

	protected:
		//void arc( CBitmap *work, int x, int y, double startAngle, int radius, Uint32 color );
		//void roundRect( CBitmap *work, int radius, int x1, int y1, int x2, int y2, Uint32 color );
		//void roundRectFill( CBitmap *work, int radius, int x1, int y1, int x2, int y2, Uint32 color );
		//void arc( CBitmap *work, int x, int y, double startAngle, int radius,  Colors::ColorDefinition color );
		void roundRect( CBitmap *work, int radius, int x1, int y1, int x2, int y2,  Colors::ColorDefinition color );
		void roundRectFill( CBitmap *work, int radius, int x1, int y1, int x2, int y2,  Colors::ColorDefinition color );

		void checkWorkArea();
		Util::CReferenceCount<CBitmap> checkWorkArea(const CBitmap & parent);

		CBitmap *workArea;
};
} //end namespace Gui
} //end SGF
#endif
