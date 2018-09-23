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


#ifndef __SGF_LINKLIST_H__
#define __SGF_LINKLIST_H__

/**
 * \class CLinkedList
 *
 * \ingroup SGF_Data_Structures
 *
 * \brief Cria uma Lista Circular
 *
 * \note ItemType é uma estrutura ou classe, para a qual se deseja criar a lista
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 20 de Janeiro de 2013
 */

/**
Uma lista ligada ou lista encadeada é uma estrutura de dados linear e dinâmica. 
Ela é composta por células que apontam para o próximo elemento da lista. 
Para "ter" uma lista ligada/encadeada, basta guardar seu primeiro elemento, 
e seu último elemento aponta para uma célula nula. 
O esquema a seguir representa uma lista ligada/encadeada com 5 elementos:

Célula 1 ----> Célula 2 ---> Célula 3 ---> Célula 4 ---> Célula 5 ---> (Nulo)

Para inserir dados ou remover dados é necessário ter um ponteiro que aponte para o 1º elemento 
e outro que aponte para o fim, porque se queremos inserir ou apagar dados que estão nessas posições, 
a operação é rapidamente executada. Caso seja necessário editar um nó que esteja no meio da lista haverá 
uma busca pela posição desejada.

http://pt.wikipedia.org/wiki/Lista_ligada
http://www.ime.usp.br/~pf/algoritmos/aulas/lista.html
*/

template< class ItemType >
class CLinkedList {
public:
						CLinkedList();
						~CLinkedList();

	bool				isListEmpty() const;
	bool				isInList() const;
	int					getNum() const;
	void				clear();

	void				insertBefore( CLinkedList &node );
	void				insertAfter( CLinkedList &node );
	void				addToEnd( CLinkedList &node );
	void				addToFront( CLinkedList &node );

	void				remove();

	ItemType *			getNext() const;
	ItemType *			getPrev() const;

	ItemType *			getOwner() const;
	void				setOwner( ItemType *object );

	CLinkedList *		getListHead() const;
	CLinkedList *		getNextNode() const;
	CLinkedList *		getPrevNode() const;

private:
	CLinkedList *		head;
	CLinkedList *		next;
	CLinkedList *		prev;
	ItemType *			owner;
};

/**
 \brief Node is initialized to be the head of an empty list
 \brief construtor da lista ligada
* \note O nó é inicializado para ser o nó cabeça
*/
template< class ItemType >
CLinkedList<ItemType>::CLinkedList() {
	owner	= NULL;
	head	= this;	
	next	= this;
	prev	= this;
}

/**
CLinkedList<ItemType>::~CLinkedList
Removes the node from the list, or if it's the head of a list, removes
all the nodes from the list.
* \note se o nó a ser removido for o nó cabeça, remove a lista toda
*/
template< class ItemType >
CLinkedList<ItemType>::~CLinkedList() {
	clear();
}

/*
CLinkedList<ItemType>::isListEmpty
Returns true if the list is empty.
*/

/** \brief verifica se a lista está vazia
* \return true se a lista estiver vazia
*/
template< class ItemType >
bool CLinkedList<ItemType>::isListEmpty() const {
	return head->next == head;
}

/*
CLinkedList<ItemType>::isInList
Returns true if the node is in a list.  If called on the head of a list, will always return false.
*/
/** \brief verifica se um nó faz parte da lista
* \note se o nó for o cabeça, retornará falso
* \return true se o né faz parte da lista
*/
template< class ItemType >
bool CLinkedList<ItemType>::isInList() const {
	return head != this;
}

/*
CLinkedList<ItemType>::getNum
Returns the number of nodes in the list.
*/
/** \brief retorna o número de nós numa lista
*/
template< class ItemType >
int CLinkedList<ItemType>::getNum() const {
	CLinkedList<ItemType>	*node;
	int					num;

	num = 0;
	for( node = head->next; node != head; node = node->next ) {
		num++;
	}

	return num;
}


/** \brief Limpa a lista
* \note Se o nó é o cabeça (nó head), o método limpa a lista
* \note Se o nó não é o cabeça (nó head), o método simplesmente retira o nó da lista.
*/
template< class ItemType >
void CLinkedList<ItemType>::clear() {
	if ( head == this ) {
		while( next != this ) {
			next->remove();
		}
	} else {
		remove();
	}
}


/** 
* \brief Remove um node da lista	
*/
template< class ItemType >
void CLinkedList<ItemType>::remove() {
	prev->next = next;
	next->prev = prev;

	next = this;
	prev = this;
	head = this;
}

