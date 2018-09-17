#include "bitmap.h"
#include "atmosphere.h"
#include "rain_atmosphere.h"
#include "snow_atmosphere.h"
#include "night_atmosphere.h"
#include "fog_atmosphere.h"
#include "global.h"
#include "../gamecore/util/debug.h"

Atmosphere::Atmosphere(){
}
	
Atmosphere::~Atmosphere(){
}
	
Atmosphere * Atmosphere::createAtmosphere( const std::string & name ){
	if ( name == "rain" ){
		return new RainAtmosphere();
	}
	if ( name == "snow" ){
		return new SnowAtmosphere();
	}
	if ( name == "night" ){
		return new NightAtmosphere();
	}
	if ( name == "fog" ){
		return new FogAtmosphere();
	}

        Debug::debug(0) << "Invalid atmosphere name " << name << std::endl;
        /* throw an exception? */
	return NULL;
}
