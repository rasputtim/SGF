
/*
  SGF - Salvat Game Fabric  (https://sourceforge.net/projects/sgfabric/)
  Copyright (C) 2010-2011 Salvatore Giannotta Filho <a_materasu@hotmail.com>

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

//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#ifndef _S_G_F_Binary_CHeap_Generic_
#define _S_G_F_Binary_CHeap_Generic_

/*

Heaps

 Outro tipo de árvore binária especial é chamada de heap. A fim de entender o que é um amontoado, 
 é preciso primeiro definir uma árvore binária completa e plena. 
 Em uma árvore binária completa, todos os nós são ou um pai com dois filhos, ou uma folha. 
 Em uma árvore binária completa, todos os níveis, exceto o último deve ser completamente preenchido.
 No último nível, todos os nós devem ser preenchidos a partir do lado esquerdo, sem espaçamento entre eles, 
 no entanto, não têm de ser preenchidos até o fim.

 Um heap é uma árvore binária completa, que é parcialmente ordenado ou com o max heap ou heap min-propriedades.
 Ou seja, se uma pilha é um max-heap, então os filhos de cada nó ter um valor menor do que o nó. 
 Em um heap min-, os filhos de cada nó são maiores do que o próprio nó. 
 Com tal configuração, a raiz principal tem sempre tanto o valor mais alto ou mais baixo na árvore.
 Para fins de demonstração, vamos mostrar como implementar um max-heap, como também uma parte importante do algoritmo heapsort, 
 que será posteriormente coberto. 
 [É fácil alterar o código para funcionar como um heap min-mudando os operadores relacionais entre os valores de nó]. 
 A max-heap normalmente usado para manter filas de prioridade. 
 Filas de prioridade armazenar valores e liberar o objeto com a mais alta "prioridade" (ou valor), quando necessário. 
 Por exemplo, um valor é associado a uma determinada tarefa em um programa, 
 colocado em uma estrutura deste tipo, e depois executado com base em sua posição.
 Uma vez que uma pilha deve respeitar a propriedade árvore completa, 
 fórmulas simples podem ser libraryeloped para encontrar a posição lógica dos filhos de um nó pai e 
 dada a posição do próprio nó. Por isso é muito fácil e eficiente de implementar uma pilha usando arrays, 
 e é feito na maioria das vezes, mesmo se alocação dinâmica de memória está disponível.
Em uma implementação de matriz, devemos alocar uma certa quantidade de espaço de memória que podem ser 
usados ​​para o heap. O espaço não pode ser usado para cima, e é, portanto, um desperdício de memória. 
Outras vezes, talvez seja necessário adicionar mais nós ao monte do que a memória alocada para o permite.
No entanto, costumamos atribuir mais espaço do que pensamos pode ser necessária a fim de assegurar a pilha 
é utilizável. Se temos uma árvore de estruturas muito grandes, este espaço pode ser significativo. 
No entanto, este é o preço que paga sempre para maior eficiência. 
Deve observar, porém, que não temos mais três ponteiros para cada nó da árvore (à esquerda, pai, direita), 
que pegou um monte de espaço na implementação de memória dinâmica. 
A posição lógica de um nó em uma pilha corresponde ao índice da posição do nó de matriz, 
tornando assim muito fácil de acessar qualquer nó. A implementação genérica é mostrada abaixo.
*/



#include "../exceptions/all.h"

