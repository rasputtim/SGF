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
#ifndef __Menu_V2_h
#define __Menu_V2_h

#include <vector>
#include <string>
#include <map>
#include <queue>
#include <map>
#include <ostream>
#include <sstream>
#include "../SGF_Config.h"
#include "SGF_MenuOption.h"
#include "../util/SGF_FontSystem.h"
#include "../util/SGF_Token.h"
#include "../resource/all.h"
#include "../SGF_Global.h"
#include "../configuration/SGF_Configuration.h"
#include "../util/SGF_AudioSystem.h"
#include "../exceptions/all.h"
#include "../structures/SGF_Parameter.h"
#include "../graphics/all.h"
#include "SGF_OptionFactory.h"
#include "SGF_ActionFactory.h"
#include "../exceptions/all.h"
#include "../gui/all.h"
#include "../input/all.h"
#include "SGF_Menu.h"

#ifdef _MSC_VER
#ifndef uint32_t
typedef unsigned __int32 uint32_t;
#endif
#endif


using namespace std;
namespace SGF {

class CFont;
class CBitmap;
class CMenuOption;
class Token;
class TokenView;
class CFontInfo;
class COptionFactory;


namespace Gui {
	class CAnimation;
	class CAnimationManager;
}
namespace Menu{


class  SGE_API CInfoBox: public Gui::CWidget {
    public:
        CInfoBox();
        ~CInfoBox();
        
        void act(const CFont &);
        virtual void render(const CBitmap &);
        void render(const CBitmap &, const CFont & font);
        void open();
        void close();
        void setText(const string &);
        
        inline bool isActive(){
            return (this->state != NotActive);
        }
        
        
        //inline void setFont(const Util::CReferenceCount<CFontInfo> & font){
        //    this->font = font;
        //}
        
        virtual void initialize(const CFont & font);
        
    private:
        enum State{
            NotActive,
            Opening,
            Active,
            Closing,
        };
        
        State state;
        Gui::CPopupBox popup;
        
        // Util::CReferenceCount<CFontInfo> font;
        
        int fadeAlpha;
        
        vector<string> text;
};

class CMenuException : public Exception::CBase{
    public:
        CMenuException(const string & file, int line, const string reason = "");
        CMenuException(const CMenuException & copy);
        CMenuException(const Exception::CBase & copy);
        virtual ~CMenuException() throw();
    protected:
        
        string reason;
        
        virtual inline const string getReason() const {
            return reason;
        }
        
        virtual Exception::CBase * copy() const;
};

// reload the current menu, usually thrown by some option 
class  SGE_API CReload: public CMenuException {
public:
    CReload(const string & file, int line, const string reason = "");
    virtual ~CReload() throw();
protected:
    virtual Exception::CBase * copy() const;
};

class CValueHolder{
    public:
        CValueHolder(const string &);
        CValueHolder(const CValueHolder &);
        virtual ~CValueHolder();

        virtual CValueHolder & operator=(const CValueHolder &);
        
        virtual CValueHolder & operator<<(const string &);
        virtual CValueHolder & operator<<(bool val);
        virtual CValueHolder & operator<<(int val);
        virtual CValueHolder & operator<<(double val);  
        virtual CValueHolder & operator<<(TokenView &); 
        
        virtual CValueHolder & operator>>(string &);
        virtual CValueHolder & operator>>(bool &);
        virtual CValueHolder & operator>>(int &);
        virtual CValueHolder & operator>>(double &);

        virtual inline const string & getName() const {
            return this->name;
        }

        virtual const string getValues();

    private:
        string name;
        vector<string> values;
        unsigned int location;
        
        void next();
};
#if 0
//! CMenu_v2 Backgrounds 
class  SGE_API CBackground{
    public:
        CBackground();
        ~CBackground();

        //! Logic - Change over to Gui::Space later 
        void act(const Gui::CCoordinate &);

        void render(const Gui::CAnimation::Depth &, const CBitmap &);

        void add(Gui::CAnimation *);
    private:
        map<Gui::CAnimation::Depth, vector<Gui::CAnimation *> > backgrounds;

