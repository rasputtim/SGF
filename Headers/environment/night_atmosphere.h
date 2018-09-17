#ifndef _night_atmosphere_h
#define _night_atmosphere_h

class CBitmap;

#include "../gamecore/util/token_exception.h"
#include "atmosphere.h"
#include <vector>
#include "bitmap.h"
class Token;


struct Light{
    Light(const int x, const int y, const int lower_width, const int upper_width, const int color, const int alpha):
        x(x), y(y), lower_width(lower_width), upper_width(upper_width),
        alpha(alpha), color(color){
    }

    int x, y;
    int lower_width, upper_width;
    int alpha, color;
};

class NightAtmosphere: public Atmosphere {
public:

    NightAtmosphere();	
    virtual ~NightAtmosphere();

    virtual void drawBackground(CBitmap * work, int x);
    virtual void drawForeground(CBitmap * work, int x);
    virtual void drawFront(CBitmap * work, int x);
    virtual void drawScreen(CBitmap * work, int x);
    virtual void act(const Scene & level);
    virtual void addLight(const int x, const int y, const int lower_width, const int upper_width, const int color, const int alpha);
    virtual void interpret(Token * message);

protected:

    //void drawLight(CBitmap * original, CBitmap * work, const int x, const int y, const int lower_width, const int upper_width, const int black, const int black_alpha, const int light, const int light_alpha);
    void processLight(Token * token) throw (TokenException);

    std::vector<Light*> lights;

    /* alpha between 0-255, 255 is completely dark */
    int darkness;

    CBitmap * lamp;
};

#endif
