#ifndef GBAXX_FIXED_POINT_HPP
#define GBAXX_FIXED_POINT_HPP

#include <type_traits>

#include <gba/bios.hpp>
#include <gba/math.hpp>
#include <gba/type_promotion.hpp>

namespace gba {

template <typename ReprType = int, unsigned ExpBits = 0>
class fixed_point {
	static_assert( std::is_integral<ReprType>::value, "ReprType must be an integral type" );
	static_assert( !std::is_same<ReprType, bool>::value, "ReprType cannot be bool" );

public:
	using repr_type = ReprType;

	static constexpr auto exponent = ExpBits;
	static constexpr auto digits = ( sizeof( repr_type ) * 8 ) - ( std::is_signed<repr_type>::value ? 1 : 0 );
	static constexpr auto integer_digits = digits - exponent;
	static constexpr auto fractional_digits = exponent;

protected:
	static constexpr auto unit = static_cast<repr_type>( 1ULL << exponent );

	template <typename UIntType>
	static constexpr auto to_value( UIntType ui ) noexcept -> typename std::enable_if<std::is_integral<UIntType>::value && std::is_unsigned<UIntType>::value, repr_type>::type {
		return static_cast<repr_type>( ui ) << exponent;
	}

	template <typename IntType>
	static constexpr auto to_value( IntType i ) noexcept -> typename std::enable_if<std::is_integral<IntType>::value && std::is_signed<IntType>::value, repr_type>::type {
		return static_cast<repr_type>( i ) * unit;
	}

	template <typename FloatType>
	static constexpr auto to_value( FloatType f ) noexcept -> typename std::enable_if<std::is_floating_point<FloatType>::value, repr_type>::type {
		return static_cast<repr_type>( f * unit );
	}

	template <typename RhsReprType, unsigned RhsExpBits>
	static constexpr auto to_value( const fixed_point<RhsReprType, RhsExpBits>& x ) noexcept -> typename std::enable_if<std::is_unsigned<RhsReprType>::value && ( RhsExpBits < exponent ), repr_type>::type {
		constexpr auto shift = exponent - fixed_point<RhsReprType, RhsExpBits>::exponent;

		return static_cast<repr_type>( x.data() ) << shift;
	}

	template <typename RhsReprType, unsigned RhsExpBits>
	static constexpr auto to_value( const fixed_point<RhsReprType, RhsExpBits>& x ) noexcept -> typename std::enable_if<std::is_unsigned<RhsReprType>::value && ( RhsExpBits > exponent ), repr_type>::type {
		constexpr auto shift = fixed_point<RhsReprType, RhsExpBits>::exponent - exponent;

		return static_cast<repr_type>( x.data() >> shift );
	}

	template <typename RhsReprType, unsigned RhsExpBits>
	static constexpr auto to_value( const fixed_point<RhsReprType, RhsExpBits>& x ) noexcept -> typename std::enable_if<std::is_signed<RhsReprType>::value && ( RhsExpBits < exponent ), repr_type>::type {
		constexpr auto mul = static_cast<repr_type>( 1ULL << ( exponent - fixed_point<RhsReprType, RhsExpBits>::exponent ) );

		return static_cast<repr_type>( x.data() ) * mul;
	}

	template <typename RhsReprType, unsigned RhsExpBits>
	static constexpr auto to_value( const fixed_point<RhsReprType, RhsExpBits>& x ) noexcept -> typename std::enable_if<std::is_signed<RhsReprType>::value && ( RhsExpBits > exponent ), repr_type>::type {
		constexpr auto div = static_cast<repr_type>( 1ULL << ( fixed_point<RhsReprType, RhsExpBits>::exponent - exponent ) );

		return static_cast<repr_type>( x.data() / div );
	}

	template <typename RhsReprType, unsigned RhsExpBits>
	static constexpr auto to_value( const fixed_point<RhsReprType, RhsExpBits>& x ) noexcept -> typename std::enable_if<( RhsExpBits == exponent ), repr_type>::type {
		return static_cast<repr_type>( x.data() );
	}

public:
	static constexpr fixed_point from_data( repr_type repr ) noexcept {
		fixed_point a;
		a.m_value = repr;
		return a;
	}

	template <typename RhsReprType, unsigned RhsExpBits>
	static constexpr fixed_point reciprocal( const fixed_point<RhsReprType, RhsExpBits>& x ) noexcept {
		using lhs_wider_type = promote::make_wider<repr_type>;

		fixed_point a;
		a.m_value = ( static_cast<lhs_wider_type>( unit ) << RhsExpBits ) / x.data();
		return a;
	}

	template <typename IntType, typename std::enable_if<std::is_integral<IntType>::value && !std::is_same<IntType, bool>::value, int>::type Enable = 0>
	static constexpr fixed_point reciprocal( IntType i ) noexcept {
		fixed_point a;
		a.m_value = ( unit + i - 1 ) / i;
		return a;
	}

	template <typename FloatType, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
	static constexpr fixed_point reciprocal( FloatType f ) noexcept {
		return fixed_point( 1 / f );
	}

	// ctors

	constexpr fixed_point() noexcept : m_value( 0 ) {}

	template <typename FromType, typename std::enable_if<std::is_arithmetic<FromType>::value, int>::type Enable = 0>
	constexpr fixed_point( FromType x ) noexcept : m_value( to_value( x ) ) {}

	template <typename RhsReprType, unsigned RhsExpBits>
	constexpr fixed_point( const fixed_point<RhsReprType, RhsExpBits>& x ) noexcept : m_value( to_value( x ) ) {}

	// data accessors

	constexpr const repr_type& data() const noexcept {
		return m_value;
	}

	constexpr repr_type& data() noexcept {
		return m_value;
	}

