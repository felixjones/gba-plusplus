#ifndef GBAXX_ALLOCATOR_HPP
#define GBAXX_ALLOCATOR_HPP

#include <cstddef>
#include <cstring>

#if defined( __EXCEPTIONS )
#include <new>
#endif

#include <gba/int.hpp>
#include <gba/packed_ptr.hpp>

namespace gba::util {

// C++ implementation of tiny alloc
// https://github.com/thi-ng/tinyalloc
template <std::size_t MaxBlocks, std::size_t SplitThreshold, std::size_t Alignment>
class allocator {
private:
	struct block {
		uintptr			addr;
		struct block *	next;
		std::size_t		size;
	};

public:
	allocator( uintptr base, uintptr limit ) noexcept : m_base( base ), m_limit( limit ), m_free( nullptr ), m_used( nullptr ), m_fresh( &m_blocks[0] ), m_top( base ), m_blocks {} {
		auto b = &m_blocks[0];
		auto ii = MaxBlocks;
		while ( ii-- ) {
			b->next = b + 1;
			++b;
		}
	}

	allocator( const allocator& other ) = delete;
	
	[[nodiscard]]
	void * malloc( std::size_t size ) {
		const auto b = alloc_block( size );
		if ( b ) {
#if defined( _DEBUG )
			std::memset( ( void * )b->addr, 0xCD, size );
#endif
			return ( void * )b->addr;
		}
#if defined( __EXCEPTIONS )
		throw std::bad_alloc();
#endif
		return nullptr;
	}

	[[nodiscard]]
	void * calloc( std::size_t num, std::size_t size ) {
		size *= num;
		const auto b = alloc_block( size );
		if ( b ) {
			std::memset( ( void * )b->addr, 0, size );
			return ( void * )b->addr;
		}
#if defined( __EXCEPTIONS )
		throw std::bad_alloc();
#endif
		return nullptr;
	}

	[[nodiscard]]
	void * realloc( void * ptr, std::size_t size ) {
		const auto newPtr = malloc( size );
		if ( !newPtr ) {
#if defined( __EXCEPTIONS )
			throw std::bad_alloc();
#endif
			return nullptr;
		}
		if ( !ptr ) return newPtr;

		auto b = m_used;
		block * prev = nullptr;
		while ( b ) {
			if ( ( uintptr )ptr == b->addr ) {
				std::memcpy( newPtr, ptr, b->size );
#if defined( _DEBUG )
				std::memset( ptr, 0xDD, b->size );
#endif

				if ( prev ) {
					prev->next = b->next;
				} else {
					m_used = b->next;
				}

				insert_block( b );
				compact();

				return newPtr;
			}

			prev = b;
			b = b->next;
		}

		free( newPtr );
#if defined( __EXCEPTIONS )
		throw std::bad_alloc();
#endif
		return nullptr;
	}

	void free( void * ptr ) {
		if ( !ptr ) return;

		auto b = m_used;
		block * prev = nullptr;
		while ( b ) {
			if ( ( uintptr )ptr == b->addr ) {
#if defined( _DEBUG )
				std::memset( ptr, 0xDD, b->size );
#endif
				if ( prev ) {
					prev->next = b->next;
				} else {
					m_used = b->next;
				}

				insert_block( b );
				compact();

				return;
			}

			prev = b;
			b = b->next;
		}
	}

protected:
	void release_blocks( block * scan, block * to ) {
		while ( scan != to ) {
			const auto scanNext = scan->next;
			scan->next = m_fresh;
			m_fresh = scan;
			scan->addr = 0;
			scan->size = 0;
			scan = scanNext;
		}
	}

	void insert_block( block * b ) {
		auto ptr = m_free;
		block * prev = nullptr;

		while ( ptr ) {
			if ( b->addr <= ptr->addr ) {
				break;
			}

			prev = ptr;
			ptr = ptr->next;
		}

		if ( prev ) {
			prev->next = b;
		} else {
			m_free = b;
		}

		b->next = ptr;
	}

	void compact() {
		auto ptr = m_free;

		while ( ptr ) {
			auto prev = ptr;
			auto scan = ptr->next;

			while ( scan && ( prev->addr + prev->size ) == scan->addr ) {
				prev = scan;
				scan = scan->next;
			}

			if ( prev != ptr ) {
				const auto new_size = prev->addr - ptr->addr + prev->size;

				ptr->size = new_size;
				const auto next = prev->next;
				// make merged blocks available
				release_blocks( ptr->next, prev->next );
				// relink
				ptr->next = next;
			}

			ptr = ptr->next;
		}
	}

	[[gnu::noinline]]
	block * alloc_block( std::size_t num ) {
		// align
		num = ( num + Alignment - 1 ) & -Alignment;

		auto ptr = m_free;
		block * prev = nullptr;
		const auto top = m_top;

		while ( ptr ) {
			const auto isTop = ( ptr->addr + ptr->size >= top ) && ( ptr->addr + num <= m_limit );

			if ( isTop || ptr->size >= num ) {
				if ( prev ) {
					prev->next = ptr->next;
				} else {
					m_free = ptr->next;
				}

				ptr->next = m_used;
				m_used = ptr;

				if ( isTop ) {
					ptr->size = num;
					m_top = ptr->addr + num;
				} else if ( m_fresh ) {
					const auto excess = ptr->size - num;

					if ( excess >= SplitThreshold ) {
						ptr->size = num;
						const auto split = m_fresh;
						m_fresh = split->next;
						split->addr = ptr->addr + num;

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
		if ( m_fresh && newTop <= m_limit ) {
			ptr = m_fresh;
			m_fresh = ptr->next;
			ptr->addr = top;
			ptr->next = m_used;
			ptr->size = num;
			m_used = ptr;
			m_top = newTop;

			return ptr;
		}

		return nullptr;
	}

private:
	const uintptr	m_base;
	const uintptr	m_limit;

	block *	m_free;
	block *	m_used;
	block *	m_fresh;
	uintptr	m_top;
	block	m_blocks[MaxBlocks];
	
};

} // gba::util

#endif // define GBAXX_ALLOCATOR_HPP
