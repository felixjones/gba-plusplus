#ifndef GBAXX_VIDEO_ALLOCATOR_HPP
#define GBAXX_VIDEO_ALLOCATOR_HPP

#include <cstddef>

namespace gba {

template <class T>
struct video_allocator {

	using value_type = T;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using propagate_on_container_move_assignment = std::true_type;
	using is_always_equal = std::true_type;

	constexpr video_allocator() noexcept {}
	constexpr video_allocator( const video_allocator& other ) noexcept {}

	template< class U >
	constexpr video_allocator( const video_allocator<U>& other ) noexcept {}

	constexpr ~video_allocator() {}

	[[nodiscard]]
	constexpr T * allocate( std::size_t n ) {
		return nullptr;
	}

	constexpr void deallocate( T * p, std::size_t n ) {

	}

};

template <class T1, class T2>
constexpr bool operator==( const video_allocator<T1>& lhs, const video_allocator<T2>& rhs ) noexcept {
	return true;
}

} // gba

#endif // define GBAXX_VIDEO_ALLOCATOR_HPP