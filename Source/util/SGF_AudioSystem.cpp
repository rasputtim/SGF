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



#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <vector>
#include "util/SGF_AudioSystem.h"
#include "util/SGF_Util.h"

namespace SGF {

//inicializando variáveis staticas
Mix_Music * CMusic::pMyMusic=NULL; /* Mix_Music actually holds the music information.  */
//Util::CReferenceCount<Mix_Music> CMusic::MyMusic=NULL;
static CMusic * instance = NULL;
int CMusic::volume = 10;
bool CSoundSystem::m_bAudioOk=false;
//static double CMusic::volume = 1.0;
// static bool muted = false;

//static bool CMusic::alive = true;
/* remove an element from a vector at index 'pos' and return it */
template< class Tx_ >
static Tx_ removeVectorElement( vector< Tx_ > & toRemove, int pos ){
    int count = 0;
    typename vector< Tx_ >::iterator it;
    for ( it = toRemove.begin(); it != toRemove.end() && count < pos; count++, it++ );

    if ( it == toRemove.end() ){
        /* this isnt right, but whatever */
        return toRemove.front();
    }

    const Tx_ & removed = toRemove[ pos ];
    toRemove.erase( it );
    return removed;

}


//Konstructor
CSoundSystem::CSoundSystem():
phaserChannel(-1)
{

  NumChunkDecoders=Mix_GetNumChunkDecoders();
/* Every sound that gets played is assigned to a channel.  Note that
   this is different from the number of channels you request when you
   open the audio device; a channel in SDL_mixer holds information
   about a sound sample that is playing, while the number of channels
   you request when opening the device is dependant on what sort of
   sound you want (1 channel = mono, 2 = stereo, etc) */



}


//Destructor
CSoundSystem::~CSoundSystem()
{
    Debug::debug(Debug::resources,__FUNCTION__) << "CSoundSystem::~CSoundSystem() Cleaning Up"<<endl;

    CleanUp();

}

Mix_Music *CSoundSystem::LoadMusic(const string & path)
{

	Mix_Music *lpTempMusic;
	/* Actually loads up the music */
	lpTempMusic = Mix_LoadMUS(path.c_str());
	return lpTempMusic;
}
void CSoundSystem::PauseMusic() {
::Mix_PauseMusic();
}
void CSoundSystem::ResumeMusic() {
	if(Mix_PausedMusic()) {
	::Mix_ResumeMusic();
	}
}

int CSoundSystem::IsMusicPlaying() {
	//Returns: Zero if the music is not playing, or 1 if it is playing.


	return Mix_PlayingMusic() ;
}

Mix_Chunk *CSoundSystem::LoadChunk(const string & path)
{

	Mix_Chunk *lpTempChunk;
/* We're going to pre-load the sound effects that we need right here
   */
  lpTempChunk = Mix_LoadWAV(path.c_str());
  if(lpTempChunk == NULL) {
	Debug::debug(Debug::resources,__FUNCTION__) << "CSoundSystem::LoadChunk - Unable to load WAV file:"<< Mix_GetError()<<endl;

   }
  return lpTempChunk;

}
Mix_Chunk *CSoundSystem::LoadChunkMem(Uint8 *wave)
{
	// I assume you have the wave loaded raw,
                // or compiled in the program...
Mix_Chunk *wave_chunk;
if(!(wave_chunk=Mix_QuickLoad_WAV(wave))) {
    Debug::debug(Debug::resources,__FUNCTION__) << "Mix_QuickLoad_WAV: "<< Mix_GetError()<<endl;
    // handle error
}else
return wave_chunk;

}

int CSoundSystem::PlayMusic(Mix_Music *Music)
{


	/* This begins playing the music - the first argument is a
	   pointer to Mix_Music structure, and the second is how many
	   times you want it to loop (use -1 for infinite, and 0 to
	   have it just play once) */
	return Mix_PlayMusic(Music, 0);

}

int CSoundSystem::PlayMusicLoop(Mix_Music *Music)
{


	/* This begins playing the music - the first argument is a
	   pointer to Mix_Music structure, and the second is how many
	   times you want it to loop (use -1 for infinite, and 0 to
	   have it just play once) */
	return Mix_PlayMusic(Music, -1);

}
int CSoundSystem::PlayMusicSomeTimes(Mix_Music *Music, int times)
{


	/* This begins playing the music - the first argument is a
	   pointer to Mix_Music structure, and the second is how many
	   times you want it to loop (use -1 for infinite, and 0 to
	   have it just play once) */
	return Mix_PlayMusic(Music, times);

}

void CSoundSystem::setVolumeMusic(int volume){
	//max volume=128
	::Mix_VolumeMusic(volume * 128 / 100);
}
int CSoundSystem::GetVolumeMusic() {
	return  ::Mix_VolumeMusic(-1);
}

int  CSoundSystem::GetVolumeChunk(int channel){
	return ::Mix_Volume(channel,-1);
}
void CSoundSystem::SetVolumeChunk(Mix_Chunk *Mysound, int volume){
	::Mix_VolumeChunk(Mysound,volume);
}

void CSoundSystem::PlayChunk()
{
if(phaserChannel < 0) {

			PlayChunk(LoadChunk("data\\menu\\sounds\\menu-ok.wav"));

		} else {
	        HaltChannel();
            phaserChannel = -1;
		}
}
int CSoundSystem::PlayChunk(Mix_Chunk *Music)
{
	   Util::Thread::ScopedLock scoped(lock);
/* Mix_PlayChannel takes, as its arguments, the channel that
	   the given sound should be played on, the sound itself, and
	   the number of times it should be looped.  If you don't care
	   what channel the sound plays on, just pass in -1.  Looping
	   works like Mix_PlayMusic. This function returns the channel
	   that the sound was assigned to, which you'll need later. */
	   phaserChannel = Mix_PlayChannel(-1, Music, 0);
       return phaserChannel;
}
int CSoundSystem::PlayChunkLoop(Mix_Chunk *Music, int times)
{
/* Mix_PlayChannel takes, as its arguments, the channel that
	   the given sound should be played on, the sound itself, and
	   the number of times it should be looped.  If you don't care
	   what channel the sound plays on, just pass in -1.  Looping
	   works like Mix_PlayMusic. This function returns the channel
	   that the sound was assigned to, which you'll need later. */
	   Util::Thread::ScopedLock scoped(lock);
	   phaserChannel = Mix_PlayChannel(-1, Music, times);
       return phaserChannel;
}

int CSoundSystem::PlayChunkSomeTimes(Mix_Chunk *Music, int times)
{
/* Mix_PlayChannel takes, as its arguments, the channel that
	   the given sound should be played on, the sound itself, and
	   the number of times it should be looped.  If you don't care
	   what channel the sound plays on, just pass in -1.  Looping
	   works like Mix_PlayMusic. This function returns the channel
	   that the sound was assigned to, which you'll need later. */
	   Util::Thread::ScopedLock scoped(lock);
	   phaserChannel = Mix_PlayChannel(-1, Music, times);
       return phaserChannel;
}

void CSoundSystem::HaltChannel()
{
/* Mix_HaltChannel stops a certain channel from playing - this
	 is one of the reasons we kept track of which channel the
	 phaser had been assigned to */
      Mix_HaltChannel(phaserChannel);

	  }

void CSoundSystem::HaltChannel(int phaserChannel)
{
/* Mix_HaltChannel stops a certain channel from playing - this
	 is one of the reasons we kept track of which channel the
	 phaser had been assigned to */
      Mix_HaltChannel(phaserChannel);

	  }
void CSoundSystem::stopMusic()
{
/* Stop the music from playing */

	Mix_HaltMusic();

}

void CSoundSystem::FadeOutMusic(int miliseconds) {
if (!::Mix_FadeOutMusic(miliseconds))
    Debug::debug(1,__FUNCTION__) << "Falha no fadeout da musica"<<endl;

}

void CSoundSystem::FadeInMusic(Mix_Music *Music, int msec) {
	if(Mix_FadeInMusic(Music, -1, msec)==-1) {
    Debug::debug(1,__FUNCTION__) <<"Mix_FadeInMusic Error: " << Mix_GetError() <<endl;
   }
}
void CSoundSystem::CleanUp()
{
   /* This is the cleaning up part */
    Mix_CloseAudio();
}

bool CSoundSystem::InitSystem()
{

    Debug::debug(Debug::resources,__FUNCTION__) << "CSoundSystem::InitSystem()"<<endl;
    /* We're going to be requesting certain things from our audio
     device, so we set them up beforehand */

	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
	int audio_channels = 2;
	int audio_buffers = 4096;
      /* This is where we open up our audio device.  Mix_OpenAudio takes
     as its parameters the audio format we'd /like/ to have. */
  if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
    Debug::debug(Debug::resources,__FUNCTION__) << "Unable to open audio!"<<endl;
    
	exit(1);
  }else m_bAudioOk=true;
/* If we actually care about what we got, we can ask here.  In this
     program we don't, but I'm showing the function call here anyway
     in case we'd want to know later. */
  Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
/* We want to know when our music has stopped playing so we
	   can free it up and set 'music' back to NULL.  SDL_Mixer
	   provides us with a callback routine we can use to do
	   exactly that */
  Mix_HookMusicFinished(MusicDone);

