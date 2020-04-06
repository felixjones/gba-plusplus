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
	static_assert( sizeof( ReprType ) <= sizeof( std::uintmax_t ), "ReprType too big" );
	
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
	constexpr fixed_point( S s ) noexcept : m_value( static_cast<repr_type>( s ) * ( 1ULL << Exponent ) ) {}

	template <class S, typename std::enable_if<std::is_floating_point<S>::value, int>::type Dummy = 0>
	constexpr fixed_point( S s ) noexcept : m_value( static_cast<repr_type>( s * ( 1ULL << Exponent ) ) ) {}

	template <class FromReprType, int FromExponent>
	constexpr fixed_point( const fixed_point<FromReprType, FromExponent>& rhs ) noexcept : m_value( Exponent > FromExponent ? static_cast<repr_type>( rhs.data() ) * ( 1ULL << ( Exponent - FromExponent ) ) : static_cast<repr_type>( rhs.data() ) / ( 1ULL << ( FromExponent - Exponent ) ) ) {}

	template <class S, typename std::enable_if<std::is_integral<S>::value, int>::type Dummy = 0>
	constexpr operator S() const noexcept {
		return m_value / ( 1ULL << Exponent );
	}

	template <class S, typename std::enable_if<std::is_floating_point<S>::value, int>::type Dummy = 0>
	explicit constexpr operator S() const noexcept {
		return m_value / static_cast<S>( 1ULL << Exponent );
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
		return std::numeric_limits<ReprType>::min() * ( 1ULL << Exponent );
	}

	static constexpr auto max() {
		return std::numeric_limits<ReprType>::max() * ( 1ULL << Exponent );
	}

	static constexpr auto lowest() {
		return min();
	}

};

namespace gba {
namespace detail {

	template<class T, class U>
	using wider = typename std::conditional<sizeof( T ) >= sizeof( U ), T, U>::type;

