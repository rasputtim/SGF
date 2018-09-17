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
#ifndef _S_G_F_Poligon_h_
#define _S_G_F_Poligon_h_

#include "../SGF_Config.h"
#include "SGF_Bitmap.h"
#include "SGF_Color.h"


namespace SGF {
class CBitmap;

			 /**
			 * \class CPolygon
			 * Poligonos são segmentos de linha que passam por um
			 * conjunto de pontos 2D e estão inseridos num CBitmap
			 *
			 * \ingroup SGF_Graphics
			 * 
			 * \brief Controle de Bitmap, efeitos, drawing, blitting 
			 *
			 * \author (last to touch it) $Autor: Rasputtim $
			 *
			 * \version 1.0 $Revision: 1.0 $
			 *
			 * Contact: raputtim@hotmail.com
			 *
			 * Created on: 05 de Janeiro de 2012
			  */

class  SGE_API CPolygon: public CBitmap {
public:
    CPolygon(const CBitmap & b);
    CPolygon();
    virtual ~CPolygon();

	/** Desenha um ponto na tela, nas coordenadas x, y e com a cor definida (RGBA)
	* \param x: coordenada horizontal
	* \param y: coordenada vertical
	* \param R: componente Vermelha da cor do desenho
	* \param G: componente Verde da cor do desenho
	* \param B: componente azul da cor do desenho
	* \param A: componente Alpha da cor desenho
	*/
	virtual void point( int x, int y, Uint8 R, Uint8 G, Uint8 B, Uint8 A=255 ) const;
	virtual void point( int x, int y,  Colors::ColorDefinition color, Uint8 A=255 ) const;
	virtual void point( int x, int y) const;
    //!Desenha pontos na tela . atualmente só no modo sdl1.3 sem compatililidade
	virtual void points( Gui::CPoints &points ) const;
	virtual void points( vector<Gui::CAbsolutePoint*> &points ) const; 

	virtual void rectangle( int x1, int y1, int x2, int y2, Uint32 color_pixel, Uint8 A=255 ) const;
	/** \brief Desenha um retângulo na tela, nas coordenadas x, y e com a cor definida (RGBA)
	* \param x1: coordenada horizontal do vértice 1
	* \param y1: coordenada vertical do vértice1
	* \param x2: coordenada horizontal do vertice 2
	* \param y2: coordenada vertical do vértice 2
	* \param R: componente Vermelha da cor do desenho
	* \param G: componente Verde da cor do desenho
	* \param B: componente azul da cor do desenho
	* \param A: componente Alpha da cor desenho
	*/
	virtual void rectangle( int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B, Uint8 A=255) const;
	virtual void rectangle( int x1, int y1, int x2, int y2,  Colors::ColorDefinition color, Uint8 A=255) const;
	virtual void rectangle( int x1, int y1, int x2, int y2) const;

	virtual void rectangleFill( int x1, int y1, int x2, int y2, Uint32 color_pixel, Uint8 A=255) const;
	/** \brief Desenha um retângulo preenchido na tela, nas coordenadas x, y e com a cor definida (RGBA)
	* \param x1: coordenada horizontal do vértice 1
	* \param y1: coordenada vertical do vértice1
	* \param x2: coordenada horizontal do vertice 2
	* \param y2: coordenada vertical do vértice 2
	* \param R: componente Vermelha da cor do desenho
	* \param G: componente Verde da cor do desenho
	* \param B: componente azul da cor do desenho
	* \param A: componente Alpha da cor desenho
	*/
	virtual void rectangleFill( int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B, Uint8 A=255) const;
	virtual void rectangleFill( int x1, int y1, int x2, int y2,  Colors::ColorDefinition color, Uint8 A=255) const;
	virtual void rectangleFill( int x1, int y1, int x2, int y2) const;
	
	virtual void roundRect( int radius, int x1, int y1, int x2, int y2, Uint32 color_pixel,Uint8 A=255 )const;
	virtual void roundRect( int radius, int x1, int y1, int x2, int y2,  Colors::ColorDefinition color,Uint8 A=255 )const ;
	
