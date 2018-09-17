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

#ifndef _sgf_object_h
#define _sgf_object_h
#include "../SGF_Config.h"
#include "../util/all_sound.h"
#include "../util/SGF_Pointer.h"
//#include "network/network.h"
#include <string>
#include <vector>

using namespace std;
namespace SGF{

class CBitmap;
//class ECollide;
class CObjectAttack;
class CTheater;
//class Stimulation;

namespace Script{
    class CObject;
}

#define MIN_(a,b) ((a) < (b) ? (a) : (b))
#define MAX_(a,b) ((a) > (b) ? (a) : (b))
#define MID_(a,b,c) MAX_(a,MIN_(b,c))

class CBaseObject;


/* Wrapper class for a character id (int) */
class CObjectId{
private:
    int id;

public:
    CObjectId();
    CObjectId(const CObjectId & copy);
    explicit CObjectId(int value);
    virtual ~CObjectId();
    bool operator==(const CObjectId &) const;
    bool operator!=(const CObjectId &) const;
    bool operator<(const CObjectId &) const;

    /* Used to pass the raw integer value to mugen script */
    int intValue() const;
};


/**
 * \class CObjectList
 *
 * \ingroup SGF_Objects
 *
 * \brief Controla a lista de objetos e converte tipos
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Novembro de 2012
 */
//template <typename Output>
class  SGE_API CObjectList{
public:
	CObjectList(){};
	int getSize() { return objects.size();}
	int getSize() const { return objects.size();}
	CBaseObject * getObject(int n){
		if (n >= getSize()) {
			return NULL;
			//Todo:: raise some error or message
		}else
		return objects[n];
	}
	CBaseObject * getObject(int n) const{
		return objects[n];
	}
	void eraseObject(int n) {
		objects.erase(objects.begin()+n);
	};
                //it = objects.erase(it);
	vector< CBaseObject *> & getVector(){ return objects;};
/*	vector< Output *> get(Output){
		Output * pointer = (Output *)
	}*/
	void goToBegin() {
	 it = objects.begin();
	}
	void next() {
		it++;
	}

	void addObject(CBaseObject * o);

CBaseObject * findObject(CObjectId id);

private:
vector< CBaseObject *>::iterator it;
vector< CBaseObject *> objects;

};

/**
 * \class CBaseObject
 *
 * \ingroup SGF_Objects
 *
 * \brief Classe Base para  Objetos
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CBaseObject{
public:
	enum Facing {
	FACING_LEFT=-1,
	FACING_RIGHT=1,
	FACING_UP,
	FACING_DOWN,
	};

    enum ObjType{
		SGFNone,
		SGFElement,
		SGFObject,
		SGFCollidable,
	};

	CBaseObject(ObjType type);
	CBaseObject(int x, int y, ObjType type);
	virtual ~CBaseObject(){};
	CBaseObject( const CBaseObject & copy );
	void setPaused(bool b) { paused = b; }
	/* draw:
	 * Draws the object onto the specified CBitmap
	 */
	virtual void draw(CBitmap * work, int rel_x, int rel_y){};
	virtual void draw(){};
	virtual bool load(){return true;};
	virtual void act(){}; //Act the object
	/* regular ids
    */
	ObjType getObjectType() {
		return type;
	}
	bool isElement(){
		return type == SGFElement;
	}
	bool isObject() {
		return type == SGFObject;
	}
	bool isCollidable() {
		return type == SGFCollidable;
	}

	virtual inline CObjectId getObjectId() const {
		return this->objectId;
	}

	virtual void reset()=0;

	inline double getX() const {
		return my_stateData.virtualx;
	}

	/* getY:
	 * Returns the Y coordinate of the object
	 * Y is how far the object is from the ground
	 */
	inline double getY() const {
		return my_stateData.virtualy;
	}

	/* getZ:
	 * Returns the Z coordinate of the object
	 * Z is how far the object is into the screen
	 */
	inline double getZ() const {
		return my_stateData.virtualz;
	}

	 /* getRX:
	 * Returns the absolute X position of the object
	 */
	virtual inline int getRX() const {
		return (int) getX();
	}

	virtual inline int getRZ() const {
		return (int) getZ();
	}
	/* getRY:
	 * Returns the absolute Y position of the object.
	 * This turns out to be the Z coordinate minus the Y coordinate.
	 * Z specifies how far into the screen the object is, Y is how high the
	 * object is off of the ground
	 */
	virtual inline int getRY() const {
		return (int)(getZ() - getY());
		//return (int) getY();
	}


	/* setX:
	 * Set the X coordinate
	 */
	inline void setX( const double x ){
		actualx = (int) x;
		my_stateData.virtualx = x;
	}

