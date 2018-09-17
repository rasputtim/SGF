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
#ifndef _S_G_F_BEHAVIOR_BASE_h
#define _S_G_F_BEHAVIOR_BASE_h

#include "../SGF_Config.h"
#include "../objects/SGF_Object.h"
#include "../game/SGF_Command.h"

using namespace std;
namespace SGF {
class CObject;
/**
 * \class CBehavior
 *
 * \ingroup SGF_AI_Map
 * 
 * \brief Esta Classe Manipula a Entrada e diz ao caracter qual comando deve ser executado
 *
 * \note 
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
template <typename X>
class  SGE_API CBehavior{
public:
    CBehavior():name("Base Class behavior"){};

	
	/** Este método retorna um vetor contendo os comandos 
	* deste objeto
	*/
	virtual vector<string> currentCommands(const CTheater & stage, SGF::CObject * owner, const vector<CCommand<X>*> & commands, bool reversed)=0;

    /** Este método é chamado quando o objeto acertar (hit)
	outro objeto do jogo */
	virtual void hit(CObject * enemy){};
	

	/** Este método é chamado quando o objeto muda de direção
    * muito util para atualização o input map */
	virtual void hFlip() = 0;
	/** Este método é chamado quando o objeto muda de direção
    * muito util para atualização o input map */
	virtual void vFlip() = 0;

	virtual ~CBehavior(){};
	/*** retorna o nome do behavior */
	virtual string getName() {return name;}; 
private:
	string name;
};


/* handles input and tells the character what commands to invoke */
 
class SGE_API CBehavior2{
public:
	CBehavior2(string name):name(name){};
   
    
    /* called when the player changes direction. useful for updating
     * the input mapping.
     */
    virtual void hFlip() = 0;
	virtual void vFlip() = 0;
	string getName(){ return name;};
    /* hit someone */
	virtual void hit(SGF::CObject * enemy)=0;

	virtual ~CBehavior2(){};
	/*** retorna o nome do behavior */

private:
	string name;
};

} //end namespace SGF
#endif
