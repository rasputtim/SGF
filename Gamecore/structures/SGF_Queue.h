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
#include <queue>
#include "../SGF_Config.h"
#include "../util/SGF_Thread.h"

namespace SGF {
/**
 * \class CQueue
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
 * Created on: 20 de Janeiro de 2013
 */


//#define CQueueTemp( ItemType, next )		CQueue<ItemType, (int)&(((ItemType*)NULL)->next)>
/*
 * http://www.cplusplus.com/forum/general/71229/
 *
 * Esta classe não é thread safe ainda.
 */
template <typename ItemType>
class CQueue
{
private:
	struct Node { ItemType item; struct Node * next;};
	const static int Q_SIZE = 10;
	Node * front;												// pointer to front of Queue
	Node * rear;												// pointer to rear of Queue
	int count;													// current number of items in Queue
	int qsize;											// maximum number of items in Queue

	// preemptive definitions to prevent public copying
	CQueue(const CQueue & q) : qsize(0) {};
	CQueue & operator=(const CQueue & q) {return *this;};

public:
	CQueue(int qs = Q_SIZE);										// create queue with a qs limit
	~CQueue();
	bool isempty() const;
	bool isfull() const;
	int queuecount() const;
	bool addItem(const ItemType &element);									// add item to end
	bool getItem(ItemType &);											// remove item from front


};

//=========================
// implementation
template <typename ItemType>
CQueue<ItemType>::CQueue(int qs)
{
	qsize = qs;
	count = 0;

	front = rear = NULL;


}

template <typename ItemType>
CQueue<ItemType>::~CQueue()
{
	Node * temp;						// create temporary address store
	while(front != (void *) 0)			// while the queue is not empty
	{
		temp = front;
		front = front->next;			// advance the front object to the next
		delete temp;					// delete the temporary data
	}
}

template <typename ItemType>
bool CQueue<ItemType>::isempty() const
{
	return count == 0;
}

template <typename ItemType>
bool CQueue<ItemType>::isfull() const
{
	return count == qsize;
}

template <typename ItemType>
int CQueue<ItemType>::queuecount() const
{
	return count;
}

template <typename ItemType>
bool CQueue<ItemType>::addItem(const ItemType &data)  	// add item to end
{
	if(isfull())						// if queue is full halt queuing
		return false;

	Node * add = new Node;				// create node
	add->item = data;					// set node pointers
	add->next = NULL;		// or nullptr;
	count++;
	if (front == NULL)			// if queue is empty,
		front = add;					// place item at front
	else
		rear->next = add;				// else place at rear
	rear = add;							// have rear point to new node

	return true;
}

template <typename ItemType>
bool CQueue<ItemType>::getItem(ItemType &data)			// remove item from front
{
	if(front == NULL)				// front node is empty, queue is empty
		return false;

	data = front->item;					// set data to first item in queue
	count--;							// decrement item count
	Node * temp = front; 				// save location of first item
	front = front->next; 				// reset front to next item
	delete temp;						// delete former first item

	if (count == 0)						// if the queue is now empty set rear to point to nothing
		rear = NULL;

	return true;

}



//========================

 /*
 * http://www.justsoftwaresolutions.co.uk/threading/implementing-a-thread-safe-queue-using-condition-variables.html
 * Esta classe é thread safe.
 */

template<typename ItemType>
class CQueueConcurrent
{
private:
	const static int Q_SIZE = 10;
	CQueue<ItemType> the_queue;  //queue com 10 elementos
    mutable Util::Thread::CMutex _my_mutex;
    Util::Thread::Condition * _my_condition_variable;

public:
	CQueueConcurrent(int _size_=Q_SIZE):
	the_queue(_size_)
	{
		Util::Thread::initializeCondition(_my_condition_variable);
	}
	~CQueueConcurrent()
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

/* Old Queue implement*/
/*
template< class ItemType >
class CQueue {
public:
							CQueue();
							//! adiciona um item na fila
	void					addItem( ItemType *element );
							//! retira um item da fila
	ItemType *				getItem();

private:
	ItemType *					m_pFirst; //! aponta para o primeiro elemento
	ItemType *					m_pLast; //! aponta para o elemtno atual, que é o último também
	int							m_iNextOffset; //! é o offset em bytes para o ponteiro do próximo elemento dentro da estrutura de dados ItemType
};

#define NEXT_POINTER_QUEUE( element )		(*((ItemType**)(((SGF_Byte*)element)+m_iNextOffset)))
//! m_iNextOffset is the offset to the next pointer inside he ItemType structure
//! offsetof( ItemType, next )
template< class ItemType >
CQueue<ItemType>::CQueue() {
	m_pFirst = m_pLast = NULL;
	m_iNextOffset =offsetof( ItemType, next );
}

template< class ItemType >
void CQueue<ItemType>::addItem( ItemType *element ) {
	//! seta o next do elemento atual para NULL;
	NEXT_POINTER_QUEUE(element) = NULL;
	if ( m_pLast ) {
		//!atualiza o next do último elemento para apontar paa o nó atual
		NEXT_POINTER_QUEUE(m_pLast) = element;
	} else {
		m_pFirst = element;
	}
	// atualiza o último elemento da fila para o nó atual
	m_pLast = element;
}

template< class ItemType >
ItemType *CQueue<ItemType>::getItem() {
	ItemType *element;

	element = m_pFirst;
	if ( element ) {
		m_pFirst = NEXT_POINTER_QUEUE(m_pFirst);
		if ( m_pLast == element ) {
			m_pLast = NULL;
		}
		NEXT_POINTER_QUEUE(element) = NULL;
	}
	return element;
}
*/
} //end SGF
#endif /* !__SGF_QUEUE_H__*/
