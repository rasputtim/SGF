#include "graphics/all.h"
#include <string>
#include <vector>
#include <stdarg.h>
#include "util/SGF_FontSystem.h"
#include "util/SGF_Util.h"
#include "resource/all.h"

using namespace std;
using namespace std;
namespace SGF {

/*
struct render_message{
	render_message( Font * f, int x, int y, int fg, int bg, const string & str ){
		r_font = f;
		this->x = x;
		this->y = y;
		this->fg = fg;
		this->bg = bg;
		this->str = str;
	}

	render_message( const render_message & c ){
		r_font = c.r_font;
		x = c.x;
		y = c.y;
		fg = c.fg;
		bg = c.bg;
		str = c.str;
	}

	Font * r_font;
	int x;
	int y;
	int fg;
	int bg;
	string str;
};
*/

CFontRender * CFontRender::my_render = NULL;
CFontRender * CFontRender::getInstance(){
	if ( my_render == NULL )
		my_render = new CFontRender();
	return my_render;
}

void CFontRender::destroy(){
	if ( my_render != NULL )
		delete my_render;
}

void CFontRender::render(const CBitmap * work ){
	for ( vector<render_message>::iterator it = my_messages.begin(); it != my_messages.end(); it++ ){
		const render_message & r = *it;

                /* FIXME: replace with work->translucent() */
                if (r.translucency != -1){
                    CBitmap::transBlender(0, 0, 0, r.translucency);
                    //S work->drawingMode( CBitmap::MODE_TRANS );
                }

		// work->printf( r.x, r.y, r.fg, r.r_font, r.str );
		//S r.r_font.printf( r.x, r.y, r.sizeX, r.sizeY, r.fg, *work, r.str, 0 );
		// work->printf( ky + x1, y1, Bitmap::makeColor(255,255,255), player_font, getName() );
                if (r.translucency != -1){
                    //S work->drawingMode( CBitmap::MODE_SOLID );
                }
	}
	my_messages.clear();
}

void CFontRender::addMessage( const CFont & f, int x, int y, Colors::ColorDefinition fg, Colors::ColorDefinition bg, int translucency, const string & str ){
    render_message r( f, x, y, f.getSizeX(), f.getSizeY(), fg, bg, translucency, str );
    my_messages.push_back( r );
}

void CFontRender::addMessage( const CFont & f, int x, int y, Colors::ColorDefinition fg, Colors::ColorDefinition bg, const string & str ){
    addMessage(f, x, y, fg, bg, -1, str);
}

void CFontRender::addMessage( const CFont & f, int x, int y, Colors::ColorDefinition fg, Colors::ColorDefinition bg, const char * str, ... ){
	char buf[1024];
	va_list ap;

	va_start(ap, str);
        Util::limitPrintf(buf, sizeof(buf), str, ap);
	va_end(ap);
	string mm( buf );
	addMessage( f, x, y, fg, bg, -1, mm );
}
	
void CFontRender::addMessage(const Filesystem::CRelativePath & font_name, int x, int y, Colors::ColorDefinition fg, Colors::ColorDefinition bg, const string & str ){
    addMessage(CFont::getFont(font_name), x, y, fg, bg, -1, str );
}
} //end SGF