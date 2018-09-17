/* ebox version 3:
 * by Jon Rafkind
 */

#ifndef _ebox_3_h
#define _ebox_3_h
#include "../SGF_Config.h"
#include "../graphics/all.h"
#include <vector>
namespace SGF {

class  SGE_API CEQuad{
public:

	CEQuad( CEQuad * const head );
	CEQuad( int w, int h, CEQuad * _parent );
	CEQuad( const CBitmap * who, int min_size, int mask_pixel, int min_x, int min_y, CEQuad * _parent );

	void draw( const CBitmap & work, int x, int y, int color, bool flipped = false );
	void draw( const CBitmap & work, int x, int y, int color, CEQuad * who );

	inline int getWidth() const{
		return width;
	}

	inline int getHeight() const{
		return height;
	}

	inline void setFull( bool x ){
		full = x;
	}

	CEQuad * getQuad( int x ) const;

	bool addQuad( CEQuad * who );

	inline int getPosX() const {
		if ( parent )
			return min_x + parent->getPosX();
		return min_x;
	}

	inline int getPosY() const {
		if ( parent )
			return min_y + parent->getPosY();
		return min_y;
	}

	void gather( int mx, int my, int x1, int y1, int x2, int y2, vector< CEQuad * > & collides, bool xflipped, bool yflipped );

	// bool collide( int mx, int my, int x1, int y1, int x2, int y2, CEQuad ** last );
	bool collide( int mx, int my, int x1, int y1, int x2, int y2, CEQuad ** last, bool xflipped = false, bool yflipped = false );
	// int collide( int mx, int my, int x1, int y1, int x2, int y2, CEQuad ** last, int depth );
	
	int calcSize();

	void setMinX( int x );
	void setMinY( int y );
	
	int getFullX1( bool xflipped = false );
	int getFullY1( bool yflipped = false );

	inline int getMinX() const{
		return min_x;
	}

	inline int getMinY() const{
		return min_y;
	}

	int totalQuads();

	~CEQuad();

protected:

	int getX1( bool xflipped = false );
	int getY1( bool yflipped = false );

	CEQuad * getQuad() const;
	void detach( CEQuad * const who );
	void checkQuad( CEQuad *& q );

	inline int numQuads() const{
		int total = 0;
		if ( quads[0] != NULL ) total++;
		if ( quads[1] != NULL ) total++;
		if ( quads[2] != NULL ) total++;
		if ( quads[3] != NULL ) total++;
		// for ( int total = 0; total < 4 && quads[total] != NULL; total++ );
		return total;
	}
	
	bool empty();
	// bool boxCollide( int zx1, int zy1, int zx2, int zy2, int zx3, int zy3, int zx4, int zy4 );

protected:

	int width, height;
	// CEQuad * quad1, * quad2, * quad3, * quad4;

	bool full;

	int min_x, min_y;
	CEQuad * quads[ 4 ];
	CEQuad * parent;
	int num_quads;

};

class  SGE_API CECollide{
public:
	CECollide( CEQuad * const head );
	// CECollide( BITMAP * who, int mask_pixel = CBitmap::MaskColor );
	CECollide( const CBitmap * who, int mask_pixel = CBitmap::getDefaultColorkey() );
	CECollide( const CBitmap & who, int mask_pixel = CBitmap::getDefaultColorkey() );
	CECollide( const CECollide & e );
	CECollide( const CECollide * e );
	CECollide( int width, int height );

	void draw( const CBitmap & work, int x, int y, int color, bool flipped = false );
	void draw( const CBitmap & work, int x, int y, int color, CEQuad * who );

	bool Collision( CECollide * col, int mx, int my, int ax, int ay, bool my_xflipped = false, bool my_yflipped = false, bool him_xflipped = false, bool him_flipped = false );
	bool Collision( int mx, int my, int ax, int ay, bool xflipped = false, bool yflipped = false );
	bool Collision( int mx, int my, int x1, int y1, int x2, int y2, bool xflipped = false, bool yflipped = false );

	int getMinHeight();
	int getMaxHeight();
	int getMinWidth();
	int getMaxWidth();
	

	CECollide * copy();

	CEQuad * getLast();

	CEQuad * getHead() const{
		return head_quad;
	}

	void gather( int mx, int my, int x1, int y1, int x2, int y2, vector< CEQuad * > & e, bool xflipped, bool yflipped );

	int calcSize();

	inline int getWidth() const{
		return head_quad->getWidth();
	}

	inline int getHeight() const{
		return head_quad->getHeight();
	}

	int numQuads() const;

	~CECollide();

private:
	void initCECollide( const CBitmap * who, int mask_pixel );
	void initQuad( CEQuad * const head );


	static long long totalTime;

protected:

	bool collide( int mx, int my, int x1, int y1, int x2, int y2, bool xflipped = false, bool yflipped = false );
	bool collide( int mx, int my, int x1, int y1, int x2, int y2, CEQuad ** last, bool xflipped, bool yflipped );
	// bool collide( int mx, int my, int x1, int y1 );

	CEQuad * head_quad;
	CEQuad * last_collide;

};
} //end SGF
#endif
