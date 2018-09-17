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

#ifndef __SGF_HEAP_H__
#define __SGF_HEAP_H__

#include "../SGF_Config.h"
#include "SGF_Util.h"
#include "../math/SGF_Simd.h"

#ifndef _WIN32
#include <sys/mman.h>
#else
#include <Windows.h>
#endif

namespace SGF{
	// pointer to SIMD processor
extern CSIMDProcessor *SIMDProcessor;

/*
===============================================================================

	Memory Management

	This is a replacement for the compiler heap code (i.e. "C" malloc() and
	free() calls). On average 2.5-3.0 times faster than MSVC malloc()/free().
	Worst case performance is 1.65 times faster and best case > 70 times.

===============================================================================
*/




typedef struct {
	int		num;
	int		minSize;
	int		maxSize;
	int		totalSize;
} memoryStats_t;


void		Mem_Init();
void		Mem_Shutdown();
void		Mem_EnableLeakTest( const char *name );
void		Mem_ClearFrameStats();
void		Mem_GetFrameStats( memoryStats_t &allocs, memoryStats_t &frees );
void		Mem_GetStats( memoryStats_t &stats );
void		Mem_Dump_f( const class CCMDLineArgs &args );
void		Mem_DumpCompressed_f( const class CCMDLineArgs &args );
void		Mem_AllocDefragBlock();


#ifndef ID_DEBUG_MEMORY

void *		Mem_Alloc( const int size );
void *		Mem_ClearedAlloc( const int size );
void		Mem_Free( void *ptr );
char *		Mem_CopyString( const char *in );
void *		Mem_Alloc16( const int size );
void		Mem_Free16( void *ptr );

#ifdef ID_REDIRECT_NEWDELETE

__inline void *operator new( size_t s ) {
	return Mem_Alloc( s );
}
__inline void operator delete( void *p ) {
	Mem_Free( p );
}
__inline void *operator new[]( size_t s ) {
	return Mem_Alloc( s );
}
__inline void operator delete[]( void *p ) {
	Mem_Free( p );
}

#endif

#else /* ID_DEBUG_MEMORY */

void *		Mem_Alloc( const int size, const char *fileName, const int lineNumber );
void *		Mem_ClearedAlloc( const int size, const char *fileName, const int lineNumber );
void		Mem_Free( void *ptr, const char *fileName, const int lineNumber );
char *		Mem_CopyString( const char *in, const char *fileName, const int lineNumber );
void *		Mem_Alloc16( const int size, const char *fileName, const int lineNumber );
void		Mem_Free16( void *ptr, const char *fileName, const int lineNumber );

#ifdef ID_REDIRECT_NEWDELETE

__inline void *operator new( size_t s, int t1, int t2, char *fileName, int lineNumber ) {
	return Mem_Alloc( s, fileName, lineNumber );
}
__inline void operator delete( void *p, int t1, int t2, char *fileName, int lineNumber ) {
	Mem_Free( p, fileName, lineNumber );
}
__inline void *operator new[]( size_t s, int t1, int t2, char *fileName, int lineNumber ) {
	return Mem_Alloc( s, fileName, lineNumber );
}
__inline void operator delete[]( void *p, int t1, int t2, char *fileName, int lineNumber ) {
	Mem_Free( p, fileName, lineNumber );
}
__inline void *operator new( size_t s ) {
	return Mem_Alloc( s, "", 0 );
}
__inline void operator delete( void *p ) {
	Mem_Free( p, "", 0 );
}
__inline void *operator new[]( size_t s ) {
	return Mem_Alloc( s, "", 0 );
}
__inline void operator delete[]( void *p ) {
	Mem_Free( p, "", 0 );
}

#define ID_DEBUG_NEW						new( 0, 0, __FILE__, __LINE__ )
#undef new
#define new									ID_DEBUG_NEW

#endif

#define		Mem_Alloc( size )				Mem_Alloc( size, __FILE__, __LINE__ )
#define		Mem_ClearedAlloc( size )		Mem_ClearedAlloc( size, __FILE__, __LINE__ )
#define		Mem_Free( ptr )					Mem_Free( ptr, __FILE__, __LINE__ )
#define		Mem_CopyString( s )				Mem_CopyString( s, __FILE__, __LINE__ )
#define		Mem_Alloc16( size )				Mem_Alloc16( size, __FILE__, __LINE__ )
#define		Mem_Free16( ptr )				Mem_Free16( ptr, __FILE__, __LINE__ )

#endif /* ID_DEBUG_MEMORY */


/*
===============================================================================

	Block based allocator for fixed size objects.

	All objects of the 'type' are properly constructed.
	However, the constructor is not called for re-used objects.

===============================================================================
*/

template<class type, int blockSize>
class CBlockAlloc {
public:
							CBlockAlloc();
							~CBlockAlloc();