    Debug::debug(Debug::resources,__FUNCTION__) << "There are "<<NumChunkDecoders<<" sample chunk deocoders available" <<endl;

	// set the callback for when a channel stops playing
    Mix_ChannelFinished(this->ChannelDone);
    return true;
}


//To clear 
void CSoundSystem::Clear()
{


}
void CSoundSystem::WaitAnyAvailableChannel()
{

while(Mix_Playing(-1)>=NumChunkDecoders)
{}

}

/* This is the function that we told SDL_Mixer to call when the music
   was finished. In our case, we're going to simply unload the music
   as though the player wanted it stopped.  In other applications, a
   different music file might be loaded and played. */
void CSoundSystem::MusicDone() {
  Mix_HaltMusic();
  CMusic::freeMusic();

}


//Check if the image is already aviable
bool CSoundSystem::IsSoundAviable(short nID,short nGroupNumber,short nImageNumber)
{

	return true;
}


// make a channelDone function
void CSoundSystem::ChannelDone(int channel)
{
   // printf("channel %d finished playing.\n", channel);
}


CMusic::CMusic(bool on):
paused( false ),
enabled(on),
fading( 2000 ),
currentSong(""){
	if ( instance != NULL ){
		Debug::debug(Debug::error,__FUNCTION__) << "Trying to instantiate music object twice!" << endl;
		return;
	}
	//volume = (double) CConfiguration::getMusicVolume() / 100.0;
	instance = this;

}

