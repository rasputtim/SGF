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

#include <string>
#include "util/SGF_MessageQueue.h"
#include "util/SGF_Thread.h"
 namespace SGF {

Util::Thread::Lock MessageQueue::messageLock;

MessageQueue::MessageQueue(){
    Util::Thread::initializeLock(&lock);
}

void MessageQueue::add(const string & str){
    Util::Thread::acquireLock(&lock);
    messages.push(str);
    Util::Thread::releaseLock(&lock);
}

bool MessageQueue::hasAny(){
    bool any = false;
    Util::Thread::acquireLock(&lock);
    any = messages.size() > 0;
    Util::Thread::releaseLock(&lock);
    return any;
}

string MessageQueue::get(){
     string str;
    Util::Thread::acquireLock(&lock);
    if (messages.size() > 0){
        str = messages.front();
        messages.pop();
    }
    Util::Thread::releaseLock(&lock);
    return str;
}

MessageQueue::~MessageQueue(){
}

static vector<string> messageBuffer;
/* should support infinite queues eventually */
static MessageQueue * current = NULL;
void MessageQueue::registerInfo(MessageQueue * queue){
    Util::Thread::acquireLock(&messageLock);
    current = queue;
    if (current != NULL){
        /* push all saved messages immediately to the queue */
        for (vector<string>::iterator it = messageBuffer.begin(); it != messageBuffer.end(); it++){
            current->add(*it);
        }
        messageBuffer.clear();
    }
    Util::Thread::releaseLock(&messageLock);
}

/* clear any buffered messages */
void MessageQueue::clearInfo(){
    Util::Thread::acquireLock(&messageLock);
    messageBuffer.clear();
    Util::Thread::releaseLock(&messageLock);
}

void MessageQueue::unregisterInfo(MessageQueue * queue){
    Util::Thread::acquireLock(&messageLock);
    if (current == queue){
        current = NULL;
    }
    Util::Thread::releaseLock(&messageLock);
}

void MessageQueue::info(const std::string & str){
    Util::Thread::acquireLock(&messageLock);
    if (current != NULL){
        current->add(str);
    } else {
        /* save it for later until a message-queue is registered */
        messageBuffer.push_back(str);
    }
    Util::Thread::releaseLock(&messageLock);
}




 } //end SGF