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

#include "util/SGF_Heap.h"
#include "util/SGF_Debug.h"

namespace SGF {
//#pragma hdrstop

#ifndef USE_LIBC_MALLOC
	#define USE_LIBC_MALLOC		0
#endif

#ifndef CRASH_ON_STATIC_ALLOCATION
//	#define CRASH_ON_STATIC_ALLOCATION
#endif

bool Sys_LockMemory(void *ptr, int bytes){
#ifdef _WIN32
  // http://msdn.microsoft.com/en-us/library/windows/desktop/aa366895%28v=vs.85%29.aspx
  /**Locks the specified regionf the process's virtual address space into physical memory, 
   * ensuring that subsequent access to the region will not incur a page fault.
   * **/
return (VirtualLock(ptr,(SIZE_T)bytes )!= FALSE );
#else
// http://www.informit.com/articles/article.aspx?p=23618&seqNum=9

return (mlock(ptr,(size_t)bytes) != -1);
#endif  
  
}

bool Sys_UnlockMemory( void *ptr, int bytes) {
#ifdef _WIN32
return (VirtualUnlock(ptr,(SIZE_T)bytes )!= FALSE );
#else
return (munlock(ptr,(size_t)bytes)!= -1);
#endif   
  
}



//===============================================================
//
//	CHeap
//
//===============================================================

#define SMALL_HEADER_SIZE		( (int) ( sizeof( SGF_Byte ) + sizeof( SGF_Byte ) ) )
#define MEDIUM_HEADER_SIZE		( (int) ( sizeof( mediumHeapEntry_s ) + sizeof( SGF_Byte ) ) )
#define LARGE_HEADER_SIZE		( (int) ( sizeof( SGF_Dword * ) + sizeof( SGF_Byte ) ) )

#define ALIGN_SIZE( bytes )		( ( (bytes) + ALIGN - 1 ) & ~(ALIGN - 1) )
#define SMALL_ALIGN( bytes )	( ALIGN_SIZE( (bytes) + SMALL_HEADER_SIZE ) - SMALL_HEADER_SIZE )
#define MEDIUM_SMALLEST_SIZE	( ALIGN_SIZE( 256 ) + ALIGN_SIZE( MEDIUM_HEADER_SIZE ) )


class CHeap {

public:
					CHeap();
					~CHeap();				// frees all associated data
	void			Init();					// initialize
	void *			Allocate( const SGF_Dword bytes );	// allocate memory
	void			Free( void *p );				// free memory
	void *			Allocate16( const SGF_Dword bytes );// allocate 16 SGF_Byte aligned memory
	void			Free16( void *p );				// free 16 SGF_Byte aligned memory
	SGF_Dword		Msize( void *p );				// return size of data block
	void			Dump( void  );

	void 			AllocDefragBlock();		// hack for huge renderbumps

private:

	enum {
		ALIGN = 8									// memory alignment in bytes
	};

	enum {
		INVALID_ALLOC	= 0xdd,
		SMALL_ALLOC		= 0xaa,						// small allocation
		MEDIUM_ALLOC	= 0xbb,						// medium allocaction
		LARGE_ALLOC		= 0xcc						// large allocaction
	};

	struct page_s {									// allocation page
		void *				data;					// data pointer to allocated memory
		SGF_Dword				dataSize;				// number of bytes of memory 'data' points to
		page_s *			next;					// next free page in same page manager
		page_s *			prev;					// used only when allocated
		SGF_Dword				largestFree;			// this data used by the medium-size heap manager
		void *				firstFree;				// pointer to first free entry
	};

	struct mediumHeapEntry_s {
		page_s *			page;					// pointer to page
		SGF_Dword				size;					// size of block
		mediumHeapEntry_s *	prev;					// previous block
		mediumHeapEntry_s *	next;					// next block
		mediumHeapEntry_s *	prevFree;				// previous free block
		mediumHeapEntry_s *	nextFree;				// next free block
		SGF_Dword				freeBlock;				// non-zero if free block
	};

	// variables
	void *			smallFirstFree[256/ALIGN+1];	// small heap allocator lists (for allocs of 1-255 bytes)
	page_s *		smallCurPage;					// current page for small allocations
	SGF_Dword		smallCurPageOffset;				// SGF_Byte offset in current page
	page_s *		smallFirstUsedPage;				// first used page of the small heap manager

	page_s *		mediumFirstFreePage;			// first partially free page
	page_s *		mediumLastFreePage;				// last partially free page
	page_s *		mediumFirstUsedPage;			// completely used page

	page_s *		largeFirstUsedPage;				// first page used by the large heap manager

	page_s *		swapPage;

	SGF_Dword			pagesAllocated;					// number of pages currently allocated
	SGF_Dword			pageSize;						// size of one alloc page in bytes

	SGF_Dword			pageRequests;					// page requests
	SGF_Dword			OSAllocs;						// number of allocs made to the OS

	int				c_heapAllocRunningCount;

	void			*defragBlock;					// a single huge block that can be allocated
													// at startup, then freed when needed

	// methods
	page_s *		AllocatePage( SGF_Dword bytes );	// allocate page from the OS
	void			FreePage( CHeap::page_s *p );	// free an OS allocated page

	void *			SmallAllocate( SGF_Dword bytes );	// allocate memory (1-255 bytes) from small heap manager
	void			SmallFree( void *ptr );			// free memory allocated by small heap manager

	void *			MediumAllocateFromPage( CHeap::page_s *p, SGF_Dword sizeNeeded );
	void *			MediumAllocate( SGF_Dword bytes );	// allocate memory (256-32768 bytes) from medium heap manager
	void			MediumFree( void *ptr );		// free memory allocated by medium heap manager

	void *			LargeAllocate( SGF_Dword bytes );	// allocate large block from OS directly
	void			LargeFree( void *ptr );			// free memory allocated by large heap manager

