#ifndef GBAXX_TINY_ALLOC_HPP
#define GBAXX_TINY_ALLOC_HPP

#include <cstddef>

#include <gba/int.hpp>

namespace gba::util {

// C++ implementation of tiny alloc
// https://github.com/thi-ng/tinyalloc
class tiny_alloc {
public:
	tiny_alloc( uintptr base, uintptr limit, const std::size_t heapBlocks, const std::size_t splitThresh, const std::size_t alignment );

	void	free( void * p );

	[[nodiscard]]
	void *	alloc( std::size_t num );

	[[nodiscard]]
	void *	calloc( std::size_t num, std::size_t size );

	std::size_t	num_free() const;
	std::size_t	num_used() const;
	std::size_t	num_fresh() const;

	bool check() const {
		return m_maxBlocks == ( num_free() + num_used() + num_fresh() );
	}

private:
	void			insert_block( struct block * b );
	void			compact();

	[[nodiscard]]
	struct block *	alloc_block( std::size_t num );

	std::size_t		count_blocks( struct block * ptr ) const;
	void			release_blocks( struct block * scan, struct block * to );

	struct heap *	m_heap;
	uintptr			m_limit;
	std::size_t		m_splitThresh;
	std::size_t		m_alignment;
	std::size_t		m_maxBlocks;

};

} // gba::util

#endif // define GBAXX_TINY_ALLOC_HPP