        void drawBackgrounds(vector<Gui::CAnimation *> &, const CBitmap &);
};
#endif
//! CMenu_v2 actions 
enum Actions{
    Up,
    Down,
    Left,
    Right,
    Select,
    Back,
    Cancel,
    Modify,
    Pause,
};

class CContext;

//! CMenu_v2 CMenuRenderer
 // Allows menu to modify the way it displays it's contents
 // ie regular menus, tab menus, specialized menu etc
 
class  SGE_API CMenuRenderer{
    public:
        CMenuRenderer();
        virtual ~CMenuRenderer();
        
        //! Reader
        virtual bool readToken(const Token *, const COptionFactory &) throw(CLoadException)=0;
        
        virtual void initialize(CContext &)=0;
        virtual void finish()=0;
        virtual bool active()=0;
        
        virtual void act(const CContext &)=0;
        virtual void render(const CBitmap &, const CFont & font)=0;
	    virtual string getType()=0;
	// Set font if applicable
	// virtual void setFont(const Util::CReferenceCount<CFontInfo> &);
        
        //! Compatibility for now, remove later
        virtual void addOption(CMenuOption *)=0;
        virtual vector<Util::CReferenceCount<CMenuOption> > getOptions() const  = 0;
        
        //! Handle action, with access to context
        
        virtual void doAction(const Actions &, CContext &)=0;

		       /*! Invoke override */
        virtual void invokeOverride(const CContext &)=0;

    protected:
        //! Info boxes 
        vector <CInfoBox *> info;
        
        //! CMenu_v2 info box 
        CInfoBox menuInfoBox;
        
        //! Add info box 
        virtual void addInfo(const string &, const Gui::CWidget &, CContext &, const CFont &);
        
        //! act info box 
        virtual void actInfo(const CFont &);
        
        //! render info box 
        virtual void renderInfo(const CBitmap &, const CFont & font);
};

//! Regular CMenu_v2 
class  SGE_API DefaultRenderer : public CMenuRenderer {
    public:
        DefaultRenderer();
        virtual ~DefaultRenderer();
        
	// virtual void setFont(const Util::CReferenceCount<CFontInfo> &);
        virtual bool readToken(const Token *, const COptionFactory &) throw(CLoadException);
        virtual void initialize(CContext &);
        virtual void finish();
        virtual bool active();
        virtual void act(const CContext &);
        virtual void render(const CBitmap &, const CFont &); 
        virtual void addOption(CMenuOption *);
        virtual void doAction(const Actions &, CContext &);
        virtual vector<Util::CReferenceCount<CMenuOption> > getOptions() const ;
		virtual string getType() { return "default renderer";}
  
        virtual void invokeOverride(const CContext &);

        virtual const Gui::CContextBox & getBox() const {
            return menuContentBox;
        }
        
        virtual Gui::CContextBox & getBox(){
            return menuContentBox;
        }


    private:

        //! Options 
        vector<Util::CReferenceCount<CMenuOption> > options;
        
        //! CContext Box 
        Gui::CContextBox menuContentBox; //! CAIXA ONDE SERÃO COLOCADAS ASOPÇÕES
       /*! Override */
        bool hasOverride;
        
        /*! Override index */
        unsigned int overrideIndex;

};

//! Tabbed CMenu_v2 
class  SGE_API CTabInfo {
    public:
        CTabInfo();
        ~CTabInfo();
        string name;
        string info;
       //! Texto geral sobre o Menu, paracido com as informações sobre as opções, Se vazio, não desenha nada e também apaga as cores ca caixa do Menu principal
        string menuInfo;
        
        void act();
        
        //! Options 
        vector<Util::CReferenceCount<CMenuOption> > options;
};

class CTabRenderer : public CMenuRenderer {
    public:
        CTabRenderer();
        virtual ~CTabRenderer();
        
