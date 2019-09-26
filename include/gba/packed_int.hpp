#ifndef GBAXX_PACKED_INT_HPP
#define GBAXX_PACKED_INT_HPP

#include <type_traits>
#include <limits>
#include <array>

#include <gba/int_type.hpp>

namespace gba {

// TODO : Make volatile compatible
template <typename Container, unsigned int Size>
class [[gnu::packed]] packed_int {
	static_assert( std::numeric_limits<Container>::is_integer, "packed_int Container must be integer type" );
	static_assert( Size > 0, "packed_int Size cannot be zero" );
public:
	using value_type = Container;
	using machine_type = typename std::conditional<std::is_signed<value_type>::value, typename int_sized_type<sizeof( value_type ) * Size>::fast, typename uint_sized_type<sizeof( value_type ) * Size>::fast>::type;
	using size_type = typename std::array<value_type, Size>::size_type;

	constexpr packed_int() {}

	constexpr packed_int( machine_type value ) {
		operator=( value );
	}

	constexpr packed_int& operator=( machine_type value ) {
		for ( size_type ii = 0; ii < m_data.size(); ++ii ) {
			m_data[ii] = value >> ( ii * ( 8 * sizeof( value_type ) ) );
		}
		return *this;
	}

	constexpr operator machine_type() const {
		// Negative numbers have their high bits padded with 0xff
		machine_type value = ( std::is_signed<value_type>::value && sizeof( machine_type ) > ( sizeof( value_type ) * Size ) && m_data.back() < 0 ) ? static_cast<typename std::make_unsigned<machine_type>::type>( -1 ) << ( m_data.size() * ( 8 * sizeof( value_type ) ) ) : 0;

		for ( size_type ii = 0; ii < m_data.size(); ++ii ) {
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
		for ( size_type ii = 0; ii < m_data.size(); ++ii ) {
			m_data[ii] |= rhs.m_data[ii];
		}
		return *this;
	}

	constexpr packed_int& operator&=( const packed_int& rhs ) {
		for ( size_type ii = 0; ii < m_data.size(); ++ii ) {
			m_data[ii] &= rhs.m_data[ii];
		}
		return *this;
	}

	constexpr packed_int& operator^=( const packed_int& rhs ) {
		for ( size_type ii = 0; ii < m_data.size(); ++ii ) {
			m_data[ii] ^= rhs.m_data[ii];
		}
		return *this;
	}

private:
	std::array<value_type, Size>	m_data;

};

} // gba

template <typename Container, unsigned int Size>
struct std::numeric_limits<gba::packed_int<Container, Size>> : public std::numeric_limits<Container> {

	static constexpr typename gba::packed_int<Container, Size>::machine_type min() {
		return std::numeric_limits<Container>::is_signed ? gba::int_sized_type<sizeof( Container ) * Size>::min() : 0;
	}

	static constexpr typename gba::packed_int<Container, Size>::machine_type max() {
		return std::numeric_limits<Container>::is_signed ? gba::int_sized_type<sizeof( Container ) * Size>::max() : gba::uint_sized_type<sizeof( Container ) * Size>::max();
	}

	static constexpr auto lowest() {
		return min();
	}

};

template <typename Container, unsigned int Size>
struct std::is_integral<gba::packed_int<Container, Size>> : std::is_integral<Container> {};

template <typename Container, unsigned int Size>
struct std::is_arithmetic<gba::packed_int<Container, Size>> : std::is_arithmetic<Container> {};

#endif // define GBAXX_PACKED_INT_HPP