	// type conversions

	template <typename BoolType, typename std::enable_if<std::is_same<BoolType, bool>::value, int>::type Enable = 0>
	constexpr operator BoolType() const noexcept {
		return static_cast<bool>( m_value );
	}

	template <typename UIntType, typename std::enable_if<std::is_integral<UIntType>::value && std::is_unsigned<UIntType>::value && !std::is_same<UIntType, bool>::value, int>::type Enable = 0>
	constexpr operator UIntType() const noexcept {
		using urepr_type = typename std::make_unsigned<repr_type>::type;

		return static_cast<urepr_type>( m_value ) >> exponent;
	}

	template <typename IntType, typename std::enable_if<std::is_integral<IntType>::value && std::is_signed<IntType>::value && std::is_unsigned<repr_type>::value, int>::type Enable = 0>
	constexpr operator IntType() const noexcept {
		return m_value >> exponent; // lsr
	}

	template <typename IntType, typename std::enable_if<std::is_integral<IntType>::value && std::is_signed<IntType>::value && std::is_signed<repr_type>::value, int>::type Enable = 0>
	constexpr operator IntType() const noexcept {
		return m_value >> exponent; // asr
	}

	template <typename FloatType, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
	constexpr operator FloatType() const noexcept {
		return static_cast<FloatType>( m_value ) / unit;
	}

	// constant operators

	constexpr auto operator !() const noexcept {
		return !m_value;
	}

	constexpr auto& operator +() noexcept {
		return *this;
	}

	constexpr auto operator +() const noexcept {
		return *this;
	}

	constexpr auto operator -() const noexcept {
		return fixed_point::from_data( -m_value );
	}

	// mutating operators

	constexpr auto operator ++( int ) noexcept {
		const auto copy = *this;
		m_value += unit;
		return copy;
	}

	constexpr auto operator --( int ) noexcept {
		const auto copy = *this;
		m_value -= unit;
		return copy;
	}

	constexpr auto& operator ++() noexcept {
		m_value += unit;
		return *this;
	}

	constexpr auto& operator --() noexcept {
		m_value -= unit;
		return *this;
	}

	// arithmetic mutating operators

	template <typename RhsReprType, unsigned RhsExpBits>
	constexpr auto& operator +=( const fixed_point<RhsReprType, RhsExpBits>& x ) noexcept {
		m_value += to_value( x );
		return *this;
	}

	template <typename UIntType, typename std::enable_if<std::is_integral<UIntType>::value && std::is_unsigned<UIntType>::value, int>::type Enable = 0>
	constexpr auto& operator +=( UIntType ui ) noexcept {
		m_value += to_value( ui );
		return *this;
	}

	template <typename IntType, typename std::enable_if<std::is_integral<IntType>::value && std::is_signed<IntType>::value, int>::type Enable = 0>
	constexpr auto& operator +=( IntType i ) noexcept {
		m_value += to_value( i );
		return *this;
	}

	template <typename FloatType, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
	constexpr auto& operator +=( FloatType f ) noexcept {
		m_value += to_value( f );
		return *this;
	}

	template <typename RhsReprType, unsigned RhsExpBits>
	constexpr auto& operator -=( const fixed_point<RhsReprType, RhsExpBits>& x ) noexcept {
		m_value -= to_value( x );
		return *this;
	}

	template <typename UIntType, typename std::enable_if<std::is_integral<UIntType>::value && std::is_unsigned<UIntType>::value, int>::type Enable = 0>
	constexpr auto& operator -=( UIntType ui ) noexcept {
		m_value -= to_value( ui );
		return *this;
	}

	template <typename IntType, typename std::enable_if<std::is_integral<IntType>::value && std::is_signed<IntType>::value, int>::type Enable = 0>
	constexpr auto& operator -=( IntType i ) noexcept {
		m_value -= to_value( i );
		return *this;
	}

	template <typename FloatType, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
	constexpr auto& operator -=( FloatType f ) noexcept {
		m_value -= to_value( f );
		return *this;
	}

	template <typename RhsReprType, unsigned RhsExpBits>
	constexpr auto& operator *=( const fixed_point<RhsReprType, RhsExpBits>& x ) noexcept {
		using rhs_type = fixed_point<RhsReprType, RhsExpBits>;
		using wider_repr_type = promote::copy_sign<repr_type, typename std::conditional<sizeof( repr_type ) >= sizeof( typename rhs_type::repr_type ), 
			promote::make_wider<repr_type>,
			typename rhs_type::repr_type
		>::type>;

		m_value = ( static_cast<wider_repr_type>( m_value ) * x.data() ) >> rhs_type::exponent;
		return *this;
	}

	template <typename IntType, typename std::enable_if<std::is_integral<IntType>::value, int>::type Enable = 0>
	constexpr auto& operator *=( IntType i ) noexcept {
		m_value *= i;
		return *this;
	}

	template <typename FloatType, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
	constexpr auto& operator *=( FloatType f ) noexcept {
		*this *= fixed_point( f );
		return *this;
	}

	template <typename RhsReprType, unsigned RhsExpBits>
	constexpr auto& operator /=( const fixed_point<RhsReprType, RhsExpBits>& x ) noexcept {
		using rhs_type = fixed_point<RhsReprType, RhsExpBits>;
		using wider_repr_type = promote::copy_sign<repr_type, typename std::conditional<sizeof( repr_type ) >= sizeof( typename rhs_type::repr_type ), 
			promote::make_wider<repr_type>, 
			typename rhs_type::repr_type
		>::type>;

		m_value = ( static_cast<wider_repr_type>( m_value ) << rhs_type::exponent ) / x.data();
		return *this;
	}