	/** \brief Desenha um retângulo com bordas arredondadas na tela, nas coordenadas x, y e com a cor definida (RGBA)
	* \param x1: coordenada horizontal do vértice 1
	* \param y1: coordenada vertical do vértice1
	* \param x2: coordenada horizontal do vertice 2
	* \param y2: coordenada vertical do vértice 2
	* \param R: componente Vermelha da cor do desenho
	* \param G: componente Verde da cor do desenho
	* \param B: componente azul da cor do desenho
	* \param A: componente Alpha da cor desenho
	*/
	virtual void roundRect( int radius, int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B,Uint8 A=255 )const;
	
	virtual void roundRectFill( int radius, int x1, int y1, int x2, int y2, Uint32 color_pixel, Uint8 A=255 )const;
	virtual void roundRectFill( int radius, int x1, int y1, int x2, int y2,  Colors::ColorDefinition color, Uint8 A=255 )const;
	/** \brief Desenha um retângulo com bordas arredondadas e preenchido, com a cor definida (RGBA)
	* \param x1: coordenada horizontal do vértice 1
	* \param y1: coordenada vertical do vértice1
	* \param x2: coordenada horizontal do vertice 2
	* \param y2: coordenada vertical do vértice 2
	* \param R: componente Vermelha da cor do desenho
	* \param G: componente Verde da cor do desenho
	* \param B: componente azul da cor do desenho
	* \param A: componente Alpha da cor desenho
	*/
	virtual void roundRectFill( int radius, int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B, Uint8 A=255 )const;


	virtual void line( const int x1, const int y1, const int x2, const int y2, const Uint32 color_pixel, Uint8 A=255) const;

	/** \brief Desenha uma linha, do vértice 1 ao vértice 2 e com a cor definida (RGBA)
	* \param x1: coordenada horizontal do vértice 1
	* \param y1: coordenada vertical do vértice1
	* \param x2: coordenada horizontal do vertice 2
	* \param y2: coordenada vertical do vértice 2
	* \param R: componente Vermelha da cor do desenho
	* \param G: componente Verde da cor do desenho
	* \param B: componente azul da cor do desenho
	* \param A: componente Alpha da cor desenho
	*/	
	virtual void line( const int x1, const int y1, const int x2, const int y2, Uint8 R, Uint8 G, Uint8 B, Uint8 A=255 ) const;
	virtual void line( const int x1, const int y1, const int x2, const int y2, const  Colors::ColorDefinition color, Uint8 A=255 ) const;
	virtual void line( const int x1, const int y1, const int x2, const int y2) const;
	
	virtual void hline( const int x1, const int y1, const int x2, const Uint32 color_pixel, Uint8 A=255) const;

	/** \brief Desenha uma linha horizontal, do vértice 1 ao vértice 2 e com a cor definida (RGBA)
	* \param x1: coordenada horizontal do vértice 1
	* \param y1: coordenada vertical do vértice1
	* \param x2: coordenada horizontal do vertice 2
	* \param y2: coordenada vertical do vértice 2
	* \param R: componente Vermelha da cor do desenho
	* \param G: componente Verde da cor do desenho
	* \param B: componente azul da cor do desenho
	* \param A: componente Alpha da cor desenho
	*/	
	
	virtual void hline( const int x1, const int y1, const int x2, Uint8 R, Uint8 G, Uint8 B, Uint8 A=255 ) const;
	virtual void hline( const int x1, const int y1, const int x2, const  Colors::ColorDefinition color, Uint8 A=255 ) const;
	virtual void hline( const int x1, const int y1, const int x2 ) const;
	
	virtual void vline( const int x1, const int y1, const int y2, const Uint32 color_pixel, Uint8 A=255) const;
	
	/** \brief Desenha uma linha vertical, do vértice 1 ao vértice 2 e com a cor definida (RGBA)
	* \param x1: coordenada horizontal do vértice 1
	* \param y1: coordenada vertical do vértice1
	* \param x2: coordenada horizontal do vertice 2
	* \param y2: coordenada vertical do vértice 2
	* \param R: componente Vermelha da cor do desenho
	* \param G: componente Verde da cor do desenho
	* \param B: componente azul da cor do desenho
	* \param A: componente Alpha da cor desenho
	*/	
	virtual void vline( const int x1, const int y1, const int y2, Uint8 R, Uint8 G, Uint8 B, Uint8 A=255 ) const;
	virtual void vline( const int x1, const int y1, const int y2, const  Colors::ColorDefinition color, Uint8 A=255 ) const;
	virtual void vline( const int x1, const int y1, const int y2) const;
	
	
	virtual void lines( Gui::CPoints &points ) const ;

