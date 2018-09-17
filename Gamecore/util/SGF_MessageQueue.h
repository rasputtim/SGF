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
#ifndef _message_queue_h
#define _message_queue_h



#include <string>
#include <queue>
#include "../SGF_Config.h"
#include "SGF_Thread.h"

namespace SGF {

/**
 * \class MessageQueue
 *
 * \ingroup SGF_Util
 *
 * \brief Fila  de mensagens Multithread FIFO
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API MessageQueue{
public:
    MessageQueue();

    /* push on */
    void add(const string & str);
    /* true if any messages are left */
    bool hasAny();
    /* get the first message */
    string get();

    ~MessageQueue();

	static void registerInfo(MessageQueue *);
    static void unregisterInfo(MessageQueue *);
    static void info(const std::string & str);
    static void clearInfo();
    static Util::Thread::Lock messageLock;


private:
    std::queue<string> messages;
	//CMyQueue<string> messages;
     Util::Thread::Lock lock;
};
} //end SGF
#endif