	void			ReleaseSwappedPages();
	void			FreePageReal( CHeap::page_s *p );
};


/*
================
CHeap::Init
================
*/
void CHeap::Init () {
	OSAllocs			= 0;
	pageRequests		= 0;
	pageSize			= 65536 - sizeof( CHeap::page_s );
	pagesAllocated		= 0;								// reset page allocation counter

	largeFirstUsedPage	= NULL;								// init large heap manager
	swapPage			= NULL;

	memset( smallFirstFree, 0, sizeof(smallFirstFree) );	// init small heap manager
	smallFirstUsedPage	= NULL;
	smallCurPage		= AllocatePage( pageSize );
	assert( smallCurPage );
	smallCurPageOffset	= SMALL_ALIGN( 0 );

	defragBlock = NULL;

	mediumFirstFreePage	= NULL;								// init medium heap manager
	mediumLastFreePage	= NULL;
	mediumFirstUsedPage	= NULL;

	c_heapAllocRunningCount = 0;
}

/*
================
CHeap::CHeap
================
*/
CHeap::CHeap() {
	Init();
}

/*
================
CHeap::~CHeap

  returns all allocated memory back to OS
================
*/
CHeap::~CHeap() {

	CHeap::page_s	*p;

	if ( smallCurPage ) {
		FreePage( smallCurPage );			// free small-heap current allocation page
	}
	p = smallFirstUsedPage;					// free small-heap allocated pages 
	while( p ) {
		CHeap::page_s *next = p->next;
		FreePage( p );
		p= next;
	}

	p = largeFirstUsedPage;					// free large-heap allocated pages
	while( p ) {
		CHeap::page_s *next = p->next;
		FreePage( p );
		p = next;
	}

	p = mediumFirstFreePage;				// free medium-heap allocated pages
	while( p ) {
		CHeap::page_s *next = p->next;
		FreePage( p );
		p = next;
	}

	p = mediumFirstUsedPage;				// free medium-heap allocated completely used pages
	while( p ) {
		CHeap::page_s *next = p->next;
		FreePage( p );
		p = next;
	}

	ReleaseSwappedPages();			

	if ( defragBlock ) {
		free( defragBlock );
	}

	assert( pagesAllocated == 0 );
}

/*
================
CHeap::AllocDefragBlock
================
*/
void CHeap::AllocDefragBlock() {
	int		size = 0x40000000;

	if ( defragBlock ) {
		return;
	}
	while( 1 ) {
		defragBlock = malloc( size );
		if ( defragBlock ) {
			break;
		}
		size >>= 1;
	}
	Debug::debug(Debug::heap,__FUNCTION__) << "Allocated a %i mb defrag block size: " << size / (1024*1024) << endl;
}

/*
================
CHeap::Allocate
================
*/
void *CHeap::Allocate( const SGF_Dword bytes ) {
	if ( !bytes ) {
		return NULL;
	}
	c_heapAllocRunningCount++;

#if USE_LIBC_MALLOC
	return malloc( bytes );
#else
	if ( !(bytes & ~255) ) {
		return SmallAllocate( bytes );
	}
	if ( !(bytes & ~32767) ) {
		return MediumAllocate( bytes );
	}
	return LargeAllocate( bytes );
#endif
}

/*
================
CHeap::Free
================
*/
void CHeap::Free( void *p ) {
	if ( !p ) {
		return;
	}
	c_heapAllocRunningCount--;

#if USE_LIBC_MALLOC
	free( p );
#else
	switch( ((SGF_Byte *)(p))[-1] ) {
		case SMALL_ALLOC: {
			SmallFree( p );
			break;
		}
		case MEDIUM_ALLOC: {
			MediumFree( p );
			break;
		}
		case LARGE_ALLOC: {
			LargeFree( p );
			break;
		}
		default: {
			//TODO: Debug::debug(Debug::error,__FUNCTION__) <<  "CHeap::Free: invalid memory block : " << idLib::sys->GetCallStackCurStr( 4 ) << endl;
			break;
		}
	}
#endif
}

/*
================
CHeap::Allocate16
================
*/
void *CHeap::Allocate16( const SGF_Dword bytes ) {
	SGF_Byte *ptr, *alignedPtr;

	ptr = (SGF_Byte *) malloc( bytes + 16 + 4 );
	if ( !ptr ) {
		if ( defragBlock ) {
			Debug::debug(Debug::heap,__FUNCTION__) << "Freeing defragBlock on alloc of : "<< bytes <<endl;
			free( defragBlock );
			defragBlock = NULL;
			ptr = (SGF_Byte *) malloc( bytes + 16 + 4 );			
			AllocDefragBlock();
		}
		if ( !ptr ) {
			Debug::debug(Debug::error,__FUNCTION__) <<"malloc failure for : "<< bytes << endl;
		}
	}
	alignedPtr = (SGF_Byte *) ( ( (uintptr_t) ptr ) + 15 & ~15 );
	if ( alignedPtr - ptr < 4 ) {
		alignedPtr += 16;
	}
	*((int *)(alignedPtr - 4)) = (uintptr_t) ptr;
	return (void *) alignedPtr;
}

/*
================
CHeap::Free16
================
*/
void CHeap::Free16( void *p ) {
	free( (void *) *((int *) (( (SGF_Byte *) p ) - 4)) );
}

/*
================
CHeap::Msize

  returns size of allocated memory block
  p	= pointer to memory block
  Notes:	size may not be the same as the size in the original
			allocation request (due to block alignment reasons).
================
*/
SGF_Dword CHeap::Msize( void *p ) {

	if ( !p ) {
		return 0;
	}

#if USE_LIBC_MALLOC
	#ifdef _WIN32
		return _msize( p );
	#else
		return 0;
	#endif
#else
	switch( ((SGF_Byte *)(p))[-1] ) {
		case SMALL_ALLOC: {
			return SMALL_ALIGN( ((SGF_Byte *)(p))[-SMALL_HEADER_SIZE] * ALIGN );
		}
		case MEDIUM_ALLOC: {
			return ((mediumHeapEntry_s *)(((SGF_Byte *)(p)) - ALIGN_SIZE( MEDIUM_HEADER_SIZE )))->size - ALIGN_SIZE( MEDIUM_HEADER_SIZE );
		}
		case LARGE_ALLOC: {
			return ((CHeap::page_s*)(*((SGF_Dword *)(((SGF_Byte *)p) - ALIGN_SIZE( LARGE_HEADER_SIZE )))))->dataSize - ALIGN_SIZE( LARGE_HEADER_SIZE );
		}
		default: {
			//Todo: Debug::debug(Debug::error,__FUNCTION__) << "CHeap::Msize: invalid memory block -> "<< idLib::sys->GetCallStackCurStr( 4 ) << endl;
			return 0;
		}
	}
#endif
}

/*
================
CHeap::Dump

  dump contents of the heap
================
*/
void CHeap::Dump() {
	CHeap::page_s	*pg;

	for ( pg = smallFirstUsedPage; pg; pg = pg->next ) {
		Debug::debug(Debug::heap,__FUNCTION__) << pg->data << "  bytes "<< pg->dataSize <<"-8d  (in use by small heap)"<<endl;
	}

	if ( smallCurPage ) {
		pg = smallCurPage;
		Debug::debug(Debug::heap,__FUNCTION__) << pg->data << "  bytes "<<pg->dataSize <<"-8d  (small heap active page)"<< endl;
	}

	for ( pg = mediumFirstUsedPage; pg; pg = pg->next ) {
		Debug::debug(Debug::heap,__FUNCTION__) << pg->data<<"  bytes "<< pg->dataSize<<"-8d  (completely used by medium heap)\n"<< endl;
	}

	for ( pg = mediumFirstFreePage; pg; pg = pg->next ) {
		Debug::debug(Debug::heap,__FUNCTION__) << pg->data<<"  bytes "<< pg->dataSize <<"-8d  (partially used by medium heap)\n"<< endl;
	}
	
	for ( pg = largeFirstUsedPage; pg; pg = pg->next ) {
		Debug::debug(Debug::heap,__FUNCTION__) << pg->data<<"  bytes "<<pg->dataSize <<"-8d  (fully used by large heap)\n"<< endl;
	}

	Debug::debug(Debug::heap,__FUNCTION__) << "pages allocated : "<< pagesAllocated <<endl;
}

/*
================
CHeap::FreePageReal

  frees page to be used by the OS
  p	= page to free
================
*/
void CHeap::FreePageReal( CHeap::page_s *p ) {
	assert( p );
	::free( p );
}

/*
================
CHeap::ReleaseSwappedPages

  releases the swap page to OS
================
*/
void CHeap::ReleaseSwappedPages () {
	if ( swapPage ) {
		FreePageReal( swapPage );
	}
	swapPage = NULL;
}

/*
================
CHeap::AllocatePage

  allocates memory from the OS
  bytes	= page size in bytes
  returns pointer to page
================
*/
CHeap::page_s* CHeap::AllocatePage( SGF_Dword bytes ) {
	CHeap::page_s*	p;

	pageRequests++;

	if ( swapPage && swapPage->dataSize == bytes ) {			// if we've got a swap page somewhere
		p			= swapPage;
		swapPage	= NULL;
	}
	else {
		SGF_Dword size;

		size = bytes + sizeof(CHeap::page_s);

		p = (CHeap::page_s *) ::malloc( size + ALIGN - 1 );
		if ( !p ) {
			if ( defragBlock ) {
				Debug::debug(Debug::heap,__FUNCTION__) <<  "Freeing defragBlock on alloc of : "<< size + ALIGN - 1 <<endl;
				free( defragBlock );
				defragBlock = NULL;
				p = (CHeap::page_s *) ::malloc( size + ALIGN - 1 );			
				AllocDefragBlock();
			}
			if ( !p ) {
				Debug::debug(Debug::error,__FUNCTION__) <<  "malloc failure for "<< bytes <<endl;
			}
		}

		p->data		= (void *) ALIGN_SIZE( (uintptr_t)((SGF_Byte *)(p)) + sizeof( CHeap::page_s ) );
		p->dataSize	= size - sizeof(CHeap::page_s);
		p->firstFree = NULL;
		p->largestFree = 0;
		OSAllocs++;
	}

	p->prev = NULL;
	p->next = NULL;

	pagesAllocated++;
	
	return p;
}

/*
================
CHeap::FreePage

  frees a page back to the operating system
  p	= pointer to page
================
*/
void CHeap::FreePage( CHeap::page_s *p ) {
	assert( p );

	if ( p->dataSize == pageSize && !swapPage ) {			// add to swap list?
		swapPage = p;
	}
	else {
		FreePageReal( p );
	}

	pagesAllocated--;
}

//===============================================================
//
//	small heap code
//
//===============================================================

/*
================
CHeap::SmallAllocate

  allocate memory (1-255 bytes) from the small heap manager
  bytes = number of bytes to allocate
  returns pointer to allocated memory
================
*/
void *CHeap::SmallAllocate( SGF_Dword bytes ) {
	// we need the at least sizeof( SGF_Dword ) bytes for the free list
	if ( bytes < sizeof( SGF_Dword ) ) {
		bytes = sizeof( SGF_Dword );
	}

	// increase the number of bytes if necessary to make sure the next small allocation is aligned
	bytes = SMALL_ALIGN( bytes );

	SGF_Byte *smallBlock = (SGF_Byte *)(smallFirstFree[bytes / ALIGN]);
	if ( smallBlock ) {
		SGF_Dword *link = (SGF_Dword *)(smallBlock + SMALL_HEADER_SIZE);
		smallBlock[1] = SMALL_ALLOC;					// allocation identifier
		smallFirstFree[bytes / ALIGN] = (void *)(*link);
		return (void *)(link);
	}

	SGF_Dword bytesLeft = (long)(pageSize) - smallCurPageOffset;
	// if we need to allocate a new page
	if ( bytes >= bytesLeft ) {

		smallCurPage->next	= smallFirstUsedPage;
		smallFirstUsedPage	= smallCurPage;
		smallCurPage		= AllocatePage( pageSize );
		if ( !smallCurPage ) {
			return NULL;
		}
		// make sure the first allocation is aligned
		smallCurPageOffset	= SMALL_ALIGN( 0 );
	}

	smallBlock			= ((SGF_Byte *)smallCurPage->data) + smallCurPageOffset;
	smallBlock[0]		= (SGF_Byte)(bytes / ALIGN);		// write # of bytes/ALIGN
	smallBlock[1]		= SMALL_ALLOC;					// allocation identifier
	smallCurPageOffset  += bytes + SMALL_HEADER_SIZE;	// increase the offset on the current page
	return ( smallBlock + SMALL_HEADER_SIZE );			// skip the first two bytes
}

/*
================
CHeap::SmallFree

  frees a block of memory allocated by SmallAllocate() call
  data = pointer to block of memory
================
*/
void CHeap::SmallFree( void *ptr ) {
	((SGF_Byte *)(ptr))[-1] = INVALID_ALLOC;

	SGF_Byte *d = ( (SGF_Byte *)ptr ) - SMALL_HEADER_SIZE;
	SGF_Dword *dt = (SGF_Dword *)ptr;
	// index into the table with free small memory blocks
	SGF_Dword ix = *d;

	// check if the index is correct
	if ( ix > (256 / ALIGN) ) {
		Debug::debug(Debug::error,__FUNCTION__) << "SmallFree: invalid memory block" <<endl;
	}

	*dt = (uintptr_t)smallFirstFree[ix];	// write next index
	smallFirstFree[ix] = (void *)d;		// link
}

//===============================================================
//
//	medium heap code
//
//	Medium-heap allocated pages not returned to OS until heap destructor
//	called (re-used instead on subsequent medium-size malloc requests).
//
//===============================================================

/*
================
CHeap::MediumAllocateFromPage

  performs allocation using the medium heap manager from a given page
  p				= page
  sizeNeeded	= # of bytes needed
  returns pointer to allocated memory
================
*/
void *CHeap::MediumAllocateFromPage( CHeap::page_s *p, SGF_Dword sizeNeeded ) {

	mediumHeapEntry_s	*best,*nw = NULL;
	SGF_Byte				*ret;

	best = (mediumHeapEntry_s *)(p->firstFree);			// first block is largest

	assert( best );
	assert( best->size == p->largestFree );
	assert( best->size >= sizeNeeded );

	// if we can allocate another block from this page after allocating sizeNeeded bytes
	if ( best->size >= (SGF_Dword)( sizeNeeded + MEDIUM_SMALLEST_SIZE ) ) {
		nw = (mediumHeapEntry_s *)((SGF_Byte *)best + best->size - sizeNeeded);
		nw->page		= p;
		nw->prev		= best;
		nw->next		= best->next;
		nw->prevFree	= NULL;
		nw->nextFree	= NULL;
		nw->size		= sizeNeeded;
		nw->freeBlock	= 0;			// used block
		if ( best->next ) {
			best->next->prev = nw;
		}
		best->next	= nw;
		best->size	-= sizeNeeded;
		
		p->largestFree = best->size;
	}
	else {
		if ( best->prevFree ) {
			best->prevFree->nextFree = best->nextFree;
		}
		else {
			p->firstFree = (void *)best->nextFree;
		}
		if ( best->nextFree ) {
			best->nextFree->prevFree = best->prevFree;
		}

		best->prevFree  = NULL;
		best->nextFree  = NULL;
		best->freeBlock = 0;			// used block
		nw = best;

		p->largestFree = 0;
	}

	ret		= (SGF_Byte *)(nw) + ALIGN_SIZE( MEDIUM_HEADER_SIZE );
	ret[-1] = MEDIUM_ALLOC;		// allocation identifier

	return (void *)(ret);
}

/*
================
CHeap::MediumAllocate

  allocate memory (256-32768 bytes) from medium heap manager
  bytes	= number of bytes to allocate
  returns pointer to allocated memory
================
*/
void *CHeap::MediumAllocate( SGF_Dword bytes ) {
	CHeap::page_s		*p;
	void				*data;

	SGF_Dword sizeNeeded = ALIGN_SIZE( bytes ) + ALIGN_SIZE( MEDIUM_HEADER_SIZE );

	// find first page with enough space
	for ( p = mediumFirstFreePage; p; p = p->next ) {
		if ( p->largestFree >= sizeNeeded ) {
			break;
		}
	}

	if ( !p ) {								// need to allocate new page?
		p = AllocatePage( pageSize );
		if ( !p ) {
			return NULL;					// malloc failure!
		}
		p->prev		= NULL;
		p->next		= mediumFirstFreePage;
		if (p->next) {
			p->next->prev = p;
		}
		else {
			mediumLastFreePage	= p;
		}

		mediumFirstFreePage		= p;
		
		p->largestFree	= pageSize;
		p->firstFree	= (void *)p->data;

		mediumHeapEntry_s *e;
		e				= (mediumHeapEntry_s *)(p->firstFree);
		e->page			= p;
		// make sure ((SGF_Byte *)e + e->size) is aligned
		e->size			= pageSize & ~(ALIGN - 1);
		e->prev			= NULL;
		e->next			= NULL;
		e->prevFree		= NULL;
		e->nextFree		= NULL;
		e->freeBlock	= 1;
	}

	data = MediumAllocateFromPage( p, sizeNeeded );		// allocate data from page

    // if the page can no longer serve memory, move it away from free list
	// (so that it won't slow down the later alloc queries)
	// this modification speeds up the pageWalk from O(N) to O(sqrt(N))
	// a call to free may swap this page back to the free list

	if ( p->largestFree < MEDIUM_SMALLEST_SIZE ) {
		if ( p == mediumLastFreePage ) {
			mediumLastFreePage = p->prev;
		}

		if ( p == mediumFirstFreePage ) {
			mediumFirstFreePage = p->next;
		}

		if ( p->prev ) {
			p->prev->next = p->next;
		}
		if ( p->next ) {
			p->next->prev = p->prev;
		}

		// link to "completely used" list
		p->prev = NULL;
		p->next = mediumFirstUsedPage;
		if ( p->next ) {
			p->next->prev = p;
		}
		mediumFirstUsedPage = p;
		return data;
	} 

	// re-order linked list (so that next malloc query starts from current
	// matching block) -- this speeds up both the page walks and block walks

	if ( p != mediumFirstFreePage ) {
		assert( mediumLastFreePage );
		assert( mediumFirstFreePage );
		assert( p->prev);

		mediumLastFreePage->next	= mediumFirstFreePage;
		mediumFirstFreePage->prev	= mediumLastFreePage;
		mediumLastFreePage			= p->prev;
		p->prev->next				= NULL;
		p->prev						= NULL;
		mediumFirstFreePage			= p;
	}

	return data;
}

/*
================
CHeap::MediumFree

  frees a block allocated by the medium heap manager
  ptr	= pointer to data block
================
*/
void CHeap::MediumFree( void *ptr ) {
	((SGF_Byte *)(ptr))[-1] = INVALID_ALLOC;

	mediumHeapEntry_s	*e = (mediumHeapEntry_s *)((SGF_Byte *)ptr - ALIGN_SIZE( MEDIUM_HEADER_SIZE ));
	CHeap::page_s		*p = e->page;
	bool				isInFreeList;

	isInFreeList = p->largestFree >= MEDIUM_SMALLEST_SIZE;

	assert( e->size );
	assert( e->freeBlock == 0 );

	mediumHeapEntry_s *prev = e->prev;

	// if the previous block is free we can merge
	if ( prev && prev->freeBlock ) {
		prev->size += e->size;
		prev->next = e->next;
		if ( e->next ) {
			e->next->prev = prev;
		}
		e = prev;
	}
	else {
		e->prevFree		= NULL;				// link to beginning of free list
		e->nextFree		= (mediumHeapEntry_s *)p->firstFree;
		if ( e->nextFree ) {
			assert( !(e->nextFree->prevFree) );
			e->nextFree->prevFree = e;
		}

		p->firstFree	= e;
		p->largestFree	= e->size;
		e->freeBlock	= 1;				// mark block as free
	}
			
	mediumHeapEntry_s *next = e->next;

	// if the next block is free we can merge
	if ( next && next->freeBlock ) {
		e->size += next->size;
		e->next = next->next;
		
		if ( next->next ) {
			next->next->prev = e;
		}
		
		if ( next->prevFree ) {
			next->prevFree->nextFree = next->nextFree;
		}
		else {
			assert( next == p->firstFree );
			p->firstFree = next->nextFree;
		}

		if ( next->nextFree ) {
			next->nextFree->prevFree = next->prevFree;
		}
	}

	if ( p->firstFree ) {
		p->largestFree = ((mediumHeapEntry_s *)(p->firstFree))->size;
	}
	else {
		p->largestFree = 0;
	}

	// did e become the largest block of the page ?

	if ( e->size > p->largestFree ) {
		assert( e != p->firstFree );
		p->largestFree = e->size;

		if ( e->prevFree ) {
			e->prevFree->nextFree = e->nextFree;
		}
		if ( e->nextFree ) {
			e->nextFree->prevFree = e->prevFree;
		}
		
		e->nextFree = (mediumHeapEntry_s *)p->firstFree;
		e->prevFree = NULL;
		if ( e->nextFree ) {
			e->nextFree->prevFree = e;
		}
		p->firstFree = e;
	}

	// if page wasn't in free list (because it was near-full), move it back there
	if ( !isInFreeList ) {

		// remove from "completely used" list
		if ( p->prev ) {
			p->prev->next = p->next;
		}
		if ( p->next ) {
			p->next->prev = p->prev;
		}
		if ( p == mediumFirstUsedPage ) {
			mediumFirstUsedPage = p->next;
		}

		p->next = NULL;
		p->prev = mediumLastFreePage;

		if ( mediumLastFreePage ) {
			mediumLastFreePage->next = p;
		}
		mediumLastFreePage = p;
		if ( !mediumFirstFreePage ) {
			mediumFirstFreePage = p;
		}
	} 
}

//===============================================================
//
//	large heap code
//
//===============================================================

/*
================
CHeap::LargeAllocate

  allocates a block of memory from the operating system
  bytes	= number of bytes to allocate
  returns pointer to allocated memory
================
*/
void *CHeap::LargeAllocate( SGF_Dword bytes ) {
	CHeap::page_s *p = AllocatePage( bytes + ALIGN_SIZE( LARGE_HEADER_SIZE ) );

	assert( p );

	if ( !p ) {
		return NULL;
	}

	SGF_Byte *	d	= (SGF_Byte*)(p->data) + ALIGN_SIZE( LARGE_HEADER_SIZE );
	SGF_Dword *	dw	= (SGF_Dword*)(d - ALIGN_SIZE( LARGE_HEADER_SIZE ));
	dw[0]		= (uintptr_t)p;				// write pointer back to page table
	d[-1]		= LARGE_ALLOC;			// allocation identifier

	// link to 'large used page list'
	p->prev = NULL;
	p->next = largeFirstUsedPage;
	if ( p->next ) {
		p->next->prev = p;
	}
	largeFirstUsedPage = p;

	return (void *)(d);
}

/*
================
CHeap::LargeFree

  frees a block of memory allocated by the 'large memory allocator'
  p	= pointer to allocated memory
================
*/
void CHeap::LargeFree( void *ptr) {
	CHeap::page_s*	pg;

	((SGF_Byte *)(ptr))[-1] = INVALID_ALLOC;

	// get page pointer
	pg = (CHeap::page_s *)(*((SGF_Dword *)(((SGF_Byte *)ptr) - ALIGN_SIZE( LARGE_HEADER_SIZE ))));

	// unlink from doubly linked list
	if ( pg->prev ) {
		pg->prev->next = pg->next;
	}
	if ( pg->next ) {
		pg->next->prev = pg->prev;
	}
	if ( pg == largeFirstUsedPage ) {
		largeFirstUsedPage = pg->next;
	}
	pg->next = pg->prev = NULL;

	FreePage(pg);
}

//===============================================================
//
//	memory allocation all in one place
//
//===============================================================

#undef new

static CHeap *			mem_heap = NULL;
static memoryStats_t	mem_total_allocs = { 0, 0x0fffffff, -1, 0 };
static memoryStats_t	mem_frame_allocs;
static memoryStats_t	mem_frame_frees;

/*
==================
Mem_ClearFrameStats
==================
*/
void Mem_ClearFrameStats() {
	mem_frame_allocs.num = mem_frame_frees.num = 0;
	mem_frame_allocs.minSize = mem_frame_frees.minSize = 0x0fffffff;
	mem_frame_allocs.maxSize = mem_frame_frees.maxSize = -1;
	mem_frame_allocs.totalSize = mem_frame_frees.totalSize = 0;
}

/*
==================
Mem_GetFrameStats
==================
*/
void Mem_GetFrameStats( memoryStats_t &allocs, memoryStats_t &frees ) {
	allocs = mem_frame_allocs;
	frees = mem_frame_frees;
}

/*
==================
Mem_GetStats
==================
*/
void Mem_GetStats( memoryStats_t &stats ) {
	stats = mem_total_allocs;
}

/*
==================
Mem_UpdateStats
==================
*/
void Mem_UpdateStats( memoryStats_t &stats, int size ) {
	stats.num++;
	if ( size < stats.minSize ) {
		stats.minSize = size;
	}
	if ( size > stats.maxSize ) {
		stats.maxSize = size;
	}
	stats.totalSize += size;
}

/*
==================
Mem_UpdateAllocStats
==================
*/
void Mem_UpdateAllocStats( int size ) {
	Mem_UpdateStats( mem_frame_allocs, size );
	Mem_UpdateStats( mem_total_allocs, size );
}

/*
==================
Mem_UpdateFreeStats
==================
*/
void Mem_UpdateFreeStats( int size ) {
	Mem_UpdateStats( mem_frame_frees, size );
	mem_total_allocs.num--;
	mem_total_allocs.totalSize -= size;
}


#ifndef ID_DEBUG_MEMORY

/*
==================
Mem_Alloc
==================
*/
void *Mem_Alloc( const int size ) {
	if ( !size ) {
		return NULL;
	}
	if ( !mem_heap ) {
#ifdef CRASH_ON_STATIC_ALLOCATION
		*((int*)0x0) = 1;
#endif
		return malloc( size );
	}
	void *mem = mem_heap->Allocate( size );
	Mem_UpdateAllocStats( mem_heap->Msize( mem ) );
	return mem;
}

/*
==================
Mem_Free
==================
*/
void Mem_Free( void *ptr ) {
	if ( !ptr ) {
		return;
	}
	if ( !mem_heap ) {
#ifdef CRASH_ON_STATIC_ALLOCATION
		*((int*)0x0) = 1;
#endif
		free( ptr );
		return;
	}
	Mem_UpdateFreeStats( mem_heap->Msize( ptr ) );
 	mem_heap->Free( ptr );
}

/*
==================
Mem_Alloc16
==================
*/
void *Mem_Alloc16( const int size ) {
	if ( !size ) {
		return NULL;
	}
	if ( !mem_heap ) {
#ifdef CRASH_ON_STATIC_ALLOCATION
		*((int*)0x0) = 1;
#endif
		return malloc( size );
	}
	void *mem = mem_heap->Allocate16( size );
	// make sure the memory is 16 SGF_Byte aligned
	assert( ( ((uintptr_t)mem) & 15) == 0 );
	return mem;
}

/*
==================
Mem_Free16
==================
*/
void Mem_Free16( void *ptr ) {
	if ( !ptr ) {
		return;
	}
	if ( !mem_heap ) {
#ifdef CRASH_ON_STATIC_ALLOCATION
		*((int*)0x0) = 1;
#endif
		free( ptr );
		return;
	}
	// make sure the memory is 16 SGF_Byte aligned
	assert( ( ((uintptr_t)ptr) & 15) == 0 );
 	mem_heap->Free16( ptr );
}

/*
==================
Mem_ClearedAlloc
==================
*/
void *Mem_ClearedAlloc( const int size ) {
	void *mem = Mem_Alloc( size );
#ifndef ANDROID
	SIMDProcessor->Memset( mem, 0, size );
#else
	memset(mem,0,size);
#endif
	return mem;
}

/*
==================
Mem_ClearedAlloc
==================
*/
void Mem_AllocDefragBlock() {
	mem_heap->AllocDefragBlock();
}

/*
==================
Mem_CopyString
==================
*/
char *Mem_CopyString( const char *in ) {
	char	*out;
	
	out = (char *)Mem_Alloc( strlen(in) + 1 );
	strcpy( out, in );
	return out;
}

/*
==================
Mem_Dump_f
==================
*/
void Mem_Dump_f( const CCMDLineArgs &args ) {
}

/*
==================
Mem_DumpCompressed_f
==================
*/
void Mem_DumpCompressed_f( const CCMDLineArgs &args ) {
}

/*
==================
Mem_Init
==================
*/
void Mem_Init() {
	mem_heap = new CHeap;
	Mem_ClearFrameStats();
}

/*
==================
Mem_Shutdown
==================
*/
void Mem_Shutdown() {
	CHeap *m = mem_heap;
	mem_heap = NULL;
	delete m;
}

/*
==================
Mem_EnableLeakTest
==================
*/
void Mem_EnableLeakTest( const char *name ) {
}


#else /* !ID_DEBUG_MEMORY */

#undef		Mem_Alloc
#undef		Mem_ClearedAlloc
#undef		Com_ClearedReAlloc
#undef		Mem_Free
#undef		Mem_CopyString
#undef		Mem_Alloc16
#undef		Mem_Free16

#define MAX_CALLSTACK_DEPTH		6

// size of this struct must be a multiple of 16 bytes
typedef struct debugMemory_s {
	const char *			fileName;
	int						lineNumber;
	int						frameNumber;
	int						size;
	address_t				callStack[MAX_CALLSTACK_DEPTH];
	struct debugMemory_s *	prev;
	struct debugMemory_s *	next;
} debugMemory_t;

static debugMemory_t *	mem_debugMemory = NULL;
static char				mem_leakName[256] = "";

/*
==================
Mem_CleanupFileName
==================
*/
const char *Mem_CleanupFileName( const char *fileName ) {
	int i1, i2;
	CMyString newFileName;
	static char newFileNames[4][MAX_STRING_CHARS];
	static int index;

	newFileName = fileName;
	newFileName.BackSlashesToSlashes();
	i1 = newFileName.Find( "neo", false );
	if ( i1 >= 0 ) {
		i1 = newFileName.Find( "/", false, i1 );
		newFileName = newFileName.Right( newFileName.Length() - ( i1 + 1 ) );
	}
	while( 1 ) {
		i1 = newFileName.Find( "/../" );
		if ( i1 <= 0 ) {
			break;
		}
		i2 = i1 - 1;
		while( i2 > 1 && newFileName[i2-1] != '/' ) {
			i2--;
		}
		newFileName = newFileName.Left( i2 - 1 ) + newFileName.Right( newFileName.Length() - ( i1 + 4 ) );
	}
	index = ( index + 1 ) & 3;
	strncpy( newFileNames[index], newFileName.c_str(), sizeof( newFileNames[index] ) );
	return newFileNames[index];
}

/*
==================
Mem_Dump
==================
*/
void Mem_Dump( const char *fileName ) {
	int i, numBlocks, totalSize;
	char dump[32], *ptr;
	debugMemory_t *b;
	CMyString module, funcName;
	FILE *f;

	f = fopen( fileName, "wb" );
	if ( !f ) {
		return;
	}

	totalSize = 0;
	for ( numBlocks = 0, b = mem_debugMemory; b; b = b->next, numBlocks++ ) {
		ptr = ((char *) b) + sizeof(debugMemory_t);
		totalSize += b->size;
		for ( i = 0; i < (sizeof(dump)-1) && i < b->size; i++) {
			if ( ptr[i] >= 32 && ptr[i] < 127 ) {
				dump[i] = ptr[i];
			} else {
				dump[i] = '_';
			}
		}
		dump[i] = '\0';
		if ( ( b->size >> 10 ) != 0 ) {
			fprintf( f, "size: %6d KB: %s, line: %d [%s], call stack: %s\r\n", ( b->size >> 10 ), Mem_CleanupFileName(b->fileName), b->lineNumber, dump, idLib::sys->GetCallStackStr( b->callStack, MAX_CALLSTACK_DEPTH ) );
		}
		else {
			fprintf( f, "size: %7d B: %s, line: %d [%s], call stack: %s\r\n", b->size, Mem_CleanupFileName(b->fileName), b->lineNumber, dump, idLib::sys->GetCallStackStr( b->callStack, MAX_CALLSTACK_DEPTH ) );
		}
	}

	idLib::sys->ShutdownSymbols();

	fprintf( f, "%8d total memory blocks allocated\r\n", numBlocks );
	fprintf( f, "%8d KB memory allocated\r\n", ( totalSize >> 10 ) );

	fclose( f );
}

/*
==================
Mem_Dump_f
==================
*/
void Mem_Dump_f( const CCMDLineArgs &args ) {
	const char *fileName;

	if ( args.Argc() >= 2 ) {
		fileName = args.Argv( 1 );
	}
	else {
		fileName = "memorydump.txt";
	}
	Mem_Dump( fileName );
}

/*
==================
Mem_DumpCompressed
==================
*/
typedef struct allocInfo_s {
	const char *			fileName;
	int						lineNumber;
	int						size;
	int						numAllocs;
	address_t				callStack[MAX_CALLSTACK_DEPTH];
	struct allocInfo_s *	next;
} allocInfo_t;

typedef enum {
	MEMSORT_SIZE,
	MEMSORT_LOCATION,
	MEMSORT_NUMALLOCS,
	MEMSORT_CALLSTACK
} memorySortType_t;

void Mem_DumpCompressed( const char *fileName, memorySortType_t memSort, int sortCallStack, int numFrames ) {
	int numBlocks, totalSize, r, j;
	debugMemory_t *b;
	allocInfo_t *a, *nexta, *allocInfo = NULL, *sortedAllocInfo = NULL, *prevSorted, *nextSorted;
	CMyString module, funcName;
	FILE *f;

	// build list with memory allocations
	totalSize = 0;
	numBlocks = 0;
	for ( b = mem_debugMemory; b; b = b->next ) {

		if ( numFrames && b->frameNumber < idLib::frameNumber - numFrames ) {
			continue;
		}

		numBlocks++;
		totalSize += b->size;

		// search for an allocation from the same source location
		for ( a = allocInfo; a; a = a->next ) {
			if ( a->lineNumber != b->lineNumber ) {
				continue;
			}
			for ( j = 0; j < MAX_CALLSTACK_DEPTH; j++ ) {
				if ( a->callStack[j] != b->callStack[j] ) {
					break;
				}
			}
			if ( j < MAX_CALLSTACK_DEPTH ) {
				continue;
			}
			if ( CMyString::Cmp( a->fileName, b->fileName ) != 0 ) {
				continue;
			}
			a->numAllocs++;
			a->size += b->size;
			break;
		}

		// if this is an allocation from a new source location
		if ( !a ) {
			a = (allocInfo_t *) ::malloc( sizeof( allocInfo_t ) );
			a->fileName = b->fileName;
			a->lineNumber = b->lineNumber;
			a->size = b->size;
			a->numAllocs = 1;
			for ( j = 0; j < MAX_CALLSTACK_DEPTH; j++ ) {
				a->callStack[j] = b->callStack[j];
			}
			a->next = allocInfo;
			allocInfo = a;
		}
	}

	// sort list
	for ( a = allocInfo; a; a = nexta ) {
		nexta = a->next;

		prevSorted = NULL;
		switch( memSort ) {
			// sort on size
			case MEMSORT_SIZE: {
				for ( nextSorted = sortedAllocInfo; nextSorted; nextSorted = nextSorted->next ) {
					if ( a->size > nextSorted->size ) {
						break;
					}
					prevSorted = nextSorted;
				}
				break;
			}
			// sort on file name and line number
			case MEMSORT_LOCATION: {
				for ( nextSorted = sortedAllocInfo; nextSorted; nextSorted = nextSorted->next ) {
					r = CMyString::Cmp( Mem_CleanupFileName( a->fileName ), Mem_CleanupFileName( nextSorted->fileName ) );
					if ( r < 0 || ( r == 0 && a->lineNumber < nextSorted->lineNumber ) ) {
						break;
					}
					prevSorted = nextSorted;
				}
				break;
			}
			// sort on the number of allocations
			case MEMSORT_NUMALLOCS: {
				for ( nextSorted = sortedAllocInfo; nextSorted; nextSorted = nextSorted->next ) {
					if ( a->numAllocs > nextSorted->numAllocs ) {
						break;
					}
					prevSorted = nextSorted;
				}
				break;
			}
			// sort on call stack
			case MEMSORT_CALLSTACK: {
				for ( nextSorted = sortedAllocInfo; nextSorted; nextSorted = nextSorted->next ) {
					if ( a->callStack[sortCallStack] < nextSorted->callStack[sortCallStack] ) {
						break;
					}
					prevSorted = nextSorted;
				}
				break;
			}
		}
		if ( !prevSorted ) {
			a->next = sortedAllocInfo;
			sortedAllocInfo = a;
		}
		else {
			prevSorted->next = a;
			a->next = nextSorted;
		}
	}

	f = fopen( fileName, "wb" );
	if ( !f ) {
		return;
	}

	// write list to file
	for ( a = sortedAllocInfo; a; a = nexta ) {
		nexta = a->next;
		fprintf( f, "size: %6d KB, allocs: %5d: %s, line: %d, call stack: %s\r\n",
					(a->size >> 10), a->numAllocs, Mem_CleanupFileName(a->fileName),
							a->lineNumber, idLib::sys->GetCallStackStr( a->callStack, MAX_CALLSTACK_DEPTH ) );
		::free( a );
	}

	idLib::sys->ShutdownSymbols();

	fprintf( f, "%8d total memory blocks allocated\r\n", numBlocks );
	fprintf( f, "%8d KB memory allocated\r\n", ( totalSize >> 10 ) );

	fclose( f );
}

/*
==================
Mem_DumpCompressed_f
==================
*/
void Mem_DumpCompressed_f( const CCMDLineArgs &args ) {
	int argNum;
	const char *arg, *fileName;
	memorySortType_t memSort = MEMSORT_LOCATION;
	int sortCallStack = 0, numFrames = 0;

	// get cmd-line options
	argNum = 1;
	arg = args.Argv( argNum );
	while( arg[0] == '-' ) {
		arg = args.Argv( ++argNum );
		if ( CMyString::Icmp( arg, "s" ) == 0 ) {
			memSort = MEMSORT_SIZE;
		} else if ( CMyString::Icmp( arg, "l" ) == 0 ) {
			memSort = MEMSORT_LOCATION;
		} else if ( CMyString::Icmp( arg, "a" ) == 0 ) {
			memSort = MEMSORT_NUMALLOCS;
		} else if ( CMyString::Icmp( arg, "cs1" ) == 0 ) {
			memSort = MEMSORT_CALLSTACK;
			sortCallStack = 2;
		} else if ( CMyString::Icmp( arg, "cs2" ) == 0 ) {
			memSort = MEMSORT_CALLSTACK;
			sortCallStack = 1;
		} else if ( CMyString::Icmp( arg, "cs3" ) == 0 ) {
			memSort = MEMSORT_CALLSTACK;
			sortCallStack = 0;
		} else if ( arg[0] == 'f' ) {
			numFrames = atoi( arg + 1 );
		} else {
			Debug::debug(Debug::math,__FUNCTION__) << "memoryDumpCompressed [options] [filename]\n"
						"options:\n"
						"  -s     sort on size\n"
						"  -l     sort on location\n"
						"  -a     sort on the number of allocations\n"
						"  -cs1   sort on first function on call stack\n"
						"  -cs2   sort on second function on call stack\n"
						"  -cs3   sort on third function on call stack\n"
						"  -f<X>  only report allocations the last X frames\n"
						"By default the memory allocations are sorted on location.\n"
						"By default a 'memorydump.txt' is written if no file name is specified.\n" );
			return;
		}
		arg = args.Argv( ++argNum );
	}
	if ( argNum >= args.Argc() ) {
		fileName = "memorydump.txt";
	} else {
		fileName = arg;
	}
	Mem_DumpCompressed( fileName, memSort, sortCallStack, numFrames );
}

