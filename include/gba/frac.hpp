#ifndef GBAXX_FRAC_HPP
#define GBAXX_FRAC_HPP

#include <type_traits>

#include <gba/fixed_point.hpp>
#include <gba/int_type.hpp>

namespace gba {

// 0..1 = 0x0..0xf
template <class ReprType, int Exponent = ( sizeof( ReprType ) * 8 )>
class frac {
	static_assert( std::is_fundamental<ReprType>::value, "ReprType must be a fundamental type" );
	static_assert( std::is_integral<ReprType>::value, "ReprType must be a integral type" );
	static_assert( sizeof( ReprType ) <= sizeof( std::uintmax_t ), "ReprType too big" );

protected:
	constexpr static auto unit = ( 1 << Exponent ) - 1;

public:
	using repr_type = typename std::make_unsigned<ReprType>::type;

	constexpr static int exponent = Exponent;

	static constexpr frac from_data( repr_type repr ) noexcept {
		frac a;
		a.m_value = repr;
		return a;
	}

	static constexpr frac from_ratio( int l, int r ) noexcept {
		frac a;
		a.m_value = ( l * unit ) / ( l + r );
		return a;
	}

	constexpr frac() noexcept : m_value( unit ) {}

	template <typename A, typename B>
	constexpr frac( A a, B b ) noexcept : m_value( ( a * unit ) / b ) {}

	template <class S, typename std::enable_if<std::is_arithmetic<S>::value, int>::type Dummy = 0>
	constexpr frac( S s ) noexcept : m_value( static_cast<repr_type>( s * unit ) ) {}

	template <class FromReprType, int FromExponent>
	constexpr frac( const fixed_point<FromReprType, FromExponent>& s ) noexcept : m_value( static_cast<repr_type>( s * unit ) ) {}

	template <class FromReprType, int FromExponent>
	constexpr frac( const frac<FromReprType, FromExponent>& s ) noexcept : m_value( ( s.data() * unit ) / ( ( 1 << FromExponent ) - 1 ) ) {}

	template <class ToReprType, int ToExponent>
	explicit constexpr operator fixed_point<ToReprType, ToExponent>() const noexcept {
		return fixed_point<ToReprType, ToExponent>::from_data( ( m_value << ToExponent ) / unit );
	}

	template <class S, typename std::enable_if<std::is_floating_point<S>::value, int>::type Dummy = 0>
	explicit constexpr operator S() const noexcept {
		return m_value / static_cast<S>( unit );
	}

	explicit constexpr operator bool() const noexcept {
		return m_value != 0;
	}

	template <class Rhs, typename std::enable_if<std::is_arithmetic<Rhs>::value, int>::type Dummy = 0>
	frac& operator*=( const Rhs& rhs ) noexcept {
		m_value *= rhs;
		return *this;
	}

	template <class Rhs, typename std::enable_if<std::is_arithmetic<Rhs>::value, int>::type Dummy = 0>
	frac& operator/=( const Rhs& rhs ) noexcept {
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

template <unsigned FractionalBits>
using make_frac = frac<typename uint_type<FractionalBits>::type, FractionalBits>;

} // gba

template <class ReprType, int Exponent>
struct std::numeric_limits<gba::frac<ReprType, Exponent>> : public std::numeric_limits<ReprType> {

	static constexpr auto min() {
		return 0;
	}

	static constexpr auto max() {
		return ( 1 << Exponent ) - 1;
	}

