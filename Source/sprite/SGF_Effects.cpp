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

#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <ostream>
#include <sstream>
#include <iostream>

// To aid in filesize
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "sprite/SGF_Efects.h"


using namespace std;
namespace SGF {

Mugen::CEffects::CEffects():
trans(None),
alphaSource(255),
alphaDest(255),
mask(false),
hflip(0),
vflip(0),
scalex(1),
scaley(1),
rotation(0),
filter(NULL){
}

Mugen::CEffects::CEffects(const Mugen::CEffects & copy){
    this->trans = copy.trans;
    this->alphaSource = copy.alphaSource;
    this->alphaDest = copy.alphaDest;
    this->mask = copy.mask;
    this->hflip = copy.hflip;
    this->vflip = copy.vflip;
    this->scalex = copy.scalex;
    this->scaley = copy.scaley;
    this->dimension = copy.dimension;
	this->rotation = copy.rotation;
    this->filter = copy.filter;
}

const Mugen::CEffects &Mugen::CEffects::operator=(const Mugen::CEffects &e){
    // Check for self-assignment!
    if (this == &e)      // Same object?
      return *this;        // Yes, so skip assignment, and just return *this.


	this->trans = e.trans;
    this->alphaSource = e.alphaSource;
    this->alphaDest = e.alphaDest;
    this->mask = e.mask;
    this->hflip = e.hflip;
    this->vflip = e.vflip;
    this->scalex = e.scalex;
    this->scaley = e.scaley;
    this->dimension = e.dimension;
	this->rotation = e.rotation;
    this->filter = e.filter;
    return *this;
}

Mugen::CEffects Mugen::CEffects::operator+(const Mugen::CEffects & e2) const {
    Mugen::CEffects result(*this);
        result.mask |= e2.mask;
    result.trans = e2.trans;
    result.alphaSource = e2.alphaSource;
    result.alphaDest = e2.alphaDest;
    result.scalex = e2.scalex;
    result.scaley = e2.scaley;
    result.hflip = result.hflip ^ e2.hflip;
    result.vflip = result.vflip ^ e2.vflip;
    result.rotation = e2.rotation;
    if (result.filter == NULL){
        result.filter = e2.filter;
    }return result;
}
            
Mugen::CEffects Mugen::CEffects::operator+(const TransType & translucent) const {
    Mugen::CEffects result(*this);
    result.trans = translucent;
    return result;
}
Mugen::CEffects::~CEffects(){
}
} //end SGF

