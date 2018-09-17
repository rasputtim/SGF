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
#ifndef _S_G_F_util_font_info_h
#define _S_G_F_util_font_info_h

#include <string>
#include "../SGF_Config.h"
#include "SGF_FileSystem.h"
#include "SGF_FontSystem.h"
#include "../resource/all.h"


typedef ::SGF::CFont::fonttype fonttype;

namespace SGF {

class CFont;
class CAbsoluteFontInfo;
class CRelativeFontInfo;


/**
 * \class CFontInfo
 *
 * \ingroup SGF_Util
 *
 * \brief Classe Base de Gerenciamento de informações de fontes
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CFontInfo {
    public:
	//CFontInfo();
	CFontInfo(fonttype typeOfFont);
	virtual ~CFontInfo();

        /*
	inline void set(const Filesystem::RelativePath & font, int width, int height){
	    this->font = font;
	    this->width = width;
	    this->height = height;
	}
        */

	virtual const CFont & get() const = 0;
	virtual const CFont & get(const CFont & next) const = 0;
    virtual const CFontInfo & get(const CFontInfo & next) const = 0;
	virtual bool operator==(const CFontInfo & who) const = 0;
    virtual bool operator==(const CAbsoluteFontInfo & who) const = 0;
    virtual bool operator==(const CRelativeFontInfo & who) const = 0;
        /*
	inline void setFont(const Filesystem::RelativePath & font){
	    this->font = font;
	}
        */

    virtual string getName() const = 0;
	virtual string getPath() const = 0;

	virtual const void setWidth(int width)=0;

	virtual const int getWidth(const CFontInfo & next) const = 0;


	virtual const void setHeight(int height)=0;

	virtual const fonttype getTypeOfFont()const  { return typeOfFont;}
	virtual const int getHeight(const CFontInfo & next) const = 0;

	virtual const bool empty() const = 0;

private:
	fonttype typeOfFont;
    };

template <class Type>
class  SGE_API CPathFontInfo: public CFontInfo {
public:
    CPathFontInfo(const Type & path, int width, int height,fonttype fontType):
    CFontInfo(fontType),
	path(path),
    width(width),
    height(height){
    }
	CPathFontInfo(const Type & path, int width, int height):
    CFontInfo(setType(path)),
	path(path),
    width(width),
    height(height){
    }
	virtual const fonttype setType(Type path) {
		string filename = path.getFilename().path();
		string extension = Filesystem::checkExtension(Util::lowerCaseAll(filename));
		if (extension == "ttf")  return CFont::TrueTypeFont;
		if (extension == "otf")  return CFont::TrueTypeFont;
		if (extension == "fnt")  return CFont::MUGENFont;
		if (extension == "bmp")  return CFont::BitmapFont;
		if (extension == "png")  return CFont::BitmapFont;
		else    return CFont::Unknown;

	}

    virtual const CFont & get() const {
		fonttype tipo = getTypeOfFont();

		if(  tipo == CFont::TrueTypeFont) {
			try {
			return *CResource::getTTFont(getName(), width, height);
			}catch (Exception::Filesystem::CNotFound &ex) {
				 ostringstream out;
				 out << "CFont not found " << ex.getTrace()<< endl;
				 Debug::debug(Debug::font,__FUNCTION__) << out.str() << endl;
			}

		}else {//} (tipo == CFont::fonttype::BitmapFont) {
			return  *CResource::getBitmapFont(getName(), width, height);
		}
		//else if (tipo == CFont::fonttype::MUGENFont) {
			//return *CResource::getMugenFont(getName(), width, height);

		//} else {
			// tentando utilizar uma fonte sem suporte

		//}
		return  *CResource::getBitmapFont(getName(), width, height);
    }

    virtual const CFont & get(const CFont & next) const {
        return get();
    }

    virtual const CFontInfo & get(const CFontInfo & next) const {
        return *this;
    }

    virtual string getName() const {
        return path.getFilename().path();
    }

	virtual string getPath() const {
        return path.path();
    }
    virtual const int getWidth(const CFontInfo & next) const {
        return width;
    }

    virtual const int getHeight(const CFontInfo & next) const {
        return height;
    }

	virtual const void setWidth(int width) {
	    this->width = width;
	}


	virtual const void setHeight(int height){
	    this->height = height;
	}

    virtual const bool empty() const {
        return path.path().empty();
    }

protected:
    Type path;
    int width;
    int height;
};
/**
 * \class CRelativeFontInfo
 *
 * \ingroup SGF_Util
 *
 * \brief Informações de fontes inicializadas com caminhos relativos CRelativePath
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CRelativeFontInfo: public CPathFontInfo<Filesystem::CRelativePath> {
public:
	CRelativeFontInfo(const Filesystem::CRelativePath & path, int width, int height,fonttype fontType):
    CPathFontInfo<Filesystem::CRelativePath>(path, width, height,fontType){
    }
	CRelativeFontInfo(const Filesystem::CRelativePath & path, int width, int height):
    CPathFontInfo<Filesystem::CRelativePath>(path, width, height){
    }
	using CFontInfo::operator==;
    virtual bool operator==(const CFontInfo & who) const;
    virtual bool operator==(const CAbsoluteFontInfo & who) const;
    virtual bool operator==(const CRelativeFontInfo & who) const;
};
/**
 * \class CAbsoluteFontInfo
 *
 * \ingroup SGF_Util
 *
 * \brief Informações de fontes inicializadas com caminhos absolutos CAbsolutePath
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CAbsoluteFontInfo: public CPathFontInfo<Filesystem::CAbsolutePath> {
public:
    CAbsoluteFontInfo(const Filesystem::CAbsolutePath & path, int width, int height,fonttype fontType):
    CPathFontInfo<Filesystem::CAbsolutePath>(path, width, height,fontType){
    }
	CAbsoluteFontInfo(const Filesystem::CAbsolutePath & path, int width, int height):
    CPathFontInfo<Filesystem::CAbsolutePath>(path, width, height){
    }
	virtual bool operator==(const CFontInfo & who) const;
    virtual bool operator==(const CAbsoluteFontInfo & who) const;
    virtual bool operator==(const CRelativeFontInfo & who) const;
};


} //end SGF

#endif
