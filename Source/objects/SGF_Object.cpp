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

#include "objects/SGF_Object.h"
//#include "stimulation.h"
//#include "util/ebox.h"
//#include "script/script.h"
#include <math.h>
#include <exception>
#include <iostream>


using namespace std;

namespace SGF {

/*
const int CObject::FACING_LEFT = 0;
const int CObject::FACING_RIGHT = 1;
*/


//=======================CObjectId=====================
CObjectId::CObjectId():
id(-1){
}
    
CObjectId::CObjectId(int value):
id(value){
}

CObjectId::~CObjectId(){
}
    
CObjectId::CObjectId(const CObjectId & copy):
id(copy.id){
}

bool CObjectId::operator<(const CObjectId & him) const {
    return id < him.id;
}
    
bool CObjectId::operator==(const CObjectId & him) const {
    return id == him.id;
}

bool CObjectId::operator!=(const CObjectId & him) const {
    return !(*this == him);
}
    
int CObjectId::intValue() const {
    return id;
}

//=================END CObjectId====================



void CObjectList::addObject(CBaseObject * o){
			objects.push_back(o);
		}

CBaseObject * CObjectList::findObject(CObjectId id){

	for (vector< CBaseObject*>::iterator it = objects.begin(); it != objects.end(); it++){

        if ((*it)->getObjectId() == id){
            return (*it);
        }
    }
    return NULL;
}
static int GlobalObjectId=0;



CBaseObject::CBaseObject(ObjType type_):
actualx( 0 ),
actualy( 0 ),
actualz( 0 ),
objectId(nextObjId()),
paused(true),
alpha(255),
objectPath(""),
type(type_)
{
}

CBaseObject::CBaseObject(int x,int y,ObjType type_):
actualx( x ),
actualy( y ),
actualz( 0 ),
my_stateData(x,y),
objectId(nextObjId()),
paused(true),
alpha(255),
objectPath(""),
type(type_)
{
}
CBaseObject::CBaseObject( const CBaseObject & copy ):
	actualx(copy.actualx),
	actualy(copy.actualy),
	actualz(copy.actualz),
	my_stateData(copy.my_stateData),
	objectId(nextObjId()),
	paused(copy.paused),
	type(copy.type)

