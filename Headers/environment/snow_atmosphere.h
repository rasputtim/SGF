#ifndef _snow_atmosphere_h
#define _snow_atmosphere_h

#include <vector>

class CBitmap;
class Token;

#include "atmosphere.h"

struct Flake{
    Flake(int x, int y, int type, int angle ):
        x(x),
        y(y),
        dx(x),
        dy(y),
        angle(angle),
        type(type),
        dir(0),
        spin(0){}
    int x, y;
    double dx, dy;
    int angle;
    int type;
    int dir;
    int spin;
};

class SnowAtmosphere: public Atmosphere {
public:

	SnowAtmosphere();	
	virtual ~SnowAtmosphere();

    virtual void drawBackground(CBitmap * work, int x);
	virtual void drawForeground(CBitmap * work, int x);
	virtual void drawFront(CBitmap * work, int x);
    virtual void drawScreen(CBitmap * work, int x);
	virtual void act(const Scene & level);
    virtual void interpret(Token * message);
	
protected:
    std::vector< Flake * > flakes;
};

#endif