/*
==================
Mem_AllocDebugMemory
==================
*/
void *Mem_AllocDebugMemory( const int size, const char *fileName, const int lineNumber, const bool align16 ) {
	void *p;
	debugMemory_t *m;

	if ( !size ) {
		return NULL;
	}

	if ( !mem_heap ) {
#ifdef CRASH_ON_STATIC_ALLOCATION
		*((int*)0x0) = 1;
#endif
		// NOTE: set a breakpoint here to find memory allocations before mem_heap is initialized
		return malloc( size );
	}

	if ( align16 ) {
		p = mem_heap->Allocate16( size + sizeof( debugMemory_t ) );
	}
	else {
		p = mem_heap->Allocate( size + sizeof( debugMemory_t ) );
	}

	Mem_UpdateAllocStats( size );

	m = (debugMemory_t *) p;
	m->fileName = fileName;
	m->lineNumber = lineNumber;
	m->frameNumber = idLib::frameNumber;
	m->size = size;
	m->next = mem_debugMemory;
	m->prev = NULL;
	if ( mem_debugMemory ) {
		mem_debugMemory->prev = m;
	}
	mem_debugMemory = m;
	idLib::sys->GetCallStack( m->callStack, MAX_CALLSTACK_DEPTH );

	return ( ( (SGF_Byte *) p ) + sizeof( debugMemory_t ) );
}

