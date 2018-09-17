#ifndef _fog_atmosphere_h
#define _fog_atmosphere_h

class CBitmap;

#include "atmosphere.h"
#include <vector>

class Token;

struct Fog{
	Fog( int x, int y, unsigned int ang ):x(x),y(y),ang(ang){}
	int x, y;
	unsigned int ang;
};

class FogAtmosphere: public Atmosphere {
public:

	FogAtmosphere();	
	virtual ~FogAtmosphere();

	virtual void drawBackground(CBitmap * work, int x);
	virtual void drawForeground(CBitmap * work, int x);
	virtual void drawFront(CBitmap * work, int x);
	virtual void drawScreen(CBitmap * work, int x);
	virtual void act(const Scene & level);
    virtual void interpret(Token * message);

protected:
	CBitmap * fog;
	std::vector< Fog * > fogs;
};

#endif
