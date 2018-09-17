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

 *  This software was based on Sffextract by Christophe.
 */

#include "lists/SGF_PcxList.h"

using namespace std;
namespace SGF {

short CPCXList::nHowManyObjects=0;

CPCXList::~CPCXList()
{

 //Debug::debug(Debug::resources,__FUNCTION__) << "CPCXList::~CPCXList() - Cleaning UP" <<endl;

}

CPCXList::CPCXList():
Corrente(NULL),
Comeco(NULL),
Final(NULL)
{
	CPCXList::nHowManyObjects=0;
}

void CPCXList::Add(PCXLinkedList *PCXData)
{
	if(Comeco==NULL)
	{
		Comeco=Final=Corrente=PCXData;
		PCXData->Sucessor=NULL;
		PCXData->Antecessor=NULL;

	}
	else
	{
		Final->Sucessor=PCXData;
		PCXData->Antecessor=Final;
		PCXData->Sucessor=NULL;
		Corrente=Final=PCXData;


	}
    nHowManyObjects++;
}

void CPCXList::Delete(PCXLinkedList *PCXData)
{
	if(PCXData==NULL) //nao tem o que apagar
	{

	}
	else if (PCXData->Antecessor==NULL && PCXData->Sucessor!=NULL) //Primeiro Elemento
	{
		PCXData->Sucessor->Antecessor=NULL;
        Comeco=PCXData->Sucessor;
		if (Corrente==PCXData) // corrente = atual
			Corrente=Comeco;
		delete PCXData;
		nHowManyObjects--;
	} else if (PCXData->Sucessor==NULL) //Ultimo Elemento
	{
		PCXData->Antecessor->Sucessor=NULL;
		Final=PCXData->Antecessor;
        if (Corrente==PCXData)
			Corrente=Final;
		delete PCXData;
		nHowManyObjects--;
	}else
	{
		PCXData->Antecessor->Sucessor=PCXData->Sucessor;
		PCXData->Sucessor->Antecessor=PCXData->Antecessor;
        if (Corrente==PCXData)
			Corrente=PCXData->Antecessor;
		delete PCXData;
		nHowManyObjects--;
	}

}

void CPCXList::Next()
{
	if(Corrente!=NULL)
	{
		Corrente=Corrente->Sucessor;
	}

}

void CPCXList::Prev()
{
	if(Corrente!=NULL)
	{
		Corrente=Corrente->Antecessor;
	}
}





void CPCXList::CleanUpTheList()
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

PCXLinkedList* CPCXList::GetImage(int nImageNumber,int nGroupNumber)
{
	this->SetStart();

	if(Corrente==NULL)
	{
	  return NULL;
	}

    while(Corrente->Sucessor!=NULL)
	{
		if(Corrente->pcxdata.ImageNumber==nImageNumber
			&& Corrente->pcxdata.GroupNumber==nGroupNumber)
		{
			return Corrente;

		}else {
		this->Next();
		}
	}


	return NULL;

}

} //end SGF