/*
==================
Mem_FreeDebugMemory
==================
*/
void Mem_FreeDebugMemory( void *p, const char *fileName, const int lineNumber, const bool align16 ) {
	debugMemory_t *m;

	if ( !p ) {
		return;
	}

	if ( !mem_heap ) {
#ifdef CRASH_ON_STATIC_ALLOCATION
		*((int*)0x0) = 1;
#endif
		// NOTE: set a breakpoint here to find memory being freed before mem_heap is initialized
		free( p );
		return;
	}

	m = (debugMemory_t *) ( ( (SGF_Byte *) p ) - sizeof( debugMemory_t ) );

	if ( m->size < 0 ) {
		idLib::common->FatalError( "memory freed twice, first from %s, now from %s", idLib::sys->GetCallStackStr( m->callStack, MAX_CALLSTACK_DEPTH ), idLib::sys->GetCallStackCurStr( MAX_CALLSTACK_DEPTH ) );
	}

	Mem_UpdateFreeStats( m->size );

	if ( m->next ) {
		m->next->prev = m->prev;
	}
	if ( m->prev ) {
		m->prev->next = m->next;
	}
	else {
		mem_debugMemory = m->next;
	}

	m->fileName = fileName;
	m->lineNumber = lineNumber;
	m->frameNumber = idLib::frameNumber;
	m->size = -m->size;
	idLib::sys->GetCallStack( m->callStack, MAX_CALLSTACK_DEPTH );

	if ( align16 ) {
 		mem_heap->Free16( m );
	}
	else {
 		mem_heap->Free( m );
	}
}

