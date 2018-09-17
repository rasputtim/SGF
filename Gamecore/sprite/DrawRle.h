// At this point the following methods should be defined:

// METHODNAME: The name of the drawing method
// METHODNAME_FLIPT: The name of the flipped drawing method
// PIXEL_PTR: type of pointer to the target surface pixels
// PUT_PIXEL(p,c): Draw pixel of color c to pixel ptr type p
// PITCH: This added to PIXEL_PTR type will result in the next scanline


void METHODNAME_FLIP(SDL_Surface* dst, RLE_SPRITE* src, int dx, int dy )
{
#define RLE_PTR					signed char*
#define RLE_IS_EOL(c)			((c) == 0)
//#define PIXEL_PTR				unsigned char*
#define OFFSET_PIXEL_PTR(p,x)	((PIXEL_PTR) (p) + (x))
#define INC_PIXEL_PTR(p)		((p)++)
#define DEC_PIXEL_PTR(p)		((p)--)
//#define PUT_PIXEL(p,c)			(*((unsigned char *)(p)) = (c))

	int x, y, w, h;		// width and height of visible area
	int dxbeg, dybeg;	// beginning in destination
	int sxbeg, sybeg;	// beginning in source
	RLE_PTR s;

	
	// Clip to dst->clip_rect
	int dst_cl = dst->clip_rect.x;
	int dst_cr = dst->clip_rect.w + dst_cl - 1;
	int dst_ct = dst->clip_rect.y;
	int dst_cb = dst->clip_rect.h + dst_ct;

//	if (dst->clip)
	if (1)
	{
		int tmp;

		dxbeg = dx;
		if ( dst_cl > dx ) dxbeg = dst_cl;

		tmp = dx + src->w - dst_cr;
		sxbeg = ((tmp < 0) ? 0 : tmp);

		tmp = dx + src->w;
		if (tmp > dst_cr ) tmp = dst_cr;
		w = tmp - dxbeg;
		if (w <= 0)
			return;
	
		tmp = dst_ct - dy;
		sybeg = ((tmp < 0) ? 0 : tmp);
		dybeg = sybeg + dy;

		tmp = dst_cb - dy;
		h = ((tmp > src->h) ? src->h : tmp) - sybeg;
		if (h <= 0)
			return;
	}
	else {
		w = src->w;
		h = src->h;
		sxbeg = 0;
		sybeg = 0;
		dxbeg = dx;
		dybeg = dy;
	}

	s = (RLE_PTR) (src->dat);
	dxbeg += w;

	// Clip top.
	for (y = sybeg - 1; y >= 0; y--) 
	{
		long c = *s++;

		while (!RLE_IS_EOL(c)) 
		{
			if (c > 0)
				s += c;
			c = *s++;
		}
	}

	//@@@ bmp_select(dst);

	/* Visible part.  */
	for (y = 0; y < h; y++) 
	{
		//@@@ PIXEL_PTR d = OFFSET_PIXEL_PTR(bmp_write_line(dst, dybeg + y), dxbeg);
		PIXEL_PTR d = (PIXEL_PTR) dst->pixels;
		d += (dybeg+y)*PITCH; // 24bpp ->(y * dst->pitch)
		if (dst->format->BitsPerPixel != 24)
			d = OFFSET_PIXEL_PTR( d, dxbeg );
		else	{	

			//d = OFFSET_PIXEL_PTR( d, (x * sizeof(Uint8) * 3));
			d += (dybeg+y * dst->pitch) + (dxbeg * sizeof(Uint8) * 3);
		}	
	long c = *s++;

		// Clip left.
		for (x = sxbeg; x > 0; ) 
		{
			if (RLE_IS_EOL(c))
				goto next_line;
			else if (c > 0) 
			{
				// Run of solid pixels.
				if ((x - c) >= 0) 
				{
					// Fully clipped.
					x -= c;
					s += c;
				}
				else 
				{
					// Visible on the right.
					c -= x;
					s += x;
					break;
				}
			}
			else 
			{
				// Run of transparent pixels.
				if ((x + c) >= 0) {
					// Fully clipped.
					x += c;
				}
				else {
					// Visible on the right.
					c += x;
					break;
				}
			}

			c = *s++;
		}

		/* Visible part.  */
		for (x = w; x > 0; ) 
		{
			if (RLE_IS_EOL(c))
				goto next_line;
			else if (c > 0) 
			{
				/* Run of solid pixels.  */
				if ((x - c) >= 0) 
				{
					/* Fully visible.  */
					x -= c;
					for (c--; c >= 0; s++, DEC_PIXEL_PTR(d), c--) 
					{
						unsigned long col = *s;
						PUT_PIXEL(d, col);
					}
				}
				else 
				{
					/* Clipped on the right.  */
					c -= x;
					for (x--; x >= 0; s++, DEC_PIXEL_PTR(d), x--) 
					{
						unsigned long col = *s;
						PUT_PIXEL(d, col);
					}
					break;
				}
			}
			else 
			{
				/* Run of transparent pixels.  */
				x += c;
				d = OFFSET_PIXEL_PTR(d, c);
			}

			c = *s++;
		}

		/* Clip right.  */
		while (!RLE_IS_EOL(c)) 
		{
			if (c > 0)
				s += c;
			c = *s++;
		}

		next_line: ;
	}

   //@@@bmp_unwrite_line(dst);
}

