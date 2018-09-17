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
#ifndef _S_G_E_mugen_effects_h
#define _S_G_E_mugen_effects_h

#include <string>
#include <map>
#include <vector>
#include <list>
#include "../SGF_Config.h"
#include "../graphics/all.h"

/*
#include "exception.h"

#include "../input/all.h"
#include "../util/SGF_Point.h"
#include "../util/SGF_FileSystem.h"
#include "../sprite/defs.h"
#include "mugenutil.h"


class CMugenAnimation;
class CMugenBackground;
class CMugenSprite;
class CMugenSound;
class CMugenItemContent;
class CMugenSection;
class CMugenCharacterSelect;
namespace Ast{
    class CSection;
	class CAstManager;
}
*/

using namespace std;
namespace SGF {
class CBitmap;

namespace Mugen{

enum TransType{
    None = 0,
    Add,
    Add1,
    Sub,
    AddAlpha,
    Translucent,
    /* used by the Trans controller to specify the trans should not change */
    Default
};
/**
 * \class CEffects
 *
 * \ingroup SGF_Sprite
 * 
 * \brief Efeitos que podem ser aplicados aos sprites
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CEffects{
    public:
	CEffects();
    CEffects(const CEffects & copy);
	const CEffects &operator=(const CEffects &e);
	virtual ~CEffects();

	    /* adds the mask from the parameter to this object */
        CEffects operator+(const CEffects &) const;

        /* adds the translucency */
        CEffects operator+(const TransType & translucent) const;

        /* what kind of translucency to use */
	TransType trans;

        /* translucency values */
	int alphaSource;
	int alphaDest;

            /* if the masking color should be shown or not, true is not shown */
	
	bool mask;

    /* horizontal flip */
	bool hflip;

    /* vertical flip */
	bool vflip;

        /* scale horizontally */
	double scalex;

        /* scale vertically */
	double scaley;

	double rotation;

        /* clipping. -1 means dont alter clipping */
        struct Dimension{
            Dimension():x1(-1), x2(-1), y1(-1), y2(-1){}

            int x1, x2;
            int y1, y2;
        } dimension;
		CBitmap::CFilter * filter;
};
} //End Mugen
} // end namespace SGF


#endif
