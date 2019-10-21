#ifndef GBAXX_BIT_CAST_HPP
#define GBAXX_BIT_CAST_HPP

#include <cstring>
#include <type_traits>

namespace gba {

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wclass-memaccess"

template <class To, class From>
auto bit_cast( const From &src ) noexcept -> typename std::enable_if<( sizeof( To ) == sizeof( From ) ) && std::is_trivially_copyable<From>::value && std::is_trivial<To>::value, To>::type {
	To dst;
	std::memcpy( &dst, &src, sizeof( To ) );
	return dst;
}

#pragma GCC diagnostic pop

} // gba

#endif // define GBAXX_BIT_CAST_HPP