/*
==================
Mem_Alloc
==================
*/
void *Mem_Alloc( const int size, const char *fileName, const int lineNumber ) {
	if ( !size ) {
		return NULL;
	}
	return Mem_AllocDebugMemory( size, fileName, lineNumber, false );
}

/*
==================
Mem_Free
==================
*/
void Mem_Free( void *ptr, const char *fileName, const int lineNumber ) {
	if ( !ptr ) {
		return;
	}
	Mem_FreeDebugMemory( ptr, fileName, lineNumber, false );
}

/*
==================
Mem_Alloc16
==================
*/
void *Mem_Alloc16( const int size, const char *fileName, const int lineNumber ) {
	if ( !size ) {
		return NULL;
	}
	void *mem = Mem_AllocDebugMemory( size, fileName, lineNumber, true );
	// make sure the memory is 16 SGF_Byte aligned
	assert( ( ((int)mem) & 15) == 0 );
	return mem;
}

/*
==================
Mem_Free16
==================
*/
void Mem_Free16( void *ptr, const char *fileName, const int lineNumber ) {
	if ( !ptr ) {
		return;
	}
	// make sure the memory is 16 SGF_Byte aligned
	assert( ( ((int)ptr) & 15) == 0 );
	Mem_FreeDebugMemory( ptr, fileName, lineNumber, true );
}

