#ifndef _S_G_F_GAME_COMMANDS_H
#define _S_G_F_GAME_COMMANDS_H

#include <string>
#include "../input/all.h"
#include "../mugen/Ast/all.h"

using namespace std;
namespace SGF{

class CCompiledKeySingle;
/**
 * \class CCompiledKey
 *
 * \ingroup SGF_Game
 *
 * \brief Classe base para definição de teclas compiladas que serão utilizadas nos comandos
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */
template <typename X>
class CCompiledKey{
public:
	CCompiledKey(){};

    virtual bool pressed(const X & keys, const X & oldKeys, int & holdKey, const CCompiledKey *& holder, const CCompiledKey*& needRelease) const = 0;

    virtual string toString() const = 0;

    virtual bool same(const CCompiledKey & key) const {
        return false;
    }

    virtual bool same(const CCompiledKeySingle & key) const {
        return false;
    }

    virtual bool operator==(const CCompiledKey & key) const {
        return key.same(*this);
    }

	virtual ~CCompiledKey(){};
};

/* A finite state automata that can map a single integer to a state.
 * This is convenient for serialization (for network mode).
 */
template <class X>
class CKeyDFA{
public:
    enum Constraint{
        Pressed,
        Released
    };

    CKeyDFA(int id):
    emit(false),
    id(id),
    next(NULL){
    }
    
    virtual bool transition(const X & input, bool & emit) = 0;
    virtual void setEmit(){
        emit = true;
    }

    virtual bool getEmit() const {
        return emit;
    }

    virtual void setNextState(CKeyDFA * next){
        this->next = next;
    }

    const int getId() const {
        return id;
    }

    virtual ~CKeyDFA(){
    }

protected:
    /* If `emit' is true then when this state transitions it will act
     * like an accept state and emit a value.
     */
    bool emit;
    const int id;
    CKeyDFA * next;
};

/**
 * \class CCommand
 *
 * \ingroup SGF_Game
 *
 * \brief Classe base para definição de comandos do jogo
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * \note O parâmetro X do template referese à estrutura Input, contendo os comandos em formas de teclas, 
 *       como no exemplo abaixo:
 struct Input{
    Input(){
    }

    bool operator==(const Input & him) const {
        return pressed == him.pressed && released == him.released;
    }

    bool operator!=(const Input & him) const {
        return !(*this == him);
    }

    
	
    struct Key{
        bool a, b, c;
        bool x, y, z;
        bool back, forward;
        bool up, down;
        bool start;

        Key():
            a(false), b(false), c(false),
            x(false), y(false), z(false),
            back(false), forward(false),
            up(false), down(false),
            start(false){
            }
		 bool operator==(const Key & him) const {
            return a == him.a &&
                   b == him.b &&
                   c == him.c &&
                   x == him.x &&
                   y == him.y &&
                   z == him.z &&
                   back == him.back &&
                   forward == him.forward &&
                   up == him.up &&
                   down == him.down &&
                   start == him.start;
        }

    };

    Key pressed, released;
};
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */
template <class X>
class  SGE_API  CCommand{
public:
	/** \brief constrói um objeto Comando
	* \param name: nome do comando, que é case sensitive (QCB_a is NOT the same as Qcb_a or QCB_A)
	* \param keys: teclas que compões o comando. lista de botões e direções, separada por vírgula
*   Directions and buttons can be preceded by special characters:
*   slash (/) - means the key must be held down
*          egs. command = /D       ;hold the down direction
*               command = /DB, a   ;hold down-back while you press a
*   tilde (~) - to detect key releases
*          egs. command = ~a       ;release the a button
*               command = ~D, F, a ;release down, press fwd, then a
*          If you want to detect "charge moves", you can specify
*          the time the key must be held down for (in game-ticks)
*          egs. command = ~30a     ;hold a for at least 30 ticks, then release
*   dollar ($) - Direction-only: detect as 4-way
*          egs. command = $D       ;will detect if D, DB or DF is held
*               command = $B       ;will detect if B, DB or UB is held
*   plus (+) - Buttons only: simultaneous press
*          egs. command = a+b      ;press a and b at the same time
*               command = x+y+z    ;press x, y and z at the same time
*   greater-than (>) - means there must be no other keys pressed or released
*                      between the previous and the current symbol.
*          egs. command = a, >~a   ;press a and release it without having hit
*                                  ;or released any other keys in between
*   You can combine the symbols:
*     eg. command = ~30$D, a+b     ;hold D, DB or DF for 30 ticks, release,
*                                  ;then press a and b together
*
*   Note: Successive direction symbols are always expanded in a manner similar
*         to this example:
*           command = F, F
*         is expanded when MUGEN reads it, to become equivalent to:
*           command = F, >~F, >F
*   It is recommended that for most "motion" commads, eg. quarter-circle-fwd,
*   you start off with a "release direction". This makes the command easier
*   to do.

* \param maxTime: Tempo máximo permitido para realizar o comando, em ticks.
* O valor padrão típico é 15 ticks
* \param bufferTime: (opcional) Tempo que o comando irápermanecer no buffer,
*   em gameticks. Se o comando foi executado então ele será válido pelo empo bufferTime.
*   O caso mais simples é inicializar bufferTime em 1. Isto significa que o
*   comando é válido somente no mesmo tick em que é realizado. Com valores maiores,
*   como 3 ou 4, você poderá sentir como se perdesse o comando.
*   O resultado é que combos podem se tornar mais fáceis de fazer pois você
*   pode realizar o comando mais cedo.
*   Este parâmetro não afeta comandos do tipo hold-only (ex. /F). Ele será
*   assumido como 1 para estes comandos.
*   Se você tiver dois ou mais comandos com o mesmo nome, todos irão
*   funcionar. Você pode usá-lo para permitir variações para o mesmo movimento
*/
CCommand(string name, Ast::CKeyList * keys, int maxTime, int bufferTime):
name(name),
keys(keys),
maxTime(maxTime),
bufferTime(bufferTime),
ticks(-1),
holdKey(-1),
currentState(0),
successTime(0),
debug(0){
	Debug::debug(Debug::input,__FUNCTION__) << "Constructor - Constructs a empty object of CCommand"<<  endl;
};

