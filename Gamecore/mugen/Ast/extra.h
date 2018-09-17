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
#ifndef _S_G_E_ast_extra_h
#define _S_G_E_ast_extra_h

#include <list>
#include <string>
#include <algorithm>
#include <string.h>
#include "Section.h"
#include "exception.h"
#include "../../util/SGF_Debug.h"
#include "../../util/tokenreader.h"

using namespace std;
namespace SGF{

namespace Ast{

/* output from the def parser. I think all mugen files are just lists
 * of sections so we can probably rename this to AstResult or something
 * like that and make it more generic.
 */
class  SGE_API CAstParse{
public:
  //this classe was replaceb by CAstManager
};

} // end AST
} //end SGF
#endif
