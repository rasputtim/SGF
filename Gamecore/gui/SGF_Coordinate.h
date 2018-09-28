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
#ifndef _SGF_gui_coordinate_h
#define _SGF_gui_coordinate_h
#include <vector>
#include "../SGF_Config.h"
#include "../exceptions/all.h"
using namespace std;
namespace SGF{
class CBitmap;
class Point;

namespace Gui {

namespace Space{

class CSpace;

/**
 * \class CSpace
 *
 * \ingroup SGF_Gui
 * 
 * \brief Mapeamento de coordenadas espaciais para f�sicas
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */
class  SGE_API CSpace{
public:
    CSpace(double minX, double minY, double maxX, double maxY);
    //::CPoint fromPhysical(int x, int y);

    bool operator==(const CSpace & space) const;

    double sizeX() const;
    double sizeY() const;
    double centerX() const;
    double centerY() const;
    double getLocalX(int physicalX) const;
    double getLocalY(int physicalY) const;
private:
    double minX, minY, maxX, maxY;
};

}

class  SGE_API CPoint{
    public:

    CPoint(double x=0,double y=0, double z=0); //! inicializa um ponto na origem (0,0,0)
/*
    CPoint(int x, int y); //! inicializa um ponto nas coordenadas (x,y,0)
	CPoint(int x, int y, int z); //! inicializa um ponto nas coordenadas (x,y,z)
  */  
	//CPoint(double x, double y, const Gui::Space::CSpace & space);
    //CPoint(double x, double y, double z, const Gui::Space::CSpace & space);
    //CPoint(const CPoint & point, const Gui::Space::CSpace & space);
    
	
	CPoint(const CPoint & point);

    CPoint operator+(const CPoint &);
    CPoint & operator+=(const CPoint &);
    CPoint & operator=(const CPoint &);
	
    /* convert to physical space */
    //int physicalX() const;
    //int physicalY() const;

    //const Gui::Space::CSpace & space;

	//-----------------------
	//CPoint(double numpoints); //! inicializa v�rios pontos (num_points), na coordenada (0,0,0)
	
	void set(double ponto);
	void set(double ponto1, double ponto2);
	void set(double ponto1, double ponto2, double ponto3);
	void setX(double ponto);
	void setY(double ponto);
	void setZ(double ponto);
	void setXY(double x, double y);
	void setXYZ(double x, double y, double z);
	
	double getX();
	double getY();
	double getZ();

	inline const bool operator==(const CPoint &p) const{
	    return ((this->x == p.x) && (this->y == p.y)&& (this->z == p.z));
	}
	inline const bool operator!=(const CPoint &p) const{
	    return ((this->x != p.x) || (this->y != p.y)|| (this->z != p.z));
	}
	~CPoint();


	//private:
	// devem ser private depois qe resolver problema em tab.menu
	double x; ///< coordenada horizontal do ponto
    double y; ///< coordenada vertical do ponto
	double z; //< coordenada profundidade do ponto. S� utilizado para opera��es em 3D (simula��o 3D)

    /* true if points use the same space system */
    // bool sameSpace(const CPoint & point);
};

/**
 * \class CAbsolutePoint
 *
 * \ingroup SGF_Gui
 * 
 * \brief Ponto Absoluto na tela
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */

class  SGE_API CAbsolutePoint : public CPoint {
    public:
        CAbsolutePoint(); //! inicializa um ponto na origem (0,0,0)
        explicit CAbsolutePoint(int x, int y, int z=0); //! inicializa um ponto nas coordenadas (x,y,0)
        //CAbsolutePoint(int numpoints); //! inicializa v�rios pontos (num_points), na coordenada (0,0,0)
		CAbsolutePoint(const CAbsolutePoint &);
        virtual ~CAbsolutePoint();
        