	void					Shutdown();

	type *					Alloc();
	void					Free( type *element );

	int						GetTotalCount() const { return total; }
	int						GetAllocCount() const { return active; }
	int						GetFreeCount() const { return total - active; }

private:
	typedef struct element_s {
		struct element_s *	next;
		type				t;
	} element_t;
	typedef struct block_s {
		element_t			elements[blockSize];
		struct block_s *	next;
	} block_t;

	block_t *				blocks;
	element_t *				free;
	int						total;
	int						active;
};

template<class type, int blockSize>
CBlockAlloc<type,blockSize>::CBlockAlloc() {
	blocks = NULL;
	free = NULL;
	total = active = 0;
}

template<class type, int blockSize>
CBlockAlloc<type,blockSize>::~CBlockAlloc() {
	Shutdown();
}

template<class type, int blockSize>
type *CBlockAlloc<type,blockSize>::Alloc() {
	if ( !free ) {
		block_t *block = new block_t;
		block->next = blocks;
		blocks = block;
		for ( int i = 0; i < blockSize; i++ ) {
			block->elements[i].next = free;
			free = &block->elements[i];
		}
		total += blockSize;
	}
	active++;
	element_t *element = free;
	free = free->next;
	element->next = NULL;
	return &element->t;
}

template<class type, int blockSize>
void CBlockAlloc<type,blockSize>::Free( type *t ) {
	element_t *element = (element_t *)( ( (unsigned char *) t ) - ( (int) &((element_t *)0)->t ) );
	element->next = free;
	free = element;
	active--;
}

template<class type, int blockSize>
void CBlockAlloc<type,blockSize>::Shutdown() {
	while( blocks ) {
		block_t *block = blocks;
		blocks = blocks->next;
		delete block;
	}
	blocks = NULL;
	free = NULL;
	total = active = 0;
}

/*
==============================================================================

	Dynamic allocator, simple wrapper for normal allocations which can
	be interchanged with CDynamicBlockAlloc.

	No constructor is called for the 'type'.
	Allocated blocks are always 16 SGF_Byte aligned.

==============================================================================
*/

template<class type, int baseBlockSize, int minBlockSize>
class CDynamicAlloc {
public:
									CDynamicAlloc();
									~CDynamicAlloc();

	void							Init();
	void							Shutdown();
	void							SetFixedBlocks( int numBlocks ) {}
	void							SetLockMemory( bool lock ) {}
	void							FreeEmptyBaseBlocks() {}

	type *							Alloc( const int num );
	type *							Resize( type *ptr, const int num );
	void							Free( type *ptr );
	const char *					CheckMemory( const type *ptr ) const;

	int								GetNumBaseBlocks() const { return 0; }
	int								GetBaseBlockMemory() const { return 0; }
	int								GetNumUsedBlocks() const { return numUsedBlocks; }
	int								GetUsedBlockMemory() const { return usedBlockMemory; }
	int								GetNumFreeBlocks() const { return 0; }
	int								GetFreeBlockMemory() const { return 0; }
	int								GetNumEmptyBaseBlocks() const { return 0; }

private:
	int								numUsedBlocks;			// number of used blocks
	int								usedBlockMemory;		// total memory in used blocks

	int								numAllocs;
	int								numResizes;
	int								numFrees;

