/*
  SGF - Super Game Fabric  Super Game Fabric
  Copyright (C) 2010-2011 Rasputtim <raputtim@hotmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the freeMem Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the freeMem Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

  */

#ifndef __MATH_INTERPOLATE_H__
#define __MATH_INTERPOLATE_H__
#include "../SGF_Config.h"
namespace SGF {
/*
==============================================================================================

	Linear interpolation.

==============================================================================================
*/

template< class type >
class CInterpolation {
public:
						CInterpolation();

	void				Init( const float startTime, const float duration, const type &startValue, const type &endValue );
	void				SetStartTime( float time ) { this->startTime = time; }
	void				SetDuration( float duration ) { this->duration = duration; }
	void				SetStartValue( const type &startValue ) { this->startValue = startValue; }
	void				SetEndValue( const type &endValue ) { this->endValue = endValue; }

	type				GetCurrentValue( float time ) const;
	bool				IsDone( float time ) const { return ( time >= startTime + duration ); }

	float				GetStartTime() const { return startTime; }
	float				GetEndTime() const { return startTime + duration; }
	float				GetDuration() const { return duration; }
	const type &		GetStartValue() const { return startValue; }
	const type &		GetEndValue() const { return endValue; }

private:
	float				startTime;
	float				duration;
	type				startValue;
	type				endValue;
	mutable float		currentTime;
	mutable type		currentValue;
};

/*
====================
CInterpolation::CInterpolation
====================
*/
template< class type >
SGF_INLINE_FORCED CInterpolation<type>::CInterpolation() {
	currentTime = startTime = duration = 0;
	memset( &currentValue, 0, sizeof( currentValue ) );
	startValue = endValue = currentValue;
}

/*
====================
CInterpolation::Init
====================
*/
template< class type >
SGF_INLINE_FORCED void CInterpolation<type>::Init( const float startTime, const float duration, const type &startValue, const type &endValue ) {
	this->startTime = startTime;
	this->duration = duration;
	this->startValue = startValue;
	this->endValue = endValue;
	this->currentTime = startTime - 1;
	this->currentValue = startValue;
}

/*
====================
CInterpolation::GetCurrentValue
====================
*/
template< class type >
SGF_INLINE_FORCED type CInterpolation<type>::GetCurrentValue( float time ) const {
	float deltaTime;

	deltaTime = time - startTime;
	if ( time != currentTime ) {
		currentTime = time;
		if ( deltaTime <= 0 ) {
			currentValue = startValue;
		} else if ( deltaTime >= duration ) {
			currentValue = endValue;
		} else {
			currentValue = startValue + ( endValue - startValue ) * ( (float) deltaTime / duration );
		}
	}
	return currentValue;
}


/*
==============================================================================================

	Continuous interpolation with linear acceleration and deceleration phase.
	The velocity is continuous but the acceleration is not.

==============================================================================================
*/

template< class type >
class idInterpolateAccelDecelLinear  {
public:
						idInterpolateAccelDecelLinear();

	void				Init( const float startTime, const float accelTime, const float decelTime, const float duration, const type &startValue, const type &endValue );
	void				SetStartTime( float time ) { startTime = time; Invalidate(); }
	void				SetStartValue( const type &startValue ) { this->startValue = startValue; Invalidate(); }
	void				SetEndValue( const type &endValue ) { this->endValue = endValue; Invalidate(); }

	type				GetCurrentValue( float time ) const;
	type				GetCurrentSpeed( float time ) const;
	bool				IsDone( float time ) const { return ( time >= startTime + accelTime + linearTime + decelTime ); }

	float				GetStartTime() const { return startTime; }
	float				GetEndTime() const { return startTime + accelTime + linearTime + decelTime; }
	float				GetDuration() const { return accelTime + linearTime + decelTime; }
	float				GetAcceleration() const { return accelTime; }
	float				GetDeceleration() const { return decelTime; }
	const type &		GetStartValue() const { return startValue; }
	const type &		GetEndValue() const { return endValue; }

private:
	float				startTime;
	float				accelTime;
	float				linearTime;
	float				decelTime;
	type				startValue;
	type				endValue;
	mutable CExtrapolation<type> extrapolate;