	/* setY:
	 * Set the Y coordinate
	 */
	inline void setY( const double y ){
		my_stateData.virtualy = y;

		actualy = (int) y;
	}

	/* setZ:
	 * Set the Z coordinate
	 */
	inline void setZ( const double z ){
		actualz = (int) z;
		my_stateData.virtualz = z;
	}

	//! Move Object
	void moveRight( const int x );
	void moveLeft( const int x );
    void moveRight(const double x);
    void moveLeft(const double x);

	void moveX( const int x );
	void moveY( const int y );
	void moveZ( const int z );


	void moveX( int dir, const int x );
    void moveX(int dir, const double x);

	virtual void moveX(double x, bool force = false);
    virtual void moveY(double y, bool force = false);
	virtual void moveZ(double y, bool force = false);
	virtual void moveLeftForce(double x);
	virtual void moveRightForce(double y);


	 void setAlpha(int a) { alpha = a; }


	/* setFacing:
	 * Sets the direction the object is facing, either left or right.
	 */
	inline virtual void setFacing( const Facing _f ){
	Debug::debug(Debug::gameObject,__FUNCTION__) << "SETTING FACING TO: "<< _f << endl;

		my_stateData.facing = _f;
		Debug::debug(Debug::gameObject,__FUNCTION__) << "FACING is now: "<< getFacing() << endl;

	}

	inline void reverseFacing(){
		setFacing( getOppositeFacing() );
	}


	inline Facing getOppositeFacing() const{
		if ( getFacing() == FACING_LEFT )
			return FACING_RIGHT;
		return FACING_LEFT;
	}

	/* getFacing:
	 * Returns the direction the object is facing.
	 */
	inline Facing getFacing() const{
		return my_stateData.facing;
	}

	SGF_INLINE void setObjectPath(string path) { objectPath=path;}
	SGF_INLINE string getObjectPath() { return objectPath;}

	void freezeObj(){
		my_stateData.my_frozen=true;
	}
	void unFreezeObj(){
		my_stateData.my_frozen=false;
	}

	struct ObjStateData{
	ObjStateData():
	virtualx(0),
	virtualy(0),
	virtualz(0),
	facing( FACING_RIGHT ){}
	ObjStateData(int x, int y):
	virtualx((double) x),
	virtualy((double)y),
	virtualz(0),
	facing( FACING_RIGHT ),
	my_frozen(false){}

	ObjStateData(const ObjStateData &copy){
	virtualx=copy.virtualx;
	virtualy=copy.virtualy;
	virtualz=copy.virtualz;
	facing = copy.facing;
	my_frozen=copy.my_frozen;
	}
	bool operator==(const ObjStateData & him) const {
            return virtualx == him.virtualx &&
                   virtualy == him.virtualy &&
                   virtualz == him.virtualz &&
				   facing   == him.facing &&
				   my_frozen== him.my_frozen;
              }


    bool operator!=(const ObjStateData & him) const {
        return !(*this == him);
    }
	ObjStateData & operator=( const ObjStateData &copy ){
		// Check for self assignment!
		if (this == &copy)      // Same object?
			return *this;
		virtualx = copy.virtualx;
        virtualy = copy.virtualy;
        virtualz = copy.virtualz;
		facing   = copy.facing;
		my_frozen = copy.my_frozen;
		 return *this;
	}

	//! Coordinates of the object in pixels

	double virtualx;
	double virtualy;
	double virtualz;
	Facing facing; // enum
	bool my_frozen; //the object is frozen and can not move

};
	const ObjStateData & getObjStateData()const { return my_stateData;};
	ObjStateData & getStateData(){
        return my_stateData;
    }
	void setObjStateData(const ObjStateData & data){
		this->my_stateData = data;
	}

	ObjStateData * getObjstateDataAddr(){return &my_stateData;};

private:
	CObjectId nextObjId();
	int actualx;
	int actualy;
	int actualz;
	const CObjectId & getObjId() const{
		 return objectId;
	}
    void setObjId(const CObjectId id){
		objectId = id;
	}


	ObjStateData my_stateData;


protected:
	 bool paused;
	 int alpha;
	 string objectPath; //para guardar informações de caminho
	 CObjectId objectId;
	 ObjType type;
};

