#ifndef _font_render_h
#define _font_render_h

#include <string>
#include <vector>

#include "../util/SGF_FontSystem.h"
#include "../util/SGF_FileSystem.h"
namespace SGF{

class CBitmap;


struct render_message{
	render_message( const CFont & f, int x, int y, int sizeX, int sizeY, Colors::ColorDefinition fg, Colors::ColorDefinition bg, int translucency, const string & str ):r_font( f ){
            this->sizeX = sizeX;
            this->sizeY = sizeY;
            this->x = x;
            this->y = y;
            this->fg = fg;
            this->bg = bg;
            this->str = str;
            this->translucency = translucency;
	}

	render_message( const render_message & c ):
		r_font( c.r_font ){
                sizeX = c.sizeX;
                sizeY = c.sizeY;
		x = c.x;
		y = c.y;
		fg = c.fg;
		bg = c.bg;
		str = c.str;
                translucency = c.translucency;
	}

	render_message & operator=( const render_message & rhs ){
		if ( this == &rhs ) return *this;

		/*
		this->r_font = rhs.r_font;
		this->x = rhs.x;
		this->y = rhs.y;
		this->fg = rhs.fg;
		this->bg = rhs.bg;
		this->str = rhs.str;
		*/
		return *this;
	}

	const CFont & r_font;
        int sizeX;
        int sizeY;
	int x;
	int y;
		Colors::ColorDefinition fg;
        Colors::ColorDefinition bg;
        string str;
        int translucency;
};

/* factory class to render strings later on */
class CFontRender{
public:

	static CFontRender * getInstance();
	static void destroy();

	void addMessage(const CFont & f, int x, int y, Colors::ColorDefinition  fg, Colors::ColorDefinition  bg, const string & str);
	void addMessage(const CFont & f, int x, int y, Colors::ColorDefinition  fg, Colors::ColorDefinition  bg, int translucency, const string & str);
	void addMessage(const CFont & f, int x, int y, Colors::ColorDefinition  fg, Colors::ColorDefinition  bg, const char * str, ...);
	void addMessage(const Filesystem::CRelativePath & font_name, int x, int y, Colors::ColorDefinition  fg, Colors::ColorDefinition  bg, const string & str );
	void render(const CBitmap * work);

private:

	static CFontRender * my_render;

    vector<render_message> my_messages;

};
} //end SGF
#endif
