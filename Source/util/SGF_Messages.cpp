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

#include "util/SGF_MessageQueue.h"
#include "util/SGF_Messages.h"
namespace SGF {

namespace Messages {

/* should support infinite queues eventually */
static MessageQueue * current = NULL;

void registerInfo(MessageQueue * queue){
    current = queue;
}

void unregisterInfo(MessageQueue * queue){
    if (current == queue){
        current = NULL;
		
    }
}

void info(const string & str){
    if (current != NULL){
		current->add(str);
    }
}


CMessages::CMessages( int width, int height, int opaque ):
width(width),
height(height),
opaque(opaque),
borderColor(Colors::Thistle){
}

static vector< string > wrapStrings( const string & left, const string & right, const CFont & font, int max, vector< string > accum ){
    if (left == ""){
        return accum;
    }

    int length = font.getTextLength(left.c_str());

    if (length >= max){
        return wrapStrings(left.substr( 0, left.length() / 2 ), left.substr( left.length() / 2 ) + right, font, max, accum);
    } else if (length >= max - font.getTextLength("E") || right == ""){
        accum.push_back(left);
        return wrapStrings(right, "", font, max, accum);
    } else {
        string newleft = left + right.substr(0, 1);
        /* edge case where adding one character goes over the limit. in that
         * case treat it as the 2nd case.
         */
        if (font.getTextLength(newleft.c_str()) >= max - font.getTextLength("E")){
            accum.push_back(left);
            return wrapStrings(right, "", font, max, accum);
        }
        return wrapStrings(newleft, right.substr(1), font, max, accum);
    }
}

/*
static int wrapPrint( const Bitmap & area, int y, int top, const CFont & font, const string & left, const string & right ){
	if ( left == "" ){
		return top;
	}

	int length = font.textLength( left.c_str() );
	int max = area.getWidth();

	if ( length >= max ){
		return wrapPrint( area, y - font.getHeight(), top - font.getHeight(), font, left.substr( 0, left.length() / 2 ), left.substr( left.length() / 2 ) + right );
	} else if ( length >= max - font.textLength( "E" ) || right == "" ){
		font.printf( 0, y, Bitmap::makeColor( 255, 255, 255 ), area, left, 0 );
		return wrapPrint( area, y + font.getHeight(), top, font, right, "" );
	} else {
		return wrapPrint( area, y, top, font, left + right.substr( 0, 1 ), right.substr( 1 ) );
	}
}
*/

void CMessages::addMessage( const string & s ){
	messages.push_back( s );
}
	
void CMessages::draw( int x, int y, const CBitmap & work, const CFont & font ){
    // work.drawingMode( Bitmap::MODE_TRANS );
    CBitmap::transBlender(0, 0, 0, this->opaque);
    work.translucent().rectangleFill( x, y, x + width, y + height, Colors::makeColor( 0, 0, 0 ) );
    // work.drawingMode( Bitmap::MODE_SOLID );
    // work.rectangle( x, y, x + width-1, y + height-1, Bitmap::makeColor( 255, 255, 255 ) );
    //s work.border(0, 1, borderColor);

    /* fast because its a sub-bitmap */
    CBitmap area(work, x, y, width, height);

    int current_y = height - font.getHeight() - 1;
    // int max_length = area.getWidth() / font.textLength( "E" );
    for ( vector< string >::reverse_iterator it = messages.rbegin(); it != messages.rend(); it++ ){
        if ( current_y < 0 - font.getHeight() ){
            break;
        }
        const string & s = *it;
        vector< string > all;
        all = wrapStrings(s, "", font, area.getWidth() - 3, all);
        current_y -= font.getHeight() * (all.size() - 1);
        int my = current_y;
        for ( vector< string >::iterator str = all.begin(); str != all.end(); str++ ){
			font.drawText(2, my, Colors::Blue, area, *str, 0);
            my += font.getHeight();

        }
        // current_y = wrapPrint( area, current_y, current_y, font, s, "" );
        /*
           int lines = font.textLength( s.c_str() ) / area.getWidth();
           current_y -= font.getHeight() * lines;
           int my = current_y;
           while ( s != "" ){
           string sub = s.substr( 0, max_length );
           s.erase( 0, max_length );
           font.printf( 0, my, Bitmap::makeColor( 255, 255, 255 ), area, sub, 0 );
           my += font.getHeight();
           }
           */
        current_y -= font.getHeight();
    }
}
	
CMessages::~CMessages(){
}



} // end Messages
} //end SGF