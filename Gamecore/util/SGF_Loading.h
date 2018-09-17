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
#ifndef _loading_h
#define _loading_h
#include "../SGF_Config.h"
//#include "tbb/atomic.h"
//#include "tbb/compat/thread"
//#include "tbb/task.h"
//#include "tbb/compat/thread"
#include "SGF_Messages.h"
#include "SGF_MessageQueue.h"
#include "../level/SGF_LevelUtils.h"
#include "SGF_Thread.h"
namespace SGF {

namespace Loader{

/* tipo de carregador a ser mostrado */

enum Kind{
    Default,
    SimpleCircle
};

/**
 * \class CLoadingContext
 *
 * \ingroup SGF_Util
 *
 * \brief Espera durante o Carregamento de Configurações
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CLoadingContext{
public:
    CLoadingContext();
    virtual ~CLoadingContext();
    virtual void doLoad();
    virtual void load() = 0;
    virtual bool done();
    static void * load_it(void * arg);
protected:
    Util::Thread::Lock lock;
    bool finished;
};


extern volatile bool done_loading;

//static void setupBackground(const CBitmap & background, int load_x, int load_y, int load_width, int load_height, int infobox_x, int infobox_y, int infoWidth, int infoHeight, const CBitmap & infoBackground, const CBitmap & work);
void * loadingScreen( void * arg );
class CInfo{
public:
    CInfo();
     ~CInfo();

private:
    MessageQueue messages;
};

#if 0
class  SGE_API CLoadingScreen: public tbb::task {
public:
	CLoadingScreen( void * _arg );
	void * arg;
	int load_x;
    int load_y;
    const int infobox_width;
    const int infobox_height;
    CInfo info;
    string fontName;
    CTTFFont * myFont;
    CTTFFont * infoFont;
    Level::CLevelInfo levelInfo;
	task* execute();
};

#endif
void startLoading(void * arg = 0);
void stopLoading();

void loadScreen(CLoadingContext & context, const Level::CLevelInfo & info, Kind kind = Default);
void * loadingScreen(void *);

}
	} //end SGF
#endif
