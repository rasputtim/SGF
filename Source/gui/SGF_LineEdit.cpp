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

#include "graphics/all.h"
#include "util/SGF_FontSystem.h"
#include "gui/SGF_LineEdit.h"
#include "util/SGF_Debug.h"
#include <iostream>
using namespace std;
namespace SGF{

using namespace Gui;

void handleRight(void *arg ) {
	if (arg==NULL) return;
	CLineEdit * este= (CLineEdit*) arg;
	este->cursorToRight();
	
}
void handleLeft(void *arg ) {
	if (arg==NULL) return;
	CLineEdit * este= (CLineEdit*) arg;
	este->cursorToLeft();
	
}

void handlePgUp(void *arg ) {
	if (arg==NULL) return;
	CLineEdit * este= (CLineEdit*) arg;
	este->scrollUp();
	
}

void handlePgDn(void *arg ) {
	if (arg==NULL) return;
	CLineEdit * este= (CLineEdit*) arg;
	este->scrollDown();
	
}

void handleEnter (void *arg){
	if (arg==NULL) return;
	CLineEdit * este = (CLineEdit *) arg;
	este->m_iStatus=CLineEdit::T_InputFinished;
//	este->addString(este->getText().c_str(),Colors::makeColor(255,44,67));
//	este->clearText();
}

CLineEdit::CLineEdit(bool useTextBox) : 
m_iStatus(T_NoInput),
currentSetFont(0), 
hAlignment(T_Middle),
hAlignMod(T_Middle),
vAlignment(T_Middle),
inputTypeValue(inputGeneral),
changed_(0),
autoResizable(0),
textX(0),
textY(0),
cursorX(0),
cursorY(0),
cursorIndex(0),
textColor(Colors::Transparent),
textSizeH(0),
limit(0),
blinkRate(500),
blink(false),
focused(false),
changeCounter(0),
m_iScrollOffset(0),
m_bUseTextBox(useTextBox){
	m_sTitle.clear();
    cursorTime.reset();
	hookKey(CKeyboard::Key_ENTER,handleEnter,(void*) this);
	hookKey(CKeyboard::Key_RIGHT,handleRight,(void*) this);
	hookKey(CKeyboard::Key_LEFT,handleLeft,(void*) this);
	hookKey(CKeyboard::Key_PGUP,handlePgUp,(void*) this);
	hookKey(CKeyboard::Key_PGDN,handlePgDn,(void*) this);
	hookKey(CKeyboard::Key_9_PAD,handlePgUp,(void*) this);
	hookKey(CKeyboard::Key_3_PAD,handlePgDn,(void*) this);
}

CLineEdit::~CLineEdit(){
    if (focused){
        input.disable();
    }
}
    
void CLineEdit::hookKey(CKeyboard::Key key, void (*callback)(void *), void * arg,bool replace){
    input.addBlockingHandle(key, callback, arg);
}
	
bool CLineEdit::didChanged(unsigned long long & counter){
    bool did = counter < changeCounter;
    counter = changeCounter;
    return did;
}

// If the font size changes
void CLineEdit::fontChange(){
    changed();
}

// Update
void CLineEdit::act(const CFont & font){
    if (cursorTime.msecs() >= blinkRate){
        cursorTime.reset();
        blink = !blink;
        changed();
    }
    /*
    if ((blinkRate * 2) <= cursorTime.msecs()){
        cursorTime.reset();
        changed();
    }
    */
	
    if (input.doInput()){
        changed();
        cursorIndex = input.getText().size();
		m_iStatus=T_InputStarted;
    }
	
    if (changed_){
        textSizeH = currentSetFont->getHeight();
        if (autoResizable) {
            location.setDimensions(textSizeH+2, currentSetFont->getTextLength(input.getText().c_str()) + 4);
        } else {
            if (hAlignMod==T_Left){
                if (currentSetFont->getTextLength(input.getText().c_str())>location.getWidth()){
                    hAlignment = T_Right;
                } else {
                    hAlignment = T_Left;
                }
            }
        }

        switch (hAlignment) {
            case T_Left:
                textX = 2;
                cursorX = textX + currentSetFont->getTextLength(input.getText().substr(0,cursorIndex).c_str()) + 1;
                break;
            case T_Middle:
                textX = (location.getWidth()/2) - (currentSetFont->getTextLength(input.getText().c_str())/2);
                cursorX = (textX) + currentSetFont->getTextLength(input.getText().substr(0,cursorIndex).c_str()) + 1;
                break;
            case T_Right:
                textX = location.getWidth() - currentSetFont->getTextLength(input.getText().c_str());//(position.width - 1)-2;
                cursorX = location.getWidth() - currentSetFont->getTextLength(input.getText().substr(0, input.getText().length()-cursorIndex).c_str());
                break;
            case T_Bottom:
            case T_Top:
                break;
        }

        switch (vAlignment) {
            case T_Top:
                textY = 1;
                cursorY = 1;
                break;
            case T_Middle:
                textY = cursorY = (location.getHeight() - textSizeH-(5))/2;
                break;
            case T_Bottom:
                textY = (location.getHeight() - 1) - textSizeH - 1;
                cursorY = textY - textSizeH;
                break;
            case T_Right:
            case T_Left:
                break;
        }

        //textY++;
        //textX++;
		
        stable();
    }
}


void CLineEdit::addString( const char* a_poText, int a_iColor ){
	while ( a_poText && *a_poText )
	{
		// 1. FORMAT THE TEXT SO IT FITS US NICELY
		
		MESSAGESIZE oRect;
		int i, j;
		
		for ( i=0; a_poText[i]; ++i )
		{
			oRect = currentSetFont->getTextSize( a_poText, i );
			if ( oRect.w > location.getWidth() )
			{
				if ( i>0 )--i;
				break;
			}
		}
		
		// i now points to the character AFTER the last good character.
		//if ( a_poText[i] && i>1 ) --i;
		
		// Trace back to the first space BEFORE i
		if ( a_poText[i] )
		{
			for ( j = i; j>0; --j )
			{
				if ( isspace( a_poText[j] ) )
				{
					break;
				}
			}
			if ( j>0 )
			{
				i = j;
			}
		}
		
		// 2. ADD IT.
		
		m_asRowTexts.push_front( std::string(a_poText,i) );
		m_aiRowColors.push_front( a_iColor );
		if ( m_iScrollOffset > 0 )
		{
			++m_iScrollOffset;
		}
		
		a_poText += i;
		Debug::debug(Debug::font,__FUNCTION__)<< "Added "<< m_asRowTexts.front().c_str()<<" number of texts is:  "<< m_asRowTexts.size() <<endl;
	}
}
	
void CLineEdit::scrollUp(){
	if ( m_iScrollOffset < (int) m_asRowTexts.size() - location.getHeight() / currentSetFont->getHeight() )
	{
		++m_iScrollOffset;
	//	renderTextList();
	}
}
void CLineEdit::scrollDown(){
	if ( m_iScrollOffset > 0 )
	{
		--m_iScrollOffset;
	//	RenderList();
	}
}
void CLineEdit::cursorToLeft(){

	if (cursorIndex>=0)
	cursorIndex--;

}
void CLineEdit::cursorToRight(){
	if (cursorIndex<= input.getText().size())
	cursorIndex++;

}
// Draw
void CLineEdit::render(const CBitmap & work){
	//cria um novo bitmap do tamanho do location com o fundo identico ao bitmap work(se existir),
	//caso contrário cria um bitmap transparente
    Util::CReferenceCount<CBitmap> workArea = checkWorkArea(work);
	workArea->useSurface();
    /* Check if we are using a rounded box */
    if (transforms.getRadius() > 0){
        workArea->translucent(0, 0, 0, colors.body.a).roundRectFill((int)transforms.getRadius(), 0, 0, location.getWidth()-1, location.getHeight()-1, colors.body );
        workArea->translucent(0, 0, 0, colors.border.a).roundRect((int)transforms.getRadius(), 0, 0, location.getWidth()-1, location.getHeight()-1, colors.border);
    } else {
        workArea->translucent(0, 0, 0, colors.body.a).rectangleFill(0, 0, location.getWidth()-1, location.getHeight()-1, colors.body);
        workArea->translucent(0, 0, 0, colors.border.a).rectangle(0, 0, location.getWidth()-1, location.getHeight()-1, colors.border);
    }

    if (currentSetFont){
		int x=0,y=0;
		if (workArea->getBitmapMode()==SGF::CBitmap::DRAW_TYPE_TEXTURE) {
		x = location.getX()+textX+10; //this is relative to the screen, not workarea.
		y = location.getY()+textY + ((CTTFFont *)currentSetFont)->getFontAscent();
		}else {
		x = textX+10; //this is relative to the screen, not workarea.
		y = textY + ((CTTFFont *)currentSetFont)->getFontAscent();
		
		}
		currentSetFont->drawText(x, y, textColor, *workArea, input.getText().c_str(), 0);
    
	}

    if (focused){
        if (blink){
            workArea->polygon().line(cursorX, cursorY, cursorX, cursorY+textSizeH-5, textColor);
        }
    }

	if(m_bUseTextBox) renderTextList(workArea);

	if (work.getBitmapMode()==SGF::CBitmap::DRAW_TYPE_TEXTURE){
		workArea->useTexture();
		workArea->CreateTextureFromBitmap();
		workArea->SetBlendMode(CBitmap::MODE_TRANS);
		workArea->Blit(location.getX(), location.getY());
		
	}else{
		workArea->BlitSurface(location.getX(), location.getY(),work);
	}
}

void CLineEdit::renderTextList(Util::CReferenceCount<CBitmap> workArea){
	if(!m_bUseTextBox) return;
	
	workArea->useSurface();
    /* Check if we are using a rounded box */
    

	TStringList::const_iterator itString = m_asRowTexts.begin();
	TIntList::const_iterator itColors = m_aiRowColors.begin();

	for ( int i=0; i<m_iScrollOffset; ++i )
	{
		++itString;
		++itColors;
	}

	workArea->useSurface();

	((CTTFFont *)currentSetFont)->AAenable();

	//the first line is for entering new text
	//iRows determina quantas linhas a caixa de texto tem
	int iRows = workArea->getHeight() /  ((CTTFFont *)currentSetFont)->getHeight();
	//calcula qual a última linha
	int yPos = (iRows-2) * ((CTTFFont *)currentSetFont)->getHeight();
	int TitlePos = (iRows-1) * ((CTTFFont *)currentSetFont)->getHeight();
	for ( ; yPos >= 2*currentSetFont->getHeight(); yPos -= ((CTTFFont *)currentSetFont)->getHeight() )
	{
		if ( itColors == m_aiRowColors.end() )
		{
			break;
		}
		// Print the current text
		//((CTTFFont *)currentSetFont)->textout( workArea, itString->c_str(), x, yPos + ((CTTFFont *)currentSetFont)->getFontAscent(), *itColors, C_BLACK, 255 );
		int x=0,y=0;
		if (workArea->getBitmapMode()==SGF::CBitmap::DRAW_TYPE_TEXTURE) {
		x = location.getX()+10; //this is relative to the screen, not workarea.
		y = location.getY()+textY+yPos + ((CTTFFont *)currentSetFont)->getFontAscent();
		}else {
			x=10;
			y=yPos;
		}
		currentSetFont->drawText(x,y, *itColors, *workArea, itString->c_str(), 0);
		
		++itString;
		++itColors;
	}
	currentSetFont->drawText(10,TitlePos, Colors::White, *workArea, m_sTitle.c_str(), 0);	
	((CTTFFont *)currentSetFont)->AAdisable();
}

// Set text
void CLineEdit::setText(const string & text){
    input.setText(text);
    if (limit!=0) {
        if (input.getText().length() > limit) {
            while (input.getText().length() > limit){
                // currentSetText.erase(currentSetText.begin()+currentSetText.length()-1);
            }
        }
    }
    cursorIndex = input.getText().length();
    changed();
}


//! Get text
const string CLineEdit::getText(){
    return input.getText();
}
		
//! Clear entered text
void CLineEdit::clearText(){
    input.clearInput();
    cursorIndex=0;
    changed();
}


void CLineEdit::clearTextList()
{
	m_aiRowColors.clear();
	m_asRowTexts.clear();
	m_iScrollOffset = 0;
}

//! Set text limit
void CLineEdit::setLimit(unsigned int l){
    limit = l;
    if (limit!=0){
        if (input.getText().length()>limit){
            while (input.getText().length()>limit){
                 //currentSetText.erase(currentSetText.begin()+currentSetText.length()-1);
            }
        }
    }
    cursorIndex = input.getText().length();
    changed();
}
		
// Set Horizontal Alignment
void CLineEdit::setHorizontalAlign(const textAlign & a){
    hAlignment = hAlignMod = a;
    changed();
}
		
// Set Vertical Alignment
void CLineEdit::setVerticalAlign(const textAlign & a){
    vAlignment = a;
    changed();
}

//! Set the type of input default general
void CLineEdit::setInputType(const inputType i){
    inputTypeValue = i;
}
		
// Set textColor
void CLineEdit::setTextColor(const Colors::ColorDefinition color){
    textColor = color;
}

//! Set textColor
void CLineEdit::setCursorColor(const Colors::ColorDefinition color){
    textColor = color;
}

// Set font
void CLineEdit::setFont(const CFont *f){
    currentSetFont = f;
    if (currentSetFont) changed();
}

// Set autoResizeable
void CLineEdit::setAutoResize(bool r){
    autoResizable = r;
}

// Set the cursor blink rate in miliseconds (default 500)
void CLineEdit::setCursorBlinkRate(unsigned int msecs){
    blinkRate = msecs;
}

//! set Focus
void CLineEdit::setFocused(bool focus){
    focused = focus;
    if (focus){
        input.enable();
    } else {
        input.disable();
    }
}

//! check Focus
bool CLineEdit::isFocused(){
    return focused;
}
int CLineEdit::getStatus(){
return m_iStatus;
}
} //ens SGF