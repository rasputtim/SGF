#ifndef _rain_atmosphere_h
#define _rain_atmosphere_h

#include "atmosphere.h"
//#include "util/sound.h"
#include <vector>

class CBitmap;
class Token;

struct Drop{
	Drop( int x, int y, int length, int color ):x(x),y(y),length(length),color(color){}
	int x, y;
	int length;
	int color;
};

struct Puddle{
    Puddle(int x, int y, int size):
        x(x), y(y), size(size), current(1){
        }

    int x, y;
    int size;
    double current;
};

class RainAtmosphere: public Atmosphere {
public:

	RainAtmosphere();	
	virtual ~RainAtmosphere();

	virtual void drawBackground(CBitmap * work, int x);
	virtual void drawForeground(CBitmap * work, int x);
	virtual void drawFront(CBitmap * work, int x);
	virtual void drawScreen(CBitmap * work, int x);
	virtual void act(const Scene & level);
    virtual void interpret(Token * message);
	
protected:
        std::vector<Drop *> rain_drops;
        std::vector<Puddle *> puddles;
	//Sound rain_sound;
	bool playing;
};

#endif
