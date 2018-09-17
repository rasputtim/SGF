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
#ifndef SGF_mugen_sound_h
#define SGF_mugen_sound_h

#include <string>
#include <map>
#include "SGF_Pointer.h"

#ifndef byte
typedef unsigned char BYTE;
#endif
using namespace std;
namespace SGF {

class CMugenSound;
typedef map< unsigned int, Util::CReferenceCount<CMugenSound> > MugenSoundGroup;
typedef map< unsigned int, MugenSoundGroup > MugenSoundMap;



class CSound;

class CMugenSound{
public:
    CMugenSound();
	CMugenSound(CSound *);
    CMugenSound(const CMugenSound &copy);
    virtual ~CMugenSound();
	void setSound(CSound *som);
    void load();
    void play();
    void stop();

    int next;
    int length;
    int groupNumber;
    int sampleNumber;
    BYTE * sample; //used to store the byte stream of the sound. tirar isso, visto que o strea já é guardado no CSound???
    CSound * sound;

};

} //end SGF
#endif
