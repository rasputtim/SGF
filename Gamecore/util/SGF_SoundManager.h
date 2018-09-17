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


#ifndef ___SGF__SOUNDMANAGER___
#define ___SGF__SOUNDMANAGER___

#include "../SGF_Config.h"
#include "SGF_AudioSystem.h"
#include "SGF_Pointer.h"
namespace SGF {

typedef map<int, Util::CReferenceCount<CSound> > SoundList;
typedef vector<string> SoundIndiceList;
typedef map<string, Mix_Music* > MusicList;
typedef SoundList::iterator			SoundMapIterator;
typedef MusicList::iterator			MusicMapIterator;



class CSound;

/**
 * \class CSoundManager
 *
 * \ingroup SGF_Util
 *
 * \brief Gerenciamento de listas de sons
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
class  SGE_API CSoundManager {
public:
    CSoundManager ();
    ~CSoundManager ();
    bool init(map<int, string> &paths);
    void LoadSound( const string a_pcFilename, const char* a_pcSampleName=NULL );
	void UnloadSound( const string a_pcSampleName );
	void play(int index, bool looped=0, int volume=128);
	void play( const string a_pcSampleName, bool looped=0, int volume=100);
	void stop(int index);
    void stop();
    void toggleSounds();
    bool on;
	//	virtual bool init()=0;
bool
            isinit;
private:
	SoundList soundList;
	SoundIndiceList soundIndice;

};


/**
 * \class CMusicManager
 *
 * \ingroup SGF_Util
 *
 * \brief Gerenciamento de listas de musicas
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \note sintaxe:  template <> vector<int> Parameter<int>::stack;
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Dezembro de 2012
 */
class  SGE_API CMusicManager {
public:
    CMusicManager ();
    ~CMusicManager ();
    bool init(map<int, string> &paths);
	void loadMusic( const string a_pcFilename, const char* a_pcMusicName=NULL );
	void UnloadMusic( const string a_pcMusicName );
	void playMusic( const string a_pcMusicName, int looped=-1, int volume=100);
	void fadeMusic( int a_iMilliSec );
	void setMusicVolume( int a_iVolume );
	void stop();
    void toggleSounds();
    bool on;
	bool isinit;
private:
	MusicList musicList;
	int m_iMusicVolume;

};
	} //end SGF
#endif