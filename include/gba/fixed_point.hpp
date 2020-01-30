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
	explicit constexpr fixed_point( S s ) noexcept : m_value( static_cast< repr_type >( s * ( 1 << Exponent ) ) ) {}

	template <class FromReprType, int FromExponent>
	explicit constexpr fixed_point( const fixed_point<FromReprType, FromExponent>& rhs ) noexcept : m_value( Exponent > FromExponent ? rhs.data() * ( 1 << ( Exponent - FromExponent ) ) : rhs.data() / ( 1 << ( FromExponent - Exponent ) ) ) {}

	template <class S, typename std::enable_if<std::is_integral<S>::value, int>::type Dummy = 0>
	explicit constexpr operator S() const noexcept {
		return m_value / ( 1 << Exponent );
	}

	template <class S, typename std::enable_if<std::is_floating_point<S>::value, int>::type Dummy = 0>
	explicit constexpr operator S() const noexcept {
		return m_value / static_cast<S>( 1 << Exponent );
	}

	explicit constexpr operator bool() const noexcept {
		return m_value != 0;
	}

	template <class Rhs, typename std::enable_if<std::is_arithmetic<Rhs>::value, int>::type Dummy = 0>
	fixed_point& operator*=( const Rhs& rhs ) noexcept {
		m_value *= rhs;
		return *this;
	}

	template <class Rhs, typename std::enable_if<std::is_arithmetic<Rhs>::value, int>::type Dummy = 0>
	fixed_point& operator/=( const Rhs& rhs ) noexcept {
		m_value /= rhs;
		return *this;
	}

	constexpr const auto& data() const noexcept {
		return m_value;
	}

	constexpr auto& data() noexcept {
		return m_value;
	}

