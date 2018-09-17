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


#ifndef __SGF_STACK_H__
#define __SGF_STACK_H__

#include <stdio.h>
#include <stddef.h>
#include "../SGF_Config.h"


namespace SGF {
/**
 * \class CStack
 *
 * \ingroup SGF_Data_Structures
 *
 * \brief Cria uma Lista Ligada
 *
 * \note ItemType é uma estrutura ou classe, para a qual se deseja criar a fila
 * \note ItemType precisa ter uma variável membro ponteiro do tipo ItemType chamada next, que irá apontar
 * \note para o próximo item da pilha
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 20 de Janeiro de 2013
 */


//#define CStackTemp( ItemType, next )		CStack<ItemType, (int)&(((ItemType*)NULL)->next)>

template< class ItemType>
class CStack {
public:
	CStack( void );
	void	addItem( ItemType *element );
	ItemType *	getItem( void );

private:
	ItemType *	m_pTop;
	ItemType *	m_pBottom;
	int		m_iNextOffset;
};

#define NEXT_POINTER_STACK( element )		(*(ItemType**)(((SGF_Byte*)element)+m_iNextOffset))
//! m_iNextOffset is the offset to the nxt pointer inside he ItemType structure
//! offsetof( ItemType, next )
template< class ItemType>
CStack<ItemType>::CStack( void ) {
	m_pTop = m_pBottom = NULL;
	m_iNextOffset = offsetof( ItemType, next );
}

template< class ItemType>
void CStack<ItemType>::addItem( ItemType *element ) {
	NEXT_POINTER_STACK(element) = m_pTop;
	m_pTop = element;
	if ( !m_pBottom ) {
		m_pBottom = element;
	}
}

template< class ItemType>
ItemType *CStack<ItemType>::getItem( void ) {
	ItemType *element;

	element = m_pTop;
	if ( element ) {
		m_pTop = NEXT_POINTER_STACK(m_pTop);
		if ( m_pBottom == element ) {
			m_pBottom = NULL;
		}
		NEXT_POINTER_STACK(element) = NULL;
	}
	return element;
}
} //end SGF
#endif /* !__SGF_STACK_H__ */
