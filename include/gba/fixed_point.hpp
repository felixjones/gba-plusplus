#ifndef GBAXX_FIXED_POINT_HPP
#define GBAXX_FIXED_POINT_HPP

#include <type_traits>
#include <limits>

#include <gba/int.hpp>
#include <gba/int_type.hpp>

namespace gba {

template <typename Container, unsigned int Exponent = 0, bool Fast = false>
class fixed_point {
	static_assert( std::numeric_limits<Container>::is_integer, "fixed_point Container must be integer type" );
public:
	using value_type = Container;

	constexpr fixed_point() : m_value {} {}

	template <typename FloatType, typename = std::enable_if<std::is_floating_point<FloatType>::value>>
	constexpr fixed_point( FloatType value ) : m_value {} {
		operator=( value );
	}

	constexpr fixed_point( value_type value ) : m_value {} {
		operator=( value );
	}

	template <typename FloatType, typename = std::enable_if<std::is_floating_point<FloatType>::value>>
	constexpr fixed_point & operator=( FloatType value ) {
		m_value = value * ( 1 << Exponent );
		return *this;
	}

	constexpr fixed_point& operator=( value_type value ) {
		using uvalue_type = typename uint_size_type<sizeof( value_type )>::fast;

		m_value = static_cast<uvalue_type>( value ) << Exponent;
		if ( std::numeric_limits<value_type>::is_signed && value < 0 && Fast == false ) {
			// Negative numbers need sign to be restored
			m_value |= ( 1 << ( sizeof( value_type ) * 8 - 1 ) );
		}
		return *this;
	}

	template <typename FloatType, typename = std::enable_if<std::is_floating_point<FloatType>::value>>
	constexpr operator FloatType() const {
		return m_value / static_cast<FloatType>( 1 << Exponent );
	}

	constexpr operator value_type() const {
		using uvalue_type = typename uint_size_type<sizeof( value_type )>::fast;

		if ( std::numeric_limits<value_type>::is_signed && m_value < 0 && Fast == false ) {
			// Negative numbers have their high bits padded with 0xff
			constexpr auto minus_bits = ~( static_cast<uvalue_type>( -1 ) >> Exponent );
			return ( minus_bits | ( static_cast<uvalue_type>( m_value ) >> Exponent ) ) + 1;
		} else {
			return static_cast<uvalue_type>( m_value ) >> Exponent;
		}
	}

private:
	value_type	m_value;

};

template <typename Container, unsigned int Exponent = 0>
using fixed_point_fast = fixed_point<Container, Exponent, true>;

} // gba

#endif // define GBAXX_FIXED_POINT_HPP