	template <typename IntType, typename std::enable_if<std::is_integral<IntType>::value, int>::type Enable = 0>
	constexpr auto& operator /=( IntType i ) noexcept {
		m_value /= i;
		return *this;
	}

	template <typename FloatType, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
	constexpr auto& operator /=( FloatType f ) noexcept {
		*this /= fixed_point( f );
		return *this;
	}

protected:
	repr_type   m_value;

};

// mul operators

template <typename LhsReprType, unsigned LhsExpBits, typename RhsReprType, unsigned RhsExpBits>
constexpr auto operator *( const fixed_point<LhsReprType, LhsExpBits>& a, const fixed_point<RhsReprType, RhsExpBits>& b ) noexcept {
	using lhs_type = fixed_point<LhsReprType, LhsExpBits>;
	using rhs_type = fixed_point<RhsReprType, RhsExpBits>;
	using repr_type = promote::integer<LhsReprType, RhsReprType>;

	constexpr auto exponent = ( sizeof( repr_type ) * 8 ) - ( std::is_signed<repr_type>::value ?
		std::max( sizeof( LhsReprType ) * 8 - LhsExpBits, sizeof( RhsReprType ) * 8 - RhsExpBits ) :
		std::max( lhs_type::integer_digits, rhs_type::integer_digits ) );

	using lhs_wider_type = typename std::conditional<( sizeof( repr_type ) > sizeof( LhsReprType ) ), repr_type, promote::make_wider<repr_type>>::type;
	using rhs_wider_type = typename std::conditional<( sizeof( repr_type ) > sizeof( RhsReprType ) ), repr_type, promote::make_wider<repr_type>>::type;

	constexpr auto shift = ( LhsExpBits + RhsExpBits ) - exponent;

	const auto value = ( static_cast<lhs_wider_type>( a.data() ) * static_cast<rhs_wider_type>( b.data() ) ) >> shift;

	return fixed_point<repr_type, exponent>::from_data( value );
}

template <typename ReprType, unsigned ExpBits, typename IntType, typename std::enable_if<std::is_integral<IntType>::value, int>::type Enable = 0>
constexpr auto operator *( const fixed_point<ReprType, ExpBits>& a, IntType b ) noexcept {
	using repr_type = promote::integer<ReprType, IntType>;

	using lhs_wider_type = typename std::conditional<( sizeof( repr_type ) > sizeof( ReprType ) ), repr_type, promote::make_wider<repr_type>>::type;
	using rhs_wider_type = typename std::conditional<( sizeof( repr_type ) > sizeof( IntType ) ), repr_type, promote::make_wider<repr_type>>::type;

	return fixed_point<repr_type, ExpBits>::from_data( static_cast<lhs_wider_type>( a.data() ) * static_cast<rhs_wider_type>( b ) );
}

template <typename ReprType, unsigned ExpBits, typename FloatType, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
constexpr auto operator *( const fixed_point<ReprType, ExpBits>& a, FloatType b ) noexcept {
	using lhs_type = fixed_point<ReprType, ExpBits>;

	return a * lhs_type( b ); 
}

template <typename IntType, typename ReprType, unsigned ExpBits, typename std::enable_if<std::is_integral<IntType>::value, int>::type Enable = 0>
constexpr auto operator *( IntType a, const fixed_point<ReprType, ExpBits>& b ) noexcept {
	using repr_type = promote::integer<ReprType, IntType>;

	using lhs_wider_type = typename std::conditional<( sizeof( repr_type ) > sizeof( ReprType ) ), repr_type, promote::make_wider<repr_type>>::type;
	using rhs_wider_type = typename std::conditional<( sizeof( repr_type ) > sizeof( IntType ) ), repr_type, promote::make_wider<repr_type>>::type;

	return fixed_point<repr_type, ExpBits>::from_data( static_cast<rhs_wider_type>( a ) * static_cast<lhs_wider_type>( b.data() ) );
}

template <typename FloatType, typename ReprType, unsigned ExpBits, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
constexpr auto operator *( FloatType a, const fixed_point<ReprType, ExpBits>& b ) noexcept {
	using rhs_type = fixed_point<ReprType, ExpBits>;

	return rhs_type( a ) * b; 
}

// div operators

template <typename LhsReprType, unsigned LhsExpBits, typename RhsReprType, unsigned RhsExpBits>
constexpr auto operator /( const fixed_point<LhsReprType, LhsExpBits>& a, const fixed_point<RhsReprType, RhsExpBits>& b ) noexcept {
	using lhs_type = fixed_point<LhsReprType, LhsExpBits>;
	using rhs_type = fixed_point<RhsReprType, RhsExpBits>;
	using repr_type = promote::integer<LhsReprType, RhsReprType>;

	using lhs_wider_type = typename std::conditional<( sizeof( repr_type ) > sizeof( LhsReprType ) ), repr_type, promote::make_wider<repr_type>>::type;
	using rhs_wider_type = typename std::conditional<( sizeof( repr_type ) > sizeof( RhsReprType ) ), repr_type, promote::make_wider<repr_type>>::type;

	constexpr auto exponent = ( sizeof( repr_type ) * 8 ) - ( std::is_signed<repr_type>::value ?
		std::max( sizeof( LhsReprType ) * 8 - LhsExpBits, sizeof( RhsReprType ) * 8 - RhsExpBits ) :
		std::max( lhs_type::integer_digits, rhs_type::integer_digits ) );

	constexpr auto left_shift = ( exponent > LhsExpBits ? exponent - LhsExpBits : 0 );
	constexpr auto right_shift = ( LhsExpBits > exponent ? LhsExpBits - exponent : 0 );

	const auto data = ( static_cast<lhs_wider_type>( a.data() ) << RhsExpBits ) / static_cast<rhs_wider_type>( b.data() );
	return fixed_point<repr_type, exponent>::from_data( ( data << left_shift ) >> right_shift );
}

template <typename ReprType, unsigned ExpBits, typename IntType, typename std::enable_if<std::is_integral<IntType>::value, int>::type Enable = 0>
constexpr auto operator /( const fixed_point<ReprType, ExpBits>& a, IntType b ) noexcept {
	using repr_type = promote::integer<ReprType, IntType>;

	using lhs_wider_type = typename std::conditional<( sizeof( repr_type ) > sizeof( ReprType ) ), repr_type, promote::make_wider<repr_type>>::type;
	using rhs_wider_type = typename std::conditional<( sizeof( repr_type ) > sizeof( IntType ) ), repr_type, promote::make_wider<repr_type>>::type;

	return fixed_point<repr_type, ExpBits>::from_data( static_cast<lhs_wider_type>( a.data() ) / static_cast<rhs_wider_type>( b ) );
}

template <typename ReprType, unsigned ExpBits, typename FloatType, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
constexpr auto operator /( const fixed_point<ReprType, ExpBits>& a, FloatType b ) noexcept {
	using lhs_type = fixed_point<ReprType, ExpBits>;

	return a / lhs_type( b ); 
}

template <typename IntType, typename ReprType, unsigned ExpBits, typename std::enable_if<std::is_integral<IntType>::value, int>::type Enable = 0>
constexpr auto operator /( IntType a, const fixed_point<ReprType, ExpBits>& b ) noexcept {
	using rhs_type = fixed_point<IntType>;

	return rhs_type( a ) / b;
}

template <typename FloatType, typename ReprType, unsigned ExpBits, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
constexpr auto operator /( FloatType a, const fixed_point<ReprType, ExpBits>& b ) noexcept {
	using rhs_type = fixed_point<ReprType, ExpBits>;

	return rhs_type( a ) / b; 
}

// add operators

template <typename LhsReprType, unsigned LhsExpBits, typename RhsReprType, unsigned RhsExpBits>
constexpr auto operator +( const fixed_point<LhsReprType, LhsExpBits>& a, const fixed_point<RhsReprType, RhsExpBits>& b ) noexcept {
	using lhs_type = fixed_point<LhsReprType, LhsExpBits>;
	using rhs_type = fixed_point<RhsReprType, RhsExpBits>;
	using repr_type = promote::integer<LhsReprType, RhsReprType>;

	constexpr auto exponent = ( sizeof( repr_type ) * 8 ) - ( std::is_signed<repr_type>::value ?
		std::max( sizeof( LhsReprType ) * 8 - LhsExpBits, sizeof( RhsReprType ) * 8 - RhsExpBits ) :
		std::max( lhs_type::integer_digits, rhs_type::integer_digits ) );

	using fixed_type = fixed_point<repr_type, exponent>;

	return fixed_type::from_data( fixed_type( a ).data() + fixed_type( b ).data() );
}

template <typename ReprType, unsigned ExpBits, typename IntType, typename std::enable_if<std::is_integral<IntType>::value, int>::type Enable = 0>
constexpr auto operator +( const fixed_point<ReprType, ExpBits>& a, IntType b ) noexcept {
	using lhs_type = fixed_point<ReprType, ExpBits>;

	return lhs_type::from_data( a.data() + lhs_type( b ).data() );
}

template <typename ReprType, unsigned ExpBits, typename FloatType, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
constexpr auto operator +( const fixed_point<ReprType, ExpBits>& a, FloatType b ) noexcept {
	using lhs_type = fixed_point<ReprType, ExpBits>;

	return lhs_type::from_data( a.data() + lhs_type( b ).data() );
}

template <typename IntType, typename ReprType, unsigned ExpBits, typename std::enable_if<std::is_integral<IntType>::value, int>::type Enable = 0>
constexpr auto operator +( IntType a, const fixed_point<ReprType, ExpBits>& b ) noexcept {
	using rhs_type = fixed_point<ReprType, ExpBits>;

	return rhs_type::from_data( rhs_type( a ).data() + b.data() );
}

template <typename FloatType, typename ReprType, unsigned ExpBits, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
constexpr auto operator +( FloatType a, const fixed_point<ReprType, ExpBits>& b ) noexcept {
	using rhs_type = fixed_point<ReprType, ExpBits>;

	return rhs_type::from_data( rhs_type( a ).data() + b.data() );
}

// sub operators

template <typename LhsReprType, unsigned LhsExpBits, typename RhsReprType, unsigned RhsExpBits>
constexpr auto operator -( const fixed_point<LhsReprType, LhsExpBits>& a, const fixed_point<RhsReprType, RhsExpBits>& b ) noexcept {
	using lhs_type = fixed_point<LhsReprType, LhsExpBits>;
	using rhs_type = fixed_point<RhsReprType, RhsExpBits>;
	using repr_type = promote::integer<LhsReprType, RhsReprType>;

	constexpr auto exponent = ( sizeof( repr_type ) * 8 ) - ( std::is_signed<repr_type>::value ?
		std::max( sizeof( LhsReprType ) * 8 - LhsExpBits, sizeof( RhsReprType ) * 8 - RhsExpBits ) :
		std::max( lhs_type::integer_digits, rhs_type::integer_digits ) );

	using fixed_type = fixed_point<repr_type, exponent>;

	return fixed_type::from_data( fixed_type( a ).data() - fixed_type( b ).data() );
}

template <typename ReprType, unsigned ExpBits, typename IntType, typename std::enable_if<std::is_integral<IntType>::value, int>::type Enable = 0>
constexpr auto operator -( const fixed_point<ReprType, ExpBits>& a, IntType b ) noexcept {
	using lhs_type = fixed_point<ReprType, ExpBits>;

	return lhs_type::from_data( a.data() - lhs_type( b ).data() );
}

template <typename ReprType, unsigned ExpBits, typename FloatType, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
constexpr auto operator -( const fixed_point<ReprType, ExpBits>& a, FloatType b ) noexcept {
	using lhs_type = fixed_point<ReprType, ExpBits>;

	return lhs_type::from_data( a.data() - lhs_type( b ).data() );
}

template <typename IntType, typename ReprType, unsigned ExpBits, typename std::enable_if<std::is_integral<IntType>::value, int>::type Enable = 0>
constexpr auto operator -( IntType a, const fixed_point<ReprType, ExpBits>& b ) noexcept {
	using rhs_type = fixed_point<ReprType, ExpBits>;

	return rhs_type::from_data( rhs_type( a ).data() - b.data() );
}

template <typename FloatType, typename ReprType, unsigned ExpBits, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
constexpr auto operator -( FloatType a, const fixed_point<ReprType, ExpBits>& b ) noexcept {
	using rhs_type = fixed_point<ReprType, ExpBits>;

	return rhs_type::from_data( rhs_type( a ).data() - b.data() );
}

// bool operators

template <typename LhsReprType, unsigned LhsExpBits, typename RhsReprType, unsigned RhsExpBits>
constexpr auto operator ==( const fixed_point<LhsReprType, LhsExpBits>& a, const fixed_point<RhsReprType, RhsExpBits>& b ) noexcept {
	using lhs_type = fixed_point<LhsReprType, LhsExpBits>;
	using rhs_type = fixed_point<RhsReprType, RhsExpBits>;
	using repr_type = promote::integer<LhsReprType, RhsReprType>;

	constexpr auto exponent = ( sizeof( repr_type ) * 8 ) - ( std::is_signed<repr_type>::value ?
		std::max( sizeof( LhsReprType ) * 8 - LhsExpBits, sizeof( RhsReprType ) * 8 - RhsExpBits ) :
		std::max( lhs_type::integer_digits, rhs_type::integer_digits ) );

	using fixed_type = fixed_point<repr_type, exponent>;

	return fixed_type( a ).data() == fixed_type( b ).data();
}

template <typename ReprType, unsigned ExpBits, typename IntType, typename std::enable_if<std::is_integral<IntType>::value, int>::type Enable = 0>
constexpr auto operator ==( const fixed_point<ReprType, ExpBits>& a, IntType b ) noexcept {
	using lhs_type = fixed_point<ReprType, ExpBits>;

	return a.data() == lhs_type( b ).data();
}

template <typename ReprType, unsigned ExpBits, typename FloatType, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
constexpr auto operator ==( const fixed_point<ReprType, ExpBits>& a, FloatType b ) noexcept {
	using lhs_type = fixed_point<ReprType, ExpBits>;

	return a.data() == lhs_type( b ).data();
}

template <typename IntType, typename ReprType, unsigned ExpBits, typename std::enable_if<std::is_integral<IntType>::value, int>::type Enable = 0>
constexpr auto operator ==( IntType a, const fixed_point<ReprType, ExpBits>& b ) noexcept {
	using rhs_type = fixed_point<ReprType, ExpBits>;

	return rhs_type( a ).data() == b.data();
}

template <typename FloatType, typename ReprType, unsigned ExpBits, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
constexpr auto operator ==( FloatType a, const fixed_point<ReprType, ExpBits>& b ) noexcept {
	using rhs_type = fixed_point<ReprType, ExpBits>;

	return rhs_type( a ).data() == b.data();
}

template <typename LhsReprType, unsigned LhsExpBits, typename RhsReprType, unsigned RhsExpBits>
constexpr auto operator !=( const fixed_point<LhsReprType, LhsExpBits>& a, const fixed_point<RhsReprType, RhsExpBits>& b ) noexcept {
	using lhs_type = fixed_point<LhsReprType, LhsExpBits>;
	using rhs_type = fixed_point<RhsReprType, RhsExpBits>;
	using repr_type = promote::integer<LhsReprType, RhsReprType>;

	constexpr auto exponent = ( sizeof( repr_type ) * 8 ) - ( std::is_signed<repr_type>::value ?
		std::max( sizeof( LhsReprType ) * 8 - LhsExpBits, sizeof( RhsReprType ) * 8 - RhsExpBits ) :
		std::max( lhs_type::integer_digits, rhs_type::integer_digits ) );

	using fixed_type = fixed_point<repr_type, exponent>;

	return fixed_type( a ).data() != fixed_type( b ).data();
}

template <typename ReprType, unsigned ExpBits, typename IntType, typename std::enable_if<std::is_integral<IntType>::value, int>::type Enable = 0>
constexpr auto operator !=( const fixed_point<ReprType, ExpBits>& a, IntType b ) noexcept {
	using lhs_type = fixed_point<ReprType, ExpBits>;

	return a.data() != lhs_type( b ).data();
}

template <typename ReprType, unsigned ExpBits, typename FloatType, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
constexpr auto operator !=( const fixed_point<ReprType, ExpBits>& a, FloatType b ) noexcept {
	using lhs_type = fixed_point<ReprType, ExpBits>;

	return a.data() != lhs_type( b ).data();
}

template <typename IntType, typename ReprType, unsigned ExpBits, typename std::enable_if<std::is_integral<IntType>::value, int>::type Enable = 0>
constexpr auto operator !=( IntType a, const fixed_point<ReprType, ExpBits>& b ) noexcept {
	using rhs_type = fixed_point<ReprType, ExpBits>;

	return rhs_type( a ).data() != b.data();
}

template <typename FloatType, typename ReprType, unsigned ExpBits, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
constexpr auto operator !=( FloatType a, const fixed_point<ReprType, ExpBits>& b ) noexcept {
	using rhs_type = fixed_point<ReprType, ExpBits>;

	return rhs_type( a ).data() != b.data();
}

// comparison operators

template <typename LhsReprType, unsigned LhsExpBits, typename RhsReprType, unsigned RhsExpBits>
constexpr auto operator <( const fixed_point<LhsReprType, LhsExpBits>& a, const fixed_point<RhsReprType, RhsExpBits>& b ) noexcept {
	using lhs_type = fixed_point<LhsReprType, LhsExpBits>;
	using rhs_type = fixed_point<RhsReprType, RhsExpBits>;
	using repr_type = promote::integer<LhsReprType, RhsReprType>;

	constexpr auto exponent = ( sizeof( repr_type ) * 8 ) - ( std::is_signed<repr_type>::value ?
		std::max( sizeof( LhsReprType ) * 8 - LhsExpBits, sizeof( RhsReprType ) * 8 - RhsExpBits ) :
		std::max( lhs_type::integer_digits, rhs_type::integer_digits ) );

	using fixed_type = fixed_point<repr_type, exponent>;

	return fixed_type( a ).data() < fixed_type( b ).data();
}

template <typename ReprType, unsigned ExpBits, typename IntType, typename std::enable_if<std::is_integral<IntType>::value, int>::type Enable = 0>
constexpr auto operator <( const fixed_point<ReprType, ExpBits>& a, IntType b ) noexcept {
	using lhs_type = fixed_point<ReprType, ExpBits>;

	return a.data() < lhs_type( b ).data();
}

template <typename ReprType, unsigned ExpBits, typename FloatType, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
constexpr auto operator <( const fixed_point<ReprType, ExpBits>& a, FloatType b ) noexcept {
	using lhs_type = fixed_point<ReprType, ExpBits>;

	return a.data() < lhs_type( b ).data();
}

template <typename IntType, typename ReprType, unsigned ExpBits, typename std::enable_if<std::is_integral<IntType>::value, int>::type Enable = 0>
constexpr auto operator <( IntType a, const fixed_point<ReprType, ExpBits>& b ) noexcept {
	using rhs_type = fixed_point<ReprType, ExpBits>;

	return rhs_type( a ).data() < b.data();
}

template <typename FloatType, typename ReprType, unsigned ExpBits, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
constexpr auto operator <( FloatType a, const fixed_point<ReprType, ExpBits>& b ) noexcept {
	using rhs_type = fixed_point<ReprType, ExpBits>;

	return rhs_type( a ).data() < b.data();
}

template <typename LhsReprType, unsigned LhsExpBits, typename RhsReprType, unsigned RhsExpBits>
constexpr auto operator <=( const fixed_point<LhsReprType, LhsExpBits>& a, const fixed_point<RhsReprType, RhsExpBits>& b ) noexcept {
	using lhs_type = fixed_point<LhsReprType, LhsExpBits>;
	using rhs_type = fixed_point<RhsReprType, RhsExpBits>;
	using repr_type = promote::integer<LhsReprType, RhsReprType>;

	constexpr auto exponent = ( sizeof( repr_type ) * 8 ) - ( std::is_signed<repr_type>::value ?
		std::max( sizeof( LhsReprType ) * 8 - LhsExpBits, sizeof( RhsReprType ) * 8 - RhsExpBits ) :
		std::max( lhs_type::integer_digits, rhs_type::integer_digits ) );

	using fixed_type = fixed_point<repr_type, exponent>;

	return fixed_type( a ).data() <= fixed_type( b ).data();
}

template <typename ReprType, unsigned ExpBits, typename IntType, typename std::enable_if<std::is_integral<IntType>::value, int>::type Enable = 0>
constexpr auto operator <=( const fixed_point<ReprType, ExpBits>& a, IntType b ) noexcept {
	using lhs_type = fixed_point<ReprType, ExpBits>;

	return a.data() <= lhs_type( b ).data();
}

template <typename ReprType, unsigned ExpBits, typename FloatType, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
constexpr auto operator <=( const fixed_point<ReprType, ExpBits>& a, FloatType b ) noexcept {
	using lhs_type = fixed_point<ReprType, ExpBits>;

	return a.data() <= lhs_type( b ).data();
}

template <typename IntType, typename ReprType, unsigned ExpBits, typename std::enable_if<std::is_integral<IntType>::value, int>::type Enable = 0>
constexpr auto operator <=( IntType a, const fixed_point<ReprType, ExpBits>& b ) noexcept {
	using rhs_type = fixed_point<ReprType, ExpBits>;

	return rhs_type( a ).data() <= b.data();
}

template <typename FloatType, typename ReprType, unsigned ExpBits, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
constexpr auto operator <=( FloatType a, const fixed_point<ReprType, ExpBits>& b ) noexcept {
	using rhs_type = fixed_point<ReprType, ExpBits>;

	return rhs_type( a ).data() <= b.data();
}

template <typename LhsReprType, unsigned LhsExpBits, typename RhsReprType, unsigned RhsExpBits>
constexpr auto operator >( const fixed_point<LhsReprType, LhsExpBits>& a, const fixed_point<RhsReprType, RhsExpBits>& b ) noexcept {
	using lhs_type = fixed_point<LhsReprType, LhsExpBits>;
	using rhs_type = fixed_point<RhsReprType, RhsExpBits>;
	using repr_type = promote::integer<LhsReprType, RhsReprType>;

	constexpr auto exponent = ( sizeof( repr_type ) * 8 ) - ( std::is_signed<repr_type>::value ?
		std::max( sizeof( LhsReprType ) * 8 - LhsExpBits, sizeof( RhsReprType ) * 8 - RhsExpBits ) :
		std::max( lhs_type::integer_digits, rhs_type::integer_digits ) );

	using fixed_type = fixed_point<repr_type, exponent>;

	return fixed_type( a ).data() > fixed_type( b ).data();
}

template <typename ReprType, unsigned ExpBits, typename IntType, typename std::enable_if<std::is_integral<IntType>::value, int>::type Enable = 0>
constexpr auto operator >( const fixed_point<ReprType, ExpBits>& a, IntType b ) noexcept {
	using lhs_type = fixed_point<ReprType, ExpBits>;

	return a.data() > lhs_type( b ).data();
}

template <typename ReprType, unsigned ExpBits, typename FloatType, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
constexpr auto operator >( const fixed_point<ReprType, ExpBits>& a, FloatType b ) noexcept {
	using lhs_type = fixed_point<ReprType, ExpBits>;

	return a.data() > lhs_type( b ).data();
}

template <typename IntType, typename ReprType, unsigned ExpBits, typename std::enable_if<std::is_integral<IntType>::value, int>::type Enable = 0>
constexpr auto operator >( IntType a, const fixed_point<ReprType, ExpBits>& b ) noexcept {
	using rhs_type = fixed_point<ReprType, ExpBits>;

	return rhs_type( a ).data() > b.data();
}

template <typename FloatType, typename ReprType, unsigned ExpBits, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
constexpr auto operator >( FloatType a, const fixed_point<ReprType, ExpBits>& b ) noexcept {
	using rhs_type = fixed_point<ReprType, ExpBits>;

	return rhs_type( a ).data() > b.data();
}

template <typename LhsReprType, unsigned LhsExpBits, typename RhsReprType, unsigned RhsExpBits>
constexpr auto operator >=( const fixed_point<LhsReprType, LhsExpBits>& a, const fixed_point<RhsReprType, RhsExpBits>& b ) noexcept {
	using lhs_type = fixed_point<LhsReprType, LhsExpBits>;
	using rhs_type = fixed_point<RhsReprType, RhsExpBits>;
	using repr_type = promote::integer<LhsReprType, RhsReprType>;

	constexpr auto exponent = ( sizeof( repr_type ) * 8 ) - ( std::is_signed<repr_type>::value ?
		std::max( sizeof( LhsReprType ) * 8 - LhsExpBits, sizeof( RhsReprType ) * 8 - RhsExpBits ) :
		std::max( lhs_type::integer_digits, rhs_type::integer_digits ) );

	using fixed_type = fixed_point<repr_type, exponent>;

	return fixed_type( a ).data() >= fixed_type( b ).data();
}

template <typename ReprType, unsigned ExpBits, typename IntType, typename std::enable_if<std::is_integral<IntType>::value, int>::type Enable = 0>
constexpr auto operator >=( const fixed_point<ReprType, ExpBits>& a, IntType b ) noexcept {
	using lhs_type = fixed_point<ReprType, ExpBits>;

	return a.data() >= lhs_type( b ).data();
}

template <typename ReprType, unsigned ExpBits, typename FloatType, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
constexpr auto operator >=( const fixed_point<ReprType, ExpBits>& a, FloatType b ) noexcept {
	using lhs_type = fixed_point<ReprType, ExpBits>;

	return a.data() >= lhs_type( b ).data();
}

template <typename IntType, typename ReprType, unsigned ExpBits, typename std::enable_if<std::is_integral<IntType>::value, int>::type Enable = 0>
constexpr auto operator >=( IntType a, const fixed_point<ReprType, ExpBits>& b ) noexcept {
	using rhs_type = fixed_point<ReprType, ExpBits>;

	return rhs_type( a ).data() >= b.data();
}

template <typename FloatType, typename ReprType, unsigned ExpBits, typename std::enable_if<std::is_floating_point<FloatType>::value, int>::type Enable = 0>
constexpr auto operator >=( FloatType a, const fixed_point<ReprType, ExpBits>& b ) noexcept {
	using rhs_type = fixed_point<ReprType, ExpBits>;

	return rhs_type( a ).data() >= b.data();
}

template <unsigned IntegerBits, unsigned FractionalBits = 0>
using make_fixed = fixed_point<typename int_type<IntegerBits + FractionalBits>::type, FractionalBits>;

template <unsigned IntegerBits, unsigned FractionalBits = 0>
using make_ufixed = fixed_point<typename uint_type<IntegerBits + FractionalBits>::type, FractionalBits>;

namespace math {
namespace detail {

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

template <typename ReprType, unsigned Exponent>
constexpr auto sqrt( const fixed_point<ReprType, Exponent>& x ) noexcept {
	if ( __builtin_constant_p( x.data() ) ) {
		using widened_type = fixed_point<promote::make_wider<ReprType>, Exponent * 2>;
		return fixed_point<ReprType, Exponent>::from_data( static_cast<ReprType>( math::detail::sqrt_solve1( widened_type( x ).data() ) ) );
	}
	return bios::sqrt( x );
}

template <typename ReprType, unsigned Exponent>
constexpr auto sin( const fixed_point<ReprType, Exponent>& radian ) noexcept {
	return math::detail::sin_bam16( math::detail::radian_to_bam16( radian ) );
}

template <typename ReprType, unsigned Exponent>
constexpr auto cos( const fixed_point<ReprType, Exponent>& radian ) noexcept {
	return math::detail::sin_bam16( math::detail::radian_to_bam16( radian ) + 0x2000 );
}

template <class S, typename std::enable_if<std::is_arithmetic<S>::value, int>::type Dummy = 0>
constexpr auto sin( const S radian ) noexcept {
	return math::detail::sin_bam16( math::detail::radian_to_bam16( make_ufixed<13, 19>( radian ) ) );
}

template <class S, typename std::enable_if<std::is_arithmetic<S>::value, int>::type Dummy = 0>
constexpr auto cos( const S radian ) noexcept {
	return math::detail::sin_bam16( math::detail::radian_to_bam16( make_ufixed<13, 19>( radian ) ) + 0x2000 );
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

template <typename ReprType, unsigned Exponent>
constexpr auto signbit( const fixed_point<ReprType, Exponent>& x ) noexcept -> typename std::enable_if<std::is_unsigned<ReprType>::value, bool>::type {
	return false;
}

template <typename ReprType, unsigned Exponent>
constexpr auto signbit( const fixed_point<ReprType, Exponent>& x ) noexcept -> typename std::enable_if<std::is_signed<ReprType>::value, bool>::type {
	return x.data() < 0;
}

template <typename ReprType, unsigned Exponent>
constexpr auto round( const fixed_point<ReprType, Exponent>& x ) noexcept {
	const auto halfBit = x.data() & ( 1 << ( Exponent - 1 ) );
	return ( x.data() + ( halfBit << 1 ) ) >> Exponent;
}

template <typename ReprType, unsigned Exponent>
constexpr auto floor( const fixed_point<ReprType, Exponent>& x ) noexcept {
	return static_cast<ReprType>( x );
}

template <typename ReprType, unsigned Exponent>
constexpr auto ceil( const fixed_point<ReprType, Exponent>& x ) noexcept {
	constexpr auto mask = ( 1 << Exponent ) - 1;
	const auto fractional = x.data() & mask;
	return static_cast<ReprType>( x ) + ( fractional ? 1 : 0 );
}

template <typename ReprType, unsigned Exponent>
constexpr auto trunc( const fixed_point<ReprType, Exponent>& x ) noexcept -> typename std::enable_if<std::is_unsigned<ReprType>::value, ReprType>::type {
	return floor( x );
}

template <typename ReprType, unsigned Exponent>
constexpr auto trunc( const fixed_point<ReprType, Exponent>& x ) noexcept -> typename std::enable_if<std::is_signed<ReprType>::value, ReprType>::type {
	if ( x.data() < 0 ) {
		return ceil( x );
	}
	return floor( x );
}

} // math

namespace bios {