	virtual void arc(const int x, const int y, const double ang1, const double ang2, const int radius, const Uint32 pixel, Uint8 A=255 ) const;
	virtual void arc(const int x, const int y, const double ang1, const double ang2, const int radius, const  Colors::ColorDefinition color, Uint8 A=255  ) const;
	
	/** \brief Desenha um arco, do ângulo 1 ao ângulo 2 e com a cor definida (RGBA)
	* \param x: coordenada horizontal do centro do circulo
	* \param y: coordenada vertical do centro do circulo
	* \param ang1: ângulo inicial do arco em graus
	* \param ang2: ângulo final do arco em graus
	* \param radius: raio do arco
	* \param R: componente Vermelha da cor do desenho
	* \param G: componente Verde da cor do desenho
	* \param B: componente azul da cor do desenho
	* \param A: componente Alpha da cor desenho
	* \param method: um dos três métodos disponiveis para desenahr um arco
	*/	
	
	virtual void arc(const int x, const int y, const double ang1, const double ang2, const int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 A=255, int method=3  ) const;

	virtual void arcFill(const int x, const int y, const double ang1, const double ang2, const int radius, const Uint32 pixel, Uint8 A=255 ) const;
	virtual void arcFill(const int x, const int y, const double ang1, const double ang2, const int radius, const  Colors::ColorDefinition color, Uint8 A=255  ) const;
	
	/** \brief Desenha um arco preenchido, do ângulo 1 ao ângulo 2 e com a cor definida (RGBA)
	* \param x: coordenada horizontal do centro do circulo
	* \param y: coordenada vertical do centro do circulo
	* \param ang1: ângulo inicial do arco em graus
	* \param ang2: ângulo final do arco em graus
	* \param radius: raio do arco
	* \param R: componente Vermelha da cor do desenho
	* \param G: componente Verde da cor do desenho
	* \param B: componente azul da cor do desenho
	* \param A: componente Alpha da cor desenho
	* \param method: um dos três métodos disponiveis para desenahr um arco
	*/	
	virtual void arcFill(const int x, const int y, const double ang1, const double ang2, const int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 A=255, int method=3  ) const;

    virtual void pie(const int x, const int y, const double ang1, const double ang2, const int radius, const Uint32 pixel, Uint8 A=255 ) const;
    virtual void pie(const int x, const int y, const double ang1, const double ang2, const int radius, const  Colors::ColorDefinition color, Uint8 A=255  ) const;
	virtual void pie(const int x, const int y, const double ang1, const double ang2, const int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 A=255 ) const;
	
	virtual void pieFill(const int x, const int y, const double ang1, const double ang2, const int radius, const Uint32 pixel, Uint8 A=255 ) const;
    virtual void pieFill(const int x, const int y, const double ang1, const double ang2, const int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 A=255 ) const;
	virtual void pieFill(const int x, const int y, const double ang1, const double ang2, const int radius, const  Colors::ColorDefinition color, Uint8 A=255  ) const;


	virtual void circle( int x, int y, int radius, Uint32 color_pixel, Uint8 A=255 ) const;
	/** \brief Desenha um círculo, com a cor definida (RGBA)
	* \param x: coordenada horizontal do centro do circulo
	* \param y: coordenada vertical do centro do circulo
	* \param radius: raio do círculo
	* \param R: componente Vermelha da cor do desenho
	* \param G: componente Verde da cor do desenho
	* \param B: componente azul da cor do desenho
	* \param A: componente Alpha da cor desenho
	* \param method: um dos três métodos disponiveis para desenahr um arco
	*/	
	virtual void circle( int x, int y, int radius, int R, int G, int B, int A, int method=3 ) const;


	virtual void circleFill( int x, int y, int radius, Uint32 color_pixel, Uint8 A=255 ) const;
	virtual void circleFill( int x, int y, int radius,  Colors::ColorDefinition color ,Uint8 A=255) const;
	/** \brief Desenha um círculo preenchido, com a cor definida (RGBA)
	* \param x: coordenada horizontal do centro do circulo
	* \param y: coordenada vertical do centro do circulo
	* \param radius: raio do círculo
	* \param R: componente Vermelha da cor do desenho
	* \param G: componente Verde da cor do desenho
	* \param B: componente azul da cor do desenho
	* \param A: componente Alpha da cor desenho
	* \param method: um dos três métodos disponiveis para desenahr um arco
	*/	
	virtual void circleFill( int x, int y, int radius, int R, int G, int B, int A=255) const;


