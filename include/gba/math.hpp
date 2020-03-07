#ifndef GBAXX_MATH_HPP
#define GBAXX_MATH_HPP

#include <type_traits>

#include <gba/int.hpp>

namespace gba {
namespace math {

// Count trailing zeros
template <typename Type>
constexpr typename std::enable_if<std::is_integral<Type>::value && sizeof( Type ) == 8, int>::type
ctz( Type n ) noexcept {
	return __builtin_ctzll( n );
}

template <typename Type>
constexpr typename std::enable_if<std::is_integral<Type>::value && sizeof( Type ) < 8, int>::type
ctz( Type n ) noexcept {
	return __builtin_ctz( n );
}

// Count leading zeros
template <typename Type>
constexpr typename std::enable_if<std::is_integral<Type>::value && sizeof( Type ) == 8, int>::type
clz( Type n ) noexcept {
	return __builtin_clzll( n );
}

template <typename Type>
constexpr typename std::enable_if<std::is_integral<Type>::value && sizeof( Type ) < 8, int>::type
clz( Type n ) noexcept {
	return __builtin_clz( n );
}

template <typename Type>
constexpr typename std::enable_if<std::is_integral<Type>::value && sizeof( Type ) == 8, Type>::type
ceil2( Type n ) noexcept {
	--n;
	n = __builtin_clzll( n );
	return 1 << ( 64 - n );
}

template <typename Type>
constexpr typename std::enable_if<std::is_integral<Type>::value && sizeof( Type ) < 8, Type>::type
ceil2( Type n ) noexcept {
	--n;
	n = __builtin_clz( n );
	return 1 << ( 32 - n );
}

template <typename Type>
constexpr typename std::enable_if<std::is_integral<Type>::value && sizeof( Type ) == 8, Type>::type
floor2( Type n ) noexcept {
	n = __builtin_clzll( n );
	return 1 << ( 63 - n );
}

template <typename Type>
constexpr typename std::enable_if<std::is_integral<Type>::value && sizeof( Type ) < 8, Type>::type
floor2( Type n ) noexcept {
	n = __builtin_clz( n );
	return 1 << ( 31 - n );
}

// Rotate left
template <typename Type>
constexpr typename std::enable_if<std::is_integral<Type>::value, Type>::type
rotl( Type n, unsigned s ) noexcept {
	typename std::make_unsigned<Type>::type un = n;
	return ( un << s ) | ( un >> ( ( sizeof( un ) * 8 ) - s ) );
}

// Rotate right
template <typename Type>
constexpr typename std::enable_if<std::is_integral<Type>::value, Type>::type
rotr( Type n, unsigned s ) noexcept {
	typename std::make_unsigned<Type>::type un = n;
	return ( un >> s ) | ( un << ( ( sizeof( un ) * 8 ) - s ) );
}

} // math
} // gba

#endif // define GBAXX_MATH_HPP
