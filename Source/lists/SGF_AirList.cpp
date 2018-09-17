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



#include "lists/SGF_AirList.h"
#include "SGF_Global.h"
//#include "../util/SGF_Debug.h"

using namespace std;
namespace SGF {
CAirList::~CAirList()
{


}

CAirList::CAirList()
{
	Corrente=Comeco=Final=NULL;
}

void CAirList::Adicionar(AirLinkedList *AirData)
{
	if(Comeco==NULL)
	{
		Comeco=Final=Corrente=AirData;
		AirData->Sucessor=NULL;
		AirData->Antecessor=NULL;

	}
	else
	{
		Final->Sucessor=AirData;
		AirData->Antecessor=Final;
		AirData->Sucessor=NULL;
		Final=AirData;


	}

}

void CAirList::Next()
{
	if(Corrente!=NULL)
	{
		Corrente=Corrente->Sucessor;
	}

}

void CAirList::Prev()
{
	if(Corrente!=NULL)
	{
		Corrente=Corrente->Antecessor;
	}
}

void CAirList::CleanUpTheList()
{

	this->SetStart();

	if(Corrente==NULL)
	  return;

	while(Corrente->Sucessor)
	{

		Comeco=Corrente->Sucessor;
		delete Corrente;
		Comeco->Antecessor=NULL;
		Corrente=Comeco;

	}

}
} //end SGF