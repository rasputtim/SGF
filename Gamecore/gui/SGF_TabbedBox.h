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
#ifndef _S_G_F_gui_tabbed_box_h
#define _S_G_F_gui_tabbed_box_h

#include <string>
#include <vector>

#include "../SGF_Config.h"
#include "SGF_Widget.h"
#include "../util/SGF_Token.h"
#include "../graphics/all.h"
#include "SGF_ContextBox.h"
namespace SGF{
class Token;

namespace Gui{

class CContextBox;
class CContextItem;
/**
 * \class CTab
 *
 * \ingroup SGF_Gui
 * 
 * \brief Item da caixa de Tabulação
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */

class  SGE_API CTab{
    public:
        CTab();
     virtual ~CTab();

	void addOption(const Util::CReferenceCount<CContextItem> & item);
	virtual void render(const CBitmap & work, const CFont & font);
    virtual void act(const CFont & font);
    virtual void setList(const vector<Util::CReferenceCount<CContextItem> > & list);

    virtual const Gui::CContextBox & getContext() const {
        return context;
    }

    virtual Gui::CContextBox & getContext(){
        return context;
    }

    virtual void close();
    virtual void open();
    virtual void previous(const CFont & font);
    virtual void next(const CFont & font);
    virtual void adjustLeft();
    virtual void adjustRight();
    virtual int getCurrentIndex();

    virtual void setName(const string & name);

        string name;
        bool active;
//protected:
		Gui::CContextBox context;
};

/**
 * \class CTabbedBox
 *
 * \ingroup SGF_Gui
 * 
 * \brief Caixa de Tabulação
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */

class  SGE_API CTabbedBox : public CWidget{
    public:
        CTabbedBox();
        CTabbedBox( const CTabbedBox & );
        virtual ~CTabbedBox();
        
        //! copy
        CTabbedBox &operator=( const CTabbedBox &);
        
        //! Logic
        virtual void act(const CFont &);
        
        //! Render
        using CWidget::render;
        virtual void render(const CBitmap &);
        virtual void render(const CBitmap &, const CFont &);
        
        //! Add tab
        virtual void addTab(const string &, const vector<Util::CReferenceCount<CContextItem> > & list);
        virtual void addTab(CTab * tab);        
        //! Up
        virtual void _up(const CFont &);
        
        //! Down
        virtual void down(const CFont &);
        
        //! Left 
        virtual void left(const CFont &);
        
        //! Right
        virtual void right(const CFont &);
	
	//! Virtual
	virtual void toggleTabSelect();
        
        //! Set current font
        virtual inline void setFont(const Filesystem::CRelativePath & font, int width, int height){
            this->font = font;
            this->fontWidth = width;
            this->fontHeight = height;
        }
        
        //! Get current tab
        virtual inline unsigned int getCurrentTab() const {
            return this->current;
        }
        
        //! Get current index on selected tab
        virtual unsigned int getCurrentIndex() const;
	
	//! Set tab font colors
	virtual void setTabFontColor(Colors::ColorDefinition color);
	
	//! Set selected tab font color
	virtual void setSelectedTabFontColor(Colors::ColorDefinition color);
        
        //! Empty
        virtual inline bool empty() const {
            return this->tabs.empty();
        }
        
        virtual inline bool isInTab() const {
	    return this->inTab;
	}
        
        /*! CTab Colors */
        ColorInfo tabColors;
        
        /*! Selected CTab Colors */
        ColorInfo selectedTabColors;
	
        /*! Selected CTab Colors */
        ColorInfo runningTabColors;
	
    protected:
        void moveTab(int direction);

        vector<Gui::CTab *> tabs;
        
        unsigned int current;
        
        Filesystem::CRelativePath font;
        int fontWidth;
        int fontHeight;
        
        /*! Is in tab */
        bool inTab;
        
        /*! Max Width of tabs */
        int tabWidthMax;
        
        /*! Render tab */
        void renderTabs(const CBitmap &, const CFont &);
	
	/*! CFont Color */
	Colors::ColorDefinition tabFontColor;
	
	/*! Current CTab CFont Color */
	Colors::ColorDefinition currentTabFontColor;
	
	/*! Gradient for selected CFont */
	Effects::Gradient  * activeTabFontColor;
};

}
} //end SGF
#endif
