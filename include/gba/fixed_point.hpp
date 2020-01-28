#ifndef GBAXX_FIXED_POINT_HPP
#define GBAXX_FIXED_POINT_HPP

#include <algorithm>
#include <cstdint>
#include <limits>
#include <type_traits>

#include <gba/int_type.hpp>

namespace gba {

template <class ReprType = int, int Exponent = 0>
class fixed_point {
	static_assert( std::is_fundamental<ReprType>::value, "ReprType must be a fundamental type" );
	static_assert( std::is_integral<ReprType>::value, "ReprType must be a integral type" );
	static_assert( sizeof( ReprType ) < sizeof( std::uintmax_t ), "ReprType should not be the largest size" );
	
public:
	using repr_type = ReprType;

	constexpr static int exponent = Exponent;
	constexpr static int digits = ( sizeof( repr_type ) * 8 ) - ( std::is_signed<repr_type>::value ? 1 : 0 );
	constexpr static int integer_digits = digits - Exponent;
	constexpr static int fractional_digits = Exponent;

	static constexpr fixed_point from_data( repr_type repr ) noexcept {
		fixed_point a;
		a.m_value = repr;
		return a;
	}

	constexpr fixed_point() noexcept : m_value( 0 ) {}

	template <class S, typename std::enable_if<std::is_integral<S>::value, int>::type Dummy = 0>
	explicit constexpr fixed_point( S s ) noexcept : m_value( s * ( 1 << Exponent ) ) {}

	template <class S, typename std::enable_if<std::is_floating_point<S>::value, int>::type Dummy = 0>
	explicit constexpr fixed_point( S s ) noexcept : m_value( static_cast<repr_type>( s * ( 1 << Exponent ) ) ) {}

	template <class FromReprType, int FromExponent>
	explicit constexpr fixed_point( const fixed_point<FromReprType, FromExponent>& rhs ) noexcept : m_value( 0 ) {
		if constexpr ( std::is_signed<repr_type>::value ) {
			if constexpr ( Exponent > FromExponent ) {
				m_value = rhs.data() * ( 1 << ( Exponent - FromExponent ) );
			} else {
				m_value = rhs.data() / ( 1 << ( FromExponent - Exponent ) );
			}
		} else {
			if constexpr ( Exponent > FromExponent ) {
				m_value = rhs.data() << ( Exponent - FromExponent );
			} else {
				m_value = rhs.data() >> ( FromExponent - Exponent );
			}
		}
	}

	template <class S, typename std::enable_if<std::is_integral<S>::value, int>::type Dummy = 0>
	explicit constexpr operator S() const noexcept {
		if constexpr ( std::is_signed<repr_type>::value ) {
			return m_value / ( 1 << Exponent );
		} else {
			return m_value >> Exponent;
		}
	}

	template <class S, typename std::enable_if<std::is_floating_point<S>::value, int>::type Dummy = 0>
	explicit constexpr operator S() const noexcept {
		return m_value / static_cast<S>( 1 << Exponent );
	}

	explicit constexpr operator bool() const noexcept {
		return m_value != 0;
	}

	constexpr repr_type data() const noexcept {
		return m_value;
	}

protected:
	repr_type	m_value;

};

template <int IntegerBits, int FractionalBits = 0>
using make_fixed = fixed_point<typename int_type<IntegerBits + FractionalBits>::type, FractionalBits>;

template <int IntegerBits, int FractionalBits = 0>
using make_ufixed = fixed_point<typename uint_type<IntegerBits + FractionalBits>::type, FractionalBits>;

} // gba

template <class ReprType, int Exponent>
struct std::numeric_limits<gba::fixed_point<ReprType, Exponent>> : public std::numeric_limits<ReprType> {

	static constexpr auto min() {
		return std::numeric_limits<ReprType>::min() * ( 1 << Exponent );
	}

	static constexpr auto max() {
		return std::numeric_limits<ReprType>::max() * ( 1 << Exponent );
	}

	static constexpr auto lowest() {
		return min();
	}

};

namespace gba {

	template<class T, class U>
	using wider = typename std::conditional<sizeof( T ) >= sizeof( U ), T, U>::type;

	template <class FixedA, class FixedB>
	using fixed_promote = 
		typename std::conditional<std::is_signed<typename FixedA::repr_type>::value || std::is_signed<typename FixedB::repr_type>::value,
			fixed_point<
				typename std::make_signed<wider<typename FixedA::repr_type, typename FixedB::repr_type>>::type,
				( sizeof( wider<typename FixedA::repr_type, typename FixedB::repr_type> ) * 8 ) - std::max( sizeof( typename FixedA::repr_type ) * 8 - FixedA::exponent, sizeof( typename FixedB::repr_type ) * 8 - FixedB::exponent )
			>,
			fixed_point<
				typename std::make_unsigned<wider<typename FixedA::repr_type, typename FixedB::repr_type>>::type,
				( sizeof( wider<typename FixedA::repr_type, typename FixedB::repr_type> ) * 8 ) - std::max( FixedA::integer_digits, FixedB::integer_digits )
			>
		>::type;
	
	template <class AReprType, int AExponent, class BReprType, int BExponent>
	constexpr auto operator+( fixed_point<AReprType, AExponent> a, fixed_point<BReprType, BExponent> b ) -> fixed_promote<decltype( a ), decltype( b )> {
		typedef fixed_promote<decltype( a ), decltype( b )> fixed_promoted;
		return fixed_promoted::from_data( fixed_promoted( a ).data() + fixed_promoted( b ).data() );
	}

	template <class AReprType, int AExponent, class BReprType, int BExponent>
	constexpr auto operator-( fixed_point<AReprType, AExponent> a, fixed_point<BReprType, BExponent> b ) -> fixed_promote<decltype( a ), decltype( b )> {
		typedef fixed_promote<decltype( a ), decltype( b )> fixed_promoted;
		return fixed_promoted::from_data( fixed_promoted( a ).data() - fixed_promoted( b ).data() );
	}

} // gba

#endif // define GBAXX_FIXED_POINT_HPP