	void							Clear();
};

template<class type, int baseBlockSize, int minBlockSize>
CDynamicAlloc<type, baseBlockSize, minBlockSize>::CDynamicAlloc() {
	Clear();
}

template<class type, int baseBlockSize, int minBlockSize>
CDynamicAlloc<type, baseBlockSize, minBlockSize>::~CDynamicAlloc() {
	Shutdown();
}

template<class type, int baseBlockSize, int minBlockSize>
void CDynamicAlloc<type, baseBlockSize, minBlockSize>::Init() {
}

template<class type, int baseBlockSize, int minBlockSize>
void CDynamicAlloc<type, baseBlockSize, minBlockSize>::Shutdown() {
	Clear();
}

template<class type, int baseBlockSize, int minBlockSize>
type *CDynamicAlloc<type, baseBlockSize, minBlockSize>::Alloc( const int num ) {
	numAllocs++;
	if ( num <= 0 ) {
		return NULL;
	}
	numUsedBlocks++;
	usedBlockMemory += num * sizeof( type );
	return Mem_Alloc16( num * sizeof( type ) );
}

template<class type, int baseBlockSize, int minBlockSize>
type *CDynamicAlloc<type, baseBlockSize, minBlockSize>::Resize( type *ptr, const int num ) {

	numResizes++;

	if ( ptr == NULL ) {
		return Alloc( num );
	}

	if ( num <= 0 ) {
		Free( ptr );
		return NULL;
	}

	assert( 0 );
	return ptr;
}

template<class type, int baseBlockSize, int minBlockSize>
void CDynamicAlloc<type, baseBlockSize, minBlockSize>::Free( type *ptr ) {
	numFrees++;
	if ( ptr == NULL ) {
		return;
	}
	Mem_Free16( ptr );
}

template<class type, int baseBlockSize, int minBlockSize>
const char *CDynamicAlloc<type, baseBlockSize, minBlockSize>::CheckMemory( const type *ptr ) const {
	return NULL;
}

template<class type, int baseBlockSize, int minBlockSize>
void CDynamicAlloc<type, baseBlockSize, minBlockSize>::Clear() {
	numUsedBlocks = 0;
	usedBlockMemory = 0;
	numAllocs = 0;
	numResizes = 0;
	numFrees = 0;
}


/*
==============================================================================

	Fast dynamic block allocator.

	No constructor is called for the 'type'.
	Allocated blocks are always 16 SGF_Byte aligned.

==============================================================================
*/

#include "../structures/BTree.h"

//#define DYNAMIC_BLOCK_ALLOC_CHECK

template<class type>
class CDynamicBlock {
public:
	type *							GetMemory() const { return (type *)( ( (SGF_Byte *) this ) + sizeof( CDynamicBlock<type> ) ); }
	int								GetSize() const { return abs( size ); }
	void							SetSize( int s, bool isBaseBlock ) { size = isBaseBlock ? -s : s; }
	bool							IsBaseBlock() const { return ( size < 0 ); }

#ifdef DYNAMIC_BLOCK_ALLOC_CHECK
	int								id[3];
	void *							allocator;
#endif

	int								size;					// size in bytes of the block
	CDynamicBlock<type> *			prev;					// previous memory block
	CDynamicBlock<type> *			next;					// next memory block
	idBTreeNode<CDynamicBlock<type>,int> *node;			// node in the B-Tree with free blocks
};

template<class type, int baseBlockSize, int minBlockSize>
class CDynamicBlockAlloc {
public:
									CDynamicBlockAlloc();
									~CDynamicBlockAlloc();

	void							Init();
	void							Shutdown();
	void							SetFixedBlocks( int numBlocks );
	void							SetLockMemory( bool lock );
	void							FreeEmptyBaseBlocks();

	type *							Alloc( const int num );
	type *							Resize( type *ptr, const int num );
	void							Free( type *ptr );
	const char *					CheckMemory( const type *ptr ) const;

	int								GetNumBaseBlocks() const { return numBaseBlocks; }
	int								GetBaseBlockMemory() const { return baseBlockMemory; }
	int								GetNumUsedBlocks() const { return numUsedBlocks; }
	int								GetUsedBlockMemory() const { return usedBlockMemory; }
	int								GetNumFreeBlocks() const { return numFreeBlocks; }
	int								GetFreeBlockMemory() const { return freeBlockMemory; }
	int								GetNumEmptyBaseBlocks() const;

private:
	CDynamicBlock<type> *			firstBlock;				// first block in list in order of increasing address
	CDynamicBlock<type> *			lastBlock;				// last block in list in order of increasing address
	idBTree<CDynamicBlock<type>,int,4>freeTree;			// B-Tree with free memory blocks
	bool							allowAllocs;			// allow base block allocations
	bool							lockMemory;				// lock memory so it cannot get swapped out

#ifdef DYNAMIC_BLOCK_ALLOC_CHECK
	int								blockId[3];
#endif