	void				Invalidate();
	void				SetPhase( float time ) const;
};

/*
====================
idInterpolateAccelDecelLinear::idInterpolateAccelDecelLinear
====================
*/
template< class type >
SGF_INLINE_FORCED idInterpolateAccelDecelLinear<type>::idInterpolateAccelDecelLinear() {
	startTime = accelTime = linearTime = decelTime = 0;
	memset( &startValue, 0, sizeof( startValue ) );
	endValue = startValue;
}

/*
====================
idInterpolateAccelDecelLinear::Init
====================
*/
template< class type >
SGF_INLINE_FORCED void idInterpolateAccelDecelLinear<type>::Init( const float startTime, const float accelTime, const float decelTime, const float duration, const type &startValue, const type &endValue ) {
	type speed;

	this->startTime = startTime;
	this->accelTime = accelTime;
	this->decelTime = decelTime;
	this->startValue = startValue;
	this->endValue = endValue;

	if ( duration <= 0.0f ) {
		return;
	}

	if ( this->accelTime + this->decelTime > duration ) {
		this->accelTime = this->accelTime * duration / ( this->accelTime + this->decelTime );
		this->decelTime = duration - this->accelTime;
	}
	this->linearTime = duration - this->accelTime - this->decelTime;
	speed = ( endValue - startValue ) * ( 1000.0f / ( (float) this->linearTime + ( this->accelTime + this->decelTime ) * 0.5f ) );

	if ( this->accelTime ) {
		extrapolate.Init( startTime, this->accelTime, startValue, ( startValue - startValue ), speed, EXTRAPOLATION_ACCELLINEAR );
	} else if ( this->linearTime ) {
		extrapolate.Init( startTime, this->linearTime, startValue, ( startValue - startValue ), speed, EXTRAPOLATION_LINEAR );
	} else {
		extrapolate.Init( startTime, this->decelTime, startValue, ( startValue - startValue ), speed, EXTRAPOLATION_DECELLINEAR );
	}
}

/*
====================
idInterpolateAccelDecelLinear::Invalidate
====================
*/
template< class type >
SGF_INLINE_FORCED void idInterpolateAccelDecelLinear<type>::Invalidate() {
	extrapolate.Init( 0, 0, extrapolate.GetStartValue(), extrapolate.GetBaseSpeed(), extrapolate.GetSpeed(), EXTRAPOLATION_NONE );
}

/*
====================
idInterpolateAccelDecelLinear::SetPhase
====================
*/
template< class type >
SGF_INLINE_FORCED void idInterpolateAccelDecelLinear<type>::SetPhase( float time ) const {
	float deltaTime;

	deltaTime = time - startTime;
	if ( deltaTime < accelTime ) {
		if ( extrapolate.GetExtrapolationType() != EXTRAPOLATION_ACCELLINEAR ) {
			extrapolate.Init( startTime, accelTime, startValue, extrapolate.GetBaseSpeed(), extrapolate.GetSpeed(), EXTRAPOLATION_ACCELLINEAR );
		}
	} else if ( deltaTime < accelTime + linearTime ) {
		if ( extrapolate.GetExtrapolationType() != EXTRAPOLATION_LINEAR ) {
			extrapolate.Init( startTime + accelTime, linearTime, startValue + extrapolate.GetSpeed() * ( accelTime * 0.001f * 0.5f ), extrapolate.GetBaseSpeed(), extrapolate.GetSpeed(), EXTRAPOLATION_LINEAR );
		}
	} else {
		if ( extrapolate.GetExtrapolationType() != EXTRAPOLATION_DECELLINEAR ) {
			extrapolate.Init( startTime + accelTime + linearTime, decelTime, endValue - ( extrapolate.GetSpeed() * ( decelTime * 0.001f * 0.5f ) ), extrapolate.GetBaseSpeed(), extrapolate.GetSpeed(), EXTRAPOLATION_DECELLINEAR );
		}
	}
}

/*
====================
idInterpolateAccelDecelLinear::GetCurrentValue
====================
*/
template< class type >
SGF_INLINE_FORCED type idInterpolateAccelDecelLinear<type>::GetCurrentValue( float time ) const {
	SetPhase( time );
	return extrapolate.GetCurrentValue( time );
}

/*
====================
idInterpolateAccelDecelLinear::GetCurrentSpeed
====================
*/
template< class type >
SGF_INLINE_FORCED type idInterpolateAccelDecelLinear<type>::GetCurrentSpeed( float time ) const {
	SetPhase( time );
	return extrapolate.GetCurrentSpeed( time );
}


/*
==============================================================================================

	Continuous interpolation with sinusoidal acceleration and deceleration phase.
	Both the velocity and acceleration are continuous.

==============================================================================================
*/

template< class type >
class idInterpolateAccelDecelSine  {
public:
						idInterpolateAccelDecelSine();

	void				Init( const float startTime, const float accelTime, const float decelTime, const float duration, const type &startValue, const type &endValue );
	void				SetStartTime( float time ) { startTime = time; Invalidate(); }
	void				SetStartValue( const type &startValue ) { this->startValue = startValue; Invalidate(); }
	void				SetEndValue( const type &endValue ) { this->endValue = endValue; Invalidate(); }

	type				GetCurrentValue( float time ) const;
	type				GetCurrentSpeed( float time ) const;
	bool				IsDone( float time ) const { return ( time >= startTime + accelTime + linearTime + decelTime ); }

