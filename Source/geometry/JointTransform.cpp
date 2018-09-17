/*
  SGF - Super Game Fabric  Super Game Fabric
  Copyright (C) 2010-2011 Rasputtim <raputtim@hotmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

  */

#include "geometry/SGF_JointTransform.h"

//#pragma hdrstop

namespace SGF{
/*
=============
CJointMatriz::ToJointQuat
=============
*/
CJointQuaternion CJointMatriz::ToJointQuat( void ) const {
	CJointQuaternion	jq;
	float		trace;
	float		s;
	float		t;
	int     	i;
	int			j;
	int			k;

	static int 	next[3] = { 1, 2, 0 };

	trace = mat[0 * 4 + 0] + mat[1 * 4 + 1] + mat[2 * 4 + 2];

	if ( trace > 0.0f ) {

		t = trace + 1.0f;
		s = CMath::InvSqrt( t ) * 0.5f;

		jq.q[3] = s * t;
		jq.q[0] = ( mat[1 * 4 + 2] - mat[2 * 4 + 1] ) * s;
		jq.q[1] = ( mat[2 * 4 + 0] - mat[0 * 4 + 2] ) * s;
		jq.q[2] = ( mat[0 * 4 + 1] - mat[1 * 4 + 0] ) * s;

	} else {

		i = 0;
		if ( mat[1 * 4 + 1] > mat[0 * 4 + 0] ) {
			i = 1;
		}
		if ( mat[2 * 4 + 2] > mat[i * 4 + i] ) {
			i = 2;
		}
		j = next[i];
		k = next[j];

		t = ( mat[i * 4 + i] - ( mat[j * 4 + j] + mat[k * 4 + k] ) ) + 1.0f;
		s = CMath::InvSqrt( t ) * 0.5f;

		jq.q[i] = s * t;
		jq.q[3] = ( mat[j * 4 + k] - mat[k * 4 + j] ) * s;
		jq.q[j] = ( mat[i * 4 + j] + mat[j * 4 + i] ) * s;
		jq.q[k] = ( mat[i * 4 + k] + mat[k * 4 + i] ) * s;
	}

	jq.t[0] = mat[0 * 4 + 3];
	jq.t[1] = mat[1 * 4 + 3];
	jq.t[2] = mat[2 * 4 + 3];

	return jq;
}

}//end SGF