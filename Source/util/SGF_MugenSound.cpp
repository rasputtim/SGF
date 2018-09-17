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
#include <string.h>
#include "util/SGF_MugenSound.h"
#include "util/SGF_AudioSystem.h"
namespace SGF {

CMugenSound::CMugenSound():
next(0),
length(0),
groupNumber(0),
sampleNumber(0),
sample(0),
sound(0){
    //Nothing
}
CMugenSound::CMugenSound(CSound *som):
next(0),
length(0),
groupNumber(0),
sampleNumber(0),
sample(0),
sound(som){
    //Nothing
}

void CMugenSound::load(){
	if (sample !=NULL)
    sound = new CSound(sample);


}

void CMugenSound::setSound(CSound *som){
    sound = som;
}
void CMugenSound::play(){
    if (sound !=NULL){
        sound->play();
    }
}

void CMugenSound::stop(){
    if (sound!=NULL){
        sound->stop();
    }
}

CMugenSound::CMugenSound( const CMugenSound &copy ){
    this->next = copy.next;
    this->length = copy.length;
    this->groupNumber = copy.groupNumber;
    this->sampleNumber = copy.sampleNumber;
    this->sample = new BYTE[this->length];
    memcpy(this->sample, copy.sample, this->length);
    sound = new CSound(sample);
}

CMugenSound::~CMugenSound(){
    if (sample!=NULL){
        delete[] sample;
    }
    if (sound!=NULL){
		SGF::Debug::debug(SGF::Debug::error,__FUNCTION__) << "DELETING SOUND (group, sample): ( "<<groupNumber<< " , " << sampleNumber << " )" << endl;

        delete sound;
    }
}

} // end SGF