/**
 * \class CObject
 *
 * \ingroup SGF_Objects
 *
 * \brief Classe Base para  Objetos Ativos
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class CObject: public CBaseObject{
public:

    typedef unsigned int networkid_t;

	/* Constructors
         * alliance - team number for the object. all objects on the same
         * team cannot hurt each other.
         * x - x position in the world
         * z - z position in the world
         */
	CObject( int alliance );
	CObject( const int x, const int z, int alliance );

        /* copy constructor */
	CObject( const CObject & copy );
	/* act:
	 * Performs any logic the object wants to do
	 */
	virtual void act( CObjectList & others, CTheater * world, CObjectList * add=NULL ) = 0;

	/* draw:
	 * Draws the object onto the specified CBitmap
	 */
	virtual void draw(CBitmap * work, int rel_x, int rel_y) = 0;
	/* getX:
	 * Returns the X coordinate of the object
	 */
	/* weve been grabbed */
	//virtual void grabbed( CObject * obj ) = 0;
	/* stop grabbing */
	virtual void unGrab() = 0;
	virtual bool isGrabbed() = 0;

	/* copy:
	 * Return an exact copy of this object
	 */
	virtual CObject * copy() = 0;

	/* called when this object touches 'obj' regardless of an attack.
	 * usually only called for things that are gettable, like items.
	 */
	virtual void touch( CObject * obj );

	virtual const string & getAttackName() = 0;

	/* ZDistance:
	 * Computes the distance in the Z coordinate between two
	 * objects.
	 */
	virtual double ZDistance( const CObject * obj );
	virtual double XDistance( const CObject * obj );

	/* collision:
	 * Returns true if this collides with obj
	 */
	//virtual bool collision( CObjectAttack * obj ) = 0;

	/* collided
	 * You have collided with this object. Make your time.
	 */
	//virtual void collided(CTheater * world, CObjectAttack * obj, vector< CObject * > & objects );

	/* send an arbitrary stimulation to an object */
	//virtual void stimulate( const Stimulation & stim );

	/* getCollide
	 * Returns the ECollide object that encompasses this object
	 */
	//virtual ECollide * getCollide() const;

	virtual double currentDamage() const {
		return damage;
	}

	virtual void reduceDamage( const double much = 0.09 );

	/* takeDamage
	 * Take some damage and do other things
	 */
	virtual void takeDamage( CTheater & world, CObject * obj, int x );

	/* getDamage:
	 * Gets the current amount of damage the object can do
	 */
	virtual int getDamage() const = 0;

	/* isCollidable:
	 * Returns true if this object can collide with other objects
	 */
	virtual bool isCollidable() = 0;

	virtual bool isGettable() = 0;

	/* isAttacking:
	 * Returns true if this object is performing an attack move
	 */
	virtual bool isAttacking()const = 0;

	/* getAttackCoords:
	 * Sets x, y to the upper left hand corner of the attacking
	 * bounding box.
	 */
	// virtual void getAttackCoords( int & x, int & y) = 0;

	/* getWidth:
	 * Returns the width of the object
	 */
	virtual int getWidth() const = 0;

	/* getHeight:
	 * Returns the height of the object
	 */
	virtual int getHeight() const = 0;


	//virtual Network::Message getCreateMessage() = 0;

	//virtual void interpretMessage(CTheater * world, Network::Message & m );

	//virtual Network::Message movedMessage();
	//virtual Network::Message collidedMessage();

        /* these are network ids */
	virtual inline void setNetId(networkid_t id){
		this->my_netId = id;
	}

	virtual inline networkid_t getNetId() const {
		return this->my_netId;
	}



	/* this object died. this object can add arbitrary objects
	 * into 'objects'
	 */
	virtual void died( vector< CObject * > & objects );

	/* set fall velocities */
	virtual void fall( double x_vel, double y_vel );

	/* object has been thrown */
	virtual void thrown();

	inline void setAlliance( const int x ){
		alliance = x;
	}

	virtual int getAlliance() const;



	/* getHealth:
	 * Returns the amount of health the object has left.
	 */
	inline virtual double getHealth() const {
		if ( health < 0 )
			return 0;
		return health;
		// return health;
	}

	inline int getMaxHealth() const {
		return max_health;
	}

	/* getLife:
	 * alternate spelling for getHealth()
	 */
	/*
	inline const int getLife() const {
		return getHealth();
		// return health;
	}
	*/

	/* setHealth:
	 * Sets the amount of health the object has
	 */
	inline void setHealth( int h ){
		if ( h < 0 ){
			health = 0;
		} else if ( h > getMaxHealth() ){
			health = getMaxHealth();
		} else {
			health = h;
		}
	}

	virtual inline void setMaxHealth( int h ){
		max_health = h;
	}

        /* set this object to face obj, basically auto-turn */
	virtual void faceObject( const CObject * obj );

	/* hurt:
	 * take some damage
	 */
	virtual void hurt( int x );

        virtual void setScriptObject(void * object){
            scriptObject = object;
        }

        virtual void * getScriptObject(){
            return scriptObject;
        }

	/* destructor
	 * Nothing to cleanup.
	 */
	virtual ~CObject();



private:

	double health;
	int max_health;
	double damage;
	int alliance;
	unsigned int attack_ticket;
    /** identificador de rede */
	networkid_t my_netId;
    void * scriptObject;
};
} //end SGF
#endif
