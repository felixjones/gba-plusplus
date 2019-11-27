#include <gba/tiny_alloc.hpp>

#include <cstring>
#include <gba/bit_cast.hpp>

using namespace gba;
using namespace util;

namespace gba::util {

struct block {
	void *			addr;
	struct block *	next;
	std::size_t		size;
};

struct heap {
	block *		free;   // first free block
	block *		used;   // first used block
	block *		fresh;  // first available blank block
	std::size_t top;    // top free addr
};

} // gba::util

tiny_alloc::tiny_alloc( uintptr base, uintptr limit, const std::size_t heapBlocks, const std::size_t splitThresh, const std::size_t alignment ) {
	m_heap = bit_cast<heap *>( base );
	m_limit = limit;
	m_splitThresh = splitThresh;
	m_alignment = alignment;
	m_maxBlocks = heapBlocks;

	m_heap->free = nullptr;
	m_heap->used = nullptr;
	m_heap->fresh = bit_cast<block *>( m_heap + 1 );
	m_heap->top = bit_cast<std::size_t>( m_heap->fresh + heapBlocks );

	auto b = m_heap->fresh;
	auto ii = heapBlocks - 1;
	while ( ii-- ) {
		b->next = b + 1;
		++b;
	}

	b->next = nullptr;
}

void tiny_alloc::free( void * p ) {
	if ( !p ) return;

	auto b = m_heap->used;
	block * prev = nullptr;
	while ( b ) {
		if ( p == b->addr ) {
			if ( prev ) {
				prev->next = b->next;
			} else {
				m_heap->used = b->next;
			}

			insert_block( b );
			compact();

			return;
		}

		prev = b;
		b = b->next;
	}
}

void * tiny_alloc::alloc( std::size_t num ) {
	const auto b = alloc_block( num );
	if ( b ) {
		return b->addr;
	}
	return nullptr;
}

void * tiny_alloc::calloc( std::size_t num, std::size_t size ) {
	num *= size;
	const auto b = alloc_block( num );
	if ( b ) {
		std::memset( b->addr, 0, num );
		return b->addr;
	}
	return nullptr;
}

std::size_t tiny_alloc::num_free() const {
	return count_blocks( m_heap->free );
}

std::size_t tiny_alloc::num_used() const {
	return count_blocks( m_heap->used );
}

std::size_t tiny_alloc::num_fresh() const {
	return count_blocks( m_heap->fresh );
}

void tiny_alloc::insert_block( block * b ) {
	auto ptr = m_heap->free;
	block * prev = nullptr;

	while ( ptr ) {
		if ( ( std::size_t )b->addr <= ( size_t )ptr->addr ) {
			break;
		}

		prev = ptr;
		ptr = ptr->next;
	}

	if ( prev ) {
		prev->next = b;
	} else {
		m_heap->free = b;
	}

	b->next = ptr;
}

void tiny_alloc::compact() {
	auto ptr = m_heap->free;
	block * prev;
	block * scan;

	while ( ptr ) {
		prev = ptr;
		scan = ptr->next;

		while ( scan && ( size_t )prev->addr + prev->size == ( size_t )scan->addr ) {
			prev = scan;
			scan = scan->next;
		}

		if ( prev != ptr ) {
			const auto new_size = ( size_t )prev->addr - ( size_t )ptr->addr + prev->size;

			ptr->size = new_size;
			auto next = prev->next;
			// make merged blocks available
			release_blocks( ptr->next, prev->next );
			// relink
			ptr->next = next;
		}

		ptr = ptr->next;
	}
}

block * tiny_alloc::alloc_block( std::size_t num ) {
	auto ptr = m_heap->free;
	block * prev = nullptr;
	const auto top = m_heap->top;

	num = ( num + m_alignment - 1 ) & -m_alignment;
	while ( ptr ) {
		const auto isTop = ( ( size_t )ptr->addr + ptr->size >= top ) && ( ( size_t )ptr->addr + num <= m_limit );

		if ( isTop || ptr->size >= num ) {
			if ( prev ) {
				prev->next = ptr->next;
			} else {
				m_heap->free = ptr->next;
			}

			ptr->next = m_heap->used;
			m_heap->used = ptr;

			if ( isTop ) {
				ptr->size = num;
				m_heap->top = ( size_t )ptr->addr + num;
			} else if ( m_heap->fresh ) {
				const auto excess = ptr->size - num;

				if ( excess >= m_splitThresh ) {
					ptr->size = num;
					const auto split = m_heap->fresh;
					m_heap->fresh = split->next;
					split->addr = ( void * )( ( size_t )ptr->addr + num );

					split->size = excess;
					insert_block( split );

					compact();
				}
			}

			return ptr;
		}

		prev = ptr;
		ptr = ptr->next;
	}

	// no matching free blocks
	// see if any other blocks available
	const auto newTop = top + num;
	if ( m_heap->fresh && newTop <= m_limit ) {
		ptr = m_heap->fresh;
		m_heap->fresh = ptr->next;
		ptr->addr = ( void * )top;
		ptr->next = m_heap->used;
		ptr->size = num;
		m_heap->used = ptr;
		m_heap->top = newTop;

		return ptr;
	}

	return nullptr;
}

std::size_t tiny_alloc::count_blocks( block * ptr ) const {
	std::size_t num = 0;
	while ( ptr ) {
		num++;
		ptr = ptr->next;
	}
	return num;
}

void tiny_alloc::release_blocks( block * scan, block * to ) {
	block * scanNext;
	while ( scan != to ) {
		scanNext = scan->next;
		scan->next = m_heap->fresh;
		m_heap->fresh = scan;
		scan->addr = 0;
		scan->size = 0;
		scan = scanNext;
	}
}
