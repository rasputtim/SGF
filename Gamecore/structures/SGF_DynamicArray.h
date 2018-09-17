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
#ifndef _S_G_F_DYNAMIC_ARRAY_h
#define _S_G_F_DYNAMIC_ARRAY_h


#include <iostream>
#include <cstdlib>
#include "../SGF_Config.h"
#include "../util/SGF_Pointer.h"
#include "../util/SGF_Debug.h"
#include "../../ExternalLibs/SDL2/include/SDL.h"
#include "../exceptions/SGF_Error.h"

using namespace ::std;
namespace SGF {
/**
 * \class CDynamicArray
 *
 * \ingroup SGF_Data_Structures
 *
 * \brief Array Dinâmico
 *
 * É bom quando você sabe o tamanho do array
 * Não funciona como ao container Vector que você pode adicionar alementos
 * mas é muito mais rápido
 * \note é possível um resize do array dinâmicamente
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
template <typename Type>
class  SGE_API CDynamicArray {
protected:
unsigned int _capacity;
unsigned int sizeX;
Type *_data;
Type *ITEN_NULL;


public:
	typedef Type *iterator;
    typedef const Type *const_iterator;

CDynamicArray():
_capacity(0),
sizeX(0),
_data(0),
ITEN_NULL(0) {};

CDynamicArray<Type>(const CDynamicArray<Type>& array) :
_capacity(0),
sizeX(0),
_data(0),
ITEN_NULL(0){
      sizeX = array.sizeX;
	  _capacity = sizeX;
      _data = new Type[_capacity];
      for(unsigned int i = 0; i < sizeX; i++)
        _data[i] = array._data[i];
}

CDynamicArray(unsigned int size):
_capacity(size + 128),
sizeX(size),
_data(0),
ITEN_NULL(0)
{
  try {
	_data = new Type [_capacity] ;
	if (ITEN_NULL) {
		for (int i =0; i < _capacity; i++) {
		_data[i] = *ITEN_NULL;
		}
    }else{
			for (unsigned int i =0; i < _capacity; i++) {
			memset(&_data[i],0,(sizeof(Type)));
			}
		}

  }catch (bad_alloc& xa) { // Catch block, for exceptions
	throw CGeneralError("Alocation Memory Error",__FUNCTION__,__LINE__);
  }
}

// Inicializa o item que significa valor nulo para Types que não possuem default construtor
CDynamicArray(unsigned int size, Type * Nulo):
_capacity(size + 128),
sizeX(size),
ITEN_NULL(Nulo),
_data(0)
{
  try {
	_data = new Type [_capacity] ;
	if (ITEN_NULL) {
		for (int i =0; i < _capacity; i++) {
		_data[i] = *ITEN_NULL;
		}
    }else{
			for (unsigned int i =0; i < _capacity; i++) {
			memset(&_data[i],0,(sizeof(Type)));
			}
		}
  }catch (bad_alloc& xa) { // Catch block, for exceptions
	throw CGeneralError("Alocation Memory Error",__FUNCTION__,__LINE__);
  }
}

/**
 * @brief inicializa o objeto que tem o valor de nulo
 * @param nulo objeto que tem o valor de nulo
 */
void setNULL (Type *nulo) {ITEN_NULL=nulo;};

~CDynamicArray() {
		if (_data) delete [] _data ;
		if (ITEN_NULL) delete ITEN_NULL;
}

/**
 * @brief aumenta o tamanho do array, criando elementos vazios e copiando os já existentes
 *
 * @param newsize o novo tamanho do array
 * \note não diminui o array
 */
void resize(unsigned int newsize) {
	if (newsize <= _capacity) 	throw CGeneralError("Can't Resize to less elements",__FUNCTION__,__LINE__);
	if(_data==0) {
		//int i = 0;
		_capacity = newsize + 128;
		if (_data) delete [] _data ;

		try {
		_data = new Type [_capacity] ;
		if (ITEN_NULL) {
			for (unsigned int i =0; i < _capacity; i++) {
			_data[i] = *ITEN_NULL;
			}
		}else{
			for (unsigned int i =0; i < _capacity; i++) {
			memset(&_data[i],0,(sizeof(Type)));
			}
		}
		}catch (bad_alloc& xa) { // Catch block, for exceptions
//		Debug::debug(Debug::error,__FUNCTION__) << "Allocation error\n";

		throw CGeneralError("Alocation Memory Error",__FUNCTION__,__LINE__);
		}
	}else {

		 try {
			 _capacity = newsize + 128;
			 //cria um novo array
			//Type *old_data = _data;
		    Type *new_data = new Type [_capacity] ;

			if (new_data!=NULL)
			{
			//copia os elementos
			for(unsigned int i = 0; i <sizeX; i++) {
				new_data[ i ] = _data[ i ];
			}
			if (ITEN_NULL) {
				for (unsigned int i =sizeX; i < _capacity; i++) {
				new_data[i] = *ITEN_NULL;
				}
			}else{
				for (unsigned int i =sizeX; i < _capacity; i++) {
				memset(&new_data[i],0,(sizeof(Type)));
				}
			}
			delete [] _data;
			_data = NULL;
			_data = new_data;
			}
			}catch (bad_alloc& xa) { // Catch block, for exceptions
			throw CGeneralError("Alocation Memory Error",__FUNCTION__,__LINE__);
		  }


	}
}

/**
 * @brief operador de cópia do array
 *
 * @param ob objeto a ser copiado
 */
 CDynamicArray &operator=(CDynamicArray &ob)
{
  int i;

  if (_data)
      delete [] _data;
      sizeX = ob.sizeX;
      _capacity = ob._capacity;
      _data = new Type[_capacity];
	  ITEN_NULL=ob.ITEN_NULL;

  for(i = 0; i <sizeX; i++) {

	  _data[ i ] = ob._data[ i ];

  }
  for(i = sizeX; i <_capacity; i++) {

	  memset(&_data[i],0,(sizeof(Type)));

  }
  return *this;
}


/**
 * @brief Overload do operador []
 *
 * @param i indice do elemento [i]
 */
Type& operator[](unsigned int i)
	{
	  if(i <0  || i>=sizeX) {
//		Debug::debug(Debug::error,__FUNCTION__) << "\nIndex value of ";
//		Debug::debug(Debug::error,__FUNCTION__)  << i << " is out-of-bounds.\n";
		//todo: retornar um elemento que signifique nulo ou o ultimo elemento
		throw CGeneralError("Out of band Element",__FUNCTION__,__LINE__);
	  }
	  return _data[ i ];
	};

const	Type& operator[](unsigned int i) const
	{
	  if(i <0  || i>=sizeX) {
//		Debug::debug(Debug::error,__FUNCTION__) << "\nIndex value of ";
//		Debug::debug(Debug::error,__FUNCTION__)  << i << " is out-of-bounds.\n";
		//todo: retornar um elemento que signifique nulo ou o ultimo elemento
		throw CGeneralError("Out of band Element",__FUNCTION__,__LINE__);
	  }
	  return _data[ i ];
	};

/**
 * @brief adiciona um elemento no final do array
 *
 * @param element elemento a adicionar
 */
void push_back(const Type& element)
{
    if (sizeX >= _capacity || _data==NULL) resize(sizeX + 1);
     _data[sizeX] = element;
	sizeX++;

};

/**
 * @brief adiciona um array no final deste array
 *
 * @param array: Array a adicionar
 */
void push_back(const CDynamicArray<Type>& array)
{
      if (sizeX + array.sizeX > _capacity) resize(sizeX + array.sizeX);
      for(int i = 0; i < array.sizeX; i++)
        _data[sizeX++] = array._data[i];
}
/**
 * @brief adiciona um elemento no final do array se ele for unico
 *
 * @param element: elemento a adicionar
 */
void push_back_unique(const Type& element)
{
      if(!contains(element))
      {
        if (sizeX > _capacity) resize(sizeX + 1);
        _data[sizeX++] = element;
      }
}


/**
 * @brief insere um elemento numa certa posição
 *
 * @param offset a posição onde inserir o elemento
 * @param e o elemento a ser inserido
 */
void insert_at(int offset, Type e){
	if (offset > sizeX || _capacity==0 || offset <0) throw CGeneralError("offset element does not exist",__FUNCTION__,__LINE__);


	try {
        Type *temp;
		if (sizeX>= _capacity) {
			//não usa resize aqui para não copiar os elementos duas vezes
			//cria um novo array
			_capacity = sizeX +128;
			temp = new Type [_capacity] ;
			//copia os elementos
			for(int i = 0; i < offset; i++) {
				temp[ i ] = _data[ i ];
			}
			temp[ offset ]=e;
			for(int i = offset; i < sizeX; i++) {
				temp[ i+1 ] = _data[ i ];
			}
			delete [] _data;
			_data = temp;
	        sizeX++;
		}else {

			//copia os elementos
			for(int i = sizeX; i >= offset; i--) {
				_data[ i+1 ] = _data[ i ];
			}
			temp[ offset ]=e;

		}
			}catch (bad_alloc& xa) { // Catch block, for exceptions
			throw CGeneralError("Alocation Memory Error",__FUNCTION__,__LINE__);
		  }

};

/**
 * @brief verifica se existe um determinado elemento no array
 *
 * @param key: elemento a ser encontrado
 * @return true: se o elemento existir, caso contrario retorna false
 */
bool contains(const Type &key) const
{
      for (const_iterator i = begin(); i != end(); ++i) {
        if (*i == key)
          return true;
      }
      return false;
}

/**
 * @brief troca um elemento do array
 *
 * @param offset a posição do elemento a ser torcado
 * @param e o novo elemento
 */
void replaceElement(int offset, Type e){
	if (offset > _capacity || _capacity==0) throw CGeneralError("element does not exist",__FUNCTION__,__LINE__);
	//replace
	return _data[ offset ]=e;

};

/**
 * @brief pega um elemento do array
 *
 * @param offset a posição do elemento
 */
Type getElement(int offset) const {
	if (offset > _capacity || _capacity==0) throw CGeneralError("element does not exist",__FUNCTION__,__LINE__);

	return _data[ offset ];
};



/**
 * @brief remove um elemento do array
 * @note nao diminui a capacidade do array
 * @param offset a posição do elemento a remover
 */
void removeElement(int offset) {
	if (offset > sizeX || sizeX==0) throw CGeneralError("element does not exist",__FUNCTION__,__LINE__);

		for(int i = offset+1; i < sizeX; i++) {

					_data[ i-1 ] = _data[ i ];
		}

	sizeX--;
};

/**
 * @brief remove o último elemento do array
 *
 */
void removeLast() {
	if (sizeX==0) throw CGeneralError("element does not exist",__FUNCTION__,__LINE__);

	if(ITEN_NULL)
		_data[sizeX-1]=*ITEN_NULL;
	sizeX--;
};

/**
 * @brief remove o primeiro elemento do array
 *
 */
void removeFirst() {
	if (sizeX<=0) throw CGeneralError("element does not exist",__FUNCTION__,__LINE__);


	//copia os elementos
	for(int i = 0; i < sizeX-1; i++) {
				_data[ i ] = _data[ i+1 ];
	}
	if(ITEN_NULL)
		_data[sizeX-1]=*ITEN_NULL;

	sizeX--;
};

/**
 * @brief o número de elementos no array
 *
 */
int size() {return sizeX;};


/**
 * @brief o tamanho máximo do array
 *
 */
int capacity() {return _capacity;};
/**
 * @brief limpa o array, deleta os dados e reseta as variáveis
 * \brief nao limpa i Iten NuLL
 *
 */
void clear()
    {
      if(_data)
      {
        delete [] _data;
        _data = 0;
      }
      sizeX = 0;
      _capacity = 0;

    }

bool isEmpty() const
    {
      return (sizeX == 0);
    }

iterator begin()
    {
      return _data;
    }

iterator end()
    {
      return _data + sizeX;
    }

const_iterator begin() const
    {
      return _data;
    }

const_iterator end() const
    {
      return _data + sizeX;
    }



}; // fim do template


