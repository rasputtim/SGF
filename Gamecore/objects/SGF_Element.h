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

#ifndef _sge_element_h
#define _sge_element_h
#include "../SGF_Config.h"
#include "../graphics/all.h"
#include "../gui/SGF_Coordinate.h"
#include "all.h"
namespace SGF{

class CBitmap;
namespace Gui{

class CAbsolutePoint;

}

/**
 * \class CElement
 *
 * \ingroup SGF_Objects
 * 
 * \brief Classe Basse para de Elementos. Elementos são objetos coadjuvantes, não atacam, nem colidem
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CElement: public CBaseObject  {
    public:
	CElement();
	CElement(CElement & copy);
	virtual ~CElement();
	
	virtual void act()=0;
	virtual void render(int x, int y,const CBitmap &, CBitmap::CFilter * filter=NULL){};
	
	enum Layer {
	    Background,
	    Foreground,
	    Top
	};
	
	virtual inline void setID(int id){
	    this->ID = id;
	}
	
	virtual inline int getID() const {
	    return this->ID;
	}
	
	virtual inline void setLayer(const Layer &layer){
	    this->layer = layer;
	}
	
	virtual inline const Layer & getLayer() const {
	    return this->layer;
	}
	
	virtual inline void setName(const string & name){
	    this->name = name;
	}
	
	virtual inline const string & getName() const {
	    return this->name;
	}
    
    private:
	//! ID of said element
	//! this id is set by the definition file,
	//! that's why we can not use objectId instead
	int ID;
	//! Layer where element will be drawn (background or foreground)
	Layer layer;
	//! Name of element
	string name;
};



/**
 * \class CBackgroundElement
 *
 * \ingroup SGF_Objects
 * 
 * \brief Classe Básica de Elementos de Background
 *
 * \note  só deve ser usadas quando os elementos pertencerem ao background
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CBackgroundElement : public CElement {
    public:
	CBackgroundElement(const string & name);
    CBackgroundElement(const CBackgroundElement &);
	virtual ~CBackgroundElement();
	
	virtual void act()=0;
	virtual void render(int x, int y,const CBitmap &, CBitmap::CFilter * filter = NULL) = 0;
    virtual void reset()=0;
    // Copy operator so we can make an initial copy of are starting values to restore on a reset
    const CBackgroundElement & operator=(const CBackgroundElement &);


	
	
	//! Set the passed element to this elements values, this is called when the next element is linked to this one
        virtual void setLink(CBackgroundElement *element);
		 //! used by the = operator
		inline virtual void setLinkedElement(CBackgroundElement *element) { linkedElement=element;}

        virtual double getCurrentX() const;
        virtual double getCurrentY() const;
	
	virtual inline void setVisible(bool visible){
            this->visible = visible;
        }

        virtual inline bool getVisible(){
            return this->visible && this->enabled;
        }

        virtual inline void setEnabled(bool enabled){
            this->enabled = enabled;
        }

        virtual inline bool getEnabled(){
            return this->enabled;
        }

        virtual inline void setStart(const Gui::CPoint &point){
	    this->start = point;
	}
	
	virtual inline Gui::CPoint getStart() const{
	    return start;
	}
	
	virtual inline void setDelta(double x, double y){
	    this->deltaX = x;
	    this->deltaY = y;
	}
	
	virtual inline double getDeltaX() const{
	    return this->deltaX;
	}
	
	virtual inline double getDeltaY() const{
	    return this->deltaY;
	}
	
	virtual inline void setTile(const Gui::CPoint &point){
	    this->tile = point;
	}
	
	virtual inline Gui::CPoint getTile() const {
	    return this->tile;
	}
	
	virtual inline void setTileSpacing(const Gui::CPoint &point){
	    this->tileSpacing = point;
	}
	
	virtual inline Gui::CPoint getTileSpacing() const {
	    return this->tileSpacing;
	}
	
	virtual inline void setWindow(int x1, int y1, int x2, int y2){
	    this->window = RectArea(x1,y1,x2-x1,y2-y1);
	}
	
	virtual inline const RectArea & getWindow() const {
	    return this->window;
	}
	
	virtual inline void setWindowDelta(double x, double y){
	    this->windowDeltaX = x;
	    this->windowDeltaY = y;
	}
	
	virtual inline double getWindowDeltaX() const{
	    return this->windowDeltaX;
	}
	
	virtual inline double getWindowDeltaY() const{
	    return this->windowDeltaY;
	}
	
	virtual inline void setLinked(bool link){
	    this->isLinked = link;
	}
	
	virtual inline bool getLinked() const {
	    return this->isLinked;
	}	
	virtual inline void setVelocity(double x, double y){
	    this->velocityX = x;
	    this->velocityY = y;
	}
	
	virtual inline double getVelocityX() const{
	    return this->velocityX;
	}
	
	virtual inline double getVelocityY() const{
	    return this->velocityY;
	}
	



    private:

        //! get linked element
        CBackgroundElement *getLinkedElement();
		//! The current element is linked to the previous element in the definion file. It takes on the start,delta,and sin properties of the linked element
		bool isLinked;
		//! Visible
        bool visible;
        //! Enabled
        bool enabled;
        //! The starting coordinate relative to 0,0 which is center of screen
		Gui::CPoint start;
        
		//! Delta values used for movement defaults to 1
		double deltaX;
		double deltaY;
	
	//! Does this element tile 0 = no tile 1 = infinite above 1 = tile that many times
	Gui::CPoint tile;
	//! Tile spacing
	Gui::CPoint tileSpacing;
	//! Window for clipping
	RectArea window;
	//! Window delta
	double windowDeltaX;
	double windowDeltaY;
	
	//! Velocity of this element
	double velocityX;
	double velocityY;
	//! The previous element that this one is linked to it used by setLink
    CBackgroundElement *linkedElement;


};


} //end SGF

#endif
