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

#ifndef __MATH_LCP_H__
#define __MATH_LCP_H__


#include "../SGF_Config.h"
namespace SGF{
	class CMatrizXD;
	class CVectorXD;
	/*
===============================================================================

  Box Constrained Mixed Linear Complementarity Problem solver

  A is a matrix of dimension n*n and x, b, lo, hi are vectors of dimension n

  Solve: Ax = b + t, where t is a vector of dimension n, with
  complementarity condition: (x[i] - lo[i]) * (x[i] - hi[i]) * t[i] = 0
  such that for each 0 <= i < n one of the following holds:

    1. lo[i] < x[i] < hi[i], t[i] == 0
    2. x[i] == lo[i], t[i] >= 0
    3. x[i] == hi[i], t[i] <= 0

  Partly bounded or unbounded variables can have lo[i] and/or hi[i]
  set to negative/positive CMath::INFITITY respectively.

  If boxIndex != NULL and boxIndex[i] != -1 then

    lo[i] = - fabs( lo[i] * x[boxIndex[i]] )
    hi[i] = fabs( hi[i] * x[boxIndex[i]] )
	boxIndex[boxIndex[i]] must be -1
  
  Before calculating any of the bounded x[i] with boxIndex[i] != -1 the
  solver calculates all unbounded x[i] and all x[i] with boxIndex[i] == -1.

===============================================================================
*/

class CLinCP {
public:
	static CLinCP *	AllocSquare();		// A must be a square matrix
	static CLinCP *	AllocSymmetric();		// A must be a symmetric matrix

	virtual			~CLinCP();

	virtual bool	Solve( const CMatrizXD &A, CVectorXD &x, const CVectorXD &b, const CVectorXD &lo, const CVectorXD &hi, const int *boxIndex = NULL ) = 0;
	virtual void	SetMaxIterations( int max );
	virtual int		GetMaxIterations();

protected:
	int				maxIterations;
};
}
#endif /* !__MATH_LCP_H__ */
