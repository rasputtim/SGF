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

#ifndef __MATH_ODE_H__
#define __MATH_ODE_H__
#include "../SGF_Config.h"
namespace SGF{
/*
===============================================================================

	Numerical solvers for ordinary differential equations.

===============================================================================
*/


//===============================================================
//
//	CODifEq
//
//===============================================================

typedef void (*deriveFunction_t)( const float t, const void *userData, const float *state, float *derivatives );

class CODifEq {

public:
	virtual				~CODifEq() {}

	virtual float		Evaluate( const float *state, float *newState, float t0, float t1 ) = 0;

protected:
	int					dimension;		// dimension in floats allocated for
	deriveFunction_t	derive;			// derive function
	const void *		userData;		// client data
};

//===============================================================
//
//	CODifEq_Euler
//
//===============================================================

class CODifEq_Euler : public CODifEq {

public:
						CODifEq_Euler( const int dim, const deriveFunction_t dr, const void *ud );
	virtual				~CODifEq_Euler();

	virtual float		Evaluate( const float *state, float *newState, float t0, float t1 );

protected:
	float *				derivatives;	// space to store derivatives
};

//===============================================================
//
//	CODifEq_Midpoint
//
//===============================================================

class CODifEq_Midpoint : public CODifEq {

public:
						CODifEq_Midpoint( const int dim, const deriveFunction_t dr, const void *ud );
	virtual				~CODifEq_Midpoint();

	virtual float		Evaluate( const float *state, float *newState, float t0, float t1 );

protected:
	float *				tmpState;
	float *				derivatives;	// space to store derivatives
};

//===============================================================
//
//	CODifEq_RK4
//
//===============================================================

class CODifEq_RK4 : public CODifEq {

public:
						CODifEq_RK4( const int dim, const deriveFunction_t dr, const void *ud );
	virtual				~CODifEq_RK4();

	virtual float		Evaluate( const float *state, float *newState, float t0, float t1 );

protected:
	float *				tmpState;
	float *				d1;				// derivatives
	float *				d2;
	float *				d3;
	float *				d4;
};

//===============================================================
//
//	CODifEq_RK4Adaptive
//
//===============================================================

class CODifEq_RK4Adaptive : public CODifEq {

public:
						CODifEq_RK4Adaptive( const int dim, const deriveFunction_t dr, const void *ud );
	virtual				~CODifEq_RK4Adaptive();

	virtual float		Evaluate( const float *state, float *newState, float t0, float t1 );
	void				SetMaxError( const float err );

protected:
	float				maxError;		// maximum allowed error
	float *				tmpState;
	float *				d1;				// derivatives
	float *				d1half;
	float *				d2;
	float *				d3;
	float *				d4;
};
} //end SGF
#endif /* !__MATH_ODE_H__ */