        const CAbsolutePoint & operator=(const CAbsolutePoint &);
		bool operator<(const CAbsolutePoint & other)const {

			if (this->z==0) {  //ponto 2D
			    if (this->x == other.x){
					return ((this->y < other.y));
				}else if (this->y == other.y) {
					return ((this->x < other.x));
				}else {
					return ((this->x < other.x) && (this->y < other.y)) ;
				}
			
			}else  {  //ponto 3D
				if (this->z == other.z){

						if (this->x == other.x){
							return ((this->y < other.y));
						}else if (this->y == other.y) {
							return ((this->x < other.x));
						}else {
							return ((this->x < other.x) && (this->y < other.y)) ;
						}

				}else if (this->y == other.y) { 
						if (this->x == other.x){
							return ((this->z < other.z));
						}else {
							return ((this->x < other.x) && (this->z < other.z)) ;
						}

				}else if (this->x == other.x) {
							return ((this->y < other.y) && (this->z < other.z)) ;
				}else {
					return ((this->x < other.x) && (this->y < other.y) && (this->z < other.z));
				}
			}

			 
		}

	bool operator>(const CAbsolutePoint & other)const {
		if (this->z==0) {  //ponto 2D
			    if (this->x == other.x){
					return ((this->y > other.y));
				}else if (this->y == other.y) {
					return ((this->x > other.x));
				}else {
					return ((this->x > other.x) && (this->y > other.y)) ;
				}
			
			}else  {  //ponto 3D
				if (this->z == other.z){

						if (this->x == other.x){
							return ((this->y > other.y));
						}else if (this->y == other.y) {
							return ((this->x > other.x));
						}else {
							return ((this->x > other.x) && (this->y > other.y)) ;
						}

				}else if (this->y == other.y) { 
						if (this->x == other.x){
							return ((this->z > other.z));
						}else {
							return ((this->x > other.x) && (this->z > other.z)) ;
						}

				}else if (this->x == other.x) {
							return ((this->y > other.y) && (this->z > other.z)) ;
				}else {
					return ((this->x > other.x) && (this->y > other.y) && (this->z > other.z));
				}
			}

		}

        virtual inline void setX(int x){
            this->x = x;
        }
        virtual int getX() const;
        virtual inline void setY(int y){
            this->y = y;
        }
        virtual int getY() const;
		 virtual inline void setZ(int z){
            this->z = z;
        }
		virtual int getZ() const;
		virtual void set(double ponto) {
			x=ponto;
		}
		virtual void set(double ponto1, double ponto2) {
			x=ponto1;
			y=ponto2;
		}
		virtual void set(double ponto1, double ponto2, double ponto3) {
			x=ponto1;
			y=ponto2;
			z=ponto3;
		}
		virtual inline void setXYZ(int x, int y,int z){
            this->x = x;
			this->y = y;
			this->z = z;
        }
		virtual inline void setXY(int x, int y){
            this->x = x;
			this->y = y;
			
        }

		inline const bool operator==(const CAbsolutePoint &p) const{
	    return ((this->x == p.x) && (this->y == p.y)&& (this->z == p.z));
		}
		inline const bool operator!=(const CAbsolutePoint &p) const{
	    return ((this->x != p.x) || (this->y != p.y)|| (this->z != p.z));
		}

   // private:  //por enquanto, at� corrigir  a class CElement
		
     //   int x; ///< coordenada horizontal do ponto
     //   int y; ///< coordenada vertical do ponto
	//	int z;  ///< coordenada profundidade do ponto. S� utilizado para opera��es em 3D (simula��o 3D)
};

//Classe utilizada para armazenar v�rios pontos
/// Esta Classe ser� substitu�da pela do grupo SGF_Util

class  SGE_API CPoints :public CAbsolutePoint {
public:
	CPoints(int num_points);
	~CPoints();
    int num_points;
	CAbsolutePoint **Point;
	void setPoints(int i, int x, int y, int z=0);
private:
	vector<CAbsolutePoint*> points;
};
/**
 * \class CRelativePoint
 *
 * \ingroup SGF_Gui
 * 
 * \brief Ponto Relativo na tela
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */
class  SGE_API CRelativePoint : public CPoint {
    public:
        CRelativePoint();
        explicit CRelativePoint(double x, double y);
        CRelativePoint(const CRelativePoint &);
        CRelativePoint(const CAbsolutePoint &);
        virtual ~CRelativePoint();
        