/**
 * \class CMaxHeap
 *
 * \ingroup SGF_Util
 * 
 * \brief Heap Binário Genérico
 *
 * \ note este código foi adaptado e alterado da seguinte base :http://library.thinkquest.org/C005618/text/heaps.htm
 * \ note ItemType deve ter implementado o operador assignment para este template funcionar
 *
 * \author (last to touch it) $Autor: Salvatore Giannotta Filho $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: a_materasu@hotmail.com
 *
 * Created on: 14 de Janeiro de 2012
 */

 template <class ItemType>
 class CMaxHeap
 {
 public:
    CMaxHeap(int Size=0);
	CMaxHeap();
	~CMaxHeap();
	void init(int toSize);
	void resize(int newSize);
    int left(int) const;
    int right(int) const;
    int parent(int) const;
    void insert(const ItemType&);
    ItemType remove_max();
    bool IsEmpty() const;
    bool IsFull() const;
    int count() const;
    ItemType value(int) const;
	ItemType swap(int pos, int new_pos);
 private:
    ItemType *_array;
    int elements; //how many elements are in the CMaxHeap
    void ReHeap(int);
	int swap_pos;
 };

 //default constructor - initialize private variables
 template <class ItemType>
 CMaxHeap<ItemType>::CMaxHeap(int size):
 _array(0),
 swap_pos(0),
 elements(0)
 {
 }

 template <class ItemType>
 CMaxHeap<ItemType>::CMaxHeap(int size):
 elements(0),
 swap_pos(size+1)
 {
    try {
	_array = new ItemType *[size+1] ;
  
	}catch (bad_alloc& xa) { // Catch block, for exceptions
	throw CGeneralError("Alocation Memory Error",__FUNCTION__,__LINE__);
	}
   
 }

 template <class ItemType>
 CMaxHeap<ItemType>::~CMaxHeap()
 {
   if (_array) delete [] _array;   
 }

 /** quando o heap for construido com o construtor default
 * será presico inicialiar o heap com um determinado tamanho.
 * este método realiza esta função, inicializando o heap
 */
template <class ItemType>
void  CMaxHeap<ItemType>::init(int toSize){

}
/** se o heap estiver cheio, pode ter seu tamanho alterado com este método
* \note não permite diminuir o heap
*/
template <class ItemType>
void  CMaxHeap<ItemType>::resize(int newSize){
	if (size==0) {
		init(newSize);
		return;
	}else if ( newSize > size) {
		ItemType *_new_array;
		int atualSize=size+1; // adiciona um elemento para swap
		// cria um novo heap com o tamanho certo
		try {
			_new_array = new ItemType *[newSize+1] ;
  
		}catch (bad_alloc& xa) { // Catch block, for exceptions
			throw CGeneralError("Alocation Memory Error",__FUNCTION__,__LINE__);
		}
		// copia os elementos do heap anterior para o novo heap
		for (int i=0; i < atualSize ; i++) {
			_new_array[i]=_array[i];
		}
		// deleta o heap anterior
		if(_array) delete [] _array;
	}else throw CGeneralError("Operation not allowwed to resize the heap with less size",__FUNCTION__,__LINE__);
}


/**
Os métodos left(), right(), and parent() retornam o índice das posíçoes filho e pai.
Desde que o índice de cada elemento corresponde a posição lógica do elemento dentro do heap
Heap implementado em  array
If node x is in location i
root----------------------> [0]
left_child(x) -------------> 2 i + 1
right_child(x) -----------> 2i + 2
parent(x) ----------------> [i-1] / 2

*/
template <class ItemType>
 int CMaxHeap<ItemType>::left(int root) const
 {
     if(elements> (root*2)+1) throw CGeneralError("Do not have a Left Children",__FUNCTION__,__LINE__);
 	 return (root *2)+1;
	 
 }

 template <class ItemType>
 int CMaxHeap<ItemType>::right(int root) const
 {
    if(elements > (root *2)+2) throw CGeneralError("Do not have a right Children",__FUNCTION__,__LINE__);
    return (root * 2) + 2;
 }

 template <class ItemType>
 int CMaxHeap<ItemType>::parent(int child) const
 {
    if(child <= 0)throw CGeneralError("Root node does not have Parent",__FUNCTION__,__LINE__);
    return (child - 1) / 2; ok
 }
 /**
 * O método swap aceita o dois valores de um item como parâmetro
 * Ele funciona trocando os itens de posição no heap
 */
