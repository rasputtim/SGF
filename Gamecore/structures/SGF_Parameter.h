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
#ifndef _S_G_F_parameter_h
#define _S_G_F_parameter_h
#include "../SGF_Config.h"
#include "../util/SGF_Pointer.h"

/* parâmetros devem ser utilizados para controlar a dimensão dinâmica dos valores.
 * valores podem ser inseridos na dimensão actual e são automaticamente retirados
 * Após o retorno da função.
 * É similar a 'parameters' na linguagem Racket (http://racket-lang.org/)
 *
 * Esta classe não é thread safe ainda.
 */

#include <vector>


using namespace std;
namespace SGF{
namespace Util{


/**
 * \class CParameter
 *
 * \ingroup SGF_Data_Structures
 *
 * \brief Template para uma Pilha de tipo Genérico
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \note sintaxe:  template <> vector<int> Parameter<int>::stack;
 * semelhante a 'parameters' no Racket.
 * http://docs.racket-lang.org/reference/eval-model.html#%28part._parameter-model%29
 * não é thread safe.
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
template <class Value>
class  SGE_API CParameter{
public:
    /** \brief adiciona um novo valor à pilha
	* \param what: objeto a ser adicionado à pilha
	*/
    CParameter(CParameter & parent, const Value & what):
    stack(parent.stack),
    items(0){
        push(what);
    }

    CParameter(CParameter & parent):
    stack(parent.stack),
    items(0){
    }

    CParameter():
    items(0){
        stack = new vector<Value>();
    }


    ~CParameter(){
        for (int i = 0; i < items; i++){
            if (stack->size() > 0){
                stack->pop_back();
            }
        }
    }

	/** \brief adiciona um valor na pilha
	* \param what: objeto a ser adicionado na pilha
	*/
    void push(const Value & what){
        items += 1;
        stack->push_back(what);
    }

    /** \brief pega o valor atual */
    Value current(){
        if (stack->size() > 0){
            return stack->back();
        }
        return Value();
    }

 CReferenceCount<vector<Value> > stack;

protected:
    /** número de coisas adicionadas à pilha por este objeto
	* \note este não é o número de itens na fila, porque se há multiplos
	* objetos CParameter, então cada um deles pode inserir 1 objeto. Assim
	* a pilha terá vários objetos, mas cada CParameter terá um item = 1.
	*/


 int items;
};

}
  } //end namespace SGF
#endif