	// virtual void setFont(const Util::CReferenceCount<CFontInfo> &);
        virtual bool readToken(const Token *, const COptionFactory &) throw(CLoadException);
        virtual void initialize(CContext &);
        virtual void finish();
        virtual bool active();
        virtual void act(const CContext &);
        virtual void render(const CBitmap &, const CFont &);
        virtual void addOption(CMenuOption *);
        virtual void doAction(const Actions &, CContext &);
        virtual vector<Util::CReferenceCount<CMenuOption> > getOptions() const;
        virtual void invokeOverride(const CContext &);
        
		virtual string getType() { return "tab renderer";}
		virtual Gui::CTabbedBox & getBox(){
            return menu;
        }

private:

        //! Tabs 
        vector <CTabInfo *> tabs;
        
        //! Tabbed Box 
        Gui::CTabbedBox menu;

		/*! Override */
        bool hasOverride;
        
        /*! Override index */
        unsigned int overrideIndex;
        
};

/*! CMenu_v2 contexts
    - Each menu has a context which it defaults to
        - Sub menus will be passed the parents context when run
    - Fader
    - Backgrounds (No background will fall back onto a fill screen)
    - CMenu_v2 (options, CContextBox, etc)
    - Contexts are settable to omit drawing certain items (usefull for things like in-game menus)
 */
class  SGE_API CContext{
    public:
        CContext();
        CContext(const CContext &, const CContext &);
        virtual ~CContext();
        
        virtual void act();
        /*! Pass the widget (CMenu_v2 CContextBox in this case) to be drawn
         * Allows for custom widget menus to be draw in place (ie for tabs or something)
        */
        virtual void render(CMenuRenderer *, const CBitmap &);
        
        /*! Parse data */
        virtual void parseToken(const Token *);

        //! Compatibility stuff
        virtual void addBackground(const Token *);
        virtual void addBackground(const string &);
        virtual void addBackground(const CBitmap & image);
        
        /*! Initializes things like faders */
        virtual void initialize();
        
        /*! Closes things out like faders */
        virtual void finish();
        
        /*! Play sound */
       virtual void playSound(const Actions &);
        
        /*! Add sound */
        virtual void addSound(const Actions &, const Filesystem::CRelativePath &);
        
        /*! Play music */
        virtual void playMusic();
        
        /*! set music */
        virtual inline void setMusic(const Filesystem::CRelativePath & music){
            this->music = music;
        }

        /*! Current state */
        enum State{
            NotStarted,
            Initializing,
            Running,
            Finishing,
            Completed,
        };
        
        inline const State & getState() const {
            return this->state;
        }
        
        virtual void setFadeTool(Gui::CFadeTool *);

        virtual inline Gui::CFadeTool * getFadeTool(){
            return this->fades;
        }

 /*       virtual void setBackground(CBackground *);

        virtual inline CBackground * getBackground(){
            return this->background;
        }

		*/
		
		virtual bool hasFont() const;
		
        virtual inline void setFont(const Util::CReferenceCount<CFontInfo> & font){
            this->font = font;
        }

        virtual inline const Util::CReferenceCount<CFontInfo> & getFont() const {
            return this->font;
        }
		
		virtual inline const Util::CReferenceCount<CFontInfo> & getFontInfo() const {
            return this->font;
        }
        
		virtual inline void setInfoLocation(double x, double y){
            this->infoLocation.set(x,y);
        }
        
        virtual inline const Gui::CRelativePoint & getInfoLocation() const {
            return this->infoLocation;
        }
        
        virtual inline void setMenuInfoLocation(double x, double y){
            this->menuInfoLocation.set(x,y);
        }
        
        virtual inline const Gui::CRelativePoint & getMenuInfoLocation() const {
            return this->menuInfoLocation;
        }
        
        virtual inline void setMenuInfoText(const string & text){
            this->menuInfo = text;
        }
        
        virtual inline const string & getMenuInfoText() const {
            return this->menuInfo;
        }
        
		virtual vector<string> getLanguages() const;
        virtual void setLanguages(const vector<string> & languages);
/*! Backgrounds */
         Gui::CAnimationManager  background;

    private:
        /*! Require cleanup *default constructor only* */
        bool cleanup;

        /*! Current state */
        State state;

        /*! Fade Tool */
        Gui::CFadeTool * fades;

        

