#ifndef GBAXX_MATH_HPP
#define GBAXX_MATH_HPP

#include <cmath>
#include <type_traits>

#include <gba/bios.hpp>
#include <gba/int.hpp>
#include <gba/type_promotion.hpp>

namespace gba {
namespace math {
namespace detail {

	template <class ReprType>
	constexpr ReprType sqrt_bit( ReprType n, ReprType bit ) noexcept {
		if ( bit > n ) {
			return sqrt_bit<ReprType>( n, bit >> 2 );
		} else {
			return bit;
		}
	}

	template <class ReprType>
	constexpr auto sqrt_bit( ReprType n ) noexcept {
		return sqrt_bit<ReprType>( n, ReprType( 1 ) << ( sizeof( ReprType ) * 8 - 2 ) );
	}

	template <class ReprType>
	constexpr ReprType sqrt_solve3( ReprType n, ReprType bit, ReprType result ) noexcept {
		if ( bit != 0 ) {
			if ( n >= result + bit ) {
				return sqrt_solve3<ReprType>( static_cast<ReprType>( n - ( result + bit ) ), bit >> 2, static_cast<ReprType>( ( result >> 1 ) + bit ) );
			} else {
				return sqrt_solve3<ReprType>( n, bit >> 2, result >> 1 );
			}
		} else {
			return result;
		}
	}

	template <class ReprType>
	constexpr auto sqrt_solve1( ReprType n ) noexcept {
		return sqrt_solve3<ReprType>( n, sqrt_bit<ReprType>( n ), 0 );
	}

} // detail

template <class T>
constexpr auto sqrt( T x ) noexcept -> typename std::enable_if<std::is_floating_point<T>::value, T>::type {
	return std::sqrt( x );
}

template <class T>
constexpr auto sqrt( T x ) noexcept -> typename std::enable_if<std::is_integral<T>::value && !std::is_same<bool, T>::value, T>::type {
	if ( __builtin_constant_p( x ) ) {
		using wider_type = typename std::make_signed<promote::make_wider<T>>::type;

		const auto result = detail::sqrt_solve1( wider_type( x ) << ( sizeof( T ) * 8 ) );
		return static_cast<T>( result ) >> ( sizeof( T ) * 4 );
	}
	return bios::sqrt( x );
}

} // math
} // gba

#endif // define GBAXX_MATH_HPP
