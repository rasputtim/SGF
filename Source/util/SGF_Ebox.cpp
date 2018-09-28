/* ebox version 3:
 * by Jon Rafkind
 */

#include "util/SGF_Ebox.h"
#include <stdio.h>
//#include "funcs.h"
#include "graphics/all.h"
#include <iostream>
#include "graphics/SGF_Poligon.h"
using namespace std;

// extern "C" void rest( int i );

// using namespace Ebox2;
namespace SGF {

#ifndef debug
// #define debug printf("File: %s Line: %d\n", __FILE__, __LINE__ );
#define debug cout<<"File: "<<__FILE__<<" Line: "<<__LINE__<<endl;
#endif

// #define MIN_SIZE 8
const int MIN_SIZE = 8;

/* copy constructor but with a pointer */
CEQuad::CEQuad( CEQuad * const head ):
width( head->width ),
height( head->height ),
full( head->full ),
min_x( head->min_x ),
min_y( head->min_y ),
parent( NULL ),
num_quads( head->num_quads ){

        for ( int q = 0; q < 4; q++ )
                quads[q] = NULL;

        for ( int i = 0; i < head->numQuads(); i++ ){
                // CEQuad * tmp = head->getQuad( i );
                quads[i] = new CEQuad( head->getQuad( i ) );
                quads[i]->parent = this;
        }

}

CEQuad::CEQuad( int w, int h, CEQuad * _parent ):
width( w ),
height( h ),
min_x( 0 ),
min_y( 0 ),
parent( _parent ),
num_quads( 0 ){
        full = true;
        for ( int i = 0; i < 4; i++ )
                quads[i] = NULL;
}

CEQuad::CEQuad( const CBitmap * who, int min_size, int mask_pixel, int _min_x, int _min_y, CEQuad * _parent ):
width( who->getWidth() ),
height( who->getHeight() ),
full( false ),
min_x( _min_x ),
min_y( _min_y ),
parent( _parent ){

        CBitmap * b1, * b2, * b3, * b4;
        CEQuad * quad1, * quad2, * quad3, * quad4;
        quad1 = quad2 = quad3 = quad4 = NULL;

        if ( width > min_size && height > min_size ){


                int w = who->getWidth() >> 1;
                int h = who->getHeight() >> 1;

                // b1 = create_sub_CBitmap( who, 0, 0, w, h );
                b1 = new CBitmap( *who, 0, 0, w, h );
                quad1 = new CEQuad( b1, min_size, mask_pixel, 0, 0, this );
                // destroy_CBitmap( b1 );
                delete b1;

                // b2 = create_sub_CBitmap( who, w, 0, w, h );
                b2 = new CBitmap( *who, w, 0, w, h );
                quad2 = new CEQuad( b2, min_size, mask_pixel, w, 0, this );
                delete b2;
                // destroy_CBitmap( b2 );


                // b3 = create_sub_CBitmap( who, 0, h, w, h );
                b3 = new CBitmap( *who, 0, h, w, h );
                quad3 = new CEQuad( b3, min_size, mask_pixel, 0, h, this );
                delete b3;
                // destroy_CBitmap( b3 );

                // b4 = create_sub_CBitmap( who, w, h, w, h );
                b4 = new CBitmap( *who, w, h, w, h );
                quad4 = new CEQuad( b4, min_size, mask_pixel, w, h, this );
                delete b4;
                // destroy_CBitmap( b4 );

                if ( quad1->empty() ){
                        delete quad1;
                        quad1 = NULL;
                }
                if ( quad2->empty() ){
                        delete quad2;
                        quad2 = NULL;
                }
                if ( quad3->empty() ){
                        delete quad3;
                        quad3 = NULL;
                }
                if ( quad4->empty() ){
                        delete quad4;
                        quad4 = NULL;
                }

                if ( quad1 && quad2 && quad3 && quad4 )
                        if ( quad1->full && quad2->full && quad3->full && quad4->full ){
                                delete quad1;
                                delete quad2;
                                delete quad3;
                                delete quad4;
                                quad1 = NULL;
                                quad2 = NULL;
                                quad3 = NULL;
                                quad4 = NULL;
                                full = true;
                        }

                checkQuad( quad1 );
                checkQuad( quad2 );
                checkQuad( quad3 );
                checkQuad( quad4 );

        } else {
                // printf("Size X:%d Y:%d\n", width, height );
                int total = 0;
                int denom = who->getWidth() * who->getHeight();

                /* empty sprite? */
                if (denom < 1){
                    denom = 1;
                }
                for ( int x = 0; x < who->getWidth(); x++ ){
                        for ( int y = 0; y < who->getHeight(); y++ ){
                                // int pixel = _getpixel16( who, x, y );
                                int pixel = who->getPixelSurface( x, y );
                                if ( pixel != mask_pixel ){
                                        ++total;
                                }
                                if ( total * 100 / denom > 50 ){
                                        /* we're done already,
                                         * stop counting pixels
                                         */
                                        goto short_circuit;
                                }
                        }
                }

                /* johnny 5 alive! */
                short_circuit:

                if ( total * 100 / denom > 50 ){
                        full = true;
                }
        }

        for ( int i = 0; i < 4; i++ )
                quads[i] = NULL;

        int i = 0;
        if ( quad1 ) quads[i++] = quad1;
        if ( quad2 ) quads[i++] = quad2;
        if ( quad3 ) quads[i++] = quad3;
        if ( quad4 ) quads[i++] = quad4;

        num_quads = numQuads();
}

bool CEQuad::addQuad( CEQuad * who ){
        int n = numQuads();
        if ( n < 4 ){
                quads[n] = who;
                full = false;
                return true;
        } else return false;
}

void CEQuad::checkQuad( CEQuad *& q ){
        if ( q != NULL ){
                while ( q->numQuads() == 1 ){
                        CEQuad * const newquad = q->getQuad();
                        q->detach( newquad );
                        int x = q->getMinX();
                        int y = q->getMinY();
                        delete q;
                        q = newquad;
                        newquad->setMinX( newquad->getMinX() + x );
                        newquad->setMinY( newquad->getMinY() + y );
                        q->parent = this;
                }
        }
}

int CEQuad::totalQuads(){
        if ( full ) return 1;
        int total = 0;
        for ( int i = 0; i < numQuads(); i++ )
                if ( quads[i] )
                        total += quads[i]->totalQuads();
                        /*
        if ( quad1 ) total += quad1->totalQuads();
        if ( quad2 ) total += quad2->totalQuads();
        if ( quad3 ) total += quad3->totalQuads();
        if ( quad4 ) total += quad4->totalQuads();
        */

        return total;
}

void CEQuad::setMinX( int x ){
        min_x = x;
}

void CEQuad::setMinY( int y ){
        min_y = y;
}

/*
int CEQuad::numQuads() const{
        int total = 0;
        / *
        if ( quad1 ) ++total;
        if ( quad2 ) ++total;
        if ( quad3 ) ++total;
        if ( quad4 ) ++total;
        * /
        for ( total = 0; total < 4 && quads[total] != NULL; total++ );

        return total;
}
*/

CEQuad * CEQuad::getQuad() const {
        return quads[0];
        /*
        if ( quad1 ) return quad1;
        if ( quad2 ) return quad2;
        if ( quad3 ) return quad3;
        if ( quad4 ) return quad4;
        return NULL;
        */
}

CEQuad * CEQuad::getQuad( int x ) const {
        return quads[x];
}

void CEQuad::detach( CEQuad * const who ){

        // printf("Detach %p\n", who );
        /*
        if ( who == quad1 ) quad1 = NULL;
        if ( who == quad2 ) quad2 = NULL;
        if ( who == quad3 ) quad3 = NULL;
        if ( who == quad4 ) quad4 = NULL;
        */
        for ( int i = 0; i < numQuads(); i++ )
                if ( who == quads[i] )
                        quads[i] = NULL;

        CEQuad * tmp[ 4 ];
        int begin = 0;
        for ( int i = 0; i < 4; i++ )
                if ( quads[i] ){
                        tmp[begin++] = quads[i];
                        quads[i] = NULL;
                }

        for ( int q = 0; q < begin; q++ )
                quads[q] = tmp[q];

}

int CEQuad::calcSize(){
        int total = sizeof(*this);
        for ( int q = 0; q < numQuads(); q++ ){
                total += quads[q]->calcSize();
        }
        return total;
}

bool CEQuad::empty(){

        if ( numQuads() == 0 ) return !full;
        // if ( !quad1 && !quad2 && !quad3 && !quad4 ) return !full;
        return false;

}

void CEQuad::draw( const CBitmap & work, int x, int y, int color, bool flipped ){

        int mx = x + getMinX();
        int my = y + getMinY();
        // cout<<"getMinX: "<<getMinX()<<endl;
        if ( flipped ){
                if ( parent ){
                        mx = x + parent->getWidth() - (getMinX()+getWidth());
                        // mx = getMinX() - parent->getWidth()/2 + x;
                        // my = y + parent->getHeight()/2 - getMinY();
                        // my = y + getMinY();

                        // mx2 = mx - getWidth();
                        // mx2 = mx + getWidth();

                        /*
                        int i;
                        i = mx;
                        mx = mx2;
                        mx2 = i;
                        */
                }
        }

        int mx2 = mx + getWidth();
        int my2 = my + getHeight();

        for ( int i = 0; i < numQuads(); i++ )
                quads[i]->draw( work, mx, my, color, flipped );

        if ( full )
                work.polygon().rectangle( mx, my, mx2, my2, color );
        /*
        if ( full )
                work->rectangle( x+getMinX(), y+getMinY(), x+getMinX()+getWidth(), y+getMinY()+getHeight(), CBitmap::makeColor(255,64,32) );
        else
                work->rectangle( x+getMinX(), y+getMinY(), x+getMinX()+getWidth(), y+getMinY()+getHeight(), color );
                */
}

void CEQuad::draw( const CBitmap & work, int x, int y, int color, CEQuad * who ){

        bool cy = false;
        for ( int i = 0; i < numQuads(); i++ )
                if ( who == quads[i] )
                        cy = true;

        int mx = x + getMinX();
        int my = y + getMinY();
        if ( cy )
                who->draw( work, mx, my, color );
        else {
                for ( int i = 0; i < numQuads(); i++ )
                        quads[i]->draw( work, mx, my, color, who );
        }

}

static bool boxCollide( int zx1, int zy1, int zx2, int zy2, int zx3, int zy3, int zx4, int zy4 ){

        if ( zx1 < zx3 && zx1 < zx4 &&
                zx2 < zx3 && zx2 < zx4 ) return false;
        if ( zx1 > zx3 && zx1 > zx4 &&
                zx2 > zx3 && zx2 > zx4 ) return false;
        if ( zy1 < zy3 && zy1 < zy4 &&
                zy2 < zy3 && zy2 < zy4 ) return false;
        if ( zy1 > zy3 && zy1 > zy4 &&
                zy2 > zy3 && zy2 > zy4 ) return false;

        return true;

}

/* sure this could be simplified, but thats no fun :p */
int CEQuad::getX1( bool xflipped ){
        if ( parent ){
                if ( xflipped ){
                        return parent->getWidth() - (getMinX() + getWidth());
                } else {
                        return getMinX();
                }
        } else {
                return getMinX();
        }
}

int CEQuad::getFullX1( bool xflipped ){
        if ( parent ){
                if ( xflipped ){
                        return parent->getFullX1( xflipped ) + parent->getWidth() - (getMinX() + getWidth());
                } else {
                        return parent->getFullX1( xflipped ) + getMinX();
                }
        } else {
                return getMinX();
        }
}

int CEQuad::getY1( bool yflipped ){
        if ( parent ){
                if ( yflipped ){
                        return parent->getHeight() - (getMinY() + getHeight());
                } else {
                        return getMinY();
                }
        } else {
                return getMinY();
        }
}

int CEQuad::getFullY1( bool yflipped ){
        if ( parent ){
                if ( yflipped ){
                        return parent->getFullY1( yflipped ) - (parent->getHeight() + getMinY() + getHeight());
                } else {
                        return parent->getFullY1( yflipped ) + getMinY();
                }
        } else {
                return getMinY();
        }
}

void CEQuad::gather( int mx, int my, int x1, int y1, int x2, int y2, vector< CEQuad * > & collides, bool xflipped, bool yflipped ){
        /*
        int rx = mx + getX1();
        int ry = my + getY1();
        */
        int rx = mx;
        int ry = my;

        int rx2 = rx + getWidth();
        int ry2 = ry + getHeight();

        if ( ! boxCollide( rx, ry, rx2, ry2, x1, y1, x2, y2 ) ){
                return;
        }

        for ( int i = 0; i < numQuads(); i++ ){
                quads[i]->gather( rx + quads[i]->getX1( xflipped ), ry + quads[i]->getY1( yflipped ), x1, y1, x2, y2, collides, xflipped, yflipped );
        }

        if ( full ){
                collides.push_back( this );
        }
}

bool CEQuad::collide( int mx, int my, int x1, int y1, int x2, int y2, CEQuad ** last, bool xflipped, bool yflipped ){

        /*
        int rx = mx + getMinX();
        int ry = my + getMinY();

        if ( parent ){
                if ( xflipped ){
                        rx = mx + parent->getWidth() - (getMinX()+getWidth());
                }
                if ( yflipped ){
                        ry = my + parent->getHeight() - (getMinY()+getHeight());
                }
        }
        */

        int rx = mx + getX1( xflipped );
        int ry = my + getY1( yflipped );

        int rx2 = rx + getWidth();
        int ry2 = ry + getHeight();

        // rect( screen, rx, ry, rx2, ry2, makecol(255,255,0) );

        bool cy = boxCollide( rx, ry, rx2, ry2, x1, y1, x2, y2 );
        if ( !cy ) return false;

        for ( int i = 0; i < numQuads(); i++ )
                if ( quads[i]->collide( rx, ry, x1, y1, x2, y2, last ) )
                        return true;

        if ( !full ) return false;
        if ( cy ) *last = this;
        return cy;

        return false;

}

CEQuad::~CEQuad(){
        /*
        if ( quad1 ) delete quad1;
        if ( quad2 ) delete quad2;
        if ( quad3 ) delete quad3;
        if ( quad4 ) delete quad4;
        */

        for ( int q = 0; q < 4; q++ )
                if ( quads[q] != NULL )
                        delete quads[q];
}

long long CECollide::totalTime = 0;
void CECollide::initCECollide( const CBitmap * who, int mask_pixel ){
        /*
        TimeDifference dif;
        dif.startTime();
        */
        head_quad = new CEQuad( who, MIN_SIZE, mask_pixel, 0, 0, NULL );
        last_collide = NULL;

        /*
        dif.endTime();
        totalTime += dif.getTime();
        cout<<"Total time taken: "<< totalTime / 1000 <<" ms" <<endl;
        */
}

CECollide::CECollide( const CBitmap * who, int mask_pixel ){
        initCECollide( who, mask_pixel );
        /*
        head_quad = new CEQuad( who, MIN_SIZE, mask_pixel, 0, 0, NULL );
        last_collide = NULL;
        */

}

CECollide::CECollide( const CBitmap & who, int mask_pixel ){

        initCECollide( &who, mask_pixel );

        /*
        head_quad = new CEQuad( &who, MIN_SIZE, mask_pixel, 0, 0, NULL );
        last_collide = NULL;
        */

}

#if 0
CECollide::CECollide( BITMAP * who, int mask_pixel ){

        CBitmap tmp( who );
        initCECollide( &tmp, mask_pixel );

        /*
        head_quad = new CEQuad( &tmp, MIN_SIZE, mask_pixel, 0, 0, NULL );
        last_collide = NULL;
        */
}
#endif

CECollide::CECollide( int width, int height ){

        last_collide = NULL;
        head_quad = new CEQuad( width, height, NULL );

}

CECollide::CECollide( const CECollide * e ){

        initQuad( e->head_quad );
        /*
        last_collide = NULL;
        head_quad = new CEQuad( e->head_quad );
        */
}

CECollide::CECollide( const CECollide & e ){
        initQuad( e.head_quad );
        /*
        last_collide = NULL;
        head_quad = new CEQuad( e.head_quad );
        */
}

CECollide::CECollide( CEQuad * const head ){
        initQuad( head );
        /*
        last_collide = NULL;
        head_quad = new CEQuad( head );
        */
}

void CECollide::initQuad( CEQuad * const head ){
        last_collide = NULL;
        head_quad = new CEQuad( head );
}

CECollide * CECollide::copy(){
        return new CECollide( head_quad );
}

int CECollide::getMinHeight(){
        return head_quad->getMinY();
}

int CECollide::getMaxHeight(){
        return head_quad->getMinY() + head_quad->getHeight();
}

int CECollide::getMinWidth(){
        return head_quad->getMinX();
}

int CECollide::getMaxWidth(){
        return head_quad->getMinX() + head_quad->getWidth();
}

int CECollide::calcSize(){
        int total = sizeof(*this);
        if ( head_quad )
                total += head_quad->calcSize();
        return total;
}

bool CECollide::collide( int mx, int my, int x1, int y1, int x2, int y2, bool xflipped, bool yflipped ){
        last_collide = NULL;
        return head_quad->collide(mx,my,x1,y1,x2,y2, &last_collide, xflipped, yflipped );
}

bool CECollide::collide( int mx, int my, int x1, int y1, int x2, int y2, CEQuad ** last, bool xflipped, bool yflipped ){
        return head_quad->collide(mx,my,x1,y1,x2,y2, last, xflipped, yflipped );
}

void CECollide::gather( int mx, int my, int x1, int y1, int x2, int y2, vector< CEQuad * > & e, bool xflipped, bool yflipped ){
        return head_quad->gather( mx, my, x1, y1, x2, y2, e, xflipped, yflipped );
}

bool CECollide::Collision( int mx, int my, int ax, int ay, bool xflipped, bool ylfipped ){

        return collide( mx, my, ax, ay, ax, ay );

}

bool CECollide::Collision( int mx, int my, int x1, int y1, int x2, int y2, bool xflipped, bool yflipped ){

        return collide( mx, my, x1, y1, x2, y2 );

}

bool CECollide::Collision( CECollide * col, int mx, int my, int ax, int ay, bool my_xflipped, bool my_yflipped, bool him_xflipped, bool him_yflipped ){
        if ( !col ) return false;

        int x1 = mx > ax ? mx : ax;
        int y1 = my > ay ? my : ay;
        int x2 = (mx+getWidth()) < (ax+col->getWidth()) ? (mx+getWidth()) : (ax+col->getWidth());
        int y2 = (my+getHeight()) < (ay+col->getHeight()) ? (my+getHeight()) : (ay+col->getHeight());

        if ( x1 > x2 ) return false;
        if ( y1 > y2 ) return false;

        vector< CEQuad * > collides1;
        gather( mx, my, x1, y1, x2, y2, collides1, my_xflipped, my_yflipped );
        vector< CEQuad * > collides2;
        col->gather( ax, ay, x1, y1, x2, y2, collides2, him_xflipped, him_yflipped );
        for ( vector< CEQuad * >::iterator it = collides1.begin(); it != collides1.end(); it++ ){
                CEQuad * e = *it;
                int px1 = mx + e->getFullX1( my_xflipped );
                int py1 = my + e->getFullY1( my_yflipped );
                int px2 = px1 + e->getWidth();
                int py2 = py1 + e->getHeight();

                // CBitmap::Screen->rectangle( px1, py1, px2, py2, CBitmap::makeColor( 128, 128, 255 ) );

                for ( vector< CEQuad * >::iterator it2 = collides2.begin(); it2 != collides2.end(); it2++ ){
                        CEQuad * e2 = *it2;
                        int zx1 = ax + e2->getFullX1( him_xflipped );
                        int zy1 = ay + e2->getFullY1( him_yflipped );

                        // printf( "Test %d,%d,%d,%d against %d,%d,%d,%d\n", px1, py1, px2, py2, zx1, zy1, zx1 + e2->getWidth(), zy1 + e2->getHeight() );

                        // CBitmap::Screen->rectangle( zx1, zy1, zx1 + e2->getWidth(), zy1 + e2->getHeight(), CBitmap::makeColor( Util::rnd( 255 ), 255, 255 ) );

                        // if ( e2->collide( zx1, zy1, px1, py1, px2, py2, &last_collide, him_xflipped, him_yflipped ) ){
                        if ( boxCollide( px1, py1, px2, py2, zx1, zy1, zx1 + e2->getWidth(), zy1 + e2->getHeight() ) ){
                                // CBitmap::Screen->rectangle( zx1, zy1, zx1 + e2->getWidth(), zy1 + e2->getHeight(), CBitmap::makeColor( 255, 255, 0 ) );
                                // cout << "Collided!" << endl;
                                // rest( 1000 );
                                return true;
                        }
                }
        }

        // rest( 100 );

        return false;

        /*
        return ( collide(mx,my,x1,y1,x2,y2,my_xflipped,my_yflipped) && col->collide(ax,ay,x1,y1,x2,y2,him_xflipped,him_yflipped) );
        */
}

/*
int CECollide::getWidth() const{
        return head_quad->getWidth();
}

int CECollide::getHeight() const{
        return head_quad->getHeight();
}
*/

void CECollide::draw( const CBitmap & work, int x, int y, int color, bool flipped ){

        head_quad->draw( work, x, y, color, flipped );

}

int CECollide::numQuads() const{
        return head_quad->totalQuads();
}

void CECollide::draw( const CBitmap & work, int x, int y, int color, CEQuad * who ){
        if ( head_quad == who )
                head_quad->draw( work, x, y, color );
        else	head_quad->draw( work, x, y, color, who );
}

CEQuad * CECollide::getLast(){
        return last_collide;
}

CECollide::~CECollide(){
        delete head_quad;
}
} //end SGF