        /*! Sounds */
        map<Actions, Filesystem::CRelativePath> sounds;
        
        /*! CMusic */
        Filesystem::CRelativePath music;
        
        /*! CFont */
        Util::CReferenceCount<CFontInfo> font;

        /*! Info Placement */
        Gui::CRelativePoint infoLocation;
        
        /*! CMenu_v2 Info Placement */
        //! Localização na tela, das informações do vetor menuinfo
		Gui::CRelativePoint menuInfoLocation;
        
        /*! CMenu_v2 Info Text */
        //! Texto geral sobre o Menu, paracido com as informações sobre as opções, Se vazio, não desenha nada e também apaga as cores ca caixa do Menu principal
		string menuInfo;

        vector<string> languages;
};

//! New CMenu_v2 class 
class  SGE_API CMenu_v2 : public CMenu{
    public:
	enum Type{
	    Default,
	    Tabbed,
	};
        CMenu_v2(const Type & type = Default) throw(CLoadException); //! Construtor 1
        CMenu_v2(const Filesystem::CAbsolutePath &,  const COptionFactory & defFactory, const Type & type = Default) throw(CLoadException); //! Construtor 3
        CMenu_v2(const Filesystem::CAbsolutePath &,  const Type & type = Default) throw(CLoadException); //! Construtor 2
 		CMenu_v2(const Token *, const COptionFactory & defFactory, const Type & type = Default) throw(CLoadException); //! Construtor 4
        CMenu_v2(const Token *, const Type & type = Default) throw(CLoadException); //! Construtor 5
        
		virtual ~CMenu_v2();

        //! Run CMenu_v2 pass parent context 
        virtual void run(const CContext &);

        //! Logic pass local context 
        virtual void act(CContext &);

        //! render pass local context and work 
        virtual void render(CContext &, const CBitmap &);

        virtual void setRenderer(const Type &);
        //! Nosso CBitmap atual, onde desenhamos
		/* can't this be passed in instead of created for every menu? */
		CBitmap *work;

		/* a list of languages (translations) supported by this menu */
        virtual vector<string> getLanguages() const;
       
        //! Get Name 
        virtual string getName();
        virtual string getInfo();

        virtual void setFont(const Util::CReferenceCount<CFontInfo> &);
        
        //! Add option 
        virtual inline void addOption(CMenuOption * opt){
            if (renderer){
                this->renderer->addOption(opt);
            }
        }
		//! Load New DINAMIC Options to the current Menu
		virtual void loadOption(const CMenuOption *option, const COptionFactory & factory) throw(CLoadException);
        virtual inline CMenuRenderer * getRenderer() const {
            return renderer;
        }
        virtual inline CContext getContext() const {
            return context;
        }
	static const int Width = 640;
	static const int Height = 480;
	COptionFactory defaultOptionFactory;
    protected:
		 CInputManager *pCurInputManager;
        void setupDefaultLanguage(const CContext & context, const CMenu_v2 & parent);
        virtual void openOptions();
        virtual void closeOptions();
        //! CContext 
        CContext context;
        
        //! Data holder 
        map<string, CValueHolder *> data;

        //! CMenuRenderer 
        CMenuRenderer * renderer;
        /*! Define o Menu Pai */
		//virtual void setParent(CMenu *menu){} // so usado na versao 1 do menu
        /*! load token */
		void load(const Token * token, const COptionFactory & factory) throw(CLoadException);
       
       
        
	
	//! Do current version 
	virtual void handleCurrentVersion(const Token *) throw(CLoadException);
	
        //! Prior token compatibility based on version Global::getVersion() 
        virtual void handleCompatibility(const Token *, int version, const COptionFactory & factory);
        
        //! Add Data 
        void addData(CValueHolder *);
        
        //! Keys 
        CInputMap<Actions> input;
	
	//! Type 
	Type type;
	
	//! Check type 
	virtual CMenuRenderer * rendererType(const Type &);
	//! Version
	int major;
	int minor;
	int micro;

	vector<string> languages;

};

}
} //end SGF
#endif