bool CMusic::loadSong(const string & path){

	if (pMyMusic) {
		Mix_FreeMusic(pMyMusic);
	}
	pMyMusic = LoadMusic( path.c_str() );

	if ( !pMyMusic ){
        string xf( "Could not load " );
        xf += path;
		Debug::debug(Debug::resources,__FUNCTION__) << xf << endl;
        //throw LoadException(xf);
		return false;
    }

    Debug::debug(Debug::resources,__FUNCTION__) << "Song Loaded: " << path << endl;
	return true;
}

void CMusic::freeMusic(){
  if(pMyMusic) Mix_FreeMusic(pMyMusic);
  pMyMusic = NULL;

}

CMusic::~CMusic() {
	/* Unload the music from memory, since we don't need it
	   anymore */
	freeMusic();

}

/*
void CMusic::loadSong( const vector< string > & Songs ){

    //
    //   cout << "Songs = " << &Songs << endl;
    //   if ( ! loadSong( "music/song5.xm" ) ){
    //   cerr << "Could not load music/song5.xm" << endl;
   //    }
   //    return;


	vector< string > _songs = Songs;
	vector< string > songs;
    while ( ! _songs.empty() ){
        int i = Util::rnd( _songs.size() );
		songs.push_back( removeVectorElement< string >( _songs, i ) );
    }


    //   songs.clear();
    //   songs.push_back( "music/song3.xm" );


    for ( vector< string >::iterator it = songs.begin(); it != songs.end(); it++ ){
        Debug::debug( 1 ) << "Trying to load song " << *it << endl;
        if (loadSong(*it)){
            break;
        }
    }
} */