typedef SGF::CDynamicArray<int>   IntArray;
typedef SGF::CDynamicArray<bool>  BoolArray;
typedef SGF::CDynamicArray<Uint8> ByteArray;

/**
 * \class CDynamic2DArray
 *
 * \ingroup SGF_Util
 *
 * \brief Array Dinâmico de duas dimenssões
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
template <typename Type>
class  SGE_API CDynamic2DArray {
  unsigned int sizeX;
  unsigned int sizeY;
  Type **dynamicArray;
public:

CDynamic2DArray():
sizeX(0),
sizeY(0),
dynamicArray(NULL) {};

CDynamic2DArray(unsigned int rows,unsigned int columns):
sizeX(rows),
sizeY(columns)
{
	int i = 0;
	int ar_count=0;
  try {
	dynamicArray = new Type *[rows] ;
	ar_count++;
	for( i = 0 ; i < rows ; i++ ) {
	  dynamicArray[i] = new Type[columns];
	}

  }catch (bad_alloc& xa) { // Catch block, for exceptions
	//Debug::debug(Debug::error,__FUNCTION__) << "Allocation error\n";
    switch (ar_count){
	case 0: break;
	case 1:   for (i = i - 1; i >= 0; i--){ //Count down from the highest value of i that was reached before the exception
            if (dynamicArray[i]) delete[] dynamicArray[i];
         } // End for i
           delete [] dynamicArray;
		break;

	default : break;
	}
	throw CGeneralError("Alocation Memory Error",__FUNCTION__,__LINE__);
  }
};

~CDynamic2DArray() {
	for( unsigned int i = 0 ; i < sizeX ; i++ ) if (dynamicArray[i]) delete [] dynamicArray[i] ;
	if (dynamicArray) delete [] dynamicArray ;
	};
void resize(unsigned int rows,unsigned int columns) {
	int ar_count=0;
	unsigned int i = 0;
	for( i = 0 ; i < sizeX ; i++ ) if (dynamicArray[i]) delete [] dynamicArray[i] ;
	if (dynamicArray) delete [] dynamicArray ;
	sizeX= rows;
	sizeY= columns;
	try {
	dynamicArray = new Type *[sizeX] ;
	ar_count ++;
	for( i = 0 ; i < sizeX ; i++ ) dynamicArray[i] = new Type[sizeY];
	}catch (bad_alloc& xa) { // Catch block, for exceptions
	//Debug::debug(Debug::error,__FUNCTION__) << "Allocation error\n";
    switch (ar_count){
	case 0: break;
	case 1:   for (i = i - 1; i >= 0; i--){ //Count down from the highest value of i that was reached before the exception
            if (dynamicArray[i]) delete[] dynamicArray[i];
         } // End for i
           if (dynamicArray) delete [] dynamicArray;
		break;

	default : break;
	}
	throw CGeneralError("Alocation Memory Error",__FUNCTION__,__LINE__);
  }

}
  CDynamic2DArray &operator=(CDynamic2DArray &ob)
{
  unsigned int i,y;
  int ar_count=0;
  if (sizeX==0 && sizeY == 0) {
	  sizeX= ob.sizeX;
	  sizeY= ob.sizeY;
	  try {
	  dynamicArray = new Type *[sizeX] ;
	  ar_count++;
	  for( unsigned int i = 0 ; i < sizeX ; i++ ) dynamicArray[i] = new Type[sizeY];
	  	}catch (bad_alloc& xa) { // Catch block, for exceptions
		//Debug::debug(Debug::error,__FUNCTION__) << "Allocation error\n";
		switch (ar_count){
		case 0: break;
		case 1:   for ( unsigned int i = i - 1; i >= 0; i--){ //Count down from the highest value of i that was reached before the exception
				if (dynamicArray[i]) delete[] dynamicArray[i];
			 } // End for i
			   if (dynamicArray) delete [] dynamicArray;
			break;

		default : break;
		}
		throw CGeneralError("Alocation Memory Error",__FUNCTION__,__LINE__);
		}
  }
  if(sizeX!=ob.sizeX ||sizeY!=ob.sizeY ) {
    //Debug::debug(Debug::error,__FUNCTION__)  << "Cannot copy arrays of differing sizes!\n";
    exit(1);
  }

  for(i = 0; i <sizeX; i++) {
	  for (y=0; y< sizeY;y++) {
	  dynamicArray[ i ][ y ] = ob.dynamicArray[ i ][ y ];
	  }
  }
  return *this;
}

  // Overload []
	Type * operator[](unsigned int i)
	{
	  if(i <0  || i>sizeX) {
		//Debug::debug(Debug::error,__FUNCTION__) << "\nIndex value of ";
		//Debug::debug(Debug::error,__FUNCTION__)  << i << " is out-of-bounds.\n";
		return NULL;
	  }
	  return dynamicArray[ i ];
	};


};

/**
 * \class CDynamic3DArray
 *
 * \ingroup SGF_Util
 *
 * \brief Array Dinâmico de trÊs dimenssões
 *
 * \note não testado ainda
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
template <typename Type>
class  SGE_API CDynamic3DArray {
  Type ***dynamicArray;
unsigned int sizeX;
unsigned int sizeY;
unsigned int sizeZ;
public:
	CDynamic3DArray():
	sizeX(0),
	sizeY(0),
	sizeZ(0),
dynamicArray(NULL)
{}
	CDynamic3DArray(unsigned int rows,unsigned int columns,unsigned int depth):
sizeX(rows),
sizeY(columns),
sizeZ(depth)
{
		//_my2Darray.resize(rows,columns);
		int ar_count=0;
		try{
		// Allocate memory
		  dynamicArray = new Type**[rows];
		  ar_count++;
		  for (int i = 0; i < sizeX; ++i) {
			dynamicArray[i] = new Type*[columns];

			for (int j = 0; j < sizeY; ++j)
			  dynamicArray[i][j] = new Type[depth];
		  }
  	  	}catch (bad_alloc& xa) { // Catch block, for exceptions
		//Debug::debug(Debug::error,__FUNCTION__) << "Allocation error\n";
		switch (ar_count){
		case 0: break;
		case 1:   for (int i = i - 1; i >= 0; i--){ //Count down from the highest value of i that was reached before the exception

			for (int j = j-1; j >=0; j--) if(dynamicArray[i][j]) delete [] dynamicArray[i][j];
			if (dynamicArray[i]) delete[] dynamicArray[i];

			} // End for i
			   delete [] dynamicArray;
			break;

		default : break;
		}
		throw CGeneralError("Alocation Memory Error",__FUNCTION__,__LINE__);
		}
}

void resize(unsigned int rows,unsigned int columns,unsigned int depth) {
	// De-Allocate memory to prevent memory leak
  for (int i = 0; i < sizeX; ++i) {
    for (int j = 0; j < sizeY; ++j)
      if(dynamicArray[i][j]) delete [] dynamicArray[i][j];

    if (dynamicArray[i]) delete [] dynamicArray[i];
  }
  if (dynamicArray) delete [] dynamicArray;
	sizeX= rows;
	sizeY= columns;
	sizeZ= depth;
	int ar_count=0;
	try {
		dynamicArray = new Type**[rows];
		ar_count++;
		  for (int i = 0; i < sizeX; ++i) {
			dynamicArray[i] = new Type*[columns];

			for (int j = 0; j < sizeY; ++j)
			  dynamicArray[i][j] = new Type[depth];
		  }
	}catch (bad_alloc& xa) { // Catch block, for exceptions
		//Debug::debug(Debug::error,__FUNCTION__) << "Allocation error\n";
		switch (ar_count){
		case 0: break;
		case 1:   for (int i = i - 1; i >= 0; i--){ //Count down from the highest value of i that was reached before the exception

			for (int j = j-1; j >=0; j--) if(dynamicArray[i][j]) delete [] dynamicArray[i][j];
			if (dynamicArray[i]) delete[] dynamicArray[i];

			} // End for i
			   delete [] dynamicArray;
			break;

		default : break;
		}
		throw CGeneralError("Alocation Memory Error",__FUNCTION__,__LINE__);
		}


}
  // Assign values
 // p2DArray[0][0][0] = 3.6;
 // p2DArray[1][2][4] = 4.0;
~CDynamic3DArray(){
  // De-Allocate memory to prevent memory leak
  for (int i = 0; i < sizeX; ++i) {
    for (int j = 0; j < sizeY; ++j)
      if(dynamicArray[i][j]) delete [] dynamicArray[i][j];

    if (dynamicArray[i]) delete [] dynamicArray[i];
  }
  if (dynamicArray)delete [] dynamicArray;
}

  CDynamic3DArray &operator=(CDynamic3DArray &ob)
{
  int i,y;
  if (sizeX==0 && sizeY == 0 && sizeZ == 0) {
  sizeX= ob.sizeX;
  sizeY= ob.sizeY;
  sizeZ= ob.sizeZ;
  int ar_count=0;
  try{
  	dynamicArray = new Type**[sizeX];
	  for (int i = 0; i < sizeX; ++i) {
		dynamicArray[i] = new Type*[sizeY];

		for (int j = 0; j < sizeY; ++j)
		  dynamicArray[i][j] = new Type[sizeZ];
	  }


  }catch (bad_alloc& xa) { // Catch block, for exceptions
		//Debug::debug(Debug::error,__FUNCTION__) << "Allocation error\n";
		switch (ar_count){
		case 0: break;
		case 1:   for (i = i - 1; i >= 0; i--){ //Count down from the highest value of i that was reached before the exception

			for (int j = j-1; j >=0; j--) if(dynamicArray[i][j]) delete [] dynamicArray[i][j];
			if (dynamicArray[i]) delete[] dynamicArray[i];

			} // End for i
			   delete [] dynamicArray;
			break;

		default : break;
		}
		throw CGeneralError("Alocation Memory Error",__FUNCTION__,__LINE__);
		}
  }
  if(sizeX!=ob.sizeX ||sizeY!=ob.sizeY ||sizeZ!=ob.sizeZ ) {
	//  Debug::debug(Debug::error,__FUNCTION__) << "Cannot copy arrays of differing sizes!\n";
    exit(1);
  }

  for(int i = 0; i <sizeX; i++) {
	  for (int y=0; y< sizeY;y++) {
		  for (int z=0; z< sizeZ;z++) {
			dynamicArray[ i ][ y ] [z]= ob.dynamicArray[ i ][ y ][z];
		  }
	  }
  }
  return *this;
}

  // Overload []
	Type * operator[](int i)
	{
	  if(i <0 || i>sizeX) {
		//Debug::debug(Debug::error,__FUNCTION__)  << "\nIndex value of ";
		//Debug::debug(Debug::error,__FUNCTION__)  << i << " is out-of-bounds.\n";
		exit(1);
	  }
	  return dynamicArray[ i ];
	};

private:
//	CDynamic2DArray<Type> _my2Darray;

};


} //end namespace SGF

#endif