	virtual void triangle( int x1, int y1, int x2, int y2, int x3, int y3, Uint32 color_pixel , Uint8 A=255 ) const;
	virtual void triangle( int x1, int y1, int x2, int y2, int x3, int y3, Uint8 R, Uint8 G, Uint8 B, Uint8 A=255  ) const;
	virtual void triangle( int x1, int y1, int x2, int y2,int x3, int y3,  Colors::ColorDefinition color, Uint8 A=255  ) const;
	
	virtual void equilateralTriangle(int x, int y, int angle, int size, int color) const;

	
	virtual void ellipse(int x, int y, int rx, int ry,  Colors::ColorDefinition color, Uint8 A=255  ) const;
	virtual void ellipse(int x, int y, int rx, int ry, Uint32 color_pixel , Uint8 A=255  ) const;
	virtual void ellipse(int x, int y, int rx, int ry, Uint8 R, Uint8 G, Uint8 B, Uint8 A=255  ) const;
	
	virtual void ellipseFill(int x, int y, int rx, int ry,  Colors::ColorDefinition color, Uint8 A=255  ) const;
	virtual void ellipseFill( int x, int y, int rx, int ry, Uint32 color_pixel , Uint8 A=255  ) const;
	virtual void ellipseFill( int x, int y, int rx, int ry, Uint8 R, Uint8 G, Uint8 B, Uint8 A=255  ) const;

	//virtual void floodfill( const int x, const int y, const int color ) const;
	virtual void horizontalLine( const int x1, const int y, const int x2, const int color ) const;
	virtual void hLine( const int x1, const int y, const int x2, const Colors::ColorDefinition color ) const;
	virtual void hLine( const int x1, const int y, const int x2, const int color ) const;
	virtual void vLine( const int y1, const int x, const int y2, const Colors::ColorDefinition color ) const;
	virtual void vLine( const int y1, const int x, const int y2, const int color ) const;
	virtual void polygon( const Sint16 * xverts, const Sint16 * yverts, const int nverts, const int color ) const;

protected:

	//Draw methods
	void rectangleSurface( int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B, Uint8 A  ) const;
	void rectangleTexture( int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B, Uint8 A  ) const;
	void rectangleFillSurface( int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B, Uint8 A  ) const;
	void rectangleFillTexture( int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B, Uint8 A  ) const;
	
	void roundRectSurface( int radius, int x1, int y1, int x2, int y2,  Uint8 R, Uint8 G, Uint8 B, Uint8 A  )const ;
	void roundRectTexture( int radius, int x1, int y1, int x2, int y2,  Uint8 R, Uint8 G, Uint8 B, Uint8 A  )const ;
	void roundRectFillSurface( int radius, int x1, int y1, int x2, int y2,  Uint8 R, Uint8 G, Uint8 B, Uint8 A  ) const;
	void roundRectFillTexture( int radius, int x1, int y1, int x2, int y2,  Uint8 R, Uint8 G, Uint8 B, Uint8 A  ) const;


	void lineSurface( const int x1, const int y1, const int x2, const int y2, Uint8 R, Uint8 G, Uint8 B, Uint8 A ) const;
	void lineTexture( const int x1, const int y1, const int x2, const int y2, Uint8 R, Uint8 G, Uint8 B, Uint8 A ) const;
	
	void arcSurface(const int x, const int y, const double ang1, const double ang2, const int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 A, int method=3  ) const;
	void arcTexture(const int x, const int y, const double ang1, const double ang2, const int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 A, int method=3  ) const;
    void arcFillSurface(const int x, const int y, const double ang1, const double ang2, const int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 A, int method=3  ) const;
	void arcFillTexture(const int x, const int y, const double ang1, const double ang2, const int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 A ) const;
   
	void circleFillSurface( int x, int y, int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 A  ) const;
	void circleFillTexture( int x, int y, int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 A  ) const;
	void circleSurface( int x, int y, int radius, int R, int G, int B, int A ) const;
	void circleTexture( int x, int y, int radius, int R, int G, int B, int A, int method=3 ) const;