	int								numBaseBlocks;			// number of base blocks
	int								baseBlockMemory;		// total memory in base blocks
	int								numUsedBlocks;			// number of used blocks
	int								usedBlockMemory;		// total memory in used blocks
	int								numFreeBlocks;			// number of free blocks
	int								freeBlockMemory;		// total memory in free blocks

	int								numAllocs;
	int								numResizes;
	int								numFrees;

	void							Clear();
	CDynamicBlock<type> *			AllocInternal( const int num );
	CDynamicBlock<type> *			ResizeInternal( CDynamicBlock<type> *block, const int num );
	void							FreeInternal( CDynamicBlock<type> *block );
	void							LinkFreeInternal( CDynamicBlock<type> *block );
	void							UnlinkFreeInternal( CDynamicBlock<type> *block );
	void							CheckMemory() const;
};

template<class type, int baseBlockSize, int minBlockSize>
CDynamicBlockAlloc<type, baseBlockSize, minBlockSize>::CDynamicBlockAlloc() {
	Clear();
}

template<class type, int baseBlockSize, int minBlockSize>
CDynamicBlockAlloc<type, baseBlockSize, minBlockSize>::~CDynamicBlockAlloc() {
	Shutdown();
}

template<class type, int baseBlockSize, int minBlockSize>
void CDynamicBlockAlloc<type, baseBlockSize, minBlockSize>::Init() {
	freeTree.Init();
}

template<class type, int baseBlockSize, int minBlockSize>
void CDynamicBlockAlloc<type, baseBlockSize, minBlockSize>::Shutdown() {
	CDynamicBlock<type> *block;

	for ( block = firstBlock; block != NULL; block = block->next ) {
		if ( block->node == NULL ) {
			FreeInternal( block );
		}
	}

	for ( block = firstBlock; block != NULL; block = firstBlock ) {
		firstBlock = block->next;
		assert( block->IsBaseBlock() );
		if ( lockMemory ) {
			Sys_UnlockMemory( block, block->GetSize() + (int)sizeof( CDynamicBlock<type> ) );
		}
		Mem_Free16( block );
	}

	freeTree.Shutdown();

	Clear();
}

template<class type, int baseBlockSize, int minBlockSize>
void CDynamicBlockAlloc<type, baseBlockSize, minBlockSize>::SetFixedBlocks( int numBlocks ) {
	CDynamicBlock<type> *block;

	for ( int i = numBaseBlocks; i < numBlocks; i++ ) {
		block = ( CDynamicBlock<type> * ) Mem_Alloc16( baseBlockSize );
		if ( lockMemory ) {
			Sys_LockMemory( block, baseBlockSize );
		}
#ifdef DYNAMIC_BLOCK_ALLOC_CHECK
		memcpy( block->id, blockId, sizeof( block->id ) );
		block->allocator = (void*)this;
#endif
		block->SetSize( baseBlockSize - (int)sizeof( CDynamicBlock<type> ), true );
		block->next = NULL;
		block->prev = lastBlock;
		if ( lastBlock ) {
			lastBlock->next = block;
		} else {
			firstBlock = block;
		}
		lastBlock = block;
		block->node = NULL;

		FreeInternal( block );

		numBaseBlocks++;
		baseBlockMemory += baseBlockSize;
	}

	allowAllocs = false;
}

template<class type, int baseBlockSize, int minBlockSize>
void CDynamicBlockAlloc<type, baseBlockSize, minBlockSize>::SetLockMemory( bool lock ) {
	lockMemory = lock;
}

template<class type, int baseBlockSize, int minBlockSize>
void CDynamicBlockAlloc<type, baseBlockSize, minBlockSize>::FreeEmptyBaseBlocks() {
	CDynamicBlock<type> *block, *next;

	for ( block = firstBlock; block != NULL; block = next ) {
		next = block->next;

		if ( block->IsBaseBlock() && block->node != NULL && ( next == NULL || next->IsBaseBlock() ) ) {
			UnlinkFreeInternal( block );
			if ( block->prev ) {
				block->prev->next = block->next;
			} else {
				firstBlock = block->next;
			}
			if ( block->next ) {
				block->next->prev = block->prev;
			} else {
				lastBlock = block->prev;
			}
			if ( lockMemory ) {
				Sys_UnlockMemory( block, block->GetSize() + (int)sizeof( CDynamicBlock<type> ) );
			}
			numBaseBlocks--;
			baseBlockMemory -= block->GetSize() + (int)sizeof( CDynamicBlock<type> );
			Mem_Free16( block );
		}
	}

#ifdef DYNAMIC_BLOCK_ALLOC_CHECK
	CheckMemory();
#endif
}

template<class type, int baseBlockSize, int minBlockSize>
int CDynamicBlockAlloc<type, baseBlockSize, minBlockSize>::GetNumEmptyBaseBlocks() const {
	int numEmptyBaseBlocks;
	CDynamicBlock<type> *block;

	numEmptyBaseBlocks = 0;
	for ( block = firstBlock; block != NULL; block = block->next ) {
		if ( block->IsBaseBlock() && block->node != NULL && ( block->next == NULL || block->next->IsBaseBlock() ) ) {
			numEmptyBaseBlocks++;
		}
	}
	return numEmptyBaseBlocks;
}

template<class type, int baseBlockSize, int minBlockSize>
type *CDynamicBlockAlloc<type, baseBlockSize, minBlockSize>::Alloc( const int num ) {
	CDynamicBlock<type> *block;

	numAllocs++;

	if ( num <= 0 ) {
		return NULL;
	}

	block = AllocInternal( num );
	if ( block == NULL ) {
		return NULL;
	}
	block = ResizeInternal( block, num );
	if ( block == NULL ) {
		return NULL;
	}

#ifdef DYNAMIC_BLOCK_ALLOC_CHECK
	CheckMemory();
#endif

	numUsedBlocks++;
	usedBlockMemory += block->GetSize();

	return block->GetMemory();
}

template<class type, int baseBlockSize, int minBlockSize>
type *CDynamicBlockAlloc<type, baseBlockSize, minBlockSize>::Resize( type *ptr, const int num ) {

	numResizes++;

	if ( ptr == NULL ) {
		return Alloc( num );
	}

	if ( num <= 0 ) {
		Free( ptr );
		return NULL;
	}

	CDynamicBlock<type> *block = ( CDynamicBlock<type> * ) ( ( (SGF_Byte *) ptr ) - (int)sizeof( CDynamicBlock<type> ) );

	usedBlockMemory -= block->GetSize();

	block = ResizeInternal( block, num );
	if ( block == NULL ) {
		return NULL;
	}

#ifdef DYNAMIC_BLOCK_ALLOC_CHECK
	CheckMemory();
#endif

	usedBlockMemory += block->GetSize();

	return block->GetMemory();
}

template<class type, int baseBlockSize, int minBlockSize>
void CDynamicBlockAlloc<type, baseBlockSize, minBlockSize>::Free( type *ptr ) {

	numFrees++;

	if ( ptr == NULL ) {
		return;
	}

	CDynamicBlock<type> *block = ( CDynamicBlock<type> * ) ( ( (SGF_Byte *) ptr ) - (int)sizeof( CDynamicBlock<type> ) );

	numUsedBlocks--;
	usedBlockMemory -= block->GetSize();

	FreeInternal( block );

#ifdef DYNAMIC_BLOCK_ALLOC_CHECK
	CheckMemory();
#endif
}

template<class type, int baseBlockSize, int minBlockSize>
const char *CDynamicBlockAlloc<type, baseBlockSize, minBlockSize>::CheckMemory( const type *ptr ) const {
	CDynamicBlock<type> *block;

	if ( ptr == NULL ) {
		return NULL;
	}

	block = ( CDynamicBlock<type> * ) ( ( (SGF_Byte *) ptr ) - (int)sizeof( CDynamicBlock<type> ) );

	if ( block->node != NULL ) {
		return "memory has been freed";
	}

#ifdef DYNAMIC_BLOCK_ALLOC_CHECK
	if ( block->id[0] != 0x11111111 || block->id[1] != 0x22222222 || block->id[2] != 0x33333333 ) {
		return "memory has invalid id";
	}
	if ( block->allocator != (void*)this ) {
		return "memory was allocated with different allocator";
	}
#endif

	/* base blocks can be larger than baseBlockSize which can cause this code to fail
	CDynamicBlock<type> *base;
	for ( base = firstBlock; base != NULL; base = base->next ) {
		if ( base->IsBaseBlock() ) {
			if ( ((int)block) >= ((int)base) && ((int)block) < ((int)base) + baseBlockSize ) {
				break;
			}
		}
	}
	if ( base == NULL ) {
		return "no base block found for memory";
	}
	*/

	return NULL;
}

template<class type, int baseBlockSize, int minBlockSize>
void CDynamicBlockAlloc<type, baseBlockSize, minBlockSize>::Clear() {
	firstBlock = lastBlock = NULL;
	allowAllocs = true;
	lockMemory = false;
	numBaseBlocks = 0;
	baseBlockMemory = 0;
	numUsedBlocks = 0;
	usedBlockMemory = 0;
	numFreeBlocks = 0;
	freeBlockMemory = 0;
	numAllocs = 0;
	numResizes = 0;
	numFrees = 0;

#ifdef DYNAMIC_BLOCK_ALLOC_CHECK
	blockId[0] = 0x11111111;
	blockId[1] = 0x22222222;
	blockId[2] = 0x33333333;
#endif
}

template<class type, int baseBlockSize, int minBlockSize>
CDynamicBlock<type> *CDynamicBlockAlloc<type, baseBlockSize, minBlockSize>::AllocInternal( const int num ) {
	CDynamicBlock<type> *block;
	int alignedBytes = ( num * sizeof( type ) + 15 ) & ~15;

	block = freeTree.FindSmallestLargerEqual( alignedBytes );
	if ( block != NULL ) {
		UnlinkFreeInternal( block );
	} else if ( allowAllocs ) {
		int allocSize = MAX( baseBlockSize, alignedBytes + (int)sizeof( CDynamicBlock<type> ) );
		block = ( CDynamicBlock<type> * ) Mem_Alloc16( allocSize );
		if ( lockMemory ) {
			Sys_LockMemory( block, baseBlockSize );
		}
#ifdef DYNAMIC_BLOCK_ALLOC_CHECK
		memcpy( block->id, blockId, sizeof( block->id ) );
		block->allocator = (void*)this;
#endif
		block->SetSize( allocSize - (int)sizeof( CDynamicBlock<type> ), true );
		block->next = NULL;
		block->prev = lastBlock;
		if ( lastBlock ) {
			lastBlock->next = block;
		} else {
			firstBlock = block;
		}
		lastBlock = block;
		block->node = NULL;

		numBaseBlocks++;
		baseBlockMemory += allocSize;
	}

	return block;
}

template<class type, int baseBlockSize, int minBlockSize>
CDynamicBlock<type> *CDynamicBlockAlloc<type, baseBlockSize, minBlockSize>::ResizeInternal( CDynamicBlock<type> *block, const int num ) {
	int alignedBytes = ( num * sizeof( type ) + 15 ) & ~15;

#ifdef DYNAMIC_BLOCK_ALLOC_CHECK
	assert( block->id[0] == 0x11111111 && block->id[1] == 0x22222222 && block->id[2] == 0x33333333 && block->allocator == (void*)this );
#endif

	// if the new size is larger
	if ( alignedBytes > block->GetSize() ) {

		CDynamicBlock<type> *nextBlock = block->next;

		// try to annexate the next block if it's free
		if ( nextBlock && !nextBlock->IsBaseBlock() && nextBlock->node != NULL &&
				block->GetSize() + (int)sizeof( CDynamicBlock<type> ) + nextBlock->GetSize() >= alignedBytes ) {

			UnlinkFreeInternal( nextBlock );
			block->SetSize( block->GetSize() + (int)sizeof( CDynamicBlock<type> ) + nextBlock->GetSize(), block->IsBaseBlock() );
			block->next = nextBlock->next;
			if ( nextBlock->next ) {
				nextBlock->next->prev = block;
			} else {
				lastBlock = block;
			}
		} else {
			// allocate a new block and copy
			CDynamicBlock<type> *oldBlock = block;
			block = AllocInternal( num );
			if ( block == NULL ) {
				return NULL;
			}
			memcpy( block->GetMemory(), oldBlock->GetMemory(), oldBlock->GetSize() );
			FreeInternal( oldBlock );
		}
	}

	// if the unused space at the end of this block is large enough to hold a block with at least one element
	if (( block->GetSize() - alignedBytes - (int)sizeof( CDynamicBlock<type> )) < (MAX( minBlockSize, (int)sizeof( type ) )) ) {
		return block;
	}

	CDynamicBlock<type> *newBlock;

	newBlock = ( CDynamicBlock<type> * ) ( ( (SGF_Byte *) block ) + (int)sizeof( CDynamicBlock<type> ) + alignedBytes );
#ifdef DYNAMIC_BLOCK_ALLOC_CHECK
	memcpy( newBlock->id, blockId, sizeof( newBlock->id ) );
	newBlock->allocator = (void*)this;
#endif
	newBlock->SetSize( block->GetSize() - alignedBytes - (int)sizeof( CDynamicBlock<type> ), false );
	newBlock->next = block->next;
	newBlock->prev = block;
	if ( newBlock->next ) {
		newBlock->next->prev = newBlock;
	} else {
		lastBlock = newBlock;
	}
	newBlock->node = NULL;
	block->next = newBlock;
	block->SetSize( alignedBytes, block->IsBaseBlock() );

	FreeInternal( newBlock );

	return block;
}

template<class type, int baseBlockSize, int minBlockSize>
void CDynamicBlockAlloc<type, baseBlockSize, minBlockSize>::FreeInternal( CDynamicBlock<type> *block ) {

	assert( block->node == NULL );

#ifdef DYNAMIC_BLOCK_ALLOC_CHECK
	assert( block->id[0] == 0x11111111 && block->id[1] == 0x22222222 && block->id[2] == 0x33333333 && block->allocator == (void*)this );
#endif

	// try to merge with a next free block
	CDynamicBlock<type> *nextBlock = block->next;
	if ( nextBlock && !nextBlock->IsBaseBlock() && nextBlock->node != NULL ) {
		UnlinkFreeInternal( nextBlock );
		block->SetSize( block->GetSize() + (int)sizeof( CDynamicBlock<type> ) + nextBlock->GetSize(), block->IsBaseBlock() );
		block->next = nextBlock->next;
		if ( nextBlock->next ) {
			nextBlock->next->prev = block;
		} else {
			lastBlock = block;
		}
	}

	// try to merge with a previous free block
	CDynamicBlock<type> *prevBlock = block->prev;
	if ( prevBlock && !block->IsBaseBlock() && prevBlock->node != NULL ) {
		UnlinkFreeInternal( prevBlock );
		prevBlock->SetSize( prevBlock->GetSize() + (int)sizeof( CDynamicBlock<type> ) + block->GetSize(), prevBlock->IsBaseBlock() );
		prevBlock->next = block->next;
		if ( block->next ) {
			block->next->prev = prevBlock;
		} else {
			lastBlock = prevBlock;
		}
		LinkFreeInternal( prevBlock );
	} else {
		LinkFreeInternal( block );
	}
}

template<class type, int baseBlockSize, int minBlockSize>
SGF_INLINE_FORCED void CDynamicBlockAlloc<type, baseBlockSize, minBlockSize>::LinkFreeInternal( CDynamicBlock<type> *block ) {
	block->node = freeTree.Add( block, block->GetSize() );
	numFreeBlocks++;
	freeBlockMemory += block->GetSize();
}

template<class type, int baseBlockSize, int minBlockSize>
SGF_INLINE_FORCED void CDynamicBlockAlloc<type, baseBlockSize, minBlockSize>::UnlinkFreeInternal( CDynamicBlock<type> *block ) {
	freeTree.Remove( block->node );
	block->node = NULL;
	numFreeBlocks--;
	freeBlockMemory -= block->GetSize();
}

template<class type, int baseBlockSize, int minBlockSize>
void CDynamicBlockAlloc<type, baseBlockSize, minBlockSize>::CheckMemory() const {
	CDynamicBlock<type> *block;

	for ( block = firstBlock; block != NULL; block = block->next ) {
		// make sure the block is properly linked
		if ( block->prev == NULL ) {
			assert( firstBlock == block );
		} else {
			assert( block->prev->next == block );
		}
		if ( block->next == NULL ) {
			assert( lastBlock == block );
		} else {
			assert( block->next->prev == block );
		}
	}
}
} //end SGF
#endif /* !__SGF_HEAP_H__ */
