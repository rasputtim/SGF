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

#ifndef __DRAWVERT_H__
#define __DRAWVERT_H__
#include "../SGF_Config.h"
#include "../math/SGF_Vector.h"
#include "../math/SGF_Simd.h"
namespace SGF{
	
/*
===============================================================================

	Draw Vertex.

===============================================================================
*/

class CDrawVertice {
public:
	CVector3D			xyz;
	CVector2D			st;
	CVector3D			normal;
	CVector3D			tangents[2];
	SGF_Byte			color[4];
#if 0 // was MACOS_X see comments concerning DRAWVERT_PADDED in Simd_Altivec.h 
	float			padding;
#endif
	float			operator[]( const int index ) const;
	float &			operator[]( const int index );

	void			Clear( void );

	void			Lerp( const CDrawVertice &a, const CDrawVertice &b, const float f );
	void			LerpAll( const CDrawVertice &a, const CDrawVertice &b, const float f );

	void			Normalize( void );

	void			SetColor( SGF_Dword color );
	SGF_Dword			GetColor( void ) const;
};

SGF_INLINE_FORCED float CDrawVertice::operator[]( const int index ) const {
	assert( index >= 0 && index < 5 );
	return ((float *)(&xyz))[index];
}
SGF_INLINE_FORCED float	&CDrawVertice::operator[]( const int index ) {
	assert( index >= 0 && index < 5 );
	return ((float *)(&xyz))[index];
}

SGF_INLINE_FORCED void CDrawVertice::Clear( void ) {
	xyz.Zero();
	st.Zero();
	normal.Zero();
	tangents[0].Zero();
	tangents[1].Zero();
	color[0] = color[1] = color[2] = color[3] = 0;
}

SGF_INLINE_FORCED void CDrawVertice::Lerp( const CDrawVertice &a, const CDrawVertice &b, const float f ) {
	xyz = a.xyz + f * ( b.xyz - a.xyz );
	st = a.st + f * ( b.st - a.st );
}

SGF_INLINE_FORCED void CDrawVertice::LerpAll( const CDrawVertice &a, const CDrawVertice &b, const float f ) {
	xyz = a.xyz + f * ( b.xyz - a.xyz );
	st = a.st + f * ( b.st - a.st );
	normal = a.normal + f * ( b.normal - a.normal );
	tangents[0] = a.tangents[0] + f * ( b.tangents[0] - a.tangents[0] );
	tangents[1] = a.tangents[1] + f * ( b.tangents[1] - a.tangents[1] );
	color[0] = (SGF_Byte)( a.color[0] + f * ( b.color[0] - a.color[0] ) );
	color[1] = (SGF_Byte)( a.color[1] + f * ( b.color[1] - a.color[1] ) );
	color[2] = (SGF_Byte)( a.color[2] + f * ( b.color[2] - a.color[2] ) );
	color[3] = (SGF_Byte)( a.color[3] + f * ( b.color[3] - a.color[3] ) );
}

SGF_INLINE_FORCED void CDrawVertice::SetColor( SGF_Dword color ) {
	*reinterpret_cast<SGF_Dword *>(this->color) = color;
}

SGF_INLINE_FORCED SGF_Dword CDrawVertice::GetColor( void ) const {
	return *reinterpret_cast<const SGF_Dword *>(this->color);
}

} //end SGF
#endif /* !__DRAWVERT_H__ */
