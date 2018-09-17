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
#ifndef _S_G_F_gradient_h
#define _S_G_F_gradient_h
#include "../../ExternalLibs/SDL2/include/SDL.h"
#include "../SGF_Config.h"
#include "../util/SGF_Token.h"
#include "../graphics/SGF_Color.h"

using namespace std;

namespace SGF {
class Token;
namespace Effects{

/**
 * \class Gradient
 *
 * \ingroup SGF_Graphics
 * 
 * \brief Efeito de Gradiente
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */

class  SGE_API Gradient{
public:
    Gradient();
    Gradient(int singleColor);
	Gradient(Colors::ColorDefinition singleColor);
    Gradient & operator=(const Gradient & copy);

	Gradient(int size,  Colors::ColorDefinition startColor,  Colors::ColorDefinition endColor);
	Gradient(int size, int startColor, int endColor);

    Gradient(const Token * token);
	Gradient(const Gradient & copy);
	/* move to next color. update is an alias for `forward' */
    void update();
    void forward();
    void backward();
	 /* start at startColor */
    void reset();

    /* get current color */
     Colors::ColorDefinition current()const;
	 Colors::ColorDefinition current(int offset) const;

	int current_intcolor()const;
	
    virtual ~Gradient();

protected:
     Colors::ColorDefinition * colors;

    unsigned int size;
    unsigned int index;
};
/**
 * \class CGradientSimple
 *
 * \ingroup SGF_Graphics
 * 
 * \brief Efeito de Gradiente Simples com as cores
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */

class  SGE_API CGradientSimple{
public:
    CGradientSimple & operator=(const CGradientSimple & copy);

	CGradientSimple(int size,  Colors::ColorDefinition startColor,  Colors::ColorDefinition endColor);
	CGradientSimple(int size, int startColor, int endColor);

    CGradientSimple(const Token * token);
	CGradientSimple(const CGradientSimple & copy);
	/* move to next color. update is an alias for `forward' */
    void update(int x,int y);
    void forward();
    void backward();
	 /* start at startColor */
    void reset();

    /* get current color */
     Colors::ColorDefinition current()const;
	 Colors::ColorDefinition current(int offset) const;

	int current_intcolor()const;
	
    virtual ~CGradientSimple();

protected:
     Colors::ColorDefinition * colors;

    unsigned int size;
    unsigned int index;
};

}
} //end SGF
#endif
