#ifndef _atmosphere_h
#define _atmosphere_h

class CBitmap;

#include <string>

class Scene;
class Token;
class Atmosphere{
protected:
	Atmosphere();
public:
	virtual ~Atmosphere();

    /* drawn in front of all background things but before objects */
	virtual void drawBackground(CBitmap * work, int x) = 0;

    /* drawn in front of all objects. you might think this method should
     * be called drawFront, but its called drawForeground because its
     * in front of the background. drawFront is just for drawing on
     * what the scene calls foreground sprites.
     */
	virtual void drawForeground(CBitmap * work, int x) = 0;
        
        /* drawn only on the foreground */
	virtual void drawFront(CBitmap * work, int x) = 0;

    /* drawn on the entire screen */
    virtual void drawScreen(CBitmap * work, int x) = 0;

	virtual void act(const Scene & level) = 0;

    /* interpret a trigger's message */
    virtual void interpret(Token * message) = 0;

	static Atmosphere * createAtmosphere( const std::string & name );
};

#endif
