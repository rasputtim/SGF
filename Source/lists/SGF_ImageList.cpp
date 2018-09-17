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



#include "SGF_Global.h"
#include "lists/SGF_ImageList.h"
#include "graphics/SGF_Bitmap.h"
#include <SDL.h>

using namespace std;

namespace SGF{


CVideoImageList::CVideoImageList()
{
	Aktuell=NULL;
	Anfang=NULL;
	Ende=NULL;

}

CVideoImageList::~CVideoImageList()
{

}

void CVideoImageList::CleanUp()
{
    ImageList *temp;
    SetStart();
    
    while(Aktuell)
    {
        temp=Aktuell->Next; 
		CBitmap *Temp = (CBitmap *)Aktuell->lpBitmap;
		SDL_FreeSurface(Temp->getBitmap());
        delete Aktuell;
        Aktuell=temp;
    
    }
    

}

void CVideoImageList::SetStart()
{
	Aktuell=Anfang;
}

ImageList *CVideoImageList::GetImage(short nGroupNumber,short nImageNumber)
{
    SetStart();
    
    while(Aktuell)
    {
        if(Aktuell->nGroupNumber==nGroupNumber && Aktuell->nImageNumber == nImageNumber)
                return Aktuell;
        
        Aktuell=Aktuell->Next;
    
    }
    
    

    return NULL;

}

void CVideoImageList::Add(ImageList *p)
{
	if(Anfang==NULL)
	{
		p->Next=NULL;
		p->Prev=NULL;
		Aktuell=Ende=Anfang=p;
	}
	else
	{
		Ende->Next=p;
		p->Prev=Ende;
		p->Next=NULL;
		Ende=p;
		Aktuell=p;

	}

}
} //end SGF