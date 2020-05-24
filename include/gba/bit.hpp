#ifndef GBAXX_BIT_HPP
#define GBAXX_BIT_HPP

#if __cpp_lib_bitops
#include <bit>
#endif

#include <type_traits>

namespace gba {

template <class T>
constexpr auto has_single_bit( T x ) noexcept -> typename std::enable_if<std::is_unsigned<T>::value && !std::is_same<T, bool>::value, bool>::type {
#if __cpp_lib_bitops
	return std::has_single_bit( x );
#else
	return __builtin_popcount( x ) == 1;
#endif
}

template <class T>
constexpr auto bit_ceil( T x ) noexcept -> typename std::enable_if<std::is_unsigned<T>::value && !std::is_same<T, bool>::value, T>::type {
#if __cpp_lib_bitops
	return std::bit_ceil( x );
#else
	--x;
	x = __builtin_clz( x );
	return 1 << ( 32 - x );
#endif
}

template <class T>
constexpr auto bit_floor( T x ) noexcept -> typename std::enable_if<std::is_unsigned<T>::value && !std::is_same<T, bool>::value, T>::type {
#if __cpp_lib_bitops
	return std::bit_floor( x );
#else
	x = __builtin_clz( x );
	return 1 << ( 31 - x );
#endif
}

template <class T>
constexpr auto bit_width( T x ) noexcept -> typename std::enable_if<std::is_unsigned<T>::value && !std::is_same<T, bool>::value, T>::type {
#if __cpp_lib_bitops
	return std::bit_width( x );
#else
	x = __builtin_clz( x );
	return 32 - x;
#endif
}

template <class T>
[[nodiscard]] constexpr auto rotl( T x, int s ) noexcept -> typename std::enable_if<std::is_unsigned<T>::value && !std::is_same<T, bool>::value, T>::type {
#if __cpp_lib_bitops
	return std::rotl( x );
#else
	return ( x << s ) | ( x >> ( 32 - s ) );
#endif
}

template <class T>
[[nodiscard]] constexpr auto rotr( T x, int s ) noexcept -> typename std::enable_if<std::is_unsigned<T>::value && !std::is_same<T, bool>::value, T>::type {
#if __cpp_lib_bitops
	return std::rotr( x );
#else
	return ( x >> s ) | ( x << ( 32 - s ) );
#endif
}

template <class T>
constexpr auto countl_zero( T x ) noexcept -> typename std::enable_if<std::is_unsigned<T>::value && !std::is_same<T, bool>::value, T>::type {
#if __cpp_lib_bitops
	return std::countl_zero( x );
#else
	return __builtin_clz( x );
#endif
}

template <class T>
constexpr auto countl_one( T x ) noexcept -> typename std::enable_if<std::is_unsigned<T>::value && !std::is_same<T, bool>::value, T>::type {
#if __cpp_lib_bitops
	return std::countl_one( x );
#else
	return __builtin_clz( ~x );
#endif
}

template <class T>
constexpr auto countr_zero( T x ) noexcept -> typename std::enable_if<std::is_unsigned<T>::value && !std::is_same<T, bool>::value, T>::type {
#if __cpp_lib_bitops
	return std::countr_zero( x );
#else
	return __builtin_ctz( x );
#endif
}

template <class T>
constexpr auto countr_one( T x ) noexcept -> typename std::enable_if<std::is_unsigned<T>::value && !std::is_same<T, bool>::value, T>::type {
#if __cpp_lib_bitops
	return std::countr_one( x );
#else
	return __builtin_ctz( ~x );
#endif
}

template <class T>
constexpr auto popcount( T x ) noexcept -> typename std::enable_if<std::is_unsigned<T>::value && !std::is_same<T, bool>::value, T>::type {
#if __cpp_lib_bitops
	return std::popcount( x );
#else
	return __builtin_popcount( x );
#endif
}

} // gba

#endif // define GBAXX_BIT_HPP
