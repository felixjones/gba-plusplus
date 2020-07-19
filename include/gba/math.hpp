#ifndef GBAXX_MATH_HPP
#define GBAXX_MATH_HPP

#include <cmath>
#include <type_traits>

#include <gba/bios.hpp>
#include <gba/int.hpp>
#include <gba/fixed_point.hpp>
#include <gba/math_constants.hpp>
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

	constexpr auto sin_bam16( int16 bam ) noexcept {
		auto x = bam << 17;
		if ( ( x ^ ( x << 1 ) ) < 0 ) {
			x = ( 1 << 31 ) - x;
		}
		x = x >> 17;
		return fixed_point<int32, 12>::from_data( x * ( 0x18000 - ( ( x * x ) >> 11 ) ) >> 17 );
	}

	template <typename ReprType, unsigned Exponent>
	constexpr int16 radian_to_bam16( const fixed_point<ReprType, Exponent>& radian ) noexcept {
		constexpr auto radTo16 = make_ufixed<13, 19>( 16384.0 / 3.14159265358979323846264338327950288 );
		return static_cast<int16>( radian * radTo16 );
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

template <typename ReprType, unsigned Exponent>
constexpr auto sqrt( const fixed_point<ReprType, Exponent>& x ) noexcept {
	if ( __builtin_constant_p( x.data() ) ) {
		using widened_type = fixed_point<promote::make_wider<ReprType>, Exponent * 2>;
		return fixed_point<ReprType, Exponent>::from_data( static_cast<ReprType>( detail::sqrt_solve1( widened_type( x ).data() ) ) );
	}
	return bios::sqrt( x );
}

template <typename ReprType, unsigned Exponent>
constexpr auto sin( const fixed_point<ReprType, Exponent>& radian ) noexcept {
	return detail::sin_bam16( detail::radian_to_bam16( radian ) );
}

template <class S, typename std::enable_if<std::is_arithmetic<S>::value, int>::type Dummy = 0>
constexpr auto sin( const S radian ) noexcept {
	return detail::sin_bam16( detail::radian_to_bam16( make_ufixed<13, 19>( radian ) ) );
}

template <typename ReprType, unsigned Exponent>
constexpr auto cos( const fixed_point<ReprType, Exponent>& radian ) noexcept {
	return detail::sin_bam16( detail::radian_to_bam16( radian ) + 0x2000 );
}

template <class S, typename std::enable_if<std::is_arithmetic<S>::value, int>::type Dummy = 0>
constexpr auto cos( const S radian ) noexcept {
	return detail::sin_bam16( detail::radian_to_bam16( make_ufixed<13, 19>( radian ) ) + 0x2000 );
}

template <class AT, class BT, typename ReprType, unsigned Exponent>
constexpr auto mix( const AT& a, const BT& b, const fixed_point<ReprType, Exponent>& scale ) noexcept {
	return a * ( fixed_point<ReprType, Exponent>( 1 ) - scale ) + b * scale;
}

template <typename ReprType, unsigned Exponent>
constexpr auto abs( const fixed_point<ReprType, Exponent>& x ) noexcept -> typename std::enable_if<std::is_signed<ReprType>::value, fixed_point<typename std::make_unsigned<ReprType>::type, Exponent>>::type {
	using fixed_type = fixed_point<typename std::make_unsigned<ReprType>::type, Exponent>;

	return fixed_type::from_data( x.data() < 0 ? -x.data() : x.data() );
}

template <typename ReprType, unsigned Exponent>
constexpr auto abs( const fixed_point<ReprType, Exponent>& x ) noexcept -> typename std::enable_if<std::is_unsigned<ReprType>::value, fixed_point<ReprType, Exponent>>::type {
	return x;
}

} // math
} // gba

#endif // define GBAXX_MATH_HPP