	template <class T>
	using wider_promote = typename std::conditional<std::is_signed<T>::value, typename int_sized_type<sizeof( T ) + 1>::type, typename uint_sized_type<sizeof( T ) + 1>::type>::type;

} // detail

template <class FixedA, class FixedB>
using fixed_promote = 
	typename std::conditional<std::is_signed<typename FixedA::repr_type>::value || std::is_signed<typename FixedB::repr_type>::value,
		fixed_point<
			typename std::make_signed<detail::wider<typename FixedA::repr_type, typename FixedB::repr_type>>::type,
			( sizeof( detail::wider<typename FixedA::repr_type, typename FixedB::repr_type> ) * 8 ) - std::max( sizeof( typename FixedA::repr_type ) * 8 - FixedA::exponent, sizeof( typename FixedB::repr_type ) * 8 - FixedB::exponent )
		>,
		fixed_point<
			typename std::make_unsigned<detail::wider<typename FixedA::repr_type, typename FixedB::repr_type>>::type,
			( sizeof( detail::wider<typename FixedA::repr_type, typename FixedB::repr_type> ) * 8 ) - std::max( FixedA::integer_digits, FixedB::integer_digits )
		>
	>::type;

template <class AReprType, int AExponent, class BReprType, int BExponent>
constexpr bool operator==( const fixed_point<AReprType, AExponent>& lhs, const fixed_point<BReprType, BExponent>& rhs ) noexcept {
	using fixed_promoted = fixed_promote<fixed_point<AReprType, AExponent>, fixed_point<BReprType, BExponent>>;

	return fixed_promoted( lhs ).data() == fixed_promoted( rhs ).data();
}

template <class AReprType, int AExponent, class BReprType, int BExponent>
constexpr bool operator!=( const fixed_point<AReprType, AExponent>& lhs, const fixed_point<BReprType, BExponent>& rhs ) noexcept {
	using fixed_promoted = fixed_promote<fixed_point<AReprType, AExponent>, fixed_point<BReprType, BExponent>>;

	return fixed_promoted( lhs ).data() != fixed_promoted( rhs ).data();
}

template <class AReprType, int AExponent, class BReprType, int BExponent>
constexpr bool operator<( const fixed_point<AReprType, AExponent>& lhs, const fixed_point<BReprType, BExponent>& rhs ) noexcept {
	using fixed_promoted = fixed_promote<fixed_point<AReprType, AExponent>, fixed_point<BReprType, BExponent>>;

	return fixed_promoted( lhs ).data() < fixed_promoted( rhs ).data();
}

template <class AReprType, int AExponent, class BReprType, int BExponent>
constexpr bool operator>( const fixed_point<AReprType, AExponent>& lhs, const fixed_point<BReprType, BExponent>& rhs ) noexcept {
	using fixed_promoted = fixed_promote<fixed_point<AReprType, AExponent>, fixed_point<BReprType, BExponent>>;

	return fixed_promoted( lhs ).data() > fixed_promoted( rhs ).data();
}

template <class AReprType, int AExponent, class BReprType, int BExponent>
constexpr bool operator<=( const fixed_point<AReprType, AExponent>& lhs, const fixed_point<BReprType, BExponent>& rhs ) noexcept {
	using fixed_promoted = fixed_promote<fixed_point<AReprType, AExponent>, fixed_point<BReprType, BExponent>>;

	return fixed_promoted( lhs ).data() <= fixed_promoted( rhs ).data();
}

template <class AReprType, int AExponent, class BReprType, int BExponent>
constexpr bool operator>=( const fixed_point<AReprType, AExponent>& lhs, const fixed_point<BReprType, BExponent>& rhs ) noexcept {
	using fixed_promoted = fixed_promote<fixed_point<AReprType, AExponent>, fixed_point<BReprType, BExponent>>;

	return fixed_promoted( lhs ).data() >= fixed_promoted( rhs ).data();
}

template <class ReprType, int Exponent>
constexpr fixed_point<ReprType, Exponent> operator-( const fixed_point<ReprType, Exponent>& rhs ) noexcept {
	return fixed_point<ReprType, Exponent>::from_data( -rhs.data() );
}

template <class AReprType, int AExponent, class BReprType, int BExponent>
constexpr auto operator+( fixed_point<AReprType, AExponent> a, fixed_point<BReprType, BExponent> b ) noexcept -> fixed_promote<decltype( a ), decltype( b )> {
	using fixed_promoted = fixed_promote<fixed_point<AReprType, AExponent>, fixed_point<BReprType, BExponent>>;

	return fixed_promoted::from_data( fixed_promoted( a ).data() + fixed_promoted( b ).data() );
}

template <class AReprType, int AExponent, class BReprType, int BExponent>
constexpr auto operator-( fixed_point<AReprType, AExponent> a, fixed_point<BReprType, BExponent> b ) noexcept -> fixed_promote<decltype( a ), decltype( b )> {
	using fixed_promoted = fixed_promote<fixed_point<AReprType, AExponent>, fixed_point<BReprType, BExponent>>;

	return fixed_promoted::from_data( fixed_promoted( a ).data() - fixed_promoted( b ).data() );
}

template <class AReprType, int AExponent, class BReprType, int BExponent>
fixed_point<AReprType, AExponent>& operator+=( fixed_point<AReprType, AExponent>& lhs, const fixed_point<BReprType, BExponent>& rhs ) noexcept {
	lhs.data() += fixed_point<AReprType, AExponent>( rhs ).data();
	return lhs;
}

template <class AReprType, int AExponent, class BReprType, int BExponent>
fixed_point<AReprType, AExponent>& operator-=( fixed_point<AReprType, AExponent>& lhs, const fixed_point<BReprType, BExponent>& rhs ) noexcept {
	lhs.data() -= fixed_point<AReprType, AExponent>( rhs ).data();
	return lhs;
}

template <class AReprType, int AExponent, class BReprType, int BExponent>
fixed_point<AReprType, AExponent>& operator*=( fixed_point<AReprType, AExponent>& lhs, const fixed_point<BReprType, BExponent>& rhs ) noexcept {
	using wider_repr_type = detail::wider_promote<AReprType>;

	lhs.data() = static_cast<AReprType>( ( static_cast<wider_repr_type>( lhs.data() ) * static_cast<wider_repr_type>( rhs.data() ) ) >> AExponent );
	return lhs;
}

template <class AReprType, int AExponent, class BReprType, int BExponent>
fixed_point<AReprType, AExponent>& operator/=( fixed_point<AReprType, AExponent>& lhs, const fixed_point<BReprType, BExponent>& rhs ) noexcept {
	using div_promote = fixed_point<detail::wider_promote<AReprType>, AExponent * 2>;

	lhs.data() = static_cast<AReprType>( div_promote( lhs ).data() / rhs.data() );
	return lhs;
}

template <class LReprType, int LExponent, class Rhs, typename std::enable_if<std::is_arithmetic<Rhs>::value>::type * = nullptr>
constexpr auto operator+( const fixed_point<LReprType, LExponent>& lhs, const Rhs& rhs ) noexcept {
	return lhs + fixed_point<LReprType, LExponent>( rhs );
}

template <class Lhs, class RReprType, int RExponent, typename std::enable_if<std::is_arithmetic<Lhs>::value>::type * = nullptr>
constexpr auto operator+( const Lhs& lhs, const fixed_point<RReprType, RExponent>& rhs ) noexcept {
	return fixed_point<RReprType, RExponent>( lhs ) + rhs;
}

template <class LReprType, int LExponent, class Rhs, typename std::enable_if<std::is_arithmetic<Rhs>::value>::type * = nullptr>
constexpr auto operator-( const fixed_point<LReprType, LExponent>& lhs, const Rhs& rhs ) noexcept {
	return lhs - fixed_point<LReprType, LExponent>( rhs );
}

template <class Lhs, class RReprType, int RExponent, typename std::enable_if<std::is_arithmetic<Lhs>::value>::type * = nullptr>
constexpr auto operator-( const Lhs& lhs, const fixed_point<RReprType, RExponent>& rhs ) noexcept {
	return fixed_point<RReprType, RExponent>( lhs ) - rhs;
}

template <class AReprType, int AExponent, class BReprType, int BExponent>
constexpr auto operator*( fixed_point<AReprType, AExponent> a, fixed_point<BReprType, BExponent> b ) -> fixed_promote<decltype( a ), decltype( b )> {
	using fixed_promoted = fixed_promote<decltype( a ), decltype( b )>;
	using mul_promoted = fixed_promote<fixed_point<detail::wider_promote<AReprType>, AExponent>, fixed_point<detail::wider_promote<BReprType>, BExponent>>;

	return fixed_promoted::from_data( ( mul_promoted( a ).data() * mul_promoted( b ).data() ) / ( 1ULL << mul_promoted::exponent ) );
}

template <class AReprType, int AExponent, class BReprType, int BExponent>
constexpr auto operator/( fixed_point<AReprType, AExponent> a, fixed_point<BReprType, BExponent> b ) -> fixed_promote<decltype( a ), decltype( b )> {
	using fixed_promoted = fixed_promote<decltype( a ), decltype( b )>;
	using div_promote = fixed_point<detail::wider_promote<typename fixed_promoted::repr_type>, fixed_promoted::exponent << 1>;

	return fixed_promoted::from_data( div_promote( a ).data() / fixed_promoted( b ).data() );
}

template <class LhsReprType, int LhsExponent, class Integer, typename = typename std::enable_if<std::is_integral<Integer>::value>::type>
constexpr auto operator*( const fixed_point<LhsReprType, LhsExponent>& lhs, const Integer& rhs ) noexcept {
	return fixed_point<LhsReprType, LhsExponent>::from_data( lhs.data() * rhs );
}

template <class LhsReprType, int LhsExponent, class Integer, typename = typename std::enable_if<std::is_integral<Integer>::value>::type>
constexpr auto operator/( const fixed_point<LhsReprType, LhsExponent>& lhs, const Integer& rhs ) noexcept {
	using fixed_type = fixed_point<LhsReprType, LhsExponent>;

	return fixed_type::from_data( lhs.data() / rhs );
}

template <class Integer, class RhsReprType, int RhsExponent, typename = typename std::enable_if<std::is_integral<Integer>::value>::type>
constexpr auto operator*( const Integer& lhs, const fixed_point<RhsReprType, RhsExponent>& rhs ) noexcept {
	return fixed_point<RhsReprType, RhsExponent>::from_data( lhs * rhs.data() );
}

template <class Integer, class RhsReprType, int RhsExponent, typename = typename std::enable_if<std::is_integral<Integer>::value>::type>
constexpr auto operator/( const Integer& lhs, const fixed_point<RhsReprType, RhsExponent>& rhs ) noexcept {
	using fixed_type = fixed_point<RhsReprType, RhsExponent>;
	using wider_type = fixed_point<detail::wider_promote<typename fixed_type::repr_type>, RhsExponent * 2>;

	return fixed_type::from_data( wider_type( lhs ).data() / rhs.data() );
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

} // gba

#endif // define GBAXX_FIXED_POINT_HPP
