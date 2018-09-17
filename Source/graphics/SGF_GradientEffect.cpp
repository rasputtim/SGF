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

#include "graphics/SGF_GradientEffect.h"
#include "util/SGF_Util.h"
#include "graphics/SGF_Bitmap.h"
#include "graphics/SGF_Color.h"

using namespace std;
namespace SGF {
namespace Effects{

Gradient::Gradient():
colors(NULL),
size(1),
index(0){
    colors = new  Colors::ColorDefinition[size];
    colors[0].r = 255;
	colors[0].g = 255;
	colors[0].b = 255;
}
    
Gradient::Gradient(int singleColor):
colors(NULL),
size(1),
index(0){
    colors = new  Colors::ColorDefinition[size];
	colors[0].r = Colors::getRed(singleColor);
	colors[0].g = Colors::getBlue(singleColor);
	colors[0].b = Colors::getGreen(singleColor);
}


/* this class does virtually no error checking. great job */
Gradient::Gradient(int size,  Colors::ColorDefinition startColor,  Colors::ColorDefinition endColor):
colors(NULL),
size(size),
index(0){
    colors = new  Colors::ColorDefinition[size];
    Colors::blend_palette(colors, size / 2, startColor, endColor);
    Colors::blend_palette(colors + size / 2, size / 2, endColor, startColor);
}

Gradient::Gradient(Colors::ColorDefinition startColor):
colors(NULL),
size(1),
index(0){
    colors = new  Colors::ColorDefinition[size];
    colors[0] =startColor;
}

Gradient::Gradient(int size, int startColor, int endColor):
colors(NULL),
size(size),
index(0){
	 Colors::ColorDefinition startColorSDL, endColorSDL;
	startColorSDL.r= Colors::getRed(startColor);
	startColorSDL.g= Colors::getBlue(startColor);
	startColorSDL.b= Colors::getGreen(startColor);
	endColorSDL.r= Colors::getRed(endColor);
	endColorSDL.g= Colors::getBlue(endColor);
	endColorSDL.b= Colors::getGreen(endColor);

    colors = new  Colors::ColorDefinition[size];
    Colors::blend_palette(colors, size / 2, startColorSDL, endColorSDL);
    Colors::blend_palette(colors + size / 2, size / 2, endColorSDL, startColorSDL);
}

Gradient::Gradient(const Gradient & copy):
colors(NULL),
size(copy.size),
index(copy.index){
    colors = new  Colors::ColorDefinition[size];
    for (unsigned int i = 0; i < size; i++){
        colors[i].r = copy.colors[i].r;
		colors[i].g = copy.colors[i].g;
		colors[i].b = copy.colors[i].b;
    }
}

Gradient::Gradient(const Token * token):
colors(NULL),
size(10),
index(0){
    int lowRed = 0, lowGreen = 0, lowBlue = 0;
    int highRed = 255, highGreen = 255, highBlue = 255;
    token->match("_/low", lowRed, lowGreen, lowBlue);
    token->match("_/high", highRed, highGreen, highBlue);
    token->match("_/distance", size);
    token->match("_/size", size);

    size = Util::clamp(size, 2, 10000);

     Colors::ColorDefinition startColor;
	startColor.r= lowRed;
	startColor.g= lowGreen;
	startColor.b= lowBlue;
     Colors::ColorDefinition endColor;
	endColor.r= highRed;
	endColor.g= highGreen;
	endColor.b= highBlue;

    colors = new  Colors::ColorDefinition[size];
    Colors::blend_palette(colors, size / 2, startColor, endColor);
    Colors::blend_palette(colors + size / 2, size / 2, endColor, startColor);
}

void Gradient::update(){
    forward();
}
void Gradient::forward(){
    index = (index + 1) % size;
}

void Gradient::backward(){
    index = (index - 1 + size) % size;
}
 Colors::ColorDefinition Gradient::current()const {
    return colors[index];
}

Colors::ColorDefinition Gradient::current(int offset) const {
    return colors[(index + offset + size) % size];
}

int Gradient::current_intcolor()const{
	
	return Colors::makeColor(colors[index].r,colors[index].g,colors[index].b);
}
void Gradient::reset(){
    index = 0;
}

Gradient & Gradient::operator=(const Gradient & copy){
    delete[] colors;
    size = copy.size;
    index = copy.index;
    colors = new  Colors::ColorDefinition[size];
    for (unsigned int i = 0; i < size; i++){
        colors[i].r = copy.colors[i].r;
		colors[i].g = copy.colors[i].g;
		colors[i].b = copy.colors[i].b;
    }
    return *this;
}
Gradient::~Gradient(){
	
    if (colors) delete [] colors;
}
//===========Simple GRADIENT============================
    


/* this class does virtually no error checking. great job */
CGradientSimple::CGradientSimple(int size,  Colors::ColorDefinition startColor,  Colors::ColorDefinition endColor):
colors(NULL),
size(size),
index(0){
    colors = new  Colors::ColorDefinition[size];
    //Colors::blend_palette(colors, size / 2, startColor, endColor);
    //Colors::blend_palette(colors + size / 2, size / 2, endColor, startColor);
	 colors[0].r = colors[0].g = colors[0].b = 0;
	colors[1] = colors[0];

	// The rest is red->yellow gradient.

	for (int i=2; i<size; ++i )
	{
		int j = i > 25 ? i-25 : 0;
		colors[i].r = 255;
		colors[i].g = 255-j;
		colors[i].b = 0;
	}
}



CGradientSimple::CGradientSimple(int size, int startColor, int endColor):
colors(NULL),
size(size),
index(0){
	 Colors::ColorDefinition startColorSDL, endColorSDL;
	startColorSDL.r= Colors::getRed(startColor);
	startColorSDL.g= Colors::getBlue(startColor);
	startColorSDL.b= Colors::getGreen(startColor);
	endColorSDL.r= Colors::getRed(endColor);
	endColorSDL.g= Colors::getBlue(endColor);
	endColorSDL.b= Colors::getGreen(endColor);

    colors = new  Colors::ColorDefinition[size];
    colors[0].r = colors[0].g = colors[0].b = 0;
	colors[1] = colors[0];

	// The rest is red->yellow gradient.

	for (int i=2; i<size; ++i )
	{
		int j = i > 25 ? i-25 : 0;
		colors[i].r = 255;
		colors[i].g = 255-j;
		colors[i].b = 0;
	}
}

CGradientSimple::CGradientSimple(const CGradientSimple & copy):
colors(NULL),
size(copy.size),
index(copy.index){
    colors = new  Colors::ColorDefinition[size];
    for (unsigned int i = 0; i < size; i++){
        colors[i].r = copy.colors[i].r;
		colors[i].g = copy.colors[i].g;
		colors[i].b = copy.colors[i].b;
    }
}

CGradientSimple::CGradientSimple(const Token * token):
colors(NULL),
size(10),
index(0){
    int lowRed = 0, lowGreen = 0, lowBlue = 0;
    int highRed = 255, highGreen = 255, highBlue = 255;
    token->match("_/low", lowRed, lowGreen, lowBlue);
    token->match("_/high", highRed, highGreen, highBlue);
    token->match("_/distance", size);
    token->match("_/size", size);

    size = Util::clamp(size, 2, 10000);

     Colors::ColorDefinition startColor;
	startColor.r= lowRed;
	startColor.g= lowGreen;
	startColor.b= lowBlue;
     Colors::ColorDefinition endColor;
	endColor.r= highRed;
	endColor.g= highGreen;
	endColor.b= highBlue;

    colors = new  Colors::ColorDefinition[size];
    Colors::blend_palette(colors, size / 2, startColor, endColor);
    Colors::blend_palette(colors + size / 2, size / 2, endColor, startColor);
}

void CGradientSimple::update(int sizeh,int y){
	index = (size-2) * y / (sizeh-1) + 1;
    //return colors[index];//forward();
}
//void CGradientSimple::forward(){
 //   index = (index + 1) % size;
//}
void CGradientSimple::forward(){
	    if (index < size-1 )
	index = (index + 1);
	else index = 0;
}
void CGradientSimple::backward(){
   if (index > 0)
	index = (index - 1 );
   else index = size-1;
}
 Colors::ColorDefinition CGradientSimple::current()const {
    return colors[index];
}

Colors::ColorDefinition CGradientSimple::current(int offset) const {
    if (offset >0 && offset < size)
	return colors[offset];
	else return colors[0];
}

int CGradientSimple::current_intcolor()const{
	
	return Colors::makeColor(colors[index].r,colors[index].g,colors[index].b);
}
void CGradientSimple::reset(){
    index = 0;
}

CGradientSimple & CGradientSimple::operator=(const CGradientSimple & copy){
    delete[] colors;
    size = copy.size;
    index = copy.index;
    colors = new  Colors::ColorDefinition[size];
    for (unsigned int i = 0; i < size; i++){
        colors[i].r = copy.colors[i].r;
		colors[i].g = copy.colors[i].g;
		colors[i].b = copy.colors[i].b;
    }
    return *this;
}
CGradientSimple::~CGradientSimple(){
	
    if (colors) delete [] colors;
}
}
} //end SGF