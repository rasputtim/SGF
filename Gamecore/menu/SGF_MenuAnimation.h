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
#ifndef _menu_animation_h
#define _menu_animation_h

#include <vector>
#include <map>  
#include "../SGF_Config.h"
#include "../exceptions/all.h"
#include "SGF_StructsMenu.h"

using namespace std;
namespace SGF {

class Token;
class CBitmap;

// para armazenar imagens através de números, mais fáceis de acessar e reutilizar

typedef map< int, CBitmap *> imageMap;



class  SGE_API CMenuFrame{
    public:
	    //Copnstrutor da Classe
		//Parâmetros: *token=Ponteiro para os tokens recebidos do arquivo de configuração
        //            images= Mapa de imagens indexadas por números
		CMenuFrame(const Token *token, imageMap &images) throw(CLoadException);
	virtual ~CMenuFrame();
	virtual void act(const double xvel, const double yvel);
	virtual void draw(const int xaxis, const int yaxis, CBitmap *work);
	CBitmap *pBmp;
	MenuPoint offset;
	MenuPoint scrollOffset;
	int time;
	bool horizontalFlip;
	bool verticalFlip;
	int alpha;
};

class  SGE_API CMenuAnimation{
public:
	//Construtor da Classe
	// parâmetros: *token = ponteiro para os tokens recebidos do arquivo de configuração
	CMenuAnimation(const Token *token) throw(CLoadException);
	virtual ~CMenuAnimation();
	// Logic
	virtual void act();
	virtual void draw(CBitmap *work);
	virtual void forwardFrame();
	virtual void backFrame();
	
	inline void reset(){ if (allowReset){ currentFrame = 0; } }
	inline int getID() const { return id; }
	inline int getLocation() const { return location; }
	
private:
	int id;
	int location;
	int ticks;
	unsigned int currentFrame;
	unsigned int loop;
	bool allowReset;
	MenuPoint axis;
	// This allows the frames to scroll in place
	MenuPoint velocity;
	MenuArea window;
	vector<CMenuFrame *> frames;
	imageMap images;
};
} //ens SGF
#endif
