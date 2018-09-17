
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

#ifndef _S_G_F_chat_widget_h
#define _S_G_F_chat_widget_h

#include "../SGF_Config.h"
#include <deque>
#include "../input/all.h"
#include "../objects/all.h"
#include "../game/all.h"
namespace SGF{

class CTheater;

class CChatWidget{
public:
    CChatWidget(CTheater & world, CObject::networkid_t id);
    virtual ~CChatWidget();

    virtual void act();
    void receiveMessage(string message);

    /*
    inline const std::deque<string> & getChatMessages() const {
        return chatMessages;
    }
    */

    virtual void drawChat(CBitmap * work, int start);

public:
    void endChatLine();

private:
    struct Message{
        Message(string sender, string text, int life):
            sender(sender),
            text(text),
            life(life){
            }

        string sender;
        string text;
        int life;
    };

    enum Inputs{
        Talk,
    };

    CTheater & world;
    std::deque<Message> chatMessages;
    int removeChatTimer;
    bool enable_chat;
    CTextInput chatInput;
    CInputMap<Inputs> input;
    CObject::networkid_t id;
};
} //end SGF
#endif