	{
}

CObjectId CBaseObject::nextObjId(){
    int now = GlobalObjectId;
    GlobalObjectId += 1;
    return CObjectId(now);
}
/* move in an absolute direction */
void CBaseObject::moveRight( const int x ){
    moveRight((double) x);
}

void CBaseObject::moveRight( const double x ){
    moveX( FACING_RIGHT, x );
}

void CBaseObject::moveLeft( const int x ){
    moveLeft((double) x);
}

void CBaseObject::moveLeft( const double x ){
    moveX( FACING_LEFT, x );
}

void CBaseObject::moveX( int dir, const int x ){
    moveX(dir, (double) x);
}



void CBaseObject::moveX( int dir, const double x ){
	
		if ( dir == getFacing() ){
			moveX( x );
		} else {
			moveX( -x );
		}
	
}
void CBaseObject::moveX( const int x ){
	moveX( (double)x ,false);
}
void CBaseObject::moveY( const int y ){
	moveY( (double)y ,false);
}

void CBaseObject::moveZ( const int z ){
	moveZ( (double)z ,false);
}

//! force:  move the object even if it is frozen
void CBaseObject::moveX(double x, bool force){
	if (force || ! my_stateData.my_frozen) {
		if ( getFacing() == FACING_LEFT ){
		my_stateData.virtualx -= x;
	} else {
		my_stateData.virtualx += x;
	}
	actualx = (int)my_stateData.virtualx;
	}else {
	actualx = (int)x;
	}
	
}

void CBaseObject::moveY(double y, bool force){
  if (force || !my_stateData.my_frozen){
	my_stateData.virtualy += y;
  }
  actualy = (int)my_stateData.virtualy;
	if ( actualy < 0 ){
		my_stateData.virtualy = 0;
		actualy = 0;
	}
}
void CBaseObject::moveZ(double z, bool force){
	if (force || ! my_stateData.my_frozen){
	  my_stateData.virtualz += z;
  }
  actualz = (int)my_stateData.virtualz;
}

void CBaseObject::moveLeftForce(double x){
    if (getFacing() == FACING_LEFT){
        moveX(x, true);
    } else {
        moveX(-x, true);
    }
}

void CBaseObject::moveRightForce(double x){
    if (getFacing() == FACING_RIGHT){
        moveX(x, true);
    } else {
        moveX(-x, true);
    }
}


//======================================================
static unsigned int ticket = 1;


CObject::CObject( int alliance ):
CBaseObject(CBaseObject::SGFObject),
health( 0 ),
max_health( 0 ),
damage( 0 ),
alliance( alliance ),
attack_ticket( ticket++ ),
my_netId( 0 ),
scriptObject(NULL){
}

CObject::CObject( const int x, const int y, int _alliance ):
CBaseObject(x,y, CBaseObject::SGFObject),
health( 0 ),
max_health( 0 ),
damage( 0 ),
alliance( _alliance ),
attack_ticket( ticket++ ),
my_netId( 0 ),
scriptObject(NULL){

}

CObject::CObject( const CObject & copy ):
CBaseObject(copy),
health( copy.health ),
max_health( copy.max_health ),
damage( copy.damage ),
alliance( copy.alliance ),
attack_ticket( copy.attack_ticket ),
my_netId( copy.my_netId ),
scriptObject(NULL){
	
}

double CObject::ZDistance( const CObject * obj ){
	return fabs( obj->getZ() - getZ() );
	/*
	if ( obj->getZ() > getZ() )
		return obj->getZ() - getZ();
	return getZ() - obj->getZ();
	*/
}

double CObject::XDistance( const CObject * obj ){
	if ( obj->getX() > getX() )
		return obj->getX() - getX();
	return getX() - obj->getX();
}
/*
void CObject::stimulate( const Stimulation & stim ){
    stim.stimulate( *this );
}*/





void CObject::faceObject( const CObject * o ){
	if ( o->getX() < getX() ){
		setFacing( CObject::FACING_LEFT );
	} else {
		setFacing( CObject::FACING_RIGHT );
	}
}

void CObject::thrown(){
}



void CObject::died( vector< CObject * > & objects ){
}



int CObject::getAlliance() const{
	return alliance;
}
	/*
void CObject::collided(CTheater * world, CObjectAttack * obj, vector< CObject * > & objects ){
	hit.play();
        if (getScriptObject() != NULL){
            void * object = NULL;
            if (obj != NULL){
                object = obj->getScriptObject();
            }
            Script::Engine::getEngine()->objectCollided(getScriptObject(), object);
        }
}  */



	/*
void CObject::interpretMessage(CTheater * world, Network::Message & message ){
    int type;
    message >> type;
    switch ( type ){
        case CObjectMessages::Moved : {
            int x, y, z, facing;
            int xfrac;
            message >> x >> xfrac >> y >> z >> facing;
            setX( x + xfrac / 100.0 );
            setY( y );
            setZ( z );
            setFacing( facing );
            break;
        }
        case CObjectMessages::Collided : {
            vector< CObject * > objects;
            // TODO: get the real object that collided instead of NULL
            collided(NULL, NULL, objects );
            break;
        }
    }
}

Network::Message CObject::collidedMessage(){
	Network::Message m;

	m.id = getId();
	m << CObjectMessages::Collided;

	return m;
}

Network::Message CObject::movedMessage(){
	Network::Message m;

	m.id = getId();
	m << CObjectMessages::Moved;
	m << (int) getX();
	/// include the decimal part of x
	m << (int) ((getX() - (int) getX()) * 100);
	m << (int) getY();
	m << (int) getZ();
	m << getFacing();

	return m;
}
	*/
void CObject::fall( double x_vel, double y_vel ){
}

void CObject::hurt( int x ){
    setHealth(getHealth() - x);
}

void CObject::reduceDamage( const double much ){
	damage -= much;
	if ( damage < 0 ){
		damage = 0;
	}
}

void CObject::takeDamage( CTheater & world, CObject * obj, int x ){
	this->hurt( x );
	damage += x;
        if (getScriptObject() != NULL){
            void * him = NULL;
            if (obj != NULL){
                him = obj->getScriptObject();
            }
            //S Script::Engine::getEngine()->objectTakeDamage(getScriptObject(), him, x);
        }
}



void CObject::touch( CObject * obj ){
}
/*
ECollide * CObject::getCollide() const {
	return 0;
}  */

CObject::~CObject(){
    if (getScriptObject() != NULL){
        //Script::Engine::getEngine()->destroyObject(getScriptObject());
    }
}
} //end SGF