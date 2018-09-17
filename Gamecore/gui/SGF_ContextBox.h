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
#ifndef _S_G_F_gui_context_box_h
#define _S_G_F_gui_context_box_h

#include <string>
#include <vector>
#include "../SGF_Config.h"
#include "SGF_Widget.h"
#include "SGF_PopupBox.h"
#include "SGF_ScrollList.h"
#include "../util/SGF_LanguageString.h"
#include "../graphics/all.h"


using namespace std;
namespace SGF{
class CLanguageString;

namespace Gui{

Effects::Gradient standardGradient(int max);
Effects::Gradient modifiedGradient(Colors::ColorDefinition low, Colors::ColorDefinition high, int max);

/**
 * \class CListValues
 *
 * \ingroup SGF_Gui
 * 
 * \brief Classe Usada na CContextbox para guardar as propriedades da contextbox
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 16 de Janeiro de 2012
  */
class SGE_API CListValues{
public:
    CListValues();
    CListValues(const CListValues &);
    virtual ~CListValues();
    const CListValues & operator=(const CListValues &);
    /**
	* tokens: \n
	* interpolate-selected vai interpolar a opção atual entre as cores:  color-low e color-high: 0 | 1 (o padrão é 1) \n
	* color-low para o espectro inferior das cores de interpolação: vermelho, verde azul (padrão é 19 167 168) \n
	* color-high para o espectro superior das cores de interpolação: vermelho verde azul (o padrão é 27 237 239) \n
	* interpolate-distance:  distância de interpolação: NUM (o padrão é 50) \n
	* selected-color é a cor da opção atual, se a interpolação está desativada: vermelho, verde azul (padrão é 19 167 168) \n
	* selected-color-alpha é o alfa da cor da  opção atual: NUM (padrão é 255) \n
	* other-color é a cor das outras opções: vermelho, verde azul (padrão é 255 255 255) \n
	* other-color-alpha é o alfa das outras opções: NUM (padrão é 255) \n
	* distance-fade-multiplier multiplica a quantidade do efeito de esvanecimento (fade) pela distância dos itens não selecionados: NUM (o padrão é 35) \n
	* distance-fade fará com que as opções esvanecerem de acordo com a distância se tornar maior a partir da opção selecionada: 0 | 1 (o padrão é 1) \n
	*/
    void getValues(const Token *);
    
	/** Verifica se a interpolação está habilitada ou não
	* \return true se a interpolação estiver habilitada
	* \return false se a interpolação não estiver habilitada
	*/
    virtual inline bool getInterpolate() const {
        return this->interpolate;
    }
	/** Habilita ou desabilita a interpolação
	* \param interpolate: true se a interpolação deve habilitada ou \
	*  false se a interpolação deve ser  dasabilitada
	*/
    virtual inline void setInterpolate(bool interpolate){
        this->interpolate = interpolate;
    }
	/** Verifica qual a cor de interpolação inferior
	* \return cor: valor de pixel tipo int representando a cor
	* 
	*/
	virtual inline Colors::ColorDefinition getLowColor() const {
        return this->lowColor;
    }
	/** inicializa a cor de interpolação inferior
	* \param color: int que representa a cor 
	*/
	virtual inline void setLowColor(Colors::ColorDefinition color){
        this->lowColor = color;
    }

	/** Verifica qual a cor de interpolação superior
	* \return cor: valor de pixel tipo int representando a cor
	* 
	*/
	virtual inline Colors::ColorDefinition getHighColor() const {
        return this->highColor;
    }
	/** inicializa a cor de interpolação superior
	* \param color: int que representa a cor 
	*/
    virtual inline void setHighColor(Colors::ColorDefinition color){
        this->highColor = color;
    }

    virtual inline int getMaxGradient() const {
        return this->maxGradient;
    }
	/** inicializa a cor máxima do efeito gradiente
	* \param max: int que representa a cor máxima
	*/
    virtual inline void setMaxGradient(int max){
        this->maxGradient = max;
    }
	/** Verifica qual a cor do item selecionado
	* \return cor: valor de pixel tipo int representando a cor
	* 
	*/
	virtual inline Colors::ColorDefinition getSelectedColor() const {
        return this->selectedColor;
    }
	/** inicializa a cor do item selecionado
	* \param color: int que representa a cor 
	*/
	virtual inline void setSelectedColor(Colors::ColorDefinition color){
        this->selectedColor = color;
    }

