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

#include "math/SGF_Polynomial.h"
#include "util/SGF_Util.h"
#include "math/SGF_Vector.h"
#include "math/SGF_Matriz.h"
#include "math/SGF_Angles.h"
#include "util/SGF_StringUtils.h"

//#pragma hdrstop

namespace SGF {
const float EPSILON		= 1e-6f;

/*
=============
CPolynomial::Laguer
=============
*/
int CPolynomial::Laguer( const CComplex *coef, const int degree, CComplex &x ) const {
	const int MT = 10, MAX_ITERATIONS = MT * 8;
	static const float frac[] = { 0.0f, 0.5f, 0.25f, 0.75f, 0.13f, 0.38f, 0.62f, 0.88f, 1.0f };
	int i, j;
	float abx, abp, abm, err;
	CComplex dx, cx, b, d, f, g, s, gps, gms, g2;

	for ( i = 1; i <= MAX_ITERATIONS; i++ ) {
		b = coef[degree];
		err = b.Abs();
		d.Zero();
		f.Zero();
		abx = x.Abs();
		for ( j = degree - 1; j >= 0; j-- ) {
			f = x * f + d;
			d = x * d + b;
			b = x * b + coef[j];
			err = b.Abs() + abx * err;
		}
		if ( b.Abs() < err * EPSILON ) {
			return i;
		}
		g = d / b;
		g2 = g * g;
		s = ( ( degree - 1 ) * ( degree * ( g2 - 2.0f * f / b ) - g2 ) ).Sqrt();
		gps = g + s;
		gms = g - s;
		abp = gps.Abs();
		abm = gms.Abs();
		if ( abp < abm ) {
			gps = gms;
		}
		if ( MAX( abp, abm ) > 0.0f ) {
			dx = degree / gps;
		} else {
			dx = CMath::Exp( CMath::Log( 1.0f + abx ) ) * CComplex( CMath::Cos( i ), CMath::Sin( i ) );
		}
		cx = x - dx;
		if ( x == cx ) {
			return i;
		}
		if ( i % MT == 0 ) {
			x = cx;
		} else {
			x -= frac[i/MT] * dx;
		}
	}
	return i;
}

/*
=============
CPolynomial::GetRoots
=============
*/
int CPolynomial::GetRoots( CComplex *roots ) const {
	int i, j;
	CComplex x, b, c, *coef;

	coef = (CComplex *) _allocafloat16( ( degree + 1 ) * sizeof( CComplex ) );
	for ( i = 0; i <= degree; i++ ) {
		coef[i].Set( coefficient[i], 0.0f );
	}

	for ( i = degree - 1; i >= 0; i-- ) {
		x.Zero();
		Laguer( coef, i + 1, x );
		if ( CMath::Fabs( x.i ) < 2.0f * EPSILON * CMath::Fabs( x.r ) ) {
			x.i = 0.0f;
		}
		roots[i] = x;
		b = coef[i+1];
		for ( j = i; j >= 0; j-- ) {
			c = coef[j];
			coef[j] = b;
			b = x * b + c;
		}
	}

	for ( i = 0; i <= degree; i++ ) {
		coef[i].Set( coefficient[i], 0.0f );
	}
	for ( i = 0; i < degree; i++ ) {
		Laguer( coef, degree, roots[i] );
	}

	for ( i = 1; i < degree; i++ ) {
		x = roots[i];
		for ( j = i - 1; j >= 0; j-- ) {
			if ( roots[j].r <= x.r ) {
				break;
			}
			roots[j+1] = roots[j];
		}
		roots[j+1] = x;
	}

	return degree;
}

/*
=============
CPolynomial::GetRoots
=============
*/
int CPolynomial::GetRoots( float *roots ) const {
	int i, num;
	CComplex *complexRoots;

	switch( degree ) {
		case 0: return 0;
		case 1: return GetRoots1( coefficient[1], coefficient[0], roots );
		case 2: return GetRoots2( coefficient[2], coefficient[1], coefficient[0], roots );
		case 3: return GetRoots3( coefficient[3], coefficient[2], coefficient[1], coefficient[0], roots );
		case 4: return GetRoots4( coefficient[4], coefficient[3], coefficient[2], coefficient[1], coefficient[0], roots );
	}

	// The Abel-Ruffini theorem states that there is no general solution
	// in radicals to polynomial equations of degree five or higher.
	// A polynomial equation can be solved by radicals if and only if
	// its Galois group is a solvable group.

	complexRoots = (CComplex *) _allocafloat16( degree * sizeof( CComplex ) );

	GetRoots( complexRoots );

	for ( num = i = 0; i < degree; i++ ) {
		if ( complexRoots[i].i == 0.0f ) {
			roots[i] = complexRoots[i].r;
			num++;
		}
	}
	return num;
}

/*
=============
CPolynomial::ToString
=============
*/
const char *CPolynomial::ToString( int precision ) const {
	return CMyString::FloatArrayToString( ToFloatPtr(), GetDimension(), precision );
}

/*
=============
CPolynomial::Test
=============
*/
void CPolynomial::Test() {
	int i, num;
	float roots[4], value;
	CComplex complexRoots[4], complexValue;
	CPolynomial p;

	p = CPolynomial( -5.0f, 4.0f );
	num = p.GetRoots( roots );
	for ( i = 0; i < num; i++ ) {
		value = p.GetValue( roots[i] );
		assert( CMath::Fabs( value ) < 1e-4f );
	}

	p = CPolynomial( -5.0f, 4.0f, 3.0f );
	num = p.GetRoots( roots );
	for ( i = 0; i < num; i++ ) {
		value = p.GetValue( roots[i] );
		assert( CMath::Fabs( value ) < 1e-4f );
	}

	p = CPolynomial( 1.0f, 4.0f, 3.0f, -2.0f );
	num = p.GetRoots( roots );
	for ( i = 0; i < num; i++ ) {
		value = p.GetValue( roots[i] );
		assert( CMath::Fabs( value ) < 1e-4f );
	}

	p = CPolynomial( 5.0f, 4.0f, 3.0f, -2.0f );
	num = p.GetRoots( roots );
	for ( i = 0; i < num; i++ ) {
		value = p.GetValue( roots[i] );
		assert( CMath::Fabs( value ) < 1e-4f );
	}

	p = CPolynomial( -5.0f, 4.0f, 3.0f, 2.0f, 1.0f );
	num = p.GetRoots( roots );
	for ( i = 0; i < num; i++ ) {
		value = p.GetValue( roots[i] );
		assert( CMath::Fabs( value ) < 1e-4f );
	}

	p = CPolynomial( 1.0f, 4.0f, 3.0f, -2.0f );
	num = p.GetRoots( complexRoots );
	for ( i = 0; i < num; i++ ) {
		complexValue = p.GetValue( complexRoots[i] );
		assert( CMath::Fabs( complexValue.r ) < 1e-4f && CMath::Fabs( complexValue.i ) < 1e-4f );
	}

	p = CPolynomial( 5.0f, 4.0f, 3.0f, -2.0f );
	num = p.GetRoots( complexRoots );
	for ( i = 0; i < num; i++ ) {
		complexValue = p.GetValue( complexRoots[i] );
		assert( CMath::Fabs( complexValue.r ) < 1e-4f && CMath::Fabs( complexValue.i ) < 1e-4f );
	}
}

} //end SGF