	/// @ingroup bios_math
	/// @brief Returns the fixed-point square root of x
	/// @param x gba::fixed_point
	/// @return square root of x
	template <typename ReprType, unsigned ExpBits>
	[[gnu::const]]
	auto sqrt( const fixed_point<ReprType, ExpBits>& x ) noexcept {
		using exp_even_type = fixed_point<uint32, ExpBits - ( ExpBits % 2 )>;
		using exp_half_type = fixed_point<uint32, exp_even_type::exponent / 2>;

		const auto resultData = swi::sqrt( exp_even_type( x ).data() );
		const auto resultFixed = exp_half_type::from_data( resultData );
		return fixed_point<ReprType, ExpBits>( resultFixed );
	}

	/// @ingroup bios_math
	/// @brief Returns the principal value of the arc tangent of x, expressed in radians
	/// @param x gba::fixed_point
	/// @return arctan of x
	template <typename ReprType, unsigned ExpBits>
	[[gnu::const]]
	auto arc_tan( const fixed_point<ReprType, ExpBits>& x ) noexcept -> typename std::enable_if<std::is_signed<ReprType>::value, fixed_point<ReprType, ExpBits>>::type {
		using fixed_type = fixed_point<ReprType, ExpBits>;
		using fixed14_type = fixed_point<int32, 14>;

		constexpr auto halfPi = math::constants<fixed14_type::exponent>::pi / 2;

		const auto resultData = swi::arc_tan( fixed14_type( x ).data() );
		const auto resultFixed = fixed14_type::from_data( resultData ); // -1 .. 1
		return static_cast<fixed_type>( resultFixed * halfPi ); // -pi/2 .. +pi/2
	}

