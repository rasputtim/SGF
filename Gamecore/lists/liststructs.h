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
#pragma once
#ifndef _LIST_STRUCTS_H_
#define  _LISTSTRUCTS_H_
#include "../../ExternalLibs/SDL2/include/SDL.h"
#include "../SGF_Config.h"

using namespace std;
namespace SGF{

struct ClsnRECT
{
    short x,y;
    short h,w;

};
//Clsn Struct to hold one Clns Rectangle with type
struct Clsn
{
	bool bClsn1;
	ClsnRECT ClsnRect;

};


//Element Strcut to save one Elment of an Action Block
struct Element
{
	int nGroupNumber;
	int nImageNumber;
	int x;
	int y;
	int nDuringTime;
	Uint16 FlipFlags;
	Uint16 ColorFlags;
	Clsn *pClnsData;
	int nNumberOfClsn;
};


//Action Element to hold one Action Block with its Elements
struct ActionElement
{
	int nActionNumber;
	Element* AnimationElement;
	int loopStart;
	int nNumberOfElements;
	int nCurrentImage;
	Uint16 dwStartTime;
	Uint16 dwCompletAnimTime;
	Uint16 dwCurrTime;
	Uint16 dwCurrentImageTime;
	bool bLooped;


};
//Linked list struct for Airmanger
struct AirLinkedList
{
	ActionElement ElementData;
	AirLinkedList *Sucessor;
	AirLinkedList *Antecessor;

};

struct ImageList
{
    ImageList *Next;
    ImageList *Prev;
    short nGroupNumber;
    short nImageNumber;
    void *lpBitmap; //pointer to CBitmap

};


} //end SGF

#endif