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



#include "structures/SGF_StackString.h"
#include <string.h>
#include <memory.h>
#include "util/SGF_Debug.h"

namespace SGF {


CStackString::CStackString():
nPos(0),
error(0)
{
    //memset(m_Stack,0,sizeof(m_Stack));

}


CStackString::~CStackString()
{

}

void CStackString::ResetStack()
{
    //Debug::debug(Debug::resources,__FUNCTION__) << "CStack::ResetStack Reseting Stack" <<endl;
   	nPos=0;
    //memset(m_Stack,0,sizeof(m_Stack));

}

void CStackString::push(string strValue)
{
    //if(nPos>STACKSIZE)
    //    Debug::debug(Debug::resources,__FUNCTION__) << "CStack::Push Stack overflow"<< endl;

	if(strValue!=""){
		m_Stack[nPos]=strValue;
	    nPos++;
	}
}

std::string CStackString::pop()
{
    if(nPos<0) {
        //Debug::debug(Debug::resources,__FUNCTION__) << "CStack::Pop Stack underflow"<< endl;
		error=-1;
		}
	else {
    return m_Stack[--nPos];
	}

}

bool CStackString::empty(){
	if(this->nPos<=0)
		return true;
	else
		return false;
}

std::string CStackString::top()
{

    //Debug::debug(Debug::resources,__FUNCTION__) << "CStack::Pop Popping "<< endl;

	if(nPos<0){
		//Debug::debug(Debug::resources,__FUNCTION__) << "CStack::Pop Stack underflow"<< endl;
	error =-1;
	} else if (nPos>0) {
    return m_Stack[nPos-1];
	}

}
	} //end SGF
