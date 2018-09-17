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

#include "objects/SGF_ObjectCollidable.h"
#include "SGF_Global.h"
#include <string>
using namespace std;
namespace SGF {

CObjectCollidable::CObjectCollidable( const int x, const int y):
CBaseObject( x, y , CBaseObject::SGFCollidable),
collide(0){
	no_name = "";
}

CObjectCollidable::CObjectCollidable( const CObjectCollidable & obj ):
CBaseObject( obj ),
collide(0){
}
CObjectCollidable::~CObjectCollidable()
{

}
void CObjectCollidable::initColision(CBitmap *pic)
{
	if (!collide.data)  {
		collide  =new CECollide(pic);
	}

}

CECollide * CObjectCollidable::getCollide() const {
    //if (animation_current != NULL){
    //    return animation_current->getCollide(getFacing());
    //}
    //Global::debug(0) << "No animation collide"<<endl;
	return collide.data;//List;
    //return vector<CECollide*>();
}
bool CObjectCollidable::collision( CObjectCollidable * obj ){
    //vector<CECollide*> myCollides = this->getCollide();
    //vector<CECollide*> himCollides = obj->getCollide();
	CECollide *myCollide = this->getCollide();
	CECollide *hisCollide = obj->getCollide();

    //for (vector<CECollide*>::iterator mine = myCollides.begin(); mine != myCollides.end(); mine++){
    //    for (vector<CECollide*>::iterator him = himCollides.begin(); him != himCollides.end(); him++){

    //        CECollide * myCollide = *mine;
    //        CECollide * hisCollide = *him;
            // cout << "Obj attacking with " << obj->getAttackName() << " my collide = " << myCollide << " his collide = " << hisCollide << endl;
            if (myCollide != 0 && hisCollide){

				bool my_xflip = false;
                bool his_xflip = false;
                if (getFacing() == FACING_LEFT)
                    my_xflip = true;
                if (obj->getFacing() == FACING_LEFT)
                    his_xflip = true;


                int my_x, my_y;
                int his_x, his_y;

				//find Center
				my_x = (this->getRX()+(getWidth()/2)) ;
				my_y = (this->getRY()+(this->getHeight()/2));
                his_x = (obj->getRX()+(obj->getWidth()/2));
                his_y = (obj->getRY()+(obj->getHeight()/2));
				Debug::debug(Debug::gameEngine,__FUNCTION__) << "PAC[x,y]=[ " << my_x << " , " << my_y << "]" <<" / GHOST{x,y] [ " << his_x<< " , "<< his_y << " ]" << endl;
                /*
                   mx = getRX();
                   my = getRY();
                   ax = obj->getRX();
                   ay = obj->getRY();
                   */

                // Bitmap Screen( screen );
                /*
                   myCollide->draw( *Bitmap::Screen, mx, my, Bitmap::makeColor( 255, 0, 128 ), my_xflip );
                   hisCollide->draw( *Bitmap::Screen, ax, ay, Bitmap::makeColor( 128, 255, 0 ), his_xflip );
                   */

                // cout<<"Mx: "<<mx<< " My: "<<my<<" Width: "<<myCollide->getWidth()<<" Height: "<<myCollide->getHeight()<<endl;
                // cout<<"Ax: "<<ax<< " Ay: "<<ay<<" Width: "<<hisCollide->getWidth()<<" Height: "<<hisCollide->getHeight()<<endl;

                bool b = myCollide->Collision( hisCollide, my_x, my_y, his_x, his_y, my_xflip, false, his_xflip, false );

                /*
                   if ( b && false ){
                   myCollide->draw( *Bitmap::Screen, 50, 50, my_xflip );
                   hisCollide->draw( *Bitmap::Screen, 50 + (ax - mx), 50 + (ay - my), his_xflip );
                   Util::rest( 500 );
                   }
                   */
                if (b){
                    return b;
                }
          //  }
       // }
    }
    return false;
}
} //end SGF