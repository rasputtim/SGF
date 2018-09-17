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

#ifndef _AIRMANAGER_H_
#define _AIRMANAGER_H_


#include "../lists/all.h"
#include "../lists/liststructs.h"
#include "../sprite/defs.h"
namespace SGF {

class CAirlist;

class  SGE_API CAirManager
{
public:
	CAirManager();
	~CAirManager();

public:
   void AddAction(int nActionNumber);
   void AddElement(int nGroupNumber,int nImageNumber,int x,int y,int nDuringTime,Uint16 nFlip,Uint16 nColorFlag);
   void SetLoop();
   void AddClsnBox(short x,short y,short w,short h,int nNumberOfClsn);
   void CreateClsnBox(int nNumberOfClsn,bool bClsn1,bool bDefault);
   void OpenAir(const char *strFileName);
   ActionElement* GetAction(int nActionNumber);
   void CleanUp();
   void RealocateActionBlock();
   void Reset();


public:
	CAirList m_AirList;
	AirLinkedList *pTempList;
	int nCurrentElement;
	int nCurrentClsn;
	int nCurrentClsn2;
	int nHowManyClsn;
	int nHowManyBlocks;
	Clsn *pTempClsn;
	bool bClsnDefault;
	bool bClsn1or2;



};
} //end SGF
#endif
