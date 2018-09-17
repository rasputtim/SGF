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
#include "menu/SGF_MenuV2.h"
#include "util/SGF_Token.h"
#include "util/SGF_TokenReader_xml.h"



//UNDEF GNU DEFINITIONS
#ifdef major
#undef major
#endif
#ifdef minor
#undef minor
#endif

using namespace std;
namespace SGF {

class Token;
class CTokenReaderXML;

using namespace std;
using namespace Gui;
using namespace Input;

//class Gui::CAnimation;
//template <class Value> vector<Value> Util::CParameter<Value>::stack;
namespace Menu{

/* the current font is a property of the dynamic execution. so it will
 * be modified by various functions that call Parameter::push
 */
static const CFont & currentFont(){
	Debug::debug(Debug::menu,__FUNCTION__) <<  endl;
   // return Util::CParameter<Util::CReferenceCount<Menu::CFontInfo> >::current()->get();
	//Todo: use CConfiguration to load the initial font.
	if (CConfiguration::getMenuFont_v2()==NULL) {
	return *CResource::getDefaultFont(CConfiguration::menuFontSize.getInteger(),CConfiguration::menuFontSize.getInteger());
	
	} else {
		//Debug::debug(Debug::menu,__FUNCTION__) << "Font (width,height): ( "<< CConfiguration::menuFontSize.getInteger() << " , " << CConfiguration::menuFontSize.getInteger() <<" )" << endl;
		return CConfiguration::getMenuFont_v2()->get();
	}

}

static string sharedFont = string(DEF_FONT_PATH)+"arial.ttf";
static int sharedFontWidth = 24;
static int sharedFontHeight = 24;

static const int GradientMax = 50;
static Uint8 clamp(Uint8 in, Uint8 low = 0, Uint8 high = 255){
    return Util::clamp(in,low,high);
}

Menu::CInfoBox::CInfoBox():
state(NotActive),
fadeAlpha(0){
    popup.setFadeSpeed(20);
}

Menu::CInfoBox::~CInfoBox(){
}

void Menu::CInfoBox::act(const CFont & font){
    popup.act(font);

    int speed = 9;
    switch (state){
        case Opening: {
            if (fadeAlpha < 255){
                fadeAlpha += speed;
            }

            if (fadeAlpha >= 255){
                fadeAlpha = 255;
                if (popup.isActive()){
                    state = Active;
                }
            }
            break;
        }
        case Closing: {
            if (fadeAlpha > 0){
                fadeAlpha -= speed;
            }

            if (fadeAlpha <= 0){
                fadeAlpha = 0;
                if (!popup.isActive()){
                    state = NotActive;
                }
            }
            break;
        }
        case Active:
        case NotActive:
        default:
            break;
    }
}

void Menu::CInfoBox::render(const CBitmap &){
    throw CMenuException(__FILE__, __LINE__, "Don't call the render(CBitmap) function");
}

void Menu::CInfoBox::render(const CBitmap & bmp, const CFont & vFont){
    Debug::debug(Debug::menu,__FUNCTION__) << "Begin / [ CBitmap: ( "<< &bmp <<" )]" << endl;
	Debug::debug(Debug::menu,__FUNCTION__) << "[ Font: ( "<< &vFont <<" )]" << endl;
	popup.render(bmp);

    // const CFont & vFont = CConfiguration::getMenuFont_v2()->get(*font);

     int x1 = popup.getArea().getX()+(int)(popup.getArea().getRadius()/2);
     int y1 = popup.getArea().getY()+2;
     int x2 = popup.getArea().getX2()-(int)(popup.getArea().getRadius()/2);
     int y2 = popup.getArea().getY2()-2;
	Debug::debug(Debug::menu,__FUNCTION__) << "[ x1,y1: ( "<< x1<<" , "<< y1 <<" )]" << endl;
	Debug::debug(Debug::menu,__FUNCTION__) << "[ x2,y2: ( "<< x2<<" , "<< y2 <<" )]" << endl;

	bmp.setClipRect(x1, y1, x2, y2);
    //int sy = location.getY() - 5;
	int sy = y1+ ((y2-y1-vFont.getHeight()) /2);
    //static int white = CBitmap::makeColor(255,255,255);
    for (vector<string>::iterator it = text.begin(); it != text.end(); it++){
        string & str = *it;
        if (fadeAlpha < 255){
            CBitmap::transBlender(0, 0, 0, fadeAlpha);
            // CBitmap::drawingMode( CBitmap::MODE_TRANS );
			vFont.drawText(location.getX() + 5, sy, Colors::White, bmp.translucent(), str.c_str(), 0 );
			       // CBitmap::drawingMode(CBitmap::MODE_SOLID);
        } else {
			vFont.drawText(location.getX() + 5, sy, Colors::White, bmp, str.c_str(), 0 );
        }
        sy += vFont.getHeight();
    }
    bmp.setClipRect(0, 0, bmp.getWidth(), bmp.getHeight());
}

void Menu::CInfoBox::open(){
	Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN: " <<  endl;
    state = Opening;
	Debug::debug(Debug::menu,__FUNCTION__) << "Will Set up popup Location (x,y): "<< location.getX()<< " , " << location.getY() <<  endl;
    popup.location = location;
    Debug::debug(Debug::menu,__FUNCTION__) << "1 - Seted up popup Location (x,y): "<< popup.location.getX()<< " , " << popup.location.getY() <<  endl;
	popup.colors = colors;
    popup.open();
    fadeAlpha = 0;
	Debug::debug(Debug::menu,__FUNCTION__) << "2 - Seted up popup Location (x,y): "<< popup.location.getX()<< " , " << popup.location.getY() <<  endl;
	Debug::debug(Debug::menu,__FUNCTION__) << "END: " <<  endl;
}

void Menu::CInfoBox::close(){
    state = Closing;
    popup.close();
}

//! dimensions are computed lazily when we get a font, but only compute once per font
void Menu::CInfoBox::initialize(const CFont & font){
    int maxWidth = 0;
    int height = 0;
    for (vector<string>::iterator it = text.begin(); it != text.end(); it++){
        int w = font.getTextLength((*it).c_str()) + 10;
        if (w > maxWidth){
            maxWidth = w;
        }
        height += font.getHeight();
    }

    location.setDimensions(maxWidth, height);
}

void Menu::CInfoBox::setText(const string & info){
    if (info.empty()){
        return;
    }
    text.clear();
    // const CFont & vFont = CConfiguration::getMenuFont_v2()->get(*font);
    size_t start = 0;
    size_t last = 0;
    start = info.find("\n");
    while (start != string::npos){
        text.push_back(info.substr(last, start - last));
        last = start + 1;
        start = info.find("\n", last);
    }
    text.push_back(info.substr(last));

    /*
    int maxWidth = 0;
    int height = 0;
    for (vector<string>::iterator it = text.begin(); it != text.end(); it++){
        int w = vFont.textLength((*it).c_str()) + 10;
        if (w > maxWidth){
            maxWidth = w;
        }
        height += vFont.getHeight();
    }

    location.setDimensions(maxWidth, height);
    */
}
//! Função que prepara as opções do menu na classe CContentBox
static vector<Util::CReferenceCount<CContextItem> > toContextList(const CContextBox & context, const vector<Util::CReferenceCount<CMenuOption> > & list){
    vector<Util::CReferenceCount<CContextItem> > contextItems;
    for (vector<Util::CReferenceCount<CMenuOption> >::const_iterator i = list.begin(); i != list.end(); ++i){
        const Util::CReferenceCount<CMenuOption> & option = *i;
        contextItems.push_back(option);
    }
    return contextItems;
}

static void tryPlaySound(const Filesystem::CRelativePath & path){
	CSound * ok = CResource::getSound(path.path());
    if (ok != NULL){
        ok->play();
    }
}

