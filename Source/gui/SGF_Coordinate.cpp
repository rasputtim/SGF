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

#include "graphics/all.h"
#include "gui/SGF_Coordinate.h"
#include "SGF_Global.h"
#include "exceptions/all.h"
#include <sstream>

using namespace SGF::Gui;
namespace SGF {
namespace Gui{
namespace Space{

CSpace::CSpace(double minX, double minY, double maxX, double maxY):
minX(minX),
minY(minY),
maxX(maxX),
maxY(maxY){
}

bool CSpace::operator==(const CSpace & space) const {
    if (this == &space){
        return true;
    }

    return minX == space.minX &&
           minY == space.minY &&
           maxX == space.maxX &&
           maxY == space.maxY;
}

#if 0
::CPoint CSpace::fromPhysical(int x, int y){
    return ::CPoint(getLocalX(x), getLocalY(y), *this);
}
#endif


double CSpace::sizeX() const {
    return maxX - minX;
}

double CSpace::sizeY() const {
    return maxY - minY;
}

double CSpace::centerX() const {
    return (maxX - minX) / 2;
}

double CSpace::centerY() const {
    return (maxY - minY) / 2;
}

double CSpace::getLocalX(int physicalX) const {
    return (physicalX - centerX()) / sizeX();
}

double CSpace::getLocalY(int physicalY) const {
    return (physicalY - centerY()) / sizeY();
}

} // end namespace SPace



} // end Namespace Gui


//===========CPoint=====================

Gui::CPoint::CPoint(double x, double y, double z):
x(x),
y(y),
z(z){
}

Gui::CPoint::CPoint(const CPoint & p) {

	this->x = p.x;
    this->y = p.y;
	this->z = p.z;

}

Gui::CPoint & Gui::CPoint::operator+=(const Gui::CPoint & point){
    *this = *this + point;
    return *this;
}

Gui::CPoint Gui::CPoint::operator+(const Gui::CPoint & point){
   // if (sameSpace(point)){
        x += point.x;
		y += point.y;
		z += point.z;
        return *this;
   // } else {
   //     return *this + CPoint(point, space);
   // }
}

Gui::CPoint &Gui::CPoint::operator=(const Gui::CPoint &p){
 //   if (!sameSpace(p)){
        /* FIXME: throw an error */
 //   }
	if (this == &p)      // Same object?
          return *this;
	this->x = p.x;
    this->y = p.y;
	this->z = p.z;

    return *this;
}


Gui::CPoint::~CPoint(){

}


void Gui::CPoint::set(double ponto) {
	x=ponto;
}
void Gui::CPoint::set(double ponto1, double ponto2) {
	x=ponto1;
	y=ponto2;
}
void Gui::CPoint::set(double ponto1, double ponto2, double ponto3) {
	x=ponto1;
	y=ponto2;
	z=ponto3;
}

void Gui::CPoint::setX(double ponto) {
	x=ponto;
}
void Gui::CPoint::setY(double ponto) {
	y=ponto;
}
void Gui::CPoint::setZ(double ponto) {
	z=ponto;
}
void Gui::CPoint::setXY(double ponto1, double ponto2) {
	x=ponto1;
	y=ponto2;
}
void Gui::CPoint::setXYZ(double ponto1, double ponto2, double ponto3) {
	x=ponto1;
	y=ponto2;
	z=ponto3;
}
double Gui::CPoint::getX() {
	return x;
}
double Gui::CPoint::getY() {
	return y;
}
double Gui::CPoint::getZ() {
	return z;
}
//===============End  CPoint

static int relativeToAbsolute(double x, int center){
  return (int)(center + (center * x));
}

static int amountFromCenterX(int x){
    return x - (640 / 2);
}

static int amountFromCenterY(int y){
    return y - (480 / 2);
}

/* scale an absolute distance to a relative distance
 * distance / absolute = X / relative
 * absolute space = 0 to 640
 * relative space = -1 to 1
 * X = distance * relative / absolute
 */
static double scaleAbsoluteToRelativeDistanceX(int distance){
    return distance * (1.0 - (-1.0)) / (640.0 - 0);
}

static double scaleAbsoluteToRelativeDistanceY(int distance){
    return distance * (1.0 - (-1.0)) / (480.0 - 0);
}

/* convert a point in absolute space to relative space */
static double absoluteToRelative(int x, int center){
	Debug::debug(Debug::gui,__FUNCTION__) << " converting x: "<< x <<" Center: " <<center<< " converted: " << (double)(x-center)/center << endl;
    return (double)(x-center)/center;
}

static double relativeToAbsoluteX(double x){
    // return relativeToAbsolute(x, Global::getScreenWidth() / 2);
    return relativeToAbsolute(x, 640 / 2);
}

static double relativeToAbsoluteY(double y){
    // return relativeToAbsolute(y, Global::getScreenHeight() / 2);
    return relativeToAbsolute(y, 480 / 2);
}

static double absoluteToRelativeX(int x){
    return absoluteToRelative(x, 640/2);
}

static double absoluteToRelativeY(int y){
    return absoluteToRelative(y, 480/2);
}

CAbsolutePoint::CAbsolutePoint():
CPoint(0,0,0){
}
CAbsolutePoint::CAbsolutePoint(int x, int y,int z):
CPoint(x,y,z){
}
CAbsolutePoint::CAbsolutePoint(const CAbsolutePoint & copy){
	this->x = copy.x;
	this->y = copy.y;
	this->z = copy.z;

}
CAbsolutePoint::~CAbsolutePoint(){
}

const CAbsolutePoint & CAbsolutePoint::operator=(const CAbsolutePoint & copy){
     if (this == &copy)      // Same object?
          return *this;
	this->x = copy.x;
    this->y = copy.y;
	this->z = copy.z;
    return *this;
}

int CAbsolutePoint::getX() const {
    return x;
}

int CAbsolutePoint::getY() const {
    return y;
}
int CAbsolutePoint::getZ() const {
    return z;
}

//-------------------------CPoints---------------------


Gui::CPoints::CPoints(int num_points):
num_points(num_points){
	//Point = (CAbsolutePoint **) malloc( num_points * sizeof(CAbsolutePoint));

	for (int i=0;i < num_points ;i++) {
	 points[i]= new CAbsolutePoint();
	}

}
void Gui::CPoints::setPoints(int index, int x, int y, int z){
if (index > num_points)
	return;
points[index]->setXYZ(x,y,z);
}
Gui::CPoints::~CPoints(){


	for (int i=0; i < num_points; i++) {
	//Debug::debug(1,__FUNCTION__) << "CPoints::~CPoints() // Destructor - Memory freed - Point: " <<i<< " x= " <<Point[i]->GetX() <<	endl;
	delete points[i];
	//Debug::debug(1,__FUNCTION__) << "CPoints::~CPoints() // Destructor - Memory freed - Point: " <<i<< " x= " <<Point[i]->GetX() <<	endl;
	}

}




// ----------------CRelativePoint



CRelativePoint::CRelativePoint():
CPoint(0,0,0){
}

CRelativePoint::CRelativePoint(double x, double y):
CPoint(x,y,0){
}

CRelativePoint::CRelativePoint(const CRelativePoint & copy){
	this->x=copy.x;
	this->y=copy.y;
	//this->z=copy.z;

}

CRelativePoint::CRelativePoint(const CAbsolutePoint & point){
x=absoluteToRelativeX(point.getX());
y=absoluteToRelativeY(point.getY());
}

CRelativePoint::~CRelativePoint(){
}

const CRelativePoint & CRelativePoint::operator=(const CRelativePoint & copy){
    this->x = copy.x;
    this->y = copy.y;
    return *this;
}
const CRelativePoint & CRelativePoint::operator=(const CAbsolutePoint & point){
    this->x = absoluteToRelativeX(point.getX());
    this->y = absoluteToRelativeY(point.getY());
    return *this;
}
bool CRelativePoint::operator==(const CRelativePoint & point){
    return (this->x == point.x && this->y == point.y);
}
bool CRelativePoint::operator!=(const CRelativePoint & point){
    return !(*this == point);
}

int CRelativePoint::getX() const{
    return relativeToAbsoluteX(x);
}

int CRelativePoint::getY() const{
    return relativeToAbsoluteY(y);
}

int CRelativePoint::getDistanceFromCenterX(){
    return amountFromCenterX(getX());
}

int CRelativePoint::getDistanceFromCenterY(){
    return amountFromCenterY(getY());
}

void CRelativePoint::moveX(double percent){
    x += percent;
}

void CRelativePoint::moveY(double percent){
    y += percent;
}

void CRelativePoint::moveBy(double x, double y){
    moveX(x);
    moveY(y);
}

CAbsolutePoint CRelativePoint::getAbsolute(){
    return CAbsolutePoint(relativeToAbsoluteX(x), relativeToAbsoluteY(y));
}

double CRelativePoint::getRelativeX() const{
    return x;
}

double CRelativePoint::getRelativeY() const{
    return y;
}

CCoordinate::CCoordinate():
position(),
position2(),
z(0),
radius(0){
}

CCoordinate::CCoordinate(CAbsolutePoint & position, CAbsolutePoint & position2):
position(position),
position2(position2),
z(0),
radius(0){
}

CCoordinate::CCoordinate(const CRelativePoint & position, const CRelativePoint & position2):
position(position),
position2(position2),
z(0),
radius(0){
}

CCoordinate::CCoordinate(const CCoordinate & copy):
position(copy.position),
position2(copy.position2),
z(copy.z),
radius(copy.radius){
}

CCoordinate::~CCoordinate(){
}

const CCoordinate & CCoordinate::operator=(const CCoordinate & copy){
	Debug::debug(Debug::gui,__FUNCTION__) << "Beguin "<<   endl;
	Debug::debug(Debug::gui,__FUNCTION__) << "copy.x "<< copy.position.getX() <<  endl;
	Debug::debug(Debug::gui,__FUNCTION__) << "copy.y "<< copy.position.getY() <<  endl;
    Debug::debug(Debug::gui,__FUNCTION__) << "this.x "<< position.getX() <<  endl;
	Debug::debug(Debug::gui,__FUNCTION__) << "this.y "<< position.getY() <<  endl;

	this->position = copy.position;
    this->position2 = copy.position2;
    this->z = copy.z;
    this->radius = copy.radius;
	Debug::debug(Debug::gui,__FUNCTION__) << "copy.x "<< copy.position.getX() <<  endl;
	Debug::debug(Debug::gui,__FUNCTION__) << "copy.y "<< copy.position.getY() <<  endl;
    Debug::debug(Debug::gui,__FUNCTION__) << "this.x "<< position.getX() <<  endl;
	Debug::debug(Debug::gui,__FUNCTION__) << "this.y "<< position.getY() <<  endl;

    Debug::debug(Debug::gui,__FUNCTION__) << "END "<<   endl;
    return *this;
}

int CCoordinate::getX() const{
    return position.getX();
}
int CCoordinate::getY() const{
    return position.getY();
}

int CCoordinate::getWidth() const {
    return position2.getX() - position.getX();
}

int CCoordinate::getHeight() const {
    return position2.getY() - position.getY();
}

int CCoordinate::getX2() const{
    return position2.getX();
}
int CCoordinate::getY2() const{
    return position2.getY();
}

void CCoordinate::growHorizontal(double by){
    position.moveX(-(by));
    position2.moveX(by);
}

void CCoordinate::growHorizontalAbsolute(int distance){
    growHorizontal(scaleAbsoluteToRelativeDistanceX(distance));
}

void CCoordinate::growVerticalAbsolute(int distance){
    growVertical(scaleAbsoluteToRelativeDistanceY(distance));
}

void CCoordinate::growVertical(double by){
    position.moveY(-(by));
    position2.moveY(by);
}

void CCoordinate::growTo(const CCoordinate & coord, double percent){
    if (position.getRelativeX() > coord.position.getRelativeX()){
        position.moveX(-(percent));
        if (position.getRelativeX() < coord.position.getRelativeX()){
            position.setX(coord.position.getRelativeX());
        }
    } else if (position.getRelativeX() < coord.position.getRelativeX()){
        position.moveX(percent);
        if (position.getRelativeX() > coord.position.getRelativeX()){
            position.setX(coord.position.getRelativeX());
        }
    }
    if (position.getRelativeY() > coord.position.getRelativeY()){
        position.moveY(-(percent));
        if (position.getRelativeY() < coord.position.getRelativeY()){
            position.setY(coord.position.getRelativeY());
        }
    } else if (position.getRelativeY() < coord.position.getRelativeY()){
        position.moveY(percent);
        if (position.getRelativeY() > coord.position.getRelativeY()){
            position.setY(coord.position.getRelativeY());
        }
    }
    if (position2.getRelativeX() > coord.position2.getRelativeX()){
        position2.moveX(-(percent));
        if (position2.getRelativeX() < coord.position2.getRelativeX()){
            position2.setX(coord.position2.getRelativeX());
        }
    } else if (position2.getRelativeX() < coord.position2.getRelativeX()){
        position2.moveX(percent);
        if (position2.getRelativeX() > coord.position2.getRelativeX()){
            position2.setX(coord.position2.getRelativeX());
        }
    }
    if (position2.getRelativeY() > coord.position2.getRelativeY()){
        position2.moveY(-(percent));
        if (position2.getRelativeY() < coord.position2.getRelativeY()){
            position2.setY(coord.position2.getRelativeY());
        }
    } else if (position2.getRelativeY() < coord.position2.getRelativeY()){
        position2.moveY(percent);
        if (position2.getRelativeY() > coord.position2.getRelativeY()){
            position2.setY(coord.position2.getRelativeY());
        }
    }
}

void CCoordinate::center(const CCoordinate & coord){
    const double centerx = (coord.getRelativeX1() + coord.getRelativeX2())/2;
    const double centery = (coord.getRelativeY1() + coord.getRelativeY2())/2;

    set(centerx, centery, centerx, centery);
}

void CCoordinate::moveBy(double x, double y){
    position.moveBy(x, y);
    position2.moveBy(x, y);
}

bool CCoordinate::operator==( const CCoordinate & coord){
    return ( (position == coord.position) &&
            (position2 == coord.position2));
}

bool CCoordinate::operator!=( const CCoordinate & coord){
    return ( !(position == coord.position) ||
            !(position2 == coord.position2));
}

bool CCoordinate::operator==( const CBitmap & bmp){
    return ( (getWidth() == bmp.getWidth()) &&
            (getHeight() == bmp.getHeight()));
}

bool CCoordinate::operator!=( const CBitmap & bmp){
    return !(*this == bmp);
}

void CCoordinate::setPosition(const CRelativePoint & point){
    position = point;
}

void CCoordinate::setPosition(const CAbsolutePoint & point){

	position = CRelativePoint(point);
	Debug::debug(Debug::gui,__FUNCTION__) << "Convert Absolute Point ( "<< point.getX()<<","<<point.getY() <<" ) to a Relative Point ("<<position.getX() << " , "<<position.getY() << ") and store in Position: " << endl;
}

void CCoordinate::setPosition2(const CRelativePoint & point){
    position2 = point;
}

void CCoordinate::setPosition2(const CAbsolutePoint & point){
    position2 = CRelativePoint(point);
}

void CCoordinate::moveTo(const CAbsolutePoint & where){
    double dx = position2.getRelativeX() - position.getRelativeX();
    double dy = position2.getRelativeY() - position.getRelativeY();
    setPosition(where);

    /* sort of ugly, use operator+ for RelativePosition */
    setPosition2(CRelativePoint(position.getRelativeX() + dx, position.getRelativeY() + dy));
}

void CCoordinate::checkDimensions() throw (CLoadException){
    if (getWidth() < 0 || getHeight() < 0){
        ::std::ostringstream out;
        out << "Cannot have a negative coordinate dimension " << getWidth() << ", " << getHeight();
        throw CLoadException(__FILE__, __LINE__, out.str());
    }
}

void CCoordinate::setDimensions(int width, int height){
    position2 = CRelativePoint(CAbsolutePoint(getX() + width, getY() + height));
}

void CCoordinate::setCenterPosition(const CRelativePoint & center){
    int width = getWidth();
    int height = getHeight();
    this->position = center;
    this->position2 = center;
    growHorizontalAbsolute(width / 2.0);
    growVerticalAbsolute(height / 2.0);
}
} //end SGF