	static constexpr auto lowest() {
		return min();
	}

};

namespace gba {

template <class FracA, class FracB>
using frac_promote = frac<wider<typename FracA::repr_type, typename FracB::repr_type>, ( FracA::exponent > FracB::exponent ? FracA::exponent : FracB::exponent )>;

template <class ReprType, int Exponent>
constexpr bool operator==( const frac<ReprType, Exponent>& lhs, const frac<ReprType, Exponent>& rhs ) noexcept {
	typedef frac_promote<frac<ReprType, Exponent>, frac<ReprType, Exponent>> frac_promoted;
	return frac_promoted( lhs ).data() == frac_promoted( rhs ).data();
}

template <class ReprType, int Exponent>
constexpr bool operator!=( const frac<ReprType, Exponent>& lhs, const frac<ReprType, Exponent>& rhs ) noexcept {
	typedef frac_promote<frac<ReprType, Exponent>, frac<ReprType, Exponent>> frac_promoted;
	return frac_promoted( lhs ).data() != frac_promoted( rhs ).data();
}

template <class ReprType, int Exponent>
constexpr bool operator<( const frac<ReprType, Exponent>& lhs, const frac<ReprType, Exponent>& rhs ) noexcept {
	typedef frac_promote<frac<ReprType, Exponent>, frac<ReprType, Exponent>> frac_promoted;
	return frac_promoted( lhs ).data() < frac_promoted( rhs ).data();
}

template <class ReprType, int Exponent>
constexpr bool operator>( const frac<ReprType, Exponent>& lhs, const frac<ReprType, Exponent>& rhs ) noexcept {
	typedef frac_promote<frac<ReprType, Exponent>, frac<ReprType, Exponent>> frac_promoted;
	return frac_promoted( lhs ).data() > frac_promoted( rhs ).data();
}

template <class ReprType, int Exponent>
constexpr bool operator<=( const frac<ReprType, Exponent>& lhs, const frac<ReprType, Exponent>& rhs ) noexcept {
	typedef frac_promote<frac<ReprType, Exponent>, frac<ReprType, Exponent>> frac_promoted;
	return frac_promoted( lhs ).data() <= frac_promoted( rhs ).data();
}

template <class ReprType, int Exponent>
constexpr bool operator>=( const frac<ReprType, Exponent>& lhs, const frac<ReprType, Exponent>& rhs ) noexcept {
	typedef frac_promote<frac<ReprType, Exponent>, frac<ReprType, Exponent>> frac_promoted;
	return frac_promoted( lhs ).data() >= frac_promoted( rhs ).data();
}

template <class AReprType, int AExponent, class BReprType, int BExponent>
constexpr auto operator+( frac<AReprType, AExponent> a, frac<BReprType, BExponent> b ) -> frac_promote<decltype( a ), decltype( b )> {
	typedef frac_promote<decltype( a ), decltype( b )> frac_promoted;
	return frac_promoted::from_data( frac_promoted( a ).data() + frac_promoted( b ).data() );
}

template <class AReprType, int AExponent, class BReprType, int BExponent>
constexpr auto operator-( frac<AReprType, AExponent> a, frac<BReprType, BExponent> b ) -> frac_promote<decltype( a ), decltype( b )> {
	typedef frac_promote<decltype( a ), decltype( b )> frac_promoted;
	return frac_promoted::from_data( frac_promoted( a ).data() - frac_promoted( b ).data() );
}

template <class ReprType, int Exponent>
frac<ReprType, Exponent>& operator+=( frac<ReprType, Exponent>& lhs, const frac<ReprType, Exponent>& rhs ) noexcept {
	lhs.data() += frac<ReprType, Exponent>( rhs ).data();
	return lhs;
}

template <class ReprType, int Exponent>
frac<ReprType, Exponent>& operator-=( frac<ReprType, Exponent>& lhs, const frac<ReprType, Exponent>& rhs ) noexcept {
	lhs.data() -= frac<ReprType, Exponent>( rhs ).data();
	return lhs;
}

template <class ReprType, int Exponent>
frac<ReprType, Exponent>& operator*=( frac<ReprType, Exponent>& lhs, const frac<ReprType, Exponent>& rhs ) noexcept {
	typedef wider_promote<ReprType> wider_repr_type;
	lhs.data() = static_cast<ReprType>( ( static_cast<wider_repr_type>( lhs.data() ) * static_cast<wider_repr_type>( rhs.data() ) ) >> Exponent );
	return lhs;
}

template <class ReprType, int Exponent>
frac<ReprType, Exponent>& operator/=( frac<ReprType, Exponent>& lhs, const frac<ReprType, Exponent>& rhs ) noexcept {
	typedef frac<wider_promote<ReprType>, Exponent << 1> div_promote;
	lhs.data() = static_cast<ReprType>( div_promote( lhs ).data() / rhs.data() );
	return lhs;
}

template <class LReprType, int LExponent, class Rhs, typename std::enable_if<std::is_arithmetic<Rhs>::value>::type * = nullptr>
constexpr auto operator+( const frac<LReprType, LExponent>& lhs, const Rhs& rhs ) noexcept {
	return lhs + frac<LReprType, LExponent>( rhs );
}

template <class Lhs, class RReprType, int RExponent, typename std::enable_if<std::is_arithmetic<Lhs>::value>::type * = nullptr>
constexpr auto operator+( const Lhs& lhs, const frac<RReprType, RExponent>& rhs ) noexcept {
	return frac<RReprType, RExponent>( lhs ) + rhs;
}

template <class LReprType, int LExponent, class Rhs, typename std::enable_if<std::is_arithmetic<Rhs>::value>::type * = nullptr>
constexpr auto operator-( const frac<LReprType, LExponent>& lhs, const Rhs& rhs ) noexcept {
	return lhs - frac<LReprType, LExponent>( rhs );
}

template <class Lhs, class RReprType, int RExponent, typename std::enable_if<std::is_arithmetic<Lhs>::value>::type * = nullptr>
constexpr auto operator-( const Lhs& lhs, const frac<RReprType, RExponent>& rhs ) noexcept {
	return frac<RReprType, RExponent>( lhs ) - rhs;
}

template <class AReprType, int AExponent, class BReprType, int BExponent>
constexpr auto operator*( frac<AReprType, AExponent> a, frac<BReprType, BExponent> b ) -> frac_promote<decltype( a ), decltype( b )> {
	typedef frac_promote<decltype( a ), decltype( b )> frac_promoted;
	typedef frac_promote<frac<wider_promote<AReprType>, AExponent>, frac<wider_promote<BReprType>, BExponent>> mul_promoted;
	return frac_promoted::from_data( ( mul_promoted( a ).data() * mul_promoted( b ).data() ) / ( 1 << mul_promoted::exponent ) );
}

template <class AReprType, int AExponent, class BReprType, int BExponent>
constexpr auto operator/( frac<AReprType, AExponent> a, frac<BReprType, BExponent> b ) -> frac_promote<decltype( a ), decltype( b )> {
	typedef frac_promote<decltype( a ), decltype( b )> frac_promoted;
	typedef wider_promote<typename frac_promoted::repr_type> wider_repr_type;
	typedef frac<wider_repr_type, frac_promoted::exponent << 1> div_promote;
	return frac_promoted::from_data( div_promote( a ).data() / frac_promoted( b ).data() );
}

template <class LhsReprType, int LhsExponent, class Integer, typename = typename std::enable_if<std::is_integral<Integer>::value>::type>
constexpr auto operator*( const frac<LhsReprType, LhsExponent>& lhs, const Integer& rhs ) noexcept {
	return frac<LhsReprType, LhsExponent>::from_data( lhs.data() * rhs );
}

template <class LhsReprType, int LhsExponent, class Integer, typename = typename std::enable_if<std::is_integral<Integer>::value>::type>
constexpr auto operator/( const frac<LhsReprType, LhsExponent>& lhs, const Integer& rhs ) noexcept {
	return frac<LhsReprType, LhsExponent>::from_data( lhs.data() / rhs );
}

template <class Integer, class RhsReprType, int RhsExponent, typename = typename std::enable_if<std::is_integral<Integer>::value>::type>
constexpr auto operator*( const Integer& lhs, const frac<RhsReprType, RhsExponent>& rhs ) noexcept {
	return frac<RhsReprType, RhsExponent>::from_data( lhs * rhs.data() );
}

template <class Integer, class RhsReprType, int RhsExponent, typename = typename std::enable_if<std::is_integral<Integer>::value>::type>
constexpr auto operator/( const Integer& lhs, const frac<RhsReprType, RhsExponent>& rhs ) noexcept {
	return frac<RhsReprType, RhsExponent>::from_data( lhs / rhs.data() );
}

template <class LhsReprType, int Exponent, class Rhs>
frac<LhsReprType, Exponent>& operator+=( frac<LhsReprType, Exponent>& lhs, const Rhs& rhs ) noexcept {
	lhs += frac<LhsReprType, Exponent>( rhs );
	return lhs;
}

template <class LhsReprType, int Exponent, class Rhs>
frac<LhsReprType, Exponent>& operator-=( frac<LhsReprType, Exponent>& lhs, const Rhs& rhs ) noexcept {
	lhs -= frac<LhsReprType, Exponent>( rhs );
	return lhs;
}

} // gba

#endif // GBAXX_FRAC_HPP