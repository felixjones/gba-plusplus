#ifndef GBAXX_IWRAM_ALLOCATOR_HPP
#define GBAXX_IWRAM_ALLOCATOR_HPP

#include <cstddef>

#include <gba/int.hpp>

namespace gba {

void * iwram_malloc( std::size_t n );
void iwram_free( void * p );

template <class T>
struct iwram_allocator {

	using value_type = T;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using propagate_on_container_move_assignment = std::true_type;
	using is_always_equal = std::true_type;

	constexpr iwram_allocator() noexcept {}
	constexpr iwram_allocator( const iwram_allocator& other ) noexcept {}

	template <class U>
	constexpr iwram_allocator( const iwram_allocator<U>& other ) noexcept {}

	~iwram_allocator() {}

	[[nodiscard]]
	constexpr T * allocate( std::size_t n ) {
		return reinterpret_cast<T *>( iwram_malloc( n ) );
	}

	constexpr void deallocate( T * p, std::size_t n ) {
		iwram_free( p );
	}

};

template <class T1, class T2>
constexpr bool operator==( const iwram_allocator<T1>& lhs, const iwram_allocator<T2>& rhs ) noexcept {
	return true;
}

} // gba

#endif // define GBAXX_IWRAM_ALLOCATOR_HPP
