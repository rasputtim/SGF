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

//   VorGaenger = Antecessor
//   Anfang = Começo
//   Aktuell = Corrente, Atual
//   Hinzufuegen = Adicionar
//   Ende = Final
//   NachFolger = Sucessor

#ifndef SNDLIST_H
#define SNDLIST_H
#ifndef byte
typedef unsigned char BYTE;
#endif

#include "../SGF_Config.h"
#include "../util/SGF_AudioSystem.h"

using namespace std;
namespace SGF{


class CSound;
//Sound data struct
struct SNDDATA
{
	SNDDATA():
	nGroupNumber(-1),
	nSampleNumber(-1),
	nLenght(-1),
	bySndData(NULL),
	pCSound(NULL){}
	int nGroupNumber;
	int nSampleNumber;
	int nLenght;
	BYTE *bySndData; //ponteiro para o som em binario
    CSound *pCSound;
};

//Linked list struct
struct SoundLinkedList
{
	SNDDATA SoundData;
	SoundLinkedList *Sucessor;
	SoundLinkedList *Antecessor;


};




class  SGE_API CSndList
{
public:
	CSndList();
	~CSndList();

public:
	SoundLinkedList *Corrente;
	SoundLinkedList *Comeco;
	SoundLinkedList *Final;

public:
	void Adicionar(SoundLinkedList *SoundData);
	void Next();
	void Prev();
	void SetStart(){Corrente=Comeco;};
	SoundLinkedList * GetSound(int nSoundNumber,int nGroupNumber);
	SoundLinkedList *GetSoundData(){return Corrente;}
	void CleanUpTheList();
    void Apaga(SoundLinkedList *SoundData);
	int getNumberofSounds() {
	return nHowManyObjects;
	}
private:   
	static int nHowManyObjects;

};
} //end SGF
#endif /*StateDef */
