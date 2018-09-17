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




#include "lists/SGF_SndList.h"
#include "SGF_Global.h"
//#include "util/SGF_Debug.h"

using namespace std;
namespace SGF{

int CSndList::nHowManyObjects=0;

CSndList::~CSndList()
{
 
 //Debug::debug(Debug::resources,__FUNCTION__) << "Cleaning UP" <<endl;

}

CSndList::CSndList()
{
	CSndList::nHowManyObjects=0;
	Corrente=Comeco=Final=NULL;
}

void CSndList::Adicionar(SoundLinkedList *SoundData)
{
	if(Comeco==NULL)
	{
		Comeco=Final=Corrente=SoundData;
		SoundData->Sucessor=NULL;
		SoundData->Antecessor=NULL;

	}
	else
	{
		Final->Sucessor=SoundData;
		SoundData->Antecessor=Final;
		SoundData->Sucessor=NULL;
		Corrente=Final=SoundData;


	}
    nHowManyObjects++;
}

void CSndList::Apaga(SoundLinkedList *SoundData)
{
	if(SoundData==NULL) //nao tem o que apagar
	{
		
	}
	else if (SoundData->Antecessor==NULL && SoundData->Sucessor!=NULL) //Primeiro Elemento
	{
		SoundData->Sucessor->Antecessor=NULL;
        Comeco=SoundData->Sucessor;
		if (Corrente==SoundData) // corrente = atual
			Corrente=Comeco;
		delete SoundData;
		nHowManyObjects--;
	} else if (SoundData->Sucessor==NULL) //Ultimo Elemento
	{
		SoundData->Antecessor->Sucessor=NULL;
		Final=SoundData->Antecessor;
        if (Corrente==SoundData)
			Corrente=Final;
		delete SoundData;
		nHowManyObjects--;
	}else 
	{
		SoundData->Antecessor->Sucessor=SoundData->Sucessor;
		SoundData->Sucessor->Antecessor=SoundData->Antecessor;
        if (Corrente==SoundData)
			Corrente=SoundData->Antecessor;
		delete SoundData;
		nHowManyObjects--;
	}

}

void CSndList::Next()
{
	if(Corrente!=NULL)
	{
		Corrente=Corrente->Sucessor;	
	}

}

void CSndList::Prev()
{
	if(Corrente!=NULL)
	{
		Corrente=Corrente->Antecessor;	
	}
}





void CSndList::CleanUpTheList()
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

SoundLinkedList* CSndList::GetSound(int nSoundNumber,int nGroupNumber)
{
	

	this->SetStart();
 	
	if(Corrente==NULL)
	{
	  return NULL;
	}

    while(Corrente->Sucessor)
	{
		if(Corrente->SoundData.nSampleNumber==nSoundNumber 
		  && Corrente->SoundData.nGroupNumber==nGroupNumber)
		{
			return Corrente;

		}
	this->Next();
	}
	
	
	return NULL;

}

} //end SGF