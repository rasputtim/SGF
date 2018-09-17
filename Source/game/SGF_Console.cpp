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


#include "game/SGF_Console.h"
#include "graphics/SGF_Poligon.h"

using namespace std;
namespace SGF {
namespace Console{

CConsoleEnd CConsole::endl;

static void doProcess(void * self){
    CConsole * console = (CConsole*) self;
    console->activate();
}

static void doToggle(void * self){
    CConsole * console = (CConsole*) self;
    console->toggle();
}

static void doPreviousHistory(void * self){
    CConsole * console = (CConsole*) self;
    console->previousHistory();
}

static void doNextHistory(void * self){
    CConsole * console = (CConsole*) self;
    console->nextHistory();
}

static void doTabComplete(void * self){
    CConsole * console = (CConsole*) self;
    console->tabComplete();
}

static void doPageUp(void * self){
    CConsole * console = (CConsole*) self;
    console->pageUp();
}

static void doPageDown(void * self){
    CConsole * console = (CConsole*) self;
    console->pageDown();
}

CConsole::CConsole(const int maxHeight, const Filesystem::CAbsolutePath & font):
state(Closed),
maxHeight(maxHeight),
height(0),
font(font),
textHeight(15),
textWidth(15),
offset(0),
historyIndex(0),
pagePosition(-1){
    textInput.addBlockingHandle(CKeyboard::Key_TILDE, doToggle, this);
    textInput.addBlockingHandle(CKeyboard::Key_ENTER, doProcess, this);
    textInput.addBlockingHandle(CKeyboard::Key_UP, doPreviousHistory, this);
    textInput.addBlockingHandle(CKeyboard::Key_DOWN, doNextHistory, this);
    textInput.addBlockingHandle(CKeyboard::Key_TAB, doTabComplete, this);
    textInput.addBlockingHandle(CKeyboard::Key_PGUP, doPageUp, this);
    textInput.addBlockingHandle(CKeyboard::Key_PGDN, doPageDown, this);
}

CConsole::~CConsole(){
    textInput.disable();
}

/* attempt to complete the current text to a command */
void CConsole::tabComplete(){
    string text = textInput.getText();
    for (map<string, Util::CReferenceCount<CCommand> >::iterator it = commands.begin(); it != commands.end(); it++){
        string what = it->first;
        if (what.find(text) == 0){
            Debug::debug(Debug::error,__FUNCTION__) << "Auto complete '" << what << "'" << ::std::endl;
            textInput.setText(what);
            return;
        }
    }
}
void CConsole::addCommand(const string & name, const Util::CReferenceCount<CCommand> & command){
    if (command == NULL){
        return;
    }

    if (commands[name] != 0){
        Debug::debug(Debug::error,__FUNCTION__) << "Warning: duplicate console command for '" << name << "'" << ::std::endl;
    }
    commands[name] = command;
}
    
void CConsole::addAlias(const string & alias, const string & name){
    addCommand(alias, commands[name]);
}

void CConsole::previousHistory(){
    if (historyIndex < history.size()){
        textInput.setText(history[historyIndex]);
        historyIndex += 1;
    }
}

void CConsole::nextHistory(){
    if (historyIndex > 0){
        historyIndex -= 1;
        textInput.setText(history[historyIndex]);
    } else {
        textInput.setText(string());
    }
}

static const int PAGE_MOVEMENT = 3;
void CConsole::pageUp(){
    if (pagePosition == -1){
        pagePosition = lines.size();
    }
    pagePosition -= PAGE_MOVEMENT;
    if (pagePosition < PAGE_MOVEMENT){
        pagePosition = PAGE_MOVEMENT;
    }
}

void CConsole::pageDown(){
    if (pagePosition != -1){
        pagePosition += PAGE_MOVEMENT;
    }
    if (pagePosition >= lines.size()){
        pagePosition = -1;
    }
}
    
void CConsole::act(){
    double speed = 10.0;
    switch (state){
        case Closed : {
            break;
        }
        case Open : {
            break;
        }
        case Closing : {
            int distance = height;
            height -= (int)((double)distance / speed + 1.0);
            if (height <= 0){
                height = 0;
                state = Closed;
            }
            break;
        }
        case Opening : {
            int distance = maxHeight - height;
            height += (int)((double)distance / speed + 1.0);
            if (height >= maxHeight){
                height = maxHeight;
                state = Open;
            }
            break;
        }
    }
}

/*
static bool isChar(char c){
    const char * letters = "abcdefghijklmnopqrstuvwxyz ,.";
    return strchr(letters, c) != NULL;
}
*/

void CConsole::activate(){
    if (textInput.getText() != ""){
        process(textInput.getText());
    }
    textInput.clearInput();
}
    
bool CConsole::isActive() const {
    return state == Open || state == Opening;
}

/* console input */
bool CConsole::doInput() {
    if (state == Closed || state == Closing){
        return false;
    }

    textInput.doInput();

    return true;
}

void CConsole::draw(const CBitmap & work){
    int x = 3;
    /* if we can show something */
    if (height > 0){
        CBitmap::transBlender(0, 0, 0, 160);
        work.translucent().rectangleFill(0, 0, work.getWidth(), height, Colors::makeColor(200,0,0));
        work.translucent().hLine(0, height, work.getWidth(), Colors::makeColor(200, 200, 200));
        const CFont & font = CFont::getFont(getFont(), textWidth, textHeight);
        int start = height - font.getHeight() * 2;

        int position = 0;
        if (pagePosition != -1){
            position = lines.size() - pagePosition;
        }
        for (vector<string>::reverse_iterator i = lines.rbegin() + position; i != lines.rend() && start > 0; ++i){
            string str = *i;
			font.drawText(x, start, Colors::makeColor(255,255,255), work, str.c_str(), 0);
            start -= font.getHeight();
        }
        if (position != 0){
            work.polygon().circleFill(x, height - font.getHeight() - 2, 1, Colors::makeColor(255, 255, 255));
            work.polygon().circleFill(x + 5, height - font.getHeight() - 2, 1, Colors::makeColor(255, 255, 255));
            work.polygon().circleFill(x + 10, height - font.getHeight() - 2, 1, Colors::makeColor(255, 255, 255));
            work.polygon().circleFill(x + 15, height - font.getHeight() - 2, 1, Colors::makeColor(255, 255, 255));
            work.polygon().circleFill(x + 20, height - font.getHeight() - 2, 1, Colors::makeColor(255, 255, 255));
        }
        font.drawText(x, height - font.getHeight(), Colors::makeColor(255,255,255), work, "> " + textInput.getText() + "|", 0);
    }
}
    
void CConsole::toggle(){
	Debug::debug(Debug::console,__FUNCTION__) << "Toggle Console - actual state: " << state << ::std::endl;
    switch (state){
        case Open:
        case Opening: {
            state = Closing;
            textInput.disable();
            break;
        }
        case Closed:
        case Closing: {
            state = Opening;
            textInput.enable();
            break;
        }
    }
	Debug::debug(Debug::console,__FUNCTION__) << "Toggle Console - New state: " << state << ::std::endl;
   
}

static vector<string> split(string str, char splitter){
    vector<string> strings;
    size_t next = str.find(splitter);
    while (next != string::npos){
        strings.push_back(str.substr(0, next));
        str = str.substr(next+1);
        next = str.find(splitter);
    }
    if (str != ""){
        strings.push_back(str);
    }

    return strings;
}

/* do something with a command */
void CConsole::process(const string & command){
	Debug::debug(Debug::console,__FUNCTION__)<< "Processando Comandos do Console" << ::std::endl;
    Debug::debug(Debug::console,__FUNCTION__)<< "Comando: "<< command << ::std::endl;
    
	/* reset history index */
    historyIndex = 0;
    /* don't duplicate history */
    //if (history.size() == 0 || (history.size() > 0 && !(command == history[1])))){
        history.push_front(command);
    //}
    string start = command;
    if (command.find(' ') != string::npos){
        start = command.substr(0, command.find(' '));
    }

    const map<string, Util::CReferenceCount<CCommand> > & commandSet = commands;
    if (commandSet.find(start) != commandSet.end()){
        map<string, Util::CReferenceCount<CCommand> >::const_iterator found = commandSet.find(start);
        addLine(found->second->act(command));
    } else {
        addLine("Unknown command '" + start + "'");
    }
}
    
void CConsole::addLine(const string & line){
    vector<string> each = split(line, '\n');
    for (vector<string>::iterator it = each.begin(); it != each.end(); it++){
        lines.push_back(*it);
    }
}

CConsole & CConsole::operator<<(const CConsoleEnd & e){
    return *this;
}

void CConsole::clear(){
    lines.clear();
}

vector<Util::CReferenceCount<CCommand> > CConsole::getCommands() const {
    vector<Util::CReferenceCount<CCommand> > out;
    for (map<string, Util::CReferenceCount<CCommand> >::const_iterator it = commands.begin(); it != commands.end(); it++){
        Util::CReferenceCount<CCommand> command = it->second;
        if (command != NULL){
            out.push_back(command);
        }
    }
    return out;
}

}
} //end SGF