protected:
	repr_type   m_value;

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

	template <class T>
	using wider_promote = typename std::conditional<std::is_signed<T>::value, typename int_sized_type<sizeof( T ) + 1>::type, typename uint_sized_type<sizeof( T ) + 1>::type>::type;

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

	template <class ReprType, int Exponent>
	constexpr bool operator==( const fixed_point<ReprType, Exponent>& lhs, const fixed_point<ReprType, Exponent>& rhs ) noexcept {
		typedef fixed_promote<fixed_point<ReprType, Exponent>, fixed_point<ReprType, Exponent>> fixed_promoted;
		return fixed_promoted( lhs ).data() == fixed_promoted( rhs ).data();
	}

	template <class ReprType, int Exponent>
	constexpr bool operator!=( const fixed_point<ReprType, Exponent>& lhs, const fixed_point<ReprType, Exponent>& rhs ) noexcept {
		typedef fixed_promote<fixed_point<ReprType, Exponent>, fixed_point<ReprType, Exponent>> fixed_promoted;
		return fixed_promoted( lhs ).data() != fixed_promoted( rhs ).data();
	}

	template <class ReprType, int Exponent>
	constexpr bool operator<( const fixed_point<ReprType, Exponent>& lhs, const fixed_point<ReprType, Exponent>& rhs ) noexcept {
		typedef fixed_promote<fixed_point<ReprType, Exponent>, fixed_point<ReprType, Exponent>> fixed_promoted;
		return fixed_promoted( lhs ).data() < fixed_promoted( rhs ).data();
	}

	template <class ReprType, int Exponent>
	constexpr bool operator>( const fixed_point<ReprType, Exponent>& lhs, const fixed_point<ReprType, Exponent>& rhs ) noexcept {
		typedef fixed_promote<fixed_point<ReprType, Exponent>, fixed_point<ReprType, Exponent>> fixed_promoted;
		return fixed_promoted( lhs ).data() > fixed_promoted( rhs ).data();
	}

	template <class ReprType, int Exponent>
	constexpr bool operator<=( const fixed_point<ReprType, Exponent>& lhs, const fixed_point<ReprType, Exponent>& rhs ) noexcept {
		typedef fixed_promote<fixed_point<ReprType, Exponent>, fixed_point<ReprType, Exponent>> fixed_promoted;
		return fixed_promoted( lhs ).data() <= fixed_promoted( rhs ).data();
	}

	template <class ReprType, int Exponent>
	constexpr bool operator>=( const fixed_point<ReprType, Exponent>& lhs, const fixed_point<ReprType, Exponent>& rhs ) noexcept {
		typedef fixed_promote<fixed_point<ReprType, Exponent>, fixed_point<ReprType, Exponent>> fixed_promoted;
		return fixed_promoted( lhs ).data() >= fixed_promoted( rhs ).data();
	}

	template <class ReprType, int Exponent>
	constexpr fixed_point<ReprType, Exponent> operator-( const fixed_point<ReprType, Exponent>& rhs ) noexcept {
		return fixed_point<ReprType, Exponent>::from_data( -rhs.data() );
	}

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

	template <class ReprType, int Exponent>
	fixed_point<ReprType, Exponent>& operator+=( fixed_point<ReprType, Exponent>& lhs, const fixed_point<ReprType, Exponent>& rhs ) noexcept {
		lhs.data() += fixed_point<ReprType, Exponent>( rhs ).data();
		return lhs;
	}

	template <class ReprType, int Exponent>
	fixed_point<ReprType, Exponent>& operator-=( fixed_point<ReprType, Exponent>& lhs, const fixed_point<ReprType, Exponent>& rhs ) noexcept {
		lhs.data() -= fixed_point<ReprType, Exponent>( rhs ).data();
		return lhs;
	}

	template <class ReprType, int Exponent>
	fixed_point<ReprType, Exponent>& operator*=( fixed_point<ReprType, Exponent>& lhs, const fixed_point<ReprType, Exponent>& rhs ) noexcept {
		typedef wider_promote<ReprType> wider_repr_type;
		lhs.data() = static_cast<ReprType>( ( static_cast<wider_repr_type>( lhs.data() ) * static_cast<wider_repr_type>( rhs.data() ) ) >> Exponent );
		return lhs;
	}

	template <class ReprType, int Exponent>
	fixed_point<ReprType, Exponent>& operator/=( fixed_point<ReprType, Exponent>& lhs, const fixed_point<ReprType, Exponent>& rhs ) noexcept {
		typedef fixed_point<wider_promote<ReprType>, Exponent << 1> div_promote;
		lhs.data() = static_cast< ReprType >( div_promote( lhs ).data() / rhs.data() );
		return lhs;
	}

	template <class Lhs, class Rhs>
	constexpr auto operator+( const Lhs& lhs, const Rhs& rhs ) noexcept {
		if constexpr ( std::is_arithmetic<Rhs>::value ) {
			return lhs + Lhs( rhs );
		} else {
			return Rhs( lhs ) + rhs;
		}
	}

	template <class Lhs, class Rhs>
	constexpr auto operator-( const Lhs& lhs, const Rhs& rhs ) noexcept {
		if constexpr ( std::is_arithmetic<Rhs>::value ) {
			return lhs - Lhs( rhs );
		} else {
			return Rhs( lhs ) - rhs;
		}
	}

	template <class AReprType, int AExponent, class BReprType, int BExponent>
	constexpr auto operator*( fixed_point<AReprType, AExponent> a, fixed_point<BReprType, BExponent> b ) -> fixed_promote<decltype( a ), decltype( b )> {
		typedef fixed_promote<decltype( a ), decltype( b )> fixed_promoted;
		typedef fixed_promote<fixed_point<wider_promote<AReprType>, AExponent>, fixed_point<wider_promote<BReprType>, BExponent>> mul_promoted;
		return fixed_promoted::from_data( ( mul_promoted( a ).data() * mul_promoted( b ).data() ) / ( 1 << mul_promoted::exponent ) );
	}

	template <class AReprType, int AExponent, class BReprType, int BExponent>
	constexpr auto operator/( fixed_point<AReprType, AExponent> a, fixed_point<BReprType, BExponent> b ) -> fixed_promote<decltype( a ), decltype( b )> {
		typedef fixed_promote<decltype( a ), decltype( b )> fixed_promoted;
		typedef wider_promote<typename fixed_promoted::repr_type> wider_repr_type;
		typedef fixed_point<wider_repr_type, fixed_promoted::exponent << 1> div_promote;
		return fixed_promoted::from_data( div_promote( a ).data() / fixed_promoted( b ).data() );
	}

	template <class LhsReprType, int LhsExponent, class Integer>
	constexpr auto operator*( const fixed_point<LhsReprType, LhsExponent>& lhs, const Integer& rhs ) noexcept {
		return fixed_point<LhsReprType, LhsExponent>::from_data( lhs.data() * rhs );
	}

	template <class LhsReprType, int LhsExponent, class Integer>
	constexpr auto operator/( const fixed_point<LhsReprType, LhsExponent>& lhs, const Integer& rhs ) noexcept {
		return fixed_point<LhsReprType, LhsExponent>::from_data( lhs.data() / rhs );
	}

	template <class Integer, class RhsReprType, int RhsExponent>
	constexpr auto operator*( const Integer& lhs, const fixed_point<RhsReprType, RhsExponent>& rhs ) noexcept {
		return fixed_point<RhsReprType, RhsExponent>::from_data( lhs * rhs.data() );
	}

	template <class Integer, class RhsReprType, int RhsExponent>
	constexpr auto operator/( const Integer& lhs, const fixed_point<RhsReprType, RhsExponent>& rhs ) noexcept {
		return fixed_point<RhsReprType, RhsExponent>::from_data( lhs / rhs.data() );
	}

	template <class LhsReprType, int Exponent, class Rhs>
	fixed_point<LhsReprType, Exponent>& operator+=( fixed_point<LhsReprType, Exponent>& lhs, const Rhs& rhs ) noexcept {
		lhs += fixed_point<LhsReprType, Exponent>( rhs );
		return lhs;
	}

	template <class LhsReprType, int Exponent, class Rhs>
	fixed_point<LhsReprType, Exponent>& operator-=( fixed_point<LhsReprType, Exponent>& lhs, const Rhs& rhs ) noexcept {
		lhs -= fixed_point<LhsReprType, Exponent>( rhs );
		return lhs;
	}

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

	} // detail

	template <class ReprType, int Exponent>
	constexpr auto sqrt( const fixed_point<ReprType, Exponent>& x ) noexcept {
		using widened_type = fixed_point<wider_promote<ReprType>, Exponent * 2>;
		return fixed_point<ReprType, Exponent>::from_data( static_cast< ReprType >( detail::sqrt_solve1( widened_type( x ).data() ) ) );
	}

} // gba

#endif // define GBAXX_FIXED_POINT_HPP