/*
Places the node before the existing node in the list.  If the existing node is the head,
then the new node is placed at the end of the list.
*/

/**
* CLinkedList<ItemType>::insertBefore
* \brief coloca o novo nó antes do nó atual na lista.
* \brief Se o nó atual for o cabeça, o novo nó é colocado no final da lista 
* \param node: O nó a ser inserido
*/

template< class ItemType >
void CLinkedList<ItemType>::insertBefore( CLinkedList &node ) {
	remove();

	next		= &node;
	prev		= node.prev;
	node.prev	= this;
	prev->next	= this;
	head		= node.head;
}

/*
CLinkedList<ItemType>::insertAfter
Places the node after the existing node in the list.  If the existing node is the head,
then the new node is placed at the beginning of the list.
*/
/** \brief coloca o nó depois do nó atual da lista
* \note se o nó atual for o cabeça, o novo nó é colocado no início da lista
* \param O nó a ser inserido
*/
template< class ItemType >
void CLinkedList<ItemType>::insertAfter( CLinkedList &node ) {
	remove();

	prev		= &node;
	next		= node.next;
	node.next	= this;
	next->prev	= this;
	head		= node.head;
}

/*
CLinkedList<ItemType>::addToEnd
Adds node at the end of the list
*/
/** \brief adiciona o nó no final da lista
* \param o nó a ser inserido
*/
template< class ItemType >
void CLinkedList<ItemType>::addToEnd( CLinkedList &node ) {
	insertBefore( *node.head );
}

/*
CLinkedList<ItemType>::addToFront
Adds node at the beginning of the list
*/
/** \brief  adiciona o nó no início da lista
* \param node: o nó a ser inserido
*/
template< class ItemType >
void CLinkedList<ItemType>::addToFront( CLinkedList &node ) {
	insertAfter( *node.head );
}

/*
CLinkedList<ItemType>::getListHead
Returns the head of the list.  If the node isn't in a list, it returns
a pointer to itself.
*/
/** \brief retorna o nó cabeça da lista
* \return um ponteiro para o nó cabeça
*/
template< class ItemType >
CLinkedList<ItemType> *CLinkedList<ItemType>::getListHead() const {
	return head;
}

/*
CLinkedList<ItemType>::getNext
Returns the next object in the list, or NULL if at the end.
*/
/** \brief retorna o próximo objeto na lista, ou NULO caso esteja no final da lista
* \return Um ponteiro para o objeto do próximo nó
*/
template< class ItemType >
ItemType *CLinkedList<ItemType>::getNext() const {
	if ( !next || ( next == head ) ) {
		return NULL;
	}
	return next->owner;
}

/*
CLinkedList<ItemType>::getPrev
Returns the previous object in the list, or NULL if at the beginning.
*/
/** \brief retorna o objeto anterior
* \return Um ponteiro para  o objeto do nó anteior
*/
template< class ItemType >
ItemType *CLinkedList<ItemType>::getPrev() const {
	if ( !prev || ( prev == head ) ) {
		return NULL;
	}
	return prev->owner;
}

/*
CLinkedList<ItemType>::getNextNode
Returns the next node in the list, or NULL if at the end.
*/
/** \brief retorna op próximo nó
* \return Um ponteiro para o próximo nó da lista
*/
template< class ItemType >
CLinkedList<ItemType> *CLinkedList<ItemType>::getNextNode() const {
	if ( next == head ) {
		return NULL;
	}
	return next;
}

/*
CLinkedList<ItemType>::getPrevNode
Returns the previous node in the list, or NULL if at the beginning.
*/
/** \brief retorna o nó anterior da lista
* \return um ponteiro para o nó anterior
*/
template< class ItemType >
CLinkedList<ItemType> *CLinkedList<ItemType>::getPrevNode() const {
	if ( prev == head ) {
		return NULL;
	}
	return prev;
}

/*
CLinkedList<ItemType>::getOwner
Gets the object that is associated with this node.
*/
/** \brief retorna o objeto associaso ao nó atual
*  \ return Um ponteiro para o objeto em questão
*/
template< class ItemType >
ItemType *CLinkedList<ItemType>::getOwner() const {
	return owner;
}

/*
CLinkedList<ItemType>::setOwner
Sets the object that this node is associated with.
*/
/** \brief configura o objeto ao qual este nó está associado
* \param Up ponteiro para o objeto em questão
*/
template< class ItemType >
void CLinkedList<ItemType>::setOwner( ItemType *object ) {
	owner = object;
}

#endif /* !__LINKLIST_H__ */