	/// @ingroup bios_math
	/// @brief Computes the arc tangent of y/x using the signs of arguments to determine the correct quadrant
	/// @param x gba::fixed_point (signed)
	/// @param y gba::fixed_point (signed)
	/// @return promoted fixed_point between -pi and +pi
	template <typename LhsReprType, unsigned LhsExpBits, typename RhsReprType, unsigned RhsExpBits, typename = typename std::enable_if<std::is_signed<LhsReprType>::value && std::is_signed<RhsReprType>::value, void>::type>
	[[gnu::const]]
	auto arc_tan2( const fixed_point<LhsReprType, LhsExpBits>& x, const fixed_point<RhsReprType, RhsExpBits>& y ) noexcept {
		using repr_type = promote::integer<LhsReprType, RhsReprType>;

		constexpr auto exponent = ( sizeof( repr_type ) * 8 ) - std::max( sizeof( LhsReprType ) * 8 - LhsExpBits, sizeof( RhsReprType ) * 8 - RhsExpBits );

		using fixed14_type = fixed_point<repr_type, 14>;
		using fixed15_type = fixed_point<int16, 15>;
		using fixed_type = fixed_point<repr_type, exponent>;

		constexpr auto pi = math::constants<fixed15_type::exponent>::pi;

		const auto a = fixed14_type( x ).data();
		const auto b = fixed14_type( y ).data();
		const auto resultData = swi::arc_tan2( a, b );
		const auto resultFixed = fixed15_type::from_data( resultData ); // -1..+1
		return static_cast<fixed_type>( resultFixed * pi ); // -pi..+pi
	}

} // bios
} // gba

template <typename ReprType, unsigned Exponent>
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

#endif // define GBAXX_FIXED_POINT_HPP
