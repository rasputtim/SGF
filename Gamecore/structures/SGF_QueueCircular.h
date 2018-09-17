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


#ifndef __SGF_QUEUE_H__
#define __SGF_QUEUE_H__
#include <stdio.h>
#include <stddef.h>
#include "../SGF_Config.h"

namespace SGF {
/**
 * \class CQueueCirc
 *
 * \ingroup SGF_Data_Structures
 *
 * \brief Cria uma fila FIFO (First in First out)
 *
 * \note ItemType é uma estrutura ou classe, para a qual se deseja criar a fila
 * \note next
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 20 de Junho de 2014
 */

 /*
 * Esta classe não é thread safe ainda.
 */ 
template <typename ItemType>
class  CQueueCirc
{
private:
	struct Node { ItemType item; struct Node * next;};
	const static int Q_SIZE = 10;								
	Node * m_pFront;									// pointer to Front of Queue
	Node * m_pRear;										// pointer to Rear of Queue
	int count;											// current number of items in Queue
	int qsize;											// maximum number of items in Queue

	// preemptive definitions to prevent public copying
	 CQueueCirc(const  CQueueCirc & q) : qsize(0) {};
	 CQueueCirc & operator=(const  CQueueCirc & q) {return *this;};

public:
	 CQueueCirc(int qs = Q_SIZE);										// create queue with a qs limit
	~ CQueueCirc();
	bool isempty() const;
	bool isfull() const;
	int queuecount() const;
	bool addItem(const ItemType &element);									// add item to end
	bool getItem(ItemType &);											// remove item from m_pFront
	

};

//=========================
// implementation
template <typename ItemType>
 CQueueCirc<ItemType>:: CQueueCirc(int qs)
{
	qsize = qs;
	count = 0;
	m_pFront = m_pRear = nullptr;
}

template <typename ItemType>
 CQueueCirc<ItemType>::~ CQueueCirc()
{
	Node * temp;						// create temporary address store
	while(m_pFront != (void *) 0)			// while the queue is not empty
	{
		temp = m_pFront;
		m_pFront = m_pFront->next;			// advance the m_pFront object to the next
		delete temp;					// delete the temporary data
	}
}

template <typename ItemType>
bool  CQueueCirc<ItemType>::isempty() const
{
	return count == 0;
}

template <typename ItemType>
bool  CQueueCirc<ItemType>::isfull() const
{
	return count == qsize;
}

template <typename ItemType>
int  CQueueCirc<ItemType>::queuecount() const
{
	return count;
}

template <typename ItemType>
bool  CQueueCirc<ItemType>::deleteFirst()			// remove item from Front
{
	if(m_pFront == NULL)				// Front node is empty, queue is empty
		return false;

	count--;							// decrement item count
	Node * temp = m_pFront; 				// save location of first item
	m_pFront = m_pFront->next; 				// reset m_pFront to next item
	delete temp;						// delete former first item

	if (count == 0)						// if the queue is now empty set Rear to point to nothing
		m_pRear = NULL;

	return true;

}

template <typename ItemType>
bool  CQueueCirc<ItemType>::addItem(const ItemType &data)  	// add item to end
{
	if(isfull())						// if queue is full: delete first item and add a new one
	{
		deleteFirst();
	}

	Node * add = new Node;			// create node
	add->item = data;				// set node pointers
	add->next = NULL;				// or nullptr;
	count++;
	if (m_pFront == NULL)			// if queue is empty,
		m_pFront = add;				// place item at Front
	else
		m_pRear->next = add;		// else place at Rear
	m_pRear = add;					// have Rear point to new node

	return true;
}

template <typename ItemType>
bool  CQueueCirc<ItemType>::getItem(ItemType &data)			// remove item from Front
{
	if(m_pFront == NULL)				// Front node is empty, queue is empty
		return false;

	data = m_pFront->item;					// set data to first item in queue
	count--;							// decrement item count
	Node * temp = m_pFront; 				// save location of first item
	m_pFront = m_pFront->next; 				// reset m_pFront to next item
	delete temp;						// delete former first item

	if (count == 0)						// if the queue is now empty set m_pRear to point to nothing
		m_pRear = NULL;

	return true;

}

/*
 * Esta classe é thread safe.
 */

template<typename ItemType>
class CQueueCircConcurrent
{
private:
	const static int Q_SIZE = 10; 
	CQueueCirc<ItemType> the_queue;  
    mutable Util::Thread::CMutex _my_mutex;
    Util::Thread::Condition * _my_condition_variable;
	
public:
	CQueueCircConcurrent(int _size_=Q_SIZE):
	the_queue(_size_)
	{
		Util::Thread::initializeCondition(_my_condition_variable);
	}
	~CQueueCircConcurrent()
	{
		Util::Thread::destroyCondition(_my_condition_variable);
	}
    void addItem(ItemType const& data)
    {
        _my_mutex.lock();
        the_queue.addItem(data);
        _my_mutex.unlock();
		Util::Thread::conditionSignal(_my_condition_variable);
        //_my_condition_variable.notify_one();
    }

    bool empty() const
    {
        _my_mutex.lock();
        return the_queue.empty();
		_my_mutex.unlock();
    }

    bool getItem_try(ItemType& popped_value)
    {
        _my_mutex.lock();
		if(the_queue.isempty())
        {
            return false;
        }
        the_queue.getItem(popped_value);
        //popped_value=the_queue.front();
        //the_queue.pop();
		_my_mutex.unlock();
        return true;
    }



    void getItem_after_wait(ItemType& popped_value)
    {
        _my_mutex.lock();
        while(the_queue.isempty())
        {
			Util::Thread::conditionWait(_my_condition_variable, _my_mutex.getLock());
            //_my_condition_variable.wait(lock);
        }
        the_queue.getItem(popped_value);
       // popped_value=the_queue.front();
       // the_queue.pop();
		_my_mutex.unlock();
    }

};



} //end SGF
#endif /* !__SGF_QUEUE_H__*/
