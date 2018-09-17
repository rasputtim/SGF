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

#include "math/SGF_Odife.h"
#include "math/SGF_Vector.h"
#include "math/SGF_Matriz.h"
#include "math/SGF_Angles.h"
#include "util/SGF_StringUtils.h"

//#pragma hdrstop

namespace SGF{
//===============================================================
//
//	CODifEq_Euler
//
//===============================================================

/*
=============
CODifEq_Euler::CODifEq_Euler
=============
*/
CODifEq_Euler::CODifEq_Euler( const int dim, deriveFunction_t dr, const void *ud ) {
	dimension = dim;
	derivatives = new float[dim];
	derive = dr;
	userData = ud;
}

/*
=============
CODifEq_Euler::~CODifEq_Euler
=============
*/
CODifEq_Euler::~CODifEq_Euler() {
	delete[] derivatives;
}

/*
=============
CODifEq_Euler::Evaluate
=============
*/
float CODifEq_Euler::Evaluate( const float *state, float *newState, float t0, float t1 ) {
	float delta;
	int i;

	derive( t0, userData, state, derivatives );
	delta = t1 - t0;
	for ( i = 0; i < dimension; i++ ) {
		newState[i] = state[i] + delta * derivatives[i];
	}
	return delta;
}

//===============================================================
//
//	CODifEq_Midpoint
//
//===============================================================

/*
=============
CODifEq_Midpoint::CODifEq_Midpoint
=============
*/
CODifEq_Midpoint::CODifEq_Midpoint( const int dim, deriveFunction_t dr, const void *ud ) {
	dimension = dim;
	tmpState = new float[dim];
	derivatives = new float[dim];
	derive = dr;
	userData = ud;
}

/*
=============
CODifEq_Midpoint::~CODifEq_Midpoint
=============
*/
CODifEq_Midpoint::~CODifEq_Midpoint() {
	delete tmpState;
	delete derivatives;
}

/*
=============
CODifEq_Midpoint::~Evaluate
=============
*/
float CODifEq_Midpoint::Evaluate( const float *state, float *newState, float t0, float t1 ) {
	double delta, halfDelta;
    int i;

	delta = t1 - t0;
	halfDelta = delta * 0.5;
    // first step
	derive( t0, userData, state, derivatives );
	for ( i = 0; i < dimension; i++ ) {
		tmpState[i] = state[i] + halfDelta * derivatives[i];
	}
    // second step
	derive( t0 + halfDelta, userData, tmpState, derivatives );

	for ( i = 0; i < dimension; i++ ) {
		newState[i] = state[i] + delta * derivatives[i];
	}
	return delta;
}

//===============================================================
//
//	CODifEq_RK4
//
//===============================================================

/*
=============
CODifEq_RK4::CODifEq_RK4
=============
*/
CODifEq_RK4::CODifEq_RK4( const int dim, deriveFunction_t dr, const void *ud ) {
	dimension = dim;
	derive = dr;
	userData = ud;
	tmpState = new float[dim];
	d1 = new float[dim];
	d2 = new float[dim];
	d3 = new float[dim];
	d4 = new float[dim];
}

/*
=============
CODifEq_RK4::~CODifEq_RK4
=============
*/
CODifEq_RK4::~CODifEq_RK4() {
	delete tmpState;
	delete d1;
	delete d2;
	delete d3;
	delete d4;
}

/*
=============
CODifEq_RK4::Evaluate
=============
*/
float CODifEq_RK4::Evaluate( const float *state, float *newState, float t0, float t1 ) {
	double delta, halfDelta, sixthDelta;
	int i;

	delta = t1 - t0;
	halfDelta = delta * 0.5;
	// first step
	derive( t0, userData, state, d1 );
	for ( i = 0; i < dimension; i++ ) {
		tmpState[i] = state[i] + halfDelta * d1[i];
	}
	// second step
	derive( t0 + halfDelta, userData, tmpState, d2 );
	for ( i = 0; i < dimension; i++ ) {
		tmpState[i] = state[i] + halfDelta * d2[i];
	}
	// third step
	derive( t0 + halfDelta, userData, tmpState, d3 );
	for ( i = 0; i < dimension; i++ ) {
		tmpState[i] = state[i] + delta * d3[i];
	}
	// fourth step
	derive( t0 + delta, userData, tmpState, d4 );

	sixthDelta = delta * (1.0/6.0);
	for ( i = 0; i < dimension; i++ ) {
		newState[i] = state[i] + sixthDelta * (d1[i] + 2.0 * (d2[i] + d3[i]) + d4[i]);
	}
	return delta;
}

//===============================================================
//
//	CODifEq_RK4Adaptive
//
//===============================================================

/*
=============
CODifEq_RK4Adaptive::CODifEq_RK4Adaptive
=============
*/
CODifEq_RK4Adaptive::CODifEq_RK4Adaptive( const int dim, deriveFunction_t dr, const void *ud ) {
	dimension = dim;
	derive = dr;
	userData = ud;
	maxError = 0.01f;
	tmpState = new float[dim];
	d1 = new float[dim];
	d1half = new float [dim];
	d2 = new float[dim];
	d3 = new float[dim];
	d4 = new float[dim];
}

/*
=============
CODifEq_RK4Adaptive::~CODifEq_RK4Adaptive
=============
*/
CODifEq_RK4Adaptive::~CODifEq_RK4Adaptive() {
	delete tmpState;
	delete d1;
	delete d1half;
	delete d2;
	delete d3;
	delete d4;
}

/*
=============
CODifEq_RK4Adaptive::SetMaxError
=============
*/
void CODifEq_RK4Adaptive::SetMaxError( const float err ) {
	if ( err > 0.0f ) {
		maxError = err;
	}
}

/*
=============
CODifEq_RK4Adaptive::Evaluate
=============
*/
float CODifEq_RK4Adaptive::Evaluate( const float *state, float *newState, float t0, float t1 ) {
	double delta, halfDelta, fourthDelta, sixthDelta;
	double error, max;
	int i, n;

	delta = t1 - t0;

	for ( n = 0; n < 4; n++ ) {

		halfDelta = delta * 0.5;
		fourthDelta = delta * 0.25;

		// first step of first half delta
		derive( t0, userData, state, d1 );
		for ( i = 0; i < dimension; i++ ) {
			tmpState[i] = state[i] + fourthDelta * d1[i];
		}
		// second step of first half delta
		derive( t0 + fourthDelta, userData, tmpState, d2 );
		for ( i = 0; i < dimension; i++ ) {
			tmpState[i] = state[i] + fourthDelta * d2[i];
		}
		// third step of first half delta
		derive( t0 + fourthDelta, userData, tmpState, d3 );
		for ( i = 0; i < dimension; i++ ) {
			tmpState[i] = state[i] + halfDelta * d3[i];
		}
		// fourth step of first half delta
		derive( t0 + halfDelta, userData, tmpState, d4 );

		sixthDelta = halfDelta * (1.0/6.0);
		for ( i = 0; i < dimension; i++ ) {
			tmpState[i] = state[i] + sixthDelta * (d1[i] + 2.0 * (d2[i] + d3[i]) + d4[i]);
		}

		// first step of second half delta
		derive( t0 + halfDelta, userData, tmpState, d1half );
		for ( i = 0; i < dimension; i++ ) {
			tmpState[i] = state[i] + fourthDelta * d1half[i];
		}
		// second step of second half delta
		derive( t0 + halfDelta + fourthDelta, userData, tmpState, d2 );
		for ( i = 0; i < dimension; i++ ) {
			tmpState[i] = state[i] + fourthDelta * d2[i];
		}
		// third step of second half delta
		derive( t0 + halfDelta + fourthDelta, userData, tmpState, d3 );
		for ( i = 0; i < dimension; i++ ) {
			tmpState[i] = state[i] + halfDelta * d3[i];
		}
		// fourth step of second half delta
		derive( t0 + delta, userData, tmpState, d4 );

		sixthDelta = halfDelta * (1.0/6.0);
		for ( i = 0; i < dimension; i++ ) {
			newState[i] = state[i] + sixthDelta * (d1[i] + 2.0 * (d2[i] + d3[i]) + d4[i]);
		}

		// first step of full delta
		for ( i = 0; i < dimension; i++ ) {
			tmpState[i] = state[i] + halfDelta * d1[i];
		}
		// second step of full delta
		derive( t0 + halfDelta, userData, tmpState, d2 );
		for ( i = 0; i < dimension; i++ ) {
			tmpState[i] = state[i] + halfDelta * d2[i];
		}
		// third step of full delta
		derive( t0 + halfDelta, userData, tmpState, d3 );
		for ( i = 0; i < dimension; i++ ) {
			tmpState[i] = state[i] + delta * d3[i];
		}
		// fourth step of full delta
		derive( t0 + delta, userData, tmpState, d4 );

		sixthDelta = delta * (1.0/6.0);
		for ( i = 0; i < dimension; i++ ) {
			tmpState[i] = state[i] + sixthDelta * (d1[i] + 2.0 * (d2[i] + d3[i]) + d4[i]);
		}

		// get max estimated error
        max = 0.0;
		for ( i = 0; i < dimension; i++ ) {
			error = CMath::Fabs( (newState[i] - tmpState[i]) / (delta * d1[i] + 1e-10) );
			if ( error > max ) {
				max = error;
			}
        }
		error = max / maxError;

        if ( error <= 1.0f ) {
			return delta * 4.0;
		}
		if ( delta <= 1e-7 ) {
			return delta;
		}
		delta *= 0.25;
	}
	return delta;
}

} //end SGF