void METHODNAME( SDL_Surface* dst , RLE_SPRITE* src, int dx, int dy )
{
#define RLE_PTR					signed char*
#define RLE_IS_EOL(c)			((c) == 0)
//#define PIXEL_PTR				unsigned char*
#define OFFSET_PIXEL_PTR(p,x)	((PIXEL_PTR) (p) + (x))
#define INC_PIXEL_PTR(p)		((p)++)
#define DEC_PIXEL_PTR(p)		((p)--)
//#define PUT_PIXEL(p,c)			(*((unsigned char *)(p)) = (c))
//#define PUT_PIXEL(p,c)         bmp_write8((unsigned long) (p), (c))

	int x, y, w, h;		// width and height of visible area
	int dxbeg, dybeg;	// beginning in destination
	int sxbeg, sybeg;	// beginning in source
	RLE_PTR s;

	//SDL_Surface* dst = gamescreen;
	// Clip to dst->clip_rect
	int dst_cl = dst->clip_rect.x;
	int dst_cr = dst->clip_rect.w + dst_cl;
	int dst_ct = dst->clip_rect.y;
	int dst_cb = dst->clip_rect.h + dst_ct;

// if (dst->clip)
	if (1)
	{
		int tmp;

		tmp = dst_cl - dx;
		sxbeg = ((tmp < 0) ? 0 : tmp);
		dxbeg = sxbeg + dx;

		tmp = dst_cr - dx;
		w = ((tmp > src->w) ? src->w : tmp) - sxbeg;
		if ( w<=0 ) return;

		tmp = dst_ct - dy;
		sybeg = ((tmp < 0) ? 0 : tmp);
		dybeg = sybeg + dy;

		tmp = dst_cb - dy;
		h = ((tmp > src->h) ? src->h : tmp) - sybeg;
		if ( h<=0 ) return;
	}
	else 
	{
		w = src->w;
		h = src->h;
		sxbeg = 0;
		sybeg = 0;
		dxbeg = dx;
		dybeg = dy;
	}

	s = (RLE_PTR) (src->dat);

	/* Clip top.  */
	for (y = sybeg - 1; y >= 0; y--) 
	{
		long c = *s++;

		while (!RLE_IS_EOL(c)) 
		{
			if (c > 0)
				s += c;
			c = *s++;
		}
	}

	//@@@ bmp_select(dst);

	/* Visible part.  */
	for (y = 0; y < h; y++) 
	{
		//@@@ PIXEL_PTR d = OFFSET_PIXEL_PTR(bmp_write_line(dst, dybeg + y), dxbeg);
		PIXEL_PTR d = (PIXEL_PTR) dst->pixels;
		d += (dybeg+y)*PITCH;
		d = OFFSET_PIXEL_PTR( d, dxbeg );
		long c = *s++;

		/* Clip left.  */
		for (x = sxbeg; x > 0; ) {
			if (RLE_IS_EOL(c))
				goto next_line;
			else if (c > 0) {
				/* Run of solid pixels.  */
				if ((x - c) >= 0) {
					/* Fully clipped.  */
					x -= c;
					s += c;
				}
				else {
					/* Visible on the right.  */
					c -= x;
					s += x;
					break;
				}
			}
			else {
				/* Run of transparent pixels.  */
				if ((x + c) >= 0) {
					/* Fully clipped.  */
					x += c;
				}
				else {
					/* Visible on the right.  */
					c += x;
					break;
				}
			}

			c = *s++;
		}

		/* Visible part.  */
		for (x = w; x > 0; ) {
			if (RLE_IS_EOL(c))
				goto next_line;
			else if (c > 0) {
				/* Run of solid pixels.  */
				if ((x - c) >= 0) {
					/* Fully visible.  */
					x -= c;
					for (c--; c >= 0; s++, INC_PIXEL_PTR(d), c--) {
						unsigned long col = (unsigned char) (*s);
						PUT_PIXEL(d, col);
					}
				}
				else {
					/* Clipped on the right.  */
					c -= x;
					for (x--; x >= 0; s++, INC_PIXEL_PTR(d), x--) {
						unsigned long col = *s;
						PUT_PIXEL(d, col);
					}
					break;
				}
			}
			else {
				/* Run of transparent pixels.  */
				x += c;
				d = OFFSET_PIXEL_PTR(d, -c);
			}

			c = *s++;
		}

		/* Clip right.  */
		while (!RLE_IS_EOL(c)) {
			if (c > 0)
				s += c;
			c = *s++;
		}

next_line: ;
	}

   //@@@bmp_unwrite_line(dst);
}
//========24 bpp methods==================
#if  0
static inline Uint8* computeOffset(SDL_Surface * surface, int x, int y){
    int bpp = surface->format->BytesPerPixel;
    return ((Uint8*)surface->pixels) + (y * surface->pitch) + x * bpp;
}

