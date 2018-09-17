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
#include "gui/SGF_Box.h"
#include "util/SGF_FontSystem.h"
#include "resource/all.h"
#include "configuration/SGF_Configuration.h"
#include "graphics/SGF_Color.h"
#include "graphics/SGF_Poligon.h"
//#include "../menu/SGF_MenuV1.h"

using namespace std;
namespace SGF {
class CTTFFont;

using namespace Gui;

CBox::CBox(){
	// Nothing yet
}

CBox::CBox( const CBox & b ){
	this->location = b.location;
    this->position = b.position;
    this->workArea = b.workArea;
}

CBox::~CBox(){
	// Nothing yet
}

CBox &CBox::operator=( const CBox &copy){
    position = copy.position;
    workArea = copy.workArea;
	location = copy.location;
    return *this;
}

// Logic
void CBox::logic(){
	// Nothing yet
}

// Render
void CBox::render( const CBitmap &work){
    Debug::debug(Debug::gui,__FUNCTION__) << "BEGIN =================================" << endl;
	Debug::debug(Debug::gui,__FUNCTION__) << "work: " << &work << endl;
	Debug::debug(Debug::gui,__FUNCTION__) << "=========================================" << endl;
	//Debug::debug(Debug::gui,__FUNCTION__) << "position: " << endl;
	//Debug::debug(Debug::gui,__FUNCTION__) << "position X: " << position.x<< endl;
	//Debug::debug(Debug::gui,__FUNCTION__) << "position Y: " << position.y<< endl;
	///Debug::debug(Debug::gui,__FUNCTION__) << "position W: " << position.width<< endl;
	//Debug::debug(Debug::gui,__FUNCTION__) << "position H: " << position.height<< endl;

	int x1,y1,x2,y2,w,h,radius,bodyAlpha,borderAlpha;
	Colors::ColorDefinition bodyColor,borderColor;
	if(true /*CConfiguration::getMenuVersion() ==2 */) {
		x1 = location.getX();
		y1 = location.getY();
		x2 = location.getX2();
		y2 = location.getY2();
		w = location.getWidth();
		h = location.getHeight();
		radius = (int)location.getRadius();
		bodyColor = colors.body;
		borderColor = colors.border;
		bodyAlpha= colors.body.a;
		borderAlpha = colors.border.a;
	}/* else {
		x1 = position.x;
		y1 = position.y;
		x2 = position.x+position.width;
		y2 = position.y+position.height;
		w = position.width;
		h = position.height;
		radius = position.radius;
		bodyColor =  position.bodyColor;
		borderColor = position.borderColor;
		bodyAlpha=position.bodyAlpha;
		borderAlpha = position.borderAlpha;
	}*/
	Debug::debug(Debug::gui,__FUNCTION__) << "location: " << endl;
	Debug::debug(Debug::gui,__FUNCTION__) << "location X1: " << x1<< endl;
	Debug::debug(Debug::gui,__FUNCTION__) << "location Y1: " << y1 << endl;
	Debug::debug(Debug::gui,__FUNCTION__) << "location X2: " << x2<< endl;
	Debug::debug(Debug::gui,__FUNCTION__) << "location Y2: " << y2<< endl;
	Debug::debug(Debug::gui,__FUNCTION__) << "location W: " << w << endl;
	Debug::debug(Debug::gui,__FUNCTION__) << "location H: " << h << endl;
	Debug::debug(Debug::gui,__FUNCTION__) << "Radius: " << radius << endl;
		Debug::debug(Debug::gui,__FUNCTION__) << "=========================================" << endl;

//	if(CConfiguration::getMenuVersion() ==1 ) {
		//Para Menu V1

    // Check if we are using a rounded box
	//   Colors::ColorDefinition teste;
	//	teste.r=255;
	//teste.b=0;
	//teste.g=0;
	work.setBitmapMode(CBitmap::DRAW_TYPE_TEXTURE);
	work.setDrawBlendMode( CBitmap::MODE_TRANS );

	if(radius>0){
        work.polygon().roundRectFill(radius, x1, y1, x2-1, y2-1, bodyColor,bodyAlpha);
        work.polygon().roundRect(radius, x1, y1, x2-1, y2-1, borderColor );

	} else {
        work.polygon().rectangleFill( x1, y1, x2-1, y2-1, bodyColor ,bodyAlpha);
        work.polygon().rectangle( x1, y1, x2-1, y2-1, borderColor ,borderAlpha);

	}
	work.setDrawBlendMode( CBitmap::MODE_SOLID );



    //CBitmap::transBlender( 0, 0, 0, position.bodyAlpha );  //define a transparência alpha
    //workArea->drawingMode( CBitmap::MODE_TRANS );
    //workArea->drawTrans(position.x,position.y,*work);  //faz um draw na tela com a transparência definida
    //work->drawingMode( CBitmap::MODE_SOLID );
//	}


	Debug::debug(Debug::gui,__FUNCTION__) << "END =================================" << endl;
}
void CBox::msgDialog(const CBitmap & bmp, const string & message, int radius){
	CTTFFont *vFont;
    //Todo verificar se a fonte já foi carregada ou não
	//vFont= new CTTFFont("arial.ttf",30);

			try {
			 vFont= CResource::getTTFont("arial.ttf",30,30);
			}catch (Exception::Filesystem::CNotFound &ex) {
				 ostringstream out;
				 out << "CFont not found " << ex.getTrace()<< endl;
				 Debug::debug(Debug::font,__FUNCTION__) << out.str() << endl;
			}
	//const Font &vFont = Font::getFont(Menu::CMenu_v1::getFont(),Menu::CMenu_v1::getFontWidth(),Menu::CMenu_v1::getFontHeight());
    MESSAGESIZE *tamanho =  vFont->GetTextSize(message.c_str());
	int width =   tamanho->w+10;
	int height = tamanho->h+10;

	const int x = (bmp.getWidth()/2) - ((width)/2);
	const int y = (bmp.getHeight()/2) - ((height)/2);
    CBox dialog;
    dialog.position.width = width;
    dialog.position.height = height;
    dialog.position.radius = radius;
	dialog.position.bodyColor.r=0;
	dialog.position.bodyColor.b=0;
	dialog.position.bodyColor.g=0;
    dialog.position.bodyAlpha = 200;
    dialog.position.borderColor.r=0;
	dialog.position.borderColor.b=0;
	dialog.position.borderColor.g=0;
    dialog.position.borderAlpha = 255;
    CBitmap temp = CBitmap::temporaryBitmap(width,height);
    dialog.render(temp);
	 Colors::ColorDefinition textColor = { 255, 255, 255 };
	// Todo: Verificar porque o cgg não reconhece printf
    vFont->drawText(5,5,textColor,temp,message.c_str());
	//vFont.printf( 5, 5, Colors::makeColor(255,255,255), temp, message, -1);
    temp.Blit(x,y);  // blito default renderer
	temp.BlitToScreen();  // bli to screen

}
void CBox::messageDialog(int centerWidth, int centerHeight, const string & message, int radius){
    /* FIXME Get rid of this */
    #if 0
    const Font &vFont = Font::getFont(OldMenu::Menu::getFont(),OldMenu::Menu::getFontWidth(),OldMenu::Menu::getFontHeight());
    const int width = vFont.textLength(message.c_str()) + 10;
    const int height = vFont.getHeight() + 10;
    const int x = (centerWidth/2) - (width/2);
    const int y = (centerHeight/2) - (height/2);
    Box dialog;
    dialog.location.setDimensions(width, height);
    dialog.location.setRadius(radius);
    dialog.colors.body = Bitmap::makeColor(0,0,0);
    dialog.colors.bodyAlpha = 200;
    dialog.colors.border = Bitmap::makeColor(255,255,255);
    dialog.colors.borderAlpha = 255;
    Bitmap temp = Bitmap::temporaryBitmap(width,height);
    dialog.render(temp);
    vFont.printf( 5, 5, Bitmap::makeColor(255,255,255), temp, message, -1);
    temp.BlitToScreen(x,y);
    #endif
}

// Logic
void CBox::act(const CFont & font){
	// Nothing yet
}

} //end SGF