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

#include "graphics/SGF_Poligon.h"
#include "util/SGF_Debug.h"
#include "../../ExternalLibs/SDL_gfx-2.0.24/SDL_gfxPrimitives.h"
#include "../../ExternalLibs/SDL_gfx-2.0.24/SDL_rotozoom.h"
#include "util/SGF_Util.h"



using namespace std;
namespace SGF {
//==================== POLIGON ==============
class CBitmap;




CPolygon CBitmap::polygon() const {
	Debug::debug(Debug::bitmap,__FUNCTION__) << "Creating  Poligon : "<< endl;
    return CPolygon(*this);

}

CPolygon::CPolygon(const CBitmap & b):
CBitmap(b){
 /*   int x1, y1, x2, y2;
    b.getSurfaceClipRect(x1, y1, x2, y2);
    setSurfaceClipRect(x1, y1, x2, y2);
	b.drawingMode(CBitmap::MODE_TRANS); */
}

CPolygon::~CPolygon() {}

void CPolygon::circleFill( int x, int y, int radius, Uint32 color_pixel, Uint8 a ) const{
	Uint8 r=Colors::getRed(color_pixel);
	Uint8 g=Colors::getGreen(color_pixel);
	Uint8 b=Colors::getBlue(color_pixel);
    circleFill(x,y,radius,r,g,b,a);


}
void CPolygon::circleFill( int x, int y, int radius, int R, int G, int B, int A) const {


		switch(this->getBitmapMode()) {

				case USE_TEXTURE:
					circleFillTexture(x,y,radius,R,G,B,A);

					break;

				case USE_SURFACE:
					circleFillSurface(x,y,radius,R,G,B,A);
				break;

				case BOTH_TEXTURE_SURFACE:
					circleFillTexture(x,y,radius,R,G,B,A);
					circleFillSurface(x,y,radius,R,G,B,A);
				break;
				default:
				break;
				}



	}

void CPolygon::circleFill( int x, int y, int radius,  Colors::ColorDefinition color, Uint8 a ) const{
	Uint8 r = color.r;
	Uint8 g = color.g;
	Uint8 b = color.b;
	circleFill(x,y,radius,r,g,b,a);

}


void CPolygon::equilateralTriangle(int x, int y, int angle, int size, int color) const {
	// utiliza a lei dos senos
	// http://pessoal.sercomtel.com.br/matematica/trigonom/trigo05.htm

    double radians = Util::radians(angle);
    int x1 = x + size / 2 * cos(radians + 2 * Util::pi / 3);
    int y1 = y + size / 2 * sin(radians + 2 * Util::pi / 3);
    int x2 = x + size / 2 * cos(radians - 2 * Util::pi / 3);
    int y2 = y + size / 2 * sin(radians - 2 * Util::pi / 3);
    int x3 = x + size / 2 * cos(radians);
    int y3 = y + size / 2 * sin(radians);
    triangle(x1, y1, x2, y2, x3, y3, color);
}

void CPolygon::triangle(int x1, int y1, int x2, int y2, int x3, int y3, Uint32 color_pixel , Uint8 A ) const{
	Uint8 R = Colors::getRed(color_pixel);
	Uint8 G = Colors::getGreen(color_pixel);
	Uint8 B = Colors::getBlue(color_pixel);
	triangle(x1, y1, x2, y2,x3, y3,R,G,B,A);

}
void CPolygon::triangle( int x1, int y1, int x2, int y2,int x3, int y3,  Colors::ColorDefinition color, Uint8 A  ) const{
	//Debug::debug(18) << " Colors::ColorDefinition Mode // color= " << (Uint32)color.r << endl;
	Uint8 R = color.r;
	Uint8 G = color.g;
	Uint8 B = color.b;
	triangle(x1,y1,x2,y2,x3,y3,R,G,B,A);
}
void CPolygon::triangle( int x1, int y1, int x2, int y2,int x3, int y3, Uint8 R, Uint8 G, Uint8 B, Uint8 A  ) const{

		switch(this->getBitmapMode()) {

				case USE_TEXTURE:
					triangleTexture(x1,y1,x2,y2,x3, y3,R,G,B,A);

					break;

				case USE_SURFACE:
					triangleSurface(x1,y1,x2,y2,x3, y3,R,G,B,A);
				break;

				case BOTH_TEXTURE_SURFACE:
					triangleTexture(x1,y1,x2,y2,x3, y3,R,G,B,A);
					triangleSurface(x1,y1,x2,y2,x3, y3,R,G,B,A);
				break;
				default:
				break;
				}


}




void CPolygon::ellipse(int x, int y, int rx, int ry, Uint32 color_pixel , Uint8 A ) const{
	Uint8 R = Colors::getRed(color_pixel);
	Uint8 G = Colors::getGreen(color_pixel);
	Uint8 B = Colors::getBlue(color_pixel);
	ellipse(x, y, rx, ry,R,G,B,A);

}
void CPolygon::ellipse( int x, int y, int rx, int ry,  Colors::ColorDefinition color, Uint8 A  ) const{
	//Debug::debug(18) << " Colors::ColorDefinition Mode // color= " << (Uint32)color.r << endl;
	Uint8 R = color.r;
	Uint8 G = color.g;
	Uint8 B = color.b;
	ellipse(x, y, rx, ry,R,G,B,A);
}
void CPolygon::ellipse( int x, int y, int rx, int ry, Uint8 R, Uint8 G, Uint8 B, Uint8 A  ) const{

		switch(this->getBitmapMode()) {

				case USE_TEXTURE:
					ellipseTexture(x, y, rx, ry,R,G,B,A);

					break;

				case USE_SURFACE:
					ellipseSurface(x, y, rx, ry,R,G,B,A);
				break;

				case BOTH_TEXTURE_SURFACE:
					ellipseTexture(x, y, rx, ry,R,G,B,A);
					ellipseSurface(x, y, rx, ry,R,G,B,A);
				break;
				default:
				break;
				}

}

void CPolygon::ellipseFill( int x, int y, int rx, int ry, Uint32 color_pixel , Uint8 A ) const{
	Uint8 R = Colors::getRed(color_pixel);
	Uint8 G = Colors::getGreen(color_pixel);
	Uint8 B = Colors::getBlue(color_pixel);
	ellipseFill(x, y, rx, ry,R,G,B,A);

}
void CPolygon::ellipseFill(int x, int y, int rx, int ry,  Colors::ColorDefinition color, Uint8 A  ) const{
	//Debug::debug(18) << " Colors::ColorDefinition Mode // color= " << (Uint32)color.r << endl;
	Uint8 R = color.r;
	Uint8 G = color.g;
	Uint8 B = color.b;
	ellipseFill(x,y,rx, ry,R,G,B,A);
}
void CPolygon::ellipseFill( int x, int y, int rx, int ry, Uint8 R, Uint8 G, Uint8 B, Uint8 A  ) const{

		switch(this->getBitmapMode()) {

				case USE_TEXTURE:
					ellipseFillTexture(x, y, rx, ry,R,G,B,A);

					break;

				case USE_SURFACE:
					ellipseFillSurface(x, y, rx, ry,R,G,B,A);
				break;

				case BOTH_TEXTURE_SURFACE:
					ellipseFillTexture(x, y, rx, ry,R,G,B,A);
					ellipseFillSurface(x, y, rx, ry,R,G,B,A);
				break;
				default:
				break;
				}

}




void CPolygon::arc(const int x, const int y, const double ang1, const double ang2, const int radius, Uint32 pixel, Uint8 A ) const{
	Uint8 R;
	Uint8 G;
	Uint8 B;
	if(true) {
	}else {
	SDL_GetRGB(pixel, _my_state->Screen[this->_my_renderWindow]->getBitmap()->format, &R, &G, &B);
	::arcRGBA(getBitmap(),  x,  y, radius, ang1, ang2, R,G,B,A);
	}
}



void CPolygon::pie(const int x, const int y, const double ang1, const double ang2, const int radius, Uint32 color_pixel, Uint8 A ) const{
	Uint8 R = Colors::getRed(color_pixel);
	Uint8 G = Colors::getGreen(color_pixel);
	Uint8 B = Colors::getBlue(color_pixel);
	pie(x, y, ang1, ang2,radius,R,G,B,A);
}
void CPolygon::pie(const int x, const int y, const double ang1, const double ang2, const int radius, const  Colors::ColorDefinition color, Uint8 A ) const{
	Uint8 R = color.r;
	Uint8 G = color.g;
	Uint8 B = color.b;
	pie(x, y, ang1, ang2,radius,R,G,B,A);
}

void CPolygon::pie(const int x, const int y, const double ang1, const double ang2, const int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 A   ) const{
		switch(this->getBitmapMode()) {

				case USE_TEXTURE:
					pieTexture(x, y, ang1, ang2,radius,R,G,B,A);

					break;

				case USE_SURFACE:
					pieSurface(x, y, ang1, ang2,radius,R,G,B,A);
				break;

				case BOTH_TEXTURE_SURFACE:
					pieTexture(x, y, ang1, ang2,radius,R,G,B,A);
					pieSurface(x, y, ang1, ang2,radius,R,G,B,A);
				break;
				default:
				break;
				}

}



void CPolygon::pieFill(const int x, const int y, const double ang1, const double ang2, const int radius, Uint32 color_pixel, Uint8 A ) const{
	Uint8 R = Colors::getRed(color_pixel);
	Uint8 G = Colors::getGreen(color_pixel);
	Uint8 B = Colors::getBlue(color_pixel);
	pieFill(x, y, ang1, ang2,radius,R,G,B,A);
}
void CPolygon::pieFill(const int x, const int y, const double ang1, const double ang2, const int radius, const  Colors::ColorDefinition color, Uint8 A ) const{
	Uint8 R = color.r;
	Uint8 G = color.g;
	Uint8 B = color.b;
	pieFill(x, y, ang1, ang2,radius,R,G,B,A);
}

void CPolygon::pieFill(const int x, const int y, const double ang1, const double ang2, const int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 A   ) const{
		switch(this->getBitmapMode()) {

				case USE_TEXTURE:
					pieFillTexture(x, y, ang1, ang2,radius,R,G,B,A);

					break;

				case USE_SURFACE:
					pieFillSurface(x, y, ang1, ang2,radius,R,G,B,A);
				break;

				case BOTH_TEXTURE_SURFACE:
					pieFillTexture(x, y, ang1, ang2,radius,R,G,B,A);
					pieFillSurface(x, y, ang1, ang2,radius,R,G,B,A);
				break;
				default:
				break;
				}

}


void CPolygon::hLine( const int x1, const int y, const int x2, const int color ) const{
	::hlineColor( getBitmap(), x1, x2, y, color );
}
void CPolygon::hLine( const int x1, const int y, const int x2, const Colors::ColorDefinition color ) const{

	::vlineRGBA( getBitmap(), x1, x2, y, color.r,color.g,color.b,color.a );
}
void CPolygon::horizontalLine( const int x1, const int y, const int x2, const int color ) const{
	this->hLine( x1, y, x2, color );
}

void CPolygon::vLine( const int y1, const int x, const int y2, const int color ) const{
	::vlineColor(getBitmap(), x, y1, y2, color );
	//::vlineColor( getBitmap(), x, y1, y2, color );
}
void CPolygon::vLine( const int y1, const int x, const int y2, const Colors::ColorDefinition color ) const{
	::vlineRGBA(getBitmap(), x, y1, y2,color.r,color.g,color.b,color.a);

	//::vlineColor( getBitmap(), x, y1, y2, color );
}
void CPolygon::polygon( const Sint16 * xverts, const Sint16 * yverts,const int nverts, const int color ) const{

	::polygonColor(getBitmap(), xverts, yverts, nverts, color);
	//::polygon( getBitmap(), nverts, verts, color );
}



//Todo Converter angulos do sentido anti-horário para o sentido horário em arc
	//atualmente arc usa angulos relativos. converter para absolutos


void CPolygon::arc(const int x, const int y, const double ang1, const double ang2, const int radius, const  Colors::ColorDefinition color, Uint8 A ) const{
	Uint8 R = color.r;
	Uint8 G = color.g;
	Uint8 B = color.b;
	arc(x,y,ang1,ang2,radius,R,G,B,A,3); //3 é o método
}

void CPolygon::arc(const int x, const int y, const double ang1, const double ang2, const int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 A, int method ) const{

		switch(this->getBitmapMode()) {

				case USE_TEXTURE:
					arcTexture(x,y,ang1,ang2,radius,R,G,B,A,method);

					break;

				case USE_SURFACE:
					arcSurface(x,y,ang1,ang2,radius,R,G,B,A);
				break;

				case BOTH_TEXTURE_SURFACE:
					arcTexture(x,y,ang1,ang2,radius,R,G,B,A,method);
					arcSurface(x,y,ang1,ang2,radius,R,G,B,A);
				break;
				default:
				break;
				}


}
void CPolygon::arcFill( const int x, const int y, const double ang1, const double ang2, const int radius, Uint32 color_pixel, Uint8 a ) const{
	Uint8 R=Colors::getRed(color_pixel);
	Uint8 G=Colors::getGreen(color_pixel);
	Uint8 B=Colors::getBlue(color_pixel);

	arcFill(x,y,ang1,ang2,radius,R,G,B,a);


}
void CPolygon::arcFill(const int x, const int y, const double ang1, const double ang2, const int radius, const  Colors::ColorDefinition color, Uint8 A ) const{
	Uint8 R = color.r;
	Uint8 G = color.g;
	Uint8 B = color.b;
	arc(x,y,ang1,ang2,radius,R,G,B,A,3); //3 é o método
}
void CPolygon::arcFill(const int x, const int y, const double ang1, const double ang2, const int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 A, int method ) const{


		switch(this->getBitmapMode()) {

				case USE_TEXTURE:
					arcFillTexture(x,y,ang1,ang2,radius,R,G,B,A);

					break;

				case USE_SURFACE:
					arcFillSurface(x,y,ang1,ang2,radius,R,G,B,A);
				break;

				case BOTH_TEXTURE_SURFACE:
					arcFillTexture(x,y,ang1,ang2,radius,R,G,B,A);
					arcFillSurface(x,y,ang1,ang2,radius,R,G,B,A);
				break;
				default:
				break;
				}



}
void CPolygon::circle( int x, int y, int radius, Uint32 color_pixel, Uint8 a ) const{
	Uint8 r=Colors::getRed(color_pixel);
	Uint8 g=Colors::getGreen(color_pixel);
	Uint8 b=Colors::getBlue(color_pixel);

	
		circle(x,y,radius,r,g,b,a);
	

}
void CPolygon::circle(int x,int y,int radius, int R, int G, int B, int A, int method) const{ //Draw a Circle

		switch(this->getBitmapMode()) {

				case USE_TEXTURE:
					circleTexture(x,y,radius,R,G,B,A,method);

					break;

				case USE_SURFACE:
					circleSurface(x,y,radius,R,G,B,A);
				break;

				case BOTH_TEXTURE_SURFACE:
					circleTexture(x,y,radius,R,G,B,A,method);
					circleSurface(x,y,radius,R,G,B,A);
				break;
				default:
				break;
				}


}
void CPolygon::lines( Gui::CPoints &points ) const {
	int numero=points.num_points;
	SDL_Point *point;
    point = (SDL_Point *) calloc( numero,sizeof(SDL_Point));
	for (int i=0; i< numero;i++) {
	point[i].x = points.Point[i]->getX();
    point[i].y = points.Point[i]->getY();
	}

//		if(SDL_SelectRenderer(GetWindow())!=0)
//			Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= " <<  SDL_GetError()  << endl;

		SDL_Renderer *myRenderer= getMyRender();
		SDL_BlendMode blendMode = GetTextureDrawBlendMode();
		if(myRenderer) {
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Render: " <<  getMyRender()  << endl;

			if(SDL_SetRenderDrawBlendMode(myRenderer,blendMode)!=0){
				Debug::debug(Debug::bitmap,__FUNCTION__) << "Error setting Texture Blend Mode= " <<  SDL_GetError()  << endl;
			}
			if(SDL_RenderDrawLines(myRenderer,point,numero)!=0)
				Debug::debug(Debug::bitmap,__FUNCTION__) << "Error Rendering lines= " <<  SDL_GetError()  << endl;
			//retorna a cor original

		}



	
	free(point);
}
void CPolygon::line( const int x1, const int y1, const int x2, const int y2, Uint32 color_pixel, Uint8 a ) const{
	Uint8 redX;
	Uint8 greenX;
	Uint8 blueX;


		SDL_DisplayMode mode;
		SDL_GetDesktopDisplayMode(0,&mode);
		SDL_GetRGB(color_pixel, SDL_AllocFormat(mode.format), &redX, &greenX, &blueX);

		line(x1,y1,x2,y2,redX,greenX,blueX,a);
	
}
void CPolygon::line( const int x1, const int y1, const int x2, const int y2, Uint8 R, Uint8 G, Uint8 B, Uint8 A   ) const{

		switch(this->getBitmapMode()) {

				case USE_TEXTURE:
					lineTexture(x1,y1,x2,y2,R,G,B,A);

					break;

				case USE_SURFACE:
					lineSurface(x1,y1,x2,y2,R,G,B,A);
				break;

				case BOTH_TEXTURE_SURFACE:
					lineTexture(x1,y1,x2,y2,R,G,B,A);
					lineSurface(x1,y1,x2,y2,R,G,B,A);
				break;
				default:
				break;
				}

}
void CPolygon::line( const int x1, const int y1, const int x2, const int y2, const  Colors::ColorDefinition color, Uint8 a) const{

	Uint8 r = color.r;
	Uint8 g = color.g;
	Uint8 b = color.b;
	
		line(x1,y1,x2,y2,r,g,b,a);
	

}
void CPolygon::line( const int x1, const int y1, const int x2, const int y2) const{
//	SDL_SelectRenderer(GetWindow());
	SDL_RenderDrawLine(getMyRender(),x1, y1, x2, y2);
	

}
void CPolygon::hline( const int x1, const int y1, const int x2,  Uint32 color_pixel, Uint8 a ) const{
	Uint8 redX;
	Uint8 greenX;
	Uint8 blueX;

		SDL_DisplayMode mode;
		SDL_GetDesktopDisplayMode(0,&mode);
		SDL_GetRGB(color_pixel, SDL_AllocFormat(mode.format), &redX, &greenX, &blueX);

		line(x1,y1,x2,y1,redX,greenX,blueX,a);
	
}
void CPolygon::hline( const int x1, const int y1, const int x2, Uint8 R, Uint8 G, Uint8 B, Uint8 A   ) const{

		switch(this->getBitmapMode()) {

				case USE_TEXTURE:
					lineTexture(x1,y1,x2,y1,R,G,B,A);

					break;

				case USE_SURFACE:
					lineSurface(x1,y1,x2,y1,R,G,B,A);
				break;

				case BOTH_TEXTURE_SURFACE:
					lineTexture(x1,y1,x2,y1,R,G,B,A);
					lineSurface(x1,y1,x2,y1,R,G,B,A);
				break;
				default:
				break;
				}


}
void CPolygon::hline( const int x1, const int y1, const int x2, const  Colors::ColorDefinition color, Uint8 a) const{

	Uint8 r = color.r;
	Uint8 g = color.g;
	Uint8 b = color.b;

		line(x1,y1,x2,y1,r,g,b,a);


}
void CPolygon::hline( const int x1, const int y1, const int x2) const{
//	SDL_SelectRenderer(GetWindow());
	SDL_RenderDrawLine(getMyRender(),x1, y1, x2, y1);
	
}
void CPolygon::vline( const int x1, const int y1, const int y2, Uint32 color_pixel, Uint8 a ) const{
	Uint8 redX;
	Uint8 greenX;
	Uint8 blueX;

	SDL_DisplayMode mode;
	SDL_GetDesktopDisplayMode(0,&mode);
	SDL_GetRGB(color_pixel, SDL_AllocFormat(mode.format), &redX, &greenX, &blueX);
	line(x1,y1,x1,y2,redX,greenX,blueX,a);
	
}
void CPolygon::vline( const int x1, const int y1, const int y2, Uint8 R, Uint8 G, Uint8 B, Uint8 A   ) const{
		switch(this->getBitmapMode()) {

				case USE_TEXTURE:
					lineTexture(x1,y1,x1,y2,R,G,B,A);

					break;

				case USE_SURFACE:
					lineSurface(x1,y1,x1,y2,R,G,B,A);
				break;

				case BOTH_TEXTURE_SURFACE:
					lineTexture(x1,y1,x1,y2,R,G,B,A);
					lineSurface(x1,y1,x1,y2,R,G,B,A);
				break;
				default:
				break;
				}


}
void CPolygon::vline( const int x1, const int y1, const int y2, const  Colors::ColorDefinition color, Uint8 a) const{

	Uint8 r = color.r;
	Uint8 g = color.g;
	Uint8 b = color.b;

		line(x1,y1,x1,y2,r,g,b,a);
	

}
void CPolygon::vline( const int x1, const int y1, const int y2) const{
//	SDL_SelectRenderer(GetWindow());
	SDL_RenderDrawLine(getMyRender(),x1, y1, x1, y2);
	

}
void CPolygon::point( int x, int y, Uint8 R, Uint8 G, Uint8 B, Uint8 A ) const {
//		if(SDL_SelectRenderer(GetWindow())!=0)
//			Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= " <<  SDL_GetError()  << endl;
		Uint8 r,g,b,a;
		SDL_GetRenderDrawColor(getMyRender(),&r,&g,&b, &a);
		SDL_SetRenderDrawColor(getMyRender(),R, G, B, A);
		if(SDL_RenderDrawPoint(getMyRender(),x,y)!=0)
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= " <<  SDL_GetError()  << endl;
	    //retorna a cor original
		SDL_SetRenderDrawColor(getMyRender(),r,g,b,a);

}
void CPolygon::point( int x, int y, Colors::ColorDefinition color, Uint8 A ) const {
	Uint8 R = color.r;
	Uint8 G = color.g;
	Uint8 B = color.b;
	point(x,y,R,G,B,A);
}
void CPolygon::point( int x, int y ) const {
//		if(SDL_SelectRenderer(GetWindow())!=0)
//			Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= " <<  SDL_GetError()  << endl;
		if(SDL_RenderDrawPoint(getMyRender(),x,y)!=0)
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= " <<  SDL_GetError()  << endl;
}
void CPolygon::points( Gui::CPoints &points ) const {
	int numero=points.num_points;
	SDL_Point *point;
    point = (SDL_Point *) calloc( numero,sizeof(SDL_Point));
	for (int i=0; i< numero;i++) {
	point[i].x = points.Point[i]->getX();
    point[i].y = points.Point[i]->getY();
	}
//		if(SDL_SelectRenderer(GetWindow())!=0)
//			Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= " <<  SDL_GetError()  << endl;
		if(SDL_RenderDrawPoints(getMyRender(),point,numero)!=0)
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= " <<  SDL_GetError()  << endl;

	free (point);

}
//! desenha os pontos do vetor points na tela
//! só funciona no modo de compatilibidade 1.3 // Só para texturas por enquanto
void CPolygon::points( vector<Gui::CAbsolutePoint*> &points ) const {
	Debug::debug(Debug::bitmap,__FUNCTION__) << "with vector of points"  << endl;
	int numero=points.size();
	SDL_Point *point;
    point = (SDL_Point *) calloc( numero,sizeof(SDL_Point));
	for (int i=0; i< numero;i++) {
	point[i].x = points[i]->getX();
    point[i].y = points[i]->getY();
	Debug::debug(Debug::bitmap,__FUNCTION__) << " point ( "<<i<<" ) = "<< point[i].x << " , " << point[i].y << endl;

	}
		Debug::debug(Debug::bitmap,__FUNCTION__) << "Drawing the points"  << endl;
//		if(SDL_SelectRenderer(GetWindow())!=0)
//			Debug::debug(Debug::bitmap,__FUNCTION__) << "CPolygon::points // Error= " <<  SDL_GetError()  << endl;
		if(SDL_RenderDrawPoints(getMyRender(),point,numero)!=0)
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= " <<  SDL_GetError()  << endl;

	free (point);

}
void CPolygon::rectangle( int x1, int y1, int x2, int y2, Uint32 pixel,Uint8 A ) const{
	Uint8 R = Colors::getRed(pixel);
	Uint8 G = Colors::getGreen(pixel);
	Uint8 B = Colors::getBlue(pixel);
	rectangle(x1, y1, x2, y2,R,G,B,A);

}
void CPolygon::rectangle( int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B, Uint8 A  ) const{
		switch(this->getBitmapMode()) {

				case USE_TEXTURE:
					rectangleTexture(x1,y1,x2,y2,R,G,B,A);

					break;

				case USE_SURFACE:
					rectangleSurface(x1,y1,x2,y2,R,G,B,A);
				break;

				case BOTH_TEXTURE_SURFACE:
					rectangleTexture(x1,y1,x2,y2,R,G,B,A);
					rectangleSurface(x1,y1,x2,y2,R,G,B,A);
				break;
				default:
				break;
				}


}
void CPolygon::rectangle( int x1, int y1, int x2, int y2,  Colors::ColorDefinition color, Uint8 A  ) const{
	//Debug::debug(18) << " Colors::ColorDefinition Mode // color= " << (Uint32)color.r << endl;
	Uint8 R = color.r;
	Uint8 G = color.g;
	Uint8 B = color.b;
	rectangle(x1,y1,x2,y2,R,G,B,A);
}

//Desenha um retângulo na cor default
void CPolygon::rectangle( int x1, int y1, int x2, int y2) const{

		SDL_Rect temp;
		//Todo: protect from x2 or y2 < x1 or y1
		temp.x = x1;
		temp.y = y1;
		temp.w = x2-x1;
		temp.h = y2-y1;
//		if(SDL_SelectRenderer(GetWindow())!=0)
//			Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= " <<  SDL_GetError()  << endl;

		SDL_Renderer *myRenderer= getMyRender();
		SDL_BlendMode blendMode = GetTextureDrawBlendMode();
		if(myRenderer) {
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Render: " <<  getMyRender()  << endl;
			if(SDL_SetRenderDrawBlendMode(myRenderer,blendMode)!=0){
				Debug::debug(Debug::bitmap,__FUNCTION__) << "Error setting Texture Blend Mode= " <<  SDL_GetError()  << endl;
			}
			if(SDL_RenderDrawRect(myRenderer,&temp)!=0)
				Debug::debug(Debug::bitmap,__FUNCTION__) << "Error Rendering= " <<  SDL_GetError()  << endl;
			//retorna a cor original
		}


}

//! Desenha um retângulo na surface
void CPolygon::rectangleSurface( int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B, Uint8 A  ) const{

	::rectangleRGBA(getBitmap(), x1, y1, x2, y2,R,G,B,A);
	//::SPG_RectBlend(getBitmap(), x1, y1, x2, y2, color, alpha);
}
//! Desenha um retângulo na Textura
void CPolygon::rectangleTexture( int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B, Uint8 A  ) const{
		SDL_Rect temp;
		//Todo: protect from x2 or y2 < x1 or y1
		temp.x = x1;
		temp.y = y1;
		temp.w = x2-x1;
		temp.h = y2-y1;
//		if(SDL_SelectRenderer(GetWindow())!=0)
	//		Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= " <<  SDL_GetError()  << endl;
		Uint8 r,g,b,a;
		SDL_Renderer *myRenderer= getMyRender();
		SDL_BlendMode blendMode = GetTextureDrawBlendMode();
		if(myRenderer) {
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Render: " <<  getMyRender()  << endl;
			SDL_GetRenderDrawColor(myRenderer,&r,&g,&b, &a);
			if(SDL_SetRenderDrawBlendMode(myRenderer,blendMode)!=0){
				Debug::debug(Debug::bitmap,__FUNCTION__) << "Error setting Texture Blend Mode= " <<  SDL_GetError()  << endl;
			}
			SDL_SetRenderDrawColor(myRenderer,R, G, B, A);
			if(SDL_RenderDrawRect(myRenderer,&temp)!=0)
				Debug::debug(Debug::bitmap,__FUNCTION__) << "Error Render line= " <<  SDL_GetError()  << endl;
			//retorna a cor original
			SDL_SetRenderDrawColor(myRenderer,r,g,b,a);
		}

}

void CPolygon::rectangleFill( int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B, Uint8 A  ) const{
		switch(this->getBitmapMode()) {

				case USE_TEXTURE:
					rectangleFillTexture(x1,y1,x2,y2,R,G,B,A);

					break;

				case USE_SURFACE:
					rectangleFillSurface(x1,y1,x2,y2,R,G,B,A);
				break;

				case BOTH_TEXTURE_SURFACE:
					rectangleFillTexture(x1,y1,x2,y2,R,G,B,A);
					rectangleFillSurface(x1,y1,x2,y2,R,G,B,A);
				break;
				default:
				break;
				}

}
void CPolygon::rectangleFill( int x1, int y1, int x2, int y2,  Colors::ColorDefinition color, Uint8 A  ) const{
	Uint8 R = color.r;
	Uint8 G = color.g;
	Uint8 B = color.b;
	rectangleFill(x1,y1,x2,y2,R,G,B,A);

}
void CPolygon::rectangleFill( int x1, int y1, int x2, int y2, Uint32 color_pixel,Uint8 A ) const{
	Uint8 R = Colors::getRed(color_pixel);
	Uint8 G = Colors::getGreen(color_pixel);
	Uint8 B = Colors::getBlue(color_pixel);
	rectangleFill(x1, y1, x2, y2,R,G,B,A);

}
//! desenha um retângulo preenchido com a cor padrão
void CPolygon::rectangleFill( int x1, int y1, int x2, int y2) const{
		SDL_Rect temp;
		//Todo: protect from x2 or y2 < x1 or y1
		temp.x = x1;
		temp.y = y1;
		temp.w = x2-x1;
		temp.h = y2-y1;

//		if(SDL_SelectRenderer(GetWindow())!=0)
//			Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= " <<  SDL_GetError()  << endl;
		//Uint8 r,g,b,a;
		SDL_Renderer *myRenderer= getMyRender();
		SDL_BlendMode blendMode = GetTextureDrawBlendMode();
		if(myRenderer) {
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Render: " <<  getMyRender()  << endl;
			//SDL_GetRenderDrawColor(myRenderer,&r,&g,&b, &a);
			if(SDL_SetRenderDrawBlendMode(myRenderer,blendMode)!=0){
				Debug::debug(Debug::bitmap,__FUNCTION__) << "Error setting Texture Blend Mode= " <<  SDL_GetError()  << endl;
			}
			//SDL_SetRenderDrawColor(myRenderer,R, G, B, A);
			if(SDL_RenderFillRect(myRenderer,&temp)!=0)
				Debug::debug(Debug::bitmap,__FUNCTION__) << "Error Render line= " <<  SDL_GetError()  << endl;
			//retorna a cor original
			//SDL_SetRenderDrawColor(myRenderer,r,g,b,a);
		}

}
void CPolygon::roundRect(int radius, int x1, int y1, int x2, int y2,  Colors::ColorDefinition color, Uint8 A) const
{
    Uint8 R = color.r;
	Uint8 G = color.g;
	Uint8 B = color.b;
	roundRect(radius,x1,y1,x2,y2,R,G,B,A);
}
void CPolygon::roundRect(int radius, int x1, int y1, int x2, int y2, Uint32 color_pixel, Uint8 A) const
{
   Uint8 R = Colors::getRed(color_pixel);
	Uint8 G = Colors::getGreen(color_pixel);
	Uint8 B = Colors::getBlue(color_pixel);
	roundRect(radius,x1,y1,x2,y2,R,G,B,A);
}
void CPolygon::roundRect( int radius, int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B, Uint8 A  ) const{


		switch(this->getBitmapMode()) {

				case USE_TEXTURE:
					roundRectTexture(radius,x1,y1,x2,y2,R,G,B,A);

					break;

				case USE_SURFACE:
					roundRectSurface(radius,x1,y1,x2,y2,R,G,B,A);
				break;

				case BOTH_TEXTURE_SURFACE:
					roundRectTexture(radius,x1,y1,x2,y2,R,G,B,A);
					roundRectSurface(radius,x1,y1,x2,y2,R,G,B,A);
				break;
				default:
				break;
				}


}
void CPolygon::roundRectFill(int radius, int x1, int y1, int x2, int y2,  Colors::ColorDefinition color, Uint8 A) const {
    Uint8 R = color.r;
	Uint8 G = color.g;
	Uint8 B = color.b;
	Debug::debug(Debug::bitmap,__FUNCTION__) << " Colors::ColorDefinition " << (int) R << " , " <<(int) G<< " , "  <<(int) B << " , "  << (int)A  << endl;

	roundRectFill(radius,x1,y1,x2,y2,R,G,B,A);
//roundRectFill(work,radius,x1,y1,x2,y2,cor);
}
void CPolygon::roundRectFill(int radius, int x1, int y1, int x2, int y2, Uint32 color_pixel, Uint8 A) const {

    Uint8 R = Colors::getRed(color_pixel);
	Uint8 G = Colors::getGreen(color_pixel);
	Uint8 B = Colors::getBlue(color_pixel);
	Debug::debug(Debug::bitmap,__FUNCTION__) << "Color_pixel " << (int) R << " , " <<(int) G<< " , "  <<(int) B << " , "  << (int)A  << endl;

	roundRectFill(radius,x1,y1,x2,y2,R,G,B,A);
//roundRectFill(work,radius,x1,y1,x2,y2,cor);
}
void CPolygon::roundRectFill(int radius, int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B, Uint8 A  ) const{
	Debug::debug(Debug::bitmap,__FUNCTION__) << "Switch Surface/Texture " << (int) R << " , " <<(int) G<< " , "  <<(int) B << " , "  << (int)A  << endl;

		switch(this->getBitmapMode()) {

				case USE_TEXTURE:
					roundRectFillTexture(radius,x1,y1,x2,y2,R,G,B,A);

					break;

				case USE_SURFACE:
					roundRectFillSurface(radius,x1,y1,x2,y2,R,G,B,A);
				break;

				case BOTH_TEXTURE_SURFACE:
					roundRectFillTexture(radius,x1,y1,x2,y2,R,G,B,A);
					roundRectFillSurface(radius,x1,y1,x2,y2,R,G,B,A);
				break;
				default:
				break;
				}


}
//! Desenha um retângulo preenchido na surface
void CPolygon::rectangleFillSurface( int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B, Uint8 A  ) const{

	::boxRGBA( getBitmap(), x1, y1, x2, y2,R,G,B,A  );
	//::SPG_RectFilledBlend(getBitmap(), x1, y1, x2, y2, color, alpha);

}
//! Desenha um retângulo preenchido na Textura
void CPolygon::rectangleFillTexture( int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B, Uint8 A  ) const{
	Debug::debug(Debug::bitmap,__FUNCTION__) << x1 << " , " << y1 << " , " << x2 <<" , "<< y2 << endl;

		SDL_Rect temp;
		//Todo: protect from x2 or y2 < x1 or y1
		temp.x = x1;
		temp.y = y1;
		if (x2 > x1)
		temp.w = x2-x1;
		else
			temp.w = x1 - x2;
		if (y2 > y1)
			temp.h = y2-y1;
		else
			temp.y = y1 - y2;
//		if(SDL_SelectRenderer(GetWindow())!=0)
//			Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= " <<  SDL_GetError()  << endl;
		Uint8 r,g,b,a;
		SDL_Renderer *myRenderer= getMyRender();
		SDL_BlendMode blendMode = GetTextureDrawBlendMode();
		if(myRenderer) {
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Render: " <<  getMyRender()  << endl;
			SDL_GetRenderDrawColor(myRenderer,&r,&g,&b, &a);
			if(SDL_SetRenderDrawBlendMode(getMyRender(),blendMode)!=0){
				Debug::debug(Debug::bitmap,__FUNCTION__) << "Error setting Texture Blend Mode= " <<  SDL_GetError()  << endl;
			}
			SDL_SetRenderDrawColor(myRenderer,R, G, B, A);
			if(SDL_RenderFillRect(myRenderer,&temp)!=0)
				Debug::debug(Debug::bitmap,__FUNCTION__) << "Error Render fill Rect= " <<  SDL_GetError()  << endl;
			//retorna a cor original
			SDL_SetRenderDrawColor(myRenderer,r,g,b,a);
		}

}
void CPolygon::roundRectSurface( int radius, int x1, int y1, int x2, int y2,  Uint8 R, Uint8 G, Uint8 B, Uint8 A  )const {
	if (this->getBitmap()){
	// Uint32 pixel = Colors::makeColor(color.r,color.g,color.b);
	const int width = x2 - x1;
	const int height = y2 - y1;
	radius = MID(0, radius, MIN((x1+width - x1)/2, (y1+height - y1)/2));
	line(x1+radius, y1, x1+width-radius, y1, R,G,B,A);
	line(x1+radius, y1+height, x1+width-radius,y1+height, R,G,B,A);
	line(x1, y1+radius,x1, y1+height-radius,  R,G,B,A);
	line(x1+width, y1+radius,x1+width, y1+height-radius,  R,G,B,A);
		//Todo Converter angulos do sentido anti-horário para o sentido horário em arc
	//atualmente arc usa angulos relativos. converter para absolutos
	arc(x1+radius, y1+radius,180,270,radius,R,G,B,A);
	arc((x1+width)-radius, y1+radius,270,360,radius,R,G,B,A);
	arc(x1+radius, (y1+height)-radius,90,180,radius,R,G,B,A);
	arc((x1+width)-radius, (y1+height)-radius,0,90,radius,R,G,B,A);

	}else {
	//error  bitmap not set
	}

}
void CPolygon::roundRectTexture( int radius, int x1, int y1, int x2, int y2,  Uint8 R, Uint8 G, Uint8 B, Uint8 A  )const {
	// Uint32 pixel = Colors::makeColor(color.r,color.g,color.b);
	const int width = x2 - x1;
	const int height = y2 - y1;
	radius = MID(0, radius, MIN((x1+width - x1)/2, (y1+height - y1)/2));

	line(x1+radius, y1, x1+width-radius, y1, R,G,B,A);
	line(x1+radius, y1+height, x1+width-radius,y1+height, R,G,B,A);
	line(x1, y1+radius,x1, y1+height-radius, R,G,B,A);
	line(x1+width, y1+radius,x1+width, y1+height-radius,  R,G,B,A);
	arc(x1+radius, y1+radius,180,90,radius,R,G,B,A);
	arc((x1+width)-radius, y1+radius,270,90,radius,R,G,B,A);
	arc(x1+radius, (y1+height)-radius,90,90,radius,R,G,B,A);
	arc((x1+width)-radius, (y1+height)-radius,0,90,radius,R,G,B,A);
	

}
void CPolygon::roundRectFillSurface( int radius, int x1, int y1, int x2, int y2,  Uint8 R, Uint8 G, Uint8 B, Uint8 A  ) const{
		Debug::debug(Debug::bitmap,__FUNCTION__) << "Surface " << (int) R << " , " <<(int) G<< " , "  <<(int) B << " , "  << (int)A  << endl;
	if (this->getBitmap()){
    const int width = x2 - x1;
	const int height = y2 - y1;
	radius = MID(0, radius, MIN((x1+width - x1)/2, (y1+height - y1)/2));
	//Todo Converter Pie para SDL 1.3
	pieFill(x1+radius, y1+radius,180,275,radius, R,G,B,A);
	pieFill((x1+width)-radius, y1+radius,270,362,radius, R,G,B,A);
	pieFill(x1+radius, (y1+height)-radius,90,183,radius, R,G,B,A);
	pieFill((x1+width)-radius, (y1+height)-radius,0,93,radius, R,G,B,A);
	rectangleFill( x1+radius, y1, x2-radius, y1+radius, R,G,B,A);
	rectangleFill( x1, y1+radius, x2, y2-radius, R,G,B,A);
	rectangleFill( x1+radius, y2-radius, x2-radius, y2,  R,G,B,A);

	}else {
	//error  bitmap not set
	}
}
void CPolygon::roundRectFillTexture( int radius, int x1, int y1, int x2, int y2,  Uint8 R, Uint8 G, Uint8 B, Uint8 A  ) const{
		Debug::debug(Debug::bitmap,__FUNCTION__) << "Texture " << (int) R << " , " <<(int) G<< " , "  <<(int) B << " , "  << (int)A  << endl;

	// Uint32 pixel = Colors::makeColor(color.r,color.g,color.b);
	const int width = x2 - x1;
	const int height = y2 - y1;
	radius = MID(0, radius, MIN((x1+width - x1)/2, (y1+height - y1)/2));

	pieFill(x1+radius, y1+radius,180,275,radius, R,G,B,A);
	pieFill((x1+width)-radius, y1+radius,270,362,radius, R,G,B,A);
	pieFill(x1+radius, (y1+height)-radius,90,183,radius, R,G,B,A);
	pieFill((x1+width)-radius, (y1+height)-radius,0,93,radius, R,G,B,A);
	rectangleFill( x1+radius, y1, x2-radius, y1+radius,  R,G,B,A);
	rectangleFill( x1, y1+radius, x2, y2-radius,  R,G,B,A );
	rectangleFill( x1+radius, y2-radius, x2-radius, y2,  R,G,B,A );
	
}
void CPolygon::lineSurface( const int x1, const int y1, const int x2, const int y2, Uint8 R, Uint8 G, Uint8 B, Uint8 A ) const{
	if (this->getBitmap()){
	::lineRGBA(getBitmap(), x1, y1, x2, y2, R,G,B,A); //color no formato 32 bits//color no formato 32 bits
	}else {
	//error  bitmap not set
	}
}
void CPolygon::lineTexture( const int x1, const int y1, const int x2, const int y2, Uint8 R, Uint8 G, Uint8 B, Uint8 A ) const{
		//SDL_Rect temp;
		//Todo: protect from x2 or y2 < x1 or y1
		//temp.x = x1;
		//temp.y = y1;
		//temp.w = x2-x1;
		//temp.h = y2-y1;
//		if(SDL_SelectRenderer(GetWindow())!=0)
//			Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= " <<  SDL_GetError()  << endl;
		Uint8 r,g,b,a;
		SDL_Renderer *myRenderer= getMyRender();
		SDL_BlendMode blendMode = GetTextureDrawBlendMode();
		if(myRenderer) {
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Render: " <<  getMyRender()  << endl;
			SDL_GetRenderDrawColor(myRenderer,&r,&g,&b, &a);
			if(SDL_SetRenderDrawBlendMode(getMyRender(),blendMode)!=0){
				Debug::debug(Debug::bitmap,__FUNCTION__) << "Error setting Texture Blend Mode= " <<  SDL_GetError()  << endl;
			}
			SDL_SetRenderDrawColor(myRenderer,R, G, B, A);
			if(SDL_RenderDrawLine(getMyRender(),x1, y1, x2, y2)!=0)
				Debug::debug(Debug::bitmap,__FUNCTION__) << "Error Render line= " <<  SDL_GetError()  << endl;
			//retorna a cor original
			SDL_SetRenderDrawColor(myRenderer,r,g,b,a);
		}



}
void CPolygon::arcSurface(const int x, const int y, const double ang1, const double ang2, const int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 A, int method  ) const{
	if (this->getBitmap()){
		::arcRGBA(getBitmap(),  x,  y, radius, ang1, ang2, R,G,B,A);

	}else {
	//error  bitmap not set
	}

}
void CPolygon::arcTexture(const int x, const int y, const double ang1, const double ang2, const int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 A, int method  ) const{

	int num_segments= (int) GetNumCircleSegments(radius);
	SDL_Point *pontos = (SDL_Point*) ::SDL_calloc(num_segments,sizeof(SDL_Point));
	//convert to Rad
	float StartAngle=(float(_PI) * ang1) / float(180.0) ;
	float EndAngle=(float(_PI) * ang2) / float(180.0) ;
	Uint8 r,g,b,a;
	SDL_GetRenderDrawColor(getMyRender(),&r,&g,&b, &a);
	SDL_SetRenderDrawColor(getMyRender(),R, G, B, A);

	switch (method) {

	case 1 :
		//todo:
    break;
	case 2://método 2
		//Todo
	break;
	case 3:

	 // http://slabode.exofire.net/circle_draw.shtml
		//float theta = 2 * PI / float(num_segments - 1);
		float theta = EndAngle / float(num_segments - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open
		float tangetial_factor = tanf(theta);//calculate the tangential factor
		float radial_factor = cosf(theta);//calculate the radial factor
		//float cx = radius;//we start at angle = 0
		//float cy = 0;
		float cx = radius * cosf(StartAngle);//we now start at the start angle
		float cy = radius * sinf(StartAngle);
    	for(int ii = 0; ii < num_segments; ii++)
		{
			pontos[ii].x=(int)x + cx;
			pontos[ii].y=(int)y + cy;

			//calculate the tangential vector
			//remember, the radial vector is (x, y)
			//to get the tangential vector we flip those coordinates and negate one of them

			float tx = -cy;
			float ty = cx;
	        //add the tangential vector
			cx += tx * tangetial_factor;
			cy += ty * tangetial_factor;
			//correct using the radial factor
			cx *= radial_factor;
			cy *= radial_factor;
		}
		if(SDL_SetRenderDrawBlendMode(getMyRender(),GetTextureDrawBlendMode()));
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= " <<  SDL_GetError()  << endl;
		if(SDL_RenderDrawPoints(getMyRender(),pontos,num_segments)!=0)
			Debug::debug(Debug::bitmap,__FUNCTION__) << "Error= " <<  SDL_GetError()  << endl;

	    SDL_free( pontos);

	 break;

	//delete pontos1;
	} // end switch method
	SDL_SetRenderDrawColor(getMyRender(),r, g, b, a);

}
void CPolygon::arcFillSurface(const int x, const int y, const double ang1, const double ang2, const int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 A, int method  ) const{
	if (this->getBitmap()){
		 Debug::debug(Debug::bitmap,__FUNCTION__) << "CPolygon::arcFillSurface //TODO" <<  endl;

	}else {
	//error  bitmap not set
	}

}
void CPolygon::arcFillTexture(const int x, const int y, const double ang1, const double ang2, const int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 A  ) const{
		//!Todo   Pie   to Texture   if(xxx!=0)
		    Debug::debug(Debug::bitmap,__FUNCTION__) << "CPolygon::arcFillTexture //TODO" <<  endl;
			//Debug::debug(Debug::bitmap,__FUNCTION__) << "CPolygon::circleFillTexture // Error= " <<  SDL_GetError()  << endl;


}

void CPolygon::circleFillSurface( int x, int y, int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 A  ) const{
	if (this->getBitmap()){
		::filledCircleRGBA(getBitmap(), x, y, radius, R,G,B,A);
		//:SPG_CircleFilledBlend(getBitmap(), x, y, radius, color, alpha);
	}else {
	//error  bitmap not set
	}

}
void CPolygon::circleFillTexture( int x, int y, int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 A  ) const{
		//!Todo   Pie   to Texture   if(xxx!=0)
		    Debug::debug(Debug::bitmap,__FUNCTION__) << "CPolygon::circleFillTexture //TODO" <<  endl;
			//Debug::debug(Debug::bitmap,__FUNCTION__) << "CPolygon::circleFillTexture // Error= " <<  SDL_GetError()  << endl;

}
void CPolygon::circleSurface( int x, int y, int radius, int R, int G, int B, int A ) const{
	if (this->getBitmap()){
		::circleRGBA(getBitmap(),x,y,radius,R,G,B,A);

	}else {
	//error  bitmap not set
	}

}
void CPolygon::circleTexture( int x, int y, int radius, int R, int G, int B, int A, int method ) const{

		int num_segments= (int) GetNumCircleSegments(radius);
	Gui::CPoints pontos(num_segments);
	Gui::CPoints pontos1(360);
	Uint8 r,g,b,a;
	SDL_GetRenderDrawColor(getMyRender(),&r,&g,&b, &a);
	SDL_SetRenderDrawColor(getMyRender(),R, G, B, A);

	switch (method) {
	case 1 :
	//glBegin(GL_LINE_LOOP);
	//Método 1 testar eficiencia //http://basic4gl.wikispaces.com/2D+Drawing+in+OpenGL
	for (float angle=0;angle<=358;angle+=1.0)
	pontos1.Point[(int)angle]->setXY((int)x + sin(angle) * radius,(int)y + cos(angle) * radius);
	this->points(pontos1);
    break;
  case 2://método 2

	for(int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * float(_PI) * float(ii) / float(num_segments);//get the current angle
		float cx = radius * cosf(theta);//calculate the x component
		float cy = radius * sinf(theta);//calculate the y component
		pontos.Point[ii]->setXY((int)x + cx,(int) y + cy);

	}
	this->points(pontos);
 break;
 case 3:

	 // http://slabode.exofire.net/circle_draw.shtml
	float theta = 2 * float(_PI) / float(num_segments);
	float tangetial_factor = tanf(theta);//calculate the tangential factor
	float radial_factor = cosf(theta);//calculate the radial factor
	float cx = radius;//we start at angle = 0
	float cy = 0;

	for(int ii = 0; ii < num_segments; ii++)
	{
		pontos.Point[ii]->setXY((int)x + cx,(int) y + cy);
		//calculate the tangential vector
		//remember, the radial vector is (x, y)
		//to get the tangential vector we flip those coordinates and negate one of them
		float tx = -cy;
		float ty = cx;
        //add the tangential vector
		cx += tx * tangetial_factor;
		cy += ty * tangetial_factor;

		//correct using the radial factor

		cx *= radial_factor;
		cy *= radial_factor;
	}
	this->points(pontos);
	 break;
	}
	SDL_SetRenderDrawColor(getMyRender(),r,g,b,a);

}
void CPolygon::triangleSurface( int x1, int y1, int x2, int y2, int x3, int y3, Uint8 r, Uint8 g, Uint8 b , Uint8 A ) const{
	::aatrigonRGBA(getBitmap(), x1, y1, x2, y2, x3, y3, r,g,b,A );
}
void CPolygon::triangleTexture( int x1, int y1, int x2, int y2, int x3, int y3, Uint8 r, Uint8 g, Uint8 b , Uint8 A ) const{
		//!Todo   Pie   to Texture   if(xxx!=0)
		lineTexture(x1,y1,x2,y2,r,g,b,A);
		lineTexture(x2,y2,x3,y3,r,g,b,A);
		lineTexture(x3,y3,x1,y1,r,g,b,A);

}
void CPolygon::triangleFillSurface( int x1, int y1, int x2, int y2, int x3, int y3, Uint8 r, Uint8 g, Uint8 b , Uint8 A ) const{
	::filledTrigonRGBA(getBitmap(), x1, y1, x2, y2, x3, y3, r,g,b,A );
}
void CPolygon::triangleFillTexture( int x1, int y1, int x2, int y2, int x3, int y3, Uint8 r, Uint8 g, Uint8 b , Uint8 A ) const{
		//!Todo   Pie   to Texture   if(xxx!=0)
		    Debug::debug(Debug::bitmap,__FUNCTION__) << "CPolygon::triangleFillTexture //TODO" <<  endl;


}

void CPolygon::ellipseSurface( int x, int y, int rx, int ry, Uint8 r, Uint8 g, Uint8 b , Uint8 A  ) const {
	::aaellipseRGBA (getBitmap(), x,  y,  rx,  ry,  r,  g,  b, A);
	//::SPG_EllipseBlend(getBitmap(), x, y, rx, ry, color, alpha);
}
void CPolygon::ellipseTexture( int CX, int CY, int XRadius, int YRadius, Uint8 r, Uint8 g, Uint8 b , Uint8 A  ) const {


	vector<Gui::CAbsolutePoint *> pontos;
	vector<Gui::CAbsolutePoint *>::iterator it;
		//!Todo   Pie   to Texture   if(xxx!=0)
			//! algoritimo de acordo com o documento: http://homepage.smc.edu/kennedy_john/belipse.pdf
	int X, Y , XChange, YChange ,EllipseError;
	int TwoASquare, TwoBSquare;
	int StoppingX, StoppingY;

	TwoASquare = 2*XRadius*XRadius;
	TwoBSquare = 2*YRadius*YRadius;

	X = XRadius;
	Y = 0;

	XChange = YRadius*YRadius*(1-2*XRadius);
	YChange = XRadius*XRadius;
	EllipseError = 0;
	StoppingX = TwoBSquare*XRadius;
	StoppingY = 0;

	while ( StoppingX >= StoppingY ){ //1st set of points, yw>1

	//Plot4EllipsePoints(X,Y); //subroutine appears later
	Gui::CAbsolutePoint *temp1= new Gui::CAbsolutePoint(CX+X,CY+Y);
	Gui::CAbsolutePoint *temp2= new Gui::CAbsolutePoint(CX-X,CY+Y);
	Gui::CAbsolutePoint *temp3= new Gui::CAbsolutePoint(CX-X,CY-Y);
	Gui::CAbsolutePoint *temp4= new Gui::CAbsolutePoint(CX+X,CY-Y);
	pontos.push_back(temp1); //{point in quadrant 1}
	pontos.push_back(temp2); //{point in quadrant 2}
	pontos.push_back(temp3); //{point in quadrant 3}
	pontos.push_back(temp4); //{point in quadrant 4}

	Y++;
	StoppingY+= TwoASquare;
	EllipseError+= YChange;
	YChange+=TwoASquare;
	if ((2*EllipseError + XChange) > 0 ) {
	X--;
	StoppingX-=TwoBSquare;
	EllipseError+=XChange;
	XChange+=TwoBSquare;
	}

	} //1st point set is done; start the 2nd set of points
	X = 0;
	Y = YRadius;
	XChange = YRadius*YRadius;
	YChange = XRadius*XRadius*(1-2*YRadius);
	EllipseError = 0;
	StoppingX = 0;
	StoppingY = TwoASquare*YRadius;
	while ( StoppingX <= StoppingY ) { // 2nd set of points, yw< 1

	//Plot4EllipsePoints(X,Y); //subroutine appears later
	Gui::CAbsolutePoint *temp1= new Gui::CAbsolutePoint(CX+X,CY+Y);
	Gui::CAbsolutePoint *temp2= new Gui::CAbsolutePoint(CX-X,CY+Y);
	Gui::CAbsolutePoint *temp3= new Gui::CAbsolutePoint(CX-X,CY-Y);
	Gui::CAbsolutePoint *temp4= new Gui::CAbsolutePoint(CX+X,CY-Y);
	pontos.push_back(temp1); //{point in quadrant 1}
	pontos.push_back(temp2); //{point in quadrant 2}
	pontos.push_back(temp3); //{point in quadrant 3}
	pontos.push_back(temp4); //{point in quadrant 4}

	X++;
	StoppingX+=TwoBSquare;
	EllipseError+=XChange;
	XChange+=TwoBSquare;
			if ((2*EllipseError + YChange) > 0 ) {
				Y--;
				StoppingY-= TwoASquare;
				EllipseError+=YChange;
				YChange+=TwoASquare;
			}
	} //end procedure PlotEllipse
	this->points(pontos);

	//apagar os pontos
	for (it=pontos.begin(); it<pontos.end(); it++) {
	delete (*it);
	}

}
void CPolygon::ellipseFillSurface( int x, int y, int rx, int ry, Uint8 r, Uint8 g, Uint8 b , Uint8 A  ) const {
	::filledEllipseRGBA (getBitmap(), x,  y,  rx,  ry,  r,  g,  b, A);
}
void CPolygon::ellipseFillTexture( int x, int y, int rx, int ry, Uint8 r, Uint8 g, Uint8 b , Uint8 A  ) const {
		//!Todo   Pie   to Texture   if(xxx!=0)
		    Debug::debug(Debug::bitmap,__FUNCTION__) << "CPolygon::ellipseFillTexture //TODO" <<  endl;


}

void CPolygon::pieSurface(const int x, const int y, const double ang1, const double ang2, const int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a ) const{
	if (this->getBitmap()){
	::pieRGBA (getBitmap(), x,  y, radius, ang1, ang2,  r,  g, b, a);

	}else {
	//error  bitmap not set
	}
}
void CPolygon::pieTexture(const int x, const int y, const double ang1, const double ang2, const int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 a) const{
		//!Todo   Pie   to Texture   if(xxx!=0)
		    Debug::debug(Debug::bitmap,__FUNCTION__) << "CPolygon::pieTexture //TODO" <<  endl;

}
void CPolygon::pieFillSurface(const int x, const int y, const double ang1, const double ang2, const int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 A ) const{
	if (this->getBitmap()){

		::filledPieRGBA (getBitmap(), x, y, radius, ang1, ang2,R, G, B, A);
	}else {
	//error  bitmap not set
	}

}
void CPolygon::pieFillTexture(const int x, const int y, const double ang1, const double ang2, const int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 a ) const{
		//!Todo   Pie   to Texture   if(xxx!=0)
		double theta =  Util::radians(ang1);
		float cx = radius * cosf(theta);//calculate the x component
		float cy = radius * sinf(theta);//calculate the y component

		double theta2 =  Util::radians(ang2);
		float dx = radius * cosf(theta2);//calculate the x component
		float dy = radius * sinf(theta2);//calculate the y component

		this->triangleTexture(x,y,x+cx,y+cy,x+dx,y+dy,R,G,B,a);


}
} //end SGF

