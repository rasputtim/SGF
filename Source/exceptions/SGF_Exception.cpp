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

#include <sstream>
#include "exceptions/SGF_Exception.h"


using namespace std;
namespace SGF {
namespace Exception{

CBase::CBase(const string & file, int line):
file(file),
line(line),
nested(NULL){
}

CBase::CBase(const string & file, int line, const CBase & nested):
file(file),
line(line),
nested(nested.copy()){
}

CBase::~CBase() throw (){
    if (nested){
        delete nested;
    }
}
    
const string CBase::getReason() const { 
    return "reason not given";
}
    
const string CBase::getTrace() const {
    ::std::ostringstream out;
    out << file << ":" << line << " " << getReason();
    if (nested != NULL){
        out << "\n";
        out << nested->getTrace();
    }
    return out.str();
}

CBase::CBase(const CBase & copy):
file(copy.file),
line(copy.line),
nested(NULL){
    if (copy.nested != NULL){
        nested = copy.nested->copy();
    }
}

void CBase::set(const CBase & him){
    nested = him.copy();
}

CBase * CBase::copy() const {
    return new CBase(*this);
}

Return::Return(const string & file, int line):
CBase(file, line){
}
    
Return::Return(const string & file, int line, const CBase & nested):
CBase(file, line, nested){
}

Return::~Return() throw(){
}

void Return::throwSelf() const {
    throw *this;
}

CBase * Return::copy() const {
    return new Return(*this);
}

Quit::Quit(const string & file, int line):
CBase(file, line){
}

Quit::Quit(const string & file, int line, const CBase & nested):
CBase(file, line, nested){
}

Quit::~Quit() throw(){
}

void Quit::throwSelf() const {
    throw *this;
}

CBase * Quit::copy() const {
    return new Quit(*this);
}

}
} //end SGF