	/** Verifica qual o valor alpha do item selecionado
	* \return alpha: valor de alpha 
	* 
	*/
    virtual inline int getSelectedAlpha() const {
        return this->selectedAlpha;
    }
	/** inicializa o alpha do item selecionado
	* \param alpha: int que representa o valor alpha 
	*/
    virtual inline void setSelectedAlpha(int alpha){
        this->selectedAlpha = alpha;
    }
	/** Verifica qual a cor dos itens não selecionados
	* \return cor: valor de pixel tipo int representando a cor
	* 
	*/
    virtual inline Colors::ColorDefinition getOtherColor() const {
        return this->otherColor;
    }

	/** inicializa a cor dos itens não selecionados
	* \param color: int que representa a cor 
	*/
    virtual inline void setOtherColor(Colors::ColorDefinition color){
        this->otherColor = color;
    }

	/** Verifica qual o alpha dos itens não selecionados
	* \return alpha: valor de alpha do pixel 
	* 
	*/
    virtual inline int getOtherAlpha() const {
        return this->otherAlpha;
    }
	/** inicializa o alpha dos itens não selecionados
	* \param alpha: int que representa o valor alpha 
	*/
    virtual inline void setOtherAlpha(int alpha){
        this->otherAlpha = alpha;
    }

    virtual inline double getDistanceFadeMultiplier() const{
        return this->distanceFadeMultiplier;
    }
	/** inicializa o valor do multiplicador do efeito de esvanecimento
	* \param multiplier: double com o valor do multiplicador
	*/
    virtual inline void setDistanceFadeMultiplier(double multiplier){
        this->distanceFadeMultiplier = multiplier;
    }
	/** Verifica se o efeito de esvanecimento está habilitado
	* \return bool: true indica que o efeito de esvanecimento está habilitado e \n
	* false indica que o efeito está desabilitado
	* 
	*/
    virtual inline bool getDistanceFade() const {
        return this->fade;
    }
	/** inicializa o efeito de esvanecimento (fade)
	* \param fade: true habilita o efeito e false desabilita o efeito
	*/
    virtual inline void setDistanceFade(bool fade){
        this->fade = fade;
    }
    
protected:
    bool interpolate;
    Colors::ColorDefinition lowColor, highColor;
    int maxGradient;
    Colors::ColorDefinition selectedColor;
    int selectedAlpha;
    Colors::ColorDefinition otherColor;
    int otherAlpha;
    double distanceFadeMultiplier;
    bool fade;
};

class CScrollItem;
class CContextBox;

/**
 * \class CContextItem
 *
 * \ingroup SGF_Gui
 * 
 * \brief Item da caixa de contexto que contém o texto a ser escrito
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */
    
class SGE_API CContextItem: public CScrollItem{
    public:
	//s old CContextItem();
	CContextItem(const string &, const CContextBox &);
    virtual ~CContextItem();
	
	virtual const string getName() = 0;
	
	/** \brief Desenha (escreve) o Item no Bitmap destino where
      * \param x,y coordenadas do local na tela onde o item deve ser desenhado
	  * \param where referência para o bitmap de destinho (onde deve ser desenhado)
      * \param font a fonte que deve ser utilizada para desenhar (escrever) o item na tela
	  * \param distance: distância do efeito de esvanecimento (fade)
	  * 
      */
	virtual void draw(int x, int y, const CBitmap & where, const CFont & font, int distance) const;
    
	/** \brief Descobre o tamanho em pixels do Texto a ser desenhado na tela
      * \param font - Uma referência para a fonte que será utilizada para desenhar o texto
	  * \return Um integer contendo o tamanho do texto em pixels
      * 
      */
	virtual int size(const CFont & font) const;

	/** \brief Inicializa o texto do item
      * \param t - referência do texto a ser atualizado
	  * 
      */
    virtual void setText(const CLanguageString & t);

	/** \brief Retorna o objeto CLanguageStringo que contem o texto do Item
      * \return O Objeto CLanguageString
	  * 
      */
    inline const CLanguageString & getLanguageText() const {
        return text;
    }
	/** \brief Retorna o texto do item na linguagem adequada
      * \return Uma string contendo o texto do item
	  * 
      */
	virtual inline string getText() const { return text.get(); }


protected:

    CLanguageString text; ///< O Objeto contendo a texto do item nas várias linguagens
    const CContextBox & parent; ///< Uma referência para o pai

};

/**
 * \class CContextBox
 *
 * \ingroup SGF_Gui
 * 
 * \brief Caixa de Contexto usada no Menu para mostrar as opções
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */

class  SGE_API CContextBox : public CWidget {
    public:
        CContextBox();
        CContextBox(const CContextBox &);
        virtual ~CContextBox();
        