void CMusic::loadSong( const vector< Filesystem::CAbsolutePath > & Songs ){

    /*
       cout << "Songs = " << &Songs << endl;
       if ( ! loadSong( "music/song5.xm" ) ){
       cerr << "Could not load music/song5.xm" << endl;
       }
       return;
       */

	vector < Filesystem::CAbsolutePath > _songs = Songs;
	vector< Filesystem::CAbsolutePath > songs;
    while ( ! _songs.empty() ){
        int i = Util::rnd( _songs.size() );
		songs.push_back( removeVectorElement< Filesystem::CAbsolutePath >( _songs, i ) );
    }

    /*
       songs.clear();
       songs.push_back( "music/song3.xm" );
       */

    for ( vector< Filesystem::CAbsolutePath >::iterator it = songs.begin(); it != songs.end(); it++ ){
		Debug::debug( 1 ) << "Trying to load song " << (*it).path() << endl;
		if (loadSong((*it).path())){
            break;
        }
    }
}

void CMusic::doPlay(){

}

void CMusic::stop() {

	instance->_stop();

}
void CMusic::play() {

	instance->_play();
}

void CMusic::playLoop() {

	instance->_playLoop();

}

void CMusic::playSomeTimes(int times) {
	instance->_playsometimes(times);
}

void CMusic::pause() {
	instance->_pause();

}

void CMusic::resume() {
	instance->_resume();
}

void CMusic::setVolume(int v) {
	instance->_setVolume(v);
}

void CMusic::soften(){

        instance->_soften();

}
void CMusic::louden(){

        instance->_louden();

}

int CMusic::getVolume() {
   volume= GetVolumeMusic();
   return volume;
}

void CMusic::changeSong(){
	instance->_changesong();
}

void CMusic::fadeOut(int msec) {
	instance->_fadeOut(msec);
}
void CMusic::fadeIn(int msec) {

	instance->_fadeIn(msec);
}


void CMusic::_setVolume(int v) {
	setVolumeMusic(v);
}

void CMusic::_play(){

	if (PlayMusic(pMyMusic)==0) {
		paused=false;
	} else {
		Debug::debug(Debug::error,__FUNCTION__) <<"Could not play music: " << Mix_GetError()<<endl;

	}
}
void CMusic::_playLoop(){

if (PlayMusicLoop(pMyMusic)==0) {
		paused=false;;
	} else {
		Debug::debug(Debug::error,__FUNCTION__) <<"Could not play music: " << Mix_GetError()<<endl;

	}
}
void CMusic::_pause(){
	if(!paused) {
	PauseMusic();
	paused=true;
	}
}
void CMusic::_resume() {
	if (paused) {
	ResumeMusic();
	paused=false;
	}
}
void CMusic::_playsometimes(int times) {
	if (PlayMusicSomeTimes(pMyMusic, times)==0) {
		paused=false;;
	} else {
		Debug::debug(Debug::error,__FUNCTION__) <<"Could not play music: " << Mix_GetError()<<endl;

	}


}

