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


#ifndef _S_G_F_AUDIOSYSTEM_H_
#define _S_G_F_AUDIOSYSTEM_H_

#include <string>
#include "../../ExternalLibs/SDL2/include/SDL.h"
#include "../../ExternalLibs/SDL2_mixer-2.0.2/SDL_mixer.h"
#include "../SGF_Config.h"
#include "SGF_Thread.h"
#include "SGF_Debug.h"
#include "SGF_Path.h"

//#include "SGF_FileSystem.h"
//#include "SGF_Util.h"
#ifndef BYTE
typedef unsigned char BYTE;
#endif
using namespace std;
namespace SGF {

/**
 * \class CSoundSystem
 *
 * \ingroup SGF_Util
 * 
 * \brief Classe Base do Gerenciamento do sistema de audio
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class CMusic;
class  SGE_API CSoundSystem
{
public:
    CSoundSystem();
    virtual ~CSoundSystem();

bool InitSystem();
void CleanUp();
void Clear();
protected:
static Mix_Music *LoadMusic(const string & path);
Mix_Chunk *LoadChunk(const string & path);
Mix_Chunk *LoadChunkMem(Uint8 *wave);
static int PlayMusic(Mix_Music *Music);
static int PlayMusicLoop(Mix_Music *Music);
static int PlayMusicSomeTimes(Mix_Music *Music,int times);
static void PauseMusic();
static void ResumeMusic();
static void setVolumeMusic(int volume);
static int  GetVolumeMusic();
static void SetVolumeChunk(Mix_Chunk *sound, int volume);
static int GetVolumeChunk(int channel);

static int  IsMusicPlaying();
static void FadeOutMusic(int miliseconds);
static void FadeInMusic(Mix_Music *Music, int msec);

//sound sdlmixer functions
int PlayChunk(Mix_Chunk *Paser);
void PlayChunk();  //play test sound music.wav
int PlayChunkLoop(Mix_Chunk *Paser, int times = -1);
int PlayChunkSomeTimes(Mix_Chunk *Paser,int times);
void HaltChannel(int channel);
void HaltChannel();
static void stopMusic();
void FilterSound();
void WaitAnyAvailableChannel();
static void MusicDone();
bool IsSoundAviable(short nID,short nGroupNumber,short nSoundNumber);
static void ChannelDone(int channel);

int phaserChannel;
short NumChunkDecoders;
static bool m_bAudioOk;
friend class CMusicManager;
friend class CSoundManager;
//! Thread lock
Util::Thread::LockObject lock;
};

/**
 * \class CMusic
 *
 * \ingroup SGF_Util
 * 
 * \brief Gerenciamento de Musica
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CMusic : public CSoundSystem {
public:
	CMusic(bool on);
	CMusic( const string & path );// throw( LoadException );
	
	~CMusic();
	static bool loadSong( const char & song );
	static bool loadSong( const string & song );
    static void changeSong();

	/* load one of the songs in 'songs' */
	//static void loadSong( const vector< string > & songs );
	static void loadSong(  const vector< Filesystem::CAbsolutePath > & songs );
	
	static void pause();
	static void resume();
	static void play();
	//void play( int volume, int pan );
	static void playLoop();
	static void playSomeTimes(int times);
    static void stop();
	static void soften();
	static void louden();
	static void fadeIn( int msec=2000 );
	static void fadeOut( int msec=2000 );
	static void setVolume( int v );
	static int getVolume();
	static void mute();
	static void unmute();
	void doPlay();

	void Lock() { lockmusic.acquire();}
	void Unlock() { lockmusic.release();}
	static void freeMusic();
protected:
	static int volume;
	Util::Thread::LockObject lockmusic;
	void _setVolume( int vol );
	void _play();
	void _pause();
	void _soften();
	void _louden();
	void _fadeIn(int msec);
	void _fadeOut(int msec);
	void _playLoop();
	void _resume();
	void _playsometimes(int times);
	void _stop();
	void _changesong();

	bool paused;
	bool enabled;
	int fading;
	string currentSong;
	/* Mix_Music actually holds the music information.  */
    static Mix_Music *pMyMusic;

};
/**
 * \class CSound
 *
 * \ingroup SGF_Util
 * 
 * \brief Gerenciamento de sons diversos
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CSound : public CSoundSystem {
public:

	CSound( const string & path );// throw( LoadException );
	CSound( BYTE *chunk );
	CSound( const CSound & copy );
	~CSound();
	void play();
	//void play( int volume, int pan );
	void playLoop(int times=-1);
	void playSomeTimes(int times);
        void stop();
		inline int GetError() {
		return error;
		}
void setVolume(int volume);		
private:
	void releaseInternalSound();
	int *own;
	int channel;
	int error;
	Mix_Chunk * pMySound;
    const string path;
};

} //end SGF
#endif /*AUDIOSYSTEM_H_*/
