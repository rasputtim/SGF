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
#include "menu/SGF_OptionScreenSize.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
namespace SGF {

namespace Menu {
#if defined(WIN32) && defined(doesnt_work_yet)
#include <windows.h>
#include <stdio.h>

/* contributed by Roy Underthump from allegro.cc */
static vector<ScreenSize> getScreenResolutions(){
    HWND hwnd;
    HDC  hdc;

    // int iPixelFormat;
    int descerr;
    int retval;

    DEVMODE d;

    PIXELFORMATDESCRIPTOR pfd;

    hwnd = GetDesktopWindow();
    hdc  = GetDC(hwnd);

    vector<ScreenSize> modes;

    for (int i = 0;; i++){
        retval = EnumDisplaySettings(0,i,&d);
        if (!retval){
            break;
        }

        descerr = DescribePixelFormat(hdc, i+1, sizeof(pfd), &pfd);
        if(!descerr){
            continue;
        }

        /*
           printf("\n#%d bpp %d width %d height %d colorbits %d fps %d",i,d.dmBitsPerPel,
           d.dmPelsWidth, d.dmPelsHeight,pfd.cColorBits,d.dmDisplayFrequency);

           if(pfd.dwFlags & PFD_SUPPORT_OPENGL)printf(" OGL OK");
         */
        modes.push_back(ScreenSize(d.dmPelsWidth, d.dmPelsHeight));
    }

    if (modes.empty()){
        modes.push_back(ScreenSize(640,480));
    }

    return modes;
}
#else
static vector<ScreenSize> getScreenResolutions(){
	vector<ScreenSize> modes;
	modes.push_back(ScreenSize(640, 480));
	modes.push_back(ScreenSize(800, 600));
	modes.push_back(ScreenSize(1024, 768));
	modes.push_back(ScreenSize(1280, 1024));
	modes.push_back(ScreenSize(1600, 1200));
	return modes;
}
#endif

static bool doSort(const ScreenSize & a, const ScreenSize & b){
    return (a.w * a.h) < (b.w * b.h);
}

static vector<ScreenSize> sortResolutions(const vector<ScreenSize> & modes){
    vector<ScreenSize> copy(modes);
    sort(copy.begin(), copy.end(), doSort);
    return copy;
}

COptionScreenSize::COptionScreenSize(const Gui::CContextBox & parent, const Token *token) throw(CLoadException):
CMenuOption(parent, token),
name(""),
lblue(255),
lgreen(255),
rblue(255),
rgreen(255){
    setRunnable(false);

    Debug::debug(Debug::menu,__FUNCTION__) << " Get screen resolution" << endl;
    modes = sortResolutions(getScreenResolutions());

  //  if (Debug::getDebug() >= 1){
  //      for (vector<ScreenSize>::iterator it = modes.begin(); it != modes.end(); it++){
  //          Debug::debug(Debug::menu,__FUNCTION__) << " Screen size: " << it->w << " x " << it->h << endl;
  //      }
  //  }

    if ( *token != "screen-size" ){
        throw CLoadException(__FILE__, __LINE__," Not a screen-size");
    }

    readName(token);
}

COptionScreenSize::~COptionScreenSize(){
    // Nothing
}

void COptionScreenSize::logic(){
    ostringstream temp;
    temp << "Screen size: " << CConfiguration::screenWidth.getInteger() << " x " << CConfiguration::screenHeight.getInteger();
    setText(temp.str());

    if (lblue < 255){
        lblue += 5;
    }

    if (rblue < 255){
        rblue += 5;
    }

    if (lgreen < 255){
        lgreen += 5;
    }

    if (rgreen < 255){
        rgreen += 5;
    }

//s    setLeftAdjustColor(Colors::makeColor(255, lblue, lgreen));
//s    setRightAdjustColor(Colors::makeColor(255, rblue, rgreen));
}


void COptionScreenSize::run(const Menu::CContext & context){
}

void COptionScreenSize::setMode(int width, int height){
    if (width != CConfiguration::screenWidth.getInteger() ||
        height != CConfiguration::screenHeight.getInteger()){
			CBitmap::_my_state->Screen[0]->SetWindowMode(width,height);

			CConfiguration::screenWidth.setInteger(width);
			
            CConfiguration::screenHeight.setInteger(height);
			
			/*
        Debug::debug(Debug::menu,__FUNCTION__) << "COptionScreenSize::setMode - Changing mode to " << width << " x " << height << endl;
        int gfx = CConfiguration::fullScreen.getBool() ? Global::FULLSCREEN : Global::WINDOWED;
        int ok = NULL;//CBitmap::setGraphicsMode(gfx, width, height);
        if (ok == 0){
            Debug::debug(Debug::menu,__FUNCTION__) << "COptionScreenSize::setMode - Success" << endl;
            CConfiguration::screenWidth.setInteger(width);
            CConfiguration::screenHeight.setInteger(height);
        } else {
            Debug::debug(Debug::menu,__FUNCTION__) << "COptionScreenSize::setMode - Fail" << endl;
            int ok = NULL;//CBitmap::setGraphicsMode(gfx, CConfiguration::screenWidth.getInteger(), CConfiguration::screenHeight.getInteger());
            Debug::debug(Debug::menu,__FUNCTION__) << "COptionScreenSize::setMode - Set mode back " << ok << endl;
        } */
    }
}

/*
static int modes[][2] = {{640,480}, {800,600}, {1024,768}, {1280,1024}, {1600,1200}};
// static int max_modes = sizeof(modes) / sizeof(int[]);
static int max_modes = 5;
*/

int COptionScreenSize::findMode(int width, int height){
    for (int mode = 0; mode < (int) modes.size(); mode++){
        if (modes[mode].w == width && modes[mode].h == height){
            return mode;
        }
    }
    return -1;
}

bool COptionScreenSize::leftKey(){
    int mode = findMode(CConfiguration::screenWidth.getInteger(), CConfiguration::screenHeight.getInteger());
    if (mode >= 1 && mode < (int)modes.size()){
        mode -= 1;
    } else {
        mode = 0;
    }

    setMode(modes[mode].w, modes[mode].h);

    lblue = lgreen = 0;
    return true;
}

bool COptionScreenSize::rightKey(){
    int mode = findMode(CConfiguration::screenWidth.getInteger(), CConfiguration::screenHeight.getInteger());
    if (mode >= 0 && mode < (int)modes.size() - 1){
        mode += 1;
    } else {
        mode = 0;
    }

    setMode(modes[mode].w, modes[mode].h);

    rblue = rgreen = 0;
    return true;
}
}
} //end SGF