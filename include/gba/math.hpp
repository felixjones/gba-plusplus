#ifndef GBAXX_MATH_HPP
#define GBAXX_MATH_HPP

#include <cmath>
#include <type_traits>

#include <gba/int.hpp>
#include <gba/fixed_point.hpp>
#include <gba/frac.hpp>

namespace gba {
namespace math {

template <unsigned Exponent>
struct constants {
	static constexpr auto e          = fixed_point<uint32, Exponent>( 2.7182818284590452354 );
	static constexpr auto log2e      = fixed_point<uint32, Exponent>( 1.4426950408889634074 );
	static constexpr auto log10e     = fixed_point<uint32, Exponent>( 0.43429448190325182765 );
	static constexpr auto pi         = fixed_point<uint32, Exponent>( 3.1415926535897932385 );
	static constexpr auto inv_pi     = fixed_point<uint32, Exponent>( 0.31830988618379067154 );
	static constexpr auto inv_sqrtpi = fixed_point<uint32, Exponent>( 0.56418958354775628695 );
	static constexpr auto ln2        = fixed_point<uint32, Exponent>( 0.69314718055994530942 );
	static constexpr auto ln10       = fixed_point<uint32, Exponent>( 2.3025850929940456840 );
	static constexpr auto sqrt2      = fixed_point<uint32, Exponent>( 1.4142135623730950488 );
	static constexpr auto sqrt3      = fixed_point<uint32, Exponent>( 1.7320508075688772935 );
	static constexpr auto inv_sqrt3  = fixed_point<uint32, Exponent>( 0.57735026918962576451 );
	static constexpr auto egmma      = fixed_point<uint32, Exponent>( 0.57721566490153286061 );
	static constexpr auto phi        = fixed_point<uint32, Exponent>( 1.6180339887498948482 );
};

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
		return sqrt_bit<ReprType>( n, ReprType( 1 ) << ( ( ( sizeof( ReprType ) * 8 - 1 ) + std::is_signed<ReprType>::value ) - 2 ) );
	}

	template <class ReprType>
	constexpr ReprType sqrt_solve3( ReprType n, ReprType bit, ReprType result ) noexcept {
		if ( bit != 0 ) {
			if ( n >= result + bit ) {
				return sqrt_solve3<ReprType>( static_cast< ReprType >( n - ( result + bit ) ), bit >> 2, static_cast< ReprType >( ( result >> 1 ) + bit ) );
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

	constexpr auto sin_bam16( int16 bam ) {
		auto x = bam << 17;
		if ( ( x ^ ( x << 1 ) ) < 0 ) {
			x = ( 1 << 31 ) - x;
		}
		x = x >> 17;
		return fixed_point<int, 12>::from_data( x * ( 0x18000 - ( ( x * x ) >> 11 ) ) >> 17 );
	}

	template <class ReprType, int Exponent>
	constexpr int16 radian_to_bam16( const fixed_point<ReprType, Exponent>& radian ) {
		constexpr auto radTo16 = make_ufixed<13, 19>( 16384.0 / 3.14159265358979323846264338327950288 );
		return static_cast<int16>( radian * radTo16 );
	}

} // detail

template <class T>
constexpr auto sqrt( T x ) noexcept -> typename std::enable_if<std::is_integral<T>::value && !std::is_same<bool, T>::value, fixed_point<T, sizeof( T ) * 4>>::type {
	using wider_type = typename std::make_signed<wider_promote<T>>::type;
	return fixed_point<T, sizeof( T ) * 4>::from_data( static_cast<T>( detail::sqrt_solve1( wider_type( x ) << ( sizeof( T ) * 8 ) ) ) );
}

template <class T>
constexpr auto sqrt( T x ) noexcept -> typename std::enable_if<std::is_floating_point<T>::value, T>::type {
	return std::sqrt( x );
}

template <class ReprType, int Exponent>
constexpr auto sqrt( const fixed_point<ReprType, Exponent>& x ) noexcept {
	using widened_type = fixed_point<wider_promote<ReprType>, Exponent * 2>;
	return fixed_point<ReprType, Exponent>::from_data( static_cast<ReprType>( detail::sqrt_solve1( widened_type( x ).data() ) ) );
}

template <class ReprType, int Exponent>
constexpr auto sin( const fixed_point<ReprType, Exponent>& radian ) noexcept {
	return detail::sin_bam16( detail::radian_to_bam16( radian ) );
}

template <class S, typename std::enable_if<std::is_floating_point<S>::value, int>::type Dummy = 0>
constexpr auto sin( const S radian ) noexcept {
	return detail::sin_bam16( detail::radian_to_bam16( make_ufixed<13, 19>( radian ) ) );
}

template <class ReprType, int Exponent>
constexpr auto cos( const fixed_point<ReprType, Exponent>& radian ) noexcept {
	return detail::sin_bam16( detail::radian_to_bam16( radian ) + 0x2000 );
}

template <class S, typename std::enable_if<std::is_floating_point<S>::value, int>::type Dummy = 0>
constexpr auto cos( const S radian ) noexcept {
	return detail::sin_bam16( detail::radian_to_bam16( make_ufixed<13, 19>( radian ) ) + 0x2000 );
}

template <class AT, class BT, class ReprType, int Exponent>
constexpr auto mix( const AT& a, const BT& b, const fixed_point<ReprType, Exponent>& scale ) noexcept {
	return a * ( fixed_point<ReprType, Exponent>( 1 ) - scale ) + b * scale;
}

template <class AT, class BT, class ReprType, int Exponent>
constexpr auto mix( const AT& a, const BT& b, const frac<ReprType, Exponent>& scale ) noexcept {
	return a * ( frac<ReprType, Exponent>( 1 ) - scale ) + b * scale;
}

} // math
} // gba

#endif // define GBAXX_MATH_HPP
