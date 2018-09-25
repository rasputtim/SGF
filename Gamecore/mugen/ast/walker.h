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
#ifndef _S_G_E_mugen_ast_walker_h
#define _S_G_E_mugen_ast_walker_h

#include "../../SGF_Config.h"

using namespace std;
namespace SGF{

namespace Ast{

class CSection;
class CAttributeSimple;
class CAttributeKeyword;
class CAttributeArray;
class CAttribute;
class CHitDefAttribute;
class CHitDefAttackAttribute;
class CValue;
class CRange;
class CValueList;
class CKeySingle;
class CKeyModifier;
class CKeyCombined;
class CExpressionInfix;
class CExpressionPostfix;
class CExpressionUnary;
class CHelper;
class CIdentifier;
class CString;
class CFunction;
class CKeyword;
class CKeywordArray;
class CNumber;
class COperand;
class CStack;
class CResource;
class CArgument;

/* the visitor pattern */
class  SGE_API CWalker{
public:
    CWalker(){
    }

    virtual void onOperand(const COperand & value){
    }

	virtual void onValue(const CValue & value){
    }

    virtual void onRange(const CRange & range){
    }

    virtual void onValueList(const CValueList & value){
    }

    virtual void onAttribute(const CAttribute & attribute){
    }

    virtual void onKeySingle(const CKeySingle & key){
    }

    virtual void onKeyModifier(const CKeyModifier & key){
    }

    virtual void onHitDefAttribute(const CHitDefAttribute & attribute){
    }

    virtual void onHitDefAttackAttribute(const CHitDefAttackAttribute & attribute){
    }

    virtual void onKeyCombined(const CKeyCombined & key){
    }

    /* start a new section */
    virtual void onSection(const CSection & section){
    }

    /* end a section */
    virtual void onSectionFinished(const CSection & section){
    }

    virtual void onAttributeSimple(const CAttributeSimple & simple){
    }

    virtual void onAttributeKeyword(const CAttributeKeyword & simple){
    }

    virtual void onAttributeArray(const CAttributeArray & simple){
    }

    virtual void onExpressionInfix(const CExpressionInfix & expression){
    }

	virtual void onExpressionPostfix(const CExpressionPostfix & expression){
    }

	virtual void onExpressionUnary(const CExpressionUnary & expression){
    }

    virtual void onIdentifier(const CIdentifier & identifier){
    }

    virtual void onHelper(const CHelper & identifier){
    }

    virtual void onString(const CString & string){
    }

	virtual void onStack(const CStack & stack){
    }

    virtual void onFunction(const CFunction & string){
    }

    virtual void onKeyword(const CKeyword & keyword){
    }

	virtual void onKeywordArray(const CKeywordArray & keyword){
    }

	virtual void onNumber(const CNumber & keyword){
    }

	virtual void onResource(const CResource & resource){
    }
	virtual void onArgument(const CArgument & argument){
    }
	
    virtual ~CWalker(){
    }


};

} //end AST
} //end SGF
#endif