 // FIXME Exception handling for CValueHolder
Menu::CMenuException::CMenuException(const string & file, int line, const string reason ):
Exception::CBase(file, line),
reason(reason){
}
Menu::CMenuException::CMenuException(const CMenuException & copy):
Exception::CBase(copy),
reason(copy.reason){
}
Menu::CMenuException::CMenuException(const Exception::CBase & copy):
Exception::CBase(copy),
reason("unknown"){
}
Menu::CMenuException::~CMenuException() throw(){
}
Exception::CBase * Menu::CMenuException::copy() const {
    return new CMenuException(*this);
}

Menu::CReload::CReload(const string & file, int line, const string reason):
CMenuException(file, line, reason){
}

Menu::CReload::~CReload() throw() {
}

Exception::CBase * Menu::CReload::copy() const {
    return new CReload(*this);
}

Menu::CValueHolder::CValueHolder(const string & name):
name(name),
location(0){
}

Menu::CValueHolder::~CValueHolder(){
}

Menu::CValueHolder::CValueHolder(const CValueHolder & copy){
    // reset position
    this->location = 0;
    this->name = copy.name;
    this->values = copy.values;
}

Menu::CValueHolder & Menu::CValueHolder::operator=(const CValueHolder & copy){
    // reset position
    this->location = 0;
    this->name = copy.name;
    this->values = copy.values;
    return *this;
}

Menu::CValueHolder & Menu::CValueHolder::operator<<(const string & val){
    values.push_back(val);
    return *this;
}
Menu::CValueHolder & Menu::CValueHolder::operator<<(bool val){
    ::std::ostringstream o;
    o << val;
    return *this << o.str();
}
Menu::CValueHolder & Menu::CValueHolder::operator<<(int val){
    ::std::ostringstream o;
    o << val;
    return *this << o.str();
}
Menu::CValueHolder & Menu::CValueHolder::operator<<(double val){
    ::std::ostringstream o;
    o << val;
    return *this << o.str();
}

Menu::CValueHolder & Menu::CValueHolder::operator<<(TokenView & view){
    string temp;
    view >> temp;
    return *this << temp;
}

Menu::CValueHolder & Menu::CValueHolder::operator>>(string & val){
    if (values[location].empty()){
        throw CMenuException(__FILE__, __LINE__, "Empty value.");
    }
    val = values[location];
    next();
    return *this;
}
Menu::CValueHolder & Menu::CValueHolder::operator>>(bool & val){
    if (values[location].empty()){
        throw CMenuException(__FILE__, __LINE__, "Empty value.");
    }
    std::istringstream i(values[location]);
    i >> val;
    next();
    return *this;
}
Menu::CValueHolder & Menu::CValueHolder::operator>>(int & val){
    if (values[location].empty()){
        throw CMenuException(__FILE__, __LINE__, "Empty value.");
    }
    std::istringstream i(values[location]);
    i >> val;
    next();
    return *this;
}
Menu::CValueHolder & Menu::CValueHolder::operator>>(double & val){
    if (values[location].empty()){
        throw CMenuException(__FILE__, __LINE__, "Empty value.");
    }
    std::istringstream i(values[location]);
    i >> val;
    next();
    return *this;
}

void Menu::CValueHolder::next(){
    location++;
    if (location >= values.size()){
        location = 0;
    }
}

const string Menu::CValueHolder::getValues() {
    string temp;
    for (vector<string>::iterator i = values.begin(); i != values.end(); ++i){
        temp += *i + "; ";
    }
    return temp;
}
#if 0
// backgrounds
Menu::CBackground::CBackground(){
}

Menu::CBackground::~CBackground(){
    for (map<Gui::CAnimation::Depth, vector<Gui::CAnimation *> >::iterator i = backgrounds.begin(); i != backgrounds.end(); ++i){
        vector<Gui::CAnimation *> & animations = i->second;
        for (vector<Gui::CAnimation *>::iterator j = animations.begin(); j != animations.end(); ++j){
            Gui::CAnimation * anim = *j;
            if (anim){
                delete anim;
            }
        }
    }
}

void Menu::CBackground::act(const Gui::CCoordinate & coord){
    for (map<Gui::CAnimation::Depth, vector<Gui::CAnimation *> >::iterator i = backgrounds.begin(); i != backgrounds.end(); ++i){
        vector<Gui::CAnimation *> & animations = i->second;
        for (vector<Gui::CAnimation *>::iterator j = animations.begin(); j != animations.end(); ++j){
            Gui::CAnimation * anim = *j;
            if (anim){
                anim->act();
            }
        }
    }
}

void Menu::CBackground::render(const Gui::CAnimation::Depth & depth, const CBitmap & bmp){
	Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN / background animation size: "<< backgrounds[depth].size() << endl;

    for (vector<Gui::CAnimation *>::iterator i = backgrounds[depth].begin(); i != backgrounds[depth].end(); ++i){
        Gui::CAnimation * anim = *i;
        if (anim){
            anim->draw(bmp);
	        }
    }
	Debug::debug(Debug::menu,__FUNCTION__) << "END" << endl;
}

void Menu::CBackground::add(Gui::CAnimation * anim){
    backgrounds[anim->getDepth()].push_back(anim);
}
#endif


static bool parseDisplayList(const Token * token, CContextBox & menu){
    if (*token == "display-list"){
        TokenView view = token->view();
        while (view.hasMore()){
            const Token * tok;
            view >> tok;
            string type;
            bool wrap = true;
            if (tok->match("type", type)){
                if (type == "normal"){
                    menu.setListType(CContextBox::Normal);
                } else if (type == "scroll"){
                    menu.setListType(CContextBox::Scroll);
                }
            } else if (tok->match("wrap", wrap)){
                menu.setListWrap(wrap);
            } else if ( *tok == "items"){
                Gui::CListValues values;
                values.getValues(tok);
                menu.setListValues(values);
            }
        }
        return true;
    }
    return false;
}


Menu::CMenuRenderer::CMenuRenderer(){
}

Menu::CMenuRenderer::~CMenuRenderer(){
    // Kill info boxes
    for (vector< Menu::CInfoBox *>::iterator i = info.begin(); i != info.end();++i){
        if (*i){
            delete *i;
        }
    }
}


//void Menu::CMenuRenderer::setFont(const Util::CReferenceCount<CFontInfo> & font){}



void Menu::CMenuRenderer::addInfo(const string & text, const Gui::CWidget & defaults, CContext & context, const CFont & font){
    Debug::debug(Debug::menu,__FUNCTION__) << "Begin  " <<  endl;
	Debug::debug(Debug::menu,__FUNCTION__) << "Text:  "<< text <<  endl;
	Debug::debug(Debug::menu,__FUNCTION__) << "Widget defaults:  " << &defaults<<  endl;
	Debug::debug(Debug::menu,__FUNCTION__) <<" font:  " << &font<<  endl;
	Debug::debug(Debug::menu,__FUNCTION__) << "MenuContentBox (x,Y) > "<< defaults.location.getX() << " , "<< defaults.location.getY() <<  endl;
	if (text.empty()){
        return;
    }
    if (!info.empty()){
        info.back()->close();
    }
    Menu::CInfoBox * temp = new Menu::CInfoBox();
    Debug::debug(Debug::menu,__FUNCTION__) << "New CInfoBox center (x,Y): "<< temp->location.getX() << " , "<< temp->location.getY() <<  endl;
    temp->setText(text);
    temp->initialize(font);
    const int width = temp->location.getWidth();
    const int height = temp->location.getHeight();
	 Debug::debug(Debug::menu,__FUNCTION__) << "New CInfoBox (width,height): "<< width << " , "<< height <<  endl;

	Debug::debug(Debug::menu,__FUNCTION__) << "context.getInfoLocation().getX(): "<< context.getInfoLocation().getX() <<   endl;
    Debug::debug(Debug::menu,__FUNCTION__) << "context.getInfoLocation().getY(): "<< context.getInfoLocation().getY() <<  endl;


	int pos1_x = context.getInfoLocation().getX() - width/2;
	int pos1_y = context.getInfoLocation().getY() - height/2;
	int pos2_x = context.getInfoLocation().getX() + width/2;
	int pos2_y = context.getInfoLocation().getY() + height/2;


	Debug::debug(Debug::menu,__FUNCTION__) << "Calculated Position 1 (x,Y) > "<< pos1_x << " , "<<  pos1_y <<  endl;
    Debug::debug(Debug::menu,__FUNCTION__) << "Calculated Position 2 (x,Y) > "<< pos2_x << " , "<<  pos2_y <<  endl;

	temp->location.setPosition(Gui::CAbsolutePoint(pos1_x,pos1_y));
    // have to pass the dimensions back in to correct proper placement
    temp->location.setPosition2(Gui::CAbsolutePoint(pos2_x,pos2_y));
    temp->location.setRadius(defaults.location.getRadius());
    temp->colors = defaults.colors;
    temp->open();
	Debug::debug(Debug::menu,__FUNCTION__) << "width:  " << width<<  endl;
	Debug::debug(Debug::menu,__FUNCTION__) << "height:  " << height <<  endl;
	Debug::debug(Debug::menu,__FUNCTION__) << "x:  " << context.getInfoLocation().getX()  <<  endl;
	Debug::debug(Debug::menu,__FUNCTION__) << "y:  " << context.getInfoLocation().getY() <<  endl;
	Debug::debug(Debug::menu,__FUNCTION__) << "Radius:  " << defaults.location.getRadius() <<  endl;
    info.push_back(temp);
	Debug::debug(Debug::menu,__FUNCTION__) << "End  " <<  endl;
}

void Menu::CMenuRenderer::actInfo(const CFont & font){
    for (vector< Menu::CInfoBox *>::iterator i = info.begin(); i != info.end();){
        Menu::CInfoBox *box = *i;
        box->act(font);
        if (!box->isActive()){
            delete box;
            i = info.erase(i);
        } else {
            i++;
        }
    }
}

void Menu::CMenuRenderer::renderInfo(const CBitmap & work, const CFont & font){
	Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN [Cbitmap: ( << "<<&work << " )]" << endl;
	Debug::debug(Debug::menu,__FUNCTION__) << "Info Size: "<< info.size() << endl;
    for (vector< Menu::CInfoBox *>::iterator i = info.begin(); i != info.end(); ++i){
        //Menu::CInfoBox *box = *i;
        //box->render(work, font);
		(*i)->render(work,font);
    }
}

Menu::DefaultRenderer::DefaultRenderer(){
	Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN Constructor - Setting Content Box Positions and Colors" << endl;
    // Default the menu to a certain size and details
    menuContentBox.location.setRadius(15);
    menuContentBox.location.set(-.6, -.3, .6, .8);
	menuContentBox.colors.body = Colors::Black;
    menuContentBox.colors.body.a = 128;
	menuContentBox.colors.border = Colors::Red;
    menuContentBox.colors.border.a = 255;
	Debug::debug(Debug::menu,__FUNCTION__) << "END Constructor - Setting Content Box Positions and Colors" << endl;
}

vector<Util::CReferenceCount<CMenuOption> > Menu::DefaultRenderer::getOptions() const {
    return options;
}
void Menu::DefaultRenderer::invokeOverride(const CContext & context){
    if (hasOverride){
        options[overrideIndex]->run(context);
        throw Exception::Return(__FILE__, __LINE__);
    }
}
Menu::DefaultRenderer::~DefaultRenderer(){
}



bool Menu::DefaultRenderer::readToken(const Token * token, const COptionFactory &factory) throw(CLoadException){
	Debug::debug(Debug::menu,__FUNCTION__) << "Begin Reading token: " << token->getName() << endl;

	if( *token == "option" ) {
		Debug::debug(Debug::menu,__FUNCTION__) << "Begin Reading token Option " <<  endl;

        try{

            CMenuOption *temp = factory.getOption(menuContentBox,token);

			if (temp){
                options.push_back(temp);
				if (!hasOverride){
                    const Token * tok;
                    token->view() >> tok;
                    if (tok->findToken("_/override") != NULL){
                        overrideIndex = options.size()-1;
                        hasOverride = true;
                    }
                }
            }

        } catch (const CLoadException & le){
            Debug::debug(Debug::menu,__FUNCTION__) << "Could not read option: " << le.getTrace() << endl;
            token->print(" ");
        }

    }

	else if ( *token == "position" ) {
        // This handles the placement of the menu list and surrounding box
       Debug::debug(Debug::menu,__FUNCTION__) << "Will set MenuContentBox location "  << endl;
            menuContentBox.setCoordinates(token);
			Debug::debug(Debug::menu,__FUNCTION__) << "MenuContentBox location setted [x1,y1,x2,y2]: "<< menuContentBox.location.getPosition().getX()<<" , "<< menuContentBox.location.getPosition().getY()<<" , "<< menuContentBox.location.getPosition2().getX()<<" , "<< menuContentBox.location.getPosition2().getY()   << endl;
    } else if ( *token == "relative-position"){
        menuContentBox.setCoordinates(token);
    } else if ( *token == "coordinate"){
        menuContentBox.setCoordinates(token);
    } else if ( *token == "position-body" ) {
        // This handles the body color of the menu box
        menuContentBox.setColors(token);
    } else if ( *token == "position-border" ) {
        // This handles the border color of the menu box
        menuContentBox.setColors(token);
    } else if ( *token == "transforms" ) {
        // This handles the border color of the menu box
        menuContentBox.setTransforms(token);
    } else if ( *token == "fade-speed" ) {
        // Menu fade in speed
        int speed;
        token->view() >> speed;
        menuContentBox.setFadeSpeed(speed);
    } else if ( parseDisplayList(token, menuContentBox) ){

	}

	else {
		Debug::debug(Debug::menu,__FUNCTION__) << "END Rendering returng FALSE: " << token->getName() << endl;
        return false;
    }

    Debug::debug(Debug::menu,__FUNCTION__) << "END Rendering returning TRUE: " << token->getName() << endl;
    return true;
}

/*
void Menu::DefaultRenderer::setFont(const Util::CReferenceCount<CFontInfo> & font){
    if (!font->empty()){
	menu.setFont(CConfiguration::getMenuFont_v2()->getFont(*font),
                     CConfiguration::getMenuFont_v2()->getWidth(*font),
                     CConfiguration::getMenuFont_v2()->getHeight(*font));
	menuInfo.setFont(font);
    }
}
*/

void Menu::DefaultRenderer::initialize(CContext & context){
	Debug::debug(Debug::menu,__FUNCTION__) << "Begin / Context: " << &context << endl;
    // FIXME This is wrong, move this over to CFontInfo so that the overrides can be accounted for

    //Filesystem::CRelativePath localFont("fonts/arial.ttf");
    //int width = 24, height = 24;



//    if (CConfiguration::getMenuFont_v2() != NULL){
//        localFont = CConfiguration::getMenuFont_v2()->getFont();
//        width = CConfiguration::menuFontSize.getInteger();
//        height = CConfiguration::menuFontSize.getInteger();
//    } else if (Filesystem::exists(context.getFont()->getFont())){
//        localFont = context.getFont()->getFont();
//        width = context.getFont()->getWidth();
//        height = context.getFont()->getHeight();
//    }

	Debug::debug(Debug::menu,__FUNCTION__) << "Begin Fase 1 - Initialize Menu Content Box "  << endl;
    // setFont(new CFontInfo(localFont, width, height));
	Debug::debug(Debug::menu,__FUNCTION__) << "Begin Fase 1a - Set list of options to MEnu Content Box. Number of options: "<< options.size()  << endl;
	menuContentBox.setList(toContextList(menuContentBox, options));
	//menuContentBox.setList(toContextList(options));
	Debug::debug(Debug::menu,__FUNCTION__) << "End Fase 1a - Number of options setted to Menu  Content Box: "<< menuContentBox.getNumberofOptions()  << endl;
    menuContentBox.open();
	Debug::debug(Debug::menu,__FUNCTION__) << "End Fase 1 - Initialize Menu Content Box: "<< &menuContentBox  << endl;

	Debug::debug(Debug::menu,__FUNCTION__) << "Begin Fase 2 - Initialize Menu Info Box " << endl;
	const CFont & font = currentFont();

    Debug::debug(Debug::menu,__FUNCTION__) << "Font: " << &font << endl;
	// Menu info

    if (!context.getMenuInfoText().empty()){
		Debug::debug(Debug::menu,__FUNCTION__) << "MenuinfoText Not empty: "<< context.getMenuInfoText() <<  endl;
        menuInfoBox.setText(context.getMenuInfoText());
        menuInfoBox.initialize(font);
        const int width = menuInfoBox.location.getWidth();
        const int height = menuInfoBox.location.getHeight();
        menuInfoBox.location.setPosition(Gui::CAbsolutePoint(context.getMenuInfoLocation().getX() - width/2, context.getMenuInfoLocation().getY() - height/2));
        // have to pass the dimensions back in to correct proper placement
        menuInfoBox.location.setPosition2(Gui::CAbsolutePoint(menuInfoBox.location.getX() + width,menuInfoBox.location.getY() + height));
        menuInfoBox.location.setRadius(menuContentBox.location.getRadius());
        menuInfoBox.colors = menuContentBox.colors;
    }

    menuInfoBox.open();
	Debug::debug(Debug::menu,__FUNCTION__) << "Fase 2 - Will Add Info to MenuContentBox> "<< &menuContentBox <<  endl;
	Debug::debug(Debug::menu,__FUNCTION__) << "Fase 2 - MenuContentBox (x,Y) > "<< menuContentBox.location.getX() << " , "<< menuContentBox.location.getY() <<  endl;
    // Add first info option
    addInfo(options[menuContentBox.getCurrentIndex()]->getInfoText(), menuContentBox, context, font);
		Debug::debug(Debug::menu,__FUNCTION__) << "End Fase 2 - Initialize Menu Info Box " << endl;
	Debug::debug(Debug::menu,__FUNCTION__) << "END  " <<  endl;
}

void Menu::DefaultRenderer::finish(){
    menuContentBox.close();
    menuInfoBox.close();
}

bool Menu::DefaultRenderer::active(){
    return menuContentBox.isActive();
}

void Menu::DefaultRenderer::act(const CContext & context){
    const CFont & font = currentFont();
    // FIXME find a better way to get options to update this is a waste
    for (vector<Util::CReferenceCount<CMenuOption> >::iterator i = options.begin(); i != options.end(); ++i){
        Util::CReferenceCount<CMenuOption> & option = *i;
        option->logic();
    }
    menuContentBox.act(font);
    menuInfoBox.act(font);
    actInfo(font);
}

void Menu::DefaultRenderer::render(const CBitmap & bmp, const CFont & font){
    Debug::debug(Debug::menu,__FUNCTION__) << "Will Render Menu  " <<  endl;
	menuContentBox.render(bmp, font);
	Debug::debug(Debug::menu,__FUNCTION__) << "Will Render MenuInfo  " <<  endl;
    menuInfoBox.render(bmp, font);
	Debug::debug(Debug::menu,__FUNCTION__) << "Will Render Info  " <<  endl;
    renderInfo(bmp, font);
}

void Menu::DefaultRenderer::addOption(CMenuOption * opt){
    this->options.push_back(opt);
}

void Menu::DefaultRenderer::doAction(const Actions & action, CContext & context){
	Debug::debug(Debug::menu,__FUNCTION__) << "Begin Render Action context: "<< &context << endl;
    Debug::debug(Debug::menu,__FUNCTION__) << "Action "<< action <<  endl;
	const CFont & font = currentFont();
    switch(action){
        case Up:
            if (menuContentBox.previous(font)){
                 context.playSound(Up);
                addInfo(options[menuContentBox.getCurrentIndex()]->getInfoText(), menuContentBox, context, font);
            }
            break;
        case Down:
            if (menuContentBox.next(font)){
                 context.playSound(Down);
                addInfo(options[menuContentBox.getCurrentIndex()]->getInfoText(), menuContentBox, context, font);
            }
            break;
        case Left:
            if (options[menuContentBox.getCurrentIndex()]->leftKey()){
		// setFont(context.getFont());
                context.playSound(Left);
            }
            break;
        case Right:
            if (options[menuContentBox.getCurrentIndex()]->rightKey()){
                // setFont(context.getFont());
				context.playSound(Right);
            }
            break;
        case Select: {
            try{
                context.playSound(Select);
                options[menuContentBox.getCurrentIndex()]->run(context);
            } catch (const CReload & reload){
                menuContentBox.open();
                menuInfoBox.open();
            }
            // setFont(context.getFont());
             context.playMusic();
            // font might have been recreated

            const CFont & font = currentFont(); //CConfiguration::getMenuFont_v2()->get(context.getFont()->get());
            addInfo(options[menuContentBox.getCurrentIndex()]->getInfoText(), menuContentBox, context, font);
            menuInfoBox.initialize(font);
            break;
        }
        case Cancel:
            context.playSound(Cancel);
            throw Exception::Return(__FILE__, __LINE__);
            break;
        default:
            break;
    }
	Debug::debug(Debug::menu,__FUNCTION__) << "End Render Action context: "<< &context << endl;
}

Menu::CTabInfo::CTabInfo(){
	Debug::debug(Debug::menu,__FUNCTION__) << "CREATING TABINFO " << endl;
}

Menu::CTabInfo::~CTabInfo(){

}

void Menu::CTabInfo::act(){
     for (vector<Util::CReferenceCount<CMenuOption> >::iterator i = options.begin(); i != options.end(); ++i){
        Util::CReferenceCount<CMenuOption> & option = *i;
        option->logic();
    }
}

Menu::CTabRenderer::CTabRenderer(){

    // Default the menu to a certain size and details
    //menu.location.setRadius(15);
    menu.location.set(-.6, -.3, .6, .8);
	menu.colors.body = Colors::Black;
    menu.colors.body.a = 128;
	menu.colors.border = Colors::Red;
    menu.colors.border.a = 255;
}

vector<Util::CReferenceCount<CMenuOption> > Menu::CTabRenderer::getOptions() const {
    vector<Util::CReferenceCount<CMenuOption> > options;
    for (vector<CTabInfo *>::const_iterator it = tabs.begin(); it != tabs.end(); ++it){
        options.insert(options.end(), (*it)->options.begin(), (*it)->options.end());
    }
    return options;
}

/* FIXME need to implement override for tabs */
void Menu::CTabRenderer::invokeOverride(const CContext & context){
    if (hasOverride){
        //options[overrideIndex]->run(context);
        throw Exception::Return(__FILE__, __LINE__);
    }
}

Menu::CTabRenderer::~CTabRenderer(){
    // Kill tabs
    for (vector<CTabInfo *>::iterator i = tabs.begin(); i != tabs.end(); ++i){
        if (*i){
            delete *i;
        }
    }
}

bool Menu::CTabRenderer::readToken(const Token * token, const COptionFactory &factory) throw(CLoadException){
	Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN - Will read Token: "<< token->getName()  << endl;
    if (*token == "menu"){
	CTabInfo * tabInfo = new CTabInfo();
	Gui::CTab * tab = new Gui::CTab();
    TokenView view = token->view();
	while (view.hasMore()){
	    const Token * tok;
	    view >> tok;
	    try{
		if (*tok == "name"){
		    tok->view() >> tabInfo->name;
			tok->view() >> tab->name;
		} else if (*tok == "info"){
		    tok->view() >> tabInfo->info;
		} else if (*tok == "menuinfo"){
		    tok->view() >> tabInfo->menuInfo;
		} else if (parseDisplayList(tok, tab->getContext())){
        }else if (*tok == "option"){
		    try {
			CMenuOption *temp = factory.getOption(tab->getContext(), tok);
			if (temp){
			    Util::CReferenceCount<CMenuOption> ref(temp);
                tabInfo->options.push_back(ref);
                tab->addOption(ref);

			}
		    } catch (const CLoadException & le){
			tok->print(" ");
		    }
		}
	    } catch (const CTokenException & ex){
		// Output something
	    }
	}
	menu.addTab(tab);
	tabs.push_back(tabInfo);
    } else if ( *token == "position" ) {
        // This handles the placement of the menu list and surrounding box
        menu.setCoordinates(token);
    } else if ( *token == "relative-position"){
        menu.setCoordinates(token);
    } else if ( *token == "coordinate"){
        menu.setCoordinates(token);
    } else if ( *token == "position-body" ) {
        // This handles the body color of the menu box
        menu.setColors(token);
    } else if ( *token == "position-border" ) {
        // This handles the border color of the menu box
        menu.setColors(token);
     } else if ( *token == "transforms" ) {
        // This handles the border color of the menu box
        menu.setTransforms(token);
    } else if ( *token == "tab-body" ) {
        int r,g,b,a;
        token->view() >> r >> g >> b >> a;
		Colors::ColorDefinition tempColor = {clamp(r),clamp(g),clamp(b),clamp(a)};
		menu.tabColors.body = tempColor;
    } else if ( *token == "tab-border" ) {
        int r,g,b,a;
        token->view() >> r >> g >> b >> a;
        Colors::ColorDefinition tempColor = {clamp(r),clamp(g),clamp(b),clamp( a)};
		menu.tabColors.border = tempColor;
    } else if ( *token == "selectedtab-body" ) {
        int r,g,b,a;
        token->view() >> r >> g >> b >> a;
        Colors::ColorDefinition tempColor = {clamp(r),clamp(g),clamp(b),clamp(a)};
		menu.selectedTabColors.body = tempColor;
    } else if ( *token == "selectedtab-border" ) {
        int r,g,b,a;
        token->view() >> r >> g >> b >> a;
         Colors::ColorDefinition tempColor = {clamp(r),clamp(g),clamp(b),clamp(a)};
		menu.selectedTabColors.border = tempColor;
    } else if ( *token == "runningtab-body" ) {
        int r,g,b,a;
        token->view() >> r >> g >> b >> a;
        Colors::ColorDefinition tempColor = {clamp(r),clamp(g),clamp(b),clamp(a)};
		menu.runningTabColors.body = tempColor;
    } else if ( *token == "runningtab-border" ) {
        int r,g,b,a;
        token->view() >> r >> g >> b >> a;
        Colors::ColorDefinition tempColor = {clamp(r),clamp(g),clamp(b),clamp(a)};
		menu.runningTabColors.border = tempColor;
    } else if ( *token == "font-color" ) {
	int r,g,b;
        token->view() >> r >> g >> b;
		Colors::ColorDefinition tempColor = { clamp(r),clamp(g),clamp(b),255};
	menu.setTabFontColor(tempColor);
    } else if ( *token == "selectedfont-color" ) {
	int r,g,b;
        token->view() >> r >> g >> b;
		Colors::ColorDefinition tempColor = { clamp(r),clamp(g),clamp(b),255};
	menu.setSelectedTabFontColor(tempColor);
    } else if ( *token == "runningfont-color" ) {

    } else if ( *token == "fade-speed" ) {
        // Menu fade in speed
        int speed;
        token->view() >> speed;
        //menu.setFadeSpeed(speed);
	} else {
		    Debug::debug(Debug::menu,__FUNCTION__) << "END - Token: "<< token->getName()  <<"returning false"<< endl;
        return false;
    }
    Debug::debug(Debug::menu,__FUNCTION__) << "END - Token: "<< token->getName()  <<"returning true"<< endl;

    return true;
}

/*
void Menu::CTabRenderer::setFont(const Util::CReferenceCount<CFontInfo> & font){
    if (!font->empty()){
	menu.setFont(CConfiguration::getMenuFont_v2()->getFont(*font),
                     CConfiguration::getMenuFont_v2()->getWidth(*font),
                     CConfiguration::getMenuFont_v2()->getHeight(*font));
	menuInfo.setFont(font);
    }
}
*/

void Menu::CTabRenderer::initialize(CContext & context){
      const CFont & font = currentFont();
    // Menu info
    if (!context.getMenuInfoText().empty()){
        menuInfoBox.setText(context.getMenuInfoText());
        menuInfoBox.initialize(font);
        const int width = menuInfoBox.location.getWidth();
        const int height = menuInfoBox.location.getHeight();
        menuInfoBox.location.setPosition(Gui::CAbsolutePoint(context.getMenuInfoLocation().getX() - width/2, context.getMenuInfoLocation().getY() - height/2));
        // have to pass the dimensions back in to correct proper placement
        menuInfoBox.location.setPosition2(Gui::CAbsolutePoint(menuInfoBox.location.getX() + width,menuInfoBox.location.getY() + height));
        menuInfoBox.transforms.setRadius(menu.transforms.getRadius());
        menuInfoBox.colors = menu.colors;
    }

    menuInfoBox.open();

    if (tabs.size() > 0 && tabs[menu.getCurrentTab()]->options.size() > menu.getCurrentIndex()){
        // Add first info option
        addInfo(tabs[menu.getCurrentTab()]->options[menu.getCurrentIndex()]->getInfoText(), menu, context, font);
    }


}

void Menu::CTabRenderer::finish(){
    //menu.close();
    menuInfoBox.close();
}

bool Menu::CTabRenderer::active(){
    return true;//menu.isActive();
}

void Menu::CTabRenderer::act(const CContext & context){
    const CFont & font = currentFont();
    // FIXME find a better way to get options to update this is a waste
    for (vector<CTabInfo *>::iterator i = tabs.begin(); i != tabs.end(); ++i){
        CTabInfo * tab = *i;
        tab->act();
    }
    menu.act(font);
    menuInfoBox.act(font);
    actInfo(font);
}

void Menu::CTabRenderer::render(const CBitmap & bmp, const CFont & font){
    menu.render(bmp, font);
    menuInfoBox.render(bmp, font);
    renderInfo(bmp, font);
}

void Menu::CTabRenderer::addOption(CMenuOption * opt){
    //this->options.push_back(opt);
}

void Menu::CTabRenderer::doAction(const Actions & action, CContext & context){
    const CFont & font = currentFont();
	bool updateInfo = false;
    switch(action){
        case Up:
            menu._up(font);
            context.playSound(Up);
            updateInfo = true;
            break;
        case Down:
            menu.down(font);
            context.playSound(Down);
            updateInfo = true;
            break;
        case Left:
            menu.left(font);
            // setFont(context.getFont());
			context.playSound(Up);
            updateInfo = true;
            break;
        case Right:
            menu.right(font);
            // setFont(context.getFont());
			context.playSound(Down);
            updateInfo = true;
            break;
        case Select:
            try{
		if (!menu.isInTab()){
		    menu.toggleTabSelect();
		} else {
		       if (menu.getCurrentTab() < tabs.size() &&
                        menu.getCurrentIndex() < tabs[menu.getCurrentTab()]->options.size()){
                        tabs[menu.getCurrentTab()]->options[menu.getCurrentIndex()]->run(context);
			   }

		}
                context.playSound(Select);
            } catch (const Exception::Return & ex){
                //menu.open();
                menuInfoBox.open();
            }
	    // setFont(context.getFont());
            context.playMusic();
            updateInfo = true;
            break;
        case Cancel:
            context.playSound(Cancel);
	    if (menu.isInTab()){
		menu.toggleTabSelect();
	    } else {
		throw Exception::Return(__FILE__, __LINE__);
	    }
            break;
        default:
            break;
    }
	 if (updateInfo){
        if (tabs.size() > menu.getCurrentTab() &&
            tabs[menu.getCurrentTab()]->options.size() > menu.getCurrentIndex()){
            addInfo(tabs[menu.getCurrentTab()]->options[menu.getCurrentIndex()]->getInfoText(), menu, context, font);
        }
    }
}

Menu::CContext::CContext():
cleanup(true),
state(NotStarted),
fades(0),
//background(0),
font(NULL),
infoLocation(0, -.5),
menuInfoLocation(0,.95){
	 Debug::debug(Debug::menu,__FUNCTION__) << "Constructor" << endl;
}

Menu::CContext::CContext(const CContext & parent, const CContext & child):
cleanup(false),
state(NotStarted),
fades(NULL),
font(NULL),
infoLocation(0,-.5),
menuInfoLocation(0,.95),
/* include child's languages?? */
languages(parent.getLanguages()){
	Debug::debug(Debug::menu,__FUNCTION__) << "Begin Constructor " <<  endl;
    // Update with parents info
    fades = parent.fades;
    background = parent.background;
    sounds = parent.sounds;
    music = parent.music;
    // font = parent.font;
    infoLocation = parent.infoLocation;
    menuInfoLocation = parent.menuInfoLocation;

    // Then overwrite with childs
    if (child.fades != NULL){
        fades = child.fades;
    }

    if (!child.background.empty()){
        background = child.background;
    }

    if (!child.sounds.empty()){
        sounds = child.sounds;
    }

	if (child.music.exist()){
        music = child.music;
    }

    if (child.hasFont()){
        font = child.getFontInfo();
    } else if (parent.hasFont()){
        font = parent.getFontInfo();
    }

    /*
    const FontInfo & result = child.getFont()->get(*parent.getFont());
    if (child.getFont() == &result){
        font = child.getFont();
    } else {
        font = parent.getFont();
    }
    */

    /*
    if (child.getFont() != NULL){
        // Filesystem::exists(child.getFont()->getFont())){
        font = child.getFont();
    }
    */

    /* what are these magic numbers -.5 and .95? */
    if (child.infoLocation.getRelativeX() != 0 || child.infoLocation.getRelativeY() != -.5){
        infoLocation = child.infoLocation;
    }

    if (child.menuInfoLocation.getRelativeX() != 0 || child.menuInfoLocation.getRelativeY() != .95){
        infoLocation = child.infoLocation;
    }

    if (!child.menuInfo.empty()){
        menuInfo = child.menuInfo;
    }
	Debug::debug(Debug::menu,__FUNCTION__) << "End Constructor " <<  endl;
}

Menu::CContext::~CContext(){
    // Only delete if required

	if (cleanup){
        if (fades != NULL){
            delete fades;
        }

    }
}

vector<string> Menu::CContext::getLanguages() const {
    return languages;
}

void Menu::CContext::setLanguages(const vector<string> & languages){
    this->languages = languages;
}

bool Menu::CContext::hasFont() const {
    return font != NULL;
}
void Menu::CContext::parseToken(const Token * token){
	Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN token: "<< token->getName() << endl;
    if ( *token != "context" ){
        throw CLoadException(__FILE__, __LINE__, "Not a menu context");
    } else if (!token->hasTokens()){
        return;
    }
    // Token
    const Token * tok;
    token->view() >> tok;

    TokenView view = tok->view();
    while (view.hasMore()){
        const Token * context;
        view >> context;
        if (*context == "fade"){
            // Fade info
            if (!fades){
                fades = new Gui::CFadeTool();
            }
            // Set fader default to white
			fades->setFadeInColor(Colors::White);
			fades->setFadeOutColor(Colors::White);
            fades->setFadeInTime(25);
            fades->setFadeOutTime(12);

            // Load defaults
            fades->parseDefaults(context);
        } else if (*context == "animation" || *context == "background"){
            // Backgrounds
            addBackground(context);
        } else if (*context == ""){
        }
    }

}

void Menu::CContext::addBackground(const Token * token){
    Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN" << endl;
	// Backgrounds
       /*if (background == NULL){
        background = new Gui::AnimationManager();
    }*/

   background.add(Util::CReferenceCount<Gui::CAnimation>(new Gui::CAnimation(token)));

   Debug::debug(Debug::menu,__FUNCTION__) << "END" << endl;
}

void Menu::CContext::addBackground(const CBitmap & image){
	Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN" << endl;
 /*   if (!background){
        background = new CBackground();
    }
    background->add(new Gui::CAnimation(new CBitmap(image)));
   */
	background.add(Util::CReferenceCount<Gui::CAnimation>(new Gui::CAnimation(Util::CReferenceCount<CBitmap>(new CBitmap(image)))));


	Debug::debug(Debug::menu,__FUNCTION__) << "END" << endl;
   }

void Menu::CContext::addBackground(const string & image){
   Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN" << endl;
	// Backgrounds
/*    if (!background){
        background = new CBackground();
    }
   background->add(new Gui::CAnimation(image));
  */
  background.add(Util::CReferenceCount<Gui::CAnimation>(new Gui::CAnimation(image)));
  Debug::debug(Debug::menu,__FUNCTION__) << "NUMERO DE BITMAPS ADDED: "<< background.getSize() << endl;
   Debug::debug(Debug::menu,__FUNCTION__) << "END" << endl;
   }

void Menu::CContext::initialize(){
   Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN Intitializing The Context" << endl;
	if (fades){
        // state
        state = Initializing;
        // set fader state
        fades->setState(CFadeTool::FadeIn);
    } else {
        // Running
        state = Running;
    }
	Debug::debug(Debug::menu,__FUNCTION__) << "END Intitializing The Context" << endl;
}

void Menu::CContext::finish(){

	if (fades){
        // state
        state = Finishing;
        // set fader state
        fades->setState(CFadeTool::FadeOut);
    } else {
        // Completed
        state = Completed;
    }

	}

void Menu::CContext::playSound(const Actions & sound){

	if (sounds[sound].exist()){
        tryPlaySound(sounds[sound]);
    }

}


void Menu::CContext::addSound(const Actions & sound, const Filesystem::CRelativePath & path){
    sounds[sound] = path;
}

void Menu::CContext::playMusic(){
	Debug::debug(Debug::menu,__FUNCTION__) << "Music:" << music.path()<< endl;
    if (CResource::getMusic(music)){
		CMusic::pause();
		CMusic::play();
    }

	//if (Filesystem::exists(music)){
     //   if (CMusic::loadSong(Filesystem::getInstance().find(music).path())){
     //       CMusic::pause();
     //       CMusic::play();
     //   }
 //   }

}

void Menu::CContext::act(){
    Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN " << endl;
	// fader
    if (fades){
       fades->act();
       if (state == Initializing){
           if(fades->getState() == Gui::CFadeTool::NoFade){
               state = Running;
           }
       } else if (state == Finishing){
           if(fades->getState() == Gui::CFadeTool::EndFade){
               state = Completed;
           }
       }
    }
    // Backgrounds
    /*
	if (background){
        background->act(Gui::CCoordinate(Gui::CAbsolutePoint(0,0),Gui::CAbsolutePoint(CMenu_v2::Width, CMenu_v2::Height)));
    }*/
	background.act();
	Debug::debug(Debug::menu,__FUNCTION__) << "END " << endl;
}

void Menu::CContext::render(CMenuRenderer * renderer, const CBitmap & bmp){
	Debug::debug(Debug::menu,__FUNCTION__) << "Begin // rendered: " << renderer->getType() << " / CBitmap: "<< &bmp << endl;
	Debug::debug(Debug::menu,__FUNCTION__) << "Fase 1 - Draw Background " << endl;
	Debug::debug(Debug::menu,__FUNCTION__) << "NUMERO DE BACKGROUNDS TO RENDER: "<< background.getSize() << endl;

	if (!background.empty()){
        // background
        background.render(Gui::CAnimation::BackgroundBottom, bmp);
        background.render(Gui::CAnimation::BackgroundMiddle, bmp);
        background.render(Gui::CAnimation::BackgroundTop, bmp);
   } else {
        bmp.fill(CBitmap::makeColor(0,0,0));
    }
	//CBitmap *t=NULL;
	//t->clear();
	// para colocar o background na teala antes das opções
	bmp.setBitmapMode(CBitmap::DRAW_TYPE_TEXTURE);
	bmp.updateTexture();
	bmp.Blit();
    bmp.setBitmapMode(CBitmap::DRAW_TYPE_DEFAULT);
    Debug::debug(Debug::menu,__FUNCTION__) << "END Fase 1 - Draw Background " << endl;
	Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN Fase 2 - Draw Menu " << endl;
    // Menu
    if (renderer){
        renderer->render(bmp, currentFont());
    }
    Debug::debug(Debug::menu,__FUNCTION__) << "END Fase 2 - Draw Draw Menu " << endl;
	Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN Fase 3 - Draw Foreground " << endl;
 //
     if (!background.empty()){
        // foreground
        background.render(Gui::CAnimation::ForegroundBottom, bmp);
        background.render(Gui::CAnimation::ForegroundMiddle, bmp);
        background.render(Gui::CAnimation::ForegroundTop, bmp);
    }
     Debug::debug(Debug::menu,__FUNCTION__) << "END Fase 3 - Draw Foreground " << endl;
	 Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN Fase 4 - Draw Fades " << endl;

    // Fades
    if (fades){
        fades->draw(bmp);
    }

			Debug::debug(Debug::menu,__FUNCTION__) << "END Fase 4 - Draw Fades " << endl;
	Debug::debug(Debug::menu,__FUNCTION__) << "END " << endl;
}

void Menu::CContext::setFadeTool(Gui::CFadeTool *fade){
    fades = fade;
}


/* New Menu */

//====================================================
//CONSTRUTOR 1
/** @fn Menu::CMenu_v2::CMenu_v2(const Type & type)
@brief Construtor do Objeto CMenu_v2. Cria Um Bitmap (work), inicializa o input manager
@param const Type & type: tipo de menu de acordo com a enum Type.
@return construtores não retornam nada.
@warning utiliza o Type default se não for definido nenhum Type.
@warning não carrega nenhuma opção
**/
Menu::CMenu_v2::CMenu_v2(const Type & type) throw(CLoadException):
work(new CBitmap(CMenu_v2::Width, CMenu_v2::Height)),
defaultOptionFactory(COptionFactory()),
pCurInputManager(CInputManager::GetInstance()),
renderer(0),
type(type),
major(0),
minor(0),
micro(0)
{  //para que seja realizada imput do Menu é necessário antes iniciar a Classe CInput Manager.
    Debug::debug(Debug::menu,__FUNCTION__) << "Begin Creating New Renderer" << endl;
	setRenderer(type);
	  Debug::debug(Debug::menu,__FUNCTION__) << "End Creating New Renderer" << endl;//se esta classe não foi inicializada antes, ela será inicializada aqui
}
//====================================================
//CONSTRUTOR 2
/** @fn Menu::CMenu_v2::CMenu_v2(const Filesystem::CAbsolutePath & filename, const Type & type)
@brief Construtor do Objeto CMenu_v2. Cria Um Bitmap (work), inicializa o input manager, lê o token (filename) no objeto tr e carrega o token (load) lido no menu
@param const Filesystem::CAbsolutePath & filename: caminho do arquivo de definição <xml>
@param const Type & type: tipo de menu de acordo com a enum Type.
@return construtores não retornam nada.
@warning utiliza o Type default se não for definido nenhum Type.
**/
Menu::CMenu_v2::CMenu_v2(const Filesystem::CAbsolutePath & filename, const Type & type) throw(CLoadException):
work(new CBitmap(CMenu_v2::Width, CMenu_v2::Height)),
defaultOptionFactory(COptionFactory()),
pCurInputManager(CInputManager::GetInstance()),
renderer(0),
type(type),
major(0),
minor(0),
micro(0)
{
	//COptionFactory defaultFactory;
    // Load up tokenizer
    try{
        Debug::debug(Debug::menu,__FUNCTION__) << "Loading menu token" << filename.path() << endl;
        CTokenReaderXML tr(filename.path());
        Token * token = tr.readToken();
        load(token,defaultOptionFactory);
		Debug::debug(Debug::menu,__FUNCTION__) << "END Loading menu token " << filename.path() << endl;
    } catch (const CTokenException & e){
        throw CLoadException(__FILE__, __LINE__, e, "Error loading menu");
    }
}
//====================================================
//CONSTRUTOR 3
/** @fn Menu::CMenu_v2::CMenu_v2(const Filesystem::CAbsolutePath & filename,  const COptionFactory & defFactory, const Type & type)
@brief Construtor do Objeto CMenu_v2. Cria Um Bitmap (work), inicializa o input manager, lê o token (filename) no objeto tr e carrega o token (load) lido no menu
@param const Filesystem::CAbsolutePath & filename: caminho do arquivo de definição <xml>
@param const Type & type: tipo de menu de acordo com a enum Type.
@return construtores não retornam nada.
@warning utiliza o Type default se não for definido nenhum Type.
**/
Menu::CMenu_v2::CMenu_v2(const Filesystem::CAbsolutePath & filename,  const COptionFactory & defFactory, const Type & type) throw(CLoadException):
work(new CBitmap(CMenu_v2::Width, CMenu_v2::Height)),
defaultOptionFactory(defFactory),
pCurInputManager(CInputManager::GetInstance()),
renderer(0),
type(type),
major(0),
minor(0),
micro(0){

    // Load up tokenizer
    try{
        Debug::debug(Debug::menu,__FUNCTION__) << "Loading menu token" << filename.path() << endl;
        CTokenReaderXML tr(filename.path());
        Token * token = tr.readToken();
        load(token,defaultOptionFactory);
		Debug::debug(Debug::menu,__FUNCTION__) << "END Loading menu token " << filename.path() << endl;
    } catch (const CTokenException & e){
        throw CLoadException(__FILE__, __LINE__, e, "Error loading menu");
    }
}
//====================================================
//CONSTRUTOR 4
/** @fn Menu::CMenu_v2::CMenu_v2(const Token * token, const Type & type)
@brief Construtor do Objeto CMenu_v2. Cria Um Bitmap (work), inicializa o input manager,  carrega o token (load) passado como parâmetro no menu
@param const Token * token: objeto tipo Token que contem as definições do menu
@param const Type & type: tipo de menu de acordo com a enum Type.
@return construtores não retornam nada.
@warning utiliza o Type default se não for definido nenhum Type.
**/
Menu::CMenu_v2::CMenu_v2(const Token * token, const COptionFactory & defFactory,const Type & type) throw(CLoadException):
work(new CBitmap(CMenu_v2::Width, CMenu_v2::Height)),
defaultOptionFactory(defFactory),
pCurInputManager(CInputManager::GetInstance()),
renderer(0),
type(type),
major(0),
minor(0),
micro(0)
{
	if (!renderer) setRenderer(type);
	Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN Constructor - Will load Token: "<< token->getName()  << endl;
    load(token,defaultOptionFactory);
	Debug::debug(Debug::menu,__FUNCTION__) << "END Constructor "<< endl;
}
//====================================================
//CONSTRUTOR 5
Menu::CMenu_v2::CMenu_v2(const Token * token, const Type & type) throw(CLoadException):
work(new CBitmap(CMenu_v2::Width, CMenu_v2::Height)),
defaultOptionFactory(COptionFactory()),
pCurInputManager(CInputManager::GetInstance()),
renderer(0),
type(type),
major(0),
minor(0),
micro(0){
	Debug::debug(Debug::menu, __FUNCTION__) <<" First we will  set the Render"<<endl;
	if (!renderer) setRenderer(type);
    Debug::debug(Debug::menu, __FUNCTION__) <<" End setting the Render"<<endl;
	Debug::debug(Debug::menu, __FUNCTION__) <<" Now we will load de Menu"<<endl;
	load(token, defaultOptionFactory);
}
Menu::CMenu_v2::~CMenu_v2(){
    // Kill values
    for (map<string,CValueHolder *>::iterator i = data.begin(); i != data.end(); ++i){
        if (i->second){
            delete i->second;
        }
    }
	if(work) delete work;
    // Kill renderer
    if (renderer){
        delete renderer;
    }
}

void Menu::CMenu_v2::setFont(const Util::CReferenceCount<CFontInfo> & font){
    context.setFont(font);

    //if (renderer){
	//renderer->setFont(font);
    //}

}

void Menu::CMenu_v2::loadOption(const CMenuOption * option, const COptionFactory & factory) throw(CLoadException){
	string xmlFile = option->getDefFile();
	CTokenReaderXML tr(xmlFile);
	Token * token = tr.readToken();
    TokenView view = token->view();
		while (view.hasMore()){
		try {const Token * tok;
		view >> tok;
		renderer->readToken(tok,factory);

		/*if( *tok == "option" ) {
			try{
				CMenuOption *temp = COptionFactory::getOption(token);
				if (temp){
					addOption(temp);
				}
			} catch (const CLoadException & le){
            Debug::debug(Debug::menu,__FUNCTION__) << "Could not read option: " << le.getTrace() << endl;
            token->print(" ");
			}
		}
		*/
		}catch ( const CTokenException & ex ) {
		throw CLoadException(__FILE__, __LINE__, ex, "Menu parse error");
	    } catch (const CLoadException & ex){
		throw ex;
	    } catch (const Exception::Filesystem::CNotFound & ex){
		throw CLoadException(__FILE__, __LINE__, ex, "Menu parse error");
	    }
		}

}


//====================================================
/** @fn Menu::CMenu_v2::load(const Token * token)
@brief Carrega o objeto da classe Token que contém as características do menu
@param const Token * token: objeto tipo Token que contem as definições do menu
@return nada.
**/
void Menu::CMenu_v2::load(const Token * token, const COptionFactory & factory) throw(CLoadException){
    // version info;
    Debug::debug(Debug::menu,__FUNCTION__) << "Start Loading Menu Tokens" << endl;
    if (!token->hasTokens()){
        throw CLoadException(__FILE__, __LINE__, "Empty Menu");
    } else {
        // Get version
        // const Token * tok;
        // token->view() >> tok;
	const Token *ourToken = token->findToken("_/type");
        if (ourToken != NULL){
	    try {
		string menuType;
		ourToken->view() >> menuType;
		if (menuType == "default"){
		    type = Default;
		} else if (menuType == "tabbed"){
		    type = Tabbed;
		}
	    } catch (const CTokenException & ex){
	    }
	}
	ourToken = token->findToken("_/version");
        if (ourToken != NULL){
            try {
                ourToken->view() >> major >> minor >> micro;
            } catch (const CTokenException & ex){
            }
        } else {
                Debug::debug(Debug::menu,__FUNCTION__) << "No version indicated, assuming 1.0.0 or below." << endl;
                major = 1;
                minor = 0;
                micro = 0;
        }
    }
    Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN Creating New Renderer" << endl;
    setRenderer(type);
    Debug::debug(Debug::menu,__FUNCTION__) << "END Creating Renderer" << endl;
    if (Global::getVersion(major, minor, micro) != Global::getVersion()){
	// Do compatible translations if necessary
	handleCompatibility(token, Global::getVersion(major, minor, micro),factory);
    Debug::debug(Debug::menu,__FUNCTION__) << "NUMERO DE BITMAPS ADDED: "<< context.background.getSize() << endl;

	} else {
	handleCurrentVersion(token);
    }

}

typedef Menu::CMenu_v2 MenuClass;
class LanguageMenu: public Menu::CMenu_v2 {

public:
	class LanguageOption: public CMenuOption {
    public:
        LanguageOption(const Gui::CContextBox & box,const string & language):
        CMenuOption(box,NULL){
            setText(language);
            setInfoText(language);
        }