	void triangleSurface( int x1, int y1, int x2, int y2, int x3, int y3, Uint8 r, Uint8 g, Uint8 b , Uint8 A ) const;
	void triangleTexture( int x1, int y1, int x2, int y2, int x3, int y3, Uint8 r, Uint8 g, Uint8 b , Uint8 A ) const;
	void triangleFillSurface( int x1, int y1, int x2, int y2, int x3, int y3, Uint8 r, Uint8 g, Uint8 b , Uint8 A ) const;
	void triangleFillTexture( int x1, int y1, int x2, int y2, int x3, int y3, Uint8 r, Uint8 g, Uint8 b , Uint8 A ) const;
	
	void ellipseSurface( int x, int y, int rx, int ry, Uint8 r, Uint8 g, Uint8 b , Uint8 A  ) const; 
	void ellipseTexture( int x, int y, int rx, int ry, Uint8 r, Uint8 g, Uint8 b , Uint8 A  ) const; 
	void ellipseFillSurface( int x, int y, int rx, int ry, Uint8 r, Uint8 g, Uint8 b , Uint8 A  ) const;
	void ellipseFillTexture( int x, int y, int rx, int ry, Uint8 r, Uint8 g, Uint8 b , Uint8 A  ) const;
    
	void pieSurface(const int x, const int y, const double ang1, const double ang2, const int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 A=255 ) const;
	void pieTexture(const int x, const int y, const double ang1, const double ang2, const int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 A=255 ) const;
	void pieFillSurface(const int x, const int y, const double ang1, const double ang2, const int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 A=255 ) const;
	void pieFillTexture(const int x, const int y, const double ang1, const double ang2, const int radius, Uint8 R, Uint8 G, Uint8 B, Uint8 A=255 ) const;


};//:public Ceylan::Locatable2D
#if 0
			{
			
				public:
				
				
					/**
					 * Creates a polygon from a suite of summit vertices. 
					 *
					 * @param summits the input list of summits for this
					 * polygon.
					 *
					 * @param listOwner tells whether this polygon owns the
					 * specified point list <b>and</b> the points in it 
					 * (and therefore will deallocate them) or not (in this
					 * case, neither the list object nor the points will be
					 * deallocated).
					 *
					 * @note Never put twice the same point object in the 
					 * list if the polygon is going to own its points, 
					 * since the duplicated points would be deleted twice,
					 * which results usually in a segmentation fault.
					 *
					 */
					explicit CPolygon( listPoint2D & summits, 
						bool listOwner = false ) throw() ;
					
					CPolygon(const CBitmap & b);
					/// Basic virtual destructor.
					virtual ~CPolygon() throw() ;
					
			};

					
					/**
					 * Draws the polygon on specified surface, with 
					 * specified color.
					 *
					 * The polygon can be rendered after transformation 
					 * with the embedded matrix, the referential of this
					 * Locatable.
					 *
					 * In all cases the place where to render the polygon 
					 * on surface is determined by this inner matrix.
					 *
					 * @param targetSurface the surface to draw to.
					 *
					 * @param colorDef the polygon color.
					 *
					 * @param filled tells whether the polygon should be 
					 * filled.
					 *
					 * @return true iff rendering succeeded.
					 *
					 */
					virtual bool draw( Surface & targetSurface,
							Pixels::ColorDefinition colorDef = Pixels::White, 
							bool filled = true )
						const throw() ;
						
					
					/**
					 * Returns the points that this polygon gathered. 
					 *
					 * @note What can be done with these points depends 
					 * on whether the polygon owns its points or not.
					 *
					 */
					virtual listPoint2D & getPoints() const throw() ;
						
						
					/**
					 * Sets the vertex list for this polygon.
					 *
					 * @param newList the new list of vertices.
					 *
					 * Any pre-existing owned list will be deallocated
					 * first.
					 *
					 */
					virtual void setPoints( listPoint2D & newList ) throw() ;
					
					
						
					/// Tells whether the polygon owns its points.
					virtual bool isListOwner() const throw() ;
										
					 	
	 	            /**
		             * Returns an user-friendly description of the state 
					 * of this object.
		             *
					 * @param level the requested verbosity level.
					 *
					 * @note Text output format is determined from 
					 * overall settings.
					 *
					 * @see Ceylan::TextDisplayable
		             *
		             */
			 		virtual const string toString( 
							Ceylan::VerbosityLevels level = Ceylan::high ) 
						const throw() ;
					
					
					
					
					// Static section.
					
					
					