void CMusic::_soften(){
	 if (volume > 10){
        volume -= 10;
    } else {
        volume = 0;
    }

    _setVolume(volume);
}
void CMusic::_louden(){

	if ( volume < 128 ){
        volume += 10;
    } else {
        volume = 128;
    }

    _setVolume(volume);
}
void CMusic::_fadeIn(int msec){
	 FadeInMusic(pMyMusic,msec);
}
void CMusic::_fadeOut(int msec){
	FadeOutMusic(msec); //2segundos
}
void CMusic::_stop() {
	if(IsMusicPlaying()) {
	stopMusic();
	paused=false;
	}
}
void CMusic::_changesong(){
    _pause();
    _fadeIn(2000);  //s segundos
	//s to solvge Filesystem problemloadSong(Filesystem::getInstance().getFiles(Filesystem::getInstance().find(Filesystem::CRelativePath("/music/")), "*" ));
    _play();
}
//===============================================
// CSound

CSound::CSound(const string & path): //:
own(NULL),
channel(-1),
error(0),
path(path),
pMySound(NULL)
{
	if (path !="") {
	Debug::debug( 1 ) << "CSound::CSound - Trying to load chunck " << path << endl;
	pMySound = LoadChunk( path.c_str() );

    if ( !pMySound ){
        string xf( "Could not load Sound" );
        xf += path;
		Debug::debug(Debug::resources,__FUNCTION__) << "CSound::CSound -Could not load Sound: " <<path<<endl;
        error=-1;
		// throw LoadException(xf);
    }else
        Debug::debug( 10 ) << "CSound::CSound - Chunck Loaded" << path << endl;

    own = new int;
    *own = 1;
	}else {
	Debug::debug( 10 ) << "CSound::CSound - path is empty" << path << endl;
	error=-1;
	}
}

CSound::CSound(BYTE *chunk): //:
own(NULL),
channel(-1),
error(0),
path(""),
pMySound(NULL)
{
pMySound =LoadChunkMem((Uint8 *)chunk);
if ( !pMySound ){
        	Debug::debug( Debug::sound, __FUNCTION__) << "Could not load Sound"  << endl;
        error=-1;
		// throw LoadException(xf);
    }else
		Debug::debug( Debug::sound, __FUNCTION__) << "CSound::CSound - BYTE Chunck Loaded"  << endl;

    own = new int;
    *own = 1;
}

//soft copy
CSound::CSound( const CSound & copy ):
own( NULL ),
channel(-1),
error(0),
path(copy.path),
pMySound(copy.pMySound)
{
	//reference count
    own = copy.own;  //usa o own do som original e adiciona uma cópia
    if ( own ){
        *own += 1;
    }

}


void CSound::play() {
channel=PlayChunk(pMySound);
}

void CSound::setVolume(int volume) {
this->SetVolumeChunk(pMySound,volume);
}

void CSound::playLoop(int times) {
channel=PlayChunkLoop(pMySound);
}

void CSound::playSomeTimes(int times) {
channel=PlayChunkSomeTimes(pMySound, times);
}

void CSound::stop() {
	if (channel > 0) {
		if (Mix_Playing(this->channel))
		HaltChannel(this->channel);
	}
}

CSound::~CSound()
{
	Debug::debug(Debug::sound,__FUNCTION__) << "CSound::~CSound() Destructor"<<endl;

    releaseInternalSound();
}

/* decrement bitmap reference counter and free memory if counter hits 0 */
void CSound::releaseInternalSound(){
	Debug::debug(Debug::sound,__FUNCTION__) << "Verifyinf to delete Chunk"<<endl;

    const int MAGIC_DEBUG = 0xa5a5a5;
    if (own != NULL){
        if (*own == MAGIC_DEBUG){
			Debug::debug(Debug::sound,__FUNCTION__) << "Trying to delete an already deleted reference counter: "<< own << endl;
        }

        (*own) -= 1;
        if ( *own == 0 ){
			Debug::debug(Debug::sound,__FUNCTION__) << " Own: " << *own << " Releasing internal sound" << endl;
            *own = MAGIC_DEBUG;
            delete own;
            ::Mix_FreeChunk(pMySound);
			own = NULL;
        }
    }
}

} //end SGF