void draw_rle_sprite_v_flip24(SDL_Surface* dst, RLE_SPRITE* src, int dx, int dy )
{
#define RLE_PTR					signed char*
#define RLE_IS_EOL(c)			((c) == 0)
//#define PIXEL_PTR				unsigned char*
#define OFFSET_PIXEL_PTR(p,x)	((PIXEL_PTR) (p) + (x))
#define INC_PIXEL_PTR(p)		((p)++)
#define DEC_PIXEL_PTR(p)		((p)--)
//#define PUT_PIXEL(p,c)			(*((unsigned char *)(p)) = (c))

	int x, y, w, h;		// width and height of visible area
	int dxbeg, dybeg;	// beginning in destination
	int sxbeg, sybeg;	// beginning in source
	RLE_PTR s;

	
	// Clip to dst->clip_rect
	int dst_cl = dst->clip_rect.x;
	int dst_cr = dst->clip_rect.w + dst_cl - 1;
	int dst_ct = dst->clip_rect.y;
	int dst_cb = dst->clip_rect.h + dst_ct;

//	if (dst->clip)
	if (1)
	{
		int tmp;

		dxbeg = dx;
		if ( dst_cl > dx ) dxbeg = dst_cl;

		tmp = dx + src->w - dst_cr;
		sxbeg = ((tmp < 0) ? 0 : tmp);

		tmp = dx + src->w;
		if (tmp > dst_cr ) tmp = dst_cr;
		w = tmp - dxbeg;
		if (w <= 0)
			return;
	
		tmp = dst_ct - dy;
		sybeg = ((tmp < 0) ? 0 : tmp);
		dybeg = sybeg + dy;

		tmp = dst_cb - dy;
		h = ((tmp > src->h) ? src->h : tmp) - sybeg;
		if (h <= 0)
			return;
	}
	else {
		w = src->w;
		h = src->h;
		sxbeg = 0;
		sybeg = 0;
		dxbeg = dx;
		dybeg = dy;
	}

	s = (RLE_PTR) (src->dat);
	dxbeg += w;

	// Clip top.
	for (y = sybeg - 1; y >= 0; y--) 
	{
		long c = *s++;

		while (!RLE_IS_EOL(c)) 
		{
			if (c > 0)
				s += c;
			c = *s++;
		}
	}

	//@@@ bmp_select(dst);

	/* Visible part.  */
	for (y = 0; y < h; y++) 
	{
		//@@@ PIXEL_PTR d = OFFSET_PIXEL_PTR(bmp_write_line(dst, dybeg + y), dxbeg);
		PIXEL_PTR d = (PIXEL_PTR) dst->pixels;
		d += (dybeg+y)*PITCH; // 24bpp ->(y * dst->pitch)
		if (dst->format->BitsPerPixel != 24)
			d = OFFSET_PIXEL_PTR( d, dxbeg );
		else	{	

			//d = OFFSET_PIXEL_PTR( d, (x * sizeof(Uint8) * 3));
			d += (dybeg+y * dst->pitch) + (dxbeg * sizeof(Uint8) * 3);
		}	
	long c = *s++;

		// Clip left.
		for (x = sxbeg; x > 0; ) 
		{
			if (RLE_IS_EOL(c))
				goto next_line;
			else if (c > 0) 
			{
				// Run of solid pixels.
				if ((x - c) >= 0) 
				{
					// Fully clipped.
					x -= c;
					s += c;
				}
				else 
				{
					// Visible on the right.
					c -= x;
					s += x;
					break;
				}
			}
			else 
			{
				// Run of transparent pixels.
				if ((x + c) >= 0) {
					// Fully clipped.
					x += c;
				}
				else {
					// Visible on the right.
					c += x;
					break;
				}
			}

			c = *s++;
		}

		/* Visible part.  */
		for (x = w; x > 0; ) 
		{
			if (RLE_IS_EOL(c))
				goto next_line;
			else if (c > 0) 
			{
				/* Run of solid pixels.  */
				if ((x - c) >= 0) 
				{
					/* Fully visible.  */
					x -= c;
					for (c--; c >= 0; s++, DEC_PIXEL_PTR(d), c--) 
					{
						unsigned long col = *s;
						PUT_PIXEL(d, col);
					}
				}
				else 
				{
					/* Clipped on the right.  */
					c -= x;
					for (x--; x >= 0; s++, DEC_PIXEL_PTR(d), x--) 
					{
						unsigned long col = *s;
						PUT_PIXEL(d, col);
					}
					break;
				}
			}
			else 
			{
				/* Run of transparent pixels.  */
				x += c;
				d = OFFSET_PIXEL_PTR(d, c);
			}

			c = *s++;
		}

		/* Clip right.  */
		while (!RLE_IS_EOL(c)) 
		{
			if (c > 0)
				s += c;
			c = *s++;
		}

		next_line: ;
	}

   //@@@bmp_unwrite_line(dst);
}

