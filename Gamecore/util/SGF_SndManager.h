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
#ifndef SNDMANAGER_H_
#define SNDMANAGER_H_
#include "../SGF_Config.h"
#include "SGF_AudioSystem.h"
#include "SGF_MugenSound.h"
#include "../lists/all.h"
#include <stdio.h>
#include <string.h>
#include "../../ExternalLibs/SDL2/include/SDL.h"
namespace SGF {

class CSoundSystem;
//Sound  header
struct SNDHEADER
{
	char signature[11]; //"ElecbyteSnd\0" signature
	short verhi;
	short verlo;
	long nNumberOfSounds;
	long SubHeaderFileOffset; //where first subfile is located.
	char strBlank[488]; //"ElecbyteSnd\0" signature

};
//Sound SubHeader
struct SNDSUBHEADER
{
	long  NextSubHeaderFileOffset; //File offset where next subfile in the linked list is located. 0 if last subfile.
	long  SubFileLenght; //(not including this subfileheader).
	long  nGroupNumber;
	long  SampleNumber; //(WAV format; PCM, 8- or 16-bit, mono or stereo)

};

//WAV File Header to get the File Header
struct WAVHEADER
{
	unsigned long ChunkID;
	unsigned long ChunkSize;
	unsigned long RIFFType;


};
//	typedef map< unsigned int, Util::CReferenceCount<CSound>> SoundGroup;
//	typedef map< unsigned int, SoundGroup > SndSoundMap;

/**
 * \class CSndSoundManager
 *
 * \ingroup SGF_Util
 *
 * \brief Gerenciamento de arquivos SND do MUGEN
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \note sintaxe:  template <> vector<int> Parameter<int>::stack;
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CSndSoundManager :public CSoundSystem
{
//Public Funktions
public:
	CSndSoundManager();
	CSndSoundManager(const string strFileName);
	~CSndSoundManager();
	//void InitSoundManager(char* strFileName);
	void ClearUpSoundManager();
	//SNDDATA GetSndSound(short nGroupNumber,short nImageNumber);
	Util::CReferenceCount<CMugenSound> getSNDSound (short nGroupNumber,short nImageNumber);
	/*CSndList & getSndList() {
	return SndSoundList;
	}*/

	MugenSoundMap & getSoundMap() {
		return sounds;
	}
    void Play(short nGroupNumber,short nSoundNumber);
    void PlayLoop(short nGroupNumber,short nSoundNumber);
	void PlaySomeTimes(short nGroupNumber,short nSoundNumber, int times);
	void TestSoundManager();
	void readSounds(const string & filename, MugenSoundMap & sounds);

   // void SetGameTicks(short nTicks){nGameTicks=nTicks;}
	//void SetID(int n){nID=n;}


//Protected Variables
protected:
	//CSndList SndSoundList;
	short nTotalChunks;
	short nCurrentChunk;

private:
   void	DecodeWavFromSnd(FILE *SndFile,short nSounds);
   MugenSoundMap sounds;

};
} //end SGF
#endif /*SFFSPRITEMANAGER_H_*/