					/**
					 * Creates a polygon whose shape is a snow flake, and 
					 * which has no local referential registered.
					 *
					 * @note The caller should deallocate this polygon when
					 * finished with it.
					 *
					 * @param length defines the height of the main branch 
					 * of this flake.
					 *
					 * @param thickness defines the width of the main 
					 * branch of this flake.
					 *
					 * @param childAngle defines the angle, in degrees, 
					 * between the main branch and the second branch.
					 *
					 * @param branchingHeightRatio tells at which height 
					 * of the main branch the second shall begin.
					 *
					 * @param scale defines the ratio of the second branch
					 * relatively to the main one.
					 *
					 * @return A polygon which does not own its points, so 
					 * that they can be freely used thanks to getPoints(). 
					 * Hence the caller will have to deallocate them
					 * explicitly (deallocating the returned polygon will 
					 * not be enough).
					 *
					 * @see PolygonSet::CreateFlake	 
					 *
					 */
					static CPolygon & CreateFlakeBranch( 
						Length length = 200,
						Length thickness = 20, 
						Ceylan::Maths::AngleInDegrees childAngle = 50, 
						Ceylan::Maths::Ratio branchingHeightRatio = 0.7, 
						Ceylan::Maths::Ratio scale = 0.3 ) throw() ;
					
					
					/**
					 * Duplicates specified list of points: returns 
					 * another list containing clones of each points in
					 * <b>source</b>.
					 *
					 * @return The duplicated list of points.
					 *
					 */
					static listPoint2D & Duplicate( const listPoint2D & source )
						throw() ;
	
	
					/**
					 * Deletes specified list of points, including the 
					 * points themselves.
					 *
					 */
					static void Delete( listPoint2D & listToBeDeleted ) 
						throw() ;
					
					
					
					/**
					 * Appends a shallow (not deep) copy of the 
					 * <b>toAppend</b> list to the <b>toBeAugmented</b> list.
					 *
					 * @note the <b>toBeAugmented</b> takes ownership of the
					 * points of <b>toAppend</b>, if <b>toBeAugmented</b> is
					 * a point owner list.
					 *
					 * @return toBeAugmented after it has been augmented 
					 * by toAppend's points.
					 * It is the same list as specified in argument, but
					 * modified: no copy is made. 
					 * Hence the returned value can be ignored, it is just
					 * convenient when chaining functions.
					 *
					 */
					static listPoint2D & Append( listPoint2D & toBeAugmented, 
						const listPoint2D & toAppend ) throw() ;
						
						
					/**
					 * Applies <b>transformation</b>, specified as a 3x3
					 * homogeneous matrix, to each point of <b>sourceList</b>.
					 *
					 * @param transformation the 2D geometrical 
					 * transformation, specified as a 3x3 homogeneous matrix.
					 *
					 * @param sourceList the list of points to transform. 
					 * It will be updated thanks to the transformation.
					 *
					 * @return sourceList after all its points have been
					 * transformed. 
					 * It is the same list as specified in argument, but
					 * modified: no copy is made. 
					 * Hence the returned value can be ignored, it is just
					 * convenient when chaining functions.
					 *
					 */	
					static listPoint2D & Apply( 
						const Ceylan::Maths::Linear::HomogeneousMatrix3 
							& transformation,
						listPoint2D & sourceList ) throw() ;
						
					
					
					
				private:
			
				
/* 
 * Takes care of the awful issue of Windows DLL with templates.
 *
 * @see Ceylan's developer guide and README-build-for-windows.txt 
 * to understand it, and to be aware of the associated risks. 
 * 
 */
#pragma warning( push )
#pragma warning( disable: 4251 )

					/// List of the summits of the polygon.
					listPoint2D * _summits ;

#pragma warning( pop ) 
			
					
					/**
					 * Tells whether the polygon owns the lists and the 
					 * points that are stored in it.
					 *
					 */					
					bool _listOwner ;
					
				
				
					/**
					 * Copy constructor made private to ensure that 
					 * it will be never called.
					 *
					 * The compiler should complain whenever this 
					 * undefined constructor is called, implicitly or not.
					 *
					 */			 
					explicit CPolygon( const CPolygon & source ) throw() ;
					
					
			
					/**
					 * Assignment operator made private to ensure 
					 * that it will be never called.
					 *
					 * The compiler should complain whenever this 
					 * undefined operator is called, implicitly or not.
					 *
					 */			 
					CPolygon & operator = ( const CPolygon & source ) throw() ;

					
			} ;
#endif
} //end namespace SGF
#endif