    class CException: public CMugenException {
    public:
		CException(){};
		virtual ~CException() throw (){};
    };
	/** \brief método que retorna o nome do comando
	* \return uma string contendo o nome do comando
	*/
    virtual inline string getName() const {
        return name;
    }

	
    virtual bool handle(X keys)=0;
	/** \brief verifica se o debug dos comandos está habilitado
	* \return true: se estiver habilitado o debug
	* \return false: se estiver desabilitado o debug
	*/
	virtual bool handle2(X keys)=0;

	virtual inline bool getDebug() const {
        return debug;
    }
	virtual ~CCommand(){};
	/** \brief mostra o comando de uma forma escrita
	*/
	virtual void debugExplain(){
	if (this->getDebug()) {
	Debug::debug(Debug::input,__FUNCTION__)<<"-----------------------------------------------" <<endl;
	Debug::debug(Debug::input,__FUNCTION__) << "Command> Name: " << name << endl;
	Debug::debug(Debug::input,__FUNCTION__) << "Command> keys: " << keys->toString() << endl;
    Debug::debug(Debug::input,__FUNCTION__) << "Command> maxTime: " << maxTime << endl;
    Debug::debug(Debug::input,__FUNCTION__) << "Command> bufferTime: " << bufferTime << endl;
	Debug::debug(Debug::input,__FUNCTION__) << "Command> ticks: " << ticks << endl;
	Debug::debug(Debug::input,__FUNCTION__) << "Command> holdKey: " << holdKey << endl;
	Debug::debug(Debug::input,__FUNCTION__) << "Command> holdKey: " << successTime << endl;
	Debug::debug(Debug::input,__FUNCTION__) << "Command> compiledKeys: " << "Not Implemented" << endl;
    Debug::debug(Debug::input,__FUNCTION__) << "Command> oldKeys: " << "Not Implemented" << endl;
//	Debug::debug(Debug::input,__FUNCTION__) << "Command> holder: " << (holder==NULL ? "NULL" : "Not Implemented") << endl;
//	Debug::debug(Debug::input,__FUNCTION__) << "Command> needRelease: " << (needRelease==NULL ? "NULL" : "Not Implemented") << endl;
	Debug::debug(Debug::input,__FUNCTION__)<<"-----------------------------------------------" <<endl;
	}
};
protected:

    virtual bool interpret(const Ast::CKey * key, X & keys, const X & oldKeys, int & holdKey, const Ast::CKey *& holder, const Ast::CKey *& needRelease)=0;

protected:
    string name;
	//! lista de teclas que compõe o comando
    Ast::CKeyList * keys;
	 
    const int maxTime;
    const int bufferTime;
	//! guarda os ticks do jogo
    int ticks;
    int holdKey;
	X oldKeys;
    unsigned int currentState;
    int successTime;
	bool debug;
	    
};

//template <typename X>
class  SGE_API CConstraintCommand{
public:
    CConstraintCommand(const std::string & name, int maxTime, int bufferTime):
	name(name),
	maxTime(maxTime),
	bufferTime(bufferTime),
	useBufferTime(0),
	emitted(false){
	}
    
const std::string & getName() const {
    return name;
}         
   // bool handle(const X & input, int ticks)=0;

    virtual SGF::Token * serialize() const=0;
    virtual void deserialize(const SGF::Token * token)=0;
	virtual void debugExplain(){
	if (true) {
	Debug::debug(Debug::input,__FUNCTION__)<<"-----------------------------------------------" <<endl;
	Debug::debug(Debug::input,__FUNCTION__) << "Command> Name: " << name << endl;
	//Debug::debug(Debug::input,__FUNCTION__) << "Command> keys: " << keys->toString() << endl;
    Debug::debug(Debug::input,__FUNCTION__) << "Command> maxTime: " << maxTime << endl;
    Debug::debug(Debug::input,__FUNCTION__) << "Command> bufferTime: " << bufferTime << endl;
	//Debug::debug(Debug::input,__FUNCTION__) << "Command> ticks: " << ticks << endl;
	//Debug::debug(Debug::input,__FUNCTION__) << "Command> holdKey: " << holdKey << endl;
	//Debug::debug(Debug::input,__FUNCTION__) << "Command> holdKey: " << successTime << endl;
	Debug::debug(Debug::input,__FUNCTION__) << "Command> compiledKeys: " << "Not Implemented" << endl;
    Debug::debug(Debug::input,__FUNCTION__) << "Command> oldKeys: " << "Not Implemented" << endl;
//	Debug::debug(Debug::input,__FUNCTION__) << "Command> holder: " << (holder==NULL ? "NULL" : "Not Implemented") << endl;
//	Debug::debug(Debug::input,__FUNCTION__) << "Command> needRelease: " << (needRelease==NULL ? "NULL" : "Not Implemented") << endl;
	Debug::debug(Debug::input,__FUNCTION__)<<"-----------------------------------------------" <<endl;
	}
};



protected:
    std::string name;
    int maxTime;
    int bufferTime;
    int useBufferTime;
    bool emitted;
	std::string type;
};

} //end SGF
#endif