template <class ItemType>
 void CMaxHeap<ItemType>::swap(int pos, int new_pos)
 {
     if(pos <0 || pos > size || new_pos > size || new_pos < 0) CGeneralError("Out of Range swap try",__FUNCTION__,__LINE__);

	 _array[swap_pos]=_array[pos];
     _array[pos]=_array[new_pos];
     _array[new_pos]=tmp;
            
 }
 /**
 * O método insert aceita o valor de um novo item como parâmetro
 * Ele funciona inserindo o novo item no final do heap e trocando  de posição
 * com seu pai, se o pai tiver um valor menor.
 * O novo item continua subindo, trocando de posições com seus novos pais até que o valor do pai 
 * seja maior que o dele.
 */
template <class ItemType>
 void CMaxHeap<ItemType>::insert(const ItemType &item)
 {
    if(!IsFull() )throw CGeneralError("Heap is Full ",__FUNCTION__,__LINE__);
	if( _array ==NULL)throw CGeneralError("Heap is Null",__FUNCTION__,__LINE__);
	
	/** elements representa a posição no array depois da última posição ocupada, já que índice inicia no zero
	*/
	_array[elements] = item; 
    int new_pos = elements; //! índice do novo item
    elements++; //! atualiza o nro de elementos no heap
    //loop enquanto o item não se tornou o root, e enquanto seu valor é menor que o de seus pais
	while((new_pos > 0) && (_array[new_pos] > _array[parent(new_pos)])) 
    {
       swap(new_pos,parent(new_pos)); //! troca o valor do item com seu pai
       new_pos = parent(new_pos); //atualiza a posição do item
    }
 }


/** o método remove_max() remove o item com maior prioridade e retorna o seu valor.
* o item é trocado com o último item, e os elemntos é atualizado para um a menos
* O novo root pode não ter a maior prioridade, portanto o método ReHeap() é utilizado para
* inserir o novo root na sua devida posição, conservando assim a propriedade de heap
* \note O item não é fisicamente deletado, ele permanece como parte do array
* \note ele não será parte do Heap porque o número de elementos é atualizado e o heap vai até 
* elementos -1
*/
 template <class ItemType>
ItemType CMaxHeap<ItemType>::remove_max()
 {
    if(!IsEmpty() )throw CGeneralError("Heap is Empty",__FUNCTION__,__LINE__);
    if( _array ==NULL)throw CGeneralError("Heap not initialized",__FUNCTION__,__LINE__);
	
    elements--; //! atualiza a quantidade de elementos no Heap
    if(elements != 0) //! pra não deletar o root
    {
       swap(0,elements);
       ReHeap(0);
    }
    return array[elements];
 }

/** o método ReHeap verifica se o filho do root é maior que ele, no caso que o filho maior é trocado com o root
* O processo continua recursivamente até que o root se torne maior que seus dois filhos
*/
template <class ItemType>
 void CMaxHeap<ItemType>::ReHeap(int root)
 {
    int child = left(root);
     //se um filho direito existe, e é maior que o filho esquerdo, ele será utilizado
	if((array[child] < array[child+1]) && (child < (elements-1)))
       child++;
    if(array[root] >= array[child]) //! para se o root é maior que o seu maior filho.
       return;
    swap(root,child); //troca o root com seu maior filho
    ReHeap(child); //continu a o processo no novo filho do root
 }


 /** método que retorna o número de elementos no heap
 */
template <class ItemType>
 int CMaxHeap<ItemType>::count() const
 {
    return elements;
 }
 /** método que retorna o valor de um elemento no heap 
 */
 template <class ItemType>
 ItemType CMaxHeap<ItemType>::value(int pos) const
 {
	 //! pos é um índice válido?
    if (pos < elements) throw CGeneralError("Out of Range Position ",__FUNCTION__,__LINE__);
    return array[pos];
 }
 /* método que retorna se o heap está cheio
 */
 template <class ItemType<
 bool CMaxHeap<ItemType>::IsEmpty() const
 {
    return (elements <= 0);
 }

 template <class ItemType>
 bool CMaxHeap<ItemType>::IsFull() const
 {
    return (elements >= size);
 }

#endif