void draw_rle_sprite24( SDL_Surface* dst , RLE_SPRITE* src, int dx, int dy )
{
#define RLE_PTR					signed char*
#define RLE_IS_EOL(c)			((c) == 0)
//#define PIXEL_PTR				unsigned char*
#define OFFSET_PIXEL_PTR(p,x)	((PIXEL_PTR) (p) + (x))
#define INC_PIXEL_PTR(p)		((p)++)
#define DEC_PIXEL_PTR(p)		((p)--)
//#define PUT_PIXEL(p,c)			(*((unsigned char *)(p)) = (c))
//#define PUT_PIXEL(p,c)         bmp_write8((unsigned long) (p), (c))

	int x, y, w, h;		// width and height of visible area
	int dxbeg, dybeg;	// beginning in destination
	int sxbeg, sybeg;	// beginning in source
	RLE_PTR s;

	//SDL_Surface* dst = gamescreen;
	// Clip to dst->clip_rect
	int dst_cl = dst->clip_rect.x;
	int dst_cr = dst->clip_rect.w + dst_cl;
	int dst_ct = dst->clip_rect.y;
	int dst_cb = dst->clip_rect.h + dst_ct;

// if (dst->clip)
	if (1)
	{
		int tmp;

		tmp = dst_cl - dx;
		sxbeg = ((tmp < 0) ? 0 : tmp);
		dxbeg = sxbeg + dx;

		tmp = dst_cr - dx;
		w = ((tmp > src->w) ? src->w : tmp) - sxbeg;
		if ( w<=0 ) return;

		tmp = dst_ct - dy;
		sybeg = ((tmp < 0) ? 0 : tmp);
		dybeg = sybeg + dy;

		tmp = dst_cb - dy;
		h = ((tmp > src->h) ? src->h : tmp) - sybeg;
		if ( h<=0 ) return;
	}
	else 
	{
		w = src->w;
		h = src->h;
		sxbeg = 0;
		sybeg = 0;
		dxbeg = dx;
		dybeg = dy;
	}

	s = (RLE_PTR) (src->dat);

	/* Clip top.  */
	for (y = sybeg - 1; y >= 0; y--) 
	{
		long c = *s++;

		while (!RLE_IS_EOL(c)) 
		{
			if (c > 0)
				s += c;
			c = *s++;
		}
	}

	//@@@ bmp_select(dst);
#if 0
	/* Visible part.  */
	for (y = 0; y < h; y++) 
	{
		//@@@ PIXEL_PTR d = OFFSET_PIXEL_PTR(bmp_write_line(dst, dybeg + y), dxbeg);
		PIXEL_PTR d = (PIXEL_PTR) dst->pixels;
		d += (dybeg+y)*PITCH;
		d = OFFSET_PIXEL_PTR( d, dxbeg );
		long c = *s++;

		/* Clip left.  */
		for (x = sxbeg; x > 0; ) {
			if (RLE_IS_EOL(c))
				goto next_line;
			else if (c > 0) {
				/* Run of solid pixels.  */
				if ((x - c) >= 0) {
					/* Fully clipped.  */
					x -= c;
					s += c;
				}
				else {
					/* Visible on the right.  */
					c -= x;
					s += x;
					break;
				}
			}
			else {
				/* Run of transparent pixels.  */
				if ((x + c) >= 0) {
					/* Fully clipped.  */
					x += c;
				}
				else {
					/* Visible on the right.  */
					c += x;
					break;
				}
			}

			c = *s++;
		}

		/* Visible part.  */
		for (x = w; x > 0; ) {
			if (RLE_IS_EOL(c))
				goto next_line;
			else if (c > 0) {
				/* Run of solid pixels.  */
				if ((x - c) >= 0) {
					/* Fully visible.  */
					x -= c;
					for (c--; c >= 0; s++, INC_PIXEL_PTR(d), c--) {
						unsigned long col = (unsigned char) (*s);
						PUT_PIXEL(d, col);
					}
				}
				else {
					/* Clipped on the right.  */
					c -= x;
					for (x--; x >= 0; s++, INC_PIXEL_PTR(d), x--) {
						unsigned long col = *s;
						PUT_PIXEL(d, col);
					}
					break;
				}
			}
			else {
				/* Run of transparent pixels.  */
				x += c;
				d = OFFSET_PIXEL_PTR(d, -c);
			}

			c = *s++;
		}

		/* Clip right.  */
		while (!RLE_IS_EOL(c)) {
			if (c > 0)
				s += c;
			c = *s++;
		}

next_line: ;
	}
#endif
   //@@@bmp_unwrite_line(dst);
	{
		int x_dir = 1;
		int y_dir = 1;
				//unsigned int mask = maskColor;
                int bpp = src->format->BytesPerPixel;
                for (y = 0; y < h; y++) {
                    //Uint8 * sourceLine = computeOffset(src, sxbeg, sybeg + y);
                    Uint8 * destLine = computeOffset(dst, dxbeg, dybeg + y * y_dir);

                    for (x = w - 1; x >= 0; sourceLine += bpp, destLine += bpp * x_dir, x--) {
                        unsigned long sourcePixel = *(Uint32*) sourceLine;
                        // if (!(sourcePixel == mask)){
                            // unsigned int destPixel = *(Uint32*) destLine;
                            // sourcePixel = globalBlend.currentBlender(destPixel, sourcePixel, globalBlend.alpha);
                           // if (filter != NULL){
                            //    *(Uint32 *)destLine = filter->filter(sourcePixel);
                            //} else {
                                *(Uint32 *)destLine = sourcePixel;
                            //}
                        //}
                    }
                }



	}
}

#endif