	float				GetStartTime() const { return startTime; }
	float				GetEndTime() const { return startTime + accelTime + linearTime + decelTime; }
	float				GetDuration() const { return accelTime + linearTime + decelTime; }
	float				GetAcceleration() const { return accelTime; }
	float				GetDeceleration() const { return decelTime; }
	const type &		GetStartValue() const { return startValue; }
	const type &		GetEndValue() const { return endValue; }

private:
	float				startTime;
	float				accelTime;
	float				linearTime;
	float				decelTime;
	type				startValue;
	type				endValue;
	mutable CExtrapolation<type> extrapolate;

	void				Invalidate();
	void				SetPhase( float time ) const;
};

/*
====================
idInterpolateAccelDecelSine::idInterpolateAccelDecelSine
====================
*/
template< class type >
SGF_INLINE_FORCED idInterpolateAccelDecelSine<type>::idInterpolateAccelDecelSine() {
	startTime = accelTime = linearTime = decelTime = 0;
	memset( &startValue, 0, sizeof( startValue ) );
	endValue = startValue;
}

/*
====================
idInterpolateAccelDecelSine::Init
====================
*/
template< class type >
SGF_INLINE_FORCED void idInterpolateAccelDecelSine<type>::Init( const float startTime, const float accelTime, const float decelTime, const float duration, const type &startValue, const type &endValue ) {
	type speed;

	this->startTime = startTime;
	this->accelTime = accelTime;
	this->decelTime = decelTime;
	this->startValue = startValue;
	this->endValue = endValue;

	if ( duration <= 0.0f ) {
		return;
	}

	if ( this->accelTime + this->decelTime > duration ) {
		this->accelTime = this->accelTime * duration / ( this->accelTime + this->decelTime );
		this->decelTime = duration - this->accelTime;
	}
	this->linearTime = duration - this->accelTime - this->decelTime;
	speed = ( endValue - startValue ) * ( 1000.0f / ( (float) this->linearTime + ( this->accelTime + this->decelTime ) * CMath::SQRT_1OVER2 ) );

	if ( this->accelTime ) {
		extrapolate.Init( startTime, this->accelTime, startValue, ( startValue - startValue ), speed, EXTRAPOLATION_ACCELSINE );
	} else if ( this->linearTime ) {
		extrapolate.Init( startTime, this->linearTime, startValue, ( startValue - startValue ), speed, EXTRAPOLATION_LINEAR );
	} else {
		extrapolate.Init( startTime, this->decelTime, startValue, ( startValue - startValue ), speed, EXTRAPOLATION_DECELSINE );
	}
}

/*
====================
idInterpolateAccelDecelSine::Invalidate
====================
*/
template< class type >
SGF_INLINE_FORCED void idInterpolateAccelDecelSine<type>::Invalidate() {
	extrapolate.Init( 0, 0, extrapolate.GetStartValue(), extrapolate.GetBaseSpeed(), extrapolate.GetSpeed(), EXTRAPOLATION_NONE );
}

/*
====================
idInterpolateAccelDecelSine::SetPhase
====================
*/
template< class type >
SGF_INLINE_FORCED void idInterpolateAccelDecelSine<type>::SetPhase( float time ) const {
	float deltaTime;

	deltaTime = time - startTime;
	if ( deltaTime < accelTime ) {
		if ( extrapolate.GetExtrapolationType() != EXTRAPOLATION_ACCELSINE ) {
			extrapolate.Init( startTime, accelTime, startValue, extrapolate.GetBaseSpeed(), extrapolate.GetSpeed(), EXTRAPOLATION_ACCELSINE );
		}
	} else if ( deltaTime < accelTime + linearTime ) {
		if ( extrapolate.GetExtrapolationType() != EXTRAPOLATION_LINEAR ) {
			extrapolate.Init( startTime + accelTime, linearTime, startValue + extrapolate.GetSpeed() * ( accelTime * 0.001f * CMath::SQRT_1OVER2 ), extrapolate.GetBaseSpeed(), extrapolate.GetSpeed(), EXTRAPOLATION_LINEAR );
		}
	} else {
		if ( extrapolate.GetExtrapolationType() != EXTRAPOLATION_DECELSINE ) {
			extrapolate.Init( startTime + accelTime + linearTime, decelTime, endValue - ( extrapolate.GetSpeed() * ( decelTime * 0.001f * CMath::SQRT_1OVER2 ) ), extrapolate.GetBaseSpeed(), extrapolate.GetSpeed(), EXTRAPOLATION_DECELSINE );
		}
	}
}

/*
====================
idInterpolateAccelDecelSine::GetCurrentValue
====================
*/
template< class type >
SGF_INLINE_FORCED type idInterpolateAccelDecelSine<type>::GetCurrentValue( float time ) const {
	SetPhase( time );
	return extrapolate.GetCurrentValue( time );
}

/*
====================
idInterpolateAccelDecelSine::GetCurrentSpeed
====================
*/
template< class type >
SGF_INLINE_FORCED type idInterpolateAccelDecelSine<type>::GetCurrentSpeed( float time ) const {
	SetPhase( time );
	return extrapolate.GetCurrentSpeed( time );
}
} //end SGF
#endif /* !__MATH_INTERPOLATE_H__ */
