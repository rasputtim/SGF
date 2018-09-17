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

#include "resource/SGF_Collector.h"


using namespace std;
namespace SGF {

//#ifndef debug
//#define debug cout<<"File: "<<__FILE__<<" Line: "<<__LINE__<<endl;
//#endif

CCollector::CCollector(){
    /* the only resource */
    my_resource = new CResource();
	my_fontlist = CFontList::GetInstance();
}

CCollector::~CCollector(){
	//Shadow::destroy();
	//ObjectFactory::destroy();
	//NamePlacer::destroy();
	//HeartFactory::destroy();
	//CFontFactory::destroy();
	 //CFontRender::destroy();
	Debug::debug(Debug::resources,__FUNCTION__) << "Cleaning Up" << endl;
    CBitmap::cleanupTemporaryBitmaps();
    if(my_resource) delete my_resource;
	if (my_fontlist) delete my_fontlist;
}
} //end SGF