#ifndef GBAXX_MATH_HPP
#define GBAXX_MATH_HPP

#include <type_traits>

#include <gba/int.hpp>

namespace gba {
namespace math {

template <typename Type>
constexpr auto ceil2( Type n ) {
	--n;
	if constexpr ( sizeof( n ) == 8 ) {
		n = __builtin_clzll( n );
		return 1 << ( 64 - n );
	} else {
		n = __builtin_clz( n );
		return 1 << ( 32 - n );
	}
}

template <typename Type>
constexpr auto floor2( Type n ) {
	if constexpr ( sizeof( n ) == 8 ) {
		n = __builtin_clzll( n );
		return 1 << ( 63 - n );
	} else {
		n = __builtin_clz( n );
		return 1 << ( 31 - n );
	}
}

template <typename Type>
constexpr auto rotl( Type n, unsigned s ) {
	typename std::make_unsigned<Type>::type un = n;
	return ( un << s ) | ( un >> ( ( sizeof( un ) * 8 ) - s ) );
}

template <typename Type>
constexpr auto rotr( Type n, unsigned s ) {
	typename std::make_unsigned<Type>::type un = n;
	return ( un >> s ) | ( un << ( ( sizeof( un ) * 8 ) - s ) );
}

template <typename Type>
constexpr auto ctz( Type n ) {
	if constexpr ( sizeof( n ) == 8 ) {
		return __builtin_ctzll( n );
	} else {
		return __builtin_ctz( n );
	}
}

template <typename Type>
constexpr auto clz( Type n ) {
	if constexpr ( sizeof( n ) == 8 ) {
		return __builtin_clzll( n );
	} else {
		return __builtin_clz( n );
	}
}

} // math
} // gba

#endif // define GBAXX_MATH_HPP