        /// construtor de cópia
        CContextBox &operator=(const CContextBox &);
        
        /** \brief executa a lógica do contextbox
		* \param CFont  - uma referência para a fonte que será utilizada no contextbox
		* 
		*/
		virtual void act(const CFont &);
        /// Render
        using CWidget::render;
        virtual void render(const CBitmap &);
        virtual void render(const CBitmap &, const CFont & font);
        /// Próximo
        virtual bool next(const CFont &);
        /// Anterior
        virtual bool previous(const CFont &);
		/// Ajuste à Esquerda
		virtual void adjustLeft();
		/// Auste à direita
		virtual void adjustRight();
		/// abre a caixa de contexto
		virtual void open();
		/// Fecha a caixa de contexto
		virtual void close();
		//! Adiciona Item
		virtual void addItem(const Util::CReferenceCount<CContextItem> & item);
        /// Inicializa a lista de Itens
		virtual inline void setList(const vector<Util::CReferenceCount<CContextItem> > & list);

		/// Scroll ou Normal 
		enum ListType{
			Normal,
			Scroll,
		};

		//! inicializa o tipo de lista
		virtual void setListType(const ListType &);
		//! Indica que o "wrap"  deve ser habilitado ou desabilitado
		virtual void setListWrap(bool wrap);
		//! Verifica a cor do item selecionado
		virtual Colors::ColorDefinition getSelectedColor() const;

       // Verifica o número de opções
		virtual inline int getNumberofOptions(){
		   return list->getNumberOfItens();
        }
        
        //! Verifica qual o índice do item atual 
		virtual inline unsigned int getCurrentIndex(){
            return this->list->getCurrentIndex();
        }
        //! Verifica se o Efeito de Esvanecimento está ativo
		virtual inline bool isActive(){
			return (this->fadeState != NotActive);
		}
        //!Inicializa a velocidade do efeito de esvanecimento
        virtual inline void setFadeSpeed(int speed){
            this->fadeSpeed = speed;
            this->boardBox.setFadeSpeed(speed);
        }
        //!Inicializa o Alpha do efeito de esvanecimento
        virtual inline void setFadeAlpha(int alpha){
            this->fadeAlpha = alpha;
        }
		//! Verifica qual o alpha do efeito de esvanecimento
         virtual inline int getFadeAlpha() const {
        return this->fadeAlpha;
		}

        //! Indica se deve ou não usar o efeito de gradiente
        virtual inline void setUseGradient(bool useGradient){
            this->useGradient = useGradient;
        }
        
        //! Indica se deve ser utilizado apenas texto no background
        virtual inline void setRenderOnlyText(bool render){
	    this->renderOnlyText = render;
		}

		//! Retorna o objeto caixa de popup do contextbox
		virtual inline CPopupBox & getBoard(){
			return boardBox;
		}

		//! Retorna o objeto de valores da lista de opções
		virtual inline const Gui::CListValues & getListValues() const {
			return this->values;
		}
        //! Retorna o objeto de valores da lista de opções
		virtual inline Gui::CListValues & getListValues(){
			return this->values;
		}
		//! Inicializa o objeto de valores da lista de opções
	   virtual void setListValues(const Gui::CListValues & values);

private:
	    //! Executa o Esvanecimento
		void doFade();
	    //! Desenha o Texto
		void drawText(const CBitmap &, const CFont & font);
	    
		//! Determina o Estado do Efeito de Esvanecimento
		enum FadeState{
			NotActive,
			FadeIn,
			Active,
			FadeOut,
		};
  
		//! Estado atual do Esvanecimento
		FadeState fadeState;

		 //! Lista de Itens
		Util::CReferenceCount<CScrollListInterface> list;
    

		//! elocidade de esvanecimento
		int fadeSpeed;
	
		//! Alpha do Esvanecimento
		int fadeAlpha;
	
		//! Board
		CPopupBox boardBox;
	
			//! Posição Central
			int cursorCenter;
			//! Coordenada atual do Cursor
			int cursorLocation;
			//! Espera do Scroll
			int scrollWait;
        
			//! Gradiente do cursor de item selecionado
			Effects::Gradient selectedGradient;

			//! Deve Usar ou não o efeito Gradiente
			bool useGradient;
	
		//! Utilizar apenas texto no background
		bool renderOnlyText;

		//! ParÂmetros da Lista de Valores 
		Gui::CListValues values;
};

}
} //end SGF
#endif