        virtual void logic(){
        }
		virtual void load(const Token *token)throw( CLoadException ) {};
		virtual void run(const Menu::CContext & context){
			CConfiguration::gameLanguage.setString(getText().c_str());
			CConfiguration::sm_saveConfiguration();
            throw Menu::CMenuException(__FILE__, __LINE__);
        }

    };
	void load(const Token * token, const COptionFactory & factory);

	static vector<string> findLanguages(const MenuClass & original){
     return original.getLanguages();
    }

    static vector<string> putEnglishFirst(vector<string> languages){
        vector<string> out;
        for (vector<string>::iterator it = languages.begin(); it != languages.end(); it++){
            const string & name = *it;
            if (name == "English"){
                out.insert(out.begin(), name);
            } else {
                out.push_back(name);
            }
        }
        return out;
    }
	LanguageMenu(const MenuClass & original){
        Menu::DefaultRenderer * renderer = (Menu::DefaultRenderer*) getRenderer();
        vector<string> languages = putEnglishFirst(findLanguages(original));
        for (vector<string>::iterator it = languages.begin(); it != languages.end(); it++){
            addOption(new LanguageOption(renderer->getBox(), *it));
        }
    }
};

void Menu::CMenu_v2::setupDefaultLanguage(const CContext & context, const MenuClass & parent){
    LanguageMenu menu(parent);
	Debug::debug(Debug::menu,__FUNCTION__) << "Will find font:" << sharedFont<< endl;

	if(CFontList::GetInstance()->isAvailable(sharedFont)){
	Util::CReferenceCount<CFontInfo> theFont = CFontList::GetInstance()->findFont(sharedFont);
	theFont->setHeight(sharedFontHeight);
	theFont->setWidth(sharedFontWidth);
	menu.setFont(theFont);
	}else throw Menu::CMenuException(__FUNCTION__,__LINE__," Font do not exist");


	CConfiguration::gameLanguage.setString("English");
    try{
        menu.run(context);
    } catch (const Menu::CMenuException & ignore){
    }
}
/** @fn Menu::CMenu_v2::openOptions()
@brief Executa operações de abertura (do método virtual open()) das opções
cada opção pode adicionar tarefas de abertura, overriding o método open
@param
@return nenhum.
@warning
**/
void Menu::CMenu_v2::openOptions(){
	vector<Util::CReferenceCount<CMenuOption> > options = getRenderer()->getOptions();
    for (vector<Util::CReferenceCount<CMenuOption> >::iterator it = options.begin(); it != options.end(); it++){
        Util::CReferenceCount<CMenuOption> & option = *it;
        Debug::debug(Debug::menu,__FUNCTION__) << "Will open Option: " << option->getName()<< endl;

		option->open();
    }

}

/** @fn Menu::CMenu_v2::closeOptions()
@brief Executa operações de fechamento (do método virtual close()) das das opções
cada opção pode adicionar tarefas de fechamento, overriding o método close
@param
@return nenhum.
@warning
**/
void Menu::CMenu_v2::closeOptions(){
	Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN CLOSING OPTIONS"<<endl;
      vector<Util::CReferenceCount<CMenuOption> > options = getRenderer()->getOptions();
    for (vector<Util::CReferenceCount<CMenuOption> >::iterator it = options.begin(); it != options.end(); it++){
        Util::CReferenceCount<CMenuOption> & option = *it;
        option->close();
    }
	Debug::debug(Debug::menu,__FUNCTION__) << "END CLOSING OPTIONS"<<endl;
}

vector<string> Menu::CMenu_v2::getLanguages() const {
    return languages;
}

/** @fn Menu::CMenu_v2::run(const CContext & parentContext)
@brief Método que executa o menu
@param	CContext & ourContext: contexto do menu
@return nenhum.
@warning
**/
void Menu::CMenu_v2::run(const CContext & parentContext){
	Debug::debug(Debug::menu,__FUNCTION__) << "Begin Running the Menu V2" << endl;
    /* TODO: replace with Parameter */
   CKeyboard::pushRepeatState(true);
   try{
		Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN FASE 1 - Initialize de Context" << endl;
        // Setup context from parent and this menu and initialize
        CContext localContext(parentContext, context);
        SGF::Util::CParameter<Util::CReferenceCount<CFontInfo> > currentFont;
        if (context.hasFont()){
            currentFont.push(context.getFontInfo());
        }
        localContext.initialize();
		Debug::debug(Debug::menu,__FUNCTION__) << "END FASE 1 - Initialize de Context" << endl;
        Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN FASE 2 - Initialize de Renderer" << endl;

		 /* Not sure if this is the right place to set the languages.
         * For now the semantics is that if a sub-menu specifies a set
         * of languages then we will use those, otherwise the
         * languages will come from the parentContext.
         *
         * getLanguages() is supposed to hold at least one language
         * which might be English, the default.
         *
         * This logic is sort of lame.. fix it.
         */
        if (getLanguages().size() > 1 || (getLanguages().size() == 1 && getLanguages()[0] != "English")){
            localContext.setLanguages(getLanguages());
        }
        // Setup menu fonts etc
        if (renderer){
            renderer->initialize(localContext);
			// Invoke Override if available
            //renderer->invokeOverride(localContext);
        }
       Debug::debug(Debug::menu,__FUNCTION__) << "END FASE 2.a - Initialize de Renderer" << endl;
		Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN FASE 2.b - Play Music" << endl;

        //Play music
        localContext.playMusic();
		Debug::debug(Debug::menu,__FUNCTION__) << "END FASE 2.b - Play Music" << endl;
		Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN FASE 2.c - Set Language" << endl;

        if (CConfiguration::gameLanguage.getString() == ""){
			
            setupDefaultLanguage(localContext, *this);
        }
		Debug::debug(Debug::menu,__FUNCTION__) << "END FASE 2.c - Set language" << endl;
		Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN FASE 3 - Open Options" << endl;

        /* do any lazy loading options want to do */
        openOptions();
		Debug::debug(Debug::menu,__FUNCTION__) << "END FASE 3 - Open Options" << endl;

		//CBitmap *ttt=NULL;
		//			ttt->clear();

        /* vi keys -- make these optional? */
        input.set(CKeyboard::Key_J, 0, true, Down);
        input.set(CKeyboard::Key_K, 0, true, Up);
        input.set(CKeyboard::Key_H, 0, true, Left);
        input.set(CKeyboard::Key_L, 0, true, Right);
        input.set(CKeyboard::Key_UP, 0, true, Up);
        /* regular keys */
		input.set(CConfiguration::getConfig(CConfiguration::Player1)->getKey("key-down"), 0,true, Down);
        input.set(CConfiguration::getConfig(CConfiguration::Player1)->getKey("key-left"), 0, true, Left);
        input.set(CConfiguration::getConfig(CConfiguration::Player1)->getKey("key-right"), 0, true, Right);
        //S input.set(CKeyboard::Key_F11, 0, true, Fullscreen);
        /* FIXME: use configuration keys */
        input.set(CKeyboard::Key_ENTER, 0, true, Select);
        input.set(CKeyboard::Key_ESC, 0, true, Cancel);
        /* joystick */
        input.set(CConfiguration::getConfig(0)->getKey("joykey-up"), 0, true, Up);
        input.set(CConfiguration::getConfig(0)->getKey("joykey-down"), 0, true, Down);
        input.set(CConfiguration::getConfig(0)->getKey("joykey-left"), 0, true, Left);
        input.set(CConfiguration::getConfig(0)->getKey("joykey-right"), 0, true, Right);
        /*! FIXME this should be changed to Select/Cancel buttons, all other buttons should be Select */
		input.set(CConfiguration::getConfig(0)->getKey("joykey-select"), 0, true, Select);
        input.set(CConfiguration::getConfig(0)->getKey("joykey-cancel"), 0, true, Cancel);
		/* mouse */
		input.set(CConfiguration::getConfig(0)->getKey("mousekey-up"), 0, true, Up);
		input.set(CConfiguration::getConfig(0)->getKey("mousekey-down"), 0, true, Down);
		//input.set(CConfiguration::getConfig(0).getMouseButtonLeft(), 0, true, Left);
		//input.set(CConfiguration::getConfig(0).getMouseButtonRight(), 0, true, Right);
		input.set(CConfiguration::getConfig(0)->getKey("mousekey-select"), 0, true, Select);
		input.set(CConfiguration::getConfig(0)->getKey("mousekey-cancel"), 0, true, Cancel);
		//input.set(CMouse::Key_WUP, 0, true, Up);
		//input.set(CMouse::Key_WDOWN, 0, true, Down);
        input.set(CMouse::Key_MoveLEFT, 0, true, Left);
		input.set(CMouse::key_MoveRIGHT, 0, true, Right);
		input.set(CMouse::Key_LEFT, 0, true, Select);


        class Logic: public Input::CLogic {
        public:
            Logic(CMenu_v2 & menu, CContext & localContext, CMenuRenderer * renderer):
            menu(menu),
            localContext(localContext),
            renderer(renderer){
            }

            CMenu_v2 & menu;
            CContext & localContext;
            CMenuRenderer * renderer;

            void run(int delay=0){

                try {
					Debug::debug(Debug::menu,__FUNCTION__) << "Begin Running Menu Logic" << endl;

                    menu.act(localContext);
					Debug::debug(Debug::menu,__FUNCTION__) << "End Running Menu Logic" << endl;
                } catch (const Exception::Return & ex){
                    Debug::debug(Debug::menu,__FUNCTION__) << "PEGUEI RETURN EXCEPTION" << endl;

					// signaled to quit current menu, closing this one out
                    localContext.finish();
                    if (renderer){
                        renderer->finish();
                    }
                }
            }

            double ticks(double system){
                return system * Global::LOGIC_MULTIPLIER;
            }

            bool done(){
                return localContext.getState() == CContext::Completed ||
                       !(renderer && renderer->active());
            }
        };

        class Draw: public Input::CDraw {
        public:
            Draw(CMenu_v2 & menu, CContext & localContext,CBitmap *_work):
            menu(menu),
            localContext(localContext),
            work(_work){
            }

            CMenu_v2 & menu;
            CContext & localContext;
            CBitmap *work;

            void draw(double FPS){
				Debug::debug(Debug::menu,__FUNCTION__) << "Begin Drawing Menu" << endl;
                SGF::Util::CParameter<Util::CReferenceCount<CFontInfo> > currentFont;
                if (CConfiguration::hasMenuFont()){
					currentFont.push(CConfiguration::getMenuFont_v2());

                }
                menu.render(localContext, *work);
				if (true){
				CResource::getDefaultFont()->DrawTextNew(0,50,Colors::White, *work,"%2.2f FPS",fps);

				Debug::debug(Debug::gameEngine,__FUNCTION__) << " FRAME y =========================" <<80-100<< endl;
             }
			work->updateTexture();
			work->BlitToScreen();
				//work->setBitmapMode(CBitmap::DRAW_TYPE_TEXTURE);
				//work->updateTexture();
				//work->Blit();
                //work->BlitToScreen();
				//work->setBitmapMode(CBitmap::DRAW_TYPE_DEFAULT);
				//Debug::debug(Debug::menu,__FUNCTION__) << "End Drawing Menu" << endl;
            }
			
        };
		Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN FASE 4 - Initilize Logic and Draw" << endl;

		Logic logic(*this, localContext, renderer);
        Draw draw(*this, localContext, work);
		Debug::debug(Debug::menu,__FUNCTION__) << "End Initilize Logic and Draw" << endl;
		Debug::debug(Debug::menu,__FUNCTION__) << "Begin running Loop" << endl;
        Input::SGE_standardLoop(logic, draw);
        Debug::debug(Debug::menu,__FUNCTION__) << "End running Loop" << endl;
        closeOptions();

        // FIXME Menu is finished, lets return. Is this even required anymore?
        throw Exception::Return(__FILE__, __LINE__);
    } catch (...){
        CKeyboard::popRepeatState();
        throw;
    }
}

/** @fn Menu::CMenu_v2::act(CContext & ourContext)
@brief Método que realiza todo o processamento do Menu, verificando e executando as ações
		determinadas pelo acionamento das teclas, etc
@param	CContext & ourContext: contexto do menu
@return nenhum.
@warning
**/
void Menu::CMenu_v2::act(CContext & ourContext){
     Debug::debug(Debug::menu,__FUNCTION__) << "Begin Act our context: "<< &context << endl;
	 Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN FASE 1 - Get Events "<<  endl;
	 vector<CInputMap<Actions>::InputEvent> events = CInputManager::getEvents(input);
	 Debug::debug(Debug::menu,__FUNCTION__) << "END FASE 1 - Got Events: "<< events.size()<<  endl;
	 Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN FASE 2 - Proccess Events "<<  endl;
    for (vector<CInputMap<Actions>::InputEvent>::iterator it = events.begin(); it != events.end(); it++){
        const CInputMap<Actions>::InputEvent & event = *it;

		if (!event.enabled){
            continue;
        }

        if (event.out == Cancel){
            if (renderer){
                CInputManager::waitForRelease(input, Cancel);
                renderer->doAction(Cancel, ourContext);
            } else {
                ourContext.playSound(Cancel);
                CInputManager::waitForRelease(input, Cancel);
                throw Exception::Return(__FILE__, __LINE__);
            }
        }

       //S if (event.out == Fullscreen){
       //S     changeScreenMode();
       //S }

		Debug::debug(Debug::menu,__FUNCTION__) << "Will Begin Render Things using renderer: "<< renderer->getType() << endl;
        if (renderer){
            switch (event.out){
                case Up: renderer->doAction(Up, ourContext); break;
                case Down: renderer->doAction(Down, ourContext); break;
                case Left: renderer->doAction(Left, ourContext); break;
                case Right: renderer->doAction(Right, ourContext); break;
                case Select: renderer->doAction(Select, ourContext); break;
                default: break;
            }
        }
    }
    Debug::debug(Debug::menu,__FUNCTION__) << "END FASE 2 - Proccess Events "<<  endl;
    if (renderer){
		Debug::debug(Debug::menu,__FUNCTION__) << "Will Use Reference Count: "<< endl;
        SGF::Util::CParameter<Util::CReferenceCount<CFontInfo> > currentFont;
        if (CConfiguration::hasMenuFont()){
            currentFont.push(CConfiguration::getMenuFont_v2());
        }
        renderer->act(ourContext);
    }
	 /*
    // Act context
    ourContext.act();
	*/
    Debug::debug(Debug::menu,__FUNCTION__) << "End Act" << endl;
}
/** @fn Menu::CMenu_v2::render(CContext & ourContext, const CBitmap & bmp)
@brief Desenha o Menu na tela chamando o método render do Contexto passado
@param	CContext & ourContext: contexto do menu
		const CBitmap & bmp: Bitmap destino
@return nenhum.
@warning
**/
void Menu::CMenu_v2::render(CContext & ourContext, const CBitmap & bmp){
    // Render context
    ourContext.render(renderer, bmp);
}

string Menu::CMenu_v2::getName(){
    string name;
    try {
        if (data["name"]){
            *data["name"] >> name;
        }
    } catch (const CMenuException & ex){
    }
    return name;
}

string Menu::CMenu_v2::getInfo(){
    string name;
    try {
        if (data["info"]){
            *data["info"] >> name;
        }
    } catch (const CMenuException & ex){
    }
    return name;
}

void Menu::CMenu_v2::addData(CValueHolder * item){
    std::pair<map<string,CValueHolder *>::iterator,bool> check;
    check = data.insert( std::pair<string,CValueHolder *>(item->getName(),item) );
    if (check.second == false){
        Debug::debug(Debug::menu,__FUNCTION__) << "Value \"" << check.first->second->getName() << "\" already exists - (" << check.first->second->getValues() << ")." << endl;
        Debug::debug(Debug::menu,__FUNCTION__) << "Replacing with value \"" << item->getName() << "\" -  (" << item->getValues() << ")." << endl;
        data[item->getName()] = item;
    }
}

void Menu::CMenu_v2::handleCurrentVersion(const Token * token) throw(CLoadException){
    TokenView view = token->view();
    while (view.hasMore()){
        try{
            const Token * tok;
            view >> tok;
            // Newer items
            if (*tok == "val" || *tok == "value"){
                const Token * val;
                tok->view() >> val;
                CValueHolder * value = new CValueHolder(val->getName());
                TokenView valueView = val->view();
                try {
                    while (true){
                        *value << valueView;
                    }
                } catch (const CTokenException & ex){
                }
                addData(value);
            } else if (*tok == "context"){
                context.parseToken(tok);
            } else {
                Debug::debug(Debug::menu,__FUNCTION__) <<"Unhandled menu attribute: "<<endl;
               // if (Debug::getDebug() >= 3){
               //     tok->print(" ");
               // }
            }
        } catch ( const CTokenException & ex ) {
            throw CLoadException(__FILE__, __LINE__, ex, "Menu parse error");
        } catch (const CLoadException & ex){
            throw ex;
        } catch (const Exception::Filesystem::CNotFound & ex){
            throw CLoadException(__FILE__, __LINE__, ex, "Menu parse error");
        }
    }
}
/** @fn Menu::CMenu_v2::handleCompatibility(const Token * token, int version)
@brief Quando o arquivo de definição foi feito para o menu V1 este método lê
os valores e inicializa corretamente as variáveis do menu V2
@param	const Token * token
		int version: vesão do menu (1 versão anterior ou 2 versão atual)
@return nenhum.
@warning se no arquivo de definição não tiver o token version é assumida versão 1
**/
void Menu::CMenu_v2::handleCompatibility(const Token * token, int version, const COptionFactory & factory){
    Debug::debug(Debug::menu,__FUNCTION__) << "Trying version: " << version << endl;
    if (version <= Global::getVersion(3, 3, 1)){
		Debug::debug(Debug::menu,__FUNCTION__) << "Version Requires Compatibility "  << endl;
		Debug::debug(Debug::menu,__FUNCTION__) << "------------------ BEGIN LOOP WHILE-------------------- "  << endl;
        const Token * languages = token->findToken("_/languages");
        if (languages != NULL){
            try{
                TokenView view = languages->view();
                while (true){
                    string language;
                    view >> language;
                    this->languages.push_back(language);
                }
            } catch (const CTokenException & fail){
            }
        }
        if (this->languages.size() == 0){
            this->languages.push_back("English");
        }

		TokenView view = token->view();
		while (view.hasMore()){

	    try {
		const Token * tok;
		view >> tok;
		Debug::debug(Debug::menu,__FUNCTION__) << "Begin Loop While: Token Name: "<< tok->getName()  << endl;
		if ( *tok == "version" ){
		    //CValueHolder * value = new CValueHolder("version");
            //Todo - Set Version;
		}

		else if ( *tok == "name" ){
		    CValueHolder * value = new CValueHolder("name");
            TokenView nameView = tok->view();
		    *value << nameView;
		    addData(value);
			Debug::debug(Debug::menu,__FUNCTION__) << "Name : " << value->getName() << endl;
		} else if ( *tok == "music" ) {
		    CValueHolder * value = new CValueHolder("music");
                    TokenView musicView = tok->view();
		    *value << musicView;
			addData(value);
		    try {
			string music;
			*value >> music;
			Debug::debug(Debug::menu,__FUNCTION__) << "Setting Context Music: " << music << endl;
  			context.setMusic(Filesystem::CRelativePath(music));
		    } catch (const CMenuException & ex){
		    }
		} else if( *tok == "select-sound" ) {
		    CValueHolder * value = new CValueHolder("select-sound");
                    TokenView soundView = tok->view();
		    *value << soundView;
		    addData(value);
		    try{
			string sound;
			*value >> sound;
			Debug::debug(Debug::menu,__FUNCTION__) << "Setting Context Up and Down Sound: " << sound << endl;
			context.addSound(Up,Filesystem::CRelativePath(sound));
			context.addSound(Down,Filesystem::CRelativePath(sound));
		    } catch (const CMenuException & ex){
		    }
		} else if (*tok == "back-sound"){
		    CValueHolder * value = new CValueHolder("back-sound");
                    TokenView soundView = tok->view();
		    *value << soundView;
		    addData(value);
		    try{
			string sound;
			*value >> sound;
			Debug::debug(Debug::menu,__FUNCTION__) << "Setting Context Back and Cancel Sound: " << sound << endl;
			context.addSound(Back,Filesystem::CRelativePath(sound));
			context.addSound(Cancel,Filesystem::CRelativePath(sound));
		    } catch (const CMenuException & ex){
		    }
		} else if (*tok == "ok-sound"){
		    CValueHolder * value = new CValueHolder("ok-sound");
                    TokenView okView = tok->view();
		    *value << okView;
		    addData(value);
		    try{
			string sound;
			*value >> sound;
			Debug::debug(Debug::menu,__FUNCTION__) << "Setting Context Select Sound: " << sound << endl;
			context.addSound(Select,Filesystem::CRelativePath(sound));

			} catch (const CMenuException & ex){
		    }
		}

		else if ( *tok == "background" ) {
		    string temp;
		    tok->view() >> temp;
			Debug::debug(Debug::menu,__FUNCTION__) << "Setting Context Background: " << temp << endl;
		    context.addBackground(temp);
		    Debug::debug(Debug::menu,__FUNCTION__) << "NUMERO DE BITMAPS ADDED: "<< context.background.getSize() << endl;


		}

		else if (*tok == "anim"){
			Debug::debug(Debug::menu,__FUNCTION__) << "Setting Context Anim: " << tok->getName() << endl;
		    context.addBackground(tok);
		}
		 else if ( *tok == "clear-color" ) {
		    // Not necessary ignore
		}

		 else if ( renderer && renderer->readToken(tok,factory) ) {
			// Verify the options token

		    // Nothing checks compatible version of renderer
		}

		 else if ( *tok == "font" ) {
		    CValueHolder * value = new CValueHolder("font");
                    TokenView fontView = tok->view();
		    *value << fontView << fontView << fontView;
		    addData(value);
		    try {
			string font;
			int w = 24, h = 24;
			*value >> font >> w >> h;
			Debug::debug(Debug::menu,__FUNCTION__) << "Setting Context font: "<<font<<" /  w,h: " << w << " , " << h << endl;
			font=Filesystem::stripDir(font);
			if (CFontList::GetInstance()->isAvailable(font)){
				const Util::CReferenceCount<CFontInfo> & reffont = CFontList::GetInstance()->findFont(font);
				reffont->setHeight(w);
				reffont->setWidth(h);
				context.setFont(reffont);
				Debug::debug(Debug::menu,__FUNCTION__) << "Context Font seted up:  "<< &reffont  << endl;
			}else throw CMenuException(__FUNCTION__,__LINE__,"Font not Exist");
			} catch (const CMenuException & ex){
		    }
		} else if ( *tok == "action"){
		    // Set speed
		    //ActionAct(tok);
		} else if ( *tok == "info-position"){
		    CValueHolder * value = new CValueHolder("info-position");
                    TokenView infoView = tok->view();
		    *value << infoView << infoView;
		    addData(value);
		    try {
			double x=0, y=-.5;
			int centerx = 640/2;
			int centery = 480/2;
			*value >> x >> y;
			Debug::debug(Debug::menu,__FUNCTION__) << "Setting InfoBoxposition x,y: " << x << " , " << y << endl;
			x = (double)(x-centerx)/centerx;
			y = (double)(y-centery)/centery;
			context.setInfoLocation(x,y);
		    } catch (const CMenuException & ex){
		    }
		} else if (*tok == "menuinfo"){
		    CValueHolder * value = new CValueHolder("menuinfo");
            TokenView infoView = tok->view();
		    *value << infoView;
		    addData(value);
		    try {
			string info;
			*value >> info;
			Debug::debug(Debug::menu,__FUNCTION__) << "Setting Menu Info text: " << info << endl;
			context.setMenuInfoText(info);

		    } catch (const CMenuException & ex){
		    }
		} else if (*tok == "menuinfo-position"){
		    CValueHolder * value = new CValueHolder("menuinfo-position");
            TokenView infoView = tok->view();
		    *value << infoView << infoView;
		    addData(value);
		    try {
			double x=0, y=.95;
			*value >> x >> y;
			Debug::debug(Debug::menu,__FUNCTION__) << "Setting Menu Info Position x,y: " << x << " , " << y << endl;
			context.setMenuInfoLocation(x,y);
		    } catch (const CMenuException & ex){
		    }
		}

		else {
		    Debug::debug(Debug::menu,__FUNCTION__) <<"Unhandled menu attribute: "<<endl;
		    //if (Debug::getDebug() >= 3){
			//tok->print(" ");
		    //}
		}
		Debug::debug(Debug::menu,__FUNCTION__) << "End Loop While Iteration: "<< tok->getName() << endl;
	    } catch ( const CTokenException & ex ) {
		throw CLoadException(__FILE__, __LINE__, ex, "Menu parse error");
	    } catch (const CLoadException & ex){
		throw ex;
	    } catch (const Exception::Filesystem::CNotFound & ex){
		throw CLoadException(__FILE__, __LINE__, ex, "Menu parse error");
	    }
	   Debug::debug(Debug::menu,__FUNCTION__) << "--------------------------- "  << endl;
	}
	Debug::debug(Debug::menu,__FUNCTION__) << "------------------ END LOOP WHILE-------------------- "  << endl;

	Debug::debug(Debug::menu,__FUNCTION__) << "END " << endl;
    }
	Debug::debug(Debug::menu,__FUNCTION__) << "NUMERO DE BITMAPS ADDED: "<< context.background.getSize() << endl;

}

void Menu::CMenu_v2::setRenderer(const Type & type){
    if (renderer){
        delete renderer;
    }
    renderer = rendererType(type);
}

Menu::CMenuRenderer * Menu::CMenu_v2::rendererType(const Type & type){
    switch (type){
	case Tabbed: {
	    return new CTabRenderer();
	    break;
        }
	case Default:
	default: {
	    return new DefaultRenderer();
	    break;
        }
    }
}
}
} //end SGF