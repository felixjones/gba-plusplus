#ifndef GBAXX_PACKED_INT_HPP
#define GBAXX_PACKED_INT_HPP

#include <type_traits>
#include <cmath>
#include <limits>

#include <gba/int_type.hpp>

namespace gba {

template <typename Container, unsigned int Size>
class packed_int {
	static_assert( std::numeric_limits<Container>::is_integer, "packed_int Container must be integer type" );
public:
	using value_type = Container;
	using machine_type = typename std::conditional<std::is_signed<value_type>::value, typename int_size_type<sizeof( value_type ) * Size>::fast, typename uint_size_type<sizeof( value_type ) * Size>::fast>::type;

	constexpr packed_int() : m_data {} {}

	constexpr packed_int( machine_type value ) : m_data {} {
		operator=( value );
	}

	constexpr packed_int& operator=( machine_type value ) {
		for ( unsigned int ii = 0; ii < Size; ++ii ) {
			m_data[ii] = value >> ( ii * ( 8 * sizeof( value_type ) ) );
		}
		return *this;
	}

	constexpr operator machine_type() const {
		// Negative numbers have their high bits padded with 0xff
		machine_type value = ( std::is_signed<value_type>::value && sizeof( machine_type ) > ( sizeof( value_type ) * Size ) && m_data[Size - 1] < 0 ) ? static_cast<typename std::make_unsigned<machine_type>::type>( -1 ) << ( Size * ( 8 * sizeof( value_type ) ) ) : 0;

		for ( unsigned int ii = 0; ii < Size; ++ii ) {
			value |= static_cast<typename std::make_unsigned<value_type>::type>( m_data[ii] ) << ( ii * ( 8 * sizeof( value_type ) ) );
		}

		return value;
	}

	constexpr packed_int& operator++() {
		operator=( *this + 1 );
		return *this;
	}

	constexpr packed_int operator++( int ) {
		packed_int value = *this;
		operator=( *this + 1 );
		return value;
	}

	constexpr packed_int& operator--() {
		operator=( *this + 1 );
		return *this;
	}

	constexpr packed_int operator--( int ) {
		packed_int value = *this;
		operator=( *this + 1 );
		return value;
	}

	constexpr packed_int& operator+=( machine_type rhs ) {
		operator=( *this + rhs );
		return *this;
	}

	constexpr packed_int& operator-=( machine_type rhs ) {
		operator=( *this - rhs );
		return *this;
	}

	constexpr packed_int& operator*=( machine_type rhs ) {
		operator=( *this * rhs );
		return *this;
	}

	constexpr packed_int& operator/=( machine_type rhs ) {
		operator=( *this / rhs );
		return *this;
	}

	constexpr packed_int& operator%=( machine_type rhs ) {
		operator=( *this % rhs );
		return *this;
	}

	constexpr packed_int& operator>>=( machine_type rhs ) {
		operator=( *this >> rhs );
		return *this;
	}

	constexpr packed_int& operator<<=( machine_type rhs ) {
		operator=( *this << rhs );
		return *this;
	}

	constexpr packed_int& operator|=( machine_type rhs ) {
		operator=( *this | rhs );
		return *this;
	}

	constexpr packed_int& operator&=( machine_type rhs ) {
		operator=( *this & rhs );
		return *this;
	}

	constexpr packed_int& operator^=( machine_type rhs ) {
		operator=( *this ^ rhs );
		return *this;
	}

	constexpr packed_int& operator|=( const packed_int& rhs ) {
		for ( unsigned int ii = 0; ii < Size; ++ii ) {
			m_data[ii] |= rhs.m_data[ii];
		}
		return *this;
	}

	constexpr packed_int& operator&=( const packed_int& rhs ) {
		for ( unsigned int ii = 0; ii < Size; ++ii ) {
			m_data[ii] &= rhs.m_data[ii];
		}
		return *this;
	}

	constexpr packed_int& operator^=( const packed_int& rhs ) {
		for ( unsigned int ii = 0; ii < Size; ++ii ) {
			m_data[ii] ^= rhs.m_data[ii];
		}
		return *this;
	}

private:
	value_type	m_data[Size];

};

} // gba

template <typename Container, unsigned int Size>
struct std::numeric_limits<gba::packed_int<Container, Size>> : public std::numeric_limits<Container> {

	static constexpr typename gba::packed_int<Container, Size>::machine_type min() {
		return is_signed ? gba::int_size_type<sizeof( Container ) * Size>::min() : 0;
	}

	static constexpr typename gba::packed_int<Container, Size>::machine_type max() {
		return is_signed ? gba::int_size_type<sizeof( Container ) * Size>::max() : gba::uint_size_type<sizeof( Container ) * Size>::max();
	}

	static constexpr auto lowest() {
		return min();
	}

};

#endif // define GBAXX_PACKED_INT_HPP
