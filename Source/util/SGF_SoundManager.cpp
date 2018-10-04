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



#include "util/SGF_SoundManager.h"
#include "util/SGF_Util.h"

#define CHECKOK if ( ! CSoundSystem::m_bAudioOk ) return;
using namespace std;
namespace SGF {

void CSoundManager::toggleSounds() {
    if ( on ) {
        on = false;
        stop();
    }
    else
        on = true;
}
void CSoundManager::stop() {

    for (SoundMapIterator first_it = soundList.begin(); first_it != soundList.end(); first_it++){
			(*first_it).second->stop();

    }

}

void CSoundManager::stop(int index) {
    if ( !isinit ) return;

	    SoundMapIterator first_it = soundList.find(index);
            if (first_it == soundList.end()){ //nao achou o indice

				Debug::debug(Debug::sound,__FUNCTION__) << "Sound not found: " << index  << endl;

			}else { //achou o camhinho. agora achar� o pallete
				Debug::debug(Debug::sound,__FUNCTION__) << "wILL STOP SOUND: " << index  << endl;
				(*first_it).second->stop();

			}
}

void CSoundManager::play(int index, bool looped, int volume) {
    /* frequency used to be a parameter here until switching to sdl
     * we might want to reenable that functionality sometime */

    if ( !isinit ) return;
    if (!on) return;

    //if (Mix_Playing(index))
     //   Mix_HaltChannel(index);
	SoundMapIterator first_it = soundList.find(index);
            if (first_it == soundList.end()){ //nao achou o indice

				Debug::debug(Debug::sound,__FUNCTION__) << "Sound not found: " << index  << endl;

			}else { //achou o camhinho. agora achar� o pallete
				(*first_it).second->setVolume(volume);
				if ( looped )
				(*first_it).second->playLoop();
				else
				(*first_it).second->play();
			}

   // int loop = 0;


}

void CSoundManager::play( const string a_pcSampleName , bool looped, int volume){
	Mix_Chunk* poSample;
	int size = soundIndice.size();
	int found = -1;
	for (int i=0; i< size ; i++) {
		if(soundIndice[i]==a_pcSampleName) found = i;;

	}
	if (found != -1) {
	SoundMapIterator it = soundList.find(found);
	Util::CReferenceCount<CSound> sound = soundList[found];
	
	sound->setVolume(volume * 128/100);
	sound->playLoop(looped);
	}
}

void CSoundManager::LoadSound( const string a_pcFilename, const char* a_pcSampleName ){

	CHECKOK;
	

	std::string sSampleName( a_pcSampleName ? a_pcSampleName : a_pcFilename );
	std::string  m_sSoundDir ="\\sound";
	std::string sSampleFile = m_sSoundDir + a_pcFilename;

	int size = soundIndice.size();
	int found = -1;
	for (int i=0; i< size ; i++) {
		if(soundIndice[i]==sSampleName) found = i;;

	}
	if (found != -1) {
	
		Debug::debug(Debug::sound,__FUNCTION__) << "Sound already loaded: " << a_pcSampleName << endl;
		return;
	}
	Debug::debug(Debug::sound,__FUNCTION__) << "LOADIN SAMPLE: " << sSampleFile << endl;
	int indice = soundIndice.size();
	soundIndice[indice]=sSampleName;
	soundList[indice] = Util::CReferenceCount<CSound>(new CSound(sSampleFile));
	
	if(soundList[indice]==NULL)
	{
		Debug::debug(Debug::sound,__FUNCTION__) << "Mix_LoadWAV: " <<  Mix_GetError() << endl;
		return;
	}
	
	Debug::debug(Debug::sound,__FUNCTION__) << "LOADED SAMPLE: " << a_pcFilename <<endl;


}

void CSoundManager::UnloadSound( const string a_pcSampleName )
{
	/*   TODO
	SampleMapIterator it = m_poPriv->m_oSamples.find( a_pcSampleName );
	if ( m_poPriv->m_oSamples.end() == it )
	{
		debug( "UnloadSample: sample %s not found", a_pcSampleName );
		return;
	}

	Mix_FreeChunk( (*it).second );
	m_poPriv->m_oSamples.erase( it ); */
}

bool CSoundManager::init(map<int, string> &paths) {

    if (isinit)
        return true;

  //  try {
        //initialize exceptions/token_exception.h mixer

       // Mix_AllocateChannels(NUMOFSOUNDS);

        //load wav files

        for (map<int, string>::iterator first_it=paths.begin();first_it != paths.end(); first_it++){
				soundList[(*first_it).first] = Util::CReferenceCount<CSound>(new CSound((*first_it).second));
           //! Todo: Verificar se carregou corretamente CSound
        }

        isinit = true;

 /*   }
    catch ( ECGeneralError& err ) {
            std::cerr << (err.getFullReason() );
            logtxt.print( err.getFullReason() );
    }
    catch ( ... ) {
        std::cerr << "Unexpected exception";

    } */
    return true;
}

CSoundManager::CSoundManager() :
        on(true), isinit(false)
{

}

CSoundManager::~CSoundManager()
{
	Debug::debug(Debug::sound,__FUNCTION__) << "Deleting Sound Manager. Util::CReferenceCount should Delete all sounds" << endl;
}


//=====================MUSIC MANAGER===============

void CMusicManager::toggleSounds() {
    if ( on ) {
        on = false;
        stop();
    }
    else
        on = true;
}
void CMusicManager::stop() {

	CSound::stopMusic();

}

void CMusicManager::fadeMusic( int a_iMilliSec )
{
CSoundSystem::FadeOutMusic(a_iMilliSec);
}

void CMusicManager::setMusicVolume( int a_iVolume )
{
	CSoundSystem::setVolumeMusic(a_iVolume);
}
void CMusicManager::playMusic( const string a_pcMusicName ,int looped, int volume)
{
	MusicMapIterator it = musicList.find( a_pcMusicName );
	if ( musicList.end() == it )
	{
		Debug::debug(Debug::sound,__FUNCTION__) << "music  not found: " << a_pcMusicName << endl;
		return;
	}

	setMusicVolume( volume );
	Mix_PlayMusic( (*it).second, looped );
	Mix_FadeInMusic( (*it).second, -1, 100 );
}


bool CMusicManager::init(map<int, string> &paths) {

    if (isinit)
        return true;

  //  try {
       
        for (map<int, string>::iterator first_it=paths.begin();first_it != paths.end(); first_it++){
			loadMusic((*first_it).second);
           
        }

        isinit = true;

 /*   }
    catch ( CGeneralError& err ) {
            std::cerr << (err.getFullReason() );
            logtxt.print( err.getFullReason() );
    }
    catch ( ... ) {
        std::cerr << "Unexpected exception";

    } */
    return true;
}


void CMusicManager::loadMusic( const string a_pcFilename, const char* a_pcMusicName )
{
	CHECKOK;
	Debug::debug(Debug::error, __FUNCTION__) << " Will try to load: "<< a_pcFilename <<" That will be named: "<<a_pcMusicName <<endl;
			
	string sMusicName( a_pcMusicName ? a_pcMusicName : a_pcFilename );
	//string sMusicFile = DATADIR;
	//sMusicFile += "/sound/";
	string sMusicFile = a_pcFilename;
	if (Util::exists(sMusicFile)) {
		if ( musicList.count( sMusicName ) )
		{
			Debug::debug(Debug::error, __FUNCTION__) <<a_pcMusicName << " already loaded"<<endl;
			return;
		}

		Mix_Music *poMusic;
		poMusic=CSoundSystem::LoadMusic(sMusicFile);
		if(!poMusic)
		{
			Debug::debug(Debug::error, __FUNCTION__) <<a_pcMusicName << "Could not be loaded: "<< Mix_GetError()<< endl;
			return;
		}

		musicList[ sMusicName ] = poMusic;
		isinit = true;
	}
}


void CMusicManager::UnloadMusic( const string a_pcMusicName )
{
	MusicMapIterator it = musicList.find( a_pcMusicName );
	if ( musicList.end() == it )
	{
		Debug::debug(Debug::sound,__FUNCTION__) << "music not found: " << a_pcMusicName << endl;
		return;
	}

	Mix_FreeMusic( (*it).second );
	musicList.erase( it );
}

CMusicManager::CMusicManager() :
on(true), isinit(false),
m_iMusicVolume(100) //max volume
{

}

CMusicManager::~CMusicManager()
{
	for (MusicMapIterator it=musicList.begin();it != musicList.end();it++) {
	if ( (*it).second !=NULL) Mix_FreeMusic( (*it).second );
	musicList.erase( it );
	}
}
} //end SGF