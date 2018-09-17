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
#ifndef _console_h
#define _console_h

#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <string>
#include <time.h>
#include <deque>
#include "../SGF_Config.h"
#include "../graphics/all.h"
#include "../exceptions/all.h"
#include "../SGF_Global.h"
#include "../resource/all.h"
#include "../input/SGF_TextInput.h"
namespace SGF {
class CBitmap;

namespace Console{

/* equivalent of endl */
class  SGE_API CConsoleEnd{
private:
    friend class CConsole;
    CConsoleEnd(){
    }
};

/**
 * \class CCommand
 *
 * \ingroup SGF_Game
 *
 * \brief Fornece comandos para o Console
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */
class  SGE_API CCommand{
public:
    CCommand(){
    }

    virtual string act(const string & line) = 0;
    virtual string getDescription() const = 0;

    virtual ~CCommand(){
    }
};


/**
 * \class CConsole
 *
 * \ingroup SGF_Game
 *
 * \brief Fornece Serviços de Console para o Jogo
 *
 * \ note inicia desabilitada
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */
class  SGE_API CConsole{
public:
	CConsole(const int maxHeight, const Filesystem::CAbsolutePath & font = Global::DEFAULT_FONT2);
    virtual ~CConsole();

    /* handle input and whatnot */
    virtual void act();
    virtual void draw(const CBitmap & work);
    /* enable / disable */
    virtual void toggle();

    /* removes all output from the console */
    virtual void clear();

    virtual bool doInput();
    /* scroll up and down */
    virtual void pageUp();
    virtual void pageDown();

    virtual bool isActive() const;

    /* add a line of text */
    virtual void addLine(const string & line);

    inline int getTextHeight(){ return textHeight; };
    inline int getTextWidth(){ return textWidth; };

    inline void setTextHeight(int h){ textHeight = h; };
    inline void setTextWidth(int w){ textWidth = w; };

    inline const Filesystem::CAbsolutePath & getFont() const {
        return font;
    }

    /* for arbitrary data */
    template<typename T> CConsole & operator<<(const T & x){
        // textInput << x;
        return *this;
    }
	vector<Util::CReferenceCount<CCommand> > getCommands() const;

	void addCommand(const string & name, const Util::CReferenceCount<CCommand> & command);

    /* make 'alias' do the same thing as command 'name' */
    void addAlias(const string & alias, const string & name);

    /* for end of line, always pass CConsole::endl */
    CConsole & operator<<(const CConsoleEnd & e);

    static CConsoleEnd endl;

    void activate();

	void previousHistory();
    void nextHistory();

    void tabComplete();

protected:

    void process(const string & command);

    enum State{
        Closed,
        Open,
        Opening,
        Closing,
    } state;

    const int maxHeight;
    int height;

    Filesystem::CAbsolutePath font;

    // Text height
    int textHeight;
    // Text width
    int textWidth;
    vector<string> lines;
    // Our text inputer
    // stringstream textInput;
    // stringstream currentCommand;
    unsigned int offset;
    // InputMap<char> input;
    CTextInput textInput;
    map<string, Util::CReferenceCount<CCommand> > commands;

    //void checkStream();
	    /* history of typed commands */
    std::deque<string> history;
    /* index into history. 0 is latest */
    unsigned int historyIndex;
    int pagePosition;

};

}
} //end SGF
#endif