/*
==================
Mem_ClearedAlloc
==================
*/
void *Mem_ClearedAlloc( const int size, const char *fileName, const int lineNumber ) {
	void *mem = Mem_Alloc( size, fileName, lineNumber );
	SIMDProcessor->Memset( mem, 0, size );
	return mem;
}

/*
==================
Mem_CopyString
==================
*/
char *Mem_CopyString( const char *in, const char *fileName, const int lineNumber ) {
	char	*out;
	
	out = (char *)Mem_Alloc( strlen(in) + 1, fileName, lineNumber );
	strcpy( out, in );
	return out;
}

/*
==================
Mem_Init
==================
*/
void Mem_Init() {
	mem_heap = new CHeap;
}

/*
==================
Mem_Shutdown
==================
*/
void Mem_Shutdown() {

	if ( mem_leakName[0] != '\0' ) {
		Mem_DumpCompressed( va( "%s_leak_size.txt", mem_leakName ), MEMSORT_SIZE, 0, 0 );
		Mem_DumpCompressed( va( "%s_leak_location.txt", mem_leakName ), MEMSORT_LOCATION, 0, 0 );
		Mem_DumpCompressed( va( "%s_leak_cs1.txt", mem_leakName ), MEMSORT_CALLSTACK, 2, 0 );
	}

	CHeap *m = mem_heap;
	mem_heap = NULL;
	delete m;
}

/*
==================
Mem_EnableLeakTest
==================
*/
void Mem_EnableLeakTest( const char *name ) {
	CMyString::Copynz( mem_leakName, name, sizeof( mem_leakName ) );
}

#endif /* !ID_DEBUG_MEMORY */
} //end SGF