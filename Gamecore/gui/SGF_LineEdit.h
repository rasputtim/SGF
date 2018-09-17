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



#ifndef _S_G_F_gui_lineedit_h
#define _S_G_F_gui_lineedit_h
#include "../SGF_Config.h"

#include <iostream>
#include <vector>

#include "SGF_Widget.h"
#include "SGF_GuiTimer.h"
#include "../input/SGF_TextInput.h"
namespace SGF{
class CFont;

class keys;

namespace Gui{
typedef std::list<std::string> TStringList;
typedef std::list<int> TIntList;

class CLineEdit: public CWidget{
public:
    //! enumerator housing alignment positions
    enum textAlign {
        T_Left = 0,
        T_Middle,
        T_Right,
        T_Top,
        T_Bottom
    };
	enum status{
		T_quit= -1,
		T_ESC = -2,
		T_NoInput =0,
		T_InputStarted = 1,
		T_InputFinished =2,
	};


    //! enumerator housing alignment positions
    enum inputType {
        inputGeneral = 0,
        inputAllCaps,
        inputNoCaps,
        inputNumerical
    };

    //! Constructor
	//! \param UseTextBox: indica se a caixa de texto que mostra as linhas previamente digitadas deverá aparecer
    CLineEdit(bool UseTextBox=true);

    //! Destructor
    virtual ~CLineEdit();

    //! Set text
    void setText(const string & text);

    //! Get text
    const string getText();

    //! Clear text
    void clearText();

	//! clear the text list
	void clearTextList();

    //! Set text limit (default 0, no limit)
    void setLimit(unsigned int l);
	//! bool replace: if true replace same key
	//! if false do not replace the same key if it find duplicate callback for the same key
    void hookKey(CKeyboard::Key, void (*callback)(void *), void * arg,bool repalace=false);

    //! Set Horizontal Alignment
    void setHorizontalAlign(const textAlign & a);

    //! Set Vertical Alignment
    void setVerticalAlign(const textAlign & a);

    //! Set the type of input default general
    void setInputType(const inputType i = inputGeneral);

    //! Set textColor
	void setTextColor(const Colors::ColorDefinition color);

    //! Set textColor
    void setCursorColor(const  Colors::ColorDefinition color);
	//! Moce Cursor to right
	void cursorToRight();
	//!move cursor to left
	void cursorToLeft();
	//! add string to the list
	void addString( const char* a_poText, int a_iColor );
	
	//!do Page UP on the texlist box
	void scrollUp();
	//!do page down on the textlist box
	void scrollDown();

	//!void delete a char from the string
	void delChar(int position);
    //! Set font
    void setFont(const CFont *f);

    //! Set autoResizeable
    void setAutoResize(bool r);

    //! Set the cursor blink rate in miliseconds (default 500)
    void setCursorBlinkRate(unsigned int msecs);

    //! Update
    void act(const CFont &);

    //! Draw
    using CWidget::render;
	//! Render to The target Bitmap depending on the tgt bitmap mode
    void render(const CBitmap &tgt);
	
	//! render the text list to the tgt bitmap
	void renderTextList(Util::CReferenceCount<CBitmap> );

    //! set Focus ND ENABLE/DISABLE THE TEXTINPUT TO RECEIVE THE TEXT
    void setFocused(bool focus);

    //! check Focus
    bool isFocused();

    bool didChanged( unsigned long long & counter );

	//! return the status
	/** Returns the current state of the line input.
	\retval -1	A quit event was encountered.
	\retval -2	Escape was pressed

	\retval 0 No input
	\retval 1	Input is in progress.
	\retval 2	Input has finished. when the enter is pressed
	*/
	int getStatus();
	void setTitle(string title){ m_sTitle=title;};

	status m_iStatus;
protected:
    //! Current font the label is currently using (uses systemFont by default)
    const CFont *currentSetFont;

    //! Current set text
    // string currentSetText;

    //! Horizontal Alignment (RIGHT, MIDDLE, LEFT)
    textAlign hAlignment;

    //! Additional checker for Horizontal alignment for easy adjustment
    textAlign hAlignMod;

    //! Vertical Alignment (TOP, MIDDLE, BOTTOM)
    textAlign vAlignment;

    //! Input type
    inputType inputTypeValue;

    //! Has changed?
    bool changed_;

    //! Auto resize
    bool autoResizable;

    //! Text horizontal position
    int textX;

    //! Text vertical position
    int textY;

    //! Cursor horizontal position
    int cursorX;

	//! Cursor vertical position
    int cursorY;

    //! Cursor index relative to the string
    unsigned int cursorIndex;

    //! Text color
	Colors::ColorDefinition textColor;

	

    //! Text size Height check in case it changes
    int textSizeH;

    //! Text limit
    unsigned int limit;

    //! Cursor timer
    Gui::CTimer cursorTime;

    //! Cursor blink rate
    unsigned int blinkRate;
    bool blink;

    //! Focused?
    bool focused;

    CTextInput input;

    // keeps track of changes
    unsigned long long changeCounter;
	// oof set to scroll text
	int					m_iScrollOffset;
	//! list of lines
	TStringList			m_asRowTexts;
	//! list of colors for each line of text
	TIntList			m_aiRowColors;
	//! true if will usee the textbox to showprevious digited  lines
	//! default is true
	bool m_bUseTextBox;
	//! a text that will be always there
	string m_sTitle;
    //! If the font size changes
    void fontChange();

    inline void changed(){
        changed_ = true;
        changeCounter += 1;
    }

    inline void stable(){
        changed_ = false;
    }
};

}
} //end SGF
#endif