        const CRelativePoint & operator=(const CRelativePoint &);
        const CRelativePoint & operator=(const CAbsolutePoint &);
        bool operator==(const CRelativePoint &);
        bool operator!=(const CRelativePoint &);
        virtual inline void setX(double x){
            this->x = x;
        }
        virtual int getX() const;
        virtual inline void setY(double y){
            this->y = y;
        }
        virtual int getY() const;
        virtual inline void set(double x, double y){
            this->x = x;
            this->y = y;
        }
        virtual int getDistanceFromCenterX();
        virtual int getDistanceFromCenterY();
        virtual void moveX(double percent);
        virtual void moveY(double percent);
        virtual void moveBy(double x, double y);
        virtual CAbsolutePoint getAbsolute();
        virtual double getRelativeX() const;
        virtual double getRelativeY() const;
    private:
    
};
/**
 * \class CCoordinate
 *
 * \ingroup SGF_Gui
 * 
 * \brief Sistema de coordenadas para manusear gr�ficos escal�veis
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */

class  SGE_API CCoordinate {
    public:
        CCoordinate();
        CCoordinate(CAbsolutePoint &, CAbsolutePoint &);
        CCoordinate(const CRelativePoint &, const CRelativePoint &);
        CCoordinate(const CCoordinate &);
        virtual ~CCoordinate();
        
        
    
        virtual inline void setZ(double z){
            this->z = z;
        }
        virtual inline double getZ() const{
            return this->z;
        }
        virtual inline void setRadius(double radius){
            this->radius = radius;
        }
        virtual inline double getRadius() const{
            return this->radius;
        }
        
        virtual int getX() const;
        virtual int getY() const;
        virtual int getWidth() const;
        virtual int getHeight() const;
        virtual int getX2() const;
        virtual int getY2() const;
        /* give a relative quantity */
        virtual void growHorizontal(double by);
        /* give an absolute quantity */
        virtual void growHorizontalAbsolute(int by);
        /* give a relative quantity */
        virtual void growVertical(double by);
        /* give an absolute quantity */
        virtual void growVerticalAbsolute(int by);

        virtual void growTo(const CCoordinate &, double percent = 0.005);
        virtual void center(const CCoordinate &);
        virtual void moveBy(double x, double y);
        virtual inline double getRelativeX1() const{
            return this->position.getRelativeX();
        }
        virtual inline double getRelativeX2() const{
            return this->position2.getRelativeX();
        }
        virtual inline double getRelativeY1() const{
            return this->position.getRelativeY();
        }
        virtual inline double getRelativeY2() const{
            return this->position2.getRelativeY();
        }

        virtual inline void set(double x1, double y1, double x2, double y2){
            this->position.setX(x1);
            this->position.setY(y1);
            this->position2.setX(x2);
            this->position2.setY(y2);
        }

        virtual inline void setX1(double x){
            this->position.setX(x);
        }
        virtual inline void setX2(double x){
            this->position2.setX(x);
        }
        virtual inline void setY1(double y){
            this->position.setY(y);
        }
        virtual inline void setY2(double y){
            this->position2.setY(y);
        }
		const CCoordinate & operator=(const CCoordinate &);

        bool operator==( const CCoordinate &);
        bool operator!=( const CCoordinate &);
        bool operator==( const CBitmap &);
        bool operator!=( const CBitmap &);

        /* moves the positions so that `center' is in the middle but the
         * width/height is maintained
         */
        virtual void setCenterPosition(const CRelativePoint & center);

        virtual void setPosition(const CRelativePoint &);
        virtual void setPosition(const CAbsolutePoint &);
        virtual void setPosition2(const CRelativePoint &);
        virtual void setPosition2(const CAbsolutePoint &);

        virtual void moveTo(const CAbsolutePoint &);

        virtual void setDimensions(int width, int height);

        virtual inline CRelativePoint & getPosition(){
            return this->position;
        }

        virtual inline CRelativePoint & getPosition2(){
            return this->position2;
        }
        
        virtual inline bool empty(){
            return (getWidth() == 0 && getHeight() == 0);
        }
        
    private:
        void checkDimensions() throw (CLoadException);

        CRelativePoint position; //! usado para armazenar x1,y1 (ponto superior esquerdo)
        CRelativePoint position2; //! usado para armazenar x2,y2 (ponto inferior direito)
        double z;
        double radius;
};

} //end GUI

} //end SGF
#endif
